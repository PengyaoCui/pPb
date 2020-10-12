#include "../../SourceFun.h"

void current(){

  TString sPath[] = {"/home/cuipengyao/study/code/Draw/macro/Cascade_WJet_LHC16k/result"};
  TString sFile[] = {"PtSpect_Xipm_wo_Norm.root"};
  TString sHist[] = {"hPtJC_Xi"};

  //-----------------------------------
  Int_t nHist = sizeof(sHist)/sizeof(TString);
  for (Int_t i = 0; i< nHist; i++){
    TString sMyPath = sPath[i]; 
    TString sMyFile = sFile[i]; 
    TString sMyHist = sHist[i]; 
   
    TH1D* h1 = (TH1D*)GetTH1FromFile(sMyPath, sMyFile, sMyHist);
    Double_t dVar2 = 0.5*(h1->GetBinContent(1)+h1->GetBinContent(3));
    Double_t dErr2 = 0.5*TMath::Sqrt(h1->GetBinError(1)*h1->GetBinError(1) +h1->GetBinError(2)*h1->GetBinError(2));
    h1->SetBinContent(2, dVar2);
    h1->SetBinError(2, dErr2);
    for (Int_t k=1; k<=h1->GetNbinsX(); k++){
       h1->SetBinContent(k, h1->GetBinContent(k)*128/463);
       h1->SetBinError(k, h1->GetBinError(k)*128/463);
    }
    
    h1->SetName(Form("hist_%d", i)); 
    h1->Draw("same");
  TFile *file = TFile::Open("./result/PtSpect_Xipm.root", "UPDATE");
  file->cd(); h1->Write("hPtJC_Xi", TObject::kSingleKey);
  file->Close();

  }

  return;
}
