#include "./inc/SourceFun.h"

void DrawUEUncer(const TString sType = "Lambda", const TString CentMin = "0", const TString CentMax = "100"){
  
  auto sPath = "./result"; 
  auto sCFile = "CentVal.root";
 
  auto sCJEList = "listJE"; 
  auto sCJetHist = Form("h%s_%s%s", sType.Data(), CentMin.Data(), CentMax.Data());

  auto sEUEFile = "UEUncer.root";
  auto sEUEList = Form("%s_UESub_%s%s_OCNJ", sType.Data(), CentMin.Data(), CentMax.Data());
  auto sEUEListOC = Form("%s_UESub_%s%s_OC", sType.Data(), CentMin.Data(), CentMax.Data());
  auto sEUEListFitOC = Form("%s_UESub_%s%s_wFitOC", sType.Data(), CentMin.Data(), CentMax.Data());

  auto sLatex(Form("p-Pb #sqrt{#it{s}_{NN}} = 5.02 TeV"));
  Double_t XMin = 0.6;
  Double_t XMax = 5.;
  
  //-----------------------------------
  TCanvas *can = nullptr;
  TLatex* tex = nullptr;
  TLegend *leg = nullptr;
  
  //const auto dMaterial = 0.04; 
  //-----------------------------------
  
  auto hJE1  = (TH1D*)GetTH1D(sPath, sCFile, sCJEList, sCJetHist); hJE1->SetName("JECen");
  auto hUE2 = (TH1D*)GetTH1D(sPath, sEUEFile, sEUEList, "hMax"); hUE2->SetName("UEErrAbs");
  auto hUE2OC = (TH1D*)GetTH1D(sPath, sEUEFile, sEUEListOC, "hMax"); hUE2OC->SetName("UEErrAbsOC");
  auto hUE2FitOC = (TH1D*)GetTH1D(sPath, sEUEFile, sEUEListFitOC, "hMax"); hUE2FitOC->SetName("UEErrAbsFitOC");
  
  auto hJErrContU = (TH1D*)hJE1->Clone("hJErrContU"); hJErrContU->Reset();//UE substruction Uncertainty contribution to JE spectrum 
  auto hJErrContUOC = (TH1D*)hJE1->Clone("hJErrContUOC"); hJErrContUOC->Reset();//UE substruction Uncertainty contribution to JE spectrum 
  auto hJErrContUFitOC = (TH1D*)hJE1->Clone("hJErrContUFitOC"); hJErrContUFitOC->Reset();//UE substruction Uncertainty contribution to JE spectrum 

 
  //-----------------------------------
  const auto nJ = hJE1->GetNbinsX();
  
  for(Int_t i = 1; i<=nJ; i++){
    auto CJE = hJE1->GetBinContent(i);
    auto EUE = hUE2->GetBinContent(i);
    auto EUEOC = hUE2OC->GetBinContent(i);
    auto EUEFitOC = hUE2FitOC->GetBinContent(i);
    hJErrContU->SetBinContent(i, EUE/CJE);//
    hJErrContUOC->SetBinContent(i, EUEOC/CJE);//
    hJErrContUFitOC->SetBinContent(i, EUEFitOC/CJE);//
  }
  
  can = MakeCanvas("can");
  leg = new TLegend(0.65,0.9,1.0,0.6); SetLegend(leg);
  hJErrContU->GetYaxis()->SetTitle("Relative systematic error");
  hJErrContU->GetXaxis()->SetTitle("#it{p}_{T}");
  hJErrContU->GetYaxis()->SetRangeUser(0, 1.);
  DrawHisto(hJErrContU, cLine[0], sMark[0], "same");leg->AddEntry(hJErrContU, "Old","l");
  DrawHisto(hJErrContUOC, cLine[1], sMark[1], "same");leg->AddEntry(hJErrContUOC, "OC08","l");
  DrawHisto(hJErrContUFitOC, cLine[2], sMark[2], "same");leg->AddEntry(hJErrContUFitOC, "Fit OC","l");
 
  //-----------------------------------
  tex =  new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.15, 0.9, sLatex);
  tex->DrawLatex(0.15, 0.8, Form("%s %s-%s%%", sType.Data(), CentMin.Data(), CentMax.Data()));
  leg->Draw();
  gStyle->SetOptStat("");
  can->SaveAs(Form("./figure/%s_JCUncert_%s%s_UEStudy_3.pdf", sType.Data(), CentMin.Data(), CentMax.Data()));
  can->SaveAs(Form("./figure/%s_JCUncert_%s%s_UEStudy_3.eps", sType.Data(), CentMin.Data(), CentMax.Data()));
  //DrawAliLogo(0.65, 0.90, 24, kTRUE);
  CanvasEnd(can);
  return;
}
