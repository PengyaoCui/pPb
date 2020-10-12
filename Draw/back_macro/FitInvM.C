#include "./SourceFun.h"

void fitInvM(Int_t ptBin = 1, TString CentMin = "10", TString CentMax = "40");
void FitInvM(){

	fitInvM(1);
	fitInvM(2);
	fitInvM(3);
	fitInvM(4);
	fitInvM(5);
	fitInvM(6);
	fitInvM(7);
	fitInvM(8);
	fitInvM(9);
	fitInvM(10);
	fitInvM(11);
	fitInvM(12);
	fitInvM(13);
	fitInvM(14);
	fitInvM(15);
	fitInvM(16);
	fitInvM(17);
	fitInvM(18);
	fitInvM(19);
	fitInvM(20);
	fitInvM(21);
	
}

void fitInvM(Int_t ptBin = 1, TString CentMin = "0", TString CentMax = "100"){

  auto PtBin = ptBin;
  TString sPath = "/home/cuipengyao/study/pPb/Local/ThisAna/Incl"; 
  TString sFile = "AnalysisOutputs_FitInvMrd.root";
  TString sList = Form("listFitInvMrd_AntiLa_Default_%s%s", CentMin.Data(), CentMax.Data());
  TString sHist = Form("hFitInvM_%d", PtBin);

  auto sLatex(Form("AntiLa Inv.Mass at centrality bin %s-%s%%", CentMin.Data(), CentMax.Data()));
  //-----------------------------------

  //TString sPtBin[] = {"0.6", "0.8", "1.0", "1.2", "1.6", "2.0", "2.2", "2.4", "2.6", "2.8", "3.2", "3.7", "4.2", "5.0"};//for AntiLa
  TString sPtBin[] = {"0.6", "0.7", "0.8", "0.9", "1.0", "1.1", "1.2", "1.4", "1.6", "1.8", "2.0", "2.2", "2.4", "2.6", "2.8", "3.2", "3.7", "4.2", "5.0", "6.0", "8.0", "12."}; //for V0 
  TString sLeg = Form("%s < #it{p}_{T} < %s", sPtBin[PtBin -1].Data(), sPtBin[PtBin].Data());
  TCanvas *can = nullptr;
  can = MakeCanvas(Form("can_%d", ptBin));
  can->SetLogy();
  can->SetGridx(); can->SetGridy();

  auto leg = new TLegend(0.7,0.9,1.0,0.6);    
  //-----------------------------------
  
  TH1D* h1 = (TH1D*)GetTH1D(sPath.Data(), sFile.Data(), sList.Data(), sHist.Data());

  TF1* fS = h1->GetFunction(Form("fFitInvM_%d", PtBin));
  Double_t dWidth = fS->GetParameter(2);
  Double_t dMass = fS->GetParameter(1);
  h1->GetXaxis()->SetRangeUser((dMass-12*dWidth)*0.9912, (dMass+12*dWidth)*1.002);//for la
  auto dMini = h1->GetMinimum();
  auto dMaxi = h1->GetMaximum();
  h1->GetYaxis()->SetRangeUser(0.8*dMini, 2*dMaxi);
  h1->SetName("Hist"); 
  SetFrame(h1, "Inv.Mass (GeV/#it{c}^{2})", "Counts");
  DrawHisto(h1, cLine[0], sMark[0], "same");
  leg->AddEntry(h1,sLeg,"");
  

  TF1* fB = (TF1*)GetTH1D(sPath.Data(), "AnalysisOutputs_FitCbinRD.root", Form("listFitCbinRD_AntiLa_Default_%s%s", CentMin.Data(), CentMax.Data()), Form("fBkgVarF_%d", PtBin));
  fB->SetLineWidth(3);
  fB->SetLineColor(kRed);
  fB->Draw("same");
 
  TLine*   lLMin = new TLine(dMass-12*dWidth, 0, dMass-12*dWidth, h1->GetBinContent(h1->FindBin(dMass-12*dWidth)));
  lLMin->SetLineColor(kBlack);
  lLMin->SetLineWidth(2);
  lLMin->Draw("same");
  
  TLine*   lRMax = new TLine(dMass+12*dWidth, 0, dMass+12*dWidth, h1->GetBinContent(h1->FindBin(dMass+12*dWidth)));
  lRMax->SetLineColor(kBlack);
  lRMax->SetLineWidth(2);
  lRMax->Draw("same");

  
  auto hS = (TH1D*)h1->Clone("HIST_2");
  hS->GetXaxis()->SetRangeUser(dMass-6*dWidth, dMass+6*dWidth);
  hS->SetFillStyle(3002);
  hS->SetFillColor(38);
  hS->Draw("histsame");

  //auto h2 = (TH1D*)h1->Clone("HIST_2");
  //h2->GetXaxis()->SetRangeUser(dMass-12*dWidth, dMass-6*dWidth);
  //h2->SetFillStyle(3002);
  //h2->SetFillColor(38);
  //h2->Draw("histsame");

  //auto h3 = (TH1D*)h1->Clone("HIST_3");
  //h3->GetXaxis()->SetRangeUser(dMass+6*dWidth, dMass+12*dWidth);
  //h3->SetFillStyle(3002);
  //h3->SetFillColor(38);
  //h3->Draw("histsame");
  
  TLatex*     tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  SetLegend(leg);
  //tex->DrawLatex(0.16, 0.91, Form("#AntiLa Inv.Mass at centrality bin %s-%s%%", CentMin.Data(), CentMax.Data()));
  tex->DrawLatex(0.16, 0.91, sLatex);
  leg->Draw();
  gStyle->SetOptStat("");

  CanvasEnd(can);
  can->SaveAs(Form("./figure/InvM/AntiLa_InvM_%s%s_%d.eps", CentMin.Data(), CentMax.Data(), ptBin));
  //TFile *f = TFile::Open("./result/FitAntiLaInvM.root", "UPDATE");
  //f->cd(); can->Write(Form("InvM_Cent%s%s_ptBin%d", CentMin.Data(), CentMax.Data(), ptBin), TObject::kSingleKey);
  //f->Close();
  return;
}
