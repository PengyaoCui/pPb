#include "../inc/PyJetUtils.h"

void UEUncer_OCFit(const TString sType = "Xi", const TString CentMin = "0", const TString CentMax = "100"){
//=============================================================================
  
  auto f = TFile::Open("/home/cuipengyao/study/pPb/Local/ThisAna/JE/AnalysisOutputs_Results.root", "read");
  auto l04 = (TList*)f->Get(Form("listResults_%s_Default_OC_%s%s",sType.Data(), CentMin.Data(), CentMax.Data()));
  auto lPCL = (TList*)f->Get(Form("listResults_%s_Default_PCL_%s%s",sType.Data(), CentMin.Data(), CentMax.Data()));
  auto lPCU = (TList*)f->Get(Form("listResults_%s_Default_PCU_%s%s",sType.Data(), CentMin.Data(), CentMax.Data()));
  f->Close();
  auto hPC = (TH1D*) lPCL->FindObject(Form("hNco"));
  auto hPCU = (TH1D*) lPCU->FindObject(Form("hNco"));
  hPC->Add(hPCU, 1.);
  hPC->Scale(0.5);
  
   
  f = TFile::Open("/home/cuipengyao/study/pPb/Local/ThisAna/Uncertainty/JE/UE/OC06/AnalysisOutputs_Results.root", "read");
  auto l06 = (TList*)f->Get(Form("listResults_%s_Default_OC_%s%s",sType.Data(), CentMin.Data(), CentMax.Data()));
  f->Close();
  f = TFile::Open("/home/cuipengyao/study/pPb/Local/ThisAna/Uncertainty/JE/UE/OC08/AnalysisOutputs_Results.root", "read");
  auto l08 = (TList*)f->Get(Form("listResults_%s_Default_OC_%s%s",sType.Data(), CentMin.Data(), CentMax.Data()));
  f->Close();
  
  auto h04 = (TH1D*) l04->FindObject(Form("hNco")); NormBinningHistogram(h04); 
  auto h06 = (TH1D*) l06->FindObject(Form("hNco")); NormBinningHistogram(h06); 
  auto h08 = (TH1D*) l08->FindObject(Form("hNco")); NormBinningHistogram(h08); 
  TH1D *h0 = new TH1D("h0", "", 20, 0, 2);
  TH1D *h1 = new TH1D("h1", "", 20, 0, 2);
  TH1D* h = (TH1D*)h04->Clone("h"); h->Reset();

  
  for(Int_t i = 1; i<= h0->GetNbinsX(); i++){
    h0->SetBinContent(h0->FindBin(0.4), h04->GetBinContent(i)); h0->SetBinError(h0->FindBin(0.4), h04->GetBinError(i));
    h0->SetBinContent(h0->FindBin(0.6), h06->GetBinContent(i)); h0->SetBinError(h0->FindBin(0.6), h06->GetBinError(i));
    h0->SetBinContent(h0->FindBin(0.8), h08->GetBinContent(i)); h0->SetBinError(h0->FindBin(0.8), h08->GetBinError(i));
    h1->SetBinContent(h1->FindBin(TMath::Pi()*0.5), hPC->GetBinContent(i)); h1->SetBinError(h1->FindBin(TMath::Pi()*0.5), hPC->GetBinError(i));
    TF1 *fun = new TF1("fun", "[0]*x+[1]", 0.6, 1.);
    h0->Fit("fun", "RN");
    TF1* Fun = new TF1("Fun",  "[0]*x+[1]", 0.6, 2.);
    Fun->FixParameter(0, fun->GetParameter(0));
    Fun->FixParameter(1, fun->GetParameter(1));
    h0->SetBinContent(h0->FindBin(TMath::Pi()*0.5), Fun->Integral(1.5, 1.6)/0.1); h0->SetBinError(h0->FindBin(TMath::Pi()*0.5), h08->GetBinError(i));
    
    h->SetBinContent(i, 0.5*TMath::Abs(hPC->GetBinContent(i) - Fun->Integral(1.5, 1.6)/0.1));
    h->SetBinError(i, 0.);
  }  
  h->SetName("hMax"); 
  TFile *F = TFile::Open("./result/UEUncer.root", "UPDATE");
  TList *l = new TList();
  l->Add(h);
  l->Write(Form("%s_UESub_%s%s_wFitOC",sType.Data(), CentMin.Data(), CentMax.Data()), TObject::kSingleKey);
  F->Close();

  return;
}

