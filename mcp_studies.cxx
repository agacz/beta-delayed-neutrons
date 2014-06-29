/*
2013-03-08  Shane Caldwell  Created mcp_studies.cxx
	Made from code from mcp_cal.cxx and mcp_studies.cxx.
	New things:
	- Corrections for events where ADC range was exceeded. (These are the same as the events
	  where there was no hit on the hit register.)
	  This correction depends on the shape of the pulse height distribution, so alpha-source
	  data must be corrected differently than ion data.
	  Corrected data are denoted by a _1, eg. rA and rA_1
	- Add rand() to numerator and denominator of x and y coords.
*/

#include <unistd.h>
//#include "stat.h"
#include "stdio.h"
#include "TH1.h"
#include "TFile.h"
#include "TTree.h"
#include "TLeaf.h"
#include "TRandom3.h"
//#include "bdn.h"

void mcp_studies (const char*);

int main (int argc, char *argv[]) {
	while (*++argv) {
		mcp_studies(argv[0]);
	}
	return 0;
}

void mcp_studies (const char *filename) {
	
	printf("\nmcp_studies started.\n");
    printf(filename);
    
	/*****************************************************************/
	/*** Code to include source code as a string in the ROOT file: ***/
	/*****************************************************************
    FILE *fsrc = fopen("mcp_studies.cxx", "r");
    char *fbuf;
    struct stat srcbuf;
	
    stat("mcp_studies.cxx", &srcbuf);
    fbuf = new char [srcbuf.st_size+1];
    fread(fbuf, sizeof(char), srcbuf.st_size, fsrc);
    fbuf[srcbuf.st_size] = '\0';    TString fstr(fbuf);
	/*****************************************************************
	
	printf(fbuf);
*/	
	TFile *f = new TFile(filename, "UPDATE");	
	TTree *tree    = (TTree*)f->Get("bdn_Tree");
	char *dir = "mcp_studies"; // results will be placed in this subdirectory of the root file
	char *dir_cycle = "mcp_studies;1"; // results will be placed in this subdirectory of the root file
	
	// Loop variables:
	const Int_t nEntries = tree->GetEntries();
	Int_t i;
	
	printf("\n%d entries",nEntries);
	
	// Cuts:
	const Int_t t_dE_Lo		= -100;
	const Int_t t_mcp_Lo	= -100;
	
	// To hold values in the event loop:
	Int_t		s_capt_state; // 0 means trap has ions
	Int_t		event_good; // 1 means no data marker mishaps
	Int_t		t_B_dEa, t_B_dEb;
	Int_t		t_L_dEa, t_L_dEb;
	Int_t		t_R_mcp;
	Int_t		t_T_mcp;
	Double_t	tof, dE, A, B, C, D;
	
	// Histograms:
	const float TOFMin	= -1.0; // us
	const float TOFMax	= 22.5; // us
	const Int_t TOFBins	= 23500; // one bin per ns
	
	// To hold values in the event loop:
	Double_t	tA, tB, tC, tD, tSum, tX, tY;
	Double_t	rA, rB, rC, rD, rSum, rX, rY;
	Double_t	tA_1, tB_1, tC_1, tD_1, tSum_1, tX_1, tY_1;
	Double_t	rA_1, rB_1, rC_1, rD_1, rSum_1, rX_1, rY_1;
	
	// Histograms
	const Double_t mapMin	= -25.0;
	const Double_t mapMax	= 25.0;
	const Double_t bin_size_mm = 0.1;
	const Int_t mapBins 	= (mapMax - mapMin)/bin_size_mm;
	
	TH2I *h_T_mcp_map_0	= new TH2I("h_T_mcp_map_0", "Top MCP map w/ all data (no cuts)", mapBins, mapMin, mapMax, mapBins, mapMin, mapMax);
	
	for (i=0; i<nEntries; i++) {
		
		if (i%1000000==0) printf("\nreached event %d",i);
		
		tree->GetEntry(i);
		
		// Values for tests on every event:
		event_good		= (Int_t)tree->GetLeaf("event_good")->GetValue();
		
		if (event_good==0) continue;
			
			// Values for coincidence tests:
			t_B_dEa			= (Int_t)tree->GetLeaf("t_B_dEa")->GetValue();
			t_B_dEb			= (Int_t)tree->GetLeaf("t_B_dEb")->GetValue();
			t_L_dEa			= (Int_t)tree->GetLeaf("t_L_dEa")->GetValue();
			t_L_dEb			= (Int_t)tree->GetLeaf("t_L_dEb")->GetValue();
			t_R_mcp			= (Int_t)tree->GetLeaf("t_R_mcp")->GetValue();
			t_T_mcp			= (Int_t)tree->GetLeaf("t_T_mcp")->GetValue();
			
	// MCP vs dEx alone:
		// Left dEa - Top MCP
			if (t_dE_Lo < t_L_dEa && t_mcp_Lo < t_T_mcp) {
				tof = 0.001*(Double_t)(t_T_mcp - t_L_dEa);
				s_capt_state	= (Int_t)tree->GetLeaf("s_capt_state")->GetValue();
				switch (s_capt_state) {
					case 0: // SIGNAL
						h_tof_LT_a -> Fill(tof);
						dE = (Int_t)tree->GetLeaf("a_L_dEa")->GetValue();
						if (dE > 200) h_tof_LT_a__a_dE_gt200 ->Fill(tof);
						A = (Int_t)tree->GetLeaf("a_T_mcpA")->GetValue();
						B = (Int_t)tree->GetLeaf("a_T_mcpB")->GetValue();
						C = (Int_t)tree->GetLeaf("a_T_mcpC")->GetValue();
						D = (Int_t)tree->GetLeaf("a_T_mcpD")->GetValue();
						if (50<A && 50<B && 50<C && 50<D) h_tof_LT_a__mcp_posts_gt50 -> Fill(tof);
						if (75<A && 75<B && 75<C && 75<D) h_tof_LT_a__mcp_posts_gt75 -> Fill(tof);
						if (99<A && 99<B && 99<C && 99<D) h_tof_LT_a__mcp_posts_gt99 -> Fill(tof);
						if (200<(A+B+C+D)) h_tof_LT_a__mcp_sum_gt200 -> Fill(tof);
						if (300<(A+B+C+D)) h_tof_LT_a__mcp_sum_gt300 -> Fill(tof);
						if (400<(A+B+C+D)) h_tof_LT_a__mcp_sum_gt400 -> Fill(tof);
						break;
					case 1: // BACKGROUND
						h_bkgd_tof_LT_a	-> Fill(tof);
						break;
					default: printf("Event %d: Invalid value s_capt_state = %d\n", i, s_capt_state); break;
				} // switch capt state
			} // if t_dEa and t_mcp
			
		// Left dEb - Top MCP
			if (t_dE_Lo < t_L_dEb && t_mcp_Lo < t_T_mcp) {
				tof = 0.001*(Double_t)(t_T_mcp - t_L_dEb);
				s_capt_state	= (Int_t)tree->GetLeaf("s_capt_state")->GetValue();
				switch (s_capt_state) {
					case 0: // SIGNAL
						h_tof_LT_b -> Fill(tof);
						dE = (Int_t)tree->GetLeaf("a_L_dEb")->GetValue();
						if (dE > 200) h_tof_LT_a__a_dE_gt200 ->Fill(tof);
						A = (Int_t)tree->GetLeaf("a_T_mcpA")->GetValue();
						B = (Int_t)tree->GetLeaf("a_T_mcpB")->GetValue();
						C = (Int_t)tree->GetLeaf("a_T_mcpC")->GetValue();
						D = (Int_t)tree->GetLeaf("a_T_mcpD")->GetValue();
						if (50<A && 50<B && 50<C && 50<D) h_tof_LT_a__mcp_posts_gt50 -> Fill(tof);
						if (75<A && 75<B && 75<C && 75<D) h_tof_LT_a__mcp_posts_gt75 -> Fill(tof);
						if (99<A && 99<B && 99<C && 99<D) h_tof_LT_a__mcp_posts_gt99 -> Fill(tof);
						if (200<(A+B+C+D)) h_tof_LT_a__mcp_sum_gt200 -> Fill(tof);
						if (300<(A+B+C+D)) h_tof_LT_a__mcp_sum_gt300 -> Fill(tof);
						if (400<(A+B+C+D)) h_tof_LT_a__mcp_sum_gt400 -> Fill(tof);
						break;
					case 1: // BACKGROUND
						h_bkgd_tof_LT_a	-> Fill(tof);
						break;
					default: printf("Event %d: Invalid value s_capt_state = %d\n", i, s_capt_state); break;
				} // switch capt state
			} // if t_dEb and t_mcp
			
		// Left dEa - Right MCP
			if (t_dE_Lo < t_L_dEa && t_mcp_Lo < t_R_mcp) {
				tof = 0.001*(Double_t)(t_R_mcp - t_L_dEa);
				s_capt_state	= (Int_t)tree->GetLeaf("s_capt_state")->GetValue();
				switch (s_capt_state) {
					case 0: // SIGNAL
						h_tof_LR_a -> Fill(tof);
						dE = (Int_t)tree->GetLeaf("a_L_dEa")->GetValue();
						if (dE > 200) h_tof_LR_a__a_dE_gt200 ->Fill(tof);
						A = (Int_t)tree->GetLeaf("a_R_mcpA")->GetValue();
						B = (Int_t)tree->GetLeaf("a_R_mcpB")->GetValue();
						C = (Int_t)tree->GetLeaf("a_R_mcpC")->GetValue();
						D = (Int_t)tree->GetLeaf("a_R_mcpD")->GetValue();
						if (50<A && 50<B && 50<C && 50<D) h_tof_LR_a__mcp_posts_gt50 -> Fill(tof);
						if (75<A && 75<B && 75<C && 75<D) h_tof_LR_a__mcp_posts_gt75 -> Fill(tof);
						if (99<A && 99<B && 99<C && 99<D) h_tof_LR_a__mcp_posts_gt99 -> Fill(tof);
						if (200<(A+B+C+D)) h_tof_LR_a__mcp_sum_gt200 -> Fill(tof);
						if (300<(A+B+C+D)) h_tof_LR_a__mcp_sum_gt300 -> Fill(tof);
						if (400<(A+B+C+D)) h_tof_LR_a__mcp_sum_gt400 -> Fill(tof);
						break;
					case 1: // BACKGROUND
						h_bkgd_tof_LR_a	-> Fill(tof);
						break;
					default: printf("Event %d: Invalid value s_capt_state = %d\n", i, s_capt_state); break;
				} // switch capt state
			} // if t_dEa and t_mcp
			
		// Left dEb - Right MCP
			if (t_dE_Lo < t_L_dEb && t_mcp_Lo < t_R_mcp) {
				tof = 0.001*(Double_t)(t_R_mcp - t_L_dEb);
				s_capt_state	= (Int_t)tree->GetLeaf("s_capt_state")->GetValue();
				switch (s_capt_state) {
					case 0: // SIGNAL
						h_tof_LR_b -> Fill(tof);
						dE = (Int_t)tree->GetLeaf("a_L_dEb")->GetValue();
						if (dE > 200) h_tof_LR_a__a_dE_gt200 ->Fill(tof);
						A = (Int_t)tree->GetLeaf("a_R_mcpA")->GetValue();
						B = (Int_t)tree->GetLeaf("a_R_mcpB")->GetValue();
						C = (Int_t)tree->GetLeaf("a_R_mcpC")->GetValue();
						D = (Int_t)tree->GetLeaf("a_R_mcpD")->GetValue();
						if (50<A && 50<B && 50<C && 50<D) h_tof_LR_a__mcp_posts_gt50 -> Fill(tof);
						if (75<A && 75<B && 75<C && 75<D) h_tof_LR_a__mcp_posts_gt75 -> Fill(tof);
						if (99<A && 99<B && 99<C && 99<D) h_tof_LR_a__mcp_posts_gt99 -> Fill(tof);
						if (200<(A+B+C+D)) h_tof_LR_a__mcp_sum_gt200 -> Fill(tof);
						if (300<(A+B+C+D)) h_tof_LR_a__mcp_sum_gt300 -> Fill(tof);
						if (400<(A+B+C+D)) h_tof_LR_a__mcp_sum_gt400 -> Fill(tof);
						break;
					case 1: // BACKGROUND
						h_bkgd_tof_LR_a	-> Fill(tof);
						break;
					default: printf("Event %d: Invalid value s_capt_state = %d\n", i, s_capt_state); break;
				} // switch capt state
			} // if t_dEb and t_mcp
			
		// Bottom dEa - Top MCP
			if (t_dE_Lo < t_B_dEa && t_mcp_Lo < t_T_mcp) {
				tof = 0.001*(Double_t)(t_T_mcp - t_B_dEa);
				s_capt_state	= (Int_t)tree->GetLeaf("s_capt_state")->GetValue();
				switch (s_capt_state) {
					case 0: // SIGNAL
						h_tof_BT_a -> Fill(tof);
						dE = (Int_t)tree->GetLeaf("a_B_dEa")->GetValue();
						if (dE > 200) h_tof_BT_a__a_dE_gt200 ->Fill(tof);
						A = (Int_t)tree->GetLeaf("a_T_mcpA")->GetValue();
						B = (Int_t)tree->GetLeaf("a_T_mcpB")->GetValue();
						C = (Int_t)tree->GetLeaf("a_T_mcpC")->GetValue();
						D = (Int_t)tree->GetLeaf("a_T_mcpD")->GetValue();
						if (50<A && 50<B && 50<C && 50<D) h_tof_BT_a__mcp_posts_gt50 -> Fill(tof);
						if (75<A && 75<B && 75<C && 75<D) h_tof_BT_a__mcp_posts_gt75 -> Fill(tof);
						if (99<A && 99<B && 99<C && 99<D) h_tof_BT_a__mcp_posts_gt99 -> Fill(tof);
						if (200<(A+B+C+D)) h_tof_BT_a__mcp_sum_gt200 -> Fill(tof);
						if (300<(A+B+C+D)) h_tof_BT_a__mcp_sum_gt300 -> Fill(tof);
						if (400<(A+B+C+D)) h_tof_BT_a__mcp_sum_gt400 -> Fill(tof);
						break;
					case 1: // BACKGROUND
						h_bkgd_tof_BT_a	-> Fill(tof);
						break;
					default: printf("Event %d: Invalid value s_capt_state = %d\n", i, s_capt_state); break;
				} // switch capt state
			} // if t_dEa and t_mcp
			
		// Bottom dEb - Top MCP
			if (t_dE_Lo < t_B_dEb && t_mcp_Lo < t_T_mcp) {
				tof = 0.001*(Double_t)(t_T_mcp - t_B_dEb);
				s_capt_state	= (Int_t)tree->GetLeaf("s_capt_state")->GetValue();
				switch (s_capt_state) {
					case 0: // SIGNAL
						h_tof_BT_b -> Fill(tof);
						dE = (Int_t)tree->GetLeaf("a_B_dEb")->GetValue();
						if (dE > 200) h_tof_BT_a__a_dE_gt200 ->Fill(tof);
						A = (Int_t)tree->GetLeaf("a_T_mcpA")->GetValue();
						B = (Int_t)tree->GetLeaf("a_T_mcpB")->GetValue();
						C = (Int_t)tree->GetLeaf("a_T_mcpC")->GetValue();
						D = (Int_t)tree->GetLeaf("a_T_mcpD")->GetValue();
						if (50<A && 50<B && 50<C && 50<D) h_tof_BT_a__mcp_posts_gt50 -> Fill(tof);
						if (75<A && 75<B && 75<C && 75<D) h_tof_BT_a__mcp_posts_gt75 -> Fill(tof);
						if (99<A && 99<B && 99<C && 99<D) h_tof_BT_a__mcp_posts_gt99 -> Fill(tof);
						if (200<(A+B+C+D)) h_tof_BT_a__mcp_sum_gt200 -> Fill(tof);
						if (300<(A+B+C+D)) h_tof_BT_a__mcp_sum_gt300 -> Fill(tof);
						if (400<(A+B+C+D)) h_tof_BT_a__mcp_sum_gt400 -> Fill(tof);
						break;
					case 1: // BACKGROUND
						h_bkgd_tof_BT_a	-> Fill(tof);
						break;
					default: printf("Event %d: Invalid value s_capt_state = %d\n", i, s_capt_state); break;
				} // switch capt state
			} // if t_dEb and t_mcp
			
		// Bottom dEa - Right MCP
			if (t_dE_Lo < t_B_dEa && t_mcp_Lo < t_R_mcp) {
				tof = 0.001*(Double_t)(t_R_mcp - t_B_dEa);
				s_capt_state	= (Int_t)tree->GetLeaf("s_capt_state")->GetValue();
				switch (s_capt_state) {
					case 0: // SIGNAL
						h_tof_BR_a -> Fill(tof);
						dE = (Int_t)tree->GetLeaf("a_B_dEa")->GetValue();
						if (dE > 200) h_tof_BR_a__a_dE_gt200 ->Fill(tof);
						A = (Int_t)tree->GetLeaf("a_R_mcpA")->GetValue();
						B = (Int_t)tree->GetLeaf("a_R_mcpB")->GetValue();
						C = (Int_t)tree->GetLeaf("a_R_mcpC")->GetValue();
						D = (Int_t)tree->GetLeaf("a_R_mcpD")->GetValue();
						if (50<A && 50<B && 50<C && 50<D) h_tof_BR_a__mcp_posts_gt50 -> Fill(tof);
						if (75<A && 75<B && 75<C && 75<D) h_tof_BR_a__mcp_posts_gt75 -> Fill(tof);
						if (99<A && 99<B && 99<C && 99<D) h_tof_BR_a__mcp_posts_gt99 -> Fill(tof);
						if (200<(A+B+C+D)) h_tof_BR_a__mcp_sum_gt200 -> Fill(tof);
						if (300<(A+B+C+D)) h_tof_BR_a__mcp_sum_gt300 -> Fill(tof);
						if (400<(A+B+C+D)) h_tof_BR_a__mcp_sum_gt400 -> Fill(tof);
						break;
					case 1: // BACKGROUND
						h_bkgd_tof_BR_a	-> Fill(tof);
						break;
					default: printf("Event %d: Invalid value s_capt_state = %d\n", i, s_capt_state); break;
				} // switch capt state
			} // if t_dEa and t_mcp
			
		// Bottom dEb - Right MCP
			if (t_dE_Lo < t_B_dEb && t_mcp_Lo < t_R_mcp) {
				tof = 0.001*(Double_t)(t_R_mcp - t_B_dEb);
				s_capt_state	= (Int_t)tree->GetLeaf("s_capt_state")->GetValue();
				switch (s_capt_state) {
					case 0: // SIGNAL
						h_tof_BR_b -> Fill(tof);
						dE = (Int_t)tree->GetLeaf("a_B_dEb")->GetValue();
						if (dE > 200) h_tof_BR_a__a_dE_gt200 ->Fill(tof);
						A = (Int_t)tree->GetLeaf("a_R_mcpA")->GetValue();
						B = (Int_t)tree->GetLeaf("a_R_mcpB")->GetValue();
						C = (Int_t)tree->GetLeaf("a_R_mcpC")->GetValue();
						D = (Int_t)tree->GetLeaf("a_R_mcpD")->GetValue();
						if (50<A && 50<B && 50<C && 50<D) h_tof_BR_a__mcp_posts_gt50 -> Fill(tof);
						if (75<A && 75<B && 75<C && 75<D) h_tof_BR_a__mcp_posts_gt75 -> Fill(tof);
						if (99<A && 99<B && 99<C && 99<D) h_tof_BR_a__mcp_posts_gt99 -> Fill(tof);
						if (200<(A+B+C+D)) h_tof_BR_a__mcp_sum_gt200 -> Fill(tof);
						if (300<(A+B+C+D)) h_tof_BR_a__mcp_sum_gt300 -> Fill(tof);
						if (400<(A+B+C+D)) h_tof_BR_a__mcp_sum_gt400 -> Fill(tof);
						break;
					case 1: // BACKGROUND
						h_bkgd_tof_BR_a	-> Fill(tof);
						break;
					default: printf("Event %d: Invalid value s_capt_state = %d\n", i, s_capt_state); break;
				} // switch capt state
			} // if t_dEb and t_mcp
			
	// Average dEa & dEb		
		// Left-Top
			if (t_dE_Lo < t_L_dEa && t_dE_Lo < t_L_dEb && t_mcp_Lo < t_T_mcp) {
				tof = 0.001*(Double_t)(t_T_mcp - 0.5*(t_L_dEa+t_L_dEb));
				switch (s_capt_state) {
					case 0: h_tof_LT_avg		-> Fill(tof); break;
					case 1: h_bkgd_tof_LT_avg	-> Fill(tof); break;
					default: printf("Event %d: Invalid value s_capt_state = %d\n", i, s_capt_state); break;
				} // switch capt_state
			} // if t_dEa & t_dEb & t_mcp
		// Left-Right
			if (t_dE_Lo < t_L_dEa && t_dE_Lo < t_L_dEb && t_mcp_Lo < t_R_mcp) {
				tof = 0.001*(Double_t)(t_R_mcp - 0.5*(t_L_dEa+t_L_dEb));
				switch (s_capt_state) {
					case 0: h_tof_LR_avg		-> Fill(tof); break;
					case 1: h_bkgd_tof_LR_avg	-> Fill(tof); break;
					default: printf("Event %d: Invalid value s_capt_state = %d\n", i, s_capt_state); break;
				} // switch capt_state
			} // if t_dEa & t_dEb & t_mcp
		// Bottom-Top
			if (t_dE_Lo < t_B_dEa && t_dE_Lo < t_B_dEb && t_mcp_Lo < t_T_mcp) {
				tof = 0.001*(Double_t)(t_T_mcp - 0.5*(t_B_dEa+t_B_dEb));
				switch (s_capt_state) {
					case 0: h_tof_BT_avg		-> Fill(tof); break;
					case 1: h_bkgd_tof_BT_avg	-> Fill(tof); break;
					default: printf("Event %d: Invalid value s_capt_state = %d\n", i, s_capt_state); break;
				} // switch capt_state
			} // if t_dEa & t_dEb & t_mcp
		// Bottom-Right
			if (t_dE_Lo < t_B_dEa && t_dE_Lo < t_B_dEb && t_mcp_Lo < t_R_mcp) {
				tof = 0.001*(Double_t)(t_R_mcp - 0.5*(t_B_dEa+t_B_dEb));
				switch (s_capt_state) {
					case 0: h_tof_BR_avg		-> Fill(tof); break;
					case 1: h_bkgd_tof_BR_avg	-> Fill(tof); break;
					default: printf("Event %d: Invalid value s_capt_state = %d\n", i, s_capt_state); break;
				} // switch capt_state
			} // if t_dEa & t_dEb & t_mcp
			
		} // event_good
	} // event loop
	
	if (f->GetDirectory(dir)) {
		f->cd();
		printf("\n\"%s:/%s\" exists... replacing it.", filename, dir);
		f->Delete(dir_cycle);
		f->mkdir(dir);
	}
	else {
		printf("\n\"%s:/%s\" does not exist... creating it.", filename, dir);
		f->cd();
		f->mkdir(dir);
	}
	
	f->cd(dir);
	
//	gDirectory->WriteTObject(fstr);
	
	gDirectory->WriteTObject(h_tof_LT_avg);
	gDirectory->WriteTObject(h_tof_LR_avg);
	gDirectory->WriteTObject(h_tof_BT_avg);
	gDirectory->WriteTObject(h_tof_BR_avg);
				
	gDirectory->WriteTObject(h_tof_LT_a);
	gDirectory->WriteTObject(h_tof_LT_b);
	gDirectory->WriteTObject(h_tof_LR_a);
	gDirectory->WriteTObject(h_tof_LR_b);
	gDirectory->WriteTObject(h_tof_BT_a);
	gDirectory->WriteTObject(h_tof_BT_b);
	gDirectory->WriteTObject(h_tof_BR_a);
	gDirectory->WriteTObject(h_tof_BR_b);
	
	gDirectory->WriteTObject(h_bkgd_tof_LT_avg);
	gDirectory->WriteTObject(h_bkgd_tof_LR_avg);
	gDirectory->WriteTObject(h_bkgd_tof_BT_avg);
	gDirectory->WriteTObject(h_bkgd_tof_BR_avg);
				
	gDirectory->WriteTObject(h_bkgd_tof_LT_a);
	gDirectory->WriteTObject(h_bkgd_tof_LT_b);
	gDirectory->WriteTObject(h_bkgd_tof_LR_a);
	gDirectory->WriteTObject(h_bkgd_tof_LR_b);
	gDirectory->WriteTObject(h_bkgd_tof_BT_a);
	gDirectory->WriteTObject(h_bkgd_tof_BT_b);
	gDirectory->WriteTObject(h_bkgd_tof_BR_a);
	gDirectory->WriteTObject(h_bkgd_tof_BR_b);
	
	gDirectory->WriteTObject(h_tof_LT_a__a_dE_gt200);
	gDirectory->WriteTObject(h_tof_LT_b__a_dE_gt200);
	gDirectory->WriteTObject(h_tof_LR_a__a_dE_gt200);
	gDirectory->WriteTObject(h_tof_LR_b__a_dE_gt200);
	gDirectory->WriteTObject(h_tof_BT_a__a_dE_gt200);
	gDirectory->WriteTObject(h_tof_BT_b__a_dE_gt200);
	gDirectory->WriteTObject(h_tof_BR_a__a_dE_gt200);
	gDirectory->WriteTObject(h_tof_BR_b__a_dE_gt200);

	gDirectory->WriteTObject(h_tof_LT_a__mcp_posts_gt50);
	gDirectory->WriteTObject(h_tof_LT_b__mcp_posts_gt50);
	gDirectory->WriteTObject(h_tof_LR_a__mcp_posts_gt50);
	gDirectory->WriteTObject(h_tof_LR_b__mcp_posts_gt50);
	gDirectory->WriteTObject(h_tof_BT_a__mcp_posts_gt50);
	gDirectory->WriteTObject(h_tof_BT_b__mcp_posts_gt50);
	gDirectory->WriteTObject(h_tof_BR_a__mcp_posts_gt50);
	gDirectory->WriteTObject(h_tof_BR_b__mcp_posts_gt50);
	gDirectory->WriteTObject(h_tof_LT_a__mcp_posts_gt50);
	
	gDirectory->WriteTObject(h_tof_LT_a__mcp_posts_gt75);
	gDirectory->WriteTObject(h_tof_LT_b__mcp_posts_gt75);
	gDirectory->WriteTObject(h_tof_LR_a__mcp_posts_gt75);
	gDirectory->WriteTObject(h_tof_LR_b__mcp_posts_gt75);
	gDirectory->WriteTObject(h_tof_BT_a__mcp_posts_gt75);
	gDirectory->WriteTObject(h_tof_BT_b__mcp_posts_gt75);
	gDirectory->WriteTObject(h_tof_BR_a__mcp_posts_gt75);
	gDirectory->WriteTObject(h_tof_BR_b__mcp_posts_gt75);
	gDirectory->WriteTObject(h_tof_LT_a__mcp_posts_gt75);
	
	gDirectory->WriteTObject(h_tof_LT_a__mcp_posts_gt99);
	gDirectory->WriteTObject(h_tof_LT_b__mcp_posts_gt99);
	gDirectory->WriteTObject(h_tof_LR_a__mcp_posts_gt99);
	gDirectory->WriteTObject(h_tof_LR_b__mcp_posts_gt99);
	gDirectory->WriteTObject(h_tof_BT_a__mcp_posts_gt99);
	gDirectory->WriteTObject(h_tof_BT_b__mcp_posts_gt99);
	gDirectory->WriteTObject(h_tof_BR_a__mcp_posts_gt99);
	gDirectory->WriteTObject(h_tof_BR_b__mcp_posts_gt99);
	gDirectory->WriteTObject(h_tof_LT_a__mcp_posts_gt99);
	
	gDirectory->WriteTObject(h_tof_LT_a__mcp_sum_gt200);
	gDirectory->WriteTObject(h_tof_LT_b__mcp_sum_gt200);
	gDirectory->WriteTObject(h_tof_LR_a__mcp_sum_gt200);
	gDirectory->WriteTObject(h_tof_LR_b__mcp_sum_gt200);
	gDirectory->WriteTObject(h_tof_BT_a__mcp_sum_gt200);
	gDirectory->WriteTObject(h_tof_BT_b__mcp_sum_gt200);
	gDirectory->WriteTObject(h_tof_BR_a__mcp_sum_gt200);
	gDirectory->WriteTObject(h_tof_BR_b__mcp_sum_gt200);
	gDirectory->WriteTObject(h_tof_LT_a__mcp_sum_gt200);
	
	gDirectory->WriteTObject(h_tof_LT_a__mcp_sum_gt300);
	gDirectory->WriteTObject(h_tof_LT_b__mcp_sum_gt300);
	gDirectory->WriteTObject(h_tof_LR_a__mcp_sum_gt300);
	gDirectory->WriteTObject(h_tof_LR_b__mcp_sum_gt300);
	gDirectory->WriteTObject(h_tof_BT_a__mcp_sum_gt300);
	gDirectory->WriteTObject(h_tof_BT_b__mcp_sum_gt300);
	gDirectory->WriteTObject(h_tof_BR_a__mcp_sum_gt300);
	gDirectory->WriteTObject(h_tof_BR_b__mcp_sum_gt300);
	gDirectory->WriteTObject(h_tof_LT_a__mcp_sum_gt300);
	
	gDirectory->WriteTObject(h_tof_LT_a__mcp_sum_gt400);
	gDirectory->WriteTObject(h_tof_LT_b__mcp_sum_gt400);
	gDirectory->WriteTObject(h_tof_LR_a__mcp_sum_gt400);
	gDirectory->WriteTObject(h_tof_LR_b__mcp_sum_gt400);
	gDirectory->WriteTObject(h_tof_BT_a__mcp_sum_gt400);
	gDirectory->WriteTObject(h_tof_BT_b__mcp_sum_gt400);
	gDirectory->WriteTObject(h_tof_BR_a__mcp_sum_gt400);
	gDirectory->WriteTObject(h_tof_BR_b__mcp_sum_gt400);
	gDirectory->WriteTObject(h_tof_LT_a__mcp_sum_gt400);
	
	f->Close();
	
	printf("\nmcp_studies done.\n\n");
	
}
