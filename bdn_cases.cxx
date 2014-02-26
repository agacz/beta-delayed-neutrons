#include "include/bdn_cases.h"
#include <cstring>

bdn_case_t bdn_cases[] = {
	{
	"137i07",	// code
	"~",		// file
	"137-Te",	// species 1
	"137-I",	// species 2
	"137-Xe",	// species 3
	6000.0,		// T_capt
	1000.0,		// T_last
	101000.0,	// T_bkgd
	246000.0,	// T_cycle
	{24.9, 0.05},	// Species 1 half-life {val, unc}
	{24.5, 0.2},	// Species 2 half-life {val, unc}
	{3.818, 0.013},	// Species 3 half-life {val, unc}
	{24.9/ln2, 0.05/ln2},
	{24.5/ln2, 0.2/ln2},
	{3.818/ln2, 0.013/ln2}
	},
	{ 0, 0, 0, 0, 0, } // null struct at the end
};

/*
void assign_bdn_cases () {
	
	using namespace bdn_casecodes;
	
	Int_t i;
	
//////////////////////////////////////////////////////////////////////////////	
	i = cc137i07;
	
	bdn_cases[i].code		= "137i07";
	bdn_cases[i].file		= "~/137i/rootfiles/137i07.root";
	bdn_cases[i].species1	= "137-Te";
	bdn_cases[i].species2	= "137-I";
	bdn_cases[i].species3	= "137-Xe";
	// Timing constants describing the experiment, in ms
	bdn_cases[i].T_capt		= 6000.0; // APT cycle time
	bdn_cases[i].T_last		= 1000.0; // time between BPT last capt and BPT ejection
	bdn_cases[i].T_bkgd		= 101000.0;// + Ta - Tf; // duration of background measurement
	bdn_cases[i].T_cycle		= 246000.0; // BPT cycle time (background + trapping)
	// Physical constants
	const Double_t ln2= 0.69314718056;
//	bdn_cases[i].halflife1 = {        1000.0 * 2.49,         1000.0 * 0.05		};
//	bdn_cases[i].halflife2 = {        1000.0 * 24.5,         1000.0 * 0.2		};
//	bdn_cases[i].halflife3 = { 60.0 * 1000.0 * 3.818, 60.0 * 1000.0 * 0.013		};
//	bdn_cases[i].lifetime1 = { bdn_cases[i].halflife1[0]/ln2, bdn_cases[i].halflife1[1]/ln2};
//	bdn_cases[i].lifetime2 = { bdn_cases[i].halflife2[0]/ln2, bdn_cases[i].halflife2[1]/ln2};
//	bdn_cases[i].lifetime3 = { bdn_cases[i].halflife3[0]/ln2, bdn_cases[i].halflife3[1]/ln2};
	
	bdn_cases[i].halflife1[0] = 1000.0 * 2.49; // value
	bdn_cases[i].halflife1[1] = 1000.0 * 0.05; // uncertainty
	bdn_cases[i].halflife2[0] = 1000.0 * 24.5; // value
	bdn_cases[i].halflife2[1] = 1000.0 * 0.2; // uncertainty
	bdn_cases[i].halflife3[0] = 60.0 * 1000.0 * 3.818; // value
	bdn_cases[i].halflife3[1] = 60.0 * 1000.0 * 0.013; // uncertainty
	bdn_cases[i].lifetime1[0] = bdn_cases[i].halflife1[0]/ln2; // value
	bdn_cases[i].lifetime1[1] = bdn_cases[i].halflife1[1]/ln2; // uncertainty
	bdn_cases[i].lifetime2[0] = bdn_cases[i].halflife2[0]/ln2; // value
	bdn_cases[i].lifetime2[1] = bdn_cases[i].halflife2[1]/ln2; // uncertainty
	bdn_cases[i].lifetime3[0] = bdn_cases[i].halflife3[0]/ln2; // value
	bdn_cases[i].lifetime3[1] = bdn_cases[i].halflife3[1]/ln2; // uncertainty
	
	printf("Case 137i07 values assigned.\n");
//	return bdn_cases[i];
}
*/
