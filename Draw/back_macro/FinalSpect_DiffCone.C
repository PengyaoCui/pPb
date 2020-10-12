#include "./SourceFun.h"

void FinalSpect(const TString sType = "Kshort", const TString CentMin = "0", const TString CentMax = "100"){
  
  auto sPath = "./result"; 
  auto sCFile = "PtSpect_ThisAna.root";
  
  auto sCInclHist = Form("hPtIncl_%s_%s%s", sType.Data(), CentMin.Data(), CentMax.Data());
  auto sCJetHist = Form("hPtJE_%s_%s%s", sType.Data(), CentMin.Data(), CentMax.Data());
  if(sType == "Lambda" || sType == "AntiLa") sCJetHist = Form("hPtJC_%s_%s%s", sType.Data(), CentMin.Data(), CentMax.Data());
  auto sCUEHist = Form("hPtPC_%s_%s%s", sType.Data(), CentMin.Data(), CentMax.Data());
  
  auto sEFile = "UncertaintyTot.root";
  auto sEList = Form("%s_UncerTot_%s%s", sType.Data(), CentMin.Data(), CentMax.Data());
  auto sEIHist = "hIErr";  
  auto sEJHist = "hJErr";  
  auto sEUHist = "hUErr";  

  auto sLatex(Form("p-Pb #sqrt{#it{s}_{NN}} = 5.02 TeV"));
 
  Double_t XMin = 0.;
  Double_t XMax;
  Double_t YMin;
  Double_t YMax;

  if(sType == "Kshort"){ XMax = 12.; YMax = 100.; YMin = 1e-6;}
  if(sType == "Lambda" || sType == "AntiLa"){ XMax = 12.; YMax = 70.; YMin = 1e-7;}
  if(sType == "Xi"){ XMax = 8.; YMax = 10.; YMin = 1e-6;}
  if(sType == "Omega"){ XMax = 5.; YMax = 1e-1; YMin = 1e-5;}
 
  //-----------------------------------
  TCanvas *can = nullptr;
  TLatex* tex = nullptr;
  TLegend *leg = nullptr;
  can = MakeCanvas("can");
  can->SetLogy(); 
  leg = new TLegend(0.7,0.9,1.0,0.6); SetLegend(leg);
  
  //-----------------------------------
  auto hIncl1 = (TH1D*)GetTH1D(sPath, sCFile, "", sCInclHist); hIncl1->SetName("InclCen");
  auto hJE1   = (TH1D*)GetTH1D(sPath, sCFile, "", sCJetHist); hJE1->SetName("JECen");
  auto hUE1   = (TH1D*)GetTH1D(sPath, sCFile, "", sCUEHist); hUE1->SetName("UECen");
  
  auto hIncl2 = (TH1D*)GetTH1D(sPath, sEFile, sEList, sEIHist); hIncl2->SetName("InclErr");
  auto hJE2 = (TH1D*)GetTH1D(sPath, sEFile, sEList, sEJHist); hJE2->SetName("JEErr");
  auto hUE2 = (TH1D*)GetTH1D(sPath, sEFile, sEList, sEUHist); hUE2->SetName("UEErr");

  if(sType == "Lambda"){
    auto hAIncl1 = (TH1D*)GetTH1D(sPath, sCFile, "", Form("hPtIncl_AntiLa_%s%s", CentMin.Data(), CentMax.Data())); hAIncl1->SetName("AInclCen");
    auto hAJE1   = (TH1D*)GetTH1D(sPath, sCFile, "", Form("hPtJC_AntiLa_%s%s", CentMin.Data(), CentMax.Data())); hAJE1->SetName("AJECen");
    auto hAUE1   = (TH1D*)GetTH1D(sPath, sCFile, "", Form("hPtPC_AntiLa_%s%s", CentMin.Data(), CentMax.Data())); hAUE1->SetName("AUECen");
    
    auto hAIncl2 = (TH1D*)GetTH1D(sPath, sEFile, Form("AntiLa_UncerTot_%s%s", CentMin.Data(), CentMax.Data()), sEIHist); hAIncl2->SetName("AInclErr");
    auto hAJE2 = (TH1D*)GetTH1D(sPath, sEFile, Form("AntiLa_UncerTot_%s%s", CentMin.Data(), CentMax.Data()), sEJHist); hAJE2->SetName("AJEErr");
    auto hAUE2 = (TH1D*)GetTH1D(sPath, sEFile, Form("AntiLa_UncerTot_%s%s", CentMin.Data(), CentMax.Data()), sEUHist); hAUE2->SetName("AUEErr");
   
    hIncl1->Add(hAIncl1);
    hJE1->Add(hAJE1);
    hUE1->Add(hAUE1);
    Double_t dIncl1, dJE1, dUE1;
    Double_t dIncl2, dJE2, dUE2;
    Double_t dAIncl1, dAJE1, dAUE1;
    Double_t dAIncl2, dAJE2, dAUE2;
    for(Int_t i = 1; i<=hIncl2->GetNbinsX(); i++){ 
      hIncl2->SetBinError(i, 0); 
      dIncl1 =  hIncl1->GetBinContent(i); 
      dIncl2 =  hIncl2->GetBinContent(i);
      dAIncl1 = hAIncl1->GetBinContent(i); 
      dAIncl2 = hAIncl2->GetBinContent(i);
      hIncl2->SetBinContent(i, TMath::Sqrt(dIncl1*dIncl2*dIncl1*dIncl2 + dAIncl1*dAIncl2*dAIncl1*dAIncl2)/(dIncl1+dAIncl1));
    } hIncl2->SetName("InclErr");
    for(Int_t i = 1; i<=hJE2->GetNbinsX(); i++){ 
      hJE2->SetBinError(i, 0); 
      dJE1 =  hJE1->GetBinContent(i); 
      dJE2 =  hJE2->GetBinContent(i);
      dAJE1 = hAJE1->GetBinContent(i); 
      dAJE2 = hAJE2->GetBinContent(i);
      hJE2->SetBinContent(i, TMath::Sqrt(dJE1*dJE2*dJE1*dJE2 + dAJE1*dAJE2*dAJE1*dAJE2)/(dJE1+dAJE1));
    } hJE2->SetName("JEErr");
    for(Int_t i = 1; i<=hUE2->GetNbinsX(); i++){ 
      hUE2->SetBinError(i, 0); 
      dUE1 =  hUE1->GetBinContent(i); 
      dUE2 =  hUE2->GetBinContent(i);
      dAUE1 = hAUE1->GetBinContent(i); 
      dAUE2 = hAUE2->GetBinContent(i);
      hUE2->SetBinContent(i, TMath::Sqrt(dUE1*dUE2*dUE1*dUE2 + dAUE1*dAUE2*dAUE1*dAUE2)/(dUE1+dAUE1));
    } hUE2->SetName("UEErr");
  }
  //-----------------------------------
  const auto nI = hIncl1->GetNbinsX();
  const auto nJ = hJE1->GetNbinsX();
  //-----------------------------------
  hIncl1->GetYaxis()->SetRangeUser(YMin, YMax);
  hIncl1->GetXaxis()->SetRangeUser(XMin, XMax);
  //-----------------------------------

  DrawHisto(hIncl1, cLine[0], sMark[0], "same");
  leg->AddEntry(hIncl1, "Incl");
  auto gIncl = (TGraphErrors*)ConvHistogramToGraphErrors(hIncl1, hIncl2, nI); gIncl->SetName("Incl");
  //DrawGraph(gIncl, cLine[0], sMark[0], "P"); 
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
  
  if(sType == "Kshort")tex->DrawLatex(0.15, 0.3, Form("K^{0}_{S}   %s-%s%%", CentMin.Data(), CentMax.Data()));
  if(sType == "Lambda")tex->DrawLatex(0.15, 0.3, Form("#Lambda + #bar{#Lambda}   %s-%s%%", CentMin.Data(), CentMax.Data()));
  if(sType == "Xi" || sType == "Omega")tex->DrawLatex(0.15, 0.3, Form("#%s  %s-%s%%", sType.Data(), CentMin.Data(), CentMax.Data()));
  
  tex->DrawLatex(0.15, 0.2, "|#it{#eta}_{K^{0}_{S}}| < 0.75, #Delta#it{R}(K^{0}_{S}, jet) < 0.4");
  leg->AddEntry(gIncl, "Sys.Error", "f");  
  leg->Draw();
  gStyle->SetOptStat("");
  can->SaveAs(Form("./figure/ThisAna/%s_wSysError_%s%s.eps", sType.Data(), CentMin.Data(), CentMax.Data()));
  //DrawAliLogo(0.65, 0.90, 24, kTRUE);
  CanvasEnd(can);
  return;
}
