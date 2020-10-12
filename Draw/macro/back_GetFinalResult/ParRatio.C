#include "./inc/TStrangeJet.h"

//-------------------------------------------------------------
void ParRatio(){

  TFile *file = TFile::Open("./result/PtSpectra.root", "UPDATE");
  TList *listIn = (TList*)file->Get(Form("listIn")); if (!listIn){listIn = new TList();}
  TList *listJC = (TList*)file->Get(Form("listJC_LowPt06")); if (!listJC){listJC = new TList();}
  TList *listPC = (TList*)file->Get(Form("listPC_LowPt06")); if (!listPC){listPC = new TList();}
  TList *listJE = (TList*)file->Get(Form("listJE_LowPt06")); if (!listJE){listJE = new TList();}
  TList *listOC04 = (TList*)file->Get(Form("listOC04_LowPt06")); if (!listOC04){listOC04 = new TList();}
  TList *listOC06 = (TList*)file->Get(Form("listOC06_LowPt06")); if (!listOC06){listOC06 = new TList();}
  TList *listOC08 = (TList*)file->Get(Form("listOC08_LowPt06")); if (!listOC08){listOC08 = new TList();}
  TList *listNJ = (TList*)file->Get(Form("listNJ_LowPt06")); if (!listNJ){listNJ = new TList();}
  
  TH1D* h = nullptr;
  TString sType[] = {"Kshort", "Lambda", "Xi", "Omega"};
  TString sCent[] = {"0100", "010", "1040", "40100"};
  for(Int_t i = 0; i< sizeof(sType)/sizeof(TString); i++)for(Int_t j = 0; j< sizeof(sCent)/sizeof(TString); j++){
    h = GetInclPtSpect(sType[i], sCent[j]); listIn->Add(h); 
  
  }
  for(Int_t i = 0; i< sizeof(sType)/sizeof(TString)-1; i++)for(Int_t j = 0; j< sizeof(sCent)/sizeof(TString); j++){
    h = GetJCPtSpect(sType[i], sCent[j]); listJC->Add(h); 
    h = GetPCPtSpect(sType[i], sCent[j]); listPC->Add(h); 
    h = GetJEPtSpect(sType[i], sCent[j]); listJE->Add(h); 
    h = GetOC04PtSpect(sType[i], sCent[j]); listOC04->Add(h); 
    h = GetOC06PtSpect(sType[i], sCent[j]); listOC06->Add(h); 
    h = GetOC08PtSpect(sType[i], sCent[j]); listOC08->Add(h); 
    h = GetNJPtSpect(sType[i], sCent[j]); listNJ->Add(h); 
  }
  
  file->cd();
  listIn->Write(Form("listIn"), TObject::kSingleKey );
  listJC->Write(Form("listJC_LowPt06"), TObject::kSingleKey );
  listPC->Write(Form("listPC_LowPt06"), TObject::kSingleKey );
  listJE->Write(Form("listJE_LowPt06"), TObject::kSingleKey );
  listOC04->Write(Form("listOC04_LowPt06"), TObject::kSingleKey );
  listOC06->Write(Form("listOC06_LowPt06"), TObject::kSingleKey );
  listOC08->Write(Form("listOC08_LowPt06"), TObject::kSingleKey );
  listNJ->Write(Form("listNJ_LowPt06"), TObject::kSingleKey );
  file->Close();

}

