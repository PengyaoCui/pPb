enum { kJR02, kJR03, kJR04 };
const TString sRjeN[] = { "JR02", "JR03", "JR04" };
const TString sRjeL[] = { "#it{R}=0.2", "#it{R}=0.3", "#it{R}=0.4" };
//=============================================================================

enum { kJC02, kJC03, kJC04, kJC06, kJC08, kJC11, kJC15 };
const TString sCjeN[] = { "JC02", "JC03", "JC04", "JC06", "JC08", "JC11", "JC15" };
const TString sCjeL[] = { "#it{R}(V^{0},jet)<0.2", "#it{R}(V^{0},jet)<0.3", "#it{R}(V^{0},jet)<0.4",
                          "#it{R}(V^{0},jet)<0.6", "#it{R}(V^{0},jet)<0.8", "#it{R}(V^{0},jet)<1.1",
                          "#it{R}(V^{0},jet)<1.5" };
//=============================================================================

enum { kV0AC, kV0AS, kV0AP, kZNAC, kZANS, kZANP };
const TString sActN[] = { "V0A_000_010", "V0A_010_040", "V0A_040_100",
                          "ZNA_000_010", "ZNA_010_040", "ZNA_040_100" };
const TString sActL[] = { "V0A 0-10%", "V0A 10-40%", "V0A 40-100%",
                          "ZNA 0-10%", "ZNA 10-40%", "ZNA 40-100%" };
//=============================================================================

enum { kPtj10, kPtj20 };
const TString sPtjN[] = { "PtJ10", "PtJ20" };
const TString sPtjL[] = { "#it{p}_{T,jet}^{ch}>10 GeV/#it{c}", "#it{p}_{T,jet}^{ch}>20 GeV/#it{c}" };
//=============================================================================

enum { kBin21, kBin08, kBin07, kBin05 };
const TString sBinN[] = { "Bin21", "Bin08", "Bin07", "Bin05" };
//=============================================================================

enum { kNJ, kPC, kOC04, kOC06, kOC08 };
const TString sBkgN[] = { "NJ", "PCM", "OC04", "OC06", "OC08" };
const TString sBkgL[] = { "events w/o #it{p}_{T,jet}^{ch}>5 GeV/#it{c}", "perp. cone",
                          "#it{R}(V^{0},jet)>0.4", "#it{R}(V^{0},jet)>0.6", "#it{R}(V^{0},jet)>0.8" };
//=============================================================================

enum { kKshort, kLambda, kAntiLa, kRatioV };
const TString sVarN[] = { "Kshort", "Lambda", "AntiLa", "RatioV" };
const TString sVarL[] = { "K_{S}^{0}", "#Lambda", "#bar{#Lambda}",
                          "(#Lambda+#bar{#Lambda})/2K_{S}^{0}" };
//=============================================================================

enum { kStat, kSyst, kTopo, kCtau, kCompM, kPID, kTPC, kInvM, kUE, kPtJ };
const TString sErrN[] = { "Stat", "Syst", "Topo", "Ctau", "CompM", "PIDinTPC", "RowsTPC", "SigmaInvM", "UE", "PtJ" };
const TString sErrL[] = { "stat error", "syst error",
                          "topological", "proper lifetime", "competing mass", "TPC PID", "TPC rows", "signal extraction",
                          "underlying", "jet #it{p}_{T}" };
//=============================================================================

enum { kHD, kJC, kUE };
const TString sType[] = { "HD", "JC", "UE" };
//=============================================================================
//=============================================================================

//_____________________________________________________________________________
TH1D *CalcMeanVal(const TH1D *h0, const TH1D *h1=0x0, const TH1D *h2=0x0)
{
  Double_t dWgt = 0.;
  TString s0="", s1="", s2="";
  if (h0) { s0 = h0->GetName(); dWgt += 1.; }
  if (h1) { s1 = h1->GetName(); dWgt += 1.; }
  if (h2) { s2 = h2->GetName(); dWgt += 1.; }

  TH1D *hMean = (TH1D*)h0->Clone(Form("hMean_%s_%s_%s",s0.Data(),s1.Data(),s2.Data()));
  hMean->Reset();

  for (Int_t k=1; k<=h0->GetNbinsX(); k++) {
    Double_t dV0=0., dV1=0., dV2=0.;
    Double_t dE0=0., dE1=0., dE2=0.;

    if (h0) { dV0 = h0->GetBinContent(k); dE0 = h0->GetBinError(k); }
    if (h1) { dV1 = h1->GetBinContent(k); dE1 = h1->GetBinError(k); }
    if (h2) { dV2 = h2->GetBinContent(k); dE2 = h2->GetBinError(k); }

    Double_t dMeanV = (dV0 + dV1 + dV2) / dWgt;
    Double_t dMeanE = TMath::Sqrt(dE0*dE0 + dE1*dE1 + dE2*dE2) / dWgt;

    hMean->SetBinContent(k, dMeanV);
    hMean->SetBinError(k, dMeanE);
  }

  return hMean;
}

//_____________________________________________________________________________
TH1D *CalcMeanErr(const TH1D *hV0,     const TH1D *hE0,
                  const TH1D *hV1=0x0, const TH1D *hE1=0x0,
                  const TH1D *hV2=0x0, const TH1D *hE2=0x0)
{
  TString s0="", s1="", s2="";
  if (hV0 && hE0) s0 = Form("%s_%s",hV0->GetName(),hE0->GetName());
  if (hV1 && hE1) s1 = Form("%s_%s",hV1->GetName(),hE1->GetName());
  if (hV2 && hE2) s2 = Form("%s_%s",hV2->GetName(),hE2->GetName());

  TH1D *hMean = (TH1D*)hV0->Clone(Form("hMean_%s_%s_%s",s0.Data(),s1.Data(),s2.Data()));
  hMean->Reset();

  for (Int_t k=1; k<=hV0->GetNbinsX(); k++) {
    Double_t dV0=0., dV1=0., dV2=0.;
    Double_t dE0=0., dE1=0., dE2=0.;

    if (hV0 && hE0) { dV0 = hV0->GetBinContent(k); dE0 = dV0 * hE0->GetBinContent(k); }
    if (hV1 && hE1) { dV1 = hV1->GetBinContent(k); dE1 = dV1 * hE1->GetBinContent(k); }
    if (hV2 && hE2) { dV2 = hV2->GetBinContent(k); dE2 = dV2 * hE2->GetBinContent(k); }

    Double_t dMeanV = (dV0 + dV1 + dV2);
    Double_t dMeanE = TMath::Sqrt(dE0*dE0 + dE1*dE1 + dE2*dE2) / dMeanV;

    hMean->SetBinContent(k, dMeanE);
  }

  return hMean;
}
//=============================================================================
//=============================================================================

//_____________________________________________________________________________
TH1D *GetResultStatMB(const UInt_t  kAct,
                      const UInt_t  kVar,
                      const TString sPath)
{
  const TString sFile = "AnalysisOutputs_CombMB.root";
  const TString sList = Form("list_%s",  sActN[kAct].Data());
  const TString sHist = Form("h%s_Stat", sVarN[kVar].Data());

  cout << "TUtilsResults.h::GetResultStatMB::"
       << sFile.Data() << "::" << sList.Data() << "::" << sHist.Data() << endl;
//=============================================================================

  TFile *file = TFile::Open(Form("%s/%s",sPath.Data(),sFile.Data()), "READ");
  TList *list = (TList*)file->Get(sList.Data());
  file->Close();
//=============================================================================

  TH1D *histo = (TH1D*)list->FindObject(sHist.Data());
  histo->SetName(Form("%s_%s_GetResultStatMB",sHist.Data(),sList.Data()));
  if (kVar!=kRatioV) NormBinningHistogram(histo);
//=============================================================================

  return histo;
}

//_____________________________________________________________________________
TGraphErrors *GetResultSystMB(const UInt_t  kAct,
                              const UInt_t  kVar,
                              const TString sPath,
                              const TH1D   *hStat)
{
  const TString sFile = "AnalysisOutputs_CombMB.root";
  const TString sList = Form("list_%s",  sActN[kAct].Data());
  const TString sHist = Form("h%s_Syst", sVarN[kVar].Data());

  cout << "TUtilsResults.h::GetResultSystMB::"
       << sFile.Data() << "::" << sList.Data() << "::" << sHist.Data() << endl;
//=============================================================================

  TFile *file = TFile::Open(Form("%s/%s",sPath.Data(),sFile.Data()), "READ");
  TList *list = (TList*)file->Get(sList.Data());
  file->Close();
//=============================================================================

  TH1D *hSyst = (TH1D*)list->FindObject(sHist.Data());
  hSyst->SetName(Form("%s_%s_GetResultSystMB",sHist.Data(),sList.Data()));
//=============================================================================

  if ((kAct==kZANS) && (kVar==kRatioV)) {
    hSyst->SetBinContent(7, 0.5*(hSyst->GetBinContent(6)+hSyst->GetBinContent(8)));
  }
//=============================================================================

  TGraphErrors *gSyst = ConvHistogramToGraphErrors(hStat, hSyst, hStat->GetNbinsX());
  gSyst->SetName(Form("g_%s",hSyst->GetName()));
//=============================================================================

  return gSyst;
}

//_____________________________________________________________________________
TH1D *GetResultSystMB(const UInt_t  kAct,
                      const UInt_t  kVar,
                      const TString sPath)
{
  const TString sFile = "AnalysisOutputs_CombMB.root";
  const TString sList = Form("list_%s",  sActN[kAct].Data());
  const TString sHist = Form("h%s_Syst", sVarN[kVar].Data());

  cout << "TUtilsResults.h::GetResultSystMB::"
       << sFile.Data() << "::" << sList.Data() << "::" << sHist.Data() << endl;
//=============================================================================

  TFile *file = TFile::Open(Form("%s/%s",sPath.Data(),sFile.Data()), "READ");
  TList *list = (TList*)file->Get(sList.Data());
  file->Close();
//=============================================================================

  TH1D *hSyst = (TH1D*)list->FindObject(sHist.Data());
  hSyst->SetName(Form("%s_%s_GetResultSystMB",sHist.Data(),sList.Data()));
//=============================================================================

  if ((kAct==kZANS) && (kVar==kRatioV)) {
    hSyst->SetBinContent(7, 0.5*(hSyst->GetBinContent(6)+hSyst->GetBinContent(8)));
  }
//=============================================================================

  return hSyst;
}
//=============================================================================
//=============================================================================

//_____________________________________________________________________________
TH1D *GetResultStatUE(const UInt_t  kCje,
                      const UInt_t  kAct,
                      const UInt_t  kPtj,
                      const UInt_t  kBkg,
                      const UInt_t  kVar,
                      const UInt_t  kOpt,
                      const TString sPath)
{
  const TString sFile = "AnalysisOutputs_StatUE.root";
  const TString sList = Form("list_%s_%s_%s_%s_%s", sRjeN[kCje].Data(),
                                                    sCjeN[kCje].Data(),
                                                    sActN[kAct].Data(),
                                                    sPtjN[kPtj].Data(),
                                                    sBkgN[kBkg].Data());
  const TString sHist = Form("h%s_%s", sVarN[kVar].Data(), sType[kOpt].Data());

  cout << "TUtilsResults.h::GetResultStatUE::"
       << sFile.Data() << "::" << sList.Data() << "::" << sHist.Data() << endl;
//=============================================================================

  TFile *file = TFile::Open(Form("%s/%s",sPath.Data(),sFile.Data()), "READ");
  TList *list = (TList*)file->Get(sList.Data());
  file->Close();
//=============================================================================

  TH1D *histo = (TH1D*)list->FindObject(sHist.Data());
  histo->SetName(Form("%s_%s_GetResultStatUE",sHist.Data(),sList.Data()));
  if (kVar!=kRatioV) NormBinningHistogram(histo);
//=============================================================================

  return histo;
}

//_____________________________________________________________________________
TH1D *GetResultStatJC(const UInt_t  kRje,
                      const UInt_t  kCje,
                      const UInt_t  kAct,
                      const UInt_t  kPtj,
                      const UInt_t  kVar,
                      const TString sPath)
{
  const TString sFile = "AnalysisOutputs_StatJC.root";
  const TString sList = Form("list_%s_%s_%s_%s", sRjeN[kRje].Data(),
                                                 sCjeN[kCje].Data(),
                                                 sActN[kAct].Data(),
                                                 sPtjN[kPtj].Data());
  const TString sHist = Form("h%s_JC", sVarN[kVar].Data());

  cout << "TUtilsResults.h::GetResultStatJC::"
       << sFile.Data() << "::" << sList.Data() << "::" << sHist.Data() << endl;
//=============================================================================

  TFile *file = TFile::Open(Form("%s/%s",sPath.Data(),sFile.Data()), "READ");
  TList *list = (TList*)file->Get(sList.Data());
  file->Close();
//=============================================================================

  TH1D *histo = (TH1D*)list->FindObject(sHist.Data());
  histo->SetName(Form("%s_%s_GetResultStatJC",sHist.Data(),sList.Data()));
  if (kVar!=kRatioV) NormBinningHistogram(histo);
//=============================================================================

  return histo;
}

//_____________________________________________________________________________
TH1D *GetResultStatHD(const UInt_t  kRje,
                      const UInt_t  kCje,
                      const UInt_t  kAct,
                      const UInt_t  kPtj,
                      const UInt_t  kVar,
                      const UInt_t  kOpt,
                      const TString sPath)
{
  const TString sFile = "AnalysisOutputs_StatHD.root";
  const TString sList = Form("list_%s_%s_%s_%s", sRjeN[kRje].Data(),
                                                 sCjeN[kCje].Data(),
                                                 sActN[kAct].Data(),
                                                 sPtjN[kPtj].Data());
  const TString sHist = Form("h%s_%s", sVarN[kVar].Data(), sType[kOpt].Data());

  cout << "TUtilsResults.h::GetResultStatHD::"
       << sFile.Data() << "::" << sList.Data() << "::" << sHist.Data() << endl;
//=============================================================================

  TFile *file = TFile::Open(Form("%s/%s",sPath.Data(),sFile.Data()), "READ");
  TList *list = (TList*)file->Get(sList.Data());
  file->Close();
//=============================================================================

  TH1D *histo = (TH1D*)list->FindObject(sHist.Data());
  histo->SetName(Form("%s_%s_GetResultStatHD",sHist.Data(),sList.Data()));
  if (kVar!=kRatioV) NormBinningHistogram(histo);
//=============================================================================

  return histo;
}
//=============================================================================
//=============================================================================

//=============================================================================
//=============================================================================

//_____________________________________________________________________________
TH1D *GetRatioVSystUE(const UInt_t  kCje,
                      const UInt_t  kAct,
                      const UInt_t  kPtj,
                      const UInt_t  kBkg,
                      const UInt_t  kOpt,
                      const TString sPath)
{
  const TString sFileHD = "AnalysisOutputs_StatUE.root";
  const TString sFileJE = "AnalysisOutputs_SystJE.root";

  const UInt_t wAct = (kAct<3 ? kAct : kAct-3);
  const UInt_t uAct = (kAct==kZANS ? kV0AS : kAct);
  const TString sListHD = Form("list_%s_%s_%s_%s_%s", sRjeN[kCje].Data(),
                                                      sCjeN[kCje].Data(),
                                                      sActN[wAct].Data(),
                                                      sPtjN[kPtj].Data(),
                                                      sBkgN[kBkg].Data());

  const TString sListJC = Form("list_%s_%s_%s_%s", sRjeN[kCje].Data(),
                                                   sCjeN[kCje].Data(),
                                                   sActN[uAct].Data(),
                                                   sPtjN[kPtj].Data());

  const TString sListUE = Form("list_%s_%s_%s_%s", sRjeN[kCje].Data(),
                                                   sCjeN[kCje].Data(),
                                                   sActN[uAct].Data(),
                                                   sPtjN[kPtj].Data());

  cout << "TUtilsResults.h::GetRatioVStatUE" << endl
       << "  ::" << sFileHD.Data() << "::" << sListHD.Data() << endl
       << "  ::" << sFileJE.Data() << "::" << sListJC.Data() << endl
       << "  ::" << sFileJE.Data() << "::" << sListUE.Data() << endl;
//=============================================================================

  TFile *fileHD = TFile::Open(Form("%s/%s",sPath.Data(),sFileHD.Data()), "READ");
  TList *listHD = (TList*)fileHD->Get(sListHD.Data());
  fileHD->Close();

  TH1D *hLambdaVarHD = (TH1D*)listHD->FindObject(Form("hLambda_%s",sType[kOpt].Data()));
  TH1D *hAntiLaVarHD = (TH1D*)listHD->FindObject(Form("hAntiLa_%s",sType[kOpt].Data()));

  hLambdaVarHD->SetName(Form("hLambdaVar%s_%s_GetRatioVStatUE",sType[kOpt].Data(),sListHD.Data()));
  hAntiLaVarHD->SetName(Form("hAntiLaVar%s_%s_GetRatioVStatUE",sType[kOpt].Data(),sListHD.Data()));
//=============================================================================

  TFile *fileJE = TFile::Open(Form("%s/%s",sPath.Data(),sFileJE.Data()), "READ");
  TList *listJC = (TList*)fileJE->Get(sListJC.Data());
  TList *listUE = (TList*)fileJE->Get(sListUE.Data());
  fileJE->Close();

  TH1D *hKshortErrJE = (TH1D*)listJC->FindObject("hKshort_JE");
  TH1D *hLambdaErrJE = (TH1D*)listJC->FindObject("hLambda_JE");
  TH1D *hAntiLaErrJE = (TH1D*)listJC->FindObject("hAntiLa_JE");
  TH1D *hRatioVErrJC = (TH1D*)listJC->FindObject("hRatioV_JC");
  TH1D *hRatioVErrUE = (TH1D*)listUE->FindObject("hRatioV_UE");

  hKshortErrJE->SetName(Form("hKshortErrJE_%s_%s_GetRatioVStatUE",sType[kOpt].Data(),sListJC.Data()));
  hLambdaErrJE->SetName(Form("hLambdaErrJE_%s_%s_GetRatioVStatUE",sType[kOpt].Data(),sListJC.Data()));
  hAntiLaErrJE->SetName(Form("hAntiLaErrJE_%s_%s_GetRatioVStatUE",sType[kOpt].Data(),sListJC.Data()));
  hRatioVErrJC->SetName(Form("hRatioVErrJC_%s_%s_GetRatioVStatUE",sType[kOpt].Data(),sListJC.Data()));
  hRatioVErrUE->SetName(Form("hRatioVErrUE_%s_%s_GetRatioVStatUE",sType[kOpt].Data(),sListUE.Data()));
//=============================================================================

  TH1D *hRatioVErrJE = CalcRatioErrV0(hKshortErrJE, hLambdaErrJE, hAntiLaErrJE,
                                                    hLambdaVarHD, hAntiLaVarHD);

  hRatioVErrJE->SetName(Form("hRatioVErrJE_%s_%s_GetRatioVStatUE",sType[kOpt].Data(),sListUE.Data()));
//=============================================================================

  TH1D *hRatioVErrHD = (TH1D*)hRatioVErrJE->Clone(Form("hRatioVErr%s",sType[kOpt].Data()));
  hRatioVErrHD->SetName(Form("hRatioVErr%s_%s_GetRatioVStatUE",sType[kOpt].Data(),sListUE.Data()));
  hRatioVErrHD->Reset();
//=============================================================================

  for (Int_t k=1; k<=hRatioVErrHD->GetNbinsX(); k++) {
    Double_t dBin = hRatioVErrHD->GetBinCenter(k);
    Int_t    kBin = hRatioVErrJC->FindBin(dBin);

    Double_t dErrJE = hRatioVErrJE->GetBinContent(k);
    Double_t dErrJC = hRatioVErrJC->GetBinContent(kBin);
    Double_t dErrUE = hRatioVErrUE->GetBinContent(kBin);

    Double_t dErrHD = dErrJE*dErrJE + dErrJC*dErrJC;
    if (kOpt==kHD) dErrHD += dErrUE*dErrUE;

    hRatioVErrHD->SetBinContent(k, TMath::Sqrt(dErrHD));
  }

  return hRatioVErrHD;
}

//_____________________________________________________________________________
TH1D *GetRatioVSystHD(const UInt_t  kRje,
                      const UInt_t  kCje,
                      const UInt_t  kAct,
                      const UInt_t  kPtj,
                      const UInt_t  kOpt,
                      const TString sPath)
{
  const TString sFileHD = "AnalysisOutputs_StatHD.root";
  const TString sFileJE = "AnalysisOutputs_SystJE.root";

  const UInt_t uAct = (kAct==kZANS ? kV0AS : kAct);
  const TString sListHD = Form("list_%s_%s_%s_%s", sRjeN[kRje].Data(),
                                                   sCjeN[kCje].Data(),
                                                   sActN[kAct].Data(),
                                                   sPtjN[kPtj].Data());

  const TString sListJC = Form("list_%s_%s_%s_%s", sRjeN[kRje].Data(),
                                                   sCjeN[kRje].Data(),
                                                   sActN[uAct].Data(),
                                                   sPtjN[kPtj].Data());

  const TString sListUE = Form("list_%s_%s_%s_%s", sRjeN[kCje].Data(),
                                                   sCjeN[kCje].Data(),
                                                   sActN[uAct].Data(),
                                                   sPtjN[kPtj].Data());

  cout << "TUtilsResults.h::GetRatioVStatHD" << endl
       << "  ::" << sFileHD.Data() << "::" << sListHD.Data() << endl
       << "  ::" << sFileJE.Data() << "::" << sListJC.Data() << endl
       << "  ::" << sFileJE.Data() << "::" << sListUE.Data() << endl;
//=============================================================================

  TFile *fileHD = TFile::Open(Form("%s/%s",sPath.Data(),sFileHD.Data()), "READ");
  TList *listHD = (TList*)fileHD->Get(sListHD.Data());
  fileHD->Close();

  TH1D *hLambdaVarHD = (TH1D*)listHD->FindObject(Form("hLambda_%s",sType[kOpt].Data()));
  TH1D *hAntiLaVarHD = (TH1D*)listHD->FindObject(Form("hAntiLa_%s",sType[kOpt].Data()));

  hLambdaVarHD->SetName(Form("hLambdaVarHD_%s_%s_GetRatioVStatHD",sType[kOpt].Data(),sListHD.Data()));
  hAntiLaVarHD->SetName(Form("hAntiLaVarHD_%s_%s_GetRatioVStatHD",sType[kOpt].Data(),sListHD.Data()));
//=============================================================================

  TFile *fileJE = TFile::Open(Form("%s/%s",sPath.Data(),sFileJE.Data()), "READ");
  TList *listJC = (TList*)fileJE->Get(sListJC.Data());
  TList *listUE = (TList*)fileJE->Get(sListUE.Data());
  fileJE->Close();

  TH1D *hKshortErrJE = (TH1D*)listJC->FindObject("hKshort_JE");
  TH1D *hLambdaErrJE = (TH1D*)listJC->FindObject("hLambda_JE");
  TH1D *hAntiLaErrJE = (TH1D*)listJC->FindObject("hAntiLa_JE");
  TH1D *hRatioVErrJC = (TH1D*)listJC->FindObject("hRatioV_JC");
  TH1D *hRatioVErrUE = (TH1D*)listUE->FindObject("hRatioV_UE");

  hKshortErrJE->SetName(Form("hKshortErrJE_%s_%s_GetRatioVStatHD",sType[kOpt].Data(),sListJC.Data()));
  hLambdaErrJE->SetName(Form("hLambdaErrJE_%s_%s_GetRatioVStatHD",sType[kOpt].Data(),sListJC.Data()));
  hAntiLaErrJE->SetName(Form("hAntiLaErrJE_%s_%s_GetRatioVStatHD",sType[kOpt].Data(),sListJC.Data()));
  hRatioVErrJC->SetName(Form("hRatioVErrJC_%s_%s_GetRatioVStatHD",sType[kOpt].Data(),sListJC.Data()));
  hRatioVErrUE->SetName(Form("hRatioVErrUE_%s_%s_GetRatioVStatHD",sType[kOpt].Data(),sListUE.Data()));
//=============================================================================

  TH1D *hRatioVErrJE = CalcRatioErrV0(hKshortErrJE, hLambdaErrJE, hAntiLaErrJE,
                                                    hLambdaVarHD, hAntiLaVarHD);

  hRatioVErrJE->SetName(Form("hRatioVErrJE_%s_%s_GetRatioVStatHD",sType[kOpt].Data(),sListUE.Data()));
//=============================================================================

  TH1D *hRatioVErrHD = (TH1D*)hRatioVErrJE->Clone(Form("hRatioVErr%s",sType[kOpt].Data()));
  hRatioVErrHD->SetName(Form("hRatioVErr%s_%s_GetRatioVStatHD",sType[kOpt].Data(),sListUE.Data()));
  hRatioVErrHD->Reset();
//=============================================================================

  for (Int_t k=1; k<=hRatioVErrHD->GetNbinsX(); k++) {
    Double_t dBin = hRatioVErrHD->GetBinCenter(k);
    Int_t    kBin = hRatioVErrJC->FindBin(dBin);

    Double_t dErrJE = hRatioVErrJE->GetBinContent(k);
    Double_t dErrJC = hRatioVErrJC->GetBinContent(kBin);
    Double_t dErrUE = hRatioVErrUE->GetBinContent(kBin);

    Double_t dErrHD = dErrJE*dErrJE + dErrJC*dErrJC;
    if (kOpt==kHD) dErrHD += dErrUE*dErrUE;

    hRatioVErrHD->SetBinContent(k, TMath::Sqrt(dErrHD));
  }

  return hRatioVErrHD;
}
//=============================================================================
//=============================================================================

//_____________________________________________________________________________
TH1D *GetResultStatVJ(const UInt_t   kRje,
                      const UInt_t   kAct,
                      const UInt_t   kPtj,
                      const Double_t dPtI,
                      const Double_t dPtF,
                      const TString  sDir,
                      TH1D *hKshort, TH1D *hLambda, TH1D *hAntiLa)
{
  const TString sPathMB = Form("%s/20140602/JE_Inclusive_%s", sDir.Data(), sActN[kAct].Data());
  const TString sPath02 = Form("%s/20140602/JE_%s_JC02_%s",   sDir.Data(), sRjeN[kRje].Data(), sActN[kAct].Data());
  const TString sPath03 = Form("%s/20140602/JE_%s_JC03_%s",   sDir.Data(), sRjeN[kRje].Data(), sActN[kAct].Data());
  const TString sPath04 = Form("%s/20140602/JE_%s_JC04_%s",   sDir.Data(), sRjeN[kRje].Data(), sActN[kAct].Data());
  const TString sPath06 = Form("%s/20140602/JE_%s_JC06_%s",   sDir.Data(), sRjeN[kRje].Data(), sActN[kAct].Data());
  const TString sPath08 = Form("%s/20140602/JE_%s_JC08_%s",   sDir.Data(), sRjeN[kRje].Data(), sActN[kAct].Data());
  const TString sPath11 = Form("%s/20140602/JE_%s_JC11_%s",   sDir.Data(), sRjeN[kRje].Data(), sActN[kAct].Data());
  const TString sPath15 = Form("%s/20140602/JE_%s_JC15_%s",   sDir.Data(), sRjeN[kRje].Data(), sActN[kAct].Data());
//=============================================================================

  const Double_t dBinV[] = { 0.6, 0.7, 0.8, 0.9, 1.0, 1.1, 1.2, 1.4, 1.6, 1.8, 2.0, 2.2, 2.4, 2.6, 2.8, 3.2, 3.7, 4.2, 5.0, 6.0, 8.0, 12. };
  const Int_t    nBinV   = sizeof(dBinV)/sizeof(Double_t) - 1;

  const Int_t kBinI = TMath::BinarySearch(nBinV+1, dBinV, dPtI+1e-6) + 1;
  const Int_t kBinF = TMath::BinarySearch(nBinV+1, dBinV, dPtF-1e-6) + 1;

  const TString sHist = Form("StatVJ_%s_%s_%s_%d_%d", sRjeN[kRje].Data(),
                                                      sActN[kAct].Data(),
                                                      sPtjN[kPtj].Data(),
                                                      kBinI, kBinF);
//=============================================================================

  TH1D *hK02 = CalcV0sCorrJE(sPathMB,sPath02,sVarN[kKshort],"Default",sPtjN[kPtj],"JC",nBinV,dBinV); hK02->SetName(Form("hK02_%s",sHist.Data()));
  TH1D *hK03 = CalcV0sCorrJE(sPathMB,sPath03,sVarN[kKshort],"Default",sPtjN[kPtj],"JC",nBinV,dBinV); hK03->SetName(Form("hK03_%s",sHist.Data()));
  TH1D *hK04 = CalcV0sCorrJE(sPathMB,sPath04,sVarN[kKshort],"Default",sPtjN[kPtj],"JC",nBinV,dBinV); hK04->SetName(Form("hK04_%s",sHist.Data()));
  TH1D *hK06 = CalcV0sCorrJE(sPathMB,sPath06,sVarN[kKshort],"Default",sPtjN[kPtj],"JC",nBinV,dBinV); hK06->SetName(Form("hK06_%s",sHist.Data()));
  TH1D *hK08 = CalcV0sCorrJE(sPathMB,sPath08,sVarN[kKshort],"Default",sPtjN[kPtj],"JC",nBinV,dBinV); hK08->SetName(Form("hK08_%s",sHist.Data()));
  TH1D *hK11 = CalcV0sCorrJE(sPathMB,sPath11,sVarN[kKshort],"Default",sPtjN[kPtj],"JC",nBinV,dBinV); hK11->SetName(Form("hK11_%s",sHist.Data()));
  TH1D *hK15 = CalcV0sCorrJE(sPathMB,sPath15,sVarN[kKshort],"Default",sPtjN[kPtj],"JC",nBinV,dBinV); hK15->SetName(Form("hK15_%s",sHist.Data()));

  TH1D *hL02 = CalcV0sCorrJE(sPathMB,sPath02,sVarN[kLambda],"Default",sPtjN[kPtj],"JC",nBinV,dBinV); hL02->SetName(Form("hL02_%s",sHist.Data()));
  TH1D *hL03 = CalcV0sCorrJE(sPathMB,sPath03,sVarN[kLambda],"Default",sPtjN[kPtj],"JC",nBinV,dBinV); hL03->SetName(Form("hL03_%s",sHist.Data()));
  TH1D *hL04 = CalcV0sCorrJE(sPathMB,sPath04,sVarN[kLambda],"Default",sPtjN[kPtj],"JC",nBinV,dBinV); hL04->SetName(Form("hL04_%s",sHist.Data()));
  TH1D *hL06 = CalcV0sCorrJE(sPathMB,sPath06,sVarN[kLambda],"Default",sPtjN[kPtj],"JC",nBinV,dBinV); hL06->SetName(Form("hL06_%s",sHist.Data()));
  TH1D *hL08 = CalcV0sCorrJE(sPathMB,sPath08,sVarN[kLambda],"Default",sPtjN[kPtj],"JC",nBinV,dBinV); hL08->SetName(Form("hL08_%s",sHist.Data()));
  TH1D *hL11 = CalcV0sCorrJE(sPathMB,sPath11,sVarN[kLambda],"Default",sPtjN[kPtj],"JC",nBinV,dBinV); hL11->SetName(Form("hL11_%s",sHist.Data()));
  TH1D *hL15 = CalcV0sCorrJE(sPathMB,sPath15,sVarN[kLambda],"Default",sPtjN[kPtj],"JC",nBinV,dBinV); hL15->SetName(Form("hL15_%s",sHist.Data()));

  TH1D *hA02 = CalcV0sCorrJE(sPathMB,sPath02,sVarN[kAntiLa],"Default",sPtjN[kPtj],"JC",nBinV,dBinV); hA02->SetName(Form("hA02_%s",sHist.Data()));
  TH1D *hA03 = CalcV0sCorrJE(sPathMB,sPath03,sVarN[kAntiLa],"Default",sPtjN[kPtj],"JC",nBinV,dBinV); hA03->SetName(Form("hA03_%s",sHist.Data()));
  TH1D *hA04 = CalcV0sCorrJE(sPathMB,sPath04,sVarN[kAntiLa],"Default",sPtjN[kPtj],"JC",nBinV,dBinV); hA04->SetName(Form("hA04_%s",sHist.Data()));
  TH1D *hA06 = CalcV0sCorrJE(sPathMB,sPath06,sVarN[kAntiLa],"Default",sPtjN[kPtj],"JC",nBinV,dBinV); hA06->SetName(Form("hA06_%s",sHist.Data()));
  TH1D *hA08 = CalcV0sCorrJE(sPathMB,sPath08,sVarN[kAntiLa],"Default",sPtjN[kPtj],"JC",nBinV,dBinV); hA08->SetName(Form("hA08_%s",sHist.Data()));
  TH1D *hA11 = CalcV0sCorrJE(sPathMB,sPath11,sVarN[kAntiLa],"Default",sPtjN[kPtj],"JC",nBinV,dBinV); hA11->SetName(Form("hA11_%s",sHist.Data()));
  TH1D *hA15 = CalcV0sCorrJE(sPathMB,sPath15,sVarN[kAntiLa],"Default",sPtjN[kPtj],"JC",nBinV,dBinV); hA15->SetName(Form("hA15_%s",sHist.Data()));
//=============================================================================

  Int_t kc = 0;
  if (sActN[kAct].Contains("000_010")) kc = 0;
  if (sActN[kAct].Contains("010_040")) kc = 1;
  if (sActN[kAct].Contains("040_100")) kc = 2; 

  FeeddownSubtraction(hL02, hA02, kc);
  FeeddownSubtraction(hL03, hA03, kc);
  FeeddownSubtraction(hL04, hA04, kc);
  FeeddownSubtraction(hL06, hA06, kc);
  FeeddownSubtraction(hL08, hA08, kc);
  FeeddownSubtraction(hL11, hA11, kc);
  FeeddownSubtraction(hL15, hA15, kc);
//=============================================================================

  Double_t deK02 = 0.; Double_t dvK02 = hK02->IntegralAndError(kBinI, kBinF, deK02);
  Double_t deK03 = 0.; Double_t dvK03 = hK03->IntegralAndError(kBinI, kBinF, deK03);
  Double_t deK04 = 0.; Double_t dvK04 = hK04->IntegralAndError(kBinI, kBinF, deK04);
  Double_t deK06 = 0.; Double_t dvK06 = hK06->IntegralAndError(kBinI, kBinF, deK06);
  Double_t deK08 = 0.; Double_t dvK08 = hK08->IntegralAndError(kBinI, kBinF, deK08);
  Double_t deK11 = 0.; Double_t dvK11 = hK11->IntegralAndError(kBinI, kBinF, deK11);
  Double_t deK15 = 0.; Double_t dvK15 = hK15->IntegralAndError(kBinI, kBinF, deK15);

  Double_t deL02 = 0.; Double_t dvL02 = hL02->IntegralAndError(kBinI, kBinF, deL02);
  Double_t deL03 = 0.; Double_t dvL03 = hL03->IntegralAndError(kBinI, kBinF, deL03);
  Double_t deL04 = 0.; Double_t dvL04 = hL04->IntegralAndError(kBinI, kBinF, deL04);
  Double_t deL06 = 0.; Double_t dvL06 = hL06->IntegralAndError(kBinI, kBinF, deL06);
  Double_t deL08 = 0.; Double_t dvL08 = hL08->IntegralAndError(kBinI, kBinF, deL08);
  Double_t deL11 = 0.; Double_t dvL11 = hL11->IntegralAndError(kBinI, kBinF, deL11);
  Double_t deL15 = 0.; Double_t dvL15 = hL15->IntegralAndError(kBinI, kBinF, deL15);

  Double_t deA02 = 0.; Double_t dvA02 = hA02->IntegralAndError(kBinI, kBinF, deA02);
  Double_t deA03 = 0.; Double_t dvA03 = hA03->IntegralAndError(kBinI, kBinF, deA03);
  Double_t deA04 = 0.; Double_t dvA04 = hA04->IntegralAndError(kBinI, kBinF, deA04);
  Double_t deA06 = 0.; Double_t dvA06 = hA06->IntegralAndError(kBinI, kBinF, deA06);
  Double_t deA08 = 0.; Double_t dvA08 = hA08->IntegralAndError(kBinI, kBinF, deA08);
  Double_t deA11 = 0.; Double_t dvA11 = hA11->IntegralAndError(kBinI, kBinF, deA11);
  Double_t deA15 = 0.; Double_t dvA15 = hA15->IntegralAndError(kBinI, kBinF, deA15);
//=============================================================================

  Double_t dnK02 = GetNormArJE(sPath02, sVarN[kKshort], "Default", sPtjN[kPtj], "JC");
  Double_t dnK03 = GetNormArJE(sPath03, sVarN[kKshort], "Default", sPtjN[kPtj], "JC");
  Double_t dnK04 = GetNormArJE(sPath04, sVarN[kKshort], "Default", sPtjN[kPtj], "JC");
  Double_t dnK06 = GetNormArJE(sPath06, sVarN[kKshort], "Default", sPtjN[kPtj], "JC");
  Double_t dnK08 = GetNormArJE(sPath08, sVarN[kKshort], "Default", sPtjN[kPtj], "JC");
  Double_t dnK11 = GetNormArJE(sPath11, sVarN[kKshort], "Default", sPtjN[kPtj], "JC");
  Double_t dnK15 = GetNormArJE(sPath15, sVarN[kKshort], "Default", sPtjN[kPtj], "JC");

  Double_t dnL02 = GetNormArJE(sPath02, sVarN[kLambda], "Default", sPtjN[kPtj], "JC");
  Double_t dnL03 = GetNormArJE(sPath03, sVarN[kLambda], "Default", sPtjN[kPtj], "JC");
  Double_t dnL04 = GetNormArJE(sPath04, sVarN[kLambda], "Default", sPtjN[kPtj], "JC");
  Double_t dnL06 = GetNormArJE(sPath06, sVarN[kLambda], "Default", sPtjN[kPtj], "JC");
  Double_t dnL08 = GetNormArJE(sPath08, sVarN[kLambda], "Default", sPtjN[kPtj], "JC");
  Double_t dnL11 = GetNormArJE(sPath11, sVarN[kLambda], "Default", sPtjN[kPtj], "JC");
  Double_t dnL15 = GetNormArJE(sPath15, sVarN[kLambda], "Default", sPtjN[kPtj], "JC");

  Double_t dnA02 = GetNormArJE(sPath02, sVarN[kAntiLa], "Default", sPtjN[kPtj], "JC");
  Double_t dnA03 = GetNormArJE(sPath03, sVarN[kAntiLa], "Default", sPtjN[kPtj], "JC");
  Double_t dnA04 = GetNormArJE(sPath04, sVarN[kAntiLa], "Default", sPtjN[kPtj], "JC");
  Double_t dnA06 = GetNormArJE(sPath06, sVarN[kAntiLa], "Default", sPtjN[kPtj], "JC");
  Double_t dnA08 = GetNormArJE(sPath08, sVarN[kAntiLa], "Default", sPtjN[kPtj], "JC");
  Double_t dnA11 = GetNormArJE(sPath11, sVarN[kAntiLa], "Default", sPtjN[kPtj], "JC");
  Double_t dnA15 = GetNormArJE(sPath15, sVarN[kAntiLa], "Default", sPtjN[kPtj], "JC");
//=============================================================================

  hKshort->SetBinContent(1,  dvK02 / dnK02); hKshort->SetBinError(1, deK02 / dnK02);
/*hKshort->SetBinContent(2,  dvK03 / dnK03); hKshort->SetBinError(2, deK03 / dnK03);
  hKshort->SetBinContent(3,  dvK04 / dnK04); hKshort->SetBinError(3, deK04 / dnK04);
  hKshort->SetBinContent(4,  dvK06 / dnK06); hKshort->SetBinError(4, deK06 / dnK06);
  hKshort->SetBinContent(5,  dvK08 / dnK08); hKshort->SetBinError(5, deK08 / dnK08);
  hKshort->SetBinContent(6,  dvK11 / dnK11); hKshort->SetBinError(6, deK11 / dnK11);
  hKshort->SetBinContent(7,  dvK15 / dnK15); hKshort->SetBinError(7, deK15 / dnK15);*/
  hKshort->SetBinContent(2, (dvK03-dvK02)/(dnK03-dnK02)); hKshort->SetBinError(2, TMath::Sqrt(deK03*deK03 + deK02*deK02)/(dnK03-dnK02));
  hKshort->SetBinContent(3, (dvK04-dvK03)/(dnK04-dnK03)); hKshort->SetBinError(3, TMath::Sqrt(deK04*deK04 + deK03*deK03)/(dnK04-dnK03));
  hKshort->SetBinContent(4, (dvK06-dvK04)/(dnK06-dnK04)); hKshort->SetBinError(4, TMath::Sqrt(deK06*deK06 + deK04*deK04)/(dnK06-dnK04));
  hKshort->SetBinContent(5, (dvK08-dvK06)/(dnK08-dnK06)); hKshort->SetBinError(5, TMath::Sqrt(deK08*deK08 + deK06*deK06)/(dnK08-dnK06));
  hKshort->SetBinContent(6, (dvK11-dvK08)/(dnK11-dnK08)); hKshort->SetBinError(6, TMath::Sqrt(deK11*deK11 + deK08*deK08)/(dnK11-dnK08));
  hKshort->SetBinContent(7, (dvK15-dvK11)/(dnK15-dnK11)); hKshort->SetBinError(7, TMath::Sqrt(deK15*deK15 + deK11*deK11)/(dnK15-dnK11));

  hLambda->SetBinContent(1,  dvL02 / dnL02); hLambda->SetBinError(1, deL02 / dnL02);
/*hLambda->SetBinContent(2,  dvL03 / dnL03); hLambda->SetBinError(2, deL03 / dnL03);
  hLambda->SetBinContent(3,  dvL04 / dnL04); hLambda->SetBinError(3, deL04 / dnL04);
  hLambda->SetBinContent(4,  dvL06 / dnL06); hLambda->SetBinError(4, deL06 / dnL06);
  hLambda->SetBinContent(5,  dvL08 / dnL08); hLambda->SetBinError(5, deL08 / dnL08);
  hLambda->SetBinContent(6,  dvL11 / dnL11); hLambda->SetBinError(6, deL11 / dnL11);
  hLambda->SetBinContent(7,  dvL15 / dnL15); hLambda->SetBinError(7, deL15 / dnL15);*/
  hLambda->SetBinContent(2, (dvL03-dvL02)/(dnL03-dnL02)); hLambda->SetBinError(2, TMath::Sqrt(deL03*deL03 + deL02*deL02)/(dnL03-dnL02));
  hLambda->SetBinContent(3, (dvL04-dvL03)/(dnL04-dnL03)); hLambda->SetBinError(3, TMath::Sqrt(deL04*deL04 + deL03*deL03)/(dnL04-dnL03));
  hLambda->SetBinContent(4, (dvL06-dvL04)/(dnL06-dnL04)); hLambda->SetBinError(4, TMath::Sqrt(deL06*deL06 + deL04*deL04)/(dnL06-dnL04));
  hLambda->SetBinContent(5, (dvL08-dvL06)/(dnL08-dnL06)); hLambda->SetBinError(5, TMath::Sqrt(deL08*deL08 + deL06*deL06)/(dnL08-dnL06));
  hLambda->SetBinContent(6, (dvL11-dvL08)/(dnL11-dnL08)); hLambda->SetBinError(6, TMath::Sqrt(deL11*deL11 + deL08*deL08)/(dnL11-dnL08));
  hLambda->SetBinContent(7, (dvL15-dvL11)/(dnL15-dnL11)); hLambda->SetBinError(7, TMath::Sqrt(deL15*deL15 + deL11*deL11)/(dnL15-dnL11));

  hAntiLa->SetBinContent(1,  dvA02 / dnA02); hAntiLa->SetBinError(1, deA02 / dnA02);
/*hAntiLa->SetBinContent(2,  dvA03 / dnA03); hAntiLa->SetBinError(2, deA03 / dnA03);
  hAntiLa->SetBinContent(3,  dvA04 / dnA04); hAntiLa->SetBinError(3, deA04 / dnA04);
  hAntiLa->SetBinContent(4,  dvA06 / dnA06); hAntiLa->SetBinError(4, deA06 / dnA06);
  hAntiLa->SetBinContent(5,  dvA08 / dnA08); hAntiLa->SetBinError(5, deA08 / dnA08);
  hAntiLa->SetBinContent(6,  dvA11 / dnA11); hAntiLa->SetBinError(6, deA11 / dnA11);
  hAntiLa->SetBinContent(7,  dvA15 / dnA15); hAntiLa->SetBinError(7, deA15 / dnA15);*/
  hAntiLa->SetBinContent(2, (dvA03-dvA02)/(dnA03-dnA02)); hAntiLa->SetBinError(2, TMath::Sqrt(deA03*deA03 + deA02*deA02)/(dnA03-dnA02));
  hAntiLa->SetBinContent(3, (dvA04-dvA03)/(dnA04-dnA03)); hAntiLa->SetBinError(3, TMath::Sqrt(deA04*deA04 + deA03*deA03)/(dnA04-dnA03));
  hAntiLa->SetBinContent(4, (dvA06-dvA04)/(dnA06-dnA04)); hAntiLa->SetBinError(4, TMath::Sqrt(deA06*deA06 + deA04*deA04)/(dnA06-dnA04));
  hAntiLa->SetBinContent(5, (dvA08-dvA06)/(dnA08-dnA06)); hAntiLa->SetBinError(5, TMath::Sqrt(deA08*deA08 + deA06*deA06)/(dnA08-dnA06));
  hAntiLa->SetBinContent(6, (dvA11-dvA08)/(dnA11-dnA08)); hAntiLa->SetBinError(6, TMath::Sqrt(deA11*deA11 + deA08*deA08)/(dnA11-dnA08));
  hAntiLa->SetBinContent(7, (dvA15-dvA11)/(dnA15-dnA11)); hAntiLa->SetBinError(7, TMath::Sqrt(deA15*deA15 + deA11*deA11)/(dnA15-dnA11));
//=============================================================================

  TH1D *hRatioV = CalcRatioVarV0(hKshort, hLambda, hAntiLa); hRatioV->SetName(Form("hRatioV_%s",sHist.Data()));
//=============================================================================

  return hRatioV;
}

//_____________________________________________________________________________
TH1D *GetResultSystVJ(const UInt_t   kRje,
                      const UInt_t   kAct,
                      const UInt_t   kPtj,
                      const Double_t dPtI,
                      const Double_t dPtF,
                      const TString  sDir,
                      TH1D *hKshort, TH1D *hLambda, TH1D *hAntiLa)
{
  const TString sDirOut = Form("%s/outputs", sDir.Data());
  const TString sPathMB = Form("%s/20140602/JE_Inclusive_%s", sDir.Data(), sActN[kAct].Data());
  const TString sPath02 = Form("%s/20140602/JE_%s_JC02_%s",   sDir.Data(), sRjeN[kRje].Data(), sActN[kAct].Data());
  const TString sPath03 = Form("%s/20140602/JE_%s_JC03_%s",   sDir.Data(), sRjeN[kRje].Data(), sActN[kAct].Data());
  const TString sPath04 = Form("%s/20140602/JE_%s_JC04_%s",   sDir.Data(), sRjeN[kRje].Data(), sActN[kAct].Data());
  const TString sPath06 = Form("%s/20140602/JE_%s_JC06_%s",   sDir.Data(), sRjeN[kRje].Data(), sActN[kAct].Data());
  const TString sPath08 = Form("%s/20140602/JE_%s_JC08_%s",   sDir.Data(), sRjeN[kRje].Data(), sActN[kAct].Data());
  const TString sPath11 = Form("%s/20140602/JE_%s_JC11_%s",   sDir.Data(), sRjeN[kRje].Data(), sActN[kAct].Data());
  const TString sPath15 = Form("%s/20140602/JE_%s_JC15_%s",   sDir.Data(), sRjeN[kRje].Data(), sActN[kAct].Data());
//=============================================================================

  const Double_t dBinV[] = { 0.6, 0.7, 0.8, 0.9, 1.0, 1.1, 1.2, 1.4, 1.6, 1.8, 2.0, 2.2, 2.4, 2.6, 2.8, 3.2, 3.7, 4.2, 5.0, 6.0, 8.0, 12. };
  const Int_t    nBinV   = sizeof(dBinV)/sizeof(Double_t) - 1;

  const Int_t kBinI = TMath::BinarySearch(nBinV+1, dBinV, dPtI+1e-6) + 1;
  const Int_t kBinF = TMath::BinarySearch(nBinV+1, dBinV, dPtF-1e-6) + 1;

  const TString sHist = Form("SystVJ_%s_%s_%s_%d_%d", sRjeN[kRje].Data(),
                                                      sActN[kAct].Data(),
                                                      sPtjN[kPtj].Data(),
                                                      kBinI, kBinF);
//=============================================================================

  TH1D *hvK02 = CalcV0sCorrJE(sPathMB,sPath02,sVarN[kKshort],"Default",sPtjN[kPtj],"JC",nBinV,dBinV); hvK02->SetName(Form("hvK02_%s",sHist.Data()));
  TH1D *hvK03 = CalcV0sCorrJE(sPathMB,sPath03,sVarN[kKshort],"Default",sPtjN[kPtj],"JC",nBinV,dBinV); hvK03->SetName(Form("hvK03_%s",sHist.Data()));
  TH1D *hvK04 = CalcV0sCorrJE(sPathMB,sPath04,sVarN[kKshort],"Default",sPtjN[kPtj],"JC",nBinV,dBinV); hvK04->SetName(Form("hvK04_%s",sHist.Data()));
  TH1D *hvK06 = CalcV0sCorrJE(sPathMB,sPath06,sVarN[kKshort],"Default",sPtjN[kPtj],"JC",nBinV,dBinV); hvK06->SetName(Form("hvK06_%s",sHist.Data()));
  TH1D *hvK08 = CalcV0sCorrJE(sPathMB,sPath08,sVarN[kKshort],"Default",sPtjN[kPtj],"JC",nBinV,dBinV); hvK08->SetName(Form("hvK08_%s",sHist.Data()));
  TH1D *hvK11 = CalcV0sCorrJE(sPathMB,sPath11,sVarN[kKshort],"Default",sPtjN[kPtj],"JC",nBinV,dBinV); hvK11->SetName(Form("hvK11_%s",sHist.Data()));
  TH1D *hvK15 = CalcV0sCorrJE(sPathMB,sPath15,sVarN[kKshort],"Default",sPtjN[kPtj],"JC",nBinV,dBinV); hvK15->SetName(Form("hvK15_%s",sHist.Data()));

  TH1D *hvL02 = CalcV0sCorrJE(sPathMB,sPath02,sVarN[kLambda],"Default",sPtjN[kPtj],"JC",nBinV,dBinV); hvL02->SetName(Form("hvL02_%s",sHist.Data()));
  TH1D *hvL03 = CalcV0sCorrJE(sPathMB,sPath03,sVarN[kLambda],"Default",sPtjN[kPtj],"JC",nBinV,dBinV); hvL03->SetName(Form("hvL03_%s",sHist.Data()));
  TH1D *hvL04 = CalcV0sCorrJE(sPathMB,sPath04,sVarN[kLambda],"Default",sPtjN[kPtj],"JC",nBinV,dBinV); hvL04->SetName(Form("hvL04_%s",sHist.Data()));
  TH1D *hvL06 = CalcV0sCorrJE(sPathMB,sPath06,sVarN[kLambda],"Default",sPtjN[kPtj],"JC",nBinV,dBinV); hvL06->SetName(Form("hvL06_%s",sHist.Data()));
  TH1D *hvL08 = CalcV0sCorrJE(sPathMB,sPath08,sVarN[kLambda],"Default",sPtjN[kPtj],"JC",nBinV,dBinV); hvL08->SetName(Form("hvL08_%s",sHist.Data()));
  TH1D *hvL11 = CalcV0sCorrJE(sPathMB,sPath11,sVarN[kLambda],"Default",sPtjN[kPtj],"JC",nBinV,dBinV); hvL11->SetName(Form("hvL11_%s",sHist.Data()));
  TH1D *hvL15 = CalcV0sCorrJE(sPathMB,sPath15,sVarN[kLambda],"Default",sPtjN[kPtj],"JC",nBinV,dBinV); hvL15->SetName(Form("hvL15_%s",sHist.Data()));

  TH1D *hvA02 = CalcV0sCorrJE(sPathMB,sPath02,sVarN[kAntiLa],"Default",sPtjN[kPtj],"JC",nBinV,dBinV); hvA02->SetName(Form("hvA02_%s",sHist.Data()));
  TH1D *hvA03 = CalcV0sCorrJE(sPathMB,sPath03,sVarN[kAntiLa],"Default",sPtjN[kPtj],"JC",nBinV,dBinV); hvA03->SetName(Form("hvA03_%s",sHist.Data()));
  TH1D *hvA04 = CalcV0sCorrJE(sPathMB,sPath04,sVarN[kAntiLa],"Default",sPtjN[kPtj],"JC",nBinV,dBinV); hvA04->SetName(Form("hvA04_%s",sHist.Data()));
  TH1D *hvA06 = CalcV0sCorrJE(sPathMB,sPath06,sVarN[kAntiLa],"Default",sPtjN[kPtj],"JC",nBinV,dBinV); hvA06->SetName(Form("hvA06_%s",sHist.Data()));
  TH1D *hvA08 = CalcV0sCorrJE(sPathMB,sPath08,sVarN[kAntiLa],"Default",sPtjN[kPtj],"JC",nBinV,dBinV); hvA08->SetName(Form("hvA08_%s",sHist.Data()));
  TH1D *hvA11 = CalcV0sCorrJE(sPathMB,sPath11,sVarN[kAntiLa],"Default",sPtjN[kPtj],"JC",nBinV,dBinV); hvA11->SetName(Form("hvA11_%s",sHist.Data()));
  TH1D *hvA15 = CalcV0sCorrJE(sPathMB,sPath15,sVarN[kAntiLa],"Default",sPtjN[kPtj],"JC",nBinV,dBinV); hvA15->SetName(Form("hvA15_%s",sHist.Data()));
//=============================================================================

  Int_t kc = 0;
  if (sActN[kAct].Contains("000_010")) kc = 0;
  if (sActN[kAct].Contains("010_040")) kc = 1;
  if (sActN[kAct].Contains("040_100")) kc = 2; 

  FeeddownSubtraction(hvL02, hvA02, kc);
  FeeddownSubtraction(hvL03, hvA03, kc);
  FeeddownSubtraction(hvL04, hvA04, kc);
  FeeddownSubtraction(hvL06, hvA06, kc);
  FeeddownSubtraction(hvL08, hvA08, kc);
  FeeddownSubtraction(hvL11, hvA11, kc);
  FeeddownSubtraction(hvL15, hvA15, kc);
//=============================================================================

  const Double_t dvK02 = hvK02->Integral(kBinI, kBinF);
  const Double_t dvK03 = hvK03->Integral(kBinI, kBinF);
  const Double_t dvK04 = hvK04->Integral(kBinI, kBinF);
  const Double_t dvK06 = hvK06->Integral(kBinI, kBinF);
  const Double_t dvK08 = hvK08->Integral(kBinI, kBinF);
  const Double_t dvK11 = hvK11->Integral(kBinI, kBinF);
  const Double_t dvK15 = hvK15->Integral(kBinI, kBinF);

  const Double_t dvL02 = hvL02->Integral(kBinI, kBinF);
  const Double_t dvL03 = hvL03->Integral(kBinI, kBinF);
  const Double_t dvL04 = hvL04->Integral(kBinI, kBinF);
  const Double_t dvL06 = hvL06->Integral(kBinI, kBinF);
  const Double_t dvL08 = hvL08->Integral(kBinI, kBinF);
  const Double_t dvL11 = hvL11->Integral(kBinI, kBinF);
  const Double_t dvL15 = hvL15->Integral(kBinI, kBinF);

  const Double_t dvA02 = hvA02->Integral(kBinI, kBinF);
  const Double_t dvA03 = hvA03->Integral(kBinI, kBinF);
  const Double_t dvA04 = hvA04->Integral(kBinI, kBinF);
  const Double_t dvA06 = hvA06->Integral(kBinI, kBinF);
  const Double_t dvA08 = hvA08->Integral(kBinI, kBinF);
  const Double_t dvA11 = hvA11->Integral(kBinI, kBinF);
  const Double_t dvA15 = hvA15->Integral(kBinI, kBinF);
//=============================================================================

  const Double_t dnK02 = GetNormArJE(sPath02, sVarN[kKshort], "Default", sPtjN[kPtj], "JC");
  const Double_t dnK03 = GetNormArJE(sPath03, sVarN[kKshort], "Default", sPtjN[kPtj], "JC");
  const Double_t dnK04 = GetNormArJE(sPath04, sVarN[kKshort], "Default", sPtjN[kPtj], "JC");
  const Double_t dnK06 = GetNormArJE(sPath06, sVarN[kKshort], "Default", sPtjN[kPtj], "JC");
  const Double_t dnK08 = GetNormArJE(sPath08, sVarN[kKshort], "Default", sPtjN[kPtj], "JC");
  const Double_t dnK11 = GetNormArJE(sPath11, sVarN[kKshort], "Default", sPtjN[kPtj], "JC");
  const Double_t dnK15 = GetNormArJE(sPath15, sVarN[kKshort], "Default", sPtjN[kPtj], "JC");

  const Double_t dnL02 = GetNormArJE(sPath02, sVarN[kLambda], "Default", sPtjN[kPtj], "JC");
  const Double_t dnL03 = GetNormArJE(sPath03, sVarN[kLambda], "Default", sPtjN[kPtj], "JC");
  const Double_t dnL04 = GetNormArJE(sPath04, sVarN[kLambda], "Default", sPtjN[kPtj], "JC");
  const Double_t dnL06 = GetNormArJE(sPath06, sVarN[kLambda], "Default", sPtjN[kPtj], "JC");
  const Double_t dnL08 = GetNormArJE(sPath08, sVarN[kLambda], "Default", sPtjN[kPtj], "JC");
  const Double_t dnL11 = GetNormArJE(sPath11, sVarN[kLambda], "Default", sPtjN[kPtj], "JC");
  const Double_t dnL15 = GetNormArJE(sPath15, sVarN[kLambda], "Default", sPtjN[kPtj], "JC");

  const Double_t dnA02 = GetNormArJE(sPath02, sVarN[kAntiLa], "Default", sPtjN[kPtj], "JC");
  const Double_t dnA03 = GetNormArJE(sPath03, sVarN[kAntiLa], "Default", sPtjN[kPtj], "JC");
  const Double_t dnA04 = GetNormArJE(sPath04, sVarN[kAntiLa], "Default", sPtjN[kPtj], "JC");
  const Double_t dnA06 = GetNormArJE(sPath06, sVarN[kAntiLa], "Default", sPtjN[kPtj], "JC");
  const Double_t dnA08 = GetNormArJE(sPath08, sVarN[kAntiLa], "Default", sPtjN[kPtj], "JC");
  const Double_t dnA11 = GetNormArJE(sPath11, sVarN[kAntiLa], "Default", sPtjN[kPtj], "JC");
  const Double_t dnA15 = GetNormArJE(sPath15, sVarN[kAntiLa], "Default", sPtjN[kPtj], "JC");
//=============================================================================

  const TString sList = Form("list_%s_%s_%s_%s", sRjeN[kRje].Data(),
                                                 sCjeN[kRje].Data(),
                                                 sActN[kAct].Data(),
                                                 sPtjN[kPtj].Data());

  TFile *file = TFile::Open(Form("%s/AnalysisOutputs_SystJE.root",sDirOut.Data()), "READ");
  TList *list = file->Get(sList.Data());
  file->Close();

  TH1D *heKje = (TH1D*)list->FindObject("hKshort_JE"); heKje->SetName(Form("heKje_%s",sHist.Data()));
  TH1D *heLje = (TH1D*)list->FindObject("hLambda_JE"); heLje->SetName(Form("heLje_%s",sHist.Data()));
  TH1D *heAje = (TH1D*)list->FindObject("hAntiLa_JE"); heAje->SetName(Form("heAje_%s",sHist.Data()));

  TH1D *heKjc = (TH1D*)list->FindObject("hKshort_JC"); heKjc->SetName(Form("heKjc_%s",sHist.Data()));
  TH1D *heLjc = (TH1D*)list->FindObject("hLambda_JC"); heLjc->SetName(Form("heLjc_%s",sHist.Data()));
  TH1D *heAjc = (TH1D*)list->FindObject("hAntiLa_JC"); heAjc->SetName(Form("heAjc_%s",sHist.Data()));

  TH1D *heRjc = (TH1D*)list->FindObject("hRatioV_JC"); heRjc->SetName(Form("heRjc_%s",sHist.Data()));
//=============================================================================

  const Double_t dPtM = 0.5 * (dPtI + dPtF);
  const Double_t deKje = heKje->GetBinContent(heKje->FindBin(dPtM));
  const Double_t deLje = heLje->GetBinContent(heLje->FindBin(dPtM));
  const Double_t deAje = heAje->GetBinContent(heAje->FindBin(dPtM));

  const Double_t deKjc = heKjc->GetBinContent(heKjc->FindBin(dPtM));
  const Double_t deLjc = heLjc->GetBinContent(heLjc->FindBin(dPtM));
  const Double_t deAjc = heAjc->GetBinContent(heAjc->FindBin(dPtM));

  const Double_t deRjc = heRjc->GetBinContent(heRjc->FindBin(dPtM));
//=============================================================================

  hKshort->SetBinContent(1,  dvK02 / dnK02); hKshort->SetBinError(1, deKje * hKshort->GetBinContent(1));
/*hKshort->SetBinContent(2,  dvK03 / dnK03); hKshort->SetBinError(2, deKje * hKshort->GetBinContent(2));
  hKshort->SetBinContent(3,  dvK04 / dnK04); hKshort->SetBinError(3, deKje * hKshort->GetBinContent(3));
  hKshort->SetBinContent(4,  dvK06 / dnK06); hKshort->SetBinError(4, deKje * hKshort->GetBinContent(4));
  hKshort->SetBinContent(5,  dvK08 / dnK08); hKshort->SetBinError(5, deKje * hKshort->GetBinContent(5));
  hKshort->SetBinContent(6,  dvK11 / dnK11); hKshort->SetBinError(6, deKje * hKshort->GetBinContent(6));
  hKshort->SetBinContent(7,  dvK15 / dnK15); hKshort->SetBinError(7, deKje * hKshort->GetBinContent(7));*/
  hKshort->SetBinContent(2, (dvK03-dvK02)/(dnK03-dnK02)); hKshort->SetBinError(2, deKje * hKshort->GetBinContent(2));
  hKshort->SetBinContent(3, (dvK04-dvK03)/(dnK04-dnK03)); hKshort->SetBinError(3, deKje * hKshort->GetBinContent(3));
  hKshort->SetBinContent(4, (dvK06-dvK04)/(dnK06-dnK04)); hKshort->SetBinError(4, deKje * hKshort->GetBinContent(4));
  hKshort->SetBinContent(5, (dvK08-dvK06)/(dnK08-dnK06)); hKshort->SetBinError(5, deKje * hKshort->GetBinContent(5));
  hKshort->SetBinContent(6, (dvK11-dvK08)/(dnK11-dnK08)); hKshort->SetBinError(6, deKje * hKshort->GetBinContent(6));
  hKshort->SetBinContent(7, (dvK15-dvK11)/(dnK15-dnK11)); hKshort->SetBinError(7, deKje * hKshort->GetBinContent(7));

  hLambda->SetBinContent(1,  dvL02 / dnL02); hLambda->SetBinError(1, deLje * hLambda->GetBinContent(1));
/*hLambda->SetBinContent(2,  dvL03 / dnL03); hLambda->SetBinError(2, deLje * hLambda->GetBinContent(2));
  hLambda->SetBinContent(3,  dvL04 / dnL04); hLambda->SetBinError(3, deLje * hLambda->GetBinContent(3));
  hLambda->SetBinContent(4,  dvL06 / dnL06); hLambda->SetBinError(4, deLje * hLambda->GetBinContent(4));
  hLambda->SetBinContent(5,  dvL08 / dnL08); hLambda->SetBinError(5, deLje * hLambda->GetBinContent(5));
  hLambda->SetBinContent(6,  dvL11 / dnL11); hLambda->SetBinError(6, deLje * hLambda->GetBinContent(6));
  hLambda->SetBinContent(7,  dvL15 / dnL15); hLambda->SetBinError(7, deLje * hLambda->GetBinContent(7));*/
  hLambda->SetBinContent(2, (dvL03-dvL02)/(dnL03-dnL02)); hLambda->SetBinError(2, deLje * hLambda->GetBinContent(2));
  hLambda->SetBinContent(3, (dvL04-dvL03)/(dnL04-dnL03)); hLambda->SetBinError(3, deLje * hLambda->GetBinContent(3));
  hLambda->SetBinContent(4, (dvL06-dvL04)/(dnL06-dnL04)); hLambda->SetBinError(4, deLje * hLambda->GetBinContent(4));
  hLambda->SetBinContent(5, (dvL08-dvL06)/(dnL08-dnL06)); hLambda->SetBinError(5, deLje * hLambda->GetBinContent(5));
  hLambda->SetBinContent(6, (dvL11-dvL08)/(dnL11-dnL08)); hLambda->SetBinError(6, deLje * hLambda->GetBinContent(6));
  hLambda->SetBinContent(7, (dvL15-dvL11)/(dnL15-dnL11)); hLambda->SetBinError(7, deLje * hLambda->GetBinContent(7));

  hAntiLa->SetBinContent(1,  dvA02 / dnA02); hAntiLa->SetBinError(1, deAje * hAntiLa->GetBinContent(1));
/*hAntiLa->SetBinContent(2,  dvA03 / dnA03); hAntiLa->SetBinError(2, deAje * hAntiLa->GetBinContent(2));
  hAntiLa->SetBinContent(3,  dvA04 / dnA04); hAntiLa->SetBinError(3, deAje * hAntiLa->GetBinContent(3));
  hAntiLa->SetBinContent(4,  dvA06 / dnA06); hAntiLa->SetBinError(4, deAje * hAntiLa->GetBinContent(4));
  hAntiLa->SetBinContent(5,  dvA08 / dnA08); hAntiLa->SetBinError(5, deAje * hAntiLa->GetBinContent(5));
  hAntiLa->SetBinContent(6,  dvA11 / dnA11); hAntiLa->SetBinError(6, deAje * hAntiLa->GetBinContent(6));
  hAntiLa->SetBinContent(7,  dvA15 / dnA15); hAntiLa->SetBinError(7, deAje * hAntiLa->GetBinContent(7));*/
  hAntiLa->SetBinContent(2, (dvA03-dvA02)/(dnA03-dnA02)); hAntiLa->SetBinError(2, deAje * hAntiLa->GetBinContent(2));
  hAntiLa->SetBinContent(3, (dvA04-dvA03)/(dnA04-dnA03)); hAntiLa->SetBinError(3, deAje * hAntiLa->GetBinContent(3));
  hAntiLa->SetBinContent(4, (dvA06-dvA04)/(dnA06-dnA04)); hAntiLa->SetBinError(4, deAje * hAntiLa->GetBinContent(4));
  hAntiLa->SetBinContent(5, (dvA08-dvA06)/(dnA08-dnA06)); hAntiLa->SetBinError(5, deAje * hAntiLa->GetBinContent(5));
  hAntiLa->SetBinContent(6, (dvA11-dvA08)/(dnA11-dnA08)); hAntiLa->SetBinError(6, deAje * hAntiLa->GetBinContent(6));
  hAntiLa->SetBinContent(7, (dvA15-dvA11)/(dnA15-dnA11)); hAntiLa->SetBinError(7, deAje * hAntiLa->GetBinContent(7));
//=============================================================================

  TH1D *hRatioV = CalcRatioVarV0(hKshort, hLambda, hAntiLa); hRatioV->SetName(Form("hRatioV_%s",sHist.Data()));
//=============================================================================

  Double_t dErrJE=0., dErrJC = 0.;
  for (Int_t k=1; k<=hRatioV->GetNbinsX(); k++) {
    dErrJC = deKjc * hKshort->GetBinContent(k); dErrJE = hKshort->GetBinError(k); hKshort->SetBinError(k, TMath::Sqrt(dErrJC*dErrJC + dErrJE*dErrJE));
    dErrJC = deLjc * hLambda->GetBinContent(k); dErrJE = hLambda->GetBinError(k); hLambda->SetBinError(k, TMath::Sqrt(dErrJC*dErrJC + dErrJE*dErrJE));
    dErrJC = deAjc * hAntiLa->GetBinContent(k); dErrJE = hAntiLa->GetBinError(k); hAntiLa->SetBinError(k, TMath::Sqrt(dErrJC*dErrJC + dErrJE*dErrJE));
    dErrJC = deRjc * hRatioV->GetBinContent(k); dErrJE = hRatioV->GetBinError(k); hRatioV->SetBinError(k, TMath::Sqrt(dErrJC*dErrJC + dErrJE*dErrJE));
  }
//=============================================================================

  return hRatioV;
}
