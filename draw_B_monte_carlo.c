{
	TFile *tfile = new TFile("B_monte_carlo_feeding.root");
	
	Int_t rebin = 1;
	Int_t rebin_realtime = 1;
	
	h_A_realtime->SetLineColor(kBlack);
	h_D_realtime->SetLineColor(kBlack);
	h_D_cyctime ->SetLineColor(kBlack);
	
	h_T1_realtime->SetLineColor(kGreen);
	h_U1_realtime->SetLineColor(kGreen);
	h_DT1_realtime->SetLineColor(kGreen);
	h_DU1_realtime->SetLineColor(kGreen);
	h_DT1_cyctime ->SetLineColor(kGreen);
	h_DU1_cyctime ->SetLineColor(kGreen);
	
	h_T2_realtime->SetLineColor(kBlue);
	h_U2_realtime->SetLineColor(kBlue);
	h_DT2_realtime->SetLineColor(kBlue);
	h_DU2_realtime->SetLineColor(kBlue);
	h_DT2_cyctime ->SetLineColor(kBlue);
	h_DU2_cyctime ->SetLineColor(kBlue);
	
	h_T3_realtime->SetLineColor(kRed);
	h_U3_realtime->SetLineColor(kRed);
	h_DT3_realtime->SetLineColor(kRed);
	h_DU3_realtime->SetLineColor(kRed);
	h_DT3_cyctime ->SetLineColor(kRed);
	h_DU3_cyctime ->SetLineColor(kRed);
	
	h_U1_realtime->SetLineStyle(7);
	h_U2_realtime->SetLineStyle(7);
	h_U3_realtime->SetLineStyle(7);
	h_DU1_realtime->SetLineStyle(7);
	h_DU2_realtime->SetLineStyle(7);
	h_DU3_realtime->SetLineStyle(7);
	h_DU1_cyctime->SetLineStyle(7);
	h_DU2_cyctime->SetLineStyle(7);
	h_DU3_cyctime->SetLineStyle(7);
	
	h_D_realtime ->Rebin(rebin_realtime);
	h_DT1_realtime ->Rebin(rebin_realtime);
	h_DT2_realtime ->Rebin(rebin_realtime);
	h_DT3_realtime ->Rebin(rebin_realtime);
	h_DU1_realtime ->Rebin(rebin_realtime);
	h_DU2_realtime ->Rebin(rebin_realtime);
	h_DU3_realtime ->Rebin(rebin_realtime);
	
	h_D_cyctime ->Rebin(rebin);
	h_DT1_cyctime ->Rebin(rebin);
	h_DT2_cyctime ->Rebin(rebin);
	h_DT3_cyctime ->Rebin(rebin);
	h_DU1_cyctime ->Rebin(rebin);
	h_DU2_cyctime ->Rebin(rebin);
	h_DU3_cyctime ->Rebin(rebin);
/*	
	TCanvas *c_pops_realtime = new TCanvas("c_pops_realtime","Ion populations versus real time",945,600);
	h_A_realtime->Draw();
	h_T1_realtime->Draw("SAME");
	h_T2_realtime->Draw("SAME");
	h_T3_realtime->Draw("SAME");
	h_U1_realtime->Draw("SAME");
	h_U2_realtime->Draw("SAME");
	h_U3_realtime->Draw("SAME");
	
	TCanvas *c_decays_realtime = new TCanvas("c_decays_realtime","Decays versus cycle time",945,600);
	h_D_realtime->Draw();
	h_DT1_realtime->Draw("SAME");
	h_DT2_realtime->Draw("SAME");
	h_DT3_realtime->Draw("SAME");
	h_DU1_realtime->Draw("SAME");
	h_DU2_realtime->Draw("SAME");
	h_DU3_realtime->Draw("SAME");
*/	
	TCanvas *c_decays_cyctime = new TCanvas("c_decays_cyctime","Decays versus cycle time",945,600);
	h_D_cyctime->Draw();
	h_DT1_cyctime->Draw("SAME");
	h_DT2_cyctime->Draw("SAME");
	h_DT3_cyctime->Draw("SAME");
	h_DU1_cyctime->Draw("SAME");
	h_DU2_cyctime->Draw("SAME");
	h_DU3_cyctime->Draw("SAME");
	
// X and Y pops	
	h_DX2_cyctime ->Rebin(rebin);
	h_DX3_cyctime ->Rebin(rebin);
	h_DY2_cyctime ->Rebin(rebin);
	h_DY3_cyctime ->Rebin(rebin);
	
	h_DX2_cyctime->SetLineStyle(8);
	h_DY2_cyctime->SetLineStyle(3);
	h_DX2_cyctime->SetLineColor(kBlue);
	h_DY2_cyctime->SetLineColor(kBlue);
	h_DX3_cyctime->SetLineStyle(8);
	h_DY3_cyctime->SetLineStyle(3);
	h_DX3_cyctime->SetLineColor(kRed);
	h_DY3_cyctime->SetLineColor(kRed);
	
	TH1D *h_DU2_cyctime_1	= (TH1D*)h_DU2_cyctime->Rebin(rebin,"h_DU2_cyctime_1");
	TH1D *h_DU3_cyctime_1	= (TH1D*)h_DU3_cyctime->Rebin(rebin,"h_DU3_cyctime_1");
	
	h_DU2_cyctime->SetLineStyle(7);
	h_DU3_cyctime->SetLineStyle(7);
	h_DU2_cyctime->SetLineColor(kBlue);
	h_DU3_cyctime->SetLineColor(kRed);
	
	TCanvas *c_feeding_cyctime = new TCanvas("c_feeding_cyctime","Decays from pops X and Y versus cycle time",945,600);
	h_DU3_cyctime_1->Draw();
	h_DX3_cyctime->Draw("SAME");
	h_DY3_cyctime->Draw("SAME");
	h_DU2_cyctime_1->Draw("SAME");
	h_DX2_cyctime->Draw("SAME");
	h_DY2_cyctime->Draw("SAME");
	

}
