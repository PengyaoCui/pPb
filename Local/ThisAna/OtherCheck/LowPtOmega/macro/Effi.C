#include "inc/PyJetUtils.h"

void Effi(){

  auto f = TFile::Open("../AnalysisOutputs_Results.root", "read");
  auto l = (TList*)f->Get(Form("listResults_Omega_Default_0100"));
  f->Close();
  TH1D *h = (TH1D*)l->FindObject(Form("hEff"));

  Double_t n1 = h->GetBinError(1); Double_t w1 = h->GetBinWidth(1);
  Double_t n2 = h->GetBinError(2); Double_t w2 = h->GetBinWidth(2);

  f = TFile:: Open("../../JEBins/AnalysisOutputs_Results.root", "read");
  l = (TList*)f->Get(Form("listResults_Omega_Default_0100"));
  f->Close();
  TH1D *h1 = (TH1D*)l->FindObject(Form("hEff"));
  Double_t n3 = h1->GetBinError(1);
  
  cout<<"n1"<< "=" <<n1<<endl;
   cout<<"n2"<< "=" <<n2<<endl;
   cout<<"n3"<< "=" <<n3<<endl;
  return;
}

