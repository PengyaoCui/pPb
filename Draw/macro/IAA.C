#include "./SourceFun.h"

void IAA( const TString CentMin = "0", const TString CentMax = "100"){

  const TString sType = "Kshort";
  //p-Pb 
  auto sPath = "./result"; 
  auto sCFile = "PtSpect_Eta.root";
  if(sType == "Xi") sCFile= "PtSpect_Eta_OldBinWidth.root";
  auto sCJetHist = Form("hPtJE_%s_%s%s", sType.Data(), CentMin.Data(), CentMax.Data());
  if(sType == "Lambda" || sType == "AntiLa") sCJetHist = Form("hPtJC_%s_%s%s", sType.Data(), CentMin.Data(), CentMax.Data());
  auto sEFile = "UncertaintyTot.root";
  if(sType == "Xi") sEFile = "UncertaintyTot_OldBinWidth.root";

  auto sEList = Form("%s_UncerTot_%s%s", sType.Data(), CentMin.Data(), CentMax.Data());
  auto sEJHist = "hJErr";  

  auto sLatex(Form("p-Pb #sqrt{#it{s}_{NN}} = 5.02 TeV"));
  Double_t XMin = 0.6;
  Double_t XMax = 12.;
  
  //-----------------------------------
  TCanvas *can = nullptr;
  TLatex* tex = nullptr;
  TLegend *leg = nullptr;
  can = MakeCanvas("can");
  leg = new TLegend(0.7,0.9,1.0,0.8); SetLegend(leg);
  
  //-----------------------------------
  auto hJE1   = (TH1D*)GetTH1D(sPath, sCFile, "", sCJetHist); hJE1->SetName("JECen");
  auto hJE2 = (TH1D*)GetTH1D(sPath, sEFile, sEList, sEJHist); hJE2->SetName("JEErr");
  //-----------------------------------
  const auto nJ = hJE1->GetNbinsX();
  //-----------------------------------
  auto hErrJE = (TH1D*)hJE2->Clone("hErrJE");
  for(Int_t i = 1; i<= hJE2->GetNbinsX(); i++){
    hErrJE->SetBinContent(i,hJE1->GetBinContent(i));
    hErrJE->SetBinError(i,hErrJE->GetBinContent(i)*hJE1->GetBinContent(i));
  }
  //-----------------------------------
  //pp
  TString sPath_pp = "/home/cuipengyao/study/pp/Draw/macro/result";
  TString sFile_pp = Form("PtSpect_Eta_Full.root"); 
  TString sJE1pp = Form("hPtJE_%s", sType.Data()); 
  Double_t dErrJEpp[] = {0.027974, 0.0246329, 0.018597, 0.0125446, 0.00735288, 0.0029652, 0.000815588};

  auto hJE1pp = (TH1D*)GetTH1D(sPath_pp, sFile_pp, "", sJE1pp); hJE1->SetName("JECenpp");
  auto hJE2pp = (TH1D*)hJE1pp->Clone("JEErrpp");hJE2pp->Reset(); 
  auto hErrJEpp = (TH1D*)hJE1pp->Clone("hErrJEpp");hErrJEpp->Reset(); 
  for(Int_t i = 1; i<= hJE2pp->GetNbinsX(); i++){
    auto dJE2C = hJE1pp->GetBinContent(i);
    hJE2pp->SetBinContent(i, dErrJEpp[i-1]/dJE2C);
    hErrJEpp->SetBinContent(i, dJE2C);
    hErrJEpp->SetBinError(i, dErrJEpp[i-1]);
  }
  hErrJEpp = RebinTH1D(hErrJEpp, hErrJE);
  
  hErrJE->Divide(hErrJEpp); 
  for(Int_t i = 1; i<= hErrJE->GetNbinsX(); i++){hErrJE->SetBinContent(i, hErrJEpp->GetBinError(i));}

  auto JEIaa = (TH1D*)hJE1->Clone("JEIaa");JEIaa->Reset();
  hJE1pp = RebinTH1D(hJE1pp, hJE1); 
  JEIaa->Divide(hJE1, hJE1pp);
  JEIaa->GetYaxis()->SetRangeUser(0.5, 2);
  JEIaa->GetYaxis()->SetTitle("#it{I}_{pPb}");
  DrawHisto(JEIaa, cLine[0], sMark[0], "same"); 

  auto gJE = (TGraphErrors*)ConvHistogramToGraphErrors(JEIaa, hErrJEpp, nJ); gJE->SetName("JE");
  DrawGraph(gJE, cLine[0], "E2");

 
  //-----------------------------------
  tex =  new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.15, 0.9, sLatex);
  leg->AddEntry(gJE, "Sys.Error", "f");  
  leg->Draw();
  gStyle->SetOptStat("");
  //can->SaveAs(Form("./figure/%s_IAA_wSysError_%s%s.eps", sType.Data(), CentMin.Data(), CentMax.Data()));
  //DrawAliLogo(0.65, 0.90, 24, kTRUE);
  CanvasEnd(can);
  return;
}
