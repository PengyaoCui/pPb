#include "./SourceFun.h"

void ratio_Cumulate(){
 
  TString sname = "NJ";
  //Bool_t IsSave(0);

  TString sFile = "./result/ratio.root";
  TString sCuts = "V0DCA";

  //Numerator information
  TString sNuPath = "/home/cuipengyao/study/code/Cascade_LHC16h/QA_Topol_UpdateBinSide";
  TString sNuFile = "AnalysisOutputs_FitInvMrd.root";
  TString sNuList = Form("listFitInvMrd_Xi_Default_%s", sCuts.Data());
  TString sNuHist = Form("hS_%s", sCuts.Data());

  TString sNuPath0 = "/home/cuipengyao/study/code/Cascade_LHC16l/QA_Topol_UpdateBinSide";
  TString sNuFile0 = "AnalysisOutputs_FitInvMrd.root";
  TString sNuList0 = Form("listFitInvMrd_Xi_Default_%s", sCuts.Data());
  TString sNuHist0 = Form("hS_%s", sCuts.Data());

  //Denominator information
  TString sDePath = "/home/cuipengyao/study/code/Cascade_LHC16k/QA_Topol_UpdateBinSide";
  TString sDeFile = "AnalysisOutputs_FitInvMrd.root";
  TString sDeList = Form("listFitInvMrd_Xi_Default_%s", sCuts.Data());
  TString sDeHist = Form("hS_%s", sCuts.Data());

  TString sLatex = Form("LHC16k as the reference");
  //TString sLatex = "Raw inclusive #Xi^{-} result to LF";
  Double_t   YMin = 1e-6;
  Double_t   YMax = 1e7; 
  Double_t   XMin = 0.;
  Double_t   XMax = 6.;
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
  c2_a->SetLogy();

  TLegend* leg = new TLegend(0.8,0.9,1.0,0.5);
    
  //-----------------------------------
  if(sNuPath.IsNull() || sNuFile.IsNull() || sNuHist.IsNull()) { cout<<"Don't have numerator information"<<endl;   return 0x0;}
  if(sDePath.IsNull() || sDeFile.IsNull() || sDeHist.IsNull()) { cout<<"Don't have denominator information"<<endl; return 0x0;}
  //-----------------------------------


  TH1D* hNumerator   = (TH1D*)GetTH1FromFile(sNuPath,  sNuFile,  sNuList, sNuHist);
  hNumerator->SetName("hNumerator");
  hNumerator->Scale(1./hNumerator->Integral(1, hNumerator->GetNbinsX()));
  //cout<<hNumerator->GetEntries()<<endl;
  //cout<<hNumerator->Integral(0, hNumerator->GetNbinsX())<<endl;
  //cout<<hNumerator->GetIntegral()<<endl;
  //hNumerator->Draw("same");
  TH1D* hSumNu = (TH1D*)hNumerator->Clone("hSumNu");hSumNu->Reset();
  for(Int_t i = 1; i<=hSumNu->GetNbinsX(); i++){
    hSumNu->SetBinContent(i, hNumerator->Integral(1, i));
    //hSumNu->SetBinError(i, TMath::Sqrt(hSumNu->GetBinContent(i)));
  }
  //hSumNu->Draw("same");
  SetLine(hSumNu,cLine[0], sMark[0]);
  SetAxis(hSumNu, YMin, YMax, XMin, XMax, "Per event yield",sCuts);
  leg->AddEntry(hSumNu,"LHC16h","lp");
  hSumNu->Draw("same");

  TH1D* hNumerator0  = (TH1D*)GetTH1FromFile(sNuPath0, sNuFile0, sNuList0, sNuHist0);
  hNumerator0->SetName("hNumerator0");
  hNumerator0->Scale(1./hNumerator0->Integral(1, hNumerator0->GetNbinsX()));
  TH1D* hSumNu0 = (TH1D*)hNumerator0->Clone("hSumNu0");hSumNu0->Reset();
  for(Int_t j = 1; j<=hSumNu0->GetNbinsX(); j++){
    hSumNu0->SetBinContent(j, hNumerator0->Integral(1, j));
    //hSumNu0->SetBinError(j, TMath::Sqrt(hSumNu0->GetBinContent(j)));
  }
  //hSumNu0->Scale(1./6.72309e+07);
  SetLine(hSumNu0,cLine[1], sMark[1]);
  leg->AddEntry(hSumNu0,"LHC16l","lp");
  hSumNu0->Draw("same");

  TH1D* hDenominator = (TH1D*)GetTH1FromFile(sDePath,  sDeFile,  sDeList, sDeHist);
  hDenominator->SetName("hDenominator");
  hDenominator->Scale(1./hDenominator->Integral(1, hDenominator->GetNbinsX()));
  TH1D* hSumDe = (TH1D*)hDenominator->Clone("hSumDe");hSumDe->Reset();
  for(Int_t k = 1; k<=hSumDe->GetNbinsX(); k++){
    hSumDe->SetBinContent(k, hDenominator->Integral(1, k));
    //hSumDe->SetBinError(k, TMath::Sqrt(hSumDe->GetBinContent(k)));
  }
  //hSumDe->Scale(1./2.49632e+08);
  SetLine(hSumDe,cLine[2], sMark[2]);
  leg->AddEntry(hSumDe,"LHC16k","lp");
  hSumDe->Draw("same");

  SetLegend(leg);
  leg->Draw();

  TLatex*     tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.15, 0.9, sCuts);
  tex->DrawLatex(0.15, 0.8, sLatex);

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

  TH1D* Numerator   = (TH1D*)hSumNu->Clone("Numerator");
  TH1D* Numerator0  = (TH1D*)hSumNu0->Clone("Numerator0");
  TH1D* Denominator = (TH1D*)hSumDe->Clone("Denominator");

  //TH1D* hRatio  = (TH1D*)RatioTH1D(Numerator,Denominator);
  Numerator->Divide(Denominator);
  TH1D* hRatio  = Numerator; 
  hRatio->SetName("Ratio");
  SetLine(hRatio,cLine[0], sMark[0]);
  SetAxis(hRatio, 0.1, 2.5, XMin, XMax, "Ratio", sCuts);
  hRatio->Draw("same");
  leg->AddEntry(hRatio,"LHC16h/LHC16k","lp");

  //TH1D* hRatio0 = (TH1D*)RatioTH1D(Numerator0,Denominator);
  Numerator0->Divide(Denominator);
  TH1D* hRatio0  = Numerator0; 
  hRatio0->SetName("Ratio0");
  SetLine(hRatio0,cLine[1], sMark[1]);
  hRatio0->Draw("same");
  leg->AddEntry(hRatio0,"LHC16l/LHC16k","lp");

  hRatio->GetXaxis()->SetTitleSize(0.13);
  hRatio->GetXaxis()->SetLabelSize(0.14);
  hRatio->GetXaxis()->SetTitleOffset(1.);

  hRatio->GetYaxis()->SetTitleSize(0.13);
  hRatio->GetYaxis()->SetLabelSize(0.13);
  hRatio->GetYaxis()->SetTitleOffset(0.4);

  TLine* l = new TLine(XMin, 1, XMax, 1);
  l->SetLineColor(kRed);
  l->SetLineWidth(2);
  l->Draw("same");

  //c2->cd();
  //c2->Draw();
  //c2->SaveAs(Form("./figure/%s.pdf", sname.Data()));

  //if(IsSave) {file->cd(); hRatio->Write(HistNeg, TObject::kSingleKey);}

  //if(IsSave) { file->Close();}

  return;
}
