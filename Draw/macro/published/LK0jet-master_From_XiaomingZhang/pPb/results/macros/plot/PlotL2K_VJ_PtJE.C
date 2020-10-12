void PlotL2K_VJ_PtJE(const UInt_t kAct = 2,
                     const UInt_t kPtv = 0)
{
  const TString sWorkDir = gSystem->WorkingDirectory();
  const TString sPckgDir = gSystem->DirName(sWorkDir.Data());

  const TString sUtilDir = Form("%s/util", sPckgDir.Data());
  const TString sDataDir = Form("%s/data", sPckgDir.Data());

  gROOT->LoadMacro(Form("%s/TUtilsOpHisto.h",sUtilDir.Data()));
  gROOT->LoadMacro(Form("%s/TUtilsToolV0s.h",sUtilDir.Data()));
  gROOT->LoadMacro(Form("%s/TUtilsResults.h",sUtilDir.Data()));
  gROOT->LoadMacro(Form("%s/TUtilsPlotStd.h",sUtilDir.Data()));
  gROOT->LoadMacro(Form("%s/TUtilsAliFigs.h",sUtilDir.Data())); SetStyle();
//=============================================================================

  const TString sPtvN[] = { "PtV0_2d2_3d7", "PtV0_0d6_1d8", "PtV0_4d2_12d" };
  const TString sPtvL[] = { "2.2<#it{p}_{T,V^{0}}<3.7 GeV/#it{c}",
                            "0.6<#it{p}_{T,V^{0}}<1.8 GeV/#it{c}",
                            "4.2<#it{p}_{T,V^{0}}<12 GeV/#it{c}" };

  TFile *file = TFile::Open("data/AnaL2K_VJ_Comp.root", "READ");
  TList *list10 = (TList*)file->Get(Form("list_%s_PtJ10_%s", sActN[kAct].Data(), sPtvN[kPtv].Data()));
  TList *list20 = (TList*)file->Get(Form("list_%s_PtJ20_%s", sActN[kAct].Data(), sPtvN[kPtv].Data()));
  file->Close();
//=============================================================================

  TH1D *hR02Stat10 = (TH1D*)list10->FindObject("hRatioV_JR02_Stat");  hR02Stat10->SetName("hR02Stat10");
  TH1D *hR02Syst10 = (TH1D*)list10->FindObject("hRatioV_JR02_Syst");  hR02Syst10->SetName("hR02Syst10");

  TH1D *hR03Stat10 = (TH1D*)list10->FindObject("hRatioV_JR03_Stat");  hR03Stat10->SetName("hR03Stat10");
  TH1D *hR03Syst10 = (TH1D*)list10->FindObject("hRatioV_JR03_Syst");  hR03Syst10->SetName("hR03Syst10");

  TH1D *hR04Stat10 = (TH1D*)list10->FindObject("hRatioV_JR04_Stat");  hR04Stat10->SetName("hR04Stat10");
  TH1D *hR04Syst10 = (TH1D*)list10->FindObject("hRatioV_JR04_Syst");  hR04Syst10->SetName("hR04Syst10");

  TH1D *hL2Kstat10 = CalcMeanVal(hR02Stat10, hR03Stat10, hR04Stat10); hL2Kstat10->SetName("hL2Kstat10");
  TH1D *hL2Ksyst10 = CalcMeanVal(hR02Syst10, hR03Syst10, hR04Syst10); hL2Ksyst10->SetName("hL2Ksyst10");


  TH1D *hR02Stat20 = (TH1D*)list20->FindObject("hRatioV_JR02_Stat");  hR02Stat20->SetName("hR02Stat20");
  TH1D *hR02Syst20 = (TH1D*)list20->FindObject("hRatioV_JR02_Syst");  hR02Syst20->SetName("hR02Syst20");

  TH1D *hR03Stat20 = (TH1D*)list20->FindObject("hRatioV_JR03_Stat");  hR03Stat20->SetName("hR03Stat20");
  TH1D *hR03Syst20 = (TH1D*)list20->FindObject("hRatioV_JR03_Syst");  hR03Syst20->SetName("hR03Syst20");

  TH1D *hR04Stat20 = (TH1D*)list20->FindObject("hRatioV_JR04_Stat");  hR04Stat20->SetName("hR04Stat20");
  TH1D *hR04Syst20 = (TH1D*)list20->FindObject("hRatioV_JR04_Syst");  hR04Syst20->SetName("hR04Syst20");

  TH1D *hL2Kstat20 = CalcMeanVal(hR02Stat20, hR03Stat20, hR04Stat20); hL2Kstat20->SetName("hL2Kstat20");
  TH1D *hL2Ksyst20 = CalcMeanVal(hR02Syst20, hR03Syst20, hR04Syst20); hL2Ksyst20->SetName("hL2Ksyst20");
//=============================================================================

  TGraphErrors *gL2Kstat10 = ConvHistogramToGraphErrors(hL2Kstat10, 0x0, hL2Kstat10->GetNbinsX(), kTRUE);
  TGraphErrors *gL2Ksyst10 = ConvHistogramToGraphErrors(hL2Ksyst10, 0x0, hL2Ksyst10->GetNbinsX(), kTRUE);

  TGraphErrors *gL2Kstat20 = ConvHistogramToGraphErrorL(hL2Kstat20, 0x0, hL2Kstat20->GetNbinsX(), kTRUE);
  TGraphErrors *gL2Ksyst20 = ConvHistogramToGraphErrorL(hL2Ksyst20, 0x0, hL2Ksyst20->GetNbinsX(), kTRUE);
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

  const TString sCanN = Form("VJ_PtJE_%s_%s", sActN[kAct].Data(), sPtvN[kPtv].Data());
//=============================================================================

  can = MakeCanvas(Form("RatioV_%s", sCanN.Data()));
  can->SetGridx(); can->SetGridy();
  frm = can->DrawFrame(dflx, dfly, dfux, 1.2);
  SetupFrame(frm, dlsx, dlsy, dtsx, dtsy, dtox, dtoy, stnx, sVarL[kRatioV]);

  DrawGraph(gL2Ksyst20, wcl[5], "E2"); DrawGraph(gL2Kstat20, wcl[5], wmk[0], "P");
  DrawGraph(gL2Ksyst10, wcl[3], "E2"); DrawHisto(hL2Kstat10, wcl[3], wmk[0], "SAME");

  leg = new TLegend(0.56, 0.70, 0.96, 0.90); SetupLegend(leg);
  leg->AddEntry(hL2Kstat10, sPtjL[kPtj10], "LP")->SetTextSizePixels(24);
  leg->AddEntry(gL2Kstat20, sPtjL[kPtj20], "LP")->SetTextSizePixels(24);
  leg->Draw();

  leg = new TLegend(0.70, 0.16, 0.96, 0.30); SetupLegend(leg);
  leg->AddEntry(hStatE, sErrL[kStat], "LEP")->SetTextSizePixels(24);
  leg->AddEntry(hSystE, sErrL[kSyst], "F")->SetTextSizePixels(24);
  leg->Draw();

  tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.16, 0.90, Form("p-Pb #sqrt{s_{NN}}=5.02 TeV, %s", sActL[kAct].Data()));
  tex->DrawLatex(0.16, 0.82, Form("anti-#it{k}_{T}, |#eta_{jet}|<0.35, |#eta_{V^{0}}|<0.75"));
  tex->DrawLatex(0.16, 0.74, Form("%s", sPtvL[kPtv].Data()));
  tex->DrawLatex(0.16, 0.20, "mean #it{R}=0.2, 0.3, 0.4");
  CanvasEnd(can);
//=============================================================================

//can->Print(Form("c%s.pdf",sCanN.Data()));
  return;
}
