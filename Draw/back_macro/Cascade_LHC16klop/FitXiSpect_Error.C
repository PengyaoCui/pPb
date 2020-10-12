#include <TF1.h>
#include "../../SourceFun.h"

void FitXiSpect_Error(){

  TString sSaveName = "FitXiPtSpect";
  TString sFuncName = "JC_FitFunc";
  TString sHistName = "JC_Xi";

  TString sPath = "~/study/code/Draw/macro/Cascade_LHC16klop/result";
  TString sFile = "PtSpect_LHC16klop.root";
  TString sHist = "hPtIncl_Xi";
  Double_t   YMin = 1e-8;
  Double_t   YMax = 1e8;

  TH1D* h1 = (TH1D*)GetTH1FromFile(sPath, sFile, sHist);
  h1->SetName("hist");
  TH1D* h3 = (TH1D*)h1->Clone("h3"); h3->Reset();
  h3->SetName("Error");
  for(Int_t i =1; i<= h1->GetNbinsX(); i++){
    Double_t dvar = h1->GetBinContent(i); 
    Double_t derr = h1->GetBinError(i); 
    h3->SetBinContent(i, dvar + derr);
    h3->SetBinError(i, derr);

   //cout<<i<<"==="<<h1->GetXaxis()->GetBinCenter(i)<<endl;
  }
  Double_t dx[] = { 0.6, 0.8, 1.0, 1.2, 1.4, 1.6, 1.8, 2.0, 2.2, 2.4, 2.6, 2.8, 3.0, 3.3, 3.6, 4.0, 4.5, 5.0, 5.5, 6.5, 7.7, 9.0, 12., 15.}; 
  //Double_t dy[] = { 0.6, 0.8, 1.0, 1.2, 1.4, 1.6, 1.8, 2.0, 2.2, 2.4, 2.6, 2.8, 3.0, 3.3, 3.6, 4.0, 4.5, 5.0, 5.5, 6.5, 7.7, 9.0, 12., 15.}; 
  Int_t nx = sizeof(dx)/sizeof(Double_t) - 1;

  TH1D* h2 = new TH1D("hist_new", "", nx, dx);
  h2->Draw("same");
  h3->Draw("same");
  SetAxis(h2, YMin, YMax, 0.6, 16.);

  //Fit h3 w/ levy function
  //-----------------------------------
  TF1* fLevyFunc = new TF1("fLevyFunc",  "[0]*(([1]-1)*([1]-2)/([1]*[2]*([1]*[2]+1.32171*([1]-2))))*x*TMath::Power(1+((TMath::Sqrt(1.32171*1.32171+x*x)-1.32171)/([1]*[2])), -[1])", 5., 7.7);
  //LevyFunc->SetParameter(0, ); 
  fLevyFunc->SetParameter(0, 3.77338e-03);
  fLevyFunc->SetParameter(1, 9.90304e+08);
  fLevyFunc->SetParameter(2, 5.80704e-01);
  h3->Fit("fLevyFunc","R");//, "QREM0");
  Double_t dChisquare = fLevyFunc->GetChisquare();
  Double_t       dNDF = fLevyFunc->GetNDF();
  Double_t dChisOverNDF = dChisquare/dNDF;

  TF1* fLevyFitFunc = new TF1("fLevyFitFunc",  "[0]*(([1]-1)*([1]-2)/([1]*[2]*([1]*[2]+1.32171*([1]-2))))*x*TMath::Power(1+((TMath::Sqrt(1.32171*1.32171+x*x)-1.32171)/([1]*[2])), -[1])", 0., 40.);
  fLevyFitFunc->FixParameter(0, fLevyFunc->GetParameter(0));
  fLevyFitFunc->FixParameter(1, fLevyFunc->GetParameter(1));
  fLevyFitFunc->FixParameter(2, fLevyFunc->GetParameter(2));
  fLevyFitFunc->Draw("same"); 

  //cout<<dChisOverNDF<<endl;
  //fLevyFunc->Draw("same");

  //Extend the bin content(mean value)
  //-----------------------------------
  for (Int_t k=1; k<=h3->GetNbinsX(); k++){
    h2->SetBinContent(k, h3->GetBinContent(k));
    h2->SetBinError(k, h3->GetBinError(k));
  }
  for (Int_t k=h3->GetNbinsX()+1; k<=h2->GetNbinsX(); k++){
    Double_t dVal = (fLevyFunc->Integral(h2->GetBinLowEdge(k), h2->GetBinLowEdge(k+1)))/(h2->GetBinWidth(k));
    //Double_t dErr = ();
    cout<<dVal<<endl;
    h2->SetBinContent(k, dVal);
  }
  h2->Draw("same");

  //Extend the bin error(sigma value)
  //-----------------------------------
  //for (Int_t k = 0; k<1000; k++){
  //  TH1D* hRandom = new TH1D(Form("hRandom_%d", k), "", nx, dx);
  //  for (Int_t i=1; i<=h1->GetNbinsX(); i++){
  //    Double_t dVarH1 = h1->GetBinContent(i);
  //    Double_t dErrH1 = h1->GetBinError(i);
  //    Double_t dRand  = gRandom->Gaus(dVarH1, dErrH1);
  //    hRandom->SetBinContent(i, dRand);
  //  }
  //  hRandom->Draw("same");
  //  hRandom->Fit("fLevyFunc","R");
  //  TF1* fLevyFitFunc = new TF1(Form("fLevyFitFunc_%d", k),  "[0]*(([1]-1)*([1]-2)/([1]*[2]*([1]*[2]+1.32171*([1]-2))))*x*TMath::Power(1+((TMath::Sqrt(1.32171*1.32171+x*x)-1.32171)/([1]*[2])), -[1])", 0., 40.);
  //  fLevyFitFunc->FixParameter(0, fLevyFunc->GetParameter(0));
  //  fLevyFitFunc->FixParameter(1, fLevyFunc->GetParameter(1));
  //  fLevyFitFunc->FixParameter(2, fLevyFunc->GetParameter(2));
  //  fLevyFitFunc->Draw("same");

  c1->SetLogy();

  //TFile *file = TFile::Open(Form("./result/%s.root", sSaveName.Data()), "UPDATE");
  //file->cd(); 
  //fLevyFitFunc->Write(sFuncName, TObject::kSingleKey);
  //h2->Write(sHistName, TObject::kSingleKey);
  //file->Close();

  return;
}
