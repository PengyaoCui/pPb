#include "../../SourceFun.h"

void Times(){
  Bool_t IsSave(1);
  TString HistName = "LF_wo_Norm";
  //Numerator information
  TString sNuPath = "/home/cuipengyao/study/code/Draw/macro/Cascade/result/D_Colella";
  TString sNuFile = "correctedspectrumfittedgfcorrphyseff.root";
  TString sNuHist = "hptraw_0";

  //Denominator information
  TString sDePath = "/home/cuipengyao/study/code/Draw/macro/Cascade/result/D_Colella";
  TString sDeFile = "correctedspectrumfittedgfcorrphyseff.root";
  TString sDeHist = "fittedgfefficiencyvspt_0";

  TString sLatex = "Inclusive result to LF ratio";
  Double_t   YMin = 0.;
  Double_t   YMax = 1e5;
  //-----------------------------------
  if (IsSave) TFile *file = TFile::Open("./result/LF_wo_Norm.root", "UPDATE");
  //-----------------------------------

  TCanvas*  c1 = new TCanvas("c1", "");
  TLegend* leg = new TLegend(0.7,0.3,0.8,0.2);
    
  //-----------------------------------
  if(sNuPath.IsNull() || sNuFile.IsNull() || sNuHist.IsNull()) { cout<<"Don't have numerator information"<<endl;   return 0x0;}
  if(sDePath.IsNull() || sDeFile.IsNull() || sDeHist.IsNull()) { cout<<"Don't have denominator information"<<endl; return 0x0;}
  //-----------------------------------
  TH1D* hNumerator = (TH1D*)GetTH1FromFile(sNuPath, sNuFile, sNuHist);
  TH1D* hDenominator = (TH1D*)GetTH1FromFile(sDePath, sDeFile, sDeHist);
  TH1D* hTimes = (TH1D*)TimesTH1D(hNumerator, hDenominator);
  //SetLine(hTimes,kBlack, 20);
  //SetAxis(hTimes, YMin, YMax, 0.6, 6., "Ratio");
  hTimes->Draw("same");
  if(IsSave) {file->cd(); hTimes->Write(HistName, TObject::kSingleKey);}
  leg->AddEntry(hTimes,"#Xi^{-}","lp");

  TLatex*     tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  SetCanv(c1);
  SetLegend(leg);
  SetStyle();
  tex->DrawLatex(0.16, 0.91, sLatex);
  leg->Draw();
 
  if(IsSave) { file->Close();}

  return;
}
