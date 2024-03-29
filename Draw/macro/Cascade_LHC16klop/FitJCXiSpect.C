#include <TF1.h>
#include "../../SourceFun.h"

void FitJCXiSpect(){

  TString sSaveName = "FitPtSpect_JC_LevyFit";
  TString sFuncName = "FitFunc_Xi";
  TString sHistName = "Hist_Xi";

  TString sPath = "/home/cuipengyao/study/code/Draw/macro/Cascade_WJet_LHC16k/result";
  TString sFile = "PtSpect_Xipm_wo_Norm.root";
  TString sHist = "hPtIncl_Xi";
  Double_t   YMin = 1;
  Double_t   YMax = 300.;
  //-----------------------------------
    
  TH1D* h1 = (TH1D*)GetTH1FromFile(sPath, sFile, sHist);
  h1->SetName("hist"); 
  Double_t dx[] = { 0.6, 0.8, 1.0, 1.2, 1.4, 1.6, 1.8, 2.0, 2.2, 2.4, 2.6, 2.8, 3.0, 3.3, 3.6, 4.0, 4.5, 5.0, 5.5, 6.5, 7.7, 9.0, 12., 15.};
  Int_t nx = sizeof(dx)/sizeof(Double_t) - 1;
  TH1D* h2 = new TH1D("hist_new", "", nx, dx);
  SetAxis(h2, YMin, YMax, 0.6, 15.);
  h2->Draw("same");
  h1->Draw("same");

  //Fit h1 w/ levy function
  //-----------------------------------
  TF1* fLevyFunc = new TF1("fLevyFunc",  "[0]*(([1]-1)*([1]-2)/([1]*[2]*([1]*[2]+1.32171*([1]-2))))*x*TMath::Power(1+((TMath::Sqrt(1.32171*1.32171+x*x)-1.32171)/([1]*[2])), -[1])", 2.5, 7.7);
  //LevyFunc->SetParameter(0, ); 
  fLevyFunc->SetParameter(0, 828);
  fLevyFunc->SetParameter(1, 7.8e+06 );
  fLevyFunc->SetParameter(2, 1.8);
  h1->Fit("fLevyFunc", "R");//, "QREM0");
  Double_t dChisquare = fLevyFunc->GetChisquare();
  Double_t       dNDF = fLevyFunc->GetNDF();
  Double_t dChisOverNDF = dChisquare/dNDF;
  cout<<"ChiOverNDF = "<<dChisOverNDF<<endl;
  fLevyFunc->Draw("SAME");
  TF1* fLevyFitFunc = new TF1("fLevyFitFunc",  "[0]*(([1]-1)*([1]-2)/([1]*[2]*([1]*[2]+1.32171*([1]-2))))*x*TMath::Power(1+((TMath::Sqrt(1.32171*1.32171+x*x)-1.32171)/([1]*[2])), -[1])", 0., 40.);
  fLevyFitFunc->FixParameter(0, fLevyFunc->GetParameter(0));
  fLevyFitFunc->FixParameter(1, fLevyFunc->GetParameter(1));
  fLevyFitFunc->FixParameter(2, fLevyFunc->GetParameter(2));
  fLevyFitFunc->Draw("same"); 

  cout<<dChisOverNDF<<endl;
  fLevyFunc->Draw("same");

  //Extend the bin content(mean value)
  //-----------------------------------
  for (Int_t k=1; k<=h1->GetNbinsX(); k++){
    h2->SetBinContent(k, h1->GetBinContent(k));
    h2->SetBinError(k, h1->GetBinError(k));
  }
  for (Int_t k=h1->GetNbinsX()+1; k<=h2->GetNbinsX(); k++){
    Double_t dVal = (fLevyFunc->Integral(h2->GetBinLowEdge(k), h2->GetBinLowEdge(k+1)))/(h2->GetBinWidth(k));
    h2->SetBinContent(k, dVal);
  }

  //TFile *file = TFile::Open(Form("./result/%s.root", sSaveName.Data()), "UPDATE");
  //file->cd();
  //fLevyFitFunc->Write(sFuncName, TObject::kSingleKey);
  //h2->Write(sHistName, TObject::kSingleKey);
  //file->Close();


  c1->SetLogy();
  return;
}
