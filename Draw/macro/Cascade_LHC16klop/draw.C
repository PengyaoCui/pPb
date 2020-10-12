#include "../../SourceFun.h"

void draw(){
  TString Path = "/home/cuipengyao/study/code/Draw/macro/Cascade_LHC16klop/result";
  TString File = "FitXiPtSpect.root";

  TString sPath[] = {Path};
  TString sFile[] = {File};
  TString sHist[] = {"PC_Xi"};
  TString  sLeg[] = {""};
  TString sLatex = "UE #Xi^{#pm}";
  Double_t   YMin = 1e-6;
  Double_t   YMax = 1e-2;
  //-----------------------------------

  TCanvas*  c1 = new TCanvas("c1", "");
  TLegend* leg = new TLegend(0.7,0.9,1.0,0.6);
    
  //-----------------------------------
  Int_t nHist = sizeof(sHist)/sizeof(TString);
  for (Int_t i = 0; i< nHist; i++){
    TString sMyPath = sPath[i]; 
    TString sMyFile = sFile[i]; 
    //TString sMyList = sList[i]; 
    TString sMyHist = sHist[i]; 
    TH1D* h1 = (TH1D*)GetTH1FromFile(sMyPath, sMyFile, sMyHist);
    h1->SetName(Form("hist_%d", i)); 
    SetLine(h1,cLine[i],sMark[i]);
    h1->SetMarkerSize(1.3);
    //SetAxis(h1, YMin, YMax, 0.6, 6.);
    SetAxis(h1, YMin, YMax, 0.6, 14., "d#rho/d#it{p}_{T}");
    h1->Draw("same");
    leg->AddEntry(h1,sLeg[i],"lp");
  }

  //TH1D* h2 = (TH1D*)GetTH1FromFile("/home/cuipengyao/study/code/Cascade_LHC15f_pass2/Inclusive_0625", "AnalysisOutputs_EffInclMC.root", "listEffInclMC_XiPlus_Default", "hPtKine");
  //NormBinSize(h2);
  //SetLine(h2,cLine[3],sMark[3]);
  //h2->SetMarkerSize(1.3);
  //h2->Draw("same");
  //leg->AddEntry(h2,"MC Gen","lp");

  TLatex*     tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  SetCanv(c1);
  //c1->SetLogy();
  SetLegend(leg);
  SetStyle();
  tex->DrawLatex(0.17, 0.91, "ALICE p-p #sqrt{s} = 13 TeV");
  tex->DrawLatex(0.17, 0.84, sLatex);
  //leg->Draw();

  return;
}
