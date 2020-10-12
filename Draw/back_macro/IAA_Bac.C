#include "./SourceFun.h"

void IAA( const TString CentMin = "0", const TString CentMax = "100"){

  const TString sType[] = {"Kshort", "Lambda", "Xi"};
  Int_t nT = sizeof(sType)/sizeof(TString); 
  //p-Pb 
  auto sPath = "./result"; 
  auto sCFile = "PtSpect_Eta.root";
  auto sCJetHist = "";
  
  auto sEFile = "UncertaintyTot.root";
  auto sEList = "";
  auto sEJHist = "hJErr";  
 
  //pp 
  TString sPath_pp = "./result_pp";
  TString sFile_pp = "";
  TString sJE1pp = ""; 
  
  Double_t dErrJEpp[] = {0.027974, 0.0246329, 0.018597, 0.0125446, 0.00735288, 0.0029652, 0.000815588};
  
  auto sLatex(Form("p-Pb #sqrt{#it{s}_{NN}} = 5.02 TeV"));
 
  TCanvas *can = nullptr;
  TLatex* tex = nullptr;
  TLegend *leg = nullptr;
  can = MakeCanvas("can");
  leg = new TLegend(0.7,0.9,1.0,0.6); SetLegend(leg);
  TGraphErrors* gJE = nullptr; 
  
  for(Int_t t = 0; t<nT; t++){
     //p-Pb
     sCJetHist = Form("hPtJE_%s_%s%s", sType[t].Data(), CentMin.Data(), CentMax.Data());
     if(sType[t] == "Lambda" || sType[t] == "AntiLa") sCJetHist = Form("hPtJC_%s_%s%s", sType[t].Data(), CentMin.Data(), CentMax.Data());
     if(sType[t] == "Xi") sCFile= "PtSpect_Eta_OldBinWidth.root";
      
     if(sType[t] == "Xi") sEFile = "UncertaintyTot_OldBinWidth.root";
     sEList = Form("%s_UncerTot_%s%s", sType[t].Data(), CentMin.Data(), CentMax.Data());
      
     //pp 
     sFile_pp =Form("PtSpect_%s.root", sType[t].Data()); 
     sJE1pp = Form("hPtJE_%s", sType[t].Data()); 
     if(sType[t] == "Lambda") dErrJEpp[] = {0.00370061, 0.00357178, 0.00387239, 0.00311807, 0.00207303, 0.000843525, 0.000212347};
     if(sType[t] == "AntiLa") dErrJEpp[] = {0.00366336, 0.00307274, 0.00337107, 0.00306934, 0.00210265, 0.000851981, 0.000171416};
     if(sType[t] == "Xi") dErrJEpp[] = {0.000873634, 0.000986836, 0.000753126, 0.000535095, 0.000327165, 0.000130094};
     auto hJE1   = (TH1D*)GetTH1D(sPath, sCFile, "", sCJetHist); hJE1->SetName(Form("JECen_%d", t));
     auto hJE2 = (TH1D*)GetTH1D(sPath, sEFile, sEList, sEJHist); hJE2->SetName(Form("JEErr_%d", t));
     const auto nJ = hJE1->GetNbinsX();
     auto hErrJE = (TH1D*)hJE2->Clone(Form("hErrJE_%d", t));
     for(Int_t i = 1; i<= hJE2->GetNbinsX(); i++){
       hErrJE->SetBinContent(i,hJE1->GetBinContent(i));
       hErrJE->SetBinError(i,hErrJE->GetBinContent(i)*hJE1->GetBinContent(i));
     }
  
     auto hJE1pp = (TH1D*)GetTH1D(sPath_pp, sFile_pp, "", sJE1pp); hJE1pp->SetName(Form("JECenpp_%d", t));
     auto hJE2pp = (TH1D*)hJE1pp->Clone(Form("JEErrpp_%d", t));hJE2pp->Reset(); 
     auto hErrJEpp = (TH1D*)hJE1pp->Clone(Form("hErrJEpp_%d", t));hErrJEpp->Reset(); 
     for(Int_t i = 1; i<= hJE2pp->GetNbinsX(); i++){
       auto dJE2C = hJE1pp->GetBinContent(i);
       hJE2pp->SetBinContent(i, dErrJEpp[i-1]/dJE2C);
       hErrJEpp->SetBinContent(i, dJE2C);
       hErrJEpp->SetBinError(i, dErrJEpp[i-1]);
     }
     hErrJEpp = RebinTH1D(hErrJEpp, hErrJE);
     hErrJE->Divide(hErrJEpp); 
     for(Int_t i = 1; i<= hErrJE->GetNbinsX(); i++){hErrJE->SetBinContent(i, hErrJEpp->GetBinError(i));}
     
     auto JEIaa = (TH1D*)hJE1->Clone(Form("JEIaa_%d", t));JEIaa->Reset();
     hJE1pp = RebinTH1D(hJE1pp, hJE1); 
     JEIaa->Divide(hJE1, hJE1pp);
     JEIaa->GetYaxis()->SetRangeUser(0.5, 2);
     JEIaa->GetYaxis()->SetTitle("#it{I}_{pPb}");
     DrawHisto(JEIaa, cLine[t], sMark[t], "same"); 
     leg->AddEntry(JEIaa, sType[t]);
     gJE = (TGraphErrors*)ConvHistogramToGraphErrors(JEIaa, hErrJEpp, nJ); gJE->SetName(Form("JE_%d", t));
     DrawGraph(gJE, cLine[t], "E2");

  } 


 
  //-----------------------------------
  tex =  new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.15, 0.9, sLatex);
  leg->AddEntry(gJE, "Sys.Error", "f");  
  leg->Draw();
  gStyle->SetOptStat("");
  //can->SaveAs(Form("./figure/%s_IAA_wSysError_%s%s.eps", sType.Data(), CentMin.Data(), CentMax.Data()));
  //DrawAliLogo(0.65, 0.90, 24, kTRUE);
  CanvasEnd(can);
  return;
}
