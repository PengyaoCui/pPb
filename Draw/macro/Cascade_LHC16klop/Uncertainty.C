#include "SourceFun.h"

void Uncertainty(){
  TString sPath = "/home/cuipengyao/study/code/Draw/macro/FinalResults/results";

  TString sLatex = "Systematic uncertainty of #Xi";
  Double_t   YMin = 0.;
  Double_t   YMax = 0.5;
  Double_t   XMin = 0.6;
  Double_t   XMax = 6.5;
  //-----------------------------------

  TCanvas*  c1 = new TCanvas("c1", "");
  TLegend* leg = new TLegend(0.7,0.9,1.0,0.6);    
  //-----------------------------------

  TH1D* hMean = (TH1D*)GetTH1FromFile(sPath, "PtSpect_Xi.root", "hPtJE_Xi");
  hMean->SetName("hMean"); 
  TH1D* hTot = (TH1D*)hMean->Clone("hTot"); hTot->Reset();
  TH1D* hRec = (TH1D*)hMean->Clone("hRec"); hRec->Reset();
  TH1D* hUE  = (TH1D*)hMean->Clone("hUE");  hUE ->Reset();
  TH1D* hJet = (TH1D*)hMean->Clone("hJet"); hJet->Reset();
  Double_t dRec[6] = {0.042832, 0.0480318, 0.0560362, 0.0641628, 0.0642275, 0.0771022};
  Double_t dUE[6]  = {0.000276884, 0.000195581, 0.000140336, 9.05768e-05, 4.74774e-05, 9.45003e-06};
  Double_t dJet[6] = {0.0591979, 0.0553908, 0.0288977, 0.0813561, 0.0241927, 0.0459242};

  for(Int_t i =0; i<6; i++){
    Double_t dMean = hMean->GetBinContent(i+1);
    hRec->SetBinContent(i+1, dRec[i]);
    hUE ->SetBinContent(i+1, dUE[i]/dMean);
    hJet->SetBinContent(i+1, dJet[i]);
    hTot->SetBinContent(i+1, TMath::Sqrt(dRec[i]*dRec[i] + (dUE[i]/dMean)*(dUE[i]/dMean) + dJet[i]*dJet[i]));
  }

  SetLine(hTot,cLine[0],sMark[0]);
  SetLine(hRec,cLine[1],sMark[0]);
  SetLine(hUE,cLine[2],sMark[0]);
  SetLine(hJet,cLine[3],sMark[0]);
  SetAxis(hTot, YMin, YMax, XMin, XMax, "Relative systematic uncertainty");

  hTot->Draw("same");
  hRec->Draw("same");
  hUE ->Draw("same");
  hJet->Draw("same");

  leg->AddEntry(hTot,"Total","nlp");
  leg->AddEntry(hRec,"#Xi reconstruction","nlp");
  leg->AddEntry(hUE, "Underlying event","nlp");
  leg->AddEntry(hJet,"Jet #it{p}_{T} scale","nlp");
  //hMean->Draw("same");

  TLatex*     tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  SetCanv(c1);
  SetLegend(leg);
  SetStyle();
  tex->DrawLatex(0.16, 0.91, sLatex);
  leg->Draw();

  return;
}
