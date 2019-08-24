#ifndef MYVALUE
#define MYVALUE
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>

// Headers needed by this particular selector
#include <vector>
using namespace std;

class mytreevalues{

	public:
/*   TTreeReaderValue<Bool_t>* isRealData; 
   TTreeReaderValue<UInt_t>* eventNumber;
   TTreeReaderValue<UInt_t>* runNumber;
   TTreeReaderValue<UInt_t>* lumiSection;
   TTreeReaderValue<UInt_t> numberOfPV; 
   TTreeReaderArray<double> PV_x; 
   TTreeReaderArray<double> PV_y; 
   TTreeReaderArray<double> PV_z;
   TTreeReaderArray<double> PV_xError; 
   TTreeReaderArray<double> PV_yError;
   TTreeReaderArray<double> PV_zError; 
   TTreeReaderValue<vector<bool>> PV_isFake; 
   TTreeReaderValue<UInt_t> numberOfMC_PUInfo;
   TTreeReaderArray<unsigned int> MC_PUInfo_bunchCrossing;
   TTreeReaderArray<unsigned int> MC_PUInfo_numberOfInteractions; 
   TTreeReaderValue<Double_t> BS_x;
   TTreeReaderValue<Double_t> BS_y; 
   TTreeReaderValue<Double_t> BS_z;
   TTreeReaderValue<Double_t> BS_zSigma; 
   TTreeReaderValue<Double_t> BS_dxdy;
   TTreeReaderValue<Double_t> BS_dydz; 
   TTreeReaderValue<Double_t> BS_xWidth;
   TTreeReaderValue<Double_t> BS_yWidth; 


   TTreeReaderValue<UInt_t> numberOfPC; 
   TTreeReaderArray<double> PC_x;
   TTreeReaderArray<double> PC_y; 
   TTreeReaderArray<double> PC_z; 
   TTreeReaderArray<double> PC_momentumOut_pt;
   TTreeReaderArray<double> PC_momentumOut_phi; 
   TTreeReaderArray<double> PC_momentumOut_theta; 
   TTreeReaderArray<unsigned int> PC_momentumOut_numberOfTracks; 
   TTreeReaderArray<double> PC_fitmomentumOut_pt;
   TTreeReaderArray<double> PC_fitmomentumOut_phi; 
   TTreeReaderArray<double> PC_fitmomentumOut_theta; 
   TTreeReaderArray<double> PC_fitmomentumOut_mass; 
   TTreeReaderArray<double> PC_pairInvariantMass;
   TTreeReaderArray<double> PC_pairCotThetaSeparation; 
   TTreeReaderArray<double> PC_distOfMinimumApproach; 
   TTreeReaderArray<double> PC_dPhiTracksAtVtx;
   TTreeReaderArray<double> PC_vtx_chi2; 
   TTreeReaderArray<double> PC_vtx_ndof; 
   TTreeReaderArray<double> PC_vtx_normalizedChi2; 
   TTreeReaderArray<double> PC_vtx_sigmaxx;
   TTreeReaderArray<double> PC_vtx_sigmayy; 
   TTreeReaderArray<double> PC_vtx_sigmazz; 
   TTreeReaderArray<double> PC_vtx_sigmaxy; 
   TTreeReaderArray<double> PC_vtx_sigmaxz; 
   TTreeReaderArray<double> PC_vtx_sigmayz;
   TTreeReaderArray<vector<int>> PC_vTrack_algo;
   TTreeReaderArray<vector<int>> PC_vTrack_charge;*/
   TTreeReaderArray<vector<double>>* PC_vTrack_pt; 
   TTreeReaderArray<vector<double>>* PC_vTrack_eta;
   TTreeReaderArray<vector<double>>* PC_vTrack_phi; 
 /*  TTreeReaderArray<vector<double>> PC_vTrack_chi2; 
   TTreeReaderArray<vector<double>> PC_vTrack_normalizedChi2; 
   TTreeReaderArray<vector<double>> PC_vTrack_rho; 
   TTreeReaderArray<vector<unsigned int>> PC_vTrack_numberOfValidHits; 
   TTreeReaderArray<vector<unsigned int>> PC_vTrack_numberOfExpectedOuterHits; 
   TTreeReaderArray<vector<unsigned int>> PC_vTrack_closestDxyPVIdx; 
   TTreeReaderArray<vector<double>> PC_vTrack_closestDxyPVIdx_dxy; 
   TTreeReaderArray<vector<double>> PC_vTrack_closestDxyPVIdx_dz; 
   TTreeReaderArray<vector<unsigned int>> PC_vTrack_closestDzPVIdx; 
   TTreeReaderArray<vector<double>> PC_vTrack_closestDzPVIdx_dxy; 
   TTreeReaderArray<vector<double>> PC_vTrack_closestDzPVIdx_dz; 
   TTreeReaderArray<vector<double>> PC_fTrack_pt; 
   TTreeReaderArray<vector<double>> PC_fTrack_eta; 
   TTreeReaderArray<vector<double>> PC_fTrack_phi; 
	*/

//	TTreeReader* reader;
	mytreevalues(TTreeReader& reader);
//	mytreevalues(mytreevalues&)=default;
//	void init();
};
mytreevalues::mytreevalues(TTreeReader& reader){
//	reader* = new TTreeReader(myreader)
//	init();	
//}
//void mytreevalues::init(){
   PC_vTrack_pt = new TTreeReaderArray<vector<double>>(reader, "PC_vTrack_pt"); 
   PC_vTrack_eta= new TTreeReaderArray<vector<double>>(reader, "PC_vTrack_eta");
   PC_vTrack_phi= new TTreeReaderArray<vector<double>>(reader, "PC_vTrack_phi"); 
  //PC_vTrack_pt(reader,"PC_vTrack_pt");
  //PC_vTrack_eta(reader,"PC_vTrack_eta");
  //PC_vTrack_phi(reader,"PC_vTrack_phi");
}


#endif
