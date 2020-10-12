void JetSample()
{

  gROOT->LoadMacro("variable.h");

  gROOT->LoadMacro("inc/TAliFigs.h");
  gROOT->LoadMacro("inc/TPlotStd.h");
  gROOT->LoadMacro("inc/TUtilHisto.h"); SetStyle();
//=============================================================================

  TH1F    *hfm = 0;
  TH1F    *hfm2 = 0;
  TCanvas *can = 0;
  TLegend *leg = 0;
  TLatex  *tex = 0;

  const Float_t dflx = -60.,   dfux = 155.;
  const Float_t dfly = 5e-8.,   dfuy = 2.;

  const TString stnx = "#it{p}_{T,jet} (GeV/#it{c})";
  const TString stny = "probability density";

//==============================================================================

  //can = MakeCanvas("subjet"); can->SetGridx(); can->SetGridy();
  can = new TCanvas("subjet","subjet",700, 500);
  /*can->Range(0., 0., 1., 1.);
  can->SetFillColor(0);
  can->SetBorderMode(0);
  can->SetBorderSize(0);
  can->SetRightMargin(0.03);
  can->SetLeftMargin(0.13);
  can->SetTopMargin(0.02);
  can->SetBottomMargin(0.15);
  can->SetFrameFillStyle(0);
  can->SetFrameBorderMode(0);
  */
  can->cd();
  TPad *c2_a = new TPad("c2_a", "c2_a", 0., 0.35, 1., 1.);

  c2_a->SetFillColor(0);
  c2_a->SetBorderMode(0);
  c2_a->SetBorderSize(0);
  c2_a->SetRightMargin(0.01);
  c2_a->SetLeftMargin(0.13);
  c2_a->SetTopMargin(0.02);
  c2_a->SetBottomMargin(0.0);
  c2_a->SetFrameFillStyle(0);
  c2_a->SetFrameBorderMode(0);
/*
  c2_a->SetRightMargin(0.03);
  c2_a->SetBorderMode(0);
  c2_a->SetBorderSize(2);

  c2_a->SetBottomMargin(0.0);
  c2_a->SetFrameBorderMode(0);
  c2_a->SetFrameBorderMode(0);
*/
  c2_a->Draw();
  c2_a->cd();
  c2_a->SetLogy();


//  can->SetLogy();
  hfm = c2_a->DrawFrame(dflx, dfly, dfux, dfuy); SetupFrame(hfm, stnx, stny, 0.07, 0.07, 0.07, 0.07);
  hfm->GetXaxis()->SetNdivisions(510);
  hfm->GetYaxis()->SetNdivisions(510);

//===============================================================================
  //TFile *file = TFile::Open("../result/15o_pass5/Merge_result.root","read");
  TFile *file = TFile::Open(path,"read");
  TList *list = (TList*)file->Get("listSubjet");
  TList *listSj = (TList*)list->FindObject("Jet_AKTChargedR040_tracks_pT0150_pt_scheme");
  TH1D *hJet = listSj->FindObject(Form("hJetPt_%d", Ncent));
  Normalization(hJet);
//  hJet->Rebin(10) ;
  NormBinningHistogram(hJet);
  TF1* fFitRHS = Fit(hJet, wcl[1]);
  //DrawHisto(hJet, wcl[0], wmk[0], "SAME HIST");
  DrawHisto(hJet, wcl[0], wmk[0], "SAME");
//================================================================================
  TList *list = (TList*)file->Get("AliAnalysisTaskEmcalJetSample_tracks_histos");
  TList *listJe = (TList*)list->FindObject("Jet_AKTChargedR040_tracks_pT0150_pt_scheme");
  TH1D *hJetSample = listJe->FindObject(Form("histJetCorrPt_%d", Ncent));
  Normalization(hJetSample);
  NormBinningHistogram(hJetSample);
  DrawHisto(hJetSample, wcl[1], wmk[0], "SAME HIST");
//================================================================================
  //Double_t dMuRHS = fFitRHS->GetParameter(1);
  Double_t dSigma = fFitRHS->GetParameter(2);


//================================================================================
  leg = new TLegend(0.55, 0.55, 0.85, 0.85); SetupLegend(leg);
  leg->AddEntry(hJet, "Jet", "LP")->SetTextSizePixels(24);
  leg->AddEntry(hJetSample, "Jet Sample", "LP")->SetTextSizePixels(24);
  //leg->AddEntry(fFitRHS, Form("#mu = %.1f,  #sigma^{RHS}= %.1f",dMuRHS, dSigma), "LP")->SetTextSizePixels(24);
  leg->Draw();

  tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.16, 0.9, Form("LHC15o, #sqrt{s} =5.02 TeV, anti- #it{k}_{T}, R=0.4, cnet:%d - %d%%", minCent, maxCent));
  tex->DrawLatex(0.16, 0.8, Form("#sigma^{LHS} = %.1f", dSigma));

//  tex->DrawLatex(0.16, 0.84, "subjet: anti- #it{k}_{T} , R_{sub} =0.1");
  can->SaveAs(Form("JetSample_%d-%d.png", minCent, maxCent));
//================================================================================
  can->cd();

  TPad *c2_b = new TPad("c2_b", "c2_b", 0., 0. , 1., 0.35);

  c2_b->SetFillColor(0);
  c2_b->SetBorderMode(0);
  c2_b->SetBorderSize(0);
  c2_b->SetRightMargin(0.01);
  c2_b->SetLeftMargin(0.13);
  c2_b->SetTopMargin(0.00);
  c2_b->SetBottomMargin(0.3);
  c2_b->SetFrameFillStyle(0);
  c2_b->SetFrameBorderMode(0);

/*  c2_b->SetTopMargin(0.);
  c2_b->SetRightMargin(0.01);
  c2_b->SetBottomMargin(0.2);
  c2_b->SetFillColor(0);
  c2_b->SetBorderMode(0);
  c2_b->SetBorderSize(2);
  c2_b->SetFrameBorderMode(0);
  c2_b->SetFrameBorderMode(0);
  */
  c2_b->Draw();
  c2_b->cd();

  hfm2 = c2_b->DrawFrame(dflx, 0.8, dfux, 1.15); SetupFrame(hfm2, stnx, "Ratio", 0.12, 0.12, 0.12, 0.13, 1.1, 0.5);
  hfm2->GetXaxis()->SetNdivisions(510);
  //hfm2->GetYaxis()->SetNdivisions(510);

  TH1D* Numerator   = (TH1D*)hJet->Clone("hJetNum");
  TH1D* Denominator = (TH1D*)hJetSample->Clone("hJetSampleDen");
  Numerator->Divide(Denominator);
  //TGraph* hn = new TGraph(Numerator);
  Numerator->Draw("same HIST");
  //hn->Draw("same L");
 // DrawGraph(hn, wcl[3], wmk[1], "same L");
  tex = new TLatex();
  tex->SetNDC();
  tex->SetTextSizePixels(24);
  tex->DrawLatex(0.16, 0.8, "Jet / sample jet");

  CanvasEnd(can);


//================================================================================
  return;

}
//________________________________________________________________________________
void Normalization(TH1D *h){

  if(!h) cout<<"ERROR: NOT Normalization"<<endl;

  Double_t entries = h->GetEntries();
  h->Scale(1/entries);
}
//________________________________________________________________________________
TF1* Fit(TH1D *h, Color_t cl){

  TF1 *fcn = new TF1("fcn","gaus", -50., 0.);
  Double_t mean = h->GetMean();
  Double_t sigma = h->GetRMS();
  fcn->SetParameters(0.1,mean,sigma);
  fcn->SetParNames("C","#mu","#sigma");
//  fcn->SetLineColor(kRed);
  fcn->SetLineColor(cl);
  fcn->SetLineStyle(2);
//  h->Fit(fcn, "R", "", -50, 0);
  //h->Fit(fcn, "R");//, "SAME");
  h->Fit(fcn, "R0", "SAME");

  Double_t mypar[3];
  fcn->GetParameters(&mypar[0]);
  for (int i=0;i<3;i++) cout << "par[" << i << "]=" << mypar[i] << endl;

  return fcn;
}

