#include "./SourceFun.h"

void JetPt(){
 
  //Numerator information
  TString sNuPath = "/home/cuipengyao/study/code/Cascade_LHC16k/JC_AddJetPt";
  TString sNuFile = "AnalysisOutputs_LoopJetRD.root";
  TString sNuList = "listLoopJetRD_Xi_Default_PtJ22_JC";
  TString sNuHist = "hJetPtAfter";

  TString xAxis = "#it{p}_{T, Leading}";
  TString sLatex = Form("Jet spectrum");
  Double_t   YMin = 1e-6;
  Double_t   YMax = 1e7;
  Double_t   XMin = 10.;
  Double_t   XMax = 100.;
  //-----------------------------------


  TCanvas * c2 = new TCanvas("c2","");
  SetStyle();
  SetCanv(c2);
  Double_t dBin[] = {10., 11., 12., 13., 14., 15., 16., 17., 18., 19., 20., 21., 22., 23., 24., 25., 26., 27., 28., 29., 30., 31., 32., 33., 34., 35., 36., 37., 38., 39., 40., 42., 44., 46., 48., 50., 53., 56., 60., 64., 68., 73., 78., 84., 90., 100. };
  const Int_t nBin = sizeof(dBin) / sizeof(Double_t)-1;

  TH1D *hRebin = new TH1D("hRebin", "", nBin, dBin);
  TH1D* hNumerator   = (TH1D*)GetTH1FromFile(sNuPath,  sNuFile, sNuList, sNuHist);
  hNumerator->SetName("hNumerator");
  //hNumerator->Rebin(10);
  //hNumerator->Scale(1./(hNumerator->GetEntries()));
  //for(Int_t i = 1; i<hNumerator->GetNbinsX(); ++i) { hNumerator->SetBinError(i, TMath::Sqrt(hNumerator->GetBinContent(i)));} 
  hNumerator->Scale(1./(2.49632*1e8));
  hNumerator = (TH1D*)RebinTH1D(hNumerator, hRebin);
  hNumerator->SetName("hNumerator");
  NormBinSize(hNumerator);
  SetLine(hNumerator,cLine[0], sMark[0]);
  SetAxis(hNumerator, YMin, YMax, XMin, XMax, "#frac{1}{N_{event}}#frac{dN}{d#it{p}_{T}}");
  hNumerator->Draw("same");


  TLatex*     tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.16, 0.9, sLatex);
  tex->DrawLatex(0.16, 0.8, "LHC16k");

  return;
}
