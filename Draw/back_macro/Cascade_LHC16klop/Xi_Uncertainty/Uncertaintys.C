#include "./SourceFun.h"

void Uncertaintys(){
 
  Bool_t IsSave(0);

  TString sSaveFile = "./result/Uncertaintys.root";

  //Numerator information
  //TString sPath = "/home/cuipengyao/study/code/Cascade_LHC16h/QA_Topol";
  TString sPath = Form("/home/cuipengyao/study/code/Draw/macro/Uncertainty/Xi_Uncertainty/result");
  TString sFile = "Uncertainty_Max_NoBarlow.root";
  TString sHist[] = {"Topological", "SignalExtract", "TPC_Trk", "TPCPID"};//Uncertainty

  const Int_t nHist  = sizeof(sHist)/sizeof(TString);

  //TString sLatex = "1#sigma Barlo criterion";
  TString sLatex = "No Barlow criterion";
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
  TLegend* leg = new TLegend(0.8,0.9,1.0,0.5);
    
  //-----------------------------------
  if(sPath.IsNull() || sFile.IsNull() ) { cout<<"Don't have file"<<endl;   return 0x0;}
  //-----------------------------------

  TH1D* h0 = (TH1D*)GetTH1FromFile(sPath, sFile, sHist[0]);
  TH1D* hUncertainty = (TH1D*)h0->Clone("hUncertainty"); hUncertainty->Reset();
  Double_t dSum = 0;
  for(Int_t i = 1; i<= hUncertainty->GetNbinsX(); i++){
    for(Int_t j=0; j<nHist; j++) {
      TH1D* hN = (TH1D*)GetTH1FromFile(sPath,  sFile,  sHist[j]);
      hN->SetName(Form("hN_%s", sHist[j].Data()));
      Double_t dContent = hN->GetBinContent(i);
      dSum = TMath::Sqrt(dSum*dSum + dContent*dContent);
    }
    hUncertainty->SetBinContent(i, dSum);
    dSum = 0;
  }
  SetLine(hUncertainty,cLine[0], sMark[0]);
  SetAxis(hUncertainty, YMin, YMax, XMin, XMax, "Relative syst. errors");
  hUncertainty->Draw("same");
  leg->AddEntry(hUncertainty, "Total","lp");

  for(Int_t j=0; j<nHist; j++) {
    TH1D* hN = (TH1D*)GetTH1FromFile(sPath,  sFile,  sHist[j]);
    hN->SetName(Form("hN_%s", sHist[j].Data()));
    SetLine(hN,cLine[j+1], sMark[j+1]);
    //SetAxis(hN, YMin, YMax, XMin, XMax, "Relative syst. errors");
    leg->AddEntry(hN, sHist[j],"lp");
    hN->Draw("same");
  }

  if(IsSave) {file->cd(); hUncertainty->Write("Uncertainty", TObject::kSingleKey);}

  TLatex*     tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  //tex->DrawLatex(0.15, 0.9, sCut);
  tex->DrawLatex(0.15, 0.9, sLatex);
  c2->SetGridy();
  c2->SetGridx();
  SetLegend(leg);
  leg->Draw();


  if(IsSave) { file->Close();}

  return;
}
