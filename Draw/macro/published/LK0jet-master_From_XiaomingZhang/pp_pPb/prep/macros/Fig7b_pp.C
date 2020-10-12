void Fig7b_pp(char *set="20161121", const Bool_t bPrint=kFALSE)
{
  gROOT->LoadMacro("utils/THistool.h");
  gROOT->LoadMacro("utils/TPlotStd.h");
  gROOT->LoadMacro("utils/TAliFigs.h"); SetStyle();
//=============================================================================

  GetData(set);
  TH1D *hLtotalStatIn = (TH1D*)gDirectory->Get("hLtotalStatIn");
  TH1D *hLtotalSystIn = (TH1D*)gDirectory->Get("hLtotalSystIn");

  TH1D *hLtotalStatUE = (TH1D*)gDirectory->Get("hLtotalStatUE");
  TH1D *hLtotalSystUE = (TH1D*)gDirectory->Get("hLtotalSystUE");

  TH1D *hLtotalStatJE = (TH1D*)gDirectory->Get("hLtotalStatJE");
  TH1D *hLtotalSystJE = (TH1D*)gDirectory->Get("hLtotalSystJE");

  TH1D *hLtotalStatHD = (TH1D*)gDirectory->Get("hLtotalStatHD");
  TH1D *hLtotalSystHD = (TH1D*)gDirectory->Get("hLtotalSystHD");
//=============================================================================

  TGraphErrors *gLambdaStatIn = ConvHistogramToGraphErrors(hLtotalStatIn, 0x0, hLtotalStatIn->GetNbinsX());
  TGraphErrors *gLambdaSystIn = ConvHistogramToGraphErrors(hLtotalStatIn, hLtotalSystIn, hLtotalStatIn->GetNbinsX());

  TGraphErrors *gLambdaStatUE = ConvHistogramToGraphErrors(hLtotalStatUE, 0x0, hLtotalStatUE->GetNbinsX());
  TGraphErrors *gLambdaSystUE = ConvHistogramToGraphErrors(hLtotalStatUE, hLtotalSystUE, hLtotalStatUE->GetNbinsX());

  TGraphErrors *gLambdaStatJE = ConvHistogramToGraphErrors(hLtotalStatJE, 0x0, hLtotalStatJE->GetNbinsX());
  TGraphErrors *gLambdaSystJE = ConvHistogramToGraphErrors(hLtotalStatJE, hLtotalSystJE, hLtotalStatJE->GetNbinsX());

  TGraphErrors *gLambdaStatHD = ConvHistogramToGraphErrors(hLtotalStatHD, 0x0, hLtotalStatHD->GetNbinsX());
  TGraphErrors *gLambdaSystHD = ConvHistogramToGraphErrors(hLtotalStatHD, hLtotalSystHD, hLtotalStatJE->GetNbinsX());
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

  can = MakeCanvas(Form("Fig7b_pp_%s",set)); can->SetLogy();
  frm = can->DrawFrame(dflx, dfly, dfux, dfuy);
  SetupFrame(frm, dlsx, dlsy, dtsx, dtsy, dtox, dtoy, stnx, stny);

  DrawAliLogo(0.82, 0.90);
  DrawGraph(gLambdaStatIn, wcl[0], wmk[0], "P"); DrawGraph(gLambdaSystIn, wcl[0], "E2");
  DrawGraph(gLambdaStatUE, wcl[2], wmk[0], "P"); DrawGraph(gLambdaSystUE, wcl[2], "E2");
  DrawGraph(gLambdaStatJE, wcl[3], wmk[0], "P"); DrawGraph(gLambdaSystJE, wcl[3], "E2");
  DrawGraph(gLambdaStatHD, wcl[1], wmk[0], "P"); DrawGraph(gLambdaSystHD, wcl[1], "E2");

  leg = new TLegend(0.66, 0.60, 0.96, 0.88); SetupLegend(leg);
  leg->AddEntry(gLambdaStatIn, "Inclusive", "LP")->SetTextSizePixels(24);
  leg->AddEntry(gLambdaStatUE, "Underlying", "LP")->SetTextSizePixels(24);
  leg->AddEntry(gLambdaStatJE, "In jet", "LP")->SetTextSizePixels(24);
  leg->AddEntry(gLambdaStatHD, "UE subtracted", "LP")->SetTextSizePixels(24);
  leg->Draw();

  tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.16, 0.92, "pp #sqrt{#it{s}}=7 TeV");
  tex->DrawLatex(0.16, 0.28, "#Lambda+#bar{#Lambda}, #it{R}(V^{0},jet)<0.4, |#eta|<0.75");
  tex->DrawLatex(0.16, 0.20, "Jet: anti-#it{k}_{T}, #it{R}=0.4, #it{p}_{T,jet}^{ch}>10 GeV/#it{c}, |#eta_{jet}|<0.35");
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

//_____________________________________________________________________________
void GetData(const char *set)
{
  TFile *file = TFile::Open(Form("data/pp/%s/ppResults.root",set), "READ");
  TList *listIn = (TList*)file->Get("pplist_Inclusive");
  TList *listUE = (TList*)file->Get("pplistUE_PCM_JC04_JR04_PtJ10");
  TList *listJE = (TList*)file->Get("pplistJE_JC04_JR04_PtJ10");
  TList *listHD = (TList*)file->Get("pplistHD_JC04_JR04_PtJ10");
  file->Close();
//=============================================================================

  TH1D *hLambdaStatIn = (TH1D*)listIn->FindObject("hLambda_Stat"); hLambdaStatIn->SetName("hLambdaStatIn");
  TH1D *hLambdaSystIn = (TH1D*)listIn->FindObject("hLambda_Syst"); hLambdaSystIn->SetName("hLambdaSystIn");

  TH1D *hAntiLaStatIn = (TH1D*)listIn->FindObject("hAntiLa_Stat"); hAntiLaStatIn->SetName("hAntiLaStatIn");
  TH1D *hAntiLaSystIn = (TH1D*)listIn->FindObject("hAntiLa_Syst"); hAntiLaSystIn->SetName("hAntiLaSystIn");

  CombinStat(hLambdaStatIn, hAntiLaStatIn, "hLtotalStatIn");
  CombinStat(hLambdaSystIn, hAntiLaStatIn, "hLtotalSystIn");
//=============================================================================

  TH1D *hLambdaStatUE = (TH1D*)listUE->FindObject("hLambda_Stat"); hLambdaStatUE->SetName("hLambdaStatUE");
  TH1D *hLambdaSystUE = (TH1D*)listUE->FindObject("hLambda_Syst"); hLambdaSystUE->SetName("hLambdaSystUE");

  TH1D *hAntiLaStatUE = (TH1D*)listUE->FindObject("hAntiLa_Stat"); hAntiLaStatUE->SetName("hAntiLaStatUE");
  TH1D *hAntiLaSystUE = (TH1D*)listUE->FindObject("hAntiLa_Syst"); hAntiLaSystUE->SetName("hAntiLaSystUE");

  CombinStat(hLambdaStatUE, hAntiLaStatUE, "hLtotalStatUE");
  CombinStat(hLambdaSystUE, hAntiLaStatUE, "hLtotalSystUE");
//=============================================================================

  TH1D *hLambdaStatJE = (TH1D*)listJE->FindObject("hLambda_Stat"); hLambdaStatJE->SetName("hLambdaStatJE");
  TH1D *hLambdaSystJE = (TH1D*)listJE->FindObject("hLambda_Syst"); hLambdaSystJE->SetName("hLambdaSystJE");

  TH1D *hAntiLaStatJE = (TH1D*)listJE->FindObject("hAntiLa_Stat"); hAntiLaStatJE->SetName("hAntiLaStatJE");
  TH1D *hAntiLaSystJE = (TH1D*)listJE->FindObject("hAntiLa_Syst"); hAntiLaSystJE->SetName("hAntiLaSystJE");

  CombinStat(hLambdaStatJE, hAntiLaStatJE, "hLtotalStatJE");
  CombinStat(hLambdaSystJE, hAntiLaStatJE, "hLtotalSystJE");
//=============================================================================

  TH1D *hLambdaStatHD = (TH1D*)listHD->FindObject("hLambda_Stat"); hLambdaStatHD->SetName("hLambdaStatHD");
  TH1D *hLambdaSystHD = (TH1D*)listHD->FindObject("hLambda_Syst"); hLambdaSystHD->SetName("hLambdaSystHD");

  TH1D *hAntiLaStatHD = (TH1D*)listHD->FindObject("hAntiLa_Stat"); hAntiLaStatHD->SetName("hAntiLaStatHD");
  TH1D *hAntiLaSystHD = (TH1D*)listHD->FindObject("hAntiLa_Syst"); hAntiLaSystHD->SetName("hAntiLaSystHD");

  CombinStat(hLambdaStatHD, hAntiLaStatHD, "hLtotalStatHD");
  CombinStat(hLambdaSystHD, hAntiLaStatHD, "hLtotalSystHD");
//=============================================================================

  return;
}

//_____________________________________________________________________________
void CombinStat(TH1D *hL, TH1D *hA, const TString s)
{
  TH1D *hist = (TH1D*)hL->Clone(s.Data());
  for (Int_t k=1; k<=hist->GetNbinsX(); k++) {
    Double_t dValL = hL->GetBinContent(k);
    Double_t dValA = hA->GetBinContent(k);
    Double_t dErrL = hL->GetBinError(k);
    Double_t dErrA = hA->GetBinError(k);

    hist->SetBinContent(k, dValL+dValA);
    hist->SetBinError(k, TMath::Abs(dErrL*dErrL + dErrA*dErrA));
  }
//=============================================================================

  hist->SetDirectory(0);
  gDirectory->Add(hist);

  return;
}

//_____________________________________________________________________________
void CombinSyst(TH1D *hL, TH1D *hA, const TString a)
{
  TH1D *hist = (TH1D*)hL->Clone(s.Data());

  for (Int_t k=1; k<=hist->GetNbinsX(); k++) {
    Double_t dErrL = hL->GetBinContent(k);
    Double_t dErrA = hA->GetBinContent(k);

    hist->SetBinContent(k, TMath::Abs(dErrL*dErrL + dErrA*dErrA));
  }
//=============================================================================

  hist->SetDirectory(0);
  gDirectory->Add(hist);

  return;
}
