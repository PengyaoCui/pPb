const UInt_t kCjeN = 7;
const Double_t dvx[] = {  0.10, 0.25, 0.35, 0.50, 0.70, 0.95, 1.30 };
const Double_t dex[] = {  0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02 };
const Double_t der[] = {  0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00 };

const TString sFxnN[] = { "BGBlastWave", "LevyTsallis" };

enum { kValY=1, kErrY, kErlY, kErhY, kValM, kErrM, kErlM, kErhM };
//=============================================================================

void PlotMeanPt_V0VJ(const UInt_t kAct = 1,
                     const UInt_t kPtj = 0,
                     const UInt_t kOut = 0)
{
  const TString sWorkDir = gSystem->WorkingDirectory();
  const TString sPckgDir = gSystem->DirName(sWorkDir.Data());
  const TString sUtilDir = Form("%s/util", sPckgDir.Data());

  gROOT->LoadMacro(Form("%s/TUtilsOpHisto.h",sUtilDir.Data()));
  gROOT->LoadMacro(Form("%s/TUtilsToolV0s.h",sUtilDir.Data()));
  gROOT->LoadMacro(Form("%s/TUtilsResults.h",sUtilDir.Data()));
  gROOT->LoadMacro(Form("%s/TUtilsMeanPtV.h",sUtilDir.Data()));
  gROOT->LoadMacro(Form("%s/TUtilsPlotStd.h",sUtilDir.Data()));
  gROOT->LoadMacro(Form("%s/TUtilsAliFigs.h",sUtilDir.Data())); SetStyle(); 
//=============================================================================

  TGraphAsymmErrors *gKstatVJ = GetStat(kAct, kPtj, kBin07, kKshort, 1, "VJ"); gKstatVJ->SetName("gKstatVJ");
  TGraphAsymmErrors *gKsystVJ = GetSyst(kAct, kPtj, kBin07, kKshort, 1, "VJ"); gKsystVJ->SetName("gKsystVJ");

  TGraphAsymmErrors *gLstatVJ = GetStat(kAct, kPtj, kBin21, kLambda, 1, "VJ"); gLstatVJ->SetName("gLstatVJ");
  TGraphAsymmErrors *gLsystVJ = GetSyst(kAct, kPtj, kBin21, kLambda, 1, "VJ"); gLsystVJ->SetName("gLsystVJ");
//=============================================================================

  TH1F    *frm = 0;
  TCanvas *can = 0;
  TLegend *leg = 0;
  TLatex  *tex = 0;
  TLine  *line = 0;

  const Float_t dflx =  0.0, dfux = 1.5;
  const Float_t dfly =  0.0, dfuy = 8.0;

  const Float_t dlsx = 0.05, dlsy = 0.05;
  const Float_t dtsx = 0.06, dtsy = 0.06;
  const Float_t dtox = 1.10, dtoy = 1.00;

  const TString stnx = "#it{R}(V^{0},jet)";
  const TString stny = "<#it{p}_{T}> (GeV/#it{c})";

  TH1D *hStatE = new TH1D("hStatE", "", 100, dflx, dfux);
  hStatE->SetLineWidth(2);
  hStatE->SetLineColor(1);
  hStatE->SetMarkerStyle(wmk[0]);
  hStatE->SetMarkerColor(1);

  TH1D *hSystE = new TH1D("hSystE", "", 100, dflx, dfux);
  hSystE->SetLineWidth(2);
  hSystE->SetLineColor(1);
  hSystE->SetFillStyle(0);
  hSystE->SetFillColor(1);
//=============================================================================

  const TString sCanN = Form("MeanPt_V0VJ_%s_%s", sActN[kAct].Data(), sPtjN[kPtj].Data());

  can = MakeCanvas(sCanN);
  can->SetGridx(); can->SetGridy();
  frm = can->DrawFrame(dflx, dfly, dfux, dfuy);
  SetupFrame(frm, dlsx, dlsy, dtsx, dtsy, dtox, dtoy, stnx, stny);

  DrawGraph(gKstatVJ, wcl[1], wmk[1], "P"); DrawGraph(gKsystVJ, wcl[1], "E2");
  DrawGraph(gLstatVJ, wcl[3], wmk[1], "P"); DrawGraph(gLsystVJ, wcl[3], "E2");

  leg = new TLegend(0.68, 0.66, 0.96, 0.80); SetupLegend(leg);
  leg->AddEntry(gKstatVJ, "K_{S}^{0}",               "LP")->SetTextSizePixels(24);
  leg->AddEntry(gLstatVJ, "(#Lambda+#bar{#Lambda})", "LP")->SetTextSizePixels(24);
  leg->Draw();

/*leg = new TLegend(0.54, 0.52, 0.76, 0.66); SetupLegend(leg);
  leg->AddEntry(hStatE, sErrL[kStat], "LEP")->SetTextSizePixels(24);
  leg->AddEntry(hSystE, sErrL[kSyst], "F")->SetTextSizePixels(24);
  leg->Draw();*/

  tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.16, 0.90, Form("p-Pb #sqrt{s_{NN}}=5.02 TeV, %s", sActL[kAct].Data()));
  tex->DrawLatex(0.16, 0.82, Form("anti-#it{k}_{T}, %s, |#eta_{jet}|<0.35, |#eta_{V^{0}}|<0.75", sPtjL[kPtj].Data()));
  CanvasEnd(can);
//=============================================================================

  if (kOut==1) can->Print(Form("c%s.pdf",sCanN.Data()));


  return;
}

//_____________________________________________________________________________
TGraphAsymmErrors *GetStat(const UInt_t  kAct,
                           const UInt_t  kPtj,
                           const UInt_t  kBin,
                           const UInt_t  kVar,
                           const UInt_t  kFxn,
                           const TString sOpt)
{
  Double_t dvy[kCjeN];
  Double_t dey[kCjeN];
  TFile *file = TFile::Open(Form("data/AnaYieldMean%s.root",sOpt.Data()), "READ");
  for (UInt_t kCje=0; kCje<kCjeN; kCje++) {
    TString sHist = Form("h%s_%s", sVarN[kVar].Data(), sFxnN[kFxn].Data());
    TString sList = Form("list_%s_%s_%s_%s_Out", sCjeN[kCje].Data(),
                                                 sActN[kAct].Data(),
                                                 sPtjN[kPtj].Data(),
                                                 sBinN[kBin].Data());

    dvy[kCje] = ((TH1D*)((TList*)file->Get(sList.Data()))->FindObject(sHist.Data()))->GetBinContent(kValM);
    dey[kCje] = ((TH1D*)((TList*)file->Get(sList.Data()))->FindObject(sHist.Data()))->GetBinContent(kErrM);
  } file->Close();
//=============================================================================

  TGraphAsymmErrors *g = new TGraphAsymmErrors(kCjeN, dvx, dvy, der, der, dey, dey);
  g->SetName(Form("g%s_%s_%s_%s_%s_Stat_%s", sVarN[kVar].Data(),
                                             sFxnN[kFxn].Data(),
                                             sActN[kAct].Data(),
                                             sPtjN[kPtj].Data(),
                                             sBinN[kBin].Data(), sOpt.Data()));

  return g;
}

//_____________________________________________________________________________
TGraphAsymmErrors *GetSyst(const UInt_t  kAct,
                           const UInt_t  kPtj,
                           const UInt_t  kBin,
                           const UInt_t  kVar,
                           const UInt_t  kFxn,
                           const TString sOpt)
{
  Double_t dvy[kCjeN];
  Double_t dly[kCjeN];
  Double_t dhy[kCjeN];
  TFile *file = TFile::Open(Form("data/AnaYieldMean%s.root",sOpt.Data()), "READ");
  for (UInt_t kCje=0; kCje<kCjeN; kCje++) {
    TString sHist = Form("h%s_%s", sVarN[kVar].Data(), sFxnN[kFxn].Data());
    TString sList = Form("list_%s_%s_%s_%s_Out", sCjeN[kCje].Data(),
                                                 sActN[kAct].Data(),
                                                 sPtjN[kPtj].Data(),
                                                 sBinN[kBin].Data());

    dvy[kCje] = ((TH1D*)((TList*)file->Get(sList.Data()))->FindObject(sHist.Data()))->GetBinContent(kValM);
    dly[kCje] = ((TH1D*)((TList*)file->Get(sList.Data()))->FindObject(sHist.Data()))->GetBinContent(kErlM);
    dhy[kCje] = ((TH1D*)((TList*)file->Get(sList.Data()))->FindObject(sHist.Data()))->GetBinContent(kErhM);
  } file->Close();
//=============================================================================

  TGraphAsymmErrors *g = new TGraphAsymmErrors(kCjeN, dvx, dvy, dex, dex, dly, dhy);
  g->SetName(Form("g%s_%s_%s_%s_%s_Syst_%s", sVarN[kVar].Data(),
                                             sFxnN[kFxn].Data(),
                                             sActN[kAct].Data(),
                                             sPtjN[kPtj].Data(),
                                             sBinN[kBin].Data(), sOpt.Data()));

  return g;
}
