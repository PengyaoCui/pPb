#include "./SourceFun.h"

void Uncertainty_Max(){
 
  Bool_t IsSave(1);

  TString sCut = "Topological";
  TString sSaveFile = "./result/Uncertainty_Max_NoBarlow.root";

  //Numerator information
  //TString sPath = "/home/cuipengyao/study/code/Cascade_LHC16h/QA_Topol";
  TString sPath = Form("/home/cuipengyao/study/code/Draw/macro/Uncertainty/Xi_Uncertainty/result");
  TString sFile = Form("Uncertainty_Separate_%s_NoBarlow.root", sCut.Data());
  //TString sHist = "hPtIncl_Xi";
  TString sNuHist[] = {"Loose", "VLoose", "Tight", "VTight", "VvTight"};//Uncertainty
  //TString sNuHist[] = {"Tight", "Loose"};//Uncertainty

  const Int_t nNuHist  = sizeof(sNuHist)/sizeof(TString);

  //TString sDeHist = "Stand";//Standard

  //TString sLatex = "1#sigma Barlo criterion";
  TString sLatex = "No Barlo criterion";
  Double_t   YMin = -0.01;
  Double_t   YMax = 0.1; 
  Double_t   XMin = 0.6;
  Double_t   XMax = 6.;
  //-----------------------------------

  if (IsSave) TFile *file = TFile::Open(sSaveFile, "UPDATE");

  TCanvas * c2 = new TCanvas("c2","");
  c2->SetFillColor(0);
  SetStyle();
  SetCanv(c2);
  //TLegend* leg = new TLegend(0.8,0.9,1.0,0.5);
    
  //-----------------------------------
  if(sPath.IsNull() || sFile.IsNull() ) { cout<<"Don't have file"<<endl;   return 0x0;}
  //-----------------------------------

  TH1D* h0 = (TH1D*)GetTH1FromFile(sPath, sFile, sNuHist[0]);
  TH1D* hUncertainty = (TH1D*)h0->Clone("hUncertainty"); hUncertainty->Reset();
  Double_t dVar = 0;
  for(Int_t i = 1; i<= hUncertainty->GetNbinsX(); i++){
    for(Int_t j=0; j<nNuHist; j++) {
      TH1D* hN = (TH1D*)GetTH1FromFile(sPath,  sFile,  sNuHist[j]);
      hN->SetName(Form("hN_%s", sNuHist[j].Data()));
      Double_t dContent = hN->GetBinContent(i);
      if (dContent>dVar) dVar = dContent;
    }
    hUncertainty->SetBinContent(i, dVar);
  //cout<<"----------------"<<endl;
    dVar = 0;
  }
  SetLine(hUncertainty,cLine[0], sMark[0]);
  SetAxis(hUncertainty, YMin, YMax, XMin, XMax, "Helative syst. errors");
  hUncertainty->Draw("same");
  //leg->AddEntry(hUncertainty, sCut,"lp");
  if(IsSave) {file->cd(); hUncertainty->Write(sCut, TObject::kSingleKey);}

  TLatex*     tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.15, 0.9, sCut);
  tex->DrawLatex(0.15, 0.8, sLatex);
  c2->SetGridy();
  c2->SetGridx();
  //SetLegend(leg);
  //leg->Draw();


  if(IsSave) { file->Close();}

  return;
}
