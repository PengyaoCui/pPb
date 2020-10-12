#include "../../SourceFun.h"

void Draw(){

  TString sCuts = "V0CPA";
  //TString Path = "";
  TString File = "AnalysisOutputs_EffInclMC.root";
  TString List = "listEffInclMC_Xi_Default";
  TString Hist = "hPtEffi";

  TString sPath[] = {"/home/cuipengyao/study/code/Cascade_LHC16klop_total/Local"};
  TString sFile[] = {File};
  TString sList[] = {List};
  TString sHist[] = {Hist};

  TString  sLeg[] = {""};

  //TString sPath[] = {"/home/cuipengyao/study/code/Cascade_LHC16k/JC_CombineXi_CorrNormFact", "/home/cuipengyao/study/code/Cascade_LHC16h/JC_CombineXi_CorrNormFact", "/home/cuipengyao/study/code/Cascade_LHC16l/JC_CombineXi_CorrNormFact"};
  ////TString sFile[] = {"AnalysisOutputs_EffInclMC.root", "AnalysisOutputs_EffInclMC.root", "AnalysisOutputs_EffInclMC.root"};
  //TString sFile[] = {"AnalysisOutputs_EffCorrJE.root", "AnalysisOutputs_EffCorrJE.root", "AnalysisOutputs_EffCorrJE.root"};
  //TString sList[] = {"listEffCorrJE_Xi_Default_PtJ22_NJ", "listEffCorrJE_Xi_Default_PtJ22_NJ", "listEffCorrJE_Xi_Default_PtJ22_NJ"};
  //TString sHist[] = {"hPtEffi", "hPtEffi", "hPtEffi"};

  TString sLatex = "Inclusive #Xi efficiency";
  Double_t   YMin = 0.;
  Double_t   YMax = 1.;
  Double_t   XMin = 0.6;
  Double_t   XMax = 6.5;
  //-----------------------------------

  TCanvas*  c1 = new TCanvas("c1", "");
  TLegend* leg = new TLegend(0.7,0.9,1.0,0.6);    
  //-----------------------------------
  Int_t nHist = sizeof(sHist)/sizeof(TString);
  for (Int_t i = 0; i< nHist; i++){
    TString sMyPath = sPath[i]; 
    TString sMyFile = sFile[i]; 
    TString sMyList = sList[i]; 
    TString sMyHist = sHist[i]; 
    TH1D* h1 = (TH1D*)GetTH1FromFile(sMyPath, sMyFile, sMyList, sMyHist);
    //cout<<h1->GetBinContent(1)<<endl;
    h1->SetName(Form("hist_%d", i)); 
    SetLine(h1,cLine[i],sMark[i]);
    h1->SetMarkerSize(1.3);
    SetAxis(h1, YMin, YMax, XMin, XMax);
    h1->GetYaxis()->SetTitle("Efficiency");

    h1->GetXaxis()->SetTitleSize(0.06);
    h1->GetYaxis()->SetTitleSize(0.06);

    h1->GetXaxis()->SetTitleOffset(1.);
    h1->GetYaxis()->SetTitleOffset(1.);

    h1->GetXaxis()->SetLabelSize(0.05);
    h1->GetYaxis()->SetLabelSize(0.05);
    h1->Draw("same");
    leg->AddEntry(h1,sLeg[i],"lp");
  }

  TLatex*     tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  SetCanv(c1);
  //c1->SetLogy();
  SetLegend(leg);
  SetStyle();
  tex->DrawLatex(0.16, 0.91, sLatex);
  //leg->Draw();

  return;
}
