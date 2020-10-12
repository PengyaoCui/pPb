void PlotEffiJC04(const Bool_t bPrint=kFALSE)
{
  const TString sWorkDir = gSystem->WorkingDirectory();
  const TString sPckgDir = gSystem->DirName(sWorkDir.Data());
  const TString sUtilDir = Form("%s/include", sPckgDir.Data());
//=============================================================================

  gROOT->LoadMacro(Form("%s/TUtilsPlotEff.h",sUtilDir.Data()));
  gROOT->LoadMacro(Form("%s/TUtilsAliFigs.h",sUtilDir.Data())); SetStyle();
//=============================================================================

  TFile *file = TFile::Open("data/AnaEfficiency.root", "READ");
  TList *list = (TList*)file->Get("listHist_JE_JR04_JC04_V0A_000_010");
  file->Close();

  TH1D *hKshortMB = (TH1D*)list->FindObject("hKshortMB");
  TH1D *hLambdaMB = (TH1D*)list->FindObject("hLambdaMB");
  TH1D *hAntiLaMB = (TH1D*)list->FindObject("hAntiLaMB");

  TH1D *hKshortJC = (TH1D*)list->FindObject("hKshortJC");
  TH1D *hLambdaJC = (TH1D*)list->FindObject("hLambdaJC");
  TH1D *hAntiLaJC = (TH1D*)list->FindObject("hAntiLaJC");

  TH1D *hKshortPC = (TH1D*)list->FindObject("hKshortPC");
  TH1D *hLambdaPC = (TH1D*)list->FindObject("hLambdaPC");
  TH1D *hAntiLaPC = (TH1D*)list->FindObject("hAntiLaPC");

  TH1D *hKshortJR = (TH1D*)list->FindObject("hKshortJR");
  TH1D *hLambdaJR = (TH1D*)list->FindObject("hLambdaJR");
  TH1D *hAntiLaJR = (TH1D*)list->FindObject("hAntiLaJR");

  TH1D *hKshortPR = (TH1D*)list->FindObject("hKshortPR");
  TH1D *hLambdaPR = (TH1D*)list->FindObject("hLambdaPR");
  TH1D *hAntiLaPR = (TH1D*)list->FindObject("hAntiLaPR");
//=============================================================================

  TH1F    *frm = 0;
  TCanvas *can = 0;
  TLegend *leg = 0;
  TLatex  *tex = 0;
  TLine  *line = 0;

  const Float_t dflx =  0.6, dfux = 12.;
  const Float_t dfly =  0.0, dfuy = 1.2;

  const Float_t dlsx = 0.05, dlsy = 0.05;
  const Float_t dtsx = 0.06, dtsy = 0.06;
  const Float_t dtox = 1.10, dtoy = 1.00;

  const TString stnx = "#it{p}_{T} (GeV/#it{c})";
  const TString stny = "";
//=============================================================================

  TPad *pUpper = 0;
  TPad *pLower = 0;
  can = MakeCanvas("EffiJC04_Kshort");
  pUpper = MakePadUpper(can->GetName());
  frm = pUpper->DrawFrame(dflx, 0.12, dfux, 0.58);
  SetupFrame(frm, 0., 0.05, 0., 0.07, 0., 0.7, "", "Efficiency");

  DrawHisto(hKshortMB, wcl[0], wmk[0], "SAME");
  DrawHisto(hKshortJC, wcl[1], wmk[0], "SAME");
  DrawHisto(hKshortPC, wcl[2], wmk[0], "SAME");

  leg = new TLegend(0.50, 0.04, 0.96, 0.28); SetupLegend(leg);
  leg->AddEntry(hKshortMB, "Inclusive", "LP")->SetTextSizePixels(24);
  leg->AddEntry(hKshortJC, "#it{R}(V^{0},jet)<0.4", "LP")->SetTextSizePixels(24);
  leg->AddEntry(hKshortPC, "#it{R}(V^{0},jet)>0.6", "LP")->SetTextSizePixels(24);
  leg->Draw();

  tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.14, 0.92, "ALICE p-Pb #sqrt{#it{s}_{NN}}=5.02 TeV");
  tex->DrawLatex(0.14, 0.84, "Jet: anti-#it{k}_{T}, #it{R}=0.4, #it{p}_{T,jet}^{ch}>10 GeV/#it{c}, |#eta_{jet}|<0.35");
  tex->DrawLatex(0.14, 0.76, "K_{s}^{0}, |#eta|<0.75");

  can->cd();
  pLower = MakePadLower(can->GetName());
  frm = pLower->DrawFrame(dflx, 0.82, dfux, 1.38);
  SetupFrame(frm, 0.08, 0.07, 0.1, 0.1, 1.1, 0.5, stnx, "Ratio to inclusive");

  DrawHisto(hKshortJR, wcl[1], wmk[0], "SAME");
  DrawHisto(hKshortPR, wcl[2], wmk[0], "SAME");

  can->cd();
  CanvasEnd(can); if (bPrint) can->Print(Form("%s.pdf",can->GetName()));
//=============================================================================

  can = MakeCanvas("EffiJC04_Lambda");
  pUpper = MakePadUpper(can->GetName());
  frm = pUpper->DrawFrame(dflx, 0.12, dfux, 0.58);
  SetupFrame(frm, 0., 0.05, 0., 0.07, 0., 0.7, "", "Efficiency");

  DrawHisto(hLambdaMB, wcl[0], wmk[0], "SAME");
  DrawHisto(hLambdaJC, wcl[1], wmk[0], "SAME");
  DrawHisto(hLambdaPC, wcl[2], wmk[0], "SAME");

  leg = new TLegend(0.50, 0.04, 0.96, 0.28); SetupLegend(leg);
  leg->AddEntry(hLambdaMB, "Inclusive", "LP")->SetTextSizePixels(24);
  leg->AddEntry(hLambdaJC, "#it{R}(V^{0},jet)<0.4", "LP")->SetTextSizePixels(24);
  leg->AddEntry(hLambdaPC, "#it{R}(V^{0},jet)>0.6", "LP")->SetTextSizePixels(24);
  leg->Draw();

  tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.14, 0.92, "ALICE p-Pb #sqrt{#it{s}_{NN}}=5.02 TeV");
  tex->DrawLatex(0.14, 0.84, "Jet: anti-#it{k}_{T}, #it{R}=0.4, #it{p}_{T,jet}^{ch}>10 GeV/#it{c}, |#eta_{jet}|<0.35");
  tex->DrawLatex(0.14, 0.76, "#Lambda, |#eta|<0.75");

  can->cd();
  pLower = MakePadLower(can->GetName());
  frm = pLower->DrawFrame(dflx, 0.82, dfux, 1.38);
  SetupFrame(frm, 0.08, 0.07, 0.1, 0.1, 1.1, 0.5, stnx, "Ratio to inclusive");

  DrawHisto(hLambdaJR, wcl[1], wmk[0], "SAME");
  DrawHisto(hLambdaPR, wcl[2], wmk[0], "SAME");

  can->cd();
  CanvasEnd(can); if (bPrint) can->Print(Form("%s.pdf",can->GetName()));
//=============================================================================

  can = MakeCanvas("EffiJC04_AntiLa");
  pUpper = MakePadUpper(can->GetName());
  frm = pUpper->DrawFrame(dflx, 0.12, dfux, 0.58);
  SetupFrame(frm, 0., 0.05, 0., 0.07, 0., 0.7, "", "Efficiency");

  DrawHisto(hAntiLaMB, wcl[0], wmk[0], "SAME");
  DrawHisto(hAntiLaJC, wcl[1], wmk[0], "SAME");
  DrawHisto(hAntiLaPC, wcl[2], wmk[0], "SAME");

  leg = new TLegend(0.50, 0.04, 0.96, 0.28); SetupLegend(leg);
  leg->AddEntry(hAntiLaMB, "Inclusive", "LP")->SetTextSizePixels(24);
  leg->AddEntry(hAntiLaJC, "#it{R}(V^{0},jet)<0.4", "LP")->SetTextSizePixels(24);
  leg->AddEntry(hAntiLaPC, "#it{R}(V^{0},jet)>0.6", "LP")->SetTextSizePixels(24);
  leg->Draw();

  tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.14, 0.92, "ALICE p-Pb #sqrt{#it{s}_{NN}}=5.02 TeV");
  tex->DrawLatex(0.14, 0.84, "Jet: anti-#it{k}_{T}, #it{R}=0.4, #it{p}_{T,jet}^{ch}>10 GeV/#it{c}, |#eta_{jet}|<0.35");
  tex->DrawLatex(0.14, 0.76, "#bar{#Lambda}, |#eta|<0.75");

  can->cd();
  pLower = MakePadLower(can->GetName());
  frm = pLower->DrawFrame(dflx, 0.82, dfux, 1.38);
  SetupFrame(frm, 0.08, 0.07, 0.1, 0.1, 1.1, 0.5, stnx, "Ratio to inclusive");

  DrawHisto(hAntiLaJR, wcl[1], wmk[0], "SAME");
  DrawHisto(hAntiLaPR, wcl[2], wmk[0], "SAME");

  can->cd();
  CanvasEnd(can); if (bPrint) can->Print(Form("%s.pdf",can->GetName()));
//=============================================================================

  return;
}

