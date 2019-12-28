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
};

histset::histset(std::string tag = ""){
	_tag = tag; 
	
	 std::vector<ROOT::TThreadedObject<TH1D>*>  Manager1(numTH1Hist);
	TH1Manager=Manager1;

	 std::vector<ROOT::TThreadedObject<TH2D>*>  Manager2(numTH2Hist);
	TH2Manager=Manager2;

	init();

}
void histset::init(){
//init TH1D
	TH1Manager.at(ind_METHist) = new ROOT::TThreadedObject<TH1D>("METHist", "MET;GeV;Entries per 5 GeV bin", 140, 100, 800);
//	TH1Manager.at(ind_cat0NjetSHist) = new ROOT::TThreadedObject<TH1D>("cat0NjetSHist", "cat0: Number of Sparticle Jets;Njet_S", 21, -0.5, 20.5);
//	TH1Manager.at(ind_cat1NjetSHist) = new ROOT::TThreadedObject<TH1D>("cat1NjetSHist", "cat1: Number of Sparticle Jets;Njet_S", 21, -0.5, 20.5);
// init TH2D
//	TH2Manager.at(ind_cat0PtcmPtisrDphiCMIHist) = new ROOT::TThreadedObject<TH2D>("cat0PtcmPtisrDphiCMIHist", "cat0: PTCM/PTISR vs dphiCMI ;dphiCMI;PTCM/PTISR", 50, 0, 3.2, 50, 0,2);
//	TH2Manager.at(ind_cat1PtcmPtisrDphiCMIHist) = new ROOT::TThreadedObject<TH2D>("cat1PtcmPtisrDphiCMIHist", "cat1: PTCM/PTISR vs dphiCMI;dphiCMI;PTCM/PTSIR", 50, 0, 3.2,50, 0,2);

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

/*	auto& PTCM = s.PTCM;
	auto& PTISR = s.PTISR;
	auto& dphiCMI = s.dphiCMI;
	auto& Njet_S = s.Njet_S;
*/

	FillTH1(ind_METHist, MET);

	//loop over cat0 and cat1
/*	for(int i=0; i<Njet_S.GetSize(); i++){
		if(i==0){
			FillTH1(ind_cat0NjetSHist, Njet_S[i] );
			FillTH2(ind_cat0PtcmPtisrDphiCMIHist,dphiCMI[i], PTCM[i]/PTISR[i]);
		}		
		if(i==1){
			FillTH1(ind_cat1NjetSHist, Njet_S[i] );
			FillTH2(ind_cat1PtcmPtisrDphiCMIHist,dphiCMI[i], PTCM[i]/PTISR[i]);
		}

	}
*/

}
#endif
