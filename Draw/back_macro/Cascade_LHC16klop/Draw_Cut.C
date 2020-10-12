#include "/home/cuipengyao/study/code/Draw/SourceFun.h"

void Draw_Cut(){

  //TString sType[] = {"XiMinus"};//, "XiPlus"};
  //TString sPath[] = {"/home/cuipengyao/study/code/Draw/macro/Cascade_0624/result", "/home/cuipengyao/study/code/Draw/macro/Cascade_0624/result"};
  TString sCut = "XiCosOfPointingAngle";
  TString sPath[] = {"./", "./"};
  TString sFile[] = {"AnalysisResults_RD.root" , "AnalysisResults_RD.root"};
  TString sList[] = {"listCascadeMakerEH", "listCascadeMakerEH"};
  TString sHist[] = {Form("Before_%s", sCut.Data()), Form("After_%s", sCut.Data())};
  TString  sLeg[] = {"Before", "After"};
  //TString sLatex = sCut;
  Double_t   YMin = 1e-2;
  Double_t   YMax = 1.6e5;
  Double_t   XMin = 0.97;
  Double_t   XMax = 1.;
  //-----------------------------------

  TCanvas*  c1 = new TCanvas("c1", "");
  TLegend* leg = new TLegend(0.7, 0.9,0.9,0.7);
    
  //-----------------------------------
  Int_t nHist = sizeof(sHist)/sizeof(TString);
  for (Int_t i = 0; i< nHist; i++){
    TString sMyPath = sPath[i]; 
    TString sMyFile = sFile[i]; 
    TString sMyList = sList[i]; 
    TString sMyHist = sHist[i]; 
    TH1D* h1 = (TH1D*)GetTH1FromFile(sMyPath, sMyFile, sMyList, sMyHist);
    h1->SetName(Form("hist_%d", i)); 
    SetLine(h1,cLine[i],sMark[i]);
    h1->SetMarkerSize(1.3);
    //SetAxis(h1, YMin, YMax, 0.6, 6.);
    SetAxis(h1, YMin, YMax, XMin, XMax, "Count", sCut);
    h1->Draw("same");
    leg->AddEntry(h1,sLeg[i],"lp");
  }

  //TLatex*     tex = new TLatex();
  //tex->SetNDC();
  //tex->SetTextSizePixels(24);
  SetCanv(c1);
  c1->SetLogy();
  SetLegend(leg);
  SetStyle();
  //tex->DrawLatex(0.15, 0.87, sLatex);
  leg->Draw();

  return;
}
