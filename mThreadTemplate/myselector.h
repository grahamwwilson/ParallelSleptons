//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Aug 14 22:05:59 2019 by ROOT version 6.12/07
// from TTree PhotonConversionsTree/PhotonConversionsTree
// found on file: /home/t3-ku/janguian/storeUser/jsingera/DPG/PC/Run2018/SingleMuon/crab_SingleMu_Run2018D_AOD/190611_214910/0000/Run2018_100.root
//////////////////////////////////////////////////////////

#ifndef myselector_h
#define myselector_h

//#include <TROOT.h>
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
   TTreeReaderValue<Bool_t> isRealData = {fReader, "isRealData"};
   TTreeReaderValue<UInt_t> eventNumber = {fReader, "eventNumber"};
   TTreeReaderValue<UInt_t> runNumber = {fReader, "runNumber"};
   TTreeReaderValue<UInt_t> lumiSection = {fReader, "lumiSection"};
   TTreeReaderValue<UInt_t> numberOfPV = {fReader, "numberOfPV"};
   TTreeReaderArray<double> PV_x = {fReader, "PV_x"};
   TTreeReaderArray<double> PV_y = {fReader, "PV_y"};
   TTreeReaderArray<double> PV_z = {fReader, "PV_z"};
   TTreeReaderArray<double> PV_xError = {fReader, "PV_xError"};
   TTreeReaderArray<double> PV_yError = {fReader, "PV_yError"};
   TTreeReaderArray<double> PV_zError = {fReader, "PV_zError"};
   TTreeReaderValue<vector<bool>> PV_isFake = {fReader, "PV_isFake"};
   TTreeReaderValue<UInt_t> numberOfMC_PUInfo = {fReader, "numberOfMC_PUInfo"};
   TTreeReaderArray<unsigned int> MC_PUInfo_bunchCrossing = {fReader, "MC_PUInfo_bunchCrossing"};
   TTreeReaderArray<unsigned int> MC_PUInfo_numberOfInteractions = {fReader, "MC_PUInfo_numberOfInteractions"};
   TTreeReaderValue<Double_t> BS_x = {fReader, "BS_x"};
   TTreeReaderValue<Double_t> BS_y = {fReader, "BS_y"};
   TTreeReaderValue<Double_t> BS_z = {fReader, "BS_z"};
   TTreeReaderValue<Double_t> BS_zSigma = {fReader, "BS_zSigma"};
   TTreeReaderValue<Double_t> BS_dxdy = {fReader, "BS_dxdy"};
   TTreeReaderValue<Double_t> BS_dydz = {fReader, "BS_dydz"};
   TTreeReaderValue<Double_t> BS_xWidth = {fReader, "BS_xWidth"};
   TTreeReaderValue<Double_t> BS_yWidth = {fReader, "BS_yWidth"};
   TTreeReaderValue<UInt_t> numberOfMC_TrkV = {fReader, "numberOfMC_TrkV"};
   TTreeReaderValue<vector<bool>> MC_TrkV_isNuclearInteraction = {fReader, "MC_TrkV_isNuclearInteraction"};
   TTreeReaderValue<vector<bool>> MC_TrkV_isKaonDecay = {fReader, "MC_TrkV_isKaonDecay"};
   TTreeReaderValue<vector<bool>> MC_TrkV_isConversion = {fReader, "MC_TrkV_isConversion"};
   TTreeReaderArray<double> MC_TrkV_x = {fReader, "MC_TrkV_x"};
   TTreeReaderArray<double> MC_TrkV_y = {fReader, "MC_TrkV_y"};
   TTreeReaderArray<double> MC_TrkV_z = {fReader, "MC_TrkV_z"};
   TTreeReaderArray<double> MC_TrkV_momentumInc_pt = {fReader, "MC_TrkV_momentumInc_pt"};
   TTreeReaderArray<double> MC_TrkV_Inc_charge = {fReader, "MC_TrkV_Inc_charge"};
   TTreeReaderArray<int> MC_TrkV_Inc_pdgId = {fReader, "MC_TrkV_Inc_pdgId"};
   TTreeReaderArray<double> MC_TrkV_momentumInc_phi = {fReader, "MC_TrkV_momentumInc_phi"};
   TTreeReaderArray<double> MC_TrkV_momentumInc_theta = {fReader, "MC_TrkV_momentumInc_theta"};
   TTreeReaderArray<double> MC_TrkV_momentumOut_pt = {fReader, "MC_TrkV_momentumOut_pt"};
   TTreeReaderArray<double> MC_TrkV_momentumOut_phi = {fReader, "MC_TrkV_momentumOut_phi"};
   TTreeReaderArray<double> MC_TrkV_momentumOut_theta = {fReader, "MC_TrkV_momentumOut_theta"};
   TTreeReaderArray<double> MC_TrkV_momentumOut_mass = {fReader, "MC_TrkV_momentumOut_mass"};
   TTreeReaderArray<unsigned int> MC_TrkV_numberOfChargedParticles_0p2 = {fReader, "MC_TrkV_numberOfChargedParticles_0p2"};
   TTreeReaderArray<unsigned int> MC_TrkV_numberOfChargedParticles_0p5 = {fReader, "MC_TrkV_numberOfChargedParticles_0p5"};
   TTreeReaderArray<unsigned int> MC_TrkV_numberOfChargedParticles_1p0 = {fReader, "MC_TrkV_numberOfChargedParticles_1p0"};
   TTreeReaderArray<unsigned int> MC_TrkV_numberOfChargedParticles_Out0p2 = {fReader, "MC_TrkV_numberOfChargedParticles_Out0p2"};
   TTreeReaderArray<unsigned int> MC_TrkV_numberOfChargedParticles_Out0p5 = {fReader, "MC_TrkV_numberOfChargedParticles_Out0p5"};
   TTreeReaderArray<unsigned int> MC_TrkV_numberOfChargedParticles_Out1p0 = {fReader, "MC_TrkV_numberOfChargedParticles_Out1p0"};
   TTreeReaderValue<vector<bool>> MC_TrkV_isAssociatedPF = {fReader, "MC_TrkV_isAssociatedPF"};
   TTreeReaderArray<unsigned int> MC_TrkV_associationPCIdx = {fReader, "MC_TrkV_associationPCIdx"};
   TTreeReaderArray<double> MC_TrkV_associationPC_deltaR2d = {fReader, "MC_TrkV_associationPC_deltaR2d"};
   TTreeReaderArray<double> MC_TrkV_associationPC_deltaR3d = {fReader, "MC_TrkV_associationPC_deltaR3d"};
   TTreeReaderArray<double> MC_TrkV_associationPC_deltaR3dPerpendicular = {fReader, "MC_TrkV_associationPC_deltaR3dPerpendicular"};
   TTreeReaderArray<double> MC_TrkV_associationPC_deltaR3dParallel = {fReader, "MC_TrkV_associationPC_deltaR3dParallel"};
   TTreeReaderValue<UInt_t> numberOfPC = {fReader, "numberOfPC"};
   TTreeReaderArray<double> PC_x = {fReader, "PC_x"};
   TTreeReaderArray<double> PC_y = {fReader, "PC_y"};
   TTreeReaderArray<double> PC_z = {fReader, "PC_z"};
   TTreeReaderArray<double> PC_momentumOut_pt = {fReader, "PC_momentumOut_pt"};
   TTreeReaderArray<double> PC_momentumOut_phi = {fReader, "PC_momentumOut_phi"};
   TTreeReaderArray<double> PC_momentumOut_theta = {fReader, "PC_momentumOut_theta"};
   TTreeReaderArray<unsigned int> PC_momentumOut_numberOfTracks = {fReader, "PC_momentumOut_numberOfTracks"};
   TTreeReaderArray<double> PC_fitmomentumOut_pt = {fReader, "PC_fitmomentumOut_pt"};
   TTreeReaderArray<double> PC_fitmomentumOut_phi = {fReader, "PC_fitmomentumOut_phi"};
   TTreeReaderArray<double> PC_fitmomentumOut_theta = {fReader, "PC_fitmomentumOut_theta"};
   TTreeReaderArray<double> PC_fitmomentumOut_mass = {fReader, "PC_fitmomentumOut_mass"};
   TTreeReaderArray<double> PC_pairInvariantMass = {fReader, "PC_pairInvariantMass"};
   TTreeReaderArray<double> PC_pairCotThetaSeparation = {fReader, "PC_pairCotThetaSeparation"};
   TTreeReaderArray<double> PC_distOfMinimumApproach = {fReader, "PC_distOfMinimumApproach"};
   TTreeReaderArray<double> PC_dPhiTracksAtVtx = {fReader, "PC_dPhiTracksAtVtx"};
   TTreeReaderArray<double> PC_vtx_chi2 = {fReader, "PC_vtx_chi2"};
   TTreeReaderArray<double> PC_vtx_ndof = {fReader, "PC_vtx_ndof"};
   TTreeReaderArray<double> PC_vtx_normalizedChi2 = {fReader, "PC_vtx_normalizedChi2"};
   TTreeReaderArray<double> PC_vtx_sigmaxx = {fReader, "PC_vtx_sigmaxx"};
   TTreeReaderArray<double> PC_vtx_sigmayy = {fReader, "PC_vtx_sigmayy"};
   TTreeReaderArray<double> PC_vtx_sigmazz = {fReader, "PC_vtx_sigmazz"};
   TTreeReaderArray<double> PC_vtx_sigmaxy = {fReader, "PC_vtx_sigmaxy"};
   TTreeReaderArray<double> PC_vtx_sigmaxz = {fReader, "PC_vtx_sigmaxz"};
   TTreeReaderArray<double> PC_vtx_sigmayz = {fReader, "PC_vtx_sigmayz"};
   TTreeReaderArray<vector<int>> PC_vTrack_algo = {fReader, "PC_vTrack_algo"};
   TTreeReaderArray<vector<int>> PC_vTrack_charge = {fReader, "PC_vTrack_charge"};
   TTreeReaderArray<vector<double>> PC_vTrack_pt = {fReader, "PC_vTrack_pt"};
   TTreeReaderArray<vector<double>> PC_vTrack_eta = {fReader, "PC_vTrack_eta"};
   TTreeReaderArray<vector<double>> PC_vTrack_phi = {fReader, "PC_vTrack_phi"};
   TTreeReaderArray<vector<double>> PC_vTrack_chi2 = {fReader, "PC_vTrack_chi2"};
   TTreeReaderArray<vector<double>> PC_vTrack_normalizedChi2 = {fReader, "PC_vTrack_normalizedChi2"};
   TTreeReaderArray<vector<double>> PC_vTrack_rho = {fReader, "PC_vTrack_rho"};
   TTreeReaderArray<vector<unsigned int>> PC_vTrack_numberOfValidHits = {fReader, "PC_vTrack_numberOfValidHits"};
   TTreeReaderArray<vector<unsigned int>> PC_vTrack_numberOfExpectedOuterHits = {fReader, "PC_vTrack_numberOfExpectedOuterHits"};
   TTreeReaderArray<vector<unsigned int>> PC_vTrack_closestDxyPVIdx = {fReader, "PC_vTrack_closestDxyPVIdx"};
   TTreeReaderArray<vector<double>> PC_vTrack_closestDxyPVIdx_dxy = {fReader, "PC_vTrack_closestDxyPVIdx_dxy"};
   TTreeReaderArray<vector<double>> PC_vTrack_closestDxyPVIdx_dz = {fReader, "PC_vTrack_closestDxyPVIdx_dz"};
   TTreeReaderArray<vector<unsigned int>> PC_vTrack_closestDzPVIdx = {fReader, "PC_vTrack_closestDzPVIdx"};
   TTreeReaderArray<vector<double>> PC_vTrack_closestDzPVIdx_dxy = {fReader, "PC_vTrack_closestDzPVIdx_dxy"};
   TTreeReaderArray<vector<double>> PC_vTrack_closestDzPVIdx_dz = {fReader, "PC_vTrack_closestDzPVIdx_dz"};
   TTreeReaderArray<vector<double>> PC_fTrack_pt = {fReader, "PC_fTrack_pt"};
   TTreeReaderArray<vector<double>> PC_fTrack_eta = {fReader, "PC_fTrack_eta"};
   TTreeReaderArray<vector<double>> PC_fTrack_phi = {fReader, "PC_fTrack_phi"};


   myselector(TTree * /*tree*/ =0) { }
  // myselector(TTreeReader myreader) { fReader = myreader; }
// explicit myselector(TTreeReader& myreader);
//myselector(TTreeReader& myreader);
//	myselector(const myselector&) = delete;
//	myselector& operator=(const myselector&)= delete;
 //  ~myselector() = default;
//	myselector(const myselector&) = delete; 
 //myselector(TTreeReader& myreader) { fReader = myreader; }
       //explicit UserQueues();
        //UserQueues(const UserQueues&) = delete;
        //UserQueues& operator=(const UserQueues&) = delete;
        //~UserQueues() = default;



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

  // ClassDef(myselector,1);
   //ClassImp(myselector);

};

#endif

#ifdef myselector_cxx
//myselector::myselector(TTreeReader& myreader){
//	fReader = myreader;
//}
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
