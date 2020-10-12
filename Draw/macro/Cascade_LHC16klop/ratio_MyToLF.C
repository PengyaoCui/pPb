#include "../../SourceFun.h"

void ratio_MyToLF(){
  

  TString sNuPath = ".";
  TString sNuFile = "AnalysisResults_MCTrkEta.root";
  TString sNuList = "listCascadeMakerEH";
  //TString sNuList = "listCascadeMakerMC";
  TString sDePath = ".";
  TString sDeFile = "AnalysisResults_LF.root";
  sDeFile = Form("%s/%s",sDePath.Data(),sDeFile.Data());

  TString sDeHist1D = "";
  TString sDeHist2D = "fHistVarDcaV0DaughtersXiPlus";
  TString sNuHist = "PosdcaV0DaughtersXi";

  TString sPara = sDeHist2D; 

  ////Numerator information
  //TString sNuPath = ".";
  //TString sNuFile = "AnalysisResults_MCTrkEta.root";
  //TString sNuList = "listCascadeMakerEH";
  //TString sNuHist = "NegV0Radius";

  ////Denominator information
  //TString sDePath = ".";
  //TString sDeFile = "AnalysisResults.root";
  //sDeFile = Form("%s/%s",sDePath.Data(),sDeFile.Data());
  //TString sDeHist1D = "fHistVarV0RadiusXiMinus";
  //TString sDeHist2D = "fHistVarV0RadiusXiMinus";
  //TString sDeHist = "hPtIncl_XiPlus";
  //TString sPara = "V0Radius"; 

  TString sLatex = sPara;
  Double_t YMin = 1e-1;
  Double_t YMax = 1e5;
  Double_t XMin = 0.; 
  Double_t XMax = 100.; 
  //-----------------------------------
  TCanvas * c2 = new TCanvas("c2","");
  SetStyle();
  c2->cd();

  //-----------------------------------
  TPad *c2_a = new TPad("c2_a", "c2_a", 0., 0.4, 0.9, 1.);
  c2_a->SetRightMargin(0.01);
  c2_a->SetBorderMode(0);
  c2_a->SetBorderSize(2);
  c2_a->SetBottomMargin(0.0);
  c2_a->SetFrameBorderMode(0);
  c2_a->SetFrameBorderMode(0);
  c2_a->Draw();
  c2_a->cd();
  c2_a->SetLogy();
  TLegend* leg = new TLegend(0.7,0.3,0.9,0.1);

  TH1D* hNumerator = (TH1D*)GetTH1FromFile(sNuPath, sNuFile, sNuList, sNuHist);
  hNumerator->SetName("hNumerator");
  //hNumerator->GetMinimumAndMaximum(XMin,XMax);
  Int_t n = hNumerator->GetNbinsX();
  XMin = hNumerator->GetXaxis()->GetBinLowEdge(0);
  XMax = hNumerator->GetXaxis()->GetBinUpEdge(n);
  //hNumerator->GetNbinsX();
  //TH1D* hDenominator = (TH1D*)GetTH1FromFile(sDePath, sDeFile, sDeHist);
  TFile* File = TFile::Open(sDeFile,"read"); if (!File->IsOpen()) return 0x0;
  TDirectoryFile* Dir = File->Get("PWGLFStrangeness.outputCheckCascade");
  TList *List = Dir->Get("fListHistMultistrangeQA");
  if (!(sDeHist1D.IsNull())){
    TH1D *hDenominator = List->FindObject(sDeHist1D);
  }
  if (!(sDeHist2D.IsNull())){
    TH2D *Hist2 = List->FindObject(sDeHist2D);
    TH1D* hDenominator = Hist2->ProjectionY();
  }
  hDenominator->SetName("hDenominator");

  //TH1D* hNumerator = RebinTH1D (hNumerator, hDenominator);
  SetLine(hNumerator,cLine[0], sMark[0]);
  SetAxis(hNumerator, YMin, YMax, XMin, XMax, "Counts", sPara);
  hNumerator->Draw("same");
  SetLine(hDenominator,cLine[1], sMark[1]);
  hDenominator->Draw("same");
  SetAxis(hDenominator, YMin, YMax, XMin, XMax, "Counts", sPara);
  leg->AddEntry(hNumerator,"My","lp");
  leg->AddEntry(hDenominator,"LF","lp");

  SetLegend(leg);
  leg->Draw();
  TLatex*     tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.16, 0.91, sLatex);
  //-----------------------------------

  c2->cd();
  TPad *c2_b = new TPad("c2_b", "c2_b", 0., 0.1 , 0.9, 0.40);
  c2_b->SetTopMargin(0.);
  c2_b->SetRightMargin(0.01);
  c2_b->SetBottomMargin(0.2);
  c2_b->SetFillColor(0);
  c2_b->SetBorderMode(0);
  c2_b->SetBorderSize(2);
  c2_b->SetFrameBorderMode(0);
  c2_b->SetFrameBorderMode(0);
  c2_b->Draw();
  c2_b->cd();

  TH1D* Numerator = (TH1D*)hNumerator->Clone("Numerator");//GetTH1FromFile(sNuPath, sNuFile, sNuHist);
  TH1D* Denominator = (TH1D*)hDenominator->Clone("Denominator");
  TH1D* Numerator = RebinTH1D (Numerator, Denominator);
  Numerator->SetName("Numerator");
  Denominator->SetName("Denominator");
  TH1D* hRatio = (TH1D*)RatioTH1D(Numerator,Denominator);
  hRatio->SetName("Ratio");
  //hRatio->SetBinErrorOption(0);
  SetLine(hRatio,kBlack, 20);
  SetAxis(hRatio, 0.7, 1.3, XMin, XMax, "Ratio", sPara);

  hRatio->GetXaxis()->SetTitleSize(0.13);
  hRatio->GetXaxis()->SetLabelSize(0.14);
  hRatio->GetXaxis()->SetTitleOffset(0.7);

  hRatio->GetYaxis()->SetTitleSize(0.13);
  hRatio->GetYaxis()->SetLabelSize(0.13);
  hRatio->GetYaxis()->SetTitleOffset(0.4);

  hRatio->Draw("same");
  TLine* l = new TLine(XMin, 1, XMax, 1);
  l->SetLineColor(kRed);
  l->SetLineWidth(2);
  l->Draw("same");

  //TF1 *f1 = (TF1*);
  //f1->Draw("same");
  return;
}
