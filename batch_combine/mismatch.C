void mismatch(string rootfile = "All.root", string dtype="BKG", string histo="CutFlowHist3", int ibin=15){
 
   string histname = dtype+histo;

   TFile *f = new TFile(rootfile.c_str());

// Event count from cutflow histogram
   TH1D *h1 = (TH1D*)f->Get(histname.c_str());
//   cout << setw(10) << h1->GetBinContent(ibin) << " +- " 
//        << setw(10) << h1->GetBinError(ibin) << endl;

   double wevs = h1->GetBinContent(ibin);

// Event count from MperpHist3 (filled when becuts.all() is true
   TH1D *h2 = (TH1D*)f->Get("BKGMperpHist3");
   double total = h2->Integral() + 
                  h2->GetBinContent(0) + 
                  h2->GetBinContent( h2->GetNbinsX() + 1 );
   f->Close();

   double diff = wevs - total;
   cout << "rootfile: " << rootfile << endl;
   cout << "h1:   " << wevs  << endl;
   cout << "h2:   " << total << endl;
   cout << "diff: " << diff << endl;
   if(abs(diff)>0.001){
      cout << "BIG DIFFERENCE " << diff << endl;
   }

}
