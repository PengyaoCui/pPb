#include "../../SourceFun.h"

void ratio_list(){
 
  //Bool_t IsSave(0);

  TString sFile = "./result/ratio.root";
  TString HistNeg = "XiNeg";

  //Numerator information
  TString sNuPath = "/home/cuipengyao/study/code/Cascade_LHC16h/JC_CombineXi_CorrNormFact";
  TString sNuFile = "AnalysisOutputs_EffCorrJE.root";
  TString sNuList = "listEffCorrJE_Xi_Default_PtJ22_JC";
  TString sNuHist = "hPtEffi";

  TString sNuPath0 = "/home/cuipengyao/study/code/Cascade_LHC16l/JC_CombineXi_CorrNormFact";
  TString sNuFile0 = "AnalysisOutputs_EffCorrJE.root";
  TString sNuList0 = "listEffCorrJE_Xi_Default_PtJ22_JC";
  TString sNuHist0 = "hPtEffi";

  //Denominator information
  TString sDePath = "/home/cuipengyao/study/code/Cascade_LHC16k/JC_CombineXi_CorrNormFact"; 
  TString sDeFile = "AnalysisOutputs_EffCorrJE.root"; 
  TString sDeList = "listEffCorrJE_Xi_Default_PtJ22_JC";
  TString sDeHist = "hPtEffi";                         

  TString sLatex = "JC #Xi^{#pm} Efficiency distribution";
  //TString sLatex = "Raw inclusive #Xi^{-} result to LF";
  Double_t   YMin = 0.;
  Double_t   YMax = 1.;
  //-----------------------------------

  //if (IsSave) TFile *file = TFile::Open(sFile, "UPDATE");

  TCanvas * c2 = new TCanvas("c2","");
  //c2->SetFillColor(0);
  SetStyle();
  //SetCanv(c2);

  c2->cd();
  TPad *c2_a = new TPad("c2_a", "c2_a", 0., 0.35, 1., 1.);

  c2_a->SetFillColor(0);
  c2_a->SetBorderMode(0);
  c2_a->SetBorderSize(0);
  c2_a->SetRightMargin(0.03);
  c2_a->SetLeftMargin(0.13);
  c2_a->SetTopMargin(0.02);
  c2_a->SetBottomMargin(0.0);
  c2_a->SetFrameFillStyle(0);
  c2_a->SetFrameBorderMode(0);


  //TPad *c2_a = new TPad("c2_a", "c2_a", 0., 0.4, 0.9, 1.);
  //c2_a->SetRightMargin(0.01);
  //c2_a->SetBorderMode(0);
  //c2_a->SetBorderSize(2);

  //c2_a->SetBottomMargin(0.0);
  //c2_a->SetFrameBorderMode(0);
  //c2_a->SetFrameBorderMode(0);
  c2_a->Draw();
  c2_a->cd();

  TLegend* leg = new TLegend(0.8,0.9,1.0,0.5);
    
  //-----------------------------------
  if(sNuPath.IsNull() || sNuFile.IsNull() || sNuHist.IsNull()) { cout<<"Don't have numerator information"<<endl;   return 0x0;}
  if(sDePath.IsNull() || sDeFile.IsNull() || sDeHist.IsNull()) { cout<<"Don't have denominator information"<<endl; return 0x0;}
  //-----------------------------------


  TH1D* hDenominator = (TH1D*)GetTH1FromFile(sDePath, sDeFile, sDeList, sDeHist);
  hDenominator->SetName("hDenominator");
  SetLine(hDenominator,cLine[0], sMark[0]);
  SetAxis(hDenominator, YMin, YMax, 0.6, 6., "Efficiency");
  leg->AddEntry(hDenominator,"LHC16k","lp");
  hDenominator->Draw("same");

  TH1D* hNumerator = (TH1D*)GetTH1FromFile(sNuPath, sNuFile, sNuList, sNuHist);
  hNumerator->SetName("hNumerator");
  SetLine(hNumerator,cLine[1], sMark[1]);
  hNumerator->Draw("same");
  leg->AddEntry(hNumerator,"LHC16h","lp");

  TH1D* hNumerator0 = (TH1D*)GetTH1FromFile(sNuPath0, sNuFile0, sNuList0, sNuHist0);
  hNumerator0->SetName("hNumerator0");
  SetLine(hNumerator0,cLine[2], sMark[2]);
  hNumerator0->Draw("same");
  leg->AddEntry(hNumerator0,"LHC16l","lp");

  SetLegend(leg);
  leg->Draw();

  TLatex*     tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.2, 0.9, sLatex);

  //c2->Update();

  c2->cd();
  TPad *c2_b = new TPad("c2_b", "c2_b", 0., 0. , 1., 0.35);

  c2_b->SetFillColor(0);
  c2_b->SetBorderMode(0);
  c2_b->SetBorderSize(0);
  c2_b->SetRightMargin(0.03);
  c2_b->SetLeftMargin(0.13);
  c2_b->SetTopMargin(0.00);
  c2_b->SetBottomMargin(0.3);
  c2_b->SetFrameFillStyle(0);
  c2_b->SetFrameBorderMode(0);

  //TPad *c2_b = new TPad("c2_b", "c2_b", 0., 0.1 , 0.9, 0.40);
  //c2_b->SetTopMargin(0.);
  //c2_b->SetRightMargin(0.01);
  //c2_b->SetBottomMargin(0.2);
  //c2_b->SetFillColor(0);
  //c2_b->SetBorderMode(0);
  //c2_b->SetBorderSize(2);
  //c2_b->SetFrameBorderMode(0);
  //c2_b->SetFrameBorderMode(0);
  c2_b->Draw();
  c2_b->cd();

  TH1D* Numerator   = (TH1D*)hNumerator->Clone("Numerator");
  TH1D* Numerator0  = (TH1D*)hNumerator0->Clone("Numerator0");
  TH1D* Denominator = (TH1D*)hDenominator->Clone("Denominator");

  Numerator->Divide(Denominator);
  TH1D* hRatio  = Numerator;
  hRatio->SetName("Ratio");
  SetLine(hRatio,cLine[3], sMark[0]);
  SetAxis(hRatio, 0.1, 2.5, 0.6, 6., "Ratio");
  leg->AddEntry(hRatio,"LHC16h/LHC16k","lp");
  hRatio->Draw("same");

  Numerator0->Divide(Denominator);
  TH1D* hRatio0  = Numerator0;
  //TH1D* hRatio0 = (TH1D*)RatioTH1D(Numerator0,Denominator);
  hRatio0->SetName("Ratio0");
  SetLine(hRatio0,cLine[4], sMark[1]);
  leg->AddEntry(hRatio0,"LHC16l/LHC16k","lp");
  hRatio0->Draw("same");

  hRatio->GetXaxis()->SetTitleSize(0.13);
  hRatio->GetXaxis()->SetLabelSize(0.14);
  hRatio->GetXaxis()->SetTitleOffset(1.);

  hRatio->GetYaxis()->SetTitleSize(0.13);
  hRatio->GetYaxis()->SetLabelSize(0.13);
  hRatio->GetYaxis()->SetTitleOffset(0.4);

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
