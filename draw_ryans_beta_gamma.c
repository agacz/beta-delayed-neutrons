
Double_t fitf (Double_t *x, Double_t *a) {
	Double_t fitval = a[0] + a[1]*TMath::Exp( -0.5 * ((x[0]-a[2])/a[3]) * ((x[0]-a[2])/a[3]) );
	return fitval;
}


void draw_ryans_beta_gamma() {

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
	
	Int_t t_bkgd	= 5000;
	Int_t t_cycle	= 15000 + t_bkgd;
	
	//TFile *f = new TFile("~/135-Sb/ROOT/files/sum_bg.root");
	//f->cd("beta_gamma");
	
	TFile *f = new TFile("~/code/analysis_011613_sb2_1-37.root");
	/*
	TH1I *h_LT		= gDirectory->Get("h_bg_LT");
	TH1I *h_LR		= gDirectory->Get("h_bg_LR");
	TH1I *h_BT		= gDirectory->Get("h_bg_BT");
	TH1I *h_BR		= gDirectory->Get("h_bg_BR");
	
	TH1I *h_bkgd_LT		= gDirectory->Get("h_bkgd_bg_LT");
	TH1I *h_bkgd_LR		= gDirectory->Get("h_bkgd_bg_LR");
	TH1I *h_bkgd_BT		= gDirectory->Get("h_bkgd_bg_BT");
	TH1I *h_bkgd_BR		= gDirectory->Get("h_bkgd_bg_BR");
	*/
	//TH1I *h_100 = h->Rebin(100,"h");
	
	TH1I *h		= gDirectory->Get("r_ge_plas_eject");
	Float_t c = 1666.0;
	
	//TF1 *fn	= new TF1("fn", fitf, 1270., 1320., 4);
	TF1 *fn	= new TF1("fn", fitf, c-50., c+50., 4);
	fn->SetParameters(4., 25.0, c, 2.9);
	fn->SetParNames("DC", "Amplitude", "Centroid", "Sigma");
	
	fn->SetParLimits(0,0,10);
	fn->SetParLimits(1,0,50);
	fn->SetParLimits(2,c-50., c+50.);
	fn->SetParLimits(3,0,3);
	
	h->Fit("fn","R+");
	//fn->SetParLimits(0,5000,12000);
	//fn->SetParLimits(1,1000,3000);
	//fn->SetParLimits(2,0,7000);
/*	
	printf("\nLT:\n");
	//h_LT->Fit("fn","+");
	printf("\nLR:\n");
	h_LR->Fit("fn","+");
	printf("\nBT:\n");
	//h_BT->Fit("fn","+");
	printf("\nBR:\n");
	h_BR->Fit("fn","+");
	
	printf("\nLT bkgd:\n");
	//h_bkgd_LT->Fit("fn","+");
	printf("\nLR bkgd:\n");
	h_bkgd_LR->Fit("fn","+");
	printf("\nBT bkgd:\n");
	//h_bkgd_BT->Fit("fn","+");
	printf("\nBR bkgd:\n");
	h_bkgd_BR->Fit("fn","+");
	
//Canvas 1
	
	TCanvas *c1_beta_gamma = new TCanvas("c1_beta_gamma","c1_beta_gamma",1000,1000);
	c1_beta_gamma->Divide(2,2);
	
	//c1_beta_gamma->cd(1);
	//h_LT->Draw();
	//h_LT->GetXaxis()->SetRangeUser(1280,1300);
	
	c1_beta_gamma->cd(2);
	h_LR->Draw();
	//h_LR->GetXaxis()->SetRangeUser(1270,1320);
	
	//c1_beta_gamma->cd(3);
	//h_BT->Draw();
	//h_BT->GetXaxis()->SetRangeUser(1280,1300);
	
	c1_beta_gamma->cd(4);
	h_BR->Draw();
	//h_BR->GetXaxis()->SetRangeUser(1280,1300);
	
//Canvas 2
	
	TCanvas *c1_bkgd_beta_gamma = new TCanvas("c1_bkgd_beta_gamma","c1_bkgd_beta_gamma",1000,1000);
	c1_bkgd_beta_gamma->Divide(2,2);
	
	//c1_bkgd_beta_gamma->cd(1);
	//h_bkgd_LT->Draw();
	//h_bkgd_LT->GetXaxis()->SetRangeUser(1280,1300);
	
	c1_bkgd_beta_gamma->cd(2);
	h_bkgd_LR->Draw();
	//h_Lbkgd_R->GetXaxis()->SetRangeUser(1270,1320);
	
	//c1_bkgd_beta_gamma->cd(3);
	//h_bkgd_BT->Draw();
	//h_bkgd_BT->GetXaxis()->SetRangeUser(1280,1300);
	
	c1_bkgd_beta_gamma->cd(4);
	h_bkgd_BR->Draw();
	//h_bkgd_BR->GetXaxis()->SetRangeUser(1280,1300);	
*/

	TCanvas *c_beta_gamma_fit_by_hand = new TCanvas("c_beta_gamma_fit_by_hand","c_beta_gamma_fit_by_hand",900,600);
	h->Draw();
	h->GetXaxis()->SetRangeUser(c-50.,c+50.);
	fn->Draw("SAME");
	
	//Int_t area = h_100->Integral(220+53,220+200);
	//printf("\ngross=%d\n\n",area);
	//area = area - 11000*147;
	//printf("\nnet=%d\n\n",area);
	
	//printf("\n%f\n",EnMax);
	
	/*
	TH1F *hh_EnSignal = new TH1F(*hh_En);
	hh_EnSignal->Sumw2();	// I don't know what this does, just copying it
	hh_EnSignal->Add(fn_EnBkgd,-1);
	// From the description of 'Add':
	// IMPORTANT NOTE1: If you intend to use the errors of this histogram later
	// you should call Sumw2 before making this operation.
	// This is particularly important if you fit the histogram after TH1::Add
	
	TCanvas *c1 = new TCanvas("c_En","En less background",800,600);
	c1->SetLogy();
	
	hh_En->Draw();
	//hh_En->SetXaxis(0,1500);
	//hh_EnSignal->Draw("BSAME");
	fn_EnBkgd->Draw("SAME");
	
//Canvas 1	
/*	c1_beta_gamma->Divide(1,2);
	
	c1_beta_gamma->cd(1);
	h_beta_vs_time->Draw();
	
	c1_beta_gamma->cd(2);
	h_beta_vs_time_B->Draw();
*/

}
