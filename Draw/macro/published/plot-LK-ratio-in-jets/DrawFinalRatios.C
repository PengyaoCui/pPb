#include "TROOT.h"
#include "TSystem.h"
#include "TString.h"
#include "TFile.h"
#include "TDirectoryFile.h"
#include "TList.h"
#include "TMath.h"

#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "THnSparse.h"
#include "TF1.h"
#include "TFitResultPtr.h"
#include "TFitResult.h"
#include "TMatrixDSym.h"

#include "TStyle.h"
#include "TAttMarker.h"
#include "TAttLine.h"
#include "TCanvas.h"
#include "TGraphErrors.h"
#include "TGraphAsymmErrors.h"
#include "TMultiGraph.h"
#include "TLatex.h"
#include "TLine.h"
#include "TLegend.h"

#include "AuxROOTFunctions.h"
#include "AuxFunctions.h"

TString sEnergy = "#sqrt{#it{s}_{NN}} = 2.76 TeV";
TString sSystem = "Pb#minusPb";
TString sCent = "0#minus10 %";
Float_t nCollCentBins[6] = {1502.7, 923.26, 438.8, 128.2, 26.82, 450.33}; // https://twiki.cern.ch/twiki/bin/viewauth/ALICE/CentStudies#Tables_with_centrality_bins_for
Float_t rcpErrorCent[4] = {0.1455895292, 0.1416009451, 0.1357282295, 0.1350063077}; // syst. error of ncoll ratios
Float_t maxYRho[3] = {200., 100., 40.};
Float_t etaNormalisation = 1.8;

TString V0Name[3] = {"K0s", "Lambda", "ALambda"};
TString V0Symbol[3] = {"K^{0}_{S}", "#Lambda", "#bar{#Lambda}"};
TString V0LabelM[3] = {"#it{m}_{inv} K_{S}^{0} (GeV/#it{c}^{2})", "#it{m}_{inv} #Lambda (GeV/#it{c}^{2})", "#it{m}_{inv} #bar{#Lambda} (GeV/#it{c}^{2})"};
Float_t fMassV0[3] = {0.497614, 1.115680, 1.115680};

// Global ranges
// centrality bins
Int_t iCentMin = 0;
Int_t iCent = 0;
//Int_t iCentMax = iNCentBins-1;
Int_t iCentMax = 0;
// jet pT bins
Int_t iJetMin = 1;
//Int_t iJetMax = iNBinsPtJet-1;
Int_t iJetMax = 2;

Bool_t bInclusive = 0;
Bool_t bInclusiveOff = 1;
Bool_t bInJets = 1;
Bool_t bInBulk = 0;

TString sYear = "2011";

Float_t fEtaV0Max = 0.7;
Float_t fRadiusJet = 0.2;
Float_t fEtaJetMax = fEtaV0Max - fRadiusJet;

//TString sLabelsYAxisRatio = "#Lambda/K_{S}^{0}";
TString sLabelsYAxisRatio = "(#Lambda #plus #bar{#Lambda})/2K_{S}^{0}";

void DrawFinalRatios(TString sNameFileInR, TString sNameFileSysJets, TString sNameFileSysBulk, TString sNameFileSysJetsFD = "")
{
  gStyle->SetCanvasColor(10);
  gStyle->SetStatColor(10);
  gStyle->SetPadColor(10);
  gStyle->SetOptStat(0);

//  TString sLabelCollisionText = Form("#splitline{%s, %s,}{%s}",sSystem.Data(),sYear.Data(),sEnergy.Data());
//  TString sLabelCollisionText = Form("#splitline{%s %s}{%s}", sSystem.Data(), sCent.Data(), sEnergy.Data());
  TString sLabelCollisionText = Form("%s, %s, %s", sSystem.Data(), sEnergy.Data(), sCent.Data());
  TLatex* labelCollision = new TLatex();
  labelCollision->SetTextFont(42);
  labelCollision->SetTextSize(0.03);
  labelCollision->SetTextAlign(13);
  TLatex* labelPt;

  TString sLabelALICE = Form("#splitline{ALICE}{Preliminary}");
  TLatex* labelALICE = new TLatex();
  labelALICE->SetTextFont(42);
  labelALICE->SetTextSize(0.035);
  labelALICE->SetTextAlign(13);

  TString sLabelSettings = Form("#splitline{|#it{#eta}_{V^{0}}| < %g}{\
#splitline{anti-#it{k}_{t}, #it{R} = %g}{\
#splitline{|#it{#eta}_{jet,ch}| < %g}{\
#splitline{#it{p}_{T}^{leading track} > 5 GeV/#it{c}}{\
#it{p}_{T}^{track} > 150 MeV/#it{c}\
}}}}", fEtaV0Max, fRadiusJet, fEtaJetMax);
  TLatex* labelSettings = new TLatex();
  labelSettings->SetTextFont(42);
  labelSettings->SetTextSize(0.03);
  labelSettings->SetTextAlign(13);
//#splitline{#color[1]{anti-#it{k}_{t}, #it{R} = %g}}{\
//  labelSettings->SetTextColor(kGray+2);

//  TLegend* legend;

  // canvas size
  Int_t iCanHeight = 600;
  Int_t iCanWidth = 600;

  //TString kImageSuf = "png";
  TString kImageSuf = "eps";

  TString sNameFileInK = "OutputK0s.root";
  TString sNameFileInL = "OutputLambda.root";
  TString sNameFileInAL = "OutputALambda.root";
  TString sNameDirPt = "Spectra";
  TString sNameFileOut = "OutputRatio.root";

  // input
  TString sNameHisInclusive = "fh1PtInclusive%s_C%d";
  TString sNameHisInJets = "fh1PtInJets%s_C%d-J%d";
  TString sNameHisInBulk = "fh1PtInBulk%s_C%d";
  TString sNameHisGenInclusive = "fh1PtGenInclusive%s_C%d";
  // output
  TString sNameHisRatioInclusive = "fh1PtRatioInclusive_%d";
  TString sNameHisRatioInJets = "fh1PtRatioInJets_C%d-J%d";
  TString sNameHisRatioInBulk = "fh1PtRatioInBulk_C%d";

  TString sNameHisRatioInJetsSys = "grExtremesCombinedRatio_C%d-J%d";
  TString sNameHisRatioInBulkSys = "grExtremesCombinedRatio_C%d";

  printf("Loading file %s ", sNameFileInR.Data());
  TFile* fileR = 0;
  fileR = new TFile(sNameFileInR.Data(), "OPEN");
  if(fileR->IsZombie())
  {
    printf("failed\nDrawRatios: Error: Cannot load file %s\n", sNameFileInR.Data());
    return;
  }
  printf("OK\n");

  printf("Loading file %s ", sNameFileSysJets.Data());
  TFile* fileRSysJ = 0;
  fileRSysJ = new TFile(sNameFileSysJets.Data(), "OPEN");
  if(fileRSysJ->IsZombie())
  {
    printf("failed\nDrawRatios: Error: Cannot load file %s\n", sNameFileSysJets.Data());
    return;
  }
  printf("OK\n");

  TFile* fileRSysJFD = 0;
  if(sNameFileSysJetsFD.Length())
  {
    printf("Loading file %s ", sNameFileSysJetsFD.Data());
    fileRSysJFD = new TFile(sNameFileSysJetsFD.Data(), "OPEN");
    if(fileRSysJFD->IsZombie())
    {
      printf("failed\nDrawRatios: Error: Cannot load file %s\n", sNameFileSysJetsFD.Data());
      return;
    }
    printf("OK\n");
  }

  TFile* fileRSysB = 0;
  if(bInBulk)
  {
    printf("Loading file %s ", sNameFileSysBulk.Data());
    fileRSysB = new TFile(sNameFileSysBulk.Data(), "OPEN");
    if(fileRSysB->IsZombie())
    {
      printf("failed\nDrawRatios: Error: Cannot load file %s\n", sNameFileSysBulk.Data());
      return;
    }
    printf("OK\n");
  }

  TString sNameFileOfficial = "./k0s_lambda_final_spectra.root";
  printf("Loading file %s ", sNameFileOfficial.Data());
  TFile* fileOff = 0;
  fileOff = new TFile(sNameFileOfficial.Data(), "OPEN");
  if(fileOff->IsZombie())
  {
    printf("failed\nDrawRatios: Error: Cannot load file %s\n", sNameFileOfficial.Data());
    return;
  }
  printf("OK\n");

  Float_t fPtInJetsXMin = 0; // minimum x value
  Float_t fPtInJetsXMax = 12; // maximum x value

  Int_t iPointMinJets = 4;
  Int_t iPointMaxJets = 8;
  Int_t iPointMinBulk = 1;
  Int_t iPointMaxBulk = 8;
  Int_t iPointMinIncl = 6;
  Int_t iPointMaxIncl = 40;

  TCanvas* canRatioCompare;
  TMultiGraph* mgrRatioCompare;
  TMultiGraph* mgrRatioCompareSys;
  TLegend* legRatioCompare;
  TLegend* legRatioOff;
  canRatioCompare = new TCanvas(Form("canRatioCompare%d", iCent), "", iCanWidth, iCanHeight);
  mgrRatioCompare = new TMultiGraph();
  mgrRatioCompareSys = new TMultiGraph();
  legRatioCompare = new TLegend(0.45, 0.65, 0.85, 0.82);
  legRatioOff = new TLegend(0.45, 0.55, 0.85, 0.63);

  for(Int_t iJet = 1; iJet <= iJetMax; iJet++)
  {
    TH1D* hisRatioInJets = (TH1D*)fileR->Get(Form(sNameHisRatioInJets.Data(), iCent, iJet));
    if(!hisRatioInJets)
    {
      printf("DrawRatios: Error: Cannot load histogram %s\n", Form(sNameHisRatioInJets.Data(), iCent, iJet));
      return;
    }
    TGraphErrors* grRatioInJets = MakeGraphErrors(hisRatioInJets, Form("in jets, #it{p}_{T}^{jet,ch} > %.0f GeV/#it{c}", dBinsPtJet[iJet]), alicolors[iJet], alimarkers[iJet], alisizes[iJet]);
    TGraphAsymmErrors* grRatioInJetsSys = (TGraphAsymmErrors*)fileRSysJ->Get(Form(sNameHisRatioInJetsSys.Data(), iCent, iJet));
    if(!grRatioInJetsSys)
    {
      printf("DrawRatios: Error: Cannot load histogram %s\n", Form(sNameHisRatioInJetsSys.Data(), iCent, iJet));
      return;
    }
    TGraphAsymmErrors* grRatioInJetsSysFD = 0;
    if(sNameFileSysJetsFD.Length())
    {
      TString sNameGrFD = Form("grExtremesRatio_C%d-J%d", iCent, iJet);
      grRatioInJetsSysFD = (TGraphAsymmErrors*)fileRSysJFD->Get(sNameGrFD.Data());
      if(!grRatioInJetsSysFD)
      {
        printf("DrawRatios: Error: Cannot load histogram %s in FD file\n", sNameGrFD.Data());
        return;
      }
    }
    for(Int_t iPoint = 0; iPoint < grRatioInJets->GetN(); iPoint++)
    {
      if(iPoint >= iPointMinJets && iPoint <= iPointMaxJets)
        continue;
      grRatioInJets->SetPoint(iPoint, -2, 0);
      grRatioInJetsSys->SetPoint(iPoint, -2, 0);
      grRatioInJetsSysFD->SetPoint(iPoint, -2, 0);
    }
    if(sNameFileSysJetsFD.Length())
    {
      SetGraphAsymmErrors(grRatioInJetsSysFD, Form("FD: #it{p}_{T}^{jet,ch} > %.0f GeV/#it{c}", dBinsPtJet[iJet]), alicolors[iJet] - 5, alimarkers[iJet], alisizes[iJet]);
      grRatioInJetsSysFD->SetFillStyle(3144);
      grRatioInJetsSysFD->SetFillColor(alicolors[iJet] - 5);
      mgrRatioCompare->Add(grRatioInJetsSysFD, "2");
    }
    mgrRatioCompare->Add(grRatioInJets);
    legRatioCompare->AddEntry(grRatioInJets);
    SetGraphAsymmErrors(grRatioInJetsSys, Form("jets: #it{p}_{T}^{jet,ch} > %.0f GeV/#it{c}", dBinsPtJet[iJet]), alicolors[iJet], alimarkers[iJet], alisizes[iJet]);
    mgrRatioCompare->Add(grRatioInJetsSys, "2");
    if(sNameFileSysJetsFD.Length() && iJet == iJetMax)
    {
      TGraphAsymmErrors* grRatioInJetsSysFDLeg = new TGraphAsymmErrors();
      grRatioInJetsSysFDLeg->SetFillStyle(3144);
      grRatioInJetsSysFDLeg->SetFillColor(kGray);
      grRatioInJetsSysFDLeg->SetTitle("feed-down uncertainty");
      grRatioInJetsSysFDLeg->SetLineColor(kGray);
      grRatioInJetsSysFDLeg->SetMarkerColor(-1);
      grRatioInJetsSysFDLeg->SetMarkerStyle(-1);
//      grRatioInJetsSysFDLeg->SetMarkerSize(size);
      legRatioCompare->AddEntry(grRatioInJetsSysFDLeg);
    }
  }
  if(bInBulk)
  {
    TH1D* hisRatioInBulk = (TH1D*)fileR->Get(Form(sNameHisRatioInBulk.Data(), iCent));
    if(!hisRatioInBulk)
    {
      printf("DrawRatios: Error: Cannot load histogram %s\n", Form(sNameHisRatioInBulk.Data(), iCent));
      return;
    }
    TGraphErrors* grRatioInBulk = MakeGraphErrors(hisRatioInBulk, Form("in underlying event"), alicolors[3], alimarkers[3], alisizes[3]);
    TGraphAsymmErrors* grRatioInBulkSys = (TGraphAsymmErrors*)fileRSysB->Get(Form(sNameHisRatioInBulkSys.Data(), iCent));
    if(!grRatioInBulkSys)
    {
      printf("DrawRatios: Error: Cannot load histogram %s\n", Form(sNameHisRatioInBulkSys.Data(), iCent));
      return;
    }
    for(Int_t iPoint = 0; iPoint < grRatioInBulk->GetN(); iPoint++)
    {
      if(iPoint >= iPointMinBulk && iPoint <= iPointMaxBulk)
        continue;
      grRatioInBulk->SetPoint(iPoint, -2, 0);
      grRatioInBulkSys->SetPoint(iPoint, -2, 0);
    }
    mgrRatioCompare->Add(grRatioInBulk);
    legRatioCompare->AddEntry(grRatioInBulk);
    SetGraphAsymmErrors(grRatioInBulkSys, Form("underlying event"), alicolors[3], alimarkers[3], alisizes[3]);
    mgrRatioCompare->Add(grRatioInBulkSys, "2");
  }

  if(bInclusiveOff)
  {
    TString sNameHisOff = "statonly_cent0005_LambdaK0s";
    TString sNameHisOffSys = "systonly_cent0005_LambdaK0s";
    TH1D* hisRatioOff = (TH1D*)fileOff->Get(Form(sNameHisOff.Data(), iCent));
    if(!hisRatioOff)
    {
      printf("DrawRatios: Error: Cannot load histogram %s\n", Form(sNameHisOff.Data(), iCent));
      return;
    }
    TGraphErrors* grRatioOff = MakeGraphErrors(hisRatioOff, "#splitline{inclusive #Lambda/K^{0}_{S}, ALICE,}{(0#minus5 %, |#it{y}_{V^{0}}| < 0.5)}", alicolors[0], alimarkers[0], alisizes[0]);
    TH1D* hisRatioOffSys = (TH1D*)fileOff->Get(Form(sNameHisOffSys.Data(), iCent));
    if(!hisRatioOffSys)
    {
      printf("DrawRatios: Error: Cannot load histogram %s\n", Form(sNameHisOffSys.Data(), iCent));
      return;
    }
    TGraphErrors* grRatioOffSys = MakeGraphErrors(hisRatioOffSys, "inclusive 0-5 %", alicolors[0], alimarkers[0], alisizes[0]);
    for(Int_t iPoint = 0; iPoint < grRatioOff->GetN(); iPoint++)
    {
      if(iPoint >= iPointMinIncl && iPoint <= iPointMaxIncl)
        continue;
//      grRatioOff->RemovePoint(iPoint);
//      grRatioOffSys->RemovePoint(iPoint);
      grRatioOff->SetPoint(iPoint, -2, 0);
      grRatioOffSys->SetPoint(iPoint, -2, 0);
    }
    grRatioOffSys->SetFillStyle(0);
    mgrRatioCompare->Add(grRatioOff);
//    legRatioCompare->AddEntry(grRatioOff);
    legRatioOff->AddEntry(grRatioOff);
    mgrRatioCompare->Add(grRatioOffSys, "2");
  }

  canRatioCompare->cd();
  canRatioCompare->SetTicks(1, 1);
//  canRatioCompare->SetGrid(1,1);
//  canRatioCompare->SetLineColor(kGray);
  canRatioCompare->SetLeftMargin(0.15);
//  mgrRatioCompare->SetTitle(Form("Baryon-meson ratios, c. %s;#Lambda/K_{S}^{0}",GetCentBinLabel(iCent).Data()));
  mgrRatioCompare->SetTitle("");
  mgrRatioCompare->SetMinimum(0);
  mgrRatioCompare->SetMaximum(2);
  mgrRatioCompare->Draw("AP");
  mgrRatioCompare->GetXaxis()->SetTitle("#it{p}_{T} (GeV/#it{c})");
  mgrRatioCompare->GetYaxis()->SetTitle(sLabelsYAxisRatio.Data());
  mgrRatioCompare->GetYaxis()->SetTitleOffset(1.7);
  mgrRatioCompare->GetXaxis()->SetRangeUser(fPtInJetsXMin, fPtInJetsXMax);
  SetLegend(legRatioCompare, 0.03);
  legRatioCompare->Draw();
  SetLegend(legRatioOff, 0.03);
  legRatioOff->Draw();

  labelPt = labelCollision->DrawLatex(5, 1.9, sLabelCollisionText.Data());
  labelPt = labelALICE->DrawLatex(0.5, 1.9, sLabelALICE.Data());
  labelPt = labelSettings->DrawLatex(7.0, 1.0, sLabelSettings.Data());
  if(bInclusiveOff)
    canRatioCompare->SaveAs(Form("canRatioCompareOff_C%d.%s", iCent, kImageSuf.Data()));
  else
    canRatioCompare->SaveAs(Form("canRatioCompare_C%d.%s", iCent, kImageSuf.Data()));
  delete canRatioCompare;
  delete mgrRatioCompare;
  delete mgrRatioCompareSys;

  printf("End\n");
}
