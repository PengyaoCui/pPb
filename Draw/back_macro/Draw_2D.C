#include "./SourceFun.h"

TCanvas* makeCanvas(TString sName);
void Draw_2D(){

  TString sPath[] = {"/home/cuipengyao/study/pPb/Local/ThisAna/NewFd/Incl"};
  TString sFile[] = {"AnalysisOutputs_LoopIncMC.root"};
  TString sList[] = {"listLoopIncMC_Lambda_Default_0100"};
  TString sHist[] = {"hPtLaXi"};

  auto sLatex("p-Pb at #sqrt{s_{NN}} = 5.02 TeV");
  //-----------------------------------
  TCanvas *can = nullptr;

  can = makeCanvas("can");
  //can->SetLogy();
  //can->SetGridx(); can->SetGridy();

  //-----------------------------------
  auto nHist = sizeof(sHist)/sizeof(TString);
  for (Int_t i = 0; i< nHist; i++){
    TString sMyPath = sPath[i]; 
    TString sMyFile = sFile[i]; 
    TString sMyList = sList[i]; 
    TString sMyHist = sHist[i]; 
    TH2D* h1 = (TH2D*)GetTH2D(sMyPath.Data(), sMyFile.Data(), sMyList.Data(), sMyHist.Data());
    h1->SetName(Form("hist_%d", i));
    h1->GetYaxis()->SetRangeUser(0.6, 12.);
    //h1->GetXaxis()->SetRangeUser(0., 12.);
    h1->GetXaxis()->SetTitle("#it{p}_{T, #Lambda}(GeV/#it{c})");
    h1->GetYaxis()->SetTitle("#it{p}_{T, #Xi}(GeV/#it{c})");
    h1->GetXaxis()->SetLabelSize(0.05);
    h1->GetYaxis()->SetLabelSize(0.05);

    h1->GetXaxis()->SetTitleSize(0.06);
    h1->GetYaxis()->SetTitleSize(0.06);

    h1->GetXaxis()->SetTitleOffset(1.);
    h1->GetYaxis()->SetTitleOffset(1.);
    h1->Draw("same colz");
  }

  TLatex* tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  //tex->DrawLatex(0.16, 0.91, sLatex);
  tex->DrawLatex(0.16, 0.91, "Inclusive Feed-down matrix");
  gStyle->SetOptStat("");

  can->SaveAs("./figure/Lambda_Fd_Matrix.eps");
  CanvasEnd(can);
  return;
}

TCanvas* makeCanvas(TString sName)
{
  TCanvas *c = new TCanvas(Form("c%s",sName.Data()), sName.Data(), 700, 500);
  c->Range(0., 0., 1., 1.);
  c->SetFillColor(0);
  c->SetBorderMode(0);
  c->SetBorderSize(0);
  c->SetRightMargin(0.1);
  c->SetLeftMargin(0.13);
  c->SetTopMargin(0.1);
  c->SetBottomMargin(0.15);
  c->SetFrameFillStyle(0);
  c->SetFrameBorderMode(0);

  return c;
}

