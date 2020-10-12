void Fig4a_pPb(const Bool_t bPrint=kFALSE)
{
  gROOT->LoadMacro("utils/TPlotStd.h");
  gROOT->LoadMacro("utils/TAliFigs.h"); SetStyle();
//=============================================================================

  TFile *file = TFile::Open("data/pPb/AnalysisResults.root", "READ");
  TList *list = (TList*)file->Get("listHD_JC04_JR04_PtJ10");
  file->Close();

  TH1D *hHD = (TH1D*)list->FindObject("hRatioV_Syst");
  hHD->SetName("HD");  // Total
//=============================================================================

  file = TFile::Open("data/pPb/AnalysisOutputs_SystJE.root", "READ");
  list = (TList*)file->Get("list_SystJE_RatioV_PtJ10");
  file->Close();

  TH1D *hJE = (TH1D*)list->FindObject("hRatioVErr_JC04");
  hJE->SetName("JE");  // Jet #it{p}_{T} scale
//=============================================================================

  file = TFile::Open("data/pPb/AnalysisOutputs_SystUE.root", "READ");
  list = (TList*)file->Get("list_SystUE_RatioV_PtJ10");
  file->Close();

  TH1D *hUE = (TH1D*)list->FindObject("hRatioVErr_JC04");
  hUE->SetName("UE");  // Underlying subtraction
//=============================================================================

  TH1D *hJC = (TH1D*)hHD->Clone("hJC");
  hJC->Reset();  // V^{0} reconstruction
  for (Int_t k=1; k<=hJC->GetNbinsX(); k++) {
    Double_t dHD = hHD->GetBinContent(k);
    Double_t dJE = hJE->GetBinContent(k);
    Double_t dUE = hUE->GetBinContent(k);
    hJC->SetBinContent(k, TMath::Sqrt(dHD*dHD - dJE*dJE -dUE*dUE));
  }
//=============================================================================

  TH1F    *frm = 0;
  TCanvas *can = 0;
  TLegend *leg = 0;
  TLatex  *tex = 0;
  TLine  *line = 0;

  const Float_t dflx =  0.0, dfux = 12.;
  const Float_t dfly =  0.0, dfuy = 0.40;

  const Float_t dlsx = 0.05, dlsy = 0.05;
  const Float_t dtsx = 0.06, dtsy = 0.06;
  const Float_t dtox = 1.10, dtoy = 1.00;

  const TString stnx = "#it{p}_{T} (GeV/#it{c})";
  const TString stny = "Relative systematic uncertainty";
//=============================================================================

  can = MakeCanvas("Fig4a_pPb");
  frm = can->DrawFrame(dflx, dfly, dfux, dfuy);
  SetupFrame(frm, dlsx, dlsy, dtsx, dtsy, dtox, dtoy, stnx, stny);

  DrawHisto(hHD, wcl[0], wmk[0], "SAME");
  DrawHisto(hJC, wcl[1], wmk[0], "SAME");
  DrawHisto(hJE, wcl[3], wmk[0], "SAME");
  DrawHisto(hUE, wcl[2], wmk[0], "SAME");

  leg = new TLegend(0.32, 0.56, 0.96, 0.72); SetupLegend(leg);
  leg->SetNColumns(2);
  leg->AddEntry(hHD, "Total", "L")->SetTextSizePixels(24);
  leg->AddEntry(hJC, "V^{0} reconstruction", "L")->SetTextSizePixels(24);
  leg->AddEntry(hJE, "Jet #it{p}_{T} scale", "L")->SetTextSizePixels(24);
  leg->AddEntry(hUE, "UE subtraction", "L")->SetTextSizePixels(24);
  leg->Draw();

  tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.16, 0.92, "ALICE p-Pb #sqrt{#it{s}_{NN}}=5.02 TeV");
  tex->DrawLatex(0.16, 0.84, "Systematic uncertainty of (#Lambda+#bar{#Lambda})/K_{s}^{0}");
  tex->DrawLatex(0.16, 0.76, "#it{p}_{T,jet}^{ch}>10 GeV/#it{c}, #it{R}=0.4, #it{R}(V^{0},jet)<0.4");
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
