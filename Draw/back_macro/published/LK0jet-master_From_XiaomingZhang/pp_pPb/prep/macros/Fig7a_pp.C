void Fig7a_pp(char *set="20161121", const Bool_t bPrint=kFALSE)
{
  gROOT->LoadMacro("utils/THistool.h");
  gROOT->LoadMacro("utils/TPlotStd.h");
  gROOT->LoadMacro("utils/TAliFigs.h"); SetStyle();
//=============================================================================

  TFile *file = TFile::Open(Form("data/pp/%s/ppResults.root",set), "READ");
  TList *listIn = (TList*)file->Get("pplist_Inclusive");
  TList *listUE = (TList*)file->Get("pplistUE_PCM_JC04_JR04_PtJ10");
  TList *listJE = (TList*)file->Get("pplistJE_JC04_JR04_PtJ10");
  TList *listHD = (TList*)file->Get("pplistHD_JC04_JR04_PtJ10");
  file->Close();
//=============================================================================

  TH1D *hKshortStatIn = (TH1D*)listIn->FindObject("hKshort_Stat"); hKshortStatIn->SetName("hKshortStatIn");
  TH1D *hKshortSystIn = (TH1D*)listIn->FindObject("hKshort_Syst"); hKshortSystIn->SetName("hKshortSystIn");
//=============================================================================

  TH1D *hKshortStatUE = (TH1D*)listUE->FindObject("hKshort_Stat"); hKshortStatUE->SetName("hKshortStatUE");
  TH1D *hKshortSystUE = (TH1D*)listUE->FindObject("hKshort_Syst"); hKshortSystUE->SetName("hKshortSystUE");
//=============================================================================

  TH1D *hKshortStatJE = (TH1D*)listJE->FindObject("hKshort_Stat"); hKshortStatJE->SetName("hKshortStatJE");
  TH1D *hKshortSystJE = (TH1D*)listJE->FindObject("hKshort_Syst"); hKshortSystJE->SetName("hKshortSystJE");
//=============================================================================

  TH1D *hKshortStatHD = (TH1D*)listHD->FindObject("hKshort_Stat"); hKshortStatHD->SetName("hKshortStatHD");
  TH1D *hKshortSystHD = (TH1D*)listHD->FindObject("hKshort_Syst"); hKshortSystHD->SetName("hKshortSystHD");
//=============================================================================

  TGraphErrors *gKshortStatIn = ConvHistogramToGraphErrors(hKshortStatIn, 0x0, hKshortStatIn->GetNbinsX());
  TGraphErrors *gKshortSystIn = ConvHistogramToGraphErrors(hKshortStatIn, hKshortSystIn, hKshortStatIn->GetNbinsX());

  TGraphErrors *gKshortStatUE = ConvHistogramToGraphErrors(hKshortStatUE, 0x0, hKshortStatUE->GetNbinsX());
  TGraphErrors *gKshortSystUE = ConvHistogramToGraphErrors(hKshortStatUE, hKshortSystUE, hKshortStatUE->GetNbinsX());

  TGraphErrors *gKshortStatJE = ConvHistogramToGraphErrors(hKshortStatJE, 0x0, hKshortStatJE->GetNbinsX());
  TGraphErrors *gKshortSystJE = ConvHistogramToGraphErrors(hKshortStatJE, hKshortSystJE, hKshortStatJE->GetNbinsX());

  TGraphErrors *gKshortStatHD = ConvHistogramToGraphErrors(hKshortStatHD, 0x0, hKshortStatHD->GetNbinsX());
  TGraphErrors *gKshortSystHD = ConvHistogramToGraphErrors(hKshortStatHD, hKshortSystHD, hKshortStatJE->GetNbinsX());
//=============================================================================

  TH1F    *frm = 0;
  TCanvas *can = 0;
  TLegend *leg = 0;
  TLatex  *tex = 0;
  TLine  *line = 0;

  const Float_t dflx =  0.0,  dfux = 12.;
  const Float_t dfly =  8e-6, dfuy = 0.8;

  const Float_t dlsx = 0.05, dlsy = 0.05;
  const Float_t dtsx = 0.06, dtsy = 0.06;
  const Float_t dtox = 1.10, dtoy = 1.00;

  const TString stnx = "#it{p}_{T} (GeV/#it{c})";
  const TString stny = "d#rho / d#it{p}_{T} (GeV/#it{c} rad)^{-1}";
//=============================================================================

  can = MakeCanvas(Form("Fig7a_pp_%s",set)); can->SetLogy();
  frm = can->DrawFrame(dflx, dfly, dfux, dfuy);
  SetupFrame(frm, dlsx, dlsy, dtsx, dtsy, dtox, dtoy, stnx, stny);

  DrawAliLogo(0.82, 0.90);
  DrawGraph(gKshortStatIn, wcl[0], wmk[0], "P"); DrawGraph(gKshortSystIn, wcl[0], "E2");
  DrawGraph(gKshortStatUE, wcl[2], wmk[0], "P"); DrawGraph(gKshortSystUE, wcl[2], "E2");
  DrawGraph(gKshortStatJE, wcl[3], wmk[0], "P"); DrawGraph(gKshortSystJE, wcl[3], "E2");
  DrawGraph(gKshortStatHD, wcl[1], wmk[0], "P"); DrawGraph(gKshortSystHD, wcl[1], "E2");

  leg = new TLegend(0.66, 0.60, 0.96, 0.88); SetupLegend(leg);
  leg->AddEntry(gKshortStatIn, "Inclusive", "LP")->SetTextSizePixels(24);
  leg->AddEntry(gKshortStatUE, "Underlying", "LP")->SetTextSizePixels(24);
  leg->AddEntry(gKshortStatJE, "In jet", "LP")->SetTextSizePixels(24);
  leg->AddEntry(gKshortStatHD, "UE subtracted", "LP")->SetTextSizePixels(24);
  leg->Draw();

  tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.16, 0.92, "pp #sqrt{#it{s}}=7 TeV");
  tex->DrawLatex(0.16, 0.28, "K_{s}^{0}, #it{R}(V^{0},jet)<0.4, |#eta|<0.75");
  tex->DrawLatex(0.16, 0.20, "Jet: anti-#it{k}_{T}, #it{R}=0.4 #it{p}_{T,jet}^{ch}>10 GeV/#it{c}, |#eta_{jet}|<0.35");
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
