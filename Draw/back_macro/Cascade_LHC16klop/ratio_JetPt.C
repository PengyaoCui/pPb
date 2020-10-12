#include "./SourceFun.h"

void ratio_JetPt(){
 
  //Numerator information
  TString sNuPath = "/home/cuipengyao/study/code/Cascade_LHC16l/JC_AddJetPt";
  TString sNuFile = "AnalysisOutputs_LoopJetRD.root";
  TString sNuList = "listLoopJetRD_Xi_Default_PtJ22_JC";
  TString sNuHist = "hJetEta";

  TString sNuPath0 = "/home/cuipengyao/study/code/Cascade_LHC16o/JC_AddJetPt";
  TString sNuFile0 = "AnalysisOutputs_LoopJetRD.root";
  TString sNuList0 = "listLoopJetRD_Xi_Default_PtJ22_JC";
  TString sNuHist0 = "hJetEta";

  //Denominator information
  TString sDePath = "/home/cuipengyao/study/code/Cascade_LHC16k/JC_AddJetPt";
  TString sDeFile = "AnalysisOutputs_LoopJetRD.root";
  TString sDeList = "listLoopJetRD_Xi_Default_PtJ22_JC";
  TString sDeHist = "hJetEta";

  //TString xAxis = "#it{p}_{T, Leading}";
  //TString xAxis = "#it{p}_{T, jet}";
  TString xAxis = "#eta_{jet}";
  TString sLatex = Form("Jet #eta distribution");
  Double_t   YMin = 1e-6;
  Double_t   YMax = 1e7;
  Double_t   XMin = -0.5;
  Double_t   XMax = 0.5;
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
  //Double_t dBin[] = {0., 1., 2., 3., 4., 5., 6., 7., 8., 9., 10., 11., 12., 13., 14., 15., 16., 17., 18., 19., 20., 22., 24., 26., 28., 30., 32., 34., 36., 38., 40., 44., 48., 53., 59., 66., 74., 85., 100. };
  //Double_t dBin[] = {0., 1., 2., 3., 4., 5., 6., 7., 8., 9., 10., 12., 14., 16., 19., 22., 26., 30.};
  //const Int_t nBin = sizeof(dBin) / sizeof(Double_t)-1;
  //cout<<nBin<<endl;

  //TH1D *hRebin = new TH1D("hRebin", "", nBin, dBin);
  TH1D* hNumerator   = (TH1D*)GetTH1FromFile(sNuPath,  sNuFile, sNuList, sNuHist);
  hNumerator->SetName("hNumerator");
  //hNumerator->Rebin(5);
  hNumerator->Scale(1./(hNumerator->GetEntries()));
  //hNumerator = (TH1D*)RebinTH1D(hNumerator, hRebin);
  hNumerator->SetName("hNumerator");
  //for(Int_t i = 1; i<hNumerator->GetNbinsX(); ++i) { cout<<hNumerator->GetBinLowEdge(i)<<endl;} 
  //cout<<hNumerator->GetXaxis()->GetBinLowEdge(hNumerator->GetNbinsX()+1 ) <<endl;
  NormBinSize(hNumerator);

  SetLine(hNumerator,cLine[0], sMark[0]);
  SetAxis(hNumerator, YMin, YMax, XMin, XMax, "Probability density");
  leg->AddEntry(hNumerator,"LHC16h","lp");
  hNumerator->Draw("same");

  TH1D* hNumerator0  = (TH1D*)GetTH1FromFile(sNuPath0, sNuFile0, sNuList0, sNuHist0);
  hNumerator0->SetName("hNumerator0");
  //hNumerator0->Rebin(5);
  //hNumerator0->Rebin(nBin, "hNumerator0", dBin);
  hNumerator0->Scale(1./(hNumerator0->GetEntries()));
  //hNumerator0 = (TH1D*)RebinTH1D(hNumerator0, hRebin);
  hNumerator0->SetName("hNumerator0");
  NormBinSize(hNumerator0);
  SetLine(hNumerator0,cLine[1], sMark[1]);
  leg->AddEntry(hNumerator0,"LHC16l","lp");
  hNumerator0->Draw("same");

  TH1D* hDenominator = (TH1D*)GetTH1FromFile(sDePath,  sDeFile, sDeList, sDeHist);
  hDenominator->SetName("hDenominator");
  //hDenominator->Rebin(5);
  //hDenominator->Rebin(nBin, "hDenominator", dBin);
  hDenominator->Scale(1./(hDenominator->GetEntries()));
  //hDenominator = (TH1D*)RebinTH1D(hDenominator, hRebin);
  hDenominator->SetName("hDenominator");
  NormBinSize(hDenominator);
  SetLine(hDenominator,cLine[2], sMark[2]);
  leg->AddEntry(hDenominator,"LHC16k","lp");
  hDenominator->Draw("same");

  SetLegend(leg);
  leg->Draw();
  //leg->SetHeader("  "); // option "C" allows to center the header

  TLatex*     tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.16, 0.9, sLatex);
  tex->DrawLatex(0.16, 0.8, "Reference: LHC16k");

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
  SetLine(hRatio,cLine[0], sMark[0]);
  SetAxis(hRatio, 0.01, 2.5, XMin, XMax, "Ratio", xAxis);
  hRatio->Draw("same");
  leg->AddEntry(hRatio,"LHC16h/LHC16k","lp");

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

  //TLatex* tex0 = new TLatex();
  //tex0->SetNDC();
  //tex0->SetTextSizePixels(24);
  //tex0->DrawLatex(0.16, 0.8, "Reference: LHC16k");
  //c2->cd();
  //c2->Draw();
  //c2->SaveAs(Form("./figure/%s.pdf", sname.Data()));

  //if(IsSave) {file->cd(); hRatio->Write(HistNeg, TObject::kSingleKey);}

  //if(IsSave) { file->Close();}

  return;
}
