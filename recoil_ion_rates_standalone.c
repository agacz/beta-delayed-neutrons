void rates_on_mcp_region () {
	gROOT->Reset();
	
	gROOT->ProcessLineSync(".L allMacros.c");
	gROOT->ProcessLineSync("TH1I *h_temp = draw_tof_spectrum_of_mcp_region()");
	recoil_ion_rates_standalone(h_temp);
}

void recoil_ion_rates_standalone(TH1I *h_tof_LT)
{
    
    printf("\nrecoil_ion_rates started.");
/*    
    Int_t tMax = 25000;
    Int_t tMin = -25000;
    Int_t tBins = tMax-tMin;
    
    const Double_t TOFMin	= -1000.0; // ns
	const Double_t TOFMax	= 25500.0; // ns
	const Int_t TOFBins		= 26500; // one bin per ns
*/	
    Int_t t_min = -1000;
	Int_t bdn_t_low = 2*(230-t_min)+1;	// bin # = 2*(tof-tof_min)+1
	Int_t bdn_t_high = 2*(1550-t_min)+1;
	Int_t beta_t_low = 2*(1551-t_min)+1;
	Int_t beta_t_high = 2*(10001-t_min)+1;
	Int_t bkgd_t_low = 2*(12000-t_min)+1;
	Int_t bkgd_t_high = 2*(20000-t_min)+1;
    
    Int_t bdn_t_range	= bdn_t_high - bdn_t_low;
	Int_t beta_t_range	= beta_t_high - beta_t_low;
	Int_t bkgd_t_range	= bkgd_t_high - bkgd_t_low;
    
    Double_t bkgd_per_ch_left_top		= h_tof_LT->Integral(bkgd_t_low,bkgd_t_high) / bkgd_t_range;
//	Double_t bkgd_per_ch_left_right		= h_tof_LR->Integral(bkgd_t_low,bkgd_t_high) / bkgd_t_range;
//	Double_t bkgd_per_ch_bottom_top		= h_tof_BT->Integral(bkgd_t_low,bkgd_t_high) / bkgd_t_range;
//	Double_t bkgd_per_ch_bottom_right	= h_tof_BR->Integral(bkgd_t_low,bkgd_t_high) / bkgd_t_range;
    
    Double_t bdn_area_left_top		= h_tof_LT->Integral(bdn_t_low,bdn_t_high) - bkgd_per_ch_left_top*bdn_t_range;
//	Double_t bdn_area_left_right	= h_tof_LR->Integral(bdn_t_low,bdn_t_high) - bkgd_per_ch_left_right*bdn_t_range;
//	Double_t bdn_area_bottom_top	= h_tof_BT->Integral(bdn_t_low,bdn_t_high) - bkgd_per_ch_bottom_top*bdn_t_range;
//	Double_t bdn_area_bottom_right	= h_tof_BR->Integral(bdn_t_low,bdn_t_high) - bkgd_per_ch_bottom_right*bdn_t_range;
	
	Double_t beta_area_left_top		= h_tof_LT->Integral(beta_t_low,beta_t_high) - bkgd_per_ch_left_top*beta_t_range;
//	Double_t beta_area_left_right	= h_tof_LR->Integral(beta_t_low,beta_t_high) - bkgd_per_ch_left_right*beta_t_range;
//	Double_t beta_area_bottom_top	= h_tof_BT->Integral(beta_t_low,beta_t_high) - bkgd_per_ch_bottom_top*beta_t_range;
//	Double_t beta_area_bottom_right	= h_tof_BR->Integral(beta_t_low,beta_t_high) - bkgd_per_ch_bottom_right*beta_t_range;
	
	Double_t bdn_area_tot = bdn_area_left_top;// + bdn_area_left_right + bdn_area_bottom_top + bdn_area_bottom_right;
	Double_t beta_area_tot = beta_area_left_top;// + beta_area_left_right + beta_area_bottom_top + beta_area_bottom_right;
    
    Int_t a = h_tof_LT->Integral(beta_t_low,beta_t_high);
//    Int_t b = h_tof_LR->Integral(beta_t_low,beta_t_high);
//    Int_t c = h_tof_BT->Integral(beta_t_low,beta_t_high);
//    Int_t d = h_tof_BR->Integral(beta_t_low,beta_t_high);
    
    Int_t e = h_tof_LT->Integral(bkgd_t_low,bkgd_t_high);
//    Int_t f = h_tof_LR->Integral(bkgd_t_low,bkgd_t_high);
//    Int_t g = h_tof_BT->Integral(bkgd_t_low,bkgd_t_high);
//    Int_t h = h_tof_BR->Integral(bkgd_t_low,bkgd_t_high);
    
    Int_t i = h_tof_LT->Integral(bdn_t_low,bdn_t_high);
//    Int_t j = h_tof_LR->Integral(bdn_t_low,bdn_t_high);
//    Int_t k = h_tof_BT->Integral(bdn_t_low,bdn_t_high);
//    Int_t l = h_tof_BR->Integral(bdn_t_low,bdn_t_high);
    
    cout << " " << endl << endl;
    
    cout << "Fast counts: " << i << "\tSlow counts: " << a << "\tBkgd counts: " << e << endl;
//    cout << "Fast LR counts: " << j << "\tSlow LR counts: " << b << "\tBkgd LR counts: " << f << endl;
//    cout << "Fast BT counts: " << k << "\tSlow BT counts: " << c << "\tBkgd BT counts: " << g << endl;
//    cout << "Fast BR counts: " << l << "\tSlow BR counts: " << d << "\tBkgd BR counts: " << h << endl;
    
    cout << " " << endl;
    
    cout << "Fast range: " << (bdn_t_low-1)/2.0+t_min << " to " << (bdn_t_high-1)/2.0+t_min << " ns ==> Delta = " << bdn_t_range/2.0 << " ns" << endl;
    cout << "Slow range: " << (beta_t_low-1)/2.0+t_min << " to " << (beta_t_high-1)/2.0+t_min << " ns ==> Delta = " << beta_t_range/2.0 << " ns" << endl;
    cout << "Bkgd range: " << (bkgd_t_low-1)/2.0+t_min << " to " << (bkgd_t_high-1)/2.0+t_min << " ns ==> Delta = " << bkgd_t_range/2.0 << " ns" << endl;
    
    cout << " " << endl;
    
    cout << "/********** RATES **********/ " << endl;
    
//    cout << endl << "Left dE - Top MCP:" << endl;
	cout << "Background per channel: " << bkgd_per_ch_left_top << endl;
	cout << "Delayed-neutron events: " << bdn_area_left_top << endl;
	cout << "Beta-only events      : " << beta_area_left_top << endl;
	
//	cout << endl << "Left dE - Right MCP:" << endl;
//	cout << "Background per channel: " << bkgd_per_ch_left_right << endl;
//	cout << "Delayed-neutron events: " << bdn_area_left_right << endl;
//	cout << "Beta-only events      : " << beta_area_left_right << endl;
    
//	cout << endl << "Bottom dE - Top MCP:" << endl;
//	cout << "Background per channel: " << bkgd_per_ch_bottom_top << endl;
//	cout << "Delayed-neutron events: " << bdn_area_bottom_top << endl;
//	cout << "Beta-only events      : " << beta_area_bottom_top << endl;
    
//	cout << endl << "Bottom dE - Right MCP:" << endl;
//	cout << "Background per channel: " << bkgd_per_ch_bottom_right << endl;
//	cout << "Delayed-neutron events: " << bdn_area_bottom_right << endl;
//	cout << "Beta-only events      : " << beta_area_bottom_right << endl;
	
	cout << endl << "TOTAL:" << endl;
	cout << "Delayed-neutron events: " << bdn_area_tot << endl;
	cout << "Beta-only events      : " << beta_area_tot << endl;
    
    printf("\nrecoil_ion_rates done.\n\n");
	
}
