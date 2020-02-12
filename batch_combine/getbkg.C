void getbkg(string dtype="BKG", string histo = "CutFlowHist3", int ibin=15){

   string rootfile = "tmp.root";
   
   string histname = dtype+histo;

   TFile *f = new TFile(rootfile.c_str());
   TH1D *h = (TH1D*)f->Get(histname.c_str());

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

   cout << "Weighted event TOTAL " << endl;
   
//   for (int i=14; i<=14; i++){
//      string mystring = cutStrings[i-1];

      cout << setw(10) << h->GetBinContent(ibin) << " +- " 
           << setw(10) << h->GetBinError(ibin) << endl;

//   }
   f->Close();
}
