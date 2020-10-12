#include "./SourceFun.h"

void UncerJet(const TString sType = "Kshort", const TString CentMin = "0", const TString CentMax = "100"){
               
  TString sCut[] = {"Tight", "Loose"}; 
  
  TString sPath = "/home/cuipengyao/study/pPb/Local/ThisAna/Uncertainty/JE"; 
  TString sFile = "AnalysisOutputs_Results.root";
  TString sList = "listResults";
  TString sHist = "hNco";
  if(sType == "Lambda" || sType == "AntiLa") sFile = "AnalysisOutputs_MakeLaFdR.root";
  if(sType == "Lambda" || sType == "AntiLa") sList = "listMakeLaFdR";
  if(sType == "Lambda" || sType == "AntiLa") sHist = "hPtLaNormCorr";
  TString List = Form("%s_%s_Default_JC_%s%s", sList.Data(), sType.Data(), CentMin.Data(), CentMax.Data());
  TString UEList = Form("%s_%s_Default_PCL_%s%s", sList.Data(), sType.Data(), CentMin.Data(), CentMax.Data());

  TString sLeg = "Total";

  auto sLatex(Form("Uncertainty of %s in %s-%s%%", sType.Data(), CentMin.Data(), CentMax.Data()));
  Double_t XMin = 0.6;
  Double_t XMax = 12.;
  //-----------------------------------
  TCanvas *can = nullptr;
  TLatex* tex = nullptr;
  TLegend *leg = nullptr;
  can = MakeCanvas("can");
 
  leg = new TLegend(0.7,0.9,1.0,0.6); SetLegend(leg);
  //-----------------------------------
  auto nHist = sizeof(sCut)/sizeof(TString);
  const auto nhist = nHist;

  TH1D* h0 = nullptr;
  TH1D* hUE0 = nullptr;
  TH1D* h2 = nullptr;
  TH1D* hUE2 = nullptr;
  TH1D* h1 = nullptr;
  TH1D* hUE1 = nullptr;
  TH1D* hRatio = nullptr;
  //-------------------------------Default JE
  h2 = (TH1D*)GetTH1D(Form("/home/cuipengyao/study/pPb/Local/ThisAna/JEBins"), sFile.Data(), List.Data(), sHist.Data());
  h2->SetName("Default");
  h2->SetTitle("");
  NormHistBinWidth(h2);  
  if((sType != "Lambda") && (sType != "AntiLa")) {
    hUE2 = (TH1D*)GetTH1D(Form("/home/cuipengyao/study/pPb/Local/ThisAna/JEBins"), sFile.Data(), UEList.Data(), sHist.Data());
    hUE2->SetName("DefaultUE");
    hUE2->SetTitle("");
    NormHistBinWidth(hUE2);
    h2->Add(hUE2, -1.);
  }

  TFile *f = TFile::Open("./result/JetPtUncertainty.root", "UPDATE");
  TList *l = new TList();
  
  TString sMyPath = Form("%s/%s", sPath.Data(), sCut[0].Data()); 
  h0 = (TH1D*)GetTH1D(sMyPath.Data(), sFile.Data(), List.Data(), sHist.Data());
  NormHistBinWidth(h0);
  h0->SetName(Form("hist_0"));
  if((sType != "Lambda") && (sType != "AntiLa")) {
    hUE0 = (TH1D*)GetTH1D(sMyPath.Data(), sFile.Data(), UEList.Data(), sHist.Data());
    hUE0->SetName(Form("UEhist_0"));
    NormHistBinWidth(hUE0);
    h0->Add(hUE0, -1.); 
    l->Add(h0);
  }
  
  sMyPath = Form("%s/%s", sPath.Data(), sCut[1].Data()); 
  h1 = (TH1D*)GetTH1D(sMyPath.Data(), sFile.Data(), List.Data(), sHist.Data());
  NormHistBinWidth(h1);
  h1->SetName(Form("hist_1"));
  if((sType != "Lambda") && (sType != "AntiLa")) {
    hUE1 = (TH1D*)GetTH1D(sMyPath.Data(), sFile.Data(), UEList.Data(), sHist.Data());
    hUE1->SetName(Form("UEhist_1"));
    NormHistBinWidth(hUE1);
    h1->Add(hUE1, -1.); 
    l->Add(h1);
  }
  hRatio = (TH1D*) h2->Clone(Form("hRatio")); hRatio->Reset();
  for(Int_t j = 1; j <= h2->GetNbinsX(); j++){
    Double_t dVar0 = h0->GetBinContent(j); 
    Double_t dErr0 = h0->GetBinError(j); 
    Double_t dVar1 = h1->GetBinContent(j); 
    Double_t dErr1 = h1->GetBinError(j); 
    Double_t dVar2 = h1->GetBinContent(j); 
    Double_t dErr2 = h1->GetBinError(j); 
     
    Double_t dVar = TMath::Abs((dVar0 - dVar1)/(dVar2*TMath::Sqrt(12.))); 
    //Double_t dErr = TMath::Sqrt(TMath::Abs((dErr0*dErr0) - (dErr1*dErr1))/12.); 
    Double_t dErr = 0; 
    hRatio->SetBinContent(j, dVar);
    hRatio->SetBinError(j, dErr);
  } 
  hRatio->SetName("hMax");
  //hRatio->Divide(h2);
  hRatio->GetYaxis()->SetRangeUser(0., 0.5);
  DrawHisto(hRatio, cLine[0], sMark[0], "same");
  SetFrame(hRatio, "#it{p}_{T}(GeV/#it{c})", "Relative syst. on JetPt");
  leg->AddEntry(hRatio, "Max","l");
  l->Add(hRatio);

  TF1 *f0 = new TF1("fFit", "[0]", XMin, XMax); 
  f0->SetParameter(0, 0.1);
  hRatio->Fit(f0, "L0+");
  TH1D* hFit = (TH1D*)hRatio->Clone("hFit");hFit->Reset();
  for(Int_t n =1; n<= hFit->GetNbinsX(); n++){ hFit->SetBinContent(n, f0->GetParameter(0)); hFit->SetBinError(n, 0);}
  DrawHisto(hFit, cLine[nhist+1], sMark[nhist+1], "same");
  SetFrame(hFit, "#it{p}_{T}(GeV/#it{c})", "Relative syst. on JetPt");
  hFit->SetLineStyle(2);
  l->Add(hFit);
  
  f->cd(); 
  l->Write(Form("%s_JetPt_%s%s",sType.Data(), CentMin.Data(), CentMax.Data()), TObject::kSingleKey);
  f->Close();

  tex =  new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.15, 0.9, sLatex);
  leg->Draw();
  gStyle->SetOptStat("");
  can->SaveAs(Form("./figure/Uncert/%s_JetPt_%s%s.eps", sType.Data(), CentMin.Data(), CentMax.Data()));
  CanvasEnd(can);
  return;
}
