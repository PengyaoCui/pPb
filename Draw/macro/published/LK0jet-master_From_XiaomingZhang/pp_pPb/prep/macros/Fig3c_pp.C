void Fig3c_pp(const Bool_t bPrint=kFALSE)
{
  gROOT->LoadMacro("utils/TPlotStd.h");
  gROOT->LoadMacro("utils/TAliFigs.h"); SetStyle();
//=============================================================================

  TFile *file = TFile::Open("data/pp/syst/AnaL2K_Pt_PtJE.root", "READ");
  TList *listHD = (TList*)file->Get("pplistHD_JC04_JR04_PtJ10");
  file->Close();

  TH1D *hHD = (TH1D*)listHD->FindObject("hKshort_Syst"); hHD->SetName("hHD");
//=============================================================================

  TFile *file = TFile::Open("data/pp/syst/AnaSystematic.root", "READ");
  TList *listIn = (TList*)file->Get("list_Inclusive_Uncert");
  TList *listJE = (TList*)file->Get("list_JetPt_Uncert");
  TList *listUE = (TList*)file->Get("list_UE_Uncert");
  file->Close();

  TH1D *hIn = (TH1D*)listIn->FindObject("hKshort"); hIn->SetName("hIn");
  TH1D *hJE = (TH1D*)listJE->FindObject("hKshort"); hJE->SetName("hJE");
  TH1D *hUE = (TH1D*)listUE->FindObject("hKshort"); hUE->SetName("hUE");
//=============================================================================

  TH1F    *frm = 0;
  TCanvas *can = 0;
  TLegend *leg = 0;
  TLatex  *tex = 0;
  TLine  *line = 0;

  const Float_t dflx =  0.0, dfux = 12.;
  const Float_t dfly =  0.0, dfuy = 0.8;

  const Float_t dlsx = 0.05, dlsy = 0.05;
  const Float_t dtsx = 0.06, dtsy = 0.06;
  const Float_t dtox = 1.10, dtoy = 1.00;

  const TString stnx = "#it{p}_{T} (GeV/#it{c})";
  const TString stny = "Relative systematic uncertainty";
//=============================================================================

  can = MakeCanvas("Fig3c_pp");
  frm = can->DrawFrame(dflx, dfly, dfux, dfuy);
  SetupFrame(frm, dlsx, dlsy, dtsx, dtsy, dtox, dtoy, stnx, stny);

  DrawHisto(hHD, wcl[0], wmk[0], "SAME");
  DrawHisto(hIn, wcl[1], wmk[0], "SAME");
  DrawHisto(hJE, wcl[3], wmk[0], "SAME");
  DrawHisto(hUE, wcl[2], wmk[0], "SAME");

  leg = new TLegend(0.32, 0.56, 0.96, 0.72); SetupLegend(leg);
  leg->SetNColumns(2);
  leg->AddEntry(hHD, "Total", "L")->SetTextSizePixels(24);
  leg->AddEntry(hIn, "V^{0} reconstruction", "L")->SetTextSizePixels(24);
  leg->AddEntry(hJE, "Jet #it{p}_{T} scale", "L")->SetTextSizePixels(24);
  leg->AddEntry(hUE, "UE subtraction", "L")->SetTextSizePixels(24);
  leg->Draw();

  tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.16, 0.92, "ALICE pp #sqrt{#it{s}_{NN}}=7 TeV");
  tex->DrawLatex(0.16, 0.84, "Systematic uncertainty of K_{s}^{0}");
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
