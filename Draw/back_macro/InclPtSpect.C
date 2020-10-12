#include "./SourceFun.h"

void InclPtSpect(){
  
  //TString sPath = "/home/cuipengyao/study/pPb/Strangeness/Local/Combine_inJetAna";
  TString sPath = "/home/cuipengyao/study/pPb/Strangeness/UPDATE_wOmega/Local/Inclusive_ZNA";
  TString sFile = "";
  TString sList = "";
  TString sHist = "hNco";
  //TString sHist = "hSco";

  sFile = "AnalysisOutputs_Results.root";
  sList = "listResults_Kshort";

  //TString sCent[] = {"05", "510",  "1020", "2040", "4060", "6080", "80100", "0100"}; 
  //TString sLeg[] = {"0-5%", "5-10%", "10-20%", "20-40%", "40-60%", "60-80%", "80-100%", "0-100%"}; 
  TString sCent[] = {"2040"}; 
  TString sLeg[] = {"20-40%"}; 

  auto sLatex("#Xi spectra");
  //-----------------------------------
  TCanvas *can = nullptr;

  TFile *f = TFile::Open("./result/PtSpect_test.root", "update");
  can = MakeCanvas("can");
  can->SetLogy();
  can->SetGridx(); can->SetGridy();

  auto leg = new TLegend(0.7,0.9,1.0,0.6);    
  //-----------------------------------
  auto nHist = sizeof(sCent)/sizeof(TString);
  for (Int_t i = 0; i< nHist; i++){
    TString sMyList = Form("%s_%s", sList.Data(), sCent[i].Data()); 
    TH1D* h1 = (TH1D*)GetTH1D(sPath.Data(), sFile.Data(), sMyList.Data(), sHist.Data());
    h1->SetName(Form("hist_%d", i)); 
    NormHistBinWidth(h1);
    //TH1D* h2 = (TH1D*)GetTH1D(sPath.Data(), sFile.Data(), sMyList.Data(), "hEvent");
    //NormIncl(h1, h2); 
    for(Int_t j =1; j<= h1->GetNbinsX(); j++){
      auto dBinCent = h1->GetXaxis()->GetBinCenter(j);
      auto dContent = h1->GetBinContent(j); 
      auto dError   = h1->GetBinError(j); 
      h1->SetBinContent(j, dContent/dBinCent);
      h1->SetBinError (j, dError/dBinCent);
    }
    
    f->cd(); h1->Write(Form("hPtIncl_Kshort_%s", sCent[i].Data()), TObject::kSingleKey);
       
    SetFrame(h1, "#it{p}_{T}(GeV/#it{c})", "1/2#pi 1/#it{p}_{T} 1/#it{N}_{ev} d^{2}#it{N}/(d#it{p}_{T}d#it{y})(#it{c}/GeV)^{2}");
    //SetFrame(h1, "#it{p}_{T}", "1/#it{N}_{ev} #times (#Delta #varphi #Delta #eta)^{-1} #times d#it{N}/d#it{p}_{T}(#it{c}/GeV)");
    DrawHisto(h1, cLine[i], sMark[i], "same");
    //h1->Draw("same"); 
    leg->AddEntry(h1,sLeg[i],"lp");
  }

  f->Close();

  TLatex*     tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  SetLegend(leg);
  tex->DrawLatex(0.16, 0.91, sLatex);
  tex->DrawLatex(0.5, 0.91, "V0A multiplicity event classes");
  tex->DrawLatex(0.16, 0.3, "0 < y_{CMS} < 0.5");
  tex->DrawLatex(0.16, 0.2, "p-Pb #sqrt{#it{s}_{NN}} = 5.02 TeV");
  leg->Draw();
  gStyle->SetOptStat("");
  CanvasEnd(can);

  //can->SaveAs("./figure/Kshort_Incl.eps");
  return;
}
