#include "./SourceFun.h"

void PtSpect(){

  Bool_t IsLa(0);
  Bool_t IsIncl(1);	
  Bool_t   IsJC(0);	
  Bool_t   IsPC(0);	
  Bool_t   IsOC(0);	
  Bool_t   IsNJ(0);	
  //TString sPath = "/home/cuipengyao/study/pPb/Strangeness/FullStatistic/ThisAna_New/JEBins";
  TString sPath = "/home/cuipengyao/study/pPb/Strangeness/FullStatistic/ThisAna_New/Incl";
  TString sFile = "AnalysisOutputs_Results.root";
  TString sList = "listResults";
  TString sHist = "hNco";
  if(IsLa) sFile = "AnalysisOutputs_MakeLaFdR.root";
  if(IsLa) sList = "listMakeLaFdR";
  if(IsLa) sHist = "hPtLaNormCorr";

  TString sCent[] = {"0100", "010", "1040", "40100"}; 
  TString sTex[] = {"0-100", "0-10", "10-40", "40-100"};
  TString sLeg[] = {"Inclusive", "JC", "UE", "JE"};
  //TString sCent[] = {"0100", "05", "510", "1020", "2040", "4060", "6080", "80100"}; 
  //TString sTex[] = {"0100", "05", "510", "1020", "2040", "4060", "6080", "80100"};
  //TString sLeg[] = {"Inclusive", "JC", "UE", "JE"};
  
  
  TString sLatex("Lambda spectra");
  //-----------------------------------
  TCanvas *can = nullptr;
  gStyle->SetOptStat("");

  auto tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  

  //-----------------------------------
  auto nHist = sizeof(sCent)/sizeof(TString);
  TH1D *hJC = nullptr;
  TH1D *hPC = nullptr;
  TH1D *hOC = nullptr;
  for (Int_t i = 0; i< nHist; i++){
    can = MakeCanvas(Form("can_%d", i));
    can->SetLogy();
    can->SetGridx(); can->SetGridy();
    auto leg = new TLegend(0.7,0.9,1.0,0.6);    
    SetLegend(leg);
    
    if(IsIncl){
      TString sInclList = Form("%s_Lambda_Default_%s", sList.Data(), sCent[i].Data());
      //sInclList = Form("%s_Lambda_%s", sList.Data(), sCent[i].Data());
      auto hIncl = (TH1D*)GetTH1D(sPath.Data(), sFile.Data(), sInclList.Data(), sHist.Data());
      hIncl->SetName(Form("hIncl_%d", i)); 
      NormHistBinWidth(hIncl);
      hIncl->GetYaxis()->SetRangeUser(1e-7, 1.); 
      //hIncl->GetXaxis()->SetRangeUser(1., 7.); 
      SetFrame(hIncl, "#it{p}_{T}(GeV/c)", "d#rho/d#it{p}_{T}(#it{c}/GeV)");
      DrawHisto(hIncl, cLine[0], sMark[0], "same");
      leg->AddEntry(hIncl , "Inclusive","lp");
      TFile *f = TFile::Open("./result/PtSpect_ThisAna_New.root", "UPDATE");
      f->cd(); hIncl->Write(Form("hPtIncl_Lambda_%s", sCent[i].Data()), TObject::kSingleKey); f->Close();
    }
    
    if(IsJC){
      TString sJCList = Form("%s_Lambda_Default_JC_%s", sList.Data(), sCent[i].Data()); 
      hJC = (TH1D*)GetTH1D(sPath.Data(), sFile.Data(), sJCList.Data(), sHist.Data());
      hJC->SetName(Form("hJC_%d", i)); 
      hJC->GetYaxis()->SetRangeUser(1e-7, 1.); 
      //hJC->GetXaxis()->SetRangeUser(0., 12.); 
      NormHistBinWidth(hJC);
      SetFrame(hJC, "#it{p}_{T}(GeV/c)", "d#rho/d#it{p}_{T}(#it{c}/GeV)");
      DrawHisto(hJC, cLine[3], sMark[3], "same");
      leg->AddEntry(hJC , "JC","lp");
      TFile *f = TFile::Open("./result/PtSpect_ThisAna_New.root", "UPDATE");
      f->cd(); hJC->Write(Form("hPtJC_Lambda_%s", sCent[i].Data()), TObject::kSingleKey); f->Close();
    } 
    
    if(IsPC){
      TString sPCLList = Form("%s_Lambda_Default_PCL_%s", sList.Data(), sCent[i].Data()); 
      auto hPCL = (TH1D*)GetTH1D(sPath.Data(), sFile.Data(), sPCLList.Data(), sHist.Data());
      hPCL->SetName(Form("hPCL_%d", i)); 
      //Int_t nbin = hPCL->GetNbinsX();
      //hPCL->SetBinContent(nbin, 0.); hPCL->SetBinError(nbin, 0.); 
      //hPCL->SetBinError(nbin-1, 0.); hPCL->SetBinContent(nbin-1, 0.); 
      TString sPCUList = Form("%s_Lambda_Default_PCL_%s", sList.Data(), sCent[i].Data()); 
      auto hPCU = (TH1D*)GetTH1D(sPath.Data(), sFile.Data(), sPCUList.Data(), sHist.Data());
      hPCU->SetName(Form("hPCU_%d", i)); 
      //hPCU->SetBinContent(nbin, 0.); hPCU->SetBinError(nbin, 0.); 
      //hPCU->SetBinError(nbin-1, 0.); hPCU->SetBinContent(nbin-1, 0.); 
      hPC = (TH1D*)hPCL->Clone(Form("hPC_%d", i)); hPC->Reset(); 
      hPC->Add(hPCL, hPCU, 0.5, 0.5); 
      NormHistBinWidth(hPC);
      hPC->GetYaxis()->SetRangeUser(1e-7, 1.); 
      SetFrame(hPC, "#it{p}_{T}(GeV/c)", "d#rho/d#it{p}_{T}(#it{c}/GeV)");
      DrawHisto(hPC, cLine[2], sMark[2], "same");
      leg->AddEntry(hPC , "PC","lp");
      TFile *f = TFile::Open("./result/PtSpect_ThisAna_New.root", "UPDATE");
      f->cd(); hPC->Write(Form("hPtPC_Lambda_%s", sCent[i].Data()), TObject::kSingleKey); f->Close();
    }
    
    if(IsOC){
      TString sOCList = Form("%s_Lambda_Default_OC_%s", sList.Data(), sCent[i].Data()); 
      hOC = (TH1D*)GetTH1D(sPath.Data(), sFile.Data(), sOCList.Data(), sHist.Data());
      hOC->SetName(Form("hOC_%d", i)); 
      NormHistBinWidth(hOC);
      hOC->GetYaxis()->SetRangeUser(1e-7, 1.); 
      SetFrame(hOC, "#it{p}_{T}(GeV/c)", "d#rho/d#it{p}_{T}(#it{c}/GeV)");
      DrawHisto(hOC, cLine[4], sMark[4], "same");
      leg->AddEntry(hOC , "OC","lp");
      //TFile *f = TFile::Open("./result/PtSpect_ThisAna_New.root", "UPDATE");
      //f->cd(); hOC->Write(Form("hPtOC_Lambda_%s", sCent[i].Data()), TObject::kSingleKey); f->Close();
    } 
    
    if(IsJC && IsPC){
      auto hJE = (TH1D*)hJC->Clone(Form("hJE_%d", i));
      //RebinTH1D(hPC, hJE);
      hJE->Add(hPC, -1.); 
      leg->AddEntry(hJE , "JE","lp");
      hJE->GetYaxis()->SetRangeUser(1e-7, 1.); 
      SetFrame(hJE, "#it{p}_{T}(GeV/c)", "d#rho/d#it{p}_{T}(#it{c}/GeV)");
      DrawHisto(hJE, cLine[1], sMark[1], "same");
      TFile *f = TFile::Open("./result/PtSpect_ThisAna_New.root", "UPDATE");
      f->cd(); hJE->Write(Form("hPtJE_Lambda_%s", sCent[i].Data()), TObject::kSingleKey); f->Close();
    } 
    
    if(IsNJ){
      TString sNJList = Form("%s_Lambda_Default_NJ_%s", sList.Data(), sCent[i].Data()); 
      auto hNJ = (TH1D*)GetTH1D(sPath.Data(), sFile.Data(), sNJList.Data(), sHist.Data());
      hNJ->SetName(Form("hNJ_%d", i)); 
      NormHistBinWidth(hNJ);
      hNJ->GetYaxis()->SetRangeUser(1e-7, 1.); 
      SetFrame(hNJ, "#it{p}_{T}(GeV/c)", "d#rho/d#it{p}_{T}(#it{c}/GeV)");
      DrawHisto(hNJ, cLine[5], sMark[5], "same");
      leg->AddEntry(hNJ , "NJ","lp");
      //TFile *f = TFile::Open("./result/PtSpect_ThisAna_New.root", "UPDATE");
      //f->cd(); hNJ->Write(Form("hPtNJ_Lambda_%s", sCent[i].Data()), TObject::kSingleKey); f->Close();
    } 
       
    tex->DrawLatex(0.16, 0.91, sLatex);
    tex->DrawLatex(0.5, 0.91, Form("V0A : %s", sTex[i].Data()));
    tex->DrawLatex(0.16, 0.3, "|#eta| < 0.75");
    tex->DrawLatex(0.16, 0.2, "p-Pb #sqrt{#it{s}_{NN}} = 5.02 TeV");
    leg->Draw();
    CanvasEnd(can);
  }



  return;
}

#if 0
over pT center each bins
for(Int_t j =1; j<= h1->GetNbinsX(); j++){
  auto dBinCent = h1->GetXaxis()->GetBinCenter(j);
  auto dContent = h1->GetBinContent(j); 
  auto dError   = h1->GetBinError(j); 
  h1->SetBinContent(j, dContent/dBinCent);
  h1->SetBinError (j, dError/dBinCent);
}
#endif 
