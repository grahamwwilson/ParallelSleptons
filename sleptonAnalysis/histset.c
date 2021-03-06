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
#include <boost/dynamic_bitset.hpp>
#include <boost/algorithm/string.hpp>

using MyTH1D = ROOT::TThreadedObject<TH1D>;
using MyTH2D = ROOT::TThreadedObject<TH2D>;

//ROOT::TThreadedObject<int> nseen;
//int nseen = 0;  // TODO FIX could be race condition

class histset{
	
	public:
	   histset(std::string tag);	
	   void init(); 

	   void AnalyzeEntry(myselector& s); 

	   //bookeeping enumeration: (if we do this we dont need to worry about hist ptr copies and merging)

       enum th1d_index{ind_METHist, ind_MS1Hist, ind_MISR1Hist, 
                       ind_CutFlowHist, ind_CutFlowHist2, ind_RISR0Hist, ind_MLLHist,
                       ind_ECutFlowHist, ind_ECutFlowHist2, 
                       ind_CutFlowHist3, ind_ECutFlowHist3, ind_MCutFlowHist3, 
                       ind_CategoryHist, ind_MperpHist, ind_MperpHist2, ind_MperpHist3,
                       ind_MTTHist, ind_MTTpHist, ind_LeptonsCategory,
                       ind_NjetHist, ind_PTISR0Hist, ind_PTISR1Hist, 
                       ind_RISR1Hist, 
                       ind_NlepS1Hist, ind_mNlepabHist, ind_MaxSIP3DHist,
                       ind_WeightHist, ind_MCutFlowHist2, ind_IsoHist, ind_NullHist,
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
	//this tag will be automatically prepended to the variable name in each histogram on write
	
	//cut sequence and event selection variables
	   void initCounts();
	   void processCutFile(std::string cutfile);
	   void printSelectionTables(std::ofstream& f );

	   std::vector<std::string> _cutsequence{"nocut"}; //cut names read from cut list
	   std::vector<double> _npass{};//raw
	   std::vector<double> _npassw{};//weighted
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

void PrintCuts(const boost::dynamic_bitset<uint16_t> &mybits ){

// Here we assume that the passed bitset is the one corresponding 
// to our current list. 

   const char *cutStrings[ ] = {" >= 2 leptons ",
                                " ID'd lepton pair ",
                                " Isolated lepton pair ",
                                " Prompt lepton pair ", 
                                " Same-flavor lepton pair ", 
                                " Opposite-sign lepton pair ",
                                " Exactly two leptons ",
                                " No b-jets ",
                                " MET > 200 GeV ",
                                " PTISR0 > 200 GeV ", 
                                " RISR0 > 0.95 "};

   unsigned int num_bits = mybits.size();
   cout << "   " << endl;
   cout << " Mask:  " << mybits.to_ulong() << endl;
      for (unsigned int i=0; i<num_bits; i++){
         string mystring = cutStrings[i];
         if (mybits.test(i)) {
            cout << mystring << " PASS " << endl;
         }
         else{
            cout << mystring << " FAIL " << endl;
         }
      }
      cout << " -----------cutStrings---------------------" << endl;
}

void PrintCuts2(const boost::dynamic_bitset<uint16_t> &mybits){

// Here we assume that the passed bitset is the one corresponding 
// to our current list. 

   const char *cutStrings[ ] = {" >= 2 leptons ",
                                " ID'd lepton pair ",
                                " Isolated lepton pair ",
                                " Prompt lepton pair ", 
                                " Same-flavor lepton pair ", 
                                " Opposite-sign lepton pair ",
                                " Exactly two leptons ",
                                " No b-jets ",
                                " MET > 200 GeV ",
                                " Njet > 0 ",
                                " Njet_S1 == 0 ", 
                                " PTISR1 > 250 GeV ", 
                                " RISR1 > 0.95 "};

   unsigned int num_bits = mybits.size();
   cout << "   " << endl;
   cout << " Mask:  " << mybits.to_ulong() << endl;
   for (unsigned int i=0; i<num_bits; i++){
       string mystring = cutStrings[i];
       if (mybits.test(i)) {
          cout << mystring << " PASS " << endl;
       }
       else{
          cout << mystring << " FAIL " << endl;
       }
   }
      cout << " -----------cutStrings2--------------------" << endl;
}

void PrintCuts3(const boost::dynamic_bitset<uint16_t> &mybits){

// Here we assume that the passed bitset is the one corresponding 
// to our current list. 
/*
    boost::dynamic_bitset<uint16_t> becuts(numCuts2);
    if( Nlep >= 2 )                becuts.set(kLeptons);
    if( Nidentified >= 2)          becuts.set(kID);
    if( Nisolated >= 2)            becuts.set(kISO);
    if( Nprompt >= 2)              becuts.set(kPROMPT);
    if( Nele >= 2 || Nmu >= 2 )    becuts.set(kSF);
    if( Nnegl > 0 && Nposl > 0)    becuts.set(kOS);
    if( Nlep == 2 )                becuts.set(k2L);
    if( Nbjet_ISR1 == 0 )          becuts.set(kbjet);      //Erich
    if( MET > 200.0 )              becuts.set(kMET); 
    if( RISR1 <= 0.98 )            becuts.set(kNjetISR1);  //Erich
    if( Njet_S1 + NSV_S1 == 0 )    becuts.set(kNjetS1);    //Erich
    if( PTISR1 > 200.0 )           becuts.set(kPTISR1);    //Erich
    if( RISR1 > 0.95 )             becuts.set(kRISR1);
*/

   const char *cutStrings[ ] = {" >= 2 leptons ",
                                " ID'd lepton pair ",
                                " Isolated lepton pair ",
                                " Prompt lepton pair ", 
                                " Same-flavor lepton pair ", 
                                " Opposite-sign lepton pair ",
                                " Exactly two leptons ",
                                " No b-jets in ISR system",
                                " MET > 200 GeV ",
                                " RISR <= 0.98 ",
                                " NjetS1 + NSVS1 = 0 ", 
                                " PTISR1 > 200 GeV ", 
                                " RISR1 > 0.95 "};

   unsigned int num_bits = mybits.size();
   cout << "   " << endl;
   cout << " Mask:  " << mybits.to_ulong() << endl;
   for (unsigned int i=0; i<num_bits; i++){
       string mystring = cutStrings[i];
       if (mybits.test(i)) {
          cout << mystring << " PASS " << endl;
       }
       else{
          cout << mystring << " FAIL " << endl;
       }
   }
      cout << " -----------cutStrings3--------------------" << endl;
}



bool xcut(const boost::dynamic_bitset<uint16_t> &mybits, int kCut){
// New style with boost:dynamic_bitset.
// Read in bitset with all the cuts that are satisfied
// and check whether all the cuts are satisfied or the event only 
// fails the one specific cut

// With dynamic_bitset need to figure out the current size

   unsigned int num_bits = mybits.size();

   boost::dynamic_bitset<uint16_t> bpcuts(num_bits);
   boost::dynamic_bitset<uint16_t> bncuts(num_bits);

   bpcuts = mybits;
   bncuts = bpcuts.flip();

   bool pass = false;
   if(bpcuts.all()){
      pass = true;
   }
   else{
      unsigned long testvalue = bncuts.to_ulong();
      if(testvalue == pow(2, kCut)) pass = true;
   } 
   return pass;
}

bool xxcut(const boost::dynamic_bitset<uint16_t> &mybits, int kCut1, int kCut2){
// New style with boost:dynamic_bitset.
// Read in bitset with all the cuts that are satisfied
// and check whether the event would pass a selection with 
// cuts kCut1 and kCut2 removed.

// With dynamic_bitset need to figure out the current size

   unsigned int num_bits = mybits.size();

   boost::dynamic_bitset<uint16_t> bpcuts(num_bits);
   boost::dynamic_bitset<uint16_t> bncuts(num_bits);

   bpcuts = mybits;
   bncuts = bpcuts.flip();

   bool pass = false;
   if(bpcuts.all()){
      pass = true;
   }
   else{
      unsigned long testvalue = bncuts.to_ulong();
      if ( testvalue == pow(2, kCut1) ) pass = true;
      if ( testvalue == pow(2, kCut2) ) pass = true;
      if ( testvalue == pow(2, kCut1) + pow(2, kCut2) ) pass = true;
   } 
   return pass;
}


/*
bool ecut2(const boost::dynamic_bitset<uint16_t> &mybits, int kCut){
// New style with boost:dynamic_bitset.
// Check whether all except one cut is satisfied.
// ie. assess how many events would recovered if this cut was removed

   unsigned int num_bits = mybits.size();

   boost::dynamic_bitset<uint16_t> bpcuts(num_bits);
   boost::dynamic_bitset<uint16_t> bncuts(num_bits);

   bpcuts = mybits;
   bncuts = mybits.flip();

   bool pass = false;
   unsigned long testvalue = bncuts.to_ulong();
   if(testvalue == pow(2, kCut)) pass = true; 
   return pass;
}
*/

bool ecut(const boost::dynamic_bitset<uint16_t> &mybits, int kCut){
// New style with boost:dynamic_bitset.
// Check whether all except one cut is satisfied.
// ie. assess how many events would recovered if this cut was removed

   unsigned int num_bits = mybits.size();

   boost::dynamic_bitset<uint16_t> bpcuts(num_bits);
   boost::dynamic_bitset<uint16_t> bncuts(num_bits);

   bpcuts = mybits;
   bncuts = mybits;
   bncuts.flip();
//   bncuts = mybits.flip();  // this would modify mybits - so does not obey the const specification

   bool pass = false;
   unsigned long testvalue = bncuts.to_ulong();
   if(testvalue == pow(2, kCut)) pass = true; 
   return pass;
}

bool ecut3(const boost::dynamic_bitset<uint16_t> &mybits, int kCut){
// New style with boost:dynamic_bitset.
// Check whether all except one cut is satisfied.
// ie. assess how many events would recovered if this cut was removed

   unsigned int num_bits = mybits.size();
   boost::dynamic_bitset<uint16_t> bpcuts(num_bits);
   bpcuts = mybits;
   bool pass = false;
   unsigned long testvalue = (bpcuts.flip()).to_ulong();
   if(testvalue == pow(2, kCut)) pass = true; 
   return pass;
}

bool nocut(double& count, double weight){
	count = count + weight;
	return true;
	}

bool performcut(double& count, double weight,  double observedvalue, 
          double cutvalue, std::function<bool(double,double)> func ){
	if( func(observedvalue, cutvalue) ){
		count = count + weight;
		return true;
	}
	return false;
}

bool GetMasses(std::string s, int* MP, int* MC){
//
// Read input string for SMS and background samples.
// Use the boolean return argument to signify 
// signal (true) and background (false).
// The parent and child masses for signal are returned using pointers.
//
// The masses are only valid when this function returns true.
//
   bool pass;
   std::vector<std::string> results;
   boost::split(results, s, [](char c){return c == '_';});

   if(results.size()==3){   
      pass = true;    // SMS files should be SMS_400_200 etc
      *MP = std::stoi(results[1]);
      *MC = std::stoi(results[2]);
   }
   else{
      pass = false;   // Background file
      *MP = -999;
      *MC = -999;
   }
   return pass;
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
	TH1Manager.at(ind_MS1Hist) = new MyTH1D("MS1Hist", "MS1;GeV;Entries per 5 GeV bin", 50, 0.0, 250.0);
	TH1Manager.at(ind_MISR1Hist) = new MyTH1D("MISR1Hist", "MISR1;GeV;Entries per 5 GeV bin", 100, 0.0, 500.0);
	TH1Manager.at(ind_MLLHist) = new MyTH1D("MLLHist", "MLL;GeV;Entries per 5 GeV bin", 100, 0.0, 500.0);
	TH1Manager.at(ind_MTTHist) = new MyTH1D("MTTHist", "Mtautau;GeV;Entries per 5 GeV bin", 102, -10.0, 500.0);
	TH1Manager.at(ind_MTTpHist) = new MyTH1D("MTTpHist", "Mtautaup;GeV;Entries per 5 GeV bin", 200, -500.0, 500.0);
	TH1Manager.at(ind_RISR0Hist) = new MyTH1D("RISR0Hist", "RISR0; RISR0 ;Entries per 0.01 bin", 120, 0.0, 1.2);
	TH1Manager.at(ind_PTISR0Hist) = new MyTH1D("PTISR0Hist", "PTISR0; PTISR0 (GeV);Entries per 10 GeV bin", 100, 0.0, 1000.0);
	TH1Manager.at(ind_RISR1Hist) = new MyTH1D("RISR1Hist", "RISR1; RISR1 ;Entries per 0.01 bin", 120, 0.0, 1.2);
	TH1Manager.at(ind_PTISR1Hist) = new MyTH1D("PTISR1Hist", "PTISR1; PTISR1 (GeV);Entries per 10 GeV bin", 100, 0.0, 1000.0);
	TH1Manager.at(ind_NjetHist) = new MyTH1D("NjetHist", "Njet; Njet ;Entries per multiplicity bin", 10, -0.5, 9.5);
	TH1Manager.at(ind_LeptonsCategory) = new MyTH1D("LeptonsCategory", 
        "Lepton Exclusive Multiplicity; Category ;Entries per bin", 5, -0.5, 4.5 );
	TH1Manager.at(ind_CutFlowHist) = new MyTH1D("CutFlowHist", "CutFlow; Cut; Weighted events", 12, -1.5, 10.5);

	TH1Manager.at(ind_CutFlowHist2) = new MyTH1D("CutFlowHist2", "CutFlow; Cut; Weighted events", 14, -1.5, 12.5);
	TH1Manager.at(ind_MCutFlowHist2) = new MyTH1D("MCutFlowHist2", "MCutFlow; Cut; Weighted events", 8192, -0.5, 8191.5);
	TH1Manager.at(ind_ECutFlowHist2) = new MyTH1D("ECutFlowHist2", "ECutFlow; Cut; Weighted events", 14, -1.5, 12.5);

	TH1Manager.at(ind_CutFlowHist3)  = new MyTH1D("CutFlowHist3", "CutFlow; Cut; Weighted events", 15, -1.5, 13.5);
	TH1Manager.at(ind_MCutFlowHist3) = new MyTH1D("MCutFlowHist3", "MCutFlow; Cut; Weighted events", 16384, -0.5, 16383.5);
	TH1Manager.at(ind_ECutFlowHist3) = new MyTH1D("ECutFlowHist3", "ECutFlow; Cut; Weighted events", 15, -1.5, 13.5);

	TH1Manager.at(ind_MperpHist) = new MyTH1D("MperpHist", "Mperp; Mperp (GeV); Weighted events", 50, 0.0, 50.0);
	TH1Manager.at(ind_MperpHist2) = new MyTH1D("MperpHist2", "Mperp; Mperp (GeV); Weighted events", 50, 0.0, 50.0);
	TH1Manager.at(ind_MperpHist3) = new MyTH1D("MperpHist3", "Mperp; Mperp (GeV); Weighted events", 50, 0.0, 50.0);

	TH1Manager.at(ind_ECutFlowHist) = new MyTH1D("ECutFlowHist", "ECutFlow; Cut; Weighted events", 12, -1.5, 10.5);

	TH1Manager.at(ind_CategoryHist) = new MyTH1D("CategoryHist", "Categories; Category; Weighted events", 20, -0.5, 19.5);
	TH1Manager.at(ind_NlepS1Hist) = new MyTH1D("NlepS1Hist", "Nleptons S1; Nleptons S1; Weighted events", 6, -0.5, 5.5);
	TH1Manager.at(ind_mNlepabHist) = new MyTH1D("mNlepabHist", "min(Nlepab) S1; min(Nlepab) S1; Weighted events", 6, -0.5, 5.5);
	TH1Manager.at(ind_MaxSIP3DHist) = new MyTH1D("MaxSIP3DHist", "max(SIP3D); max(SIP3D); Weighted events", 50, 0.0, 10.0);
	TH1Manager.at(ind_WeightHist) = new MyTH1D("WeightHist", "Weight; Weight; Weighted events", 2000, -1.0, 1.0);
	TH1Manager.at(ind_IsoHist) = new MyTH1D("IsoHist", "Isolation; Isolation (GeV); Weighted events", 40, 0.0, 20.0);
	TH1Manager.at(ind_NullHist) = new MyTH1D("NullHist", "Control for no entries; Variable; Weighted events", 40, 0.0, 20.0);

//                       ind_NlepS1Hist, ind_mNlepabHist,
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

    auto tid = ROOT::Internal::TThreadedObjectUtils::GetTThreadedObjectIndex();

    cout << "WriteHist tid " << tid << endl;

	TFile* outfile = new TFile(outputfilename.c_str(),TFileOption.c_str());

//REMOVE ZERO ENTRY CHECKS AS THEY CAUSE NON-ZERO PARTS TO BE OMITTED
	for(int i=0; i<numTH1Hist; i++){
		//do a check for entries, merge isnt safe on 0 entry histograms
		auto hptr = TH1Manager.at(i)->Get();		
        cout << "Histogram " << i << endl;
        hptr->Print();
	    auto histmerged = TH1Manager.at(i)->Merge();
		TH1D* h = (TH1D*) histmerged->Clone();
		std::string hname(h->GetName());
		outfile->WriteObject(h, (_tag+hname).c_str() );
	}

	for(int i=0; i<numTH2Hist; i++){
		auto hptr = TH2Manager.at(i)->Get();
			auto histmerged = TH2Manager.at(i)->Merge();
			TH2D* h = (TH2D*) histmerged->Clone();
			std::string hname(h->GetName());
			outfile->WriteObject(h,(_tag+hname).c_str() );
	}
	outfile->Close();	

}
void histset::AnalyzeEntry(myselector& s){
   	
    bool lprint = false;
    auto tid = ROOT::Internal::TThreadedObjectUtils::GetTThreadedObjectIndex();

/*
    if(tid==1)cout << "Saw tag " << _tag << endl;
    int MP,MC;
    bool SignalSample = GetMasses(_tag, &MP, &MC);
    if(tid==1){
       if(SignalSample){
          cout << "Signal: MP = " << MP << endl;
          cout << "Signal: MC = " << MC << endl;
       }
       else{
          cout << "Bkgd sample" << endl;
       }
    }
*/

    double PI =4.0*atan(1.0);

    #include "mylocaltree.h"

    double w = 137.0*weight;    //Normalize to 137 inverse fb
    if(genNsusy>0.0)w*=2.76;

    double genMET_x = genMET*cos(genMET_phi);
    double genMET_y = genMET*sin(genMET_phi);
    double MET_x = MET*cos(MET_phi);
    double MET_y = MET*sin(MET_phi);

    int Nposl = 0;
    int Nnegl = 0;
    int Nidentified = 0;
    int Nisolated = 0;
    int Nprompt = 0;
// Count leptons: positive, negative, IDd, isolated, prompt.
    double maxsip3d = 0.0;
    double maxisovalue = 0.0;
    for(int i=0; i<Nlep; i++){
        if(ID_lep[i] >=3)Nidentified +=1;
        if(MiniIso_lep[i]*PT_lep[i] < 6.0)Nisolated +=1;
        if(MiniIso_lep[i]*PT_lep[i] > maxisovalue)maxisovalue = MiniIso_lep[i]*PT_lep[i];
        if(abs(SIP3D_lep[i]) < 4.0)Nprompt +=1;
        if(abs(SIP3D_lep[i]) > maxsip3d) maxsip3d = abs(SIP3D_lep[i]);
        if(Charge_lep[i] >= 1){
           Nposl += 1;
        }
        else if(Charge_lep[i] <= -1){
           Nnegl += 1;
        }
        else{
           cout << "Funny charge ?? " << i << " " << Charge_lep[i] << endl;
        }
    }
    
// Move all the basic cuts etc here. 
// The order of application is immaterial. The enum definition that 
// defines numCuts and the bitset indices is currently global.
// (this was necessary when using STL bitset - but is no longer).

    enum cutNames {kLeptons=0, kID=1, kISO=2, kPROMPT=3, kSF=4, kOS=5,
                   k2L=6, kbjet=7, kMET=8, kPTISR0=9, kRISR0=10, 
                   numCuts=11};
//    enum cutNames2{kNlepS1=9, kNjetS1=10, kPTISR1=11, kRISR1=12, 
//                   numCuts2=13};
    enum cutNames2{kNjetISR1=9, kNjetS1=10, kPTISR1=11, kRISR1=12, 
                   numCuts2=13};

    enum cutNames3{kbjetISR1 = 7, kSVS1=9, kRISRH=13, 
                   numCuts3=14};

    boost::dynamic_bitset<uint16_t> bpcuts(numCuts);
    if( Nlep >= 2 )                bpcuts.set(kLeptons);
    if( Nidentified >= 2)          bpcuts.set(kID);
    if( Nisolated >= 2)            bpcuts.set(kISO);
    if( Nprompt >= 2)              bpcuts.set(kPROMPT);
    if( Nele >= 2 || Nmu >= 2 )    bpcuts.set(kSF);
    if( Nnegl > 0 && Nposl > 0)    bpcuts.set(kOS);
    if( Nlep == 2 )                bpcuts.set(k2L);
    if( Nbjet == 0 )               bpcuts.set(kbjet);
    if( MET > 200.0 )              bpcuts.set(kMET);
    if( PTISR0 > 200.0 )           bpcuts.set(kPTISR0);
    if( RISR0 > 0.95 )             bpcuts.set(kRISR0);

    boost::dynamic_bitset<uint16_t> bcuts(numCuts2);
    if( Nlep >= 2 )                bcuts.set(kLeptons);
    if( Nidentified >= 2)          bcuts.set(kID);
    if( Nisolated >= 2)            bcuts.set(kISO);
    if( Nprompt >= 2)              bcuts.set(kPROMPT);
    if( Nele >= 2 || Nmu >= 2 )    bcuts.set(kSF);
    if( Nnegl > 0 && Nposl > 0)    bcuts.set(kOS);
    if( Nlep == 2 )                bcuts.set(k2L);
    if( Nbjet == 0 )               bcuts.set(kbjet);
    if( MET > 200.0 )              bcuts.set(kMET);
    if( Njet_ISR1 > 0 )            bcuts.set(kNjetISR1);
    if( Njet_S1 == 0 )             bcuts.set(kNjetS1);
    if( PTISR1 > 250.0 )           bcuts.set(kPTISR1);
    if( RISR1 > 0.95 )             bcuts.set(kRISR1);

// Nbjet_ISR1
// N_S[1] = Njet_S[1] + NSV_S[1]

// https://www.geeksforgeeks.org/c-boostdynamic_bitset-class-with-examples/

    boost::dynamic_bitset<uint16_t> becuts(numCuts3);
    if( Nlep >= 2 )                becuts.set(kLeptons);
    if( Nidentified >= 2)          becuts.set(kID);
    if( Nisolated >= 2)            becuts.set(kISO);
    if( Nprompt >= 2)              becuts.set(kPROMPT);
    if( Nele >= 2 || Nmu >= 2 )    becuts.set(kSF);
    if( Nnegl > 0 && Nposl > 0)    becuts.set(kOS);
    if( Nlep == 2 )                becuts.set(k2L);
    if( Nbjet_ISR1 == 0 )          becuts.set(kbjetISR1);  //Erich - not really different
    if( MET > 200.0 )              becuts.set(kMET); 
    if( NSV_S1 == 0 )              becuts.set(kSVS1);      //Erich 
    if( Njet_S1 == 0 )             becuts.set(kNjetS1);   
    if( PTISR1 > 200.0 )           becuts.set(kPTISR1);    //Erich
    if( RISR1 > 0.95 )             becuts.set(kRISR1);
    if( RISR1 <= 0.98 )            becuts.set(kRISRH);     //Erich

    const boost::dynamic_bitset<uint16_t> cbecuts(numCuts3, becuts.to_ulong());

    bool elepair = (Nele >=2);
    bool mupair = (Nmu >=2);

    if(bpcuts.all())FillTH1(ind_CategoryHist,0.0,w);
    if(bcuts.all())FillTH1(ind_CategoryHist,1.0,w);
    if(bcuts.all()&&bpcuts.all())FillTH1(ind_CategoryHist,2.0,w);
    if(bcuts.all()||bpcuts.all())FillTH1(ind_CategoryHist,3.0,w);
    if(bpcuts.all() && elepair )FillTH1(ind_CategoryHist,4.0,w);
    if(bpcuts.all() && mupair  )FillTH1(ind_CategoryHist,5.0,w);
    if(bcuts.all() && elepair  )FillTH1(ind_CategoryHist,6.0,w);
    if(bcuts.all() && mupair   )FillTH1(ind_CategoryHist,7.0,w);

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
// ie. explains the MET in terms of two neutrino 4-vectors.
// Ax = y with solution of x = A^-1 y

// this only makes sense if Nlep>=2 ...
    double det =  px[0]*py[1] - px[1]*py[0];
    double xi0 =  py[1]*MET_x - px[1]*MET_y;
    double xi1 = -py[0]*MET_x + px[0]*MET_y;
    if(Nlep>=2 && abs(det)<1.0e-8)cout << "Really small determinant ... " << det << endl;

    double mtautau = 0.0;
    double mtautaup = 0.0;
    double mll = 0.0;
    bool ltaudebug = false;
    if(Nlep>=2){
       xi0 = xi0/det;
       xi1 = xi1/det;
//       cout << "Found xi0, xi1 = " << xi0 << " " << xi1 << endl;
       TLorentzVector v0,v1,vMET,vgenMET,vll;
       v0.SetPtEtaPhiM(PT_lep[0],Eta_lep[0],Phi_lep[0],M_lep[0]);
       v1.SetPtEtaPhiM(PT_lep[1],Eta_lep[1],Phi_lep[1],M_lep[1]);
       vMET.SetPtEtaPhiM(MET,0.0,MET_phi,0.0);  // Massless transverse 4-vector
       vgenMET.SetPtEtaPhiM(genMET,0.0,genMET_phi,0.0);  // Massless transverse 4-vector
       vll = v0+v1;
       mll = vll.M();
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
       mtautau = vtt.M();   // should return -ve value if mass-squared is negative??
// Alternative value
       double mtautaupsq = (1.0 +xi0)*(1.0+xi1)*mll*mll;
// Sometimes this is negative
       mtautaup = (mtautaupsq < 0.0) ? -sqrt(-mtautaupsq) : sqrt(mtautaupsq);

       if(ltaudebug){
//|| nseen < 1000 || bpcuts.all() ){
//       cout << "nseen : " << nseen << endl;
       cout << "Event selection " << bpcuts.all() << endl;
       cout << "MET:    " << vMET.Px() << " " << vMET.Py() << " " 
                          << vMET.Pz() << " " << vMET.M() << endl;
       cout << "genMET:    " << vgenMET.Px() << " " << vgenMET.Py() 
            << " " << vgenMET.Pz() << " " << vgenMET.M() << endl;
       cout << "Leptons " << endl;
       cout << "L0:     " << v0.Px() << " " << v0.Py() << " " << v0.Pz() << " " << v0.M() << endl;
       cout << "L1:     " << v1.Px() << " " << v1.Py() << " " << v1.Pz() << " " << v1.M() << endl;
       cout << "LL:     " << vll.Px() << " " << vll.Py() << " " << vll.Pz() << " " << vll.M() << endl;
       cout << "n0:     " << vn0.Px() << " " << vn0.Py() << " " << vn0.Pz() << " " << vn0.M() << endl;
       cout << "n1:     " << vn1.Px() << " " << vn1.Py() << " " << vn1.Pz() << " " << vn1.M() << endl;
       cout << "tau0:   " << vtau0.Px() << " " << vtau0.Py() << " " << vtau0.Pz() << " " << vtau0.M() << endl;
       cout << "tau1:   " << vtau1.Px() << " " << vtau1.Py() << " " << vtau1.Pz() << " " << vtau1.M() << endl;
       cout << "tautau: " << vtt.Px() << " " << vtt.Py() << " " << vtt.Pz() << " " << vtt.M() << endl;
       cout << "tau-tau kinematics  det: " << det << " xi0: " << xi0 
            << " xi1: " << xi1 << " M2: " << mtautausq << " M: "
            << mtautau << " M' " << mtautaup << endl;
       }
    }

// Lepton categories. Firstly multiplicity.
    FillTH1(ind_LeptonsCategory, 0.0, w);  // All events
    if( Is_1L ) FillTH1(ind_LeptonsCategory, 1.0, w);
    if( Is_2L ) FillTH1(ind_LeptonsCategory, 2.0, w);
    if( Is_3L ) FillTH1(ind_LeptonsCategory, 3.0, w);
    if( Is_4L ) FillTH1(ind_LeptonsCategory, 4.0, w);

// Histograms for potential additional cuts
    if(cbecuts.all()){
       FillTH1(ind_MLLHist, mll, w);
       FillTH1(ind_MTTHist, mtautau, w);
       FillTH1(ind_MTTpHist, mtautaup, w);
	   FillTH1(ind_MS1Hist, MS1, w);
	   FillTH1(ind_MISR1Hist, MISR1, w);
	   FillTH1(ind_NjetHist, Njet, w);
    }

// xcut removes a particular cut
    if(xcut(bpcuts, kRISR0)) FillTH1(ind_RISR0Hist, RISR0, w);
    if(xcut(bpcuts, kPTISR0)) FillTH1(ind_PTISR0Hist, PTISR0, w);
    if(xxcut(cbecuts, kRISR1, kRISRH)) FillTH1(ind_RISR1Hist, RISR1, w);
    if(xcut(cbecuts, kPTISR1)) FillTH1(ind_PTISR1Hist, PTISR1, w);
    if(xcut(cbecuts, kMET)) FillTH1(ind_METHist, MET, w);
    if(xcut(cbecuts, kPROMPT)) FillTH1(ind_MaxSIP3DHist, maxsip3d, w);
    if(xcut(cbecuts, kISO)) FillTH1(ind_IsoHist, maxisovalue, w);
    
// Cut Flow 1
    FillTH1(ind_CutFlowHist, -1.0, w);
    for (int i=0; i<numCuts; i++){
       bool pass = true;
       for (int j=0; j<=i; j++){
          if(!bpcuts.test(j))pass = false;
       }
       if(pass)FillTH1(ind_CutFlowHist, i, w);
       if(ecut(bpcuts,i))FillTH1(ind_ECutFlowHist, i, w);
    }

// Cut Flow 2
    FillTH1(ind_CutFlowHist2, -1.0, w);
    for (int i=0; i<numCuts2; i++){
       bool pass = true;
       for (int j=0; j<=i; j++){
          if(!bcuts.test(j))pass = false;
       }
       if(pass)FillTH1(ind_CutFlowHist2, i, w);
       if(ecut(bcuts,i))FillTH1(ind_ECutFlowHist2, i, w);
    }

// Cut Flow 3
    bool lsel3 = false;
    FillTH1(ind_CutFlowHist3, -1.0, w);
    for (int i=0; i<numCuts3; i++){
       bool pass = true;
       for (int j=0; j<=i; j++){
          if(!cbecuts.test(j))pass = false;
       }
       if(pass){
          FillTH1(ind_CutFlowHist3, i, w);
          if(i==numCuts3-1){
             lsel3 = true;
             cout << "Event Selected at 10" << endl;
             FillTH1(ind_CategoryHist,10.0,w);
          }
       }
       if(ecut(cbecuts,i))FillTH1(ind_ECutFlowHist3, i, w);
    }

    if(bcuts.all()){
// Passes all cuts
//                       ind_NlepS1Hist, ind_mNlepabHist,
       FillTH1(ind_NlepS1Hist, Nlep_S1, w);
       FillTH1(ind_mNlepabHist, min(Nlepa_S1,Nlepb_S1), w);
    }

// Weight distribution
    FillTH1(ind_WeightHist, w, w);
    unsigned long maskvalue2 = bcuts.to_ulong();
    FillTH1(ind_MCutFlowHist2, maskvalue2, w);

    unsigned long maskvalue3 = becuts.to_ulong();
    FillTH1(ind_MCutFlowHist3, maskvalue3, w);

   if(bpcuts.all())FillTH1(ind_MperpHist, Mperp, w);
   if(bcuts.all())FillTH1(ind_MperpHist2, Mperp, w);
   if(becuts.all())FillTH1(ind_MperpHist3, Mperp, w);

/*   if(lsel3){
      if(cbecuts.all()){
         cout << "Event Selected pre 11" << endl;
         cout << "Event Mperp = " << Mperp << " wt = " << w << endl;
         cout << "Event tid = " << tid << " " << tid%16 << endl;
         FillTH1(ind_MperpHist3, Mperp, w);  // How is this never filled
         FillTH1(ind_CategoryHist,11.0,w);   // but this is on the WWToLNuQQ sample
         cout << "Event Selected post 11" << endl;
      }
      else{
         FillTH1(ind_CategoryHist,12.0,w);
      }
   }
   else{
       if(cbecuts.all())FillTH1(ind_CategoryHist,13.0,w);     
   }
   if(cbecuts.all())FillTH1(ind_CategoryHist,14.0,w);  
*/
   
  bool lgeninfo = false;

  if(lgeninfo){
  if(bpcuts.all()){
    cout << "genMET: " << genMET << " " << genMET_x << " " << genMET_y << endl;
    //loop over all generator leptons
    if( genNlep > 0){      
       for(int i=0; i<genPT_lep.GetSize(); i++){
           TLorentzVector v;
           v.SetPtEtaPhiM(genPT_lep[i], genEta_lep[i], genPhi_lep[i], genM_lep[i]);
           cout << "genlep : " << i << " " << genPDGID_lep[i] << " " 
                << genMomPDGID_lep[i] << " " << v.Px() << " " << v.Py() 
                << " " << v.Pz() << " " << v.M() << endl;
       }
    }
    //loop over all generator neutrinos
    if( genNnu > 0){      
       for(int i=0; i<genPT_nu.GetSize(); i++){
           TLorentzVector v;
           v.SetPtEtaPhiM(genPT_nu[i], genEta_nu[i], genPhi_nu[i], 0.0);
           cout << "gennu  : " << i << " " << genPDGID_nu[i] << " " 
                << genMomPDGID_nu[i] << " " << v.Px() << " " << v.Py() 
                << " " << v.Pz() << " " << v.M() << endl;
       }
    }
    //loop over all generator sparticles
    if( genNsusy > 0){      
       for(int i=0; i<genPT_susy.GetSize(); i++){
           TLorentzVector v;
           v.SetPtEtaPhiM(genPT_susy[i], genEta_susy[i], genPhi_susy[i], genM_susy[i]);
           cout << "gensusy: " << i << " " << genPDGID_susy[i] << " " 
                << genMomPDGID_susy[i] << " " << v.Px() << " " << v.Py()
                << " " << v.Pz() << " " << v.M() << endl;
       }
    }
  }
  }

/*
  if(nseen == 1){
     cout << "nseen  = " << nseen << " Event weight set to " << w << endl;
     PrintCuts(bpcuts);
     PrintCuts2(bcuts);
  }
*/

}
#endif
