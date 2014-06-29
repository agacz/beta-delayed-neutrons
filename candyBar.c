{
	gROOT->Reset();

	// include .c file with all the functions in it
    #include <allMacros.c>

    gStyle->SetScreenFactor(1);
    
    Float_t x1 = 0.0; // first column left edge
    Float_t x2 = 0.5; // first column right edge/2nd column left edge
    Float_t x3 = 1.0; // 2nd column right edge
    Float_t y1, y2;
    
    // definition of the bar: number of buttons
    const int numButtons = 16; // this is number of button rows.
    Float_t y1arr[numButtons];
    Float_t y2arr[numButtons];
    
    for (Int_t i=0; i<numButtons; i++){
        y1 = (float) i/numButtons;
        y2 = y1 + (1.0/numButtons);
        y1arr[i] = y1;
        y2arr[i] = y2;
    }
    
    TCanvas *menu = new TCanvas("menu", "menu", -1, 0, 450, 500);

    // buttons go in reverse order: first defined button is on the bottom, last defined button goes on top
    // first defined button needs to start with [pos], not [++pos]
    // to change position of the button, just change its position in the code
    
    Float_t textSize = 0.5;
    Int_t pos = 0;
    
    TButton *butSca = new TButton("ADC: MCP Maps", "adc_draw_both_mcp_maps();", x1, y1arr[pos], x2, y2arr[pos]);
    butSca->SetFillColor(kRed-2);
    butSca->SetFraming(1);
    butSca->SetTextSize(textSize);
    butSca->Draw();

    TButton *butSca = new TButton("ADC: MCP PHD's (All)", "adc_draw_all_mcp_phds();", x1, y1arr[++pos], x2, y2arr[pos]);
    butSca->SetFillColor(kRed+2);
    butSca->SetFraming(1);
    butSca->SetTextSize(textSize);
    butSca->Draw();
    
    TButton *butSca = new TButton("ADC: MCP Sum PHD's", "adc_draw_both_mcp_sum_phds();", x1, y1arr[++pos], x2, y2arr[pos]);
    butSca->SetFillColor(kRed+1);
    butSca->SetFraming(1);
    butSca->SetTextSize(textSize);
    butSca->Draw();
    
    TButton *butSca = new TButton("ADC: MCP R PHD's Near 0", "adc_draw_R_mcp_post_phds_near_zero();", x1, y1arr[++pos], x2, y2arr[pos]);
    butSca->SetFillColor(kRed-3);
    butSca->SetFraming(1);
    butSca->SetTextSize(textSize);
    butSca->Draw();

    TButton *butSca = new TButton("ADC: MCP T PHD's Near 0", "adc_draw_T_mcp_post_phds_near_zero();", x1, y1arr[++pos], x2, y2arr[pos]);
    butSca->SetFillColor(kRed-7);
    butSca->SetFraming(1);
    butSca->SetTextSize(textSize);
    butSca->Draw();
    
    TButton *butSca = new TButton("ADC: MCP R PHD's", "adc_draw_R_mcp_post_phds();", x1, y1arr[++pos], x2, y2arr[pos]);
    butSca->SetFillColor(kRed-4);
    butSca->SetFraming(1);
    butSca->SetTextSize(textSize);
    butSca->Draw();
    
    TButton *butSca = new TButton("ADC: MCP T PHD's", "adc_draw_T_mcp_post_phds();", x1, y1arr[++pos], x2, y2arr[pos]);
    butSca->SetFillColor(kRed);
    butSca->SetFraming(1);
    butSca->SetTextSize(textSize);
    butSca->Draw();
    
    TButton *butSca = new TButton("ADC: Plastic Coinc plots", "adc_draw_plastic_coinc_plots();", x1, y1arr[++pos], x2, y2arr[pos]);
    butSca->SetFillColor(kAzure-3);
    butSca->SetFraming(1);
    butSca->SetTextSize(textSize);
    butSca->Draw();
    
    TButton *butSca = new TButton("ADC: Plastic Singles", "adc_draw_all_plastic_singles();", x1, y1arr[++pos], x2, y2arr[pos]);
    butSca->SetFillColor(kAzure+7);
    butSca->SetFraming(1);
    butSca->SetTextSize(textSize);
    butSca->Draw();
    
    TButton *butSca = new TButton("ADC: HPGe Singles", "adc_draw_all_hpge_singles();", x1, y1arr[++pos], x2, y2arr[pos]);
    butSca->SetFillColor(kYellow-7);
    butSca->SetFraming(1);
    butSca->SetTextSize(textSize);
    butSca->Draw();
/*    
    TButton *butSca = new TButton("MCP Gated PHDs", "gated_mcp_phd();", x1, y1arr[++pos], x2, y2arr[pos]);
    butSca->SetFillColor(kViolet);
    butSca->SetFraming(1);
    butSca->SetTextSize(textSize);
    butSca->SetTextColor(10);
    butSca->Draw();
*/    
    TButton *butSca = new TButton("Slow Recoils vs Cycle Time", "draw_slow_recoils_vs_cycle_time();", x1, y1arr[++pos], x2, y2arr[pos]);
    butSca->SetFillColor(kViolet-1);
    butSca->SetFraming(1);
    butSca->SetTextSize(textSize);
    butSca->SetTextColor(10);
    butSca->Draw();
    
    TButton *butSca = new TButton("Betas vs Cycle Time", "draw_betas_vs_cycle_time();", x1, y1arr[++pos], x2, y2arr[pos]);
    butSca->SetFillColor(kViolet-6);
    butSca->SetFraming(1);
    butSca->SetTextSize(textSize);
    butSca->SetTextColor(10);
    butSca->Draw();
    
    TButton *butSca = new TButton("ADC: Beta-Gamma Ge", "adc_draw_all_hpge_betas();", x1, y1arr[++pos], x2, y2arr[pos]);
    butSca->SetFillColor(kGreen-3);
    butSca->SetFraming(1);
    butSca->SetTextSize(textSize);
    butSca->Draw();
    
    // TDC
    
    pos=0;
    
    TButton *butSca = new TButton("TDC: MCP Singles"	,"tdc_draw_all_mcp_singles();", x2, y1arr[pos], x3, y2arr[pos]);
    butSca->SetFillColor(kRed-5);
    butSca->SetFraming(1);
    butSca->SetTextSize(textSize);
    butSca->Draw();
    
    TButton *butSca = new TButton("TDC: MCP Singles Near 0"	,"tdc_draw_all_mcp_singles_near_zero();", x2, y1arr[++pos], x3, y2arr[pos]);
    butSca->SetFillColor(kRed-8);
    butSca->SetFraming(1);
    butSca->SetTextSize(textSize);
    butSca->Draw();
    
    TButton *butSca = new TButton("TDC: TOF Spectra (dE-MCP)"		,"tdc_draw_dE_mcp_tof_spectra();", x2, y1arr[++pos], x3, y2arr[pos]);
    butSca->SetFillColor(kRed-10);
    butSca->SetFraming(1);
    butSca->SetTextSize(textSize);
    butSca->Draw();
    
    TButton *butSca = new TButton("TDC: TOF Spectra (dE-MCP BACKGROUND)"	,"tdc_draw_background_dE_mcp_tof_spectra();", x2, y1arr[++pos], x3, y2arr[pos]);
    butSca->SetFillColor(kRed-9);
    butSca->SetFraming(1);
    butSca->SetTextSize(textSize);
    butSca->Draw();
    
    TButton *butSca = new TButton("TDC: Plastic Singles", "tdc_draw_all_plastic_singles();", x2, y1arr[++pos], x3, y2arr[pos]);
    butSca->SetFillColor(kCyan+3);
    butSca->SetFraming(1);
    butSca->SetTextSize(textSize);
    butSca->Draw();
    
    TButton *butSca = new TButton("TDC: Plastic Singles Rebinned", "tdc_draw_all_plastic_singles_rebinned();", x2, y1arr[++pos], x3, y2arr[pos]);
    butSca->SetFillColor(kCyan-1);
    butSca->SetFraming(1);
    butSca->SetTextSize(textSize);
    butSca->Draw();
    
    TButton *butSca = new TButton("TDC: Plastic Singles Near 0", "tdc_draw_all_plastic_singles_near_zero();", x2, y1arr[++pos], x3, y2arr[pos]);
    butSca->SetFillColor(kCyan-5);
    butSca->SetFraming(1);
    butSca->SetTextSize(textSize);
    butSca->Draw();
    
    TButton *butSca = new TButton("TDC: Plastic dE-E TOF"		,"tdc_draw_dE_E_tof_spectra();", x2, y1arr[++pos], x3, y2arr[pos]);
    butSca->SetFillColor(kCyan-6);
    butSca->SetFraming(1);
    butSca->SetTextSize(textSize);
    butSca->Draw();
    
    TButton *butSca = new TButton("TDC: Plastic Coinc plots"		,"tdc_draw_plastic_coinc_plots();", x2, y1arr[++pos], x3, y2arr[pos]);
    butSca->SetFillColor(kCyan-8);
    butSca->SetFraming(1);
    butSca->SetTextSize(textSize);
    butSca->Draw();
    
    TButton *butSca = new TButton("TDC: Plastic Diffs"		,"tdc_draw_plastic_diffs();", x2, y1arr[++pos], x3, y2arr[pos]);
    butSca->SetFillColor(kCyan-3);
    butSca->SetFraming(1);
    butSca->SetTextSize(textSize);
    butSca->Draw();
    
    TButton *butSca = new TButton("TDC: Ge singles","tdc_ge();", x2, y1arr[++pos], x3, y2arr[pos]);
    butSca->SetFillColor(kYellow-3);
    butSca->SetFraming(1);
    butSca->SetTextSize(textSize);
    butSca->Draw();
    
    TButton *butSca = new TButton("TDC: MCP-Ge diff", "tdc_draw_ge_mcp_tof_spectra();", x2, y1arr[++pos], x3, y2arr[pos]);
    butSca->SetFillColor(kOrange);
    butSca->SetFraming(1);
    butSca->SetTextSize(textSize);
    butSca->Draw();
    
    TButton *butSca = new TButton("TDC: Ge-dE diff", "tdc_draw_dE_Ge_tof_spectra();", x2, y1arr[++pos], x3, y2arr[pos]);
    butSca->SetFillColor(kGreen-2);
    butSca->SetFraming(1);
    butSca->SetTextSize(textSize);
    butSca->Draw();
    
    TButton *butSca = new TButton("Recoil ion rates", "recoil_ion_rates();", x2, y1arr[++pos], x3, y2arr[pos]);
    butSca->SetFillColor(kGreen-2);
    butSca->SetFraming(1);
    butSca->SetTextSize(textSize);
    butSca->Draw();
    
    TButton *butSca = new TButton("Slow ion PHD's", "draw_slow_recoil_phds();", x2, y1arr[++pos], x3, y2arr[pos]);
    butSca->SetFillColor(kGreen-2);
    butSca->SetFraming(1);
    butSca->SetTextSize(textSize);
    butSca->Draw();
    
    TButton *butSca = new TButton("Fast ion PHD's", "draw_fast_recoil_phds();", x2, y1arr[++pos], x3, y2arr[pos]);
    butSca->SetFillColor(kGreen-2);
    butSca->SetFraming(1);
    butSca->SetTextSize(textSize);
    butSca->Draw();
    
    gROOT->SaveContext();
    
}
