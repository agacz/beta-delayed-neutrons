/*
2013-12-07 Shane Caldwell
	Made from fit_beta_singles.cxx.
	Will modify as necessary to validate against B_monte_carlo output.
2014-02-26
	Making a standalone C++ version of B_fit.cpp, which is a ROOT program.
	Big difference: this program does not output plots to screen. Instead it saves them to a
	subdirectory of the ROOT file that is given to it.
*/

#include <unistd.h>
#include "stdio.h"
#include <iostream>
#include <cstring>
#include "TROOT.h"
#include "TString.h"
#include "TStyle.h"
#include "TMath.h"
#include "TFitResult.h"
#include "TMatrixDSym.h"
#include "TFile.h"
#include "TF1.h"
#include "TH1.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TPaveStats.h"
#include "Fit/FitConfig.h"
#include "TCanvas.h"
//#include "include/bdn.h"
//#include "include/sb135.h"
#include "bdn_cases.h"
#include "B_fit_model.h"

// Global variables
Int_t			gdx; // global index to identify case
bdn_case_t		bdn_case;
//B_fit_model::B_fit_case_t	fit_case;

Double_t		tau1[2], tau2[2], tau3[2];

void B_fit (const char*, const Int_t);

int main (int argc, char *argv[]) {
	using namespace std;
	cout << endl;
	
	bdn_case_t *m;
	for (m = bdn_cases, gdx = 0; m->code != 0 && strcmp(m->code, argv[1]) != 0; ++m, ++gdx);
	if (m->code == 0) {
		cout << "No match found for casecode entered. Execute the program like this:" << endl;
		cout << "'$ ./PROGRAM 137i07' for 137-I run 7" << endl << endl;
		return 0;
	}
	B_fit(m->code, gdx);
	return 0;
}

void B_fit (const char* case_code, const Int_t case_int) {
	
	printf("B_fit started on case %s\n",case_code);
	
//	using namespace B_model;
	using namespace std;
	using namespace TMath;
	
	bdn_case_t bdn_case = bdn_cases[case_int];
	tau1 = { bdn_case.halflife1[0]/ln2, bdn_case.halflife1[1]/ln2};
	tau2 = { bdn_case.halflife2[0]/ln2, bdn_case.halflife2[1]/ln2};
	tau3 = { bdn_case.halflife3[0]/ln2, bdn_case.halflife3[1]/ln2};
	
	B_fit_case_t fit_case = B_fit_cases[case_int];
	
	TString separator = "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
	std::cout << endl << separator << endl;
	std::cout << "BETA SINGLES MODEL" << endl << separator << endl;
	std::cout << "Case: " << bdn_case.code << endl;
	std::cout << "File: " << bdn_case.file << endl;
//	std::cout << "Histogram: " << fit_case.histname << endl;
	printf("Total cycle time\t= %9.3f s\n",bdn_case.T_cycle/1000.0);
	printf("Background time\t\t= %9.3f s\n",bdn_case.T_bkgd/1000.0);
	printf("Capture cycle time\t= %9.3f s\n",bdn_case.T_capt/1000.0);
	std::cout << bdn_case.species1; printf(" halflife\t\t= %9.3f s  (lifetime %9.3f s)\n",bdn_case.halflife1[0]/1000.0,bdn_case.lifetime1[0]/1000.0);
	std::cout << bdn_case.species2; printf(" halflife\t\t= %9.3f s  (lifetime %9.3f s)\n",bdn_case.halflife2[0]/1000.0,bdn_case.lifetime2[0]/1000.0);
	std::cout << bdn_case.species3; printf(" halflife\t\t= %9.3f s  (lifetime %9.3f s)\n",bdn_case.halflife3[0]/1000.0,bdn_case.lifetime3[0]/1000.0);
	std::cout << separator << endl;
//	if (fit_case.do_fit) std::cout << "Doing fit with option string: " << fit_case.options << endl;
//	else std::cout << "Not fitting! Drawing functions using parameter seed values." << endl;
	std::cout << separator << endl;
	
	// Get histogram
	TFile *f = new TFile(bdn_case.file);
//	TH1D *h	= (TH1D*)f->Get(fit_case.histname);
//	Double_t rebin_factor = fit_case.bin_width/(h->GetBinWidth(1));
//	TH1D *h1	= (TH1D*)h->Rebin(rebin_factor,fit_case.histname);
//	TH1D *h2	= (TH1D*)h->Rebin(rebin_factor,fit_case.histname);
	
	
//	file->WriteTObject(h_T_oops_vs_cycle_time);
//	file->Close();
	
	
	
	printf("B_fit done with case %s\n",case_code);
	
}
