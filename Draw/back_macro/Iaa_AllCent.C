#include "./SourceFun.h"

void Iaa_AllCent(){
  const TString CentMin[] = {"0", "10", "40", "0"};
  const TString CentMax[] = {"10", "40", "100", "100"};
  const TString sType = "Xi";
  //p-Pb 
  auto sPath = "./result"; 
  auto sCFile = "PtSpect_Eta.root";
  auto sCJetHist = "";
  //pp
  TString sPath_pp = "/home/cuipengyao/study/pp/Draw/macro/result";
  TString sFile_pp = Form("PtSpect_Eta_16-17.root"); 
  TString sJE1pp = Form("hPtJE_%s", sType.Data()); 
  if(sType == "Lambda" || sType == "AntiLa") sJE1pp = Form("hPtJC_%s", sType.Data());

  auto hJE1pp = (TH1D*)GetTH1D(sPath_pp, sFile_pp, "", sJE1pp); hJE1pp->SetName("JECenpp");
 

  auto sLatex(Form("p-Pb #sqrt{#it{s}_{NN}} = 5.02 TeV"));
  Double_t XMin = 0.6;
  Double_t XMax = 12.;
  
  //-----------------------------------
  TCanvas *can = nullptr;
  TLatex* tex = nullptr;
  TLegend *leg = nullptr;
  can = MakeCanvas("can");
  leg = new TLegend(0.7,0.9,1.0,0.6); SetLegend(leg);
 
  TH1D* hJE1 = nullptr;
  TH1D* JEIaa = nullptr;
  auto nHist = sizeof(CentMin)/sizeof(TString);
  TFile *f = TFile::Open("./result/IAA_woSysErr.root", "UPDATE");
 
  for (Int_t i = 0; i< nHist; ++i){
    sCJetHist = Form("hPtJE_%s_%s%s", sType.Data(), CentMin[i].Data(), CentMax[i].Data());
    if(sType == "Lambda" || sType == "AntiLa") sCJetHist = Form("hPtJC_%s_%s%s", sType.Data(), CentMin[i].Data(), CentMax[i].Data());
    hJE1  = (TH1D*)GetTH1D(sPath, sCFile, "", sCJetHist); hJE1->SetName("JECen");
    hJE1->SetName(Form("hJE1_%d", i));

    //-----------------------------------
    JEIaa = (TH1D*)hJE1->Clone(Form("JEIaa_%d", i));JEIaa->Reset();
    hJE1pp = RebinTH1D(hJE1pp, hJE1); 
    JEIaa->Divide(hJE1, hJE1pp);
    JEIaa->GetYaxis()->SetRangeUser(0., 3.);
    JEIaa->GetYaxis()->SetTitle("#it{I}_{pPb}");
    JEIaa->GetXaxis()->SetRangeUser(XMin, XMax);
    leg->AddEntry(JEIaa, Form("%s-%s%%",CentMin[i].Data(), CentMax[i].Data()), "lp");

    DrawHisto(JEIaa, cLine[i], sMark[i], "same"); 
    f->cd(); JEIaa->Write(Form("%s_%s%s", sType.Data(), CentMin[i].Data(), CentMax[i].Data()), TObject::kSingleKey); 
  }
  f->Close();

  TLine* l = new TLine(XMin, 1., XMax, 1.);
  l->SetLineColor(kRed);
  l->SetLineStyle(2);
  l->SetLineWidth(2);
  l->Draw("same");
  //-----------------------------------
  tex =  new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.15, 0.9, sType);
  tex->DrawLatex(0.15, 0.8, sLatex);
  leg->Draw();
  gStyle->SetOptStat("");
  //can->SaveAs(Form("./figure/%s_IAA_woSysError_AllCent.eps", sType.Data()));
  //DrawAliLogo(0.65, 0.90, 24, kTRUE);
  CanvasEnd(can);
  return;
}
