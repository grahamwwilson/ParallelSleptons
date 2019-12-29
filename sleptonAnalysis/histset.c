#ifndef HISTS
#define HISTS


#include "TH1D.h"
#include "TH2D.h"
#include "ROOT/TThreadedObject.hxx"
#include "TTreeReader.h"
#include "TTreeReaderValue.h"
#include "myselector.C"

class histset{
	
	public:
	   histset(std::string tag);	
	   void init(); 

	   void AnalyzeEntry(myselector& s); 
	 //  void AnalyzeEntry(mytreevalues& s);

	   //bookeeping enumeration: (if we do this we dont need to worry about hist ptr copies and merging)
//	   enum th1d_index{ind_METHist, ind_cat0NjetSHist, ind_cat1NjetSHist, numTH1Hist};
//	   enum th2d_index{ind_cat0PtcmPtisrDphiCMIHist, ind_cat1PtcmPtisrDphiCMIHist, numTH2Hist};
	 enum th1d_index{ind_METHist,numTH1Hist};
	 enum th2d_index{numTH2Hist};
	

	   // make a big vector and load enumerated histograms onto the vector
	 std::vector<ROOT::TThreadedObject<TH1D>* >  TH1Manager{};
	 std::vector<ROOT::TThreadedObject<TH2D>* >  TH2Manager{};


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
	std::string cutlist = "/home/j342a201/slepton/ParallelSleptons/sleptonAnalysis/cutfile.list";

	
	

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
	TH1Manager.at(ind_METHist) = new ROOT::TThreadedObject<TH1D>("METHist", "MET;GeV;Entries per 5 GeV bin", 140, 100, 800);

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
   	
	//always make a local copy, if its a value dereference.. if you dont do this scope/dereferencing will get really weird, clunky, and unmanageable
	//have to auto& or myreader will try to register copy of the readerarray ptr
	auto MET = *(s.MET);
	auto Nmu = *(s.Nmu);	
	auto weight = *(s.weight);

	_weight = weight;
	//auto& PTCM = s.PTCM;

	FillTH1(ind_METHist, MET);



	//event selection
	//iterate over cut sequence, apply operators and values
	bool pass;
        for(unsigned int i=0; i<_cutsequence.size(); i++){
                std::string cut = _cutsequence.at(i);
		double cutvalue = _cutval.at(i);

		if(cut.compare("nocut")==0){
			pass = nocut(_npass[i], 1);
			pass = nocut(_npassw[i], weight);
		}
		if( cut.compare("minMET")==0){
			pass = performcut( _npass[i], 1, MET, cutvalue, std::greater<double>());
			pass = performcut( _npassw[i], weight, MET, cutvalue, std::greater<double>());		
                        if(!pass) break;
                }
                if( cut.compare("minMu")==0){
               		pass = performcut( _npass[i],1, Nmu, cutvalue, std::greater_equal<double>());
                        pass = performcut( _npassw[i],weight,Nmu,cutvalue,std::greater_equal<double>());
			if(!pass) break;
		}
             
	}//end cut sequence loop	


}
#endif
