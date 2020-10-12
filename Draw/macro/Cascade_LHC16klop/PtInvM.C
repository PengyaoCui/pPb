#include"../../SourceFun.h"

void PtInvM(){
  TString sRootFilePath = "/home/cuipengyao/study/code/Cascade_LHC16klop_total/Local";
  TString sRootFileName = "AnalysisOutputs_Loop1ndRD.root";
  TString     sListName = "listLoop1ndRD_Xi_Default";
  TString       sObject = "hPtInvM";
  //TString          sTex = "#Lambda";
  TString          sTex = "#Xi^{#pm}";
//-----------------------------------------------------------------

  MakeCanvas("c1");
  //TCanvas* c1 = new TCanvas("c1", "");
  TLatex*  tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(50);
//-----------------------------------------------------------------
  if (sRootFilePath.IsNull() || sListName.IsNull() || sRootFileName.IsNull() || sObject.IsNull()) { cout<<"Input Error !!!!"<<endl; return;} 

  TH2D* hPtInvM = (TH2D*)GetTH2DFromList(sRootFilePath, sRootFileName, sListName, sObject);
  SetAxisStyle(hPtInvM,"#it{p}_{T}(GeV/c)", "Inv. Mass(GeV/#it{c}^{2})");
  hPtInvM->GetXaxis()->SetTitleOffset(0.8); 
  hPtInvM->GetYaxis()->SetTitleOffset(0.8); 
  hPtInvM->GetYaxis()->SetRangeUser(1.24,1.56);
  hPtInvM->Draw("same colz"); 

//-----------------------------------------------------------------
  SetStyle();
  tex->DrawLatex(0.2, 0.92, sTex);

}
TCanvas* MakeCanvas(TString sName)
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

