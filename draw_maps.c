
Double_t fitf (Double_t *x, Double_t *a) {
	Double_t fitval = a[0] * ( a[1] + a[2]*TMath::Exp( -TMath::Power((x[0]-a[3])/a[4], 8.0) ) );
	return fitval;
}


void draw_maps() {

	gROOT->Reset();
	gStyle->SetOptStat("e");

// ****** CHOOSE FILE AND HISTOS ***********
	
	TFile *f1 = new TFile("~/shane/cal2013/rootfiles/238Pu_R_mcp_mask2_rawMCP.root");
//	TFile *f1 = new TFile("~/shane/cal2013/rootfiles/238Pu_T_mcp_mask2_rawMCP.root");
//	TFile *f1 = new TFile("~/shane/cal2013/rootfiles/238Pu_T_mcp_mask3_rawMCP.root");
//	TFile *f1 = new TFile("~/shane/cal2013/rootfiles/run_rawMCP_01147.root");// Top MCP, Mask 3, Bias = -2450V
//	TFile *f1 = new TFile("~/shane/cal2013/rootfiles/run_rawMCP_01144.root");// Top MCP, Mask 3, Bias = -2300V
//	TFile *f1 = new TFile("~/shane/cal2013/rootfiles/run_rawMCP_01183.root");// Top MCP, Mask 2, Bias = -2500V
//	TFile *f1 = new TFile("~/shane/cal2013/rootfiles/run_rawMCP_01186.root");// Top MCP, Mask 2, Bias = -2550V
	f1->cd("mcp_cal");
	TH2I *hXY = (TH2I*)gDirectory->Get("h_R_mcp_map_2");
	TH1I *hX = (TH1I*)gDirectory->Get("h_R_mcpX_2");
	TH1I *hY = (TH1I*)gDirectory->Get("h_R_mcpY_2");
//	TH2I *hXY = (TH2I*)gDirectory->Get("h_T_mcp_map_2");
//	TH1I *hX = (TH1I*)gDirectory->Get("h_T_mcpX_2");
//	TH1I *hY = (TH1I*)gDirectory->Get("h_T_mcpY_2");
	
// ******************************************
	
	TCanvas *c1 = new TCanvas("c1","MCP Map",600,600);
	hXY->Draw("colz");
	
	Int_t X0 = 500;
	Int_t DX = 50;
	
	TCanvas *cX = new TCanvas("cX","MCP X-Coord",945,600);
	hX->Draw();
//	hXY->ProjectionX("_pX", X0-DX, X0+DX)->Draw("same");
//	hXY->ProjectionX("_pX", 20, 70)->Draw("same");
	
	Int_t Y0 = 500;
	Int_t DY = 50;
	
	TCanvas *cY = new TCanvas("cY","MCP Y-Coord",945,600);
	hY->Draw();
//	hXY->ProjectionY("_pY1", Y0-DY, Y0+DY)->Draw("same");
//	hXY->ProjectionY("_pY2", 30, 90)->Draw("same");
	
}
