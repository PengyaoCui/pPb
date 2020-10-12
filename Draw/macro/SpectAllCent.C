#include "./SourceFun.h"

void SpectAllCent(){
  
  const TString sType = "Xi";
  TString CentMin[] = {"0", "0", "10", "40"}; 
  TString CentMax[] = {"100", "10", "40", "100"}; 
 
  auto n = sizeof(CentMin)/sizeof(TString); 
  
  TString sPath = "./result"; 
  TString sCFile = "PtSpect_Eta.root";
  TString sCHist = "hPtPC";//hPtIncl, hPtJC, hPtJE, hPtPC
  TString sEFile = "UncertaintyTot.root";
  TString sEList = "UncerTot";
  TString sEHist = "hUErr"; //"hIErr", "hUErr", "hJErr" 

  auto sLatex(Form("p-Pb #sqrt{#it{s}_{NN}} = 5.02 TeV"));
  Double_t XMin = 0.6;
  Double_t XMax = 12.;
  
  //-----------------------------------
  TCanvas *can = nullptr;
  TLatex* tex = nullptr;
  TLegend *leg = nullptr;
  can = MakeCanvas("can");
  can->SetLogy(); 
  leg = new TLegend(0.7,0.9,1.0,0.6); SetLegend(leg);
  
  //-----------------------------------
  TH1D*h1;
  TH1D*h2;
  TGraphErrors*g;
  for(Int_t i =0; i< n; i++){ 
    h1 = (TH1D*)GetTH1D(sPath, sCFile, "", Form("%s_%s_%s%s", sCHist.Data(), sType.Data(), CentMin[i].Data(), CentMax[i].Data()));
    h1->SetName(Form("Cen_%d", i));
    h2 = (TH1D*)GetTH1D(sPath, sEFile, Form("%s_%s_%s%s", sType.Data(), sEList.Data(), CentMin[i].Data(), CentMax[i].Data()), sEHist);
    h2->SetName(Form("Err_%d", i));
    const auto nI = h1->GetNbinsX();
    h1->GetYaxis()->SetRangeUser(1e-7, 2e1);
    h1->GetXaxis()->SetRangeUser(0., 12.);
    DrawHisto(h1, cLine[i], sMark[i], "same");
    leg->AddEntry(h1, Form("%s-%s%%", CentMin[i].Data(), CentMax[i].Data()));
    g = (TGraphErrors*)ConvHistogramToGraphErrors(h1, h2, nI); g->SetName(Form("gErr_%d", i));
    DrawGraph(g, cLine[i], "E2");
  }
  //-----------------------------------
  
  
  tex =  new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.15, 0.9, sLatex);
  tex->DrawLatex(0.15, 0.8, Form("UE %s", sType.Data()));
  leg->AddEntry(g, "Sys.Error", "f");  
  leg->Draw();
  gStyle->SetOptStat("");
  can->SaveAs(Form("./figure/%s_wSysError_UE.eps", sType.Data()));
  //DrawAliLogo(0.65, 0.90, 24, kTRUE);
  CanvasEnd(can);
  return;
}
