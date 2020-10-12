#include "./SourceFun.h"

void UnctSource(const TString sType = "Kshort", const TString CentMin = "0", const TString CentMax = "100", const TString sUncertType = "Topological"){
 
  auto IsSaveCan = kFALSE;
  auto IsSaveFile = kTRUE;
  
  Int_t nCut;
 
  if(sType =="Kshort"){
    if( sUncertType == "CompetMass") nCut = 2;
    if( sUncertType == "MLoverP") nCut = 3;
    if( sUncertType == "SigExtrac")nCut = 3;
    if( sUncertType == "Topological")nCut = 4;
    if( sUncertType == "TPCPID")nCut = 2;
    if( sUncertType == "TrackQuality") nCut = 3;
  }
  
  if(sType == "Lambda" || sType == "AntiLa"){
    if( sUncertType == "MLoverP") nCut = 4;
    if( sUncertType == "SigExtrac")nCut = 3;
    if( sUncertType == "Topological")nCut = 4;
    if( sUncertType == "TPCPID")nCut = 2;
    if( sUncertType == "TrackQuality") nCut = 3;
  } 
 
  if(sType =="Xi"){
    if( sUncertType == "MLoverP") nCut = 4;
    if( sUncertType == "SigExtrac")nCut = 2;
    if( sUncertType == "Topological")nCut = 4;
    if( sUncertType == "TPCPID")nCut = 2;
    if( sUncertType == "TrackQuality") nCut = 2;
  }

  if(sType =="Omega"){
    if( sUncertType == "MLoverP") nCut = 4;
    if( sUncertType == "SigExtrac")nCut = 2;
    if( sUncertType == "Topological")nCut = 3;
    if( sUncertType == "TPCPID")nCut = 2;
    if( sUncertType == "TrackQuality") nCut = 2;
  }
  
  const Int_t nNCut = nCut; TString Cut[nNCut];
  
  if(sType == "Kshort"){
    if(sUncertType == "CompetMass"){ Cut[0] = "Loose"; Cut[1] ="Tight"; } 
    if(sUncertType == "MLoverP"){ Cut[0] = "VLoose"; Cut[1] = "Loose"; Cut[2] ="Tight"; } 
    if(sUncertType == "SigExtrac"){ Cut[0] = "Loose"; Cut[1] = "Tight"; Cut[2] = "VTight";} 
    if(sUncertType == "Topological"){ Cut[0] = "VLoose"; Cut[1] = "Loose"; Cut[2] ="Tight"; Cut[3] = "VTight";} 
    if(sUncertType == "TPCPID"){ Cut[0] = "Loose"; Cut[1] = "Tight"; }
    if(sUncertType == "TrackQuality"){ Cut[0] = "nCrosRows/Tight"; Cut[1] = "nCrosRows/VTight"; Cut[2] ="nCrosRowsOverFind/Tight";} 
  }
  
  if(sType == "Lambda" || sType == "AntiLa"){
    if(sUncertType == "MLoverP"){ Cut[0] = "VLoose"; Cut[1] = "Loose"; Cut[2] ="Tight"; Cut[3] ="VTight"; } 
    if(sUncertType == "SigExtrac"){ Cut[0] = "Loose"; Cut[1] = "Tight"; Cut[2] = "VTight";} 
    if(sUncertType == "Topological"){ Cut[0] = "VLoose"; Cut[1] = "Loose"; Cut[2] ="Tight"; Cut[3] = "VTight";} 
    if(sUncertType == "TPCPID"){ Cut[0] = "Loose"; Cut[1] = "Tight"; }
    if(sUncertType == "TrackQuality"){ Cut[0] = "nCrosRows/Tight"; Cut[1] = "nCrosRows/VTight"; Cut[2] ="nCrosRowsOverFind/Tight";} 
  }
 
  if(sType == "Xi"){
    if(sUncertType == "MLoverP"){ Cut[0] = "VvLoose"; Cut[1] = "VLoose"; Cut[2] ="Loose";  Cut[3] ="Tight"; } 
    if(sUncertType == "SigExtrac"){ Cut[0] = "Loose"; Cut[1] = "Tight";} 
    if(sUncertType == "Topological"){ Cut[0] = "VLoose"; Cut[1] = "Loose"; Cut[2] ="Tight"; Cut[3] = "VTight";} 
    if(sUncertType == "TPCPID"){ Cut[0] = "Loose"; Cut[1] = "Tight"; }
    if(sUncertType == "TrackQuality"){ Cut[0] = "Tight"; Cut[1] = "VTight";} 
  }

  if(sType == "Omega"){
    if(sUncertType == "MLoverP"){ Cut[0] = "VvLoose"; Cut[1] = "VLoose"; Cut[2] ="Loose";  Cut[3] ="Tight"; } 
    if(sUncertType == "SigExtrac"){ Cut[0] = "Loose"; Cut[1] = "Tight";} 
    if(sUncertType == "Topological"){ Cut[0] = "VLoose"; Cut[1] = "Loose"; Cut[2] ="Tight"; } 
    if(sUncertType == "TPCPID"){ Cut[0] = "Loose"; Cut[1] = "Tight"; }
    if(sUncertType == "TrackQuality"){ Cut[0] = "Tight"; Cut[1] = "VTight";} 
  }

  TString sPath = Form("/home/cuipengyao/study/pPb/Local/ThisAna/Uncertainty/Incl/%s/%s", sType.Data(), sUncertType.Data());
  TString sFile = "AnalysisOutputs_Results.root";
  TString sList = "listResults";
  TString sHist = "hNco";
  //if(sType == "Lambda" || sType == "AntiLa") sFile = "AnalysisOutputs_MakeLaFdR.root";
  //if(sType == "Lambda" || sType == "AntiLa") sList = "listMakeLaFdR";
  //if(sType == "Lambda" || sType == "AntiLa") sHist = "hPtLaNormCorr";
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
  can->SetGridy(); 
  can->SetGridx(); 
  leg = new TLegend(0.7,0.9,1.0,0.6); SetLegend(leg);
  //-----------------------------------
  auto nHist = sizeof(Cut)/sizeof(TString);
  const auto nhist = nHist;

  TH1D* h2 = nullptr;
  TH1D* h1 = nullptr;
  TH1D* hRatio = nullptr;
  TH1D* hU[nhist];
  h2 = (TH1D*)GetTH1D(Form("/home/cuipengyao/study/pPb/Local/ThisAna/Incl"), sFile.Data(), List.Data(), sHist.Data());
  if(sType == "Xi")h2 = (TH1D*)GetTH1D(Form("/home/cuipengyao/study/pPb/Local/ThisAna/Uncertainty/Incl/Xi/MLoverP/Default"), sFile.Data(), List.Data(), sHist.Data());
  h2->SetName("Default");
  h2->SetTitle("");

  TFile *f = TFile::Open("./result/UncertaintySource.root", "UPDATE");
  //TFile *f = TFile::Open("./result/TestSource.root", "UPDATE");
  TList *l = new TList();
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
      if(sType == "Omega" && sUncertType == "Topological") dVar = 0.5*dVar;
      //Double_t dErr = TMath::Sqrt((dVar1*dVar1)*(dErr2*dErr2) + (dVar2*dVar2)*(dErr1*dErr1)); 
      Double_t dErr = TMath::Sqrt(TMath::Abs(dErr2*dErr2 - dErr1*dErr1)); 
      
      if (TMath::Abs(dVar1 - dVar2)/(TMath::Sqrt(TMath::Abs(dErr1*dErr1 - dErr2*dErr2))+1e-12) > 1 ){
        hRatio->SetBinContent(j, dVar);
        hRatio->SetBinError(j, dErr);
        if(IsSaveCan)hRatio->SetBinError(j, 0);
      }else{
        hRatio->SetBinContent(j, 0.);
        hRatio->SetBinError(j, 1e-12);
        if(IsSaveCan)hRatio->SetBinError(j, 0);
      }
    } 
    hRatio->SetName(Cut[i]);
    hRatio->GetYaxis()->SetRangeUser(0., 0.1);
    if(sType == "Xi" || sType == "Omega")hRatio->GetYaxis()->SetRangeUser(0., 0.2);
    DrawHisto(hRatio, cLine[i], sMark[i], "same");
    SetFrame(hRatio, "#it{p}_{T}(GeV/#it{c})", Form("Relative syst. on %s", sUncertType.Data()));
    leg->AddEntry(hRatio, Cut[i],"l");
    l->Add(hRatio);
    hU[i] = hRatio;
  }
  if(IsSaveFile){
    auto hUMax = (TH1D*)MaxHistograms(nhist, hU);
    DrawHisto(hUMax, cLine[nhist], sMark[nhist], "same");
    SetFrame(hUMax, "#it{p}_{T}(GeV/#it{c})", Form("Relative syst. on %s", sUncertType.Data()));
    leg->AddEntry(hUMax, "Max","l");
    l->Add(hUMax);
  } 
  f->cd(); 
  if(IsSaveFile) l->Write(Form("%s_%s_%s%s",sType.Data(), sUncertType.Data(), CentMin.Data(), CentMax.Data()), TObject::kSingleKey);
  f->Close();

  tex =  new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.15, 0.9, sLatex);
  tex->DrawLatex(0.15, 0.8, sUncertType);
  leg->Draw();
  gStyle->SetOptStat("");
  if(IsSaveCan) can->SaveAs(Form("./figure/Uncert/%s_%s_%s%s.eps", sType.Data(), sUncertType.Data(), CentMin.Data(), CentMax.Data()));
  CanvasEnd(can);
  return;
}


