#include "./SourceFun.h"

void JetPt(){

  TString sPath[] = {"/home/cuipengyao/study/pPb/Strangeness/Local/JetQA", "/home/cuipengyao/study/pPb/Strangeness/Local/JetQA"};
  TString sFile[] = {"AnalysisOutputs_LoopJetRD_Eta35.root", "AnalysisOutputs_LoopJetRD_Eta35.root"};
  TString sList[] = {"listLoopJetRD_Kshort_0100_JC", "listLoopJetRD_Kshort_0100_JC"};
  TString sHist[] = {"hJetPtBefore", "hJetPtAfter"};
  TString sLeg[] = {"measured #it{p}_{T, jet}", "measure #it{p}_{T, jet} - #rho_{bkg}#it{A}_{jet}"};

  auto sLatex("#it{R}_{jet} = 0.4, V0A: 0-100%");
  //-----------------------------------
  TCanvas *can = nullptr;

  can = MakeCanvas("can");
  can->SetLogy();
  can->SetGridx(); can->SetGridy();

  Double_t dBin[] = {5., 10, 20, 30, 40, 50, 60, 80, 100};
  Int_t nBin = sizeof(dBin)/sizeof(Double_t) - 1;
  TH1D *hPtJet = new TH1D("hPtJet", "", nBin, dBin);

  auto leg = new TLegend(0.6,0.9,1.0,0.7);    
  //-----------------------------------
  auto nHist = sizeof(sHist)/sizeof(TString);
  for (Int_t i = 0; i< nHist; i++){
    //TString sMyPath = Form("%s_%s", Path.Data(), sPath[i].Data()); 
    TString sMyPath = sPath[i]; 
    TString sMyFile = sFile[i]; 
    TString sMyList = sList[i]; 
    TString sMyHist = sHist[i]; 
    TH1D* h1 = (TH1D*)GetTH1D(sMyPath.Data(), sMyFile.Data(), sMyList.Data(), sMyHist.Data());
    h1->SetName(Form("hist_%d", i));
    TH1D* h2 = (TH1D*)GetTH1D(sMyPath.Data(), sMyFile.Data(), sMyList.Data(), "hEvent");
    h2->SetName(Form("hEvent_%d", i));
    //h1 = (TH1D*) h1-> Rebin(nBin, "h1", dBin);
    h1 = RebinTH1D(h1, hPtJet);
    h1->Scale(1./h2->GetEntries());
    NormHistBinWidth(h1);
    auto dMini = h1->GetMinimum(); 
    auto dMaxi = h1->GetMaximum(); 
    //h1->GetYaxis()->SetRangeUser(0.1*dMini, 100*dMaxi);
    h1->GetYaxis()->SetRangeUser(1e-8, 1.);
    SetFrame(h1, "#it{p}_{T}(GeV/#it{c})", "1/#it{N}_{ev} #times d#it{N}/d#it{p}_{T} (GeV/#it{c})");
    DrawHisto(h1, cLine[i], sMark[i], "same");
    leg->AddEntry(h1,sLeg[i],"lp");
  }

  TLatex* tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  SetLegend(leg);
  tex->DrawLatex(0.16, 0.8, sLatex);
  tex->DrawLatex(0.16, 0.91, "p-Pb at #sqrt{s_{NN}} = 5.02 TeV");
  leg->Draw();
  gStyle->SetOptStat("");

  can->SaveAs("./figure/JetPt_0100.eps");
  CanvasEnd(can);
  return;
}
