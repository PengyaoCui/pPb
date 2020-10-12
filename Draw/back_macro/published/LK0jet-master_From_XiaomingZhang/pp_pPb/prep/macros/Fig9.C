void Fig9(const Bool_t bPrint=kFALSE)
{
  gROOT->LoadMacro("utils/THistool.h");
  gROOT->LoadMacro("utils/TPlotStd.h");
  gROOT->LoadMacro("utils/TAliFigs.h"); SetStyle();
//=============================================================================

  TFile *file = TFile::Open("data/pPb/AnalysisResults.root", "READ");
  TList *list = (TList*)file->Get("listHD_JC04_JR04_PtJ10");
  file->Close();

  TH1D *hStatpA = (TH1D*)list->FindObject("hRatioV_Stat"); hStatpA->SetName("hStatpA");
  TH1D *hSystpA = (TH1D*)list->FindObject("hRatioV_Syst"); hSystpA->SetName("hSystpA");

  TGraphErrors *gStatpA = ConvHistogramToGraphErrors(hStatpA, 0x0, hStatpA->GetNbinsX());
  TGraphErrors *gSystpA = ConvHistogramToGraphErrors(hStatpA, hSystpA, hStatpA->GetNbinsX());
//=============================================================================

  file = TFile::Open("data/pp/20161126/ppResults.root", "READ");
  list = (TList*)file->Get("pplistHD_JC04_JR04_PtJ10");
  file->Close();

  TH1D *hStatpp = (TH1D*)list->FindObject("hRatioV_Stat"); hStatpp->SetName("hStatpp");
  TH1D *hSystpp = (TH1D*)list->FindObject("hRatioV_Syst"); hSystpp->SetName("hSystpp");

  TGraphErrors *gStatpp = ConvHistogramToGraphErrors(hStatpp, 0x0, hStatpp->GetNbinsX());
  TGraphErrors *gSystpp = ConvHistogramToGraphErrors(hStatpp, hSystpp, hStatpp->GetNbinsX());
//=============================================================================

  TH1F    *frm = 0;
  TCanvas *can = 0;
  TLegend *leg = 0;
  TLatex  *tex = 0;
  TLine  *line = 0;

  const Float_t dflx =  0.,  dfux = 12.;
  const Float_t dfly =  8e-6, dfuy = 1.1;

  const Float_t dlsx = 0.05, dlsy = 0.05;
  const Float_t dtsx = 0.06, dtsy = 0.06;
  const Float_t dtox = 1.10, dtoy = 1.00;

  const TString stnx = "#it{p}_{T} (GeV/#it{c})";
  const TString stny = "(#Lambda+#bar{#Lambda}) / 2K_{S}^{0}";
//=============================================================================

  can = MakeCanvas("Fig9");
  frm = can->DrawFrame(dflx, dfly, dfux, dfuy);
  SetupFrame(frm, dlsx, dlsy, dtsx, dtsy, dtox, dtoy, stnx, stny);

  DrawAliLogo(0.82, 0.90);
  DrawGraph(gStatpA, wcl[1], wmk[0], "P"); DrawGraph(gSystpA, wcl[1], "E2");
  DrawGraph(gStatpp, wcl[3], wmk[0], "P"); DrawGraph(gSystpp, wcl[3], "E2");

  leg = new TLegend(0.66, 0.64, 0.96, 0.80); SetupLegend(leg);
  leg->AddEntry(gStatpA, "p-Pb", "LP")->SetTextSizePixels(24);
  leg->AddEntry(gStatpp, "pp", "LP")->SetTextSizePixels(24);
  leg->Draw();

  tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.16, 0.92, "p-Pb #sqrt{#it{s}_{NN}}=5.02 TeV and pp #sqrt{#it{s}}=7");
  tex->DrawLatex(0.16, 0.84, "Jet: anti-#it{k}_{T}, #it{R}=0.4, #it{p}_{T,jet}>10 GeV/#it{c}, |#eta_{jet}|<0.35");
  tex->DrawLatex(0.16, 0.76, "|#eta_{V^{0}}|<0.75, #it{R}(V^{0},jet)<0.4");
  CanvasEnd(can);
//=============================================================================

  if (bPrint) {
    can->Print(Form("%s.pdf",can->GetName()));
    can->Print(Form("%s.png",can->GetName()));
    can->Print(Form("%s.eps",can->GetName()));
  }
//=============================================================================

  return;
}
