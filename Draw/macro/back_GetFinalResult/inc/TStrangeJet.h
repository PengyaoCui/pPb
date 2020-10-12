#include "./SourceFun.h"
//-------------------------------------------------------------
TH1D* GetInclPtSpect(TString sType = "Kshort", TString sCent = "0100"){

  TString sPath = Form("/home/cuipengyao/study/pPb/Local/ThisAna/Incl/%s", sType.Data());

  TString sFile = "AnalysisOutputs_Results.root";
  TString sList = Form("listResults_%s_Default_%s", sType.Data(), sCent.Data());
  TString sHist = "hNco";

  if(sType == "Lambda") sFile = "AnalysisOutputs_MakeLaFdR.root";
  if(sType == "Lambda") sList = Form("listMakeLaFdR_%s_Default_%s", sType.Data(), sCent.Data());
  if(sType == "Lambda") sHist = "hPtLaNormCorr";

  auto h = (TH1D*)GetTH1D(sPath.Data(), sFile.Data(), sList.Data(), sHist.Data());
  if(sType == "Lambda"){
    auto hA = (TH1D*)GetTH1D(sPath.Data(), sFile.Data(), Form("listMakeLaFdR_AntiLa_Default_%s", sCent.Data()), sHist.Data());
    h->Add(hA);
  }
  NormHistBinWidth(h);
  h->SetName(Form("%s_%s", sType.Data(), sCent.Data()));

  return h;
}
//-------------------------------------------------------------
TH1D* GetPCPtSpect(TString sType = "Kshort", TString sCent = "0100"){

  TString sPath = Form("/home/cuipengyao/study/pPb/Local/ThisAna/JE/%s", sType.Data());

  TString sFile = "AnalysisOutputs_Results.root";
  TString sListL = Form("listResults_%s_Default_PCL_%s", sType.Data(), sCent.Data());
  TString sListU = Form("listResults_%s_Default_PCU_%s", sType.Data(), sCent.Data());
  TString sHist = "hNco";

  if(sType == "Lambda") sFile = "AnalysisOutputs_MakeLaFdR.root";
  if(sType == "Lambda") sListL = Form("listMakeLaFdR_%s_Default_PCL_%s", sType.Data(), sCent.Data());
  if(sType == "Lambda") sListU = Form("listMakeLaFdR_%s_Default_PCU_%s", sType.Data(), sCent.Data());
  if(sType == "Lambda") sHist = "hPtLaNormCorr";

  auto hL = (TH1D*)GetTH1D(sPath.Data(), sFile.Data(), sListL.Data(), sHist.Data());
  auto hU = (TH1D*)GetTH1D(sPath.Data(), sFile.Data(), sListU.Data(), sHist.Data());

  if(sType == "Lambda"){
    auto hAL = (TH1D*)GetTH1D(sPath.Data(), sFile.Data(), Form("listMakeLaFdR_AntiLa_Default_PCL_%s", sCent.Data()), sHist.Data());
    auto hAU = (TH1D*)GetTH1D(sPath.Data(), sFile.Data(), Form("listMakeLaFdR_AntiLa_Default_PCU_%s", sCent.Data()), sHist.Data());
    hL->Add(hAL);
    hU->Add(hAU);
  }
  TH1D* h = (TH1D*)hL->Clone(Form("%s_%s", sType.Data(), sCent.Data())); h->Reset();

  h->Add(hL, hU);
  h->Scale(0.5);
  NormHistBinWidth(h);

  return h;
}



//-------------------------------------------------------------
TH1D* GetJCPtSpect(TString sType = "Kshort", TString sCent = "0100"){
  
  TString sPath = Form("/home/cuipengyao/study/pPb/Local/ThisAna/JE/%s", sType.Data());
  
  TString sFile = "AnalysisOutputs_Results.root";
  TString sList = Form("listResults_%s_Default_JC_%s", sType.Data(), sCent.Data());
  TString sHist = "hNco";
  
  if(sType == "Lambda") sFile = "AnalysisOutputs_MakeLaFdR.root";
  if(sType == "Lambda") sList = Form("listMakeLaFdR_%s_Default_JC_%s", sType.Data(), sCent.Data());
  if(sType == "Lambda") sHist = "hPtLaNormCorr";
  
  auto h = (TH1D*)GetTH1D(sPath.Data(), sFile.Data(), sList.Data(), sHist.Data());
  NormHistBinWidth(h);

  if(sType == "Lambda"){
    auto hA = (TH1D*)GetTH1D(sPath.Data(), sFile.Data(), Form("listMakeLaFdR_AntiLa_Default_JC_%s", sCent.Data()), sHist.Data());
    NormHistBinWidth(hA);
    h->Add(hA);
    auto hPC = GetPCPtSpect(sType, sCent);
    h->Add(hPC);
  }
  h->SetName(Form("%s_%s", sType.Data(), sCent.Data()));

  return h;
}

//-------------------------------------------------------------
TH1D* GetJEPtSpect(TString sType = "Kshort", TString sCent = "0100"){
  
  auto hPC = GetPCPtSpect(sType, sCent);
  auto hJC = GetJCPtSpect(sType, sCent);
  auto h = (TH1D*)hJC->Clone(Form("%s_%s", sType.Data(), sCent.Data())); h->Reset();
  h->Add(hJC, hPC, 1., -1.);

  return h;
}



//-------------------------------------------------------------
TH1D* GetOC04PtSpect(TString sType = "Kshort", TString sCent = "0100"){

  TString sPath = Form("/home/cuipengyao/study/pPb/Local/ThisAna/JE/%s", sType.Data());

  TString sFile = "AnalysisOutputs_Results.root";
  TString sList = Form("listResults_%s_Default_OC_%s", sType.Data(), sCent.Data());
  TString sHist = "hNco";

  if(sType == "Lambda") sFile = "AnalysisOutputs_MakeLaFdR.root";
  if(sType == "Lambda") sList = Form("listMakeLaFdR_%s_Default_OC_%s", sType.Data(), sCent.Data());
  if(sType == "Lambda") sHist = "hPtLaNormCorr";

  auto h = (TH1D*)GetTH1D(sPath.Data(), sFile.Data(), sList.Data(), sHist.Data());

  if(sType == "Lambda"){
    auto hA = (TH1D*)GetTH1D(sPath.Data(), sFile.Data(), Form("listMakeLaFdR_AntiLa_Default_OC_%s", sCent.Data()), sHist.Data());
    h->Add(hA);
  }
  NormHistBinWidth(h);
  h->SetName(Form("%s_%s", sType.Data(), sCent.Data()));

  return h;
}

//-------------------------------------------------------------
TH1D* GetOC06PtSpect(TString sType = "Kshort", TString sCent = "0100"){

  TString sPath = Form("/home/cuipengyao/study/pPb/Local/ThisAna/Uncertainty/JE/UE/OC06");

  TString sFile = "AnalysisOutputs_Results.root";
  TString sList = Form("listResults_%s_Default_OC_%s", sType.Data(), sCent.Data());
  TString sHist = "hNco";

  if(sType == "Lambda") sFile = "AnalysisOutputs_MakeLaFdR.root";
  if(sType == "Lambda") sList = Form("listMakeLaFdR_%s_Default_OC_%s", sType.Data(), sCent.Data());
  if(sType == "Lambda") sHist = "hPtLaNormCorr";

  auto h = (TH1D*)GetTH1D(sPath.Data(), sFile.Data(), sList.Data(), sHist.Data());

  if(sType == "Lambda"){
    auto hA = (TH1D*)GetTH1D(sPath.Data(), sFile.Data(), Form("listMakeLaFdR_AntiLa_Default_OC_%s", sCent.Data()), sHist.Data());
    h->Add(hA);
  }
  NormHistBinWidth(h);
  h->SetName(Form("%s_%s", sType.Data(), sCent.Data()));

  return h;
}

//-------------------------------------------------------------
TH1D* GetOC08PtSpect(TString sType = "Kshort", TString sCent = "0100"){

  TString sPath = Form("/home/cuipengyao/study/pPb/Local/ThisAna/Uncertainty/JE/UE/OC08");

  TString sFile = "AnalysisOutputs_Results.root";
  TString sList = Form("listResults_%s_Default_OC_%s", sType.Data(), sCent.Data());
  TString sHist = "hNco";

  if(sType == "Lambda") sFile = "AnalysisOutputs_MakeLaFdR.root";
  if(sType == "Lambda") sList = Form("listMakeLaFdR_%s_Default_OC_%s", sType.Data(), sCent.Data());
  if(sType == "Lambda") sHist = "hPtLaNormCorr";

  auto h = (TH1D*)GetTH1D(sPath.Data(), sFile.Data(), sList.Data(), sHist.Data());

  if(sType == "Lambda"){
    auto hA = (TH1D*)GetTH1D(sPath.Data(), sFile.Data(), Form("listMakeLaFdR_AntiLa_Default_OC_%s", sCent.Data()), sHist.Data());
    h->Add(hA);
  }
  NormHistBinWidth(h);
  h->SetName(Form("%s_%s", sType.Data(), sCent.Data()));

  return h;
}

//-------------------------------------------------------------
TH1D* GetNJPtSpect(TString sType = "Kshort", TString sCent = "0100"){

  TString sPath = Form("/home/cuipengyao/study/pPb/Local/ThisAna/JE/%s", sType.Data());

  TString sFile = "AnalysisOutputs_Results.root";
  TString sList = Form("listResults_%s_Default_NJ_%s", sType.Data(), sCent.Data());
  TString sHist = "hNco";

  if(sType == "Lambda") sFile = "AnalysisOutputs_MakeLaFdR.root";
  if(sType == "Lambda") sList = Form("listMakeLaFdR_%s_Default_NJ_%s", sType.Data(), sCent.Data());
  if(sType == "Lambda") sHist = "hPtLaNormCorr";

  auto h = (TH1D*)GetTH1D(sPath.Data(), sFile.Data(), sList.Data(), sHist.Data());

  if(sType == "Lambda"){
    auto hA = (TH1D*)GetTH1D(sPath.Data(), sFile.Data(), Form("listMakeLaFdR_AntiLa_Default_NJ_%s", sCent.Data()), sHist.Data());
    h->Add(hA);
  }
  NormHistBinWidth(h);
  h->SetName(Form("%s_%s", sType.Data(), sCent.Data()));

  return h;
}

