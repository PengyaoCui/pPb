#include "../../SourceFun.h"

//___________________________________________________________________
void PtSpect(){
  TString   sType[] = {"XiMinus"};//, "XiPlus"};//"XiPlus"; "XiMinus"
  //TString sSaveName = "PtSpect_JC_test_everycut";
  TString sSaveName = "PtSpect_0924";

  Bool_t IsEffCorr(1);

  Bool_t   IsAnaMC(0);//Draw MC Pt spect to compare with inclusive
  Bool_t IsAnaIncl(1);
  Bool_t   IsAnaJC(1);
  Bool_t   IsAnaJE(0);
  Bool_t   IsAnaPC(0);
  Bool_t   IsAnaOC(0);
  Bool_t   IsAnaNJ(0);

  Bool_t   IsSave(1);
  Bool_t  IsRebin(0);
  Bool_t   IsNorm(1);
//===================================================================
  //TString sEventFilePath = "/home/cuipengyao/study/code/Cascade_LHC15f_pass2/JC_test_everycut";
  //TString sEventFilePath = "/home/cuipengyao/study/code/cascade_LHC15f_pass2_test/Inclusive";
  TString sEventFilePath = "/home/cuipengyao/study/code/cascade_LHC15f_pass2_test/JC_Test";
  //TString sEventFilePath = "/home/cuipengyao/study/code/Cascade_LHC15f_pass2/Eff_JC_W_Rap_WO_LaMassCut_20170606";

//===================================================================
  TString   sMCEventFile = "AnalysisOutputs_LoopIncMC.root";
  TString sInclEventFile = "AnalysisOutputs_Loop1ndRD.root";
  TString  sJetEventFile = "AnalysisOutputs_LoopJetRD.root";

//-------------------------------------------------------------------
  TString   sMCSpectFile = "AnalysisOutputs_FitCbinMC.root";
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
  Double_t YMin = 1e-6;
  Double_t YMax = 1e7;
  Double_t XMin = 0.6;
  Double_t XMax = 6.5;
  
//-------------------------------------------------------------------
  TCanvas*  c1 = new TCanvas("c1", "");
  TLegend* leg = new TLegend(0.7,0.7,0.9,0.9);
//-------------------------------------------------------------------
  if(IsSave){
    //TFile *file = TFile::Open(Form("./result/%s.root", sSaveName.Data()), "UPDATE");
    if (IsEffCorr && IsNorm)  TFile *file = TFile::Open(Form("./result/%s.root", sSaveName.Data()), "UPDATE");
    if (IsNorm && !IsEffCorr) TFile *file = TFile::Open(Form("./result/%s_wo_EffCorr.root", sSaveName.Data()), "UPDATE");
    if (!IsNorm && IsEffCorr) TFile *file = TFile::Open(Form("./result/%s_wo_Norm.root", sSaveName.Data()), "UPDATE");
    if (!IsNorm && !IsEffCorr)TFile *file = TFile::Open(Form("./result/%s_wo_Norm_EffCorr.root", sSaveName.Data()), "UPDATE");
    //TList *list = (TList*)file->Get("PtSpect"); if (list) { file->Close(); return; } else { list = new TList(); }
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
    TString sOpt = sType[i];
  //-------------------------------------------------------------------
    TString   sMCEventList = Form("listLoopIncMC_%s_Default;1",sOpt.Data());
    TString sInclEventList = Form("listLoop1ndRD_%s_Default;1",sOpt.Data());
    //TString  sJetEventList = Form("listLoopJetRD_%s_Default_PtJ22_JC;1",sOpt.Data());
    TString  sJetEventList = "listLoopJetRD_Xi_Default_PtJ22_JC;1";
    TString   sListNJEvent = Form("listLoopJetRD_%s_Default_PtJ22_NJ",sOpt.Data());
  //-------------------------------------------------------------------
  
    TString    sListMC = Form("listFitCbinMC_%s_Default;1",sOpt.Data());
    TString  sListIncl = Form("listFitCbinRD_%s_Default;1",sOpt.Data());
    //TString    sListJC = Form("listFitCbinJE_%s_Default_PtJ22_JC;1",sOpt.Data());
    TString    sListJC = "listFitCbinJE_Xi_Default_PtJ22_JC;1";
    TString   sListPCL = Form("listFitCbinJE_%s_Default_PtJ22_PCL;1",sOpt.Data());
    TString   sListPCU = Form("listFitCbinJE_%s_Default_PtJ22_PCU;1",sOpt.Data());
    TString    sListOC = Form("listFitCbinJE_%s_Default_PtJ22_OC;1",sOpt.Data());
    TString    sListNJ = Form("listFitCbinJE_%s_Default_PtJ22_NJ;1",sOpt.Data());
  
    TString   sEffIncl = Form("listEffInclMC_%s_Default;1",sOpt.Data());
    //TString     sEffJC = Form("listEffCorrJE_%s_Default_PtJ22_JC;1",sOpt.Data());
    TString     sEffJC = "listEffCorrJE_Xi_Default_PtJ22_JC;1";
    TString    sEffPCL = Form("listEffCorrJE_%s_Default_PtJ22_PCL;1",sOpt.Data());
    TString    sEffPCU = Form("listEffCorrJE_%s_Default_PtJ22_PCU;1",sOpt.Data());
    TString     sEffOC = Form("listEffCorrJE_%s_Default_PtJ22_OC;1",sOpt.Data());
    TString     sEffNJ = Form("listEffCorrJE_%s_Default_PtJ22_NJ;1",sOpt.Data());
  
  //===================================================================
    if (IsAnaMC){
      if (sEventFilePath.IsNull() || sMCEventFile.IsNull() || sMCEventList.IsNull() || sEvent.IsNull()) return;
      TH1D* hMCEvent = (TH1D*)GetTH1FromFile(sEventFilePath, sMCEventFile, sMCEventList, sEvent);
    }
    if (IsAnaIncl){
      if (sEventFilePath.IsNull() || sInclEventFile.IsNull() || sInclEventList.IsNull() || sEvent.IsNull()) return;
      TH1D* hInclEvent = (TH1D*)GetTH1FromFile(sEventFilePath, sInclEventFile, sInclEventList, sEvent);
      //TH1D* hInclEvent = (TH1D*)GetTH1FromFile(sEventFilePath, sJetEventFile, sJetEventList, sEvent);
    }
    if (IsAnaJC || IsAnaPC || IsAnaOC || IsAnaJE){
      if (sEventFilePath.IsNull() || sJetEventFile.IsNull() || sJetEventList.IsNull() || sEvent.IsNull()) return;
      TH1D* hJetEvent = (TH1D*)GetTH1FromFile(sEventFilePath, sJetEventFile, sJetEventList, sEvent);
    }
  
    if (IsAnaNJ){
      if (sEventFilePath.IsNull() || sJetEventFile.IsNull() || sListNJEvent.IsNull() || sEvent.IsNull()) return;
      TH1D* hNJEvent = (TH1D*)GetTH1FromFile(sEventFilePath, sJetEventFile, sListNJEvent, sEvent);
    }
  
  //-------------------------------------------------------------------

    if (IsAnaMC){
      if (sListMC.IsNull()) return;
      TH1D*  hPtMC = (TH1D*)GetTH1FromFile(sEventFilePath, sMCSpectFile, sListMC, sObject);
      hPtMC->SetName(Form("hPtMC_%s", sOpt.Data()));
      NormBinSize(hPtMC);
      if (IsNorm) hPtMC = NormIncl(hPtMC, hMCEvent);
      SetLine(hPtMC,cLine[i+1],sMark[i+1]);
      SetAxis(hPtMC, YMin, YMax, XMin, XMax);
      if(IsSave) {file->cd(); hPtMC->Write(Form("hPtMC_%s", sOpt.Data()), TObject::kSingleKey);}
      hPtMC->Draw("same");
      if (sOpt == "XiPlus")  leg->AddEntry(hPtMC,"MC #bar#Xi^{+}","lp");
      if (sOpt == "XiMinus") leg->AddEntry(hPtMC,"MC #Xi^{-}","lp");
    }
  
    if (IsAnaIncl){
      if (sListIncl.IsNull() || sEffIncl.IsNull()) return;
      TH1D*  hPtIncl = (TH1D*)GetTH1FromFile(sEventFilePath, sInclSpectFile, sListIncl, sObject);
      hPtIncl->SetName(Form("hPtIncl_%s", sOpt.Data()));
      if (IsEffCorr) TH1D* hEffIncl = (TH1D*)GetTH1FromFile(sEventFilePath, sEffInclFile, sEffIncl, sEff);
      NormBinSize(hPtIncl);
      if (IsNorm) hPtIncl = NormIncl(hPtIncl, hInclEvent);
      if (IsEffCorr) hPtIncl = RatioTH1D(hPtIncl, hEffIncl);
      SetLine(hPtIncl,cLine[i],sMark[i]);
      SetAxis(hPtIncl, YMin, YMax, XMin, XMax);
      if(IsSave) {file->cd(); hPtIncl->Write(Form("hPtIncl_%s", sOpt.Data()), TObject::kSingleKey);}
      hPtIncl->Draw("same");
      if (sOpt == "XiPlus")  leg->AddEntry(hPtIncl,"Inclsive #Xi^{+}","lp");
      if (sOpt == "XiMinus") leg->AddEntry(hPtIncl,"Inclsive #Xi^{-}","lp");
    }
  
    if (IsAnaJC){
      if (sListJC.IsNull() || sEffJC.IsNull()) return;
      TH1D*  hPtJC = (TH1D*)GetTH1FromFile(sEventFilePath, sJetSpectFile, sListJC, sObject);
      hPtJC->SetName(Form("hPtJC_%s", sOpt.Data()));
      NormBinSize(hPtJC);
      if (IsRebin) hPtJC = (TH1D*)RebinTH1D(hPtJC, hRebin);
      if (IsEffCorr) TH1D* hEffJC = (TH1D*)GetTH1FromFile(sEventFilePath, sEffJetFile, sEffJC, sEff);
      if (IsRebin && IsEffCorr) hEffJC = (TH1D*)RebinTH1D(hEffJC, hRebin);
      hPtJC->SetName("hPtJC");
  
      if (IsNorm) hPtJC = NormJC(hPtJC, hJetEvent);
      if (IsEffCorr) hPtJC = RatioTH1D(hPtJC, hEffJC);
      SetLine(hPtJC,cLine[i+nType],sMark[i+nType]);
      SetAxis(hPtJC, YMin, YMax, XMin, XMax);
      if(IsSave) {file->cd(); hPtJC->Write(Form("hPtJC_%s", sOpt.Data()), TObject::kSingleKey);}
      hPtJC->Draw("same");
      if (sOpt == "XiPlus")  leg->AddEntry(hPtJC,"JC #Xi^{+}","lp");
      if (sOpt == "XiMinus") leg->AddEntry(hPtJC,"JC #Xi^{-}","lp");
    }
  
    if (IsAnaPC){
      if (sListPCL.IsNull() || sListPCU.IsNull() || sEffPCL.IsNull() || sEffPCU.IsNull()) return;
      TH1D*  hPtPCL = (TH1D*)GetTH1FromFile(sEventFilePath, sJetSpectFile, sListPCL, sObject);
      hPtPCL->SetName("hPtPCL");
      NormBinSize(hPtPCL);
      if (IsRebin) hPtPCL = (TH1D*)RebinTH1D(hPtPCL, hRebin);
      if (IsEffCorr) TH1D* hEffPCL = (TH1D*)GetTH1FromFile(sEventFilePath, sEffJetFile, sEffPCL, sEff);
      if (IsRebin && IsEffCorr) hEffPCL = (TH1D*)RebinTH1D(hEffPCL, hRebin);
  
      TH1D*  hPtPCU = (TH1D*)GetTH1FromFile(sEventFilePath, sJetSpectFile, sListPCU, sObject);
      hPtPCU->SetName("hPtPCU");
      NormBinSize(hPtPCU);
      if (IsRebin) hPtPCU = (TH1D*)RebinTH1D(hPtPCU, hRebin);
      if (IsEffCorr) TH1D* hEffPCU = (TH1D*)GetTH1FromFile(sEventFilePath, sEffJetFile, sEffPCU, sEff);
      if (IsRebin && IsEffCorr) hEffPCU = (TH1D*)RebinTH1D(hEffPCU, hRebin);
  
      if (IsEffCorr) hPtPCL = RatioTH1D(hPtPCL, hEffPCL);
      if (IsEffCorr) hPtPCU = RatioTH1D(hPtPCU, hEffPCU);
      if (IsNorm) TH1D* hPtPC = NormPC(hPtPCL, hPtPCU, hJetEvent);
      hPtPC->SetName("hPtPC");
      //SetLine(hPtPC,kRed,24);
      SetLine(hPtPC,cLine[i+2*nType],sMark[i+2*nType]);
      SetAxis(hPtPC, YMin, YMax, XMin, XMax);
      if(IsSave) {file->cd(); hPtPC->Write(Form("hPtPC_%s", sOpt.Data()), TObject::kSingleKey);}
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
      //SetLine(hPtJE,kBlue,25);
      SetLine(hPtJE,cLine[i+3*nType],sMark[i+3*nType]);
      if(IsSave) {file->cd(); hPtJE->Write(Form("hPtJE_%s", sOpt.Data()), TObject::kSingleKey);}
      hPtJE->Draw("same");
      if (sOpt == "XiPlus")  leg->AddEntry(hPtJE,"JE #Xi^{+}","lp");
      if (sOpt == "XiMinus") leg->AddEntry(hPtJE,"JE #Xi^{-}","lp");
      //leg->AddEntry(hPtJE,"JE","lp");
  
    }
  
    if (IsAnaOC){
      if (sListOC.IsNull() || sEffOC.IsNull()) return;
      TH1D*  hPtOC = (TH1D*)GetTH1FromFile(sEventFilePath, sJetSpectFile, sListOC, sObject);
      NormBinSize(hPtOC);
      if (IsRebin) hPtOC = (TH1D*)RebinTH1D(hPtOC, hRebin);
      if (IsEffCorr) TH1D* hEffOC = (TH1D*)GetTH1FromFile(sEventFilePath, sEffJetFile, sEffOC, sEff);
      if (IsRebin && IsEffCorr) hEffOC = (TH1D*)RebinTH1D(hEffOC, hRebin);
      hPtOC->SetName("hPtOC");
    
      if (IsNorm) TH1D* hPtOC = NormOC(hPtOC, hJetEvent);
      cout<<"CPY OC1  "<<hPtOC->GetBinContent(5)<<endl;
      if (IsEffCorr) hPtOC = RatioTH1D(hPtOC, hEffOC);
      cout<<"CPY OC2  "<<hPtOC->GetBinContent(5)<<endl;
      //SetLine(hPtOC, kRed+3, 22);
      SetLine(hPtOC,cLine[i],sMark[i]);
      SetAxis(hPtOC, YMin, YMax, XMin, XMax);
      if(IsSave) {file->cd(); hPtOC->Write(Form("hPtOC_%s", sOpt.Data()), TObject::kSingleKey);}
      hPtOC->Draw("same");
      //leg->AddEntry(hPtOC,"OC","lp");
      if (sOpt == "XiPlus")  leg->AddEntry(hPtOC,"OC #Xi^{+}","lp");
      if (sOpt == "XiMinus") leg->AddEntry(hPtOC,"OC #Xi^{-}","lp");
    }
  
    if (IsAnaNJ){
    if (sListNJ.IsNull() || sEffNJ.IsNull()) return;
      TH1D*  hPtNJ = (TH1D*)GetTH1FromFile(sEventFilePath, sJetSpectFile, sListNJ, sObject);
      NormBinSize(hPtNJ);
      if (IsRebin) hPtNJ = (TH1D*)RebinTH1D(hPtNJ, hRebin);
      if (IsEffCorr) TH1D* hEffNJ = (TH1D*)GetTH1FromFile(sEventFilePath, sEffJetFile, sEffNJ, sEff);
      if (IsRebin) hEffNJ = (TH1D*)RebinTH1D(hEffNJ, hRebin);
      hPtNJ->SetName("hPtNJ");
  
      if (IsNorm) TH1D* hPtNJ = NormNJ(hPtNJ, hNJEvent);
      cout<<"CPY NJ1  "<<hPtNJ->GetBinContent(5)<<endl;
      if (IsEffCorr) hPtNJ = RatioTH1D(hPtNJ, hEffNJ);
      cout<<"CPY NJ2  "<<hPtNJ->GetBinContent(5)<<endl;
      //SetLine(hPtNJ, kMagenta+2, 23);
      SetLine(hPtNJ,cLine[i+nType],sMark[i+nType]);
      SetAxis(hPtNJ, YMin, YMax, XMin, XMax);
      if(IsSave) {file->cd(); hPtNJ->Write(Form("hPtNJ_%s", sOpt.Data()), TObject::kSingleKey);}
      hPtNJ->Draw("same");
      //leg->AddEntry(hPtNJ,"NJ","lp");
      if (sOpt == "XiPlus")  leg->AddEntry(hPtNJ, "NJ #bar{#Xi}^{+}","lp");
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
  if(IsSave) { file->Close();}

  return;
}

