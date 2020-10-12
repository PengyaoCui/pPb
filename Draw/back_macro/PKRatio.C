#include "./SourceFun.h"

void PKRatio(){


  TString sPath = "./result";
  //TString sFile = "PtSpect_ThisAna_TestPCL.root";
  TString sPist = "";
 
  TString SaveName = "XKRatio"; 
  TString sFile[] = {"PtSpect_ThisAna_TestPCL.root", "PtSpect_ThisAna_TestPCL.root"};
  TString sK[] = {"hPtIncl_Kshort", "hPtPC_Kshort"};
  TString sP[] = {"hPtIncl_Xi",     "hPtPC_Xi"};
  TString sA[] = {"hPtIncl_Xi",     "hPtPC_Xi"};
 
  //TString sCent[] = {"0100", "010", "1040", "40100"};
  //TString sLeg[] = {"0100", "0-10%", "10-40%", "40-100%"};
  TString sCent[] = {"1100", "1100"};
  TString sLeg[] = {"Incl", "PC"};
  //TString sCent[] = {"40100"}; 
  //TString sLeg[] = {"Incl", "JE", "PC", "OC", "NJ"};

  auto sLatex("#Xi to K^{0}_{S} ratio");
  auto sTex("1-100%");
  Double_t XMin = 0.; Double_t XMax = 8.;
  Double_t YMin = 0.; Double_t YMax = 0.3;
  //-----------------------------------
 
  TCanvas *can = nullptr;
  TLatex* tex = nullptr;
  TLegend *leg = nullptr;

  //TFile *f = TFile::Open("./result/PKRatio.root", "UPDATE");
  can = MakeCanvas("can");

  leg = new TLegend(0.6,0.85,1.0,0.65); SetLegend(leg);
  //-----------------------------------
  auto nHist = sizeof(sCent)/sizeof(TString);
  
  TH1D* hP = nullptr;
  TH1D* hA = nullptr;
  TH1D* hK = nullptr;
  TH1D* hRatio = nullptr;

  //Double_t dBin[] = {0.6, 0.7, 0.8, 0.9, 1.0, 1.1, 1.2, 1.4, 1.6, 1.8, 2.0, 2.2, 2.4, 2.6, 2.8, 4.2, 6.0, 8.0};
  //Int_t nBin = sizeof(dBin)/sizeof(Double_t) - 1;
  //auto *h = new TH1D("h", "", nBin, dBin);

  //for (Int_t i = 0; i< nHist; ++i){
  for (Int_t i = 0; i< 1; ++i){
    for(Int_t j = 0; j< sizeof(sK)/sizeof(TString); ++j){
      TString sMyPath = sPath; 
      //TString sMyFile = sFile; 
      TString sMyFile = sFile[j]; 
      TString sMyList = sPist; 
      TString sMyHistL = Form("%s_%s", sP[j].Data(), sCent[j].Data()); 
      TString sMyHistA = Form("%s_%s", sA[j].Data(), sCent[j].Data()); 
      TString sMyHistK = Form("%s_%s", sK[j].Data(), sCent[j].Data()); 
      
      hP = (TH1D*)GetTH1D(sMyPath.Data(), sMyFile.Data(), sMyList.Data(), sMyHistL.Data());
      hP->SetName(Form("Par_%d%d", i, j)); 
      //hP=RebinTH1D(hP, h);
      DeNormHistBinWidth(hP); 
      
      hA = (TH1D*)GetTH1D(sMyPath.Data(), sMyFile.Data(), sMyList.Data(), sMyHistA.Data());
      hA->SetName(Form("AntiPa_%d%d", i, j)); 
      DeNormHistBinWidth(hA); 
      hA=RebinTH1D(hA, hP);
      hP->Add(hA);

      hK = (TH1D*)GetTH1D(sMyPath.Data(), sMyFile.Data(), sMyList.Data(), sMyHistK.Data());
      hK->SetName(Form("Kshort_%d%d", i, j)); 
      DeNormHistBinWidth(hK); 
      hK=RebinTH1D(hK, hP);
      hK->Scale(4.); 
      
      hRatio = (TH1D*) hK->Clone(Form("hRatio_%d%d", i, j)); hRatio->Reset();
      hRatio->Divide(hP, hK);
      hRatio->SetName(Form("hratio_%d%d", i, j));
      //f->cd(); hRatio->Write(Form("%s_%s_%s", SaveName.Data(), sP[j].Data(), sCent[i].Data()), TObject::kSingleKey);
      
      auto dMini = hRatio->GetMinimum();
      auto dMaxi = hRatio->GetMaximum();
      //hRatio->GetYaxis()->SetRangeUser(0.8*dMini, 1.2*dMaxi);
      hRatio->GetXaxis()->SetRangeUser(XMin, XMax);
      hRatio->GetYaxis()->SetRangeUser(YMin, YMax);
      //DrawHisto(hRatio, cLine[i], sMark[i], "same");
      //leg->AddEntry(hRatio, sLeg[i], "lp");
      DrawHisto(hRatio, cLine[j], sMark[j], "same");
      leg->AddEntry(hRatio, sLeg[j], "lp");
      SetFrame(hRatio, "#it{p}_{T} (GeV/#it{c})", "#frac{#Xi + #bar{#Xi}}{2K^{0}_{S}}");
    }
  }
  //f->Close();
  tex =  new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.16, 0.9, sLatex);
  tex->DrawLatex(0.7, 0.9, sTex);
  leg->Draw();
  gStyle->SetOptStat("");
  CanvasEnd(can);
  //can->SaveAs(Form("./figure/ThisAna/XitoKshortRatio_%s_woUncertainty_TestPCL.eps", sCent[0].Data()));
  return;
}
