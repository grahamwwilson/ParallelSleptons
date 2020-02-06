void plotb2(){

   TFile *f = new TFile("Bkgd.root");
   TH1D *h = (TH1D*)f->Get("DYCutFlowHist");
   h->Reset();

   TH1D *h1 = (TH1D*)f->Get("DYCutFlowHist");
   TH1D *h2 = (TH1D*)f->Get("TTCutFlowHist");
   TH1D *h3 = (TH1D*)f->Get("WJCutFlowHist");
   TH1D *h4 = (TH1D*)f->Get("ZZCutFlowHist");
   TH1D *h5 = (TH1D*)f->Get("WWCutFlowHist");
   TH1D *h6 = (TH1D*)f->Get("WZCutFlowHist");
   TH1D *h7 = (TH1D*)f->Get("ZJCutFlowHist");
   TH1D *h8 = (TH1D*)f->Get("STCutFlowHist");

   h->Add(h1); h->Add(h2); h->Add(h3); h->Add(h4); 
   h->Add(h5); h->Add(h6); h->Add(h7); h->Add(h8);

   cout << "h1 (DY) " << h1->GetBinContent(12) << endl;
   cout << "h2 (TT) " << h2->GetBinContent(12) << endl;
   cout << "h3 (WJ) " << h3->GetBinContent(12) << endl;
   cout << "h4 (ZZ) " << h4->GetBinContent(12) << endl;
   cout << "h5 (WW) " << h5->GetBinContent(12) << endl;
   cout << "h6 (WZ) " << h6->GetBinContent(12) << endl;
   cout << "h7 (ZJ) " << h7->GetBinContent(12) << endl;
   cout << "h8 (ST) " << h8->GetBinContent(12) << endl;
   cout << "h  " << h->GetBinContent(12) << endl;

}
