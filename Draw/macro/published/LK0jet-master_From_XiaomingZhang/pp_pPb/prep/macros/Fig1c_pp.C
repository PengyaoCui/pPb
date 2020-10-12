void Fig1c_pp(const char *set="20161121", const Bool_t bPrint=kFALSE)
{
  gROOT->LoadMacro("utils/TPlotStd.h");
  gROOT->LoadMacro("utils/TAliFigs.h"); SetStyle();
//=============================================================================

  TFile *file = TFile::Open(Form("data/pp/%s/AnaEfficiency.root",set), "READ");
  TList *list = (TList*)file->Get("listHist_JE_JR04_JC04_V0A_000_010");
  file->Close();

  TH1D *hKshortIn = (TH1D*)list->FindObject("hKshortMB");
  TH1D *hLambdaIn = (TH1D*)list->FindObject("hLambdaMB");
  TH1D *hAntiLaIn = (TH1D*)list->FindObject("hAntiLaMB");

  TH1D *hKshortJC = (TH1D*)list->FindObject("hKshortJC");
  TH1D *hLambdaJC = (TH1D*)list->FindObject("hLambdaJC");
  TH1D *hAntiLaJC = (TH1D*)list->FindObject("hAntiLaJC");

  TH1D *hKshortPC = (TH1D*)list->FindObject("hKshortPC");
  TH1D *hLambdaPC = (TH1D*)list->FindObject("hLambdaPC");
  TH1D *hAntiLaPC = (TH1D*)list->FindObject("hAntiLaPC");
//=============================================================================

  TH1F    *frm = 0;
  TCanvas *can = 0;
  TLegend *leg = 0;
  TLatex  *tex = 0;
  TLine  *line = 0;

  const Float_t dflx =  0., dfux = 12.;
  const Float_t dfly =  0., dfuy = 1.02;

  const Float_t dlsx = 0.05, dlsy = 0.05;
  const Float_t dtsx = 0.06, dtsy = 0.06;
  const Float_t dtox = 1.10, dtoy = 1.00;

  const TString stnx = "#it{p}_{T} (GeV/#it{c})";
  const TString stny = "Efficiency";
//=============================================================================

  TH1D *hIn = new TH1D("hIn", "", 10, 0., 10.);
  hIn->SetLineWidth(2);
  hIn->SetLineColor(wcl[0]);
  hIn->SetMarkerStyle(wmk[0]);
  hIn->SetMarkerColor(wcl[0]);

  TH1D *hJC = new TH1D("hJC", "", 10, 0., 10.);
  hJC->SetLineWidth(2);
  hJC->SetLineColor(wcl[0]);
  hJC->SetMarkerStyle(wmk[1]);
  hJC->SetMarkerColor(wcl[0]);

  TH1D *hPC = new TH1D("hPC", "", 10, 0., 10.);
  hPC->SetLineWidth(2);
  hPC->SetLineColor(wcl[0]);
  hPC->SetMarkerStyle(wmk[3]);
  hPC->SetMarkerColor(wcl[0]);
//=============================================================================

  can = MakeCanvas(Form("Fig1c_pp_%s",set));
  frm = can->DrawFrame(dflx, dfly, dfux, dfuy);
  SetupFrame(frm, dlsx, dlsy, dtsx, dtsy, dtox, dtoy, stnx, stny);

  DrawHisto(hKshortIn, wcl[1], wmk[0], "SAME");
  DrawHisto(hKshortJC, wcl[1], wmk[1], "SAME");
  DrawHisto(hKshortPC, wcl[1], wmk[3], "SAME");

  DrawHisto(hLambdaIn, wcl[2], wmk[0], "SAME");
  DrawHisto(hLambdaJC, wcl[2], wmk[1], "SAME");
  DrawHisto(hLambdaPC, wcl[2], wmk[3], "SAME");

  DrawHisto(hAntiLaIn, wcl[3], wmk[0], "SAME");
  DrawHisto(hAntiLaJC, wcl[3], wmk[1], "SAME");
  DrawHisto(hAntiLaPC, wcl[3], wmk[3], "SAME");

  leg = new TLegend(0.66, 0.56, 0.96, 0.80); SetupLegend(leg);
  leg->AddEntry(hIn, "Inclusive", "LP")->SetTextSizePixels(24);
  leg->AddEntry(hJC, "#it{R}(V^{0},jet)<0.4", "LP")->SetTextSizePixels(24);
  leg->AddEntry(hPC, "V^{0}s in UE", "LP")->SetTextSizePixels(24);
  leg->Draw();

  leg = new TLegend(0.5, 0.56, 0.8, 0.80); SetupLegend(leg);
  leg->AddEntry(hKshortIn, "K_{S}^{0}", "L")->SetTextSizePixels(24);
  leg->AddEntry(hLambdaIn, "#Lambda", "L")->SetTextSizePixels(24);
  leg->AddEntry(hAntiLaIn, "#bar{#Lambda}", "L")->SetTextSizePixels(24);
  leg->Draw();

  tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.16, 0.92, "ALICE pp #sqrt{#it{s}}=7 TeV");
  tex->DrawLatex(0.16, 0.84, "Jet: anti-#it{k}_{T}, #it{R}=0.4, #it{p}_{T,jet}^{ch}>10 GeV/#it{c}, |#eta_{jet}|<0.35");
  tex->DrawLatex(0.16, 0.76, "|#eta_{V^{0}}|<0.75");
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
