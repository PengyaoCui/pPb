#include "./SourceFun.h"

void draw_PtSpect(TString sType = "Xi", TString sCent = "", TString sCone = "JE"){
  auto Path = "./result";
  auto File = "PtSpect_ThisAna.root";

  Bool_t IsSaveCan = kTRUE;
  //TString sCone = "";// Incl; PC; JE; JC
  //TString sCent = "010";// 010; 1040; 40100; 0100;
 
 //===============The same cone with different centrality 
  TString sPath[] = {Path, Path, Path, Path};
  TString sFile[] = {File, File, File, File};
  TString sList[] = {"", "", "", ""};
  TString sHist[] = {Form("hPt%s_%s_010",   sCone.Data(), sType.Data()), 
	             Form("hPt%s_%s_1040",  sCone.Data(), sType.Data()), 
		     Form("hPt%s_%s_40100", sCone.Data(), sType.Data())};
  if(sCone == "JE" && (sType == "Lambda" || sType == "AntiLa")){
    sHist[0] = Form("hPtJC_%s_010",   sType.Data());
    sHist[1] = Form("hPtJC_%s_1040",  sType.Data());
    sHist[2] = Form("hPtJC_%s_40100", sType.Data());
  }
  TString sLeg[] = {"0-10%", "10-40%", "40-100%"}; 
  TString sTex = sCone;
 //===============The same centrality with different cone in UE
  if(!sCent.IsNull()){
    sHist[0] = Form("hPtPC_%s_%s", sType.Data(), sCent.Data());
    sHist[1] = Form("hPtOC_%s_%s",   sType.Data(), sCent.Data());
    sHist[2] = Form("hPtNJ_%s_%s",   sType.Data(), sCent.Data());
    
    sLeg[0] = "PC"; sLeg[1] = "OC"; sLeg[2] = "NJ"; 
    
    if(sCent == "010")sTex = "0-10%";
    if(sCent == "1040")sTex = "10-40%";
    if(sCent == "40100")sTex = "40-100%";
    if(sCent == "0100")sTex = "0-100%";
  }
 //======================================================

  Double_t XMin = 0.;
  Double_t XMax;
  Double_t YMin;
  Double_t YMax;
 
  if(sType == "Kshort"){ XMax = 12.; YMax = 10.; YMin = 1e-6;}
  if(sType == "Lambda" || sType == "AntiLa"){ XMax = 12.; YMax = 10.; YMin = 1e-7;}
  if(sType == "Xi"){ XMax = 8.; YMax = 1.; YMin = 1e-6;}
  if(sType == "Omega"){ XMax = 5.; YMax = 1e-1; YMin = 1e-6;}
  
  TString sLatex(Form("#%s spectrum", sType.Data()));
  if(sType=="Kshort") sLatex = "K^{0}_{S} spectrum";
  if(sType=="AntiLa") sLatex = "#bar{#Lambda} spectrum";
  //-----------------------------------
  TCanvas *can = nullptr;

  can = MakeCanvas("can");
  can->SetLogy();
  can->SetGridx(); can->SetGridy();

  auto leg = new TLegend(0.8,0.9,1.0,0.65);    
  auto nHist = sizeof(sHist)/sizeof(TString);
  //-----------------------------------
  for (Int_t i = 0; i< nHist; i++){
    TString sMyPath = sPath[i]; 
    TString sMyFile = sFile[i]; 
    TString sMyList = sList[i]; 
    TString sMyHist = sHist[i]; 
    TH1D* h1 = (TH1D*)GetTH1D(sMyPath.Data(), sMyFile.Data(), sMyList.Data(), sMyHist.Data());
    h1->SetName(Form("hist_%d", i));
    h1->GetYaxis()->SetRangeUser(YMin, YMax);
    h1->GetXaxis()->SetRangeUser(XMin, XMax);
    h1->SetTitle(""); 
    SetFrame(h1, "#it{p}_{T}(GeV/#it{c})", "d#rho/d#it{p}_{T}");
    DrawHisto(h1, cLine[i], sMark[i], "same");
    leg->AddEntry(h1,sLeg[i],"lp");
  }

  TLatex* tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  SetLegend(leg);
  tex->DrawLatex(0.16, 0.91, sLatex);
  if(!sCone.IsNull())tex->DrawLatex(0.5, 0.91, Form("%s", sTex.Data()));
  if(!sCent.IsNull())tex->DrawLatex(0.5, 0.91, Form("V0A : %s", sTex.Data()));
  tex->DrawLatex(0.16, 0.3, "|#eta| < 0.75");
  tex->DrawLatex(0.16, 0.2, "p-Pb #sqrt{#it{s}_{NN}} = 5.02 TeV");
  leg->Draw();
  gStyle->SetOptStat("");

  if((!sCent.IsNull()) && IsSaveCan)can->SaveAs(Form("./figure/ThisAna_New/%s_DiffConePt_%s_woUncertainty.eps", sType.Data(), sCent.Data()));
  //if((!sCent.IsNull()) && IsSaveCan)can->SaveAs(Form("./figure/ThisAna_New/%s_UE_%s_woUncertainty.eps", sType.Data(), sCent.Data()));
  if((!sCone.IsNull()) && IsSaveCan)can->SaveAs(Form("./figure/ThisAna_New/%s_PtSpect_%s_woUncertainty.eps", sType.Data(), sCone.Data()));
  CanvasEnd(can);
  return;
}
