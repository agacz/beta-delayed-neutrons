
Double_t fitf (Double_t *x, Double_t *a) {
	Double_t fitval = a[0] * ( a[1] + a[2]*TMath::Exp( -TMath::Power((x[0]-a[3])/a[4], 8.0) ) );
	return fitval;
}


void maps() {

	gROOT->Reset();
	
	TFile *f = new TFile("/disks/3/bpttrap/135-Sb/ROOT/files/bdn.root");
	
	Int_t mapBins = 1000;
	TH2I *h_T_map_sum_gt400	= new TH2I("h_T_map_sum_gt400", "Top MCP map with sum of posts > 400", mapBins, -25.0, 25.0, mapBins, -25.0, 25.0);
	TH2I *h_T_map_post_gt2500	= new TH2I("h_T_map_post_gt2500", "Top MCP map w/ any post > 2500", mapBins, -25.0, 25.0, mapBins, -25.0, 25.0);
	TH2I *h_T_map_post_gt3000	= new TH2I("h_T_map_post_gt3000", "Top MCP map w/ any post > 3000", mapBins, -25.0, 25.0, mapBins, -25.0, 25.0);
	TH2I *h_T_map_post_gt3500	= new TH2I("h_T_map_post_gt3500", "Top MCP map w/ any post > 3500", mapBins, -25.0, 25.0, mapBins, -25.0, 25.0);
	TH1I *h_T_x		= new TH1I("h_T_x", "Top MCP x values", mapBins, -25.0, 25.0);
	TH1I *h_T_y		= new TH1I("h_T_y", "Top MCP y values", mapBins, -25.0, 25.0);
	TTree *t = (TTree*)f->Get("bdn_Tree");
	Int_t nEntries = t->GetEntries();
	Double_t a, b, c, d, e, x, y;
	
	printf("\n %d entries \n\n",nEntries);
	
	for (Int_t i=0; i<=nEntries; i++) {
		
		t->GetEntry(i);
		
		a = t->GetLeaf("a_T_mcpA")->GetValue();
		b = t->GetLeaf("a_T_mcpB")->GetValue();
		c = t->GetLeaf("a_T_mcpC")->GetValue();
		d = t->GetLeaf("a_T_mcpD")->GetValue();
		e = a+b+c+d;
		x = 25.0*(t->GetLeaf("T_mcpX")->GetValue());
		y = 25.0*(t->GetLeaf("T_mcpY")->GetValue());
		
		if (e > 400) {
			h_T_map_sum_gt400->Fill(x,y);
			if (-3.0 < y && y < 3.0) h_T_x->Fill(x);
			if (-3.0 < x && x < 3.0) h_T_y->Fill(y);
		}
		if (a>2500 || b>2500 || c>2500 || d>2500) h_T_map_post_gt2500->Fill(x,y);
		if (a>3000 || b>3000 || c>3000 || d>3000) h_T_map_post_gt3000->Fill(x,y);
		if (a>3500 || b>3500 || c>3500 || d>3500) h_T_map_post_gt3500->Fill(x,y);
		
	}
	
	TF1 *fn	= new TF1("fn", fitf, -3.0, 3.0, 5);
	fn->SetParameters(50.0/mapBins, 0.1., 200.0/(50.0/mapBins), 0.4, 0.5);
	fn->SetParNames("Bin width", "Constant", "Amplitude", "Centroid", "Width", "Power");
	
	fn->FixParameter(0, 50.0/mapBins);
	/*fn->SetParLimits(1,0,3000);
	fn->SetParLimits(2,0,3000);
	fn->SetParLimits(3,0,3000);
	fn->SetParLimits(4,0,3000);
	fn->SetParLimits(5,0,3000);*/
	
	gStyle->SetOptStat(10);
	
	
	TCanvas *c_gt400 = new TCanvas("c_gt400","c_gt400",900,900);
	h_T_map_sum_gt400->Draw();
/*		
	TCanvas *c_gt2500 = new TCanvas("c_gt2500","c_gt2500",900,900);
	h_T_map_post_gt2500->Draw();

	
	TCanvas *c_gt3000 = new TCanvas("c_gt3000","c_gt3000",900,900);
	h_T_map_post_gt3000->Draw();
	
	TCanvas *c_gt3500 = new TCanvas("c_gt3500","c_gt3500",900,900);
	h_T_map_post_gt3500->Draw();
*/	
	TCanvas *c_x = new TCanvas("c_x","c_x",1400,700);
	c_x->Divide(2,1);
	c_x->cd(1);
	h_T_x->Draw();
	h_T_x->Fit("fn","R+");
	//fn->Draw("SAME");
	
	//TCanvas *c_y = new TCanvas("c_y","c_y",900,900);
	c_x->cd(2);
	h_T_y->Draw();
	fn->SetParameters(50.0/mapBins, 0.1., 200.0/(50.0/mapBins), -0.4, 0.5);
	h_T_y->Fit("fn","R+");

}
