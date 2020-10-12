#include "./SourceFun.h"
void ratio_THnSpares2(){

  Bool_t IsSave = 1;
  //TString sPeriod[] = {"LHC16k", "LHC16h", "LHC16l"};
  TString sPeriod = "LHC16l";
  Int_t k = 1;
  TString sCut[29];
  sCut[ 0] = "V0Radius";
  sCut[ 1] = "V0CPA";
  sCut[ 2] = "V0DistToPVoverP";
  sCut[ 3] = "V0DausDCA";
  sCut[ 4] = "PosDCAtoPV";
  sCut[ 5] = "NegDCAtoPV";
  sCut[ 6] = "DauXrowsTPC";
  sCut[ 7] = "DauXrowsOverFindableClusTPC";
  sCut[ 8] = "V0Pt";
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


  TString sPath0 = Form("/home/cuipengyao/study/code/Cascade_%s/JC_CombineXi_CorrNormFact", sPeriod.Data());
  TString sPath1 = Form("/home/cuipengyao/study/code/Cascade_%s/JC_CombineXi_CorrNormFact", sPeriod.Data());
  //TString sPath2 = Form("/home/cuipengyao/study/code/Cascade_%s/JC_CombineXi_CorrNormFact", sPeriod[2].Data());

  //TFile *f[] = {NULL};
  //for (Int_t i = 0; i< nPeriod; i++) f[i] = TFile::Open(Form("%s/AnalysisOutputs_Loop1ndRD.root", sPath[i].Data())); 

  TFile     *f0 = TFile::Open(Form("%s/AnalysisOutputs_Loop1ndRD.root", sPath0.Data())); 
  TList *flist0 = (TList *)f0->Get("listLoop1ndRD_Xi_Default");  
  THnSparseD *hsCuts0 = (THnSparseD*)flist0->FindObject("hsCutAfter");
  hsCuts0->SetName("hsCuts0"); 
  f0->Close();

  TFile     *f1 = TFile::Open(Form("%s/AnalysisOutputs_LoopIncMC.root", sPath1.Data())); 
  TList *flist1 = (TList *)f1->Get("listLoopIncMC_Xi_Default");  
  THnSparseD *hsCuts1 = (THnSparseD*)flist1->FindObject("hsCutAfter");
  hsCuts1->SetName("hsCuts1"); 
  f1->Close();


  TCanvas *c1 = new TCanvas("c1","");
  SetStyle();

  c1->cd();
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


  TLegend* leg = new TLegend(0.8,0.9,1.0,0.5);

  TH1D *h0 =(TH1D*)hsCuts0->Projection(k);
  h0->SetName("h0");
  //h0->Scale(1./2.49632e+08);
  //h0->Rebin(10);
  for(Int_t i = 0; i<h0->GetNbinsX(); i++){h0->SetBinError(i, TMath::Sqrt(h0->GetBinContent(i)));}
  h0->Scale(1./(h0->GetEntries()));
  NormBinSize(h0);
  h0->GetYaxis()->SetTitleSize(0.06);
  h0->GetYaxis()->SetTitleOffset(1.);
  h0->GetXaxis()->SetLabelSize(0.05);
  h0->GetYaxis()->SetLabelSize(0.06);
  h0->GetYaxis()->SetTitle("Probability density"); 

  SetLine(h0,cLine[0], sMark[0]);
  h0->SetTitle("");
  leg->AddEntry(h0,"RD","lp");
 
  TH1D *h1 =(TH1D*)hsCuts1->Projection(k);
  h1->SetName("h1");
  //h1->Rebin(10);
  for(Int_t i = 0; i<h1->GetNbinsX(); i++){h1->SetBinError(i, TMath::Sqrt(h1->GetBinContent(i)));}
  //h1->Scale(1./1.28757e+08 );
  h1->Scale(1./(h1->GetEntries()));
  NormBinSize(h1);
  SetLine(h1,cLine[1], sMark[1]);
  h1->SetTitle("");
  leg->AddEntry(h1,"MC","lp");

  h0->Draw("same");
  h1->Draw("same");

  //SetCanv(c1);
  SetLegend(leg);
  leg->Draw();
  TLatex*     tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.15, 0.9,Form("%s   %s", sPeriod.Data(), sCut[k].Data()));

  c1->cd();
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

  TH1D *h_0 = (TH1D*)h0->Clone("h_0");
  TH1D *h_1 = (TH1D*)h1->Clone("h_1");

  TH1D* hRatio  =0; 
  h_1->Divide(h_0);
  hRatio = h_1;
  hRatio->SetName("Ratio");
  SetLine(hRatio,cLine[3], sMark[0]);
  //leg->AddEntry(hRatio,"MC/RD","lp");
  hRatio->Draw("same");

  hRatio->GetXaxis()->SetTitle(sCut[k]);
  hRatio->GetYaxis()->SetTitle("MC/RD");
  hRatio->GetXaxis()->SetTitleSize(0.13);
  hRatio->GetXaxis()->SetLabelSize(0.14);
  hRatio->GetXaxis()->SetTitleOffset(1.);

  hRatio->GetXaxis()->SetTitleSize(0.13);
  hRatio->GetYaxis()->SetTitleSize(0.13);
  hRatio->GetYaxis()->SetLabelSize(0.13);
  hRatio->GetYaxis()->SetTitleOffset(0.4);
  
  if(IsSave){
  TFile *file = TFile::Open(Form("./result/%s.root", sCut[k].Data()), "UPDATE");
  file->cd();
  hRatio->Write(Form("MC_Data_%s", sPeriod.Data()), TObject::kSingleKey);
  file->Close();
  }
  //TLine* l = new TLine(0., 1, 10., 1);
  //l->SetLineColor(kRed);
  //l->SetLineWidth(2);
  //l->Draw("same");

 

}

