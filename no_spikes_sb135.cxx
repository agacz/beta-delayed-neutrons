/*

2012-12-02 Shane Caldwell

Remove data with s_ms_since_eject in the spiky values.

*/

#include <unistd.h>
#include <iostream>
#include <algorithm>
#include <vector>
//#include "stat.h"
#include "stdio.h"
#include "TH1.h"
#include "TH2.h"
#include "TFile.h"
#include "TTree.h"
#include "TLeaf.h"
#include "TMath.h"
#include "bdn.h"

void no_spikes (const char*);

int main (int argc, char *argv[]) {
	while (*++argv) {
		no_spikes(argv[0]);
	}
	return 0;
}

void no_spikes (const char *filename) {
	
	printf("\nno_spikes started.\n%s\n",filename);
	char *dir = "no_spikes"; // results will be placed in this subdirectory of the root file
	char *dir_cycle = "no_spikes;1"; // results will be placed in this subdirectory of the root file
    
	/*****************************************************************/
	/*** Code to include source code as a string in the ROOT file: ***/
	/*****************************************************************
    FILE *fsrc = fopen("no_spikes.cxx", "r");
    char *fbuf;
    struct stat srcbuf;
	
    stat("no_spikes.cxx", &srcbuf);
    fbuf = new char [srcbuf.st_size+1];
    fread(fbuf, sizeof(char), srcbuf.st_size, fsrc);
    fbuf[srcbuf.st_size] = '\0';    TString fstr(fbuf);
	/*****************************************************************
	
	printf(fbuf);
*/	
	TFile *f	= new TFile(filename, "UPDATE");
	TTree *tree	= (TTree*)f->Get("bdn_Tree");
	TTree *tree_no_spikes 	= tree->CloneTree(0);
	
	Long64_t nEntries = tree->GetEntries();
	
	Int_t msMin = -1000;
	Int_t msMax = 22000;
	Int_t msBins= 23000;
	
	// Make histogram of s_ms_since_eject values
	TH1I *h = new TH1I("h", "135Sb: Time since last ejection pulse (trap full)", msBins, msMin, msMax);
	TH1I *hs_ms_since_eject_trap_full_no_spikes = new TH1I("hs_ms_since_eject_trap_full_no_spikes", "135Sb: Time since last ejection pulse (trap full) with spikes removed", msBins, msMin, msMax);
	TH1I *hs_ms_since_eject_trap_full = new TH1I("hs_ms_since_eject_trap_full", "135Sb: Time since last ejection pulse (trap full)", msBins, msMin, msMax);
	tree->Project("h", "s_ms_since_eject", "s_capt_state==0");
	
	const Double_t TOFMin	= -0.1; // us
	const Double_t TOFMax	= 22.5; // us
	const Int_t TOFBins		= 22600; // one bin per ns
	TH1I *h_tof_no_spikes	= new TH1I("h_tof_no_spikes",	 "TOF in us with spikes taken out of t_since_capt, All combos"	,TOFBins,TOFMin,TOFMax);
	TH1I *h_tof_no_spikes_LT= new TH1I("h_tof_no_spikes_LT", "TOF in us with spikes taken out of t_since_capt, Left-Top"	,TOFBins,TOFMin,TOFMax);
	TH1I *h_tof_no_spikes_LR= new TH1I("h_tof_no_spikes_LR", "TOF in us with spikes taken out of t_since_capt, Left-Right"	,TOFBins,TOFMin,TOFMax);
	TH1I *h_tof_no_spikes_BT= new TH1I("h_tof_no_spikes_BT", "TOF in us with spikes taken out of t_since_capt, Bottom-Top"	,TOFBins,TOFMin,TOFMax);
	TH1I *h_tof_no_spikes_BR= new TH1I("h_tof_no_spikes_BR", "TOF in us with spikes taken out of t_since_capt, Bottom-Right",TOFBins,TOFMin,TOFMax);
	
	// Loop variables:
	Long64_t	i;
	Double_t	y;
	Double_t	count = 0.0;
	Double_t	sum = 0.0;
	Double_t	variate_sum = 0.0;
	Double_t	mean, sigma;
	
	Int_t		s_capt_state, s_ms_since_eject;
	Int_t		t_B_dEa, t_B_dEb;
	Int_t		t_L_dEa, t_L_dEb;
	Int_t		t_R_mcp;
	Int_t		t_T_mcp;
	Int_t		a_R_mcpA, a_R_mcpB, a_R_mcpC, a_R_mcpD;
	Int_t		a_T_mcpA, a_T_mcpB, a_T_mcpC, a_T_mcpD;
	Double_t	tof, dE, A, B, C, D;
	
	// Get mean of histogram y values
	for (i=6100; i<=21000; i++) {
		y = h->GetBinContent(i);
		sum += y;
		if (y>0) count++;
	}
	
	mean = sum/count;
	
	printf("mean: %f (sum %f on %f counts)\n", mean, sum, count);
	
	// Get stdev of histogram y values
	for (i=6100; i<=21000; i++) {
		y = h->GetBinContent(i);
		variate_sum += TMath::Power((y - mean), 2.0);
	}
	
	sigma = TMath::Power(variate_sum/(count-1), 0.5);
	
	printf("sigma: %f (variate sum %f on %f counts)\n", sigma, variate_sum, count);
	printf("second pass:\n");
	
	// Second pass
	count = 0.0;
	sum = 0.0;
	variate_sum = 0.0;
	
	// Get mean of histogram y values
	for (i=1; i<=msBins; i++) {
		y = h->GetBinContent(i);
		if (TMath::Abs((y-mean)/sigma) < 2.0) {
			count++;
			sum += y;
		}
	}
	
	mean = sum/count;
	printf("mean: %f (sum %f on %f counts)\n", mean, sum, count);
	
	// Get stdev of histogram y values
	for (i=1; i<=msBins; i++) {
		y = h->GetBinContent(i);
		if (TMath::Abs((y-mean)/sigma) < 2.0) variate_sum += TMath::Power((y - mean), 2.0);
	}
	
	sigma = TMath::Power(variate_sum/(count-1), 0.5);
	
	printf("sigma: %f (variate sum %f on %f counts)\n", sigma, variate_sum, count);
	printf("Threshold for spikes is %f\n", mean+4.0*sigma);

	// Now select the spikes and add their s_ms_since_eject values to a TVector
	std::vector<Int_t>				spikes;
	std::vector<Int_t>::iterator	iter;
	Int_t x;
	for (i=1; i<=msBins; i++) {
		x = msMin + i- 1; // msMin+i-1 is the value of s_ms_since_capt that corresponds to bin i
		y = h->GetBinContent(i);
		if ((y-mean)/sigma > 5.0) spikes.push_back(x); // Add x to the list of values where there are spikes
	}
	
	std::cout << "spikes at: ";
	for (iter = spikes.begin(); iter < spikes.end(); iter++) std::cout << ' ' << *iter;
	std::cout << '\n';

// EVENT LOOP
	for (i=0; i<nEntries; i++) {
		tree->GetEntry(i);
		s_ms_since_eject= (Int_t)tree->GetLeaf("s_ms_since_eject")	-> GetValue();
		s_capt_state	= (Int_t)tree->GetLeaf("s_capt_state")		-> GetValue();
		
		
		if (s_capt_state==0) { // if trap full
			
			hs_ms_since_eject_trap_full->Fill(s_ms_since_eject);
			
			if (std::find(spikes.begin(), spikes.end(), s_ms_since_eject) == spikes.end()) { // if not a spike
			// ie. if s_ms_since_eject is not in the spikes vector
				
				tree_no_spikes->Fill();
				hs_ms_since_eject_trap_full_no_spikes->Fill(s_ms_since_eject);
				
				t_B_dEa			= (Int_t)tree->GetLeaf("t_B_dEa")->GetValue();
				t_B_dEb			= (Int_t)tree->GetLeaf("t_B_dEb")->GetValue();
				t_L_dEa			= (Int_t)tree->GetLeaf("t_L_dEa")->GetValue();
				t_L_dEb			= (Int_t)tree->GetLeaf("t_L_dEb")->GetValue();
				t_R_mcp			= (Int_t)tree->GetLeaf("t_R_mcp")->GetValue();
				t_T_mcp			= (Int_t)tree->GetLeaf("t_T_mcp")->GetValue();
				a_R_mcpA		= (Int_t)tree->GetLeaf("a_R_mcpA")->GetValue();
				a_R_mcpB		= (Int_t)tree->GetLeaf("a_R_mcpB")->GetValue();
				a_R_mcpC		= (Int_t)tree->GetLeaf("a_R_mcpC")->GetValue();
				a_R_mcpD		= (Int_t)tree->GetLeaf("a_R_mcpD")->GetValue();
				a_T_mcpA		= (Int_t)tree->GetLeaf("a_T_mcpA")->GetValue();
				a_T_mcpB		= (Int_t)tree->GetLeaf("a_T_mcpB")->GetValue();
				a_T_mcpC		= (Int_t)tree->GetLeaf("a_T_mcpC")->GetValue();
				a_T_mcpD		= (Int_t)tree->GetLeaf("a_T_mcpD")->GetValue();
				
				// Left-Top
				if (-100<t_L_dEa && -100<t_L_dEb && -100<t_T_mcp && t_L_dEa<0 && t_L_dEb<0 && a_T_mcpA>100 && a_T_mcpB>100 && a_T_mcpC>100 && a_T_mcpD>100) {
					 tof 	= 0.001*((double)t_T_mcp - (t_L_dEa + t_L_dEb)/2.0); // convert ns to us
					 h_tof_no_spikes_LT	->Fill(tof);
					 h_tof_no_spikes	->Fill(tof);
				}
				// Left-Right
				if (-100<t_L_dEa && -100<t_L_dEb && -100<t_R_mcp && t_L_dEa<0 && t_L_dEb<0 && a_R_mcpA>100 && a_R_mcpB>100 && a_R_mcpC>100 && a_R_mcpD>100) {
					 tof 	= 0.001*((double)t_R_mcp - (t_L_dEa + t_L_dEb)/2.0); // convert ns to us
					 h_tof_no_spikes_LR	->Fill(tof);
					 h_tof_no_spikes	->Fill(tof);
				}
				// Bottom-Top
				if (-100<t_B_dEa && -100<t_B_dEb && -100<t_T_mcp && t_B_dEa<0 && t_B_dEb<0 && a_T_mcpA>100 && a_T_mcpB>100 && a_T_mcpC>100 && a_T_mcpD>100) {
					 tof 	= 0.001*((double)t_T_mcp - (t_B_dEa + t_B_dEb)/2.0); // convert ns to us
					 h_tof_no_spikes_BT	->Fill(tof);
					 h_tof_no_spikes	->Fill(tof);
				}
				// Bottom-Right
				if (-100<t_B_dEa && -100<t_B_dEb && -100<t_R_mcp && t_B_dEa<0 && t_B_dEb<0 && a_R_mcpA>100 && a_R_mcpB>100 && a_R_mcpC>100 && a_R_mcpD>100) {
					 tof 	= 0.001*((double)t_R_mcp - (t_B_dEa + t_B_dEb)/2.0); // convert ns to us
					 h_tof_no_spikes_BR	->Fill(tof);
					 h_tof_no_spikes	->Fill(tof);
				}
			} // if spike
		} // if trap full
		
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
	gDirectory->WriteTObject(hs_ms_since_eject_trap_full);
	gDirectory->WriteTObject(hs_ms_since_eject_trap_full_no_spikes);
	
	gDirectory->WriteTObject(h_tof_no_spikes);
	gDirectory->WriteTObject(h_tof_no_spikes_LT);
	gDirectory->WriteTObject(h_tof_no_spikes_LR);
	gDirectory->WriteTObject(h_tof_no_spikes_BT);
	gDirectory->WriteTObject(h_tof_no_spikes_BR);
	
	f->Close();
	
	printf("\nno_spikes done.\n\n");
	
}
