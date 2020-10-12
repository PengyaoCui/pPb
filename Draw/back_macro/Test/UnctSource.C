#include "./SourceFun.h"

void UnctSource(const TString sType = "Xi", const TString CentMin = "0", const TString CentMax = "100", const TString sUncertType = "Topological"){
               
  TString UncertType = sUncertType;
  TString sCut[] = {"VLoose", "Loose", "Tight", "VTight"}; 
  const Int_t nCut = sizeof(sCut)/sizeof(TString);
  TString Cut[nCut];
  for(Int_t n = 0; n<nCut; n++){Cut[n] = sCut[n];}

  TString sPath = Form("/home/cuipengyao/study/Backup/pPb_20200511/Strangeness/Local/Uncertainty_V0/%s", UncertType.Data());
  TString sFile = "AnalysisOutputs_Results.root";
  TString sList = "listResults";
  TString sHist = "hNco";
  if(sType == "Lambda" || sType == "AntiLa") sFile = "AnalysisOutputs_MakeLaFdR.root";
  if(sType == "Lambda" || sType == "AntiLa") sList = "listMakeLaFdR";
  if(sType == "Lambda" || sType == "AntiLa") sHist = "hPtLaNormCorr";
  TString List = Form("%s_%s_Default_%s%s", sList.Data(), sType.Data(), CentMin.Data(), CentMax.Data());

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
  auto nHist = sizeof(Cut)/sizeof(TString);
  const auto nhist = nHist;

  TH1D* h2 = nullptr;
  TH1D* h1 = nullptr;
  TH1D* hRatio = nullptr;
  TH1D* hU[nhist];
  h2 = (TH1D*)GetTH1D(Form("/home/cuipengyao/study/Backup/pPb_20200511/Strangeness/Local/Uncertainty_V0/Default"), sFile.Data(), List.Data(), sHist.Data());
  h2->SetName("Default");
  h2->SetTitle("");

  //TFile *f = TFile::Open("./result/UncertaintySource.root", "UPDATE");
  //TList *l = new TList();
  for (Int_t i = 0; i< nHist; ++i){
    TString sMyPath = Form("%s/%s", sPath.Data(), Cut[i].Data()); 
    TString sMyFile = sFile; 
    TString sMyList = List; 
    TString sMyHist = sHist; 
    h1 = (TH1D*)GetTH1D(sMyPath.Data(), sMyFile.Data(), sMyList.Data(), sMyHist.Data());
    h1->SetName(Form("hist_%d", i));
    hRatio = (TH1D*) h2->Clone(Form("hRatio_%d", i)); hRatio->Reset();
    for(Int_t j = 1; j <= h2->GetNbinsX(); j++){
      Double_t dVar1 = h1->GetBinContent(j); 
      Double_t dErr1 = h1->GetBinError(j); 
      Double_t dVar2 = h2->GetBinContent(j);
      Double_t dErr2 = h2->GetBinError(j);
      Double_t dVar = TMath::Abs((dVar1 - dVar2)/dVar2); 
      Double_t dErr = TMath::Sqrt((dVar1*dVar1)*(dErr2*dErr2) + (dVar2*dVar2)*(dErr1*dErr1)); 
      
      if (TMath::Abs(dVar1 - dVar2)/(TMath::Sqrt(TMath::Abs(dErr1*dErr1 - dErr2*dErr2))+1e-12) > 1 ){
        hRatio->SetBinContent(j, dVar);
        hRatio->SetBinError(j, dErr);
        //hRatio->SetBinError(j, 0);
      }else{
        hRatio->SetBinContent(j, 0.);
        hRatio->SetBinError(j, 1e-12);
      }
    } 
    hRatio->SetName(Cut[i]);
    hRatio->GetYaxis()->SetRangeUser(0., 0.1);
    DrawHisto(hRatio, cLine[i], sMark[i], "same");
    SetFrame(hRatio, "#it{p}_{T}(GeV/#it{c})", Form("Relative syst. on %s", sUncertType.Data()));
    leg->AddEntry(hRatio, Cut[i],"l");
    //l->Add(hRatio);
    hU[i] = hRatio;
  }
  auto hUMax = (TH1D*)MaxHistograms(nhist, hU);
  DrawHisto(hUMax, cLine[nhist], sMark[nhist], "same");
  SetFrame(hUMax, "#it{p}_{T}(GeV/#it{c})", Form("Relative syst. on %s", sUncertType.Data()));
  leg->AddEntry(hUMax, "Max","l");
  //l->Add(hUMax);
  
  //f->cd(); 
  //l->Write(Form("%s_Topological_%s%s",sType.Data(), CentMin.Data(), CentMax.Data()), TObject::kSingleKey);
  //f->Close();

  tex =  new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.15, 0.9, sLatex);
  leg->Draw();
  gStyle->SetOptStat("");
  //can->SaveAs(Form("./figure/%s_%s_%s%s.eps", sType.Data(), sUncertType.Data(), CentMin.Data(), CentMax.Data()));
  CanvasEnd(can);
  return;
}
