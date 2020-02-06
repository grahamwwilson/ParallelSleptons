    // mylocaltree.h 
    // Here we can make local copies of everything that 
    // we use - or even everything that exists.

	//Always make a local copy, if it is a value dereference. 
    //If you don't do this, scope/dereferencing will get really weird, 
    // clunky, and unmanageable
	//have to auto& or myreader will try to register copy of 
    //the readerarray ptr

	//reco leptons
	auto Nlep = *(s.Nlep);
	auto& PT_lep = s.PT_lep;
	auto& Eta_lep = s.Eta_lep;
	auto& Phi_lep = s.Phi_lep;
    auto& ID_lep = s.ID_lep;            //int
    auto& SIP3D_lep = s.SIP3D_lep;      //double 
	auto& Charge_lep = s.Charge_lep;
	auto& PDGID_lep = s.PDGID_lep;
	auto& M_lep = s.M_lep;
    auto& MiniIso_lep = s.MiniIso_lep;  //double

	//susy variables for category 0 
	auto& Njet_ISR0 = s.Njet_ISR[0];
	auto& Njet_S0 = s.Njet_S[0];
	auto& Nlep_S0 = s.Nlep_S[0];
	auto& Nlepa_S0 = s.Nlep_a[0];
	auto& Nlepb_S0 = s.Nlep_b[0];
	auto& MS0 = s.MS[0];
	auto& PS0 = s.PS[0];
	auto& PTISR0 = s.PTISR[0];
	auto& RISR0 = s.RISR[0];
	auto& MISR0 = s.MISR[0];

	//susy variables for category 1
	auto& Njet_ISR1 = s.Njet_ISR[1];
	auto& Njet_S1 = s.Njet_S[1];
	auto& Nlep_S1 = s.Nlep_S[1];
	auto& Nlepa_S1 = s.Nlep_a[1];
	auto& Nlepb_S1 = s.Nlep_b[1];
	auto& MS1 = s.MS[1];
	auto& PS1 = s.PS[1];
	auto& PTISR1 = s.PTISR[1];
	auto& RISR1 = s.RISR[1];
	auto& MISR1 = s.MISR[1];

	auto MET = *(s.MET);
	auto MET_phi = *(s.MET_phi);
	auto genMET = *(s.genMET);
	auto genMET_phi = *(s.genMET_phi);

    auto Njet = *(s.Njet);
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
    auto& genMomPDGID_susy = s.genMomPDGID_susy;
    auto& genPT_susy = s.genPT_susy;
    auto& genEta_susy = s.genEta_susy;
    auto& genPhi_susy = s.genPhi_susy;
    auto& genM_susy = s.genM_susy;

//gen leptons (we dont require susy)
    auto genNlep = *(s.genNlep);
    auto& genPDGID_lep = s.genPDGID_lep;
    auto& genMomPDGID_lep = s.genMomPDGID_lep;
    auto& genPT_lep = s.genPT_lep;
    auto& genEta_lep = s.genEta_lep;
    auto& genPhi_lep = s.genPhi_lep;
    auto& genM_lep = s.genM_lep;

//gen neutrinos
    auto genNnu = *(s.genNnu);
    auto& genPDGID_nu = s.genPDGID_nu;
    auto& genMomPDGID_nu = s.genMomPDGID_nu;
    auto& genPT_nu = s.genPT_nu;
    auto& genEta_nu = s.genEta_nu;
    auto& genPhi_nu = s.genPhi_nu;

	auto weight = *(s.weight);

