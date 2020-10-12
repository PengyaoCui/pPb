const Int_t   nSyst   = 5;
const TString sSyst[] = { "Topo", "Ctau", "CompM", "PIDinTPC", "RowsTPC" , "SigmaInvM" };
const TString sLegN[] = { "Topological", "Proper lifetime", "Competing V^{0}",
                          "PID",         "Track selection", "Signal extraction" };
//=============================================================================

void PlotSystIncl(const Bool_t bPrint=kFALSE)
{
  const TString sWorkDir = gSystem->WorkingDirectory();
  const TString sPckgDir = gSystem->DirName(sWorkDir.Data());
  const TString sUtilDir = Form("%s/include", sPckgDir.Data());
//=============================================================================

  gROOT->LoadMacro(Form("%s/TUtilsPlotStd.h",sUtilDir.Data()));
  gROOT->LoadMacro(Form("%s/TUtilsAliFigs.h",sUtilDir.Data())); SetStyle();
//=============================================================================

  TFile *file = TFile::Open("data/AnaSystematic.root", "READ");
  TList *list = (TList*)file->Get("listIncl");
  file->Close();

  TH1D *hKshortSyst = (TH1D*)list->FindObject("hKshortSyst");
  TH1D *hLambdaSyst = (TH1D*)list->FindObject("hLambdaSyst");
  TH1D *hAntiLaSyst = (TH1D*)list->FindObject("hAntiLaSyst");

  TH1D *hKshortErrR[nSyst];
  TH1D *hLambdaErrR[nSyst];
  TH1D *hAntiLaErrR[nSyst];
  for (Int_t i=0; i<nSyst; i++) {
    hKshortErrR[i] = (TH1D*)list->FindObject(Form("hKshortErr_%s",sSyst[i].Data()));
    hLambdaErrR[i] = (TH1D*)list->FindObject(Form("hLambdaErr_%s",sSyst[i].Data()));
    hAntiLaErrR[i] = (TH1D*)list->FindObject(Form("hAntiLaErr_%s",sSyst[i].Data()));
  }
//=============================================================================

  TH1F    *frm = 0;
  TCanvas *can = 0;
  TLegend *leg = 0;
  TLatex  *tex = 0;
  TLine  *line = 0;

  const Float_t dflx =  0.6, dfux = 12.;
  const Float_t dfly =  0.0, dfuy = 0.06;

  const Float_t dlsx = 0.05, dlsy = 0.05;
  const Float_t dtsx = 0.06, dtsy = 0.06;
  const Float_t dtox = 1.10, dtoy = 1.00;

  const TString stnx = "#it{p}_{T} (GeV/#it{c})";
  const TString stny = "Relative systematic error";
//=============================================================================

  can = MakeCanvas("SystIncl_Kshort");
  frm = can->DrawFrame(dflx, dfly, dfux, 0.05);
  SetupFrame(frm, dlsx, dlsy, dtsx, dtsy, dtox, dtoy, stnx, stny);

  leg = new TLegend(0.36, 0.66, 0.96, 0.88); SetupLegend(leg);
  leg->SetNColumns(2);

  DrawHisto(hKshortSyst, wcl[0], wmk[0], "SAME");
  leg->AddEntry(hKshortSyst, "Total", "LP")->SetTextSizePixels(24);

  for (Int_t i=0; i<nSyst; i++) {
    DrawHisto(hKshortErrR[i], (i==4 ? wcl[7] : wcl[i+1]), wmk[0], "SAME");
    leg->AddEntry(hKshortErrR[i], sLegN[i], "LP")->SetTextSizePixels(24);
  } leg->Draw();

  tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.16, 0.92, "ALICE p-Pb #sqrt{#it{s}_{NN}}=5.02 TeV");
  tex->DrawLatex(0.16, 0.84, "K_{s}^{0}, |#eta|<0.75");
  CanvasEnd(can); if (bPrint) can->Print(Form("%s.pdf",can->GetName()));
//=============================================================================

  can = MakeCanvas("SystIncl_Lambda");
  frm = can->DrawFrame(dflx, dfly, dfux, 0.14);
  SetupFrame(frm, dlsx, dlsy, dtsx, dtsy, dtox, dtoy, stnx, stny);

  leg = new TLegend(0.36, 0.66, 0.96, 0.88); SetupLegend(leg);
  leg->SetNColumns(2);

  DrawHisto(hLambdaSyst, wcl[0], wmk[0], "SAME");
  leg->AddEntry(hLambdaSyst, "Total", "LP")->SetTextSizePixels(24);

  for (Int_t i=0; i<nSyst; i++) {
    DrawHisto(hLambdaErrR[i], (i==4 ? wcl[7] : wcl[i+1]), wmk[0], "SAME");
    leg->AddEntry(hLambdaErrR[i], sLegN[i], "LP")->SetTextSizePixels(24);
  } leg->Draw();

  tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.16, 0.92, "ALICE p-Pb #sqrt{#it{s}_{NN}}=5.02 TeV");
  tex->DrawLatex(0.16, 0.84, "#Lambda, |#eta|<0.75");
  CanvasEnd(can); if (bPrint) can->Print(Form("%s.pdf",can->GetName()));
//=============================================================================

  can = MakeCanvas("SystIncl_AntiLa");
  frm = can->DrawFrame(dflx, dfly, dfux, 0.14);
  SetupFrame(frm, dlsx, dlsy, dtsx, dtsy, dtox, dtoy, stnx, stny);

  leg = new TLegend(0.36, 0.66, 0.96, 0.88); SetupLegend(leg);
  leg->SetNColumns(2);

  DrawHisto(hAntiLaSyst, wcl[0], wmk[0], "SAME");
  leg->AddEntry(hAntiLaSyst, "Total", "LP")->SetTextSizePixels(24);

  for (Int_t i=0; i<nSyst; i++) {
    DrawHisto(hAntiLaErrR[i], (i==4 ? wcl[7] : wcl[i+1]), wmk[0], "SAME");
    leg->AddEntry(hAntiLaErrR[i], sLegN[i], "LP")->SetTextSizePixels(24);
  } leg->Draw();

  tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.16, 0.92, "ALICE p-Pb #sqrt{#it{s}_{NN}}=5.02 TeV");
  tex->DrawLatex(0.16, 0.84, "#bar{#Lambda}, |#eta|<0.75");
  CanvasEnd(can); if (bPrint) can->Print(Form("%s.pdf",can->GetName()));
//=============================================================================

  return;
}

