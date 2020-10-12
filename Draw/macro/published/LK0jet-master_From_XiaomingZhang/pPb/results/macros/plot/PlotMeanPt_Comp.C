const UInt_t kActN = 3;
const Double_t dvx[] = { 40.5969,  25.6367,  11.3038   };
const Double_t dex[] = {  0.89993, 0.566758, 0.245346  };
const Double_t der[] = {  0.,       0.,       0.       };

const TString sFxnN[] = { "BGBlastWave", "LevyTsallis" };

enum { kValY=1, kErrY, kErlY, kErhY, kValM, kErrM, kErlM, kErhM };
//=============================================================================

void PlotMeanPt_Comp(const UInt_t kPtj=0,
                     const UInt_t kCje=0,
                     const UInt_t kOut=0)
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

  TGraphAsymmErrors *gKstatMB = GetKstatMeanPtMB();
  TGraphAsymmErrors *gKsystMB = GetKsystMeanPtMB();

  TGraphAsymmErrors *gLstatMB = GetLstatMeanPtMB();
  TGraphAsymmErrors *gLsystMB = GetLsystMeanPtMB();


  TGraphAsymmErrors *gKstatHD = GetStat(kCje, kPtj, kBin07, kKshort, 1, "JC"); gKstatHD->SetName("gKstatHD");
  TGraphAsymmErrors *gKsystHD = GetSyst(kCje, kPtj, kBin07, kKshort, 1, "JC"); gKsystHD->SetName("gKsystHD");

  TGraphAsymmErrors *gLstatHD = GetStat(kCje, kPtj, kBin21, kLambda, 1, "JC"); gLstatHD->SetName("gLstatHD");
  TGraphAsymmErrors *gLsystHD = GetSyst(kCje, kPtj, kBin21, kLambda, 1, "JC"); gLsystHD->SetName("gLsystHD");
//=============================================================================

  TH1F    *frm = 0;
  TCanvas *can = 0;
  TLegend *leg = 0;
  TLatex  *tex = 0;
  TLine  *line = 0;

  const Float_t dflx =  2.0, dfux = 200.;
  const Float_t dfly =  0.0, dfuy = 8.0;

  const Float_t dlsx = 0.05, dlsy = 0.05;
  const Float_t dtsx = 0.06, dtsy = 0.06;
  const Float_t dtox = 1.10, dtoy = 1.00;

  const TString stnx = "<d#it{N}_{ch}/d#eta_{lab}>_{|#eta_{lab}|<0.5}";
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

  const TString sCanN = Form("MeanPt_Comp_%s_%s", sCjeN[kCje].Data(), sPtjN[kPtj].Data());

  can = MakeCanvas(sCanN);
  can->SetLogx();
  can->SetGridx(); can->SetGridy();
  frm = can->DrawFrame(dflx, dfly, dfux, dfuy);
  SetupFrame(frm, dlsx, dlsy, dtsx, dtsy, dtox, dtoy, stnx, stny);

  DrawGraph(gKstatMB, wcl[1], wmk[0], "P"); DrawGraph(gKsystMB, wcl[1], "E2");
  DrawGraph(gLstatMB, wcl[3], wmk[0], "P"); DrawGraph(gLsystMB, wcl[3], "E2");

  DrawGraph(gKstatHD, wcl[1], wmk[1], "P"); DrawGraph(gKsystHD, wcl[1], "E2");
  DrawGraph(gLstatHD, wcl[3], wmk[1], "P"); DrawGraph(gLsystHD, wcl[3], "E2");


  leg = new TLegend(0.68, 0.62, 0.96, 0.86); SetupLegend(leg);
  leg->AddEntry(gKstatMB, "K_{S}^{0} inclusive",               "LP")->SetTextSizePixels(24);
  leg->AddEntry(gLstatMB, "(#Lambda+#bar{#Lambda}) inclusive", "LP")->SetTextSizePixels(24);
  leg->AddEntry(gKstatHD, "K_{S}^{0} in jets",                 "LP")->SetTextSizePixels(24);
  leg->AddEntry(gLstatHD, "(#Lambda+#bar{#Lambda}) in jets",   "LP")->SetTextSizePixels(24);
  leg->Draw();

  leg = new TLegend(0.54, 0.52, 0.76, 0.66); SetupLegend(leg);
  leg->AddEntry(hStatE, sErrL[kStat], "LEP")->SetTextSizePixels(24);
  leg->AddEntry(hSystE, sErrL[kSyst], "F")->SetTextSizePixels(24);
  leg->Draw();

  tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.16, 0.90, Form("p-Pb #sqrt{s_{NN}}=5.02 TeV, %s, anti-#it{k}_{T}", sPtjL[kPtj].Data()));
  tex->DrawLatex(0.16, 0.82, Form("|#eta_{jet}|<0.35, |#eta_{V^{0}}|<0.75, %s", sCjeL[kCje].Data()));
  CanvasEnd(can);
//=============================================================================

  if (kOut==1) can->Print(Form("c%s.pdf",sCanN.Data()));


  return;
}

//_____________________________________________________________________________
TGraphAsymmErrors *GetStat(const UInt_t  kCje,
                           const UInt_t  kPtj,
                           const UInt_t  kBin,
                           const UInt_t  kVar,
                           const UInt_t  kFxn,
                           const TString sOpt)
{
  Double_t dvy[kActN];
  Double_t dey[kActN];
  TFile *file = TFile::Open(Form("data/AnaYieldMean%s.root",sOpt.Data()), "READ");
  for (UInt_t kAct=0; kAct<kActN; kAct++) {
    TString sHist = Form("h%s_%s", sVarN[kVar].Data(), sFxnN[kFxn].Data());
    TString sList = Form("list_%s_%s_%s_%s_Out", sCjeN[kCje].Data(),
                                                 sActN[kAct].Data(),
                                                 sPtjN[kPtj].Data(),
                                                 sBinN[kBin].Data());

    dvy[kAct] = ((TH1D*)((TList*)file->Get(sList.Data()))->FindObject(sHist.Data()))->GetBinContent(kValM);
    dey[kAct] = ((TH1D*)((TList*)file->Get(sList.Data()))->FindObject(sHist.Data()))->GetBinContent(kErrM);
  } file->Close();
//=============================================================================

  TGraphAsymmErrors *g = new TGraphAsymmErrors(kActN, dvx, dvy, der, der, dey, dey);
  g->SetName(Form("g%s_%s_%s_%s_%s_Stat_%s", sVarN[kVar].Data(),
                                             sFxnN[kFxn].Data(),
                                             sCjeN[kCje].Data(),
                                             sPtjN[kPtj].Data(),
                                             sBinN[kBin].Data(), sOpt.Data()));

  return g;
}

//_____________________________________________________________________________
TGraphAsymmErrors *GetSyst(const UInt_t  kCje,
                           const UInt_t  kPtj,
                           const UInt_t  kBin,
                           const UInt_t  kVar,
                           const UInt_t  kFxn,
                           const TString sOpt)
{
  Double_t dvy[kActN];
  Double_t dly[kActN];
  Double_t dhy[kActN];
  TFile *file = TFile::Open(Form("data/AnaYieldMean%s.root",sOpt.Data()), "READ");
  for (UInt_t kAct=0; kAct<kActN; kAct++) {
    TString sHist = Form("h%s_%s", sVarN[kVar].Data(), sFxnN[kFxn].Data());
    TString sList = Form("list_%s_%s_%s_%s_Out", sCjeN[kCje].Data(),
                                                 sActN[kAct].Data(),
                                                 sPtjN[kPtj].Data(),
                                                 sBinN[kBin].Data());

    dvy[kAct] = ((TH1D*)((TList*)file->Get(sList.Data()))->FindObject(sHist.Data()))->GetBinContent(kValM);
    dly[kAct] = ((TH1D*)((TList*)file->Get(sList.Data()))->FindObject(sHist.Data()))->GetBinContent(kErlM);
    dhy[kAct] = ((TH1D*)((TList*)file->Get(sList.Data()))->FindObject(sHist.Data()))->GetBinContent(kErhM);
  } file->Close();
//=============================================================================

  TGraphAsymmErrors *g = new TGraphAsymmErrors(kActN, dvx, dvy, dex, dex, dly, dhy);
  g->SetName(Form("g%s_%s_%s_%s_%s_Syst_%s", sVarN[kVar].Data(),
                                             sFxnN[kFxn].Data(),
                                             sCjeN[kCje].Data(),
                                             sPtjN[kPtj].Data(),
                                             sBinN[kBin].Data(), sOpt.Data()));

  return g;
}
