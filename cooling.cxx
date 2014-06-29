/*
2012-11-24 Shane Caldwell

For 135-Sb data, make trees for different times after capture.

*/

#include <unistd.h>
//#include "stat.h"
#include "stdio.h"
#include "TH1.h"
#include "TH2.h"
#include "TFile.h"
#include "TTree.h"
#include "TLeaf.h"
#include "bdn.h"

void cooling (const char*);

int main (int argc, char *argv[]) {
	while (*++argv) {
		cooling(argv[0]);
	}
	return 0;
}

void cooling (const char *filename) {
	
	printf("\ncooling started.\n%s\n",filename);
	char *dir = "cooling"; // results will be placed in this subdirectory of the root file
	char *dir_cycle = "cooling;1"; // results will be placed in this subdirectory of the root file
    
	/*****************************************************************/
	/*** Code to include source code as a string in the ROOT file: ***/
	/*****************************************************************
    FILE *fsrc = fopen("cooling.cxx", "r");
    char *fbuf;
    struct stat srcbuf;
	
    stat("cooling.cxx", &srcbuf);
    fbuf = new char [srcbuf.st_size+1];
    fread(fbuf, sizeof(char), srcbuf.st_size, fsrc);
    fbuf[srcbuf.st_size] = '\0';    TString fstr(fbuf);
	/*****************************************************************
	
	printf(fbuf);
*/	
	TFile *f			= new TFile(filename, "UPDATE");
	TTree *tree			= (TTree*)f->Get("bdn_Tree");
	//TTree *tree_100ms 	= new TTree("tree_100ms", "data with  0 ms < s_ms_since_capt < 100ms");
	//TTree *tree_200ms 	= new TTree("tree_200ms", "data with 100ms < s_ms_since_capt < 200ms");
	//TTree *tree_300ms 	= new TTree("tree_300ms", "data with 200ms < s_ms_since_capt < 300ms");
	TTree *tree_100ms 	= tree->CloneTree(0);
	TTree *tree_200ms 	= tree->CloneTree(0);
	TTree *tree_300ms 	= tree->CloneTree(0);
	
	const Double_t TOFMin	= -0.1; // us
	const Double_t TOFMax	= 22.5; // us
	const Int_t TOFBins		= 22600; // one bin per ns
	TH1I *h_tof_100ms			= new TH1I("h_tof_100ms",		"TOF in us for t < 100ms after capture, All combos"		,TOFBins,TOFMin,TOFMax);
	TH1I *h_tof_100ms_LT		= new TH1I("h_tof_100ms_LT",	"TOF in us for t < 100ms after capture, Left-Top"		,TOFBins,TOFMin,TOFMax);
	TH1I *h_tof_100ms_LR		= new TH1I("h_tof_100ms_LR",	"TOF in us for t < 100ms after capture, Left-Right"		,TOFBins,TOFMin,TOFMax);
	TH1I *h_tof_100ms_BT		= new TH1I("h_tof_100ms_BT",	"TOF in us for t < 100ms after capture, Bottom-Top"		,TOFBins,TOFMin,TOFMax);
	TH1I *h_tof_100ms_BR		= new TH1I("h_tof_100ms_BR",	"TOF in us for t < 100ms after capture, Bottom-Right"	,TOFBins,TOFMin,TOFMax);
	TH1I *h_tof_200ms			= new TH1I("h_tof_200ms",		"TOF in us for 100ms < t < 200ms after capture, All combos"		,TOFBins,TOFMin,TOFMax);
	TH1I *h_tof_200ms_LT		= new TH1I("h_tof_200ms_LT",	"TOF in us for 100ms < t < 200ms after capture, Left-Top"		,TOFBins,TOFMin,TOFMax);
	TH1I *h_tof_200ms_LR		= new TH1I("h_tof_200ms_LR",	"TOF in us for 100ms < t < 200ms after capture, Left-Right"		,TOFBins,TOFMin,TOFMax);
	TH1I *h_tof_200ms_BT		= new TH1I("h_tof_200ms_BT",	"TOF in us for 100ms < t < 200ms after capture, Bottom-Top"		,TOFBins,TOFMin,TOFMax);
	TH1I *h_tof_200ms_BR		= new TH1I("h_tof_200ms_BR",	"TOF in us for 100ms < t < 200ms after capture, Bottom-Right"	,TOFBins,TOFMin,TOFMax);
	TH1I *h_tof_300ms			= new TH1I("h_tof_300ms",		"TOF in us for 200ms < t < 300ms after capture, All combos"		,TOFBins,TOFMin,TOFMax);
	TH1I *h_tof_300ms_LT		= new TH1I("h_tof_300ms_LT",	"TOF in us for 200ms < t < 300ms after capture, Left-Top"		,TOFBins,TOFMin,TOFMax);
	TH1I *h_tof_300ms_LR		= new TH1I("h_tof_300ms_LR",	"TOF in us for 200ms < t < 300ms after capture, Left-Right"		,TOFBins,TOFMin,TOFMax);
	TH1I *h_tof_300ms_BT		= new TH1I("h_tof_300ms_BT",	"TOF in us for 200ms < t < 300ms after capture, Bottom-Top"		,TOFBins,TOFMin,TOFMax);
	TH1I *h_tof_300ms_BR		= new TH1I("h_tof_300ms_BR",	"TOF in us for 200ms < t < 300ms after capture, Bottom-Right"	,TOFBins,TOFMin,TOFMax);

	// Loop variables:
	Long64_t	i;
	Long64_t	nEntries	= tree->GetEntries();
	Int_t		s_capt_state, s_ms_since_capt;
	Int_t		t_B_dEa, t_B_dEb;
	Int_t		t_L_dEa, t_L_dEb;
	Int_t		t_R_mcp;
	Int_t		t_T_mcp;
	Int_t		a_R_mcpA, a_R_mcpB, a_R_mcpC, a_R_mcpD;
	Int_t		a_T_mcpA, a_T_mcpB, a_T_mcpC, a_T_mcpD;
	Double_t	tof, dE, A, B, C, D;
	
	for (i=0; i<nEntries; i++) {
		tree->GetEntry(i);
		s_ms_since_capt	= (Int_t)tree->GetLeaf("s_ms_since_capt")	-> GetValue();
		s_capt_state	= (Int_t)tree->GetLeaf("s_capt_state")		-> GetValue();
		t_B_dEa			= (Int_t)tree->GetLeaf("t_B_dEa")->GetValue();
		t_B_dEb			= (Int_t)tree->GetLeaf("t_B_dEb")->GetValue();
		t_L_dEa			= (Int_t)tree->GetLeaf("t_L_dEa")->GetValue();
		t_L_dEb			= (Int_t)tree->GetLeaf("t_L_dEb")->GetValue();
		t_R_mcp			= (Int_t)tree->GetLeaf("t_R_mcp")->GetValue();
		t_T_mcp			= (Int_t)tree->GetLeaf("t_T_mcp")->GetValue();
		a_R_mcpA			= (Int_t)tree->GetLeaf("a_R_mcpA")->GetValue();
		a_R_mcpB			= (Int_t)tree->GetLeaf("a_R_mcpB")->GetValue();
		a_R_mcpC			= (Int_t)tree->GetLeaf("a_R_mcpC")->GetValue();
		a_R_mcpD			= (Int_t)tree->GetLeaf("a_R_mcpD")->GetValue();
		a_T_mcpA			= (Int_t)tree->GetLeaf("a_T_mcpA")->GetValue();
		a_T_mcpB			= (Int_t)tree->GetLeaf("a_T_mcpB")->GetValue();
		a_T_mcpC			= (Int_t)tree->GetLeaf("a_T_mcpC")->GetValue();
		a_T_mcpD			= (Int_t)tree->GetLeaf("a_T_mcpD")->GetValue();
		
		if (s_capt_state==0 &&							s_ms_since_capt <= 100)	{
			
			tree_100ms->Fill();
			
			// Left-Top
			if (-100<t_L_dEa && -100<t_L_dEb && -100<t_T_mcp && t_L_dEa<0 && t_L_dEb<0 && a_T_mcpA>100 && a_T_mcpB>100 && a_T_mcpC>100 && a_T_mcpD>100) {
				 tof 	= 0.001*((double)t_T_mcp - (t_L_dEa + t_L_dEb)/2.0); // convert ns to us
				 h_tof_100ms_LT	->Fill(tof);
				 h_tof_100ms	->Fill(tof);
			}
			// Left-Right
			if (-100<t_L_dEa && -100<t_L_dEb && -100<t_R_mcp && t_L_dEa<0 && t_L_dEb<0 && a_R_mcpA>100 && a_R_mcpB>100 && a_R_mcpC>100 && a_R_mcpD>100) {
				 tof 	= 0.001*((double)t_R_mcp - (t_L_dEa + t_L_dEb)/2.0); // convert ns to us
				 h_tof_100ms_LR	->Fill(tof);
				 h_tof_100ms	->Fill(tof);
			}
			// Bottom-Top
			if (-100<t_B_dEa && -100<t_B_dEb && -100<t_T_mcp && t_B_dEa<0 && t_B_dEb<0 && a_T_mcpA>100 && a_T_mcpB>100 && a_T_mcpC>100 && a_T_mcpD>100) {
				 tof 	= 0.001*((double)t_T_mcp - (t_B_dEa + t_B_dEb)/2.0); // convert ns to us
				 h_tof_100ms_BT	->Fill(tof);
				 h_tof_100ms	->Fill(tof);
			}
			// Bottom-Right
			if (-100<t_B_dEa && -100<t_B_dEb && -100<t_R_mcp && t_B_dEa<0 && t_B_dEb<0 && a_R_mcpA>100 && a_R_mcpB>100 && a_R_mcpC>100 && a_R_mcpD>100) {
				 tof 	= 0.001*((double)t_R_mcp - (t_B_dEa + t_B_dEb)/2.0); // convert ns to us
				 h_tof_100ms_BR	->Fill(tof);
				 h_tof_100ms	->Fill(tof);
			}
			
		}
		
		if (s_capt_state==0 && 100 < s_ms_since_capt && s_ms_since_capt <= 200) {
		
			tree_200ms->Fill();
			
			// Left-Top
			if (-100<t_L_dEa && -100<t_L_dEb && -100<t_T_mcp && t_L_dEa<0 && t_L_dEb<0 && a_T_mcpA>100 && a_T_mcpB>100 && a_T_mcpC>100 && a_T_mcpD>100) {
				 tof 	= 0.001*((double)t_T_mcp - (t_L_dEa + t_L_dEb)/2.0); // convert ns to us
				 h_tof_200ms_LT	->Fill(tof);
				 h_tof_200ms	->Fill(tof);
			}
			// Left-Right
			if (-100<t_L_dEa && -100<t_L_dEb && -100<t_R_mcp && t_L_dEa<0 && t_L_dEb<0 && a_R_mcpA>100 && a_R_mcpB>100 && a_R_mcpC>100 && a_R_mcpD>100) {
				 tof 	= 0.001*((double)t_R_mcp - (t_L_dEa + t_L_dEb)/2.0); // convert ns to us
				 h_tof_200ms_LR	->Fill(tof);
				 h_tof_200ms	->Fill(tof);
			}
			// Bottom-Top
			if (-100<t_B_dEa && -100<t_B_dEb && -100<t_T_mcp && t_B_dEa<0 && t_B_dEb<0 && a_T_mcpA>100 && a_T_mcpB>100 && a_T_mcpC>100 && a_T_mcpD>100) {
				 tof 	= 0.001*((double)t_T_mcp - (t_B_dEa + t_B_dEb)/2.0); // convert ns to us
				 h_tof_200ms_BT	->Fill(tof);
				 h_tof_200ms	->Fill(tof);
			}
			// Bottom-Right
			if (-100<t_B_dEa && -100<t_B_dEb && -100<t_R_mcp && t_B_dEa<0 && t_B_dEb<0 && a_R_mcpA>100 && a_R_mcpB>100 && a_R_mcpC>100 && a_R_mcpD>100) {
				 tof 	= 0.001*((double)t_R_mcp - (t_B_dEa + t_B_dEb)/2.0); // convert ns to us
				 h_tof_200ms_BR	->Fill(tof);
				 h_tof_200ms	->Fill(tof);
			}
			
		}	
			
		if (s_capt_state==0 && 200 < s_ms_since_capt && s_ms_since_capt <= 300) {
			
			tree_300ms->Fill();
			
			// Left-Top
			if (-100<t_L_dEa && -100<t_L_dEb && -100<t_T_mcp && t_L_dEa<0 && t_L_dEb<0 && a_T_mcpA>100 && a_T_mcpB>100 && a_T_mcpC>100 && a_T_mcpD>100) {
				 tof 	= 0.001*((double)t_T_mcp - (t_L_dEa + t_L_dEb)/2.0); // convert ns to us
				 h_tof_300ms_LT	->Fill(tof);
				 h_tof_300ms	->Fill(tof);
			}
			// Left-Right
			if (-100<t_L_dEa && -100<t_L_dEb && -100<t_R_mcp && t_L_dEa<0 && t_L_dEb<0 && a_R_mcpA>100 && a_R_mcpB>100 && a_R_mcpC>100 && a_R_mcpD>100) {
				 tof 	= 0.001*((double)t_R_mcp - (t_L_dEa + t_L_dEb)/2.0); // convert ns to us
				 h_tof_300ms_LR	->Fill(tof);
				 h_tof_300ms	->Fill(tof);
			}
			// Bottom-Top
			if (-100<t_B_dEa && -100<t_B_dEb && -100<t_T_mcp && t_B_dEa<0 && t_B_dEb<0 && a_T_mcpA>100 && a_T_mcpB>100 && a_T_mcpC>100 && a_T_mcpD>100) {
				 tof 	= 0.001*((double)t_T_mcp - (t_B_dEa + t_B_dEb)/2.0); // convert ns to us
				 h_tof_300ms_BT	->Fill(tof);
				 h_tof_300ms	->Fill(tof);
			}
			// Bottom-Right
			if (-100<t_B_dEa && -100<t_B_dEb && -100<t_R_mcp && t_B_dEa<0 && t_B_dEb<0 && a_R_mcpA>100 && a_R_mcpB>100 && a_R_mcpC>100 && a_R_mcpD>100) {
				 tof 	= 0.001*((double)t_R_mcp - (t_B_dEa + t_B_dEb)/2.0); // convert ns to us
				 h_tof_300ms_BR	->Fill(tof);
				 h_tof_300ms	->Fill(tof);
			}
			
		}	
			
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
	gDirectory->WriteTObject(tree_100ms);
	gDirectory->WriteTObject(tree_200ms);
	gDirectory->WriteTObject(tree_300ms);
	
	gDirectory->WriteTObject(h_tof_100ms);
	gDirectory->WriteTObject(h_tof_100ms_LT);
	gDirectory->WriteTObject(h_tof_100ms_LR);
	gDirectory->WriteTObject(h_tof_100ms_BT);
	gDirectory->WriteTObject(h_tof_100ms_BR);
	
	gDirectory->WriteTObject(h_tof_200ms);
	gDirectory->WriteTObject(h_tof_200ms_LT);
	gDirectory->WriteTObject(h_tof_200ms_LR);
	gDirectory->WriteTObject(h_tof_200ms_BT);
	gDirectory->WriteTObject(h_tof_200ms_BR);
	
	gDirectory->WriteTObject(h_tof_300ms);
	gDirectory->WriteTObject(h_tof_300ms_LT);
	gDirectory->WriteTObject(h_tof_300ms_LR);
	gDirectory->WriteTObject(h_tof_300ms_BT);
	gDirectory->WriteTObject(h_tof_300ms_BR);
	
	f->Close();
	
	printf("\ncooling done.\n\n");
	
}
