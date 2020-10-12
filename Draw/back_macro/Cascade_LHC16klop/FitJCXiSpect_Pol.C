#include <TF1.h>
#include "../../SourceFun.h"

void FitJCXiSpect(){

  TString sSaveName = "FitPtSpect_JC";
  TString sFuncName = "FitFunc_Xi";
  TString sHistName = "Hist_Xi";

  TString sPath = "/home/cuipengyao/study/code/Draw/macro/Cascade_WJet_LHC16k/result";
  TString sFile = "PtSpect_Xipm_wo_Norm.root";
  TString sHist = "hPtJC_Xi";
/*Double_t   YMin = 1e-8;
  Double_t   YMax = 1e8;*/
  Double_t   YMin = 1;
  Double_t   YMax = 300.;
  //-----------------------------------
    
  TH1D* h1 = (TH1D*)GetTH1FromFile(sPath, sFile, sHist);
  h1->SetName("hist"); 
  Double_t dx[] = { 0.6, 0.8, 1.0, 1.2, 1.4, 1.6, 1.8, 2.0, 2.2, 2.4, 2.6, 2.8, 3.0, 3.3, 3.6, 4.0, 4.5, 5.0, 5.5, 6.5, 7.7, 9.0, 12.};//, 15.};
  Int_t nx = sizeof(dx)/sizeof(Double_t) - 1;
  TH1D* h2 = new TH1D("hist_new", "", nx, dx);
  SetAxis(h2, YMin, YMax, 0.6, 8.);
  h2->Draw("same");
  h1->Draw("same");

  //SetLine(h1,cLine[0],sMark[0]);

  TF1* f1 = new TF1("f1", "pol1", 4., 7.7);
  //f1->SetParameter(0, 172.);
  //f1->SetParameter(1, -13.);
  h1->Fit(f1, "R");//, "QREM0");
  
  Double_t dChisquare = f1->GetChisquare();
  Double_t       dNDF = f1->GetNDF();
  Double_t dChisOverNDF = dChisquare/dNDF;
  cout<<"ChiOverNDF = "<<dChisOverNDF<<endl;

  TF1* f1Fit = new TF1("f1Fit", "pol1", 0., 40.);
  f1Fit->FixParameter(0, f1->GetParameter(0));
  f1Fit->FixParameter(1, f1->GetParameter(1));
  f1Fit->Draw("same");

  //Extend the bin content(mean value)
  //-----------------------------------
  for (Int_t k=1; k<=h1->GetNbinsX(); k++){
    h2->SetBinContent(k, h1->GetBinContent(k));
    h2->SetBinError(k, h1->GetBinError(k));
  }
  for (Int_t k=h1->GetNbinsX()+1; k<=h2->GetNbinsX(); k++){
    Double_t dVal = (f1->Integral(h2->GetBinLowEdge(k), h2->GetBinLowEdge(k+1)))/(h2->GetBinWidth(k));
    h2->SetBinContent(k, dVal);
  }

  //TFile *file = TFile::Open(Form("./result/%s.root", sSaveName.Data()), "UPDATE");
  //file->cd();
  //f1Fit->Write(sFuncName, TObject::kSingleKey);
  //h2->Write(sHistName, TObject::kSingleKey);
  //file->Close();




  c1->SetLogy();
  return;
}
