#include "./SourceFun.h"

void Ratio(){
 
  TString sname = "NJ";
  Bool_t IsSave(0);

  TString sFile = "./result/ratio.root";
  TString sCut = "SignalExtract";

  //Numerator information
  //TString sPath = "/home/cuipengyao/study/code/Cascade_LHC16h/QA_Topol";
  TString sPath = Form("/home/cuipengyao/study/code/Draw/macro/Uncertainty/result");
  TString sFile = Form("PtSpect_%s.root", sCut.Data());
  TString sHist = "hPtIncl_Xi";
  //TString sNuHist[] = {"Loose", "VLoose", "Tight", "VTight", "VvTight"};
  TString sNuHist[] = {"Tight", "Loose"};

  const Int_t nNuHist  = sizeof(sNuHist)/sizeof(TString);

  TString sDeHist = "Stand";

  TString sLatex = Form("Standard cuts as the reference");
  Double_t   YMin = 1e-6;
  Double_t   YMax = 1e7; 
  Double_t   XMin = 0.6;
  Double_t   XMax = 6.;
  //-----------------------------------

  if (IsSave) TFile *file = TFile::Open(sFile, "UPDATE");

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
  c2_a->Draw();
  c2_a->cd();
  c2_a->SetLogy();

  TLegend* leg = new TLegend(0.8,0.9,1.0,0.5);
    
  //-----------------------------------
  if(sPath.IsNull() || sFile.IsNull() ) { cout<<"Don't have file"<<endl;   return 0x0;}
  //-----------------------------------

  for(Int_t i=0; i<nNuHist; i++) {
    TString sNumerator = Form("%s_%s", sHist.Data(), sNuHist[i].Data());
    TH1D* hNumerator = (TH1D*)GetTH1FromFile(sPath,  sFile,  sNumerator);
    hNumerator->SetName(Form("hNumerator_%s", sNumerator.Data()));
    //for(Int_t i = 0; i<hNumerator->GetNbinsX(); i++){hNumerator->SetBinError(i, TMath::Sqrt(hNumerator->GetBinContent(i)));}
    //NormBinSize(hNumerator);
    //hNumerator->Scale(1./hNumerator->Integral(1, 4));
    SetLine(hNumerator,cLine[i+1], sMark[i+1]);
    SetAxis(hNumerator, YMin, YMax, XMin, XMax, "d#rho/d#it{p}_{T}");
    leg->AddEntry(hNumerator,sNuHist[i],"lp");
    hNumerator->Draw("same");
  }

  TString sDenominator = Form("%s_%s", sHist.Data(), sDeHist.Data());
  TH1D* hDenominator = (TH1D*)GetTH1FromFile(sPath,  sFile,  sDenominator);
  hDenominator->SetName("hDenominator");
  SetLine(hDenominator,cLine[0], sMark[0]);
  leg->AddEntry(hDenominator,sDeHist,"lp");
  hDenominator->Draw("same");
  SetLegend(leg);
  leg->Draw();

  TLatex*     tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.15, 0.9, sCut);
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

  c2_b->Draw();
  c2_b->cd();


  for(Int_t i=0; i<nNuHist; i++) {

    TString sRatio = Form("%s/%s", sNuHist[i].Data(), sDeHist.Data());

    //TH1D* Numerator   = (TH1D*)hNumerator->Clone("Numerator");
    TString sNum = Form("%s_%s", sHist.Data(), sNuHist[i].Data());
    TH1D* Numerator = (TH1D*)GetTH1FromFile(sPath,  sFile,  sNum);
    Numerator->SetName(Form("Numerator_%s", sNuHist[i].Data()));
    TH1D* Denominator = (TH1D*)hDenominator->Clone("Denominator");

    //TH1D* hRatio  = (TH1D*)RatioTH1D(Numerator,Denominator);
    Numerator->Divide(Denominator);
    TH1D* hRatio  = Numerator; 
    hRatio->SetName(sRatio);
    SetLine(hRatio,cLine[i+1], sMark[i+1]);
    SetAxis(hRatio, 0.95, 1.05, XMin, XMax, "Ratio");
    hRatio->Draw("same");
    //leg->AddEntry(hRatio,sRatio,"lp");


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

  //c2->cd();
  //c2->Draw();
  //c2->SaveAs(Form("./figure/%s.pdf", sname.Data()));

  if(IsSave) {file->cd(); hRatio->Write(HistNeg, TObject::kSingleKey);}

  if(IsSave) { file->Close();}

  return;
}
