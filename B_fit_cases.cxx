// Always enclose header file contents with these ifndef/endif directives.
#ifndef _B_fit_model_h
#define _B_fit_model_h

#include "TString.h"
#include "Rtypes.h"

struct B_fit_case_t {
    	TString histname;
    	Int_t bin_width; // ms
	// Parameter switches; 1 = parameter varies; 0 = parameter is fixed to seed value
	    Bool_t toggle[nPars];
	// Initial parameter values for fitting
	    Double_t seed[nPars];
	// Initial parameter step sizes
		Double_t step[nPars];
		TString options;
		Bool_t do_fit; // 0 results in plotting from seed values
	};
	
B_fit_case_t B_fit_cases[] = {
	{
		/* code */		"137i07",
		/* file */		"B_monte_carlo_feeding_lifetime_1.root",
		/* species1 */	"137-Te",
		/* species2 */	"137-I",
		/* species3 */	"137-Xe",
		/* T_capt */	6000.0,
		/* T_last */	1000.0,
		/* T_bkgd */	101000.0,
		/* T_cycle */	246000.0,
		/* halflife1 */	{ 1000.0 * 2.49, 1000.0 * 0.05},
		/* halflife2 */	{ 1000.0 * 24.5, 1000.0 * 0.20},
		/* halflife3 */	{ 60.0 * 1000.0 * 3.818, 60.0 * 1000.0 * 0.013}
		
		/* histname */		"h_D_cyctime",
		/* bin_width */		500, // ms
	// Parameter switches: kTrue = parameter varies; kFalse = parameter is fixed to _seed value
		/* toggle[DC] */	0,
		/* toggle[r1] */	0,
		/* toggle[r2] */	0,
		/* toggle[r3] */	0,
		/* toggle[p] */		1,
		/* toggle[l] */		0,
		/* toggle[epsT] */	0,
		/* toggle[epsU] */	0,
		/* toggle[epsV] */	0,
		/* toggle[epsW] */	0,
		/* toggle[epsX] */	0,
		/* toggle[epsY] */	1,
		/* toggle[tau1] */	0,
		/* toggle[tau2] */	0,
		/* toggle[tau3] */	0,
		/* toggle[tauT1] */	0,
		/* toggle[tauT2] */	0,
		/* toggle[tauT3] */	0,
		/* toggle[tauU1] */	0,
		/* toggle[tauU2] */	0,
		/* toggle[tauU3] */	0,
		/* toggle[dt] */	0,
	// Initial parameter values
		/* seed[DC] */			10000.0 * 0.040,
		/* seed[r1] */			10000.0 * 0.024,
		/* seed[r2] */			10000.0 * 0.120,
		/* seed[r3] */			0*100.0 * 0.080,
		/* seed[p] */			0.75,
		/* seed[l] */			1.0,
		/* seed[epsT] */		1.0,
		/* seed[epsU] */		1.0,
		/* seed[epsV] */		1.0,
		/* seed[epsW] */		1.0,
		/* seed[epsX] */		1.0,
		/* seed[epsY] */		1.5,
		/* seed[tau1] */		1000.0 * 2.49 / ln2,
		/* seed[tau2] */		1000.0 * 24.5 / ln2,
		/* seed[tau3] */		60.0 * 1000.0 * 3.818 / ln2,
		/* seed[tauT1] */		1000.0 * 2.49 / ln2,//1.0 / ( 1.0/bdn_case.lifetime1[0] + 1.0/15000.0 ),//bdn_case.lifetime1[0],
		/* seed[tauT2] */		1000.0 * 24.5 / ln2,//1.0 / ( 1.0/bdn_case.lifetime2[0] + 1.0/15000.0 ),//bdn_case.lifetime2[0],
		/* seed[tauT3] */		60.0 * 1000.0 * 3.818 / ln2,//1.0 / ( 1.0/bdn_case.lifetime3[0] + 1.0/15000.0 ),//bdn_case.lifetime3[0],
		/* seed[tauU1] */		1000.0 * 2.49 / ln2,//1.0 / ( 1.0/bdn_case.lifetime1[0] + 1.0/15000.0 ),//bdn_case.lifetime1[0],
		/* seed[tauU2] */		1000.0 * 24.5 / ln2,//1.0 / ( 1.0/bdn_case.lifetime2[0] + 1.0/15000.0 ),//bdn_case.lifetime2[0],
		/* seed[tauU3] */		60.0 * 1000.0 * 3.818 / ln2,//1.0 / ( 1.0/bdn_case.lifetime3[0] + 1.0/15000.0 ),//bdn_case.lifetime3[0],
		/* seed[dt] */			500,
	// Initial parameter step sizes
		/* step[DC] */			0.1,
		/* step[r1] */			0.1,
		/* step[r2] */			0.1,
		/* step[r3] */			0.1,
		/* step[p] */			0.02,
		/* step[l] */			0.02,
		/* step[epsT] */		0.02,
		/* step[epsU] */		0.02,
		/* step[epsV] */		0.02,
		/* step[epsW] */		0.02,
		/* step[epsX] */		0.02,
		/* step[epsY] */		0.02,
		/* step[tau1] */		1000.0 * 0.05 / ln2,
		/* step[tau2] */		1000.0 * 0.20 / ln2,
		/* step[tau3] */		60.0 * 1000.0 * 0.013 / ln2,
		/* step[tauT1] */		100.0,
		/* step[tauT2] */		100.0,
		/* step[tauT3] */		100.0,
		/* step[tauU1] */		100.0,
		/* step[tauU2] */		100.0,
		/* step[tauU3] */		100.0,
		/* step[dt] */			0.0000000001,
	// Options
		/* options */			"QIR0MESLL",
		/* do_fit */			0,
		/* monte_carlo */		1,
		/* has_DDC */			1,
		/* has_VWXY */			1,
		},
	{ 0, 0, 0, 0, 0, } // null struct at the end, to terminate the array
};

#endif
