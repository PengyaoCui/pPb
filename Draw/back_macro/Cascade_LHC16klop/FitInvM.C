#include"../../SourceFun.h"

//==================================================================
void FitInvM(){
  TString sRootFilePath  = "/home/cuipengyao/study/code/Cascade_LHC16klop_total/Local";
  TString  sRootFileName = "AnalysisOutputs_FitInvMrd.root";
  TString       Particle = "Xi";
  TString      sListName = Form("listFitInvMrd_%s_Default;1", Particle.Data());

  Double_t dYmin = 1.;
  Double_t dYmax = 1.e4;
  Double_t dXmin = 1.25;
  Double_t dXmax = 1.45;

  TString  sPtBins[] = {"0.6", "0.8", "1.0", "1.2", "1.4",
                        "1.6", "1.8", "2.0", "2.2", "2.4",
                        "2.6", "2.8", "3.0", "3.3", "3.6",
                        "4.0", "4.5", "5.0", "5.5", "6.5",
                        "7.7"};


  
  for(Int_t i=4; i<5; i++){
    TString sObject = Form("hFitInvM_%d",i);
    
    TCanvas* c1 = new TCanvas(Form("c1_%d",i), "");
    TLatex*     tex = new TLatex();
    tex->SetNDC();
    tex->SetTextSizePixels(24);

    TH1D* hFitInvM = (TH1D*)GetHistFromList(sRootFilePath, sRootFileName, sListName, sObject);
    SetAxis(hFitInvM,dYmin, dYmax, dXmin, dXmax, "Yeild","Inv. Mass(GeV/#it{c}^{2})");
    SetLine(hFitInvM,kBlack,4);
    hFitInvM->Draw("same");
    TLegend*    leg = new TLegend(0.6,0.6,0.9,0.9);
    leg->AddEntry((TObject*)0, Form("#Xi^{#pm}: %s<#it{p}_{T}<%s GeV/c", sPtBins[i-1].Data(), sPtBins[i].Data()) ,"");

    TF1* fS = hFitInvM->GetFunction(Form("fFitInvM_%d",i));
    fS->SetLineWidth(2);
    fS->Draw("same");

    TF1* fB = (TF1*)GetTF1FromList(sRootFilePath, "AnalysisOutputs_FitCbinRD.root", Form("listFitCbinRD_%s_Default;1", Particle.Data()), Form("fBkgVarF_%d",i));
    fB->SetLineColor(kBlue);
    fB->Draw("same");
 
    Double_t dWidth = fS->GetParameter(2);
    Double_t dMass = fS->GetParameter(1);
    TLine*   lLMin = new TLine(dMass-12*dWidth,0, dMass-12*dWidth, 8000);
    lLMin->SetLineColor(kGreen);
    lLMin->SetLineWidth(2);
    lLMin->Draw("same");

    TLine*   lLMax = new TLine(dMass-6*dWidth, 0, dMass-6*dWidth, 8000);
    lLMax->SetLineWidth(2);
    lLMax->Draw("same");

    TLine*   lSMax = new TLine(dMass+3*dWidth, 0, dMass+3*dWidth, 8000);
    lSMax->SetLineColor(kOrange);
    lSMax->SetLineWidth(2);
    lSMax->Draw("same");

    TLine*   lSMin = new TLine(dMass-3*dWidth, 0, dMass-3*dWidth, 8000);
    lSMin->SetLineColor(kOrange);
    lSMin->SetLineWidth(2);
    lSMin->Draw("same");

    TLine*   lRMin = new TLine(dMass+6*dWidth, 0, dMass+6*dWidth, 8000);
    lRMin->SetLineWidth(2);
    lRMin->Draw("same");

    TLine*   lRMax = new TLine(dMass+12*dWidth,0, dMass+12*dWidth, 8000);
    lRMax->SetLineColor(kGreen);
    lRMax->SetLineWidth(2);
    lRMax->Draw("same");
    tex->DrawLatex(0.16, 0.91, "p-p collisions at #sqrt{s}=13 TeV, Data");
  SetCanv(c1);
  c1->SetLogy(); 
  }
  SetStyle();
  SetLegend(leg);
  leg->Draw();
}
