
void mcp_physical() {
	
//	TFile *f1 = new TFile("~/shane/cal2013/rootfiles/238Pu_R_mcp_mask2.root","read");
//	TFile *f1 = new TFile("~/shane/cal2013/rootfiles/238Pu_T_mcp_mask2.root","read");
//	TFile *f1 = new TFile("~/shane/cal2013/rootfiles/238Pu_T_mcp_mask3.root","read");
	TFile *f1 = new TFile("~/shane/cal2013/rootfiles/238Pu_R_mcp_NoMask.root","read");
//	TFile *f1 = new TFile("~/shane/cal2013/rootfiles/run02338.root","read");
//	TFile *f1 = new TFile("~/shane/cal2013/rootfiles/run_rawMCP_02338.root","read");
//	TFile *f1 = new TFile("~/shane/cal2013/rootfiles/run01185.root","read");
	
	Int_t use_cal = 0;
	Int_t use_fidArea = 1;
	
	if (use_cal == 0) {
		if (use_fidArea == 1) {
			cout << "Using Fid Area" << endl;
			TH2I *h_R_phys	= (TH2I*)gDirectory->Get("h_R_mcpMapPhysFidArea");
			TH2I *h_R_3post	= (TH2I*)gDirectory->Get("h_R_mcpMapPhysFidArea_3post");
			TH2I *h_T_phys	= (TH2I*)gDirectory->Get("h_T_mcpMapPhysFidArea");
			TH2I *h_T_3post	= (TH2I*)gDirectory->Get("h_T_mcpMapPhysFidArea_3post");
		}
		else {
			TH2I *h_R_phys	= (TH2I*)gDirectory->Get("h_R_mcpMapPhys");
			TH2I *h_R_3post	= (TH2I*)gDirectory->Get("h_R_mcpMapPhys_3post");
			TH2I *h_T_phys	= (TH2I*)gDirectory->Get("h_T_mcpMapPhys");
			TH2I *h_T_3post	= (TH2I*)gDirectory->Get("h_T_mcpMapPhys_3post");
		}
	}
	else {
		f1->cd("mcp_cal");
		TH2I *h_R_phys	= (TH2I*)gDirectory->Get("h_R_mcp_map_1");
		TH2I *h_R_3post	= (TH2I*)gDirectory->Get("h_R_mcp_map_missingOne_1");
		TH2I *h_T_phys	= (TH2I*)gDirectory->Get("h_T_mcp_map_1");
		TH2I *h_T_3post	= (TH2I*)gDirectory->Get("h_T_mcp_map_missingOne_1");
	}
	
	TCanvas *c_phys = new TCanvas("c_phys","Physical Maps",1000,1000);
	gStyle->SetOptStat("e");
	c_phys->Divide(2,2);
	c_phys->cd(1);
	h_T_phys->Draw("colz");
	c_phys->cd(2);
	h_R_phys->Draw("colz");
	c_phys->cd(3);
	h_T_3post->Draw("colz");
	c_phys->cd(4);
	h_R_3post->Draw("colz");
	
}
