#include "./SourceFun.h"

void FinalRatio(const TString CentMin = "0", const TString CentMax = "100"){
  
  TString sPath = "./result"; 
  TString sFile = "UncertaintyRatio.root";
  TString sList = Form("LKR_Uncer_%s%s", CentMin.Data(), CentMax.Data());
  
  TString sCIH = "hCILKR";
  TString sCJH = "hCJLKR";
  TString sCUH = "hCULKR";
  
  TString sEIH = "hEILKR";  
  TString sEJH = "hEJLKR";  
  TString sEUH = "hEULKR";  

  auto sLatex(Form("p-Pb #sqrt{#it{s}_{NN}} = 5.02 TeV"));
  Double_t XMin = 0.6;
  Double_t XMax = 12.;
  
  //-----------------------------------
  TCanvas *can = nullptr;
  TLatex* tex = nullptr;
  TLegend *leg = nullptr;
  can = MakeCanvas("can");
  //can->SetLogy(); 
  leg = new TLegend(0.7,0.9,1.0,0.6); SetLegend(leg);
  
  //-----------------------------------
  auto hIncl1 = (TH1D*)GetTH1D(sPath, sFile, sList, sCIH); hIncl1->SetName("InclCen");
  auto hJE1   = (TH1D*)GetTH1D(sPath, sFile, sList, sCJH); hJE1->SetName("JECen");
  auto hUE1   = (TH1D*)GetTH1D(sPath, sFile, sList, sCUH); hUE1->SetName("UECen");
  
  auto hIncl2 = (TH1D*)GetTH1D(sPath, sFile, sList, sEIH); hIncl2->SetName("InclErr");
  auto hJE2   = (TH1D*)GetTH1D(sPath, sFile, sList, sEJH); hJE2->SetName("JEErr");
  auto hUE2   = (TH1D*)GetTH1D(sPath, sFile, sList, sEUH); hUE2->SetName("UEErr");

  //-----------------------------------
  const auto nI = hIncl1->GetNbinsX();
  const auto nJ = hJE1->GetNbinsX();
  //-----------------------------------
  hIncl1->GetYaxis()->SetRangeUser(0., 1.5);
  hIncl1->GetXaxis()->SetRangeUser(0., 12.);
  hIncl1->GetYaxis()->SetTitle("#frac{#Lambda + #bar{#Lambda}}{2K^{0}_{S}}");
  //hIncl1->GetYaxis()->SetTitle("#frac{#Xi + #bar{#Xi}}{2K^{0}_{S}}");
  //-----------------------------------

  DrawHisto(hIncl1, cLine[0], sMark[0], "same");
  leg->AddEntry(hIncl1, "Incl");
  auto gIncl = (TGraphErrors*)ConvHistogramToGraphErrors(hIncl1, hIncl2, nI); gIncl->SetName("Incl");
  //DrawGraph(gIncl, cLine[0], sMark[0], "P"); 
  
  //gIncl->SetFillColorAlpha(cLine[3],0.35);
  //gIncl->Draw("E2 same");

  DrawGraph(gIncl, cLine[0], "E2");
  //-----------------------------------

  DrawHisto(hJE1, cLine[1], sMark[1], "same");
  leg->AddEntry(hJE1, "JE");
  auto gJE = (TGraphErrors*)ConvHistogramToGraphErrors(hJE1, hJE2, nJ); gJE->SetName("JE");
  //DrawGraph(gJE, cLine[1], sMark[1], "P"); 
  DrawGraph(gJE, cLine[1], "E2");
  //-----------------------------------
  DrawHisto(hUE1, cLine[2], sMark[2], "same");
  leg->AddEntry(hUE1, "UE");
  auto gUE = (TGraphErrors*)ConvHistogramToGraphErrors(hUE1, hUE2, nJ); gUE->SetName("UE");
  //DrawGraph(gUE, cLine[2], sMark[2], "P");
  DrawGraph(gUE, cLine[2], "E2");
 
  //-----------------------------------
  tex =  new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.15, 0.9, sLatex);
  tex->DrawLatex(0.15, 0.83, "Jet: Anti-#it{k}_{T}, #it{R} = 0.4");
  tex->DrawLatex(0.15, 0.75, "#it{p}_{T, jet}^{ch} > 10 GeV/#it{c}, |#it{#eta}_{jet}| < 0.35");
  tex->DrawLatex(0.15, 0.65, Form("%s-%s%%", CentMin.Data(), CentMax.Data()));
  tex->DrawLatex(0.15, 0.59, "|#it{#eta}_{V^{0}}| < 0.75, #Delta#it{R}(V^{0}, jet) < 0.4");
  leg->AddEntry(gIncl, "Sys.Error", "f");  
  leg->Draw();
  gStyle->SetOptStat("");
  //can->SaveAs(Form("./figure/LKR_wSysError_%s%s.eps", CentMin.Data(), CentMax.Data()));
  //DrawAliLogo(0.65, 0.90, 24, kTRUE);
  CanvasEnd(can);
  return;
}
