void PlotL2K_VJ_Comp(const UInt_t kAct = 3,
                     const UInt_t kPtj = 0, // 0: pTjet > 10 GeV/c; 1: pTjet > 20 GeV/c
                     const UInt_t kPtV = 0, // 0: 2.2 < pTV0 < 3.7 GeV/c; 1: 0.6 < pTV0 < 1.8 GeV/c; 2: 4.2 < pTV0 < 12 GeV/c
                     const UInt_t kOut = 0)
{
  const TString sWorkDir = gSystem->WorkingDirectory();
  const TString sPckgDir = gSystem->DirName(sWorkDir.Data());
  const TString sUtilDir = Form("%s/include", sPckgDir.Data());
//=============================================================================

  gROOT->LoadMacro(Form("%s/TUtilsOpHisto.h",sUtilDir.Data()));
  gROOT->LoadMacro(Form("%s/TUtilsResults.h",sUtilDir.Data()));
  gROOT->LoadMacro(Form("%s/TUtilsPlotStd.h",sUtilDir.Data()));
  gROOT->LoadMacro(Form("%s/TUtilsAliFigs.h",sUtilDir.Data())); SetStyle();
//=============================================================================

  TString sPtvN = "", sPtvL = "";
  if (kPtV==0) { sPtvN = "PtV0_2d2_3d7"; sPtvL = "2.2<#it{p}_{T,V^{0}}<3.7 GeV/#it{c}"; }
  if (kPtV==1) { sPtvN = "PtV0_0d6_1d8"; sPtvL = "0.6<#it{p}_{T,V^{0}}<1.8 GeV/#it{c}"; }
  if (kPtV==2) { sPtvN = "PtV0_4d2_12d"; sPtvL = "4.2<#it{p}_{T,V^{0}}<12 GeV/#it{c}";  }

  const TString sList = Form("list_%s_%s_%s", sActN[kAct].Data(), sPtjN[kPtj].Data(), sPtvN.Data());

  TFile *file = TFile::Open("data/AnaL2K_VJ_Comp.root", "READ");
  TList *list = (TList*)file->Get(sList.Data());
  file->Close();

  TH1D *hK02Stat = (TH1D*)list->FindObject("hKshort_JR02_Stat");
  TH1D *hK02Syst = (TH1D*)list->FindObject("hKshort_JR02_Syst");

  TH1D *hK03Stat = (TH1D*)list->FindObject("hKshort_JR03_Stat");
  TH1D *hK03Syst = (TH1D*)list->FindObject("hKshort_JR03_Syst");

  TH1D *hK04Stat = (TH1D*)list->FindObject("hKshort_JR04_Stat");
  TH1D *hK04Syst = (TH1D*)list->FindObject("hKshort_JR04_Syst");


  TH1D *hL02Stat = (TH1D*)list->FindObject("hLambda_JR02_Stat");
  TH1D *hL02Syst = (TH1D*)list->FindObject("hLambda_JR02_Syst");

  TH1D *hL03Stat = (TH1D*)list->FindObject("hLambda_JR03_Stat");
  TH1D *hL03Syst = (TH1D*)list->FindObject("hLambda_JR03_Syst");

  TH1D *hL04Stat = (TH1D*)list->FindObject("hLambda_JR04_Stat");
  TH1D *hL04Syst = (TH1D*)list->FindObject("hLambda_JR04_Syst");


  TH1D *hA02Stat = (TH1D*)list->FindObject("hAntiLa_JR02_Stat");
  TH1D *hA02Syst = (TH1D*)list->FindObject("hAntiLa_JR02_Syst");

  TH1D *hA03Stat = (TH1D*)list->FindObject("hAntiLa_JR03_Stat");
  TH1D *hA03Syst = (TH1D*)list->FindObject("hAntiLa_JR03_Syst");

  TH1D *hA04Stat = (TH1D*)list->FindObject("hAntiLa_JR04_Stat");
  TH1D *hA04Syst = (TH1D*)list->FindObject("hAntiLa_JR04_Syst");

  hL02Stat->Add(hA02Stat); hL02Syst->Add(hA02Syst);
  hL03Stat->Add(hA02Stat); hL03Syst->Add(hA03Syst);
  hL04Stat->Add(hA02Stat); hL04Syst->Add(hA04Syst);


  TH1D *hR02Stat = (TH1D*)list->FindObject("hRatioV_JR02_Stat");
  TH1D *hR02Syst = (TH1D*)list->FindObject("hRatioV_JR02_Syst");

  TH1D *hR03Stat = (TH1D*)list->FindObject("hRatioV_JR03_Stat");
  TH1D *hR03Syst = (TH1D*)list->FindObject("hRatioV_JR03_Syst");

  TH1D *hR04Stat = (TH1D*)list->FindObject("hRatioV_JR04_Stat");
  TH1D *hR04Syst = (TH1D*)list->FindObject("hRatioV_JR04_Syst");
//=============================================================================

  TGraphErrors *gK02Stat = ConvHistogramToGraphErrorL(hK02Stat, 0x0, hK02Stat->GetNbinsX(), kTRUE);
  TGraphErrors *gK03Stat = ConvHistogramToGraphErrors(hK03Stat, 0x0, hK03Stat->GetNbinsX(), kTRUE);
  TGraphErrors *gK04Stat = ConvHistogramToGraphErrorR(hK04Stat, 0x0, hK04Stat->GetNbinsX(), kTRUE);

  TGraphErrors *gK02Syst = ConvHistogramToGraphErrorL(hK02Syst, 0x0, hK02Syst->GetNbinsX(), kTRUE);
  TGraphErrors *gK03Syst = ConvHistogramToGraphErrors(hK03Syst, 0x0, hK03Syst->GetNbinsX(), kTRUE);
  TGraphErrors *gK04Syst = ConvHistogramToGraphErrorR(hK04Syst, 0x0, hK04Syst->GetNbinsX(), kTRUE);


  TGraphErrors *gL02Stat = ConvHistogramToGraphErrorL(hL02Stat, 0x0, hL02Stat->GetNbinsX(), kTRUE);
  TGraphErrors *gL03Stat = ConvHistogramToGraphErrors(hL03Stat, 0x0, hL03Stat->GetNbinsX(), kTRUE);
  TGraphErrors *gL04Stat = ConvHistogramToGraphErrorR(hL04Stat, 0x0, hL04Stat->GetNbinsX(), kTRUE);

  TGraphErrors *gL02Syst = ConvHistogramToGraphErrorL(hL02Syst, 0x0, hL02Syst->GetNbinsX(), kTRUE);
  TGraphErrors *gL03Syst = ConvHistogramToGraphErrors(hL03Syst, 0x0, hL03Syst->GetNbinsX(), kTRUE);
  TGraphErrors *gL04Syst = ConvHistogramToGraphErrorR(hL04Syst, 0x0, hL04Syst->GetNbinsX(), kTRUE);


  TGraphErrors *gA02Stat = ConvHistogramToGraphErrorL(hA02Stat, 0x0, hA02Stat->GetNbinsX(), kTRUE);
  TGraphErrors *gA03Stat = ConvHistogramToGraphErrors(hA03Stat, 0x0, hA03Stat->GetNbinsX(), kTRUE);
  TGraphErrors *gA04Stat = ConvHistogramToGraphErrorR(hA04Stat, 0x0, hA04Stat->GetNbinsX(), kTRUE);

  TGraphErrors *gA02Syst = ConvHistogramToGraphErrorL(hA02Syst, 0x0, hA02Syst->GetNbinsX(), kTRUE);
  TGraphErrors *gA03Syst = ConvHistogramToGraphErrors(hA03Syst, 0x0, hA03Syst->GetNbinsX(), kTRUE);
  TGraphErrors *gA04Syst = ConvHistogramToGraphErrorR(hA04Syst, 0x0, hA04Syst->GetNbinsX(), kTRUE);


  TGraphErrors *gR02Stat = ConvHistogramToGraphErrorL(hR02Stat, 0x0, hR02Stat->GetNbinsX(), kTRUE);
  TGraphErrors *gR03Stat = ConvHistogramToGraphErrors(hR03Stat, 0x0, hR03Stat->GetNbinsX(), kTRUE);
  TGraphErrors *gR04Stat = ConvHistogramToGraphErrorR(hR04Stat, 0x0, hR04Stat->GetNbinsX(), kTRUE);

  TGraphErrors *gR02Syst = ConvHistogramToGraphErrorL(hR02Syst, 0x0, hR02Syst->GetNbinsX(), kTRUE);
  TGraphErrors *gR03Syst = ConvHistogramToGraphErrors(hR03Syst, 0x0, hR03Syst->GetNbinsX(), kTRUE);
  TGraphErrors *gR04Syst = ConvHistogramToGraphErrorR(hR04Syst, 0x0, hR04Syst->GetNbinsX(), kTRUE);
//=============================================================================

  TH1F    *frm = 0;
  TCanvas *can = 0;
  TLegend *leg = 0;
  TLatex  *tex = 0;
  TLine  *line = 0;

  const Float_t dflx =  0.0, dfux = 1.5;
  const Float_t dfly =  0.0, dfuy = 0.22;

  const Float_t dlsx = 0.05, dlsy = 0.05;
  const Float_t dtsx = 0.06, dtsy = 0.06;
  const Float_t dtox = 1.10, dtoy = 1.00;

  const TString stnx = "#it{R}(V^{0},jet)";
  const TString stny = "d#rho/d#it{R}";

  TH1D *hStatE = new TH1D("hStatE", "", 100, dflx, dfux);
  hStatE->SetLineWidth(2);
  hStatE->SetLineColor(1);
  hStatE->SetMarkerStyle(wmk[0]);
  hStatE->SetMarkerColor(1);

  TH1D *hSystE = new TH1D("hSystE", "", 100, dflx, dfux);
  hSystE->SetLineWidth(2);
  hSystE->SetLineColor(1);
  hSystE->SetFillStyle(0);
  hSystE->SetFillColor(1);
//=============================================================================

  const TString sCanN = Form("VJ_Comp_%s_%s_%s", sActN[kAct].Data(), sPtjN[kPtj].Data(), sPtvN.Data());
//=============================================================================

  can = MakeCanvas(Form("Kshort_%s", sCanN.Data()));
  frm = can->DrawFrame(dflx, dfly, dfux, 0.2);
  SetupFrame(frm, dlsx, dlsy, dtsx, dtsy, dtox, dtoy, stnx, stny);

  DrawGraph(gK02Syst, wcl[3], "E2"); DrawGraph(gK02Stat, wcl[3], wmk[0], "P");
  DrawGraph(gK04Syst, wcl[2], "E2"); DrawGraph(gK04Stat, wcl[2], wmk[0], "P");
  DrawGraph(gK03Syst, wcl[1], "E2"); DrawHisto(hK03Stat, wcl[1], wmk[0], "SAME");

  leg = new TLegend(0.70, 0.48, 0.96, 0.70); SetupLegend(leg);
  leg->AddEntry(gK02Stat, sRjeL[kJC02], "LP")->SetTextSizePixels(24);
  leg->AddEntry(hK03Stat, sRjeL[kJC03], "LP")->SetTextSizePixels(24);
  leg->AddEntry(gK04Stat, sRjeL[kJC04], "LP")->SetTextSizePixels(24);
  leg->Draw();

  leg = new TLegend(0.30, 0.54, 0.52, 0.68); SetupLegend(leg);
  leg->AddEntry(hStatE, sErrL[kStat], "LEP")->SetTextSizePixels(24);
  leg->AddEntry(hSystE, sErrL[kSyst], "F")->SetTextSizePixels(24);
  leg->Draw();

  tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.30, 0.92, Form("%s, ALICE p-Pb #sqrt{s_{NN}}=5.02 TeV", sVarL[kKshort].Data()));
  tex->DrawLatex(0.24, 0.84, Form("%s, |#eta_{jet}|<0.35, anti-#it{k}_{T}", sPtjL[kPtj].Data()));
  tex->DrawLatex(0.24, 0.76, Form("%s, |#eta_{V^{0}}|<0.75", sPtvL.Data()));
  CanvasEnd(can); if (kOut==1) can->Print(Form("%s.pdf",can->GetName()));
//=============================================================================

  can = MakeCanvas(Form("Lambda_%s", sCanN.Data()));
  frm = can->DrawFrame(dflx, dfly, dfux, 0.2);
  SetupFrame(frm, dlsx, dlsy, dtsx, dtsy, dtox, dtoy, stnx, stny);

  DrawGraph(gL02Syst, wcl[3], "E2"); DrawGraph(gL02Stat, wcl[3], wmk[0], "P");
  DrawGraph(gL04Syst, wcl[2], "E2"); DrawGraph(gL04Stat, wcl[2], wmk[0], "P");
  DrawGraph(gL03Syst, wcl[1], "E2"); DrawHisto(hL03Stat, wcl[1], wmk[0], "SAME");

  leg = new TLegend(0.70, 0.72, 0.96, 0.96); SetupLegend(leg);
  leg->AddEntry(gL02Stat, sRjeL[kJC02], "LP")->SetTextSizePixels(24);
  leg->AddEntry(hL03Stat, sRjeL[kJC03], "LP")->SetTextSizePixels(24);
  leg->AddEntry(gL04Stat, sRjeL[kJC04], "LP")->SetTextSizePixels(24);
  leg->Draw();

  leg = new TLegend(0.70, 0.54, 0.96, 0.68); SetupLegend(leg);
  leg->AddEntry(hStatE, sErrL[kStat], "LEP")->SetTextSizePixels(24);
  leg->AddEntry(hSystE, sErrL[kSyst], "F")->SetTextSizePixels(24);
  leg->Draw();

  tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.16, 0.92, Form("#Lambda+#bar{#Lambda}, ALICE p-Pb #sqrt{s_{NN}}=5.02 TeV", sVarL[kLambda].Data()));
  tex->DrawLatex(0.16, 0.84, Form("%s, |#eta_{jet}|<0.35, anti-#it{k}_{T}", sPtjL[kPtj].Data()));
  tex->DrawLatex(0.16, 0.76, Form("%s, |#eta_{V^{0}}|<0.75", sPtvL.Data()));
  CanvasEnd(can); if (kOut==1) can->Print(Form("%s.pdf",can->GetName()));
//=============================================================================

  can = MakeCanvas(Form("RatioV_%s", sCanN.Data()));
  frm = can->DrawFrame(dflx, dfly, dfux, 1.2);
  SetupFrame(frm, dlsx, dlsy, dtsx, dtsy, dtox, dtoy, stnx, sVarL[kRatioV]);

  DrawGraph(gR02Syst, wcl[3], "E2"); DrawGraph(gR02Stat, wcl[3], wmk[0], "P");
  DrawGraph(gR04Syst, wcl[2], "E2"); DrawGraph(gR04Stat, wcl[2], wmk[0], "P");
  DrawGraph(gR03Syst, wcl[1], "E2"); DrawHisto(hR03Stat, wcl[1], wmk[0], "SAME");

  leg = new TLegend(0.70, 0.72, 0.96, 0.96); SetupLegend(leg);
  leg->AddEntry(gR02Stat, sRjeL[kJC02], "LP")->SetTextSizePixels(24);
  leg->AddEntry(hR03Stat, sRjeL[kJC03], "LP")->SetTextSizePixels(24);
  leg->AddEntry(gR04Stat, sRjeL[kJC04], "LP")->SetTextSizePixels(24);
  leg->Draw();

  leg = new TLegend(0.70, 0.20, 0.96, 0.34); SetupLegend(leg);
  leg->AddEntry(hStatE, sErrL[kStat], "LEP")->SetTextSizePixels(24);
  leg->AddEntry(hSystE, sErrL[kSyst], "F")->SetTextSizePixels(24);
  leg->Draw();

  tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.16, 0.90, Form("ALICE p-Pb #sqrt{s_{NN}}=5.02 TeV"));
  tex->DrawLatex(0.16, 0.82, Form("%s, |#eta_{jet}|<0.35, anti-#it{k}_{T}", sPtjL[kPtj].Data()));
  tex->DrawLatex(0.16, 0.74, Form("%s, |#eta_{V^{0}}|<0.75", sPtvL.Data()));
  CanvasEnd(can); if (kOut==1) can->Print(Form("%s.pdf",can->GetName()));
//=============================================================================

  return;
}
