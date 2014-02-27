// Always enclose header file contents with these ifndef/endif directives.
#ifndef _bdn_cases_h
#define _bdn_cases_h

#include "TString.h"
#include "Rtypes.h"
#include <cmath>
//#ifndef _bdn_cases_cxx
//#define EXTERNAL extern
//#else
//#define EXTERNAL
//#endif

const Double_t ln2 = log(2.0);

namespace bdn_casecodes {
    enum casecodes_e { cc137i07, cc138i07, unknown };
}

struct bdn_case_t {
	
//	Int_t teeth;
	
	// Descriptors
	const char* code;
	const char* file;
	const char* species1;
	const char* species2;
	const char* species3;
	
    // Timing constants describing the experiment, in ms
	double T_capt;	// Time between captures
	double T_last;	// Time between last capture and ejection
	double T_bkgd;	// Duration of background measurement
	double T_cycle;	// BPT cycle time (background + trapping)
	
    // Half-lives; array holding {value, sigma}
//    Double_t halflife1[2];
 //   Double_t halflife2[2];
    //Double_t halflife3[2];
    //Double_t lifetime1[2];
    //Double_t lifetime2[2];
    //Double_t lifetime3[2];
	double halflife1[2];
    double halflife2[2];
    double halflife3[2];
    double lifetime1[2];
    double lifetime2[2];
    double lifetime3[2];
    
    // veto info
    // masses
    // nuclear physics?
    
};

extern bdn_case_t bdn_cases[];
//void assign_bdn_cases();

#endif
