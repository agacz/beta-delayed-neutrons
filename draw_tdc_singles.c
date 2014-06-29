void draw_tdc_singles(char*);

void draw_tdc_singles(char *histo) {
	TFile *f = new TFile("~/135-Sb/ROOT/files/sum.root");
	TH1I *h1 = f->Get(histo);
	TH1I *h2 = (TH1I*)h1->Clone("h2");
	
	TCanvas *c1_tdc_singles = new TCanvas("c1_tdc_singles","c1_tdc_singles",900,600);
	c1_tdc_singles->SetLogy();
	h1->Draw();
	
	TCanvas *c2_tdc_singles = new TCanvas("c2_tdc_singles","c2_tdc_singles",900,600);
	c2_tdc_singles->SetLogy();
	h2->GetXaxis()->SetRangeUser(-100,200);
	h2->Draw();
	
	// Find peak
	Int_t x, y, xMax, yMax;
	for (x=-100; x<=200; x++) {
		y = h2->GetBinContent(x+101);
		if (yMax < y) {
			xMax = x;
			yMax = y;
		}
	}
	
	printf("\npeak y=%d at tdc=%dns\n\n",yMax,xMax);
	
	/*
	TF1 *fit = new TF1("fit","gaus",-50,50);
	*/

}
