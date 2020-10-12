#include "../../SourceFun.h"

//___________________________________________________________________
void Compare_Eff(){
  TString sType[] = {"XiMinus", "XiPlus"};//"XiPlus"; "XiMinus"

  TString   sCone = "JC"; //"JC"; "PCL"; "PCU"; "OC"; "NJ"
  Bool_t IsJC(0); 

  TString sPath[] = {"/home/cuipengyao/study/code/Cascade_LHC15f_pass2/Eff_JC", "/home/cuipengyao/study/code/Cascade_LHC15f_pass2/Eff_JC_Pri"};
//==================================================================
  TString  sObject = "hPtEffi";

  Double_t YMin = -0.1;
  Double_t YMax = 0.6;
  Double_t XMin = 0.6;
  Double_t XMax = 6.5;
//==================================================================
  TCanvas* c1 = new TCanvas("c1", "");
  TLegend* leg = new TLegend(0.8,0.8,0.99,0.99);

  TString sFileName = ""; 
  TString sListName = "";

  const Int_t nType  = sizeof(sType)/sizeof(TString);
  for(Int_t i=0; i<nType; i++) {
    TString      sOpt = sType[i];
    TString sFilePath = sPath[i];
    if(IsJC){
      sFileName = "AnalysisOutputs_EffCorrJE.root";
      sListName = Form("listEffCorrJE_%s_Default_PtJ22_%s;1", sOpt.Data(), sCone.Data());
    }else{
      sFileName = "AnalysisOutputs_EffCorrMC.root";
      sListName = Form("listEffCorrMC_%s_Default;1", sOpt.Data());
    }

    TH1D* hEff = (TH1D*)GetTH1FromList(sFilePath, sFileName, sListName, sObject);
    if (!hEff) return 0x0;
    SetLine(hEff, cLine[i],sMark[i]);
    SetAxis(hEff, YMin, YMax, XMin, XMax, "Efficiency");
    hEff->Draw("same");
    if (sOpt == "XiPlus"  && i == 0 ) leg->AddEntry(hEff,"PhyPri #Xi^{+}","lp");
    if (sOpt == "XiPlus"  && i == 1 ) leg->AddEntry(hEff,"Pri #Xi^{+}","lp");
    if (sOpt == "XiMinus" && i == 0 ) leg->AddEntry(hEff,"PhyPri #Xi^{-}","lp");
    if (sOpt == "XiMinus" && i == 1 ) leg->AddEntry(hEff,"Pri #Xi^{-}","lp");
  }
  TLatex* tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  SetCanv(c1);
  SetLegend(leg);
  SetStyle();
  if(IsJC)  tex->DrawLatex(0.16, 0.91, Form("13 TeV %s #Xi efficiency",sCone.Data()));
  if(!IsJC) tex->DrawLatex(0.16, 0.91, "13 TeV inclusive #Xi efficiency");
  leg->Draw();
}

