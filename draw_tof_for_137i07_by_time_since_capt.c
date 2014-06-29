{
	
	Int_t rebin = 100;
	
// Draw 90deg spectra
	TCanvas *c_tof_by_time_since_capt_90deg = new TCanvas("c_tof_by_time_since_capt_90deg","TOF Spectrum (90-degree combos) by time since capture",945,600);
    h_tof_90deg_1st_3s_after_capt->Rebin(rebin);
    h_tof_90deg_2nd_3s_after_capt->Rebin(rebin);
    h_tof_90deg_1st_minus_2nd->Rebin(rebin);
    h_tof_90deg_1st_minus_2nd->Draw("E");
    h_tof_90deg_1st_3s_after_capt->Draw("HSAME");
    h_tof_90deg_2nd_3s_after_capt->Draw("HSAME");
    
    h_tof_90deg_1st_3s_after_capt->SetLineColor(kRed);
    h_tof_90deg_1st_minus_2nd->SetLineColor(kBlack);
    
    TLegend *leg_1 = new TLegend(0.78, 0.64, 0.98, 0.775);
	leg_1->AddEntry(h_tof_90deg_1st_3s_after_capt,"0-3 sec");
	leg_1->AddEntry(h_tof_90deg_2nd_3s_after_capt,"3-6 sec");
	leg_1->AddEntry(h_tof_90deg_1st_minus_2nd,"0-3s minus 3-6s");
	leg_1->SetFillColor(0);
	leg_1->Draw();
	
// Draw 180deg spectra
	TCanvas *c_tof_by_time_since_capt_180deg = new TCanvas("c_tof_by_time_since_capt_180deg","TOF Spectrum (180-degree combos) by time since capture",945,600);
    h_tof_180deg_1st_3s_after_capt->Rebin(rebin);
    h_tof_180deg_2nd_3s_after_capt->Rebin(rebin);
    h_tof_180deg_1st_minus_2nd->Rebin(rebin);
    h_tof_180deg_1st_minus_2nd->Draw("E");
    h_tof_180deg_1st_3s_after_capt->Draw("HSAME");
    h_tof_180deg_2nd_3s_after_capt->Draw("HSAME");
    
    h_tof_180deg_1st_3s_after_capt->SetLineColor(kRed);
    h_tof_180deg_1st_minus_2nd->SetLineColor(kBlack);
    
//	TLegend *leg_1 = new TLegend(0.78, 0.64, 0.98, 0.775);
//	leg_1->AddEntry(h_tof_180deg_1st_3s_after_capt,"0-3 sec");
//	leg_1->AddEntry(h_tof_180deg_2nd_3s_after_capt,"3-6 sec");
//	leg_1->AddEntry(h_tof_180deg_1st_minus_2nd,"0-3s minus 3-6s");
//	leg_1->SetFillColor(0);
	leg_1->Draw();
	
	printf("\ndraw_tof_for_137i07_by_time_since_capt done.\n\n");

}
