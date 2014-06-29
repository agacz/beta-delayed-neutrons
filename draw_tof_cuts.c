{
	gROOT->Reset();
	
	Double_t xMin_1 = -.05;
	Double_t xMax_1 = .05;
	
	Double_t xMin_2 = -0.1;
	Double_t xMax_2 = 10.;
	Double_t yMax_2 = 300.;
	
	Double_t mean_x1 = 1.5;
	Double_t mean_x2 = 10.;
	
	Int_t color_a = kRed;
	Int_t color_b = kBlue;
	
	Double_t mean;
	Double_t mean_100ms;
	Double_t mean_200ms;
	Double_t mean_300ms;
	
	TFile *f = new TFile("/disks/3/bpttrap/135-Sb/ROOT/files/bdn.root");

//Canvas 1 - LT

	f->cd("tof_cuts");
	
	TCanvas *c1_tof_cuts_LT = new TCanvas("c1_tof_cuts_LT","c1_tof_cuts_LT",900,600);
	c1_tof_cuts_LT->SetLogy();
	
	TH1I *h_tof_LT_a_1 = (TH1I*)h_tof_LT_a->Clone("h_tof_LT_a_1");
	TH1I *h_tof_LT_b_1 = (TH1I*)h_tof_LT_b->Clone("h_tof_LT_b_1");
	//TH1I *h_tof_LT_a_1 = (TH1I*)h_tof_LT_a_1->Rebin(100,"h_tof_LT_1");
	
	h_tof_LT_a_1->SetLineColor(color_a);
	h_tof_LT_b_1->SetLineColor(color_b);
	h_tof_LT_a_1->GetXaxis()->SetRangeUser(xMin_1, xMax_1);
	h_tof_LT_b_1->GetXaxis()->SetRangeUser(xMin_1, xMax_1);
	h_tof_LT_a_1->Draw();
	h_tof_LT_b_1->Draw("SAME");
	
	leg_LR = new TLegend(0.7, 0.85, 0.98, 1.0);
	leg_LR->AddEntry(h_tof_LR_a_1, "mcp - dEa, no cuts");
	leg_LR->AddEntry(h_tof_LR_b_1, "mcp - dEb, no cuts");
	leg_LR->Draw();
	
//Canvas 1 - LR

	f->cd("tof_cuts");
	
	TCanvas *c1_tof_cuts_LR = new TCanvas("c1_tof_cuts_LR","c1_tof_cuts_LR",900,600);
	c1_tof_cuts_LR->SetLogy();
	
	TH1I *h_tof_LR_a_1 = (TH1I*)h_tof_LR_a->Clone("h_tof_LR_a_1");
	TH1I *h_tof_LR_b_1 = (TH1I*)h_tof_LR_b->Clone("h_tof_LR_b_1");
	//TH1I *h_tof_LR_a_1 = (TH1I*)h_tof_LR_a_1->Rebin(100,"h_tof_LR_1");
	
	h_tof_LR_a_1->SetLineColor(color_a);
	h_tof_LR_b_1->SetLineColor(color_b);
	h_tof_LR_a_1->GetXaxis()->SetRangeUser(xMin_1, xMax_1);
	h_tof_LR_b_1->GetXaxis()->SetRangeUser(xMin_1, xMax_1);
	h_tof_LR_a_1->Draw();
	h_tof_LR_b_1->Draw("SAME");
	
	leg_LR = new TLegend(0.7, 0.85, 0.98, 1.0);
	leg_LR->AddEntry(h_tof_LR_a_1, "mcp - dEa, no cuts");
	leg_LR->AddEntry(h_tof_LR_b_1, "mcp - dEb, no cuts");
	leg_LR->Draw();
	
//Canvas 1 - BT

	f->cd("tof_cuts");
	
	TCanvas *c1_tof_cuts_BT = new TCanvas("c1_tof_cuts_BT","c1_tof_cuts_BT",900,600);
	c1_tof_cuts_BT->SetLogy();
	
	TH1I *h_tof_BT_a_1 = (TH1I*)h_tof_BT_a->Clone("h_tof_BT_a_1");
	TH1I *h_tof_BT_b_1 = (TH1I*)h_tof_BT_b->Clone("h_tof_BT_b_1");
	//TH1I *h_tof_BT_a_1 = (TH1I*)h_tof_BT_a_1->Rebin(100,"h_tof_BT_1");
	
	h_tof_BT_a_1->SetLineColor(color_a);
	h_tof_BT_b_1->SetLineColor(color_b);
	h_tof_BT_a_1->GetXaxis()->SetRangeUser(xMin_1, xMax_1);
	h_tof_BT_b_1->GetXaxis()->SetRangeUser(xMin_1, xMax_1);
	h_tof_BT_a_1->Draw();
	h_tof_BT_b_1->Draw("SAME");
	
	leg_LR = new TLegend(0.7, 0.85, 0.98, 1.0);
	leg_LR->AddEntry(h_tof_LR_a_1, "mcp - dEa, no cuts");
	leg_LR->AddEntry(h_tof_LR_b_1, "mcp - dEb, no cuts");
	leg_LR->Draw();

//Canvas 1 - BR

	f->cd("tof_cuts");
	
	TCanvas *c1_tof_cuts_BR = new TCanvas("c1_tof_cuts_BR","c1_tof_cuts_BR",900,600);
	c1_tof_cuts_BR->SetLogy();
	
	TH1I *h_tof_BR_a_1 = (TH1I*)h_tof_BR_a->Clone("h_tof_BR_a_1");
	TH1I *h_tof_BR_b_1 = (TH1I*)h_tof_BR_b->Clone("h_tof_BR_b_1");
	//TH1I *h_tof_BR_a_1 = (TH1I*)h_tof_BR_a_1->Rebin(100,"h_tof_BR_1");
	
	h_tof_BR_a_1->SetLineColor(color_a);
	h_tof_BR_b_1->SetLineColor(color_b);
	h_tof_BR_a_1->GetXaxis()->SetRangeUser(xMin_1, xMax_1);
	h_tof_BR_b_1->GetXaxis()->SetRangeUser(xMin_1, xMax_1);
	h_tof_BR_a_1->Draw();
	h_tof_BR_b_1->Draw("SAME");
	
	leg_LR = new TLegend(0.7, 0.85, 0.98, 1.0);
	leg_LR->AddEntry(h_tof_LR_a_1, "mcp - dEa, no cuts");
	leg_LR->AddEntry(h_tof_LR_b_1, "mcp - dEb, no cuts");
	leg_LR->Draw();
	
	
/*	
//Canvas 2
	
	f->cd();
	
	TCanvas *c2_tof_cuts = new TCanvas("c2_tof_cuts","c2_tof_cuts",900,600);
	//c2_tof_cuts->SetLogy();
	
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
*/	
	
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
