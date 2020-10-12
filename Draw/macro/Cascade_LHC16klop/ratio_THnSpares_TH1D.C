#include "./SourceFun.h"
void ratio_THnSpares_TH1D(){

  TString sPeriod[] = {"LHC16k", "LHC16h", "LHC16l"};
  //TString  Period[] = {"LHC16i4a", "LHC17f5", "LHC16i4b"};

  TString sFile = "AnalysisOutputs_LoopIncMC.root";
  TString sList = "listLoopIncMC_Xi_Default";
  
  //TString sFile = "AnalysisOutputs_Loop1ndRD.root";
  //TString sList = "listLoop1ndRD_Xi_Default";

  Double_t XMin = 0.;
  Double_t XMax = 40.;

  Double_t binmin = 1.;
  Double_t binmax = 20.;

  Int_t k = 5; 
  TString sCuts = "NegDCA";


  TString sCut[29];
  sCut[ 0] = "V0Radius";
  sCut[ 1] = "V0CPA";
  sCut[ 2] = "V0DistToPVoverP";
  sCut[ 3] = "V0DausDCA";
  sCut[ 4] = "PosDCAtoPV";
  sCut[ 5] = "NegDCAtoPV";
  sCut[ 6] = "DauXrowsTPC";
  sCut[ 7] = "DauXrowsOverFindableClusTPC";
  sCut[ 8] = "XiPt";
  sCut[ 9] = "RapidityLa";
  sCut[10] = "Lambda.M";
  sCut[11] = "AntiLa.M";
  sCut[12] = "Pos.Eta";
  sCut[13] = "Neg.Eta";

  sCut[14] = "XiRadius";
  sCut[15] = "XiCPA";
  sCut[16] = "XiDCAtoPV";
  sCut[17] = "V0toBachDCA";
  sCut[18] = "V0DCAtoPV";
  sCut[19] = "BachDCAtoPV";
  sCut[20] = "BachXrowsTPC";
  sCut[21] = "BachXrowsOverFindableClusTPC";
  sCut[22] = "V0.Eta";
  sCut[23] = "Bach.Eta";

  sCut[24] = "PosPionSigmaTPC";
  sCut[25] = "PosProtonSigmaTPC";
  sCut[26] = "NegPionSigmaTPC";
  sCut[27] = "NegProtonSigmaTPC";
  sCut[28] = "BachSigmaTPC";

  

  TString sPath0 = Form("/home/cuipengyao/study/code/Cascade_%s/JC_CombineXi_CorrNormFact", sPeriod[0].Data());

  //TFile *f[] = {NULL};
  //for (Int_t i = 0; i< nPeriod; i++) f[i] = TFile::Open(Form("%s/AnalysisOutputs_Loop1ndRD.root", sPath[i].Data())); 

  TFile     *f0 = TFile::Open(Form("%s/%s", sPath0.Data(), sFile.Data())); 
  TList *flist0 = (TList *)f0->Get(sList);  
  THnSparseD *hsCuts0 = (THnSparseD*)flist0->FindObject("hsCutAfter");
  hsCuts0->SetName("hsCuts0"); 
  //hsCuts0->GetAxis(8)->SetRange( hsCuts0->GetAxis(8)->FindBin(binmin), hsCuts0->GetAxis(8)->FindBin(binmax));
  f0->Close();


  TCanvas *c1 = new TCanvas("c1","");
  SetStyle();

  //c1->cd();
  //TPad *c2_a = new TPad("c2_a", "c2_a", 0., 0.4, 0.9, 1.);
  //c2_a->SetRightMargin(0.01);
  //c2_a->SetBorderMode(0);
  //c2_a->SetBorderSize(2);

  //c2_a->SetBottomMargin(0.0);
  //c2_a->SetFrameBorderMode(0);
  //c2_a->SetFrameBorderMode(0);
  //TPad *c2_a = new TPad("c2_a", "c2_a", 0., 0.35, 1., 1.);

  //c2_a->SetFillColor(0);
  //c2_a->SetBorderMode(0);
  //c2_a->SetBorderSize(0);
  //c2_a->SetRightMargin(0.03);
  //c2_a->SetLeftMargin(0.13);
  //c2_a->SetTopMargin(0.02);
  //c2_a->SetBottomMargin(0.0);
  //c2_a->SetFrameFillStyle(0);
  //c2_a->SetFrameBorderMode(0);

  //c2_a->Draw();
  //c2_a->cd();
  //c2_a->SetLogy();

  TLegend* leg = new TLegend(0.8,0.9,1.0,0.5);

  TString sPath = "/home/cuipengyao/study/code/Cascade_LHC16k/QA_Topol_UpdateBinSide";
  TString sFile = "AnalysisOutputs_FitInvMrd.root";
  TString sList = Form("listFitInvMrd_Xi_Default_%s", sCuts.Data());
  TString sHist = Form("hS_%s", sCuts.Data());

  TH1D* h1   = (TH1D*)GetTH1FromFile(sPath,  sFile,  sList, sHist);
  h1->SetName("h1");
  NormBinSize(h1);
  h1->Scale(1./h1->Integral(0, h1->GetNbinsX()));
  SetLine(h1,cLine[1], sMark[1]);
  leg->AddEntry(h1,"RD","lp");

  TH1D *h0 =(TH1D*)hsCuts0->Projection(k);
  h0->SetName("h0");
  for(Int_t i = 0; i<h0->GetNbinsX(); i++){h0->SetBinError(i, TMath::Sqrt(h0->GetBinContent(i)));}
  h0->SetTitle("");

  //h0 = RebinTH1D(h0, h1);
  NormBinSize(h0);
  h0->Scale(1./(h0->Integral(1, h0->GetNbinsX())));
  SetLine(h0,cLine[0], sMark[0]);
  leg->AddEntry(h0,"MC","lp");

  SetAxis(h0, 1e-4, 1e1, XMin, XMax, "Ratio");
  h0->GetYaxis()->SetTitleSize(0.06);
  h0->GetYaxis()->SetTitleOffset(1.);
  h0->GetXaxis()->SetLabelSize(0.05);
  h0->GetYaxis()->SetLabelSize(0.06);
  h0->GetYaxis()->SetTitle("Probability density"); 

  //h1->Scale(1./hNumerator->Integral(1, 4));
  h1->Draw("same");
  h0->Draw("same");

  //SetCanv(c1);
  SetLegend(leg);
  leg->Draw();
  TLatex*     tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  //tex->DrawLatex(0.15, 0.9,Form("%s as the reference", sPeriod[0].Data()));
  //tex->DrawLatex(0.15, 0.8,Form("%s distribution in 2<#it{p}_{T}<3(GeV/#it{c})", sCut[k].Data()));
  tex->DrawLatex(0.15, 0.9,Form("%s distribution", sCut[k].Data()));


  //c1->cd();
  //TPad *c2_b = new TPad("c2_b", "c2_b", 0., 0. , 1., 0.35);

  //c2_b->SetFillColor(0);
  //c2_b->SetBorderMode(0);
  //c2_b->SetBorderSize(0);
  //c2_b->SetRightMargin(0.03);
  //c2_b->SetLeftMargin(0.13);
  //c2_b->SetTopMargin(0.00);
  //c2_b->SetBottomMargin(0.3);
  //c2_b->SetFrameFillStyle(0);
  //c2_b->SetFrameBorderMode(0);
  //TPad *c2_b = new TPad("c2_b", "c2_b", 0., 0.05 , 0.9, 0.40);
  //c2_b->SetTopMargin(0.);
  //c2_b->SetRightMargin(0.01);
  //c2_b->SetBottomMargin(0.2);
  //c2_b->SetFillColor(0);
  //c2_b->SetBorderMode(0);
  //c2_b->SetBorderSize(2);
  //c2_b->SetFrameBorderMode(0);
  //c2_b->SetFrameBorderMode(0);
  //c2_b->Draw();
  //c2_b->cd();

  //TH1D *h_0 = (TH1D*)h0->Clone("h_0");
  //TH1D *h_1 = (TH1D*)h1->Clone("h_1");

  //TH1D* hRatio  =0; 
  //h_1->Divide(h_0);
  //hRatio = h_1;
  //SetAxis(hRatio, 0.5, 1.5, XMin, XMax, "RD/MC");
  //hRatio->SetName("Ratio");
  //SetLine(hRatio,cLine[3], sMark[0]);
  ////leg->AddEntry(hRatio,Form("%s/%s", sPeriod[1].Data(), sPeriod[0].Data()),"lp");
  //hRatio->Draw("same");


  //hRatio->GetXaxis()->SetTitle(sCut[k]);
  //hRatio->GetYaxis()->SetTitle("Ratio");
  //hRatio->GetXaxis()->SetTitleSize(0.13);
  //hRatio->GetXaxis()->SetLabelSize(0.14);
  //hRatio->GetXaxis()->SetTitleOffset(1.);

  //hRatio->GetXaxis()->SetTitleSize(0.13);
  //hRatio->GetYaxis()->SetTitleSize(0.13);
  //hRatio->GetYaxis()->SetLabelSize(0.13);
  //hRatio->GetYaxis()->SetTitleOffset(0.4);

  //TLine* l = new TLine(XMin, 1, XMax, 1);
  //l->SetLineColor(kRed);
  //l->SetLineWidth(2);
  //l->Draw("same");

 

}

