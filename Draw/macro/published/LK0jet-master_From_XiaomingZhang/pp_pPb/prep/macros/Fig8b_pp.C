void Fig8b_pp(const char *set="20161121", const Bool_t bPrint=kFALSE)
{
  gROOT->LoadMacro("utils/THistool.h");
  gROOT->LoadMacro("utils/TPlotStd.h");
  gROOT->LoadMacro("utils/TAliFigs.h"); SetStyle();
//=============================================================================

  TFile *file = TFile::Open(Form("data/pp/%s/ppResults.root",set), "READ");
  TList *listIn = (TList*)file->Get("pplist_Inclusive");
  TList *listUE = (TList*)file->Get("pplistUE_PCM_JC04_JR04_PtJ10");
  TList *list10 = (TList*)file->Get("pplistJE_JC04_JR04_PtJ10");
  TList *list20 = (TList*)file->Get("pplistHD_JC04_JR04_PtJ10");
  file->Close();
//=============================================================================

  TH1D *hStatIn = (TH1D*)listIn->FindObject("hRatioV_Stat"); hStatIn->SetName("hStatIn");
  TH1D *hSystIn = (TH1D*)listIn->FindObject("hRatioV_Syst"); hSystIn->SetName("hSystIn");
//=============================================================================

  TH1D *hStatUE = (TH1D*)listUE->FindObject("hRatioV_Stat"); hStatUE->SetName("hStatUE");
  TH1D *hSystUE = (TH1D*)listUE->FindObject("hRatioV_Syst"); hSystUE->SetName("hSystUE");
//=============================================================================

  TH1D *hStat10 = (TH1D*)list10->FindObject("hRatioV_Stat"); hStat10->SetName("hStat10");
  TH1D *hSyst10 = (TH1D*)list10->FindObject("hRatioV_Syst"); hSyst10->SetName("hSyst10");
//=============================================================================

  TH1D *hStat20 = (TH1D*)list20->FindObject("hRatioV_Stat"); hStat20->SetName("hStat20");
  TH1D *hSyst20 = (TH1D*)list20->FindObject("hRatioV_Syst"); hSyst20->SetName("hSyst20");
//=============================================================================

  TGraphErrors *gStatIn = ConvHistogramToGraphErrors(hStatIn, 0x0, hStatIn->GetNbinsX());
  TGraphErrors *gSystIn = ConvHistogramToGraphErrors(hStatIn, hSystIn, hStatIn->GetNbinsX());

  TGraphErrors *gStatUE = ConvHistogramToGraphErrors(hStatUE, 0x0, hStatUE->GetNbinsX());
  TGraphErrors *gSystUE = ConvHistogramToGraphErrors(hStatUE, hSystUE, hStatUE->GetNbinsX());

  TGraphErrors *gStat10 = ConvHistogramToGraphErrors(hStat10, 0x0, hStat10->GetNbinsX());
  TGraphErrors *gSyst10 = ConvHistogramToGraphErrors(hStat10, hSyst10, hStat10->GetNbinsX());

  TGraphErrors *gStat20 = ConvHistogramToGraphErrors(hStat20, 0x0, hStat20->GetNbinsX());
  TGraphErrors *gSyst20 = ConvHistogramToGraphErrors(hStat20, hSyst20, hStat20->GetNbinsX());
//=============================================================================

  file = TFile::Open("data/pythia/AnalysisOutputs_7000GeV.root");
  TList *listSoft = (TList*)file->Get("listSoft_Acc");
  TList *listHard = (TList*)file->Get("listHard_Exc1_R32");
  file->Close();

  TH1D *hPySoft = (TH1D*)listSoft->FindObject("hRatioV");
  hPySoft->SetName("hPySoft");

  TH1D *hPyHard = (TH1D*)listHard->FindObject("hRatioV");
  hPyHard->SetName("hPyHard");

  TGraph *gPySoft = new TGraph(hPySoft); gPySoft->SetLineStyle(9);
  TGraph *gPyHard = new TGraph(hPyHard); gPyHard->SetLineStyle(9);
//=============================================================================

  TH1F    *frm = 0;
  TCanvas *can = 0;
  TLegend *leg = 0;
  TLatex  *tex = 0;
  TLine  *line = 0;

  const Float_t dflx =  0.0,  dfux = 12.;
  const Float_t dfly =  8e-6, dfuy = 1.1;

  const Float_t dlsx = 0.05, dlsy = 0.05;
  const Float_t dtsx = 0.06, dtsy = 0.06;
  const Float_t dtox = 1.10, dtoy = 1.00;

  const TString stnx = "#it{p}_{T} (GeV/#it{c})";
  const TString stny = "(#Lambda+#bar{#Lambda}) / 2K_{S}^{0}";

  TGraph *gTemp = new TGraph();
  gTemp->SetLineStyle(9);
  gTemp->SetLineWidth(2);
//=============================================================================

  can = MakeCanvas(Form("Fig8b_pp_%s",set));
  frm = can->DrawFrame(dflx, dfly, dfux, dfuy);
  SetupFrame(frm, dlsx, dlsy, dtsx, dtsy, dtox, dtoy, stnx, stny);

  DrawAliLogo(0.82, 0.90);
  DrawGraph(gStatIn, wcl[0], wmk[0], "P"); DrawGraph(gSystIn, wcl[0], "E2");
  DrawGraph(gStatUE, wcl[2], wmk[0], "P"); DrawGraph(gSystUE, wcl[2], "E2");
  DrawGraph(gStat10, wcl[3], wmk[0], "P"); DrawGraph(gSyst10, wcl[3], "E2");
  DrawGraph(gStat20, wcl[1], wmk[0], "P"); DrawGraph(gSyst20, wcl[1], "E2");

  DrawGraph(gPySoft, wcl[0], "C");
  DrawGraph(gPyHard, wcl[1], "C");

  leg = new TLegend(0.66, 0.50, 0.96, 0.82); SetupLegend(leg);
  leg->AddEntry(gStatIn, "Inclusive", "LP")->SetTextSizePixels(24);
  leg->AddEntry(gStatUE, "Perp. cone", "LP")->SetTextSizePixels(24);
  leg->AddEntry(gStat10, "V^{0} in jets", "LP")->SetTextSizePixels(24);
  leg->AddEntry(gStat20, "UE subtracted", "LP")->SetTextSizePixels(24);
  leg->Draw();

  leg = new TLegend(0.66, 0.18, 0.96, 0.26); SetupLegend(leg);
  leg->AddEntry(gTemp, "PYTHIA8", "LP")->SetTextSizePixels(24);
  leg->Draw();

  tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.16, 0.92, "pp #sqrt{#it{s}}=7 TeV");
  tex->DrawLatex(0.16, 0.84, "Jet: anti-#it{k}_{T}, #it{R}=0.4, #it{p}_{T,jet}^{ch}>10 GeV/#it{c}, |#eta_{jet}|<0.35");
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
