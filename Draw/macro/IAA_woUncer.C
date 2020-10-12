#include "./SourceFun.h"

void IAA_woUncer( const TString CentMin = "0", const TString CentMax = "10"){

  const TString sType = "Kshort";
  //p-Pb 
  auto sPath = "./result"; 
  auto sCFile = "PtSpect_Eta.root";
  auto sCJetHist = Form("hPtJE_%s_%s%s", sType.Data(), CentMin.Data(), CentMax.Data());
  if(sType == "Lambda" || sType == "AntiLa") sCJetHist = Form("hPtJC_%s_%s%s", sType.Data(), CentMin.Data(), CentMax.Data());

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
  //-----------------------------------
  const auto nJ = hJE1->GetNbinsX();
  //-----------------------------------
  //pp
  TString sPath_pp = "/home/cuipengyao/study/pp/Draw/macro/result";
  TString sFile_pp = Form("PtSpect_Eta_16-17.root"); 
  TString sJE1pp = Form("hPtJE_%s", sType.Data()); 

  auto hJE1pp = (TH1D*)GetTH1D(sPath_pp, sFile_pp, "", sJE1pp); hJE1->SetName("JECenpp");

  auto JEIaa = (TH1D*)hJE1->Clone("JEIaa");JEIaa->Reset();
  hJE1pp = RebinTH1D(hJE1pp, hJE1); 
  JEIaa->Divide(hJE1, hJE1pp);
  JEIaa->GetYaxis()->SetRangeUser(0.5, 2);
  JEIaa->GetYaxis()->SetTitle("#it{I}_{pPb}");
  DrawHisto(JEIaa, cLine[0], sMark[0], "same"); 
 
  //-----------------------------------
  tex =  new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.15, 0.9, sType);
  tex->DrawLatex(0.15, 0.8, sLatex);
  leg->Draw();
  gStyle->SetOptStat("");
  //can->SaveAs(Form("./figure/%s_IAA_wSysError_%s%s.eps", sType.Data(), CentMin.Data(), CentMax.Data()));
  //DrawAliLogo(0.65, 0.90, 24, kTRUE);
  CanvasEnd(can);
  return;
}
