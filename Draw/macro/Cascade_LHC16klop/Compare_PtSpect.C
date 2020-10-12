#include "../../SourceFun.h"

//___________________________________________________________________
void Compare_PtSpect(){
  TString sType[] = {"XiMinus", "XiPlus"};//"XiPlus"; "XiMinus"

  Bool_t IsEffCorr(1);
  
  Bool_t IsAnaIncl(1);
  Bool_t   IsAnaJC(0);
  Bool_t   IsAnaJE(0);
  Bool_t   IsAnaPC(0);
  Bool_t   IsAnaOC(0);
  Bool_t   IsAnaNJ(0);

  Bool_t   IsSave(0);
  Bool_t  IsRebin(0);
//===================================================================
  TString sPath[] = {"/home/cuipengyao/study/code/Cascade_LHC15f_pass2/Eff_JC", "/home/cuipengyao/study/code/Cascade_LHC15f_pass2/Eff_JC_Pri"};
  //TString sEventFilePath = "/home/cuipengyao/study/code/Cascade_LHC15f_pass2/JC";

//===================================================================
  TString sInclEventFile = "AnalysisOutputs_Loop1ndRD.root";
  TString  sJetEventFile = "AnalysisOutputs_LoopJetRD.root";

//-------------------------------------------------------------------
  TString sInclSpectFile = "AnalysisOutputs_FitCbinRD.root";
  TString   sEffInclFile = "AnalysisOutputs_EffInclMC.root";
  TString  sJetSpectFile = "AnalysisOutputs_FitCbinJE.root";
  TString    sEffJetFile = "AnalysisOutputs_EffCorrJE.root";
//===================================================================

  TString      sEvent = "hEvent";
//-------------------------------------------------------------------
  TString sObject = "hS";
  TString    sEff = "hPtEffi";
//===================================================================
  Double_t YMin = 1e-5;
  Double_t YMax = 1e0;
  Double_t XMin = 0.6;
  Double_t XMax = 6.5;
  
//-------------------------------------------------------------------
  TCanvas*  c1 = new TCanvas("c1", "");
  TLegend* leg = new TLegend(0.7,0.7,0.9,0.9);
//-------------------------------------------------------------------
  if(IsSave){
    TFile *file = TFile::Open("./result/RebinPtSpect.root", "UPDATE");
    TList *list = (TList*)file->Get(sOpt.Data()); if (list) { file->Close(); return; } else { list = new TList(); }
  }
//-------------------------------------------------------------------
  
  if(IsRebin){
    const Double_t dPtBin[] = {  0.6, 1.6, 2.2, 2.8, 3.7, 5.0, 8.0, 12.0};
    const Int_t nPtBin = sizeof(dPtBin)/sizeof(Double_t)-1;
    TH1D* hRebin = new TH1D("hRebin","",nPtBin,dPtBin);
    // hPtPCL = (TH1D*)RebinTH1D(hPtPCL, hRebin);
  }
  const Int_t nType  = sizeof(sType)/sizeof(TString);

  for(Int_t i=0; i<nType; i++) {
    TString           sOpt = sType[1];
    TString sEventFilePath = sPath[i];
  //-------------------------------------------------------------------
    TString sInclEventList = Form("listLoop1ndRD_%s_Default;1",sOpt.Data());
    TString  sJetEventList = Form("listLoopJetRD_%s_Default_PtJ22_JC;1",sOpt.Data());
    TString   sListNJEvent = Form("listLoopJetRD_%s_Default_PtJ22_NJ",sOpt.Data());
  //-------------------------------------------------------------------
  
    TString  sListIncl = Form("listFitCbinRD_%s_Default;1",sOpt.Data());
    TString    sListJC = Form("listFitCbinJE_%s_Default_PtJ22_JC;1",sOpt.Data());
    TString   sListPCL = Form("listFitCbinJE_%s_Default_PtJ22_PCL;1",sOpt.Data());
    TString   sListPCU = Form("listFitCbinJE_%s_Default_PtJ22_PCU;1",sOpt.Data());
    TString    sListOC = Form("listFitCbinJE_%s_Default_PtJ22_OC;1",sOpt.Data());
    TString    sListNJ = Form("listFitCbinJE_%s_Default_PtJ22_NJ;1",sOpt.Data());
  
    TString   sEffIncl = Form("listEffInclMC_%s_Default;1",sOpt.Data());
    TString     sEffJC = Form("listEffCorrJE_%s_Default_PtJ22_JC;1",sOpt.Data());
    TString    sEffPCL = Form("listEffCorrJE_%s_Default_PtJ22_PCL;1",sOpt.Data());
    TString    sEffPCU = Form("listEffCorrJE_%s_Default_PtJ22_PCU;1",sOpt.Data());
    TString     sEffOC = Form("listEffCorrJE_%s_Default_PtJ22_OC;1",sOpt.Data());
    TString     sEffNJ = Form("listEffCorrJE_%s_Default_PtJ22_NJ;1",sOpt.Data());
  
  //===================================================================
    if (IsAnaIncl){
      if (sEventFilePath.IsNull() || sInclEventFile.IsNull() || sInclEventList.IsNull() || sEvent.IsNull()) return;
      TH1D* hInclEvent = (TH1D*)GetHistFromList(sEventFilePath, sInclEventFile, sInclEventList, sEvent);
    }
    if (IsAnaJC || IsAnaPC || IsAnaOC || IsAnaJE){
      if (sEventFilePath.IsNull() || sJetEventFile.IsNull() || sJetEventList.IsNull() || sEvent.IsNull()) return;
      TH1D* hJetEvent = (TH1D*)GetHistFromList(sEventFilePath, sJetEventFile, sJetEventList, sEvent);
    }
  
    if (IsAnaNJ){
      if (sEventFilePath.IsNull() || sJetEventFile.IsNull() || sListNJEvent.IsNull() || sEvent.IsNull()) return;
      TH1D* hNJEvent = (TH1D*)GetHistFromList(sEventFilePath, sJetEventFile, sListNJEvent, sEvent);
    }
  
  //-------------------------------------------------------------------
  
    if (IsAnaIncl){
      if (sListIncl.IsNull() || sEffIncl.IsNull()) return;
      TH1D*  hPtIncl = (TH1D*)GetHistFromList(sEventFilePath, sInclSpectFile, sListIncl, sObject);
      hPtIncl->SetName("hPtIncl");
      if (IsEffCorr) TH1D* hEffIncl = (TH1D*)GetHistFromList(sEventFilePath, sEffInclFile, sEffIncl, sEff);
      NormBinSize(hPtIncl);
      hPtIncl = NormIncl(hPtIncl, hInclEvent);
      cout<<"Incl Err "<<hPtIncl->GetBinError(5)<<endl;
      cout<<"CPY Inclusive1  "<<hPtIncl->GetBinContent(5)<<endl;
      if (IsEffCorr) hPtIncl = RatioTH1D(hPtIncl, hEffIncl);
      cout<<"CPY Inclusive2  "<<hPtIncl->GetBinContent(5)<<endl;
      if(IsSave) {list->Add(hPtIncl);}
      SetLine(hPtIncl,cLine[i],sMark[i]);
      SetAxis(hPtIncl, YMin, YMax, XMin, XMax);
      hPtIncl->Draw("same");
      if (sOpt == "XiPlus"  && i == 0)  leg->AddEntry(hPtIncl,"Inclsive Phy #Xi^{+}","lp");
      if (sOpt == "XiPlus"  && i == 1)  leg->AddEntry(hPtIncl,"Inclsive Pri #Xi^{+}","lp");
      if (sOpt == "XiMinus" && i == 0)  leg->AddEntry(hPtIncl,"Inclsive Phy #Xi^{-}","lp");
      if (sOpt == "XiMinus" && i == 1)  leg->AddEntry(hPtIncl,"Inclsive Pri #Xi^{-}","lp");
    }
  
    if (IsAnaJC){
      if (sListJC.IsNull() || sEffJC.IsNull()) return;
      TH1D*  hPtJC = (TH1D*)GetHistFromList(sEventFilePath, sJetSpectFile, sListJC, sObject);
      NormBinSize(hPtJC);
      if (IsRebin) hPtJC = (TH1D*)RebinTH1D(hPtJC, hRebin);
      if (IsEffCorr) TH1D* hEffJC = (TH1D*)GetHistFromList(sEventFilePath, sEffJetFile, sEffJC, sEff);
      if (IsRebin && IsEffCorr) hEffJC = (TH1D*)RebinTH1D(hEffJC, hRebin);
      hPtJC->SetName("hPtJC");
  
      hPtJC = NormJC(hPtJC, hJetEvent);
      cout<<"CPY JC1  "<<hPtJC->GetBinContent(5)<<endl;
      if (IsEffCorr) hPtJC = RatioTH1D(hPtJC, hEffJC);
      cout<<"CPY JC2  "<<hPtJC->GetBinContent(5)<<endl;
      if(IsSave) {list->Add(hPtJC);}
      SetLine(hPtJC,cLine[i+nType],sMark[i+nType]);
      SetAxis(hPtJC, YMin, YMax, XMin, XMax);
      hPtJC->Draw("same");
      if (sOpt == "XiPlus")  leg->AddEntry(hPtJC,"JC #Xi^{+}","lp");
      if (sOpt == "XiMinus") leg->AddEntry(hPtJC,"JC #Xi^{-}","lp");
    }
  
    if (IsAnaPC){
      if (sListPCL.IsNull() || sListPCU.IsNull() || sEffPCL.IsNull() || sEffPCU.IsNull()) return;
      TH1D*  hPtPCL = (TH1D*)GetHistFromList(sEventFilePath, sJetSpectFile, sListPCL, sObject);
      hPtPCL->SetName("hPtPCL");
      NormBinSize(hPtPCL);
      if (IsRebin) hPtPCL = (TH1D*)RebinTH1D(hPtPCL, hRebin);
      if (IsEffCorr) TH1D* hEffPCL = (TH1D*)GetHistFromList(sEventFilePath, sEffJetFile, sEffPCL, sEff);
      if (IsRebin && IsEffCorr) hEffPCL = (TH1D*)RebinTH1D(hEffPCL, hRebin);
  
      TH1D*  hPtPCU = (TH1D*)GetHistFromList(sEventFilePath, sJetSpectFile, sListPCU, sObject);
      hPtPCU->SetName("hPtPCU");
      NormBinSize(hPtPCU);
      if (IsRebin) hPtPCU = (TH1D*)RebinTH1D(hPtPCU, hRebin);
      if (IsEffCorr) TH1D* hEffPCU = (TH1D*)GetHistFromList(sEventFilePath, sEffJetFile, sEffPCU, sEff);
      if (IsRebin && IsEffCorr) hEffPCU = (TH1D*)RebinTH1D(hEffPCU, hRebin);
  
      if (IsEffCorr) hPtPCL = RatioTH1D(hPtPCL, hEffPCL);
      if (IsEffCorr) hPtPCU = RatioTH1D(hPtPCU, hEffPCU);
      TH1D* hPtPC = NormPC(hPtPCL, hPtPCU, hJetEvent);
      hPtPC->SetName("hPtPC");
      cout<<"CPY PC  "<<hPtPC->GetBinContent(5)<<endl;
      if(IsSave) {list->Add(hPtPC);}
      //SetLine(hPtPC,kRed,24);
      SetLine(hPtPC,cLine[i+2*nType],sMark[i+2*nType]);
      SetAxis(hPtPC, YMin, YMax, XMin, XMax);
      hPtPC->Draw("same");
      if (sOpt == "XiPlus")  leg->AddEntry(hPtPC,"PC #Xi^{+}","lp");
      if (sOpt == "XiMinus") leg->AddEntry(hPtPC,"PC #Xi^{-}","lp");
      //leg->AddEntry(hPtPC,"PC","lp");
    }
  
    if (IsAnaJE){
      if (!hPtJC || !hPtPC) return;
      TH1D* hPtJE = hPtJC->Clone("hPtJE");
      hPtJE->SetName("hPtJE");
      TH1D* hPtUE = hPtPC->Clone("hPtUE");
      hPtUE->SetName("hPtUE");
      hPtJE = (TH1D*)Subtract(hPtJE, hPtUE);
      cout<<"JE Err "<<hPtJE->GetBinError(5)<<endl;
      if(IsSave) {list->Add(hPtJE);}
      //SetLine(hPtJE,kBlue,25);
      SetLine(hPtJE,cLine[i+3*nType],sMark[i+3*nType]);
      hPtJE->Draw("same");
      if (sOpt == "XiPlus")  leg->AddEntry(hPtJE,"JE #Xi^{+}","lp");
      if (sOpt == "XiMinus") leg->AddEntry(hPtJE,"JE #Xi^{-}","lp");
      //leg->AddEntry(hPtJE,"JE","lp");
  
    }
  
    if (IsAnaOC){
      if (sListOC.IsNull() || sEffOC.IsNull()) return;
      TH1D*  hPtOC = (TH1D*)GetHistFromList(sEventFilePath, sJetSpectFile, sListOC, sObject);
      NormBinSize(hPtOC);
      if (IsRebin) hPtOC = (TH1D*)RebinTH1D(hPtOC, hRebin);
      if (IsEffCorr) TH1D* hEffOC = (TH1D*)GetHistFromList(sEventFilePath, sEffJetFile, sEffOC, sEff);
      if (IsRebin && IsEffCorr) hEffOC = (TH1D*)RebinTH1D(hEffOC, hRebin);
      hPtOC->SetName("hPtOC");
    
      TH1D* hPtOC = NormOC(hPtOC, hJetEvent);
      cout<<"CPY OC1  "<<hPtOC->GetBinContent(5)<<endl;
      if (IsEffCorr) hPtOC = RatioTH1D(hPtOC, hEffOC);
      cout<<"CPY OC2  "<<hPtOC->GetBinContent(5)<<endl;
      if(IsSave) {list->Add(hPtOC);}
      //SetLine(hPtOC, kRed+3, 22);
      SetLine(hPtOC,cLine[i],sMark[i]);
      SetAxis(hPtOC, YMin, YMax, XMin, XMax);
      hPtOC->Draw("same");
      //leg->AddEntry(hPtOC,"OC","lp");
      if (sOpt == "XiPlus")  leg->AddEntry(hPtOC,"OC #Xi^{+}","lp");
      if (sOpt == "XiMinus") leg->AddEntry(hPtOC,"OC #Xi^{-}","lp");
    }
  
    if (IsAnaNJ){
    if (sListNJ.IsNull() || sEffNJ.IsNull()) return;
      TH1D*  hPtNJ = (TH1D*)GetHistFromList(sEventFilePath, sJetSpectFile, sListNJ, sObject);
      NormBinSize(hPtNJ);
      if (IsRebin) hPtNJ = (TH1D*)RebinTH1D(hPtNJ, hRebin);
      if (IsEffCorr) TH1D* hEffNJ = (TH1D*)GetHistFromList(sEventFilePath, sEffJetFile, sEffNJ, sEff);
      if (IsRebin) hEffNJ = (TH1D*)RebinTH1D(hEffNJ, hRebin);
      hPtNJ->SetName("hPtNJ");
  
      TH1D* hPtNJ = NormNJ(hPtNJ, hNJEvent);
      cout<<"CPY NJ1  "<<hPtNJ->GetBinContent(5)<<endl;
      if (IsEffCorr) hPtNJ = RatioTH1D(hPtNJ, hEffNJ);
      cout<<"CPY NJ2  "<<hPtNJ->GetBinContent(5)<<endl;
      if(IsSave) {list->Add(hPtNJ);}
      //SetLine(hPtNJ, kMagenta+2, 23);
      SetLine(hPtNJ,cLine[i+nType],sMark[i+nType]);
      SetAxis(hPtNJ, YMin, YMax, XMin, XMax);
      hPtNJ->Draw("same");
      //leg->AddEntry(hPtNJ,"NJ","lp");
      if (sOpt == "XiPlus")  leg->AddEntry(hPtNJ, "NJ #Xi^{+}","lp");
      if (sOpt == "XiMinus") leg->AddEntry(hPtNJ, "NJ #Xi^{-}","lp");
    }
  }
  TLatex*     tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  SetCanv(c1);
  c1->SetLogy();
  SetLegend(leg);
  SetStyle();
  tex->DrawLatex(0.16, 0.91, "#Xi #it{p}_{T} spectrum");
  leg->Draw();
  if(IsSave) {file->cd(); list->Write(sOpt.Data(), TObject::kSingleKey); file->Close();}

  return;
}

