#include"../../SourceFun.h"

void THnSparse(){

  TFile *f1    = TFile::Open("/home/cuipengyao/study/code/Cascade_LHC15f_pass2/JC_test_everycut/AnalysisOutputs_Loop1ndRD.root");

  TList *flistNeg = (TList *)f1->Get("listLoop1ndRD_XiMinus_Default");
  THnSparseD *hsXiNeg   = (THnSparseD*)flistNeg->FindObject("hsCutAfter");
  hsXiNeg->SetName("XiNeg");

  TList *flistPos = (TList *)f1->Get("listLoop1ndRD_XiPlus_Default");
  THnSparseD *hsXiPos   = (THnSparseD*)flistPos->FindObject("hsCutAfter");
  hsXiPos->SetName("XiPos");

  THnSparseD *hsXiN = hsXiNeg->Clone("XiN");
  THnSparseD *hsXiP = hsXiPos->Clone("XiP");
  hsXiN->Add(hsXiP);

  THnSparseD  *hsXiAfter = hsXiN->Clone("XiAfter");
  THnSparseD *hsXiBefore = (THnSparseD*)flistNeg->FindObject("hsCutBefore");
//=====================================================================
  TString sCut[29];
  //TString sCut[24];
   
  sCut[ 0] = "V0Radius";
  sCut[ 1] = "V0PA";
  sCut[ 2] = "V0DistToPVoverP";
  sCut[ 3] = "DausDCA";
  sCut[ 4] = "PosDCAtoPV";
  sCut[ 5] = "NegDCAtoPV";
  sCut[ 6] = "DauXrowsTPC";
  sCut[ 7] = "DauXrowsOverFindableClusTPC";
  sCut[ 8] = "V0Pt";
  sCut[ 9] = "RapidityLa";
  sCut[10] = "Lambda.M";
  sCut[11] = "AntiLa.M";
  sCut[12] = "Pos.Eta";
  sCut[13] = "Neg.Eta";

  sCut[14] = "XiRadius";
  sCut[15] = "XiCPA";
  sCut[16] = "XiDCAtoPV";
  sCut[17] = "V0toBachDCA";
  sCut[18] = "V0DCAtoPV";
  sCut[19] = "BachDCAtoPV";
  sCut[20] = "BachXrowsTPC";
  sCut[21] = "BachXrowsOverFindableClusTPC";
  sCut[22] = "V0.Eta";
  sCut[23] = "Bach.Eta";

  sCut[24] = "PosPionSigmaTPC";
  sCut[25] = "PosProtonSigmaTPC";
  sCut[26] = "NegPionSigmaTPC";
  sCut[27] = "NegProtonSigmaTPC";
  sCut[28] = "BachSigmaTPC";
//=====================================================================

  //TFile *output = TFile::Open("THnSparseCut.root","NEW"); TList *listxx = new TList();

  for(Int_t i =0; i<29; i++){
    TCanvas* c1 = new TCanvas(Form("c1_%d",i), "");

    TLegend* leg = new TLegend(0.7,0.7,0.9,0.9);

    TH1D *hBefore = (TH1D*)hsXiBefore->Projection(i);
    TH1D  *hAfter = (TH1D*)hsXiAfter->Projection(i);
    SetLine(hBefore,cLine[0],sMark[0]);
    SetLine(hAfter, cLine[2],sMark[1]);
    //listxx->Add(hBefore);
    //listxx->Add(hAfter);
    hBefore->SetTitle("");
    hAfter ->SetTitle("");
    hBefore->Draw("same");
    hAfter ->Draw("same");
    leg->AddEntry(hBefore,"Before Cuts","lp");
    leg->AddEntry(hAfter, "After Cuts","lp");

    TLatex* tex = new TLatex();
    tex->SetNDC();
    tex->SetTextSizePixels(29);
    SetCanv(c1);    
    c1->SetLogy();
    SetLegend(leg);
    leg->Draw();
    SetStyle();
    tex->DrawLatex(0.48, 0.05, sCut[i]);

    //TPaveText* t = ("");
    //TPaveText::DeleteText();
    //TPaveText::Clear();
  }

  //listxx->Add(hsXi);
  //output->cd(); listxx->Write(); output->Close();

}

