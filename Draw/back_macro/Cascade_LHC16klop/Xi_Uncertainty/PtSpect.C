#include "./SourceFun.h"

//___________________________________________________________________
void PtSpect(){
  TString   sType[] = {"Xi"};//"XiPlus"; "XiMinus"
  TString sCut = "Topology";
  TString sSaveName = Form("PtSpect_%s", sCut.Data());
  TString sCutType = "Stand";
  TString sTex = "Period : LHC16k LHC16l LHC16 and LHC16p";

  Bool_t IsEffCorr(1);

  Bool_t IsAnaIncl(1);

  Bool_t   IsSave(1);
  Bool_t   IsNorm(1);
//===================================================================
  if (sCutType == "Stand") 
  {
    TString sEventFilePath = Form("/home/cuipengyao/study/code/Cascade_LHC16klop_total/Local");
  }else{
    TString sEventFilePath = Form("/home/cuipengyao/study/code/Cascade_LHC16klop_total/Uncertainty/%s/%s", sCut.Data(), sCutType.Data());
  }
  //TString sEventFilePathk = Form("/home/cuipengyao/study/code/Cascade_LHC16klop_total/Uncertainty/%s/%s/LHC16k", sCut.Data(), sCutType.Data());
  //TString sEventFilePathh = Form("/home/cuipengyao/study/code/Cascade_LHC16klop_total/Uncertainty/%s/%s/LHC16h", sCut.Data(), sCutType.Data());
  //TString sEventFilePathl = Form("/home/cuipengyao/study/code/Cascade_LHC16klop_total/Uncertainty/%s/%s/LHC16l", sCut.Data(), sCutType.Data());
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
    if (IsEffCorr && IsNorm)  TFile *file = TFile::Open(Form("./result/%s.root", sSaveName.Data()), "UPDATE");
    if (IsNorm && !IsEffCorr) TFile *file = TFile::Open(Form("./result/%s_wo_EffCorr.root", sSaveName.Data()), "UPDATE");
    if (!IsNorm && IsEffCorr) TFile *file = TFile::Open(Form("./result/%s_wo_Norm.root", sSaveName.Data()), "UPDATE");
    if (!IsNorm && !IsEffCorr)TFile *file = TFile::Open(Form("./result/%s_wo_Norm_EffCorr.root", sSaveName.Data()), "UPDATE");
  }
//-------------------------------------------------------------------
  

  const Int_t nType  = sizeof(sType)/sizeof(TString);
  for(Int_t i=0; i<nType; i++) {
    TString sOpt = sType[i];
  //-------------------------------------------------------------------
    //TString   sMCEventList = Form("listLoopIncMC_%s_Default;1",sOpt.Data());
    TString sInclEventList = Form("listLoop1ndRD_%s_Default;1",sOpt.Data());
  //-------------------------------------------------------------------
  
    TString    sListMC = Form("listFitCbinMC_%s_Default;1",sOpt.Data());
    TString  sListIncl = Form("listFitCbinRD_%s_Default;1",sOpt.Data());
  
    TString   sEffIncl = Form("listEffInclMC_%s_Default;1",sOpt.Data());
  
  //===================================================================
    if (IsAnaIncl){
      if (sEventFilePath.IsNull() || sInclEventFile.IsNull() || sInclEventList.IsNull() || sEvent.IsNull()) return;
      TH1D* hInclEvent = (TH1D*)GetTH1FromFile(sEventFilePath, sInclEventFile, sInclEventList, sEvent);
      //TH1D* hInclEvent = (TH1D*)GetTH1FromFile(sEventFilePath, sJetEventFile, sJetEventList, sEvent);
    }
  
  //-------------------------------------------------------------------
    if (IsAnaIncl){
      if (sListIncl.IsNull() || sEffIncl.IsNull()) return;
      TH1D*  hPtIncl = (TH1D*)GetTH1FromFile(sEventFilePath, sInclSpectFile, sListIncl, sObject);
      hPtIncl->SetName(Form("hPtIncl_%s", sOpt.Data()));
      if (IsNorm) hPtIncl = NormIncl(hPtIncl, hInclEvent);
      if (IsEffCorr){
        TH1D* hEffIncl = (TH1D*)GetTH1FromFile(sEventFilePath, sEffInclFile, sEffIncl, sEff);
        hEffIncl->SetName(Form("hEffIncl_%s", sOpt.Data()));
        hPtIncl = RatioTH1D(hPtIncl, hEffIncl);
        //TH1D* hEffInclk = (TH1D*)GetTH1FromFile(sEventFilePathk, sEffInclFile, sEffIncl, sEff);
        //hEffInclk->SetName(Form("hEffInclk_%s", sOpt.Data()));
        //hEffInclk->Scale(2.49632e8/(2.49632e8 + 1.28757e8 + 6.72309e7));
        //TH1D* hEffInclh = (TH1D*)GetTH1FromFile(sEventFilePathh, sEffInclFile, sEffIncl, sEff);
        //hEffInclh->SetName(Form("hEffInclh_%s", sOpt.Data()));
        //hEffInclh->Scale(1.28757e8/(2.49632e8 + 1.28757e8 + 6.72309e7));

        //TH1D* hEffIncll = (TH1D*)GetTH1FromFile(sEventFilePathl, sEffInclFile, sEffIncl, sEff);
        //hEffIncll->SetName(Form("hEffIncll_%s", sOpt.Data()));
        //hEffIncll->Scale(6.72309e7/(2.49632e8 + 1.28757e8 + 6.72309e7));

        //TH1D *hEffIncl = (TH1D*) hEffInclk->Clone(Form("hEffIncl_%s", sOpt.Data()));
        //hEffIncl->Add(hEffInclh);
        //hEffIncl->Add(hEffIncll); 

        //hPtIncl = RatioTH1D(hPtIncl, hEffIncl);

      }
      NormBinSize(hPtIncl);
      SetLine(hPtIncl,cLine[i],sMark[i]);
      SetAxis(hPtIncl, YMin, YMax, XMin, XMax, "d#it{#rho}/d#it{p}_{T}");
      if(IsSave) {file->cd(); hPtIncl->Write(Form("hPtIncl_%s_%s", sOpt.Data(), sCutType.Data()), TObject::kSingleKey);}
      hPtIncl->Draw("same");
      leg->AddEntry(hPtIncl,"Inclusive","lp");
    }
  
  }
  TLatex*     tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  SetCanv(c1);
  c1->SetLogy();
  c1->SetGridy();
  c1->SetGridx();
  SetLegend(leg);
  SetStyle();
  //tex->DrawLatex(0.16, 0.91, sTex );
  tex->DrawLatex(0.17, 0.91, "p-p #sqrt{s} = 13 TeV #Xi^{#pm}");
  tex->DrawLatex(0.17, 0.84, sTex);
  //tex->DrawLatex(0.17, 0.77, );
  leg->Draw();
  if(IsSave) { file->Close();}

  return;
}

