#include "./SourceFun.h"

void test(){
  TCanvas *can = nullptr;

  can = MakeCanvas("can");
  can->SetGridx(); can->SetGridy();

  TH1D* h1 = new TH1D("a", "", 2, 1, 2);
  TH1D* h2 = new TH1D("a", "", 4, 1, 4);
  TH1D* h3 = nullptr;
  h1->SetBinContent(1, 8);
  h1->SetBinContent(2, 4);
  for(Int_t i = 1; i<=4; i++) h2->SetBinContent(i, 10);

  h2->Add(h1, -1.);
  
  //h3 = RebinTH1D(h1, h2);
  //for(Int_t i = 1; i<=4; i++) cout<< i << "====" <<h3->GetBinContent(i)<<endl;

  h2->Draw(); 
  gStyle->SetOptStat("");

  CanvasEnd(can);
  return;
}
