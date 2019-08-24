//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Aug 19 15:37:41 2019 by ROOT version 6.12/07
// from TTree KUAnalysis/KUAnalysis
// found on file: /home/t3-ku/crogan/NTUPLES/SUSYNANO/Autum18_102X/ZJetsToNuNu_HT-200To400_13TeV-madgraph_Autumn18_102X.root
//////////////////////////////////////////////////////////

#ifndef myselector_h
#define myselector_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>

// Headers needed by this particular selector
#include <vector>

using namespace std;

class myselector : public TSelector {
public :
   TTreeReader     fReader;  //!the tree reader
   TTree          *fChain = 0;   //!pointer to the analyzed TTree or TChain

   // Readers to access the data (delete the ones you do not need).
   TTreeReaderValue<Double_t> weight = {fReader, "weight"};
   TTreeReaderValue<Double_t> MET = {fReader, "MET"};
   TTreeReaderValue<Double_t> MET_phi = {fReader, "MET_phi"};
   TTreeReaderValue<Double_t> genMET = {fReader, "genMET"};
   TTreeReaderValue<Double_t> genMET_phi = {fReader, "genMET_phi"};
   TTreeReaderValue<Double_t> HT = {fReader, "HT"};
   TTreeReaderValue<Int_t> Nele = {fReader, "Nele"};
   TTreeReaderValue<Int_t> Nmu = {fReader, "Nmu"};
   TTreeReaderValue<Int_t> Nlep = {fReader, "Nlep"};
   TTreeReaderArray<double> PT_lep = {fReader, "PT_lep"};
   TTreeReaderArray<double> Eta_lep = {fReader, "Eta_lep"};
   TTreeReaderArray<double> Phi_lep = {fReader, "Phi_lep"};
   TTreeReaderArray<double> M_lep = {fReader, "M_lep"};
   TTreeReaderArray<int> Charge_lep = {fReader, "Charge_lep"};
   TTreeReaderArray<int> PDGID_lep = {fReader, "PDGID_lep"};
   TTreeReaderArray<int> RelIso_lep = {fReader, "RelIso_lep"};
   TTreeReaderArray<int> MiniIso_lep = {fReader, "MiniIso_lep"};
   TTreeReaderArray<int> ID_lep = {fReader, "ID_lep"};
   TTreeReaderArray<int> Index_lep = {fReader, "Index_lep"};
   TTreeReaderValue<Int_t> Njet = {fReader, "Njet"};
   TTreeReaderValue<Int_t> Nbjet = {fReader, "Nbjet"};
   TTreeReaderArray<double> PT_jet = {fReader, "PT_jet"};
   TTreeReaderArray<double> Eta_jet = {fReader, "Eta_jet"};
   TTreeReaderArray<double> Phi_jet = {fReader, "Phi_jet"};
   TTreeReaderArray<double> M_jet = {fReader, "M_jet"};
   TTreeReaderArray<double> Btag_jet = {fReader, "Btag_jet"};
   TTreeReaderArray<double> Flavor_jet = {fReader, "Flavor_jet"};
   TTreeReaderValue<Int_t> genNele = {fReader, "genNele"};
   TTreeReaderValue<Int_t> genNmu = {fReader, "genNmu"};
   TTreeReaderValue<Int_t> genNlep = {fReader, "genNlep"};
   TTreeReaderArray<double> genPT_lep = {fReader, "genPT_lep"};
   TTreeReaderArray<double> genEta_lep = {fReader, "genEta_lep"};
   TTreeReaderArray<double> genPhi_lep = {fReader, "genPhi_lep"};
   TTreeReaderArray<double> genM_lep = {fReader, "genM_lep"};
   TTreeReaderArray<int> genCharge_lep = {fReader, "genCharge_lep"};
   TTreeReaderArray<int> genPDGID_lep = {fReader, "genPDGID_lep"};
   TTreeReaderArray<int> genMomPDGID_lep = {fReader, "genMomPDGID_lep"};
   TTreeReaderArray<int> genIndex_lep = {fReader, "genIndex_lep"};
   TTreeReaderValue<Int_t> genNnu = {fReader, "genNnu"};
   TTreeReaderArray<double> genPT_nu = {fReader, "genPT_nu"};
   TTreeReaderArray<double> genEta_nu = {fReader, "genEta_nu"};
   TTreeReaderArray<double> genPhi_nu = {fReader, "genPhi_nu"};
   TTreeReaderArray<int> genPDGID_nu = {fReader, "genPDGID_nu"};
   TTreeReaderArray<int> genMomPDGID_nu = {fReader, "genMomPDGID_nu"};
   TTreeReaderValue<Int_t> genNboson = {fReader, "genNboson"};
   TTreeReaderArray<double> genPT_boson = {fReader, "genPT_boson"};
   TTreeReaderArray<double> genEta_boson = {fReader, "genEta_boson"};
   TTreeReaderArray<double> genPhi_boson = {fReader, "genPhi_boson"};
   TTreeReaderArray<double> genM_boson = {fReader, "genM_boson"};
   TTreeReaderArray<int> genPDGID_boson = {fReader, "genPDGID_boson"};
   TTreeReaderArray<int> genMomPDGID_boson = {fReader, "genMomPDGID_boson"};
   TTreeReaderValue<Int_t> genNsusy = {fReader, "genNsusy"};
   TTreeReaderArray<double> genPT_susy = {fReader, "genPT_susy"};
   TTreeReaderArray<double> genEta_susy = {fReader, "genEta_susy"};
   TTreeReaderArray<double> genPhi_susy = {fReader, "genPhi_susy"};
   TTreeReaderArray<double> genM_susy = {fReader, "genM_susy"};
   TTreeReaderArray<int> genPDGID_susy = {fReader, "genPDGID_susy"};
   TTreeReaderArray<int> genMomPDGID_susy = {fReader, "genMomPDGID_susy"};
   TTreeReaderArray<int> Njet_a = {fReader, "Njet_a"};
   TTreeReaderArray<int> Njet_b = {fReader, "Njet_b"};
   TTreeReaderArray<int> Nbjet_a = {fReader, "Nbjet_a"};
   TTreeReaderArray<int> Nbjet_b = {fReader, "Nbjet_b"};
   TTreeReaderArray<int> Nlep_a = {fReader, "Nlep_a"};
   TTreeReaderArray<int> Nlep_b = {fReader, "Nlep_b"};
   TTreeReaderArray<int> Njet_ga = {fReader, "Njet_ga"};
   TTreeReaderArray<int> Njet_gb = {fReader, "Njet_gb"};
   TTreeReaderArray<int> Nbjet_ga = {fReader, "Nbjet_ga"};
   TTreeReaderArray<int> Nbjet_gb = {fReader, "Nbjet_gb"};
   TTreeReaderArray<int> Nlep_ga = {fReader, "Nlep_ga"};
   TTreeReaderArray<int> Nlep_gb = {fReader, "Nlep_gb"};
   TTreeReaderArray<vector<int>> index_jet_a = {fReader, "index_jet_a"};
   TTreeReaderArray<vector<int>> index_jet_b = {fReader, "index_jet_b"};
   TTreeReaderArray<vector<int>> index_lep_a = {fReader, "index_lep_a"};
   TTreeReaderArray<vector<int>> index_lep_b = {fReader, "index_lep_b"};
   TTreeReaderArray<vector<int>> index_jet_ga = {fReader, "index_jet_ga"};
   TTreeReaderArray<vector<int>> index_jet_gb = {fReader, "index_jet_gb"};
   TTreeReaderArray<vector<int>> index_lep_ga = {fReader, "index_lep_ga"};
   TTreeReaderArray<vector<int>> index_lep_gb = {fReader, "index_lep_gb"};
   TTreeReaderArray<double> MSS = {fReader, "MSS"};
   TTreeReaderArray<double> PSS = {fReader, "PSS"};
   TTreeReaderArray<double> cosSS = {fReader, "cosSS"};
   TTreeReaderArray<double> dphiSS = {fReader, "dphiSS"};
   TTreeReaderArray<double> PTSS = {fReader, "PTSS"};
   TTreeReaderArray<double> PzSS = {fReader, "PzSS"};
   TTreeReaderArray<double> MCa = {fReader, "MCa"};
   TTreeReaderArray<double> cosCa = {fReader, "cosCa"};
   TTreeReaderArray<double> MCb = {fReader, "MCb"};
   TTreeReaderArray<double> cosCb = {fReader, "cosCb"};
   TTreeReaderArray<double> MGCa = {fReader, "MGCa"};
   TTreeReaderArray<double> cosGCa = {fReader, "cosGCa"};
   TTreeReaderArray<double> MGCb = {fReader, "MGCb"};
   TTreeReaderArray<double> cosGCb = {fReader, "cosGCb"};
   TTreeReaderArray<double> H11SS = {fReader, "H11SS"};
   TTreeReaderArray<double> H21SS = {fReader, "H21SS"};
   TTreeReaderArray<double> HT21SS = {fReader, "HT21SS"};
   TTreeReaderArray<double> H22SS = {fReader, "H22SS"};
   TTreeReaderArray<double> HT22SS = {fReader, "HT22SS"};
   TTreeReaderArray<double> H42SS = {fReader, "H42SS"};
   TTreeReaderArray<double> HT42SS = {fReader, "HT42SS"};
   TTreeReaderArray<double> H11Ca = {fReader, "H11Ca"};
   TTreeReaderArray<double> H11Cb = {fReader, "H11Cb"};
   TTreeReaderArray<double> H21Ca = {fReader, "H21Ca"};
   TTreeReaderArray<double> H21Cb = {fReader, "H21Cb"};
   TTreeReaderArray<double> MVa = {fReader, "MVa"};
   TTreeReaderArray<double> PVa = {fReader, "PVa"};
   TTreeReaderArray<double> cosVa = {fReader, "cosVa"};
   TTreeReaderArray<double> MVb = {fReader, "MVb"};
   TTreeReaderArray<double> PVb = {fReader, "PVb"};
   TTreeReaderArray<double> cosVb = {fReader, "cosVb"};
   TTreeReaderValue<Bool_t> Is_1L_2J = {fReader, "Is_1L_2J"};
   TTreeReaderValue<Bool_t> Is_2L_2J = {fReader, "Is_2L_2J"};
   TTreeReaderValue<Bool_t> Is_1L_1L = {fReader, "Is_1L_1L"};
   TTreeReaderValue<Bool_t> Is_2L_1L = {fReader, "Is_2L_1L"};
   TTreeReaderValue<Bool_t> Is_2L_2L = {fReader, "Is_2L_2L"};
   TTreeReaderValue<Bool_t> Is_1L_B = {fReader, "Is_1L_B"};
   TTreeReaderValue<Bool_t> Is_2L_B = {fReader, "Is_2L_B"};
   TTreeReaderValue<Bool_t> Is_1LB_1LB = {fReader, "Is_1LB_1LB"};
   TTreeReaderValue<Bool_t> Is_3L_B = {fReader, "Is_3L_B"};
   TTreeReaderArray<int> Njet_ISR = {fReader, "Njet_ISR"};
   TTreeReaderArray<int> Njet_S = {fReader, "Njet_S"};
   TTreeReaderArray<int> Nbjet_ISR = {fReader, "Nbjet_ISR"};
   TTreeReaderArray<int> Nbjet_S = {fReader, "Nbjet_S"};
   TTreeReaderArray<int> Nlep_ISR = {fReader, "Nlep_ISR"};
   TTreeReaderArray<int> Nlep_S = {fReader, "Nlep_S"};
   TTreeReaderArray<vector<int>> index_jet_ISR = {fReader, "index_jet_ISR"};
   TTreeReaderArray<vector<int>> index_jet_S = {fReader, "index_jet_S"};
   TTreeReaderArray<vector<int>> index_lep_ISR = {fReader, "index_lep_ISR"};
   TTreeReaderArray<vector<int>> index_lep_S = {fReader, "index_lep_S"};
   TTreeReaderArray<double> PTISR = {fReader, "PTISR"};
   TTreeReaderArray<double> PTCM = {fReader, "PTCM"};
   TTreeReaderArray<double> RISR = {fReader, "RISR"};
   TTreeReaderArray<double> cosCM = {fReader, "cosCM"};
   TTreeReaderArray<double> cosS = {fReader, "cosS"};
   TTreeReaderArray<double> MISR = {fReader, "MISR"};
   TTreeReaderArray<double> MS = {fReader, "MS"};
   TTreeReaderArray<double> MV = {fReader, "MV"};
   TTreeReaderArray<double> ML = {fReader, "ML"};
   TTreeReaderArray<double> dphiCMI = {fReader, "dphiCMI"};
   TTreeReaderArray<double> dphiSI = {fReader, "dphiSI"};
   TTreeReaderArray<double> dphiISRI = {fReader, "dphiISRI"};


   myselector(TTree * /*tree*/ =0) { }
   virtual ~myselector() { }
   virtual Int_t   Version() const { return 2; }
   virtual void    Begin(TTree *tree);
   virtual void    SlaveBegin(TTree *tree);
   virtual void    Init(TTree *tree);
   virtual Bool_t  Notify();
   virtual Bool_t  Process(Long64_t entry);
   virtual Int_t   GetEntry(Long64_t entry, Int_t getall = 0) { return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0; }
   virtual void    SetOption(const char *option) { fOption = option; }
   virtual void    SetObject(TObject *obj) { fObject = obj; }
   virtual void    SetInputList(TList *input) { fInput = input; }
   virtual TList  *GetOutputList() const { return fOutput; }
   virtual void    SlaveTerminate();
   virtual void    Terminate();

   //ClassDef(myselector,0);

};

#endif

#ifdef myselector_cxx
void myselector::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the reader is initialized.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   fReader.SetTree(tree);
}

Bool_t myselector::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}


#endif // #ifdef myselector_cxx
