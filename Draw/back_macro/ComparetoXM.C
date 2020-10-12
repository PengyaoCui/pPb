#include "./SourceFun.h"

void ComparetoXM(){

  const TString sRatio = "ThisAna/ALICE";
  const TString CentMin = "0";
  const TString CentMax = "100";
  TString sPathNu[] = {"./result"};
  TString sFileNu[] = {"PtSpect_Compare2XM.root"};
  TString sListNu[] = {""};
  TString sHistNu[] = {Form("hPtJE_Kshort_%s%s", CentMin.Data(), CentMax.Data())};
  //TString sHistNu[] = {"hist_0"};

  TString sPathDe = "./published";
  TString sFileDe = "AnalysisResults_XM.root";
  TString sListDe = "listHD_JC04_JR04_PtJ10";//HD
  //TString sListDe = "listIn";
  TString sHistDe = "hKshort_Stat";
  TString sHistSyst = "hKshort_Syst";

  TString sLeg[] = {"This Ana", "Paper draft"};

  auto sLatex(Form("JE Kshort %s-%s%%", CentMin.Data(), CentMax.Data()));
  Double_t XMin = 0.6;
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

  h2 = (TH1D*)GetTH1D(sPathDe.Data(), sFileDe.Data(), sListDe.Data(), sHistDe.Data());
  h2->SetName("h2_De");
  h2->SetTitle("");

  auto h3 = (TH1D*)GetTH1D(sPathDe.Data(), sFileDe.Data(), sListDe.Data(), sHistSyst.Data());
  h3->SetName("h3_De");
  h3->SetTitle("");
  for(Int_t j = 1; j<=h3->GetNbinsX(); ++j){
	  
    auto StatErr = (Double_t) h2->GetBinError(j);
    auto SystErr = (Double_t) h3->GetBinContent(j);
    auto Content = (Double_t) h2->GetBinContent(j);
    auto TotErr = TMath::Sqrt(StatErr*StatErr + (SystErr*SystErr*Content*Content)); 
    h2->SetBinError(j, TotErr);
  } 
  NormHistBinWidth(h2); 
  //h2->Add(h3, -1.);

  leg->AddEntry(h2, sLeg[nHist],"lp");
  padT->cd();
  h2->GetXaxis()->SetRangeUser(XMin, XMax);
  h2->GetYaxis()->SetRangeUser(1e-4, 1.);
  SetFrame(h2, "#it{p}_{T}", "d#rho/d#it{p}_{T}(#it{c}/GeV)");


  for (Int_t i = 0; i< nHist; ++i){
    TString sMyPath = sPathNu[i]; 
    TString sMyFile = sFileNu[i]; 
    TString sMyList = sListNu[i]; 
    TString sMyHist = sHistNu[i]; 
    h1 = (TH1D*)GetTH1D(sMyPath.Data(), sMyFile.Data(), sMyList.Data(), sMyHist.Data());
    h1->SetName(Form("hist_%d", i)); 
    DeNormHistBinWidth(h1); 
    h1=RebinTH1D(h1, h2);
    //h1->Scale(2.);
    NormHistBinWidth(h1); 
    
    hRatio = (TH1D*) h2->Clone(Form("hRatio_%d", i)); hRatio->Reset();
    hRatio->Divide(h1, h2);
    hRatio->SetName(Form("hratio_%d", i));
    hRatio->GetYaxis()->SetRangeUser(0.5, 2);
    padT->cd();
    DrawHisto(h1, cLine[i], sMark[i], "same");
    leg->AddEntry(h1, sLeg[i], "lp");
    padB->cd();
    padB->SetGridy();
    DrawHisto(hRatio, cLine[i], sMark[i], "same");
    SetFrame(hRatio, "#it{p}_{T} (GeV/#it{c})", sRatio, 0.08, 0.08, 0.1, 0.1, 1.10, 0.6);
  }
  padT->cd(); 
  DrawHisto(h2, cLine[nHist], sMark[nHist], "same");


  padB->cd();
  //TLine* l = new TLine(XMin, 1.2, XMax, 1.2);
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
  //can->SaveAs(Form("./figure/Kshort_JEPt_%s%s_ComparetoXM.eps", CentMin.Data(), CentMax.Data()));
  CanvasEnd(can);
  return;
}
