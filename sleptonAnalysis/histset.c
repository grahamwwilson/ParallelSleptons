#ifndef HISTS
#define HISTS

#include <bitset>
#include "TH1D.h"
#include "TH2D.h"
#include "TLorentzVector.h"
#include "ROOT/TThreadedObject.hxx"
#include "TTreeReader.h"
#include "TTreeReaderValue.h"
#include "myselector.C"

using MyTH1D = ROOT::TThreadedObject<TH1D>;
using MyTH2D = ROOT::TThreadedObject<TH2D>;

class histset{
	
	public:
	   histset(std::string tag);	
	   void init(); 

	   void AnalyzeEntry(myselector& s); 

	 //bookeeping enumeration: (if we do this we dont need to worry about hist ptr copies and merging)

	 enum th1d_index{ind_METHist, ind_MSHist, ind_MISRHist, 
                     ind_CutFlowHist, ind_RISRHist, 
                     ind_LeptonsCategory, 
                     numTH1Hist};
	 enum th2d_index{numTH2Hist};
	
	   // make a big vector and load enumerated histograms onto the vector
	 std::vector<MyTH1D*> TH1Manager{};
	 std::vector<MyTH2D*> TH2Manager{};

	  //locate the histogram and perform ptr copying 
	  void FillTH1(int index, double x, double w);
	  void FillTH2(int index, double x, double y);
	
	  void WriteHist(std::string outputfilename, std::string TFileOption);

	//Tag for compiling multiple datasets into same file which share the same plots
	std::string _tag{}; 
	//this tag will automatically appended to the variable name in each histogram on write
	
	//cut sequence and event selection variables
	void initCounts();
	void processCutFile(std::string cutfile);
	void printSelectionTables(std::ofstream& f );

	std::vector<std::string> _cutsequence{"nocut"}; //cut names read from cut list
	std::vector<double> _npass{};//raw
	std::vector<double> _npassw{};//weighted
 	double _weight{};
	std::vector<double> _cutval{1.}; //cut values read from cut list

	//for now add absolute path of cut file
	std::string cutlist = "/home/gwwilson/slepton/ParallelSleptons/sleptonAnalysis/cutfile.list";

};

histset::histset(std::string tag = ""){
	_tag = tag; 
	
	 std::vector<ROOT::TThreadedObject<TH1D>*>  Manager1(numTH1Hist);
	TH1Manager=Manager1;

	 std::vector<ROOT::TThreadedObject<TH2D>*>  Manager2(numTH2Hist);
	TH2Manager=Manager2;

	init();
	processCutFile(cutlist);
	initCounts();

}
bool nocut(double& count, double weight){
	count = count + weight;
	return true;
	}
bool performcut(double& count, double weight,  double observedvalue, double cutvalue, std::function<bool(double,double)> func ){
	if( func(observedvalue, cutvalue) ){
		count = count + weight;
		return true;
	}
	return false;

}
///CUT LIST I/O
template <typename Out>
void split(const std::string &s, char delim, Out result) {
    std::istringstream iss(s);
    std::string item;
    while (std::getline(iss, item, delim)) {
        *result++ = item;
    }
}
std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}
void histset::processCutFile(std::string cutfile){
        ifstream file;
        file.open (cutfile);
        std::string line;
        while (getline(file, line)) {
        	std::vector<std::string> strs = split(line,  ' ');
                //push back cut names 
                _cutsequence.push_back(strs[0]);
                _cutval.push_back(std::stod(strs[1]));
         }
        for(int i=0; i< _cutsequence.size(); i++){
                std::cout<<_cutsequence.at(i)<<" "<<_cutval.at(i)<<" ";
        }
        std::cout<<std::endl;
	
        file.close();
}
//END CUT LIST I/O
void histset::initCounts(){
        std::vector<double> c(_cutsequence.size());	
	std::vector<double> cw(_cutsequence.size());

	for(unsigned int i=0; i<_cutsequence.size(); i++){
		c[i] = 0.;
		cw[i] = 0.;
	}
	_npass = c;
	_npassw = cw;
}
void histset::init(){

//init TH1D
	TH1Manager.at(ind_METHist) = new MyTH1D("METHist", "MET;GeV;Entries per 5 GeV bin", 140, 100.0, 800.0);
	TH1Manager.at(ind_MSHist) = new MyTH1D("MSHist", "MS;GeV;Entries per 5 GeV bin", 50, 0.0, 250.0);
	TH1Manager.at(ind_MISRHist) = new MyTH1D("MISRHist", "MISR;GeV;Entries per 5 GeV bin", 100, 0.0, 500.0);
	TH1Manager.at(ind_RISRHist) = new MyTH1D("RISRHist", "RISR; RISR ;Entries per 0.01 bin", 120, 0.0, 1.2);
	TH1Manager.at(ind_LeptonsCategory) = new MyTH1D("LeptonsCategory", 
        "Lepton Exclusive Multiplicity; Category ;Entries per bin", 5, -0.5, 4.5 );
// TODO  label bins of CutFlow
	TH1Manager.at(ind_CutFlowHist) = new MyTH1D("CutFlowHist", "CutFlow; Cut; Weighted events", 6, -1.5, 4.5);
}
template <class type>
void printvec(std::ofstream& f, std::vector<type> vec){
	for(unsigned int i=0; i< vec.size(); i++){
	f<<vec[i]<<" ";
	}
	f<<"\n";
}
void histset::printSelectionTables(std::ofstream& f){
	f<<_tag<<" "<<" "<<"no_w\n";
	printvec( f, _cutsequence );
	printvec( f, _npass );
	f<<"\n";

	f<<_tag<<" "<<" "<<"w\n";
	printvec( f, _cutsequence );
	//multiply by weight
	printvec( f, _npassw );
	f<<"\n";
}
void histset::FillTH1(int index, double x, double w=1){
	//we must make ptr copies for performance reasons when trying to fill a histogram
	auto myhist = TH1Manager.at(index)->Get();
	myhist->Fill(x,w);
}
void histset::FillTH2(int index, double x, double y){
	auto myhist = TH2Manager.at(index)->Get();
	myhist->Fill(x,y);
}
void histset::WriteHist(std::string outputfilename, std::string TFileOption){

	TFile* outfile = new TFile(outputfilename.c_str(),TFileOption.c_str());


	for(int i=0; i<numTH1Hist; i++){
		//do a check for entries, merge isnt safe on 0 entry histograms
		auto hptr = TH1Manager.at(i)->Get();		
		if(hptr->GetEntries() > 0){
			auto histmerged = TH1Manager.at(i)->Merge();
			TH1D* h = (TH1D*) histmerged->Clone();
			std::string hname(h->GetName());
			outfile->WriteObject(h, (_tag+hname).c_str() );
		}
		else{
			auto h = TH1Manager.at(i)->Get()->Clone();
			std::string hname(h->GetName());
			outfile->WriteObject(h, (_tag+hname).c_str() );
		}
	}

	for(int i=0; i<numTH2Hist; i++){
		auto hptr = TH2Manager.at(i)->Get();
		if(hptr->GetEntries() > 0){
			auto histmerged = TH2Manager.at(i)->Merge();
			TH2D* h = (TH2D*) histmerged->Clone();
			std::string hname(h->GetName());
			outfile->WriteObject(h,(_tag+hname).c_str() );
		}
		else{
			auto h = TH2Manager.at(i)->Get()->Clone();
			std:;string hname(h->GetName());
			outfile->WriteObject(h, (_tag+hname).c_str() );
		}
	}
	outfile->Close();	

}
void histset::AnalyzeEntry(myselector& s){
   	
	//Always make a local copy, if it is a value dereference. 
    //If you don't do this, scope/dereferencing will get really weird, 
    // clunky, and unmanageable
	//have to auto& or myreader will try to register copy of 
    //the readerarray ptr

    double PI =4.0*atan(1.0);

	auto weight = *(s.weight);
 	_weight = weight;
    double w = 137.0*_weight;    //Normalize to 137 inverse fb

	//reco leptons
	auto Nlep = *(s.Nlep);
	auto& PT_lep = s.PT_lep;
	auto& Eta_lep = s.Eta_lep;
	auto& Phi_lep = s.Phi_lep;
    auto& ID_lep = s.ID_lep;
	auto& Charge_lep = s.Charge_lep;
	auto& PDGID_lep = s.PDGID_lep;
	auto& M_lep = s.M_lep;
    auto& MiniIso_lep = s.MiniIso_lep;

	//susy variables for category 0 (leptons to S)
	auto& Njet_ISR = s.Njet_ISR[0];
	auto& Njet_S = s.Njet_S[0];
	auto& Nlep_S = s.Nlep_S[0];
	auto& MS = s.MS[0];
	auto& PS = s.PS[0];
	auto& PTISR = s.PTISR[0];
	auto& RISR = s.RISR[0];
	auto& MISR = s.MISR[0];

	auto MET = *(s.MET);
	auto MET_phi = *(s.MET_phi);
	auto genMET = *(s.genMET);
	auto genMET_phi = *(s.genMET_phi);

    auto Nbjet = *(s.Nbjet);
    auto Nmu = *(s.Nmu);
    auto Nele = *(s.Nele);
    auto Is_1L = *(s.Is_1L);
    auto Is_2L = *(s.Is_2L);
    auto Is_3L = *(s.Is_3L);
    auto Is_4L = *(s.Is_4L);

//variables needed for gen level susy stuff
    auto genNsusy = *(s.genNsusy);
    auto& genPDGID_susy = s.genPDGID_susy;
    auto& genPT_susy = s.genPT_susy;
    auto& genEta_susy = s.genEta_susy;
    auto& genPhi_susy = s.genPhi_susy;
    auto& genM_susy = s.genM_susy;

//gen leptons (we dont require susy)
    auto genNlep = *(s.genNlep);
    auto& genPDGID_lep = s.genPDGID_lep;
    auto& genPT_lep = s.genPT_lep;
    auto& genEta_lep = s.genEta_lep;
    auto& genPhi_lep = s.genPhi_lep;
    auto& genM_lep = s.genM_lep;

    //loop over all generator leptons
    if( genNlep > 0){      
       for(int i=0; i<genPT_lep.GetSize(); i++){
           TLorentzVector v;
           v.SetPtEtaPhiM(genPT_lep[i], genEta_lep[i], genPhi_lep[i], genM_lep[i]);
           cout << "genlep : " << i << " " << genPDGID_lep[i] << " " << v.Px() << " " << v.Py() << " " << v.Pz() << " " << v.M() << endl;
       }
    }
    //loop over all generator sparticles
    if( genNsusy > 0){      
       for(int i=0; i<genPT_susy.GetSize(); i++){
           TLorentzVector v;
           v.SetPtEtaPhiM(genPT_susy[i], genEta_susy[i], genPhi_susy[i], genM_susy[i]);
           cout << "gensusy: " << i << " " << genPDGID_susy[i] << " " << v.Px() << " " << v.Py() << " " << v.Pz() << " " << v.M() << endl;
       }
    }

    double MET_x = MET*cos(MET_phi);
    double MET_y = MET*sin(MET_phi);

// x and y momentum components of each lepton
    double px[4];
    double py[4];
    for(int i=0; i<4; i++){
        if(i<Nlep){
           px[i] = PT_lep[i]*cos(Phi_lep[i]);
           py[i] = PT_lep[i]*sin(Phi_lep[i]);
        }
        else{
           px[i] = 0.0;
           py[i] = 0.0;
        }
    }

// reconstruct tau-tau invariant mass squared under the collinear approximation
// First solve for the (xi0, xi1) vector that satisfies
// xi0*px[0] + xi1*px[1] = MET_x
// xi0*py[0] + xi1*py[1] = MET_y
// Ax = y with solution of x = A^-1 y

    double det =  px[0]*py[1] - px[1]*py[0];
    double xi0 =  py[1]*MET_x - px[1]*MET_y;
    double xi1 = -py[0]*MET_x + px[0]*MET_y;
    if(abs(det)<1.0e-8)cout << "Really small determinant ... " << det << endl;
    if(Nlep>=2){
       xi0 = xi0/det;
       xi1 = xi1/det;
       cout << "Found xi0, xi1 = " << xi0 << " " << xi1 << endl;
       TLorentzVector v0,v1,vMET,vgenMET;
       v0.SetPtEtaPhiM(PT_lep[0],Eta_lep[0],Phi_lep[0],M_lep[0]);
       v1.SetPtEtaPhiM(PT_lep[1],Eta_lep[1],Phi_lep[1],M_lep[1]);
       vMET.SetPtEtaPhiM(MET,0.0,MET_phi,0.0);  // Massless transverse 4-vector
       vgenMET.SetPtEtaPhiM(genMET,0.0,genMET_phi,0.0);  // Massless transverse 4-vector

       TLorentzVector vn0,vn1;
       if(xi0>0.0){
          vn0.SetPtEtaPhiM(xi0*PT_lep[0],Eta_lep[0],Phi_lep[0],0.0);
       }
       else{
          vn0.SetPtEtaPhiM(-xi0*PT_lep[0],-Eta_lep[0],PI+Phi_lep[0],0.0);
       }
       if(xi1>0.0){
          vn1.SetPtEtaPhiM(xi1*PT_lep[1],Eta_lep[1],Phi_lep[1],0.0);
       }
       else{
          vn1.SetPtEtaPhiM(-xi1*PT_lep[1],-Eta_lep[1],PI+Phi_lep[1],0.0);
       }
       TLorentzVector vtau0,vtau1;
       vtau0 = v0 + vn0;
       vtau1 = v1 + vn1;
       TLorentzVector vtt;
       vtt = vtau0 + vtau1;
       double mtautausq = vtt.M2();
       double mtautau = vtt.M();   // should return -ve value if mass-squared is negative

       cout << "MET:    " << vMET.Px() << " " << vMET.Py() << " " << vMET.Pz() << " " << vMET.M() << endl;
       cout << "genMET:    " << vgenMET.Px() << " " << vgenMET.Py() << " " << vgenMET.Pz() << " " << vgenMET.M() << endl;
       cout << "Leptons " << endl;
       cout << "L0:     " << v0.Px() << " " << v0.Py() << " " << v0.Pz() << " " << v0.M() << endl;
       cout << "L1:     " << v1.Px() << " " << v1.Py() << " " << v1.Pz() << " " << v1.M() << endl;
       cout << "n0:     " << vn0.Px() << " " << vn0.Py() << " " << vn0.Pz() << " " << vn0.M() << endl;
       cout << "n1:     " << vn1.Px() << " " << vn1.Py() << " " << vn1.Pz() << " " << vn1.M() << endl;
       cout << "tau0:   " << vtau0.Px() << " " << vtau0.Py() << " " << vtau0.Pz() << " " << vtau0.M() << endl;
       cout << "tau1:   " << vtau1.Px() << " " << vtau1.Py() << " " << vtau1.Pz() << " " << vtau1.M() << endl;
       cout << "tautau: " << vtt.Px() << " " << vtt.Py() << " " << vtt.Pz() << " " << vtt.M() << endl;
 
       cout << "tau-tau kinematics: " << det << " " << xi0 
            << " " << xi1 << " M2: " << mtautausq << " M: " 
            << mtautau << endl; 

    }


// Dump variables
    cout << "Is_Lepton: " << Is_1L << " " << Is_2L << " " << Is_3L << " " << Is_4L << endl;
    cout << "Check sizes " << Nlep << endl;
    cout << "PT " << PT_lep.GetSize() << endl;
    cout << "Eta " << Eta_lep.GetSize() << endl;
    cout << "Phi " << Phi_lep.GetSize() << endl;

    enum cutnames{kLeptons, kMET, kbjet, kPTISR, kRISR, NCUTS};
// https://www.geeksforgeeks.org/c-bitset-and-its-application/
    bitset<NCUTS> bncuts{};
    bitset<NCUTS> bpcuts{};

// First method for cut accounting (as I used to use ..)
// Disadvantage is that we specify things using negative logic.
    unsigned int cutmask = 0; // Events passing ALL cuts => cutmask=0
    if( !Is_2L )        cutmask +=  1;
    if( MET < 120.0 )   cutmask +=  2;
    if( Nbjet > 0 )     cutmask +=  4; 
    if( PTISR < 200.0 ) cutmask +=  8;
    if( RISR < 0.95 )   cutmask += 16;

// Second method using bitset with negative logic
    if( !Is_2L )        bncuts[kLeptons] = 1;
    if( MET < 120.0 )   bncuts[kMET] = 1;
    if( Nbjet > 0 )     bncuts[kbjet] = 1; 
    if( PTISR < 200.0 ) bncuts[kPTISR] = 1;
    if( RISR < 0.95 )   bncuts[kRISR]= 1;

// Third method using bitset with positive logic
    if( Is_2L )         bpcuts[kLeptons] = 1;
    if( MET > 120.0 )   bpcuts[kMET] = 1;
    if( Nbjet == 0 )    bpcuts[kbjet] = 1; 
    if( PTISR > 200.0 ) bpcuts[kPTISR] = 1;
    if( RISR > 0.95 )   bpcuts[kRISR] = 1;
// Also could use bpcuts.set(kRISR) syntax

// Compare
    cout << "cutmask: " << cutmask 
         << " bncuts: " << bncuts 
         << " bpcuts: " << bpcuts << endl;

// Lepton categories. Firstly multiplicity.
    FillTH1(ind_LeptonsCategory, 0.0, w);  // All events
    if( Is_1L ) FillTH1(ind_LeptonsCategory, 1.0, w);
    if( Is_2L ) FillTH1(ind_LeptonsCategory, 2.0, w);
    if( Is_3L ) FillTH1(ind_LeptonsCategory, 3.0, w);
    if( Is_4L ) FillTH1(ind_LeptonsCategory, 4.0, w);

    if(bpcuts.all()){
// Require all cuts are passed
       FillTH1(ind_METHist, MET, w);
	   FillTH1(ind_MSHist, MS, w);
	   FillTH1(ind_MISRHist, MISR, w);
    }

    if(bpcuts.all() || cutmask==16) FillTH1(ind_RISRHist, RISR, w);

// Cut Flow
    FillTH1(ind_CutFlowHist, -1.0, w);
    for (int i=0; i<NCUTS; i++){
       bool pass = true;
       for (int j=0; j<=i; j++){
          if(!bpcuts.test(j))pass = false;
       }
       if(pass)FillTH1(ind_CutFlowHist, i, w);
    }

	//event selection
	//iterate over cut sequence, apply operators and values
	bool pass;
        for(unsigned int i=0; i<_cutsequence.size(); i++){
                std::string cut = _cutsequence.at(i);
		double cutvalue = _cutval.at(i);

		if(cut.compare("nocut")==0){
			pass = nocut(_npass[i], 1);
			pass = nocut(_npassw[i], w);
		}
		if( cut.compare("minMET")==0){
			pass = performcut( _npass[i], 1, MET, cutvalue, std::greater<double>());
			pass = performcut( _npassw[i], w, MET, cutvalue, std::greater<double>());		
                        if(!pass) break;
                }
                if( cut.compare("minMu")==0){
               		pass = performcut( _npass[i],1, Nmu, cutvalue, std::greater_equal<double>());
                        pass = performcut( _npassw[i], w, Nmu, cutvalue, std::greater_equal<double>());
			if(!pass) break;
		}
             
	}//end cut sequence loop	


}
#endif
