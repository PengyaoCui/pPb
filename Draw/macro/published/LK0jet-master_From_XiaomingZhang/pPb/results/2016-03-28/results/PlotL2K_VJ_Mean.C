void PlotL2K_VJ_Mean(const UInt_t kAct = 3,
                     const UInt_t kPtj = 0,  // 0: pTjet > 10 GeV/c; 1: pTjet > 20 GeV/c
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

  enum { kPtvM, kPtvL, kPtvR };
  const TString sPtvN[] = { "PtV0_2d2_3d7", "PtV0_0d6_1d8", "PtV0_4d2_12d" };
  const TString sPtvL[] = { "2.2<#it{p}_{T,V^{0}}<3.7 GeV/#it{c}",
                            "0.6<#it{p}_{T,V^{0}}<1.8 GeV/#it{c}",
                            "4.2<#it{p}_{T,V^{0}}<12 GeV/#it{c}" };

  const TString sList = Form("list_%s_%s", sActN[kAct].Data(), sPtjN[kPtj].Data());

  TFile *file = TFile::Open("data/AnaL2K_VJ_Comp.root", "READ");
  TList *listL = (TList*)file->Get(Form("%s_%s", sList.Data(), sPtvN[kPtvL].Data()));
  TList *listM = (TList*)file->Get(Form("%s_%s", sList.Data(), sPtvN[kPtvM].Data()));
  TList *listR = (TList*)file->Get(Form("%s_%s", sList.Data(), sPtvN[kPtvR].Data()));
  file->Close();
//=============================================================================

  TH1D *hR02StatM = (TH1D*)listM->FindObject("hRatioV_JR02_Stat"); hR02StatM->SetName("hR02StatM");
  TH1D *hR02SystM = (TH1D*)listM->FindObject("hRatioV_JR02_Syst"); hR02SystM->SetName("hR02SystM");

  TH1D *hR03StatM = (TH1D*)listM->FindObject("hRatioV_JR03_Stat"); hR03StatM->SetName("hR03StatM");
  TH1D *hR03SystM = (TH1D*)listM->FindObject("hRatioV_JR03_Syst"); hR03SystM->SetName("hR03SystM");

  TH1D *hR04StatM = (TH1D*)listM->FindObject("hRatioV_JR04_Stat"); hR04StatM->SetName("hR04StatM");
  TH1D *hR04SystM = (TH1D*)listM->FindObject("hRatioV_JR04_Syst"); hR04SystM->SetName("hR04SystM");

  TH1D *hL2KstatM = CalcMeanVal(hR02StatM, hR03StatM, hR04StatM);  hL2KstatM->SetName("hL2KstatM");
  TH1D *hL2KsystM = CalcMeanVal(hR02SystM, hR03SystM, hR04SystM);  hL2KsystM->SetName("hL2KsystM");


  TH1D *hR02StatL = (TH1D*)listL->FindObject("hRatioV_JR02_Stat"); hR02StatL->SetName("hR02StatL");
  TH1D *hR02SystL = (TH1D*)listL->FindObject("hRatioV_JR02_Syst"); hR02SystL->SetName("hR02SystL");

  TH1D *hR03StatL = (TH1D*)listL->FindObject("hRatioV_JR03_Stat"); hR03StatL->SetName("hR03StatL");
  TH1D *hR03SystL = (TH1D*)listL->FindObject("hRatioV_JR03_Syst"); hR03SystL->SetName("hR03SystL");

  TH1D *hR04StatL = (TH1D*)listL->FindObject("hRatioV_JR04_Stat"); hR04StatL->SetName("hR04StatL");
  TH1D *hR04SystL = (TH1D*)listL->FindObject("hRatioV_JR04_Syst"); hR04SystL->SetName("hR04SystL");

  TH1D *hL2KstatL = CalcMeanVal(hR02StatL, hR03StatL, hR04StatL);  hL2KstatL->SetName("hL2KstatL");
  TH1D *hL2KsystL = CalcMeanVal(hR02SystL, hR03SystL, hR04SystL);  hL2KsystL->SetName("hL2KsystL");


  TH1D *hR02StatR = (TH1D*)listR->FindObject("hRatioV_JR02_Stat"); hR02StatR->SetName("hR02StatR");
  TH1D *hR02SystR = (TH1D*)listR->FindObject("hRatioV_JR02_Syst"); hR02SystR->SetName("hR02SystR");

  TH1D *hR03StatR = (TH1D*)listR->FindObject("hRatioV_JR03_Stat"); hR03StatR->SetName("hR03StatR");
  TH1D *hR03SystR = (TH1D*)listR->FindObject("hRatioV_JR03_Syst"); hR03SystR->SetName("hR03SystR");

  TH1D *hR04StatR = (TH1D*)listR->FindObject("hRatioV_JR04_Stat"); hR04StatR->SetName("hR04StatR");
  TH1D *hR04SystR = (TH1D*)listR->FindObject("hRatioV_JR04_Syst"); hR04SystR->SetName("hR04SystR");

  TH1D *hL2KstatR = CalcMeanVal(hR02StatR, hR03StatR, hR04StatR);  hL2KstatR->SetName("hL2KstatR");
  TH1D *hL2KsystR = CalcMeanVal(hR02SystR, hR03SystR, hR04SystR);  hL2KsystR->SetName("hL2KsystR");
//============================================================================= 
  TGraphErrors *gL2KstatM = ConvHistogramToGraphErrors(hL2KstatM, 0x0, hL2KstatM->GetNbinsX(), kTRUE);
  TGraphErrors *gL2KsystM = ConvHistogramToGraphErrors(hL2KsystM, 0x0, hL2KsystM->GetNbinsX(), kTRUE);

  TGraphErrors *gL2KstatL = ConvHistogramToGraphErrorL(hL2KstatL, 0x0, hL2KstatL->GetNbinsX(), kTRUE);
  TGraphErrors *gL2KsystL = ConvHistogramToGraphErrorL(hL2KsystL, 0x0, hL2KsystL->GetNbinsX(), kTRUE);

  TGraphErrors *gL2KstatR = ConvHistogramToGraphErrorR(hL2KstatR, 0x0, hL2KstatR->GetNbinsX(), kTRUE);
  TGraphErrors *gL2KsystR = ConvHistogramToGraphErrorR(hL2KsystR, 0x0, hL2KsystR->GetNbinsX(), kTRUE);
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

  const TString sCanN = Form("VJ_Mean_%s_%s", sActN[kAct].Data(), sPtjN[kPtj].Data());
//=============================================================================

  can = MakeCanvas(Form("RatioV_%s", sCanN.Data()));
  frm = can->DrawFrame(dflx, dfly, dfux, 1.2);
  SetupFrame(frm, dlsx, dlsy, dtsx, dtsy, dtox, dtoy, stnx, sVarL[kRatioV]);

  DrawGraph(gL2KsystR, wcl[2], "E2"); DrawGraph(gL2KstatR, wcl[2], wmk[0], "P");
  DrawGraph(gL2KsystL, wcl[3], "E2"); DrawGraph(gL2KstatL, wcl[3], wmk[0], "P");
  DrawGraph(gL2KsystM, wcl[1], "E2"); DrawHisto(hL2KstatM, wcl[1], wmk[0], "SAME");

  leg = new TLegend(0.56, 0.66, 0.96, 0.90); SetupLegend(leg);
  leg->AddEntry(gL2KstatL, sPtvL[kPtvL], "LP")->SetTextSizePixels(24);
  leg->AddEntry(hL2KstatM, sPtvL[kPtvM], "LP")->SetTextSizePixels(24);
  leg->AddEntry(gL2KstatR, sPtvL[kPtvR], "LP")->SetTextSizePixels(24);
  leg->Draw();

  leg = new TLegend(0.70, 0.16, 0.96, 0.30); SetupLegend(leg);
  leg->AddEntry(hStatE, sErrL[kStat], "LEP")->SetTextSizePixels(24);
  leg->AddEntry(hSystE, sErrL[kSyst], "F")->SetTextSizePixels(24);
  leg->Draw();

  tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.16, 0.92, Form("p-Pb #sqrt{s_{NN}}=5.02 TeV"));
  tex->DrawLatex(0.16, 0.84, Form("%s, anti-#it{k}_{T}", sPtjL[kPtj].Data()));
  tex->DrawLatex(0.16, 0.76, Form("|#eta_{jet}|<0.35, #eta_{V^{0}}|<0.75"));
  tex->DrawLatex(0.16, 0.20, "mean #it{R}=0.2, 0.3, 0.4");
  CanvasEnd(can); if (kOut==1) can->Print(Form("%s.pdf",can->GetName()));
//=============================================================================

  return;
}
