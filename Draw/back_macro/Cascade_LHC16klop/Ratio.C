#include "../../SourceFun.h"

void Ratio(){
  TString sCut = "hJetLeadTrkPt";

  TString sPath[] = {"/home/cuipengyao/study/code/Cascade_LHC16l/JC_AddJetPt", "/home/cuipengyao/study/code/Cascade_LHC16o/JC_AddJetPt", "/home/cuipengyao/study/code/Cascade_LHC16p/JC_AddJetPt"};
  TString sFile[] = {"AnalysisOutputs_LoopJetRD.root", "AnalysisOutputs_LoopJetRD.root", "AnalysisOutputs_LoopJetRD.root"};
  TString sList[] = {"listLoopJetRD_Xi_Default_PtJ22_JC", "listLoopJetRD_Xi_Default_PtJ22_JC", "listLoopJetRD_Xi_Default_PtJ22_JC"};
  TString sHist[] = {sCut, sCut, sCut};

  TString sDePath = "/home/cuipengyao/study/code/Cascade_LHC16k/JC_AddJetPt";
  TString sDeFile = "AnalysisOutputs_LoopJetRD.root";
  TString sDeList = "listLoopJetRD_Xi_Default_PtJ22_JC";
  TString sDeHist = sCut;

  TString  sLeg[] = {"LHC16l", "LHC16o", "LHC16p", "LHC16k"};
  TString sLatex = "LHC16k as the reference";
  Double_t   YMin = 1e-4;
  Double_t   YMax = 1e8;
  Double_t   XMin = 3.;
  Double_t   XMax = 22.;
  //-----------------------------------
  TCanvas * c2 = new TCanvas("c2","");
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

  c2_a->Draw();
  c2_a->cd();
  c2_a->SetLogy();


  TLegend* leg = new TLegend(0.7,0.9,1.0,0.6);    
  //-----------------------------------
  Int_t nHist = sizeof(sHist)/sizeof(TString);
  const Int_t nhist = nHist;
  TH1D* h[nhist] = {NULL};
  //Double_t dBin[] = {0., 1., 2., 3., 4., 5., 6., 7., 8., 9., 10., 11., 12., 13., 14., 15., 16., 17., 18., 19., 20., 22., 24., 26., 28., 30., 32., 34., 36., 38., 40., 44., 48., 53., 59., 66., 74., 85., 100. };
  Double_t dBin[] = { 3., 4., 5., 6., 7., 8., 9., 10., 12., 14., 16., 19., 22.};
  const Int_t nBin = sizeof(dBin) / sizeof(Double_t)-1;
  cout<<nBin<<endl;
  TH1D *hRebin = new TH1D("hRebin", "", nBin, dBin);

  //Denominator
  //-----------------------------------
  TH1D* h2 = (TH1D*)GetTH1FromFile(sDePath, sDeFile, sDeList, sDeHist);
  h2->SetName("DeHist"); 
  //h2->Rebin(200);
  h2 = RebinTH1D(h2, hRebin);
  NormBinSize(h2);
  h2->Scale(1./h2->Integral(0, h2->GetNbinsX()));
  SetLine(h2,cLine[nHist],sMark[nHist]);
  SetAxis(h2, YMin, YMax, XMin, XMax, "Probability density");
  h2->GetXaxis()->SetTitleSize(0.06);
  h2->GetYaxis()->SetTitleSize(0.06);
  h2->GetXaxis()->SetTitleOffset(1.);
  h2->GetYaxis()->SetTitleOffset(1.);
  h2->GetXaxis()->SetLabelSize(0.05);
  h2->GetYaxis()->SetLabelSize(0.05);
  h2->Draw("same");
  leg->AddEntry(h2,sLeg[nHist],"lp");

  //hRatios
  //-----------------------------------
  for (Int_t i = 0; i< nHist; i++){
    TString sMyPath = sPath[i]; 
    TString sMyFile = sFile[i]; 
    TString sMyList = sList[i]; 
    TString sMyHist = sHist[i]; 
    h[i] = (TH1D*)GetTH1FromFile(sMyPath, sMyFile, sMyList, sMyHist);
    h[i]->SetName(Form("NuHist_%d", i)); 
    //h[i]->Rebin(200);
    //cout<<"======================"<<endl;
    //h[i] = RebinTH1D(h[i], hRebin);
    //cout<<"++++++++++++++++++++++"<<endl;
    //NormBinSize(h[i]);
    //h[i]->Scale(1./h[i]->Integral(0, h[i]->GetNbinsX()));
    //SetLine(h[i],cLine[i],sMark[i]);
    //h[i]->SetMarkerSize(1.3);
    //h[i]->Draw("same");
    //leg->AddEntry(h[i],sLeg[i],"lp");
  }
  TH1D* ha = h[0];
  TH1D* hb = h[1];
  TH1D* hc = h[2];
  h[0] = RebinTH1D(ha, hRebin);
  h[1] = RebinTH1D(hb, hRebin);
  h[2] = RebinTH1D(hc, hRebin);
  NormBinSize(h[0]);
  NormBinSize(h[1]);
  NormBinSize(h[2]);
  h[0]->Scale(1./h[0]->Integral(0, h[0]->GetNbinsX()));
  h[1]->Scale(1./h[1]->Integral(0, h[1]->GetNbinsX()));
  h[2]->Scale(1./h[2]->Integral(0, h[2]->GetNbinsX()));

  SetLine(h[0],cLine[0],sMark[0]);
  SetLine(h[1],cLine[1],sMark[1]);
  SetLine(h[2],cLine[2],sMark[2]);

  h[0]->Draw("same");
  h[1]->Draw("same");
  h[2]->Draw("same");
  leg->AddEntry(h[0],sLeg[0],"lp");
  leg->AddEntry(h[1],sLeg[1],"lp");
  leg->AddEntry(h[2],sLeg[2],"lp");

  TLatex*     tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  SetCanv(c2);
  c2->SetLogy();
  SetLegend(leg);
  SetStyle();
  tex->DrawLatex(0.16, 0.91, sLatex);
  leg->Draw();

//=========================================
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

  c2_b->Draw();
  c2_b->cd();

  //NuHist_1->Divide(h2);
  for (Int_t j = 0; j< nHist; j++){
    TH1D* hRatio   = (TH1D*)h[j]->Clone(Form("hRatio_%d",j));
    hRatio->Divide(h2);
    SetLine(hRatio,cLine[j],sMark[j]);
    SetAxis(hRatio, 0.6, 1.4, XMin, XMax, "Ratio");
    hRatio->SetMarkerSize(1.3);
    hRatio->Draw("same");
    //hRatio->GetXaxis()->SetTitle(sCut);
    hRatio->GetXaxis()->SetTitle("#it{p}_{T, Leading}(GeV/#it{c})");
    hRatio->GetXaxis()->SetTitleSize(0.13);
    hRatio->GetXaxis()->SetLabelSize(0.14);
    hRatio->GetXaxis()->SetTitleOffset(1.);

    hRatio->GetYaxis()->SetTitleSize(0.13);
    hRatio->GetYaxis()->SetLabelSize(0.13);
    hRatio->GetYaxis()->SetTitleOffset(0.4);
  }

  TLine* l = new TLine(XMin, 1, XMax, 1);
  l->SetLineColor(kRed);
  l->SetLineWidth(2);
  l->Draw("same");

  return;
}
