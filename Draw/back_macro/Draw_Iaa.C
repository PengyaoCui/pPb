#include "./SourceFun.h"

void Draw_Iaa(){
  auto Path = "./result";
  auto File = "IAA_woSysErr.root";
  TString sPath[] = {Path, Path, Path};
  TString sFile[] = {File, File, File};
  TString sList[] = {"", "", ""};
  TString sHist[] = {"Kshort_0100", "Lambda_0100", "Xi_0100"};
  TString sLeg[] = {"K^{0}_{S}", "#Lambda", "#Xi"}; 

  auto sLatex("#it{I}_{AA}");
  //-----------------------------------
  TCanvas *can = nullptr;

  can = MakeCanvas("can");
  //can->SetLogy();
  can->SetGridx(); can->SetGridy();

  auto leg = new TLegend(0.8,0.9,1.0,0.65);    
  //-----------------------------------
  auto nHist = sizeof(sHist)/sizeof(TString);
  for (Int_t i = 0; i< nHist; i++){
    TString sMyPath = sPath[i]; 
    TString sMyFile = sFile[i]; 
    TString sMyList = sList[i]; 
    TString sMyHist = sHist[i]; 
    TH1D* h1 = (TH1D*)GetTH1D(sMyPath.Data(), sMyFile.Data(), sMyList.Data(), sMyHist.Data());
    h1->SetName(Form("hist_%d", i));
    if(sMyHist == "Lambda_0100") {
      TH1D*h11 =(TH1D*)GetTH1D(sMyPath.Data(), sMyFile.Data(), sMyList.Data(), "AntiLa_0100");
      h1->Add(h11);
      h1->Scale(0.5);
    }
    
    auto dMini = h1->GetMinimum(); 
    auto dMaxi = h1->GetMaximum(); 
    h1->GetXaxis()->SetRangeUser(0.6, 12.);
    h1->GetYaxis()->SetRangeUser(0., 3.);
    h1->SetTitle(""); 
    SetFrame(h1, "#it{p}_{T}(GeV/#it{c})", "#it{I}_{AA}");
    DrawHisto(h1, cLine[i], sMark[i], "same");
    leg->AddEntry(h1,sLeg[i],"lp");
  }
  TLine* l = new TLine(0.6, 1., 12, 1.);
  l->SetLineColor(kRed);
  l->SetLineStyle(2);
  l->SetLineWidth(2);
  l->Draw("same");

  TLatex* tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  SetLegend(leg);
  tex->DrawLatex(0.16, 0.91, sLatex);
  tex->DrawLatex(0.26, 0.3, "|#eta| < 0.75");
  tex->DrawLatex(0.26, 0.2, "p-Pb #sqrt{#it{s}_{NN}} = 5.02 TeV");
  leg->Draw();
  gStyle->SetOptStat("");

  can->SaveAs("./figure/Iaa_AllParticles.eps");
  CanvasEnd(can);
  return;
}
