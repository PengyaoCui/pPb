void PlotSystJC04PtJ20(const Bool_t bPrint=kFALSE)
{
  const TString sWorkDir = gSystem->WorkingDirectory();
  const TString sPckgDir = gSystem->DirName(sWorkDir.Data());
  const TString sUtilDir = Form("%s/include", sPckgDir.Data());
//=============================================================================

  gROOT->LoadMacro(Form("%s/TUtilsPlotStd.h",sUtilDir.Data()));
  gROOT->LoadMacro(Form("%s/TUtilsAliFigs.h",sUtilDir.Data())); SetStyle();
//=============================================================================

  TFile *file = TFile::Open("data/AnaSystematic.root", "READ");
  TList *list = (TList*)file->Get("list_JC04_JR04_PtJ20");
  file->Close();

  TH1D *hRatioVErrHD = (TH1D*)list->FindObject("hRatioVErrHD_list_JR04_JC04_ZNA_000_100_PtJ20_GetRatioVStatHD");
  TH1D *hRatioVErrJE = (TH1D*)list->FindObject("hRatioVErrJE_HD_list_JR04_JC04_ZNA_000_100_PtJ20_GetRatioVStatHD");
  TH1D *hRatioVErrJC = (TH1D*)list->FindObject("hRatioVErrJC_HD_list_JR04_JC04_ZNA_000_100_PtJ20_GetRatioVStatHD");
  TH1D *hRatioVErrUE = (TH1D*)list->FindObject("hRatioVErrUE_HD_list_JR04_JC04_ZNA_000_100_PtJ20_GetRatioVStatHD");
//=============================================================================

  TH1F    *frm = 0;
  TCanvas *can = 0;
  TLegend *leg = 0;
  TLatex  *tex = 0;
  TLine  *line = 0;

  const Float_t dflx =  0.6, dfux = 12.;
  const Float_t dfly =  0.0, dfuy = 0.5;

  const Float_t dlsx = 0.05, dlsy = 0.05;
  const Float_t dtsx = 0.06, dtsy = 0.06;
  const Float_t dtox = 1.10, dtoy = 1.00;

  const TString stnx = "#it{p}_{T} (GeV/#it{c})";
  const TString stny = "Relative systematic error";
//=============================================================================

  can = MakeCanvas("Syst_JC04_PtJ20");
  frm = can->DrawFrame(dflx, dfly, dfux, dfuy);
  SetupFrame(frm, dlsx, dlsy, dtsx, dtsy, dtox, dtoy, stnx, stny);

  DrawHisto(hRatioVErrHD, wcl[0], wmk[0], "SAME");
  DrawHisto(hRatioVErrJE, wcl[1], wmk[0], "SAME");
  DrawHisto(hRatioVErrJC, wcl[4], wmk[0], "SAME");
  DrawHisto(hRatioVErrUE, wcl[2], wmk[0], "SAME");

  leg = new TLegend(0.36, 0.58, 0.96, 0.74); SetupLegend(leg);
  leg->SetNColumns(2);
  leg->AddEntry(hRatioVErrHD, "Total", "LP")->SetTextSizePixels(24);
  leg->AddEntry(hRatioVErrJE, "V^{0} reconstruction", "LP")->SetTextSizePixels(24);
  leg->AddEntry(hRatioVErrJC, "Jet #it{p}_{T}", "LP")->SetTextSizePixels(24);
  leg->AddEntry(hRatioVErrUE, "Underlying subtraction", "LP")->SetTextSizePixels(24);
  leg->Draw();

  tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.16, 0.92, "ALICE p-Pb #sqrt{#it{s}_{NN}}=5.02 TeV");
  tex->DrawLatex(0.16, 0.84, "Systematic uncertainty of (#Lambda+#bar{#Lambda})/K_{s}^{0}");
  tex->DrawLatex(0.16, 0.76, "#it{p}_{T,jet}^{ch}>20 GeV/#it{c}, #it{R}=0.4, #it{R}(V^{0},jet)<0.4");
  CanvasEnd(can); if (bPrint) can->Print(Form("%s.pdf",can->GetName()));
//=============================================================================

  return;
}
