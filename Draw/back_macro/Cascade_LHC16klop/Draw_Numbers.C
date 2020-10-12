#include "/home/cuipengyao/study/code/Draw/SourceFun.h"

void Draw_Numbers(){

  TString sPath[] = {"/home/cuipengyao/study/code/Draw/macro/Cascade_LHC16klop/AnalysisResults"};//, "/home/cuipengyao/study/code/Cascade_LHC15f_pass2/Inclusive_0625"};
  TString sFile[] = {"AnalysisResults_LHC17j5d.root"};// , "AnalysisOutputs_EffInclMC.root"};
  TString sList[] = {"listCascadeMakerEH"};//, "listEffInclMC_XiPlus_Default"};
  TString sHist[] = {"hEventNumbers"};//, "hPtEffi"};
  TString  sLeg[] = {""}//, "#Xi^{+}"};
  TString sLatex = "LHC17j5d";
  Double_t   YMin = 0.;
  Double_t   YMax = 1e9;
  //-----------------------------------

  TCanvas*  c1 = new TCanvas("c1", "");
  //TLegend* leg = new TLegend(0.3,0.3,0.5,0.2);
    
  //-----------------------------------
  Int_t nHist = sizeof(sHist)/sizeof(TString);
  for (Int_t i = 0; i< nHist; i++){
    TString sMyPath = sPath[i]; 
    TString sMyFile = sFile[i]; 
    TString sMyList = sList[i]; 
    TString sMyHist = sHist[i]; 
    TH1D* h1 = (TH1D*)GetTH1FromFile(sMyPath, sMyFile, sMyList, sMyHist);
    h1->SetName(Form("hist_%d", i)); 
    //SetLine(h1,cLine[i],sMark[i]);
    h1->SetMarkerSize(1.3);
    //SetAxis(h1, YMin, YMax, 0.6, 6.);
    SetAxis(h1, YMin, YMax, 0., 7.1, "Events", "Cuts");
    h1->SetFillColor(38);
    h1->Draw("HIST TEXT00");
    //h1->Draw("same");
    //leg->AddEntry(h1,sLeg[i],"lp");
  }

  TLatex*     tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  SetCanv(c1);
  //c1->SetLogy();
  //SetLegend(leg);
  SetStyle();
  tex->DrawLatex(0.15, 0.87, sLatex);
  //leg->Draw();

  return;
}
