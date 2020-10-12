#include "./SourceFun.h"

void SBRatio(){


  TString Path = "/home/cuipengyao/study/pPb/Xi/CorrectEffi/Local_CompareToLF_LHC17f2a/Local";
  TString File = "AnalysisOutputs_FitCbinRD.root";
  TString List = "listFitCbinRD_XiNeg_Default";
  TString HistS = "hS";
  TString HistB = "hB";
  
  TString sPath[] = {"", ""};
  TString sFile[] = {File,  File};
  TString sList[] = {List, "listFitCbinRD_XiPos_Default"};
  TString sHistS[] = {HistS, HistS};
  TString sHistB[] = {HistB, HistB};
  TString sLeg[] = {"#Xi^{-}", "#bar{#Xi}^{+}"};

  auto sLatex("Signal to background ratio");
  Double_t YMin = 1e-12;
  Double_t YMax = 1e12;
  Double_t XMin = 0.;
  Double_t XMax = 12.;
  //-----------------------------------
  TCanvas *can = nullptr;

  can = MakeCanvas("can");
  //can->SetLogy();
  can->SetGridx(); can->SetGridy();

  auto leg = new TLegend(0.7,0.9,1.0,0.6);    
  //-----------------------------------
  auto nHist = sizeof(sHistS)/sizeof(TString);
  for (Int_t i = 0; i< nHist; i++){
    TString sMyPath = Form("%s_%s", Path.Data(), sPath[i].Data()); 
    TString sMyFile = sFile[i]; 
    TString sMyList = sList[i]; 
    TString sMyHistS = sHistS[i]; 
    TString sMyHistB = sHistB[i]; 
    TH1D* h1 = (TH1D*)GetTH1D(sMyPath.Data(), sMyFile.Data(), sMyList.Data(), sMyHistS.Data());
    h1->SetName(Form("hists_%d", i)); 
    TH1D* h2 = (TH1D*)GetTH1D(sMyPath.Data(), sMyFile.Data(), sMyList.Data(), sMyHistB.Data());
    h2->SetName(Form("histb_%d", i)); 
    h1->Divide(h2);
    //SetFrame(h1, "#it{p}_{T}", "1/2#pi 1/#it{p}_{T} 1/#it{N}_{ev}d^{2}#it{N}/(d#it{p}_{T}d#it{y})(GeV/#it{c})^{-2}");
    SetFrame(h1, "#it{p}_{T} (GeV/#it{c})", "Sig/Bkg");
    DrawHisto(h1, cLine[i], sMark[i], "same");
    leg->AddEntry(h1,sLeg[i],"lp");
  }

  TLatex*     tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  SetLegend(leg);
  //tex->DrawLatex(0.16, 0.91, sLatex);
  //tex->DrawLatex(0.5, 0.91, "V0A multiplicity event classes");
  //tex->DrawLatex(0.16, 0.3, "-0.5 < #it{y}_{CMS} < 0");
  //tex->DrawLatex(0.16, 0.2, "p-Pb #sqrt{#it{s}_{NN}} = 5.02 TeV");
  leg->Draw();
  gStyle->SetOptStat("");

  CanvasEnd(can);
  return;
}
