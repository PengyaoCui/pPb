#include "../../SourceFun.h"

//______________________________________________________________________________________________
void TH1Ratio(){
  //Ratio("Incl");
  Ratio("JC");
  //Ratio("PC");
  //Ratio("OC");
  //Ratio("NJ");
  //Ratio("JE");
}

void Ratio(TString sReg){
  TString sRootFilePath = "/home/cuipengyao/study/code/Reproduce_V0InJet/JC_Eta";

  //TString sNumFileName = "NormSpect_J10.root";
  //TString    sNumListK = "Kshort_EffCorr;1";
  //TString   sNumListLa = "Lambda_EffCorr;1"; 
  //TString sNumListAnLa = "AntiLa_EffCorr;1";

  //TString sDenFileName = "NormSpect.root";
  //TString    sDenListK = "Kshort_EffCorr;1";
  //TString   sDenListLa = "Lambda_EffCorr;1";
  //TString sDenListAnLa = "AntiLa_EffCorr;1";

  //TString sObject = Form("hPt%s", sReg.Data());
  //TString   sText = Form("V^{0}s spectrum ratio in %s", sReg.Data());
  //if(0){
  //  TString sRootFilePath = "/home/cuipengyao/study/code/LHC15f_pass2/Eff_UE_NJ_20170306";

    TString sNumFileName = "AnalysisOutputs_EffCorrJE.root";
    TString    sNumListK = Form("listEffCorrJE_Kshort_Default_PtJ22_%s;1", sReg.Data());
    TString   sNumListLa = Form("listEffCorrJE_Lambda_Default_PtJ22_%s;1", sReg.Data());
    TString sNumListAnLa = Form("listEffCorrJE_AntiLa_Default_PtJ22_%s;1", sReg.Data());

    TString sDenFileName = "AnalysisOutputs_EffInclMC.root";
    TString    sDenListK = "listEffInclMC_Kshort_Default;1";
    TString   sDenListLa = "listEffInclMC_Lambda_Default;1";
    TString sDenListAnLa = "listEffInclMC_AntiLa_Default;1";

    TString sObject = "hPtEffi";
    TString   sText = Form("Efficiency ratio of V^{0}s in %s to inclusive", sReg.Data());
  //}
  Double_t   YMin = 0.4;
  Double_t   YMax = 1.6;
  
  TCanvas* canv = new TCanvas(sReg);
  TLegend*  leg = new TLegend(0.7,0.6,0.9,0.9);
  //leg->SetHeader(sHeader); // option "C" allows to center the header

  const Double_t dPtBin[] = {  0.6, 1.6, 2.2, 2.8, 3.7, 5.0, 8.0, 12.0};
  const Int_t      nPtBin = sizeof(dPtBin)/sizeof(Double_t)-1;
  TH1D*            hRebin = new TH1D("hRebin","",nPtBin,dPtBin);

  //-----------------------------------
  if(!sNumListK.IsNull()){
    
    TH1D* hNumK = (TH1D*)GetHistFromList(sRootFilePath, sNumFileName, sNumListK, sObject);
    hNumK->SetName("hNumKshort");
    hNumK = (TH1D*)RebinTH1D(hNumK, hRebin);
  
    TH1D* hDenK = (TH1D*)GetHistFromList(sRootFilePath, sDenFileName, sDenListK, sObject);
    hDenK->SetName("hDenKshort");
    hDenK = (TH1D*)RebinTH1D(hDenK, hNumK);
   
    //hNumK->Divide(hDenK);
    hNumK = (TH1D*)RatioTH1D(hNumK,hDenK);
    hNumK->SetName("hKshort");
    SetLine(hNumK, kBlack, 20);
    SetAxis(hNumK, YMin, YMax, 0.6, 12, "Ratio");
    hNumK->Draw("same");
    leg->AddEntry(hNumK,"K_{S}^{0}","lp");
  }
  //------------------------------------
  if(!sNumListLa.IsNull()){
    
    TH1D* hNumLa = (TH1D*)GetHistFromList(sRootFilePath, sNumFileName, sNumListLa, sObject);
    hNumLa->SetName("hNumLambada");
    hNumLa = (TH1D*)RebinTH1D(hNumLa, hRebin);
    
    TH1D* hDenLa = (TH1D*)GetHistFromList(sRootFilePath, sDenFileName, sDenListLa, sObject);
    hDenLa->SetName("hDenLambda");
    hDenLa = (TH1D*)RebinTH1D(hDenLa, hNumLa);
   
    //hNumLa->Divide(hDenLa);
    hNumLa = (TH1D*)RatioTH1D(hNumLa, hDenLa);
    hNumLa->SetName("hLambda");
    SetLine(hNumLa, kBlue, 24);
    hNumLa->Draw("same");
    leg->AddEntry(hNumLa,"#Lambda","lp");
  }
  //------------------------------------
  if(!sNumListAnLa.IsNull()){
    
    TH1D* hNumAnLa = (TH1D*)GetHistFromList(sRootFilePath, sNumFileName, sNumListAnLa, sObject);
    hNumAnLa->SetName("hNumAntiLambada");
    hNumAnLa = (TH1D*)RebinTH1D(hNumAnLa, hRebin);
    
    TH1D* hDenAnLa = (TH1D*)GetHistFromList(sRootFilePath, sDenFileName, sDenListAnLa, sObject);
    hDenAnLa->SetName("hDenAntiLambda");
    hDenAnLa = (TH1D*)RebinTH1D(hDenAnLa, hNumAnLa);
   
    //hNumAnLa->Divide(hDenAnLa);
    hNumAnLa = (TH1D*)RatioTH1D(hNumAnLa, hDenAnLa);
    hNumAnLa->SetName("hAntiLambda");
    SetLine(hNumAnLa, kRed, 25);
    hNumAnLa->Draw("same");
    leg->AddEntry(hNumAnLa,"#bar{#Lambda}","lp");
  }
  //------------------------------------
  TLatex*     tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.16, 0.91, sText);

  SetCanv(canv);
  SetLegend(leg);
  SetStyle();
  leg->Draw();
} 
  

//_________________________________________________________________________________________________
void Ratio13to7(){
  TString sRootFilePath13 = "/home/cuipengyao/study/code/LHC15f_pass2/Local";
  TString  sRootFilePath7 = "/home/cuipengyao/study/code/LHC10d/Local"; 
  TString   sRootFileName = "AnalysisOutputs_FitInvMrd.root";
  TString       sListName = "listFitInvMrd_Kshort_Default;1";
  TString         sObject = "hPt";
  Double_t           YMin = 1;
  Double_t           YMax = 1.6;

  TH1D* hPtKShort13 = (TH1D*)GetHistFromList(sRootFilePath13, sRootFileName, sListName, sObject);
  NormBinSize(hPtKShort13);
  hPtKShort13->SetName("Kshort13");
  Double_t    dEvent13 = GetEventNum(sRootFilePath13);
  cout<<"dEvent13"<<"="<<dEvent13<<endl;
  hPtKShort13->Scale(1/dEvent13); 
  //for (Int_t k=0; k<= hPtKShort13->GetNbinsX(); k++){
     // Double_t  dPtK = hPtKShort13->GetBinContent(k)/iEvent13;
     // hPtKShort13 ->SetBinContent(k,dPtK);
  //} 

  TH1D* hPtKShort7 = (TH1D*)GetHistFromList(sRootFilePath7, sRootFileName, sListName, sObject);
  NormBinSize(hPtKShort7);
  hPtKShort7->SetName("Kshort7");
  Double_t   dEvent7  = GetEventNum(sRootFilePath7);
  cout<<"dEvent7"<<"="<<dEvent7<<endl;
  hPtKShort7->Scale(1/dEvent7); 

  hPtKShort13->Divide(hPtKShort7);
  hPtKShort13->SetName("#it{p}_{T} Ratio 13 TeV to 7 TeV");
//  TH1D*     hRatio = Ratio(hPtKShort13, hPtKShort7,"#it{p}_{T} Ratio 13 TeV to 7 TeV");
  //hPtKShort13->Draw();
  SetLineStyle(hPtKShort13, kBlack, kBlue, 21, YMin, YMax);
  hPtKShort13->Draw("same");
}

