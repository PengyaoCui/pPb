#include <TF1.h>
//#include "style.h"
void Histo(){

  Double_t const eta=0.75;
  Double_t const yCMS=0.5;
  Double_t const dCentMin=0.;
  Double_t const dCentMax=100.;

  TFile *f1    = TFile::Open("AnalysisResults_MC.root"); 
  TList *flist = (TList *)f1->Get("listCascadeMakerMC");  
  const auto hsV0   = (THnSparseD*)flist->FindObject("hsV0");
  const auto hsXi   = (THnSparseD*)flist->FindObject("hsXi");
  
  auto iCentMin = -1.;
  auto iCentMax = -1.;
  iCentMin = hsXi->GetAxis(6)->FindBin(dCentMin);
  iCentMax = hsXi->GetAxis(6)->FindBin(dCentMax);
  
  auto yCmsMin=0;
  auto yCmsMax=0;
  yCmsMin = hsXi->GetAxis(3)->FindBin(0.+1e-12);
  yCmsMax = hsXi->GetAxis(3)->FindBin(0.5-1e-12);
  
  auto hsKshort = (THnSparseD*)hsV0->Clone("hsKshort");
  hsKshort->GetAxis(6)->SetRange(iCentMin, iCentMax);
  hsKshort->GetAxis(3)->SetRange(yCmsMin, yCmsMax);
  hsKshort->GetAxis(5)->SetRange(1, 1);
  auto hPtKshort =(TH1D*)hsKshort->Projection(0);
  hPtKshort->SetName("Kshort"); 

  auto hsLambda = (THnSparseD*)hsV0->Clone("hsLambda");
  hsLambda->GetAxis(6)->SetRange(iCentMin, iCentMax);
  hsLambda->GetAxis(3)->SetRange(yCmsMin, yCmsMax);
  hsLambda->GetAxis(5)->SetRange(2, 2);
  auto hPtLambda =(TH1D*)hsLambda->Projection(0);
  hPtLambda->SetName("Lambda"); 
   
  auto hsAntiLa = (THnSparseD*)hsV0->Clone("hsAntiLa");
  hsAntiLa->GetAxis(6)->SetRange(iCentMin, iCentMax);
  hsAntiLa->GetAxis(3)->SetRange(yCmsMin, yCmsMax);
  hsAntiLa->GetAxis(5)->SetRange(3, 3);
  auto hPtAntiLa =(TH1D*)hsAntiLa->Projection(0);
  hPtAntiLa->SetName("AntiLa"); 
   
  auto hsXiNeg = (THnSparseD*)hsXi->Clone("hsXiNeg");
  hsXiNeg->GetAxis(6)->SetRange(iCentMin, iCentMax);
  hsXiNeg->GetAxis(3)->SetRange(yCmsMin, yCmsMax);
  hsXiNeg->GetAxis(5)->SetRange(1, 1);
  auto hPtXiNeg =(TH1D*)hsXiNeg->Projection(0);
  hPtXiNeg->SetName("XiNeg"); 

  auto hsXiPos = (THnSparseD*)hsXi->Clone("hsXiPos");
  hsXiPos->GetAxis(6)->SetRange(iCentMin, iCentMax);
  hsXiPos->GetAxis(3)->SetRange(yCmsMin, yCmsMax);
  hsXiPos->GetAxis(5)->SetRange(2, 2);
  auto hPtXiPos =(TH1D*)hsXiPos->Projection(0);
  hPtXiPos->SetName("XiPos"); 
  
  auto hsOmegaNeg = (THnSparseD*)hsXi->Clone("hsOmegaNeg");
  hsOmegaNeg->GetAxis(6)->SetRange(iCentMin, iCentMax);
  hsOmegaNeg->GetAxis(3)->SetRange(yCmsMin, yCmsMax);
  hsOmegaNeg->GetAxis(5)->SetRange(3, 3);
  auto hPtOmegaNeg =(TH1D*)hsOmegaNeg->Projection(0);
  hPtOmegaNeg->SetName("OmegaNeg"); 

  auto hsOmegaPos = (THnSparseD*)hsXi->Clone("hsOmegaPos");
  hsOmegaPos->GetAxis(6)->SetRange(iCentMin, iCentMax);
  hsOmegaPos->GetAxis(3)->SetRange(yCmsMin, yCmsMax);
  hsOmegaPos->GetAxis(5)->SetRange(4, 4);
  auto hPtOmegaPos =(TH1D*)hsOmegaPos->Projection(0);
  hPtOmegaPos->SetName("OmegaPos"); 

//================================================================================================

  TFile *output = TFile::Open("histos.root","NEW"); TList *listxx = new TList();
  listxx->Add(hPtKshort);
  listxx->Add(hPtLambda);
  listxx->Add(hPtAntiLa);
  listxx->Add(hPtXiNeg);
  listxx->Add(hPtXiPos);
  listxx->Add(hPtOmegaNeg);
  listxx->Add(hPtOmegaPos);

  output->cd(); listxx->Write(); output->Close();

}

TH1D *GetTH1D(char *file,char *list , char * name){

  TFile *f1  = TFile::Open(file);
  if(list){
    TList *flist = (TList *)f1->Get(list);
    cout<<(TH1D*)flist->FindObject(name)<<endl;
    return (TH1D*)flist->FindObject(name);
  }else{

    return (TH1D*)f1->Get(name);
  }
 cout<<(TH1D*)f1->Get(name)<<endl;
}
