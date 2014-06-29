
void draw_missing_posts () {
	TFile *infile = new TFile("MissingPosts.root","read");
	TCanvas *c_missing_posts = new TCanvas("c_missing_posts","Number of missing MCP posts",945,600);
	c_missing_posts->SetLogy();
	hn_R_missing->Draw();
	hn_T_missing->Draw("same");
	hn_T_missing->SetLineColor(kRed);
	
	Int_t nR[5], nT[5];
	for (Int_t i = 0; i<5; i++) {
		nR[i] = hn_R_missing->GetBinContent(i+1);
		nT[i] = hn_T_missing->GetBinContent(i+1);
	}
	cout << endl;
	cout << "Top MCP  : " << nT[0] << " missing 0; " << nT[1] << " missing 1; " << nT[2] << " missing 2; " << nT[3] << " missing 3; " << nT[4] << " missing 4." << endl;
	cout << "Right MCP: " << nR[0] << " missing 0; " << nR[1] << " missing 1; " << nR[2] << " missing 2; " << nR[3] << " missing 3; " << nR[4] << " missing 4." << endl;
	
}
