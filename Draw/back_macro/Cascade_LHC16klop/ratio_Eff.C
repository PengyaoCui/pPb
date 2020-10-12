#include "../../SourceFun.h"

void ratio_Eff(){
 
  //Bool_t IsSave(0);

  TString sFile = "./result/ratio.root";
  TString HistNeg = "XiNeg";

  //Numerator information
  TString sNuPath = "/home/cuipengyao/study/code/cascade_LHC15f_pass2_test/Inclusive_correctMC";
  TString sNuFile = "AnalysisOutputs_EffInclMC.root";
  TString sNuList = "listEffInclMC_XiMinus_Default";
  TString sNuHist = "hPtEffi";
  //TString sNuPath = "/home/cuipengyao/study/code/Cascade_LHC15f_pass2/JC_test_everycut";
  //TString sNuList = "listEffInclMC_XiPlus_Default";

  //Denominator information
  TString sDePath = "/home/cuipengyao/study/code/Draw/macro/Cascade_NoJet_0907/result/D_Colella";
  TString sDeFile = "correctedspectrumfittedgfcorrphyseff.root";
  TString sDeHist = "fittedgfefficiencyvspt_0";
  //TString sDePath = "/home/cuipengyao/study/code/Draw/macro/Cascade_NoJet_0907/result";
  //TString sDeFile = "PtSpect_0910_wo_Norm_EffCorr.root";
  //TString sDeHist = "hPtMC_XiPlus";

  TString sLatex = "#Xi^{-} efficiency distribution";
  //TString sLatex = "Raw inclusive #Xi^{-} result to LF";
  Double_t   YMin = 0.;
  Double_t   YMax = 0.6;
  //-----------------------------------

  //if (IsSave) TFile *file = TFile::Open(sFile, "UPDATE");

  TCanvas * c2 = new TCanvas("c2","");
  //c2->SetFillColor(0);
  SetStyle();
  //SetCanv(c2);

  c2->cd();
  TPad *c2_a = new TPad("c2_a", "c2_a", 0., 0.4, 0.9, 1.);
  c2_a->SetRightMargin(0.01);
  c2_a->SetBorderMode(0);
  c2_a->SetBorderSize(2);

  c2_a->SetBottomMargin(0.0);
  c2_a->SetFrameBorderMode(0);
  c2_a->SetFrameBorderMode(0);
  c2_a->Draw();
  c2_a->cd();

  TLegend* leg = new TLegend(0.7,0.3,0.8,0.2);
    
  //-----------------------------------
  if(sNuPath.IsNull() || sNuFile.IsNull() || sNuHist.IsNull()) { cout<<"Don't have numerator information"<<endl;   return 0x0;}
  if(sDePath.IsNull() || sDeFile.IsNull() || sDeHist.IsNull()) { cout<<"Don't have denominator information"<<endl; return 0x0;}
  //-----------------------------------


  TH1D* hNumerator = (TH1D*)GetTH1FromFile(sNuPath, sNuFile, sNuList, sNuHist);
  TH1D* hDenominator = (TH1D*)GetTH1FromFile(sDePath, sDeFile, sDeHist);
  TH1D* hNumerator = RebinTH1D (hNumerator, hDenominator);
  hNumerator->SetName("hNumerator");
  hDenominator->SetName("hDenominator");
  SetLine(hNumerator,cLine[0], sMark[0]);
  SetAxis(hNumerator, YMin, YMax, 0.6, 6., "Efficiency");
  hNumerator->Draw("same");

  SetLine(hDenominator,cLine[1], sMark[1]);
  hDenominator->Draw("same");
  SetAxis(hDenominator, YMin, YMax, 0.6, 6., "dN/d#it{p}_{T}");
  leg->AddEntry(hNumerator,"This analysis","lp");
  leg->AddEntry(hDenominator,"D.Colella ","lp");
  //leg->AddEntry(hNumerator,"#Xi^{-}","lp");
  //leg->AddEntry(hDenominator,"#bar{#Xi}^{+}","lp");
  SetLegend(leg);
  leg->Draw();

  TLatex*     tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.2, 0.8, sLatex);

  //c2->Update();

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

  TH1D* Numerator = (TH1D*)hNumerator->Clone("Numerator");;
  Numerator->SetName("Numerator");
  TH1D* Denominator = (TH1D*)hDenominator->Clone("Denominator");
  Denominator->SetName("Denominator");
  Numerator->Divide(Denominator);
  TH1D* hRatio = (TH1D*)Numerator;
  hRatio->SetName("Ratio");
  SetLine(hRatio,kBlack, 20);
  SetAxis(hRatio, 0.1, 2.2, 0.6, 6., "Ratio");

  hRatio->GetXaxis()->SetTitleSize(0.13);
  hRatio->GetXaxis()->SetLabelSize(0.14);
  hRatio->GetXaxis()->SetTitleOffset(0.6);

  hRatio->GetYaxis()->SetTitleSize(0.13);
  hRatio->GetYaxis()->SetLabelSize(0.13);
  hRatio->GetYaxis()->SetTitleOffset(0.4);

  hRatio->Draw("same");
  TLine* l = new TLine(0.6, 1, 6., 1);
  l->SetLineColor(kRed);
  l->SetLineWidth(2);
  l->Draw("same");

  //c2->cd();
  //c2->Draw();


  //if(IsSave) {file->cd(); hRatio->Write(HistNeg, TObject::kSingleKey);}

  //if(IsSave) { file->Close();}

  return;
}
