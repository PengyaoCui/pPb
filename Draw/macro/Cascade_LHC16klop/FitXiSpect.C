#include <TF1.h>
#include "SourceFun.h"

void FitXiSpect(){

  TString sSaveName = "FitXiPtSpect_Sys";
  TString sFuncName = "JE_FitFunc";
  TString sHistName = "JE_Xi";

  //TString sPath = "~/study/code/Draw/macro/Cascade_LHC16klop/result";
  //TString sFile = "PtSpect_LHC16klop.root";
  //TString sHist = "hPtJE_Xi";

  TString sPath = "~/study/code/Draw/macro/Cascade_LHC16klop/result";
  TString sFile = "XiSysErr.root";
  TString sHist = "hPtJC_Xi_Sys";

  Double_t   YMin = 1e-8;
  Double_t   YMax = 1e8;

  TString sTex = "PC #Xi";



  TH1D* h1 = (TH1D*)GetTH1FromFile(sPath, sFile, sHist);
  h1->SetName("hist");
  //Double_t dx[] = { 0.6, 0.8, 1.0, 1.2, 1.4, 1.6, 1.8, 2.0, 2.2, 2.4, 2.6, 2.8, 3.0, 3.3, 3.6, 4.0, 4.5, 5.0, 5.5, 6.5, 7.7, 9.0, 12., 15.}; 
  Double_t dx[] = { 2.0, 2.4, 2.8, 3.3, 4.0, 5.0, 6.5, 7.7, 9.0, 12., 15.}; 
  Int_t nx = sizeof(dx)/sizeof(Double_t) - 1;
  for(Int_t i =1; i<= h1->GetNbinsX(); i++){
    Double_t dvar = h1->GetBinContent(i); 
    Double_t dcent = h1->GetXaxis()->GetBinCenter(i); 
    //cout<<dcent<<"====="<<dvar<<endl;
   //cout<<i<<"==="<<h1->GetXaxis()->GetBinCenter(i)<<endl;
  }

  TH1D* h2 = new TH1D("hist_new", "", nx, dx);
  h2->Draw("same");
  h1->Draw("same");
  SetAxis(h1, YMin, YMax, 0.6, 16.);

  //Fit h1 w/ levy function
  //-----------------------------------
  TF1* fLevyFunc = new TF1("fLevyFunc",  "[0]*(([1]-1)*([1]-2)/([1]*[2]*([1]*[2]+1.32171*([1]-2))))*x*TMath::Power(1+((TMath::Sqrt(1.32171*1.32171+x*x)-1.32171)/([1]*[2])), -[1])", 2.5, 6.5);
  //LevyFunc->SetParameter(0, ); 
  fLevyFunc->SetParameter(0, 3.e-03);//3.77338e-03);
  fLevyFunc->SetParameter(1, 9.e+08);//9.90304e+08);
  fLevyFunc->SetParameter(2, 5.e-01);//5.80704e-01);
  h1->Fit("fLevyFunc","R");//, "QREM0");
  Double_t dChisquare = fLevyFunc->GetChisquare();
  Double_t       dNDF = fLevyFunc->GetNDF();
  Double_t dChisOverNDF = dChisquare/dNDF;

  TF1* fLevyFitFunc = new TF1("fLevyFitFunc",  "[0]*(([1]-1)*([1]-2)/([1]*[2]*([1]*[2]+1.32171*([1]-2))))*x*TMath::Power(1+((TMath::Sqrt(1.32171*1.32171+x*x)-1.32171)/([1]*[2])), -[1])", 0., 40.);
  fLevyFitFunc->FixParameter(0, fLevyFunc->GetParameter(0));
  fLevyFitFunc->FixParameter(1, fLevyFunc->GetParameter(1));
  fLevyFitFunc->FixParameter(2, fLevyFunc->GetParameter(2)); fLevyFitFunc->Draw("same"); 

  //cout<<dChisOverNDF<<endl;
  //fLevyFunc->Draw("same");


  //Extend the bin content(mean value)
  for (Int_t k=h1->GetNbinsX()+1; k<=h2->GetNbinsX(); k++){
    Double_t dVal = (fLevyFunc->Integral(h2->GetBinLowEdge(k), h2->GetBinLowEdge(k+1)))/(h2->GetBinWidth(k));
    Double_t dErr = TMath::Abs(fLevyFunc->Eval(h2->GetBinCenter(k))- fLevyFunc->Eval(h2->GetBinCenter(k)));
    //cout<<dVal<<endl;
    h2->SetBinContent(k, dVal);
    h2->SetBinError(k, dErr);
  }
  h2->Draw("same");

  //Extend the bin error(sigma value)
  TH1D* hRMS1 = new TH1D("hRMS1", "", 10000, 0., 10e-3);
  TH1D* hRMS2 = new TH1D("hRMS2", "", 10000, 0., 10e-3);
  TH1D* hRMS3 = new TH1D("hRMS3", "", 10000, 0., 10e-3);
  //-----------------------------------
  for (Int_t k = 0; k<1000; k++){
    TH1D* hRandom = new TH1D(Form("hRandom_%d", k), "", nx, dx);
    for (Int_t i=1; i<=h1->GetNbinsX(); i++){
      Double_t dVarH1 = h1->GetBinContent(i);
      Double_t dErrH1 = h1->GetBinError(i);
      Double_t dRand  = gRandom->Gaus(dVarH1, dErrH1);
      hRandom->SetBinContent(i, dRand);
    }
    //hRandom->Draw("same");
    hRandom->Fit("fLevyFunc","R");
    TF1* fLevyFitFunc = new TF1(Form("fLevyFitFunc_%d", k),  "[0]*(([1]-1)*([1]-2)/([1]*[2]*([1]*[2]+1.32171*([1]-2))))*x*TMath::Power(1+((TMath::Sqrt(1.32171*1.32171+x*x)-1.32171)/([1]*[2])), -[1])", 0., 40.);
    fLevyFitFunc->FixParameter(0, fLevyFunc->GetParameter(0));
    fLevyFitFunc->FixParameter(1, fLevyFunc->GetParameter(1));
    fLevyFitFunc->FixParameter(2, fLevyFunc->GetParameter(2));
    //fLevyFitFunc->Draw("same");
    hRMS1->Fill(fLevyFitFunc->Eval(h2->GetBinCenter(h1->GetNbinsX()+1))); 
    hRMS2->Fill(fLevyFitFunc->Eval(h2->GetBinCenter(h1->GetNbinsX()+2))); 
    hRMS3->Fill(fLevyFitFunc->Eval(h2->GetBinCenter(h1->GetNbinsX()+3))); 
  }

  //-----------------------------------
  for (Int_t k=1; k<=h1->GetNbinsX(); k++){
    h2->SetBinContent(k, h1->GetBinContent(k));
    h2->SetBinError(k, h1->GetBinError(k));
  }
  Double_t dVal[3] = 0; 
  Double_t dErr[3] = 0;
  dVal[0] = hRMS1->GetMean();
  dErr[0] = hRMS1->GetRMS();
  dVal[1] = hRMS2->GetMean();
  dErr[1] = hRMS2->GetRMS();
  dVal[2] = hRMS3->GetMean();
  dErr[2] = hRMS3->GetRMS();
  h2->SetBinContent(h1->GetNbinsX()+1, dVal[0]);
  h2->SetBinError(h1->GetNbinsX()+1, dErr[0]);
  h2->SetBinContent(h1->GetNbinsX()+2, dVal[1]);
  h2->SetBinError(h1->GetNbinsX()+2, dErr[1]);
  h2->SetBinContent(h1->GetNbinsX()+3, dVal[2]);
  h2->SetBinError(h1->GetNbinsX()+3, dErr[2]);
  h2->Draw("same");

  TLatex*     tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);

  c1->SetLogy();
  SetCanv(c1);
  SetStyle();
  tex->DrawLatex(0.17, 0.9, sTex);
  TFile *file = TFile::Open(Form("./result/%s.root", sSaveName.Data()), "UPDATE");
  file->cd(); 
  fLevyFitFunc->Write(sFuncName, TObject::kSingleKey);
  h2->Write(sHistName, TObject::kSingleKey);
  file->Close();

  return;
}
