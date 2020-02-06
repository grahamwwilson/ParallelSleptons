void get(string rootfile="All.root", string dtype="BKG", 
         string histtype="CutFlowHist2"){

// Print cut-flow type things for Selection 2 on specific data-set.
// Default is all SM backgrounds 
// root -l -b -q 'get.C("LLVV.root")'
// root -l -b -q 'get.C("Slep.root","SMS_250_240")'
// root -l -b -q 'get.C("Slep.root","SMS_250_240","ECutFlowHist2")'

   string histname = dtype+histtype;
   cout << "Statistics constructed from rootfile: " << rootfile << endl;
   cout << "using histogram                     : " << histname << endl;

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

   cout << "Cut flow for " << dtype << " events " << endl;
   cout << "Weighted events passing each cut sequentially" << endl;
   
   for (int i=1; i<=14; i++){
      string mystring = cutStrings[i-1];

      cout << setw(2) << i << " " << setw(30) << mystring 
           << setw(10) << h->GetBinContent(i) << "  +- " 
           << setw(8) << h->GetBinError(i) << endl;

   }
}
