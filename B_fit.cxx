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
#include "include/bdn.h"
#include "include/sb135.h"
#include "include/bdn_cases.h"
#include "B_model.h"

Int_t gdx; // global index to identify case

void B_fit (const char*, const Int_t);

int main (int argc, char *argv[]) {
	using namespace std;
	cout << endl;
	
	bdn_case_t *m;
	for (m = bdn_cases, gdx = 0; m->code != 0 && strcmp(m->code, argv[1]) != 0; ++m, ++gdx);
	if (m->code == 0) {
		cout << "No match found for casecode entered. Execute the program like this:" << endl;
		cout << "'$ ./B_fit 137i07' for 137-I run 7" << endl << endl;
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
	
//	assign_bdn_cases();
	bdn_case_t fit_case = bdn_cases[case_int];
//	bdn_case_t fit_case = assign_bdn_cases();
	
	printf("\n");
	printf("Hello. Here is your case data:\n");
	printf("Case code from command line: %s\n",case_code);
	printf("Integer index of this code: %d\n",case_int);
	printf("T_capt = %8.3f s\n",bdn_cases[case_int].T_capt);
	printf("Species 2 lifetime = %8.3f s  (half-life %8.3f s)\n",fit_case.lifetime2[0],fit_case.halflife2[0]);
	printf("\n");
	
//	file->WriteTObject(h_T_oops_vs_cycle_time);
//	file->Close();
	
	
	
	printf("B_fit done with case %s\n",case_code);
	
}
