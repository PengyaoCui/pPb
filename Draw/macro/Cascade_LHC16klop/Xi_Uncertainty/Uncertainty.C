#include "./SourceFun.h"

void Uncertainty(){
 
  Bool_t IsSave(0);

  TString sCut = "Topology";
  TString sSaveFile = Form("./result/Uncertainty_Separate_%s_1Sigma.root", sCut.Data());

  //Numerator information
  //TString sPath = "/home/cuipengyao/study/code/Cascade_LHC16h/QA_Topol";
  TString sPath = Form("/home/cuipengyao/study/code/Draw/macro/Cascade_LHC16klop/Xi_Uncertainty/result");
  TString sFile = Form("PtSpect_%s.root", sCut.Data());
  TString sHist = "hPtIncl_Xi";
  TString sNuHist[] = {"Loose", "VLoose", "Tight", "VTight", "VvTight"};//Uncertainty
  //TString sNuHist[] = {"Tight"};//Uncertainty

  const Int_t nNuHist  = sizeof(sNuHist)/sizeof(TString);

  TString sDeHist = "Stand";//Standard

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

  TString sDenominator = Form("%s_%s", sHist.Data(), sDeHist.Data());
  TH1D* hDenominator = (TH1D*)GetTH1FromFile(sPath,  sFile,  sDenominator);
  hDenominator->SetName("hDenominator");

  for(Int_t i=0; i<nNuHist; i++) {
    TString sNumerator = Form("%s_%s", sHist.Data(), sNuHist[i].Data());
    TH1D* hNumerator = (TH1D*)GetTH1FromFile(sPath,  sFile,  sNumerator);
    hNumerator->SetName(Form("hNumerator_%s", sNumerator.Data()));
    TString sRatio = Form("%s/%s", sNuHist[i].Data(), sDeHist.Data());
    TH1D* hRatio = (TH1D*)hDenominator->Clone(sRatio); hRatio->Reset();
    for(Int_t j=1; j<=hRatio->GetNbinsX(); j++){
      Double_t dVarStand = hDenominator->GetBinContent(j);
      Double_t dErrStand = hDenominator->GetBinError(j);
      Double_t dVarUncer = hNumerator->GetBinContent(j);
      Double_t dErrUncer = hNumerator->GetBinError(j);
      Double_t dVarRatio = TMath::Abs((dVarStand - dVarUncer)/dVarStand);
      //Double_t dErrRatio = (dErrUncer/dErrStand)*(TMath::Sqrt(dErrUncer*dErrUncer/(dVarUncer*dVarUncer) + dErrStand*dErrStand/(dVarStand*dVarStand))); 
      Double_t dErrRatio = (dVarUncer/dVarStand)*(TMath::Sqrt(dErrUncer*dErrUncer/(dVarUncer*dVarUncer) + dErrStand*dErrStand/(dVarStand*dVarStand))); 

      //cout<< dErrUncer/dErrStand <<"=========="<<dVarUncer/dVarStand <<endl;

      if (TMath::Abs(dVarStand - dVarUncer)/TMath::Sqrt(TMath::Abs(dErrStand*dErrStand - dErrUncer*dErrUncer)) > 1 ){
        hRatio->SetBinContent(j, dVarRatio);
        hRatio->  SetBinError(j, 1e-12);
        //hRatio->  SetBinError(j, dErrRatio);
      }else{
        hRatio->SetBinContent(j, 0.);
        hRatio->  SetBinError(j, 1e-12);
      }
    }
    SetLine(hRatio,cLine[i], sMark[i]);
    SetAxis(hRatio, YMin, YMax, XMin, XMax, "Relative syst. errors");
    hRatio->Draw("same");
    leg->AddEntry(hRatio, sNuHist[i],"lp");
    if(IsSave) {file->cd(); hRatio->Write(sNuHist[i], TObject::kSingleKey);}

  }

  TLatex*     tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.15, 0.9, sCut);
  tex->DrawLatex(0.15, 0.8, sLatex);
  c2->SetGridy();
  c2->SetGridx();
  SetLegend(leg);
  leg->Draw();


  if(IsSave) { file->Close();}

  return;
}
