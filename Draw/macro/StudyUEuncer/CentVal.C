#include "./inc/TStrangeJet.h"

//-------------------------------------------------------------
void CentVal(){

  TString Path = "/home/cuipengyao/study/pPb/Local/ThisAna/JE_OmegaBins";
  TFile *file = TFile::Open("./result/CentVal.root", "UPDATE");
  TList *listIn = (TList*)file->Get(Form("listIn"));             if (!listIn){listIn = new TList();}

  TList *listJC = (TList*)file->Get(Form("listJC"));     if (!listJC){listJC = new TList();}
  TList *listPC = (TList*)file->Get(Form("listPC"));     if (!listPC){listPC = new TList();}
  TList *listJE = (TList*)file->Get(Form("listJE"));     if (!listJE){listJE = new TList();}
  TList *listOC04 = (TList*)file->Get(Form("listOC04")); if (!listOC04){listOC04 = new TList();}
  TList *listNJ = (TList*)file->Get(Form("listNJ"));     if (!listNJ){listNJ = new TList();}
  
  TH1D* h = nullptr;
  TString sType[] = {"Kshort", "Lambda", "AntiLa", "Xi", "Omega"};
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

  for(Int_t j = 0; j< sizeof(sCent)/sizeof(TString); j++){
    h = GetJCPtSpect(sType[4], sCent[j], Path);   listJC->Add(h); 
    h = GetPCPtSpect(sType[4], sCent[j], Path);   listPC->Add(h); 
    h = GetJEPtSpect(sType[4], sCent[j], Path);   listJE->Add(h); 
    h = GetOC04PtSpect(sType[4], sCent[j], Path); listOC04->Add(h); 
    h = GetNJPtSpect(sType[4], sCent[j], Path);   listNJ->Add(h); 
  
  }
  
  //----------------------------
  for(Int_t i = 0; i< sizeof(sCent)/sizeof(TString); i++){
    h = GetInclRatioLK(sCent[i]);   listIn->Add(h); 
    h = GetInclRatioXK(sCent[i]);   listIn->Add(h); 
    h = GetInclRatioOK(sCent[i]);   listIn->Add(h); 
    h = GetInclRatioXL(sCent[i]);   listIn->Add(h); 
    h = GetInclRatioOL(sCent[i]);   listIn->Add(h); 
    h = GetInclRatioOX(sCent[i]);   listIn->Add(h); 
    
    h = GetJCRatioLK(sCent[i]);   listJC->Add(h); 
    h = GetJCRatioXK(sCent[i]);   listJC->Add(h); 
    h = GetJCRatioXL(sCent[i]);   listJC->Add(h); 
    h = GetJCRatioOK(sCent[i]);   listJC->Add(h); 
    h = GetJCRatioOL(sCent[i]);   listJC->Add(h); 
    h = GetJCRatioOX(sCent[i]);   listJC->Add(h); 
    
    h = GetPCRatioLK(sCent[i]);   listPC->Add(h); 
    h = GetPCRatioXK(sCent[i]);   listPC->Add(h); 
    h = GetPCRatioXL(sCent[i]);   listPC->Add(h); 
    h = GetPCRatioOK(sCent[i]);   listPC->Add(h); 
    h = GetPCRatioOL(sCent[i]);   listPC->Add(h); 
    h = GetPCRatioOX(sCent[i]);   listPC->Add(h); 
    
    h = GetJERatioLK(sCent[i]);   listJE->Add(h);
    h = GetJERatioXK(sCent[i]);   listJE->Add(h);
    h = GetJERatioXL(sCent[i]);   listJE->Add(h);
    h = GetJERatioOK(sCent[i]);   listJE->Add(h);
    h = GetJERatioOL(sCent[i]);   listJE->Add(h);
    h = GetJERatioOX(sCent[i]);   listJE->Add(h);

    h = GetOC04RatioLK(sCent[i]);   listOC04->Add(h);
    h = GetOC04RatioXK(sCent[i]);   listOC04->Add(h);
    h = GetOC04RatioXL(sCent[i]);   listOC04->Add(h);
    h = GetOC04RatioOK(sCent[i]);   listOC04->Add(h);
    h = GetOC04RatioOL(sCent[i]);   listOC04->Add(h);
    h = GetOC04RatioOX(sCent[i]);   listOC04->Add(h);

    h = GetNJRatioLK(sCent[i]);   listNJ->Add(h);
    h = GetNJRatioXK(sCent[i]);   listNJ->Add(h);
    h = GetNJRatioXL(sCent[i]);   listNJ->Add(h);
    h = GetNJRatioOK(sCent[i]);   listNJ->Add(h);
    h = GetNJRatioOL(sCent[i]);   listNJ->Add(h);
    h = GetNJRatioOX(sCent[i]);   listNJ->Add(h);

  }
 
 
  
  file->cd();
  listIn->Write(Form("listIn"), TObject::kSingleKey );
  
  listJC->Write(Form("listJC"), TObject::kSingleKey );
  listPC->Write(Form("listPC"), TObject::kSingleKey );
  listJE->Write(Form("listJE"), TObject::kSingleKey );
  listOC04->Write(Form("listOC04"), TObject::kSingleKey );
  listNJ->Write(Form("listNJ"), TObject::kSingleKey );
  
  file->Close();

}

