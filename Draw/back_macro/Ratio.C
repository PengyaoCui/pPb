#include "./SourceFun.h"

void Ratio(){

  const TString sRatio = "wSDD as Ref";
  TString sPathNu[] = {"./result", "./result"};
  TString sFileNu[] = {"PtSpect_Eta_woSDD.root", "PtSpect_Eta_Fast.root"};
  TString sListNu[] = {"", ""};
  TString sHistNu[] = {"hPtIncl_Omega_0100", "hPtIncl_Omega_0100"};

  TString sPathDe = "./result";
  TString sFileDe = "PtSpect_Eta_V0BinCascade.root";
  TString sListDe = "";
  TString sHistDe = {"hPtIncl_Omega_0100"};

  TString sLeg[] = {"woSDD", "FAST", "wSDD"};

  auto sLatex(Form("Inclusive Omega 0-100%%"));
  Double_t XMin = 0.;
  Double_t XMax = 12.;
  //-----------------------------------
  TCanvas *can = nullptr;
  TPad *padT = nullptr;
  TPad *padB = nullptr;
  TLatex* tex = nullptr;
  TLegend *leg = nullptr;

  can = MakeCanvas("can");
 
  leg = new TLegend(0.7,0.9,1.0,0.6); SetLegend(leg);
  //-----------------------------------
  auto nHist = sizeof(sHistNu)/sizeof(TString);
  const auto nhist = nHist;

  TH1D* h2 = nullptr;
  TH1D* h1 = nullptr;
  TH1D* hRatio = nullptr;

  padB = MakePadB("padB");
  can->cd();
  padT = MakePadT("padT");
  padT->SetLogy();

  //Double_t dBin[] = {10, 15, 20, 25, 30, 35, 40, 50, 60, 80, 100};
  //Double_t dBin[] = {0.6, 0.8, 1.0, 1.2, 1.4, 1.6, 1.8, 2.0, 2.2, 2.4, 2.6, 2.8, 3.2, 3.7, 4.2, 5.0, 6.0, 8.0, 12.};
  //Int_t nBin = sizeof(dBin)/sizeof(Double_t) - 1;
  //TH1D *h0 = new TH1D("h0", "", nBin, dBin);

  h2 = (TH1D*)GetTH1D(sPathDe.Data(), sFileDe.Data(), sListDe.Data(), sHistDe.Data());
  h2->SetName("h2_De");
  h2->SetTitle("");
  //h2=RebinTH1D(h2, h0);
  


  leg->AddEntry(h2, sLeg[nHist],"lp");
  padT->cd();
  h2->GetXaxis()->SetRangeUser(XMin, XMax);
  h2->GetYaxis()->SetRangeUser(1e-7, 1e0);
  SetFrame(h2, "#it{p}_{T}", "#frac{d#it{#rho}}{d#it{p}_{T}}");
  DrawHisto(h2, cLine[nHist], sMark[nHist], "same");


  for (Int_t i = 0; i< nHist; ++i){
    TString sMyPath = sPathNu[i]; 
    TString sMyFile = sFileNu[i]; 
    TString sMyList = sListNu[i]; 
    TString sMyHist = sHistNu[i]; 
    h1 = (TH1D*)GetTH1D(sMyPath.Data(), sMyFile.Data(), sMyList.Data(), sMyHist.Data());
    h1->SetName(Form("hist_%d", i)); 
    //DeNormHistBinWidth(h1); 
    //h1->Scale(1./1646615);
    h1=RebinTH1D(h1, h2);
    //NormHistBinWidth(h1); 
    hRatio = (TH1D*) h2->Clone(Form("hRatio_%d", i)); hRatio->Reset();
    hRatio->Divide(h1, h2);
    hRatio->SetName(Form("hratio_%d", i));
    hRatio->GetYaxis()->SetRangeUser(0.8, 1.2);
    padT->cd();
    DrawHisto(h1, cLine[i], sMark[i], "same");
    leg->AddEntry(h1, sLeg[i], "lp");
    padB->cd();
    padB->SetGridy();
    DrawHisto(hRatio, cLine[i], sMark[i], "same");
    SetFrame(hRatio, "#it{p}_{T} (GeV/#it{c})", sRatio, 0.08, 0.08, 0.1, 0.1, 1.10, 0.6);
  }


  padB->cd();
  //TLine* l = new TLine(XMin, 1., XMax, 1.);
  //l->SetLineColor(kRed);
  //l->SetLineWidth(2);
  //l->Draw("same");

  padT->cd();
  tex =  new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.2, 0.9, sLatex);
  leg->Draw();
  gStyle->SetOptStat("");
  can->SaveAs(Form("./figure/QAPlots/QA_Omega_0100_Incl.eps"));
  CanvasEnd(can);
  return;
}
