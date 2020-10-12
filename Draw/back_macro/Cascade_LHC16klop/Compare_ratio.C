void Compare_ratio{
///////////////////////////////////////////////////////////////////////////
	TFile *file =new TFile("v2XiLHC15o.root");

	TH1D *TPC05 = (TH1D*)file->Get("v3SPXiCent05");
	TH1D *TPC510 = (TH1D*)file->Get("v3SPXiCent510");
	TH1D *TPC1020 = (TH1D*)file->Get("v3SPXiCent1020");
	TH1D *TPC2030 = (TH1D*)file->Get("v3SPXiCent2030");
	TH1D *TPC3040 = (TH1D*)file->Get("v3SPXiCent3040");
        TH1D *TPC4050 = (TH1D*)file->Get("v3SPXiCent4050");


        TFile *file_2 =new TFile("v3XiLHC11h.root");
	TH1D *VZE05 = (TH1D*)file_2->Get("v3SPXiCent05");
        TH1D *VZE510 = (TH1D*)file_2->Get("v3SPXiCent510");
        TH1D *VZE1020 = (TH1D*)file_2->Get("v3SPXiCent1020");
        TH1D *VZE2030 = (TH1D*)file_2->Get("v3SPXiCent2030");
        TH1D *VZE3040 = (TH1D*)file_2->Get("v3SPXiCent3040");
        TH1D *VZE4050 = (TH1D*)file_2->Get("v3SPXiCent4050");
        TH1F * ratio1 = TPC05->Clone("ratio1");
        ratio1->Divide(VZE05);
        TH1F * ratio2 = TPC510->Clone("ratio2");
        ratio2->Divide(VZE510);
        TH1F * ratio3 = TPC1020->Clone("ratio3");
        ratio3->Divide(VZE1020);
        TH1F * ratio4 = TPC2030->Clone("ratio4");
        ratio4->Divide(VZE2030);
        TH1F * ratio5 = TPC3040->Clone("ratio5");
        ratio5->Divide(VZE3040);
        TH1F * ratio6 = TPC4050->Clone("ratio6");
        ratio6->Divide(VZE4050);
//////////////////////////////////////////////////////////////////////////////


/////////////////////////////cent 5-10///////////////////////////////////////


        TPad * c2 = new TPad();
        
        c2->SetFillColor(0);

        c2->Draw();
        c2->cd();
        
        TLegend* leg = new TLegend(0.85, 0.85, 0.98, 0.98);
        leg->AddEntry((TObject*)0, "cent 5-10", "");
        leg->AddEntry(TPC510, "LHC15o", "l");
        leg->AddEntry(VZE510, "LHC11h", "l");
        leg->Draw();
//////////////////////////////Pada///////
        TPad *c2_a = new TPad("c2_a", "c2_a", 0, 0.2, 0.85., 1.);
        c2_a->SetRightMargin(0.01);
        c2_a->SetBorderMode(0);
        c2_a->SetBorderSize(2);
        
        c2_a->SetBottomMargin(0.0);
        c2_a->SetFrameBorderMode(0);
        c2_a->SetFrameBorderMode(0);

        c2_a->Draw();
        c2_a->cd();
        
        TPC510->GetXaxis()->SetTitle();
        TPC510->GetXaxis()->CenterTitle();
        TPC510->SetLineColor(2);
        TPC510->SetMarkerColor(9);
        TPC510->SetMarkerStyle(20);
        TPC510->GetXaxis()->SetLabelColor(0);
        TPC510->Draw();
        
        VZE510->GetXaxis()->SetTitle();
        VZE510->GetXaxis()->CenterTitle();
        VZE510->SetMarkerColor(4);
        VZE510->SetMarkerStyle(27);
        VZE510->SetLineColor(8);
        VZE510->GetXaxis()->SetLabelColor(0);
	VZE510->Draw("same");
///////////////////////////////padb//////////        
        c2->cd();
        TPad *c2_b = new TPad("c2_b", "c2_b", 0., 0. , 0.85, 0.20);
        c2_b->SetTopMargin(0.);
        c2_b->SetRightMargin(0.01);
        c2_b->SetBottomMargin(0.2);
        c2_b->SetFillColor(0);
        c2_b->SetBorderMode(0);
        c2_b->SetBorderSize(2);
        c2_b->SetFrameBorderMode(0);
        c2_b->SetFrameBorderMode(0);
        c2_b->Draw();
        c2_b->cd();

        c2_b->Draw();
        c2_b->cd();
       
        ratio2->GetYaxis()->SetRangeUser(-3,3);
        ratio2->GetYaxis()->SetTitle();
        ratio2->SetLineColor(2);
        ratio2->SetMarkerColor(4);
        ratio2->SetMarkerStyle(23);
        ratio2->GetXaxis()->SetLabelColor();
        ratio2->GetXaxis()->SetLabelFont();
        ratio2->GetXaxis()->SetLabelSize(0.15);   
        ratio2->GetYaxis()->SetLabelSize(0.1);
        ratio2->Draw();


}
