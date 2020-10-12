#include "./SourceFun.h"

void ratio(){
 
  //Bool_t IsSave(0);

  TString sFile = "/home/cuipengyao/study/code/Draw/macro/Cascade_LHC16klop/result/PtSpect_test.root";
  TString HistNeg = "XiNeg";

  //Numerator information
  TString sNuPath = "/home/cuipengyao/study/code/Draw/macro/Cascade_LHC16klop/result";
  TString sNuFile = "PtSpect_test.root";
  //TString sNuList = "listEffCorrJE_Xi_Default_PtJ22_JC";
  TString sNuHist = "hPtIncl_Xi";

  //Denominator information
  TString sDePath = "/home/cuipengyao/study/code/Draw/macro/Cascade_LHC16klop/result";
  TString sDeFile = "PtSpect_test.root";
  //TString sDeList = "listEffInclMC_Xi_Default";
  TString sDeHist = "hPtMC_Xi";

  TString sLatex = "";
  Double_t   YMin = 1e-7;
  Double_t   YMax = 1e7;
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
  c2_a->SetLogy();
  c2_a->cd();

  TLegend* leg = new TLegend(0.8,0.9,1.0,0.5);
    
  //-----------------------------------
  if(sNuPath.IsNull() || sNuFile.IsNull() || sNuHist.IsNull()) { cout<<"Don't have numerator information"<<endl;   return 0x0;}
  if(sDePath.IsNull() || sDeFile.IsNull() || sDeHist.IsNull()) { cout<<"Don't have denominator information"<<endl; return 0x0;}
  //-----------------------------------


  TH1D* hNumerator = (TH1D*)GetTH1FromFile(sNuPath, sNuFile, sNuHist);
  TH1D* hDenominator = (TH1D*)GetTH1FromFile(sDePath, sDeFile, sDeHist);
  //TH1D* hNumerator = RebinTH1D (hNumerator, hDenominator);
  hNumerator->SetName("hNumerator");
  hDenominator->SetName("hDenominator");
  SetLine(hNumerator,cLine[0], sMark[0]);
  SetAxis(hNumerator, YMin, YMax, 0.6, 6., "Yeild");
  hNumerator->Draw("same");

  SetLine(hDenominator,cLine[1], sMark[1]);
  hDenominator->Draw("same");
  leg->AddEntry(hNumerator,"RD Raw","lp");
  leg->AddEntry(hDenominator,"MC","lp");
  //leg->AddEntry(hNumerator,"#Xi^{-}","lp");
  //leg->AddEntry(hDenominator,"#bar{#Xi}^{+}","lp");
  SetLegend(leg);
  leg->Draw();

  TLatex*     tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.15, 0.9, sLatex);

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

  TH1D* Numerator = (TH1D*)hNumerator->Clone("Numerator");;
  Numerator->SetName("Numerator");
  TH1D* Denominator = (TH1D*)hDenominator->Clone("Denominator");
  Denominator->SetName("Denominator");
  Numerator->Divide(Denominator);
  TH1D* hRatio = (TH1D*)Numerator;
  hRatio->SetName("Ratio");
  SetLine(hRatio,kBlack, 20);
  SetAxis(hRatio, 0.1, 2.2, 0.6, 6., "RD/MC");

  hRatio->GetXaxis()->SetTitleSize(0.13);
  hRatio->GetXaxis()->SetLabelSize(0.14);
  hRatio->GetXaxis()->SetTitleOffset(1.);

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
