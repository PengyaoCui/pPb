#include "./SourceFun.h"

void combine(){
 
  TString sname = "NJ";
  //Bool_t IsSave(0);
  Bool_t IsSave(1);
  //Double_t dEvent = 2.49632e+8+1.28757e+8+6.72309e+7;//Incl 
  //Double_t dEvent = (417987.+202441.+113201.)*0.06;//JC 
  //Double_t dEvent = (417987.+202441.+113201.)*0.06*4;//PC 
  //Double_t dEvent = (417987.+202441.+113201.)*0.94;//OC 
  Double_t dEvent = 2.45977e+8+1.26938e+8+6.62423e+7;//No Jet 

  TString sFile = "./result/PtSpect_LHC16khl.root";
  TString HistNeg = "XiNeg";

  TString sPath  = "/home/cuipengyao/study/code/Draw/macro/Cascade_LHC16klh/result";
  TString sFilek = "PtSpect_LHC16k_wo_Norm.root";
  TString sFileh = "PtSpect_LHC16h_wo_Norm.root";
  TString sFilel = "PtSpect_LHC16l_wo_Norm.root";
  TString sHist  = Form("hPt%s_Xi", sname.Data());

  TString sLatex = Form("%s #Xi^{#pm} #it{p}_{T} distribution",sname.Data());
  //TString sLatex = "Raw inclusive #Xi^{-} result to LF";
  Double_t   YMin = 2e-6;
  Double_t   YMax = 1e7;
  //-----------------------------------
  TCanvas * c2 = new TCanvas("c2","");
  SetStyle();
  SetCanv(c2);
  c2->SetLogy();
  if (IsSave) TFile *file = TFile::Open(sFile, "UPDATE");
  //-----------------------------------
  TH1D *hk = (TH1D*)GetTH1FromFile(sPath,  sFilek,  sHist);
  hk->SetName(Form("hk_%s",sname.Data()));
  SetLine(hk,cLine[0], sMark[0]);
  SetAxis(hk, YMin, YMax, 0.6, 7., "d#rho/d#it{p}_{T}");
  //hk->Draw("same");

  TH1D *hh = (TH1D*)GetTH1FromFile(sPath,  sFileh,  sHist);
  hh->SetName(Form("hh_%s",sname.Data()));
  SetLine(hh,cLine[1], sMark[1]);
  SetAxis(hh, YMin, YMax, 0.6, 7., "d#rho/d#it{p}_{T}");
  //hh->Draw("same");

  TH1D *hl = (TH1D*)GetTH1FromFile(sPath,  sFilel,  sHist);
  hl->SetName(Form("hl_%s",sname.Data()));
  SetLine(hl,cLine[2], sMark[2]);
  SetAxis(hl, YMin, YMax, 0.6, 7., "d#rho/d#it{p}_{T}");
  //hl->Draw("same");

  TH1D *hTotal = (TH1D*)hk->Clone(Form("hTotal_%s",sname.Data()));
  hTotal->Add(hh);
  hTotal->Add(hl);
  SetLine(hTotal,cLine[3], sMark[3]);
  hTotal->Draw("same");
  hTotal->Scale(1./(dEvent*2*0.75*TMath::TwoPi()));
  hTotal->SetName(Form("hTotal_%s",sname.Data()));
  //dIncl/(dEvent*2*0.75*TMath::TwoPi()) 
  if(IsSave) {file->cd(); hTotal->Write(Form("hTotal_%s",sname.Data()), TObject::kSingleKey);}
  if(IsSave) {file->Close();}

  return;
}
