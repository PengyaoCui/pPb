void Fig1d_pp(const char *set="20161121", const Bool_t bPrint=kFALSE)
{
  gROOT->LoadMacro("utils/TPlotStd.h");
  gROOT->LoadMacro("utils/TAliFigs.h"); SetStyle();
//=============================================================================

  TFile *file = TFile::Open(Form("data/pp/%s/AnaEfficiency.root",set), "READ");
  TList *list = (TList*)file->Get("listHist_JE_JR04_JC04_V0A_000_010");
  file->Close();

  TH1D *hKshortJR = (TH1D*)list->FindObject("hKshortJR");
  TH1D *hLambdaJR = (TH1D*)list->FindObject("hLambdaJR");
  TH1D *hAntiLaJR = (TH1D*)list->FindObject("hAntiLaJR");

  TH1D *hKshortPR = (TH1D*)list->FindObject("hKshortPR");
  TH1D *hLambdaPR = (TH1D*)list->FindObject("hLambdaPR");
  TH1D *hAntiLaPR = (TH1D*)list->FindObject("hAntiLaPR");

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

  TH1D *hKshortJR = CalcEfficiency(hKshortJC, hKshortIn, "hKshortJR_Calc");
  TH1D *hLambdaJR = CalcEfficiency(hLambdaJC, hLambdaIn, "hLambdaJR_Calc");
  TH1D *hAntiLaJR = CalcEfficiency(hAntiLaJC, hAntiLaIn, "hAntiLaJR_Calc");

  TH1D *hKshortPR = CalcEfficiency(hKshortPC, hKshortIn, "hKshortJR_Calc");
  TH1D *hLambdaPR = CalcEfficiency(hLambdaPC, hLambdaIn, "hLambdaJR_Calc");
  TH1D *hAntiLaPR = CalcEfficiency(hAntiLaPC, hAntiLaIn, "hAntiLaJR_Calc");
//=============================================================================

  TH1F    *frm = 0;
  TCanvas *can = 0;
  TLegend *leg = 0;
  TLatex  *tex = 0;
  TLine  *line = 0;

  const Float_t dflx =  0.0, dfux = 12.;
  const Float_t dfly =  0.8, dfuy = 1.56;

  const Float_t dlsx = 0.05, dlsy = 0.05;
  const Float_t dtsx = 0.06, dtsy = 0.06;
  const Float_t dtox = 1.10, dtoy = 1.00;

  const TString stnx = "#it{p}_{T} (GeV/#it{c})";
  const TString stny = "Efficiency ratio to inclusive";
//=============================================================================

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

  can = MakeCanvas(Form("Fig1d_pp_%s",set));
  frm = can->DrawFrame(dflx, dfly, dfux, dfuy);
  SetupFrame(frm, dlsx, dlsy, dtsx, dtsy, dtox, dtoy, stnx, stny);

  DrawHisto(hKshortJR, wcl[1], wmk[1], "SAME");
  DrawHisto(hKshortPR, wcl[1], wmk[3], "SAME");

  DrawHisto(hLambdaJR, wcl[2], wmk[1], "SAME");
  DrawHisto(hLambdaPR, wcl[2], wmk[3], "SAME");

  DrawHisto(hAntiLaJR, wcl[3], wmk[1], "SAME");
  DrawHisto(hAntiLaPR, wcl[3], wmk[3], "SAME");

  leg = new TLegend(0.66, 0.64, 0.96, 0.80); SetupLegend(leg);
  leg->AddEntry(hJC, "#it{R}(V^{0},jet)<0.4", "LP")->SetTextSizePixels(24);
  leg->AddEntry(hPC, "V^{0}s in UE", "LP")->SetTextSizePixels(24);
  leg->Draw();

  leg = new TLegend(0.5, 0.56, 0.8, 0.80); SetupLegend(leg);
  leg->AddEntry(hKshortJR, "K_{S}^{0}", "L")->SetTextSizePixels(24);
  leg->AddEntry(hLambdaJR, "#Lambda", "L")->SetTextSizePixels(24);
  leg->AddEntry(hAntiLaJR, "#bar{#Lambda}", "L")->SetTextSizePixels(24);
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

//_____________________________________________________________________________
TH1D *CalcEfficiency(TH1D *hd, TH1D *hn, const TString sN)
{

  TH1D *hr = (TH1D*)hd->Clone(sN.Data());
  hr->Reset();

  for (Int_t k=1; k<=hr->GetNbinsX(); ++k) {
    Double_t ddv = hd->GetBinContent(k);
    Double_t dnv = hn->GetBinContent(k);

    Double_t dde = hd->GetBinError(k);
    Double_t dne = hn->GetBinError(k);

    Double_t drv = ddv / dnv;
    hr->SetBinContent(k, drv);
    hr->SetBinError(k, TMath::Sqrt(dde*dde + dne*dne));
  }

  return hr;
}
