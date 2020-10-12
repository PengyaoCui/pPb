const Int_t   nSyst   = 7;
const TString sSyst[] = { "Total", "Topo", "Ctau", "CompM", "PIDinTPC",  "RowsTPC" , "Sig" };
const TString sLegN[] = { "Total",   "Topological", "Proper lifetime", "Competing V^{0}",
                          "TPC PID", "Track selection", "Signal extraction" };
//=============================================================================

void Fig2c_pp(const char *set="20161128", const Bool_t bPrint=kFALSE)
{
  gROOT->LoadMacro("utils/TPlotStd.h");
  gROOT->LoadMacro("utils/TAliFigs.h"); SetStyle();
//=============================================================================

  TFile *file = TFile::Open(Form("data/pp/%s/AnaSystematic_v1.root",set), "READ");
  TList *list = (TList*)file->Get("listIncl");
  file->Close();

  TH1D *hK[nSyst];
  hK[0] = (TH1D*)list->FindObject("hKshortSyst");
  for (Int_t i=1; i<nSyst; i++) {
    hK[i] = (TH1D*)list->FindObject(Form("hKshortErr_%s",sSyst[i].Data()));
  }
//=============================================================================

  TH1F    *frm = 0;
  TCanvas *can = 0;
  TLegend *leg = 0;
  TLatex  *tex = 0;
  TLine  *line = 0;

  const Float_t dflx =  0.0, dfux = 12.;
  const Float_t dfly =  0.0, dfuy = 0.18;

  const Float_t dlsx = 0.05, dlsy = 0.05;
  const Float_t dtsx = 0.06, dtsy = 0.06;
  const Float_t dtox = 1.10, dtoy = 1.00;

  const TString stnx = "#it{p}_{T} (GeV/#it{c})";
  const TString stny = "Relative systematic uncertainty";
//=============================================================================

  can = MakeCanvas(Form("Fig2c_pp_%s",set));
  frm = can->DrawFrame(dflx, dfly, dfux, dfuy);
  SetupFrame(frm, dlsx, dlsy, dtsx, dtsy, dtox, dtoy, stnx, stny);

  leg = new TLegend(0.36, 0.66, 0.96, 0.88); SetupLegend(leg);
  leg->SetNColumns(2);

  for (Int_t i=0; i<nSyst; i++) {
    DrawHisto(hK[i],  wcl[i], "SAME");
    leg->AddEntry(hK[i], sLegN[i], "L")->SetTextSizePixels(24);
  } leg->Draw();

  tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.16, 0.92, "ALICE pp #sqrt{#it{s}}=7 TeV");
  tex->DrawLatex(0.16, 0.84, "K_{s}^{0}, |#eta|<0.75");
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
