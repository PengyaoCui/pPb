void Event(){

TFile* f = TFile::Open("AnalysisOutputs_LoopJetRD.root");
TList*l = (TList*)f->Get("listLoopJetRD_Kshort_Default_JC");
TH1D*h = (TH1D*)l->FindObject("hEvent");
cout<<h->GetBinContent(1)<<endl;

return 0x0;
}
