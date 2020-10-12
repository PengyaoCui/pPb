#include "SourceFun.h"

//_________________________________________________________________________________________________
void StoBRatio(){
  //TString sType[] = {"XiPlus", "XiMinus"};
  TString sType[] = {"Xi"};

  TString sRootFilePath = "/home/cuipengyao/study/code/Cascade_LHC16klop_total/Local";


  TString sRootFileName = "AnalysisOutputs_FitCbinRD.root";
  TString      sObjectS = "hS";
  TString      sObjectB = "hB";
//===================================================================
  Double_t YMin = 0;
  Double_t YMax = 200;
  Double_t XMin = 0.6;
  Double_t XMax = 6.5;
//-------------------------------------------------------------------
  TCanvas*  c1 = new TCanvas("c1", "");
  TLegend* leg = new TLegend(0.75,0.75,0.95,0.95);

  const Int_t nType  = sizeof(sType)/sizeof(TString);

//===================================================================
  for(Int_t i=0; i<nType; i++) {
    TString sOpt = sType[i];

    TString    sListName = Form("listFitCbinRD_%s_Default;1", sOpt.Data());

    TH1D* hSig = (TH1D*)GetHistFromList(sRootFilePath, sRootFileName, sListName, sObjectS);
    hSig->SetName("Sigal");
    TH1D* hBkg = (TH1D*)GetHistFromList(sRootFilePath, sRootFileName, sListName, sObjectB);
    hBkg->SetName("Background");
    hSig->Divide(hBkg);

    SetLine(hSig,cLine[i],sMark[i]);
    SetAxis(hSig, YMin, YMax, XMin, XMax,"S/B");
    hSig->Draw("same");
    if (sOpt == "XiPlus")  leg->AddEntry(hSig,"#bar{#Xi}^{+}","lp");
    if (sOpt == "XiMinus") leg->AddEntry(hSig,"#Xi^{-}","lp");
  }
  TLatex*     tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  SetCanv(c1);
  SetLegend(leg);
  SetStyle();
  tex->DrawLatex(0.16, 0.91, "#Xi^{#pm} signal to background ratio");
  leg->Draw();
}

