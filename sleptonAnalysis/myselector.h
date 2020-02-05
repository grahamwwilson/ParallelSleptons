//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sun Feb  2 16:40:49 2020 by ROOT version 6.18/04
// from TTree KUAnalysis/KUAnalysis
// found on file: NewTTree.root
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

using namespace std;  //GWW

class myselector : public TSelector {
public :
   TTreeReader     fReader;  //!the tree reader
   TTree          *fChain = 0;   //!pointer to the analyzed TTree or TChain

   // Readers to access the data (delete the ones you do not need).
   TTreeReaderValue<Bool_t> event_skipped = {fReader, "event_skipped"};
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
   TTreeReaderArray<double> RelIso_lep = {fReader, "RelIso_lep"};
   TTreeReaderArray<double> MiniIso_lep = {fReader, "MiniIso_lep"};
   TTreeReaderArray<double> Dxy_lep = {fReader, "Dxy_lep"};
   TTreeReaderArray<double> DxyErr_lep = {fReader, "DxyErr_lep"};
   TTreeReaderArray<double> Dz_lep = {fReader, "Dz_lep"};
   TTreeReaderArray<double> DzErr_lep = {fReader, "DzErr_lep"};
   TTreeReaderArray<double> IP3D_lep = {fReader, "IP3D_lep"};
   TTreeReaderArray<double> SIP3D_lep = {fReader, "SIP3D_lep"};
   TTreeReaderArray<int> ID_lep = {fReader, "ID_lep"};
   TTreeReaderArray<int> Index_lep = {fReader, "Index_lep"};
   TTreeReaderValue<Int_t> Njet = {fReader, "Njet"};
   TTreeReaderValue<Int_t> Nbjet = {fReader, "Nbjet"};
   TTreeReaderArray<double> PT_jet = {fReader, "PT_jet"};
   TTreeReaderArray<double> Eta_jet = {fReader, "Eta_jet"};
   TTreeReaderArray<double> Phi_jet = {fReader, "Phi_jet"};
   TTreeReaderArray<double> M_jet = {fReader, "M_jet"};
   TTreeReaderArray<double> Btag_jet = {fReader, "Btag_jet"};
   TTreeReaderArray<int> BtagID_jet = {fReader, "BtagID_jet"};
   TTreeReaderArray<double> Flavor_jet = {fReader, "Flavor_jet"};
   TTreeReaderArray<vector<int>> index_jet_a = {fReader, "index_jet_a"};
   TTreeReaderArray<vector<int>> index_jet_b = {fReader, "index_jet_b"};
   TTreeReaderArray<vector<int>> index_jet_ISR = {fReader, "index_jet_ISR"};
   TTreeReaderArray<vector<int>> index_jet_S = {fReader, "index_jet_S"};
   TTreeReaderValue<Int_t> NSV = {fReader, "NSV"};
   TTreeReaderArray<double> PT_SV = {fReader, "PT_SV"};
   TTreeReaderArray<double> Eta_SV = {fReader, "Eta_SV"};
   TTreeReaderArray<double> Phi_SV = {fReader, "Phi_SV"};
   TTreeReaderArray<double> M_SV = {fReader, "M_SV"};
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
   TTreeReaderArray<int> Njet_ISR = {fReader, "Njet_ISR"};
   TTreeReaderArray<int> Njet_S = {fReader, "Njet_S"};
   TTreeReaderArray<int> Nbjet_ISR = {fReader, "Nbjet_ISR"};
   TTreeReaderArray<int> Nbjet_S = {fReader, "Nbjet_S"};
   TTreeReaderArray<int> Nlep_ISR = {fReader, "Nlep_ISR"};
   TTreeReaderArray<int> Nlep_S = {fReader, "Nlep_S"};
   TTreeReaderArray<int> NSV_ISR = {fReader, "NSV_ISR"};
   TTreeReaderArray<int> NSV_S = {fReader, "NSV_S"};
   TTreeReaderArray<vector<int>> index_SV_ISR = {fReader, "index_SV_ISR"};
   TTreeReaderArray<vector<int>> index_SV_S = {fReader, "index_SV_S"};
   TTreeReaderArray<vector<int>> index_lep_ISR = {fReader, "index_lep_ISR"};
   TTreeReaderArray<vector<int>> index_lep_S = {fReader, "index_lep_S"};
   TTreeReaderArray<vector<double>> dphi_lep_S = {fReader, "dphi_lep_S"};
   TTreeReaderArray<vector<double>> cos_lep_S = {fReader, "cos_lep_S"};
   TTreeReaderArray<int> Njet_a = {fReader, "Njet_a"};
   TTreeReaderArray<int> Njet_b = {fReader, "Njet_b"};
   TTreeReaderArray<int> Nbjet_a = {fReader, "Nbjet_a"};
   TTreeReaderArray<int> Nbjet_b = {fReader, "Nbjet_b"};
   TTreeReaderArray<int> Nlep_a = {fReader, "Nlep_a"};
   TTreeReaderArray<int> Nlep_b = {fReader, "Nlep_b"};
   TTreeReaderArray<int> NSV_a = {fReader, "NSV_a"};
   TTreeReaderArray<int> NSV_b = {fReader, "NSV_b"};
   TTreeReaderArray<vector<int>> index_lep_a = {fReader, "index_lep_a"};
   TTreeReaderArray<vector<int>> index_lep_b = {fReader, "index_lep_b"};
   TTreeReaderArray<vector<int>> index_SV_a = {fReader, "index_SV_a"};
   TTreeReaderArray<vector<int>> index_SV_b = {fReader, "index_SV_b"};
   TTreeReaderArray<double> PTCM = {fReader, "PTCM"};
   TTreeReaderArray<double> cosCM = {fReader, "cosCM"};
   TTreeReaderArray<double> dphiCM = {fReader, "dphiCM"};
   TTreeReaderArray<double> dphiCMI = {fReader, "dphiCMI"};
   TTreeReaderArray<double> MS = {fReader, "MS"};
   TTreeReaderArray<double> PS = {fReader, "PS"};
   TTreeReaderArray<double> cosS = {fReader, "cosS"};
   TTreeReaderArray<double> dphiS = {fReader, "dphiS"};
   TTreeReaderArray<double> dphiSI = {fReader, "dphiSI"};
   TTreeReaderArray<double> PTS = {fReader, "PTS"};
   TTreeReaderArray<double> PzS = {fReader, "PzS"};
   TTreeReaderArray<double> MX3a = {fReader, "MX3a"};
   TTreeReaderArray<double> cosX3a = {fReader, "cosX3a"};
   TTreeReaderArray<double> MX3b = {fReader, "MX3b"};
   TTreeReaderArray<double> cosX3b = {fReader, "cosX3b"};
   TTreeReaderArray<double> EVa = {fReader, "EVa"};
   TTreeReaderArray<double> EVb = {fReader, "EVb"};
   TTreeReaderArray<double> PVa = {fReader, "PVa"};
   TTreeReaderArray<double> PVb = {fReader, "PVb"};
   TTreeReaderArray<double> EJa = {fReader, "EJa"};
   TTreeReaderArray<double> EJb = {fReader, "EJb"};
   TTreeReaderArray<double> PJa = {fReader, "PJa"};
   TTreeReaderArray<double> PJb = {fReader, "PJb"};
   TTreeReaderArray<double> MX2a = {fReader, "MX2a"};
   TTreeReaderArray<double> cosX2a = {fReader, "cosX2a"};
   TTreeReaderArray<double> MX2b = {fReader, "MX2b"};
   TTreeReaderArray<double> cosX2b = {fReader, "cosX2b"};
   TTreeReaderArray<double> ELa = {fReader, "ELa"};
   TTreeReaderArray<double> ELb = {fReader, "ELb"};
   TTreeReaderArray<double> PLa = {fReader, "PLa"};
   TTreeReaderArray<double> PLb = {fReader, "PLb"};
   TTreeReaderArray<double> MV = {fReader, "MV"};
   TTreeReaderArray<double> PV = {fReader, "PV"};
   TTreeReaderArray<double> MVa = {fReader, "MVa"};
   TTreeReaderArray<double> MVb = {fReader, "MVb"};
   TTreeReaderArray<double> MJa = {fReader, "MJa"};
   TTreeReaderArray<double> MJb = {fReader, "MJb"};
   TTreeReaderArray<double> MLa = {fReader, "MLa"};
   TTreeReaderArray<double> MLb = {fReader, "MLb"};
   TTreeReaderArray<double> cosJa = {fReader, "cosJa"};
   TTreeReaderArray<double> cosJb = {fReader, "cosJb"};
   TTreeReaderArray<double> cosLa = {fReader, "cosLa"};
   TTreeReaderArray<double> cosLb = {fReader, "cosLb"};
   TTreeReaderArray<double> MJ = {fReader, "MJ"};
   TTreeReaderArray<double> ML = {fReader, "ML"};
   TTreeReaderArray<double> EJ = {fReader, "EJ"};
   TTreeReaderArray<double> EL = {fReader, "EL"};
   TTreeReaderArray<double> PJ = {fReader, "PJ"};
   TTreeReaderArray<double> PL = {fReader, "PL"};
   TTreeReaderArray<double> PX3 = {fReader, "PX3"};
   TTreeReaderArray<double> PX3_BoostT = {fReader, "PX3_BoostT"};
   TTreeReaderArray<double> MX3a_BoostT = {fReader, "MX3a_BoostT"};
   TTreeReaderArray<double> MX3b_BoostT = {fReader, "MX3b_BoostT"};
// Mperp = sqrt(0.5 *(MX3a**2 + MX3b**2))
   TTreeReaderArray<double> PV_BoostT = {fReader, "PV_BoostT"};
   TTreeReaderArray<double> EVa_BoostT = {fReader, "EVa_BoostT"};
   TTreeReaderArray<double> EVb_BoostT = {fReader, "EVb_BoostT"};
   TTreeReaderArray<double> PVa_BoostT = {fReader, "PVa_BoostT"};
   TTreeReaderArray<double> PVb_BoostT = {fReader, "PVb_BoostT"};
   TTreeReaderArray<double> EJ_BoostT = {fReader, "EJ_BoostT"};
// One lepton pt-rel quantity.
   TTreeReaderArray<double> EL_BoostT = {fReader, "EL_BoostT"};
   TTreeReaderArray<double> PJ_BoostT = {fReader, "PJ_BoostT"};
   TTreeReaderArray<double> PL_BoostT = {fReader, "PL_BoostT"};
   TTreeReaderArray<double> H11S = {fReader, "H11S"};
   TTreeReaderArray<double> H21S = {fReader, "H21S"};
   TTreeReaderArray<double> HT21S = {fReader, "HT21S"};
   TTreeReaderArray<double> H22S = {fReader, "H22S"};
   TTreeReaderArray<double> HT22S = {fReader, "HT22S"};
   TTreeReaderArray<double> H42S = {fReader, "H42S"};
   TTreeReaderArray<double> HT42S = {fReader, "HT42S"};
   TTreeReaderArray<double> H11X3a = {fReader, "H11X3a"};
   TTreeReaderArray<double> H11X3b = {fReader, "H11X3b"};
   TTreeReaderArray<double> H21X3a = {fReader, "H21X3a"};
   TTreeReaderArray<double> H21X3b = {fReader, "H21X3b"};
   TTreeReaderArray<double> PTISR = {fReader, "PTISR"};
   TTreeReaderArray<double> RISR = {fReader, "RISR"};
   TTreeReaderArray<double> MISR = {fReader, "MISR"};
   TTreeReaderValue<Bool_t> Is_1L = {fReader, "Is_1L"};
   TTreeReaderValue<Bool_t> Is_2L = {fReader, "Is_2L"};
   TTreeReaderValue<Bool_t> Is_3L = {fReader, "Is_3L"};
   TTreeReaderValue<Bool_t> Is_4L = {fReader, "Is_4L"};

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

   // ClassDef(myselector,0);    // GWW

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
