#include "./inc/TStrangeJet.h"

//-------------------------------------------------------------
void CentVal(){

  TString Path = "/home/cuipengyao/study/pPb/Local/ThisAna/JE_OmegaBins";
  TString sPC2 = "/home/cuipengyao/study/pPb/Local/ThisAna/Uncertainty/JE/UE/PC02";
  TString sPC6 = "/home/cuipengyao/study/pPb/Local/ThisAna/Uncertainty/JE/UE/PC06";
  TString OPC2 = "/home/cuipengyao/study/pPb/Local/ThisAna/Uncertainty/JE_Omega/UE/PC02";
  TString OPC6 = "/home/cuipengyao/study/pPb/Local/ThisAna/Uncertainty/JE_Omega/UE/PC06";
  TFile *file = TFile::Open("./result/CentVal.root", "UPDATE");
  TList *listIn = (TList*)file->Get(Form("listIn"));             if (!listIn){listIn = new TList();}

  TList *listJC = (TList*)file->Get(Form("listJC"));     if (!listJC){listJC = new TList();}
  TList *listJE = (TList*)file->Get(Form("listJE"));     if (!listJE){listJE = new TList();}
  TList *listPC02 = (TList*)file->Get(Form("listPC02")); if (!listPC02){listPC02 = new TList();}
  TList *listPC04 = (TList*)file->Get(Form("listPC04")); if (!listPC04){listPC04 = new TList();}
  TList *listPC06 = (TList*)file->Get(Form("listPC06")); if (!listPC06){listPC06 = new TList();}
  
  TH1D* h = nullptr;
  TString sType[] = {"Kshort", "Lambda", "AntiLa", "Xi", "Omega"};
  TString sCent[] = {"0100", "010", "1040", "40100"};
  for(Int_t i = 0; i< sizeof(sType)/sizeof(TString); i++)for(Int_t j = 0; j< sizeof(sCent)/sizeof(TString); j++){
    h = GetInclPtSpect(sType[i], sCent[j]); listIn->Add(h); 
  
  }
  for(Int_t i = 0; i< sizeof(sType)/sizeof(TString)-1; i++)for(Int_t j = 0; j< sizeof(sCent)/sizeof(TString); j++){
    h = GetJCPtSpect(sType[i], sCent[j]); listJC->Add(h); 
    h = GetJEPtSpect(sType[i], sCent[j]); listJE->Add(h); 
    h = GetPCPtSpect(sType[i], sCent[j], sPC2); listPC02->Add(h); 
    h = GetPCPtSpect(sType[i], sCent[j]); listPC04->Add(h); 
    h = GetPCPtSpect(sType[i], sCent[j], sPC6); listPC06->Add(h); 
  }

  for(Int_t j = 0; j< sizeof(sCent)/sizeof(TString); j++){
    h = GetJCPtSpect(sType[4], sCent[j], Path);   listJC->Add(h); 
    h = GetJEPtSpect(sType[4], sCent[j], Path);   listJE->Add(h); 
    h = GetPCPtSpect(sType[4], sCent[j], OPC2);   listPC02->Add(h); 
    h = GetPCPtSpect(sType[4], sCent[j], Path);   listPC04->Add(h); 
    h = GetPCPtSpect(sType[4], sCent[j], OPC6);   listPC06->Add(h); 
  
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
    
    h = GetJERatioLK(sCent[i]);   listJE->Add(h);
    h = GetJERatioXK(sCent[i]);   listJE->Add(h);
    h = GetJERatioXL(sCent[i]);   listJE->Add(h);
    h = GetJERatioOK(sCent[i]);   listJE->Add(h);
    h = GetJERatioOL(sCent[i]);   listJE->Add(h);
    h = GetJERatioOX(sCent[i]);   listJE->Add(h);

    h = GetPCRatioLK(sCent[i], sPC2);   listPC02->Add(h);
    h = GetPCRatioXK(sCent[i], sPC2);   listPC02->Add(h);
    h = GetPCRatioXL(sCent[i], sPC2);   listPC02->Add(h);
    h = GetPCRatioOK(sCent[i], OPC2);   listPC02->Add(h);
    h = GetPCRatioOL(sCent[i], OPC2);   listPC02->Add(h);
    h = GetPCRatioOX(sCent[i], OPC2);   listPC02->Add(h);
    
    h = GetPCRatioLK(sCent[i]);   listPC04->Add(h); 
    h = GetPCRatioXK(sCent[i]);   listPC04->Add(h); 
    h = GetPCRatioXL(sCent[i]);   listPC04->Add(h); 
    h = GetPCRatioOK(sCent[i]);   listPC04->Add(h); 
    h = GetPCRatioOL(sCent[i]);   listPC04->Add(h); 
    h = GetPCRatioOX(sCent[i]);   listPC04->Add(h); 
    
    h = GetPCRatioLK(sCent[i], sPC6);   listPC06->Add(h);
    h = GetPCRatioXK(sCent[i], sPC6);   listPC06->Add(h);
    h = GetPCRatioXL(sCent[i], sPC6);   listPC06->Add(h);
    h = GetPCRatioOK(sCent[i], OPC6);   listPC06->Add(h);
    h = GetPCRatioOL(sCent[i], OPC6);   listPC06->Add(h);
    h = GetPCRatioOX(sCent[i], OPC6);   listPC06->Add(h);
   
  }
 
 
  
  file->cd();
  listIn->Write(Form("listIn"), TObject::kSingleKey );
  
  listJC->Write(Form("listJC"), TObject::kSingleKey );
  listJE->Write(Form("listJE"), TObject::kSingleKey );
  listPC02->Write(Form("listPC02"), TObject::kSingleKey );
  listPC04->Write(Form("listPC04"), TObject::kSingleKey );
  listPC06->Write(Form("listPC06"), TObject::kSingleKey );
  
  file->Close();

}

