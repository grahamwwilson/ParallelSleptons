void gets2(string dtype="SMS_300_290"){


//   string rootfile = dtype+"/susyHists.root";

   string rootfile = "Signal_Sleptons_New.root";
   string histname = dtype+"CutFlowHist2";

   TFile *f = new TFile(rootfile.c_str());
   TH1D *h = (TH1D*)f->Get(histname.c_str());

//   enum cutNames{kLeptons, kID, kISO, kPROMPT, kSF, kOS, k2L, kbjet, kMET, kPTISR0, kRISR0, numCuts};

   const char *cutStrings[ ] = {" None ",
                                " >= 2 leptons ",
                                " ID'd lepton pair ",
                                " Isolated lepton pair ",
                                " Prompt lepton pair ", 
                                " Same-flavor lepton pair ", 
                                " Opposite-sign lepton pair ",
                                " Exactly two leptons ",
                                " No b-jets ",
                                " MET > 200 GeV ",
                                " Nlep_S1 == 2 ",
                                " Njets_S1 == 0 ", 
                                " PTISR1 > 250 GeV ", 
                                " RISR1 > 0.95 "};

   cout << "Cut flow for " << dtype << " events " << endl;
   cout << "Weighted events passing each cut sequentially" << endl;
   
   for (int i=1; i<=14; i++){
      string mystring = cutStrings[i-1];

      cout << setw(2) << i << " " << setw(30) << mystring 
           << setw(10) << h->GetBinContent(i) << "  +- " 
           << setw(8) << h->GetBinError(i) << endl;

   }
}
