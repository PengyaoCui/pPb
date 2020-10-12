#include "./SourceFun.h"

void MakeRatio_Graph(const TString CentMin = "0", const TString CentMax = "5", const Int_t i = 1, const Int_t j = 1 ){
                     
  
  
  TString sPathNu[] = {"./result"};
  TString sFileNu[] = {"PtSpect_Compare2LF.root"};
  TString sListNu[] = {""};
  TString sHistNu[] = {Form("hPtIncl_OmegaNeg_%s%s", CentMin.Data(), CentMax.Data())};
  TString sHistNuPos[] = {Form("hPtIncl_OmegaPos_%s%s", CentMin.Data(), CentMax.Data())};

  TString sPathDe = "./published";
  TString sFileDe = "Cascade_Published.root";
  TString sListDe = Form("Table %d", i);
  TString sHistDe = Form("Hist1D_y%d", j);
  //TString sHistDe = "Graph1D_y1";

  TString sLeg[] = {"This analysis", "RUN I published"};

  auto sLatex(Form("Inclusive #Omega Spectra (%s-%s%%)", CentMin.Data(), CentMax.Data()));
  Double_t YMin = 1e-12;
  Double_t YMax = 1e12;
  Double_t XMin = 1.;
  Double_t XMax = 4.;
  //-----------------------------------
  TCanvas *can = nullptr;
  TPad *padB = nullptr;
  TPad *padT = nullptr;
  TLatex* tex = nullptr;
  TLegend *leg = nullptr;

  can = MakeCanvas("can");

  leg = new TLegend(0.7,0.9,1.0,0.6); SetLegend(leg);
  //-----------------------------------
  auto nHist = sizeof(sHistNu)/sizeof(TString);
  const auto nhist = nHist;

  TH1D* h2 = nullptr;
  TH1D* h2E1 = nullptr;
  TH1D* h2E2 = nullptr;
  //TGraphAsymmErrors* g2 = nullptr;
  TH1D* h1 = nullptr;
  TH1D* h1Neg = nullptr;
  TH1D* h1Pos = nullptr;
  TH1D* hRatio = nullptr;

  padB = MakePadB("padB");
  can->cd();
  padT = MakePadT("padT");
  padT->SetLogy();

  auto File = TFile::Open(Form("%s/%s", sPathDe.Data(), sFileDe.Data()),"read"); if (!File->IsOpen()) return 0x0;
  auto Dir = (TDirectoryFile*)(File->Get(sListDe.Data()));
  h2 = (TH1D*)(Dir->Get(sHistDe));
  h2E1 = (TH1D*)(Dir->Get(Form("%s_e1", sHistDe.Data())));
  h2E2 = (TH1D*)(Dir->Get(Form("%s_e2", sHistDe.Data())));
  //h2 = (TH1D*)GetTH1D(sPathDe.Data(), sFileDe.Data(), sListDe.Data(), sHistDe.Data());
  //g2 = (TGraphAsymmErrors*)(Dir->Get(sHistDe.Data()));
  //for(Int_t i = 0; i<h2->GetNbinsX(); i++){h2->SetBinContent(i, 0.5*(g2->GetErrorYhigh(i) + g2->GetErrorYlow(i))); h2->SetBinError(i, g2->GetErrorY(i));} 
  for(Int_t i = 0; i<=h2->GetNbinsX(); i++){h2->SetBinError(i, TMath::Sqrt(h2E1->GetBinContent(i)*h2E1->GetBinContent(i)+ h2E2->GetBinContent(i)*h2E2->GetBinContent(i)));} 
  h2->SetTitle(""); 
  leg->AddEntry(h2,sLeg[nHist],"lp");
  padT->cd();
  h2->GetXaxis()->SetRangeUser(XMin, XMax); 
  auto dMini = h2->GetMinimum();
  auto dMaxi = h2->GetMaximum();
  h2->GetYaxis()->SetRangeUser(0.2*dMini, 5.*dMaxi);

  SetFrame(h2, "d#it{p}_{T}", "1/2#pi 1/#it{p}_{T} 1/#it{N}_{ev}d^{2}#it{N}/(d#it{p}_{T}d#it{y})(GeV/#it{c})^{-2}");
  DrawHisto(h2, cLine[nHist], sMark[nHist], "same");

  hRatio = (TH1D*) h2->Clone("hRatio"); hRatio->Reset();

  for (Int_t i = 0; i< nHist; i++){
    TString sMyPath = sPathNu[i]; 
    TString sMyFile = sFileNu[i]; 
    TString sMyList = sListNu[i]; 
    TString sMyHist = sHistNu[i]; 
    TString sMyHistPos = sHistNuPos[i]; 
    h1 = (TH1D*)GetTH1D(sMyPath.Data(), sMyFile.Data(), sMyList.Data(), sMyHist.Data());
    h1->SetName(Form("hist_%d", i));
    h1Pos = (TH1D*)GetTH1D(sMyPath.Data(), sMyFile.Data(), sMyList.Data(), sMyHistPos.Data());
    h1Pos->SetName(Form("histPos_%d", i)); 
    h1->Add(h1Pos); 
    h1->Scale(0.5);
    for(Int_t j = 1; j<=h1->GetNbinsX(); j++){
     h1->SetBinContent(j, h1->GetBinContent(j)/h1->GetXaxis()->GetBinCenter(j));
     h1->SetBinError(i, h1->GetBinError(j)/h1->GetXaxis()->GetBinCenter(j));
     //cout<<h2->GetXaxis()->GetBinUpEdge(i)<<endl;
    }  
    h1=RebinTH1D(h1, h2);
    hRatio->Divide(h1, h2);
    hRatio->SetName(Form("hratio_%d", i));
    hRatio->GetYaxis()->SetRangeUser(0.5, 1.5);
    padT->cd();
    //SetFrame(h1, "#it{p}_{T}", "d#rho/d#it{p}_{T}");
    DrawHisto(h1, cLine[i], sMark[i], "same");
    leg->AddEntry(h1,sLeg[i],"lp");
    padB->cd();
    SetFrame(hRatio, "#it{p}_{T} (GeV/#it{c})", "#frac{ThisAna}{Published}", 0.08, 0.08, 0.1, 0.1, 1.10, 0.6);
    DrawHisto(hRatio, cLine[i], sMark[i], "same");
  }


  padB->cd();
  TLine* l = new TLine(XMin, 1, XMax, 1);
  l->SetLineColor(kRed);
  l->SetLineWidth(2);
  l->Draw("same");

  padT->cd();
  tex =  new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.2, 0.9, sLatex);
  leg->Draw();
  gStyle->SetOptStat("");
  CanvasEnd(can);
  can->SaveAs(Form("./figure/Compare2LF_CENT_FAST/Omega_ComparetoLF_%s%s.eps", CentMin.Data(), CentMax.Data()));
  return;
}
