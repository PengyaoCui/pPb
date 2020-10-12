void PlotL2K_Pt_Comp(const UInt_t kCje = 0,
                     const UInt_t kAct = 0,
                     const UInt_t kPtj = 0,
                     const UInt_t kOut = 0)
{
  const TString sWorkDir = gSystem->WorkingDirectory();
  const TString sPckgDir = gSystem->DirName(sWorkDir.Data());

  const TString sUtilDir = Form("%s/util", sPckgDir.Data());
  const TString sDataDir = Form("%s/data/outputs", sPckgDir.Data());

  gROOT->LoadMacro(Form("%s/TUtilsOpHisto.h",sUtilDir.Data()));
  gROOT->LoadMacro(Form("%s/TUtilsToolV0s.h",sUtilDir.Data()));
  gROOT->LoadMacro(Form("%s/TUtilsResults.h",sUtilDir.Data()));
  gROOT->LoadMacro(Form("%s/TUtilsPlotStd.h",sUtilDir.Data()));
  gROOT->LoadMacro(Form("%s/TUtilsAliFigs.h",sUtilDir.Data())); SetStyle();
//=============================================================================

  const TString sList = Form("list_%s_%s_%s", sCjeN[kCje].Data(),
                                              sActN[kAct].Data(),
                                              sPtjN[kPtj].Data());

  TFile *file = TFile::Open("data/AnaL2K_Pt_Comp.root", "READ");
  TList *list = (TList*)file->Get(sList.Data());
  file->Close();
//=============================================================================

  TH1D *hStatMB = (TH1D*)list->FindObject("hRatioV_Incl_Stat");
  TGraphErrors *gSystMB = (TGraphErrors*)list->FindObject("gRatioV_Incl_Syst");


  TH1D *hStat02 = (TH1D*)list->FindObject("hRatioV_JR02_Stat");
  TH1D *hSyst02 = (TH1D*)list->FindObject("hRatioV_JR02_Syst");

  TH1D *hStat03 = (TH1D*)list->FindObject("hRatioV_JR03_Stat");
  TH1D *hSyst03 = (TH1D*)list->FindObject("hRatioV_JR03_Syst");

  TH1D *hStat04 = (TH1D*)list->FindObject("hRatioV_JR04_Stat");
  TH1D *hSyst04 = (TH1D*)list->FindObject("hRatioV_JR04_Syst");

  TH1D *hStatUE = (TH1D*)list->FindObject("hRatioV_Ubkg_Stat");
  TH1D *hSystUE = (TH1D*)list->FindObject("hRatioV_Ubkg_Syst");


  TGraphErrors *gStat02 = ConvHistogramToGraphErrorL(hStat02, 0x0, hStat02->GetNbinsX());
  TGraphErrors *gSyst02 = ConvHistogramToGraphErrorL(hStat02, hSyst02, hStat02->GetNbinsX());

  TGraphErrors *gStat03 = ConvHistogramToGraphErrors(hStat03, 0x0, hStat03->GetNbinsX());
  TGraphErrors *gSyst03 = ConvHistogramToGraphErrors(hStat03, hSyst03, hStat03->GetNbinsX());

  TGraphErrors *gStat04 = ConvHistogramToGraphErrorR(hStat04, 0x0, hStat04->GetNbinsX());
  TGraphErrors *gSyst04 = ConvHistogramToGraphErrorR(hStat04, hSyst04, hStat04->GetNbinsX());

  TGraphErrors *gStatUE = ConvHistogramToGraphErrorL(hStatUE, 0x0, hStatUE->GetNbinsX());
  TGraphErrors *gSystUE = ConvHistogramToGraphErrorL(hStatUE, hSystUE, hStatUE->GetNbinsX());
//=============================================================================

  TH1F    *frm = 0;
  TCanvas *can = 0;
  TLegend *leg = 0;
  TLatex  *tex = 0;
  TLine  *line = 0;

  const Float_t dflx =  0.6, dfux = 12.;
  const Float_t dfly =  0.0, dfuy = 1.3;

  const Float_t dlsx = 0.05, dlsy = 0.05;
  const Float_t dtsx = 0.06, dtsy = 0.06;
  const Float_t dtox = 1.10, dtoy = 1.00;

  const TString stnx = "#it{p}_{T} (GeV/#it{c})";
  const TString stny = sVarL[kRatioV];

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

  const TString sCanN = Form("L2K_Pt_Comp_%s_%s_%s", sCjeN[kCje].Data(), sActN[kAct].Data(), sPtjN[kPtj].Data());

  can = MakeCanvas(sCanN);
  can->SetGridx(); can->SetGridy();
  frm = can->DrawFrame(dflx, dfly, dfux, dfuy);
  SetupFrame(frm, dlsx, dlsy, dtsx, dtsy, dtox, dtoy, stnx, stny);

  DrawGraph(gSystUE, wcl[2], "E2"); DrawGraph(gStatUE, wcl[2], wmk[0], "P");
  DrawGraph(gSystMB, wcl[0], "E2"); DrawHisto(hStatMB, wcl[0], wmk[0], "SAME");

  DrawGraph(gSyst02, wcl[3], "E2"); DrawGraph(gStat02, wcl[3], wmk[0], "P");
  DrawGraph(gSyst04, wcl[5], "E2"); DrawGraph(gStat04, wcl[5], wmk[0], "P");
  DrawGraph(gSyst03, wcl[1], "E2"); DrawHisto(hStat03, wcl[1], wmk[0], "SAME");

  leg = new TLegend(0.70, 0.68, 0.96, 0.96); SetupLegend(leg);
  leg->AddEntry(hStatMB, "inclusive",  "LP")->SetTextSizePixels(24);
  leg->AddEntry(gStatUE, sBkgL[kPC],   "LP")->SetTextSizePixels(24);
  leg->AddEntry(gStat02, sRjeL[kJC02], "LP")->SetTextSizePixels(24);
  leg->AddEntry(hStat03, sRjeL[kJC03], "LP")->SetTextSizePixels(24);
  leg->AddEntry(gStat04, sRjeL[kJC04], "LP")->SetTextSizePixels(24);
  leg->Draw();

  leg = new TLegend(0.54, 0.52, 0.76, 0.66); SetupLegend(leg);
  leg->AddEntry(hStatE, sErrL[kStat], "LEP")->SetTextSizePixels(24);
  leg->AddEntry(hSystE, sErrL[kSyst], "F")->SetTextSizePixels(24);
  leg->Draw();

  tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.16, 0.90, Form("p-Pb #sqrt{s_{NN}}=5.02 TeV, %s", sActL[kAct].Data()));
  tex->DrawLatex(0.16, 0.82, Form("%s, anti-#it{k}_{T}", sPtjL[kPtj].Data()));
  tex->DrawLatex(0.16, 0.74, Form("|#eta_{jet}|<0.35, |#eta_{V^{0}}|<0.75, %s", sCjeL[kCje].Data()));
  CanvasEnd(can);
//=============================================================================

  if (kOut==1) can->Print(Form("c%s.pdf",sCanN.Data()));
  return;
}
