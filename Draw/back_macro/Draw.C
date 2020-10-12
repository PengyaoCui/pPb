#include "./SourceFun.h"

void Draw(){
  auto Path = "/home/cuipengyao/study/pPb/Local/ThisAna/NewFd/Incl";
  auto File = "";
  TString sPath[] = {Path, Path, Path, Path};
  TString sFile[] = {"AnalysisOutputs_MakeLaFdR.root", "AnalysisOutputs_MakeLaFdR.root", "AnalysisOutputs_MakeLaFdR.root", "AnalysisOutputs_MakeLaFdR.root"};
  TString sList[] = {"listMakeLaFdR_Lambda_Default_0100", "listMakeLaFdR_Lambda_Default_010", "listMakeLaFdR_Lambda_Default_1040", "listMakeLaFdR_Lambda_Default_40100"};
  TString sHist[] = {"hPtFdFrac", "hPtFdFrac", "hPtFdFrac", "hPtFdFrac"};
  TString sLeg[] = {"0-100%", "0-10%", "10-40%", "40-100%"}; 

  auto sLatex("Inclusive #bar{#Lambda} feed-down fraction distribution");
  //-----------------------------------
  TCanvas *can = nullptr;

  can = MakeCanvas("can");
  //can->SetLogy();
  can->SetGridx(); can->SetGridy();

  auto leg = new TLegend(0.8,0.9,1.0,0.65);    
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
    //for(int j =1; j<=h1->GetNbinsX(); j++){cout<<h1->GetBinLowEdge(j)<<endl;}
    auto dMini = h1->GetMinimum(); 
    auto dMaxi = h1->GetMaximum(); 
    h1->GetXaxis()->SetRangeUser(0.6, 12.);
    h1->GetYaxis()->SetRangeUser(0., 0.3);
    h1->SetTitle(""); 
    SetFrame(h1, "#it{p}_{T}(GeV/#it{c})", "Feed-down Fraction");
    DrawHisto(h1, cLine[i], sMark[i], "same");
    leg->AddEntry(h1,sLeg[i],"lp");
  }

  TLatex* tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  SetLegend(leg);
  tex->DrawLatex(0.16, 0.91, sLatex);
  //tex->DrawLatex(0.26, 0.3, "|#eta| < 0.75");
  //tex->DrawLatex(0.26, 0.2, "p-Pb #sqrt{#it{s}_{NN}} = 5.02 TeV");
  leg->Draw();
  gStyle->SetOptStat("");

  can->SaveAs("./figure/AntiLa_Incl_FdFrac_NewFd.eps");
  can->SaveAs("./figure/AntiLa_Incl_FdFrac_NewFd.png");
  can->SaveAs("./figure/AntiLa_Incl_FdFrac_NewFd.pdf");
  CanvasEnd(can);
  return;
}
