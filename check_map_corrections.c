void check_map_corrections() {
	
	gROOT->Reset();
	gStyle->SetOptStat("e");
	
	Int_t use_alt = 0;
	Int_t use_cal = 0;
	
	if (use_alt == 0) {
		TFile *f1 = new TFile("~/shane/134sb/rootfiles/134sb03.root");
		TH2I *hR = (TH2I*)gDirectory->Get("h_R_mcpMap");
		TH2I *hT = (TH2I*)gDirectory->Get("h_T_mcpMap");
//		TH2I *hR = (TH2I*)gDirectory->Get("h_bkgd_R_mcpMap");
//		TH2I *hT = (TH2I*)gDirectory->Get("h_bkgd_T_mcpMap");
	}
	else {
		TFile *f1 = new TFile("~/shane/134sb/rootfiles/134sb03_alt/134sb03_alt.root");
		if (use_cal == 0) {
//			TH2I *hR = (TH2I*)gDirectory->Get("h_R_mcpMap_post200");
//			TH2I *hT = (TH2I*)gDirectory->Get("h_T_mcpMap_post200");
			TH2I *hR = (TH2I*)gDirectory->Get("h_bkgd_R_mcpMap_post200");
			TH2I *hT = (TH2I*)gDirectory->Get("h_bkgd_T_mcpMap_post200");
		}
		else {
			f1->cd("mcp_cal");
			TH2I *hR = (TH2I*)gDirectory->Get("h_R_mcp_map_1");
			TH2I *hT = (TH2I*)gDirectory->Get("h_T_mcp_map_1");
			
			TCanvas *c1 = new TCanvas("c1","Missing Posts",945,600);
			TH1I *hR_miss = (TH1I*)gDirectory->Get("hn_missing_R_mcp");
			TH1I *hT_miss = (TH1I*)gDirectory->Get("hn_missing_T_mcp");
			hR_miss->Draw();
			hT_miss->Draw("same");
			hT_miss->SetLineColor(kRed);
			printf("Top MCP # of 4-post events: %10f \n", hT_miss->GetBinContent(1));
			printf("Rgt MCP # of 4-post events: %10f \n\n", hR_miss->GetBinContent(1));
			
			TCanvas *cRecon = new TCanvas("cRecon","Reconstructed map",945,500);
			TH2I *hR_recon = (TH2I*)gDirectory->Get("h_R_mcp_map_reconstructed_1");
			TH2I *hT_recon = (TH2I*)gDirectory->Get("h_T_mcp_map_reconstructed_1");
			cRecon->Divide(2,1);
			cRecon->cd(1);
			hT_recon->Draw("colz");
			cRecon->cd(2);
			hR_recon->Draw("colz");
		}
	}
	
// ******************************************
	
//	TCanvas *c2 = new TCanvas("c2","MCP Maps",945,500);
//	c2->Divide(2,1);
//	c2->cd(1);
//	hT->Draw("colz");
//	c2->cd(2);
//	hR->Draw("colz");
	
	TFile *f_old = new TFile("~/shane/134sb/rootfiles/134sb03_alt/134sb03_alt.root");
//	TFile *f_old = new TFile("~/shane/137i/rootfiles/137i07_alt/137i07_alt.root");
	TH1F *h_old = (TH1F*)gDirectory->Get("h_tof");
	TH1F *h_LT_old = (TH1F*)gDirectory->Get("h_tof_LT");
    TH1F *h_LR_old = (TH1F*)gDirectory->Get("h_tof_LR");
    TH1F *h_BT_old = (TH1F*)gDirectory->Get("h_tof_BT");
    TH1F *h_BR_old = (TH1F*)gDirectory->Get("h_tof_BR");
//	TH1F *h_old = (TH1F*)gDirectory->Get("h_bkgd_tof");
	TFile *f_new = new TFile("~/shane/134sb/rootfiles/134sb03.root");
//	TFile *f_new = new TFile("~/shane/137i/rootfiles/137i07.root");
	TH1F *h_new = (TH1F*)gDirectory->Get("h_tof");
	TH1F *h_LT_new = (TH1F*)gDirectory->Get("h_tof_LT");
    TH1F *h_LR_new = (TH1F*)gDirectory->Get("h_tof_LR");
    TH1F *h_BT_new = (TH1F*)gDirectory->Get("h_tof_BT");
    TH1F *h_BR_new = (TH1F*)gDirectory->Get("h_tof_BR");
//	TH1F *h_new = (TH1F*)gDirectory->Get("h_bkgd_tof");
	
	Int_t t_min = -1000;
	Int_t bdn_t_low  = 2*(230-t_min)  +1;	// bin # = 2*(tof-tof_min)+1
	Int_t bdn_t_high = 2*(1550-t_min) +1;
	Int_t bkgd_t_low = 2*(12000-t_min)+1;
	Int_t bkgd_t_high = 2*(20000-t_min)+1;
	
	Int_t bdn_t_range	= bdn_t_high  - bdn_t_low;
	Int_t bkgd_t_range	= bkgd_t_high - bkgd_t_low;
    
    Double_t bkgd_LT_new	= h_LT_new->Integral(bkgd_t_low,bkgd_t_high) / bkgd_t_range;
	Double_t bkgd_LR_new	= h_LR_new->Integral(bkgd_t_low,bkgd_t_high) / bkgd_t_range;
	Double_t bkgd_BT_new	= h_BT_new->Integral(bkgd_t_low,bkgd_t_high) / bkgd_t_range;
	Double_t bkgd_BR_new	= h_BR_new->Integral(bkgd_t_low,bkgd_t_high) / bkgd_t_range;
    
    Double_t bdn_area_LT_new	= h_LT_new->Integral(bdn_t_low,bdn_t_high) - bkgd_LT_new*bdn_t_range;
	Double_t bdn_area_LR_new	= h_LR_new->Integral(bdn_t_low,bdn_t_high) - bkgd_LR_new*bdn_t_range;
	Double_t bdn_area_BT_new	= h_BT_new->Integral(bdn_t_low,bdn_t_high) - bkgd_BT_new*bdn_t_range;
	Double_t bdn_area_BR_new	= h_BR_new->Integral(bdn_t_low,bdn_t_high) - bkgd_BR_new*bdn_t_range;
	
	Double_t bkgd_LT_old	= h_LT_old->Integral(bkgd_t_low,bkgd_t_high) / bkgd_t_range;
	Double_t bkgd_LR_old	= h_LR_old->Integral(bkgd_t_low,bkgd_t_high) / bkgd_t_range;
	Double_t bkgd_BT_old	= h_BT_old->Integral(bkgd_t_low,bkgd_t_high) / bkgd_t_range;
	Double_t bkgd_BR_old	= h_BR_old->Integral(bkgd_t_low,bkgd_t_high) / bkgd_t_range;
    
    Double_t bdn_area_LT_old	= h_LT_old->Integral(bdn_t_low,bdn_t_high) - bkgd_LT_old*bdn_t_range;
	Double_t bdn_area_LR_old	= h_LR_old->Integral(bdn_t_low,bdn_t_high) - bkgd_LR_old*bdn_t_range;
	Double_t bdn_area_BT_old	= h_BT_old->Integral(bdn_t_low,bdn_t_high) - bkgd_BT_old*bdn_t_range;
	Double_t bdn_area_BR_old	= h_BR_old->Integral(bdn_t_low,bdn_t_high) - bkgd_BR_old*bdn_t_range;
	
	printf("\nOld TOF counts = %d; New TOF counts = %d\n",h_old->GetEntries(),h_new->GetEntries());
	printf("\nOld TOF counts LT = %f; New TOF counts LT = %f, New/Old = %f\n", bdn_area_LT_old, bdn_area_LT_new, bdn_area_LT_new/bdn_area_LT_old);
	printf("\nOld TOF counts LR = %f; New TOF counts LR = %f, New/Old = %f\n", bdn_area_LR_old, bdn_area_LR_new, bdn_area_LR_new/bdn_area_LR_old);
	printf("\nOld TOF counts BT = %f; New TOF counts BT = %f, New/Old = %f\n", bdn_area_BT_old, bdn_area_BT_new, bdn_area_BT_new/bdn_area_BT_old);
	printf("\nOld TOF counts BR = %f; New TOF counts BR = %f, New/Old = %f\n", bdn_area_BR_old, bdn_area_BR_new, bdn_area_BR_new/bdn_area_BR_old);
//	printf("Old TOF counts (fast only) = %d; New TOF counts (fast only) = %d\n\n",h_old->Integral(2*(230+1000)+1, 2*(1550+1000)+1),h_new->Integral(2*(230+1000)+1, 2*(1550+1000)+1));
	printf("\n");
	
	TCanvas *cTOF = new TCanvas("cTOF","TOF Spectra",945,600);
	cTOF->SetLogy();
	Int_t rebin = 500;
	h_new->Rebin(rebin);
	h_LT_new->Rebin(rebin);
	h_LR_new->Rebin(rebin);
	h_BT_new->Rebin(rebin);
	h_BR_new->Rebin(rebin);
	h_old->Rebin(rebin);
	h_LT_old->Rebin(rebin);
	h_LR_old->Rebin(rebin);
	h_BT_old->Rebin(rebin);
	h_BR_old->Rebin(rebin);
//	h_new->Draw();
	h_old->Draw();//"same");
	h_new->Draw("same");
	h_old->SetLineColor(kRed);
	
	TCanvas *cComp = new TCanvas("cComp","Ratio of event rates, with and without MCP Map cut: (with cut)/(without cut)",945,600);
	TH1F *h_ratio = new TH1F("h_ratio","Ratio of event rates, with and without MCP Map cut: (with cut)/(without cut)",2.0*26500,-1000,25500);
	Float_t y1, y2, v1, v2;
	h_ratio->Rebin(rebin);
	Int_t nBins = 2.0*26500/rebin;
	Int_t idx1  = 2000/rebin;
	
	for (Int_t idx = idx1; idx <= nBins; idx++) {
		y1 = (Float_t)h_old->GetBinContent(idx);
//		y1 = (Float_t)h_LT_old->GetBinContent(idx);
		v1 = TMath::Sqrt(y1);
		y2 = (Float_t)h_new->GetBinContent(idx);
//		y2 = (Float_t)h_LT_new->GetBinContent(idx);
		v2 = TMath::Sqrt(y2);
//		printf("i = %d; x = %f; old (%f,%f); new (%f,%f)\n", idx, rebin*idx/2.0-1000, y1, v1, y2, v2);
		if (y1 <= 1) {
			h_ratio->SetBinContent(idx, 1.0);
			h_ratio->SetBinError(idx, 2.0);
		}
		else {
			h_ratio->SetBinContent(idx, y2/y1);
			h_ratio->SetBinError(idx, (y2/y1)*TMath::Sqrt((v1*v1)/(y1*y1)+(v2*v2)/(y2*y2)));
		}
	}
//	h_ratio->Divide(h_new,h_old,1.0,1.0);
	h_ratio->Draw();
	
//	Float_t xMin = 230;
//	Float_t xMax = 1800;
	Float_t xMin = 1800;
	Float_t xMax = 10000;
//	Float_t xMin = 12000;
//	Float_t xMax = 20000;
	TF1 *c0 = new TF1("c0","[0]",xMin,xMax);
	c0->SetParameter(0, 0.836);
	h_ratio->Fit(c0,"R");
//	c0->Draw("same");
	
//	printf("h_old has %d bins, h_new has %d bins, h_ratio has %d bins.\n", h_old->GetNbinsX(), h_new->GetNbinsX(), h_ratio->GetNbinsX());
}
