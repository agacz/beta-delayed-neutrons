#include <stdlib>
#include <string>
#include <iostream>
#include <fstream>
#include <cstring>
#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <TLeaf.h>
#include <TH1.h>
#include <TH2.h>
#include "bdn.h"
#include "bdn_histograms.h"
#include "TFitResult.h"
//#include "CSVtoStruct.h"

char *filename = "bdn.root";
void GetGraphXY (char*, Int_t, Double_t[], Double_t[]);

//Int_t t_trigger_lo = -100;
//Int_t t_trigger_hi = 0;
//Int_t a_dE_lo = 100;
//Int_t t_trigger_lo = -100;
//Int_t a_mcp_lo = 200;

void adc_draw_all_hpge_singles(){
    
    printf("\nadc_draw_all_hpge_singles started.");
	
    TFile *tfile		= new TFile(filename);
    
    TCanvas * c_hpge_singles = new TCanvas("c_hpge_singles", "All HPGe singles", 1200, 800);
    
    Float_t RGe_a = 0.8471;
    Float_t RGe_b = -10.674;
    
    c_hpge_singles->Divide(2,2);
    
    c_hpge_singles->cd(1);
    c_hpge_singles_1->SetLogy();
    ha_T_ge->Draw();
    
    c_hpge_singles->cd(2);
    c_hpge_singles_2->SetLogy();
    ha_T_ge_highE->Draw();
    
    //TAxis *axisR = (TAxis*)ha_R_ge->GetXaxis();
    //axisR->SetLimits(axisR->GetXmin()*RGe_a+RGe_b, axisR->GetXmax()*RGe_a+RGe_b);
    
    c_hpge_singles->cd(3);
    c_hpge_singles_3->SetLogy();
    ha_R_ge->Draw();
    
    c_hpge_singles->cd(4);
    c_hpge_singles_4->SetLogy();
    ha_R_ge_highE->Draw();
    
    printf("\nadc_draw_all_hpge_singles done.\n\n");

}

void adc_draw_all_hpge_betas(){
    
    printf("\nadc_draw_all_hpge_betas started.");
	
    TFile *tfile		= new TFile(filename);
    
    TCanvas * c_hpge_betas = new TCanvas("c_hpge_betas", "All HPGe-Beta Coincidences", 1200, 800);
    
    TCut cut_B_dEa	= "-100<t_B_dEa";
	TCut cut_B_dEb	= "-100<t_B_dEb";
	TCut cut_B_dE = cut_B_dEa && cut_B_dEb;
	
	TCut cut_L_dEa	= "-100<t_L_dEa";
	TCut cut_L_dEb	= "-100<t_L_dEb";
	TCut cut_L_dE = cut_L_dEa && cut_L_dEb;	
	
	Float_t RGe_a = 0.8471;
    Float_t RGe_b = -10.674;
	
	TCut cut_ge_RL1 = "0<(t_R_ge - t_L_dE)";
	TCut cut_ge_RL2 = "(t_R_ge - t_L_dE)<500";
	TCut cut_ge_RL = cut_ge_RL1 && cut_ge_RL2;
	
	TCut cut_ge_RB1 = "0<(t_R_ge - t_B_dE)";
	TCut cut_ge_RB2 = "(t_R_ge - t_B_dE)<500";
	TCut cut_ge_RB = cut_ge_RB1 && cut_ge_RB2;

	TCut cut_ge_TL1 = "0<(t_T_ge - t_L_dE)";
	TCut cut_ge_TL2 = "(t_T_ge - t_L_dE)<500";
	TCut cut_ge_TL = cut_ge_TL1 && cut_ge_TL2;
	
	TCut cut_ge_TB1 = "0<(t_T_ge - t_B_dE)";
	TCut cut_ge_TB2 = "(t_T_ge - t_B_dE)<500";
	TCut cut_ge_TB = cut_ge_TB1 && cut_ge_TB2;
    
    c_hpge_betas->Divide(2,2);
    
    c_hpge_betas->cd(1);
    c_hpge_betas_1->SetLogy();
    bdn_Tree->Draw("a_R_ge>>GeRB(4000,0,4000)", cut_ge_RB);
    TAxis *axisR = (TAxis*)GeRB->GetXaxis();
    axisR->SetLimits(axisR->GetXmin()*RGe_a+RGe_b, axisR->GetXmax()*RGe_a+RGe_b);
    
    c_hpge_betas->cd(2);
    c_hpge_betas_2->SetLogy();
    bdn_Tree->Draw("a_R_ge>>GeRL(4000,0,4000)", cut_ge_RL);
    TAxis *axisRL = (TAxis*)GeRL->GetXaxis();
    axisRL->SetLimits(axisRL->GetXmin()*RGe_a+RGe_b, axisRL->GetXmax()*RGe_a+RGe_b);
    
    c_hpge_betas->cd(3);
    c_hpge_betas_3->SetLogy();
	bdn_Tree->Draw("a_T_ge>>GeTB(4000,0,4000)", cut_ge_TB);
    
    c_hpge_betas->cd(4);
    c_hpge_betas_4->SetLogy();
    bdn_Tree->Draw("a_T_ge>>GeTL(4000,0,4000)", cut_ge_TL);
    
    printf("\nadc_draw_all_hpge_betas done.\n\n");

}

void adc_draw_all_plastic_singles()
{
    
    printf("\nadc_draw_all_plastic_singles started.");

    TFile *tfile		= new TFile(filename);
    
    TCanvas * c_all_plastic_singles = new TCanvas("c_all_plastic_singles", "All plastic singles", 1024, 1024);
    
    c_all_plastic_singles->Divide(2,4);
    
    c_all_plastic_singles->cd(1);
    c_all_plastic_singles_1->SetLogy();
    ha_L_dEa->Draw();
    
    c_all_plastic_singles->cd(2);
    c_all_plastic_singles_2->SetLogy();
    ha_B_dEa->Draw();
    
    c_all_plastic_singles->cd(3);
    c_all_plastic_singles_3->SetLogy();
    ha_L_dEb->Draw();
    
	c_all_plastic_singles->cd(4);
    c_all_plastic_singles_4->SetLogy();
    ha_B_dEb->Draw();
    
    c_all_plastic_singles->cd(5);
    c_all_plastic_singles_5->SetLogy();
    ha_L_dEsum->Draw();
    
	c_all_plastic_singles->cd(6);
    c_all_plastic_singles_6->SetLogy();
    ha_B_dEsum->Draw();
    
    c_all_plastic_singles->cd(7);
    c_all_plastic_singles_7->SetLogy();
    ha_L_E->Draw();
    
	c_all_plastic_singles->cd(8);
    c_all_plastic_singles_8->SetLogy();
    ha_B_E->Draw();
    
    printf("\nadc_draw_all_plastic_singles done.\n\n");
    
}

void adc_draw_T_mcp_post_phds()
{
	
	printf("\ndraw_T_mcp_posts started.");

    TFile *tfile		= new TFile(filename);
    
    TCanvas *c_T_mcp_phds = new TCanvas("c_T_mcp_phds","Top MCP Pulse-Height Distributions",100,50,1200,800);
    
    c_T_mcp_phds->Clear();
    c_T_mcp_phds->SetFillColor(10);
    c_T_mcp_phds->Divide(2,2);
    
    Float_t lower_threshold = 0;
    Float_t upper_threshold = 4096;
    
    c_T_mcp_phds->cd(1);
    c_T_mcp_phds_1->SetLogy();
    //ha_T_mcpA->GetXaxis()->SetRangeUser(lower_threshold,upper_threshold);
    //zero_time_Tree->Draw("a_T_mcpA>>h1(4096,0,4096)");
    ha_T_mcpA->Draw();
    ha_T_mcpA->GetXaxis()->SetTitle("ADC ch");
    ha_T_mcpA->GetYaxis()->SetTitle("Counts");
    c_T_mcp_phds->cd(3);
    c_T_mcp_phds_3->SetLogy();
    //ha_T_mcpB->GetXaxis()->SetRangeUser(lower_threshold,upper_threshold);
    //zero_time_Tree->Draw("a_T_mcpB>>h2(4096,0,4096)");
    ha_T_mcpB->Draw();
    ha_T_mcpB->GetXaxis()->SetTitle("ADC ch");
    ha_T_mcpB->GetYaxis()->SetTitle("Counts");
    c_T_mcp_phds->cd(4);
    c_T_mcp_phds_4->SetLogy();
    //ha_T_mcpC->GetXaxis()->SetRangeUser(lower_threshold,upper_threshold);
    //zero_time_Tree->Draw("a_T_mcpC>>h3(4096,0,4096)");
    ha_T_mcpC->Draw();
    ha_T_mcpC->GetXaxis()->SetTitle("ADC ch");
    ha_T_mcpC->GetYaxis()->SetTitle("Counts");
    c_T_mcp_phds->cd(2);
    c_T_mcp_phds_2->SetLogy();
    //ha_T_mcpD->GetXaxis()->SetRangeUser(lower_threshold,upper_threshold);
    //zero_time_Tree->Draw("a_T_mcpD>>h4(4096,0,4096)");
    ha_T_mcpD->Draw();
    ha_T_mcpD->GetXaxis()->SetTitle("ADC ch");
    ha_T_mcpD->GetYaxis()->SetTitle("Counts");
	
	printf("\ndraw_T_mcp_posts done.\n\n");
	
}

void adc_draw_R_mcp_post_phds()
{
	
	printf("\ndraw_R_mcp_posts started.");

    TFile *tfile		= new TFile(filename);
    
    TCanvas *c_R_mcp_phds = new TCanvas("c_R_mcp_phds","Right MCP Pulse-Height Distributions",100,50,1200,800);
    
    c_R_mcp_phds->Clear();
    c_R_mcp_phds->SetFillColor(10);
    c_R_mcp_phds->Divide(2,2);
    
    Float_t lower_threshold = 0;
    Float_t upper_threshold = 4096;
    
    c_R_mcp_phds->cd(1);
    c_R_mcp_phds_1->SetLogy();
    //ha_R_mcpA->GetXaxis()->SetRangeUser(lower_threshold,upper_threshold);
    ha_R_mcpA->Draw();
    //ha_R_mcpA->GetXaxis()->SetTitle("ADC ch");
    //ha_R_mcpA->GetYaxis()->SetTitle("Counts");
    c_R_mcp_phds->cd(3);
    c_R_mcp_phds_3->SetLogy();
    //ha_R_mcpB->GetXaxis()->SetRangeUser(lower_threshold,upper_threshold);
    ha_R_mcpB->Draw();
    //ha_R_mcpB->GetXaxis()->SetTitle("ADC ch");
    //ha_R_mcpB->GetYaxis()->SetTitle("Counts");
    c_R_mcp_phds->cd(4);
    c_R_mcp_phds_4->SetLogy();
    //ha_R_mcpC->GetXaxis()->SetRangeUser(lower_threshold,upper_threshold);
    ha_R_mcpC->Draw();
    //ha_R_mcpC->GetXaxis()->SetTitle("ADC ch");
    //ha_R_mcpC->GetYaxis()->SetTitle("Counts");
    c_R_mcp_phds->cd(2);
    c_R_mcp_phds_2->SetLogy();
    //ha_R_mcpD->GetXaxis()->SetRangeUser(lower_threshold,upper_threshold);
    ha_R_mcpD->Draw();
    //ha_R_mcpD->GetXaxis()->SetTitle("ADC ch");
    //ha_R_mcpD->GetYaxis()->SetTitle("Counts");
	
	printf("\ndraw_R_mcp_posts done.\n\n");
	
}

void adc_draw_corrected_T_mcp_post_phds()
{
	
	printf("\ndraw_corrected_T_mcp_posts started.");

    TFile *tfile		= new TFile(filename);
    
    TCanvas *c_T_mcp_phds_corr = new TCanvas("c_T_mcp_phds_corr","Corrected Top MCP Pulse-Height Distributions",100,50,1200,800);
    
    c_T_mcp_phds_corr->Clear();
    c_T_mcp_phds_corr->SetFillColor(10);
    c_T_mcp_phds_corr->Divide(2,2);
    
    c_T_mcp_phds_corr->cd(1);
    c_T_mcp_phds_corr_1->SetLogy();
    //ha_T_mcpA->GetXaxis()->SetRangeUser(lower_threshold,upper_threshold);
    //zero_time_Tree->Draw("a_T_mcpA>>h1(4096,0,4096)");
    ha_T_mcpA_corr->Draw();
    ha_T_mcpA_corr->GetXaxis()->SetTitle("ADC ch");
    ha_T_mcpA_corr->GetYaxis()->SetTitle("Counts");
    c_T_mcp_phds_corr->cd(3);
    c_T_mcp_phds_corr_3->SetLogy();
    //ha_T_mcpB->GetXaxis()->SetRangeUser(lower_threshold,upper_threshold);
    //zero_time_Tree->Draw("a_T_mcpB>>h2(4096,0,4096)");
    ha_T_mcpB_corr->Draw();
    ha_T_mcpB_corr->GetXaxis()->SetTitle("ADC ch");
    ha_T_mcpB_corr->GetYaxis()->SetTitle("Counts");
    c_T_mcp_phds_corr->cd(4);
    c_T_mcp_phds_corr_4->SetLogy();
    //ha_T_mcpC->GetXaxis()->SetRangeUser(lower_threshold,upper_threshold);
    //zero_time_Tree->Draw("a_T_mcpC>>h3(4096,0,4096)");
    ha_T_mcpC_corr->Draw();
    ha_T_mcpC_corr->GetXaxis()->SetTitle("ADC ch");
    ha_T_mcpC_corr->GetYaxis()->SetTitle("Counts");
    c_T_mcp_phds_corr->cd(2);
    c_T_mcp_phds_corr_2->SetLogy();
    //ha_T_mcpD->GetXaxis()->SetRangeUser(lower_threshold,upper_threshold);
    //zero_time_Tree->Draw("a_T_mcpD>>h4(4096,0,4096)");
    ha_T_mcpD_corr->Draw();
    ha_T_mcpD_corr->GetXaxis()->SetTitle("ADC ch");
    ha_T_mcpD_corr->GetYaxis()->SetTitle("Counts");
	
	printf("\ndraw_corrected_T_mcp_posts done.\n\n");
	
}

void adc_draw_corrected_R_mcp_post_phds()
{
	
	printf("\ndraw_corrected_R_mcp_posts started.");

    TFile *tfile		= new TFile(filename);
    
    TCanvas *c_R_mcp_phds_corr = new TCanvas("c_R_mcp_phds_corr","Corrected Right MCP Pulse-Height Distributions",100,50,1200,800);
    
    c_R_mcp_phds_corr->Clear();
    c_R_mcp_phds_corr->SetFillColor(10);
    c_R_mcp_phds_corr->Divide(2,2);
    
    c_R_mcp_phds_corr->cd(1);
    c_R_mcp_phds_corr_1->SetLogy();
    //ha_R_mcpA->GetXaxis()->SetRangeUser(lower_threshold,upper_threshold);
    //zero_time_Tree->Draw("a_R_mcpA>>h1(4096,0,4096)");
    ha_R_mcpA_corr->Draw();
    ha_R_mcpA_corr->GetXaxis()->SetTitle("ADC ch");
    ha_R_mcpA_corr->GetYaxis()->SetTitle("Counts");
    c_R_mcp_phds_corr->cd(3);
    c_R_mcp_phds_corr_3->SetLogy();
    //ha_R_mcpB->GetXaxis()->SetRangeUser(lower_threshold,upper_threshold);
    //zero_time_Tree->Draw("a_R_mcpB>>h2(4096,0,4096)");
    ha_R_mcpB_corr->Draw();
    ha_R_mcpB_corr->GetXaxis()->SetTitle("ADC ch");
    ha_R_mcpB_corr->GetYaxis()->SetTitle("Counts");
    c_R_mcp_phds_corr->cd(4);
    c_R_mcp_phds_corr_4->SetLogy();
    //ha_R_mcpC->GetXaxis()->SetRangeUser(lower_threshold,upper_threshold);
    //zero_time_Tree->Draw("a_R_mcpC>>h3(4096,0,4096)");
    ha_R_mcpC_corr->Draw();
    ha_R_mcpC_corr->GetXaxis()->SetTitle("ADC ch");
    ha_R_mcpC_corr->GetYaxis()->SetTitle("Counts");
    c_R_mcp_phds_corr->cd(2);
    c_R_mcp_phds_corr_2->SetLogy();
    //ha_R_mcpD->GetXaxis()->SetRangeUser(lower_threshold,upper_threshold);
    //zero_time_Tree->Draw("a_R_mcpD>>h4(4096,0,4096)");
    ha_R_mcpD_corr->Draw();
    ha_R_mcpD_corr->GetXaxis()->SetTitle("ADC ch");
    ha_R_mcpD_corr->GetYaxis()->SetTitle("Counts");
	
	printf("\ndraw_corrected_R_mcp_posts done.\n\n");
	
}

void adc_draw_T_mcp_post_phds_near_zero()
{
	
	printf("\ndraw_T_mcp_posts started.");
	
    TFile *tfile		= new TFile(filename);
    
    TCanvas *c_T_mcp_phds_near_zero = new TCanvas("c_T_mcp_phds_near_zero","Top MCP Pulse-Height Distributions",100,50,1200,800);
    
    c_T_mcp_phds_near_zero->Clear();
    c_T_mcp_phds_near_zero->SetFillColor(10);
    c_T_mcp_phds_near_zero->Divide(2,2);
    
    Float_t lower_threshold = 0;
    Float_t upper_threshold = 200;
    
    c_T_mcp_phds_near_zero->cd(1);
    c_T_mcp_phds_near_zero_1->SetLogy();
    ha_T_mcpA->GetXaxis()->SetRangeUser(lower_threshold,upper_threshold);
    ha_T_mcpA->Draw();
    //ha_T_mcpA->GetXaxis()->SetTitle("ADC ch");
    //ha_T_mcpA->GetYaxis()->SetTitle("Counts");
    c_T_mcp_phds_near_zero->cd(3);
    c_T_mcp_phds_near_zero_3->SetLogy();
    ha_T_mcpB->GetXaxis()->SetRangeUser(lower_threshold,upper_threshold);
    ha_T_mcpB->Draw();
    //ha_T_mcpB->GetXaxis()->SetTitle("ADC ch");
    //ha_T_mcpB->GetYaxis()->SetTitle("Counts");
    c_T_mcp_phds_near_zero->cd(4);
    c_T_mcp_phds_near_zero_4->SetLogy();
    ha_T_mcpC->GetXaxis()->SetRangeUser(lower_threshold,upper_threshold);
    ha_T_mcpC->Draw();
    //ha_T_mcpC->GetXaxis()->SetTitle("ADC ch");
    //ha_T_mcpC->GetYaxis()->SetTitle("Counts");
    c_T_mcp_phds_near_zero->cd(2);
    c_T_mcp_phds_near_zero_2->SetLogy();
    ha_T_mcpD->GetXaxis()->SetRangeUser(lower_threshold,upper_threshold);
    ha_T_mcpD->Draw();
    //ha_T_mcpD->GetXaxis()->SetTitle("ADC ch");
    //ha_T_mcpD->GetYaxis()->SetTitle("Counts");
	
	printf("\ndraw_T_mcp_posts done.\n\n");
	
}

void adc_draw_R_mcp_post_phds_near_zero()
{
	
	printf("\ndraw_R_mcp_posts started.");
	
    TFile *tfile		= new TFile(filename);
    
    TCanvas *c_R_mcp_phds_near_zero = new TCanvas("c_R_mcp_phds_near_zero","Right MCP Pulse-Height Distributions",100,50,1200,800);
    
    c_R_mcp_phds_near_zero->Clear();
    c_R_mcp_phds_near_zero->SetFillColor(10);
    c_R_mcp_phds_near_zero->Divide(2,2);
    
    Float_t lower_threshold = 0;
    Float_t upper_threshold = 200;
    
    c_R_mcp_phds_near_zero->cd(1);
    c_R_mcp_phds_near_zero_1->SetLogy();
    ha_R_mcpA->GetXaxis()->SetRangeUser(lower_threshold,upper_threshold);
    ha_R_mcpA->Draw();
    //ha_R_mcpA->GetXaxis()->SetTitle("ADC ch");
    //ha_R_mcpA->GetYaxis()->SetTitle("Counts");
    c_R_mcp_phds_near_zero->cd(3);
    c_R_mcp_phds_near_zero_3->SetLogy();
    ha_R_mcpB->GetXaxis()->SetRangeUser(lower_threshold,upper_threshold);
    ha_R_mcpB->Draw();
    //ha_R_mcpB->GetXaxis()->SetTitle("ADC ch");
    //ha_R_mcpB->GetYaxis()->SetTitle("Counts");
    c_R_mcp_phds_near_zero->cd(4);
    c_R_mcp_phds_near_zero_4->SetLogy();
    ha_R_mcpC->GetXaxis()->SetRangeUser(lower_threshold,upper_threshold);
    ha_R_mcpC->Draw();
    //ha_R_mcpC->GetXaxis()->SetTitle("ADC ch");
    //ha_R_mcpC->GetYaxis()->SetTitle("Counts");
    c_R_mcp_phds_near_zero->cd(2);
    c_R_mcp_phds_near_zero_2->SetLogy();
    ha_R_mcpD->GetXaxis()->SetRangeUser(lower_threshold,upper_threshold);
    ha_R_mcpD->Draw();
    //ha_R_mcpD->GetXaxis()->SetTitle("ADC ch");
    //ha_R_mcpD->GetYaxis()->SetTitle("Counts");
	
	printf("\ndraw_R_mcp_posts done.\n\n");
	
}

void adc_draw_both_mcp_sum_phds()
{
    
    printf("\ndraw_mcp_sums started.");
    
    TFile *tfile		= new TFile(filename);
    
    TCanvas * c_mcp_sum_phds = new TCanvas("c_mcp_sum_phds", "MCP Sum-of-posts Pulse-Height Distributions", 1000, 1800);
    
    c_mcp_sum_phds->Divide(2,2);
    
    c_mcp_sum_phds->cd(1);
    c_mcp_sum_phds_1->SetLogy();
    ha_T_mcpSum->Draw();
    
	c_mcp_sum_phds->cd(2);
    c_mcp_sum_phds_2->SetLogy();
    ha_R_mcpSum->Draw();
    
    c_mcp_sum_phds->cd(3);
    c_mcp_sum_phds_3->SetLogy();
    ha_T_mcpE->Draw();
    
	c_mcp_sum_phds->cd(4);
    c_mcp_sum_phds_4->SetLogy();
    ha_R_mcpE->Draw();
    
    printf("\ndraw_mcp_sums done.\n\n");
    
}

void adc_draw_both_corrected_mcp_sum_phds()
{
    
    printf("\ndraw_corrected_mcp_sums started.");
    
    TFile *tfile		= new TFile(filename);
    
    TCanvas * c_mcp_sum_phds_corr = new TCanvas("c_mcp_sum_phds_corr", "Corrected MCP Sum-of-posts Pulse-Height Distributions", 1000, 1800);
    
    c_mcp_sum_phds_corr->Divide(2,2);
    
    c_mcp_sum_phds_corr->cd(1);
    c_mcp_sum_phds_corr_1->SetLogy();
    ha_T_mcpSum_corr->Draw();
    
	c_mcp_sum_phds_corr->cd(2);
    c_mcp_sum_phds_corr_2->SetLogy();
    ha_R_mcpSum_corr->Draw();
    
    c_mcp_sum_phds_corr->cd(3);
    c_mcp_sum_phds_corr_3->SetLogy();
    ha_T_mcpE_corr->Draw();
    
	c_mcp_sum_phds_corr->cd(4);
    c_mcp_sum_phds_corr_4->SetLogy();
    ha_R_mcpE_corr->Draw();
    
    printf("\ndraw_corrected_mcp_sums done.\n\n");
    
}

void adc_draw_all_mcp_phds()
{
	
	printf("\ndraw_c_all_mcp_phds started.");
	
    TFile *tfile		= new TFile(filename);
    
    TCanvas *c_all_mcp_phds = new TCanvas("c_all_mcp_phds","All MCP Pulse-Height Distributions",100,50,1800,900);
    gStyle->SetOptStat(11);
    
    c_all_mcp_phds->Clear();
    c_all_mcp_phds->SetFillColor(10);
    c_all_mcp_phds->Divide(6,2);
    
    Float_t lower_threshold = 0;
    Float_t upper_threshold = 4096;
    
    c_all_mcp_phds->cd(1);
    c_all_mcp_phds_1->SetLogy();
    ha_T_mcpA->Draw();
    
    c_all_mcp_phds->cd(2);
    c_all_mcp_phds_2->SetLogy();
    ha_T_mcpB->Draw();
    
    c_all_mcp_phds->cd(3);
    c_all_mcp_phds_3->SetLogy();
    ha_T_mcpC->Draw();
    
    c_all_mcp_phds->cd(4);
    c_all_mcp_phds_4->SetLogy();
    ha_T_mcpD->Draw();
    
    c_all_mcp_phds->cd(5);
    c_all_mcp_phds_5->SetLogy();
    ha_T_mcpE->Draw();
    
    c_all_mcp_phds->cd(6);
    c_all_mcp_phds_6->SetLogy();
    ha_T_mcpSum->Draw();
    
    c_all_mcp_phds->cd(7);
    c_all_mcp_phds_7->SetLogy();
    ha_R_mcpA->Draw();
    
    c_all_mcp_phds->cd(8);
    c_all_mcp_phds_8->SetLogy();
    ha_R_mcpB->Draw();
    
    c_all_mcp_phds->cd(9);
    c_all_mcp_phds_9->SetLogy();
    ha_R_mcpC->Draw();
    
    c_all_mcp_phds->cd(10);
    c_all_mcp_phds_10->SetLogy();
    ha_R_mcpD->Draw();
    
    c_all_mcp_phds->cd(11);
    c_all_mcp_phds_11->SetLogy();
    ha_R_mcpE->Draw();
    
    c_all_mcp_phds->cd(12);
    c_all_mcp_phds_12->SetLogy();
    ha_R_mcpSum->Draw();
	
	printf("\ndraw_c_all_mcp_phds.");
	
}

void adc_draw_both_mcp_maps()
{
    
    printf("\nadc_draw_both_mcp_maps started.");
    
    TFile *tfile		= new TFile(filename);
    
    TCanvas *c_mcp_maps = new TCanvas("c_mcp_maps", "MCP maps with various cuts", 1800, 900);
    gStyle->SetOptStat(111);
    c_mcp_maps->Divide(4,2);
    
    c_mcp_maps->cd(1);
    h_T_mcpMap->Draw("colz");
    
    c_mcp_maps->cd(2);
    h_T_mcpMap_post50->Draw("colz");
    
    c_mcp_maps->cd(3);
    h_T_mcpMap_post100->Draw("colz");
    
    c_mcp_maps->cd(4);
    h_T_mcpMap_post250->Draw("colz");
    
    c_mcp_maps->cd(5);
    h_R_mcpMap->Draw("colz");
    
    c_mcp_maps->cd(6);
    h_R_mcpMap_post50->Draw("colz");
    
    c_mcp_maps->cd(7);
    h_R_mcpMap_post100->Draw("colz");
    
    c_mcp_maps->cd(8);
    h_R_mcpMap_post250->Draw("colz");
    
    printf("\nadc_draw_both_mcp_maps done.\n\n");
    
}

void adc_draw_both_bkgd_mcp_maps()
{
    
    printf("\nadc_draw_both_bkgd_mcp_maps started.");
    
    TFile *tfile		= new TFile(filename);
    
    TCanvas *c_mcp_bkgd_maps = new TCanvas("c_mcp_bkgd_maps", "MCP maps with various cuts", 1800, 900);
    gStyle->SetOptStat(111);
    c_mcp_bkgd_maps->Divide(4,2);
    
    c_mcp_bkgd_maps->cd(1);
    h_bkgd_T_mcpMap->Draw("colz");
    
    c_mcp_bkgd_maps->cd(2);
    h_bkgd_T_mcpMap_post50->Draw("colz");
    
    c_mcp_bkgd_maps->cd(3);
    h_bkgd_T_mcpMap_post100->Draw("colz");
    
    c_mcp_bkgd_maps->cd(4);
    h_bkgd_T_mcpMap_post250->Draw("colz");
    
    c_mcp_bkgd_maps->cd(5);
    h_bkgd_R_mcpMap->Draw("colz");
    
    c_mcp_bkgd_maps->cd(6);
    h_bkgd_R_mcpMap_post50->Draw("colz");
    
    c_mcp_bkgd_maps->cd(7);
    h_bkgd_R_mcpMap_post100->Draw("colz");
    
    c_mcp_bkgd_maps->cd(8);
    h_bkgd_R_mcpMap_post250->Draw("colz");
    
    printf("\nadc_draw_both_bkgd_mcp_maps done.\n\n");
    
}

void tdc_draw_all_plastic_singles()
{
    
    printf("\ntdc_draw_all_plastic_singles started.\n");
    
    TFile *tfile		= new TFile(filename);
    TTree *metadata	= (TTree*)tfile->Get("metadata_Tree");
    
    metadata->GetEntry(0);
    Int_t run		= (Int_t)metadata->GetLeaf("n_run")->GetValue();
    Int_t runtime	= (Int_t)metadata->GetLeaf("run_time_sec")->GetValue();
    printf("Run %d, runtime = %d seconds\n", run, runtime);
	
    TCanvas * c_tdc_all_plastic_singles = new TCanvas("c_tdc_all_plastic_singles", "All plastic singles", 900, 800);
    
    c_tdc_all_plastic_singles->Divide(2,3);
    
    c_tdc_all_plastic_singles->cd(1);
    c_tdc_all_plastic_singles_1->SetLogy();
    ht_L_dEa->Draw();
    
    c_tdc_all_plastic_singles->cd(2);
    c_tdc_all_plastic_singles_2->SetLogy();
    ht_B_dEa->Draw();
    
    c_tdc_all_plastic_singles->cd(3);
    c_tdc_all_plastic_singles_3->SetLogy();
    ht_L_dEb->Draw();
    
	c_tdc_all_plastic_singles->cd(4);
    c_tdc_all_plastic_singles_4->SetLogy();
    ht_B_dEb->Draw();
    
    c_tdc_all_plastic_singles->cd(5);
    c_tdc_all_plastic_singles_5->SetLogy();
    ht_L_E->Draw();
    
	c_tdc_all_plastic_singles->cd(6);
    c_tdc_all_plastic_singles_6->SetLogy();
    ht_B_E->Draw();
    
    Int_t lo = 0;
    Int_t hi = 22600;
    Int_t nt_L_dEa	= ht_L_dEa	->Integral(lo, hi);
    Int_t nt_L_dEb	= ht_L_dEb	->Integral(lo, hi);
    Int_t nt_L_E	= ht_L_E	->Integral(lo, hi);
    Int_t nt_B_dEa	= ht_B_dEa	->Integral(lo, hi);
    Int_t nt_B_dEb	= ht_B_dEb	->Integral(lo, hi);
    Int_t nt_B_E	= ht_B_E	->Integral(lo, hi);
    
	printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
	printf("\n               Counts    Rate (Hz)");
	printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    printf("\nBottom dEa : %8d%8.2f", nt_B_dEa,	(Float_t)nt_B_dEa/runtime);
    printf("\nBottom dEb : %8d%8.2f", nt_B_dEb,	(Float_t)nt_B_dEb/runtime);
    printf("\nBottom E   : %8d%8.2f", nt_B_E,	(Float_t)nt_B_E/runtime);
    printf("\nLeft   dEa : %8d%8.2f", nt_L_dEa,	(Float_t)nt_L_dEa/runtime);
    printf("\nLeft   dEb : %8d%8.2f", nt_L_dEb,	(Float_t)nt_L_dEb/runtime);
    printf("\nLeft   E   : %8d%8.2f", nt_L_E,	(Float_t)nt_L_E/runtime);
    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    printf("\ntdc_draw_all_plastic_singles done.\n\n");
    
}

void tdc_draw_all_plastic_singles_rebinned()
{
    
    printf("\ntdc_draw_all_plastic_singles_rebinned started.\n");
    
    TFile *tfile		= new TFile(filename);
    TTree *metadata	= (TTree*)tfile->Get("metadata_Tree");
    
    metadata->GetEntry(0);
    Int_t run		= (Int_t)metadata->GetLeaf("n_run")->GetValue();
    Int_t runtime	= (Int_t)metadata->GetLeaf("run_time_sec")->GetValue();
    printf("Run %d, runtime = %d seconds\n", run, runtime);
	
	
	Int_t binWidth	= 200; // use ns and int's
	Int_t binSpec	= 22600 / binWidth;
	Int_t Ymax_L_dEa	= 3*(Int_t)ht_L_dEa	->Integral(1000,21000)*binWidth/20000;
	Int_t Ymax_L_dEb	= 3*(Int_t)ht_L_dEb	->Integral(1000,21000)*binWidth/20000;
	Int_t Ymax_L_E		= 3*(Int_t)ht_L_E	->Integral(1000,21000)*binWidth/20000;
	Int_t Ymax_B_dEa	= 3*(Int_t)ht_B_dEa	->Integral(1000,21000)*binWidth/20000;
	Int_t Ymax_B_dEb	= 3*(Int_t)ht_B_dEb	->Integral(1000,21000)*binWidth/20000;
	Int_t Ymax_B_E		= 3*(Int_t)ht_B_E	->Integral(1000,21000)*binWidth/20000;
	
    TCanvas * c_tdc_all_plastic_singles_rebinned = new TCanvas("c_tdc_all_plastic_singles_rebinned", "All plastic singles", 900, 800);
    
    c_tdc_all_plastic_singles_rebinned->Divide(2,3);
    
    c_tdc_all_plastic_singles_rebinned->cd(1);
    //c_tdc_all_plastic_singles_rebinned_1->SetLogy();
    ht_L_dEa->Rebin(binSpec)->Draw();
    ht_L_dEa->GetYaxis()->SetRangeUser(0,Ymax_L_dEa);
    
    c_tdc_all_plastic_singles_rebinned->cd(2);
    //c_tdc_all_plastic_singles_rebinned_2->SetLogy();
    ht_B_dEa->Rebin(binSpec)->Draw();
    ht_B_dEa->GetYaxis()->SetRangeUser(0,Ymax_B_dEa);
    
    c_tdc_all_plastic_singles_rebinned->cd(3);
    //c_tdc_all_plastic_singles_rebinned_3->SetLogy();
    ht_L_dEb->Rebin(binSpec)->Draw();
    ht_L_dEb->GetYaxis()->SetRangeUser(0,Ymax_L_dEb);
    
	c_tdc_all_plastic_singles_rebinned->cd(4);
    //c_tdc_all_plastic_singles_rebinned_4->SetLogy();
    ht_B_dEb->Rebin(binSpec)->Draw();
    ht_B_dEb->GetYaxis()->SetRangeUser(0,Ymax_B_dEb);
    
    c_tdc_all_plastic_singles_rebinned->cd(5);
    //c_tdc_all_plastic_singles_rebinned_5->SetLogy();
    ht_L_E->Rebin(binSpec)->Draw();
    ht_L_E->GetYaxis()->SetRangeUser(0,Ymax_L_E);
    
	c_tdc_all_plastic_singles_rebinned->cd(6);
    //c_tdc_all_plastic_singles_rebinned_6->SetLogy();
    ht_B_E->Rebin(binSpec)->Draw();
    ht_B_E->GetYaxis()->SetRangeUser(0,Ymax_B_E);
    
    Int_t lo = 0;
    Int_t hi = 22600;
    Int_t nt_L_dEa	= ht_L_dEa	->Integral(lo, hi);
    Int_t nt_L_dEb	= ht_L_dEb	->Integral(lo, hi);
    Int_t nt_L_E	= ht_L_E	->Integral(lo, hi);
    Int_t nt_B_dEa	= ht_B_dEa	->Integral(lo, hi);
    Int_t nt_B_dEb	= ht_B_dEb	->Integral(lo, hi);
    Int_t nt_B_E	= ht_B_E	->Integral(lo, hi);
    
	printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
	printf("\n               Counts    Rate (Hz)");
	printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    printf("\nBottom dEa : %8d%8.2f", nt_B_dEa,	(Float_t)nt_B_dEa/runtime);
    printf("\nBottom dEb : %8d%8.2f", nt_B_dEb,	(Float_t)nt_B_dEb/runtime);
    printf("\nBottom E   : %8d%8.2f", nt_B_E,	(Float_t)nt_B_E/runtime);
    printf("\nLeft   dEa : %8d%8.2f", nt_L_dEa,	(Float_t)nt_L_dEa/runtime);
    printf("\nLeft   dEb : %8d%8.2f", nt_L_dEb,	(Float_t)nt_L_dEb/runtime);
    printf("\nLeft   E   : %8d%8.2f", nt_L_E,	(Float_t)nt_L_E/runtime);
    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    printf("\ntdc_draw_all_plastic_singles_rebinned done.\n\n");
	
}

void tdc_draw_all_plastic_singles_near_zero()
{
    
    printf("\ntdc_draw_all_plastic_singles_near_zero started.");
    
    TFile *tfile		= new TFile(filename);
    
    TCanvas * c_tdc_all_plastic_singles_near_zero = new TCanvas("c_tdc_all_plastic_singles_near_zero", "All plastic singles", 900, 800);
    
    c_tdc_all_plastic_singles_near_zero->Divide(2,3);
    
    c_tdc_all_plastic_singles_near_zero->cd(1);
    c_tdc_all_plastic_singles_near_zero_1->SetLogy();
    ht_L_dEa->Draw();
    ht_L_dEa->GetXaxis()->SetRangeUser(-100,100);
    
    c_tdc_all_plastic_singles_near_zero->cd(2);
    c_tdc_all_plastic_singles_near_zero_2->SetLogy();
    ht_B_dEa->Draw();
    ht_B_dEa->GetXaxis()->SetRangeUser(-100,100);
    
    c_tdc_all_plastic_singles_near_zero->cd(3);
    c_tdc_all_plastic_singles_near_zero_3->SetLogy();
    ht_L_dEb->Draw();
    ht_L_dEb->GetXaxis()->SetRangeUser(-100,100);
    
	c_tdc_all_plastic_singles_near_zero->cd(4);
    c_tdc_all_plastic_singles_near_zero_4->SetLogy();
    ht_B_dEb->Draw();
    ht_B_dEb->GetXaxis()->SetRangeUser(-100,100);
    
    c_tdc_all_plastic_singles_near_zero->cd(5);
    c_tdc_all_plastic_singles_near_zero_5->SetLogy();
    ht_L_E->Draw();
    ht_L_E->GetXaxis()->SetRangeUser(-100,100);
    
	c_tdc_all_plastic_singles_near_zero->cd(6);
    c_tdc_all_plastic_singles_near_zero_6->SetLogy();
    ht_B_E->Draw();
    ht_B_E->GetXaxis()->SetRangeUser(-100,100);
    
    printf("\ntdc_draw_all_plastic_singles_near_zero done.\n\n");
    
}

void tdc_draw_all_mcp_singles()
{
	
	printf("\ntdc_draw_all_mcp_singles started.");
    
    TFile *tfile		= new TFile(filename);
    
    TCanvas * c_tdc_mcp_singles = new TCanvas("c_tdc_mcp_singles", "TDC: All MCP singles", 600, 800);
    
    c_tdc_mcp_singles->Divide(1,2);
    
    c_tdc_mcp_singles->cd(1);
    c_tdc_mcp_singles_1->SetLogy();
    ht_T_mcp->Draw();
    
	c_tdc_mcp_singles->cd(2);
    c_tdc_mcp_singles_2->SetLogy();
    ht_R_mcp->Draw();
    
	printf("\ntdc_draw_all_mcp_singles done.\n\n");
	
}

void tdc_draw_all_mcp_singles_near_zero()
{
    
    printf("\ntdc_draw_all_mcp_singles_near_zero started.");
    
    TFile *tfile		= new TFile(filename);
    
    TCanvas * c_tdc_mcp_singles_near_zero = new TCanvas("c_tdc_mcp_singles_near_zero", "TDC: All MCP singles near 0", 600, 800);
    
    c_tdc_mcp_singles_near_zero->Divide(1,2);
    
    c_tdc_mcp_singles_near_zero->cd(1);
    c_tdc_mcp_singles_near_zero_1->SetLogy();
    ht_T_mcp->GetXaxis()->SetRangeUser(-100,500);
    ht_T_mcp->Draw();
    
	c_tdc_mcp_singles_near_zero->cd(2);
    c_tdc_mcp_singles_near_zero_2->SetLogy();
    ht_R_mcp->GetXaxis()->SetRangeUser(-100,500);
    ht_R_mcp->Draw();
    
    printf("\ntdc_draw_all_mcp_singles_near_zero done.\n\n");
    
}

void tdc_draw_plastic_coinc_plots()
{
    
    printf("\ntdc_draw_plastic_coinc_plots started.");
    
    TFile *tfile		= new TFile(filename);
    
    TCanvas *c_tdc_plastics_tdc_on_tdc = new TCanvas("c_tdc_plastics_tdc_on_tdc", "Plastic TDC data in coincidence", 1200, 900);
	
	TCut cut_B_dEa	= "-100<t_B_dEa";
	TCut cut_B_dEb	= "-100<t_B_dEb";
	TCut cut_B_E	= "-100<t_B_E";
	TCut cut_B_dEa_dEb = cut_B_dEa && cut_B_dEb;
	
	TCut cut_L_dEa	= "-100<t_L_dEa";
	TCut cut_L_dEb	= "-100<t_L_dEb";
	TCut cut_L_E	= "-100<t_L_E";
	TCut cut_L_dEa_dEb = cut_L_dEa && cut_L_dEb;
	
    gStyle->SetOptStat(111);
    c_tdc_plastics_tdc_on_tdc->Divide(2,3);
    
    c_tdc_plastics_tdc_on_tdc->cd(1);
    bdn_Tree->Draw("t_L_dEa>>h1(200,-100,100)",cut_L_dEa_dEb && "a_L_E>616");
	
	c_tdc_plastics_tdc_on_tdc->cd(2);
	bdn_Tree->Draw("t_B_dEa>>h2(200,-100,100)",cut_B_dEa_dEb);
	
	c_tdc_plastics_tdc_on_tdc->cd(3);
    bdn_Tree->Draw("t_L_dEb>>h3(200,-100,100)",cut_L_dEa_dEb && "a_L_E>616");
	
	c_tdc_plastics_tdc_on_tdc->cd(4);
    bdn_Tree->Draw("t_B_dEb>>h4(200,-100,100)",cut_B_dEa_dEb);
	
	c_tdc_plastics_tdc_on_tdc->cd(5);
    bdn_Tree->Draw("t_L_E>>h5(200,-100,100)",cut_L_dEa_dEb && "a_L_E>616");
	
	c_tdc_plastics_tdc_on_tdc->cd(6);
    bdn_Tree->Draw("t_B_E>>h6(200,-100,100)",cut_B_dEa_dEb);
    
    printf("\ntdc_draw_plastic_coinc_plots done.\n\n");
    
}

void adc_draw_plastic_coinc_plots()
{
    
    printf("\nadc_draw_plastic_coinc_plots started.");
    
    TFile *tfile		= new TFile(filename);
    
    TCanvas *c_adc_plastics_adc_on_tdc = new TCanvas("c_adc_plastics_adc_on_tdc", "Plastic ADC data in coincidence", 1200, 900);

	TCut cut_B_dEa	= "-100<t_B_dEa";
	TCut cut_B_dEb	= "-100<t_B_dEb";
	//TCut cut_B_E	= "-100<t_B_E";    // @@@@@@@@@@@@@@@@@@@ there is a duplicate of a cut here
	TCut cut_B_E	= "250<a_B_E && a_B_E<350";
	TCut cut_B_dEa_dEb = cut_B_dEa && cut_B_dEb;
	
	TCut cut_L_dEa	= "-100<t_L_dEa";
	TCut cut_L_dEb	= "-100<t_L_dEb";
	TCut cut_L_E	= "250<a_L_E && a_L_E<350";
	TCut cut_L_dEa_dEb = cut_L_dEa && cut_L_dEb;
	
    gStyle->SetOptStat(111);
    c_adc_plastics_adc_on_tdc->Divide(2,4);
    
    c_adc_plastics_adc_on_tdc->cd(1);
    bdn_Tree->Draw("a_L_dEa>>h1(4096,0,4095)",cut_L_dEa && "-100<t_L_E"); // && cut_L_E);
	
	c_adc_plastics_adc_on_tdc->cd(2);
	bdn_Tree->Draw("a_B_dEa>>h2(4096,0,4095)",cut_B_dEa && "-100<t_B_E");// && cut_B_E);
	
	c_adc_plastics_adc_on_tdc->cd(3);
    bdn_Tree->Draw("a_L_dEb>>h3(4096,0,4095)",cut_L_dEb && "-100<t_L_E");// && cut_L_E);
	
	c_adc_plastics_adc_on_tdc->cd(4);
    bdn_Tree->Draw("a_B_dEb>>h4(4096,0,4095)",cut_B_dEb && "-100<t_B_E");// && cut_B_E);
	
	c_adc_plastics_adc_on_tdc->cd(5);
    bdn_Tree->Draw("a_L_dEa+a_L_dEb>>h5(8192,0,8191)",cut_L_dEa_dEb);// && cut_L_E);
	
	c_adc_plastics_adc_on_tdc->cd(6);
    bdn_Tree->Draw("a_B_dEa+a_B_dEb>>h6(8192,0,8191)",cut_B_dEa_dEb);// && cut_B_E);
	
	c_adc_plastics_adc_on_tdc->cd(7);
    bdn_Tree->Draw("a_L_E>>h7(4096,0,4095)",cut_L_dEa_dEb);// && "t_L_E>-100");
	
	c_adc_plastics_adc_on_tdc->cd(8);
    bdn_Tree->Draw("a_B_E>>h8(4096,0,4095)",cut_B_dEa_dEb);
    
    /*
    TCanvas *c_adc_dE_vs_E = new TCanvas("c_adc_dE_vs_E", "Plastic ADC data: dE va E", 1000, 1000);
	
    c_adc_dE_vs_E->Divide(2,2);
    
    c_adc_dE_vs_E->cd(1);
    bdn_Tree->Draw("a_L_dEa:a_L_E>>h21(1028,0,4095,1028,0,4095)","","colz");
    
    c_adc_dE_vs_E->cd(2);
    bdn_Tree->Draw("a_B_dEa:a_B_E>>h22(1028,0,4095,1028,0,4095)","","colz");
    
    c_adc_dE_vs_E->cd(3);
    bdn_Tree->Draw("a_L_dEb:a_L_E>>h23(1028,0,4095,1028,0,4095)","","colz");
    
    c_adc_dE_vs_E->cd(4);
    bdn_Tree->Draw("a_B_dEb:a_B_E>>h24(1028,0,4095,1028,0,4095)","","colz");
    */
    printf("\nadc_draw_plastic_coinc_plots done.\n\n");
/*    
    TCanvas *c_stuff = new TCanvas("c_stuff");
    TCut cut_Peak1	= "0 < a_L_dEa && a_L_dEa < 300";
    TCut cut_Peak2	= "0 < a_L_dEb && a_L_dEb < 300";
    bdn_Tree->Draw("t_L_dEa>>hS1(4096,0,4095)",cut_L_dEa_dEb && cut_Peak1 && cut_Peak2);
    
    TCanvas *c_stuff2 = new TCanvas("c_stuff2");
    bdn_Tree->Draw("a_L_E>>hS2(4096,0,4095)",cut_L_dEa_dEb && cut_Peak1);
*/    
    
}

void tdc_draw_plastic_diffs()
{
    
    printf("\ntdc_draw_plastic_diffs started.");
    
    TFile *tfile		= new TFile(filename);
    
    TCanvas *c_tdc_plastics_diffs = new TCanvas("c_tdc_plastics_diffs", "Differences of plastic TDC data", 1200, 900);
	
	TCut cut_B_dEa	= "-100<t_B_dEa";
	TCut cut_B_dEb	= "-100<t_B_dEb";
	TCut cut_B_E	= "-100<t_B_E";
	TCut cut_B_dEa_dEb = cut_B_dEa && cut_B_dEb;
	
	TCut cut_L_dEa	= "-100<t_L_dEa";
	TCut cut_L_dEb	= "-100<t_L_dEb";
	TCut cut_L_E	= "-100<t_L_E";
	TCut cut_L_dEa_dEb = cut_L_dEa && cut_L_dEb;
	
    gStyle->SetOptStat(111);
    c_tdc_plastics_diffs->Divide(2,3);
    
    c_tdc_plastics_diffs->cd(1);
    c_tdc_plastics_diffs_1->SetLogy();
    ht_L_dEdiff->Draw();
	
	c_tdc_plastics_diffs->cd(2);
	c_tdc_plastics_diffs_2->SetLogy();
	ht_B_dEdiff->Draw();
	
	c_tdc_plastics_diffs->cd(3);
    c_tdc_plastics_diffs_3->SetLogy();
    ht_L_dE->Draw();
	
	c_tdc_plastics_diffs->cd(4);
    c_tdc_plastics_diffs_4->SetLogy();
    ht_B_dE->Draw();
	
	c_tdc_plastics_diffs->cd(5);
    c_tdc_plastics_diffs_5->SetLogy();
    ht_L_dE_E->Draw();
	
	c_tdc_plastics_diffs->cd(6);
    c_tdc_plastics_diffs_6->SetLogy();
    ht_B_dE_E->Draw();
    
    printf("\ntdc_draw_plastic_diffs done.\n\n");
    
}


void tdc_ge()
{
    
    printf("\ntdc_ge started.");
    
    TFile *tfile		= new TFile(filename);
    
    TCanvas *c_tdc_ge = new TCanvas("c_tdc_ge", "Ge TDC", 1200, 900);
	
	TCut cut_B_dEa	= "-100<t_B_dEa";
	TCut cut_B_dEb	= "-100<t_B_dEb";
	TCut cut_B_E	= "-100<t_B_E";
	TCut cut_B_dEa_dEb = cut_B_dEa && cut_B_dEb;
	
	TCut cut_L_dEa	= "-100<t_L_dEa";
	TCut cut_L_dEb	= "-100<t_L_dEb";
	TCut cut_L_E	= "-100<t_L_E";
	TCut cut_L_dEa_dEb = cut_L_dEa && cut_L_dEb;
	
    gStyle->SetOptStat(111);
    c_tdc_ge->Divide(2,3);
    
    c_tdc_ge->cd(1);
    bdn_Tree->Draw("t_R_ge>>h1(1100,-100,1000)");
	
    c_tdc_ge->cd(3);
    bdn_Tree->Draw("t_R_ge>>h2(1100,-100,1000)", cut_L_E && cut_L_dEa_dEb);

    c_tdc_ge->cd(5);
    bdn_Tree->Draw("t_R_ge>>h3(1100,-100,1000)", cut_B_E && cut_B_dEa_dEb);
    
    c_tdc_ge->cd(2);
    bdn_Tree->Draw("t_T_ge>>h4(1100,-100,1000)");
	
    c_tdc_ge->cd(4);
    bdn_Tree->Draw("t_T_ge>>h5(1100,-100,1000)", cut_L_E && cut_L_dEa_dEb);
    
    c_tdc_ge->cd(6);
    bdn_Tree->Draw("t_T_ge>>h6(1100,-100,1000)", cut_B_E && cut_B_dEa_dEb);
    
    printf("\ntdc_Ge done.\n\n");
    
}

void tdc_draw_dE_Ge_tof_spectra()
{
	
	printf("\ndraw_dE-Ge_spectra started.");
	
	TFile *tfile		= new TFile(filename);
	
	TCanvas *c_dE_Ge_tof_spectra = new TCanvas("c_dE_Ge_tof_spectra","TOF Spectra (dE-Ge)",1600,1000);
	
	c_dE_Ge_tof_spectra->Divide(2,2);
	
	c_dE_Ge_tof_spectra->cd(1);
	c_dE_Ge_tof_spectra_1->SetLogy();
	h_dE_ge_tof_LT->Draw();
	
	c_dE_Ge_tof_spectra->cd(2);
	c_dE_Ge_tof_spectra_2->SetLogy();
	h_dE_ge_tof_LR->Draw();
	
	c_dE_Ge_tof_spectra->cd(3);
	c_dE_Ge_tof_spectra_3->SetLogy();
	h_dE_ge_tof_BT->Draw();
	
	c_dE_Ge_tof_spectra->cd(4);
	c_dE_Ge_tof_spectra_4->SetLogy();
	h_dE_ge_tof_BR->Draw();
	
	TCanvas *c_dE_Ge_tof_sum_spectrum = new TCanvas("c_dE_Ge_tof_sum_spectrum","TOF Spectrum (All dE-Ge combos)",800,500);
    h_dE_ge_tof->Draw();
    
	printf("\ndraw_dE-Ge_tof_spectra done.\n\n");
	
}

void tdc_draw_dE_mcp_tof_spectra()
{
	
	printf("\ndraw_dE-MCP_tof_spectra started.");
	
	TFile *tfile		= new TFile(filename);
	
	TCanvas *c_dE_MCP_tof_spectra = new TCanvas("c_dE_MCP_tof_spectra","TOF Spectra (dE-MCP)",1600,1000);
	
	c_dE_MCP_tof_spectra->Divide(2,2);
	
	c_dE_MCP_tof_spectra->cd(1);
	c_dE_MCP_tof_spectra_1->SetLogy();
	h_tof_LT->Draw();
	
	c_dE_MCP_tof_spectra->cd(2);
	c_dE_MCP_tof_spectra_2->SetLogy();
	h_tof_LR->Draw();
	
	c_dE_MCP_tof_spectra->cd(3);
	c_dE_MCP_tof_spectra_3->SetLogy();
	h_tof_BT->Draw();
	
	c_dE_MCP_tof_spectra->cd(4);
	c_dE_MCP_tof_spectra_4->SetLogy();
	h_tof_BR->Draw();
	
	TCanvas *c_dE_MCP_tof_sum_spectrum = new TCanvas("c_dE_MCP_tof_sum_spectrum","TOF Spectrum (All dE-MCP combos)",945,600);
    c_dE_MCP_tof_sum_spectrum->SetLogy();
    h_tof->Draw();
    
	printf("\ndraw_dE-MCP_tof_spectra done.\n\n");
	
}

void draw_all_dE_mcp_tof_spectra_on_one_plot()
{
	
	printf("\ndraw_all_dE_mcp_tof_spectra_on_one_plot started.");
	
	TFile *tfile		= new TFile(filename);
	TCanvas *c_dE_MCP_tof_all_combos	= new TCanvas("c_dE_MCP_tof_all_combos","TOF spectra for all four combos",945,600);
	c_dE_MCP_tof_all_combos->SetLogy();
	
	h_tof_LT->SetTitle("TOF for each detector combo");
	h_tof_LT->Draw();
	h_tof_LR->Draw("SAME");
	h_tof_BT->Draw("SAME");
	h_tof_BR->Draw("SAME");
	h_tof_LT->SetLineColor(kBlue);
	h_tof_LR->SetLineColor(kViolet);
	h_tof_BT->SetLineColor(kOrange);
	h_tof_BR->SetLineColor(kRed);
	TLegend *leg_1 = new TLegend(0.88, 0.54, 0.98, 0.775);
	leg_1->AddEntry(h_tof_LT,"LT");
	leg_1->AddEntry(h_tof_LR,"LR");
	leg_1->AddEntry(h_tof_BT,"BT");
	leg_1->AddEntry(h_tof_BR,"BR");
	leg_1->SetFillColor(0);
	leg_1->Draw();
	
	printf("\ndraw_all_dE_mcp_tof_spectra_on_one_plot done.\n\n");
	
}
	
void tdc_draw_background_dE_mcp_tof_spectra()
{
	
	printf("\ndraw_background_dE-MCP_tof_spectra started.");
	
	TFile *tfile		= new TFile(filename);
	
	TCanvas *c_bkgd_dE_MCP_tof_spectra = new TCanvas("c_bkgd_dE_MCP_tof_spectra","[BACKGROUND] TOF Spectra (dE-MCP)",1600,1000);
	
	c_bkgd_dE_MCP_tof_spectra->Divide(2,2);
	
	c_bkgd_dE_MCP_tof_spectra->cd(1);
	c_bkgd_dE_MCP_tof_spectra_1->SetLogy();
	h_bkgd_tof_LT->Draw();
	
	c_bkgd_dE_MCP_tof_spectra->cd(2);
	c_bkgd_dE_MCP_tof_spectra_2->SetLogy();
	h_bkgd_tof_LR->Draw();
	
	c_bkgd_dE_MCP_tof_spectra->cd(3);
	c_bkgd_dE_MCP_tof_spectra_3->SetLogy();
	h_bkgd_tof_BT->Draw();
	
	c_bkgd_dE_MCP_tof_spectra->cd(4);
	c_bkgd_dE_MCP_tof_spectra_4->SetLogy();
	h_bkgd_tof_BR->Draw();
	
	TCanvas *c_bkgd_dE_MCP_tof_sum_spectrum = new TCanvas("c_bkgd_dE_MCP_tof_sum_spectrum","[BACKGROUND] TOF Spectrum (All dE-MCP combos)",800,500);
	c_bkgd_dE_MCP_tof_sum_spectrum->SetLogy();
    h_bkgd_tof->Draw();
/*    
    TF1 *fq=new TF1("f4","gaus(0)+pol0(3)",0,100);
    //fq->SetParLimits(1,41.0,51.0);
    fq->SetParameter(0,20.0);
    fq->SetParameter(1,40.0);
    //fq->SetParLimits(1,40.0,50.0);
    fq->SetParameter(2,2.0);
    fq->SetParName(0,"Amplitude");
    fq->SetParName(1,"Mean");
    fq->SetParName(2,"Sigma");
    fq->SetParName(3,"Baseline");
    h_bkgd_tof->Fit(fq,"R");
*/    
    
//    h_bkgd_tof->GetXaxis()->SetRangeUser(0,100);
    
//    printf("\nFWHM = %f +/- %f\n",2.35*TMath::Abs(fq->GetParameter(2)),2.35*fq->GetParError(2));
//    printf("\ndraw_background_dE-MCP_tof_spectra done.\n\n");
/*    
    TCanvas *c_bkgd_dEmin_MCP_tof_sum_spectrum = new TCanvas("c_bkgd_dEmin_MCP_tof_sum_spectrum","[BACKGROUND] TOF Spectrum using min(dEa,dEb) (All dE-MCP combos)",800,500);
    
    TF1 *fq2=new TF1("f4min","gaus(0)+pol0(3)",0,100);
    //fq2->SetParLimits(1,40.0,50.0);
    fq2->SetParameter(0,20.0);
    fq2->SetParameter(1,40.0);
    fq2->SetParameter(2,2.0);

    fq2->SetParName(0,"Amplitude");
    fq2->SetParName(1,"Mean");
    fq2->SetParName(2,"Sigma");
    fq2->SetParName(3,"Baseline");
    h_bkgd_tof_dEmin->Fit(fq2,"R");
    
    h_bkgd_tof_dEmin->Draw();
    h_bkgd_tof_dEmin->GetXaxis()->SetRangeUser(0,100);
    
    printf("\nFWHM = %f +/- %f\n",2.35*TMath::Abs(fq2->GetParameter(2)),2.35*fq2->GetParError(2));
    printf("\ndraw_background_dE-MCP_tof_spectra done.\n\n");
*/
}

void tdc_draw_E_mcp_tof_spectra()
{
	
	printf("\ndraw_E-MCP_tof_spectra started.");
	
	TFile *tfile		= new TFile(filename);
	
	TCanvas *c_E_MCP_tof_spectra = new TCanvas("c_E_MCP_tof_spectra","TOF Spectra (dE-MCP)",1600,1000);
	
	c_E_MCP_tof_spectra->Divide(2,2);
	
	c_E_MCP_tof_spectra->cd(1);
	c_E_MCP_tof_spectra_1->SetLogy();
	h_E_tof_LT->Draw();
	
	c_E_MCP_tof_spectra->cd(2);
	c_E_MCP_tof_spectra_2->SetLogy();
	h_E_tof_LR->Draw();
	
	c_E_MCP_tof_spectra->cd(3);
	c_E_MCP_tof_spectra_3->SetLogy();
	h_E_tof_BT->Draw();
	
	c_E_MCP_tof_spectra->cd(4);
	c_E_MCP_tof_spectra_4->SetLogy();
	h_E_tof_BR->Draw();
	
	TCanvas *c_E_MCP_tof_sum_spectrum = new TCanvas("c_E_MCP_tof_sum_spectrum","TOF Spectrum (All dE-MCP combos)",800,500);
    h_E_tof->Draw();
    
	printf("\ndraw_E-MCP_tof_spectra done.\n\n");
	
}

void tdc_draw_ge_mcp_tof_spectra()
{
	
	printf("\ndraw_Ge-MCP_tof_spectra started.");
	
	TFile *tfile		= new TFile(filename);
	
	TCanvas *c_ge_MCP_tof_spectra = new TCanvas("c_ge_MCP_tof_spectra","TOF Spectra (Ge-MCP)",1600,1000);
	
	c_ge_MCP_tof_spectra->Divide(2,2);
	
	c_ge_MCP_tof_spectra->cd(1);
	c_ge_MCP_tof_spectra_1->SetLogy();
	h_ge_tof_TT->Draw();
	
	c_ge_MCP_tof_spectra->cd(2);
	c_ge_MCP_tof_spectra_2->SetLogy();
	h_ge_tof_RT->Draw();
	
	c_ge_MCP_tof_spectra->cd(3);
	c_ge_MCP_tof_spectra_3->SetLogy();
	h_ge_tof_TR->Draw();
	
	c_ge_MCP_tof_spectra->cd(4);
	c_ge_MCP_tof_spectra_4->SetLogy();
	h_ge_tof_RR->Draw();
	
	TCanvas *c_ge_MCP_tof_sum_spectrum = new TCanvas("c_ge_MCP_tof_sum_spectrum","TOF Spectrum (All Ge-MCP combos)",800,500);
    h_ge_tof->Draw();
    
	printf("\ndraw_Ge-MCP_tof_spectra done.\n\n");
	
}

void tdc_draw_dE_E_tof_spectra()
{
	
	printf("\ndraw_dE-E_tof_spectra started.");
	
	TFile *tfile		= new TFile(filename);
	
	TCanvas *c_dE_E_tof_spectra = new TCanvas("c_dE_E_tof_spectra","TOF Spectra (dE-E)",1600,1000);
	
	c_dE_E_tof_spectra->Divide(2,2);
	
	c_dE_E_tof_spectra->cd(1);
	c_dE_E_tof_spectra_1->SetLogy();
	h_dE_E_tof_LL->Draw();
	
	c_dE_E_tof_spectra->cd(2);
	c_dE_E_tof_spectra_2->SetLogy();
	h_dE_E_tof_LB->Draw();
	
	c_dE_E_tof_spectra->cd(3);
	c_dE_E_tof_spectra_3->SetLogy();
	h_dE_E_tof_BL->Draw();
	
	c_dE_E_tof_spectra->cd(4);
	c_dE_E_tof_spectra_4->SetLogy();
	h_dE_E_tof_BB->Draw();
	
	TCanvas *c_dE_E_tof_sum_spectrum = new TCanvas("c_dE_E_tof_sum_spectrum","TOF Spectrum (All dE-E combos)",800,500);
    h_dE_E_tof->Draw();
    
	printf("\ndraw_dE-E_tof_spectra done.\n\n");
	
}
/*
void gated_mcp_phd()
{
	TFile *tfile		= new TFile(filename);
	
	TCut L_beta = "-100 < t_L_dEa && -100 < t_L_dEb";
	TCut B_beta = "-100 < t_B_dEa && -100 < t_B_dEb";
	TCut dEs = "-100 < t_L_dEa && -100 < t_L_dEb";
	TCut mcp = "-100 < t_R_mcp";
	TCut tof1 = "2500 < (t_R_mcp-0.5*(t_L_dEa+t_L_dEb)) && (t_R_mcp-0.5*(t_L_dEa+t_L_dEb)) < 6000";
    TCut tof2 = "6001 < (t_R_mcp-0.5*(t_L_dEa+t_L_dEb)) && (t_R_mcp-0.5*(t_L_dEa+t_L_dEb)) < 9501";
    
    
    TCanvas *c_808 = new TCanvas("c_808", "Gated MCP PHD -- Blue = Rec+Acc, Red = Acc. only", 1200, 900);
    bdn_Tree->Draw("a_R_mcpSum>>h801(2000,0,20000)",dEs&&mcp&&tof1);
	bdn_Tree->Draw("a_R_mcpSum>>h802(2000,0,20000)",dEs&&mcp&&tof2,"SAME");
	h802->SetLineColor(2);
	
	TCanvas *c_808_diff = new TCanvas("c_808_diff", "Gated MCP PHD -- Acc. subtracted", 1200, 900);
	TH1I *h001 = (TH1I*)h801->Clone("h001");
	h001 = h001->Add(h802,-1.0);
	//h001->SetLineColor(3);
	h001->Draw();
	
}

void time_since_eject()
{

	TFile *tfile		= new TFile(filename);
	
	TCut L_beta = "-100 < t_L_dEa && -100 < t_L_dEb";
	TCut B_beta = "-100 < t_B_dEa && -100 < t_B_dEb";
	TCut dEs = "-100 < t_L_dEa && -100 < t_L_dEb";
	TCut mcp = "-100 < t_R_mcp";
	TCut tof1 = "2500 < (t_R_mcp-0.5*(t_L_dEa+t_L_dEb)) && (t_R_mcp-0.5*(t_L_dEa+t_L_dEb)) < 6000";
    TCut tof2 = "6001 < (t_R_mcp-0.5*(t_L_dEa+t_L_dEb)) && (t_R_mcp-0.5*(t_L_dEa+t_L_dEb)) < 9501";
    
	TCanvas *c_recs = new TCanvas("c_recs", "Recoil ions versus time since eject", 1200, 900);
	bdn_Tree->Draw("s_ms_since_eject>>h_recs(227000,-1000,226000)",dEs&&mcp&&tof1);
	
	TCanvas *c_betas = new TCanvas("c_betas", "Beta singles versus time since eject", 1200, 900);
	bdn_Tree->Draw("s_ms_since_eject>>h_betas(227000,-1000,226000)", (B_beta || L_beta) );

}
*/
void draw_slow_recoils_vs_cycle_time()
{
	TFile *tfile		= new TFile(filename);
	
	//TCut LT_tof1 = "2500 < (t_T_mcp-t_L_dE) && (t_T_mcp-t_L_dE) < 6000";
	//TCut LR_tof1 = "2500 < (t_R_mcp-t_L_dE) && (t_R_mcp-t_L_dE) < 6000";
	//TCut BT_tof1 = "2500 < (t_T_mcp-t_B_dE) && (t_T_mcp-t_B_dE) < 6000";
	//TCut BR_tof1 = "2500 < (t_R_mcp-t_B_dE) && (t_R_mcp-t_B_dE) < 6000";
    //TCut LT_tof2 = "10000 < (t_T_mcp-t_L_dE) && (t_T_mcp-t_L_dE) < 13500";
	//TCut LR_tof2 = "10000 < (t_R_mcp-t_L_dE) && (t_R_mcp-t_L_dE) < 13500";
	//TCut BT_tof2 = "10000 < (t_T_mcp-t_B_dE) && (t_T_mcp-t_B_dE) < 13500";
	//TCut BR_tof2 = "10000 < (t_R_mcp-t_B_dE) && (t_R_mcp-t_B_dE) < 13500";
    
    //TH1I *h_T_slow_vs_cycle_time = new TH1I("h_T_slow_vs_cycle_time","Top MCP Slow Recoils vs Cycle Time",302000,-1000.0,301000);
	//TH1I *h_R_slow_vs_cycle_time = new TH1I("h_R_slow_vs_cycle_time","Right MCP Slow Recoils vs Cycle Time",302000,-1000.0,301000);
	//TH1I *h_slow_vs_cycle_time = new TH1I("h_slow_vs_cycle_time","All MCP Slow Recoils vs Cycle Time",302000,-1000.0,301000);
	
	//beta_recoil_tree->Project("h_T_slow_vs_cycle_time","s_ms_since_eject", LT_tof1 || BT_tof1);
	//beta_recoil_tree->Project("h_R_slow_vs_cycle_time","s_ms_since_eject", LR_tof1 || BR_tof1);
	//h_slow_vs_cycle_time = h_slow_vs_cycle_time->Add(h_T_slow_vs_cycle_time,1.0);
	//h_slow_vs_cycle_time = h_slow_vs_cycle_time->Add(h_R_slow_vs_cycle_time,1.0);
	
	TCanvas *c_slow_recoils_vs_cycle_time = new TCanvas("c_slow_recoils_vs_cycle_time", "Recoil ions vs cycle time", 900, 900);
	c_slow_recoils_vs_cycle_time->Divide(1,2);
	c_slow_recoils_vs_cycle_time->cd(1);
	h_T_slow_vs_cycle_time->Draw();
	c_slow_recoils_vs_cycle_time->cd(2);
	h_R_slow_vs_cycle_time->Draw();
	
	TCanvas *c_all_slow_recoils_vs_cycle_time = new TCanvas("c_all_slow_recoils_vs_cycle_time", "Recoil ions vs cycle time", 900, 600);
	h_slow_vs_cycle_time->Draw();

}

void draw_fast_recoils_vs_cycle_time()
{
	TFile *tfile		= new TFile(filename);
	
	//TCut LT_tof1 = "2500 < (t_T_mcp-t_L_dE) && (t_T_mcp-t_L_dE) < 6000";
	//TCut LR_tof1 = "2500 < (t_R_mcp-t_L_dE) && (t_R_mcp-t_L_dE) < 6000";
	//TCut BT_tof1 = "2500 < (t_T_mcp-t_B_dE) && (t_T_mcp-t_B_dE) < 6000";
	//TCut BR_tof1 = "2500 < (t_R_mcp-t_B_dE) && (t_R_mcp-t_B_dE) < 6000";
    //TCut LT_tof2 = "10000 < (t_T_mcp-t_L_dE) && (t_T_mcp-t_L_dE) < 13500";
	//TCut LR_tof2 = "10000 < (t_R_mcp-t_L_dE) && (t_R_mcp-t_L_dE) < 13500";
	//TCut BT_tof2 = "10000 < (t_T_mcp-t_B_dE) && (t_T_mcp-t_B_dE) < 13500";
	//TCut BR_tof2 = "10000 < (t_R_mcp-t_B_dE) && (t_R_mcp-t_B_dE) < 13500";
    
    //TH1I *h_T_slow_vs_cycle_time = new TH1I("h_T_slow_vs_cycle_time","Top MCP Slow Recoils vs Cycle Time",302000,-1000.0,301000);
	//TH1I *h_R_slow_vs_cycle_time = new TH1I("h_R_slow_vs_cycle_time","Right MCP Slow Recoils vs Cycle Time",302000,-1000.0,301000);
	//TH1I *h_slow_vs_cycle_time = new TH1I("h_slow_vs_cycle_time","All MCP Slow Recoils vs Cycle Time",302000,-1000.0,301000);
	
	//beta_recoil_tree->Project("h_T_slow_vs_cycle_time","s_ms_since_eject", LT_tof1 || BT_tof1);
	//beta_recoil_tree->Project("h_R_slow_vs_cycle_time","s_ms_since_eject", LR_tof1 || BR_tof1);
	//h_slow_vs_cycle_time = h_slow_vs_cycle_time->Add(h_T_slow_vs_cycle_time,1.0);
	//h_slow_vs_cycle_time = h_slow_vs_cycle_time->Add(h_R_slow_vs_cycle_time,1.0);
	
	TCanvas *c_slow_recoils_vs_cycle_time = new TCanvas("c_slow_recoils_vs_cycle_time", "Recoil ions vs cycle time", 900, 900);
	c_slow_recoils_vs_cycle_time->Divide(1,2);
	c_slow_recoils_vs_cycle_time->cd(1);
	h_T_slow_vs_cycle_time->Draw();
	c_slow_recoils_vs_cycle_time->cd(2);
	h_R_slow_vs_cycle_time->Draw();
	
	TCanvas *c_all_slow_recoils_vs_cycle_time = new TCanvas("c_all_slow_recoils_vs_cycle_time", "Recoil ions vs cycle time", 900, 600);
	h_slow_vs_cycle_time->Draw();

}

void recoil_ion_rates()
{
    
    printf("\nrecoil_ion_rates started.");
	
    TFile *tfile		= new TFile(filename);
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
	Double_t bkgd_per_ch_left_right		= h_tof_LR->Integral(bkgd_t_low,bkgd_t_high) / bkgd_t_range;
	Double_t bkgd_per_ch_bottom_top		= h_tof_BT->Integral(bkgd_t_low,bkgd_t_high) / bkgd_t_range;
	Double_t bkgd_per_ch_bottom_right	= h_tof_BR->Integral(bkgd_t_low,bkgd_t_high) / bkgd_t_range;
    
    Double_t bdn_area_left_top		= h_tof_LT->Integral(bdn_t_low,bdn_t_high) - bkgd_per_ch_left_top*bdn_t_range;
	Double_t bdn_area_left_right	= h_tof_LR->Integral(bdn_t_low,bdn_t_high) - bkgd_per_ch_left_right*bdn_t_range;
	Double_t bdn_area_bottom_top	= h_tof_BT->Integral(bdn_t_low,bdn_t_high) - bkgd_per_ch_bottom_top*bdn_t_range;
	Double_t bdn_area_bottom_right	= h_tof_BR->Integral(bdn_t_low,bdn_t_high) - bkgd_per_ch_bottom_right*bdn_t_range;
	
	Double_t beta_area_left_top		= h_tof_LT->Integral(beta_t_low,beta_t_high) - bkgd_per_ch_left_top*beta_t_range;
	Double_t beta_area_left_right	= h_tof_LR->Integral(beta_t_low,beta_t_high) - bkgd_per_ch_left_right*beta_t_range;
	Double_t beta_area_bottom_top	= h_tof_BT->Integral(beta_t_low,beta_t_high) - bkgd_per_ch_bottom_top*beta_t_range;
	Double_t beta_area_bottom_right	= h_tof_BR->Integral(beta_t_low,beta_t_high) - bkgd_per_ch_bottom_right*beta_t_range;
	
	Double_t bdn_area_tot = bdn_area_left_top + bdn_area_left_right + bdn_area_bottom_top + bdn_area_bottom_right;
	Double_t beta_area_tot = beta_area_left_top + beta_area_left_right + beta_area_bottom_top + beta_area_bottom_right;
    
    Int_t a = h_tof_LT->Integral(beta_t_low,beta_t_high);
    Int_t b = h_tof_LR->Integral(beta_t_low,beta_t_high);
    Int_t c = h_tof_BT->Integral(beta_t_low,beta_t_high);
    Int_t d = h_tof_BR->Integral(beta_t_low,beta_t_high);
    
    Int_t e = h_tof_LT->Integral(bkgd_t_low,bkgd_t_high);
    Int_t f = h_tof_LR->Integral(bkgd_t_low,bkgd_t_high);
    Int_t g = h_tof_BT->Integral(bkgd_t_low,bkgd_t_high);
    Int_t h = h_tof_BR->Integral(bkgd_t_low,bkgd_t_high);
    
    Int_t i = h_tof_LT->Integral(bdn_t_low,bdn_t_high);
    Int_t j = h_tof_LR->Integral(bdn_t_low,bdn_t_high);
    Int_t k = h_tof_BT->Integral(bdn_t_low,bdn_t_high);
    Int_t l = h_tof_BR->Integral(bdn_t_low,bdn_t_high);
    
    cout << " " << endl << endl;
    
    cout << "Fast LT counts: " << i << "\tSlow LT counts: " << a << "\tBkgd LT counts: " << e << endl;
    cout << "Fast LR counts: " << j << "\tSlow LR counts: " << b << "\tBkgd LR counts: " << f << endl;
    cout << "Fast BT counts: " << k << "\tSlow BT counts: " << c << "\tBkgd BT counts: " << g << endl;
    cout << "Fast BR counts: " << l << "\tSlow BR counts: " << d << "\tBkgd BR counts: " << h << endl;
    
    cout << " " << endl;
    
    cout << "Fast range: " << (bdn_t_low-1)/2.0+t_min << " to " << (bdn_t_high-1)/2.0+t_min << " ns ==> Delta = " << bdn_t_range/2.0 << " ns" << endl;
    cout << "Slow range: " << (beta_t_low-1)/2.0+t_min << " to " << (beta_t_high-1)/2.0+t_min << " ns ==> Delta = " << beta_t_range/2.0 << " ns" << endl;
    cout << "Bkgd range: " << (bkgd_t_low-1)/2.0+t_min << " to " << (bkgd_t_high-1)/2.0+t_min << " ns ==> Delta = " << bkgd_t_range/2.0 << " ns" << endl;
    
    cout << " " << endl;
    
    cout << "/********** RATES **********/ " << endl;
    
    cout << endl << "Left dE - Top MCP:" << endl;
	cout << "Background per channel: " << bkgd_per_ch_left_top << endl;
	cout << "Delayed-neutron events: " << bdn_area_left_top << endl;
	cout << "Beta-only events      : " << beta_area_left_top << endl;
	
	cout << endl << "Left dE - Right MCP:" << endl;
	cout << "Background per channel: " << bkgd_per_ch_left_right << endl;
	cout << "Delayed-neutron events: " << bdn_area_left_right << endl;
	cout << "Beta-only events      : " << beta_area_left_right << endl;
    
	cout << endl << "Bottom dE - Top MCP:" << endl;
	cout << "Background per channel: " << bkgd_per_ch_bottom_top << endl;
	cout << "Delayed-neutron events: " << bdn_area_bottom_top << endl;
	cout << "Beta-only events      : " << beta_area_bottom_top << endl;
    
	cout << endl << "Bottom dE - Right MCP:" << endl;
	cout << "Background per channel: " << bkgd_per_ch_bottom_right << endl;
	cout << "Delayed-neutron events: " << bdn_area_bottom_right << endl;
	cout << "Beta-only events      : " << beta_area_bottom_right << endl;
	
	cout << endl << "TOTAL:" << endl;
	cout << "Delayed-neutron events: " << bdn_area_tot << endl;
	cout << "Beta-only events      : " << beta_area_tot << endl;
    
// Added 2014-06-17. Depends on bdn_sort_20140613 updates.
    TTree *meta = (TTree*)tfile->Get("metadata_Tree");
	Int_t	nRuns		= meta->GetEntries();
	TLeaf *nNetFastLeaf, *nNetSlowLeaf;
//	Float_t	nNetFast[] = {0, nNetFastLR = 0.0, nNetFastBT = 0.0, nNetFastBR = 0.0;
//	Float_t	nNetFastLT = 0.0, nNetFastLR = 0.0, nNetFastBT = 0.0, nNetFastBR = 0.0;
	Double_t	nNetFastLT = 0.0, nNetFastLR = 0.0, nNetFastBT = 0.0, nNetFastBR = 0.0;
	Double_t	nNetSlowLT = 0.0, nNetSlowLR = 0.0, nNetSlowBT = 0.0, nNetSlowBR = 0.0;
	Double_t	nNetFastTot = 0.0, nNetSlowTot = 0.0;
	for (Int_t iRun = 0; iRun < nRuns; iRun++) {
		meta->GetEntry(iRun);
		nNetFastLeaf = meta->GetLeaf("nNetFastCount");
		nNetFastLT	+= (Double_t)nNetFastLeaf->GetValue(0);
		nNetFastLR	+= (Double_t)nNetFastLeaf->GetValue(1);
		nNetFastBT	+= (Double_t)nNetFastLeaf->GetValue(2);
		nNetFastBR	+= (Double_t)nNetFastLeaf->GetValue(3);
		nNetSlowLeaf = meta->GetLeaf("nNetSlowCount");
		nNetSlowLT	+= (Double_t)nNetSlowLeaf->GetValue(0);
		nNetSlowLR	+= (Double_t)nNetSlowLeaf->GetValue(1);
		nNetSlowBT	+= (Double_t)nNetSlowLeaf->GetValue(2);
		nNetSlowBR	+= (Double_t)nNetSlowLeaf->GetValue(3);
	}
	nNetFastTot = nNetFastLT + nNetFastLR + nNetFastBT + nNetFastBR;
	nNetSlowTot = nNetSlowLT + nNetSlowLR + nNetSlowBT + nNetSlowBR;
	cout << endl;
	cout << "Recoils counted in event loop in sort code:" << endl;
	cout << "# runs in this file = " << nRuns				<< endl;
	printf("Combo       Fast       Slow\n");
	printf("LT       %10.2f      %10.2f\n", nNetFastLT, nNetSlowLT);
	printf("LR       %10.2f      %10.2f\n", nNetFastLR, nNetSlowLR);
	printf("BT       %10.2f      %10.2f\n", nNetFastBT, nNetSlowBT);
	printf("BR       %10.2f      %10.2f\n", nNetFastBR, nNetSlowBR);
	printf("Tot      %10.2f      %10.2f\n", nNetFastTot, nNetSlowTot);
    printf("\nrecoil_ion_rates done.\n\n");
	
}

void draw_slow_recoil_phds()
{
    
    printf("\ndraw_slow_recoil_phds started.");
	
	TFile *tfile = new TFile(filename);
	
	TCut L_beta = "-100<t_L_dE";
	TCut B_beta = "-100<t_B_dE";
	TCut R_mcp = "-100<t_R_mcp";
	TCut T_mcp = "-100<t_T_mcp";
	
	// TOF limits in ns
	Double_t tof1_lo = 1551.0; // slow ions
	Double_t tof1_hi = 10001.0;
	Double_t tof2_lo = 12000.0; // slow ion bkgd window
	Double_t tof2_hi = 20000.0;
	Double_t bkgd_ratio = (tof1_hi-tof1_lo)/(tof2_hi-tof2_lo);
	
	// Slow ion cuts
	char LT_tof1_string [200];
	char LR_tof1_string [200];
	char BT_tof1_string [200];
	char BR_tof1_string [200];
	char LT_tof2_string [200];
	char LR_tof2_string [200];
	char BT_tof2_string [200];
	char BR_tof2_string [200];
 	sprintf (LT_tof1_string, "event_good==1 && s_capt_state==0 && %d<t_L_dE && t_L_dE<%d && %d<a_L_dEsum && %d<t_T_mcp && %d<a_T_mcpSum && (%d < (t_T_mcp-t_L_dE) && (t_T_mcp-t_L_dE) < %d)", t_trigger_lo, t_trigger_hi, a_dE_lo, t_trigger_lo, a_mcp_lo, tof1_lo, tof1_hi);
 	sprintf (LT_tof2_string, "event_good==1 && s_capt_state==0 && %d<t_L_dE && t_L_dE<%d && %d<a_L_dEsum && %d<t_T_mcp && %d<a_T_mcpSum && (%d < (t_T_mcp-t_L_dE) && (t_T_mcp-t_L_dE) < %d)", t_trigger_lo, t_trigger_hi, a_dE_lo, t_trigger_lo, a_mcp_lo, tof2_lo, tof2_hi);
 	sprintf (LR_tof1_string, "event_good==1 && s_capt_state==0 && %d<t_L_dE && t_L_dE<%d && %d<a_L_dEsum && %d<t_R_mcp && %d<a_R_mcpSum && (%d < (t_R_mcp-t_L_dE) && (t_R_mcp-t_L_dE) < %d)", t_trigger_lo, t_trigger_hi, a_dE_lo, t_trigger_lo, a_mcp_lo, tof1_lo, tof1_hi);
 	sprintf (LR_tof2_string, "event_good==1 && s_capt_state==0 && %d<t_L_dE && t_L_dE<%d && %d<a_L_dEsum && %d<t_R_mcp && %d<a_R_mcpSum && (%d < (t_R_mcp-t_L_dE) && (t_R_mcp-t_L_dE) < %d)", t_trigger_lo, t_trigger_hi, a_dE_lo, t_trigger_lo, a_mcp_lo, tof2_lo, tof2_hi);
 	sprintf (BT_tof1_string, "event_good==1 && s_capt_state==0 && %d<t_B_dE && t_B_dE<%d && %d<a_B_dEsum && %d<t_T_mcp && %d<a_T_mcpSum && (%d < (t_T_mcp-t_B_dE) && (t_T_mcp-t_B_dE) < %d)", t_trigger_lo, t_trigger_hi, a_dE_lo, t_trigger_lo, a_mcp_lo, tof1_lo, tof1_hi);
 	sprintf (BT_tof2_string, "event_good==1 && s_capt_state==0 && %d<t_B_dE && t_B_dE<%d && %d<a_B_dEsum && %d<t_T_mcp && %d<a_T_mcpSum && (%d < (t_T_mcp-t_B_dE) && (t_T_mcp-t_B_dE) < %d)", t_trigger_lo, t_trigger_hi, a_dE_lo, t_trigger_lo, a_mcp_lo, tof2_lo, tof2_hi);
 	sprintf (BR_tof1_string, "event_good==1 && s_capt_state==0 && %d<t_B_dE && t_B_dE<%d && %d<a_B_dEsum && %d<t_R_mcp && %d<a_R_mcpSum && (%d < (t_R_mcp-t_B_dE) && (t_R_mcp-t_B_dE) < %d)", t_trigger_lo, t_trigger_hi, a_dE_lo, t_trigger_lo, a_mcp_lo, tof1_lo, tof1_hi);
 	sprintf (BR_tof2_string, "event_good==1 && s_capt_state==0 && %d<t_B_dE && t_B_dE<%d && %d<a_B_dEsum && %d<t_R_mcp && %d<a_R_mcpSum && (%d < (t_R_mcp-t_B_dE) && (t_R_mcp-t_B_dE) < %d)", t_trigger_lo, t_trigger_hi, a_dE_lo, t_trigger_lo, a_mcp_lo, tof2_lo, tof2_hi);
 	//sprintf (LT_tof1_string, "(%d < (t_T_mcp-t_L_dE) && (t_T_mcp-t_L_dE) < %d)", tof1_lo, tof1_hi);
 	//sprintf (LR_tof1_string, "(%d < (t_R_mcp-t_L_dE) && (t_R_mcp-t_L_dE) < %d)", tof1_lo, tof1_hi);
 	//sprintf (BT_tof1_string, "(%d < (t_T_mcp-t_B_dE) && (t_T_mcp-t_B_dE) < %d)", tof1_lo, tof1_hi);
 	//sprintf (BR_tof1_string, "(%d < (t_R_mcp-t_B_dE) && (t_R_mcp-t_B_dE) < %d)", tof1_lo, tof1_hi);
 	//sprintf (LT_tof2_string, "(%d < (t_T_mcp-t_L_dE) && (t_T_mcp-t_L_dE) < %d)", tof2_lo, tof2_hi);
 	//sprintf (LR_tof2_string, "(%d < (t_R_mcp-t_L_dE) && (t_R_mcp-t_L_dE) < %d)", tof2_lo, tof2_hi);
 	//sprintf (BT_tof2_string, "(%d < (t_T_mcp-t_B_dE) && (t_T_mcp-t_B_dE) < %d)", tof2_lo, tof2_hi);
 	//sprintf (BR_tof2_string, "(%d < (t_R_mcp-t_B_dE) && (t_R_mcp-t_B_dE) < %d)", tof2_lo, tof2_hi);	
	TCut LT_tof1 = LT_tof1_string;//"2500 < (t_T_mcp-t_L_dE) && (t_T_mcp-t_L_dE) < 6000";
    TCut LT_tof2 = LT_tof2_string;//"6001 < (t_T_mcp-t_L_dE) && (t_T_mcp-t_L_dE) < 9501";
    TCut LR_tof1 = LR_tof1_string;//"2500 < (t_R_mcp-t_L_dE) && (t_R_mcp-t_L_dE) < 6000";
    TCut LR_tof2 = LR_tof2_string;//"6001 < (t_R_mcp-t_L_dE) && (t_R_mcp-t_L_dE) < 9501";
    TCut BT_tof1 = BT_tof1_string;
    TCut BT_tof2 = BT_tof2_string;
    TCut BR_tof1 = BR_tof1_string;
    TCut BR_tof2 = BR_tof2_string;

	char range[50], title1[100], title2[100], title3[100];
	sprintf(range,"(%d < tof < %d)",tof1_lo,tof1_hi);
	sprintf(title1,"Top MCP Pulse Heights for Slow Recoils with %s, accidentals subtracted",range);
	sprintf(title2,"Right MCP Pulse Heights for Slow Recoils with %s, accidentals subtracted",range);
	
	TH1D *h_T_slow_all	= new TH1D("h_T_slow_all","Top MCP Pulse Heights for all events in slow recoil TOF window",2000,0,20000);
	TH1D *h_R_slow_all	= new TH1D("h_R_slow_all","Right MCP Pulse Heights for all events in slow recoil TOF window",2000,0,20000);
	TH1D *h_T_slow_acc	= new TH1D("h_T_slow_acc","Top MCP Pulse Heights for TOF accidentals",2000,0,20000);
	TH1D *h_R_slow_acc	= new TH1D("h_R_slow_acc","Right MCP Pulse Heights for TOF accidentals",2000,0,20000);
	TH1D *h_T_slow_net	= new TH1D("h_T_slow_net",title1,2000,0,20000);
	TH1D *h_R_slow_net	= new TH1D("h_R_slow_net",title2,2000,0,20000);
	//TH1D *h_slow_net	= new TH1D("h_slow_net","All MCP Pulse Heights for Slow Recoil Ions (accidentals subtracted)",2000,0,20000);
	
    beta_recoil_tree->Project("h_T_slow_all","a_T_mcpSum", LT_tof1 || BT_tof1);
	beta_recoil_tree->Project("h_R_slow_all","a_R_mcpSum", LR_tof1 || BR_tof1);
    beta_recoil_tree->Project("h_T_slow_acc","a_T_mcpSum", LT_tof2 || BT_tof2);
    beta_recoil_tree->Project("h_R_slow_acc","a_R_mcpSum", LR_tof2 || BR_tof2);
    
    // Make net plots by subtracting accidentals
	h_T_slow_net = h_T_slow_net->Add(h_T_slow_all,1.0);
	h_T_slow_net = h_T_slow_net->Add(h_T_slow_acc,-1.0*bkgd_ratio);
	h_R_slow_net = h_R_slow_net->Add(h_R_slow_all,1.0);
	h_R_slow_net = h_R_slow_net->Add(h_R_slow_acc,-1.0*bkgd_ratio);
	
	// Add both T and R net plots to get overall net plot
	//h_slow_net = h_slow_net->Add(h_T_slow_net,1.0);
	//h_slow_net = h_slow_net->Add(h_R_slow_net,1.0);
	
	TCanvas *c_slow_recoils_phds = new TCanvas("c_slow_recoils_phds", "Slow Recoil Ion Pulse Height Distributions", 900, 900);
	c_slow_recoils_phds->Divide(1,2);
	c_slow_recoils_phds->cd(1);
	h_T_slow_net->Draw();
	c_slow_recoils_phds->cd(2);
	h_R_slow_net->Draw();
	
	//TCanvas *c_slow_recoils_phd = new TCanvas("c_slow_recoils_sum_phd", "Slow Recoil Ion Pulse Height Distribution", 900, 600);
	//h_slow_net->Draw();
	
	printf("\ndraw_slow_recoil_phds done.\n\n");

}

void draw_fast_recoil_phds()
{
    
    printf("\ndraw_fast_recoil_phds started.");
	
	TFile *tfile		= new TFile(filename);
	
	TCut L_beta = "-100<t_L_dE";
	TCut B_beta = "-100<t_B_dE";
	TCut R_mcp = "-100<t_R_mcp";
	TCut T_mcp = "-100<t_T_mcp";
	
	// TOF limits in ns
	Double_t tof1_lo = 230; // fast ions
	Double_t tof1_hi = 1550;
	Double_t tof2_lo = 12000; // fast ion bkgd window
	Double_t tof2_hi = 20000;
	Double_t bkgd_ratio = (tof1_hi-tof1_lo)/(tof2_hi-tof2_lo);
	
	// fast ion cuts
	
 	char LT_tof1_string [200];
	char LR_tof1_string [200];
	char BT_tof1_string [200];
	char BR_tof1_string [200];
	char LT_tof2_string [200];
	char LR_tof2_string [200];
	char BT_tof2_string [200];
	char BR_tof2_string [200];
 	sprintf (LT_tof1_string, "event_good==1 && s_capt_state==0 && %d<t_L_dE && t_L_dE<%d && %d<a_L_dEsum && %d<t_T_mcp && %d<a_T_mcpSum && (%d < (t_T_mcp-t_L_dE) && (t_T_mcp-t_L_dE) < %d)", t_trigger_lo, t_trigger_hi, a_dE_lo, t_trigger_lo, a_mcp_lo, tof1_lo, tof1_hi);
 	sprintf (LT_tof2_string, "event_good==1 && s_capt_state==0 && %d<t_L_dE && t_L_dE<%d && %d<a_L_dEsum && %d<t_T_mcp && %d<a_T_mcpSum && (%d < (t_T_mcp-t_L_dE) && (t_T_mcp-t_L_dE) < %d)", t_trigger_lo, t_trigger_hi, a_dE_lo, t_trigger_lo, a_mcp_lo, tof2_lo, tof2_hi);
 	sprintf (LR_tof1_string, "event_good==1 && s_capt_state==0 && %d<t_L_dE && t_L_dE<%d && %d<a_L_dEsum && %d<t_R_mcp && %d<a_R_mcpSum && (%d < (t_R_mcp-t_L_dE) && (t_R_mcp-t_L_dE) < %d)", t_trigger_lo, t_trigger_hi, a_dE_lo, t_trigger_lo, a_mcp_lo, tof1_lo, tof1_hi);
 	sprintf (LR_tof2_string, "event_good==1 && s_capt_state==0 && %d<t_L_dE && t_L_dE<%d && %d<a_L_dEsum && %d<t_R_mcp && %d<a_R_mcpSum && (%d < (t_R_mcp-t_L_dE) && (t_R_mcp-t_L_dE) < %d)", t_trigger_lo, t_trigger_hi, a_dE_lo, t_trigger_lo, a_mcp_lo, tof2_lo, tof2_hi);
 	sprintf (BT_tof1_string, "event_good==1 && s_capt_state==0 && %d<t_B_dE && t_B_dE<%d && %d<a_B_dEsum && %d<t_T_mcp && %d<a_T_mcpSum && (%d < (t_T_mcp-t_B_dE) && (t_T_mcp-t_B_dE) < %d)", t_trigger_lo, t_trigger_hi, a_dE_lo, t_trigger_lo, a_mcp_lo, tof1_lo, tof1_hi);
 	sprintf (BT_tof2_string, "event_good==1 && s_capt_state==0 && %d<t_B_dE && t_B_dE<%d && %d<a_B_dEsum && %d<t_T_mcp && %d<a_T_mcpSum && (%d < (t_T_mcp-t_B_dE) && (t_T_mcp-t_B_dE) < %d)", t_trigger_lo, t_trigger_hi, a_dE_lo, t_trigger_lo, a_mcp_lo, tof2_lo, tof2_hi);
 	sprintf (BR_tof1_string, "event_good==1 && s_capt_state==0 && %d<t_B_dE && t_B_dE<%d && %d<a_B_dEsum && %d<t_R_mcp && %d<a_R_mcpSum && (%d < (t_R_mcp-t_B_dE) && (t_R_mcp-t_B_dE) < %d)", t_trigger_lo, t_trigger_hi, a_dE_lo, t_trigger_lo, a_mcp_lo, tof1_lo, tof1_hi);
 	sprintf (BR_tof2_string, "event_good==1 && s_capt_state==0 && %d<t_B_dE && t_B_dE<%d && %d<a_B_dEsum && %d<t_R_mcp && %d<a_R_mcpSum && (%d < (t_R_mcp-t_B_dE) && (t_R_mcp-t_B_dE) < %d)", t_trigger_lo, t_trigger_hi, a_dE_lo, t_trigger_lo, a_mcp_lo, tof2_lo, tof2_hi);
 	//sprintf (LT_tof1_string, "(%d < (t_T_mcp-t_L_dE) && (t_T_mcp-t_L_dE) < %d)", tof1_lo, tof1_hi);
 	//sprintf (LR_tof1_string, "(%d < (t_R_mcp-t_L_dE) && (t_R_mcp-t_L_dE) < %d)", tof1_lo, tof1_hi);
 	//sprintf (BT_tof1_string, "(%d < (t_T_mcp-t_B_dE) && (t_T_mcp-t_B_dE) < %d)", tof1_lo, tof1_hi);
 	//sprintf (BR_tof1_string, "(%d < (t_R_mcp-t_B_dE) && (t_R_mcp-t_B_dE) < %d)", tof1_lo, tof1_hi);
 	//sprintf (LT_tof2_string, "(%d < (t_T_mcp-t_L_dE) && (t_T_mcp-t_L_dE) < %d)", tof2_lo, tof2_hi);
 	//sprintf (LR_tof2_string, "(%d < (t_R_mcp-t_L_dE) && (t_R_mcp-t_L_dE) < %d)", tof2_lo, tof2_hi);
 	//sprintf (BT_tof2_string, "(%d < (t_T_mcp-t_B_dE) && (t_T_mcp-t_B_dE) < %d)", tof2_lo, tof2_hi);
 	//sprintf (BR_tof2_string, "(%d < (t_R_mcp-t_B_dE) && (t_R_mcp-t_B_dE) < %d)", tof2_lo, tof2_hi);	
	TCut LT_tof1 = LT_tof1_string;//"2500 < (t_T_mcp-t_L_dE) && (t_T_mcp-t_L_dE) < 6000";
    TCut LT_tof2 = LT_tof2_string;//"6001 < (t_T_mcp-t_L_dE) && (t_T_mcp-t_L_dE) < 9501";
    TCut LR_tof1 = LR_tof1_string;//"2500 < (t_R_mcp-t_L_dE) && (t_R_mcp-t_L_dE) < 6000";
    TCut LR_tof2 = LR_tof2_string;//"6001 < (t_R_mcp-t_L_dE) && (t_R_mcp-t_L_dE) < 9501";
    TCut BT_tof1 = BT_tof1_string;
    TCut BT_tof2 = BT_tof2_string;
    TCut BR_tof1 = BR_tof1_string;
    TCut BR_tof2 = BR_tof2_string;
	
	char range[50], title1[100], title2[100], title3[100];
	sprintf(range,"(%d < tof < %d)",tof1_lo,tof1_hi);
	sprintf(title1,"Top MCP Pulse Heights for Fast Recoils with %s, accidentals subtracted",range);
	sprintf(title2,"Right MCP Pulse Heights for Fast Recoils with %s, accidentals subtracted",range);
	
	TH1D *h_T_fast_all	= new TH1D("h_T_fast_all","Top MCP Pulse Heights for all events in fast recoil TOF window",2000,0,20000);
	TH1D *h_R_fast_all	= new TH1D("h_R_fast_all","Right MCP Pulse Heights for all events in fast recoil TOF window",2000,0,20000);
	TH1D *h_T_fast_acc	= new TH1D("h_T_fast_acc","Top MCP Pulse Heights for TOF accidentals",2000,0,20000);
	TH1D *h_R_fast_acc	= new TH1D("h_R_fast_acc","Right MCP Pulse Heights for TOF accidentals",2000,0,20000);
	TH1D *h_T_fast_net	= new TH1D("h_T_fast_net",title1,2000,0,20000);//"Top MCP Pulse Heights for fast Recoil Ions (accidentals subtracted)",2000,0,20000);
	TH1D *h_R_fast_net	= new TH1D("h_R_fast_net",title2,2000,0,20000);//"Right MCP Pulse Heights for fast Recoil Ions (accidentals subtracted)",2000,0,20000);
	//TH1D *h_fast_net	= new TH1D("h_fast_net","All MCP Pulse Heights for fast Recoil Ions (accidentals subtracted)",2000,0,20000);
	
    beta_recoil_tree->Project("h_T_fast_all","a_T_mcpSum", LT_tof1 || BT_tof1);
	beta_recoil_tree->Project("h_R_fast_all","a_R_mcpSum", LR_tof1 || BR_tof1);
    beta_recoil_tree->Project("h_T_fast_acc","a_T_mcpSum", LT_tof2 || BT_tof2);
    beta_recoil_tree->Project("h_R_fast_acc","a_R_mcpSum", LR_tof2 || BR_tof2);
    
    // Make net plots by subtracting accidentals
	h_T_fast_net = h_T_fast_net->Add(h_T_fast_all,1.0);
	h_T_fast_net = h_T_fast_net->Add(h_T_fast_acc,-1.0*bkgd_ratio);
	h_R_fast_net = h_R_fast_net->Add(h_R_fast_all,1.0);
	h_R_fast_net = h_R_fast_net->Add(h_R_fast_acc,-1.0*bkgd_ratio);
	
	// Add both T and R net plots to get overall net plot
	//h_fast_net = h_fast_net->Add(h_T_fast_net,1.0);
	//h_fast_net = h_fast_net->Add(h_R_fast_net,1.0);
	
	TCanvas *c_fast_recoils_phds = new TCanvas("c_fast_recoils_phds", "Fast Recoil Ion Pulse Height Distributions", 900, 900);
	c_fast_recoils_phds->Divide(1,2);
	c_fast_recoils_phds->cd(1);
	h_T_fast_net->Draw();
	c_fast_recoils_phds->cd(2);
	h_R_fast_net->Draw();
	
	//TCanvas *c_fast_recoils_phd = new TCanvas("c_fast_recoils_sum_phd", "Fast Recoil Ion Pulse Height Distribution", 900, 600);
	//h_fast_net->Draw();
	
	printf("\ndraw_fast_recoil_phds done.\n\n");

}

void draw_betas_vs_cycle_time()
{
    
    printf("\ndraw_betas_vs_cycle_time started.");
	
	TFile *tfile		= new TFile(filename);
	
	TCanvas *c_betas_vs_cycle_time = new TCanvas("c_betas_vs_cycle_time", "Betas vs Cycle Time", 945, 900);
	c_betas_vs_cycle_time->Divide(1,2);
	c_betas_vs_cycle_time->cd(1);
	h_L_betas_vs_cycle_time->Draw();
	c_betas_vs_cycle_time->cd(2);
	h_B_betas_vs_cycle_time->Draw();
	
	TCanvas *c_all_betas_vs_cycle_time = new TCanvas("c_all_betas_vs_cycle_time", "Betas vs Cycle Time", 945, 600);
	h_betas_vs_cycle_time->Draw();
	
	printf("\ndraw_betas_vs_cycle_time done.\n\n");
	
}

void fit_a_gamma_line(char* histo_name, Double_t centroid)
{
    printf("\nfit_a_gamma_line started.");
	
	TFile *tfile = new TFile(filename);
	TH1I* h = (TH1I*)tfile->Get(histo_name);
/*	if (histo_name=="137i_243keV_line") {
		TH1I* ha_bg_LT_137i_Te = new TH1I("ha_bg_LT_137i_Te","ADC: (BACKGROUND) Top Ge w/ Left dE coincident in First 10 sec of Background Cycle",4096,0,4096);
		TH1I* ha_bg_LR_137i_Te = new TH1I("ha_bg_LR_137i_Te","ADC: (BACKGROUND) Top Ge w/ Right dE coincident in First 10 sec of Background Cycle",4096,0,4096);
		TH1I* ha_bg_BT_137i_Te = new TH1I("ha_bg_BT_137i_Te","ADC: (BACKGROUND) Bottom Ge w/ Left dE coincident in First 10 sec of Background Cycle",4096,0,4096);
		TH1I* ha_bg_BR_137i_Te = new TH1I("ha_bg_BR_137i_Te","ADC: (BACKGROUND) Bottom Ge w/ Right dE coincident in First 10 sec of Background Cycle",4096,0,4096);
		char LT_string [200];
		char LR_string [200];
		char BT_string [200];
		char BR_string [200];
 		sprintf (LT_string, "s_ms_since_eject<10000 && event_good==1 && s_capt_state==1 && %d<t_L_dE && %d<a_L_dEsum && 0 < (t_T_ge-t_L_dE) && (t_T_ge-t_L_dE) < 1000", t_trigger_lo, a_dE_lo);
		sprintf (LR_string, "s_ms_since_eject<10000 && event_good==1 && s_capt_state==1 && %d<t_L_dE && %d<a_L_dEsum && 0 < (t_R_ge-t_L_dE) && (t_R_ge-t_L_dE) < 1000", t_trigger_lo, a_dE_lo);
		sprintf (BT_string, "s_ms_since_eject<10000 && event_good==1 && s_capt_state==1 && %d<t_B_dE && %d<a_B_dEsum && 0 < (t_T_ge-t_B_dE) && (t_T_ge-t_B_dE) < 1000", t_trigger_lo, a_dE_lo);
		sprintf (BR_string, "s_ms_since_eject<10000 && event_good==1 && s_capt_state==1 && %d<t_B_dE && %d<a_B_dEsum && 0 < (t_R_ge-t_B_dE) && (t_R_ge-t_B_dE) < 1000", t_trigger_lo, a_dE_lo);
		
		printf(LT_string);
		TCut LT_cut = LT_string;
		TCut LR_cut = LR_string;
		TCut BT_cut = BT_string;
		TCut BR_cut = BR_string;
		beta_gamma_tree->Project("ha_bg_LT_137i_Te","a_T_ge",LT_cut);
		beta_gamma_tree->Project("ha_bg_LR_137i_Te","a_R_ge",LR_cut);
		beta_gamma_tree->Project("ha_bg_BT_137i_Te","a_T_ge",BT_cut);
		beta_gamma_tree->Project("ha_bg_BR_137i_Te","a_R_ge",BR_cut);
		TH1I *h = (TH1I*)ha_bg_LT_137i_Te->Clone("ha_bg_LT_137i_Te");
	}
	else {
		TH1I* h = (TH1I*)tfile->Get(histo_name);
	}
*/	
	Double_t xMin = centroid-15.0;
	Double_t xMax = centroid+15.0;
	TF1 *f1 = new TF1("f1","pol1(0)+gaus(2)",xMin,xMax);
    //f1->SetParLimits(1,41.0,51.0);
    f1->SetParNames(	"Intercept",	"Slope",	"Amplitude",	"Mean",		"Sigma");//,	"A",	"k",	"phi");
    f1->SetParameters(	10.0,			0.0,		0.0,		centroid, 		0.5);//,		10.0,	24.0,	0.0);
//    f1->FixParameter(3,299.1);
//    f1->FixParameter(4,2.955);
    
    TF1 *f2 = new TF1("f2","pol1(0)+gaus(2)+gaus(5)",xMin,xMax);
    //f2->SetParLimits(1,41.0,51.0);
    f2->SetParNames(	"Intercept",	"Slope",	"Amplitude",	"Mean",		"Sigma", 	"Amplitude2",	"Mean2",		"Sigma2");
    f2->SetParameters(	0.0,			0.0,		10.0,		centroid, 		2.0,		10.0,			centroid+8.0,	2.0);
    
    TF1 *f_bkgd = new TF1("f_bkgd","pol1(0)",xMin,xMax);
    
    TF1 *fn = (TF1*)f1;
	TFitResultPtr frp = h->Fit(fn,"MIRLL");
	
	TCanvas *c_all_fit_a_gamma_line = new TCanvas("c_all_fit_a_gamma_line", "Ge ADC data", 945, 600);
	h->GetXaxis()->SetRangeUser(xMin,xMax);
	h->Draw("E");
	
	Double_t intercept = fn->GetParameter(0);
	Double_t slope = fn->GetParameter(1);
	Double_t cent = fn->GetParameter(3);
	Double_t err = fn->GetParError(3);
	Double_t cent2 = fn->GetParameter(6);
	Double_t err2 = fn->GetParError(6);
	printf("Centroid 1 = ch %10.6f +/- %10.6f\nCentroid 2 = ch %10.6f +/- %10.6f",cent,err,cent2,err2);
	
	f_bkgd->SetParameter(0, intercept);
	f_bkgd->SetParameter(1, slope);
	Double_t bkgd_integral = f_bkgd->Integral(xMin,xMax);
	Double_t c0_err = fn->GetParError(0);
	Double_t c1_err = fn->GetParError(1);
	Double_t bkgd_integral_error = TMath::Sqrt( TMath::Power((xMax-xMin)*c0_err,2.0) + TMath::Power(0.5*(xMax-xMin)*(xMax-xMin)*c1_err,2.0) );
	
	Double_t fn_integral = fn->Integral(xMin,xMax);
	Double_t fn_integral_error = fn->IntegralError( xMin, xMax, frp->GetParams(), frp->GetCovarianceMatrix()->GetMatrixArray() );
	Double_t net_area = fn_integral - bkgd_integral;
	Double_t net_area_error = TMath::Sqrt( TMath::Power(fn_integral_error,2.0) + TMath::Power(bkgd_integral_error,2.0) );
	printf("\n\nFit area = %10.6f+/-%10.6f\nBkgd area = %10.6f+/-%10.6f\nNet area = %10.6f+/-%10.6f",fn_integral,fn_integral_error,bkgd_integral,bkgd_integral_error,net_area,net_area_error);
	
	printf("\nfit_a_gamma_line done.\n\n");
}

void draw_tof_with_E_but_no_dE ()
{
    
    printf("\ndraw_tof_with_E_but_no_dE started.");
	
	TFile *tfile		= new TFile(filename);
	
	TCut L_beta = "-100<t_L_dE";
	TCut B_beta = "-100<t_B_dE";
	TCut R_mcp = "-100<t_R_mcp";
	TCut T_mcp = "-100<t_T_mcp";
	
	// TOF limits in ns
	Int_t tof1_lo = 230; // fast ions
	Int_t tof1_hi = 1550;
	Int_t tof2_lo = 15230; // fast ion bkgd window
	Int_t tof2_hi = 16550;
	
	// TOF cuts
 	char LT_string[200], LR_string[200], BT_string[200], BR_string[200];
 	sprintf (LT_string, "%d<t_L_E && event_good==1 && s_capt_state==0 && t_L_dE<%d && %d<a_L_dEsum && %d<t_T_mcp && %d<a_T_mcpSum", t_trigger_lo, t_trigger_lo, a_dE_lo, t_trigger_lo, a_mcp_lo, tof1_lo, tof1_hi);
 	sprintf (LR_string, "%d<t_L_E && event_good==1 && s_capt_state==0 && t_L_dE<%d && %d<a_L_dEsum && %d<t_R_mcp && %d<a_R_mcpSum", t_trigger_lo, t_trigger_lo, a_dE_lo, t_trigger_lo, a_mcp_lo, tof1_lo, tof1_hi);
 	sprintf (BT_string, "%d<t_B_E && event_good==1 && s_capt_state==0 && t_B_dE<%d && %d<a_B_dEsum && %d<t_T_mcp && %d<a_T_mcpSum", t_trigger_lo, t_trigger_lo, a_dE_lo, t_trigger_lo, a_mcp_lo, tof1_lo, tof1_hi);
 	sprintf (BR_string, "%d<t_B_E && event_good==1 && s_capt_state==0 && t_B_dE<%d && %d<a_B_dEsum && %d<t_R_mcp && %d<a_R_mcpSum", t_trigger_lo, t_trigger_lo, a_dE_lo, t_trigger_lo, a_mcp_lo, tof1_lo, tof1_hi);
 	
 	char LT_formula[200], LR_formula[200], BT_formula[200], BR_formula[200];
 	sprintf (LT_formula, "t_T_mcp-t_L_E-%f",LT_zeroTime_E[0]);
 	sprintf (LR_formula, "t_R_mcp-t_L_E-%f",LR_zeroTime_E[0]);
 	sprintf (BT_formula, "t_T_mcp-t_B_E-%f",BT_zeroTime_E[0]);
 	sprintf (BR_formula, "t_R_mcp-t_B_E-%f",BR_zeroTime_E[0]);
 	
 	printf(LT_formula);
 	
	TCut LT_cuts = LT_string;
    TCut LR_cuts = LR_string;
    TCut BT_cuts = BT_string;
    TCut BR_cuts = BR_string;
	
	const Double_t TOFMin	= -1000.0; // ns
	const Double_t TOFMax	= 25500.0; // ns
	const Int_t TOFBins		= 26500; // one bin per ns
	
	TH1I *h_E_tof_LT_no_dE	= new TH1I("h_E_tof_LT_no_dE","Left-Top TOF (ns) with plastic E as start and no hit in dE",TOFBins,TOFMin,TOFMax);
	TH1I *h_E_tof_LR_no_dE	= new TH1I("h_E_tof_LR_no_dE","Left-Right TOF (ns) with plastic E as start and no hit in dE",TOFBins,TOFMin,TOFMax);
	TH1I *h_E_tof_BT_no_dE	= new TH1I("h_E_tof_BT_no_dE","Bottom-Top TOF (ns) with plastic E as start and no hit in dE",TOFBins,TOFMin,TOFMax);
	TH1I *h_E_tof_BR_no_dE	= new TH1I("h_E_tof_BR_no_dE","Bottom-Right TOF (ns) with plastic E as start and no hit in dE",TOFBins,TOFMin,TOFMax);
	TH1I *h_E_tof_no_dE		= new TH1I("h_E_tof_no_dE","All combos TOF (ns) with plastic E as start and no hit in dE",TOFBins,TOFMin,TOFMax);
	
    beta_recoil_tree->Project("h_E_tof_LT_no_dE", LT_formula, LT_cuts);
	beta_recoil_tree->Project("h_E_tof_LR_no_dE", LR_formula, LR_cuts);
    beta_recoil_tree->Project("h_E_tof_BT_no_dE", BT_formula, BT_cuts);
    beta_recoil_tree->Project("h_E_tof_BR_no_dE", BR_formula, BR_cuts);
    
    // Make net plots by subtracting accidentals
	h_E_tof_no_dE = h_E_tof_no_dE->Add(h_E_tof_LT_no_dE,1.0);
	h_E_tof_no_dE = h_E_tof_no_dE->Add(h_E_tof_LR_no_dE,1.0);
	h_E_tof_no_dE = h_E_tof_no_dE->Add(h_E_tof_BT_no_dE,1.0);
	h_E_tof_no_dE = h_E_tof_no_dE->Add(h_E_tof_BR_no_dE,1.0);
	
	TCanvas *c_E_MCP_tof_spectra_no_dE = new TCanvas("c_E_MCP_tof_spectra_no_dE","TOF Spectra (E-MCP) with no dE",1600,1000);
	
	c_E_MCP_tof_spectra_no_dE->Divide(2,2);
	
	c_E_MCP_tof_spectra_no_dE->cd(1);
	c_E_MCP_tof_spectra_no_dE_1->SetLogy();
	h_E_tof_LT_no_dE->Draw();
	
	c_E_MCP_tof_spectra_no_dE->cd(2);
	c_E_MCP_tof_spectra_no_dE_2->SetLogy();
	h_E_tof_LR_no_dE->Draw();
	
	c_E_MCP_tof_spectra_no_dE->cd(3);
	c_E_MCP_tof_spectra_no_dE_3->SetLogy();
	h_E_tof_BT_no_dE->Draw();
	
	c_E_MCP_tof_spectra_no_dE->cd(4);
	c_E_MCP_tof_spectra_no_dE_4->SetLogy();
	h_E_tof_BR_no_dE->Draw();
	
	TCanvas *c_E_MCP_tof_spectrum_no_dE = new TCanvas("c_E_MCP_tof_spectrum_no_dE","TOF Spectrum (All dE-MCP combos) with no dE",800,500);
    c_E_MCP_tof_spectrum_no_dE->SetLogy();
    h_E_tof_no_dE->Rebin(100);
    h_tof->Rebin(100);
    h_E_tof_no_dE->Draw();
    h_tof->Draw("SAME");
	
	printf("\ndraw_tof_with_E_but_no_dE done.\n\n");

}

void check_deadtime_correction ()
{
	printf("\ncheck_deadtime_correction started.");
	
	TFile *tfile		= new TFile(filename);
	
//	TF1 *fn = new TF1("fn","[0]+[1]*exp(-[2]*(x-[3]))",101001.0,101015.0);
//	fn->SetParameters(200.0, 6000.0, 5.0, 101001.0);
//	h_all_vs_cycle_time->Fit("fn");
	
	TCanvas *c_all_vs_cycle_time	= new TCanvas("c_all_vs_cycle_time","All triggers vs cycle time in ms",945,600);
	h_all_vs_cycle_time->Draw();
	h_all_vs_cycle_time_observed->Draw("E SAME");
	h_all_vs_cycle_time_observed->SetLineColor(kRed);
	h_all_vs_cycle_time->GetXaxis()->SetRangeUser(100991,101021);
	h_all_vs_cycle_time_observed->GetXaxis()->SetRangeUser(100991,101021);
	
	TLegend *leg_1 = new TLegend(0.78, 0.64, 0.98, 0.775);
	leg_1->AddEntry(h_all_vs_cycle_time,"corrected");
	leg_1->AddEntry(h_all_vs_cycle_time_observed,"uncorrected");
	leg_1->SetFillColor(0);
	leg_1->Draw();
	
	TCanvas *c_deadtime_correction_factors	= new TCanvas("c_deadtime_correction_factors","Deadtime correction factor vs cycle time in ms",945,600);
	h_deadtime_correction_vs_cycle_time->SetTitle("1/(fraction of events lost to deadtime), per ms of cycle");
	h_deadtime_correction_vs_cycle_time->Draw();
	h_deadtime_correction_vs_cycle_time->GetXaxis()->SetRangeUser(100991,101021);
	
	TCanvas *c_all_vs_rf_phase	= new TCanvas("c_all_vs_rf_phase","All triggers vs (RF Phase / 2 Pi)",945,600);
	h_all_vs_rf_phase->Draw();
	h_all_vs_rf_phase_observed->Draw("E SAME");
	h_all_vs_rf_phase_observed->SetLineColor(kRed);
//	h_all_vs_rf_phase->GetXaxis()->SetRangeUser(100991,101021);
//	h_all_vs_rf_phase_observed->GetXaxis()->SetRangeUser(100991,101021);
	
	printf("\ncheck_deadtime_correction done.\n\n");
}

void tdc_draw_dE_mcp_tof_spectra_with_E()
{
	
	printf("\ndraw_dE-MCP_tof_spectra_with_E started.");
	
	TFile *tfile		= new TFile(filename);
	
	TH1I *h_tof_LT_with_E	= new TH1I("h_tof_LT_with_E","LT: TOF with an E hit required",TOFBins,TOFMin,TOFMax);
	TH1I *h_tof_LR_with_E	= new TH1I("h_tof_LR_with_E","LR: TOF with an E hit required",TOFBins,TOFMin,TOFMax);
	TH1I *h_tof_BT_with_E	= new TH1I("h_tof_BT_with_E","BT: TOF with an E hit required",TOFBins,TOFMin,TOFMax);
	TH1I *h_tof_BR_with_E	= new TH1I("h_tof_BR_with_E","BR: TOF with an E hit required",TOFBins,TOFMin,TOFMax);
	TH1I *h_tof_with_E		= new TH1I("h_tof_with_E","All combos: TOF with an E hit required",TOFBins,TOFMin,TOFMax);
	TH1I *h_tof_LT_with_high_E	= new TH1I("h_tof_LT_with_high_E","LT: TOF with an E hit required above ~3 MeV",TOFBins,TOFMin,TOFMax);
	TH1I *h_tof_LR_with_high_E	= new TH1I("h_tof_LR_with_high_E","LR: TOF with an E hit required above ~3 MeV",TOFBins,TOFMin,TOFMax);
	TH1I *h_tof_BT_with_high_E	= new TH1I("h_tof_BT_with_high_E","BT: TOF with an E hit required above ~3 MeV",TOFBins,TOFMin,TOFMax);
	TH1I *h_tof_BR_with_high_E	= new TH1I("h_tof_BR_with_high_E","BR: TOF with an E hit required above ~3 MeV",TOFBins,TOFMin,TOFMax);
	TH1I *h_tof_with_high_E		= new TH1I("h_tof_with_high_E","All combos: TOF with an E hit required above ~3 MeV",TOFBins,TOFMin,TOFMax);
	
	char LT_string [200];
	char LR_string [200];
	char BT_string [200];
	char BR_string [200];
//  h_tof cut is         event_good==1 && s_capt_state==0 && t_dE_lo<bdn.t_L_dE && bdn.t_L_dE<t_dE_hi && a_dE_lo<bdn.a_L_dEsum && t_mcp_lo<t_T_mcp && a_mcp_lo<bdn.a_T_mcpSum
 	sprintf (LT_string, "event_good==1 && s_capt_state==0 && %d<t_L_dE && t_L_dE<%d && %d<a_L_dEsum && %d<t_T_mcp && %d<a_T_mcpSum && %d<t_L_E && t_L_E<%d && %d<a_L_E", t_trigger_lo, t_trigger_hi, a_dE_lo, t_trigger_lo, a_mcp_lo, t_trigger_lo, t_trigger_hi, a_E_lo);
 	sprintf (LR_string, "event_good==1 && s_capt_state==0 && %d<t_L_dE && t_L_dE<%d && %d<a_L_dEsum && %d<t_R_mcp && %d<a_R_mcpSum && %d<t_L_E && t_L_E<%d && %d<a_L_E", t_trigger_lo, t_trigger_hi, a_dE_lo, t_trigger_lo, a_mcp_lo, t_trigger_lo, t_trigger_hi, a_E_lo);
 	sprintf (BT_string, "event_good==1 && s_capt_state==0 && %d<t_B_dE && t_B_dE<%d && %d<a_B_dEsum && %d<t_T_mcp && %d<a_T_mcpSum && %d<t_B_E && t_B_E<%d && %d<a_B_E", t_trigger_lo, t_trigger_hi, a_dE_lo, t_trigger_lo, a_mcp_lo, t_trigger_lo, t_trigger_hi, a_E_lo);
 	sprintf (BR_string, "event_good==1 && s_capt_state==0 && %d<t_B_dE && t_B_dE<%d && %d<a_B_dEsum && %d<t_R_mcp && %d<a_R_mcpSum && %d<t_B_E && t_B_E<%d && %d<a_B_E", t_trigger_lo, t_trigger_hi, a_dE_lo, t_trigger_lo, a_mcp_lo, t_trigger_lo, t_trigger_hi, a_E_lo);
	TCut LT_cut = LT_string;
	TCut LR_cut = LR_string;
	TCut BT_cut = BT_string;
	TCut BR_cut = BR_string;
    beta_recoil_tree->Project("h_tof_LT_with_E","tof_LT", LT_cut);
	beta_recoil_tree->Project("h_tof_LR_with_E","tof_LR", LR_cut);
    beta_recoil_tree->Project("h_tof_BT_with_E","tof_BT", BT_cut);
    beta_recoil_tree->Project("h_tof_BR_with_E","tof_BR", BR_cut);
    h_tof_with_E = h_tof_with_E->Add(h_tof_LT_with_E,1.0);
	h_tof_with_E = h_tof_with_E->Add(h_tof_LR_with_E,1.0);
	h_tof_with_E = h_tof_with_E->Add(h_tof_BT_with_E,1.0);
	h_tof_with_E = h_tof_with_E->Add(h_tof_BR_with_E,1.0);
	beta_recoil_tree->Project("h_tof_LT_with_high_E","tof_LT", LT_cut && "1000<a_L_E");
	beta_recoil_tree->Project("h_tof_LR_with_high_E","tof_LR", LR_cut && "1000<a_L_E");
    beta_recoil_tree->Project("h_tof_BT_with_high_E","tof_BT", BT_cut && "1000<a_B_E");
    beta_recoil_tree->Project("h_tof_BR_with_high_E","tof_BR", BR_cut && "1000<a_B_E");
    h_tof_with_high_E = h_tof_with_high_E->Add(h_tof_LT_with_high_E,1.0);
	h_tof_with_high_E = h_tof_with_high_E->Add(h_tof_LR_with_high_E,1.0);
	h_tof_with_high_E = h_tof_with_high_E->Add(h_tof_BT_with_high_E,1.0);
	h_tof_with_high_E = h_tof_with_high_E->Add(h_tof_BR_with_high_E,1.0);
	
	TCanvas *c_dE_MCP_tof_spectra_with_E = new TCanvas("c_dE_MCP_tof_spectra_with_E","TOF Spectra (dE-MCP) with E hit required",1600,1000);
	c_dE_MCP_tof_spectra_with_E->Divide(2,2);
	c_dE_MCP_tof_spectra_with_E->cd(1);
	c_dE_MCP_tof_spectra_with_E_1->SetLogy();
	h_tof_LT_with_E->Draw();
	c_dE_MCP_tof_spectra_with_E->cd(2);
	c_dE_MCP_tof_spectra_with_E_2->SetLogy();
	h_tof_LR_with_E->Draw();
	c_dE_MCP_tof_spectra_with_E->cd(3);
	c_dE_MCP_tof_spectra_with_E_3->SetLogy();
	h_tof_BT_with_E->Draw();
	c_dE_MCP_tof_spectra_with_E->cd(4);
	c_dE_MCP_tof_spectra_with_E_4->SetLogy();
	h_tof_BR_with_E->Draw();
	TCanvas *c_dE_MCP_tof_sum_spectrum_with_E = new TCanvas("c_dE_MCP_tof_sum_spectrum_with_E","TOF Spectrum (All dE-MCP combos) with E hit required",945,600);
    c_dE_MCP_tof_sum_spectrum_with_E->SetLogy();
    h_tof_with_E->Draw();
    h_tof_with_E->SetLineColor(kRed);
    h_tof_with_high_E->Draw("SAME");
    h_tof_with_high_E->SetLineColor(kOrange);
    h_tof->Draw("SAME");
    Int_t rebin = 100;
    h_tof_with_high_E	->Rebin(rebin);
    h_tof_with_E		->Rebin(rebin);
    h_tof				->Rebin(rebin);
    
    TLegend *leg_1 = new TLegend(0.78, 0.64, 0.98, 0.775);
	leg_1->AddEntry(h_tof,"Regular TOF spectrum");
	leg_1->AddEntry(h_tof_with_E,"TOF with any E hit");
	leg_1->AddEntry(h_tof_with_high_E,"TOF with E hit above ~3 MeV");
	leg_1->SetFillColor(0);
	leg_1->Draw();
    
	printf("\ndraw_dE-MCP_tof_spectra_with_E done.\n\n");
	
}

void draw_mcp_maps_gated_on_tof ()
{
    
    printf("\ndraw_mcp_maps_gated_on_tof started.");
	
	TFile *tfile		= new TFile(filename);
	//TFile *tfile		= new TFile("~/137i/rootfiles/137i_7.root");
	
	TCanvas *c_mcp_maps_gated_on_tof = new TCanvas("c_mcp_maps_gated_on_tof", "Betas vs Cycle Time", 945, 450);
	c_mcp_maps_gated_on_tof->Divide(2,1);
	c_mcp_maps_gated_on_tof->cd(1);
	h_T_oops_mcpMap->Draw("colz");
	c_mcp_maps_gated_on_tof->cd(2);
	h_R_oops_mcpMap->Draw("colz");
	
//	TCanvas *c_all_betas_vs_cycle_time = new TCanvas("c_all_betas_vs_cycle_time", "Betas vs Cycle Time", 945, 600);
//	h_betas_vs_cycle_time->Draw();
	
	printf("\ndraw_mcp_maps_gated_on_tof done.\n\n");
	
}

TH1I* draw_tof_spectrum_of_mcp_region (Double_t *x, Double_t *y)
{
    
    printf("\ndraw_tof_spectrum_of_mcp_region started.");
	
	//TFile *tfile		= new TFile(filename);
	TFile *tfile		= new TFile("~/137i/rootfiles/137i_7.root");
	
//	Double_t x[2] = {-0.1,0.1};
//	Double_t y[2] = {-1.0,1.0};
	
	char LT_title[200];
	char LR_title[200];
	char BT_title[200];
	char BR_title[200];
	char All_title[200];
	sprintf(LT_title,"LT: TOF for the MCP area (%f<x<%f) & (%f<y<%f)",x[0],x[1],y[0],y[1]);
	sprintf(LR_title,"LR: TOF for the MCP area (%f<x<%f) & (%f<y<%f)",x[0],x[1],y[0],y[1]);
	sprintf(BT_title,"BT: TOF for the MCP area (%f<x<%f) & (%f<y<%f)",x[0],x[1],y[0],y[1]);
	sprintf(BR_title,"BR: TOF for the MCP area (%f<x<%f) & (%f<y<%f)",x[0],x[1],y[0],y[1]);
	sprintf(All_title,"All combos: TOF for the MCP area (%f<x<%f) & (%f<y<%f)",x[0],x[1],y[0],y[1]);
	TH1I *h_tof_LT_local = new TH1I("h_tof_LT_local",LT_title,TOFBins,TOFMin,TOFMax);
	TH1I *h_tof_LR_local = new TH1I("h_tof_LR_local",LR_title,TOFBins,TOFMin,TOFMax);
	TH1I *h_tof_BT_local = new TH1I("h_tof_BT_local",BT_title,TOFBins,TOFMin,TOFMax);
	TH1I *h_tof_BR_local = new TH1I("h_tof_BR_local",BR_title,TOFBins,TOFMin,TOFMax);
	TH1I *h_tof_local = new TH1I("h_tof_local",All_title,TOFBins,TOFMin,TOFMax);
	
	char LT_string [200];
	char LR_string [200];
	char BT_string [200];
	char BR_string [200];
//  h_tof cut is         event_good==1 && s_capt_state==0 && t_dE_lo<bdn.t_L_dE && bdn.t_L_dE<t_dE_hi && a_dE_lo<bdn.a_L_dEsum && t_mcp_lo<t_T_mcp && a_mcp_lo<bdn.a_T_mcpSum
 	sprintf (LT_string, "event_good==1 && s_capt_state==0 && %d<t_L_dE && t_L_dE<%d && %d<a_L_dEsum && %d<t_T_mcp && %d<a_T_mcpSum && %f<T_mcpX && T_mcpX<%f && %f<T_mcpY && T_mcpY<%f", t_trigger_lo, t_trigger_hi, a_dE_lo, t_trigger_lo, a_mcp_lo, x[0], x[1], y[0], y[1]);
 	sprintf (LR_string, "event_good==1 && s_capt_state==0 && %d<t_L_dE && t_L_dE<%d && %d<a_L_dEsum && %d<t_R_mcp && %d<a_R_mcpSum && %f<R_mcpX && R_mcpX<%f && %f<R_mcpY && R_mcpY<%f", t_trigger_lo, t_trigger_hi, a_dE_lo, t_trigger_lo, a_mcp_lo, x[0], x[1], y[0], y[1]);
 	sprintf (BT_string, "event_good==1 && s_capt_state==0 && %d<t_B_dE && t_B_dE<%d && %d<a_B_dEsum && %d<t_T_mcp && %d<a_T_mcpSum && %f<T_mcpX && T_mcpX<%f && %f<T_mcpY && T_mcpY<%f", t_trigger_lo, t_trigger_hi, a_dE_lo, t_trigger_lo, a_mcp_lo, x[0], x[1], y[0], y[1]);
 	sprintf (BR_string, "event_good==1 && s_capt_state==0 && %d<t_B_dE && t_B_dE<%d && %d<a_B_dEsum && %d<t_R_mcp && %d<a_R_mcpSum && %f<R_mcpX && R_mcpX<%f && %f<R_mcpY && R_mcpY<%f", t_trigger_lo, t_trigger_hi, a_dE_lo, t_trigger_lo, a_mcp_lo, x[0], x[1], y[0], y[1]);
	TCut LT_cut = LT_string;
	TCut LR_cut = LR_string;
	TCut BT_cut = BT_string;
	TCut BR_cut = BR_string;
	beta_recoil_tree->Project("h_tof_LT_local","tof_LT",LT_cut);
	beta_recoil_tree->Project("h_tof_LR_local","tof_LR",LR_cut);
	beta_recoil_tree->Project("h_tof_BT_local","tof_BT",BT_cut);
	beta_recoil_tree->Project("h_tof_BR_local","tof_BR",BR_cut);
	h_tof_local = h_tof_local->Add(h_tof_LT_local,1.0);
	h_tof_local = h_tof_local->Add(h_tof_LR_local,1.0);
	h_tof_local = h_tof_local->Add(h_tof_BT_local,1.0);
	h_tof_local = h_tof_local->Add(h_tof_BR_local,1.0);
	
	TCanvas *c_tof_spectra_of_mcp_region = new TCanvas("c_tof_spectra_of_mcp_region","TOF Spectra (dE-MCP) on a specific MCP region",1600,1000);
	c_tof_spectra_of_mcp_region->Divide(2,2);
	c_tof_spectra_of_mcp_region->cd(1);
	c_tof_spectra_of_mcp_region_1->SetLogy();
	h_tof_LT_local->Draw();
	c_tof_spectra_of_mcp_region->cd(2);
	c_tof_spectra_of_mcp_region_2->SetLogy();
	h_tof_LR_local->Draw();
	c_tof_spectra_of_mcp_region->cd(3);
	c_tof_spectra_of_mcp_region_3->SetLogy();
	h_tof_BT_local->Draw();
	c_tof_spectra_of_mcp_region->cd(4);
	c_tof_spectra_of_mcp_region_4->SetLogy();
	h_tof_BR_local->Draw();
	TCanvas *c_dE_MCP_tof_sum_spectrum_of_mcp_region = new TCanvas("c_dE_MCP_tof_sum_spectrum_of_mcp_region","TOF Spectrum (All dE-MCP combos) on a specific MCP region",945,600);
    c_dE_MCP_tof_sum_spectrum_of_mcp_region->SetLogy();
    h_tof_local->Draw();
    
    return h_tof_local;
	
	printf("\ndraw_tof_spectrum_of_mcp_region done.\n\n");
	
}

void recoil_ion_rates_standalone(TH1I *h_tof_input)
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
    
    Double_t bkgd_per_ch_left_top		= h_tof_input->Integral(bkgd_t_low,bkgd_t_high) / bkgd_t_range;
//	Double_t bkgd_per_ch_left_right		= h_tof_LR->Integral(bkgd_t_low,bkgd_t_high) / bkgd_t_range;
//	Double_t bkgd_per_ch_bottom_top		= h_tof_BT->Integral(bkgd_t_low,bkgd_t_high) / bkgd_t_range;
//	Double_t bkgd_per_ch_bottom_right	= h_tof_BR->Integral(bkgd_t_low,bkgd_t_high) / bkgd_t_range;
    
    Double_t bdn_area_left_top		= h_tof_input->Integral(bdn_t_low,bdn_t_high) - bkgd_per_ch_left_top*bdn_t_range;
//	Double_t bdn_area_left_right	= h_tof_LR->Integral(bdn_t_low,bdn_t_high) - bkgd_per_ch_left_right*bdn_t_range;
//	Double_t bdn_area_bottom_top	= h_tof_BT->Integral(bdn_t_low,bdn_t_high) - bkgd_per_ch_bottom_top*bdn_t_range;
//	Double_t bdn_area_bottom_right	= h_tof_BR->Integral(bdn_t_low,bdn_t_high) - bkgd_per_ch_bottom_right*bdn_t_range;
	
	Double_t beta_area_left_top		= h_tof_input->Integral(beta_t_low,beta_t_high) - bkgd_per_ch_left_top*beta_t_range;
//	Double_t beta_area_left_right	= h_tof_LR->Integral(beta_t_low,beta_t_high) - bkgd_per_ch_left_right*beta_t_range;
//	Double_t beta_area_bottom_top	= h_tof_BT->Integral(beta_t_low,beta_t_high) - bkgd_per_ch_bottom_top*beta_t_range;
//	Double_t beta_area_bottom_right	= h_tof_BR->Integral(beta_t_low,beta_t_high) - bkgd_per_ch_bottom_right*beta_t_range;
	
	Double_t bdn_area_tot = bdn_area_left_top;// + bdn_area_left_right + bdn_area_bottom_top + bdn_area_bottom_right;
	Double_t beta_area_tot = beta_area_left_top;// + beta_area_left_right + beta_area_bottom_top + beta_area_bottom_right;
    
    Int_t a = h_tof_input->Integral(beta_t_low,beta_t_high);
//    Int_t b = h_tof_LR->Integral(beta_t_low,beta_t_high);
//    Int_t c = h_tof_BT->Integral(beta_t_low,beta_t_high);
//    Int_t d = h_tof_BR->Integral(beta_t_low,beta_t_high);
    
    Int_t e = h_tof_input->Integral(bkgd_t_low,bkgd_t_high);
//    Int_t f = h_tof_LR->Integral(bkgd_t_low,bkgd_t_high);
//    Int_t g = h_tof_BT->Integral(bkgd_t_low,bkgd_t_high);
//    Int_t h = h_tof_BR->Integral(bkgd_t_low,bkgd_t_high);
    
    Int_t i = h_tof_input->Integral(bdn_t_low,bdn_t_high);
//    Int_t j = h_tof_LR->Integral(bdn_t_low,bdn_t_high);
//    Int_t k = h_tof_BT->Integral(bdn_t_low,bdn_t_high);
//    Int_t l = h_tof_BR->Integral(bdn_t_low,bdn_t_high);
    
    cout << " " << endl << endl;
    cout << "Looking at histogram: " << h_tof_input->GetName() << " -- " << h_tof_input->GetTitle() << endl;
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

void sum_ge_histos ()
{
	printf("sum_ge_histos started.\n");
	
	TFile *tfile = new TFile(filename);
	
	TCanvas *c_a_R_ge	= new TCanvas("c_a_R_ge","Right Ge ADC spectrum",945,600);
	ha_R_ge->Draw();
	ha_sgnl_R_ge->Draw("SAME");
	ha_bkgd_R_ge->Draw("SAME");
	ha_sgnl_R_ge->SetLineColor(kGreen);
	ha_bkgd_R_ge->SetLineColor(kViolet);
//	h_all_vs_cycle_time->GetXaxis()->SetRangeUser(100991,101021);
//	h_all_vs_cycle_time_observed->GetXaxis()->SetRangeUser(100991,101021);
	
	TLegend *leg_1 = new TLegend(0.78, 0.64, 0.98, 0.775);
	leg_1->AddEntry(ha_R_ge,"All ADC values");
	leg_1->AddEntry(ha_sgnl_R_ge,"Capt ADC values");
	leg_1->AddEntry(ha_bkgd_R_ge,"Eject ADC values");
	leg_1->SetFillColor(0);
	leg_1->Draw();
	
//	TCanvas *c_deadtime_correction_factors	= new TCanvas("c_deadtime_correction_factors","Deadtime correction factor vs cycle time in ms",945,600);
//	h_deadtime_correction_factors->SetTitle("1/(fraction of events lost to deadtime), per ms of cycle");
//	h_deadtime_correction_factors->Draw();
//	h_deadtime_correction_factors->GetXaxis()->SetRangeUser(100991,101021);
	
	printf("sum_ge_histos done.\n\n");
}

void draw_dE_mcp_test_tof_spectra()
{
	printf("\ndraw_dE-MCP_tof_spectra started.");
	TFile *tfile		= new TFile(filename);
	TCanvas *c_dE_MCP_test_tof_spectra = new TCanvas("c_dE_MCP_test_tof_spectra","TOF Spectra (dE-MCP)",1600,1000);
	c_dE_MCP_test_tof_spectra->Divide(2,2);
	
	c_dE_MCP_test_tof_spectra->cd(1);
	c_dE_MCP_test_tof_spectra_1->SetLogy();
	beta_recoil_tree->Draw("t_T_mcp-0.5*(t_L_dEa+t_L_dEb)>>h_LT(26500,-1000,25500)");
	
	c_dE_MCP_test_tof_spectra->cd(2);
	c_dE_MCP_test_tof_spectra_2->SetLogy();
	beta_recoil_tree->Draw("t_R_mcp-0.5*(t_L_dEa+t_L_dEb)>>h_LR(26500,-1000,25500)");
	
	c_dE_MCP_test_tof_spectra->cd(3);
	c_dE_MCP_test_tof_spectra_3->SetLogy();
	beta_recoil_tree->Draw("t_T_mcp-0.5*(t_B_dEa+t_B_dEb)>>h_BT(26500,-1000,25500)");
	
	c_dE_MCP_test_tof_spectra->cd(4);
	c_dE_MCP_test_tof_spectra_4->SetLogy();
	beta_recoil_tree->Draw("t_R_mcp-0.5*(t_B_dEa+t_B_dEb)>>h_BR(26500,-1000,25500)");
	
//	TCanvas *c_dE_MCP_test_tof_sum_spectrum = new TCanvas("c_dE_MCP_test_tof_sum_spectrum","Test TOF Spectrum (All dE-MCP combos)",800,500);
//  c_dE_MCP_test_tof_sum_spectrum->SetLogy();
//  h_tof->Draw();

	printf("\ndraw_dE-MCP_tof_spectra done.\n\n");
}

void draw_tof_for_137i07_by_time_since_capt ()
{
	
	printf("\ndraw_tof_for_137i07_by_time_since_capt started.");
	
	TFile *tfile = new TFile("~/137i/rootfiles/137i07.root");
	
	// TOF limits in ns
	Int_t tof1_lo = 230; // fast ions
	Int_t tof1_hi = 1550;
	Int_t tof2_lo = 15230; // fast ion bkgd window
	Int_t tof2_hi = 16550;
	
	// TOF cuts
	char LT_string[200], LR_string[200], BT_string[200], BR_string[200];
	char First_3sec_string[2000], Second_3sec_string[2000];
// The standard TOF cut
	sprintf (LT_string, "event_good==1 && s_capt_state==0 && %d<t_L_dE && t_L_dE<%d && %d<a_L_dEsum && %d<t_T_mcp && %d<a_T_mcpSum", t_trigger_lo, t_trigger_hi, a_dE_lo, t_trigger_lo, a_mcp_lo);
	sprintf (LR_string, "event_good==1 && s_capt_state==0 && %d<t_L_dE && t_L_dE<%d && %d<a_L_dEsum && %d<t_R_mcp && %d<a_R_mcpSum", t_trigger_lo, t_trigger_hi, a_dE_lo, t_trigger_lo, a_mcp_lo);
	sprintf (BT_string, "event_good==1 && s_capt_state==0 && %d<t_B_dE && t_B_dE<%d && %d<a_B_dEsum && %d<t_T_mcp && %d<a_T_mcpSum", t_trigger_lo, t_trigger_hi, a_dE_lo, t_trigger_lo, a_mcp_lo);
	sprintf (BR_string, "event_good==1 && s_capt_state==0 && %d<t_B_dE && t_B_dE<%d && %d<a_B_dEsum && %d<t_R_mcp && %d<a_R_mcpSum", t_trigger_lo, t_trigger_hi, a_dE_lo, t_trigger_lo, a_mcp_lo);
	
	TCut LT_cuts = LT_string;
    TCut LR_cuts = LR_string;
    TCut BT_cuts = BT_string;
    TCut BR_cuts = BR_string;
    TCut First_3sec = "0<=s_ms_since_capt && s_ms_since_capt<3000 && 1<=s_capt && s_capt<=24";
    TCut Second_3sec = "3000<=s_ms_since_capt && s_ms_since_capt<6000 && 1<=s_capt && s_capt<=24";
	
	const Double_t TOFMin	= -1000.0; // ns
	const Double_t TOFMax	= 25500.0; // ns
	const Int_t TOFBins		= 26500; // one bin per ns
	
	TH1::SetDefaultSumw2(kTRUE);
	
	TH1I *h_tof_LT_1st_3s_after_capt = new TH1I("h_tof_LT_1st_3s_after_capt","Left-Top TOF (ns) in first 3 sec of capt, summed over 24 capts",TOFBins,TOFMin,TOFMax);
	TH1I *h_tof_LR_1st_3s_after_capt = new TH1I("h_tof_LR_1st_3s_after_capt","Left-Right TOF (ns) in first 3 sec of capt, summed over 24 capts",TOFBins,TOFMin,TOFMax);
	TH1I *h_tof_BT_1st_3s_after_capt = new TH1I("h_tof_BT_1st_3s_after_capt","Bottom-Top TOF (ns) in first 3 sec of capt, summed over 24 capts",TOFBins,TOFMin,TOFMax);
	TH1I *h_tof_BR_1st_3s_after_capt = new TH1I("h_tof_BR_1st_3s_after_capt","Bottom-Right TOF (ns) in first 3 sec of capt, summed over 24 capts",TOFBins,TOFMin,TOFMax);
	TH1I *h_tof_90deg_1st_3s_after_capt = new TH1I("h_tof_90deg_1st_3s_after_capt","90-degree TOF (ns) in first 3 sec of capt, summed over 24 capts",TOFBins,TOFMin,TOFMax);
	TH1I *h_tof_180deg_1st_3s_after_capt = new TH1I("h_tof_180deg_1st_3s_after_capt","180-degree TOF (ns) in first 3 sec of capt, summed over 24 capts",TOFBins,TOFMin,TOFMax);
	
	TH1I *h_tof_LT_2nd_3s_after_capt = new TH1I("h_tof_LT_2nd_3s_after_capt","Left-Top TOF (ns) in second 3 sec of capt, summed over 24 capts",TOFBins,TOFMin,TOFMax);
	TH1I *h_tof_LR_2nd_3s_after_capt = new TH1I("h_tof_LR_2nd_3s_after_capt","Left-Right TOF (ns) in second 3 sec of capt, summed over 24 capts",TOFBins,TOFMin,TOFMax);
	TH1I *h_tof_BT_2nd_3s_after_capt = new TH1I("h_tof_BT_2nd_3s_after_capt","Bottom-Top TOF (ns) in second 3 sec of capt, summed over 24 capts",TOFBins,TOFMin,TOFMax);
	TH1I *h_tof_BR_2nd_3s_after_capt = new TH1I("h_tof_BR_2nd_3s_after_capt","Bottom-Right TOF (ns) in second 3 sec of capt, summed over 24 capts",TOFBins,TOFMin,TOFMax);
	TH1I *h_tof_90deg_2nd_3s_after_capt = new TH1I("h_tof_90deg_2nd_3s_after_capt","90-degree TOF (ns) in first 3 sec of capt, summed over 24 capts",TOFBins,TOFMin,TOFMax);
	TH1I *h_tof_180deg_2nd_3s_after_capt = new TH1I("h_tof_180deg_2nd_3s_after_capt","180-degree TOF (ns) in first 3 sec of capt, summed over 24 capts",TOFBins,TOFMin,TOFMax);
	
	TH1I *h_tof_90deg_1st_minus_2nd = new TH1I("h_tof_90deg_1st_minus_2nd","90-degree TOF (ns), 0-3 sec minus 3-6 sec",TOFBins,TOFMin,TOFMax);
	TH1I *h_tof_180deg_1st_minus_2nd = new TH1I("h_tof_180deg_1st_minus_2nd","180-degree TOF (ns), 0-3 sec minus 3-6 sec",TOFBins,TOFMin,TOFMax);
	
    beta_recoil_tree->Project("h_tof_LT_1st_3s_after_capt", "tof_LT", LT_cuts && First_3sec);
	beta_recoil_tree->Project("h_tof_LR_1st_3s_after_capt", "tof_LR", LR_cuts && First_3sec);
    beta_recoil_tree->Project("h_tof_BT_1st_3s_after_capt", "tof_BT", BT_cuts && First_3sec);
    beta_recoil_tree->Project("h_tof_BR_1st_3s_after_capt", "tof_BR", BR_cuts && First_3sec);
    beta_recoil_tree->Project("h_tof_LT_2nd_3s_after_capt", "tof_LT", LT_cuts && Second_3sec);
	beta_recoil_tree->Project("h_tof_LR_2nd_3s_after_capt", "tof_LR", LR_cuts && Second_3sec);
    beta_recoil_tree->Project("h_tof_BT_2nd_3s_after_capt", "tof_BT", BT_cuts && Second_3sec);
    beta_recoil_tree->Project("h_tof_BR_2nd_3s_after_capt", "tof_BR", BR_cuts && Second_3sec);
    
    // Make 90-deg and 180-deg sums
	
//	h_tof_LT_1st_3s_after_capt->Sumw2();
//	h_tof_LR_1st_3s_after_capt->Sumw2();
//	h_tof_BT_1st_3s_after_capt->Sumw2();
//	h_tof_BR_1st_3s_after_capt->Sumw2();
//	h_tof_90deg_1st_3s_after_capt->Sumw2();
//	h_tof_180deg_1st_3s_after_capt->Sumw2();
	
//	h_tof_LT_2nd_3s_after_capt->Sumw2();
//	h_tof_LR_2nd_3s_after_capt->Sumw2();
//	h_tof_BT_2nd_3s_after_capt->Sumw2();
//	h_tof_BR_2nd_3s_after_capt->Sumw2();
//	h_tof_90deg_2nd_3s_after_capt->Sumw2();
//	h_tof_180deg_2nd_3s_after_capt->Sumw2();
	
//	h_tof_90deg_1st_minus_2nd->Sumw2();
//	h_tof_180deg_1st_minus_2nd->Sumw2();
	
	h_tof_90deg_1st_3s_after_capt  = h_tof_90deg_1st_3s_after_capt ->Add(h_tof_LT_1st_3s_after_capt,1.0);
	h_tof_90deg_1st_3s_after_capt  = h_tof_90deg_1st_3s_after_capt ->Add(h_tof_BR_1st_3s_after_capt,1.0);
	h_tof_90deg_2nd_3s_after_capt  = h_tof_90deg_2nd_3s_after_capt ->Add(h_tof_LT_2nd_3s_after_capt,1.0);
	h_tof_90deg_2nd_3s_after_capt  = h_tof_90deg_2nd_3s_after_capt ->Add(h_tof_BR_2nd_3s_after_capt,1.0);
	
	h_tof_180deg_1st_3s_after_capt = h_tof_180deg_1st_3s_after_capt->Add(h_tof_LR_1st_3s_after_capt,1.0);
	h_tof_180deg_1st_3s_after_capt = h_tof_180deg_1st_3s_after_capt->Add(h_tof_BT_1st_3s_after_capt,1.0);
	h_tof_180deg_2nd_3s_after_capt = h_tof_180deg_2nd_3s_after_capt->Add(h_tof_LR_2nd_3s_after_capt,1.0);
	h_tof_180deg_2nd_3s_after_capt = h_tof_180deg_2nd_3s_after_capt->Add(h_tof_BT_2nd_3s_after_capt,1.0);
	
	h_tof_90deg_1st_minus_2nd      = h_tof_90deg_1st_minus_2nd	   ->Add(h_tof_90deg_1st_3s_after_capt,1.0);
	h_tof_90deg_1st_minus_2nd      = h_tof_90deg_1st_minus_2nd	   ->Add(h_tof_90deg_2nd_3s_after_capt,-1.0);
	h_tof_180deg_1st_minus_2nd     = h_tof_180deg_1st_minus_2nd	   ->Add(h_tof_180deg_1st_3s_after_capt,1.0);
	h_tof_180deg_1st_minus_2nd     = h_tof_180deg_1st_minus_2nd	   ->Add(h_tof_180deg_2nd_3s_after_capt,-1.0);
	
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
	
// Write histos to file
	TFile *tof_by_time_since_capt_137i07 = new TFile("tof_by_time_since_capt_137i07.root","RECREATE");
	
	tof_by_time_since_capt_137i07->WriteTObject(h_tof_LT_1st_3s_after_capt);
	tof_by_time_since_capt_137i07->WriteTObject(h_tof_LR_1st_3s_after_capt);
	tof_by_time_since_capt_137i07->WriteTObject(h_tof_BT_1st_3s_after_capt);
	tof_by_time_since_capt_137i07->WriteTObject(h_tof_BR_1st_3s_after_capt);
	
	tof_by_time_since_capt_137i07->WriteTObject(h_tof_LT_2nd_3s_after_capt);
	tof_by_time_since_capt_137i07->WriteTObject(h_tof_LR_2nd_3s_after_capt);
	tof_by_time_since_capt_137i07->WriteTObject(h_tof_BT_2nd_3s_after_capt);
	tof_by_time_since_capt_137i07->WriteTObject(h_tof_BR_2nd_3s_after_capt);
	
	tof_by_time_since_capt_137i07->WriteTObject(h_tof_90deg_1st_3s_after_capt);
	tof_by_time_since_capt_137i07->WriteTObject(h_tof_90deg_2nd_3s_after_capt);
	tof_by_time_since_capt_137i07->WriteTObject(h_tof_90deg_1st_minus_2nd);
	
	tof_by_time_since_capt_137i07->WriteTObject(h_tof_180deg_1st_3s_after_capt);
	tof_by_time_since_capt_137i07->WriteTObject(h_tof_180deg_2nd_3s_after_capt);
	tof_by_time_since_capt_137i07->WriteTObject(h_tof_180deg_1st_minus_2nd);
	
	printf("\ndraw_tof_for_137i07_by_time_since_capt done.\n\n");
	
}

void tof_by_time_since_capt_134sb0103 ()
{
	
	printf("\ntof_by_time_since_capt_134sb0103 started.\n\n");
	
	TFile *tfile = new TFile("~/134sb/rootfiles/134sb0103.root");
	
// TOF limits in ns
//	Int_t tof1_lo = 230; // fast ions
//	Int_t tof1_hi = 1550;
//	Int_t tof2_lo = 15230; // fast ion bkgd window
//	Int_t tof2_hi = 16550;
	
// TOF cuts
	char LT_string[200], LR_string[200], BT_string[200], BR_string[200];
	char R_mcp_FidArea_string[200], T_mcp_FidArea_string[200];
	
// The standard TOF cut
	sprintf (LT_string, "%d<t_L_dE && t_L_dE<%d && %d<a_L_dEsum && %d<t_T_mcp && %d<a_T_mcpSum", t_trigger_lo, t_trigger_hi, a_dE_lo, t_trigger_lo, a_mcp_lo);
	sprintf (LR_string, "%d<t_L_dE && t_L_dE<%d && %d<a_L_dEsum && %d<t_R_mcp && %d<a_R_mcpSum", t_trigger_lo, t_trigger_hi, a_dE_lo, t_trigger_lo, a_mcp_lo);
	sprintf (BT_string, "%d<t_B_dE && t_B_dE<%d && %d<a_B_dEsum && %d<t_T_mcp && %d<a_T_mcpSum", t_trigger_lo, t_trigger_hi, a_dE_lo, t_trigger_lo, a_mcp_lo);
	sprintf (BR_string, "%d<t_B_dE && t_B_dE<%d && %d<a_B_dEsum && %d<t_R_mcp && %d<a_R_mcpSum", t_trigger_lo, t_trigger_hi, a_dE_lo, t_trigger_lo, a_mcp_lo);
	sprintf (R_mcp_FidArea_string, "%f<bdn.R_mcpX && bdn.R_mcpX<%f && %f<bdn.R_mcpY && bdn.R_mcpY<%f", fid_area_T_mcpX_lo, fid_area_T_mcpX_hi, fid_area_T_mcpY_lo, fid_area_T_mcpY_hi);
	sprintf (T_mcp_FidArea_string, "%f<bdn.T_mcpX && bdn.T_mcpX<%f && %f<bdn.T_mcpY && bdn.T_mcpY<%f", fid_area_T_mcpX_lo, fid_area_T_mcpX_hi, fid_area_T_mcpY_lo, fid_area_T_mcpY_hi);
	
	TCut LT_cuts = LT_string;
    TCut LR_cuts = LR_string;
    TCut BT_cuts = BT_string;
    TCut BR_cuts = BR_string;
    TCut R_mcp_FidArea = R_mcp_FidArea_string;
    TCut T_mcp_FidArea = T_mcp_FidArea_string;
    TCut TrapFull	= "event_good==1 && s_capt_state==0";
    TCut TrapEmpty	= "event_good==1 && s_capt_state==1";
    TCut t_capt_100ms	=   "0<=s_ms_since_capt && s_ms_since_capt<100 && 1<=s_capt && s_capt<=9";
    TCut t_capt_200ms	= "100<=s_ms_since_capt && s_ms_since_capt<200 && 1<=s_capt && s_capt<=9";
    TCut t_capt_300ms	= "200<=s_ms_since_capt && s_ms_since_capt<300 && 1<=s_capt && s_capt<=9";
    TCut t_capt_400ms	= "300<=s_ms_since_capt && s_ms_since_capt<400 && 1<=s_capt && s_capt<=9";
    TCut t_capt_500ms	= "400<=s_ms_since_capt && s_ms_since_capt<500 && 1<=s_capt && s_capt<=9";
    TCut t_capt_600ms	= "500<=s_ms_since_capt && s_ms_since_capt<600 && 1<=s_capt && s_capt<=9";
    TCut t_eject_100ms	=   "0<=s_ms_since_eject && s_ms_since_eject<100";
	TCut t_eject_200ms	= "100<=s_ms_since_eject && s_ms_since_eject<200";
	TCut t_eject_300ms	= "200<=s_ms_since_eject && s_ms_since_eject<300";
	
	const Double_t TOFMin	= -1000.0; // ns
	const Double_t TOFMax	= 25500.0; // ns
	const Int_t TOFBins		= 2*26500; // one bin per ns
	
	TH1::SetDefaultSumw2(kTRUE);
	
// Define histos	
	TH1I *h_tof_LT_100ms = new TH1I("h_tof_LT_100ms","LT TOF (ns) in 1st 100ms of capt, summed over 9 capts",TOFBins,TOFMin,TOFMax);
	TH1I *h_tof_LT_200ms = new TH1I("h_tof_LT_200ms","LT TOF (ns) in 2nd 100ms of capt, summed over 9 capts",TOFBins,TOFMin,TOFMax);
	TH1I *h_tof_LT_300ms = new TH1I("h_tof_LT_300ms","LT TOF (ns) in 3rd 100ms of capt, summed over 9 capts",TOFBins,TOFMin,TOFMax);
	TH1I *h_tof_LT_400ms = new TH1I("h_tof_LT_400ms","LT TOF (ns) in 4th 100ms of capt, summed over 9 capts",TOFBins,TOFMin,TOFMax);
	TH1I *h_tof_LT_500ms = new TH1I("h_tof_LT_500ms","LT TOF (ns) in 5th 100ms of capt, summed over 9 capts",TOFBins,TOFMin,TOFMax);
	TH1I *h_tof_LT_600ms = new TH1I("h_tof_LT_600ms","LT TOF (ns) in 6th 100ms of capt, summed over 9 capts",TOFBins,TOFMin,TOFMax);
	
	TH1I *h_tof_LR_100ms = new TH1I("h_tof_LR_100ms","LR TOF (ns) in 1st 100ms of capt, summed over 9 capts",TOFBins,TOFMin,TOFMax);
	TH1I *h_tof_LR_200ms = new TH1I("h_tof_LR_200ms","LR TOF (ns) in 2nd 100ms of capt, summed over 9 capts",TOFBins,TOFMin,TOFMax);
	TH1I *h_tof_LR_300ms = new TH1I("h_tof_LR_300ms","LR TOF (ns) in 3rd 100ms of capt, summed over 9 capts",TOFBins,TOFMin,TOFMax);
	TH1I *h_tof_LR_400ms = new TH1I("h_tof_LR_400ms","LR TOF (ns) in 4th 100ms of capt, summed over 9 capts",TOFBins,TOFMin,TOFMax);
	TH1I *h_tof_LR_500ms = new TH1I("h_tof_LR_500ms","LR TOF (ns) in 5th 100ms of capt, summed over 9 capts",TOFBins,TOFMin,TOFMax);
	TH1I *h_tof_LR_600ms = new TH1I("h_tof_LR_600ms","LR TOF (ns) in 6th 100ms of capt, summed over 9 capts",TOFBins,TOFMin,TOFMax);
	
	TH1I *h_tof_BT_100ms = new TH1I("h_tof_BT_100ms","BT TOF (ns) in 1st 100ms of capt, summed over 9 capts",TOFBins,TOFMin,TOFMax);
	TH1I *h_tof_BT_200ms = new TH1I("h_tof_BT_200ms","BT TOF (ns) in 2nd 100ms of capt, summed over 9 capts",TOFBins,TOFMin,TOFMax);
	TH1I *h_tof_BT_300ms = new TH1I("h_tof_BT_300ms","BT TOF (ns) in 3rd 100ms of capt, summed over 9 capts",TOFBins,TOFMin,TOFMax);
	TH1I *h_tof_BT_400ms = new TH1I("h_tof_BT_400ms","BT TOF (ns) in 4th 100ms of capt, summed over 9 capts",TOFBins,TOFMin,TOFMax);
	TH1I *h_tof_BT_500ms = new TH1I("h_tof_BT_500ms","BT TOF (ns) in 5th 100ms of capt, summed over 9 capts",TOFBins,TOFMin,TOFMax);
	TH1I *h_tof_BT_600ms = new TH1I("h_tof_BT_600ms","BT TOF (ns) in 6th 100ms of capt, summed over 9 capts",TOFBins,TOFMin,TOFMax);
	
	TH1I *h_tof_BR_100ms = new TH1I("h_tof_BR_100ms","BR TOF (ns) in 1st 100ms of capt, summed over 9 capts",TOFBins,TOFMin,TOFMax);
	TH1I *h_tof_BR_200ms = new TH1I("h_tof_BR_200ms","BR TOF (ns) in 2nd 100ms of capt, summed over 9 capts",TOFBins,TOFMin,TOFMax);
	TH1I *h_tof_BR_300ms = new TH1I("h_tof_BR_300ms","BR TOF (ns) in 3rd 100ms of capt, summed over 9 capts",TOFBins,TOFMin,TOFMax);
	TH1I *h_tof_BR_400ms = new TH1I("h_tof_BR_400ms","BR TOF (ns) in 4th 100ms of capt, summed over 9 capts",TOFBins,TOFMin,TOFMax);
	TH1I *h_tof_BR_500ms = new TH1I("h_tof_BR_500ms","BR TOF (ns) in 5th 100ms of capt, summed over 9 capts",TOFBins,TOFMin,TOFMax);
	TH1I *h_tof_BR_600ms = new TH1I("h_tof_BR_600ms","BR TOF (ns) in 6th 100ms of capt, summed over 9 capts",TOFBins,TOFMin,TOFMax);
	
	TH1I *h_tof_90deg_100ms = new TH1I("h_tof_90deg_100ms","90-degree TOF (ns) in 1st 100ms of capt, summed over 9 capts",TOFBins,TOFMin,TOFMax);
	TH1I *h_tof_90deg_200ms = new TH1I("h_tof_90deg_200ms","90-degree TOF (ns) in 2nd 100ms of capt, summed over 9 capts",TOFBins,TOFMin,TOFMax);
	TH1I *h_tof_90deg_300ms = new TH1I("h_tof_90deg_300ms","90-degree TOF (ns) in 3rd 100ms of capt, summed over 9 capts",TOFBins,TOFMin,TOFMax);
	TH1I *h_tof_90deg_400ms = new TH1I("h_tof_90deg_400ms","90-degree TOF (ns) in 4th 100ms of capt, summed over 9 capts",TOFBins,TOFMin,TOFMax);
	TH1I *h_tof_90deg_500ms = new TH1I("h_tof_90deg_500ms","90-degree TOF (ns) in 5th 100ms of capt, summed over 9 capts",TOFBins,TOFMin,TOFMax);
	TH1I *h_tof_90deg_600ms = new TH1I("h_tof_90deg_600ms","90-degree TOF (ns) in 6th 100ms of capt, summed over 9 capts",TOFBins,TOFMin,TOFMax);
	
	TH1F *h_tof_180deg_100ms = new TH1F("h_tof_180deg_100ms","180-degree TOF (ns) in 1st 100ms of capt, summed over 9 capts",TOFBins,TOFMin,TOFMax);
	TH1F *h_tof_180deg_200ms = new TH1F("h_tof_180deg_200ms","180-degree TOF (ns) in 2nd 100ms of capt, summed over 9 capts",TOFBins,TOFMin,TOFMax);
	TH1F *h_tof_180deg_300ms = new TH1F("h_tof_180deg_300ms","180-degree TOF (ns) in 3rd 100ms of capt, summed over 9 capts",TOFBins,TOFMin,TOFMax);
	TH1F *h_tof_180deg_400ms = new TH1F("h_tof_180deg_400ms","180-degree TOF (ns) in 4th 100ms of capt, summed over 9 capts",TOFBins,TOFMin,TOFMax);
	TH1F *h_tof_180deg_500ms = new TH1F("h_tof_180deg_500ms","180-degree TOF (ns) in 5th 100ms of capt, summed over 9 capts",TOFBins,TOFMin,TOFMax);
	TH1F *h_tof_180deg_600ms = new TH1F("h_tof_180deg_600ms","180-degree TOF (ns) in 6th 100ms of capt, summed over 9 capts",TOFBins,TOFMin,TOFMax);
	
// Fill histos	
	beta_recoil_tree->Project("h_tof_LT_100ms", "tof_LT", LT_cuts && T_mcp_FidArea && TrapFull && t_capt_100ms);
	beta_recoil_tree->Project("h_tof_LT_200ms", "tof_LT", LT_cuts && T_mcp_FidArea && TrapFull && t_capt_200ms);
	beta_recoil_tree->Project("h_tof_LT_300ms", "tof_LT", LT_cuts && T_mcp_FidArea && TrapFull && t_capt_300ms);
	beta_recoil_tree->Project("h_tof_LT_400ms", "tof_LT", LT_cuts && T_mcp_FidArea && TrapFull && t_capt_400ms);
	beta_recoil_tree->Project("h_tof_LT_500ms", "tof_LT", LT_cuts && T_mcp_FidArea && TrapFull && t_capt_500ms);
	beta_recoil_tree->Project("h_tof_LT_600ms", "tof_LT", LT_cuts && T_mcp_FidArea && TrapFull && t_capt_600ms);
	
	beta_recoil_tree->Project("h_tof_LR_100ms", "tof_LR", LR_cuts && R_mcp_FidArea && TrapFull && t_capt_100ms);
	beta_recoil_tree->Project("h_tof_LR_200ms", "tof_LR", LR_cuts && R_mcp_FidArea && TrapFull && t_capt_200ms);
	beta_recoil_tree->Project("h_tof_LR_300ms", "tof_LR", LR_cuts && R_mcp_FidArea && TrapFull && t_capt_300ms);
	beta_recoil_tree->Project("h_tof_LR_400ms", "tof_LR", LR_cuts && R_mcp_FidArea && TrapFull && t_capt_400ms);
	beta_recoil_tree->Project("h_tof_LR_500ms", "tof_LR", LR_cuts && R_mcp_FidArea && TrapFull && t_capt_500ms);
	beta_recoil_tree->Project("h_tof_LR_600ms", "tof_LR", LR_cuts && R_mcp_FidArea && TrapFull && t_capt_600ms);
	
	beta_recoil_tree->Project("h_tof_BT_100ms", "tof_BT", BT_cuts && T_mcp_FidArea && TrapFull && t_capt_100ms);
	beta_recoil_tree->Project("h_tof_BT_200ms", "tof_BT", BT_cuts && T_mcp_FidArea && TrapFull && t_capt_200ms);
	beta_recoil_tree->Project("h_tof_BT_300ms", "tof_BT", BT_cuts && T_mcp_FidArea && TrapFull && t_capt_300ms);
	beta_recoil_tree->Project("h_tof_BT_400ms", "tof_BT", BT_cuts && T_mcp_FidArea && TrapFull && t_capt_400ms);
	beta_recoil_tree->Project("h_tof_BT_500ms", "tof_BT", BT_cuts && T_mcp_FidArea && TrapFull && t_capt_500ms);
	beta_recoil_tree->Project("h_tof_BT_600ms", "tof_BT", BT_cuts && T_mcp_FidArea && TrapFull && t_capt_600ms);
	
	beta_recoil_tree->Project("h_tof_BR_100ms", "tof_BR", BR_cuts && R_mcp_FidArea && TrapFull && t_capt_100ms);
	beta_recoil_tree->Project("h_tof_BR_200ms", "tof_BR", BR_cuts && R_mcp_FidArea && TrapFull && t_capt_200ms);
	beta_recoil_tree->Project("h_tof_BR_300ms", "tof_BR", BR_cuts && R_mcp_FidArea && TrapFull && t_capt_300ms);
	beta_recoil_tree->Project("h_tof_BR_400ms", "tof_BR", BR_cuts && R_mcp_FidArea && TrapFull && t_capt_400ms);
	beta_recoil_tree->Project("h_tof_BR_500ms", "tof_BR", BR_cuts && R_mcp_FidArea && TrapFull && t_capt_500ms);
	beta_recoil_tree->Project("h_tof_BR_600ms", "tof_BR", BR_cuts && R_mcp_FidArea && TrapFull && t_capt_600ms);
    
// Make 90-deg and 180-deg sums
	h_tof_90deg_100ms  = h_tof_90deg_100ms->Add(h_tof_LT_100ms,1.0);
	h_tof_90deg_200ms  = h_tof_90deg_200ms->Add(h_tof_LT_200ms,1.0);
	h_tof_90deg_300ms  = h_tof_90deg_300ms->Add(h_tof_LT_300ms,1.0);
	h_tof_90deg_400ms  = h_tof_90deg_400ms->Add(h_tof_LT_400ms,1.0);
	h_tof_90deg_500ms  = h_tof_90deg_500ms->Add(h_tof_LT_500ms,1.0);
	h_tof_90deg_600ms  = h_tof_90deg_600ms->Add(h_tof_LT_600ms,1.0);
	
	h_tof_90deg_100ms  = h_tof_90deg_100ms->Add(h_tof_BR_100ms,1.0);
	h_tof_90deg_200ms  = h_tof_90deg_200ms->Add(h_tof_BR_200ms,1.0);
	h_tof_90deg_300ms  = h_tof_90deg_300ms->Add(h_tof_BR_300ms,1.0);
	h_tof_90deg_400ms  = h_tof_90deg_400ms->Add(h_tof_BR_400ms,1.0);
	h_tof_90deg_500ms  = h_tof_90deg_500ms->Add(h_tof_BR_500ms,1.0);
	h_tof_90deg_600ms  = h_tof_90deg_600ms->Add(h_tof_BR_600ms,1.0);
	
	h_tof_180deg_100ms  = h_tof_180deg_100ms->Add(h_tof_LR_100ms,1.0);
	h_tof_180deg_200ms  = h_tof_180deg_200ms->Add(h_tof_LR_200ms,1.0);
	h_tof_180deg_300ms  = h_tof_180deg_300ms->Add(h_tof_LR_300ms,1.0);
	h_tof_180deg_400ms  = h_tof_180deg_400ms->Add(h_tof_LR_400ms,1.0);
	h_tof_180deg_500ms  = h_tof_180deg_500ms->Add(h_tof_LR_500ms,1.0);
	h_tof_180deg_600ms  = h_tof_180deg_600ms->Add(h_tof_LR_600ms,1.0);
	
	h_tof_180deg_100ms  = h_tof_180deg_100ms->Add(h_tof_BT_100ms,1.0);
	h_tof_180deg_200ms  = h_tof_180deg_200ms->Add(h_tof_BT_200ms,1.0);
	h_tof_180deg_300ms  = h_tof_180deg_300ms->Add(h_tof_BT_300ms,1.0);
	h_tof_180deg_400ms  = h_tof_180deg_400ms->Add(h_tof_BT_400ms,1.0);
	h_tof_180deg_500ms  = h_tof_180deg_500ms->Add(h_tof_BT_500ms,1.0);
	h_tof_180deg_600ms  = h_tof_180deg_600ms->Add(h_tof_BT_600ms,1.0);
	
	printf(" 90 degree events = %f\n",  h_tof_90deg_100ms->GetEntries() + h_tof_90deg_200ms->GetEntries() + h_tof_90deg_300ms->GetEntries() + h_tof_90deg_400ms->GetEntries() + h_tof_90deg_500ms->GetEntries() + h_tof_90deg_600ms->GetEntries());
	printf("180 degree events = %f\n", h_tof_180deg_100ms->GetEntries() +h_tof_180deg_200ms->GetEntries() +h_tof_180deg_300ms->GetEntries() +h_tof_180deg_400ms->GetEntries() +h_tof_180deg_500ms->GetEntries() +h_tof_180deg_600ms->GetEntries());
	
//	h_tof_90deg_1st_minus_2nd      = h_tof_90deg_1st_minus_2nd	   ->Add(h_tof_90deg_1st_3s_after_capt,1.0);
//	h_tof_90deg_1st_minus_2nd      = h_tof_90deg_1st_minus_2nd	   ->Add(h_tof_90deg_2nd_3s_after_capt,-1.0);
//	h_tof_180deg_1st_minus_2nd     = h_tof_180deg_1st_minus_2nd	   ->Add(h_tof_180deg_1st_3s_after_capt,1.0);
//	h_tof_180deg_1st_minus_2nd     = h_tof_180deg_1st_minus_2nd	   ->Add(h_tof_180deg_2nd_3s_after_capt,-1.0);
	
	Int_t rebin = 50;
	Int_t smooth = 3;
	Float_t xMin = 1500.0;
	Float_t xMax = 5000.0;
	Float_t yMax90  = rebin/10.0;
	Float_t yMax180 = rebin/0.70;
	
// Draw 90deg spectra
	TCanvas *c_90deg_tof_by_tcapt = new TCanvas("c_90deg_tof_by_tcapt","TOF Spectra (90-degree combos) binned by time since capture",945,600);
	h_tof_90deg_100ms = drawPrep(h_tof_90deg_100ms, rebin, smooth, xMax, yMax90);
	h_tof_90deg_200ms = drawPrep(h_tof_90deg_200ms, rebin, smooth, xMax, yMax90);
	h_tof_90deg_300ms = drawPrep(h_tof_90deg_300ms, rebin, smooth, xMax, yMax90);
	h_tof_90deg_400ms = drawPrep(h_tof_90deg_400ms, rebin, smooth, xMax, yMax90);
	h_tof_90deg_500ms = drawPrep(h_tof_90deg_500ms, rebin, smooth, xMax, yMax90);
	h_tof_90deg_600ms = drawPrep(h_tof_90deg_600ms, rebin, smooth, xMax, yMax90);
	h_tof_90deg_100ms->Draw("HIST");
	h_tof_90deg_200ms->Draw("HISTSAME");
	h_tof_90deg_300ms->Draw("HISTSAME");
	h_tof_90deg_400ms->Draw("HISTSAME");
	h_tof_90deg_500ms->Draw("HISTSAME");
	h_tof_90deg_600ms->Draw("HISTSAME");
	
	c_90deg_tof_by_tcapt->SetFillColor(20);
	h_tof_90deg_100ms->SetLineColor(kYellow);
	h_tof_90deg_200ms->SetLineColor(kOrange);
	h_tof_90deg_300ms->SetLineColor(kRed);
	h_tof_90deg_400ms->SetLineColor(kViolet);
	h_tof_90deg_500ms->SetLineColor(kBlue);
	h_tof_90deg_600ms->SetLineColor(kGreen+2);
	
	TLegend *leg_1 = new TLegend(0.78, 0.44, 0.98, 0.775);
	leg_1->AddEntry(h_tof_90deg_100ms,"  0-100ms");
	leg_1->AddEntry(h_tof_90deg_200ms,"100-200ms");
	leg_1->AddEntry(h_tof_90deg_300ms,"200-300ms");
	leg_1->AddEntry(h_tof_90deg_400ms,"300-400ms");
	leg_1->AddEntry(h_tof_90deg_500ms,"400-500ms");
	leg_1->AddEntry(h_tof_90deg_600ms,"500-600ms");
	leg_1->SetFillColor(20);
	leg_1->Draw();
	gPad->Update();
	
// Draw 180deg spectra
	TCanvas *c_180deg_tof_by_tcapt = new TCanvas("c_180deg_tof_by_tcapt","TOF Spectra (180-degree combos) binned by time since capture",945,600);
	
	Int_t rescale = 1;
	
	if (rescale == 1) {
		Int_t beta_t_low = 2*(xMin-TOFMin)+1;
		Int_t beta_t_hi = 2*(xMax-TOFMin)+1;
		Double_t area100 = h_tof_180deg_100ms->Integral(beta_t_low, beta_t_hi);
		Double_t area200 = h_tof_180deg_200ms->Integral(beta_t_low, beta_t_hi);
		Double_t area300 = h_tof_180deg_300ms->Integral(beta_t_low, beta_t_hi);
		Double_t area400 = h_tof_180deg_400ms->Integral(beta_t_low, beta_t_hi);
		Double_t area500 = h_tof_180deg_500ms->Integral(beta_t_low, beta_t_hi);
		Double_t area600 = h_tof_180deg_600ms->Integral(beta_t_low, beta_t_hi);
		
		printf("100 = %f\n",area100);
		printf("200 = %f\n",area200);
		printf("300 = %f\n",area300);
		printf("400 = %f\n",area400);
		printf("500 = %f\n",area500);
		printf("600 = %f\n",area600);
		printf("100/600 = %f\n",area100/area600);
		
		h_tof_180deg_100ms->Scale(area100/area100);
		h_tof_180deg_200ms->Scale(area100/area200);
		h_tof_180deg_300ms->Scale(area100/area300);
		h_tof_180deg_400ms->Scale(area100/area400);
		h_tof_180deg_500ms->Scale(area100/area500);
		h_tof_180deg_600ms->Scale(area100/area600);
	}	
		
	h_tof_180deg_100ms = drawPrep(h_tof_180deg_100ms, rebin, smooth, xMax, yMax180);
	h_tof_180deg_200ms = drawPrep(h_tof_180deg_200ms, rebin, smooth, xMax, yMax180);
	h_tof_180deg_300ms = drawPrep(h_tof_180deg_300ms, rebin, smooth, xMax, yMax180);
	h_tof_180deg_400ms = drawPrep(h_tof_180deg_400ms, rebin, smooth, xMax, yMax180);
	h_tof_180deg_500ms = drawPrep(h_tof_180deg_500ms, rebin, smooth, xMax, yMax180);
	h_tof_180deg_600ms = drawPrep(h_tof_180deg_600ms, rebin, smooth, xMax, yMax180);
	h_tof_180deg_100ms->Draw("HIST");
	h_tof_180deg_200ms->Draw("HISTSAME");
	h_tof_180deg_300ms->Draw("HISTSAME");
	h_tof_180deg_400ms->Draw("HISTSAME");
	h_tof_180deg_500ms->Draw("HISTSAME");
	h_tof_180deg_600ms->Draw("HISTSAME");
    
	c_180deg_tof_by_tcapt->SetFillColor(20);
	h_tof_180deg_100ms->SetLineColor(kYellow);
	h_tof_180deg_200ms->SetLineColor(kOrange);
	h_tof_180deg_300ms->SetLineColor(kRed);
	h_tof_180deg_400ms->SetLineColor(kViolet);
	h_tof_180deg_500ms->SetLineColor(kBlue);
	h_tof_180deg_600ms->SetLineColor(kGreen+2);
    
    TLegend *leg_2 = new TLegend(0.78, 0.44, 0.98, 0.775);
	leg_2->AddEntry(h_tof_180deg_100ms,"  0-100ms");
	leg_2->AddEntry(h_tof_180deg_200ms,"100-200ms");
	leg_2->AddEntry(h_tof_180deg_300ms,"200-300ms");
	leg_2->AddEntry(h_tof_180deg_400ms,"300-400ms");
	leg_2->AddEntry(h_tof_180deg_500ms,"400-500ms");
	leg_2->AddEntry(h_tof_180deg_600ms,"500-600ms");
	leg_2->SetFillColor(20);
	leg_2->Draw();
	gPad->Update();
	
// Write histos to file
	TFile *outfile = new TFile("tof_by_time_since_capt_134sb0103.root","RECREATE");
	
	outfile->WriteTObject(h_tof_LT_100ms);
	outfile->WriteTObject(h_tof_LT_200ms);
	outfile->WriteTObject(h_tof_LT_300ms);
	outfile->WriteTObject(h_tof_LT_400ms);
	outfile->WriteTObject(h_tof_LT_500ms);
	outfile->WriteTObject(h_tof_LT_600ms);
	
	outfile->WriteTObject(h_tof_LR_100ms);
	outfile->WriteTObject(h_tof_LR_200ms);
	outfile->WriteTObject(h_tof_LR_300ms);
	outfile->WriteTObject(h_tof_LR_400ms);
	outfile->WriteTObject(h_tof_LR_500ms);
	outfile->WriteTObject(h_tof_LR_600ms);
	
	outfile->WriteTObject(h_tof_BT_100ms);
	outfile->WriteTObject(h_tof_BT_200ms);
	outfile->WriteTObject(h_tof_BT_300ms);
	outfile->WriteTObject(h_tof_BT_400ms);
	outfile->WriteTObject(h_tof_BT_500ms);
	outfile->WriteTObject(h_tof_BT_600ms);
	
	outfile->WriteTObject(h_tof_BR_100ms);
	outfile->WriteTObject(h_tof_BR_200ms);
	outfile->WriteTObject(h_tof_BR_300ms);
	outfile->WriteTObject(h_tof_BR_400ms);
	outfile->WriteTObject(h_tof_BR_500ms);
	outfile->WriteTObject(h_tof_BR_600ms);
	
	outfile->WriteTObject(h_tof_90deg_100ms);
	outfile->WriteTObject(h_tof_90deg_200ms);
	outfile->WriteTObject(h_tof_90deg_300ms);
	outfile->WriteTObject(h_tof_90deg_400ms);
	outfile->WriteTObject(h_tof_90deg_500ms);
	outfile->WriteTObject(h_tof_90deg_600ms);
	
	outfile->WriteTObject(h_tof_180deg_100ms);
	outfile->WriteTObject(h_tof_180deg_200ms);
	outfile->WriteTObject(h_tof_180deg_300ms);
	outfile->WriteTObject(h_tof_180deg_400ms);
	outfile->WriteTObject(h_tof_180deg_500ms);
	outfile->WriteTObject(h_tof_180deg_600ms);
	
	outfile->WriteTObject(c_90deg_tof_by_tcapt);
	outfile->WriteTObject(c_180deg_tof_by_tcapt);
	
	outfile->Close();
	
	printf("\ntof_by_time_since_capt_134sb0103 done.\n\n");
	
}

TH1* drawPrep (TH1 *hist, Int_t rebin, Int_t smooth, Float_t xMax, Float_t yMax) {
	hist->Rebin(rebin);
	hist->Smooth(smooth);
	hist->GetXaxis()->SetRangeUser(-1000,xMax);
	hist->GetYaxis()->SetRangeUser(0,yMax);
}

void extrapolate_mcp_phds ()
{
// USER MUST ALTER HARD-CODED SECTIONS WHERE INDICATED
// This function draws a line on top of an expanded-range version of the four MCP post PHD's
// The purpose is to show that the correction for lost too-large pulses makes sense
// Set the file you want to "bdn.root" in this directory
// Choose which data you want to use.
// Run this function.
	
	printf("\nextrapolate_mcp_phds started.");
	TFile *tfile		= new TFile(filename);
	
// ***** CHOOSE WHICH HISTOS TO COPY -- R or T ***** //
//	TH1I *hA_src = (TH1I*)tfile->Get("ha_R_mcpA");
//	TH1I *hB_src = (TH1I*)tfile->Get("ha_R_mcpB");
//	TH1I *hC_src = (TH1I*)tfile->Get("ha_R_mcpC");
//	TH1I *hD_src = (TH1I*)tfile->Get("ha_R_mcpD");
	TH1I *hA_src = (TH1I*)tfile->Get("ha_T_mcpA");
	TH1I *hB_src = (TH1I*)tfile->Get("ha_T_mcpB");
	TH1I *hC_src = (TH1I*)tfile->Get("ha_T_mcpC");
	TH1I *hD_src = (TH1I*)tfile->Get("ha_T_mcpD");
	
	// MCP post PHD's with expanded range (up to "ADC Channel" of 8000)
	TH1I *hA = new TH1I("h_mcp_phd_A_ext","Extrapolation of MCP Post A PHD",80000,0,80000);
	TH1I *hB = new TH1I("h_mcp_phd_B_ext","Extrapolation of MCP Post B PHD",80000,0,80000);
	TH1I *hC = new TH1I("h_mcp_phd_C_ext","Extrapolation of MCP Post C PHD",80000,0,80000);
	TH1I *hD = new TH1I("h_mcp_phd_D_ext","Extrapolation of MCP Post D PHD",80000,0,80000);
	
// ***** CHOOSE A DATA SET ***** //	
// Parameters to describe the line that extends the PHD's on a log scale
// - slope and yInt are for a line in (base-10 log of y) vs ADC channel
// - I have used channel 3000 to 4000 so far.
// - index 0, 1, 2, 3 = MCP A, B, C, D 
// ***************************** //
	
	// Alpha source, Right MCP (238Pu_R_mcp_NoMask.root)
//	Double_t slope [4] = {-0.00020189852, -0.00016960913, -0.00036797679, -0.00021788256};
//	Double_t xInt  [4] = {18196.7, 21417.9, 11607.4, 16940.7};
//	Double_t yInt  [4] = {3.67388, 3.63268, 4.27125, 3.69107};
//	Double_t mean  [4] = {6640.1, 5267.2, 6072.8, 6093.3};
//	Double_t sigma [4] = {2084.1, 2491.9, 1138.1, 1926.1};
	
	// Alpha source, Top MCP (238Pu_T_mcp_NoMask.root)
	Double_t slope [4] = {0, 0, -0.00030616964, 0};
	Double_t xInt  [4] = {10000, 10000, 9301.8, 10000};
	Double_t yInt  [4] = {1, 1, 2.8479278, 1};
	Double_t mean  [4] = {0, 0, 5518.5, 0};
	Double_t sigma [4] = {1, 1, 1126.7, 1};
	
// ***** END OF DATA SETS ***** //
	
	// Functions to use the above params
	TF1 *fA = new TF1("fA", "TMath::Power(10.0,[0]+[1]*x)", 0, xInt[0]);
	TF1 *fB = new TF1("fB", "TMath::Power(10.0,[0]+[1]*x)", 0, xInt[1]);
	TF1 *fC = new TF1("fC", "TMath::Power(10.0,[0]+[1]*x)", 0, xInt[2]);
	TF1 *fD = new TF1("fD", "TMath::Power(10.0,[0]+[1]*x)", 0, xInt[3]);
	
	fA->SetParameters(yInt[0], slope[0]);
	fB->SetParameters(yInt[1], slope[1]);
	fC->SetParameters(yInt[2], slope[2]);
	fD->SetParameters(yInt[3], slope[3]);
	
	for (Int_t i = 1; i<=8000; i++ ) {
		hA->SetBinContent(i, hA_src->GetBinContent(i));
		hB->SetBinContent(i, hB_src->GetBinContent(i));
		hC->SetBinContent(i, hC_src->GetBinContent(i));
		hD->SetBinContent(i, hD_src->GetBinContent(i));
		hA->SetEntries(hA_src->GetEntries());
		hB->SetEntries(hB_src->GetEntries());
		hC->SetEntries(hC_src->GetEntries());
		hD->SetEntries(hD_src->GetEntries());
	}
	
	TCanvas *c_extrapolate_mcp_phds = new TCanvas("c_extrapolate_mcp_phds","MCP PHD's",945,600);
	c_extrapolate_mcp_phds->Divide(2,2);
	
	c_extrapolate_mcp_phds->cd(1);
	c_extrapolate_mcp_phds_1->SetLogy();
	hA->Draw();
	hA->GetXaxis()->SetRangeUser(0,xInt[0]);
	fA->Draw("SAME");
	
	c_extrapolate_mcp_phds->cd(2);
	c_extrapolate_mcp_phds_2->SetLogy();
	hB->Draw();
	hB->GetXaxis()->SetRangeUser(0,xInt[1]);
	fB->Draw("SAME");
	
	c_extrapolate_mcp_phds->cd(3);
	c_extrapolate_mcp_phds_3->SetLogy();
	hC->Draw();
	hC->GetXaxis()->SetRangeUser(0,xInt[2]);
	fC->Draw("SAME");
	
	c_extrapolate_mcp_phds->cd(4);
	c_extrapolate_mcp_phds_4->SetLogy();
	hD->Draw();
	hD->GetXaxis()->SetRangeUser(0,xInt[3]);
	fD->Draw("SAME");
	
	printf("\nextrapolate_mcp_phds done.\n\n");
}

void find_mcp_threshold ()
{	
	printf("\nfind_mcp_threshold started.");
	TFile *tfile = new TFile(filename);
	
	TH1I *hR = (TH1I*)tfile->Get("ha_R_mcpSum");
	TH1I *hT = (TH1I*)tfile->Get("ha_T_mcpSum");
	
	Int_t xMin = 250, xMax = 6000;
	
	TF1 *fn = new TF1("fn",thresh_peak,xMin,xMax,6);
	TF1 *g  = new TF1("g","gaus",1000,3000);
	g->SetParameters(1400,2700,1800);
	fn->SetParNames("bin width", "amplitude parameter", "threshold location", "threshold width", "underlying peak location", "underlying peak width");
	fn->SetParameters(1, 180000, 770, 330, 2500, 3000);
	fn->FixParameter(0,1);
	
//	hR->Fit("fn","QIROMESLL");
	hR->Fit("g","QIROMESLL");
	
	TCanvas *c_find_mcp_threshold = new TCanvas("c_find_mcp_threshold","MCP Threshold Fit",945,600);
//	c_find_mcp_threshold->SetLogy();
	hR->Draw();
	hR->GetXaxis()->SetRangeUser(xMin,xMax);
//	fn->Draw("SAME");
	//g->Draw("SAME");
	
	printf("\nfind_mcp_threshold done.");
}

Double_t thresh_peak (Double_t *x, Double_t *a)
{
	//a[0] = bin width
	//a[1] = amplitude parameter
	//a[2] = threshold location
	//a[3] = threshold width
	//a[4] = gaussian peak location
	//a[5] = gaussian peak width
	Double_t erf = 0.5*(1.0+TMath::Erf((x[0]-a[2])/a[3]));
	Double_t gaus = TMath::Exp(-0.5*((x[0]-a[4])/a[5])**2.0)/TMath::Sqrt(2.0*TMath::Pi()*a[5]);
	return a[0]*a[1]*erf*gaus;// I always use a[0] account for binning
}

void draw_slow_recoils_vs_rf_phase ()
{	
	printf("\ndraw_slow_recoils_vs_rf_phase started.");
	TFile *tfile = new TFile(filename);
	
	TH1I *hPhObs	= (TH1I*)tfile->Get("h_slow_vs_rf_phase_observed");
	TH1I *hPhObs_LT	= (TH1I*)tfile->Get("h_LT_slow_vs_rf_phase_observed");
	TH1I *hPhObs_LR	= (TH1I*)tfile->Get("h_LR_slow_vs_rf_phase_observed");
	TH1I *hPhObs_BT	= (TH1I*)tfile->Get("h_BT_slow_vs_rf_phase_observed");
	TH1I *hPhObs_BR	= (TH1I*)tfile->Get("h_BR_slow_vs_rf_phase_observed");
	
// Slow ions vs RF phase
	TH1D *hPh		= (TH1D*)tfile->Get("h_slow_vs_rf_phase");
	TH1D *hPh_LT	= (TH1D*)tfile->Get("h_LT_slow_vs_rf_phase");
	TH1D *hPh_LR	= (TH1D*)tfile->Get("h_LR_slow_vs_rf_phase");
	TH1D *hPh_BT	= (TH1D*)tfile->Get("h_BT_slow_vs_rf_phase");
	TH1D *hPh_BR	= (TH1D*)tfile->Get("h_BR_slow_vs_rf_phase");
// Accidentals vs RF phase
	TH1D *hAcc		= (TH1D*)tfile->Get("h_oops_vs_rf_phase");
	TH1D *hAcc_LT	= (TH1D*)tfile->Get("h_LT_oops_vs_rf_phase");
	TH1D *hAcc_LR	= (TH1D*)tfile->Get("h_LR_oops_vs_rf_phase");
	TH1D *hAcc_BT	= (TH1D*)tfile->Get("h_BT_oops_vs_rf_phase");
	TH1D *hAcc_BR	= (TH1D*)tfile->Get("h_BR_oops_vs_rf_phase");
	
//	TH1I *hPh		= (TH1I*)tfile->Get("h_bkgd_slow_vs_rf_phase_observed");
//	TH1I *hPh_LT	= (TH1I*)tfile->Get("h_bkgd_LT_slow_vs_rf_phase_observed");
//	TH1I *hPh_LR	= (TH1I*)tfile->Get("h_bkgd_LR_slow_vs_rf_phase_observed");
//	TH1I *hPh_BT	= (TH1I*)tfile->Get("h_bkgd_BT_slow_vs_rf_phase_observed");
//	TH1I *hPh_BR	= (TH1I*)tfile->Get("h_bkgd_BR_slow_vs_rf_phase_observed");
	TCanvas *c_slow_recoils_vs_rf_phase = new TCanvas("c_slow_recoils_vs_rf_phase","Slow recoil rates versus RF phase",945,600);
	hPh->Draw("hist");
	
// Subtract accidentals
	TH1D *hPhNet	= hPh		-> Clone("hPhNet");
	TH1D *hPhNet_LT	= hPh_LT	-> Clone("hPhNet_LT");
	TH1D *hPhNet_LR	= hPh_LR	-> Clone("hPhNet_LR");
	TH1D *hPhNet_BT = hPh_BT	-> Clone("hPhNet_BT");
	TH1D *hPhNet_BR = hPh_BR	-> Clone("hPhNet_BR");
	
	hPhNet		-> SetTitle("Slow recoils vs (RF Phase / 2pi), Trap Full, Accidentals Subtracted");
	hPhNet_LT	-> SetTitle("LT Slow recoils vs (RF Phase / 2pi), Trap Full, Accidentals Subtracted");
	hPhNet_LR	-> SetTitle("LR Slow recoils vs (RF Phase / 2pi), Trap Full, Accidentals Subtracted");
	hPhNet_BT	-> SetTitle("BT Slow recoils vs (RF Phase / 2pi), Trap Full, Accidentals Subtracted");
	hPhNet_BR	-> SetTitle("BR Slow recoils vs (RF Phase / 2pi), Trap Full, Accidentals Subtracted");
	
	Double_t SlowToAccRatio = ((double)(tof_slow_hi - tof_slow_lo))/(tof_oops_hi - tof_oops_lo);
	printf("\n\nUsing Ratio of TOF interval (Slow/Acc) = %f\n\n", SlowToAccRatio);
	hPhNet		-> Add(hAcc,	-SlowToAccRatio);
	hPhNet_LT	-> Add(hAcc_LT,	-SlowToAccRatio);
	hPhNet_LR	-> Add(hAcc_LR,	-SlowToAccRatio);
	hPhNet_BT	-> Add(hAcc_BT,	-SlowToAccRatio);
	hPhNet_BR	-> Add(hAcc_BR,	-SlowToAccRatio);
	
	Int_t rebin = 5;
	hPhNet		->	Rebin(rebin);
	hPhNet_LT	->	Rebin(rebin);
	hPhNet_LR	->	Rebin(rebin);
	hPhNet_BT	->	Rebin(rebin);
	hPhNet_BR	->	Rebin(rebin);
	
	hPhNet_LT->SetLineColor(kRed);
	hPhNet_LR->SetLineColor(kBlue);
	hPhNet_BT->SetLineColor(kOrange+1);
	hPhNet_BR->SetLineColor(kGreen+1);
	
	TCanvas *c_accidentals_vs_rf_phase = new TCanvas("c_accidentals_vs_rf_phase","Accidental rates versus RF phase",945,600);
//	hAcc	-> Rebin(rebin);
//	hAcc	-> Draw("hist");
	hPh		-> Rebin(rebin);
	hPh		-> Draw("hist");
	
	TCanvas *c_slow_recoils_vs_rf_phase = new TCanvas("c_slow_recoils_vs_rf_phase","Slow recoil rates versus RF phase",945,600);
	hPhNet->Draw("hist");
	
	TCanvas *c_slow_recoils_vs_rf_phase_combos = new TCanvas("c_slow_recoils_vs_rf_phase_combos","Slow recoil rates versus RF phase, by combo",945,600);
	hPhNet_LR->GetXaxis()->SetRangeUser(-0.6,0.6);
	hPhNet_LR->Draw("hist");
	hPhNet_BT->Draw("hist same");
	hPhNet_BR->Draw("hist same");
	hPhNet_LT->Draw("hist same");
	
	TLegend *leg_1 = new TLegend(0.85, 0.64, 0.98, 0.775);
	leg_1->AddEntry(hPh_LR,"LR (180deg)");
	leg_1->AddEntry(hPh_BT,"BT (180deg)");
	leg_1->AddEntry(hPh_BR,"BR (90deg)");
	leg_1->AddEntry(hPh_LT,"LT (90deg)");
	leg_1->SetFillColor(20);
	leg_1->Draw();
	gPad->Update();
	
	cout << "All slows (no deadtime corr.) = " << hPhObs-> Integral() << endl;
	cout << "All slows (w/ deadtime corr.) = " << hPh	-> Integral() << endl;
	cout << "Accidentals = " << hAcc   -> Integral() << endl;
	cout << "Net slows   = " << hPhNet -> Integral() << endl;
	
	printf("\ndraw_slow_recoils_vs_rf_phase done.\n\n");
}

void draw_En_and_vInv_spectra ()
{	
	printf("\ndraw_En_and_vInv_spectra started.\n");
	TFile *tfile = new TFile(filename);
	
	Double_t c		= 299792.46; // mm/us
	Double_t rMean	= 55.7222; // mm
	Double_t massFactor	= 17057609613.0; // keV, m_ion^2/m_neutron, 137i
//	Double_t massFactor	= 126595730.0; // keV, m_ion^2/m_neutron, 137i
	
	TH1::SetDefaultSumw2(kTRUE);
	TH1D *hTOF		= tfile->Get("h_tof");
	TH1D *hv		= tfile->Get("h_v");
	TH1D *hv_LT		= tfile->Get("h_v_LT");
	TH1D *hv_LR		= tfile->Get("h_v_LR");
	TH1D *hv_BT		= tfile->Get("h_v_BT");
	TH1D *hv_BR		= tfile->Get("h_v_BR");
	TH1D *hvInv		= tfile->Get("h_vInv");
	TH1D *hvInv_LT	= tfile->Get("h_vInv_LT");
	TH1D *hvInv_LR	= tfile->Get("h_vInv_LR");
	TH1D *hvInv_BT	= tfile->Get("h_vInv_BT");
	TH1D *hvInv_BR	= tfile->Get("h_vInv_BR");
	TH1D *hEn		= tfile->Get("h_En");
	TH1D *hEn_LT	= tfile->Get("h_En_LT");
	TH1D *hEn_LR	= tfile->Get("h_En_LR");
	TH1D *hEn_BT	= tfile->Get("h_En_BT");
	TH1D *hEn_BR	= tfile->Get("h_En_BR");
	
//	TH1D *hEnNet	= (TH1D*)hEn->Clone("hEnNet");
//	hEnNet			-> SetTitle("Neutron energy (keV) w/ accidentals subtracted");
	
// Make histo with floating point entries for background subtraction	
	TH1D *hEnNet = new TH1D("hEnNet","Neutron energy (keV) w/ accidentals subtracted",EnBins,EnMin,EnMax);
	for (Int_t bin = 1; bin <= EnBins; bin++) hEnNet->SetBinContent(bin,hEn->GetBinContent(bin));
//	Double_t hEnNetArea = hEnNet->Integral(1200,3000);
//	cout << "Histo area = " << hEnNetArea << endl;
	
// Calculate background using flat part of TOF spectrum	
	Int_t EnRebin = 10; // keV
	Double_t tof1 = 14000.0;//tof_slow_lo;
	Double_t tof2 = 21000.0;//tof_slow_hi;
	Int_t tofBin1	= TMath::Floor(2*(tof1-TOFMin)+1);
	Int_t tofBin2	= TMath::Floor(2*(tof2-TOFMin)+1);
	Double_t EnBinWidth = EnRebin*(EnMax-EnMin)/EnBins;
	Double_t TOFSampleN = hTOF->Integral(tofBin1, tofBin2);
	Double_t TOFInterval= (tof2 - tof1)/1000.0; // counts/us
	Double_t TOFBkgd	= 1000.0*TOFSampleN/(tof2 - tof1); // counts/us
	TF1 *fnEnBkgd	= new TF1("fn_EnBkgd","[0]*[1]*[2]*[3]*sqrt([4]/(2*x)^3)", 0.1, EnMax);
	fnEnBkgd->SetParameters(EnBinWidth, TOFBkgd, rMean, 1.0/c, massFactor);
	
// Subtract background
	hEnNet		-> Rebin(EnRebin);
	hEnNet		-> Add(fnEnBkgd, -1.0);
	
	printf("%f cts in %f ns\n", TOFSampleN, 1000.0*TOFInterval);
	printf("TOF Background = %f cts/us\n", TOFBkgd);
	printf("Bin width = %f keV\n", EnBinWidth);
	
	char yAxisTitle[100];
	sprintf(yAxisTitle, "counts / %d keV", (int)EnBinWidth);
	
	gStyle->SetOptStat("e");
//	TCanvas *c_En_combos = new TCanvas("c_En_combos","En spectra by combo",1600,1000);
//	
//	c_En_combos->Divide(2,2);
//	
//	c_En_combos->cd(1);
//	c_En_combos_1->SetLogy();
//	h_En_LT->Draw();
//	
//	c_En_combos->cd(2);
//	c_En_combos_2->SetLogy();
//	h_En_LR->Draw();
//	
//	c_En_combos->cd(3);
//	c_En_combos_3->SetLogy();
//	h_En_BT->Draw();
//	
//	c_En_combos->cd(4);
//	c_En_combos_4->SetLogy();
//	h_En_BR->Draw();
	
	Double_t xMin 		= 0.0;//-100.0;
	Double_t xMax 		= 1500.0;
	Double_t yMin		= 0.0;
	Double_t yMax		= EnBinWidth * 10.0;
	Double_t yMinNet	=-EnBinWidth * 4.0;
	Double_t yMaxNet	= EnBinWidth * 8.0;
	
	Double_t EnThresh	= 100; // keV
	Double_t EnMinBin	= (EnThresh-EnMin) / EnBinWidth + 1;
	Double_t EnMaxBin	= (EnMax-EnMin) / EnBinWidth;
	printf("Integrating spectrum from bin %d to bin %d\n", EnMinBin, EnMaxBin);
	
	TCanvas *c_En = new TCanvas("c_En","Neutron energy spectrum",945,600);
	hEn			-> Rebin(EnRebin);
	hEn			-> GetXaxis()->SetTitle("keV");
	hEn			-> GetXaxis()->CenterTitle();
	hEn			-> GetYaxis()->SetTitle(yAxisTitle);
	hEn			-> GetYaxis()->CenterTitle();
	hEn			-> GetYaxis()->SetTitleOffset(1.5);
	hEn			-> GetXaxis()->SetRangeUser(xMin,xMax);
	hEn			-> GetYaxis()->SetRangeUser(yMin, yMax);
	hEn			-> Draw();
	fnEnBkgd	-> Draw("same");
	
//	gStyle->SetOptStat("");
	TCanvas *c_EnNet = new TCanvas("c_EnNet","Neutron energy spectrum",945,600);
//	c_find_mcp_threshold->SetLogy();
//	hEnNet		-> Rebin(EnRebin);
	hEnNet		-> GetXaxis()->SetTitle("keV");
	hEnNet		-> GetXaxis()->CenterTitle();
	hEnNet		-> GetYaxis()->SetTitle(yAxisTitle);
	hEnNet		-> GetYaxis()->CenterTitle();
	hEnNet		-> GetYaxis()->SetTitleOffset(1.2);
	hEnNet		-> GetXaxis()->SetRangeUser(xMin,xMax);
//	hEnNet		-> GetYaxis()->SetRangeUser(yMinNet, yMaxNet);
	hEnNet		-> GetYaxis()->SetRangeUser(yMin, yMax);
	hEnNet		-> SetEntries( hEnNet->Integral(EnMinBin,EnMaxBin) );
	hEnNet		-> Draw();
	
	Int_t graph = 1;
	if (graph) {
		const int nPoints = 200;
		double x[nPoints], y[nPoints];
		
//		GetGraphXY("NeutronSpectra/137iKratz.csv_transposed", nPoints, x, y);
//		GetGraphXY("NeutronSpectra/135sbKratz.csv_transposed", nPoints, x, y);
//		GetGraphXY("NeutronSpectra/135sbShalev.csv_transposed", nPoints, x, y);
//		GetGraphXY("NeutronSpectra/138iShalev.csv_transposed", nPoints, x, y);
		GetGraphXY("NeutronSpectra/138iGreenwood.csv_transposed", nPoints, x, y);
		
		TGraph *gr0 = new TGraph(nPoints,x,y);
		Double_t graphArea = gr0->Integral();
		cout << "Graph area = " << graphArea << endl;
		Double_t hEnNetArea = hEnNet->Integral((200-EnMin)/EnBinWidth+1,(2000-EnMin)/EnBinWidth+1);
		cout << "Histo area = " << hEnNetArea << endl;
		for (Int_t i = 0; i<nPoints; i++) y[i] = EnBinWidth * (hEnNetArea/graphArea) * y[i];
		TGraph *gr1 = new TGraph(nPoints,x,y);
		gr1->SetLineColor(kRed);
		gr1->SetLineWidth(2);
		gr1->Draw("same");
	}
	
//	TFile *outfile = new TFile("En_v_vInv_spectra_137i07_noGridCorrection.root","recreate");
//	outfile->WriteTObject(hEn);
//	outfile->WriteTObject(hEn_LT);
//	outfile->WriteTObject(hEn_LR);
//	outfile->WriteTObject(hEn_BT);
//	outfile->WriteTObject(hEn_BR);
//	outfile->WriteTObject(hv);
//	outfile->WriteTObject(hv_LT);
//	outfile->WriteTObject(hv_LR);
//	outfile->WriteTObject(hv_BT);
//	outfile->WriteTObject(hv_BR);
//	outfile->WriteTObject(hTOF);
//	outfile->WriteTObject(hEn_LT);
//	outfile->WriteTObject(hEn_LR);
//	outfile->WriteTObject(hEn_BT);
//	outfile->WriteTObject(hEn_BR);
//	outfile->WriteTObject(hvInv);
//	outfile->WriteTObject(hvInv_LT);
//	outfile->WriteTObject(hvInv_LR);
//	outfile->WriteTObject(hvInv_BT);
//	outfile->WriteTObject(hvInv_BR);
//	outfile->Close();
	
	printf("\ndraw_En_and_vInv_spectra done.\n\n");
}

void GetGraphXY (char *filename, Int_t nPoints, Double_t x[], Double_t y[]) {//TGraph *graph) {
//	const int nPoints = 200;
//	double x[nPoints], y[nPoints];
	ifstream file (filename);
	string line, value;
	stringstream linestream;
// Check if the file opened	
	if (file.good()) printf("File opened: %s\n", filename);
	else printf("Couldn't open file: %s.\n", filename);
	Int_t i;
// Initialize the coord arrays
	for (i = 0; i<nPoints; i++) {
		x[i] = 0.0;
		y[i] = 0.0;
	}
// x coords of known neutron spectrum
// Get first line of file
	std::getline(file, line);
//		cout << line << endl;
	linestream = line; // turn string into stream for processing
	i = 0;
	while (linestream.good())
	{
		std::getline(linestream, value, ',');
		x[i] = atof(value.c_str());
//		cout << i << " " << x[i] << endl;
		i++;
	}
// y coords of known neutron spectrum
// Get second line of file
	std::getline(file, line);
//	cout << line << endl;
	linestream = line; // turn string into stream for processing
	i = 0;
	while (linestream.good())
	{
		std::getline(linestream, value, ',');
		y[i] = atof(value.c_str());
//		cout << i << " " << y[i] << endl;
		i++;
	}
	file.close();
//	for (i = 0; i<nPoints; i++) cout << "Point #: " << i << "; (x,y) = (" << x[i] << "," << y[i] << ")" << endl;
//	*graph = new TGraph(nPoints,x,y);
}
