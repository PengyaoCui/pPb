#include "./SourceFun.h"

void GetJE(){
 
  TString sname = "JE";
  //Bool_t IsSave(0);
  Bool_t IsSave(1);

  TString sFiles = "./result/PtSpect_LHC16khl.root";
  TString HistNeg = "XiNeg";

  TString sPath  = "/home/cuipengyao/study/code/Draw/macro/Cascade_LHC16klh/result";
  TString sFile = "PtSpect_LHC16khl.root";
  TString sHistJC  = "hTotal_JC";
  TString sHistPC  = "hTotal_PC"; 

  //-----------------------------------
  TCanvas * c2 = new TCanvas("c2","");
  SetStyle();
  SetCanv(c2);
  c2->SetLogy();
  if (IsSave) TFile *file = TFile::Open(sFiles, "UPDATE");
  //-----------------------------------
  TH1D *hJC = (TH1D*)GetTH1FromFile(sPath, sFile,  sHistJC);
  hJC->SetName("hJC");
  SetLine(hJC,cLine[0], sMark[0]);
  //SetAxis(hJC, YMin, YMax, 0.6, 7., "d#rho/d#it{p}_{T}");
  hJC->Draw("same");

  TH1D *hPC = (TH1D*)GetTH1FromFile(sPath, sFile,  sHistPC);
  hPC->SetName("hPC");
  SetLine(hPC,cLine[1], sMark[1]);
  hPC->Draw("same");

  TH1D *hJE = hJC->Clone("hJE");
  hJE->Add(hPC,-1); 
  SetLine(hJE,cLine[2], sMark[2]);
  hJE->Draw("same");
  
  if(IsSave) {file->cd(); hJE->Write(Form("hTotal_%s",sname.Data()), TObject::kSingleKey);}
  if(IsSave) {file->Close();}

  return;
}
