{
	gROOT->Reset();
	
	Double_t xMin_1 = -0.1;
	Double_t xMax_1 = 10.;
	
	Double_t xMin_2 = -0.1;
	Double_t xMax_2 = 10.;
	Double_t yMax_2 = 300.;
	
	Double_t mean_x1 = 1.5;
	Double_t mean_x2 = 10.;
	
	Int_t color_100ms = kOrange;
	Int_t color_200ms = kRed;
	Int_t color_300ms = kBlue;
	
	Double_t mean;
	Double_t mean_100ms;
	Double_t mean_200ms;
	Double_t mean_300ms;
	Double_t mean_err;
	Double_t mean_err_100ms;
	Double_t mean_err_200ms;
	Double_t mean_err_300ms;
	
	TFile *f = new TFile("./files/sum.root");

//Canvas 1

	f->cd();
	
	TCanvas *c1_cooling = new TCanvas("c1_cooling","c1_cooling",900,600);
	c1_cooling->SetLogy();
	
	TH1I *h_tof_clone = (TH1I*)h_tof->Clone("h_tof_clone");
	TH1I *h_tof_1 = (TH1I*)h_tof_clone->Rebin(100,"h_tof");

	h_tof_1->GetXaxis()->SetRangeUser(mean_x1, mean_x2);
	mean = h_tof_1->GetMean();
	mean_err = h_tof_1->GetMeanError();
	
	h_tof_1->Draw();
	
	f->cd("cooling");
	
	TH1I *h_tof_100ms_clone = (TH1I*)h_tof_100ms->Clone("h_tof_100ms_clone");
	TH1I *h_tof_200ms_clone = (TH1I*)h_tof_200ms->Clone("h_tof_200ms_clone");
	TH1I *h_tof_300ms_clone = (TH1I*)h_tof_300ms->Clone("h_tof_300ms_clone");
	
	TH1I *h_tof_100ms_1 = h_tof_100ms_clone->Rebin(100,"h_tof_100ms");
	TH1I *h_tof_200ms_1 = h_tof_200ms_clone->Rebin(100,"h_tof_200ms");
	TH1I *h_tof_300ms_1 = h_tof_300ms_clone->Rebin(100,"h_tof_300ms");
	
	h_tof_100ms_1->GetXaxis()->SetRangeUser(mean_x1, mean_x2);
	mean_100ms		= h_tof_100ms_1->GetMean();
	mean_err_100ms	= h_tof_100ms_1->GetMeanError();
	
	h_tof_200ms_1->GetXaxis()->SetRangeUser(mean_x1, mean_x2);
	mean_200ms		= h_tof_200ms_1->GetMean();
	mean_err_200ms	= h_tof_200ms_1->GetMeanError();
	
	h_tof_300ms_1->GetXaxis()->SetRangeUser(mean_x1, mean_x2);
	mean_300ms 		= h_tof_300ms_1->GetMean();
	mean_err_300ms	= h_tof_300ms_1->GetMeanError();
	
	printf("\n");
	printf("h_tof:\t\t%f +/- %f\n", mean, mean_err);
	printf("h_tof_100ms:\t%f +/- %f\n", mean_100ms, mean_err_100ms);
	printf("h_tof_200ms:\t%f +/- %f\n", mean_200ms, mean_err_200ms);
	printf("h_tof_300ms:\t%f +/- %f\n", mean_300ms, mean_err_300ms);
	printf("\n");
	
	h_tof_100ms_1->SetLineColor(color_100ms);
	h_tof_200ms_1->SetLineColor(color_200ms);
	h_tof_300ms_1->SetLineColor(color_300ms);
	
	h_tof_100ms_1->Draw("SAME");
	h_tof_200ms_1->Draw("SAME");
	h_tof_300ms_1->Draw("SAME");
	
	h_tof_1->GetXaxis()->SetRangeUser(xMin_1, xMax_1);
	h_tof_100ms_1->GetXaxis()->SetRangeUser(xMin_1, xMax_1);
	h_tof_200ms_1->GetXaxis()->SetRangeUser(xMin_1, xMax_1);
	h_tof_300ms_1->GetXaxis()->SetRangeUser(xMin_1, xMax_1);
	
	leg_1 = new TLegend(0.6, 0.8, 1.0, 1.0);
	leg_1->AddEntry(h_tof_100ms_1, "0 < time since capt < 100ms");
	leg_1->AddEntry(h_tof_200ms_1, "100ms < time since capt < 200ms");
	leg_1->AddEntry(h_tof_300ms_1, "200ms < time since capt < 300ms");
	leg_1->AddEntry(h_tof_1, "0 < time since capt < 300ms (ie. all ions)");
	leg_1->Draw();
	
	//delete h_tof_100ms_clone;
	
//Canvas 2
	
	f->cd();
	
	TCanvas *c2_cooling = new TCanvas("c2_cooling","c2_cooling",900,600);
	//c2_cooling->SetLogy();
	
	//TH1I *h_tof_clone = (TH1I*)h_tof->Clone("h_tof_clone");
	//TH1I *h_tof_2 = h_tof->Rebin(100);
	//h_tof_2->Draw();

	f->cd("cooling");
	
	TH1I *h_tof_100ms_clone = (TH1I*)h_tof_100ms->Clone("h_tof_100ms_clone");
	TH1I *h_tof_200ms_clone = (TH1I*)h_tof_200ms->Clone("h_tof_200ms_clone");
	TH1I *h_tof_300ms_clone = (TH1I*)h_tof_300ms->Clone("h_tof_300ms_clone");
	
	TH1I *h_tof_100ms_2 = h_tof_100ms_clone->Rebin(100);
	TH1I *h_tof_200ms_2 = h_tof_200ms_clone->Rebin(100);
	TH1I *h_tof_300ms_2 = h_tof_300ms_clone->Rebin(100);
	
	h_tof_100ms_2->SetLineColor(color_100ms);
	h_tof_200ms_2->SetLineColor(color_200ms);
	h_tof_300ms_2->SetLineColor(color_300ms);
	
	h_tof_100ms_2->Draw("E0");
	h_tof_200ms_2->Draw("E0 SAME");
	h_tof_300ms_2->Draw("E0 SAME");
	
	//h_tof_2			->GetXaxis()->SetRangeUser(xMin_2, xMax_2);
	h_tof_100ms_2	->GetXaxis()->SetRangeUser(xMin_2, xMax_2);
	h_tof_200ms_2	->GetXaxis()->SetRangeUser(xMin_2, xMax_2);
	h_tof_300ms_2	->GetXaxis()->SetRangeUser(xMin_2, xMax_2);
	
	//h_tof_2			->GetYaxis()->SetRangeUser(0, yMax_2);
	h_tof_100ms_2	->GetYaxis()->SetRangeUser(0, yMax_2);
	h_tof_200ms_2	->GetYaxis()->SetRangeUser(0, yMax_2);
	h_tof_300ms_2	->GetYaxis()->SetRangeUser(0, yMax_2);
	
	leg_2 = new TLegend(0.6, 0.7, 1.0, 0.9);
	leg_2->AddEntry(h_tof_100ms_1, "0 < time since capt < 100ms");
	leg_2->AddEntry(h_tof_200ms_1, "100ms < time since capt < 200ms");
	leg_2->AddEntry(h_tof_300ms_1, "200ms < time since capt < 300ms");
	//leg_2->AddEntry(h_tof_1, "0 < time since capt < 300ms (ie. all ions)");
	leg_2->Draw();
	
	
/*	
	h_tof_100ms_1->GetXaxis()->SetRangeUser(0,xMax_1);
	h_tof_200ms_1->GetXaxis()->SetRangeUser(0,xMax_1);
	h_tof_300ms_1->GetXaxis()->SetRangeUser(0,xMax_1);
	
	h_tof_100ms_1->GetYaxis()->SetRangeUser(0,yMax_1);
	h_tof_200ms_1->GetYaxis()->SetRangeUser(0,yMax_1);
	h_tof_300ms_1->GetYaxis()->SetRangeUser(0,yMax_1);
	
/*	
	h_tof_100ms->Rebin(100);
	h_tof_200ms->Rebin(100);
	h_tof_300ms->Rebin(100);
	
	h_tof_100ms_1->Draw("C E0");
	h_tof_200ms_1->Draw("C E0 SAME");
	h_tof_300ms_1->Draw("C E0 SAME");
*/	
	
}
