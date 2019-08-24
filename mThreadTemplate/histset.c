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
	   histset();	
	   void init(); 

	   void AnalyzeEntry(myselector& s); 
	 //  void AnalyzeEntry(mytreevalues& s);

	   //bookeeping enumeration: (if we do this we dont need to worry about hist ptr copies and merging)
	   enum th1d_index{ind_ptHist, ind_pzHist, ind_numpcHist, numTH1Hist};
	   enum th2d_index{ind_pxpyHist, numTH2Hist};


	   // make a big vector and load enumerated histograms onto the vector
	 std::vector<ROOT::TThreadedObject<TH1D>* >  TH1Manager{};
	 std::vector<ROOT::TThreadedObject<TH2D>* >  TH2Manager{};


	  //locate the histogram and perform ptr copying 
	  void FillTH1(int index, double x, double w);
	  void FillTH2(int index, double x, double y);
	
	  void WriteHist(); 
};

histset::histset(){

	 std::vector<ROOT::TThreadedObject<TH1D>*>  Manager1(numTH1Hist);
	TH1Manager=Manager1;

	 std::vector<ROOT::TThreadedObject<TH2D>*>  Manager2(numTH2Hist);
	TH2Manager=Manager2;

	init();

}
void histset::init(){
//init TH1D
	TH1Manager.at(ind_ptHist) = new ROOT::TThreadedObject<TH1D>("ptHist", "p_{T} Distribution;p_{T};dN/p_{T}dp_{T}", 100, 0, 5);
	TH1Manager.at(ind_pzHist) = new ROOT::TThreadedObject<TH1D>("pzHist", "p_{Z} Distribution;p_{Z};dN/dp_{Z}", 100, 0, 5);
	TH1Manager.at(ind_numpcHist) = new ROOT::TThreadedObject<TH1D>("numpcHist", "Number of PC", 51, 0, 50);
// init TH2D
	TH2Manager.at(ind_pxpyHist) = new ROOT::TThreadedObject<TH2D>("pxpyHist", "p_{X} vs p_{Y} Distribution;p_{X};p_{Y}", 100, -5., 5., 100, -5., 5.);


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
void histset::WriteHist(){

	TFile* outfile = new TFile("testset.root","RECREATE");

	for(int i=0; i<numTH1Hist; i++){
		auto histmerged = TH1Manager.at(i)->Merge();
		TH1D* h = (TH1D*) histmerged->Clone();
		outfile->WriteObject(h, h->GetName() );
	}

	for(int i=0; i<numTH2Hist; i++){
		auto histmerged = TH2Manager.at(i)->Merge();
		TH2D* h = (TH2D*) histmerged->Clone();
		outfile->WriteObject(h, h->GetName() );
	}	

}
void histset::AnalyzeEntry(myselector& s){
   	
	//always make a local copy, if its a value dereference.. if you dont do this scope/dereferencing will get really weird, clunky, and unmanageable
	//have to auto& or myreader will try to register copy of the readerarray ptr
	auto& PC_vTrack_pt = s.PC_vTrack_pt;
	auto& PC_vTrack_phi = s.PC_vTrack_phi;
	auto& PC_vTrack_eta = s.PC_vTrack_eta;

	auto numberOfPC = *(s.numberOfPC);

	double px,py,pz;

	FillTH1(ind_numpcHist, numberOfPC);

	for(int i=0; i<PC_vTrack_pt.GetSize(); i++){
                for(int j=0; j<PC_vTrack_pt[i].size(); j++){

			px = PC_vTrack_pt[i][j] * cos( PC_vTrack_phi[i][j] );
			py = PC_vTrack_pt[i][j] * sin( PC_vTrack_phi[i][j] );
			pz = PC_vTrack_pt[i][j] * sinh( PC_vTrack_eta[i][j] );


                        FillTH1(ind_ptHist, PC_vTrack_pt[i][j], 1./PC_vTrack_pt[i][j]);
			FillTH1(ind_pzHist, pz);
			
			FillTH2(ind_pxpyHist, px, py);
                }
        }
	
	

}
#endif
