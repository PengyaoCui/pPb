void PlotL2K_Pt_Mean(const UInt_t kAct = 7,
                     const UInt_t kPtj = 1, // 0: pTjet = 10 GeV/c; 1 pTjet = 20 GeV/c
                     const UInt_t kOut = 0)
{
  const TString sWorkDir = gSystem->WorkingDirectory();
  const TString sPckgDir = gSystem->DirName(sWorkDir.Data());
  const TString sUtilDir = Form("%s/include", sPckgDir.Data());
//=============================================================================

  gROOT->LoadMacro(Form("%s/TUtilsOpHisto.h",sUtilDir.Data()));
  gROOT->LoadMacro(Form("%s/TUtilsResults.h",sUtilDir.Data()));
  gROOT->LoadMacro(Form("%s/TUtilsPlotStd.h",sUtilDir.Data()));
  gROOT->LoadMacro(Form("%s/TUtilsAliFigs.h",sUtilDir.Data())); SetStyle();
//=============================================================================

  const TString sList = Form("list_%s_%s", sActN[kAct].Data(),
                                           sPtjN[kPtj].Data());

  TFile *file = TFile::Open("data/AnaL2K_Pt_Mean.root", "READ");
  TList *list = (TList*)file->Get(sList.Data());
  file->Close();
//=============================================================================

  TH1D *hStatMB = (TH1D*)list->FindObject("hRatioV_Incl_Stat");
  TGraphErrors *gSystMB = (TGraphErrors*)list->FindObject("gRatioV_Incl_Syst");


  TH1D *hStat02 = (TH1D*)list->FindObject("hRatioV_JC02_Stat");
  TH1D *hSyst02 = (TH1D*)list->FindObject("hRatioV_JC02_Syst");

  TH1D *hStat04 = (TH1D*)list->FindObject("hRatioV_JC04_Stat");
  TH1D *hSyst04 = (TH1D*)list->FindObject("hRatioV_JC04_Syst");

  TH1D *hStatUE = (TH1D*)list->FindObject("hRatioV_Ubkg_Stat");
  TH1D *hSystUE = (TH1D*)list->FindObject("hRatioV_Ubkg_Syst");


  TGraphErrors *gStat02 = ConvHistogramToGraphErrors(hStat02, 0x0, hStat02->GetNbinsX());
  TGraphErrors *gSyst02 = ConvHistogramToGraphErrors(hStat02, hSyst02, hStat02->GetNbinsX());

  TGraphErrors *gStat04 = ConvHistogramToGraphErrorL(hStat04, 0x0, hStat04->GetNbinsX());
  TGraphErrors *gSyst04 = ConvHistogramToGraphErrorL(hStat04, hSyst04, hStat04->GetNbinsX());

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

  const TString sCanN = Form("L2K_Pt_Mean_%s_%s", sActN[kAct].Data(), sPtjN[kPtj].Data());

  can = MakeCanvas(sCanN);
  frm = can->DrawFrame(dflx, dfly, dfux, dfuy);
  SetupFrame(frm, dlsx, dlsy, dtsx, dtsy, dtox, dtoy, stnx, stny);

  DrawGraph(gSystUE, wcl[2], "E2"); DrawGraph(gStatUE, wcl[2], wmk[0], "P");
  DrawGraph(gSystMB, wcl[0], "E2"); DrawHisto(hStatMB, wcl[0], wmk[0], "SAME");

  DrawGraph(gSyst04, wcl[1], "E2"); DrawGraph(gStat04, wcl[1], wmk[0], "P");
  DrawGraph(gSyst02, wcl[3], "E2"); DrawHisto(hStat02, wcl[3], wmk[0], "SAME");

  leg = new TLegend(0.70, 0.68, 0.96, 0.96); SetupLegend(leg);
  leg->AddEntry(hStatMB, "inclusive",  "LP")->SetTextSizePixels(24);
  leg->AddEntry(gStatUE, sBkgL[kPC],   "LP")->SetTextSizePixels(24);
  leg->AddEntry(hStat02, sCjeL[kJC02], "LP")->SetTextSizePixels(24);
  leg->AddEntry(gStat04, sCjeL[kJC04], "LP")->SetTextSizePixels(24);
  leg->Draw();

  leg = new TLegend(0.54, 0.52, 0.76, 0.66); SetupLegend(leg);
  leg->AddEntry(hStatE, sErrL[kStat], "LEP")->SetTextSizePixels(24);
  leg->AddEntry(hSystE, sErrL[kSyst], "F")->SetTextSizePixels(24);
  leg->Draw();

  tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.16, 0.92, Form("p-Pb #sqrt{s_{NN}}=5.02 TeV"));
  tex->DrawLatex(0.16, 0.84, Form("Jet: %s, anti-#it{k}_{T}", sPtjL[kPtj].Data()));
  tex->DrawLatex(0.16, 0.76, Form("|#eta_{jet}|<0.35, |#eta_{V^{0}}|<0.75"));
  tex->DrawLatex(0.64, 0.20, Form("mean #it{R}=0.2, 0.3, 0.4"));
  CanvasEnd(can); if (kOut==1) can->Print(Form("c%s.pdf",sCanN.Data()));
//=============================================================================

  return;
}
