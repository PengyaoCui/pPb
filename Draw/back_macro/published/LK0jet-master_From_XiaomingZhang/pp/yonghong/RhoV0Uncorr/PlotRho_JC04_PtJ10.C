void PlotRho_JC04_PtJ10(const Bool_t bPrint=kFALSE)
{
  const TString sWorkDir = gSystem->WorkingDirectory();
  const TString sPckgDir = gSystem->DirName(sWorkDir.Data());
  const TString sUtilDir = Form("%s/include", sPckgDir.Data());
//=============================================================================

  gROOT->LoadMacro(Form("%s/TUtilsPlotStd.h",sUtilDir.Data()));
  gROOT->LoadMacro(Form("%s/TUtilsAliFigs.h",sUtilDir.Data())); SetStyle();
//=============================================================================

  TFile *file = TFile::Open("data/AnaV0Rho.root", "READ");

  TList *list = (TList*)file->Get("listHist_JR04_JC04_PtJ10");
  file->Close();

  TH1D *hKshortMBa = (TH1D*)list->FindObject("hKshortMBa");
  TH1D *hLambdaMBa = (TH1D*)list->FindObject("hLambdaMBa");

  TH1D *hKshortJCa = (TH1D*)list->FindObject("hKshortJCa");
  TH1D *hLambdaJCa = (TH1D*)list->FindObject("hLambdaJCa");

  TH1D *hKshortPCa = (TH1D*)list->FindObject("hKshortPCa");
  TH1D *hLambdaPCa = (TH1D*)list->FindObject("hLambdaPCa");
//=============================================================================

  TH1F    *frm = 0;
  TCanvas *can = 0;
  TLegend *leg = 0;
  TLatex  *tex = 0;
  TLine  *line = 0;

  const Float_t dflx =  0.6,  dfux = 12.;
  const Float_t dfly =  8e-6, dfuy = 1.6;

  const Float_t dlsx = 0.05, dlsy = 0.05;
  const Float_t dtsx = 0.06, dtsy = 0.06;
  const Float_t dtox = 1.10, dtoy = 1.00;

  const TString stnx = "#it{p}_{T} (GeV/#it{c})";
  const TString stny = "d#rho/d#it{p}_{T} (GeV/#it{c} rad)^{-1}";
//=============================================================================

  can = MakeCanvas("Rho_Kshort_JC04_PtJ10"); can->SetLogy();
  frm = can->DrawFrame(dflx, dfly, dfux, dfuy);
  SetupFrame(frm, dlsx, dlsy, dtsx, dtsy, dtox, dtoy, stnx, stny);

  DrawHisto(hKshortMBa, wcl[0], wmk[0], "SAME");
  DrawHisto(hKshortJCa, wcl[1], wmk[0], "SAME");
  DrawHisto(hKshortPCa, wcl[2], wmk[0], "SAME");

  leg = new TLegend(0.64, 0.72, 0.96, 0.96); SetupLegend(leg);
  leg->AddEntry(hKshortMBa, "Inclusive", "LP")->SetTextSizePixels(24);
  leg->AddEntry(hKshortJCa, "#it{R}(V^{0},jet)<0.4", "LP")->SetTextSizePixels(24);
  leg->AddEntry(hKshortPCa, "V^{0} in perp. cone", "LP")->SetTextSizePixels(24);
  leg->Draw();

  tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.16, 0.92, "ALICE p-p #sqrt{#it{s}}=7 TeV");
  tex->DrawLatex(0.16, 0.84, "Jet: anti-#it{k}_{T}, #it{R}=0.4, #it{p}_{T,jet}^{ch}>8 GeV/#it{c}, |#eta_{jet}|<0.35");
  tex->DrawLatex(0.16, 0.18, "K_{s}^{0}, |#eta|<0.75");
  CanvasEnd(can); if (bPrint) can->Print(Form("%s.pdf",can->GetName()));
//=============================================================================

  can = MakeCanvas("Rho_Lambda_JC04_PtJ10"); can->SetLogy();
  frm = can->DrawFrame(dflx, dfly, dfux, dfuy);
  SetupFrame(frm, dlsx, dlsy, dtsx, dtsy, dtox, dtoy, stnx, stny);

  DrawHisto(hLambdaMBa, wcl[0], wmk[0], "SAME");
  DrawHisto(hLambdaJCa, wcl[1], wmk[0], "SAME");
  DrawHisto(hLambdaPCa, wcl[2], wmk[0], "SAME");

  leg = new TLegend(0.64, 0.72, 0.96, 0.96); SetupLegend(leg);
  leg->AddEntry(hLambdaMBa, "Inclusive", "LP")->SetTextSizePixels(24);
  leg->AddEntry(hLambdaJCa, "#it{R}(V^{0},jet)<0.4", "LP")->SetTextSizePixels(24);
  leg->AddEntry(hLambdaPCa, "V^{0} in perp. cone", "LP")->SetTextSizePixels(24);
  leg->Draw();

  tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.16, 0.92, "ALICE p-p #sqrt{#it{s}}=7 TeV");
  tex->DrawLatex(0.16, 0.84, "Jet: anti-#it{k}_{T}, #it{R}=0.4, #it{p}_{T,jet}^{ch}>8 GeV/#it{c}, |#eta_{jet}|<0.35");
  tex->DrawLatex(0.16, 0.18, "#Lambda+#bar{#Lambda}, |#eta|<0.75");
  CanvasEnd(can); if (bPrint) can->Print(Form("%s.pdf",can->GetName()));
//=============================================================================

  return;
}

