{
	Int_t color_BT = kRed;
	Int_t color_LT = kRed;
	Int_t color_BR = kBlue;
	Int_t color_LR = kBlue;
	
	TFile *f = new TFile("~/135-Sb-1/sum_135sb1.root");
	f->cd("tof_official");
	
	TH1I *h_BT_off = (TH1I*)h_tof_BT_official->Clone("h_BT_off");
	TH1I *h_BR_off = (TH1I*)h_tof_BR_official->Clone("h_BR_off");
	TH1I *h_LT_off = (TH1I*)h_tof_LT_official->Clone("h_LT_off");
	TH1I *h_LR_off = (TH1I*)h_tof_LR_official->Clone("h_LR_off");
	
	TFile *g = new TFile("~/135-Sb-2/sum_135sb2.root");
	g->cd("tof_official");
	
	TH1I *h_BT_off2 = (TH1I*)h_tof_BT_official->Clone("h_BT_off2");
	TH1I *h_LT_off2 = (TH1I*)h_tof_LT_official->Clone("h_LT_off2");
	
	Int_t rebin=100;
	h_BT_off->Rebin(rebin);
	h_BR_off->Rebin(rebin);
	h_LT_off->Rebin(rebin);
	h_LR_off->Rebin(rebin);
	h_BT_off2->Rebin(rebin);
	h_LT_off2->Rebin(rebin);
	
	Double_t tofMin = -1.0;
	Double_t tofMax = 22.5;
	Double_t tof1 = 2.0; //us, bounds for integral
	Double_t tof2 = 10.0; //us, bounds for integral
	Double_t x1 = (tof1 - tofMin + 0.001*rebin)/(0.001*rebin);
	Double_t x2 = (tof2 - tofMin + 0.001*rebin)/(0.001*rebin);
	Double_t n_BT_off = h_BT_off->Integral(x1,x2);
	Double_t n_LR_off = h_LR_off->Integral(x1,x2);
	Double_t n_BT_off2 = h_BT_off2->Integral(x1,x2);
	Double_t n_BR_off = h_BR_off->Integral(x1,x2);
	Double_t n_LT_off = h_LT_off->Integral(x1,x2);
	Double_t n_LT_off2 = h_LT_off2->Integral(x1,x2);
	
	printf("\n");
	printf("Run 1 (180-deg) BT: %d\n",n_BT_off);
	printf("Run 1 (180-deg) LR: %d\n",n_LR_off);
	printf("Run 2 (180-deg) BT: %d\n",n_BT_off2);
	printf("Run 1  (90-deg) BR: %d\n",n_BR_off);
	printf("Run 1  (90-deg) LT: %d\n",n_LT_off);
	printf("Run 2  (90-deg) LT: %d\n",n_LT_off2);
	printf("\n");
	
	h_BT_off->SetLineColor(kRed);
	h_BR_off->SetLineColor(kBlue);
	h_LT_off->SetLineColor(kRed);
	h_LR_off->SetLineColor(kBlue);
	h_BT_off2->SetLineColor(kGreen);
	h_LT_off2->SetLineColor(kGreen);
	
	h_BT_off2->Scale(2.1);
	h_LT_off2->Scale(2.1);
	
	h_BT_off->GetYaxis()->SetRangeUser(0,400);
	h_BR_off->GetYaxis()->SetRangeUser(0,50);
	
	TCanvas *c1_problem = new TCanvas("c1_problem","180-degree combos",800,600);
	h_BT_off->Draw();
	h_LR_off->Draw("SAME");
	h_BT_off2->Draw("SAME");
	
	leg_1 = new TLegend(0.6, 0.8, 0.9, 0.9);
	leg_1->AddEntry(h_BT_off, "BT Run 1: 5478 slow");
	leg_1->AddEntry(h_LR_off, "LR Run 1: 3849 slow");
	leg_1->AddEntry(h_BT_off2, "BT Run 2: 1982 slow");
	leg_1->Draw();
	
	TCanvas *c2_problem = new TCanvas("c2_problem","90-degree combos",800,600);
	h_BR_off->Draw();
	h_LT_off->Draw("SAME");
	h_LT_off2->Draw("SAME");
	
	leg_2 = new TLegend(0.6, 0.8, 0.9, 0.9);
	leg_2->AddEntry(h_LT_off, "LT Run 1: 918 slow");
	leg_2->AddEntry(h_BR_off, "BR Run 1: 1090 slow");
	leg_2->AddEntry(h_LT_off2, "LT Run 2: 265 slow");
	leg_2->Draw();
	
}
