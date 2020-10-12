#include "/home/cuipengyao/study/code/Draw/SourceFun.h"

void Draw_2D(){

  //TString sType[] = {"XiMinus"};//, "XiPlus"};
  //TString sPath[] = {"/home/cuipengyao/study/code/Draw/macro/Cascade_0624/result", "/home/cuipengyao/study/code/Draw/macro/Cascade_0624/result"};
  TString sPath[] = {"/home/cuipengyao/study/code/V0_LHC16k/JC_Eta"};
  TString sFile[] = {"AnalysisOutputs_LoopIncMC.root"};
  TString sList[] = {"listLoopIncMC_Lambda_Default"};
  TString sHist[] = {"hPtGenLaXi"};
  //TString  sLeg[] = {"#Xi^{-}", "#Xi^{+}"};
  TString sLatex = "MC generate #Xi #it{p}_{T} Vs #Lambda #it{p}_{T} distribution";
  Double_t   YMin = 0.6;
  Double_t   YMax = 14.;
  //-----------------------------------
  MakeCanvas("c1");
  //TLegend* leg = new TLegend(0.3,0.3,0.5,0.2);
    
  //-----------------------------------
  Int_t nHist = sizeof(sHist)/sizeof(TString);
  for (Int_t i = 0; i< nHist; i++){
    TString sMyPath = sPath[i]; 
    TString sMyFile = sFile[i]; 
    TString sMyList = sList[i]; 
    TString sMyHist = sHist[i]; 
    TH2D* h1 = (TH2D*)GetTH2FromList(sMyPath, sMyFile, sMyList, sMyHist);
    h1->SetName(Form("hist_%d", i)); 
    //SetLine(h1,cLine[i],sMark[i]);
    //h1->SetMarkerSize(1.3);
    //SetAxis(h1, YMin, YMax, 0.6, 6.);
    SetAxis(h1, YMin, YMax, 0.6, 14., "#it{p}_{T, #Xi}(GeV/#it{c})", "#it{p}_{T, #Lambda}(GeV/#it{c})" );
    h1->Draw("same colz");
    //h1->Draw("same");
    //leg->AddEntry(h1,sLeg[i],"lp");
  }

  TLatex*     tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  //SetCanv(c1);
  //c1->SetLogy();
  //SetLegend(leg);
  SetStyle();
  tex->DrawLatex(0.16, 0.95, sLatex);
  //leg->Draw();

  return;
}
TCanvas* MakeCanvas(TString sName)
{
  TCanvas *c = new TCanvas(Form("c%s",sName.Data()), sName.Data(), 700, 500);
  c->Range(0., 0., 1., 1.);
  c->SetFillColor(0);
  c->SetBorderMode(0);
  c->SetBorderSize(0);
  c->SetRightMargin(0.1);
  c->SetLeftMargin(0.13);
  c->SetTopMargin(0.1);
  c->SetBottomMargin(0.15);
  c->SetFrameFillStyle(0);
  c->SetFrameBorderMode(0);

  return c;
}

