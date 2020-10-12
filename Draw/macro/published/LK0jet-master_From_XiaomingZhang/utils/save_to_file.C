void save_to_file(const char *foutname=0)
{
	if (gPad == 0x0)
		return;
	TList *l = gPad->GetListOfPrimitives();
	cout << gPad->GetTitle() << endl;
	TString sfoutname = "";
	if (foutname == 0x0)
		sfoutname = TString::Format("s2f_%s.root", gPad->GetName());
	else
		sfoutname = TString(foutname);
	TFile *fout = new TFile(sfoutname.Data(), "RECREATE");
	fout->cd();
	TIter it(l);
	TObject *o = 0x0;
	while ((o = it.Next())!=0)
	{
		//cout << "title:" << o->GetTitle();
		//cout << " name:" << o->GetName() << endl;
		//o->Write();
		//cout << "class:" << o->Class()->GetName() << endl;
		if (o->InheritsFrom("TGraph"))
		{
			TGraph *gr = (TGraph*)o;
			cout << "[i] title:" << gr->GetTitle();
			cout << " name:" << gr->GetName() << endl;
			gr->Write();
		}
		if (o->InheritsFrom("TH1"))
		{
			TH1 *h = (TH1*)o;
			cout << "[i] title:" << h->GetTitle();
			cout << " name:" << h->GetName() << endl;
			h->Write();
		}
	}
	fout->Close();
	cout << "[i] saved to file:" << sfoutname << endl;
}