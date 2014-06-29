void recoil_rates_on_mcp_region () {
	//gROOT->Reset();
	gROOT->ProcessLineSync(".L allMacros.c");
	gROOT->ProcessLineSync("Double_t x1[2] = {-0.05, 0.05}");
	gROOT->ProcessLineSync("Double_t x2[2] = {-0.15,-0.05}");
	gROOT->ProcessLineSync("Double_t x3[2] = { 0.05, 0.15}");
	gROOT->ProcessLineSync("Double_t y1[2] = {-0.7,  0.7 }");
	gROOT->ProcessLineSync("TH1I *h_tof_region1 = draw_tof_spectrum_of_mcp_region(x1,y1)");
	recoil_ion_rates_standalone(h_tof_region1);
	gROOT->ProcessLineSync("TH1I *h_tof_region2 = draw_tof_spectrum_of_mcp_region(x2,y1)");
	recoil_ion_rates_standalone(h_tof_region2);
	gROOT->ProcessLineSync("TH1I *h_tof_region3 = draw_tof_spectrum_of_mcp_region(x3,y1)");
	recoil_ion_rates_standalone(h_tof_region3);
	
// the recoil_ion_rates_standlone call must follow the draw_tof_spectrum_of_mco_region call
	
	TCanvas *c_dE_MCP_tof_sum_on_mcp_region = new TCanvas("c_dE_MCP_tof_sum_on_mcp_region","TOF Spectrum (All dE-MCP combos) on MCP regions",945,600);
    c_dE_MCP_tof_sum_on_mcp_region->SetLogy();
    
    h_tof_region1->Draw();
    h_tof_region2->Draw("SAME");
    h_tof_region3->Draw("SAME");
    h_tof_region2->SetLineColor(kRed);
    h_tof_region3->SetLineColor(kOrange);
    Int_t rebin = 100;
    h_tof_region1->Rebin(rebin);
    h_tof_region2->Rebin(rebin);
    h_tof_region3->Rebin(rebin);
    
	TLegend *leg_1 = new TLegend(0.78, 0.64, 0.98, 0.775);
	leg_1->AddEntry(h_tof_region1, "Gated on stripe");
	leg_1->AddEntry(h_tof_region2, "Left of stripe");
	leg_1->AddEntry(h_tof_region3, "Right of stripe");
	leg_1->SetFillColor(0);
	leg_1->Draw();
	
}
