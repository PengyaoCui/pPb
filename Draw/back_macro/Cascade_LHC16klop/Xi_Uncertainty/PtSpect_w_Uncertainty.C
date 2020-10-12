#include "./SourceFun.h"

void PtSpect_w_Uncertainty(){
 
  Bool_t IsSave(0);

  TString sSaveFile = "./result/CorrectedResults_w_Uncertainty.root";

  //Numerator information
  //TString sPath = "/home/cuipengyao/study/code/Cascade_LHC16h/QA_Topol";
  TString sPath = Form("/home/cuipengyao/study/code/Draw/macro/Uncertainty/Xi_Uncertainty/result");
  TString sFile = "Uncertainty_Max_NoBarlow.root";
  TString sSpectFile = "PtSpect_Topological.root";
  TString sHist[] = {"Topological", "SignalExtract", "TPC_Trk", "TPCPID"};//Uncertainty

  const Int_t nHist  = sizeof(sHist)/sizeof(TString);

  //TString sLatex = "1#sigma Barlo criterion";
  TString sLatex = "Inclusive #Xi";
  Double_t   YMin = 1e-7;
  Double_t   YMax = 1e7; 
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
  Int_t nBins = hUncertainty->GetNbinsX();
  cout<<nBins<<endl;
  Double_t dSysErr[20] = {NULL};
  for(Int_t k = 1;  k<= nBins; k++){ dSysErr[k] = hUncertainty->GetBinContent(k);}
  TH1D* hSpect = (TH1D*)GetTH1FromFile(sPath, sSpectFile, "hPtIncl_Xi_Stand"); 
  SetLine(hSpect,cLine[0], sMark[0]);
  hSpect->SetLineWidth(2);
  hSpect->SetMarkerSize(0.8);
  //hSpect->Draw("same");
  SetAxis(hSpect, YMin, YMax, XMin, XMax, "d#rho/d#it{p}_{T}");
  TH1D* hSysSpect = (TH1D*)hSpect->Clone("hSysSpect");
  for(Int_t j; j <=hSysSpect->GetNbinsX(); j++){hSysSpect->SetBinError(j, hSysSpect->GetBinContent(j)*dSysErr[j]);}
  //SetLine(hSysSpect,cLine[1], sMark[1]);
  
   hSysSpect->SetFillColor(1);
   hSysSpect->SetFillStyle(0);
   hSysSpect->SetLineColor(1);
   hSysSpect->SetLineWidth(2);
   hSysSpect->SetMarkerStyle(20);
   //hSysSpect->SetLineStyle(1);
  //hSysSpect->SetLineWidth(1);
  //hSysSpect->SetMarkerColor(0);
   hSysSpect->SetFillStyle(3001);
   hSysSpect->Draw("e2same");
  //gStyle->SetErrorX(0.2);
  //hSysSpect->Draw("same");
  //leg->AddEntry(hUncertainty, "Total","lp");


  if(IsSave) {file->cd(); hSpect->Write("hSpect_Xi_Incl", TObject::kSingleKey);}
  if(IsSave) {file->cd(); hSysSpect->Write("hSysSpect_Xi_Incl", TObject::kSingleKey);}

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
