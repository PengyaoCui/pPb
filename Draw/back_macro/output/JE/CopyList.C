void CopyList(){
  TString sFileName1 = "AnalysisOutputs_LoopJetRD.root";
  TString sFileName2 = "AnalysisOutputs_LoopJetRD_Cent.root";
  TString  sListName = "listLoopJetRD_Xi_Default_PtJ22_OC";

  TFile*   f1 = TFile::Open(sFileName1,"UPDATE"); if (!f1->IsOpen()) return 0x0;
  TFile*   f2 = TFile::Open(sFileName2,"read"); if (!f2->IsOpen()) return 0x0;
  TList* list = (TList*)f2->Get(sListName);  if (!list) return 0x0;
  f2->Close();
  f1->cd();
  list->Write(sListName, TObject::kSingleKey);
  f1->Close();
  return;
}

