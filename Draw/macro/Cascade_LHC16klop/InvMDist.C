#include"../../SourceFun.h"

//==================================================================
void InvMDist(){
  TString sRootFilePath = "/home/cuipengyao/study/code/cascade_LHC15f_pass2_test/JC_Eta_CombineXi";
  TString sRootFileName = "AnalysisOutputs_FitInvMrd.root";

  //TString    sListNameK = "";
  TString    sListNameL = "";
  TString   sListNameAn = "";

  TString    sListNameK = "listFitInvMrd_Kshort_Default;1";
  //TString    sListNameL = "listFitInvMrd_Lambda_Default;1";
  //TString   sListNameAn = "listFitInvMrd_AntiLa_Default;1";
  TString       sObject = "hFitPtInvM";

  TCanvas*   tV0sPt = new TCanvas("tV0sPt", "");
  TLegend* leg = new TLegend(0.78,0.73,0.9,0.85);

  if (!sListNameK.IsNull()) {
    TH1D* hPtKshort = (TH1D*)GetTH1FromFile(sRootFilePath, sRootFileName, sListNameK, sObject);
    leg->SetHeader("K_{S}^{0}");
    SetAxisStyle(hPtKshort,"#it{p}_{T}(GeV/c)", "");
    SetLineStyle(hPtKshort, kBlack, kBlack, 21, 0.488, 0.508,0.6, 12,"Inv. Mass(GeV/c)");
    hPtKshort->Draw("same");
    //SetLineStyle(hPtKshort, kBlack, kBlack, 21, 0, 6e4,0.42, 0.58,"Inv. Mass(GeV/c)");
  }

  if (!sListNameL.IsNull()){
    TH1D* hPtLambda = (TH1D*)GetTH1FromFile(sRootFilePath, sRootFileName, sListNameL, sObject);
    //hPtLambda->Draw("same"); 
    SetAxisStyle(hPtLambda,"#it{p}_{T}(GeV/c)", "Inv. Mass(GeV/c)");
    SetLineStyle(hPtLambda, kBlack, kBlack, 23, 1.112, 1.120,0.6,12,"Inv. Mass(GeV/c)");
    hPtLambda->Draw("same");
    leg->SetHeader("#Lambda"); 
  }

  if (!sListNameAn.IsNull()){
    TH1D* hPtAntiLa = (TH1D*)GetTH1FromFile(sRootFilePath, sRootFileName, sListNameAn, sObject);
    NormBinSize(hPtAntiLa);
    //hPtAntiLa->Draw("same"); 
    SetLineStyle(hPtAntiLa, kRed, kBlack, 4, YMin, YMax);
    hPtAntiLa->Draw("same");
    leg->AddEntry(hPtAntiLa,"#bar{#Lambda}","lp");
  }
  gStyle ->SetOptStat("");
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->Draw();

}
                       
