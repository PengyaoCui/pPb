#include "TString.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TFile.h"
#include "TSystem.h"

#include "AliPicoBaseDev.cxx++g"
#include "AliPicoCascade.cxx++g"
#include "AliPicoCascadeRD.cxx++g"
#include "AliPicoCascadeMC.cxx++g"

#include "AliAnalysisTaskUserStraneJets.cxx++g"

const TString  tType[] ={"Kshort", "Lambda", "AntiLa", "Xi", "Omega"};
//const TString  tType[] ={"Lambda", "AntiLa"};

Bool_t IsMC  = 1;
Bool_t IsAnaResults  = 1;
Bool_t IsFd  = 1;
Bool_t IsIon = kTRUE;

Bool_t IsJet = 1;

//const Int_t CentMin = 20;
//const Int_t CentMax = 40;

//===============================================================>Real Data
const TString sFileLoop1ndRD = "AnalysisOutputs_Loop1ndRD";
const TString sListLoop1ndRD = "listLoop1ndRD";

const TString sFileFitInvMrd = "AnalysisOutputs_FitInvMrd";
const TString sListFitInvMrd = "listFitInvMrd";

const TString sFileLoop2ndRD = "AnalysisOutputs_Loop2ndRD";
const TString sListLoop2ndRD = "listLoop2ndRD";

const TString sFileFitCbinRD = "AnalysisOutputs_FitCbinRD";
const TString slistFitCbinRD = "listFitCbinRD";

const TString sFileLoopJetRD = "AnalysisOutputs_LoopJetRD";
const TString sListLoopJetRD = "listLoopJetRD";

const TString sFileFitCbinJE = "AnalysisOutputs_FitCbinJE";
const TString slistFitCbinJE = "listFitCbinJE";

//===================================================================>MC analysis
const TString sFileLoopIncMC = "AnalysisOutputs_LoopIncMC";
const TString slistLoopIncMC = "listLoopIncMC";

const TString sFileFitCbinMC = "AnalysisOutputs_FitCbinMC";
const TString slistFitCbinMC = "listFitCbinMC";
//---------------------------------------------------------------------------------
const TString sFileEffInclMC ="AnalysisOutputs_EffInclMC";
const TString slistEffInclMC ="listEffInclMC";

const TString sFileEffCorrMC = "AnalysisOutputs_EffCorrMC";
const TString slistEffCorrMC = "listEffCorrMC";

const TString sFileEffCorrJE = "AnalysisOutputs_EffCorrJE";
const TString slistEffCorrJE = "listEffCorrJE";

const TString sFileMakeLaFdR ="AnalysisOutputs_MakeLaFdR";
const TString slistMakeLaFdR ="listMakeLaFdR";

const TString sFileResults ="AnalysisOutputs_Results";
const TString slistResults ="listResults";//"listMakeLaFdR_Lambda_Default"

class AliAnalysisTaskUserStraneJets;
bool LoadLibraries();
TH1D* RebinTH1D(TH1D const *hF, TH1D const *hR);

TChain* CreateAODChain(const TString sDataset);
//Bool_t Config(AliAnalysisTaskUserStraneJets *ana, TH2D *hRM=0);
Bool_t Config(AliAnalysisTaskUserStraneJets *ana, Double_t dcMin, Double_t dcMax, TH2D *hRM=0);

//=============================================================================
void runLocalStrangeJets()
{
  const Double_t CentMin = 0.;
  const Double_t CentMax = 100.;
  const TString sCent[] = {"0100", "090", "010", "1040", "4090", "40100"};
  const TString sRunList="dataset.txt";
  if (LoadLibraries()) return;
  if (sRunList.IsNull()) return;

  TString  localFiles = "dataset_mc.txt";

  AliAnalysisTaskUserStraneJets *ana = new AliAnalysisTaskUserStraneJets("AnaStrangeParJet");

  if(!IsMC){
    if (ana->SetInputEventsRD(CreateAODChain(sRunList)))return;//在runlist里找到PicoHeaderCJ并存放在 AliPicoHeaderCJ *fHeader指针。//CreateAODChain定义在343-357
  }else{
    if (ana->SetInputEventsMC(CreateAODChain(localFiles)))return;
  }

  Config(ana, CentMin, CentMax);
  TString sCut= "Default";

  Bool_t IsUE = 1;
  Bool_t PCL  = 1;
  Bool_t PCU  = 0;
  Bool_t IsOC = 0;
  Bool_t IsNJ = 0;

  Bool_t IsPCLU= (PCL||PCU);
  ana->SetIsInJPCLAna(PCL);
  ana->SetIsInJPCUAna(PCU);
  ana->SetIsInJetsAna(!IsOC);
  TString sPCLU="";
  if(IsPCLU){
    if(PCL){ sPCLU="PCL";}
    else if(PCU){ sPCLU="PCU";}
  }
  
  Double_t dJetPtBin = -1.;
  if (IsNJ)  dJetPtBin=5;
  if (!IsNJ) dJetPtBin=10.;
  ana->SetJetPtRange(dJetPtBin); 

  TString sOpt = IsUE?(IsNJ?"NJ":(IsOC?"OC":sPCLU)):"JC";
  //if(IsPCFd) sOpt = "PC";
  TString  sFix = Form("%s_%s", sCut.Data(), sOpt.Data()); 

  if(!IsMC){
    TString sType1;
    TString Cent;
    for(Int_t p = 0; p < sizeof(tType)/sizeof(TString); p++)
    {
      sType1 = tType[p];     
      ana->SetDataLoop1st(sFileLoop1ndRD, Form("%s_%s_%s",sListLoop1ndRD.Data(),sType1.Data(),sCut.Data()));ana->AnaLoop1RD(sType1.Data());
     
      for(Int_t c = 0; c < sizeof(sCent)/sizeof(TString); c++)
      {
        Cent = sCent[c]; 
        ana->SetDataLoop1st(sFileLoop1ndRD, Form("%s_%s_%s_%s",sListLoop1ndRD.Data(),sType1.Data(),sCut.Data(), Cent.Data()));
        ana->SetDataFitInvM(sFileFitInvMrd, Form("%s_%s_%s_%s",sListFitInvMrd.Data(),sType1.Data(),sCut.Data(), Cent.Data()));
	ana->AnaFitInvM(sType1.Data(), kFALSE);
      }
      
      ana->SetDataLoop1st(sFileLoop1ndRD, Form("%s_%s_%s",sListLoop1ndRD.Data(),sType1.Data(),sCut.Data()));
      ana->SetDataFitInvM(sFileFitInvMrd, Form("%s_%s_%s",sListFitInvMrd.Data(),sType1.Data(),sCut.Data()));
      ana->SetDataLoop2nd(sFileLoop2ndRD, Form("%s_%s_%s",sListLoop2ndRD.Data(),sType1.Data(),sCut.Data()));ana->AnaLoop2RD(sType1.Data()); 
      
      for(Int_t c = 0; c < sizeof(sCent)/sizeof(TString); c++)
      {
	Cent = sCent[c];
        ana->SetDataLoop1st(sFileLoop1ndRD, Form("%s_%s_%s_%s",sListLoop1ndRD.Data(),sType1.Data(),sCut.Data(), Cent.Data()));
        ana->SetDataFitInvM(sFileFitInvMrd, Form("%s_%s_%s_%s",sListFitInvMrd.Data(),sType1.Data(),sCut.Data(), Cent.Data()));
        ana->SetDataLoop2nd(sFileLoop2ndRD, Form("%s_%s_%s_%s",sListLoop2ndRD.Data(),sType1.Data(),sCut.Data(), Cent.Data())); 
        ana->SetDataFitCbin(sFileFitCbinRD, Form("%s_%s_%s_%s",slistFitCbinRD.Data(),sType1.Data(),sCut.Data(), Cent.Data()));
        ana->AnaFitCbin(sType1.Data());  
      }
      if(IsJet){
        ana->SetDataLoop1st(sFileLoop1ndRD, Form("%s_%s_%s",sListLoop1ndRD.Data(),sType1.Data(),sCut.Data()));
        ana->SetDataFitInvM(sFileFitInvMrd, Form("%s_%s_%s",sListFitInvMrd.Data(),sType1.Data(),sCut.Data()));
        ana->SetDataLoop2nd(sFileLoop2ndRD, Form("%s_%s_%s",sListLoop2ndRD.Data(),sType1.Data(),sCut.Data())); 
        ana->SetDataLoopJet(sFileLoopJetRD, Form("%s_%s_%s",sListLoopJetRD.Data(),sType1.Data(),sFix.Data()));
        if (!IsNJ) ana->AnaLoopJet(sType1.Data(),"RD04");
        if (IsNJ) ana->AnaLoopNJ(sType1.Data(),"RD04");
        for(Int_t c = 0; c < sizeof(sCent)/sizeof(TString); c++)
        {
  	  Cent = sCent[c];
          ana->SetDataLoop1st(sFileLoopJetRD, Form("%s_%s_%s_%s",sListLoopJetRD.Data(),sType1.Data(),sFix.Data(), Cent.Data()));
          ana->SetDataFitInvM(sFileFitInvMrd, Form("%s_%s_%s_%s",sListFitInvMrd.Data(),sType1.Data(),sCut.Data(), Cent.Data()));
          ana->SetDataLoop2nd(sFileLoopJetRD, Form("%s_%s_%s_%s",sListLoopJetRD.Data(),sType1.Data(),sFix.Data(), Cent.Data()));
          ana->SetDataFitCbin(sFileFitCbinJE, Form("%s_%s_%s_%s",slistFitCbinJE.Data(),sType1.Data(),sFix.Data(), Cent.Data()));
	  ana->AnaFitCbin(sType1.Data());
	}
      }
    }
  }else{
    TFile *f1=TFile::Open("histos.root");

    TH1D *hPt = nullptr;
    TH2D *hPtEta = nullptr;
    

    TString sType1;
    for(Int_t p = 0; p < sizeof(tType)/sizeof(TString); p++)
    {
      sType1 = tType[p];     
      hPt=(TH1D*)f1->Get(Form("%s_%d%d", sType1.Data(), int(CentMin), int(CentMax)));
      ana->SetDataFitInvM(sFileFitInvMrd, Form("%s_%s_%s_0100",sListFitInvMrd.Data(),sType1.Data(),sCut.Data()));
      ana->SetDataLoopsMC(sFileLoopIncMC, Form("%s_%s_%s_0100",slistLoopIncMC.Data(),sType1.Data(),sCut.Data())); ana->AnaLoopsMC(sType1.Data());
      ana->SetDataLoop1st(sFileLoopIncMC, Form("%s_%s_%s_0100",slistLoopIncMC.Data(),sType1.Data(),sCut.Data()));
      ana->SetDataLoop2nd(sFileLoopIncMC, Form("%s_%s_%s_0100",slistLoopIncMC.Data(),sType1.Data(),sCut.Data()));
      ana->SetDataFitCbin(sFileFitCbinMC, Form("%s_%s_%s_0100",slistFitCbinMC.Data(),sType1.Data(),sCut.Data()));  ana->AnaFitCbin(sType1.Data());
      ana->SetDataMakeEff(sFileEffInclMC, Form("%s_%s_%s_0100",slistEffInclMC.Data(),sType1.Data(),sCut.Data()));  ana->AnaInclEff(sType1.Data(), hPt);
      if(IsJet){
        hPtEta =(TH2D*)f1->Get(Form("%s_pT_Eta", sType1.Data()));
        ana->SetDataLoop2nd(sFileLoopJetRD, Form("%s_%s_%s_0100",sListLoopJetRD.Data(),sType1.Data(),sFix.Data()));
        ana->SetDataMakeEff(sFileEffCorrMC, Form("%s_%s_%s_0100",slistEffCorrMC.Data(),sType1.Data(),sCut.Data()));  ana->AnaCorrEff(hPtEta, "I");
        ana->SetDataMakeEff(sFileEffCorrJE, Form("%s_%s_%s_0100",slistEffCorrJE.Data(),sType1.Data(),sFix.Data()));  ana->AnaCorrEff(hPtEta, "J");
      }
    }
  }

  if(IsAnaResults){
    TString sType1;
    TString Cent;
    for(Int_t p = 0; p < sizeof(tType)/sizeof(TString); p++){
      sType1 = tType[p];
      for(Int_t c = 0; c < sizeof(sCent)/sizeof(TString); c++)
      {
        Cent = sCent[c];
        ana->SetDataLoop1st(sFileLoop1ndRD, Form("%s_%s_%s_%s",sListLoop1ndRD.Data(),sType1.Data(),sCut.Data(), Cent.Data()));
        ana->SetDataFitCbin(sFileFitCbinRD, Form("%s_%s_%s_%s",slistFitCbinRD.Data(),sType1.Data(),sCut.Data(), Cent.Data()));
        if(IsJet){
          ana->SetDataMakeEff(sFileEffCorrMC, Form("%s_%s_%s_0100",slistEffCorrMC.Data(),sType1.Data(),sCut.Data()));
        }else{
          ana->SetDataMakeEff(sFileEffInclMC, Form("%s_%s_%s_0100",slistEffInclMC.Data(),sType1.Data(),sCut.Data()));
        }
        ana->SetDataResults(sFileResults, Form("%s_%s_%s_%s",slistResults.Data(), sType1.Data(),sCut.Data(), Cent.Data()));
       	ana->AnaResults(2*0.75*TMath::TwoPi());
       
        if(IsJet){
          ana->SetDataLoop1st(sFileLoopJetRD, Form("%s_%s_%s_%s",sListLoopJetRD.Data(),sType1.Data(),sFix.Data(), Cent.Data()));
          ana->SetDataFitCbin(sFileFitCbinJE, Form("%s_%s_%s_%s",slistFitCbinJE.Data(),sType1.Data(),sFix.Data(), Cent.Data()));
          ana->SetDataMakeEff(sFileEffCorrJE, Form("%s_%s_%s_0100",slistEffCorrJE.Data(),sType1.Data(),sFix.Data()));
          ana->SetDataResults(sFileResults, Form("%s_%s_%s_%s",slistResults.Data(), sType1.Data(),sFix.Data(), Cent.Data()));
          if(!IsUE){
            ana->AnaResults(2*0.75*TMath::TwoPi()*0.06);
          }else{
            if(IsPCLU) ana->AnaResults(2*0.75*TMath::TwoPi()*0.27);
            if(IsOC) ana->AnaResults(2*0.75*TMath::TwoPi()*0.79);
            if(IsNJ) ana->AnaResults(2*0.75*TMath::TwoPi());
          }
        }
      }
    }
  }

  if (IsFd){ 
    
    TFile *f0=TFile::Open("histos.root");
    TH1D *hPtXiNegKine = (TH1D*)f0->Get("XiNeg_0100"); //for Lambda
    TH1D *hPtXiPosKine = (TH1D*)f0->Get("XiPos_0100"); //for AntiLa 
    TFile *f1=TFile::Open("AnalysisOutputs_Results.root");
    TFile *f2=TFile::Open("XiSpect.root");
  
    //const Double_t dPtBin[] = { 0.6, 1.6, 2.2, 3.0, 4.0, 5.5, 7.7, 10., 13.};
    //const Int_t nPtBin = sizeof(dPtBin)/sizeof(Double_t) - 1;
    //auto hRebin = new TH1D("Rebin", "", nPtBin, dPtBin);
    
    TString sType1;
    TString Cent;
    sType1 = "Lambda";
    
    for(Int_t c = 0; c < sizeof(sCent)/sizeof(TString); c++)
    {
      Cent = sCent[c];
      auto hPtXiIncl = (TH1D*)f2->Get(Form("Incl_Xi_%s", Cent.Data()));
      //hPtXiIncl=RebinTH1D( hPtXiIncl, hRebin);
      ana->SetDataLoopsMC(sFileLoopIncMC, Form("%s_%s_%s_0100",slistLoopIncMC.Data(),sType1.Data(),sCut.Data()));
      ana->SetDataResults(sFileResults,   Form("%s_%s_%s_%s",slistResults.Data()  ,sType1.Data(),sCut.Data(), Cent.Data()));
      ana->SetDataLoop1st(sFileLoop1ndRD, Form("%s_%s_%s_%s",sListLoop1ndRD.Data(),sType1.Data(),sCut.Data(), Cent.Data()));
      ana->SetDataMakeFdR(sFileMakeLaFdR, Form("%s_%s_%s_%s",slistMakeLaFdR.Data(),sType1.Data(),sCut.Data(), Cent.Data()));
      ana->AnaMakeFdR(hPtXiIncl, hPtXiNegKine, 2*0.75*TMath::TwoPi());

      if(IsJet){
        //auto hPtXiJC = (TH1D*)f2->Get(Form("JC_Xi_%s", Cent.Data())); 
        auto hPtXiPCL = (TH1D*)f2->Get(Form("PCL_Xi_%s", Cent.Data()));
        auto hPtXiPCU = (TH1D*)f2->Get(Form("PCU_Xi_%s", Cent.Data()));
        //auto hPtXiOC = (TH1D*)f2->Get(Form("OC_Xi_%s", Cent.Data()));
        //auto hPtXiNJ = (TH1D*)f2->Get(Form("NJ_Xi_%s", Cent.Data()));
        //hPtXiJC=RebinTH1D( hPtXiJC, hRebin);
        
	//auto hPtXiUE = (TH1D*)f2->Get(Form("PCL_Xi_%s", Cent.Data())); 
        //TH1D *hPtXiJE = (TH1D*)hPtXiJC->Clone("hPtXiJE"); hPtXiJE->Reset(); hPtXiJE->Add(hPtXiJC, hPtXiUE, 1., -0.5); 
        //auto lLaJC = (TList*)f1->Get(Form("%s_Lambda_%s_%s",slistResults.Data(), sFix.Data(), Cent.Data()));
        //auto hPtLaJC = (TH1D*)lLaJC->FindObject("hSco");
        //auto lLaUE = (TList*)f1->Get(Form("%s_Lambda_%s_PCL_%s",slistResults.Data(), sCut.Data(), Cent.Data()));
        //auto hPtLaUE = (TH1D*)lLaUE->FindObject("hSco");
        //TH1D *hPtLaJE = (TH1D*)hPtLaJC->Clone("hPtLaJE"); hPtLaJE->Reset(); hPtLaJE->Add(hPtLaJC, hPtLaUE, 1., -0.5); 

        ana->SetDataLoopsMC(sFileLoopIncMC, Form("%s_%s_%s_0100",slistLoopIncMC.Data(),sType1.Data(),sCut.Data()));
        ana->SetDataResults(sFileResults,   Form("%s_%s_%s_%s",slistResults.Data(), sType1.Data(),sFix.Data(), Cent.Data()));
        ana->SetDataLoop1st(sFileLoopJetRD, Form("%s_%s_%s_%s",sListLoopJetRD.Data(),sType1.Data(),sFix.Data(), Cent.Data()));
        ana->SetDataMakeFdR(sFileMakeLaFdR, Form("%s_%s_%s_%s",slistMakeLaFdR.Data(),sType1.Data(),sFix.Data(), Cent.Data()));
        if(PCL){ana->AnaMakeFdR(hPtXiPCL, hPtXiNegKine, 2*0.75*TMath::TwoPi()*0.27); }
        if(PCU){ana->AnaMakeFdR(hPtXiPCU, hPtXiNegKine, 2*0.75*TMath::TwoPi()*0.27); }
        //if(IsOC){ana->AnaMakeFdR(hPtXiOC, hPtXiNegKine, 2*0.75*TMath::TwoPi()*0.79); }
        //if(IsNJ){ana->AnaMakeFdR(hPtXiNJ, hPtXiNegKine, 2*0.75*TMath::TwoPi()); }
        //if(!IsUE){ana->AnaMakeFdRJC(hPtXiJE, hPtXiNegKine, hPtLaJE, 2*0.75*TMath::TwoPi()*0.06);}
      }
    } 
    sType1 = "AntiLa";
    for(Int_t c = 0; c < sizeof(sCent)/sizeof(TString); c++)
    {
      Cent = sCent[c];
      auto hPtXiIncl = (TH1D*)f2->Get(Form("Incl_Xi_%s", Cent.Data()));
      //hPtXiIncl=RebinTH1D( hPtXiIncl, hRebin);
      ana->SetDataLoopsMC(sFileLoopIncMC, Form("%s_%s_%s_0100",slistLoopIncMC.Data(),sType1.Data(),sCut.Data()));
      ana->SetDataResults(sFileResults,   Form("%s_%s_%s_%s",slistResults.Data()  ,sType1.Data(),sCut.Data(), Cent.Data()));
      ana->SetDataLoop1st(sFileLoop1ndRD, Form("%s_%s_%s_%s",sListLoop1ndRD.Data(),sType1.Data(),sCut.Data(), Cent.Data()));
      ana->SetDataMakeFdR(sFileMakeLaFdR, Form("%s_%s_%s_%s",slistMakeLaFdR.Data(),sType1.Data(),sCut.Data(), Cent.Data()));
      ana->AnaMakeFdR(hPtXiIncl, hPtXiPosKine, 2*0.75*TMath::TwoPi());
      
      if(IsJet){
        //auto hPtXiJC = (TH1D*)f2->Get(Form("JC_Xi_%s", Cent.Data())); 
        //hPtXiJC=RebinTH1D( hPtXiJC, hRebin);
        auto hPtXiPCL = (TH1D*)f2->Get(Form("PCL_Xi_%s", Cent.Data()));
        auto hPtXiPCU = (TH1D*)f2->Get(Form("PCU_Xi_%s", Cent.Data()));
        //auto hPtXiOC = (TH1D*)f2->Get(Form("OC_Xi_%s", Cent.Data()));
        //auto hPtXiNJ = (TH1D*)f2->Get(Form("NJ_Xi_%s", Cent.Data()));
	//auto hPtXiUE = (TH1D*)f2->Get(Form("PCL_Xi_%s", Cent.Data())); 
        //TH1D *hPtXiJE = (TH1D*)hPtXiJC->Clone("hPtXiJE"); hPtXiJE->Reset(); hPtXiJE->Add(hPtXiJC, hPtXiUE, 1., -0.5); 
        //auto lLaJC = (TList*)f1->Get(Form("%s_AntiLa_%s_%s",slistResults.Data(), sFix.Data(), Cent.Data()));
        //auto hPtLaJC = (TH1D*)lLaJC->FindObject("hSco");
        //auto lLaUE = (TList*)f1->Get(Form("%s_AntiLa_%s_PCL_%s",slistResults.Data(), sCut.Data(), Cent.Data()));
        //auto hPtLaUE = (TH1D*)lLaUE->FindObject("hSco");
        //TH1D *hPtLaJE = (TH1D*)hPtLaJC->Clone("hPtLaJE"); hPtLaJE->Reset(); hPtLaJE->Add(hPtLaJC, hPtLaUE, 1., -0.5); 

        ana->SetDataLoopsMC(sFileLoopIncMC, Form("%s_%s_%s_0100",slistLoopIncMC.Data(),sType1.Data(),sCut.Data()));
        ana->SetDataResults(sFileResults,   Form("%s_%s_%s_%s",slistResults.Data(), sType1.Data(),sFix.Data(), Cent.Data()));
        ana->SetDataLoop1st(sFileLoopJetRD, Form("%s_%s_%s_%s",sListLoopJetRD.Data(),sType1.Data(),sFix.Data(), Cent.Data()));
        ana->SetDataMakeFdR(sFileMakeLaFdR, Form("%s_%s_%s_%s",slistMakeLaFdR.Data(),sType1.Data(),sFix.Data(), Cent.Data()));
        if(PCL){ana->AnaMakeFdR(hPtXiPCL, hPtXiNegKine, 2*0.75*TMath::TwoPi()*0.27); }
        if(PCU){ana->AnaMakeFdR(hPtXiPCU, hPtXiNegKine, 2*0.75*TMath::TwoPi()*0.27); }
        //if(IsOC){ana->AnaMakeFdR(hPtXiOC, hPtXiNegKine, 2*0.75*TMath::TwoPi()*0.79); }
        //if(IsNJ){ana->AnaMakeFdR(hPtXiNJ, hPtXiNegKine, 2*0.75*TMath::TwoPi()); }
        //if(!IsUE){ana->AnaMakeFdRJC(hPtXiJE, hPtXiNegKine, hPtLaJE, 2*0.75*TMath::TwoPi()*0.06);}
      }
    }
  }     
  return;
}

//==========================================================================================

Bool_t Config(AliAnalysisTaskUserStraneJets *ana, Double_t dcMin, Double_t dcMax, TH2D *hRM=0)
{
  if (!ana) return kFALSE;
  
  if(IsIon){
    TString scEsti = "V0A";
    if (gSystem->Getenv("CONFIG_STR_CENT_ESTI")) scEsti = gSystem->Getenv("CONFIG_STR_CENT_ESTI");
    //Double_t dcMin = CentMin;
    //Double_t dcMax = CentMax;
    if (gSystem->Getenv("CONFIG_VAL_CENT_MIN")) dcMin = atof(gSystem->Getenv("CONFIG_VAL_CENT_MIN"));
    if (gSystem->Getenv("CONFIG_VAL_CENT_MAX")) dcMax = atof(gSystem->Getenv("CONFIG_VAL_CENT_MAX"));

    ana->SetCentralityEstimator(scEsti);
    ana->SetIsAnaIon(IsIon);
    ana->SetCentralityClass(dcMin, dcMax);
  }
  
  const Double_t dKaPtBin[] = { 0.9, 1.6, 2.2, 2.8, 3.7, 5, 8, 12.};
  const Int_t nKaPtBin = sizeof(dKaPtBin)/sizeof(Double_t) - 1;

  const Double_t dLaPtBin[] = { 0.9, 1.6, 2.2, 2.8, 3.7, 5, 8, 12.};
  const Int_t nLaPtBin = sizeof(dLaPtBin)/sizeof(Double_t) - 1;

  const Double_t dXiPtBin[] = { 0.9, 1.6, 2.2, 2.8, 3.7, 5, 8.};
  const Int_t nXiPtBin = sizeof(dXiPtBin)/sizeof(Double_t) - 1;

  const Double_t dOmegaPtBin[] = { 0.9, 2.2, 2.8, 3.7, 5.};
  const Int_t nOmegaPtBin = sizeof(dOmegaPtBin)/sizeof(Double_t) - 1;

#if 0
  const Double_t dKaPtBin[] = { 0.6, 0.7, 0.8, 0.9, 1.0, 1.1, 1.2, 1.4, 1.6, 1.8, 2.0, 2.2, 2.4, 2.6, 2.8, 3.2, 3.7, 4.2, 5.0, 6.0, 8.0, 12.};
  const Int_t nKaPtBin = sizeof(dKaPtBin)/sizeof(Double_t) - 1;

  const Double_t dLaPtBin[] = { 0.6, 0.7, 0.8, 0.9, 1.0, 1.1, 1.2, 1.4, 1.6, 1.8, 2.0, 2.2, 2.4, 2.6, 2.8, 3.2, 3.7, 4.2, 5.0, 6.0, 8.0, 12.};
  const Int_t nLaPtBin = sizeof(dLaPtBin)/sizeof(Double_t) - 1;

  const Double_t dXiPtBin[] = { 0.6, 0.7, 0.8, 0.9, 1.0, 1.1, 1.2, 1.4, 1.6, 1.8, 2.0, 2.2, 2.4, 2.6, 2.8, 3.2, 3.7, 4.2, 5.0, 6.0, 8.0};
  const Int_t nXiPtBin = sizeof(dXiPtBin)/sizeof(Double_t) - 1;

  const Double_t dOmegaPtBin[] = { 0.6, 0.8, 1.0, 1.2, 1.6, 2.0, 2.2, 2.4, 2.6, 2.8, 3.2, 3.7, 4.2, 5.0};
  const Int_t nOmegaPtBin = sizeof(dOmegaPtBin)/sizeof(Double_t) - 1;
#endif

  if (ana->SetKaPtBinning(nKaPtBin, dKaPtBin)) return kFALSE;
  if (ana->SetLaPtBinning(nLaPtBin, dLaPtBin)) return kFALSE;
  if (ana->SetXiPtBinning(nXiPtBin, dXiPtBin)) return kFALSE;
  if (ana->SetOmegaPtBinning(nOmegaPtBin, dOmegaPtBin)) return kFALSE;

  const Double_t dV0EtaMin = -0.75;
  const Double_t dV0EtaMax =  0.75;
  const Double_t dCascadeEtaMin = -0.75;
  const Double_t dCascadeEtaMax =  0.75;
  const Double_t dDauEtaMin = -0.8;
  const Double_t dDauEtaMax =  0.8;


  //ana->SetV0RapRange(-0.465, 0.035);
  ana->SetV0EtaRange(dV0EtaMin, dV0EtaMax);
  ana->SetV0DauEtaRange(dDauEtaMin, dDauEtaMax);
  ana->SetDefaultKaCutsPA();
  ana->SetDefaultLaCutsPA();

  //ana->SetCascadeRapRange(-0.465, 0.035);
  ana->SetCascadeEtaRange(dCascadeEtaMin, dCascadeEtaMax);
  ana->SetTrkEtaRange(dDauEtaMin, dDauEtaMax);
  ana->SetDefaultXiCutsPA();
  ana->SetDefaultOmegaCutsPA();

  Double_t dJR = 0.4;
  Double_t dJC = 0.6;
  if (gSystem->Getenv("CONFIG_VAL_JET_RADIUS"))   dJR = atof(gSystem->Getenv("CONFIG_VAL_JET_RADIUS"));//????
  if (gSystem->Getenv("CONFIG_VAL_JET_CONESIZE")) dJC = atof(gSystem->Getenv("CONFIG_VAL_JET_CONESIZE"));

  ana->SetInJetRadius(dJC);
  ana->SetBkgParRadius(dJC);
  //ana->SetJetIsUseEstiPt(kFALSE);
  ana->SetJetIsUseEstiPt(kTRUE);
  ana->SetIsInJetsAna(kTRUE);

  const Double_t dJetEtaMin = dV0EtaMin + dJR;
  const Double_t dJetEtaMax = dV0EtaMax - dJR;

  ana->SetJetEtaRange(dJetEtaMin, dJetEtaMax);
  Double_t dAF = 0.6;
  if (gSystem->Getenv("CONFIG_VAL_AF_CUT")) dAF = atof(gSystem->Getenv("CONFIG_VAL_AF_CUT"));

  ana->SetJetMinAreaFrac(dAF);
  ana->SetJetMultiplicityRange(1);//no multplicity cut

  Bool_t bUseRM = kFALSE;
  if (gSystem->Getenv("CONFIG_BIS_RM")) bUseRM = atoi(gSystem->Getenv("CONFIG_BIS_RM"));

  if (bUseRM) ana->SetDetectorRM(hRM);
  return kTRUE;
}


//_____________________________________________________________________________
TChain* CreateAODChain(const TString sDataset)
{
  if  (sDataset.IsNull()) return 0;
  if (!sDataset.EndsWith(".txt")) return 0;
  TString dataFile;
  TChain *chain = new TChain("aodTree");
  ifstream dataList(sDataset.Data(), ios::in);//input file stream
  while (!dataList.eof()) {
    dataFile.ReadLine(dataList,kTRUE);
    if (!dataFile.EndsWith(".root")) continue;
    if (!gSystem->AccessPathName(dataFile.Data())) chain->Add(dataFile.Data());
  } dataList.close();

  return chain;
}

//_____________________________________________________________________________
Bool_t LoadLibraries()
{
  if (gSystem->Load("libTree")       <0) return kTRUE;
  if (gSystem->Load("libGeom")       <0) return kTRUE;
  if (gSystem->Load("libPhysics")    <0) return kTRUE;
  if (gSystem->Load("libVMC")        <0) return kTRUE;
  if (gSystem->Load("libMinuit")     <0) return kTRUE;
  if (gSystem->Load("libMinuit2")    <0) return kTRUE;

  if (gSystem->Load("libCore")       <0) return kTRUE;
  if (gSystem->Load("libXMLIO")      <0) return kTRUE;
  if (gSystem->Load("libXMLParser")  <0) return kTRUE;
  if (gSystem->Load("libProof")      <0) return kTRUE;
  if (gSystem->Load("libProofPlayer")<0) return kTRUE;
  if (gSystem->Load("libGui")        <0) return kTRUE;
//=============================================================================
  gSystem->AddIncludePath("-Wno-deprecated");
  gSystem->AddIncludePath("-I$ALICE_ROOT/include");
  gSystem->AddIncludePath("-I$ALICE_PHYSICS/include");
  gSystem->AddIncludePath("-I$ALICE_PHYSICS/PWGHF/vertexingHF");
  gSystem->AddIncludePath("-I$ALICE_ROOT/ERDAL");
  gSystem->AddIncludePath("-I$ALICE_PHYSICS/JETAN");
  gSystem->AddIncludePath("-I$ALICE_PHYSICS/JETAN/fastjet");

  if (gSystem->Load("libSTEERBase")         <0) return kTRUE;
  if (gSystem->Load("libESD")               <0) return kTRUE;
  if (gSystem->Load("libAOD")               <0) return kTRUE;
  if (gSystem->Load("libANALYSIS")          <0) return kTRUE;
  if (gSystem->Load("libOADB")              <0) return kTRUE;
  if (gSystem->Load("libANALYSISalice")     <0) return kTRUE;
  if (gSystem->Load("libCORRFW")            <0) return kTRUE;

  if (gSystem->Load("libCGAL")              <0) return kTRUE;
  if (gSystem->Load("libfastjet")           <0) return kTRUE;
  if(gSystem->Load("libsiscone")            <0) return kTRUE;
  if(gSystem->Load("libsiscone_spherical")  <0) return kTRUE;
  if(gSystem->Load("libfastjetplugins")     <0) return kTRUE;
  if(gSystem->Load("libfastjettools")       <0) return kTRUE;
  if(gSystem->Load("libfastjetcontribfragile") <0)return kTRUE;

  if(gSystem->Load("libPWGJEFlavourJetTasks")  <0) return kTRUE;
//=============================================================================

  return kFALSE;
}

TH1D* RebinTH1D(TH1D const *hF, TH1D const *hR)
{
//
//  AliAnalysisTaskUserStraneJets::RebinTH1D
//

  if ((!hF) || (!hR)) return 0x0;
//=============================================================================

  const Int_t nt = hR->GetNbinsX();
  const Int_t n  = nt;

  Double_t d[n+1];
  d[n] = hR->GetXaxis()->GetBinUpEdge(n);
  for (Int_t i=0, k=1; i<n; i++, k++) d[i] = hR->GetXaxis()->GetBinLowEdge(k);

  TH1D *hN = new TH1D(Form("hN_%s_%s",hF->GetName(),hR->GetName()), "", n, d); hN->Sumw2();

  for (Int_t k=1; k<=hF->GetNbinsX(); k++) {
    Double_t dXvar = hF->GetBinCenter(k);
    if ((dXvar<d[0]) || (dXvar>=d[n])) continue;

    Double_t dYvar = hF->GetBinContent(k);
    Double_t dYerr = hF->GetBinError(k);

    Int_t nb = hN->FindBin(dXvar);
    Double_t dYsw2 = hN->GetBinError(nb);

    hN->SetBinContent(nb, dYvar + hN->GetBinContent(nb));
    hN->SetBinError(nb, TMath::Sqrt(dYerr*dYerr + dYsw2*dYsw2));
  }

  return hN;
}

