#include "./SourceFun.h"

void RatiowCent(const TString sType = "Lambda_sum", const TString sCone = "Incl"){

  TString sLatex(Form("p-Pb #sqrt{#it{s}_{NN}} = 5.02 TeV"));
 
  auto f = TFile::Open("./result/FinalSpect_ThisAna.root", "read");
  auto l0 = (TList*)f->Get(Form("%s_toKRatio_0100", sType.Data()));
  auto l1 = (TList*)f->Get(Form("%s_toKRatio_010", sType.Data()));
  auto l2 = (TList*)f->Get(Form("%s_toKRatio_1040", sType.Data()));
  auto l3 = (TList*)f->Get(Form("%s_toKRatio_40100", sType.Data()));
  f->Close();
  //TString sRInclC = "hInclR"; TString sRInclE = "InclRerr";
  //TString sRJEC = "hJER";     TString sRJEE = "JEerr";
  //TString sRUEC = "hUER";     TString sRUEE = "UERerr";

  auto h0 = (TH1D*)l0->FindObject(Form("h%sR", sCone.Data())); h0->SetName("h0");
  auto h1 = (TH1D*)l1->FindObject(Form("h%sR", sCone.Data())); h1->SetName("h1");
  auto h2 = (TH1D*)l2->FindObject(Form("h%sR", sCone.Data())); h2->SetName("h2");
  auto h3 = (TH1D*)l3->FindObject(Form("h%sR", sCone.Data())); h3->SetName("h3");

  auto g0 = (TGraphErrors*)l0->FindObject(Form("%sRerr", sCone.Data())); g0->SetName("g0");
  auto g1 = (TGraphErrors*)l1->FindObject(Form("%sRerr", sCone.Data())); g1->SetName("g1");
  auto g2 = (TGraphErrors*)l2->FindObject(Form("%sRerr", sCone.Data())); g2->SetName("g2");
  auto g3 = (TGraphErrors*)l3->FindObject(Form("%sRerr", sCone.Data())); g3->SetName("g3");

  //-----------------------------------
  TCanvas *can = nullptr;
  TLatex* tex = nullptr;
  TLegend *leg = nullptr;
  can = MakeCanvas("can");
  leg = new TLegend(0.7,0.9,1.0,0.6); SetLegend(leg);

  auto XMin = 0.; auto XMax = 0.; auto YMin = 0.; auto YMax = 0.;
  if(sType == "Lambda_sum"){XMax = 12.; YMax = 1.5;}
  if(sType == "Xi"){XMax = 8.; YMax = 0.35;}
  if(sType == "Omega"){XMax = 5.; YMax = 0.1;}

  h0->GetYaxis()->SetRangeUser(YMin, YMax);
  h0->GetXaxis()->SetRangeUser(XMin, XMax);
  if(sType == "Lambda_sum"){
    h0->GetYaxis()->SetTitle("#Lambda/K^{0}_{S}");
  }else{
    h0->GetYaxis()->SetTitle(Form("#%s/K^{0}_{S}", sType.Data()));
  }

  //-----------------------------------

  DrawHisto(h0, cLine[0], sMark[0], "same"); DrawGraph(g0, cLine[0], "E2"); leg->AddEntry(h0, "0-100%");
  DrawHisto(h1, cLine[1], sMark[1], "same"); DrawGraph(g1, cLine[1], "E2"); leg->AddEntry(h1, "0-10%");
  DrawHisto(h2, cLine[2], sMark[2], "same"); DrawGraph(g2, cLine[2], "E2"); leg->AddEntry(h2, "10-40%");
  DrawHisto(h3, cLine[3], sMark[3], "same"); DrawGraph(g3, cLine[3], "E2"); leg->AddEntry(h3, "40-100%");
  leg->AddEntry(g0, "Sys.Error", "f");
  leg->Draw();

  //-----------------------------------
  tex =  new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.15, 0.9, sLatex);
 
  if(sCone != "Incl"){
    tex->DrawLatex(0.15, 0.83, "Jet: Anti-#it{k}_{T}, #it{R} = 0.4");
    tex->DrawLatex(0.15, 0.75, "#it{p}_{T, jet}^{ch} > 10 GeV/#it{c}, |#it{#eta}_{jet}| < 0.35");
    if(sType == "Lambda_sum") tex->DrawLatex(0.15, 0.63, Form("%s #frac{#Lambda + #bar{#Lambda}}{2K^{0}_{S}}", sCone.Data()));
    if(sType == "Xi" || sType == "Omega") tex->DrawLatex(0.15, 0.63, Form("%s #frac{#%s + #bar{#%s}}{2K^{0}_{S}}", sCone.Data(), sType.Data(), sType.Data()));
  }else{
    tex->DrawLatex(0.15, 0.83, "Inclusive");
    tex->DrawLatex(0.15, 0.75, "|#it{#eta}| < 0.75");
    if(sType == "Lambda_sum"){
      tex->DrawLatex(0.15, 0.63, Form("#frac{#Lambda + #bar{#Lambda}}{2K^{0}_{S}}"));
    }
    if(sType == "Xi" || sType == "Omega"){
      tex->DrawLatex(0.15, 0.63, Form("#frac{#%s + #bar{#%s}}{2K^{0}_{S}}", sType.Data(), sType.Data()));
    }
  } 
  gStyle->SetOptStat("");
  can->SaveAs(Form("./figure/ThisAna/%s_toKRatio_wSysError_%s.eps", sType.Data(), sCone.Data()));
  //DrawAliLogo(0.65, 0.90, 24, kTRUE);
  CanvasEnd(can);
  return;
}
