void plotb2(){

   TFile *f = new TFile("Bkgd.root");
   TH1D *h = (TH1D*)f->Get("DYCutFlowHist2");
   h->Reset();

   TH1D *h1 = (TH1D*)f->Get("DYCutFlowHist2");
   TH1D *h2 = (TH1D*)f->Get("TTCutFlowHist2");
   TH1D *h3 = (TH1D*)f->Get("WJCutFlowHist2");
   TH1D *h4 = (TH1D*)f->Get("ZZCutFlowHist2");
   TH1D *h5 = (TH1D*)f->Get("WWCutFlowHist2");
   TH1D *h6 = (TH1D*)f->Get("WZCutFlowHist2");
   TH1D *h7 = (TH1D*)f->Get("ZJCutFlowHist2");
   TH1D *h8 = (TH1D*)f->Get("STCutFlowHist2");

   h->Add(h1); h->Add(h2); h->Add(h3); h->Add(h4); 
   h->Add(h5); h->Add(h6); h->Add(h7); h->Add(h8);

   cout << "h1 (DY) " << h1->GetBinContent(14) << endl;
   cout << "h2 (TT) " << h2->GetBinContent(14) << endl;
   cout << "h3 (WJ) " << h3->GetBinContent(14) << endl;
   cout << "h4 (ZZ) " << h4->GetBinContent(14) << endl;
   cout << "h5 (WW) " << h5->GetBinContent(14) << endl;
   cout << "h6 (WZ) " << h6->GetBinContent(14) << endl;
   cout << "h7 (ZJ) " << h7->GetBinContent(14) << endl;
   cout << "h8 (ST) " << h8->GetBinContent(14) << endl;
   cout << "h  " << h->GetBinContent(14) << endl;

}
