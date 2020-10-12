void copylist()
{
  
  TString sFileName1 ="AnalysisOutputs_Loop1ndRD.root";
  TString sFileName2 = "AnalysisOutputs_Loop1ndRD_back.root";
  TString  sListName = "lis";

  TFile*   f1 = TFile::Open(sFileName1,"UPDATE"); if (!f1->IsOpen()) return 0x0;
  TFile*   f2 = TFile::Open(sFileName2,"read"); if (!f2->IsOpen()) return 0x0;
  TList* list = (TList*)f2->Get(sListName);  if (!list) return 0x0;
  
  f2->Close();
  f1->cd();
  list->Write("listLoop1ndRD_AntiLa_Default_010", TObject::kSingleKey);
  f1->Close();
  return;

}

