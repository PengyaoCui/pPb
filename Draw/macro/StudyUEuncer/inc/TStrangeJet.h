#include "./SourceFun.h"

//-------------------------------------------------------------
TH1D* GetInclPtSpect(TString sType = "Kshort", TString sCent = "0100"){

  TString sPath = Form("/home/cuipengyao/study/pPb/Local/ThisAna/Incl/%s", sType.Data());

  TString sFile = "AnalysisOutputs_Results.root";
  TString sList = Form("listResults_%s_Default_%s", sType.Data(), sCent.Data());
  TString sHist = "hNco";

  if(sType == "Lambda" || sType == "AntiLa") sFile = "AnalysisOutputs_MakeLaFdR.root";
  if(sType == "Lambda" || sType == "AntiLa") sList = Form("listMakeLaFdR_%s_Default_%s", sType.Data(), sCent.Data());
  if(sType == "Lambda" || sType == "AntiLa") sHist = "hPtLaNormCorr";

  auto h = (TH1D*)GetTH1D(sPath.Data(), sFile.Data(), sList.Data(), sHist.Data());
  
  NormHistBinWidth(h);
  h->SetName(Form("h%s_%s", sType.Data(), sCent.Data()));

  return h;
}

//-------------------------------------------------------------
TH1D* GetPCPtSpect(TString sType = "Kshort", TString sCent = "0100", TString Path = "/home/cuipengyao/study/pPb/Local/ThisAna/JE"){

  TString sPath = Form("%s/%s", Path.Data(), sType.Data());

  TString sFile = "AnalysisOutputs_Results.root";
  TString sListL = Form("listResults_%s_Default_PCL_%s", sType.Data(), sCent.Data());
  TString sListU = Form("listResults_%s_Default_PCU_%s", sType.Data(), sCent.Data());
  TString sHist = "hNco";

  if(sType == "Lambda" || sType == "AntiLa") sFile = "AnalysisOutputs_MakeLaFdR.root";
  if(sType == "Lambda" || sType == "AntiLa") sListL = Form("listMakeLaFdR_%s_Default_PCL_%s", sType.Data(), sCent.Data());
  if(sType == "Lambda" || sType == "AntiLa") sListU = Form("listMakeLaFdR_%s_Default_PCU_%s", sType.Data(), sCent.Data());
  if(sType == "Lambda" || sType == "AntiLa") sHist = "hPtLaNormCorr";

  auto hL = (TH1D*)GetTH1D(sPath.Data(), sFile.Data(), sListL.Data(), sHist.Data());
  auto hU = (TH1D*)GetTH1D(sPath.Data(), sFile.Data(), sListU.Data(), sHist.Data());

  TH1D* h = (TH1D*)hL->Clone(Form("h%s_%s", sType.Data(), sCent.Data())); h->Reset();

  h->Add(hL, hU);
  h->Scale(0.5);
  NormHistBinWidth(h);

  return h;
}

//-------------------------------------------------------------
TH1D* GetJCPtSpect(TString sType = "Kshort", TString sCent = "0100", TString Path = "/home/cuipengyao/study/pPb/Local/ThisAna/JE"){

  TString sPath = Form("%s/%s", Path.Data(), sType.Data());
  
  TString sFile = "AnalysisOutputs_Results.root";
  TString sList = Form("listResults_%s_Default_JC_%s", sType.Data(), sCent.Data());
  TString sHist = "hNco";
  
  if(sType == "Lambda" || sType == "AntiLa") sFile = "AnalysisOutputs_MakeLaFdR.root";
  if(sType == "Lambda" || sType == "AntiLa") sList = Form("listMakeLaFdR_%s_Default_JC_%s", sType.Data(), sCent.Data());
  if(sType == "Lambda" || sType == "AntiLa") sHist = "hPtLaNormCorr";
  
  auto h = (TH1D*)GetTH1D(sPath.Data(), sFile.Data(), sList.Data(), sHist.Data());
  NormHistBinWidth(h);

  if(sType == "Lambda" || sType == "AntiLa"){
    auto hPC = GetPCPtSpect(sType, sCent, Path);
    h->Add(hPC);
  }
  h->SetName(Form("h%s_%s", sType.Data(), sCent.Data()));

  return h;
}

//-------------------------------------------------------------
TH1D* GetJEPtSpect(TString sType = "Kshort", TString sCent = "0100", TString Path = "/home/cuipengyao/study/pPb/Local/ThisAna/JE"){

  auto hPC = GetPCPtSpect(sType, sCent, Path);
  auto hJC = GetJCPtSpect(sType, sCent, Path);
  auto h = (TH1D*)hJC->Clone(Form("h%s_%s", sType.Data(), sCent.Data())); h->Reset();
  h->Add(hJC, hPC, 1., -1.);

  return h;
}



//-------------------------------------------------------------
TH1D* GetOC04PtSpect(TString sType = "Kshort", TString sCent = "0100", TString Path = "/home/cuipengyao/study/pPb/Local/ThisAna/JE"){

  TString sPath = Form("%s/%s", Path.Data(), sType.Data());

  TString sFile = "AnalysisOutputs_Results.root";
  TString sList = Form("listResults_%s_Default_OC_%s", sType.Data(), sCent.Data());
  TString sHist = "hNco";

  if(sType == "Lambda" || sType == "AntiLa") sFile = "AnalysisOutputs_MakeLaFdR.root";
  if(sType == "Lambda" || sType == "AntiLa") sList = Form("listMakeLaFdR_%s_Default_OC_%s", sType.Data(), sCent.Data());
  if(sType == "Lambda" || sType == "AntiLa") sHist = "hPtLaNormCorr";

  auto h = (TH1D*)GetTH1D(sPath.Data(), sFile.Data(), sList.Data(), sHist.Data());

  NormHistBinWidth(h);
  h->SetName(Form("h%s_%s", sType.Data(), sCent.Data()));

  return h;
}

//-------------------------------------------------------------
TH1D* GetNJPtSpect(TString sType = "Kshort", TString sCent = "0100", TString Path = "/home/cuipengyao/study/pPb/Local/ThisAna/JE"){

  TString sPath = Form("%s/%s", Path.Data(), sType.Data());

  TString sFile = "AnalysisOutputs_Results.root";
  TString sList = Form("listResults_%s_Default_NJ_%s", sType.Data(), sCent.Data());
  TString sHist = "hNco";

  if(sType == "Lambda" || sType == "AntiLa") sFile = "AnalysisOutputs_MakeLaFdR.root";
  if(sType == "Lambda" || sType == "AntiLa") sList = Form("listMakeLaFdR_%s_Default_NJ_%s", sType.Data(), sCent.Data());
  if(sType == "Lambda" || sType == "AntiLa") sHist = "hPtLaNormCorr";

  auto h = (TH1D*)GetTH1D(sPath.Data(), sFile.Data(), sList.Data(), sHist.Data());

  NormHistBinWidth(h);
  h->SetName(Form("h%s_%s", sType.Data(), sCent.Data()));

  return h;
}

//-------------------------------------------------------------
TH1D *GetInclRatioLK(TString sCent = "0100") 
{
  auto hK(GetInclPtSpect("Kshort", sCent));
  auto hL(GetInclPtSpect("Lambda", sCent));
  auto hA(GetInclPtSpect("AntiLa", sCent));
  hL->Add(hA);
//=============================================================================

  const TString sh("hLKRatio_" + sCent);
  auto hR(static_cast<TH1D*>(hL->Clone(sh.Data())));
  
  hR->Reset();
  hR->Divide(hL, hK, 1., 2.);
//=============================================================================

  return hR;
}

//-------------------------------------------------------------
TH1D *GetInclRatioXK(TString sCent = "0100")
{
  auto hK(GetInclPtSpect("Kshort", sCent));
  auto hX(GetInclPtSpect("Xi", sCent));
//=============================================================================

  const TString sh("hXKRatio_" + sCent);
  auto hR(static_cast<TH1D*>(hX->Clone(sh.Data())));

  DeNormHistBinWidth(hK);
  hK=RebinTH1D(hK, hR);
  NormHistBinWidth(hK);
  
  hR->Reset();
  hR->Divide(hX, hK, 1., 2.);
//=============================================================================

  return hR;
}

//-------------------------------------------------------------
TH1D *GetInclRatioOK(TString sCent = "0100")
{
  auto hK(GetInclPtSpect("Kshort", sCent));
  auto hO(GetInclPtSpect("Omega", sCent));
//=============================================================================

  const TString sh("hOKRatio_" + sCent);
  auto hR(static_cast<TH1D*>(hO->Clone(sh.Data())));

  DeNormHistBinWidth(hK);
  hK=RebinTH1D(hK, hR);
  NormHistBinWidth(hK);

  hR->Reset();
  hR->Divide(hO, hK, 1., 2.);
//=============================================================================

  return hR;
}

//-------------------------------------------------------------
TH1D *GetInclRatioOL(TString sCent = "0100")
{
  auto hL(GetInclPtSpect("Lambda", sCent));
  auto hA(GetInclPtSpect("AntiLa", sCent));
  auto hO(GetInclPtSpect("Omega", sCent));
//=============================================================================
  hL->Add(hA);
  const TString sh("hOLRatio_" + sCent);
  auto hR(static_cast<TH1D*>(hO->Clone(sh.Data())));

  DeNormHistBinWidth(hL);
  hL=RebinTH1D(hL, hR);
  NormHistBinWidth(hL);

  hR->Reset();
  hR->Divide(hO, hL, 1., 1.);
//=============================================================================

  return hR;
}

//-------------------------------------------------------------
TH1D *GetInclRatioXL(TString sCent = "0100")
{
  auto hL(GetInclPtSpect("Lambda", sCent));
  auto hA(GetInclPtSpect("AntiLa", sCent));
  auto hX(GetInclPtSpect("Xi", sCent));
//=============================================================================
  hL->Add(hA);
  const TString sh("hXLRatio_" + sCent);
  auto hR(static_cast<TH1D*>(hX->Clone(sh.Data())));

  DeNormHistBinWidth(hL);
  hL=RebinTH1D(hL, hR);
  NormHistBinWidth(hL);

  hR->Reset();
  hR->Divide(hX, hL, 1., 1.);
//=============================================================================

  return hR;
}

//-------------------------------------------------------------
TH1D *GetInclRatioOX(TString sCent = "0100")
{
  auto hO(GetInclPtSpect("Omega", sCent));
  auto hX(GetInclPtSpect("Xi", sCent));
//=============================================================================

  const TString sh("hOXRatio_" + sCent);
  auto hR(static_cast<TH1D*>(hO->Clone(sh.Data())));

  DeNormHistBinWidth(hX);
  hX=RebinTH1D(hX, hR);
  NormHistBinWidth(hX);

  hR->Reset();
  hR->Divide(hO, hX, 1., 1.);
//=============================================================================

  return hR;
}


//-------------------------------------------------------------
TH1D *GetJCRatioLK(TString sCent = "0100")
{
  auto hK(GetJCPtSpect("Kshort", sCent));
  auto hL(GetJCPtSpect("Lambda", sCent));
  auto hA(GetJCPtSpect("AntiLa", sCent));
//=============================================================================
  hL->Add(hA);
  const TString sh("hLKRatio_" + sCent);
  auto hR(static_cast<TH1D*>(hL->Clone(sh.Data())));

  hR->Reset();
  hR->Divide(hL, hK, 1., 2.);
//=============================================================================

  return hR;
}


//-------------------------------------------------------------
TH1D *GetJCRatioXK(TString sCent = "0100")
{
  auto hK(GetJCPtSpect("Kshort", sCent));
  auto hX(GetJCPtSpect("Xi", sCent));
//=============================================================================

  const TString sh("hXKRatio_" + sCent);
  auto hR(static_cast<TH1D*>(hX->Clone(sh.Data())));
  DeNormHistBinWidth(hK);
  hK=RebinTH1D(hK, hR);
  NormHistBinWidth(hK);

  hR->Reset();
  hR->Divide(hX, hK, 1., 2.);
//=============================================================================

  return hR;
}

//-------------------------------------------------------------
TH1D *GetJCRatioOK(TString sCent = "0100", TString Path = "/home/cuipengyao/study/pPb/Local/ThisAna/JE_OmegaBins")
{
  auto hK(GetJCPtSpect("Kshort", sCent, Path));
  auto hO(GetJCPtSpect("Omega", sCent, Path));
//=============================================================================

  const TString sh("hOKRatio_" + sCent);
  auto hR(static_cast<TH1D*>(hO->Clone(sh.Data())));
  DeNormHistBinWidth(hK);
  hK=RebinTH1D(hK, hR);
  NormHistBinWidth(hK);

  hR->Reset();
  hR->Divide(hO, hK, 1., 2.);
//=============================================================================

  return hR;
}

//-------------------------------------------------------------
TH1D *GetJCRatioXL(TString sCent = "0100")
{
  auto hL(GetJCPtSpect("Lambda", sCent));
  auto hA(GetJCPtSpect("AntiLa", sCent));
  auto hX(GetJCPtSpect("Xi", sCent));
//=============================================================================
  hL->Add(hA);
  const TString sh("hXLRatio_" + sCent);
  auto hR(static_cast<TH1D*>(hX->Clone(sh.Data())));
  DeNormHistBinWidth(hL);
  hL=RebinTH1D(hL, hR);
  NormHistBinWidth(hL);

  hR->Reset();
  hR->Divide(hX, hL, 1., 1.);
//=============================================================================

  return hR;
}

//-------------------------------------------------------------
TH1D *GetJCRatioOL(TString sCent = "0100", TString Path = "/home/cuipengyao/study/pPb/Local/ThisAna/JE_OmegaBins")
{
  auto hL(GetJCPtSpect("Lambda", sCent, Path));
  auto hA(GetJCPtSpect("AntiLa", sCent, Path));
  auto hO(GetJCPtSpect("Omega", sCent, Path));
//=============================================================================
  hL->Add(hA);
  const TString sh("hOLRatio_" + sCent);
  auto hR(static_cast<TH1D*>(hO->Clone(sh.Data())));
  DeNormHistBinWidth(hL);
  hL=RebinTH1D(hL, hR);
  NormHistBinWidth(hL);

  hR->Reset();
  hR->Divide(hO, hL, 1., 1.);
//=============================================================================

  return hR;
}

//-------------------------------------------------------------
TH1D *GetJCRatioOX(TString sCent = "0100", TString Path = "/home/cuipengyao/study/pPb/Local/ThisAna/JE_OmegaBins")
{
  auto hX(GetJCPtSpect("Xi", sCent, Path));
  auto hO(GetJCPtSpect("Omega", sCent, Path));
//=============================================================================

  const TString sh("hOXRatio_" + sCent);
  auto hR(static_cast<TH1D*>(hO->Clone(sh.Data())));
  
  DeNormHistBinWidth(hX);
  hX=RebinTH1D(hX, hR);
  NormHistBinWidth(hX);

  hR->Reset();
  hR->Divide(hO, hX, 1., 1.);
//=============================================================================

  return hR;
}

//-------------------------------------------------------------
TH1D *GetPCRatioLK(TString sCent = "0100")
{
  auto hK(GetPCPtSpect("Kshort", sCent));
  auto hL(GetPCPtSpect("Lambda", sCent));
  auto hA(GetPCPtSpect("AntiLa", sCent));
//=============================================================================
  hL->Add(hA);

  const TString sh("hLKRatio_" + sCent);
  auto hR(static_cast<TH1D*>(hL->Clone(sh.Data())));

  hR->Reset();
  hR->Divide(hL, hK, 1., 2.);
//=============================================================================

  return hR;
}


//-------------------------------------------------------------
TH1D *GetPCRatioXK(TString sCent = "0100")
{
  auto hK(GetPCPtSpect("Kshort", sCent));
  auto hX(GetPCPtSpect("Xi", sCent));
//=============================================================================

  const TString sh("hXKRatio_" + sCent);
  auto hR(static_cast<TH1D*>(hX->Clone(sh.Data())));
  DeNormHistBinWidth(hK);
  hK=RebinTH1D(hK, hR);
  NormHistBinWidth(hK);

  hR->Reset();
  hR->Divide(hX, hK, 1., 2.);
//=============================================================================

  return hR;
}

//-------------------------------------------------------------
TH1D *GetPCRatioOK(TString sCent = "0100", TString Path = "/home/cuipengyao/study/pPb/Local/ThisAna/JE_OmegaBins")
{
  auto hK(GetPCPtSpect("Kshort", sCent, Path));
  auto hO(GetPCPtSpect("Omega", sCent, Path));
//=============================================================================

  const TString sh("hOKRatio_" + sCent);
  auto hR(static_cast<TH1D*>(hO->Clone(sh.Data())));
  DeNormHistBinWidth(hK);
  hK=RebinTH1D(hK, hR);
  NormHistBinWidth(hK);

  hR->Reset();
  hR->Divide(hO, hK, 1., 2.);
//=============================================================================

  return hR;
}

//-------------------------------------------------------------
TH1D *GetPCRatioXL(TString sCent = "0100")
{
  auto hL(GetPCPtSpect("Lambda", sCent));
  auto hA(GetPCPtSpect("AntiLa", sCent));
  auto hX(GetPCPtSpect("Xi", sCent));
//=============================================================================
  hL->Add(hA);
  
  const TString sh("hXLRatio_" + sCent);
  auto hR(static_cast<TH1D*>(hX->Clone(sh.Data())));
  DeNormHistBinWidth(hL);
  hL=RebinTH1D(hL, hR);
  NormHistBinWidth(hL);

  hR->Reset();
  hR->Divide(hX, hL, 1., 1.);
//=============================================================================

  return hR;
}

//-------------------------------------------------------------
TH1D *GetPCRatioOL(TString sCent = "0100", TString Path = "/home/cuipengyao/study/pPb/Local/ThisAna/JE_OmegaBins")
{
  auto hL(GetPCPtSpect("Lambda", sCent, Path));
  auto hA(GetPCPtSpect("AntiLa", sCent, Path));
  auto hO(GetPCPtSpect("Omega", sCent, Path));
//=============================================================================
  hL->Add(hA);

  const TString sh("hOLRatio_" + sCent);
  auto hR(static_cast<TH1D*>(hO->Clone(sh.Data())));
  DeNormHistBinWidth(hL);
  hL=RebinTH1D(hL, hR);
  NormHistBinWidth(hL);

  hR->Reset();
  hR->Divide(hO, hL, 1., 1.);
//=============================================================================

  return hR;
}

//-------------------------------------------------------------
TH1D *GetPCRatioOX(TString sCent = "0100", TString Path = "/home/cuipengyao/study/pPb/Local/ThisAna/JE_OmegaBins")
{
  auto hX(GetPCPtSpect("Xi", sCent, Path));
  auto hO(GetPCPtSpect("Omega", sCent, Path));
//=============================================================================

  const TString sh("hOXRatio_" + sCent);
  auto hR(static_cast<TH1D*>(hO->Clone(sh.Data())));
  
  DeNormHistBinWidth(hX);
  hX=RebinTH1D(hX, hR);
  NormHistBinWidth(hX);

  hR->Reset();
  hR->Divide(hO, hX, 1., 1.);
//=============================================================================

  return hR;
}

//-------------------------------------------------------------
TH1D *GetJERatioLK(TString sCent = "0100")
{
  auto hK(GetJEPtSpect("Kshort", sCent));
  auto hL(GetJEPtSpect("Lambda", sCent));
  auto hA(GetJEPtSpect("AntiLa", sCent));
  hL->Add(hA);
//=============================================================================

  const TString sh("hLKRatio_" + sCent);
  auto hR(static_cast<TH1D*>(hL->Clone(sh.Data())));

  hR->Reset();
  hR->Divide(hL, hK, 1., 2.);
//=============================================================================

  return hR;
}


//-------------------------------------------------------------
TH1D *GetJERatioXK(TString sCent = "0100")
{
  auto hK(GetJEPtSpect("Kshort", sCent));
  auto hX(GetJEPtSpect("Xi", sCent));
//=============================================================================

  const TString sh("hXKRatio_" + sCent);
  auto hR(static_cast<TH1D*>(hX->Clone(sh.Data())));
  DeNormHistBinWidth(hK);
  hK=RebinTH1D(hK, hR);
  NormHistBinWidth(hK);

  hR->Reset();
  hR->Divide(hX, hK, 1., 2.);
//=============================================================================

  return hR;
}

//-------------------------------------------------------------
TH1D *GetJERatioOK(TString sCent = "0100", TString Path = "/home/cuipengyao/study/pPb/Local/ThisAna/JE_OmegaBins")
{
  auto hK(GetJEPtSpect("Kshort", sCent, Path));
  auto hO(GetJEPtSpect("Omega", sCent, Path));
//=============================================================================

  const TString sh("hOKRatio_" + sCent);
  auto hR(static_cast<TH1D*>(hO->Clone(sh.Data())));
  DeNormHistBinWidth(hK);
  hK=RebinTH1D(hK, hR);
  NormHistBinWidth(hK);

  hR->Reset();
  hR->Divide(hO, hK, 1., 2.);
//=============================================================================

  return hR;
}

//-------------------------------------------------------------
TH1D *GetJERatioXL(TString sCent = "0100")
{
  auto hL(GetJEPtSpect("Lambda", sCent));
  auto hA(GetJEPtSpect("AntiLa", sCent));
  auto hX(GetJEPtSpect("Xi", sCent));
//=============================================================================
  hL->Add(hA);

  const TString sh("hXLRatio_" + sCent);
  auto hR(static_cast<TH1D*>(hX->Clone(sh.Data())));
  DeNormHistBinWidth(hL);
  hL=RebinTH1D(hL, hR);
  NormHistBinWidth(hL);

  hR->Reset();
  hR->Divide(hX, hL, 1., 1.);
//=============================================================================

  return hR;
}

//-------------------------------------------------------------
TH1D *GetJERatioOL(TString sCent = "0100", TString Path = "/home/cuipengyao/study/pPb/Local/ThisAna/JE_OmegaBins")
{
  auto hL(GetJEPtSpect("Lambda", sCent, Path));
  auto hA(GetJEPtSpect("AntiLa", sCent, Path));
  auto hO(GetJEPtSpect("Omega", sCent, Path));
//=============================================================================
  hL->Add(hA);

  const TString sh("hOLRatio_" + sCent);
  auto hR(static_cast<TH1D*>(hO->Clone(sh.Data())));
  DeNormHistBinWidth(hL);
  hL=RebinTH1D(hL, hR);
  NormHistBinWidth(hL);

  hR->Reset();
  hR->Divide(hO, hL, 1., 1.);
//=============================================================================

  return hR;
}

//-------------------------------------------------------------
TH1D *GetJERatioOX(TString sCent = "0100", TString Path = "/home/cuipengyao/study/pPb/Local/ThisAna/JE_OmegaBins")
{
  auto hX(GetJEPtSpect("Xi", sCent, Path));
  auto hO(GetJEPtSpect("Omega", sCent, Path));
//=============================================================================

  const TString sh("hOXRatio_" + sCent);
  auto hR(static_cast<TH1D*>(hO->Clone(sh.Data())));
  
  DeNormHistBinWidth(hX);
  hX=RebinTH1D(hX, hR);
  NormHistBinWidth(hX);

  hR->Reset();
  hR->Divide(hO, hX, 1., 1.);
//=============================================================================

  return hR;
}

//-------------------------------------------------------------
TH1D *GetOC04RatioLK(TString sCent = "0100")
{
  auto hK(GetOC04PtSpect("Kshort", sCent));
  auto hL(GetOC04PtSpect("Lambda", sCent));
  auto hA(GetOC04PtSpect("AntiLa", sCent));
//=============================================================================
  hL->Add(hA);

  const TString sh("hLKRatio_" + sCent);
  auto hR(static_cast<TH1D*>(hL->Clone(sh.Data())));

  hR->Reset();
  hR->Divide(hL, hK, 1., 2.);
//=============================================================================

  return hR;
}


//-------------------------------------------------------------
TH1D *GetOC04RatioXK(TString sCent = "0100")
{
  auto hK(GetOC04PtSpect("Kshort", sCent));
  auto hX(GetOC04PtSpect("Xi", sCent));
//=============================================================================

  const TString sh("hXKRatio_" + sCent);
  auto hR(static_cast<TH1D*>(hX->Clone(sh.Data())));
  DeNormHistBinWidth(hK);
  hK=RebinTH1D(hK, hR);
  NormHistBinWidth(hK);

  hR->Reset();
  hR->Divide(hX, hK, 1., 2.);
//=============================================================================

  return hR;
}

//-------------------------------------------------------------
TH1D *GetOC04RatioOK(TString sCent = "0100", TString Path = "/home/cuipengyao/study/pPb/Local/ThisAna/JE_OmegaBins")
{
  auto hK(GetOC04PtSpect("Kshort", sCent, Path));
  auto hO(GetOC04PtSpect("Omega", sCent, Path));
//=============================================================================

  const TString sh("hOKRatio_" + sCent);
  auto hR(static_cast<TH1D*>(hO->Clone(sh.Data())));
  DeNormHistBinWidth(hK);
  hK=RebinTH1D(hK, hR);
  NormHistBinWidth(hK);

  hR->Reset();
  hR->Divide(hO, hK, 1., 2.);
//=============================================================================

  return hR;
}

//-------------------------------------------------------------
TH1D *GetOC04RatioXL(TString sCent = "0100")
{
  auto hL(GetOC04PtSpect("Lambda", sCent));
  auto hA(GetOC04PtSpect("AntiLa", sCent));
  auto hX(GetOC04PtSpect("Xi", sCent));
//=============================================================================
  hL->Add(hA);

  const TString sh("hXLRatio_" + sCent);
  auto hR(static_cast<TH1D*>(hX->Clone(sh.Data())));
  DeNormHistBinWidth(hL);
  hL=RebinTH1D(hL, hR);
  NormHistBinWidth(hL);

  hR->Reset();
  hR->Divide(hX, hL, 1., 1.);
//=============================================================================

  return hR;
}

//-------------------------------------------------------------
TH1D *GetOC04RatioOL(TString sCent = "0100", TString Path = "/home/cuipengyao/study/pPb/Local/ThisAna/JE_OmegaBins")
{
  auto hL(GetOC04PtSpect("Lambda", sCent, Path));
  auto hA(GetOC04PtSpect("AntiLa", sCent, Path));
  auto hO(GetOC04PtSpect("Omega", sCent, Path));
//=============================================================================
  hL->Add(hA);

  const TString sh("hOLRatio_" + sCent);
  auto hR(static_cast<TH1D*>(hO->Clone(sh.Data())));
  DeNormHistBinWidth(hL);
  hL=RebinTH1D(hL, hR);
  NormHistBinWidth(hL);

  hR->Reset();
  hR->Divide(hO, hL, 1., 1.);
//=============================================================================

  return hR;
}

//-------------------------------------------------------------
TH1D *GetOC04RatioOX(TString sCent = "0100", TString Path = "/home/cuipengyao/study/pPb/Local/ThisAna/JE_OmegaBins")
{
  auto hX(GetOC04PtSpect("Xi", sCent, Path));
  auto hO(GetOC04PtSpect("Omega", sCent, Path));
//=============================================================================

  const TString sh("hOXRatio_" + sCent);
  auto hR(static_cast<TH1D*>(hO->Clone(sh.Data())));
  
  DeNormHistBinWidth(hX);
  hX=RebinTH1D(hX, hR);
  NormHistBinWidth(hX);

  hR->Reset();
  hR->Divide(hO, hX, 1., 1.);
//=============================================================================

  return hR;
}

//-------------------------------------------------------------
TH1D *GetNJRatioLK(TString sCent = "0100")
{
  auto hK(GetNJPtSpect("Kshort", sCent));
  auto hL(GetNJPtSpect("Lambda", sCent));
  auto hA(GetNJPtSpect("AntiLa", sCent));
//=============================================================================
  hL->Add(hA);

  const TString sh("hLKRatio_" + sCent);
  auto hR(static_cast<TH1D*>(hL->Clone(sh.Data())));

  hR->Reset();
  hR->Divide(hL, hK, 1., 2.);
//=============================================================================

  return hR;
}


//-------------------------------------------------------------
TH1D *GetNJRatioXK(TString sCent = "0100")
{
  auto hK(GetNJPtSpect("Kshort", sCent));
  auto hX(GetNJPtSpect("Xi", sCent));
//=============================================================================

  const TString sh("hXKRatio_" + sCent);
  auto hR(static_cast<TH1D*>(hX->Clone(sh.Data())));
  DeNormHistBinWidth(hK);
  hK=RebinTH1D(hK, hR);
  NormHistBinWidth(hK);

  hR->Reset();
  hR->Divide(hX, hK, 1., 2.);
//=============================================================================

  return hR;
}

//-------------------------------------------------------------
TH1D *GetNJRatioOK(TString sCent = "0100", TString Path = "/home/cuipengyao/study/pPb/Local/ThisAna/JE_OmegaBins")
{
  auto hK(GetNJPtSpect("Kshort", sCent, Path));
  auto hO(GetNJPtSpect("Omega", sCent, Path));
//=============================================================================

  const TString sh("hOKRatio_" + sCent);
  auto hR(static_cast<TH1D*>(hO->Clone(sh.Data())));
  DeNormHistBinWidth(hK);
  hK=RebinTH1D(hK, hR);
  NormHistBinWidth(hK);

  hR->Reset();
  hR->Divide(hO, hK, 1., 2.);
//=============================================================================

  return hR;
}

//-------------------------------------------------------------
TH1D *GetNJRatioXL(TString sCent = "0100")
{
  auto hL(GetNJPtSpect("Lambda", sCent));
  auto hA(GetNJPtSpect("AntiLa", sCent));
  auto hX(GetNJPtSpect("Xi", sCent));
//=============================================================================
  hL->Add(hA);

  const TString sh("hXLRatio_" + sCent);
  auto hR(static_cast<TH1D*>(hX->Clone(sh.Data())));
  DeNormHistBinWidth(hL);
  hL=RebinTH1D(hL, hR);
  NormHistBinWidth(hL);

  hR->Reset();
  hR->Divide(hX, hL, 1., 1.);
//=============================================================================

  return hR;
}

//-------------------------------------------------------------
TH1D *GetNJRatioOL(TString sCent = "0100", TString Path = "/home/cuipengyao/study/pPb/Local/ThisAna/JE_OmegaBins")
{
  auto hL(GetNJPtSpect("Lambda", sCent, Path));
  auto hA(GetNJPtSpect("AntiLa", sCent, Path));
  auto hO(GetNJPtSpect("Omega", sCent, Path));
//=============================================================================

  hL->Add(hA);
  const TString sh("hOLRatio_" + sCent);
  auto hR(static_cast<TH1D*>(hO->Clone(sh.Data())));
  DeNormHistBinWidth(hL);
  hL=RebinTH1D(hL, hR);
  NormHistBinWidth(hL);

  hR->Reset();
  hR->Divide(hO, hL, 1., 1.);
//=============================================================================

  return hR;
}

//-------------------------------------------------------------
TH1D *GetNJRatioOX(TString sCent = "0100", TString Path = "/home/cuipengyao/study/pPb/Local/ThisAna/JE_OmegaBins")
{
  auto hX(GetNJPtSpect("Xi", sCent, Path));
  auto hO(GetNJPtSpect("Omega", sCent, Path));
//=============================================================================

  const TString sh("hOXRatio_" + sCent);
  auto hR(static_cast<TH1D*>(hO->Clone(sh.Data())));
  
  DeNormHistBinWidth(hX);
  hX=RebinTH1D(hX, hR);
  NormHistBinWidth(hX);

  hR->Reset();
  hR->Divide(hO, hX, 1., 1.);
//=============================================================================

  return hR;
}

TH1D* RebinToOmega(TH1D* hPar, TH1D* hOmega){

  Double_t dBin[] = {0.6, 2.2, 2.8, 3.7, 5.};
  TH1D* h0 = new TH1D(Form("%s_%s", hPar->GetName(), hOmega->GetName()), "", sizeof(dBin)/sizeof(Double_t)-1, dBin);
  DeNormHistBinWidth(hPar);
  hPar = RebinTH1D(hPar, h0);
  NormHistBinWidth(hPar);

  TH1D* h = (TH1D*)hOmega->Clone(Form("h_%s_%s", hPar->GetName(), hOmega->GetName())); h->Reset();
  for(Int_t i = 1; i<= h->GetNbinsX(); i++){
    h->SetBinContent(i, hPar->GetBinContent(i)); 
    h->SetBinError(i, hPar->GetBinError(i)); 
  }
  return h;
} 
//_____________________________________________________________________________

