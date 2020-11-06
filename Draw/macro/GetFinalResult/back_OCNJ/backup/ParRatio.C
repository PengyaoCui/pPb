#include "./inc/TStrangeJet.h"

//-------------------------------------------------------------
void ParRatio(){

  TString Path = "/home/cuipengyao/study/pPb/Local/ThisAna/JE_OmegaBins";
  TFile *file = TFile::Open("./result/PtSpectra.root", "UPDATE");
  TList *listIn = (TList*)file->Get(Form("listIn"));             if (!listIn){listIn = new TList();}

  TList *listJC = (TList*)file->Get(Form("listJC_LowPt06"));     if (!listJC){listJC = new TList();}
  TList *listPC = (TList*)file->Get(Form("listPC_LowPt06"));     if (!listPC){listPC = new TList();}
  TList *listJE = (TList*)file->Get(Form("listJE_LowPt06"));     if (!listJE){listJE = new TList();}
  TList *listOC04 = (TList*)file->Get(Form("listOC04_LowPt06")); if (!listOC04){listOC04 = new TList();}
  TList *listNJ = (TList*)file->Get(Form("listNJ_LowPt06"));     if (!listNJ){listNJ = new TList();}
  
  TList *lJC = (TList*)file->Get(Form("listJC_LowPt09"));     if (!lJC){lJC = new TList();}
  TList *lPC = (TList*)file->Get(Form("listPC_LowPt09"));     if (!lPC){lPC = new TList();}
  TList *lJE = (TList*)file->Get(Form("listJE_LowPt09"));     if (!lJE){lJE = new TList();}
  TList *lOC04 = (TList*)file->Get(Form("listOC04_LowPt09")); if (!lOC04){lOC04 = new TList();}
  TList *lNJ = (TList*)file->Get(Form("listNJ_LowPt09"));     if (!lNJ){lNJ = new TList();}
  
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
    h = GetNJPtSpect(sType[i], sCent[j]); listNJ->Add(h); 
  }

  for(Int_t i = 0; i< sizeof(sType)/sizeof(TString); i++)for(Int_t j = 0; j< sizeof(sCent)/sizeof(TString); j++){
    h = GetJCPtSpect(sType[i], sCent[j], Path);   lJC->Add(h); 
    h = GetPCPtSpect(sType[i], sCent[j], Path);   lPC->Add(h); 
    h = GetJEPtSpect(sType[i], sCent[j], Path);   lJE->Add(h); 
    h = GetOC04PtSpect(sType[i], sCent[j], Path); lOC04->Add(h); 
    h = GetNJPtSpect(sType[i], sCent[j], Path);   lNJ->Add(h); 
  
  }
  
  //----------------------------
  for(Int_t i = 0; i< sizeof(sCent)/sizeof(TString); i++){
    h = GetInclRatioLK(sCent[i]);   listIn->Add(h); 
    h = GetInclRatioXK(sCent[i]);   listIn->Add(h); 
    h = GetInclRatioOK(sCent[i]);   listIn->Add(h); 
    h = GetInclRatioXL(sCent[i]);   listIn->Add(h); 
    h = GetInclRatioOL(sCent[i]);   listIn->Add(h); 
    h = GetInclRatioOK(sCent[i]);   listIn->Add(h); 
    
    h = GetJCRatioLK(sCent[i]);   listJC->Add(h); 
    h = GetJCRatioXK(sCent[i]);   listJC->Add(h); 
    h = GetJCRatioXL(sCent[i]);   listJC->Add(h); 
    h = GetJCRatioOK(sCent[i]);   lJC->Add(h); 
    h = GetJCRatioOL(sCent[i]);   lJC->Add(h); 
    h = GetJCRatioOK(sCent[i]);   lJC->Add(h); 
    
    h = GetJERatioLK(sCent[i]);   listJE->Add(h);
    h = GetJERatioXK(sCent[i]);   listJE->Add(h);
    h = GetJERatioXL(sCent[i]);   listJE->Add(h);
    h = GetJERatioOK(sCent[i]);   lJE->Add(h);
    h = GetJERatioOL(sCent[i]);   lJE->Add(h);
    h = GetJERatioOK(sCent[i]);   lJE->Add(h);

    h = GetOC04RatioLK(sCent[i]);   listJE->Add(h);
    h = GetOC04RatioXK(sCent[i]);   listJE->Add(h);
    h = GetOC04RatioXL(sCent[i]);   listJE->Add(h);
    h = GetOC04RatioOK(sCent[i]);   lJE->Add(h);
    h = GetOC04RatioOL(sCent[i]);   lJE->Add(h);
    h = GetOC04RatioOK(sCent[i]);   lJE->Add(h);

    h = GetNJRatioLK(sCent[i]);   listNJ->Add(h);
    h = GetNJRatioXK(sCent[i]);   listNJ->Add(h);
    h = GetNJRatioXL(sCent[i]);   listNJ->Add(h);
    h = GetNJRatioOK(sCent[i]);   lNJ->Add(h);
    h = GetNJRatioOL(sCent[i]);   lNJ->Add(h);
    h = GetNJRatioOK(sCent[i]);   lNJ->Add(h);

  }
 
 
  
  file->cd();
  listIn->Write(Form("listIn"), TObject::kSingleKey );
  
  listJC->Write(Form("listJC_LowPt06"), TObject::kSingleKey );
  listPC->Write(Form("listPC_LowPt06"), TObject::kSingleKey );
  listJE->Write(Form("listJE_LowPt06"), TObject::kSingleKey );
  listOC04->Write(Form("listOC04_LowPt06"), TObject::kSingleKey );
  listNJ->Write(Form("listNJ_LowPt06"), TObject::kSingleKey );
  
  lJC->Write(Form("listJC_LowPt09"), TObject::kSingleKey );
  lPC->Write(Form("listPC_LowPt09"), TObject::kSingleKey );
  lJE->Write(Form("listJE_LowPt09"), TObject::kSingleKey );
  lOC04->Write(Form("listOC04_LowPt09"), TObject::kSingleKey );
  lNJ->Write(Form("listNJ_LowPt09"), TObject::kSingleKey );
  
  file->Close();

}

