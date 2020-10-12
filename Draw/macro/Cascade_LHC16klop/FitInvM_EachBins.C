#include"../../SourceFun.h"

//==================================================================
void FitInvM_EachBins(){
  //TString sRootFilePath  = "/home/cuipengyao/study/code/Cascade_LHC15f_pass2/JC_test_everycut";
  TString sRootFilePath  = "/home/cuipengyao/study/code/Cascade_LHC16k/JC_Eta_CombineXi";
  TString  sRootFileName = "AnalysisOutputs_FitInvMrd.root";
  TString       Particle = "Xi";
  TString      sListName = Form("listFitInvMrd_%s_Default;1", Particle.Data());
  Double_t dYmin = 1.;
  Double_t dYmax = 1e4;
  Double_t dXmin = 1.25;
  Double_t dXmax = 1.45;
  
  TString  sPtBins[] = {"0.6", "0.8", "1.0", "1.2", "1.4",
                        "1.6", "1.8", "2.0", "2.2", "2.4",
                        "2.6", "2.8", "3.0", "3.3", "3.6",
                        "4.0", "4.5", "5.0", "5.5", "6.5",
                        "7.7", "9.0", "11.0"};

  TCanvas* c1 = new TCanvas("c1", "");
  TLatex*     tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(30);
  c1->Divide(4,4);
  //Int_t nBins = sizeof(sPtBins)/sizeof(TString); 
  for(Int_t i=2; i<18; i++){
    TString sObject = Form("hFitInvM_%d",i);
    c1->cd(i-1);

    TH1D* hFitInvM = (TH1D*)GetHistFromList(sRootFilePath, sRootFileName, sListName, sObject);
    SetAxis(hFitInvM,dYmin, dYmax, dXmin, dXmax, "Yeild","Inv. Mass(GeV/c)");
    SetLine(hFitInvM,kBlack,4);
    hFitInvM->SetMarkerSize(0.8);
    hFitInvM->SetLineWidth(1);
   
    hFitInvM->Draw("same");

    TF1* fS = hFitInvM->GetFunction(Form("fFitInvM_%d",i));
    fS->SetLineWidth(2);
    fS->Draw("same");

    TF1* fB = (TF1*)GetTF1FromList(sRootFilePath, "AnalysisOutputs_FitCbinRD.root", Form("listFitCbinRD_%s_Default;1", Particle.Data()), Form("fBkgVarF_%d",i));
    fB->SetLineColor(kBlue);
    fB->Draw("same");
 
    Double_t dWidth = fS->GetParameter(2);
    Double_t dMass = fS->GetParameter(1);
    SetCanv(c1);
    c1->GetPad(i-1)->SetLogy(); 
    tex->DrawLatex(0.3, 0.91, Form("#Xi^{#pm}: %s<#it{p}_{T}<%s GeV/c", sPtBins[i-1].Data(), sPtBins[i].Data()));
  }
  SetStyle();
}
