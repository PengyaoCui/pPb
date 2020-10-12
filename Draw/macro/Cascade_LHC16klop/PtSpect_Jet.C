#include "./SourceFun.h"

//___________________________________________________________________
void PtSpect_Jet(){
  TString   sType[] = {"Xi"};//"XiPlus"; "XiMinus"
  TString sSaveName = "PtSpect_JetPt11";
  TString sTex = "#Xi";

  Bool_t IsEffCorr(1);
  Bool_t   IsUncer(1);

  Bool_t   IsAnaMC(0);//Draw MC Pt spect to compare with inclusive
  Bool_t IsAnaIncl(1);
  Bool_t   IsAnaJC(1);
  Bool_t   IsAnaJE(0);
  Bool_t   IsAnaPC(0);
  Bool_t   IsAnaOC(0);
  Bool_t   IsAnaNJ(0);

  Bool_t   IsSave(1);
  Bool_t  IsRebin(1);
  Bool_t   IsNorm(1);
//===================================================================
  TString sEventFilePath = "/home/cuipengyao/study/code/Uncertainty_Cascade/JetPt/Tight";

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
  if(IsRebin){
    const Double_t dPtBin[] = {2.0, 2.4, 2.8, 3.3, 4.0, 5.0, 6.5 };
    const Int_t nPtBin = sizeof(dPtBin)/sizeof(Double_t)-1;
    const TH1D* hRebin = new TH1D(Form("hRebin_%s", sOpt.Data()),"",nPtBin,dPtBin);
  }
  //-------------------------------------------------------------------
    TString   sMCEventList = Form("listLoopIncMC_%s_Default;1",sOpt.Data());
    TString sInclEventList = Form("listLoop1ndRD_%s_Default;1",sOpt.Data());
    TString  sJetEventList = Form("listLoopJetRD_%s_Default_PtJ22_JC;1",sOpt.Data());
    TString   sListNJEvent = Form("listLoopJetRD_%s_Default_PtJ22_NJ",sOpt.Data());
  //-------------------------------------------------------------------
  
    TString    sListMC = Form("listFitCbinMC_%s_Default;1",sOpt.Data());
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
    if (IsAnaMC){
      if (sEventFilePath.IsNull() || sMCEventFile.IsNull() || sMCEventList.IsNull() || sEvent.IsNull()) return;
      TH1D* hMCEvent = (TH1D*)GetTH1FromFile(sEventFilePath, sMCEventFile, sMCEventList, sEvent);
    }
    if (IsAnaIncl){
      if (sEventFilePath.IsNull() || sInclEventFile.IsNull() || sInclEventList.IsNull() || sEvent.IsNull()) return;
      TH1D* hInclEvent = (TH1D*)GetTH1FromFile(sEventFilePath, sInclEventFile, sInclEventList, sEvent);
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
      if (IsNorm) hPtMC = NormIncl(hPtMC, hMCEvent);
      NormBinSize(hPtMC);
      SetLine(hPtMC,cLine[i+1],sMark[i+1]);
      SetAxis(hPtMC, YMin, YMax, XMin, XMax, "d#it{#rho}/d#it{p}_{T}");
      if(IsSave) {file->cd(); hPtMC->Write(Form("hPtMC_%s", sOpt.Data()), TObject::kSingleKey);}
      hPtMC->Draw("same");
      leg->AddEntry(hPtMC,"MC","f");
    }
  
    if (IsAnaIncl){
      if (sListIncl.IsNull() || sEffIncl.IsNull()) return;
      TH1D*  hPtIncl = (TH1D*)GetTH1FromFile(sEventFilePath, sInclSpectFile, sListIncl, sObject);
      hPtIncl->SetName(Form("hPtIncl_%s", sOpt.Data()));
      if (IsEffCorr){
        TH1D* hEffIncl = (TH1D*)GetTH1FromFile(sEventFilePath, sEffInclFile, sEffIncl, sEff);
        hEffIncl->SetName(Form("hEffIncl_%s", sOpt.Data()));
        hPtIncl = RatioTH1D(hPtIncl, hEffIncl);
      }
      //if (IsRebin)hPtIncl = (TH1D*)RebinTH1D(hPtIncl, hRebin);
      if (IsNorm) hPtIncl = NormIncl(hPtIncl, hInclEvent);
      NormBinSize(hPtIncl);
      SetLine(hPtIncl,cLine[i],sMark[i]);
      SetAxis(hPtIncl, YMin, YMax, XMin, XMax, "d#it{#rho}/d#it{p}_{T}");
      if(IsSave) {file->cd(); hPtIncl->Write(Form("hPtIncl_%s", sOpt.Data()), TObject::kSingleKey);}
      hPtIncl->Draw("same");
      leg->AddEntry(hPtIncl,"Inclusive","lp");
      //leg->AddEntry(hPtIncl,"#Xi^{#pm}","lp");

      //Sys Uncertainty======>
      if (IsUncer){
        const Int_t n = 12;
        Double_t x[n] = {2.1, 2.3, 2.5, 2.7, 2.9, 3.15, 3.45, 3.8, 4.25, 4.75, 5.25, 6.};
        Double_t y[n] = NULL; for (Int_t k=8; k<hPtIncl->GetNbinsX(); k++){ y[k-8] = hPtIncl->GetBinContent(k); }
        Double_t ex[n] = {0.05, 0.05, 0.05, 0.05, 0.05, 0.06, 0.075, 0.11, 0.125, 0.125, 0.19, 0.275};
        Double_t ey[n] = {0.0314237*y[0], 0.0339172*y[1], 0.0350568*y[2], 0.042204*y[3], 0.0475007*y[4], 0.0449483*y[5], 0.0547504*y[6], 0.0568438*y[7], 0.0604477*y[8], 0.0544507*y[9], 0.0602186*y[10], 0.07328*y[11]};
        //for(Int_t m = 0; m<n; m++ ){cout<<ey[m]<<endl;}
        GrIncl = new TGraphErrors(n,x,y,ex,ey);
        GrIncl->SetFillStyle(0);
        GrIncl->SetLineWidth(2);
        GrIncl->SetLineColor(hPtIncl->GetLineColor());
        GrIncl->Draw("e2same");      
        if(IsSave) {file->cd(); GrIncl->Write(Form("GrIncl_%s", sOpt.Data()), TObject::kSingleKey);}
      }
    }
  
    if (IsAnaJC){
      if (sListJC.IsNull() || sEffJC.IsNull()) return;
      TH1D*  hPtJC = (TH1D*)GetTH1FromFile(sEventFilePath, sJetSpectFile, sListJC, sObject);
      hPtJC->SetName(Form("hPtJC_%s", sOpt.Data()));
      if (IsEffCorr) {
        TH1D* hEffJC = (TH1D*)GetTH1FromFile(sEventFilePath, sEffJetFile, sEffJC, sEff); 
        hEffJC->SetName(Form("hEffJC_%s", sOpt.Data()));
        hPtJC = RatioTH1D(hPtJC, hEffJC);
      }
      if (IsRebin) hPtJC = (TH1D*)RebinTH1D(hPtJC, hRebin);
      if (IsNorm) hPtJC = NormJC(hPtJC, hJetEvent);
      NormBinSize(hPtJC);
  
      SetLine(hPtJC,cLine[i+nType],sMark[i+nType]);
      //SetLine(hPtJC,cLine[i+3],sMark[i+3]);
      SetAxis(hPtJC, YMin, YMax, XMin, XMax, "d#it{#rho}/d#it{p}_{T}");
      if(IsSave) {file->cd();  hPtJC->Write(Form("hPtJC_%s", sOpt.Data()), TObject::kSingleKey);}
      //hPtJC->Draw("same");
      //leg->AddEntry(hPtJC,"JC","lp");
      //leg->AddEntry(hPtJC,"#Xi^{#pm}","lp");
 
     //Sys Uncertainty======>
      if (IsUncer){
        const Int_t n = 6;
        Double_t x[n] = {2.2, 2.6, 3.05, 3.65, 4.5, 5.75};
        Double_t y[n] = NULL; for (Int_t k=1; k<=hPtJC->GetNbinsX(); k++){ y[k-1] = hPtJC->GetBinContent(k); }
        Double_t ex[n] = {0.1, 0.1, 0.11, 0.15, 0.21, 0.3};
        Double_t ey[n] = {0.000230764, 0.000219466, 8.56689e-05, 0.00016243, 2.87578e-05, 2.12455e-05}; 

      //for(Int_t m = 0; m<6; m++ ){cout<<ey[m]<<endl;}
      //Double_t eI[n] ={ 0.042832, 0.0480318, 0.0560362, 0.0641628, 0.0642275, 0.0771022};
      //Double_t eJ[n] ={ 0.0591979, 0.0553908, 0.0288977, 0.0813561, 0.0241927, 0.0459242};
      //for(Int_t m = 0; m<6; m++ ){cout<<TMath::Sqrt(eI[m]*eI[m] + eJ[m]*eJ[m])<<endl;}
        GrJC = new TGraphErrors(n,x,y,ex,ey);
        GrJC->SetFillStyle(0);
        GrJC->SetLineWidth(2);
        GrJC->SetLineColor(hPtJC->GetLineColor());
        //GrJC->Draw("e2same");      
        if(IsSave) {file->cd(); GrJC->Write(Form("GrJC_%s", sOpt.Data()), TObject::kSingleKey);}
      }
    }
  
    if (IsAnaPC){
      if (sListPCL.IsNull() || sListPCU.IsNull() || sEffPCL.IsNull() || sEffPCU.IsNull()) return;
      TH1D*  hPtPCL = (TH1D*)GetTH1FromFile(sEventFilePath, sJetSpectFile, sListPCL, sObject);
      hPtPCL->SetName(Form("hPtPCL_%s", sOpt.Data()));
      if (IsEffCorr){
        TH1D* hEffPCL = (TH1D*)GetTH1FromFile(sEventFilePath, sEffJetFile, sEffPCL, sEff);
        hEffPCL->SetName(Form("hEffPCL_%s", sOpt.Data()));
        hPtPCL = RatioTH1D(hPtPCL, hEffPCL);
      }
  
      TH1D*  hPtPCU = (TH1D*)GetTH1FromFile(sEventFilePath, sJetSpectFile, sListPCU, sObject);
      hPtPCU->SetName(Form("hPtPCU_%s", sOpt.Data()));
      if (IsEffCorr){
        TH1D* hEffPCU = (TH1D*)GetTH1FromFile(sEventFilePath, sEffJetFile, sEffPCU, sEff);
        hEffPCU->SetName(Form("hEffPCU_%s", sOpt.Data()));
        hPtPCU = RatioTH1D(hPtPCU, hEffPCU);
      }
      hPtPCL->Add(hPtPCU);
      TH1D *hPtPC = hPtPCL; 
      hPtPC->SetName(Form("hPtPC_%s", sOpt.Data()));
      if (IsRebin)hPtPC = (TH1D*)RebinTH1D(hPtPC, hRebin);
      hPtPC->SetName(Form("hPtPC_%s", sOpt.Data()));
      if (IsNorm) hPtPC = NormPC(hPtPC, hJetEvent);
      hPtPC->SetName(Form("hPtPC_%s", sOpt.Data()));
      NormBinSize(hPtPC);
      //SetLine(hPtPC,kRed,24);
      SetLine(hPtPC,cLine[i+2*nType],sMark[i+2*nType]);
      SetAxis(hPtPC, YMin, YMax, XMin, XMax, "d#it{#rho}/d#it{p}_{T}");
      if(IsSave) {file->cd();  hPtPC->Write(Form("hPtPC_%s", sOpt.Data()), TObject::kSingleKey);}
      hPtPC->Draw("same");
      leg->AddEntry(hPtPC,"UE","lp");
      //for(Int_t m = 1; m<= hPtPC->GetNbinsX(); m++){ cout<<hPtPC->GetXaxis()->GetBinCenter(m)<<endl;}
//
     //Sys Uncertainty======>
      if (IsUncer){
        const Int_t n = 6;
        Double_t x[n] = {2.2, 2.6, 3.05, 3.65, 4.5, 5.75};
        Double_t y[n] = NULL; for (Int_t k=1; k<=hPtPC->GetNbinsX(); k++){ y[k-1] = hPtPC->GetBinContent(k); }

        Double_t ex[n] = {0.1, 0.1, 0.11, 0.15, 0.21, 0.3};
        Double_t ey[n] = {0.042832*y[0], 0.0480318*y[1], 0.0560362*y[2], 0.0641628*y[3], 0.0642275*y[4], 0.0771022*y[5]};
        //Double_t ey[n] = {0.000533124, 0.000389618, 0.000273601, 0.000166906, 6.99756e-05, 1.58154e-05};

        GrPC = new TGraphErrors(n,x,y,ex,ey);
        GrPC->SetFillStyle(0);
        GrPC->SetLineWidth(2);
        GrPC->SetLineColor(hPtPC->GetLineColor());
        GrPC->Draw("e2same");      
        if(IsSave) {file->cd(); GrPC->Write(Form("GrPC_%s", sOpt.Data()), TObject::kSingleKey);}
      }
    }
  
    if (IsAnaJE){
      if (!hPtJC || !hPtPC) return;
      TH1D* hPtJE = (TH1D*) hPtJC->Clone("hPtJE");
      hPtJE->SetName(Form("hPtJE_%s", sOpt.Data()));
      TH1D* hPtUE = (TH1D*) hPtPC->Clone("hPtUE");
      hPtUE->SetName(Form("hPtUE_%s", sOpt.Data()));
      hPtJE = (TH1D*)Subtract(hPtJE, hPtUE);
      //SetLine(hPtJE,kBlue,25);
      SetLine(hPtJE,cLine[1],sMark[1]);
      //SetLine(hPtJE,cLine[i+nType],sMark[i+nType]);
      if(IsSave) {file->cd();  hPtJE->Write(Form("hPtJE_%s", sOpt.Data()), TObject::kSingleKey);}
      hPtJE->Draw("same");
      leg->AddEntry(hPtJE,"JE","lp");
     //Sys Uncertainty======>
      if (IsUncer){
        const Int_t n = 6;
        Double_t x[n] = {2.2, 2.6, 3.05, 3.65, 4.5, 5.75};
        Double_t y[n] = NULL; for (Int_t k=1; k<=hPtJE->GetNbinsX(); k++){ y[k-1] = hPtJE->GetBinContent(k); }

        Double_t ex[n] = {0.1, 0.1, 0.1, 0.1, 0.1, 0.1};
        Double_t ey3[n] = {0.000873634, 0.000986836, 0.000753126, 0.000535095, 0.000327165, 0.000130094};
        Double_t ey1[n] = {0.042832*y[0], 0.0480318*y[1], 0.0560362*y[2], 0.0641628*y[3], 0.0642275*y[4], 0.0771022*y[5]};
        Double_t ey2[n] = {0.000227806*y[0], 0.000217874*y[1], 8.38218e-05*y[2], 0.000162133*y[3], 2.8552e-05*y[4], 2.12216e-05*y[5]};
        Double_t ey[n] = NULL; for(Int_t p = 0; p<n; p++){ey[p] = TMath::Sqrt(ey1[p]*ey1[p] + ey2[p]*ey2[p] + ey3[p]*ey3[p]); cout<<ey1[p]<<endl;}
     //Double_t eyP[n] = {0.000533124, 0.000389618, 0.000273601, 0.000166906, 6.99756e-05, 1.58154e-05};
      //Double_t eyJ[n] = {0.000230764, 0.000219466, 8.56689e-05, 0.00016243, 2.87578e-05, 2.12455e-05};
      //for(Int_t m = 0; m< 6; m++){ cout<<TMath::Sqrt(eyP[m] * eyP[m] + eyJ[m]*eyJ[m])<<endl;}
                           
        GrJE = new TGraphErrors(n,x,y,ex,ey);
        GrJE->SetFillStyle(0);
        GrJE->SetLineWidth(2);
        GrJE->SetLineColor(hPtJE->GetLineColor());
        GrJE->Draw("e2same");      
        if(IsSave) {file->cd(); GrJE->Write(Form("GrJE_%s", sOpt.Data()), TObject::kSingleKey);}
      } 
    }


    if (IsAnaOC){
      if (sListOC.IsNull() || sEffOC.IsNull()) return;
      TH1D*  hPtOC = (TH1D*)GetTH1FromFile(sEventFilePath, sJetSpectFile, sListOC, sObject);
      hPtOC->SetName(Form("hPtOC_%s", sOpt.Data()));
      if (IsEffCorr){
        TH1D* hEffOC = (TH1D*)GetTH1FromFile(sEventFilePath, sEffJetFile, sEffOC, sEff);
        hEffOC->SetName(Form("hEffOC_%s", sOpt.Data()));
        hPtOC = RatioTH1D(hPtOC, hEffOC);

      }
      if (IsRebin) hPtOC = (TH1D*)RebinTH1D(hPtOC, hRebin);
      if (IsNorm) TH1D* hPtOC = NormOC(hPtOC, hJetEvent);
      NormBinSize(hPtOC);
      //SetLine(hPtOC, kRed+3, 22);
      SetLine(hPtOC,cLine[i],sMark[i]);
      SetAxis(hPtOC, YMin, YMax, XMin, XMax, "d#it{#rho}/d#it{p}_{T}");
      if(IsSave) {file->cd(); hPtOC->Write(Form("hPtOC_%s", sOpt.Data()), TObject::kSingleKey);}
      hPtOC->Draw("same");
      leg->AddEntry(hPtOC,"OC","lp");
    }
  
    if (IsAnaNJ){
    if (sListNJ.IsNull() || sEffNJ.IsNull()) return;
      TH1D*  hPtNJ = (TH1D*)GetTH1FromFile(sEventFilePath, sJetSpectFile, sListNJ, sObject);
      hPtNJ->SetName(Form("hPtNJ_%s", sOpt.Data()));
      if (IsEffCorr){
        TH1D* hEffNJ = (TH1D*)GetTH1FromFile(sEventFilePath, sEffJetFile, sEffNJ, sEff);
        hEffNJ->SetName(Form("hEffNJ_%s", sOpt.Data()));
        hPtNJ = RatioTH1D(hPtNJ, hEffNJ);
      }
      if (IsNorm) TH1D* hPtNJ = NormNJ(hPtNJ, hNJEvent);
      if (IsRebin) hPtNJ = (TH1D*)RebinTH1D(hPtNJ, hRebin);
      NormBinSize(hPtNJ);

      //SetLine(hPtNJ, kMagenta+2, 23);
      SetLine(hPtNJ,cLine[i+nType],sMark[i+nType]);
      SetAxis(hPtNJ, YMin, YMax, XMin, XMax, "d#it{#rho}/d#it{p}_{T}");
      if(IsSave) {file->cd(); hPtNJ->Write(Form("hPtNJ_%s", sOpt.Data()), TObject::kSingleKey);}
      hPtNJ->Draw("same");
      //for(Int_t m = 1; m<= hPtOC->GetNbinsX(); m++){ cout<<TMath::Abs(TMath::Sqrt(1./12.)*0.5*(hPtOC->GetBinContent(m) - hPtNJ->GetBinContent(m)))<<endl;}
      //for(Int_t m = 1; m<= hPtOC->GetNbinsX(); m++){ 
      //  Double_t dOC = hPtOC->GetBinContent(m);
      //  Double_t dJC = hPtJC->GetBinContent(m);
      //  Double_t dNJ = hPtNJ->GetBinContent(m);
      //  if(TMath::Abs(dJC - dOC) >=TMath::Abs(dJC - dNJ)){
      //    cout<<TMath::Sqrt(1./12.)*TMath::Abs(dJC - dOC)<<endl;
      //  }else{
      //    cout<<TMath::Sqrt(1./12.)*TMath::Abs(dJC - dNJ)<<endl;
      //  }
      ////cout<<TMath::Abs(TMath::Sqrt(1./12.)*0.5*(hPtOC->GetBinContent(m) - hPtNJ->GetBinContent(m)))<<endl;
      //}
      leg->AddEntry(hPtNJ,"NJ","lp");
    }
  }
      
  if (IsUncer) leg->AddEntry(GrIncl, "Sys.Error", "f");
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
  tex->DrawLatex(0.17, 0.91, "ALICE p-p #sqrt{s} = 13 TeV");
  tex->DrawLatex(0.17, 0.84, sTex);
  tex->DrawLatex(0.17, 0.77, "|#eta| < 0.75");
  leg->Draw();
  if(IsSave) { file->Close();}

  return;
}

