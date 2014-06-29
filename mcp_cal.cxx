/*
2013-02-15  Shane Caldwell  Created mcp_cal.cxx
2013-02-28  Added PHD's and per-quadrant data.
2013-03-01  Now subtracting ADC pedestal values from MCP posts
2013-03-04  Centering bins on integer values
2014-03-11
  Adding Right MCP (this year we were able to calibrate it)
  Adding random component to x and y coords to elimnate funny binning
2014-03-17
  Adding mapping to physical space, putting physical maps into h_[R/T]_mcp_map_physical_2
2014-03-18
  Adding code to track when posts are missing, event by event
  - missing_[R/T]_mcp[4] holds 1 if a post is missing; correlated by event; 0=A, 1=B, 2=C, 3=D
  - h_missing_[R/T]_mcp to hold # of times each post is missing
  - hn_missing_[R/T]_mcp to hold distribution of # of missing posts
  - n_missing_[R/T]_mcp[A/B/C/D]_only to count # of times each post is the only missing post on an MCP

2014-03-20 Making pedSubtract version with pedestal subtraction
2014-03-29 Added a couple new variations:
 - a special _cut histogram that shows PHD's in a specific region of the map
 - a _post histogram showing the map with just the pedestals cut out of each post

2014-04-21 Promoting this version to mcp_cal.cxx
2014-04-25 "Missing post" channged from "<0" to "<a_missing_mcp_post (=-1000)" because pedestal subtraction makes many events "<0".
2014-04-28 Changing the missing-post maps and reconstructed maps to (sum>a_mcp_lo(=200)) rather than (sum>400) to help me do consistency checks

Histogram names:
h_ = it's a histogram
T_ = Top (R for Right, but didn't calibrate the Right MCP because it's borken
mcpA = A post amplitude
mcpSum = A + B + C + D
mcpX = X coordinate
qA = MCP hit in quadrant A
_n = sum signal > 200*n
*/

#include <unistd.h>
//#include "stat.h"
#include "stdio.h"
#include "TH1.h"
#include "TH2.h"
#include "TFile.h"
#include "TTree.h"
#include "TLeaf.h"
#include "TRandom3.h"
#include "TMath.h"
#include "bdn.h"

void mcp_cal (const char*);

int main (int argc, char *argv[]) {
	while (*++argv) {
		mcp_cal(argv[0]);
	}
	return 0;
}

void mcp_cal (const char *filename) {
	
	printf("\nmcp_cal started.\n");
    printf(filename);
    
	/*****************************************************************/
	/*** Code to include source code as a string in the ROOT file: ***/
	/*****************************************************************
    FILE *fsrc = fopen("mcp_cal.cxx", "r");
    char *fbuf;
    struct stat srcbuf;
	
    stat("mcp_cal.cxx", &srcbuf);
    fbuf = new char [srcbuf.st_size+1];
    fread(fbuf, sizeof(char), srcbuf.st_size, fsrc);
    fbuf[srcbuf.st_size] = '\0';    TString fstr(fbuf);
	/*****************************************************************
	
	printf(fbuf);
*/	
	TFile *f = new TFile(filename, "UPDATE");	
	TTree *tree    = (TTree*)f->Get("bdn_Tree");
	char *dir = "mcp_cal"; // results will be placed in this subdirectory of the root file
	char *dir_cycle = "mcp_cal;1"; // results will be placed in this subdirectory of the root file
	
	TRandom3 *randgen = new TRandom3(1);
	
	Int_t printReconstructionMessage = 0;
	
	// Loop variables:
	const Int_t nEntries = tree->GetEntries();
	Int_t i;
	
	printf("\n%d entries",nEntries);
	
	// To hold values in the event loop:
	Double_t	tA, tB, tC, tD, tSum, tX, tY;
	Double_t	rA, rB, rC, rD, rSum, rX, rY;
	Double_t	rA_calc, rB_calc, rC_calc, rD_calc;
	Double_t	tA_calc, tB_calc, tC_calc, tD_calc;
	
	Double_t x0 = -0.0081539028;
	Double_t y0 = -0.0086976241;
	Double_t scale = 26.98837;
	Double_t theta = 0.0062820831;
	Double_t tX_mm, tY_mm, rX_mm, rY_mm;
	
	// Histograms
	const Double_t mapMin	= -1.0;
	const Double_t mapMax	= 1.0;
	const Double_t mapBinSize = 0.002;
	const Int_t mapBins 	= (mapMax - mapMin)/mapBinSize;
	
	const Double_t phdMin	= -100;
	const Double_t phdMax	= 4500;
	const Int_t phdBins 	= (Int_t)(phdMax - phdMin);
	/*
	TH1I *h_R_mcpX		= new TH1I("h_R_mcpX"	,"Right MCP-X"	, mapBins, mapMin, mapMax);
	TH1I *h_R_mcpY		= new TH1I("h_R_mcpY"	,"Right MCP-Y"	, mapBins, mapMin, mapMax);
	
	TH2I *h_R_mcp_map_0	= new TH2I("h_R_mcp_map_0", "Right MCP map w/ all data (no cuts)", mapBins, mapMin, mapMax, mapBins, mapMin, mapMax);
	TH2I *h_R_mcp_map_1	= new TH2I("h_R_mcp_map_1", "Right MCP map w/ sum > 200", mapBins, mapMin, mapMax, mapBins, mapMin, mapMax);
	TH2I *h_R_mcp_map_2	= new TH2I("h_R_mcp_map_2", "Right MCP map w/ sum > 400", mapBins, mapMin, mapMax, mapBins, mapMin, mapMax);
	TH2I *h_R_mcp_map_3	= new TH2I("h_R_mcp_map_3", "Right MCP map w/ sum > 600", mapBins, mapMin, mapMax, mapBins, mapMin, mapMax);
	TH2I *h_R_mcp_map_4	= new TH2I("h_R_mcp_map_4", "Right MCP map w/ sum > 800", mapBins, mapMin, mapMax, mapBins, mapMin, mapMax);
	*/
	TH2I *h_T_mcp_map_0	= new TH2I("h_T_mcp_map_0", "Top MCP map w/ all data (no cuts)", mapBins, mapMin, mapMax, mapBins, mapMin, mapMax);
	TH2I *h_T_mcp_map_1	= new TH2I("h_T_mcp_map_1", "Top MCP map w/ sum > 200", mapBins, mapMin, mapMax, mapBins, mapMin, mapMax);
	TH2I *h_T_mcp_map_2	= new TH2I("h_T_mcp_map_2", "Top MCP map w/ sum > 400", mapBins, mapMin, mapMax, mapBins, mapMin, mapMax);
	TH2I *h_T_mcp_map_3	= new TH2I("h_T_mcp_map_3", "Top MCP map w/ sum > 600", mapBins, mapMin, mapMax, mapBins, mapMin, mapMax);
	TH2I *h_T_mcp_map_4	= new TH2I("h_T_mcp_map_4", "Top MCP map w/ sum > 800", mapBins, mapMin, mapMax, mapBins, mapMin, mapMax);
	
	TH1I *h_T_mcpA_0		= new TH1I("h_T_mcpA_0"	,"Top MCP-A (no cuts)"	, phdBins, phdMin, phdMax);
	TH1I *h_T_mcpB_0		= new TH1I("h_T_mcpB_0"	,"Top MCP-B (no cuts)"	, phdBins, phdMin, phdMax);
	TH1I *h_T_mcpC_0		= new TH1I("h_T_mcpC_0"	,"Top MCP-C (no cuts)"	, phdBins, phdMin, phdMax);
	TH1I *h_T_mcpD_0		= new TH1I("h_T_mcpD_0"	,"Top MCP-D (no cuts)"	, phdBins, phdMin, phdMax);
	TH1I *h_T_mcpSum_0		= new TH1I("h_T_mcpSum_0"	,"Top MCP sum (no cuts)"	, 4*phdBins, 4*phdMin, 4*phdMax);
	TH1I *h_T_mcpX_0		= new TH1I("h_T_mcpX_0"	,"Top MCP-X (no cuts)"	, mapBins, mapMin, mapMax);
	TH1I *h_T_mcpY_0		= new TH1I("h_T_mcpY_0"	,"Top MCP-Y (no cuts)"	, mapBins, mapMin, mapMax);
	
	TH1I *h_T_mcpA_1		= new TH1I("h_T_mcpA_1"	,"Top MCP-A w/ sum > 200"	, phdBins, phdMin, phdMax);
	TH1I *h_T_mcpB_1		= new TH1I("h_T_mcpB_1"	,"Top MCP-B w/ sum > 200"	, phdBins, phdMin, phdMax);
	TH1I *h_T_mcpC_1		= new TH1I("h_T_mcpC_1"	,"Top MCP-C w/ sum > 200"	, phdBins, phdMin, phdMax);
	TH1I *h_T_mcpD_1		= new TH1I("h_T_mcpD_1"	,"Top MCP-D w/ sum > 200"	, phdBins, phdMin, phdMax);
	TH1I *h_T_mcpSum_1		= new TH1I("h_T_mcpSum_1"	,"Top MCP sum w/ sum > 200"	, 4*phdBins, 4*phdMin, 4*phdMax);
	TH1I *h_T_mcpX_1		= new TH1I("h_T_mcpX_1"	,"Top MCP-X w/ sum > 200"	, mapBins, mapMin, mapMax);
	TH1I *h_T_mcpY_1		= new TH1I("h_T_mcpY_1"	,"Top MCP-Y w/ sum > 200"	, mapBins, mapMin, mapMax);
	
	TH1I *h_T_mcpA_2		= new TH1I("h_T_mcpA_2"	,"Top MCP-A w/ sum > 400"	, phdBins, phdMin, phdMax);
	TH1I *h_T_mcpB_2		= new TH1I("h_T_mcpB_2"	,"Top MCP-B w/ sum > 400"	, phdBins, phdMin, phdMax);
	TH1I *h_T_mcpC_2		= new TH1I("h_T_mcpC_2"	,"Top MCP-C w/ sum > 400"	, phdBins, phdMin, phdMax);
	TH1I *h_T_mcpD_2		= new TH1I("h_T_mcpD_2"	,"Top MCP-D w/ sum > 400"	, phdBins, phdMin, phdMax);
	TH1I *h_T_mcpSum_2		= new TH1I("h_T_mcpSum_2"	,"Top MCP sum w/ sum > 400"	, 4*phdBins, 4*phdMin, 4*phdMax);
	TH1I *h_T_mcpX_2		= new TH1I("h_T_mcpX_2"	,"Top MCP-X w/ sum > 400"	, mapBins, mapMin, mapMax);
	TH1I *h_T_mcpY_2		= new TH1I("h_T_mcpY_2"	,"Top MCP-Y w/ sum > 400"	, mapBins, mapMin, mapMax);
	
	TH1I *h_T_mcpA_3		= new TH1I("h_T_mcpA_3"	,"Top MCP-A w/ sum > 600"	, phdBins, phdMin, phdMax);
	TH1I *h_T_mcpB_3		= new TH1I("h_T_mcpB_3"	,"Top MCP-B w/ sum > 600"	, phdBins, phdMin, phdMax);
	TH1I *h_T_mcpC_3		= new TH1I("h_T_mcpC_3"	,"Top MCP-C w/ sum > 600"	, phdBins, phdMin, phdMax);
	TH1I *h_T_mcpD_3		= new TH1I("h_T_mcpD_3"	,"Top MCP-D w/ sum > 600"	, phdBins, phdMin, phdMax);
	TH1I *h_T_mcpSum_3		= new TH1I("h_T_mcpSum_3"	,"Top MCP sum w/ sum > 600"	, 4*phdBins, 4*phdMin, 4*phdMax);
	TH1I *h_T_mcpX_3		= new TH1I("h_T_mcpX_3"	,"Top MCP-X w/ sum > 600"	, mapBins, mapMin, mapMax);
	TH1I *h_T_mcpY_3		= new TH1I("h_T_mcpY_3"	,"Top MCP-Y w/ sum > 600"	, mapBins, mapMin, mapMax);
	
	TH1I *h_T_mcpA_4		= new TH1I("h_T_mcpA_4"	,"Top MCP-A w/ sum > 800"	, phdBins, phdMin, phdMax);
	TH1I *h_T_mcpB_4		= new TH1I("h_T_mcpB_4"	,"Top MCP-B w/ sum > 800"	, phdBins, phdMin, phdMax);
	TH1I *h_T_mcpC_4		= new TH1I("h_T_mcpC_4"	,"Top MCP-C w/ sum > 800"	, phdBins, phdMin, phdMax);
	TH1I *h_T_mcpD_4		= new TH1I("h_T_mcpD_4"	,"Top MCP-D w/ sum > 800"	, phdBins, phdMin, phdMax);
	TH1I *h_T_mcpSum_4		= new TH1I("h_T_mcpSum_4"	,"Top MCP sum w/ sum > 800"	, 4*phdBins, 4*phdMin, 4*phdMax);
	TH1I *h_T_mcpX_4		= new TH1I("h_T_mcpX_4"	,"Top MCP-X w/ sum > 800"	, mapBins, mapMin, mapMax);
	TH1I *h_T_mcpY_4		= new TH1I("h_T_mcpY_4"	,"Top MCP-Y w/ sum > 800"	, mapBins, mapMin, mapMax);
	
	TH1I *h_T_mcpA_qA_0		= new TH1I("h_T_mcpA_qA_0"	,"Top MCP-A w/ (X,Y) in quadrant A & sum > 400"	, phdBins, phdMin, phdMax);
	TH1I *h_T_mcpB_qA_0		= new TH1I("h_T_mcpB_qA_0"	,"Top MCP-B w/ (X,Y) in quadrant A & sum > 400"	, phdBins, phdMin, phdMax);
	TH1I *h_T_mcpC_qA_0		= new TH1I("h_T_mcpC_qA_0"	,"Top MCP-C w/ (X,Y) in quadrant A & sum > 400"	, phdBins, phdMin, phdMax);
	TH1I *h_T_mcpD_qA_0		= new TH1I("h_T_mcpD_qA_0"	,"Top MCP-D w/ (X,Y) in quadrant A & sum > 400"	, phdBins, phdMin, phdMax);
	TH1I *h_T_mcpSum_qA_0	= new TH1I("h_T_mcpSum_qA_0"	,"Top MCP sum w/ (X,Y) in quadrant A & sum > 400"	, 4*phdBins, 4*phdMin, 4*phdMax);
	TH1I *h_T_mcpX_qA_0		= new TH1I("h_T_mcpX_qA_0"	,"Top MCP-X w/ (X,Y) in quadrant A & sum > 400"	, mapBins, mapMin, mapMax);
	TH1I *h_T_mcpY_qA_0		= new TH1I("h_T_mcpY_qA_0"	,"Top MCP-Y w/ (X,Y) in quadrant A & sum > 400"	, mapBins, mapMin, mapMax);
	
	TH1I *h_T_mcpA_qB_0		= new TH1I("h_T_mcpA_qB_0"	,"Top MCP-A w/ (X,Y) in quadrant B & sum > 400"	, phdBins, phdMin, phdMax);
	TH1I *h_T_mcpB_qB_0		= new TH1I("h_T_mcpB_qB_0"	,"Top MCP-B w/ (X,Y) in quadrant B & sum > 400"	, phdBins, phdMin, phdMax);
	TH1I *h_T_mcpC_qB_0		= new TH1I("h_T_mcpC_qB_0"	,"Top MCP-C w/ (X,Y) in quadrant B & sum > 400"	, phdBins, phdMin, phdMax);
	TH1I *h_T_mcpD_qB_0		= new TH1I("h_T_mcpD_qB_0"	,"Top MCP-D w/ (X,Y) in quadrant B & sum > 400"	, phdBins, phdMin, phdMax);
	TH1I *h_T_mcpSum_qB_0	= new TH1I("h_T_mcpSum_qB_0"	,"Top MCP sum w/ (X,Y) in quadrant B & sum > 400"	, 4*phdBins, 4*phdMin, 4*phdMax);
	TH1I *h_T_mcpX_qB_0		= new TH1I("h_T_mcpX_qB_0"	,"Top MCP-X w/ (X,Y) in quadrant B & sum > 400"	, mapBins, mapMin, mapMax);
	TH1I *h_T_mcpY_qB_0		= new TH1I("h_T_mcpY_qB_0"	,"Top MCP-Y w/ (X,Y) in quadrant B & sum > 400"	, mapBins, mapMin, mapMax);
	
	TH1I *h_T_mcpA_qC_0		= new TH1I("h_T_mcpA_qC_0"	,"Top MCP-A w/ (X,Y) in quadrant C & sum > 400"	, phdBins, phdMin, phdMax);
	TH1I *h_T_mcpB_qC_0		= new TH1I("h_T_mcpB_qC_0"	,"Top MCP-B w/ (X,Y) in quadrant C & sum > 400"	, phdBins, phdMin, phdMax);
	TH1I *h_T_mcpC_qC_0		= new TH1I("h_T_mcpC_qC_0"	,"Top MCP-C w/ (X,Y) in quadrant C & sum > 400"	, phdBins, phdMin, phdMax);
	TH1I *h_T_mcpD_qC_0		= new TH1I("h_T_mcpD_qC_0"	,"Top MCP-D w/ (X,Y) in quadrant C & sum > 400"	, phdBins, phdMin, phdMax);
	TH1I *h_T_mcpSum_qC_0	= new TH1I("h_T_mcpSum_qC_0"	,"Top MCP sum w/ (X,Y) in quadrant C & sum > 400"	, 4*phdBins, 4*phdMin, 4*phdMax);
	TH1I *h_T_mcpX_qC_0		= new TH1I("h_T_mcpX_qC_0"	,"Top MCP-X w/ (X,Y) in quadrant C & sum > 400"	, mapBins, mapMin, mapMax);
	TH1I *h_T_mcpY_qC_0		= new TH1I("h_T_mcpY_qC_0"	,"Top MCP-Y w/ (X,Y) in quadrant C & sum > 400"	, mapBins, mapMin, mapMax);
	
	TH1I *h_T_mcpA_qD_0		= new TH1I("h_T_mcpA_qD_0"	,"Top MCP-A w/ (X,Y) in quadrant D & sum > 400"	, phdBins, phdMin, phdMax);
	TH1I *h_T_mcpB_qD_0		= new TH1I("h_T_mcpB_qD_0"	,"Top MCP-B w/ (X,Y) in quadrant D & sum > 400"	, phdBins, phdMin, phdMax);
	TH1I *h_T_mcpC_qD_0		= new TH1I("h_T_mcpC_qD_0"	,"Top MCP-C w/ (X,Y) in quadrant D & sum > 400"	, phdBins, phdMin, phdMax);
	TH1I *h_T_mcpD_qD_0		= new TH1I("h_T_mcpD_qD_0"	,"Top MCP-D w/ (X,Y) in quadrant D & sum > 400"	, phdBins, phdMin, phdMax);
	TH1I *h_T_mcpSum_qD_0	= new TH1I("h_T_mcpSum_qD_0"	,"Top MCP sum w/ (X,Y) in quadrant D & sum > 400"	, 4*phdBins, 4*phdMin, 4*phdMax);
	TH1I *h_T_mcpX_qD_0		= new TH1I("h_T_mcpX_qD_0"	,"Top MCP-X w/ (X,Y) in quadrant D & sum > 400"	, mapBins, mapMin, mapMax);
	TH1I *h_T_mcpY_qD_0		= new TH1I("h_T_mcpY_qD_0"	,"Top MCP-Y w/ (X,Y) in quadrant D & sum > 400"	, mapBins, mapMin, mapMax);
	
	TH1I *h_T_mcpA_qCenter_0		= new TH1I("h_T_mcpA_qCenter_0"	,"Top MCP-A w/ (X,Y) in \"center\" quadrant & sum > 400"	, phdBins, phdMin, phdMax);
	TH1I *h_T_mcpB_qCenter_0		= new TH1I("h_T_mcpB_qCenter_0"	,"Top MCP-B w/ (X,Y) in \"center\" quadrant & sum > 400"	, phdBins, phdMin, phdMax);
	TH1I *h_T_mcpC_qCenter_0		= new TH1I("h_T_mcpC_qCenter_0"	,"Top MCP-C w/ (X,Y) in \"center\" quadrant & sum > 400"	, phdBins, phdMin, phdMax);
	TH1I *h_T_mcpD_qCenter_0		= new TH1I("h_T_mcpD_qCenter_0"	,"Top MCP-D w/ (X,Y) in \"center\" quadrant & sum > 400"	, phdBins, phdMin, phdMax);
	TH1I *h_T_mcpSum_qCenter_0		= new TH1I("h_T_mcpSum_qCenter_0"	,"Top MCP sum w/ (X,Y) in \"center\" quadrant & sum > 400"	, 4*phdBins, 4*phdMin, 4*phdMax);
	TH1I *h_T_mcpX_qCenter_0		= new TH1I("h_T_mcpX_qCenter_0"	,"Top MCP-X w/ (X,Y) in \"center\" quadrant & sum > 400"	, mapBins, mapMin, mapMax);
	TH1I *h_T_mcpY_qCenter_0		= new TH1I("h_T_mcpY_qCenter_0"	,"Top MCP-Y w/ (X,Y) in \"center\" quadrant & sum > 400"	, mapBins, mapMin, mapMax);
	
	TH1I *h_T_mcpA_qA_2		= new TH1I("h_T_mcpA_qA_2"	,"Top MCP-A w/ (X,Y) in quadrant A & sum > 400"	, phdBins, phdMin, phdMax);
	TH1I *h_T_mcpB_qA_2		= new TH1I("h_T_mcpB_qA_2"	,"Top MCP-B w/ (X,Y) in quadrant A & sum > 400"	, phdBins, phdMin, phdMax);
	TH1I *h_T_mcpC_qA_2		= new TH1I("h_T_mcpC_qA_2"	,"Top MCP-C w/ (X,Y) in quadrant A & sum > 400"	, phdBins, phdMin, phdMax);
	TH1I *h_T_mcpD_qA_2		= new TH1I("h_T_mcpD_qA_2"	,"Top MCP-D w/ (X,Y) in quadrant A & sum > 400"	, phdBins, phdMin, phdMax);
	TH1I *h_T_mcpSum_qA_2	= new TH1I("h_T_mcpSum_qA_2"	,"Top MCP sum w/ (X,Y) in quadrant A & sum > 400"	, 4*phdBins, 4*phdMin, 4*phdMax);
	TH1I *h_T_mcpX_qA_2		= new TH1I("h_T_mcpX_qA_2"	,"Top MCP-X w/ (X,Y) in quadrant A & sum > 400"	, mapBins, mapMin, mapMax);
	TH1I *h_T_mcpY_qA_2		= new TH1I("h_T_mcpY_qA_2"	,"Top MCP-Y w/ (X,Y) in quadrant A & sum > 400"	, mapBins, mapMin, mapMax);
	
	TH1I *h_T_mcpA_qB_2		= new TH1I("h_T_mcpA_qB_2"	,"Top MCP-A w/ (X,Y) in quadrant B & sum > 400"	, phdBins, phdMin, phdMax);
	TH1I *h_T_mcpB_qB_2		= new TH1I("h_T_mcpB_qB_2"	,"Top MCP-B w/ (X,Y) in quadrant B & sum > 400"	, phdBins, phdMin, phdMax);
	TH1I *h_T_mcpC_qB_2		= new TH1I("h_T_mcpC_qB_2"	,"Top MCP-C w/ (X,Y) in quadrant B & sum > 400"	, phdBins, phdMin, phdMax);
	TH1I *h_T_mcpD_qB_2		= new TH1I("h_T_mcpD_qB_2"	,"Top MCP-D w/ (X,Y) in quadrant B & sum > 400"	, phdBins, phdMin, phdMax);
	TH1I *h_T_mcpSum_qB_2	= new TH1I("h_T_mcpSum_qB_2"	,"Top MCP sum w/ (X,Y) in quadrant B & sum > 400"	, 4*phdBins, 4*phdMin, 4*phdMax);
	TH1I *h_T_mcpX_qB_2		= new TH1I("h_T_mcpX_qB_2"	,"Top MCP-X w/ (X,Y) in quadrant B & sum > 400"	, mapBins, mapMin, mapMax);
	TH1I *h_T_mcpY_qB_2		= new TH1I("h_T_mcpY_qB_2"	,"Top MCP-Y w/ (X,Y) in quadrant B & sum > 400"	, mapBins, mapMin, mapMax);
	
	TH1I *h_T_mcpA_qC_2		= new TH1I("h_T_mcpA_qC_2"	,"Top MCP-A w/ (X,Y) in quadrant C & sum > 400"	, phdBins, phdMin, phdMax);
	TH1I *h_T_mcpB_qC_2		= new TH1I("h_T_mcpB_qC_2"	,"Top MCP-B w/ (X,Y) in quadrant C & sum > 400"	, phdBins, phdMin, phdMax);
	TH1I *h_T_mcpC_qC_2		= new TH1I("h_T_mcpC_qC_2"	,"Top MCP-C w/ (X,Y) in quadrant C & sum > 400"	, phdBins, phdMin, phdMax);
	TH1I *h_T_mcpD_qC_2		= new TH1I("h_T_mcpD_qC_2"	,"Top MCP-D w/ (X,Y) in quadrant C & sum > 400"	, phdBins, phdMin, phdMax);
	TH1I *h_T_mcpSum_qC_2	= new TH1I("h_T_mcpSum_qC_2"	,"Top MCP sum w/ (X,Y) in quadrant C & sum > 400"	, 4*phdBins, 4*phdMin, 4*phdMax);
	TH1I *h_T_mcpX_qC_2		= new TH1I("h_T_mcpX_qC_2"	,"Top MCP-X w/ (X,Y) in quadrant C & sum > 400"	, mapBins, mapMin, mapMax);
	TH1I *h_T_mcpY_qC_2		= new TH1I("h_T_mcpY_qC_2"	,"Top MCP-Y w/ (X,Y) in quadrant C & sum > 400"	, mapBins, mapMin, mapMax);
	
	TH1I *h_T_mcpA_qD_2		= new TH1I("h_T_mcpA_qD_2"	,"Top MCP-A w/ (X,Y) in quadrant D & sum > 400"	, phdBins, phdMin, phdMax);
	TH1I *h_T_mcpB_qD_2		= new TH1I("h_T_mcpB_qD_2"	,"Top MCP-B w/ (X,Y) in quadrant D & sum > 400"	, phdBins, phdMin, phdMax);
	TH1I *h_T_mcpC_qD_2		= new TH1I("h_T_mcpC_qD_2"	,"Top MCP-C w/ (X,Y) in quadrant D & sum > 400"	, phdBins, phdMin, phdMax);
	TH1I *h_T_mcpD_qD_2		= new TH1I("h_T_mcpD_qD_2"	,"Top MCP-D w/ (X,Y) in quadrant D & sum > 400"	, phdBins, phdMin, phdMax);
	TH1I *h_T_mcpSum_qD_2	= new TH1I("h_T_mcpSum_qD_2"	,"Top MCP sum w/ (X,Y) in quadrant D & sum > 400"	, 4*phdBins, 4*phdMin, 4*phdMax);
	TH1I *h_T_mcpX_qD_2		= new TH1I("h_T_mcpX_qD_2"	,"Top MCP-X w/ (X,Y) in quadrant D & sum > 400"	, mapBins, mapMin, mapMax);
	TH1I *h_T_mcpY_qD_2		= new TH1I("h_T_mcpY_qD_2"	,"Top MCP-Y w/ (X,Y) in quadrant D & sum > 400"	, mapBins, mapMin, mapMax);
	
	TH1I *h_T_mcpA_qCenter_2		= new TH1I("h_T_mcpA_qCenter_2"	,"Top MCP-A w/ (X,Y) in \"center\" quadrant & sum > 400"	, phdBins, phdMin, phdMax);
	TH1I *h_T_mcpB_qCenter_2		= new TH1I("h_T_mcpB_qCenter_2"	,"Top MCP-B w/ (X,Y) in \"center\" quadrant & sum > 400"	, phdBins, phdMin, phdMax);
	TH1I *h_T_mcpC_qCenter_2		= new TH1I("h_T_mcpC_qCenter_2"	,"Top MCP-C w/ (X,Y) in \"center\" quadrant & sum > 400"	, phdBins, phdMin, phdMax);
	TH1I *h_T_mcpD_qCenter_2		= new TH1I("h_T_mcpD_qCenter_2"	,"Top MCP-D w/ (X,Y) in \"center\" quadrant & sum > 400"	, phdBins, phdMin, phdMax);
	TH1I *h_T_mcpSum_qCenter_2		= new TH1I("h_T_mcpSum_qCenter_2"	,"Top MCP sum w/ (X,Y) in \"center\" quadrant & sum > 400"	, 4*phdBins, 4*phdMin, 4*phdMax);
	TH1I *h_T_mcpX_qCenter_2		= new TH1I("h_T_mcpX_qCenter_2"	,"Top MCP-X w/ (X,Y) in \"center\" quadrant & sum > 400"	, mapBins, mapMin, mapMax);
	TH1I *h_T_mcpY_qCenter_2		= new TH1I("h_T_mcpY_qCenter_2"	,"Top MCP-Y w/ (X,Y) in \"center\" quadrant & sum > 400"	, mapBins, mapMin, mapMax);
	
// RIGHT MCP	
	TH2I *h_R_mcp_map_0	= new TH2I("h_R_mcp_map_0", "Right MCP map w/ all data (no cuts)", mapBins, mapMin, mapMax, mapBins, mapMin, mapMax);
	TH2I *h_R_mcp_map_1	= new TH2I("h_R_mcp_map_1", "Right MCP map w/ sum > 200", mapBins, mapMin, mapMax, mapBins, mapMin, mapMax);
	TH2I *h_R_mcp_map_2	= new TH2I("h_R_mcp_map_2", "Right MCP map w/ sum > 400", mapBins, mapMin, mapMax, mapBins, mapMin, mapMax);
	TH2I *h_R_mcp_map_3	= new TH2I("h_R_mcp_map_3", "Right MCP map w/ sum > 600", mapBins, mapMin, mapMax, mapBins, mapMin, mapMax);
	TH2I *h_R_mcp_map_4	= new TH2I("h_R_mcp_map_4", "Right MCP map w/ sum > 800", mapBins, mapMin, mapMax, mapBins, mapMin, mapMax);
	
	TH1I *h_R_mcpA_0		= new TH1I("h_R_mcpA_0"	,"Right MCP-A (no cuts)"	, phdBins, phdMin, phdMax);
	TH1I *h_R_mcpB_0		= new TH1I("h_R_mcpB_0"	,"Right MCP-B (no cuts)"	, phdBins, phdMin, phdMax);
	TH1I *h_R_mcpC_0		= new TH1I("h_R_mcpC_0"	,"Right MCP-C (no cuts)"	, phdBins, phdMin, phdMax);
	TH1I *h_R_mcpD_0		= new TH1I("h_R_mcpD_0"	,"Right MCP-D (no cuts)"	, phdBins, phdMin, phdMax);
	TH1I *h_R_mcpSum_0		= new TH1I("h_R_mcpSum_0"	,"Right MCP sum (no cuts)"	, 4*phdBins, 4*phdMin, 4*phdMax);
	TH1I *h_R_mcpX_0		= new TH1I("h_R_mcpX_0"	,"Right MCP-X (no cuts)"	, mapBins, mapMin, mapMax);
	TH1I *h_R_mcpY_0		= new TH1I("h_R_mcpY_0"	,"Right MCP-Y (no cuts)"	, mapBins, mapMin, mapMax);
	
	TH1I *h_R_mcpA_1		= new TH1I("h_R_mcpA_1"	,"Right MCP-A w/ sum > 200"	, phdBins, phdMin, phdMax);
	TH1I *h_R_mcpB_1		= new TH1I("h_R_mcpB_1"	,"Right MCP-B w/ sum > 200"	, phdBins, phdMin, phdMax);
	TH1I *h_R_mcpC_1		= new TH1I("h_R_mcpC_1"	,"Right MCP-C w/ sum > 200"	, phdBins, phdMin, phdMax);
	TH1I *h_R_mcpD_1		= new TH1I("h_R_mcpD_1"	,"Right MCP-D w/ sum > 200"	, phdBins, phdMin, phdMax);
	TH1I *h_R_mcpSum_1		= new TH1I("h_R_mcpSum_1"	,"Right MCP sum w/ sum > 200"	, 4*phdBins, 4*phdMin, 4*phdMax);
	TH1I *h_R_mcpX_1		= new TH1I("h_R_mcpX_1"	,"Right MCP-X w/ sum > 200"	, mapBins, mapMin, mapMax);
	TH1I *h_R_mcpY_1		= new TH1I("h_R_mcpY_1"	,"Right MCP-Y w/ sum > 200"	, mapBins, mapMin, mapMax);
	
	TH1I *h_R_mcpA_2		= new TH1I("h_R_mcpA_2"	,"Right MCP-A w/ sum > 400"	, phdBins, phdMin, phdMax);
	TH1I *h_R_mcpB_2		= new TH1I("h_R_mcpB_2"	,"Right MCP-B w/ sum > 400"	, phdBins, phdMin, phdMax);
	TH1I *h_R_mcpC_2		= new TH1I("h_R_mcpC_2"	,"Right MCP-C w/ sum > 400"	, phdBins, phdMin, phdMax);
	TH1I *h_R_mcpD_2		= new TH1I("h_R_mcpD_2"	,"Right MCP-D w/ sum > 400"	, phdBins, phdMin, phdMax);
	TH1I *h_R_mcpSum_2		= new TH1I("h_R_mcpSum_2"	,"Right MCP sum w/ sum > 400"	, 4*phdBins, 4*phdMin, 4*phdMax);
	TH1I *h_R_mcpX_2		= new TH1I("h_R_mcpX_2"	,"Right MCP-X w/ sum > 400"	, mapBins, mapMin, mapMax);
	TH1I *h_R_mcpY_2		= new TH1I("h_R_mcpY_2"	,"Right MCP-Y w/ sum > 400"	, mapBins, mapMin, mapMax);
	
	TH1I *h_R_mcpA_3		= new TH1I("h_R_mcpA_3"	,"Right MCP-A w/ sum > 600"	, phdBins, phdMin, phdMax);
	TH1I *h_R_mcpB_3		= new TH1I("h_R_mcpB_3"	,"Right MCP-B w/ sum > 600"	, phdBins, phdMin, phdMax);
	TH1I *h_R_mcpC_3		= new TH1I("h_R_mcpC_3"	,"Right MCP-C w/ sum > 600"	, phdBins, phdMin, phdMax);
	TH1I *h_R_mcpD_3		= new TH1I("h_R_mcpD_3"	,"Right MCP-D w/ sum > 600"	, phdBins, phdMin, phdMax);
	TH1I *h_R_mcpSum_3		= new TH1I("h_R_mcpSum_3"	,"Right MCP sum w/ sum > 600"	, 4*phdBins, 4*phdMin, 4*phdMax);
	TH1I *h_R_mcpX_3		= new TH1I("h_R_mcpX_3"	,"Right MCP-X w/ sum > 600"	, mapBins, mapMin, mapMax);
	TH1I *h_R_mcpY_3		= new TH1I("h_R_mcpY_3"	,"Right MCP-Y w/ sum > 600"	, mapBins, mapMin, mapMax);
	
	TH1I *h_R_mcpA_4		= new TH1I("h_R_mcpA_4"	,"Right MCP-A w/ sum > 800"	, phdBins, phdMin, phdMax);
	TH1I *h_R_mcpB_4		= new TH1I("h_R_mcpB_4"	,"Right MCP-B w/ sum > 800"	, phdBins, phdMin, phdMax);
	TH1I *h_R_mcpC_4		= new TH1I("h_R_mcpC_4"	,"Right MCP-C w/ sum > 800"	, phdBins, phdMin, phdMax);
	TH1I *h_R_mcpD_4		= new TH1I("h_R_mcpD_4"	,"Right MCP-D w/ sum > 800"	, phdBins, phdMin, phdMax);
	TH1I *h_R_mcpSum_4		= new TH1I("h_R_mcpSum_4"	,"Right MCP sum w/ sum > 800"	, 4*phdBins, 4*phdMin, 4*phdMax);
	TH1I *h_R_mcpX_4		= new TH1I("h_R_mcpX_4"	,"Right MCP-X w/ sum > 800"	, mapBins, mapMin, mapMax);
	TH1I *h_R_mcpY_4		= new TH1I("h_R_mcpY_4"	,"Right MCP-Y w/ sum > 800"	, mapBins, mapMin, mapMax);
	
	TH1I *h_R_mcpA_qA_0		= new TH1I("h_R_mcpA_qA_0"	,"Right MCP-A w/ (X,Y) in quadrant A & sum > 400"	, phdBins, phdMin, phdMax);
	TH1I *h_R_mcpB_qA_0		= new TH1I("h_R_mcpB_qA_0"	,"Right MCP-B w/ (X,Y) in quadrant A & sum > 400"	, phdBins, phdMin, phdMax);
	TH1I *h_R_mcpC_qA_0		= new TH1I("h_R_mcpC_qA_0"	,"Right MCP-C w/ (X,Y) in quadrant A & sum > 400"	, phdBins, phdMin, phdMax);
	TH1I *h_R_mcpD_qA_0		= new TH1I("h_R_mcpD_qA_0"	,"Right MCP-D w/ (X,Y) in quadrant A & sum > 400"	, phdBins, phdMin, phdMax);
	TH1I *h_R_mcpSum_qA_0	= new TH1I("h_R_mcpSum_qA_0"	,"Right MCP sum w/ (X,Y) in quadrant A & sum > 400"	, 4*phdBins, 4*phdMin, 4*phdMax);
	TH1I *h_R_mcpX_qA_0		= new TH1I("h_R_mcpX_qA_0"	,"Right MCP-X w/ (X,Y) in quadrant A & sum > 400"	, mapBins, mapMin, mapMax);
	TH1I *h_R_mcpY_qA_0		= new TH1I("h_R_mcpY_qA_0"	,"Right MCP-Y w/ (X,Y) in quadrant A & sum > 400"	, mapBins, mapMin, mapMax);
	
	TH1I *h_R_mcpA_qB_0		= new TH1I("h_R_mcpA_qB_0"	,"Right MCP-A w/ (X,Y) in quadrant B & sum > 400"	, phdBins, phdMin, phdMax);
	TH1I *h_R_mcpB_qB_0		= new TH1I("h_R_mcpB_qB_0"	,"Right MCP-B w/ (X,Y) in quadrant B & sum > 400"	, phdBins, phdMin, phdMax);
	TH1I *h_R_mcpC_qB_0		= new TH1I("h_R_mcpC_qB_0"	,"Right MCP-C w/ (X,Y) in quadrant B & sum > 400"	, phdBins, phdMin, phdMax);
	TH1I *h_R_mcpD_qB_0		= new TH1I("h_R_mcpD_qB_0"	,"Right MCP-D w/ (X,Y) in quadrant B & sum > 400"	, phdBins, phdMin, phdMax);
	TH1I *h_R_mcpSum_qB_0	= new TH1I("h_R_mcpSum_qB_0"	,"Right MCP sum w/ (X,Y) in quadrant B & sum > 400"	, 4*phdBins, 4*phdMin, 4*phdMax);
	TH1I *h_R_mcpX_qB_0		= new TH1I("h_R_mcpX_qB_0"	,"Right MCP-X w/ (X,Y) in quadrant B & sum > 400"	, mapBins, mapMin, mapMax);
	TH1I *h_R_mcpY_qB_0		= new TH1I("h_R_mcpY_qB_0"	,"Right MCP-Y w/ (X,Y) in quadrant B & sum > 400"	, mapBins, mapMin, mapMax);
	
	TH1I *h_R_mcpA_qC_0		= new TH1I("h_R_mcpA_qC_0"	,"Right MCP-A w/ (X,Y) in quadrant C & sum > 400"	, phdBins, phdMin, phdMax);
	TH1I *h_R_mcpB_qC_0		= new TH1I("h_R_mcpB_qC_0"	,"Right MCP-B w/ (X,Y) in quadrant C & sum > 400"	, phdBins, phdMin, phdMax);
	TH1I *h_R_mcpC_qC_0		= new TH1I("h_R_mcpC_qC_0"	,"Right MCP-C w/ (X,Y) in quadrant C & sum > 400"	, phdBins, phdMin, phdMax);
	TH1I *h_R_mcpD_qC_0		= new TH1I("h_R_mcpD_qC_0"	,"Right MCP-D w/ (X,Y) in quadrant C & sum > 400"	, phdBins, phdMin, phdMax);
	TH1I *h_R_mcpSum_qC_0	= new TH1I("h_R_mcpSum_qC_0"	,"Right MCP sum w/ (X,Y) in quadrant C & sum > 400"	, 4*phdBins, 4*phdMin, 4*phdMax);
	TH1I *h_R_mcpX_qC_0		= new TH1I("h_R_mcpX_qC_0"	,"Right MCP-X w/ (X,Y) in quadrant C & sum > 400"	, mapBins, mapMin, mapMax);
	TH1I *h_R_mcpY_qC_0		= new TH1I("h_R_mcpY_qC_0"	,"Right MCP-Y w/ (X,Y) in quadrant C & sum > 400"	, mapBins, mapMin, mapMax);
	
	TH1I *h_R_mcpA_qD_0		= new TH1I("h_R_mcpA_qD_0"	,"Right MCP-A w/ (X,Y) in quadrant D & sum > 400"	, phdBins, phdMin, phdMax);
	TH1I *h_R_mcpB_qD_0		= new TH1I("h_R_mcpB_qD_0"	,"Right MCP-B w/ (X,Y) in quadrant D & sum > 400"	, phdBins, phdMin, phdMax);
	TH1I *h_R_mcpC_qD_0		= new TH1I("h_R_mcpC_qD_0"	,"Right MCP-C w/ (X,Y) in quadrant D & sum > 400"	, phdBins, phdMin, phdMax);
	TH1I *h_R_mcpD_qD_0		= new TH1I("h_R_mcpD_qD_0"	,"Right MCP-D w/ (X,Y) in quadrant D & sum > 400"	, phdBins, phdMin, phdMax);
	TH1I *h_R_mcpSum_qD_0	= new TH1I("h_R_mcpSum_qD_0"	,"Right MCP sum w/ (X,Y) in quadrant D & sum > 400"	, 4*phdBins, 4*phdMin, 4*phdMax);
	TH1I *h_R_mcpX_qD_0		= new TH1I("h_R_mcpX_qD_0"	,"Right MCP-X w/ (X,Y) in quadrant D & sum > 400"	, mapBins, mapMin, mapMax);
	TH1I *h_R_mcpY_qD_0		= new TH1I("h_R_mcpY_qD_0"	,"Right MCP-Y w/ (X,Y) in quadrant D & sum > 400"	, mapBins, mapMin, mapMax);
	
	TH1I *h_R_mcpA_qCenter_0		= new TH1I("h_R_mcpA_qCenter_0"	,"Right MCP-A w/ (X,Y) in \"center\" quadrant & sum > 400"	, phdBins, phdMin, phdMax);
	TH1I *h_R_mcpB_qCenter_0		= new TH1I("h_R_mcpB_qCenter_0"	,"Right MCP-B w/ (X,Y) in \"center\" quadrant & sum > 400"	, phdBins, phdMin, phdMax);
	TH1I *h_R_mcpC_qCenter_0		= new TH1I("h_R_mcpC_qCenter_0"	,"Right MCP-C w/ (X,Y) in \"center\" quadrant & sum > 400"	, phdBins, phdMin, phdMax);
	TH1I *h_R_mcpD_qCenter_0		= new TH1I("h_R_mcpD_qCenter_0"	,"Right MCP-D w/ (X,Y) in \"center\" quadrant & sum > 400"	, phdBins, phdMin, phdMax);
	TH1I *h_R_mcpSum_qCenter_0		= new TH1I("h_R_mcpSum_qCenter_0"	,"Right MCP sum w/ (X,Y) in \"center\" quadrant & sum > 400"	, 4*phdBins, 4*phdMin, 4*phdMax);
	TH1I *h_R_mcpX_qCenter_0		= new TH1I("h_R_mcpX_qCenter_0"	,"Right MCP-X w/ (X,Y) in \"center\" quadrant & sum > 400"	, mapBins, mapMin, mapMax);
	TH1I *h_R_mcpY_qCenter_0		= new TH1I("h_R_mcpY_qCenter_0"	,"Right MCP-Y w/ (X,Y) in \"center\" quadrant & sum > 400"	, mapBins, mapMin, mapMax);
	
	TH1I *h_R_mcpA_qA_2		= new TH1I("h_R_mcpA_qA_2"	,"Right MCP-A w/ (X,Y) in quadrant A & sum > 400"	, phdBins, phdMin, phdMax);
	TH1I *h_R_mcpB_qA_2		= new TH1I("h_R_mcpB_qA_2"	,"Right MCP-B w/ (X,Y) in quadrant A & sum > 400"	, phdBins, phdMin, phdMax);
	TH1I *h_R_mcpC_qA_2		= new TH1I("h_R_mcpC_qA_2"	,"Right MCP-C w/ (X,Y) in quadrant A & sum > 400"	, phdBins, phdMin, phdMax);
	TH1I *h_R_mcpD_qA_2		= new TH1I("h_R_mcpD_qA_2"	,"Right MCP-D w/ (X,Y) in quadrant A & sum > 400"	, phdBins, phdMin, phdMax);
	TH1I *h_R_mcpSum_qA_2	= new TH1I("h_R_mcpSum_qA_2"	,"Right MCP sum w/ (X,Y) in quadrant A & sum > 400"	, 4*phdBins, 4*phdMin, 4*phdMax);
	TH1I *h_R_mcpX_qA_2		= new TH1I("h_R_mcpX_qA_2"	,"Right MCP-X w/ (X,Y) in quadrant A & sum > 400"	, mapBins, mapMin, mapMax);
	TH1I *h_R_mcpY_qA_2		= new TH1I("h_R_mcpY_qA_2"	,"Right MCP-Y w/ (X,Y) in quadrant A & sum > 400"	, mapBins, mapMin, mapMax);
	
	TH1I *h_R_mcpA_qB_2		= new TH1I("h_R_mcpA_qB_2"	,"Right MCP-A w/ (X,Y) in quadrant B & sum > 400"	, phdBins, phdMin, phdMax);
	TH1I *h_R_mcpB_qB_2		= new TH1I("h_R_mcpB_qB_2"	,"Right MCP-B w/ (X,Y) in quadrant B & sum > 400"	, phdBins, phdMin, phdMax);
	TH1I *h_R_mcpC_qB_2		= new TH1I("h_R_mcpC_qB_2"	,"Right MCP-C w/ (X,Y) in quadrant B & sum > 400"	, phdBins, phdMin, phdMax);
	TH1I *h_R_mcpD_qB_2		= new TH1I("h_R_mcpD_qB_2"	,"Right MCP-D w/ (X,Y) in quadrant B & sum > 400"	, phdBins, phdMin, phdMax);
	TH1I *h_R_mcpSum_qB_2	= new TH1I("h_R_mcpSum_qB_2"	,"Right MCP sum w/ (X,Y) in quadrant B & sum > 400"	, 4*phdBins, 4*phdMin, 4*phdMax);
	TH1I *h_R_mcpX_qB_2		= new TH1I("h_R_mcpX_qB_2"	,"Right MCP-X w/ (X,Y) in quadrant B & sum > 400"	, mapBins, mapMin, mapMax);
	TH1I *h_R_mcpY_qB_2		= new TH1I("h_R_mcpY_qB_2"	,"Right MCP-Y w/ (X,Y) in quadrant B & sum > 400"	, mapBins, mapMin, mapMax);
	
	TH1I *h_R_mcpA_qC_2		= new TH1I("h_R_mcpA_qC_2"	,"Right MCP-A w/ (X,Y) in quadrant C & sum > 400"	, phdBins, phdMin, phdMax);
	TH1I *h_R_mcpB_qC_2		= new TH1I("h_R_mcpB_qC_2"	,"Right MCP-B w/ (X,Y) in quadrant C & sum > 400"	, phdBins, phdMin, phdMax);
	TH1I *h_R_mcpC_qC_2		= new TH1I("h_R_mcpC_qC_2"	,"Right MCP-C w/ (X,Y) in quadrant C & sum > 400"	, phdBins, phdMin, phdMax);
	TH1I *h_R_mcpD_qC_2		= new TH1I("h_R_mcpD_qC_2"	,"Right MCP-D w/ (X,Y) in quadrant C & sum > 400"	, phdBins, phdMin, phdMax);
	TH1I *h_R_mcpSum_qC_2	= new TH1I("h_R_mcpSum_qC_2"	,"Right MCP sum w/ (X,Y) in quadrant C & sum > 400"	, 4*phdBins, 4*phdMin, 4*phdMax);
	TH1I *h_R_mcpX_qC_2		= new TH1I("h_R_mcpX_qC_2"	,"Right MCP-X w/ (X,Y) in quadrant C & sum > 400"	, mapBins, mapMin, mapMax);
	TH1I *h_R_mcpY_qC_2		= new TH1I("h_R_mcpY_qC_2"	,"Right MCP-Y w/ (X,Y) in quadrant C & sum > 400"	, mapBins, mapMin, mapMax);
	
	TH1I *h_R_mcpA_qD_2		= new TH1I("h_R_mcpA_qD_2"	,"Right MCP-A w/ (X,Y) in quadrant D & sum > 400"	, phdBins, phdMin, phdMax);
	TH1I *h_R_mcpB_qD_2		= new TH1I("h_R_mcpB_qD_2"	,"Right MCP-B w/ (X,Y) in quadrant D & sum > 400"	, phdBins, phdMin, phdMax);
	TH1I *h_R_mcpC_qD_2		= new TH1I("h_R_mcpC_qD_2"	,"Right MCP-C w/ (X,Y) in quadrant D & sum > 400"	, phdBins, phdMin, phdMax);
	TH1I *h_R_mcpD_qD_2		= new TH1I("h_R_mcpD_qD_2"	,"Right MCP-D w/ (X,Y) in quadrant D & sum > 400"	, phdBins, phdMin, phdMax);
	TH1I *h_R_mcpSum_qD_2	= new TH1I("h_R_mcpSum_qD_2"	,"Right MCP sum w/ (X,Y) in quadrant D & sum > 400"	, 4*phdBins, 4*phdMin, 4*phdMax);
	TH1I *h_R_mcpX_qD_2		= new TH1I("h_R_mcpX_qD_2"	,"Right MCP-X w/ (X,Y) in quadrant D & sum > 400"	, mapBins, mapMin, mapMax);
	TH1I *h_R_mcpY_qD_2		= new TH1I("h_R_mcpY_qD_2"	,"Right MCP-Y w/ (X,Y) in quadrant D & sum > 400"	, mapBins, mapMin, mapMax);
	
	TH1I *h_R_mcpA_qCenter_2		= new TH1I("h_R_mcpA_qCenter_2"	,"Right MCP-A w/ (X,Y) in \"center\" quadrant & sum > 400"	, phdBins, phdMin, phdMax);
	TH1I *h_R_mcpB_qCenter_2		= new TH1I("h_R_mcpB_qCenter_2"	,"Right MCP-B w/ (X,Y) in \"center\" quadrant & sum > 400"	, phdBins, phdMin, phdMax);
	TH1I *h_R_mcpC_qCenter_2		= new TH1I("h_R_mcpC_qCenter_2"	,"Right MCP-C w/ (X,Y) in \"center\" quadrant & sum > 400"	, phdBins, phdMin, phdMax);
	TH1I *h_R_mcpD_qCenter_2		= new TH1I("h_R_mcpD_qCenter_2"	,"Right MCP-D w/ (X,Y) in \"center\" quadrant & sum > 400"	, phdBins, phdMin, phdMax);
	TH1I *h_R_mcpSum_qCenter_2		= new TH1I("h_R_mcpSum_qCenter_2"	,"Right MCP sum w/ (X,Y) in \"center\" quadrant & sum > 400"	, 4*phdBins, 4*phdMin, 4*phdMax);
	TH1I *h_R_mcpX_qCenter_2		= new TH1I("h_R_mcpX_qCenter_2"	,"Right MCP-X w/ (X,Y) in \"center\" quadrant & sum > 400"	, mapBins, mapMin, mapMax);
	TH1I *h_R_mcpY_qCenter_2		= new TH1I("h_R_mcpY_qCenter_2"	,"Right MCP-Y w/ (X,Y) in \"center\" quadrant & sum > 400"	, mapBins, mapMin, mapMax);
	
	TH2I *h_R_mcp_map_physical_2	= new TH2I("h_R_mcp_map_physical_2", "Right MCP map w/ sum > 400, physical locations (mm)", mapBins, 30*mapMin, 30*mapMax, mapBins, 30*mapMin, 30*mapMax);
	TH2I *h_T_mcp_map_physical_2	= new TH2I("h_T_mcp_map_physical_2", "Top MCP map w/ sum > 400, physical locations (mm)", mapBins, 30*mapMin, 30*mapMax, mapBins, 30*mapMin, 30*mapMax);
	
	TH1I *h_missing_R_mcp = new TH1I("h_missing_R_mcp","Which posts missing in Right MCP data, 0=A, 1=B, 2=C, 3=D",4,0,4);
	TH1I *h_missing_T_mcp = new TH1I("h_missing_T_mcp","Which posts missing in Top MCP data, 0=A, 1=B, 2=C, 3=D",4,0,4);
	TH1I *hn_missing_R_posts = new TH1I("hn_missing_R_mcp","Number of posts missing in Right MCP data",5,0,5);
	TH1I *hn_missing_T_posts = new TH1I("hn_missing_T_mcp","Number of posts missing in Top MCP data",5,0,5);
	
	Int_t n_missing_R_posts, n_missing_T_posts;
	Int_t missing_R_mcp[4], missing_T_mcp[4];
	Int_t n_missing_R_mcpA_only, n_missing_R_mcpB_only, n_missing_R_mcpC_only, n_missing_R_mcpD_only;
	Int_t n_missing_T_mcpA_only, n_missing_T_mcpB_only, n_missing_T_mcpC_only, n_missing_T_mcpD_only;
	
	TH2I *h_R_mcp_map_missingA_1		= new TH2I("h_R_mcp_map_missingA_1", "Right MCP map w/ sum > 200, events where post A was reconstructed", mapBins, mapMin, mapMax, mapBins, mapMin, mapMax);
	TH2I *h_R_mcp_map_missingB_1		= new TH2I("h_R_mcp_map_missingB_1", "Right MCP map w/ sum > 200, events where post B was reconstructed", mapBins, mapMin, mapMax, mapBins, mapMin, mapMax);
	TH2I *h_R_mcp_map_missingC_1		= new TH2I("h_R_mcp_map_missingC_1", "Right MCP map w/ sum > 200, events where post C was reconstructed", mapBins, mapMin, mapMax, mapBins, mapMin, mapMax);
	TH2I *h_R_mcp_map_missingD_1		= new TH2I("h_R_mcp_map_missingD_1", "Right MCP map w/ sum > 200, events where post D was reconstructed", mapBins, mapMin, mapMax, mapBins, mapMin, mapMax);
	TH2I *h_R_mcp_map_reconstructed_1	= new TH2I("h_R_mcp_map_reconstructed_1", "Right MCP map w/ sum > 200, single missing posts reconstructed", mapBins, mapMin, mapMax, mapBins, mapMin, mapMax);
	TH2I *h_R_mcp_map_missingOne_1		= new TH2I("h_R_mcp_map_missingOne_1", "Right MCP map w/ sum > 200, events where one post was reconstructed", mapBins, mapMin, mapMax, mapBins, mapMin, mapMax);
	TH2I *h_T_mcp_map_missingA_1		= new TH2I("h_T_mcp_map_missingA_1", "Top MCP map w/ sum > 200, events where post A was reconstructed", mapBins, mapMin, mapMax, mapBins, mapMin, mapMax);
	TH2I *h_T_mcp_map_missingB_1		= new TH2I("h_T_mcp_map_missingB_1", "Top MCP map w/ sum > 200, events where post B was reconstructed", mapBins, mapMin, mapMax, mapBins, mapMin, mapMax);
	TH2I *h_T_mcp_map_missingC_1		= new TH2I("h_T_mcp_map_missingC_1", "Top MCP map w/ sum > 200, events where post C was reconstructed", mapBins, mapMin, mapMax, mapBins, mapMin, mapMax);
	TH2I *h_T_mcp_map_missingD_1		= new TH2I("h_T_mcp_map_missingD_1", "Top MCP map w/ sum > 200, events where post D was reconstructed", mapBins, mapMin, mapMax, mapBins, mapMin, mapMax);
	TH2I *h_T_mcp_map_reconstructed_1	= new TH2I("h_T_mcp_map_reconstructed_1", "Top MCP map w/ sum > 200, single missing posts reconstructed", mapBins, mapMin, mapMax, mapBins, mapMin, mapMax);
	TH2I *h_T_mcp_map_missingOne_1		= new TH2I("h_T_mcp_map_missingOne_1", "Top MCP map w/ sum > 200, events where one post was reconstructed", mapBins, mapMin, mapMax, mapBins, mapMin, mapMax);
	
	TH1I *h_R_mcpA_reconstruction_diffs	= new TH1I("h_R_mcpA_reconstruction_diffs","(Reconstructed A - Measured A) for events with all 4 posts, Sum>~200, Right MCP", 30000, -5000, 15000);
	TH1I *h_R_mcpB_reconstruction_diffs	= new TH1I("h_R_mcpB_reconstruction_diffs","(Reconstructed B - Measured B) for events with all 4 posts, Sum>~200, Right MCP", 30000, -5000, 15000);
	TH1I *h_R_mcpC_reconstruction_diffs	= new TH1I("h_R_mcpC_reconstruction_diffs","(Reconstructed C - Measured C) for events with all 4 posts, Sum>~200, Right MCP", 30000, -5000, 15000);
	TH1I *h_R_mcpD_reconstruction_diffs	= new TH1I("h_R_mcpD_reconstruction_diffs","(Reconstructed D - Measured D) for events with all 4 posts, Sum>~200, Right MCP", 30000, -5000, 15000);
	TH1I *h_T_mcpA_reconstruction_diffs	= new TH1I("h_T_mcpA_reconstruction_diffs","(Reconstructed A - Measured A) for events with all 4 posts, Sum>~200, Top MCP", 30000, -5000, 15000);
	TH1I *h_T_mcpB_reconstruction_diffs	= new TH1I("h_T_mcpB_reconstruction_diffs","(Reconstructed B - Measured B) for events with all 4 posts, Sum>~200, Top MCP", 30000, -5000, 15000);
	TH1I *h_T_mcpC_reconstruction_diffs	= new TH1I("h_T_mcpC_reconstruction_diffs","(Reconstructed C - Measured C) for events with all 4 posts, Sum>~200, Top MCP", 30000, -5000, 15000);
	TH1I *h_T_mcpD_reconstruction_diffs	= new TH1I("h_T_mcpD_reconstruction_diffs","(Reconstructed D - Measured D) for events with all 4 posts, Sum>~200, Top MCP", 30000, -5000, 15000);
	
	TH1I *h_R_mcpA_normed_reconstruction_diffs	= new TH1I("h_R_mcpA_normed_reconstruction_diffs","(Reconstructed A - Measured A)/(Measured A) for events with all 4 posts, Sum>~200, Right MCP", 10000, -1, 3);
	TH1I *h_R_mcpB_normed_reconstruction_diffs	= new TH1I("h_R_mcpB_normed_reconstruction_diffs","(Reconstructed B - Measured B)/(Measured B) for events with all 4 posts, Sum>~200, Right MCP", 10000, -1, 3);
	TH1I *h_R_mcpC_normed_reconstruction_diffs	= new TH1I("h_R_mcpC_normed_reconstruction_diffs","(Reconstructed C - Measured C)/(Measured C) for events with all 4 posts, Sum>~200, Right MCP", 10000, -1, 3);
	TH1I *h_R_mcpD_normed_reconstruction_diffs	= new TH1I("h_R_mcpD_normed_reconstruction_diffs","(Reconstructed D - Measured D)/(Measured D) for events with all 4 posts, Sum>~200, Right MCP", 10000, -1, 3);
	TH1I *h_T_mcpA_normed_reconstruction_diffs	= new TH1I("h_T_mcpA_normed_reconstruction_diffs","(Reconstructed A - Measured A)/(Measured A) for events with all 4 posts, Sum>~200, Top MCP", 10000, -1, 3);
	TH1I *h_T_mcpB_normed_reconstruction_diffs	= new TH1I("h_T_mcpB_normed_reconstruction_diffs","(Reconstructed B - Measured B)/(Measured B) for events with all 4 posts, Sum>~200, Top MCP", 10000, -1, 3);
	TH1I *h_T_mcpC_normed_reconstruction_diffs	= new TH1I("h_T_mcpC_normed_reconstruction_diffs","(Reconstructed C - Measured C)/(Measured C) for events with all 4 posts, Sum>~200, Top MCP", 10000, -1, 3);
	TH1I *h_T_mcpD_normed_reconstruction_diffs	= new TH1I("h_T_mcpD_normed_reconstruction_diffs","(Reconstructed D - Measured D)/(Measured D) for events with all 4 posts, Sum>~200, Top MCP", 10000, -1, 3);
	
	TH1I *h_R_mcpA_FidArea_0		= new TH1I("h_R_mcpA_FidArea_0"	,"Right MCP-A w/ (x,y) in Fiducial Area & No cut on Sum"	, phdBins, phdMin, phdMax);
	TH1I *h_R_mcpB_FidArea_0		= new TH1I("h_R_mcpB_FidArea_0"	,"Right MCP-B w/ (x,y) in Fiducial Area & No cut on Sum"	, phdBins, phdMin, phdMax);
	TH1I *h_R_mcpC_FidArea_0		= new TH1I("h_R_mcpC_FidArea_0"	,"Right MCP-C w/ (x,y) in Fiducial Area & No cut on Sum"	, phdBins, phdMin, phdMax);
	TH1I *h_R_mcpD_FidArea_0		= new TH1I("h_R_mcpD_FidArea_0"	,"Right MCP-D w/ (x,y) in Fiducial Area & No cut on Sum"	, phdBins, phdMin, phdMax);
	TH1I *h_R_mcpSum_FidArea_0		= new TH1I("h_R_mcpSum_FidArea_0"	,"Right MCP-Sum w/ (x,y) in Fiducial Area & No cut on Sum"	, phdBins, phdMin, phdMax);
	TH1I *h_R_mcpA_FidArea_2		= new TH1I("h_R_mcpA_FidArea_2"	,"Right MCP-A w/ (x,y) in Fiducial Area & Sum > 400"	, phdBins, phdMin, phdMax);
	TH1I *h_R_mcpB_FidArea_2		= new TH1I("h_R_mcpB_FidArea_2"	,"Right MCP-B w/ (x,y) in Fiducial Area & Sum > 400"	, phdBins, phdMin, phdMax);
	TH1I *h_R_mcpC_FidArea_2		= new TH1I("h_R_mcpC_FidArea_2"	,"Right MCP-C w/ (x,y) in Fiducial Area & Sum > 400"	, phdBins, phdMin, phdMax);
	TH1I *h_R_mcpD_FidArea_2		= new TH1I("h_R_mcpD_FidArea_2"	,"Right MCP-D w/ (x,y) in Fiducial Area & Sum > 400"	, phdBins, phdMin, phdMax);
	TH1I *h_R_mcpSum_FidArea_2		= new TH1I("h_R_mcpSum_FidArea_2"	,"Right MCP-Sum w/ (x,y) in Fiducial Area & Sum > 400"	, phdBins, phdMin, phdMax);
	
	TH1I *h_T_mcpA_FidArea_0		= new TH1I("h_T_mcpA_FidArea_0"	,"Top MCP-A w/ (x,y) in Fiducial Area & No cut on Sum"	, phdBins, phdMin, phdMax);
	TH1I *h_T_mcpB_FidArea_0		= new TH1I("h_T_mcpB_FidArea_0"	,"Top MCP-B w/ (x,y) in Fiducial Area & No cut on Sum"	, phdBins, phdMin, phdMax);
	TH1I *h_T_mcpC_FidArea_0		= new TH1I("h_T_mcpC_FidArea_0"	,"Top MCP-C w/ (x,y) in Fiducial Area & No cut on Sum"	, phdBins, phdMin, phdMax);
	TH1I *h_T_mcpD_FidArea_0		= new TH1I("h_T_mcpD_FidArea_0"	,"Top MCP-D w/ (x,y) in Fiducial Area & No cut on Sum"	, phdBins, phdMin, phdMax);
	TH1I *h_T_mcpSum_FidArea_0		= new TH1I("h_T_mcpSum_FidArea_0"	,"Top MCP-Sum w/ (x,y) in Fiducial Area & No cut on Sum"	, phdBins, phdMin, phdMax);
	TH1I *h_T_mcpA_FidArea_2		= new TH1I("h_T_mcpA_FidArea_2"	,"Top MCP-A w/ (x,y) in Fiducial Area & Sum > 400"	, phdBins, phdMin, phdMax);
	TH1I *h_T_mcpB_FidArea_2		= new TH1I("h_T_mcpB_FidArea_2"	,"Top MCP-B w/ (x,y) in Fiducial Area & Sum > 400"	, phdBins, phdMin, phdMax);
	TH1I *h_T_mcpC_FidArea_2		= new TH1I("h_T_mcpC_FidArea_2"	,"Top MCP-C w/ (x,y) in Fiducial Area & Sum > 400"	, phdBins, phdMin, phdMax);
	TH1I *h_T_mcpD_FidArea_2		= new TH1I("h_T_mcpD_FidArea_2"	,"Top MCP-D w/ (x,y) in Fiducial Area & Sum > 400"	, phdBins, phdMin, phdMax);
	TH1I *h_T_mcpSum_FidArea_2		= new TH1I("h_T_mcpSum_FidArea_2"	,"Top MCP-Sum w/ (x,y) in Fiducial Area & Sum > 400"	, phdBins, phdMin, phdMax);
	
	TH1I *h_mcpA_cut		= new TH1I("h_mcpA_cut"	,"Top MCP-A PHD for C post hot spot"	, phdBins, phdMin, phdMax);
	TH1I *h_mcpB_cut		= new TH1I("h_mcpB_cut"	,"Top MCP-B PHD for C post hot spot"	, phdBins, phdMin, phdMax);
	TH1I *h_mcpC_cut		= new TH1I("h_mcpC_cut"	,"Top MCP-C PHD for C post hot spot"	, phdBins, phdMin, phdMax);
	TH1I *h_mcpD_cut		= new TH1I("h_mcpD_cut"	,"Top MCP-D PHD for C post hot spot"	, phdBins, phdMin, phdMax);
	TH1I *h_mcpSum_cut		= new TH1I("h_mcpSum_cut"	,"Top MCP sum PHD for C post hot spot"	, 4*phdBins, 4*phdMin, 4*phdMax);
	
	TH2I *h_R_mcp_map_0_post	= new TH2I("h_R_mcp_map_0_post", "Right MCP map w/ all data cutting only the pedestals", mapBins, mapMin, mapMax, mapBins, mapMin, mapMax);
	TH2I *h_R_mcp_map_2_post	= new TH2I("h_R_mcp_map_2_post", "Right MCP map w/ sum > 400 & cutting out the pedestals", mapBins, mapMin, mapMax, mapBins, mapMin, mapMax);
	TH2I *h_T_mcp_map_0_post	= new TH2I("h_T_mcp_map_0_post", "Top MCP map w/ all data cutting only the pedestals", mapBins, mapMin, mapMax, mapBins, mapMin, mapMax);
	TH2I *h_T_mcp_map_2_post	= new TH2I("h_T_mcp_map_2_post", "Top MCP map w/ sum > 400 & cutting out the pedestals", mapBins, mapMin, mapMax, mapBins, mapMin, mapMax);
	
	for (i=0; i<nEntries; i++) {
		
		if (i%1000000==0) printf("\nreached event %d",i);
		
		tree->GetEntry(i);
		
		rA = (Double_t)tree->GetLeaf("a_R_mcpA")->GetValue() - ped_R_mcpA;
		rB = (Double_t)tree->GetLeaf("a_R_mcpB")->GetValue() - ped_R_mcpB;
		rC = (Double_t)tree->GetLeaf("a_R_mcpC")->GetValue() - ped_R_mcpC;
		rD = (Double_t)tree->GetLeaf("a_R_mcpD")->GetValue() - ped_R_mcpD;
		rA += randgen->Rndm();
		rB += randgen->Rndm();
		rC += randgen->Rndm();
		rD += randgen->Rndm();
		rSum = rA + rB + rC + rD;
		rX = (rC + rD - rA - rB) / rSum;
		rY = (rA + rD - rC - rB) / rSum;
		rX_mm = scale * ((rX-x0)*TMath::Cos(theta) - (rY-y0)*TMath::Sin(theta));
		rY_mm = scale * ((rX-x0)*TMath::Sin(theta) + (rY-y0)*TMath::Cos(theta));
//		rX = 25.0 * (rC + rD - rA - rB + randgen->Rndm()) / (rSum + randgen->Rndm());
//		rY = 25.0 * (rA + rD - rC - rB + randgen->Rndm()) / (rSum + randgen->Rndm());
		
		tA = (Double_t)tree->GetLeaf("a_T_mcpA")->GetValue() - ped_T_mcpA;
		tB = (Double_t)tree->GetLeaf("a_T_mcpB")->GetValue() - ped_T_mcpB;
		tC = (Double_t)tree->GetLeaf("a_T_mcpC")->GetValue() - ped_T_mcpC;
		tD = (Double_t)tree->GetLeaf("a_T_mcpD")->GetValue() - ped_T_mcpD;
		tA += randgen->Rndm();
		tB += randgen->Rndm();
		tC += randgen->Rndm();
		tD += randgen->Rndm();
		tSum = tA + tB + tC + tD;
		tX = (tC + tD - tA - tB) / tSum;
		tY = (tA + tD - tC - tB) / tSum;
//		tX = 25.0 * (tC + tD - tA - tB + randgen->Rndm()) / (tSum + randgen->Rndm());
//		tY = 25.0 * (tA + tD - tC - tB + randgen->Rndm()) / (tSum + randgen->Rndm());
		
// TOP MCP		
		// Map with absolutely no cuts
		//h_R_mcp_map_0->Fill(rX,rY);
		h_T_mcp_map_0->Fill(tX,tY);
		h_T_mcpA_0->Fill(tA);
		h_T_mcpB_0->Fill(tB);
		h_T_mcpC_0->Fill(tC);
		h_T_mcpD_0->Fill(tD);
		h_T_mcpSum_0->Fill(tSum);
		h_T_mcpX_0->Fill(tX);
		h_T_mcpY_0->Fill(tY);
		if (a_T_mcpA_lo < tA && a_T_mcpB_lo < tB && a_T_mcpC_lo < tC && a_T_mcpD_lo < tD) {
			h_T_mcp_map_0_post->Fill(tX,tY);
		}
		
		// Sum > 200
		//if (rSum>200) h_R_mcp_map_1->Fill(rX,rY);
		if (tSum>200) {
			h_T_mcp_map_1->Fill(tX,tY);
			h_T_mcpA_1->Fill(tA);
			h_T_mcpB_1->Fill(tB);
			h_T_mcpC_1->Fill(tC);
			h_T_mcpD_1->Fill(tD);
			h_T_mcpSum_1->Fill(tSum);
			h_T_mcpX_1->Fill(tX);
			h_T_mcpY_1->Fill(tY);
			h_T_mcp_map_reconstructed_1->Fill(tX,tY);
		}
		
		// Sum > 400
		//if (rSum>400) h_R_mcp_map_2->Fill(rX,rY);
		if (tSum>400) {
			h_T_mcp_map_2->Fill(tX,tY);
			h_T_mcpA_2->Fill(tA);
			h_T_mcpB_2->Fill(tB);
			h_T_mcpC_2->Fill(tC);
			h_T_mcpD_2->Fill(tD);
			h_T_mcpSum_2->Fill(tSum);
			h_T_mcpX_2->Fill(tX);
			h_T_mcpY_2->Fill(tY);
			if (a_T_mcpA_lo < tA && a_T_mcpB_lo < tB && a_T_mcpC_lo < tC && a_T_mcpD_lo < tD) {
				h_T_mcp_map_2_post->Fill(tX,tY);
			}
		}
		
		// Sum > 600
		//if (rSum>600) h_R_mcp_map_3->Fill(rX,rY);
		if (tSum>600) {
			h_T_mcp_map_3->Fill(tX,tY);
			h_T_mcpA_3->Fill(tA);
			h_T_mcpB_3->Fill(tB);
			h_T_mcpC_3->Fill(tC);
			h_T_mcpD_3->Fill(tD);
			h_T_mcpSum_3->Fill(tSum);
			h_T_mcpX_3->Fill(tX);
			h_T_mcpY_3->Fill(tY);
		}
		
		// Sum > 800
		//if (rSum>800) h_R_mcp_map_4->Fill(rX,rY);
		if (tSum>800) {
			h_T_mcp_map_4->Fill(tX,tY);
			h_T_mcpA_4->Fill(tA);
			h_T_mcpB_4->Fill(tB);
			h_T_mcpC_4->Fill(tC);
			h_T_mcpD_4->Fill(tD);
			h_T_mcpSum_4->Fill(tSum);
			h_T_mcpX_4->Fill(tX);
			h_T_mcpY_4->Fill(tY);
		}
		
		// Quadrant A
		if (tX < 0 && tY > 0) {
			h_T_mcpA_qA_0->Fill(tA);
			h_T_mcpB_qA_0->Fill(tB);
			h_T_mcpC_qA_0->Fill(tC);
			h_T_mcpD_qA_0->Fill(tD);
			h_T_mcpSum_qA_0->Fill(tSum);
			h_T_mcpX_qA_0->Fill(tX);
			h_T_mcpY_qA_0->Fill(tY);
			if (tSum > 400) {
				h_T_mcpA_qA_2->Fill(tA);
				h_T_mcpB_qA_2->Fill(tB);
				h_T_mcpC_qA_2->Fill(tC);
				h_T_mcpD_qA_2->Fill(tD);
				h_T_mcpSum_qA_2->Fill(tSum);
				h_T_mcpX_qA_2->Fill(tX);
				h_T_mcpY_qA_2->Fill(tY);
			}
		}
		
		// Quadrant B
		if (tX < 0 && tY < 0) {
			h_T_mcpA_qB_0->Fill(tA);
			h_T_mcpB_qB_0->Fill(tB);
			h_T_mcpC_qB_0->Fill(tC);
			h_T_mcpD_qB_0->Fill(tD);
			h_T_mcpSum_qB_0->Fill(tSum);
			h_T_mcpX_qB_0->Fill(tX);
			h_T_mcpY_qB_0->Fill(tY);
			if (tSum > 400) {
				h_T_mcpA_qB_2->Fill(tA);
				h_T_mcpB_qB_2->Fill(tB);
				h_T_mcpC_qB_2->Fill(tC);
				h_T_mcpD_qB_2->Fill(tD);
				h_T_mcpSum_qB_2->Fill(tSum);
				h_T_mcpX_qB_2->Fill(tX);
				h_T_mcpY_qB_2->Fill(tY);
			}
		}
		
		// Quadrant C
		if (tX > 0 && tY < 0) {
			h_T_mcpA_qC_0->Fill(tA);
			h_T_mcpB_qC_0->Fill(tB);
			h_T_mcpC_qC_0->Fill(tC);
			h_T_mcpD_qC_0->Fill(tD);
			h_T_mcpSum_qC_0->Fill(tSum);
			h_T_mcpX_qC_0->Fill(tX);
			h_T_mcpY_qC_0->Fill(tY);
			if (tSum > 400) {
				h_T_mcpA_qC_2->Fill(tA);
				h_T_mcpB_qC_2->Fill(tB);
				h_T_mcpC_qC_2->Fill(tC);
				h_T_mcpD_qC_2->Fill(tD);
				h_T_mcpSum_qC_2->Fill(tSum);
				h_T_mcpX_qC_2->Fill(tX);
				h_T_mcpY_qC_2->Fill(tY);
			}
		}
		
		// Quadrant D
		if (tX > 0 && tY > 0) {
			h_T_mcpA_qD_0->Fill(tA);
			h_T_mcpB_qD_0->Fill(tB);
			h_T_mcpC_qD_0->Fill(tC);
			h_T_mcpD_qD_0->Fill(tD);
			h_T_mcpSum_qD_0->Fill(tSum);
			h_T_mcpX_qD_0->Fill(tX);
			h_T_mcpY_qD_0->Fill(tY);
			if (tSum > 400) {
				h_T_mcpA_qD_2->Fill(tA);
				h_T_mcpB_qD_2->Fill(tB);
				h_T_mcpC_qD_2->Fill(tC);
				h_T_mcpD_qD_2->Fill(tD);
				h_T_mcpSum_qD_2->Fill(tSum);
				h_T_mcpX_qD_2->Fill(tX);
				h_T_mcpY_qD_2->Fill(tY);
			}
		}
		
		// Center Quadrant
		if (-0.5 < tX && tX < 0.5 && -0.5 < tY && tY < 0.5) {
			h_T_mcpA_qCenter_0->Fill(tA);
			h_T_mcpB_qCenter_0->Fill(tB);
			h_T_mcpC_qCenter_0->Fill(tC);
			h_T_mcpD_qCenter_0->Fill(tD);
			h_T_mcpSum_qCenter_0->Fill(tSum);
			h_T_mcpX_qCenter_0->Fill(tX);
			h_T_mcpY_qCenter_0->Fill(tY);
			if (tSum > 400) {
				h_T_mcpA_qCenter_2->Fill(tA);
				h_T_mcpB_qCenter_2->Fill(tB);
				h_T_mcpC_qCenter_2->Fill(tC);
				h_T_mcpD_qCenter_2->Fill(tD);
				h_T_mcpSum_qCenter_2->Fill(tSum);
				h_T_mcpX_qCenter_2->Fill(tX);
				h_T_mcpY_qCenter_2->Fill(tY);
			}
		}
		
		// Fiducial area
		if (fid_area_T_mcpX_lo < tX && tX < fid_area_T_mcpX_hi && fid_area_T_mcpY_lo < tY && tY < fid_area_T_mcpY_hi) {
			h_T_mcpA_FidArea_0->Fill(tA);
			h_T_mcpB_FidArea_0->Fill(tB);
			h_T_mcpC_FidArea_0->Fill(tC);
			h_T_mcpD_FidArea_0->Fill(tD);
			h_T_mcpSum_FidArea_0->Fill(tSum);
			if (tSum > 400) {
				h_T_mcpA_FidArea_2->Fill(tA);
				h_T_mcpB_FidArea_2->Fill(tB);
				h_T_mcpC_FidArea_2->Fill(tC);
				h_T_mcpD_FidArea_2->Fill(tD);
				h_T_mcpSum_FidArea_2->Fill(tSum);
			}
		}
		
		// Special cut
		if ( 0.864 < tX && tX < 0.876 && -0.872 < tY && tY < -0.864) {
			h_mcpA_cut->Fill(tA);
			h_mcpB_cut->Fill(tB);
			h_mcpC_cut->Fill(tC);
			h_mcpD_cut->Fill(tD);
			h_mcpSum_cut->Fill(tSum);
		}
		
// RIGHT MCP		
		// Map with absolutely no cuts
		//h_R_mcp_map_0->Fill(rX,rY);
		h_R_mcp_map_0->Fill(rX,rY);
		h_R_mcpA_0->Fill(rA);
		h_R_mcpB_0->Fill(rB);
		h_R_mcpC_0->Fill(rC);
		h_R_mcpD_0->Fill(rD);
		h_R_mcpSum_0->Fill(rSum);
		h_R_mcpX_0->Fill(rX);
		h_R_mcpY_0->Fill(rY);
		if (a_R_mcpA_lo < rA && a_R_mcpB_lo < rB && a_R_mcpC_lo < rC && a_R_mcpD_lo < rD) {
			h_R_mcp_map_0_post->Fill(rX,rY);
		}
		
		// Sum > 200
		//if (rSum>200) h_R_mcp_map_1->Fill(rX,rY);
		if (rSum>200) {
			h_R_mcp_map_1->Fill(rX,rY);
			h_R_mcpA_1->Fill(rA);
			h_R_mcpB_1->Fill(rB);
			h_R_mcpC_1->Fill(rC);
			h_R_mcpD_1->Fill(rD);
			h_R_mcpSum_1->Fill(rSum);
			h_R_mcpX_1->Fill(rX);
			h_R_mcpY_1->Fill(rY);
			h_R_mcp_map_reconstructed_1->Fill(rX,rY);
		}
		
		// Sum > 400
		//if (rSum>400) h_R_mcp_map_2->Fill(rX,rY);
		if (rSum>400) {
			h_R_mcp_map_2->Fill(rX,rY);
			h_R_mcpA_2->Fill(rA);
			h_R_mcpB_2->Fill(rB);
			h_R_mcpC_2->Fill(rC);
			h_R_mcpD_2->Fill(rD);
			h_R_mcpSum_2->Fill(rSum);
			h_R_mcpX_2->Fill(rX);
			h_R_mcpY_2->Fill(rY);
			if (a_R_mcpA_lo < rA && a_R_mcpB_lo < rB && a_R_mcpC_lo < rC && a_R_mcpD_lo < rD) {
				h_R_mcp_map_2_post->Fill(rX,rY);
			}
			h_R_mcp_map_physical_2->Fill(rX_mm, rY_mm);
		}
		
		// Sum > 600
		//if (rSum>600) h_R_mcp_map_3->Fill(rX,rY);
		if (rSum>600) {
			h_R_mcp_map_3->Fill(rX,rY);
			h_R_mcpA_3->Fill(rA);
			h_R_mcpB_3->Fill(rB);
			h_R_mcpC_3->Fill(rC);
			h_R_mcpD_3->Fill(rD);
			h_R_mcpSum_3->Fill(rSum);
			h_R_mcpX_3->Fill(rX);
			h_R_mcpY_3->Fill(rY);
		}
		
		// Sum > 800
		//if (rSum>800) h_R_mcp_map_4->Fill(rX,rY);
		if (rSum>800) {
			h_R_mcp_map_4->Fill(rX,rY);
			h_R_mcpA_4->Fill(rA);
			h_R_mcpB_4->Fill(rB);
			h_R_mcpC_4->Fill(rC);
			h_R_mcpD_4->Fill(rD);
			h_R_mcpSum_4->Fill(rSum);
			h_R_mcpX_4->Fill(rX);
			h_R_mcpY_4->Fill(rY);
		}
		
		// Quadrant A
		if (rX < 0 && rY > 0) {
			h_R_mcpA_qA_0->Fill(rA);
			h_R_mcpB_qA_0->Fill(rB);
			h_R_mcpC_qA_0->Fill(rC);
			h_R_mcpD_qA_0->Fill(rD);
			h_R_mcpSum_qA_0->Fill(rSum);
			h_R_mcpX_qA_0->Fill(rX);
			h_R_mcpY_qA_0->Fill(rY);
			if (rSum > 400) {
				h_R_mcpA_qA_2->Fill(rA);
				h_R_mcpB_qA_2->Fill(rB);
				h_R_mcpC_qA_2->Fill(rC);
				h_R_mcpD_qA_2->Fill(rD);
				h_R_mcpSum_qA_2->Fill(rSum);
				h_R_mcpX_qA_2->Fill(rX);
				h_R_mcpY_qA_2->Fill(rY);
			}
		}
		
		// Quadrant B
		if (rX < 0 && rY < 0) {
			h_R_mcpA_qB_0->Fill(rA);
			h_R_mcpB_qB_0->Fill(rB);
			h_R_mcpC_qB_0->Fill(rC);
			h_R_mcpD_qB_0->Fill(rD);
			h_R_mcpSum_qB_0->Fill(rSum);
			h_R_mcpX_qB_0->Fill(rX);
			h_R_mcpY_qB_0->Fill(rY);
			if (rSum > 400) {
				h_R_mcpA_qB_2->Fill(rA);
				h_R_mcpB_qB_2->Fill(rB);
				h_R_mcpC_qB_2->Fill(rC);
				h_R_mcpD_qB_2->Fill(rD);
				h_R_mcpSum_qB_2->Fill(rSum);
				h_R_mcpX_qB_2->Fill(rX);
				h_R_mcpY_qB_2->Fill(rY);
			}
		}
		
		// Quadrant C
		if (rX > 0 && rY < 0) {
			h_R_mcpA_qC_0->Fill(rA);
			h_R_mcpB_qC_0->Fill(rB);
			h_R_mcpC_qC_0->Fill(rC);
			h_R_mcpD_qC_0->Fill(rD);
			h_R_mcpSum_qC_0->Fill(rSum);
			h_R_mcpX_qC_0->Fill(rX);
			h_R_mcpY_qC_0->Fill(rY);
			if (rSum > 400) {
				h_R_mcpA_qC_2->Fill(rA);
				h_R_mcpB_qC_2->Fill(rB);
				h_R_mcpC_qC_2->Fill(rC);
				h_R_mcpD_qC_2->Fill(rD);
				h_R_mcpSum_qC_2->Fill(rSum);
				h_R_mcpX_qC_2->Fill(rX);
				h_R_mcpY_qC_2->Fill(rY);
			}
		}
		
		// Quadrant D
		if (rX > 0 && rY > 0) {
			h_R_mcpA_qD_0->Fill(rA);
			h_R_mcpB_qD_0->Fill(rB);
			h_R_mcpC_qD_0->Fill(rC);
			h_R_mcpD_qD_0->Fill(rD);
			h_R_mcpSum_qD_0->Fill(rSum);
			h_R_mcpX_qD_0->Fill(rX);
			h_R_mcpY_qD_0->Fill(rY);
			if (rSum > 400) {
				h_R_mcpA_qD_2->Fill(rA);
				h_R_mcpB_qD_2->Fill(rB);
				h_R_mcpC_qD_2->Fill(rC);
				h_R_mcpD_qD_2->Fill(rD);
				h_R_mcpSum_qD_2->Fill(rSum);
				h_R_mcpX_qD_2->Fill(rX);
				h_R_mcpY_qD_2->Fill(rY);
			}
		}
		
		// Center Quadrant
		if (-0.5 < rX && rX < 0.5 && -0.5 < rY && rY < 0.5) {
			h_R_mcpA_qCenter_0->Fill(rA);
			h_R_mcpB_qCenter_0->Fill(rB);
			h_R_mcpC_qCenter_0->Fill(rC);
			h_R_mcpD_qCenter_0->Fill(rD);
			h_R_mcpSum_qCenter_0->Fill(rSum);
			h_R_mcpX_qCenter_0->Fill(rX);
			h_R_mcpY_qCenter_0->Fill(rY);
			if (rSum > 400) {
				h_R_mcpA_qCenter_2->Fill(rA);
				h_R_mcpB_qCenter_2->Fill(rB);
				h_R_mcpC_qCenter_2->Fill(rC);
				h_R_mcpD_qCenter_2->Fill(rD);
				h_R_mcpSum_qCenter_2->Fill(rSum);
				h_R_mcpX_qCenter_2->Fill(rX);
				h_R_mcpY_qCenter_2->Fill(rY);
			}
		}
		
		// Fiducial area
		if (fid_area_R_mcpX_lo < rX && rX < fid_area_R_mcpX_hi && fid_area_R_mcpY_lo < rY && rY < fid_area_R_mcpY_hi) {
			h_R_mcpA_FidArea_0->Fill(rA);
			h_R_mcpB_FidArea_0->Fill(rB);
			h_R_mcpC_FidArea_0->Fill(rC);
			h_R_mcpD_FidArea_0->Fill(rD);
			h_R_mcpSum_FidArea_0->Fill(rSum);
			if (rSum > 400) {
				h_R_mcpA_FidArea_2->Fill(rA);
				h_R_mcpB_FidArea_2->Fill(rB);
				h_R_mcpC_FidArea_2->Fill(rC);
				h_R_mcpD_FidArea_2->Fill(rD);
				h_R_mcpSum_FidArea_2->Fill(rSum);
			}
		}
		
// New 2014-03-18 -- code to investigate missing posts.		
		Int_t iPostIndex;
		if (rA < a_missing_mcp_post) {
			iPostIndex = 0;
			missing_R_mcp[iPostIndex] = 1;
			h_missing_R_mcp->Fill(iPostIndex);
		}
		if (rB < a_missing_mcp_post) {
			iPostIndex = 1;
			missing_R_mcp[iPostIndex] = 1;
			h_missing_R_mcp->Fill(iPostIndex);
		}
		if (rC < a_missing_mcp_post) {
			iPostIndex = 2;
			missing_R_mcp[iPostIndex] = 1;
			h_missing_R_mcp->Fill(iPostIndex);
		}
		if (rD < a_missing_mcp_post) {
			iPostIndex = 3;
			missing_R_mcp[iPostIndex] = 1;
			h_missing_R_mcp->Fill(iPostIndex);
		}
		if (tA < a_missing_mcp_post) {
			iPostIndex = 0;
			missing_T_mcp[iPostIndex] = 1;
			h_missing_T_mcp->Fill(iPostIndex);
		}
		if (tB < a_missing_mcp_post) {
			iPostIndex = 1;
			missing_T_mcp[iPostIndex] = 1;
			h_missing_T_mcp->Fill(iPostIndex);
		}
		if (tC < a_missing_mcp_post) {
			iPostIndex = 2;
			missing_T_mcp[iPostIndex] = 1;
			h_missing_T_mcp->Fill(iPostIndex);
		}
		if (tD < a_missing_mcp_post) {
			iPostIndex = 3;
			missing_T_mcp[iPostIndex] = 1;
			h_missing_T_mcp->Fill(iPostIndex);
		}
		
		n_missing_R_posts = missing_R_mcp[0]+missing_R_mcp[1]+missing_R_mcp[2]+missing_R_mcp[3];
		n_missing_T_posts = missing_T_mcp[0]+missing_T_mcp[1]+missing_T_mcp[2]+missing_T_mcp[3];
		hn_missing_R_posts->Fill(n_missing_R_posts);
		hn_missing_T_posts->Fill(n_missing_T_posts);
		
// Reset missing post flags
		for (iPostIndex = 0; iPostIndex<4; iPostIndex++) {
			missing_R_mcp[iPostIndex] = 0;
			missing_T_mcp[iPostIndex] = 0;
		}
		
//*** RECONSTRUCT MISSING POSTS HERE ***//
// RIGHT MCP
// A post missing:
		if (rB+rC+rD > a_mcp_lo) { // other 3 posts are present if they pass this test
			rA_calc = rB*rD/rC;
			if (printReconstructionMessage) printf("a_R_mcpA: Data value = %6f; Reconstructed value = %6f.\n", rA, rA_calc);
			if (rA < a_missing_mcp_post) { // this post is missing
				n_missing_R_mcpA_only++;
				rSum = rA_calc + rB + rC + rD;
				rX = (-rA_calc - rB + rC + rD) / rSum;
				rY = ( rA_calc - rB - rC + rD) / rSum;
//				rX_mm = scale * ((rX-x0)*TMath::Cos(theta) - (rY-y0)*TMath::Sin(theta));
//				rY_mm = scale * ((rX-x0)*TMath::Sin(theta) + (rY-y0)*TMath::Cos(theta));
				h_R_mcp_map_missingA_1->Fill(rX,rY);
				h_R_mcp_map_missingOne_1->Fill(rX,rY);
				h_R_mcp_map_reconstructed_1->Fill(rX,rY);// this is also filled under if (rSum > a_mcp_lo), above
			}
			else { // all 4 posts are present and we can compare measured versus "reconstructed" value
				h_R_mcpA_reconstruction_diffs->Fill(rA_calc-rA);
				h_R_mcpA_normed_reconstruction_diffs->Fill((rA_calc-rA)/rA);
			}
		}
		
// B post missing:
		if (rA+rC+rD > a_mcp_lo) { // other 3 posts are present if they pass this test
			rB_calc = rA*rC/rD;
			if (printReconstructionMessage) printf("a_R_mcpB: Data value = %6f; Reconstructed value = %6f.\n", rB, rB_calc);
			if (rB < a_missing_mcp_post) { // this post is missing
				n_missing_R_mcpB_only++;
				rSum = rA + rB_calc + rC + rD;
				rX = (-rA - rB_calc + rC + rD) / rSum;
				rY = ( rA - rB_calc - rC + rD) / rSum;
//				rX_mm = scale * ((rX-x0)*TMath::Cos(theta) - (rY-y0)*TMath::Sin(theta));
//				rY_mm = scale * ((rX-x0)*TMath::Sin(theta) + (rY-y0)*TMath::Cos(theta));
				h_R_mcp_map_missingB_1->Fill(rX,rY);
				h_R_mcp_map_missingOne_1->Fill(rX,rY);
				h_R_mcp_map_reconstructed_1->Fill(rX,rY);// this is also filled under if (rSum > a_mcp_lo), above
			}
			else { // all 4 posts are present and we can compare measured versus "reconstructed" value
				h_R_mcpB_reconstruction_diffs->Fill(rB_calc-rB);
				h_R_mcpB_normed_reconstruction_diffs->Fill((rB_calc-rB)/rB);
			}
		}
		
// C post missing:
		if (rA+rB+rD > a_mcp_lo) { // other 3 posts are present if they pass this test
			rC_calc = rB*rD/rA;
			if (printReconstructionMessage) printf("a_R_mcpC: Data value = %6f; Reconstructed value = %6f.\n", rC, rC_calc);
			if (rC < a_missing_mcp_post) { // this post is missing
				n_missing_R_mcpC_only++;
				rSum = rA + rB + rC_calc + rD;
				rX = (-rA - rB + rC_calc + rD) / rSum;
				rY = ( rA - rB - rC_calc + rD) / rSum;
//				rX_mm = scale * ((rX-x0)*TMath::Cos(theta) - (rY-y0)*TMath::Sin(theta));
//				rY_mm = scale * ((rX-x0)*TMath::Sin(theta) + (rY-y0)*TMath::Cos(theta));
				h_R_mcp_map_missingC_1->Fill(rX,rY);
				h_R_mcp_map_missingOne_1->Fill(rX,rY);
				h_R_mcp_map_reconstructed_1->Fill(rX,rY);// this is also filled under if (rSum > a_mcp_lo), above
			}
			else { // all 4 posts are present and we can compare measured versus "reconstructed" value
				h_R_mcpC_reconstruction_diffs->Fill(rC_calc-rC);
				h_R_mcpC_normed_reconstruction_diffs->Fill((rC_calc-rC)/rC);
			}
		}
		
// D post missing:
		if (rA+rB+rC > a_mcp_lo) { // other 3 posts are present if they pass this test
			rD_calc = rA*rC/rB;
			if (printReconstructionMessage) printf("a_R_mcpD: Data value = %6f; Reconstructed value = %6f.\n", rD, rD_calc);
			if (rD < a_missing_mcp_post) { // this post is missing
				n_missing_R_mcpD_only++;
				rSum = rA + rB + rC + rD_calc;
				rX = (-rA - rB + rC + rD_calc) / rSum;
				rY = ( rA - rB - rC + rD_calc) / rSum;
//				rX_mm = scale * ((rX-x0)*TMath::Cos(theta) - (rY-y0)*TMath::Sin(theta));
//				rY_mm = scale * ((rX-x0)*TMath::Sin(theta) + (rY-y0)*TMath::Cos(theta));
				h_R_mcp_map_missingD_1->Fill(rX,rY);
				h_R_mcp_map_missingOne_1->Fill(rX,rY);
				h_R_mcp_map_reconstructed_1->Fill(rX,rY);// this is also filled under if (rSum > a_mcp_lo), above
			}
			else { // all 4 posts are present and we can compare measured versus "reconstructed" value
				h_R_mcpD_reconstruction_diffs->Fill(rD_calc-rD);
				h_R_mcpD_normed_reconstruction_diffs->Fill((rD_calc-rD)/rD);
			}
		}
		
// TOP MCP
// A post missing:
		if (tB+tC+tD > a_mcp_lo) { // other 3 posts are present if they pass this test
			tA_calc = tB*tD/tC;
			if (printReconstructionMessage) printf("a_T_mcpA: Data value = %6f; Reconstructed value = %6f.\n", tA, tA_calc);
			if (tA < a_missing_mcp_post) { // this post is missing
				n_missing_T_mcpA_only++;
				tSum = tA_calc + tB + tC + tD;
				tX = (-tA_calc - tB + tC + tD) / tSum;
				tY = ( tA_calc - tB - tC + tD) / tSum;
//				tX_mm = scale * ((tX-x0)*TMath::Cos(theta) - (tY-y0)*TMath::Sin(theta));
//				tY_mm = scale * ((tX-x0)*TMath::Sin(theta) + (tY-y0)*TMath::Cos(theta));
				h_T_mcp_map_missingA_1->Fill(tX,tY);
				h_T_mcp_map_missingOne_1->Fill(tX,tY);
				h_T_mcp_map_reconstructed_1->Fill(tX,tY);// this is also filled under if (tSum > a_mcp_lo), above
			}
			else { // all 4 posts are present and we can compare measured versus "reconstructed" value
				h_T_mcpA_reconstruction_diffs->Fill(tA_calc-tA);
				h_T_mcpA_normed_reconstruction_diffs->Fill((tA_calc-tA)/tA);
			}
		}
		
// B post missing:
		if (tA+tC+tD > a_mcp_lo) { // other 3 posts are present if they pass this test
			tB_calc = tA*tC/tD;
			if (printReconstructionMessage) printf("a_T_mcpB: Data value = %6f; Reconstructed value = %6f.\n", tB, tB_calc);
			if (tB < a_missing_mcp_post) { // this post is missing
				n_missing_T_mcpB_only++;
				tSum = tA + tB_calc + tC + tD;
				tX = (-tA - tB_calc + tC + tD) / tSum;
				tY = ( tA - tB_calc - tC + tD) / tSum;
//				tX_mm = scale * ((tX-x0)*TMath::Cos(theta) - (tY-y0)*TMath::Sin(theta));
//				tY_mm = scale * ((tX-x0)*TMath::Sin(theta) + (tY-y0)*TMath::Cos(theta));
				h_T_mcp_map_missingB_1->Fill(tX,tY);
				h_T_mcp_map_missingOne_1->Fill(tX,tY);
				h_T_mcp_map_reconstructed_1->Fill(tX,tY);// this is also filled under if (tSum > a_mcp_lo), above
			}
			else { // all 4 posts are present and we can compare measured versus "reconstructed" value
				h_T_mcpB_reconstruction_diffs->Fill(tB_calc-tB);
				h_T_mcpB_normed_reconstruction_diffs->Fill((tB_calc-tB)/tB);
			}
		}
		
// C post missing:
		if (tA+tB+tD > a_mcp_lo) { // other 3 posts are present if they pass this test
			tC_calc = tB*tD/tA;
			if (printReconstructionMessage) printf("a_T_mcpC: Data value = %6f; Reconstructed value = %6f.\n", tC, tC_calc);
			if (tC < a_missing_mcp_post) { // this post is missing
				n_missing_T_mcpC_only++;
				tSum = tA + tB + tC_calc + tD;
				tX = (-tA - tB + tC_calc + tD) / tSum;
				tY = ( tA - tB - tC_calc + tD) / tSum;
//				tX_mm = scale * ((tX-x0)*TMath::Cos(theta) - (tY-y0)*TMath::Sin(theta));
//				tY_mm = scale * ((tX-x0)*TMath::Sin(theta) + (tY-y0)*TMath::Cos(theta));
				h_T_mcp_map_missingC_1->Fill(tX,tY);
				h_T_mcp_map_missingOne_1->Fill(tX,tY);
				h_T_mcp_map_reconstructed_1->Fill(tX,tY);// this is also filled under if (tSum > a_mcp_lo), above
			}
			else { // all 4 posts are present and we can compare measured versus "reconstructed" value
				h_T_mcpC_reconstruction_diffs->Fill(tC_calc-tC);
				h_T_mcpC_normed_reconstruction_diffs->Fill((tC_calc-tC)/tC);
			}
		}
		
// D post missing:
		if (tA+tB+tC > a_mcp_lo) { // other 3 posts are present if they pass this test
			tD_calc = tA*tC/tB;
			if (printReconstructionMessage) printf("a_T_mcpD: Data value = %6f; Reconstructed value = %6f.\n", tD, tD_calc);
			if (tD < a_missing_mcp_post) { // this post is missing
				n_missing_T_mcpD_only++;
				tSum = tA + tB + tC + tD_calc;
				tX = (-tA - tB + tC + tD_calc) / tSum;
				tY = ( tA - tB - tC + tD_calc) / tSum;
//				tX_mm = scale * ((tX-x0)*TMath::Cos(theta) - (tY-y0)*TMath::Sin(theta));
//				tY_mm = scale * ((tX-x0)*TMath::Sin(theta) + (tY-y0)*TMath::Cos(theta));
				h_T_mcp_map_missingD_1->Fill(tX,tY);
				h_T_mcp_map_missingOne_1->Fill(tX,tY);
				h_T_mcp_map_reconstructed_1->Fill(tX,tY);// this is also filled under if (tSum > a_mcp_lo), above
			}
			else { // all 4 posts are present and we can compare measured versus "reconstructed" value
				h_T_mcpD_reconstruction_diffs->Fill(tD_calc-tD);
				h_T_mcpD_normed_reconstruction_diffs->Fill((tD_calc-tD)/tD);
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
	
	gDirectory->WriteTObject(h_T_mcp_map_0);
	gDirectory->WriteTObject(h_T_mcp_map_1);
	gDirectory->WriteTObject(h_T_mcp_map_2);
	gDirectory->WriteTObject(h_T_mcp_map_3);
	gDirectory->WriteTObject(h_T_mcp_map_4);
	
	gDirectory->WriteTObject(h_T_mcpA_0);
	gDirectory->WriteTObject(h_T_mcpA_1);
	gDirectory->WriteTObject(h_T_mcpA_2);
	gDirectory->WriteTObject(h_T_mcpA_3);
	gDirectory->WriteTObject(h_T_mcpA_4);
	
	gDirectory->WriteTObject(h_T_mcpB_0);
	gDirectory->WriteTObject(h_T_mcpB_1);
	gDirectory->WriteTObject(h_T_mcpB_2);
	gDirectory->WriteTObject(h_T_mcpB_3);
	gDirectory->WriteTObject(h_T_mcpB_4);
	
	gDirectory->WriteTObject(h_T_mcpC_0);
	gDirectory->WriteTObject(h_T_mcpC_1);
	gDirectory->WriteTObject(h_T_mcpC_2);
	gDirectory->WriteTObject(h_T_mcpC_3);
	gDirectory->WriteTObject(h_T_mcpC_4);
	
	gDirectory->WriteTObject(h_T_mcpD_0);
	gDirectory->WriteTObject(h_T_mcpD_1);
	gDirectory->WriteTObject(h_T_mcpD_2);
	gDirectory->WriteTObject(h_T_mcpD_3);
	gDirectory->WriteTObject(h_T_mcpD_4);
	
	gDirectory->WriteTObject(h_T_mcpSum_0);
	gDirectory->WriteTObject(h_T_mcpSum_1);
	gDirectory->WriteTObject(h_T_mcpSum_2);
	gDirectory->WriteTObject(h_T_mcpSum_3);
	gDirectory->WriteTObject(h_T_mcpSum_4);
	
	gDirectory->WriteTObject(h_T_mcpX_0);
	gDirectory->WriteTObject(h_T_mcpX_1);
	gDirectory->WriteTObject(h_T_mcpX_2);
	gDirectory->WriteTObject(h_T_mcpX_3);
	gDirectory->WriteTObject(h_T_mcpX_4);
	
	gDirectory->WriteTObject(h_T_mcpY_0);
	gDirectory->WriteTObject(h_T_mcpY_1);
	gDirectory->WriteTObject(h_T_mcpY_2);
	gDirectory->WriteTObject(h_T_mcpY_3);
	gDirectory->WriteTObject(h_T_mcpY_4);
	
	gDirectory->WriteTObject(h_T_mcpA_qA_0);
	gDirectory->WriteTObject(h_T_mcpA_qB_0);
	gDirectory->WriteTObject(h_T_mcpA_qC_0);
	gDirectory->WriteTObject(h_T_mcpA_qD_0);
	gDirectory->WriteTObject(h_T_mcpA_qCenter_0);
	
	gDirectory->WriteTObject(h_T_mcpB_qA_0);
	gDirectory->WriteTObject(h_T_mcpB_qB_0);
	gDirectory->WriteTObject(h_T_mcpB_qC_0);
	gDirectory->WriteTObject(h_T_mcpB_qD_0);
	gDirectory->WriteTObject(h_T_mcpB_qCenter_0);
	
	gDirectory->WriteTObject(h_T_mcpC_qA_0);
	gDirectory->WriteTObject(h_T_mcpC_qB_0);
	gDirectory->WriteTObject(h_T_mcpC_qC_0);
	gDirectory->WriteTObject(h_T_mcpC_qD_0);
	gDirectory->WriteTObject(h_T_mcpC_qCenter_0);
	
	gDirectory->WriteTObject(h_T_mcpD_qA_0);
	gDirectory->WriteTObject(h_T_mcpD_qB_0);
	gDirectory->WriteTObject(h_T_mcpD_qC_0);
	gDirectory->WriteTObject(h_T_mcpD_qD_0);
	gDirectory->WriteTObject(h_T_mcpD_qCenter_0);
	
	gDirectory->WriteTObject(h_T_mcpSum_qA_0);
	gDirectory->WriteTObject(h_T_mcpSum_qB_0);
	gDirectory->WriteTObject(h_T_mcpSum_qC_0);
	gDirectory->WriteTObject(h_T_mcpSum_qD_0);
	gDirectory->WriteTObject(h_T_mcpSum_qCenter_0);
	
	gDirectory->WriteTObject(h_T_mcpX_qA_0);
	gDirectory->WriteTObject(h_T_mcpX_qB_0);
	gDirectory->WriteTObject(h_T_mcpX_qC_0);
	gDirectory->WriteTObject(h_T_mcpX_qD_0);
	gDirectory->WriteTObject(h_T_mcpX_qCenter_0);
	
	gDirectory->WriteTObject(h_T_mcpY_qA_0);
	gDirectory->WriteTObject(h_T_mcpY_qB_0);
	gDirectory->WriteTObject(h_T_mcpY_qC_0);
	gDirectory->WriteTObject(h_T_mcpY_qD_0);
	gDirectory->WriteTObject(h_T_mcpY_qCenter_0);
	
	gDirectory->WriteTObject(h_T_mcpA_qA_2);
	gDirectory->WriteTObject(h_T_mcpA_qB_2);
	gDirectory->WriteTObject(h_T_mcpA_qC_2);
	gDirectory->WriteTObject(h_T_mcpA_qD_2);
	gDirectory->WriteTObject(h_T_mcpA_qCenter_2);
	
	gDirectory->WriteTObject(h_T_mcpB_qA_2);
	gDirectory->WriteTObject(h_T_mcpB_qB_2);
	gDirectory->WriteTObject(h_T_mcpB_qC_2);
	gDirectory->WriteTObject(h_T_mcpB_qD_2);
	gDirectory->WriteTObject(h_T_mcpB_qCenter_2);
	
	gDirectory->WriteTObject(h_T_mcpC_qA_2);
	gDirectory->WriteTObject(h_T_mcpC_qB_2);
	gDirectory->WriteTObject(h_T_mcpC_qC_2);
	gDirectory->WriteTObject(h_T_mcpC_qD_2);
	gDirectory->WriteTObject(h_T_mcpC_qCenter_2);
	
	gDirectory->WriteTObject(h_T_mcpD_qA_2);
	gDirectory->WriteTObject(h_T_mcpD_qB_2);
	gDirectory->WriteTObject(h_T_mcpD_qC_2);
	gDirectory->WriteTObject(h_T_mcpD_qD_2);
	gDirectory->WriteTObject(h_T_mcpD_qCenter_2);
	
	gDirectory->WriteTObject(h_T_mcpSum_qA_2);
	gDirectory->WriteTObject(h_T_mcpSum_qB_2);
	gDirectory->WriteTObject(h_T_mcpSum_qC_2);
	gDirectory->WriteTObject(h_T_mcpSum_qD_2);
	gDirectory->WriteTObject(h_T_mcpSum_qCenter_2);
	
	gDirectory->WriteTObject(h_T_mcpX_qA_2);
	gDirectory->WriteTObject(h_T_mcpX_qB_2);
	gDirectory->WriteTObject(h_T_mcpX_qC_2);
	gDirectory->WriteTObject(h_T_mcpX_qD_2);
	gDirectory->WriteTObject(h_T_mcpX_qCenter_2);
	
	gDirectory->WriteTObject(h_T_mcpY_qA_2);
	gDirectory->WriteTObject(h_T_mcpY_qB_2);
	gDirectory->WriteTObject(h_T_mcpY_qC_2);
	gDirectory->WriteTObject(h_T_mcpY_qD_2);
	gDirectory->WriteTObject(h_T_mcpY_qCenter_2);
	
	gDirectory->WriteTObject(h_R_mcp_map_0);
	gDirectory->WriteTObject(h_R_mcp_map_1);
	gDirectory->WriteTObject(h_R_mcp_map_2);
	gDirectory->WriteTObject(h_R_mcp_map_physical_2);
	gDirectory->WriteTObject(h_R_mcp_map_3);
	gDirectory->WriteTObject(h_R_mcp_map_4);
	
	gDirectory->WriteTObject(h_R_mcpA_0);
	gDirectory->WriteTObject(h_R_mcpA_1);
	gDirectory->WriteTObject(h_R_mcpA_2);
	gDirectory->WriteTObject(h_R_mcpA_3);
	gDirectory->WriteTObject(h_R_mcpA_4);
	
	gDirectory->WriteTObject(h_R_mcpB_0);
	gDirectory->WriteTObject(h_R_mcpB_1);
	gDirectory->WriteTObject(h_R_mcpB_2);
	gDirectory->WriteTObject(h_R_mcpB_3);
	gDirectory->WriteTObject(h_R_mcpB_4);
	
	gDirectory->WriteTObject(h_R_mcpC_0);
	gDirectory->WriteTObject(h_R_mcpC_1);
	gDirectory->WriteTObject(h_R_mcpC_2);
	gDirectory->WriteTObject(h_R_mcpC_3);
	gDirectory->WriteTObject(h_R_mcpC_4);
	
	gDirectory->WriteTObject(h_R_mcpD_0);
	gDirectory->WriteTObject(h_R_mcpD_1);
	gDirectory->WriteTObject(h_R_mcpD_2);
	gDirectory->WriteTObject(h_R_mcpD_3);
	gDirectory->WriteTObject(h_R_mcpD_4);
	
	gDirectory->WriteTObject(h_R_mcpSum_0);
	gDirectory->WriteTObject(h_R_mcpSum_1);
	gDirectory->WriteTObject(h_R_mcpSum_2);
	gDirectory->WriteTObject(h_R_mcpSum_3);
	gDirectory->WriteTObject(h_R_mcpSum_4);
	
	gDirectory->WriteTObject(h_R_mcpX_0);
	gDirectory->WriteTObject(h_R_mcpX_1);
	gDirectory->WriteTObject(h_R_mcpX_2);
	gDirectory->WriteTObject(h_R_mcpX_3);
	gDirectory->WriteTObject(h_R_mcpX_4);
	
	gDirectory->WriteTObject(h_R_mcpY_0);
	gDirectory->WriteTObject(h_R_mcpY_1);
	gDirectory->WriteTObject(h_R_mcpY_2);
	gDirectory->WriteTObject(h_R_mcpY_3);
	gDirectory->WriteTObject(h_R_mcpY_4);
	
	gDirectory->WriteTObject(h_R_mcpA_qA_0);
	gDirectory->WriteTObject(h_R_mcpA_qB_0);
	gDirectory->WriteTObject(h_R_mcpA_qC_0);
	gDirectory->WriteTObject(h_R_mcpA_qD_0);
	gDirectory->WriteTObject(h_R_mcpA_qCenter_0);
	
	gDirectory->WriteTObject(h_R_mcpB_qA_0);
	gDirectory->WriteTObject(h_R_mcpB_qB_0);
	gDirectory->WriteTObject(h_R_mcpB_qC_0);
	gDirectory->WriteTObject(h_R_mcpB_qD_0);
	gDirectory->WriteTObject(h_R_mcpB_qCenter_0);
	
	gDirectory->WriteTObject(h_R_mcpC_qA_0);
	gDirectory->WriteTObject(h_R_mcpC_qB_0);
	gDirectory->WriteTObject(h_R_mcpC_qC_0);
	gDirectory->WriteTObject(h_R_mcpC_qD_0);
	gDirectory->WriteTObject(h_R_mcpC_qCenter_0);
	
	gDirectory->WriteTObject(h_R_mcpD_qA_0);
	gDirectory->WriteTObject(h_R_mcpD_qB_0);
	gDirectory->WriteTObject(h_R_mcpD_qC_0);
	gDirectory->WriteTObject(h_R_mcpD_qD_0);
	gDirectory->WriteTObject(h_R_mcpD_qCenter_0);
	
	gDirectory->WriteTObject(h_R_mcpSum_qA_0);
	gDirectory->WriteTObject(h_R_mcpSum_qB_0);
	gDirectory->WriteTObject(h_R_mcpSum_qC_0);
	gDirectory->WriteTObject(h_R_mcpSum_qD_0);
	gDirectory->WriteTObject(h_R_mcpSum_qCenter_0);
	
	gDirectory->WriteTObject(h_R_mcpX_qA_0);
	gDirectory->WriteTObject(h_R_mcpX_qB_0);
	gDirectory->WriteTObject(h_R_mcpX_qC_0);
	gDirectory->WriteTObject(h_R_mcpX_qD_0);
	gDirectory->WriteTObject(h_R_mcpX_qCenter_0);
	
	gDirectory->WriteTObject(h_R_mcpY_qA_0);
	gDirectory->WriteTObject(h_R_mcpY_qB_0);
	gDirectory->WriteTObject(h_R_mcpY_qC_0);
	gDirectory->WriteTObject(h_R_mcpY_qD_0);
	gDirectory->WriteTObject(h_R_mcpY_qCenter_0);
	
	gDirectory->WriteTObject(h_R_mcpA_qA_2);
	gDirectory->WriteTObject(h_R_mcpA_qB_2);
	gDirectory->WriteTObject(h_R_mcpA_qC_2);
	gDirectory->WriteTObject(h_R_mcpA_qD_2);
	gDirectory->WriteTObject(h_R_mcpA_qCenter_2);
	
	gDirectory->WriteTObject(h_R_mcpB_qA_2);
	gDirectory->WriteTObject(h_R_mcpB_qB_2);
	gDirectory->WriteTObject(h_R_mcpB_qC_2);
	gDirectory->WriteTObject(h_R_mcpB_qD_2);
	gDirectory->WriteTObject(h_R_mcpB_qCenter_2);
	
	gDirectory->WriteTObject(h_R_mcpC_qA_2);
	gDirectory->WriteTObject(h_R_mcpC_qB_2);
	gDirectory->WriteTObject(h_R_mcpC_qC_2);
	gDirectory->WriteTObject(h_R_mcpC_qD_2);
	gDirectory->WriteTObject(h_R_mcpC_qCenter_2);
	
	gDirectory->WriteTObject(h_R_mcpD_qA_2);
	gDirectory->WriteTObject(h_R_mcpD_qB_2);
	gDirectory->WriteTObject(h_R_mcpD_qC_2);
	gDirectory->WriteTObject(h_R_mcpD_qD_2);
	gDirectory->WriteTObject(h_R_mcpD_qCenter_2);
	
	gDirectory->WriteTObject(h_R_mcpSum_qA_2);
	gDirectory->WriteTObject(h_R_mcpSum_qB_2);
	gDirectory->WriteTObject(h_R_mcpSum_qC_2);
	gDirectory->WriteTObject(h_R_mcpSum_qD_2);
	gDirectory->WriteTObject(h_R_mcpSum_qCenter_2);
	
	gDirectory->WriteTObject(h_R_mcpX_qA_2);
	gDirectory->WriteTObject(h_R_mcpX_qB_2);
	gDirectory->WriteTObject(h_R_mcpX_qC_2);
	gDirectory->WriteTObject(h_R_mcpX_qD_2);
	gDirectory->WriteTObject(h_R_mcpX_qCenter_2);
	
	gDirectory->WriteTObject(h_R_mcpY_qA_2);
	gDirectory->WriteTObject(h_R_mcpY_qB_2);
	gDirectory->WriteTObject(h_R_mcpY_qC_2);
	gDirectory->WriteTObject(h_R_mcpY_qD_2);
	gDirectory->WriteTObject(h_R_mcpY_qCenter_2);
	
	gDirectory->WriteTObject(h_missing_R_mcp);
	gDirectory->WriteTObject(h_missing_T_mcp);
	gDirectory->WriteTObject(hn_missing_R_posts);
	gDirectory->WriteTObject(hn_missing_T_posts);
	
	gDirectory->WriteTObject(h_R_mcp_map_missingA_1);
	gDirectory->WriteTObject(h_R_mcp_map_missingB_1);
	gDirectory->WriteTObject(h_R_mcp_map_missingC_1);
	gDirectory->WriteTObject(h_R_mcp_map_missingD_1);
	gDirectory->WriteTObject(h_R_mcp_map_reconstructed_1);
	gDirectory->WriteTObject(h_R_mcp_map_missingOne_1);
	
	gDirectory->WriteTObject(h_T_mcp_map_missingA_1);
	gDirectory->WriteTObject(h_T_mcp_map_missingB_1);
	gDirectory->WriteTObject(h_T_mcp_map_missingC_1);
	gDirectory->WriteTObject(h_T_mcp_map_missingD_1);
	gDirectory->WriteTObject(h_T_mcp_map_reconstructed_1);
	gDirectory->WriteTObject(h_T_mcp_map_missingOne_1);
	
	gDirectory->WriteTObject(h_R_mcpA_reconstruction_diffs);
	gDirectory->WriteTObject(h_R_mcpB_reconstruction_diffs);
	gDirectory->WriteTObject(h_R_mcpC_reconstruction_diffs);
	gDirectory->WriteTObject(h_R_mcpD_reconstruction_diffs);
	gDirectory->WriteTObject(h_T_mcpA_reconstruction_diffs);
	gDirectory->WriteTObject(h_T_mcpB_reconstruction_diffs);
	gDirectory->WriteTObject(h_T_mcpC_reconstruction_diffs);
	gDirectory->WriteTObject(h_T_mcpD_reconstruction_diffs);
	
	gDirectory->WriteTObject(h_R_mcpA_normed_reconstruction_diffs);
	gDirectory->WriteTObject(h_R_mcpB_normed_reconstruction_diffs);
	gDirectory->WriteTObject(h_R_mcpC_normed_reconstruction_diffs);
	gDirectory->WriteTObject(h_R_mcpD_normed_reconstruction_diffs);
	gDirectory->WriteTObject(h_T_mcpA_normed_reconstruction_diffs);
	gDirectory->WriteTObject(h_T_mcpB_normed_reconstruction_diffs);
	gDirectory->WriteTObject(h_T_mcpC_normed_reconstruction_diffs);
	gDirectory->WriteTObject(h_T_mcpD_normed_reconstruction_diffs);
	
	gDirectory->WriteTObject(h_R_mcpA_FidArea_0);
	gDirectory->WriteTObject(h_R_mcpB_FidArea_0);
	gDirectory->WriteTObject(h_R_mcpC_FidArea_0);
	gDirectory->WriteTObject(h_R_mcpD_FidArea_0);
	gDirectory->WriteTObject(h_R_mcpSum_FidArea_0);
	gDirectory->WriteTObject(h_R_mcpA_FidArea_2);
	gDirectory->WriteTObject(h_R_mcpB_FidArea_2);
	gDirectory->WriteTObject(h_R_mcpC_FidArea_2);
	gDirectory->WriteTObject(h_R_mcpD_FidArea_2);
	gDirectory->WriteTObject(h_R_mcpSum_FidArea_2);
	
	gDirectory->WriteTObject(h_T_mcpA_FidArea_0);
	gDirectory->WriteTObject(h_T_mcpB_FidArea_0);
	gDirectory->WriteTObject(h_T_mcpC_FidArea_0);
	gDirectory->WriteTObject(h_T_mcpD_FidArea_0);
	gDirectory->WriteTObject(h_T_mcpSum_FidArea_0);
	gDirectory->WriteTObject(h_T_mcpA_FidArea_2);
	gDirectory->WriteTObject(h_T_mcpB_FidArea_2);
	gDirectory->WriteTObject(h_T_mcpC_FidArea_2);
	gDirectory->WriteTObject(h_T_mcpD_FidArea_2);
	gDirectory->WriteTObject(h_T_mcpSum_FidArea_2);
	
	gDirectory->WriteTObject(h_mcpA_cut);
	gDirectory->WriteTObject(h_mcpB_cut);
	gDirectory->WriteTObject(h_mcpC_cut);
	gDirectory->WriteTObject(h_mcpD_cut);
	gDirectory->WriteTObject(h_mcpSum_cut);
	
	gDirectory->WriteTObject(h_R_mcp_map_0_post);
	gDirectory->WriteTObject(h_R_mcp_map_2_post);
	gDirectory->WriteTObject(h_T_mcp_map_0_post);
	gDirectory->WriteTObject(h_T_mcp_map_2_post);
	
	f->Close();
	
	printf("\nmcp_cal done.\n\n");
	
}
