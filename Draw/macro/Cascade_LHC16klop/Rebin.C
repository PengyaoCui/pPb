#include "./SourceFun.h"

//___________________________________________________________________
void Rebin(){
  const Double_t dPtBin[] = {2.0, 2.4, 2.8, 3.3, 4.0, 5.0, 6.5 };
  const Int_t nPtBin = sizeof(dPtBin)/sizeof(Double_t)-1;
  const TH1D* hRebin = new TH1D("hRebin","",nPtBin,dPtBin);

  TH1D*  h1 = (TH1D*)GetTH1FromFile("/home/cuipengyao/study/code/Draw/macro/Cascade_LHC16klop/result", "Uncertaintys_InclXi.root", "Uncertainty");
  for(Int_t i=1; i<= h1->GetNbinsX(); i++){
    h1->SetBinContent(i, h1->GetBinContent(i)*h1->GetBinWidth(i));
    h1->SetBinError(i, 1e-12);
  }
  h1 = (TH1D*)RebinTH1D(h1, hRebin);
  NormBinSize(h1);
  for(Int_t j=1; j<= h1->GetNbinsX(); j++){ cout<<h1->GetBinContent(j)<<endl; }

  //SetAxis(hPtOC, YMin, YMax, XMin, XMax, "d#it{#rho}/d#it{p}_{T}");
  h1->Draw();
  return;
}

