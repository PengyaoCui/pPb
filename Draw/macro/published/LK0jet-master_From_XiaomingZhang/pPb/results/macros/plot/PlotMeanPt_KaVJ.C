const UInt_t kCjeN = 7;
const Double_t dvx[] = {  0.10, 0.25, 0.35, 0.50, 0.70, 0.95, 1.30 };
const Double_t dex[] = {  0.02, 0.02, 0.02, 0.02, 0.02, 0.02, 0.02 };
const Double_t der[] = {  0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00 };

const TString sFxnN[] = { "BGBlastWave", "LevyTsallis" };

enum { kValY=1, kErrY, kErlY, kErhY, kValM, kErrM, kErlM, kErhM };
//=============================================================================

void PlotMeanPt_KaVJ(const UInt_t kPtj = 1,
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

  TGraphAsymmErrors *gStat0 = GetStat(0, kPtj, kBin07, kKshort, 1, "VJ"); gStat0->SetName("gStat0");
  TGraphAsymmErrors *gSyst0 = GetSyst(0, kPtj, kBin07, kKshort, 1, "VJ"); gSyst0->SetName("gSyst0");

  TGraphAsymmErrors *gStat1 = GetStat(1, kPtj, kBin07, kKshort, 1, "VJ"); gStat1->SetName("gStat1");
  TGraphAsymmErrors *gSyst1 = GetSyst(1, kPtj, kBin07, kKshort, 1, "VJ"); gSyst1->SetName("gSyst1");

  TGraphAsymmErrors *gStat2 = GetStat(2, kPtj, kBin07, kKshort, 1, "VJ"); gStat2->SetName("gStat2");
  TGraphAsymmErrors *gSyst2 = GetSyst(2, kPtj, kBin07, kKshort, 1, "VJ"); gSyst2->SetName("gSyst2");
//=============================================================================

  TH1F    *frm = 0;
  TCanvas *can = 0;
  TLegend *leg = 0;
  TLatex  *tex = 0;
  TLine  *line = 0;

  const Float_t dflx =  0.0, dfux = 1.5;
  const Float_t dfly =  0.0, dfuy = 6.0;

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

  const TString sCanN = Form("MeanPt_KaVJ_%s", sPtjN[kPtj].Data());

  can = MakeCanvas(sCanN);
  can->SetGridx(); can->SetGridy();
  frm = can->DrawFrame(dflx, dfly, dfux, dfuy);
  SetupFrame(frm, dlsx, dlsy, dtsx, dtsy, dtox, dtoy, stnx, stny);

  DrawGraph(gStat0, wcl[1], wmk[0], "P"); DrawGraph(gSyst0, wcl[1], "E2");
  DrawGraph(gStat1, wcl[3], wmk[0], "P"); DrawGraph(gSyst1, wcl[3], "E2");
  DrawGraph(gStat2, wcl[5], wmk[0], "P"); DrawGraph(gSyst2, wcl[5], "E2");

  leg = new TLegend(0.68, 0.60, 0.96, 0.80); SetupLegend(leg);
  leg->AddEntry(gStat0, sActL[0], "LP")->SetTextSizePixels(24);
  leg->AddEntry(gStat1, sActL[1], "LP")->SetTextSizePixels(24);
  leg->AddEntry(gStat2, sActL[2], "LP")->SetTextSizePixels(24);
  leg->Draw();

/*leg = new TLegend(0.54, 0.52, 0.76, 0.66); SetupLegend(leg);
  leg->AddEntry(hStatE, sErrL[kStat], "LEP")->SetTextSizePixels(24);
  leg->AddEntry(hSystE, sErrL[kSyst], "F")->SetTextSizePixels(24);
  leg->Draw();*/

  tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.16, 0.90, Form("K_{S}^{0}, p-Pb #sqrt{s_{NN}}=5.02 TeV")) ;
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
