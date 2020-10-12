#include "./SourceFun.h"

void QA(){

  TString sPath = "/home/cuipengyao/study/pPb/Strangeness/NewPileup/TestFast";
  const TString sRatio = "FAST as Ref";
  TString sPathNu[] = { "CENT_woSDD"};

  TString sPathDe = "/home/cuipengyao/study/pPb/Strangeness/NewPileup/TestFast/FAST";
  //TString sFile = "AnalysisOutputs_FitCbinRD.root";
  //TString sList = "listFitCbinRD_Kshort_Default_0100";
  TString sFile = "AnalysisOutputs_Results.root";
  TString sList = "listResults_Kshort_Default_0100";
  TString sHist = "hNco";

  TString sLeg[] = { "CENT_woSDD", "CENT_wSDD", "FAST"};
  //Double_t nEvent[] = {2.652302e8, 1.755166e8, 2.619427e8};
  Double_t nEvent[] = {1., 1.};

  TString sLatex(Form("Kshort   0-10%%"));
  Double_t XMin = 0.; 
  Double_t XMax = 12. ;
  Double_t YMin = 1e-8;
  Double_t YMax = 1e1;
  Int_t a = 1;
  //-----------------------------------
  TCanvas *can = nullptr;
  TPad *padT = nullptr;
  TPad *padB = nullptr;
  TLatex* tex = nullptr;
  TLegend *leg = nullptr;

  can = MakeCanvas("can");
  leg = new TLegend(0.4, 0.7, 1., 0.9); SetLegend(leg);
  leg->SetNColumns(3);
  //-----------------------------------
  auto nHist = sizeof(sPathNu)/sizeof(TString);
  const auto nhist = nHist;
  Double_t dBin[] = {10, 15, 20, 25, 30, 35, 40, 50, 60, 80, 100};
  //Double_t dBin[] = {0.6, 0.8, 1.0, 1.2, 1.4, 1.6, 1.8, 2.0, 2.2, 2.4, 2.6, 2.8, 3.2, 3.7, 4.2, 5.0, 6.0, 8.0, 12.};
  Int_t nBin = sizeof(dBin)/sizeof(Double_t) - 1;
  TH1D *h0 = new TH1D("h0", "", nBin, dBin);
 
  TH1D* h2 = nullptr;
  TH1D* h1 = nullptr;
  TH1D* hRatio = nullptr;

  padB = MakePadB("padB");
  can->cd();
  padT = MakePadT("padT");
  padT->SetLogy(); 
  padT->SetLogy();

  h2 = (TH1D*)GetTH1D(sPathDe.Data(), sFile.Data(), sList.Data(), sHist.Data());
  //h2->Scale(1./h2->GetEntries());
  //h2->Scale(1./h2->Integral(1, h2->GetNbinsX()));
  h2->Scale(1./nEvent[nHist]);
  //h2=RebinTH1D(h2, h0);
  h2->Rebin(a);
  h2->SetName("h2_De");
  NormHistBinWidth(h2); 
  h2->SetTitle("");
  padT->cd();
  h2->GetXaxis()->SetRangeUser(XMin, XMax);
  h2->GetYaxis()->SetRangeUser(YMin, YMax);
  h2->SetMarkerSize(1);
  DrawHisto(h2, cLine[nHist], sMark[nHist], "same");
  //SetFrame(h2, "#it{p}_{T}", "Probability density");
  SetFrame(h2, "#it{p}_{T}", "#frac{1}{N_{kINT7}} #frac{d#it{N}}{d#it{p}_{T}}");


  for (Int_t i = 0; i< nHist; ++i){
    TString sMyPath = Form("%s/%s", sPath.Data(), sPathNu[i].Data());
    TString sMyFile = sFile; 
    TString sMyList = sList; 
    TString sMyHist = sHist; 
    h1 = (TH1D*)GetTH1D(sMyPath.Data(), sMyFile.Data(), sMyList.Data(), sMyHist.Data());
    //h1->Scale(1./h2->GetEntries());
    //h1->Scale(1./h1->Integral(1, h1->GetNbinsX()));
    h1->Scale(1./nEvent[i]);
    //h1=RebinTH1D(h1, h0);
    h1->Rebin(a);
    h1->SetName(Form("hist_%d", i)); 
    h1->SetTitle(""); 
    NormHistBinWidth(h1); 
    hRatio = (TH1D*) h2->Clone(Form("hRatio_%d", i)); hRatio->Reset();
    hRatio->Divide(h1, h2);
    hRatio->SetName(Form("hratio_%d", i));
    hRatio->GetYaxis()->SetRangeUser(0.6, 1.4);
    padT->cd();
    DrawHisto(h1, cLine[i], sMark[i], "same");
    leg->AddEntry(h1, sLeg[i], "lp");
    padB->cd();
    padB->SetGridy();
    DrawHisto(hRatio, cLine[i], sMark[i], "same");
    //SetFrame(hRatio, "#varphi{jet}", sRatio, 0.08, 0.08, 0.1, 0.1, 1.10, 0.6);
    SetFrame(hRatio, Form("#it{p}_{T}"), sRatio, 0.08, 0.08, 0.1, 0.1, 1.10, 0.6);
  }
  leg->AddEntry(h2, sLeg[nHist],"lp");


  padB->cd();
  //TLine* l = new TLine(XMin, 1., XMax, 1.);
  //l->SetLineColor(kRed);
  //l->SetLineWidth(2);
  //l->Draw("same");

  padT->cd();
  tex =  new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  //tex->DrawLatex(0.2, 0.9, "Kshort");
  tex->DrawLatex(0.2, 0.9, sLatex);
  leg->Draw();
  gStyle->SetOptStat("");
  //can->SaveAs(Form("./figure/QAPlots/QA_Kshort_CentFast_010.eps"));
  CanvasEnd(can);
  return;
}
