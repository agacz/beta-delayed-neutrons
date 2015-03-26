/*
2013-12-06 Shane Caldwell
	Simulating beta singles data
2013-12-20
	Trapped and untrapped pops, untrapped comes only from capture pulse
2014-01-09 Created B_monte_carlo_nefeeding_1.cxx
	Noticed run starts with an empty background cycle, which has implications for the fitting.
	To correct this, just run an extra background cycle at the end. (T_run += T_bkgd;)
	Also need to forbid decays until t = T_bkgd to prevent DC decays from being artificially 
	inflated in the background region by the extra background cycle.
	So put 'if (t >= T_bkgd) {}' around the decay code.
	Version _2: Change ion injection to fixed values, back from using Poisson-random ones.
2014-01-14
	Version _3: Was not counting nDDC in nEntries for h_D_cyctime. Add this, and also put correct nEntries in other cyctime histos.
	_highstats: 1000 cylces instead of 10, and don't write realtime histos
2014-01-15
	Changed (same version) to include h_DDC_cyctime for checking.
	New _efftrap100_1_highstats. Using p = 1.00 and new set of rates values
2014-01-16
	Was only 25% done after running overnight
	Changed (same version) to use the normal approximation to the binomial dist when appropriate to help it run faster
	Also reduced the rates values to keep pops at lower levels
	Removed normal approx -- was never being used anyway
2014-01-23
	B_monte_carlo_feeding: Putting in feeding (using 100 cycles)
2014-01-27
	B_monte_carlo_feeding: Work continues.
	Now defining four distinct pops of untrapped ions:
		V = untrapped isotopes that are lost during capture due to imperfect capture efficiency
		W = untrapped isotopes that were trapped but become untrapped because of the capture pulse
		X = untrapped isotopes that are daughters of trapped ions
		Y = untrapped isotopes that are daughters of untrapped ions
		U is now the sum of all untrapped pops. It used to be what is now V, and the other pops didn't exist.
		(V and W are "direct" contributions, X and Y are "feeding" contributions)
	Using correct individual decay probabilities pDi = 1-Exp(-T_step/ti) valid for larger T_step
2014-02-11
	_feeding_highstats version (1000 cycles, same rates)
	_feeding_veryhighstats version (1000 cycles, 10x the rates)
	IMPORTANT: Change the decay and feeding preocedure so that decays go into fed pops before fed pops decay.
		This change goes into B_monte_carlo_feeding_veryhighstats_1.root
	IMPORTANT: Ok so actually only (approximately) half the decays should go into fed pops before fed pops decay.
		This change goes into B_monte_carlo_feeding_veryhighstats_2.root
2014-02-20
	IMPORTANT: Moved the detection efficiencies out of the population decay terms, to new variables.
		Now decays_T1 = decays of pop T1, DT1 = detections of pop T1.
		Also: found problems with how I was splitting up the pops for feeding. Not sure how even the first feeding was getting the right answer....
		These changes go into B_monte_carlo_feeding_veryhighstats_3.root
2014-02-21
	_feeding_lifetime version. Uses veryhighstats and Saves to B_monte_carlo_feeding_lifetime_1.root
2014-02-22
	Added continuous trap losses. Checked that lifetimes are calculated correctly.
	These losses are concurrent with decays, just as decays are concurrent with feeding.
	Account for this in the same way as decays vs feeding: split the trap losses in half, and do the
	decays and feeding within the split.
	These losses are not feeding any daughter pop at this time.
2014-02-25
	Reducing stats (10 cycles instead of 1000) to run faster. Want to play with different parameters to find the problem with Y3 pop in my model.
2014-07-16
	Running with r1 = 0.0 to check feeding. ==> output "B_monte_carlo_feeding_lifetime_5.root"
2014-10-21
	Turning on all features to see the "right answers" to help me build the model --> "B_monte_carlo_feeding_lifetime_6.root"
2014-11-05
	New program name: BMonteCarlo.
	Adding Z populations.
2014-01-25
	Found big mistake: Z pops were never added to aggregate histos h_DUi_[] and h_D_[]. This affects all BMC runs through 0011.
*/

#include <iostream>
#include "TROOT.h"
#include "TStyle.h"
#include "TMath.h"
#include "TRandom3.h"
#include "TFitResult.h"
#include "TMatrixDSym.h"
#include "TFile.h"
#include "TF1.h"
#include "TH1.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TVector.h"
#include "TPaveStats.h"
#include "Fit/FitConfig.h"

//Double_t decay (TRandom3 *, Double_t, Double_t, Double_t);

void BMonteCarlo () {
	
	gROOT->Reset();
	
// Filename for simulation
	TRandom3 *randgen = new TRandom3(2);
	TFile *rootfile = new TFile("BMC_0033.root","RECREATE");
// Injection parameters
    const Double_t rDC		= 0.040; // in 1/ms
    const Double_t r1		= 0.080; // in 1/ms
    const Double_t r2		= 0.120; // in 1/ms
	const Double_t r3		= 0.100; // in 1/ms
	const Double_t p		= 0.67134;
	const Double_t rho		= 0.88552;
// Cycle parameters
	const Long64_t	T_cycle	= 246000;//000;
	const Long64_t	T_bkgd	= 101000;//000;
	const Long64_t	T_capt	= 6000;//00;
	const Int_t		T_step	= 5;
	const Int_t 	nCycles = 2000;
// Decay parameters
	const Double_t ln2		= 0.69314718056;
	const Double_t t1		= 2490.0/ln2;//3592.0;
    const Double_t t2		= 24500.0/ln2;//34812.0;
    const Double_t t3		= 3.818*60000.0/ln2;//330493.0;
	const Double_t gT1		= 1.0/15000.0; // non-radioactive decay rate (1/ms)
	const Double_t gT2		= 1.0/25000.0; // non-radioactive decay rate (1/ms)
	const Double_t gT3		= 1.0/35000.0; // non-radioactive decay rate (1/ms)
	const Double_t gU1		= 1.0/55000.0; // non-radioactive decay rate (1/ms)
	const Double_t gU2		= 1.0/65000.0; // non-radioactive decay rate (1/ms)
	const Double_t gU3		= 1.0/75000.0; // non-radioactive decay rate (1/ms)
// Detection efficiencies
	const Double_t eps_T	= 0.91;
	const Double_t eps_V	= 0.92;
	const Double_t eps_W	= 0.93;
	const Double_t eps_X	= 0.94;
	const Double_t eps_Y	= 0.95;
	const Double_t eps_Z	= 0.96;
	
// Calculations
	Int_t	T_run	= nCycles*T_cycle + T_bkgd;
	Int_t	nSteps	= T_run/T_step;
	Int_t	t, t_cyc, t_bin, cyc_bin;
// Probability of indivdual decay (D) or loss without decay (L) within T_step
	const Double_t pD1  = 1.0 - TMath::Exp(-T_step/t1); // beta decay probability of species 1, in time T_step
	const Double_t pD2  = 1.0 - TMath::Exp(-T_step/t2); // beta decay probability of species 2, in time T_step
	const Double_t pD3  = 1.0 - TMath::Exp(-T_step/t3); // beta decay probability of species 3, in time T_step
	const Double_t pLT1 = 1.0 - TMath::Exp(-T_step*gT1); // probability of non-beta-decay loss of trapped species 1, in time T_step
	const Double_t pLT2 = 1.0 - TMath::Exp(-T_step*gT2); // probability of non-beta-decay loss of trapped species 2, in time T_step
	const Double_t pLT3 = 1.0 - TMath::Exp(-T_step*gT3); // probability of non-beta-decay loss of trapped species 3, in time T_step
	const Double_t pLU1 = 1.0 - TMath::Exp(-T_step*gU1); // probability of non-beta-decay loss of untrapped species 1, in time T_step
	const Double_t pLU2 = 1.0 - TMath::Exp(-T_step*gU2); // probability of non-beta-decay loss of untrapped species 2, in time T_step
	const Double_t pLU3 = 1.0 - TMath::Exp(-T_step*gU3); // probability of non-beta-decay loss of untrapped species 3, in time T_step
	printf("Decay probabilities per time step:\n");
	printf(" pD1 = %7f,  pD2 = %7f,  pD3 = %7f\n",  pD1,  pD2,  pD3);
	printf("pLT1 = %7f, pLT2 = %7f, pLT3 = %7f\n", pLT1, pLT2, pLT3);
	printf("pLU1 = %7f, pLU2 = %7f, pLU3 = %7f\n", pLU1, pLU2, pLU3);
//	, pLT1     pLT2     pLT3     pLU1     pLU2     pLU3\n");
//	printf("%7f %7f %7f %7f %7f %7f %7f %7f %7f, pLT1, pLT2, pLT3, pLU1, pLU2, pLU3);
	
	// Histos on real time -- plot pops on this axis
	Int_t tBins	= (T_run+2000)/T_step;
	Int_t tMin	= -1000;
	Int_t tMax	= T_run+1000;
	// Populations
	TH1D *h_A_realtime 	 = new TH1D("h_A_realtime","All Pops vs real time in ms"		,tBins,tMin,tMax);
//	TH1D *h_T_realtime 	 = new TH1D("h_T_realtime","All Trapped Pops vs real time in ms"		,tBins,tMin,tMax);
	TH1D *h_T1_realtime  = new TH1D("h_T1_realtime","Species 1 Trapped Pop T vs real time in ms",tBins,tMin,tMax);
	TH1D *h_T2_realtime  = new TH1D("h_T2_realtime","Species 2 Trapped Pop T vs real time in ms",tBins,tMin,tMax);
	TH1D *h_T3_realtime  = new TH1D("h_T3_realtime","Species 3 Trapped Pop T vs real time in ms",tBins,tMin,tMax);
//	TH1D *h_U_realtime 	 = new TH1D("h_U_realtime","All Untrapped Pops, lost at capture, vs real time in ms"		,tBins,tMin,tMax);
	TH1D *h_U1_realtime  = new TH1D("h_U1_realtime","Species 1 All Untrapped Pops (U) vs real time in ms",tBins,tMin,tMax);
	TH1D *h_U2_realtime  = new TH1D("h_U2_realtime","Species 2 All Untrapped Pops (U) vs real time in ms",tBins,tMin,tMax);
	TH1D *h_U3_realtime  = new TH1D("h_U3_realtime","Species 3 All Untrapped Pops (U) vs real time in ms",tBins,tMin,tMax);
//	
	TH1D *h_V1_realtime  = new TH1D("h_V1_realtime","Species 1 Untrapped Pop V, from loss of injected bunch at capture, vs real time in ms",tBins,tMin,tMax);
	TH1D *h_V2_realtime  = new TH1D("h_V2_realtime","Species 2 Untrapped Pop V, from loss of injected bunch at capture, vs real time in ms",tBins,tMin,tMax);
	TH1D *h_V3_realtime  = new TH1D("h_V3_realtime","Species 3 Untrapped Pop V, from loss of injected bunch at capture, vs real time in ms",tBins,tMin,tMax);
	TH1D *h_W1_realtime  = new TH1D("h_W1_realtime","Species 1 Untrapped Pop W, from loss of already-trapped ions at capture, vs real time in ms",tBins,tMin,tMax);
	TH1D *h_W2_realtime  = new TH1D("h_W2_realtime","Species 2 Untrapped Pop W, from loss of already-trapped ions at capture, vs real time in ms",tBins,tMin,tMax);
	TH1D *h_W3_realtime  = new TH1D("h_W3_realtime","Species 3 Untrapped Pop W, from loss of already-trapped ions at capture, vs real time in ms",tBins,tMin,tMax);
	TH1D *h_Z1_realtime  = new TH1D("h_Z1_realtime","Species 1 Untrapped Pop Z, from continuous non-radioactive loss of trapped ions, vs real time in ms",tBins,tMin,tMax);
	TH1D *h_Z2_realtime  = new TH1D("h_Z2_realtime","Species 2 Untrapped Pop Z, from continuous non-radioactive loss of trapped ions, vs real time in ms",tBins,tMin,tMax);
	TH1D *h_Z3_realtime  = new TH1D("h_Z3_realtime","Species 3 Untrapped Pop Z, from continuous non-radioactive loss of trapped ions, vs real time in ms",tBins,tMin,tMax);
//	TH1D *h_X1_realtime  = new TH1D("h_X1_realtime","Species 1 Untrapped Pop X, from feeding by trapped parents, vs real time in ms",tBins,tMin,tMax);
	TH1D *h_X2_realtime  = new TH1D("h_X2_realtime","Species 2 Untrapped Pop X, from feeding by trapped parents, vs real time in ms",tBins,tMin,tMax);
	TH1D *h_X3_realtime  = new TH1D("h_X3_realtime","Species 3 Untrapped Pop X, from feeding by trapped parents, vs real time in ms",tBins,tMin,tMax);
//	TH1D *h_Y1_realtime  = new TH1D("h_Y1_realtime","Species 1 Untrapped Pop Y, from feeding by untrapped parents, vs real time in ms",tBins,tMin,tMax);
	TH1D *h_Y2_realtime  = new TH1D("h_Y2_realtime","Species 2 Untrapped Pop Y, from feeding by untrapped parents, vs real time in ms",tBins,tMin,tMax);
	TH1D *h_Y3_realtime  = new TH1D("h_Y3_realtime","Species 3 Untrapped Pop Y, from feeding by untrapped parents, vs real time in ms",tBins,tMin,tMax);
	// Decays
	TH1D *h_D_realtime	 = new TH1D("h_D_realtime","All Beta detections vs real time in ms"			,tBins,tMin,tMax);
	TH1D *h_DT1_realtime = new TH1D("h_DT1_realtime","Species 1 Betas from Trapped Pop T, vs real time in ms"	,tBins,tMin,tMax);
	TH1D *h_DT2_realtime = new TH1D("h_DT2_realtime","Species 2 Betas from Trapped Pop T, vs real time in ms"	,tBins,tMin,tMax);
	TH1D *h_DT3_realtime = new TH1D("h_DT3_realtime","Species 3 Betas from Trapped Pop T, vs real time in ms"	,tBins,tMin,tMax);
	TH1D *h_DU1_realtime  = new TH1D("h_DU1_realtime","Species 1 Betas from All Untrapped Pops (U), vs real time in ms",tBins,tMin,tMax);
	TH1D *h_DU2_realtime  = new TH1D("h_DU2_realtime","Species 2 Betas from All Untrapped Pops (U), vs real time in ms",tBins,tMin,tMax);
	TH1D *h_DU3_realtime  = new TH1D("h_DU3_realtime","Species 3 Betas from All Untrapped Pops (U), vs real time in ms",tBins,tMin,tMax);
	TH1D *h_DV1_realtime  = new TH1D("h_DV1_realtime","Species 1 Betas from Untrapped Pop V, from loss of injected bunch at capture, vs real time in ms",tBins,tMin,tMax);
	TH1D *h_DV2_realtime  = new TH1D("h_DV2_realtime","Species 2 Betas from Untrapped Pop V, from loss of injected bunch at capture, vs real time in ms",tBins,tMin,tMax);
	TH1D *h_DV3_realtime  = new TH1D("h_DV3_realtime","Species 3 Betas from Untrapped Pop V, from loss of injected bunch at capture, vs real time in ms",tBins,tMin,tMax);
	TH1D *h_DW1_realtime  = new TH1D("h_DW1_realtime","Species 1 Betas from Untrapped Pop W, from loss of already-trapped ions at capture, vs real time in ms",tBins,tMin,tMax);
	TH1D *h_DW2_realtime  = new TH1D("h_DW2_realtime","Species 2 Betas from Untrapped Pop W, from loss of already-trapped ions at capture, vs real time in ms",tBins,tMin,tMax);
	TH1D *h_DW3_realtime  = new TH1D("h_DW3_realtime","Species 3 Betas from Untrapped Pop W, from loss of already-trapped ions at capture, vs real time in ms",tBins,tMin,tMax);
	TH1D *h_DZ1_realtime  = new TH1D("h_DZ1_realtime","Species 1 Betas from Untrapped Pop Z, from continuous non-radioactive loss of trapped ions, vs real time in ms",tBins,tMin,tMax);
	TH1D *h_DZ2_realtime  = new TH1D("h_DZ2_realtime","Species 2 Betas from Untrapped Pop Z, from continuous non-radioactive loss of trapped ions, vs real time in ms",tBins,tMin,tMax);
	TH1D *h_DZ3_realtime  = new TH1D("h_DZ3_realtime","Species 3 Betas from Untrapped Pop Z, from continuous non-radioactive loss of trapped ions, vs real time in ms",tBins,tMin,tMax);
//	TH1D *h_DX1_realtime  = new TH1D("h_DX1_realtime","Species 1 Betas from Untrapped Pop X, from feeding by trapped parents, vs real time in ms",tBins,tMin,tMax);
	TH1D *h_DX2_realtime  = new TH1D("h_DX2_realtime","Species 2 Betas from Untrapped Pop X, from feeding by trapped parents, vs real time in ms",tBins,tMin,tMax);
	TH1D *h_DX3_realtime  = new TH1D("h_DX3_realtime","Species 3 Betas from Untrapped Pop X, from feeding by trapped parents, vs real time in ms",tBins,tMin,tMax);
//	TH1D *h_DY1_realtime  = new TH1D("h_DY1_realtime","Species 1 Betas from Untrapped Pop Y, from feeding by untrapped parents, vs real time in ms",tBins,tMin,tMax);
	TH1D *h_DY2_realtime  = new TH1D("h_DY2_realtime","Species 2 Betas from Untrapped Pop Y, from feeding by untrapped parents, vs real time in ms",tBins,tMin,tMax);
	TH1D *h_DY3_realtime  = new TH1D("h_DY3_realtime","Species 3 Betas from Untrapped Pop Y, from feeding by untrapped parents, vs real time in ms",tBins,tMin,tMax);
	
// Histos on cycle time
	Int_t cycBins	= 302000/T_step;//(T_cycle+2000)/T_step;
	Int_t cycMin	= -1000;
	Int_t cycMax	= 301000;//T_cycle+1000;
	
	// Decays
	TH1D *h_D_cyctime	= new TH1D("h_D_cyctime","All Beta detections vs cycle time in ms"			,cycBins,cycMin,cycMax);
	TH1D *h_DDC_cyctime	= new TH1D("h_DDC_cyctime","DC Beta detections vs cycle time in ms"			,cycBins,cycMin,cycMax);
	TH1D *h_DT1_cyctime	= new TH1D("h_DT1_cyctime","Species 1 Betas from Trapped Pop T, vs cycle time in ms"	,cycBins,cycMin,cycMax);
	TH1D *h_DT2_cyctime	= new TH1D("h_DT2_cyctime","Species 2 Betas from Trapped Pop T, vs cycle time in ms"	,cycBins,cycMin,cycMax);
	TH1D *h_DT3_cyctime	= new TH1D("h_DT3_cyctime","Species 3 Betas from Trapped Pop T, vs cycle time in ms"	,cycBins,cycMin,cycMax);
	TH1D *h_DU1_cyctime = new TH1D("h_DU1_cyctime","Species 1 Betas from All Untrapped Pops (U), vs cycle time in ms"	,cycBins,cycMin,cycMax);
	TH1D *h_DU2_cyctime = new TH1D("h_DU2_cyctime","Species 2 Betas from All Untrapped Pops (U), vs cycle time in ms"	,cycBins,cycMin,cycMax);
	TH1D *h_DU3_cyctime = new TH1D("h_DU3_cyctime","Species 3 Betas from All Untrapped Pops (U), vs cycle time in ms"	,cycBins,cycMin,cycMax);
	TH1D *h_DV1_cyctime = new TH1D("h_DV1_cyctime","Species 1 Betas from Untrapped Pop V, from loss of injected bunch at capture, vs cycle time in ms"	,cycBins,cycMin,cycMax);
	TH1D *h_DV2_cyctime = new TH1D("h_DV2_cyctime","Species 2 Betas from Untrapped Pop V, from loss of injected bunch at capture, vs cycle time in ms"	,cycBins,cycMin,cycMax);
	TH1D *h_DV3_cyctime = new TH1D("h_DV3_cyctime","Species 3 Betas from Untrapped Pop V, from loss of injected bunch at capture, vs cycle time in ms"	,cycBins,cycMin,cycMax);
	TH1D *h_DW1_cyctime = new TH1D("h_DW1_cyctime","Species 1 Betas from Untrapped Pop W, from loss of already-trapped ions at capture, vs cycle time in ms"	,cycBins,cycMin,cycMax);
	TH1D *h_DW2_cyctime = new TH1D("h_DW2_cyctime","Species 2 Betas from Untrapped Pop W, from loss of already-trapped ions at capture, vs cycle time in ms"	,cycBins,cycMin,cycMax);
	TH1D *h_DW3_cyctime = new TH1D("h_DW3_cyctime","Species 3 Betas from Untrapped Pop W, from loss of already-trapped ions at capture, vs cycle time in ms"	,cycBins,cycMin,cycMax);
	TH1D *h_DZ1_cyctime = new TH1D("h_DZ1_cyctime","Species 1 Betas from Untrapped Pop Z, from continuous non-radioactive loss of trapped ions, vs cycle time in ms"	,cycBins,cycMin,cycMax);
	TH1D *h_DZ2_cyctime = new TH1D("h_DZ2_cyctime","Species 2 Betas from Untrapped Pop Z, from continuous non-radioactive loss of trapped ions, vs cycle time in ms"	,cycBins,cycMin,cycMax);
	TH1D *h_DZ3_cyctime = new TH1D("h_DZ3_cyctime","Species 3 Betas from Untrapped Pop Z, from continuous non-radioactive loss of trapped ions, vs cycle time in ms"	,cycBins,cycMin,cycMax);
//	TH1D *h_DX1_cyctime = new TH1D("h_DX1_cyctime","Species 1 Betas from Untrapped Pop X, from feeding by trapped parents, vs cycle time in ms"	,cycBins,cycMin,cycMax);
	TH1D *h_DX2_cyctime = new TH1D("h_DX2_cyctime","Species 2 Betas from Untrapped Pop X, from feeding by trapped parents, vs cycle time in ms"	,cycBins,cycMin,cycMax);
	TH1D *h_DX3_cyctime = new TH1D("h_DX3_cyctime","Species 3 Betas from Untrapped Pop X, from feeding by trapped parents, vs cycle time in ms"	,cycBins,cycMin,cycMax);
//	TH1D *h_DY1_cyctime = new TH1D("h_DY1_cyctime","Species 1 Betas from Untrapped Pop Y, from feeding by untrapped parents, vs cycle time in ms"	,cycBins,cycMin,cycMax);
	TH1D *h_DY2_cyctime = new TH1D("h_DY2_cyctime","Species 2 Betas from Untrapped Pop Y, from feeding by untrapped parents, vs cycle time in ms"	,cycBins,cycMin,cycMax);
	TH1D *h_DY3_cyctime = new TH1D("h_DY3_cyctime","Species 3 Betas from Untrapped Pop Y, from feeding by untrapped parents, vs cycle time in ms"	,cycBins,cycMin,cycMax);
	
//	Int_t trap_flag;
	
	// Ion populations: # present
	Double_t T1 = 0, T2 = 0, T3 = 0; //   trapped ions of species 1, 2, 3
//	Double_t U1 = 0, U2 = 0, U3 = 0; // untrapped ions (all); U = V+W+X+Y
	Double_t V1 = 0, V2 = 0, V3 = 0; //   trapped ions lost during capture
	Double_t W1 = 0, W2 = 0, W3 = 0; //  injected ions lost during capture
	Double_t Z1 = 0, Z2 = 0, Z3 = 0; //  trapped ions lost continuously but non-radioactively (eg. trap lifetime)
	Double_t X2 = 0, X3 = 0; // untrapped ions from decays of trapped parents ("feeding")
	Double_t Y2 = 0, Y3 = 0; // untrapped ions from decays of untrapped parents ("feeding")
	
	// # of decays by population
	Double_t decays_T1=0, decays_T2=0, decays_T3=0, decays_T1a=0, decays_T1b=0, decays_T2a=0, decays_T2b=0;
//	Double_t decays_U1=0, decays_U2=0, decays_U3=0;
	Double_t decays_V1=0, decays_V2=0, decays_V3=0, decays_V1a=0, decays_V1b=0, decays_V2a=0, decays_V2b=0;
	Double_t decays_W1=0, decays_W2=0, decays_W3=0, decays_W1a=0, decays_W1b=0, decays_W2a=0, decays_W2b=0;
	Double_t decays_Z1=0, decays_Z2=0, decays_Z3=0, decays_Z1a=0, decays_Z1b=0, decays_Z2a=0, decays_Z2b=0;
	Double_t 			   decays_X2=0, decays_X3=0, 							 decays_X2a=0, decays_X2b=0;
	Double_t 			   decays_Y2=0, decays_Y3=0, 							 decays_Y2a=0, decays_Y2b=0;
	
	// # of already-trapped ions lost during a capture
	Double_t captloss_T1=0, captloss_T2=0, captloss_T3=0;
	
	// # of decays by population
	Double_t traploss_T1=0, traploss_T2=0, traploss_T3=0, traploss_T1a=0, traploss_T1b=0, traploss_T2a=0, traploss_T2b=0, traploss_T3a=0, traploss_T3b=0;
	Double_t traploss_V1=0, traploss_V2=0, traploss_V3=0, traploss_V1a=0, traploss_V1b=0, traploss_V2a=0, traploss_V2b=0, traploss_V3a=0, traploss_V3b=0;
	Double_t traploss_W1=0, traploss_W2=0, traploss_W3=0, traploss_W1a=0, traploss_W1b=0, traploss_W2a=0, traploss_W2b=0, traploss_W3a=0, traploss_W3b=0;
	Double_t traploss_Z1=0, traploss_Z2=0, traploss_Z3=0, traploss_Z1a=0, traploss_Z1b=0, traploss_Z2a=0, traploss_Z2b=0, traploss_Z3a=0, traploss_Z3b=0;
	Double_t 				 traploss_X2=0, traploss_X3=0, 								   traploss_X2a=0, traploss_X2b=0, traploss_X3a=0, traploss_X3b=0;
	Double_t 				 traploss_Y2=0, traploss_Y3=0, 								   traploss_Y2a=0, traploss_Y2b=0, traploss_Y3a=0, traploss_Y3b=0;
	
	// # of detections by population
	Double_t DT1=0, DT2=0, DT3=0; 
//	Double_t DU1=0, DU2=0, DU3=0;
	Double_t DV1=0, DV2=0, DV3=0;
	Double_t DW1=0, DW2=0, DW3=0;
	Double_t DZ1=0, DZ2=0, DZ3=0;
	Double_t DX2=0, DX3=0;
	Double_t DY2=0, DY3=0;
	Double_t DDC=0;
	
	// Total detections by population
	Double_t nDT1=0, nDT2=0, nDT3=0; // # of decays of each pop
	Double_t nDU1=0, nDU2=0, nDU3=0; // # of decays of each pop
	Double_t nDV1=0, nDV2=0, nDV3=0; // # of decays of each pop
	Double_t nDW1=0, nDW2=0, nDW3=0; // # of decays of each pop
	Double_t nDZ1=0, nDZ2=0, nDZ3=0; // # of decays of each pop
	Double_t nDX2=0, nDX3=0; // # of decays of each pop
	Double_t nDY2=0, nDY3=0; // # of decays of each pop
	Double_t nDDC=0;
	
	// Ions lost from trapped pops when capture pulse happens
//	Int_t captloss_T1=0, captloss_T2=0, captloss_T3=0;
	
	// The Big Loop
	for (Int_t i=0; i<nSteps; i++) { // not i<=nSteps
		
		t		= i*T_step; // real time in ms
		t_cyc	= t%T_cycle; // cycle time in ms
		t_bin 	= i					-   tMin/T_step + 1;
		cyc_bin	= i%(T_cycle/T_step)- cycMin/T_step + 1;
		if (!(i%100000)) printf("Step %10d of %10d. t=%10d\n",i,nSteps,t);
//		printf("i=%d, t=%d, t_bin=%d, cyc_bin=%d\n",i,t,t_bin,cyc_bin);
//		printf("t=%d, tcyc = %d, T1 = %d\n",t,t_cyc,T1);
		
// CAPTURE PULSE:
// Ion injection at t_cyc = T_bkgd + n*T_capt for n = 0, 1, 2, 3 ...
		if (t_cyc>=T_bkgd && (t_cyc-T_bkgd)%T_capt==0) {
			//printf("t = %d (t_cyc = %d), ions captured! Aiyeeeeee!!\n",t,t_cyc);
			
		// Fractional losses of already-trapped ions, due to capture pulse
		// Moves ions from T pops to W pops
		// Happens before new ions get in
			captloss_T1 = (1-rho)*T1;
			captloss_T2 = (1-rho)*T2;
			captloss_T3 = (1-rho)*T3;
			T1 -= captloss_T1;
			T2 -= captloss_T2;
			T3 -= captloss_T3;
			W1 += captloss_T1;
			W2 += captloss_T2;
			W3 += captloss_T3;
			
		// Add the injected bunch of ions to T and U pops
			T1 +=    p  * r1 * T_capt;//randgen->Poisson(   p * r1 * T_capt);
			T2 +=    p  * r2 * T_capt;//randgen->Poisson(   p * r2 * T_capt);
			T3 +=    p  * r3 * T_capt;//randgen->Poisson(   p * r3 * T_capt);
			V1 += (1-p) * r1 * T_capt;//randgen->Poisson((1-p)* r1 * T_capt);
			V2 += (1-p) * r2 * T_capt;//randgen->Poisson((1-p)* r2 * T_capt);
			V3 += (1-p) * r3 * T_capt;//randgen->Poisson((1-p)* r3 * T_capt);
			
		}
		
// EJECTION PULSE:
// Ion ejection at t_cyc = 0
		if (t_cyc==0) {
			T1 = 0;
			T2 = 0;
			T3 = 0;
		}
		
		if (t >= T_bkgd) { // Don't allow (DC) decays in the first background cycle... it throws things off

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~		
		// Calculate continuous trap losses
			traploss_T1 = randgen->Binomial(T1, pLT1 );
			traploss_T2 = randgen->Binomial(T2, pLT2 );
			traploss_T3 = randgen->Binomial(T3, pLT3 );
			traploss_V1 = randgen->Binomial(V1, pLU1 );
			traploss_V2 = randgen->Binomial(V2, pLU2 );
			traploss_V3 = randgen->Binomial(V3, pLU3 );
			traploss_W1 = randgen->Binomial(W1, pLU1 );
			traploss_W2 = randgen->Binomial(W2, pLU2 );
			traploss_W3 = randgen->Binomial(W3, pLU3 );
			traploss_Z1 = randgen->Binomial(Z1, pLU1 );
			traploss_Z2 = randgen->Binomial(Z2, pLU2 );
			traploss_Z3 = randgen->Binomial(Z3, pLU3 );
			traploss_X2 = randgen->Binomial(X2, pLU2 );
			traploss_X3 = randgen->Binomial(X3, pLU3 );
			traploss_Y2 = randgen->Binomial(Y2, pLU2 );
			traploss_Y3 = randgen->Binomial(Y3, pLU3 );
		// Same trick as described below for feeding. Split the trap losses to simulate their concurrency with decay losses.
			traploss_T1a = TMath::Nint(traploss_T1/2.0 + 0.1*randgen->Rndm(1)); traploss_T1b = traploss_T1 - traploss_T1a;
			traploss_T2a = TMath::Nint(traploss_T2/2.0 + 0.1*randgen->Rndm(1)); traploss_T2b = traploss_T2 - traploss_T2a;
			traploss_T3a = TMath::Nint(traploss_T3/2.0 + 0.1*randgen->Rndm(1)); traploss_T3b = traploss_T3 - traploss_T3a;
			traploss_V1a = TMath::Nint(traploss_V1/2.0 + 0.1*randgen->Rndm(1)); traploss_V1b = traploss_V1 - traploss_V1a;
			traploss_V2a = TMath::Nint(traploss_V2/2.0 + 0.1*randgen->Rndm(1)); traploss_V2b = traploss_V2 - traploss_V2a;
			traploss_V3a = TMath::Nint(traploss_V3/2.0 + 0.1*randgen->Rndm(1)); traploss_V3b = traploss_V3 - traploss_V3a;
			traploss_W1a = TMath::Nint(traploss_W1/2.0 + 0.1*randgen->Rndm(1)); traploss_W1b = traploss_W1 - traploss_W1a;
			traploss_W2a = TMath::Nint(traploss_W2/2.0 + 0.1*randgen->Rndm(1)); traploss_W2b = traploss_W2 - traploss_W2a;
			traploss_W3a = TMath::Nint(traploss_W3/2.0 + 0.1*randgen->Rndm(1)); traploss_W3b = traploss_W3 - traploss_W3a;
			traploss_Z1a = TMath::Nint(traploss_Z1/2.0 + 0.1*randgen->Rndm(1)); traploss_Z1b = traploss_Z1 - traploss_Z1a;
			traploss_Z2a = TMath::Nint(traploss_Z2/2.0 + 0.1*randgen->Rndm(1)); traploss_Z2b = traploss_Z2 - traploss_Z2a;
			traploss_Z3a = TMath::Nint(traploss_Z3/2.0 + 0.1*randgen->Rndm(1)); traploss_Z3b = traploss_Z3 - traploss_Z3a;
			traploss_X2a = TMath::Nint(traploss_X2/2.0 + 0.1*randgen->Rndm(1)); traploss_X2b = traploss_X2 - traploss_X2a;
			traploss_X3a = TMath::Nint(traploss_X3/2.0 + 0.1*randgen->Rndm(1)); traploss_X3b = traploss_X3 - traploss_X3a;
			traploss_Y2a = TMath::Nint(traploss_Y2/2.0 + 0.1*randgen->Rndm(1)); traploss_Y2b = traploss_Y2 - traploss_Y2a;
			traploss_Y3a = TMath::Nint(traploss_Y3/2.0 + 0.1*randgen->Rndm(1)); traploss_Y3b = traploss_Y3 - traploss_Y3a;
		// Remove first half of continuous trap losses
			T1 -= traploss_T1a;
			T2 -= traploss_T2a;
			T3 -= traploss_T3a;
			V1 -= traploss_V1a;
			V2 -= traploss_V2a;
			V3 -= traploss_V3a;
			W1 -= traploss_W1a;
			W2 -= traploss_W2a;
			W3 -= traploss_W3a;
			Z1 += traploss_T1a - traploss_Z1a; // Z pops get the T losses
			Z2 += traploss_T2a - traploss_Z2a; // Z pops get the T losses
			Z3 += traploss_T3a - traploss_Z3a; // Z pops get the T losses
			X2 -= traploss_X2a;
			X3 -= traploss_X3a;
			Y2 -= traploss_Y2a;
			Y3 -= traploss_Y3a;
		// It is important that decays happen within the splitting of trap losses
		// Right now we are in that splitting

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Calculate radioactive decays of populations

		// Populations that are not fed:
			decays_T1 = randgen->Binomial(T1, pD1 );
			decays_T2 = randgen->Binomial(T2, pD2 );
			decays_T3 = randgen->Binomial(T3, pD3 );
			decays_V1 = randgen->Binomial(V1, pD1 );
			decays_V2 = randgen->Binomial(V2, pD2 );
			decays_V3 = randgen->Binomial(V3, pD3 );
			decays_W1 = randgen->Binomial(W1, pD1 );
			decays_W2 = randgen->Binomial(W2, pD2 );
			decays_W3 = randgen->Binomial(W3, pD3 );
			decays_Z1 = randgen->Binomial(Z1, pD1 );
			decays_Z2 = randgen->Binomial(Z2, pD2 );
			decays_Z3 = randgen->Binomial(Z3, pD3 );

		// Polpulations that are fed
			// Break decays in this time step into two halves, a and b.
			// This reflects the fact that the average amount of time the daughter isotope has to decay again
			// is very close to half the time step (with the right choice of time step).
			// Half-integers are randomized to round up and down with equal frequency.
			
			// Split up decays that feed species 2
			decays_T1a = TMath::Nint(decays_T1/2.0 + 0.1*randgen->Rndm(1)); decays_T1b = decays_T1 - decays_T1a;
			decays_V1a = TMath::Nint(decays_V1/2.0 + 0.1*randgen->Rndm(1)); decays_V1b = decays_V1 - decays_V1a;
			decays_W1a = TMath::Nint(decays_W1/2.0 + 0.1*randgen->Rndm(1)); decays_W1b = decays_W1 - decays_W1a;
			decays_Z1a = TMath::Nint(decays_Z1/2.0 + 0.1*randgen->Rndm(1)); decays_Z1b = decays_Z1 - decays_Z1a;
			// First half of species 2 feeding
			X2 += decays_T1a;
			Y2 += decays_V1a + decays_W1a + decays_Z1a;
			// Decays of fed pops of species 2
			decays_X2 = randgen->Binomial(X2, pD2);
			decays_Y2 = randgen->Binomial(Y2, pD2);
			// Second half of species 2 feeding
			X2 += decays_T1b;
			Y2 += decays_V1b + decays_W1b + decays_Z1b;
			
			// Split up decays that feed species 3
			decays_T2a = TMath::Nint(decays_T2/2.0 + 0.1*randgen->Rndm(1)); decays_T2b = decays_T2 - decays_T2a;
			decays_V2a = TMath::Nint(decays_V2/2.0 + 0.1*randgen->Rndm(1)); decays_V2b = decays_V2 - decays_V2a;
			decays_W2a = TMath::Nint(decays_W2/2.0 + 0.1*randgen->Rndm(1)); decays_W2b = decays_W2 - decays_W2a;
			decays_Z2a = TMath::Nint(decays_Z2/2.0 + 0.1*randgen->Rndm(1)); decays_Z2b = decays_Z2 - decays_Z2a;
			decays_X2a = TMath::Nint(decays_X2/2.0 + 0.1*randgen->Rndm(1)); decays_X2b = decays_X2 - decays_X2a; // decays_X2 just defined above
			decays_Y2a = TMath::Nint(decays_Y2/2.0 + 0.1*randgen->Rndm(1)); decays_Y2b = decays_Y2 - decays_Y2a; // decays_Y2 just defined above
			// First half of species 3 feeding
			X3 += decays_T2a;
			Y3 += decays_V2a + decays_W2a + decays_Z2a + decays_X2a + decays_Y2a;
			// Decays of fed pops of species 3
			decays_X3 = randgen->Binomial(X3, pD3);
			decays_Y3 = randgen->Binomial(Y3, pD3);
			// Second half of species 3 feeding
			X3 += decays_T2b;
			Y3 += decays_V2b + decays_W2b + decays_Z2b + decays_X2b + decays_Y2b;
			
		// Remove second half of continuous trap losses
			T1 -= traploss_T1b;
			T2 -= traploss_T2b;
			T3 -= traploss_T3b;
			V1 -= traploss_V1b;
			V2 -= traploss_V2b;
			V3 -= traploss_V3b;
			W1 -= traploss_W1b;
			W2 -= traploss_W2b;
			W3 -= traploss_W3b;
			Z1 += traploss_T1b - traploss_Z1b; // Z pops get the T losses
			Z2 += traploss_T2b - traploss_Z2b; // Z pops get the T losses
			Z3 += traploss_T3b - traploss_Z3b; // Z pops get the T losses
			X2 -= traploss_X2b;
			X3 -= traploss_X3b;
			Y2 -= traploss_Y2b;
			Y3 -= traploss_Y3b;
			
		// Dectections of all pops
			DT1 = randgen->Binomial(decays_T1, eps_T );
			DT2 = randgen->Binomial(decays_T2, eps_T );
			DT3 = randgen->Binomial(decays_T3, eps_T );
			DV1 = randgen->Binomial(decays_V1, eps_V );
			DV2 = randgen->Binomial(decays_V2, eps_V );
			DV3 = randgen->Binomial(decays_V3, eps_V );
			DW1 = randgen->Binomial(decays_W1, eps_W );
			DW2 = randgen->Binomial(decays_W2, eps_W );
			DW3 = randgen->Binomial(decays_W3, eps_W );
			DZ1 = randgen->Binomial(decays_Z1, eps_Z );
			DZ2 = randgen->Binomial(decays_Z2, eps_Z );
			DZ3 = randgen->Binomial(decays_Z3, eps_Z );
			DX2 = randgen->Binomial(decays_X2, eps_X );
			DX3 = randgen->Binomial(decays_X3, eps_X );
			DY2 = randgen->Binomial(decays_Y2, eps_Y );
			DY3 = randgen->Binomial(decays_Y3, eps_Y );
		// DC background
			DDC = randgen->Poisson(rDC*T_step);//printf("%d DC decays\n",DDC);
			
		// Count all detections of each type
			nDT1 += DT1;
			nDT2 += DT2;
			nDT3 += DT3;
			nDV1 += DV1;
			nDV2 += DV2;
			nDV3 += DV3;
			nDW1 += DW1;
			nDW2 += DW2;
			nDW3 += DW3;
			nDZ1 += DZ1;
			nDZ2 += DZ2;
			nDZ3 += DZ3;
			nDX2 += DX2;
			nDX3 += DX3;
			nDY2 += DY2;
			nDY3 += DY3;
			nDDC += DDC;
			
		// Remove decay losses from populations
			T1 -= decays_T1;
			T2 -= decays_T2;
			T3 -= decays_T3;
			V1 -= decays_V1;
			V2 -= decays_V2;
			V3 -= decays_V3;
			W1 -= decays_W1;
			W2 -= decays_W2;
			W3 -= decays_W3;
			Z1 -= decays_Z1;
			Z2 -= decays_Z2;
			Z3 -= decays_Z3;
			X2 -= decays_X2;
			X3 -= decays_X3;
			Y2 -= decays_Y2;
			Y3 -= decays_Y3;
			
		}
		
		//if (i%100==0) printf("T1=%f\n",T1);
		
		h_T1_realtime->SetBinContent(t_bin,T1);
		h_T2_realtime->SetBinContent(t_bin,T2);
		h_T3_realtime->SetBinContent(t_bin,T3);
//		h_T_realtime ->SetBinContent(t_bin,T1+T2+T3);
//		h_U_realtime ->SetBinContent(t_bin,U1+U2+U3);
		h_V1_realtime->SetBinContent(t_bin,V1);
		h_V2_realtime->SetBinContent(t_bin,V2);
		h_V3_realtime->SetBinContent(t_bin,V3);
		h_W1_realtime->SetBinContent(t_bin,W1);
		h_W2_realtime->SetBinContent(t_bin,W2);
		h_W3_realtime->SetBinContent(t_bin,W3);
		h_Z1_realtime->SetBinContent(t_bin,Z1);
		h_Z2_realtime->SetBinContent(t_bin,Z2);
		h_Z3_realtime->SetBinContent(t_bin,Z3);
		h_X2_realtime->SetBinContent(t_bin,X2);
		h_X3_realtime->SetBinContent(t_bin,X3);
		h_Y2_realtime->SetBinContent(t_bin,Y2);
		h_Y3_realtime->SetBinContent(t_bin,Y3);
		h_U1_realtime->SetBinContent(t_bin,V1+W1+Z1);
		h_U2_realtime->SetBinContent(t_bin,V2+W2+Z2+X2+Y2);
		h_U3_realtime->SetBinContent(t_bin,V3+W3+Z3+X3+Y3);
		h_A_realtime->SetBinContent(t_bin, T1+T2+T3 + V1+V2+V3 + W1+W2+W3 + Z1+Z2+Z3 + X2+X3 + Y2+Y3);
		
		h_DT1_realtime->SetBinContent(t_bin,DT1);
		h_DT2_realtime->SetBinContent(t_bin,DT2);
		h_DT3_realtime->SetBinContent(t_bin,DT3);
		h_DV1_realtime->SetBinContent(t_bin,DV1);
		h_DV2_realtime->SetBinContent(t_bin,DV2);
		h_DV3_realtime->SetBinContent(t_bin,DV3);
		h_DW1_realtime->SetBinContent(t_bin,DW1);
		h_DW2_realtime->SetBinContent(t_bin,DW2);
		h_DW3_realtime->SetBinContent(t_bin,DW3);
		h_DZ1_realtime->SetBinContent(t_bin,DZ1);
		h_DZ2_realtime->SetBinContent(t_bin,DZ2);
		h_DZ3_realtime->SetBinContent(t_bin,DZ3);
		h_DX2_realtime->SetBinContent(t_bin,DX2);
		h_DX3_realtime->SetBinContent(t_bin,DX3);
		h_DY2_realtime->SetBinContent(t_bin,DY2);
		h_DY3_realtime->SetBinContent(t_bin,DY3);
		h_DU1_realtime->SetBinContent(t_bin,DV1+DW1+DZ1);
		h_DU2_realtime->SetBinContent(t_bin,DV2+DW2+DZ2+DX2+DY2);
		h_DU3_realtime->SetBinContent(t_bin,DV3+DW3+DZ3+DX3+DY3);
		
//		if ((T_cycle + t - T_bkgd)%T_cycle == T_cycle-1) printf("t=%d: T1=%d, DT1=%d, T2=%d, DT2=%d, T3=%d, DT3=%d\n",t,T1,DT1,T2,DT2,T3,DT3);
//		if ((T_cycle + t - T_bkgd)%T_cycle == 0        ) printf("t=%d: T1=%d, DT1=%d, T2=%d, DT2=%d, T3=%d, DT3=%d\n",t,T1,DT1,T2,DT2,T3,DT3);
		
		h_D_realtime->SetBinContent(  t_bin,DDC + DT1+DT2+DT3 + DV1+DV2+DV3 + DW1+DW2+DW3 + DZ1+DZ2+DZ3 + DX2+DX3 + DY2+DY3);
		h_D_cyctime	->AddBinContent(cyc_bin,DDC + DT1+DT2+DT3 + DV1+DV2+DV3 + DW1+DW2+DW3 + DZ1+DZ2+DZ3 + DX2+DX3 + DY2+DY3);
		h_DDC_cyctime->AddBinContent(cyc_bin,DDC);
		h_DT1_cyctime->AddBinContent(cyc_bin,DT1);
		h_DT2_cyctime->AddBinContent(cyc_bin,DT2);
		h_DT3_cyctime->AddBinContent(cyc_bin,DT3);
		h_DV1_cyctime->AddBinContent(cyc_bin,DV1);
		h_DV2_cyctime->AddBinContent(cyc_bin,DV2);
		h_DV3_cyctime->AddBinContent(cyc_bin,DV3);
		h_DW1_cyctime->AddBinContent(cyc_bin,DW1);
		h_DW2_cyctime->AddBinContent(cyc_bin,DW2);
		h_DW3_cyctime->AddBinContent(cyc_bin,DW3);
		h_DZ1_cyctime->AddBinContent(cyc_bin,DZ1);
		h_DZ2_cyctime->AddBinContent(cyc_bin,DZ2);
		h_DZ3_cyctime->AddBinContent(cyc_bin,DZ3);
//		h_DX1_cyctime->AddBinContent(cyc_bin,DX1);
		h_DX2_cyctime->AddBinContent(cyc_bin,DX2);
		h_DX3_cyctime->AddBinContent(cyc_bin,DX3);
//		h_DY1_cyctime->AddBinContent(cyc_bin,DY1);
		h_DY2_cyctime->AddBinContent(cyc_bin,DY2);
		h_DY3_cyctime->AddBinContent(cyc_bin,DY3);
		h_DU1_cyctime->AddBinContent(cyc_bin,DV1+DW1+DZ1);
		h_DU2_cyctime->AddBinContent(cyc_bin,DV2+DW2+DZ2+DX2+DY2);
		h_DU3_cyctime->AddBinContent(cyc_bin,DV3+DW3+DZ3+DX3+DY3);
		
		//if (i==26000) i=1000000000;
	} // Big Loop
	
	nDU1 = nDV1 + nDW1 + nDZ1;
	nDU2 = nDV2 + nDW2 + nDZ2 + nDX2 + nDY2;
	nDU3 = nDV3 + nDW3 + nDZ3 + nDX3 + nDY3;
	
	h_D_cyctime->SetEntries(nDDC+nDT1+nDT2+nDT3+nDU1+nDU2+nDU3);
	h_DDC_cyctime->SetEntries(nDDC);
	h_DT1_cyctime->SetEntries(nDT1);
	h_DT2_cyctime->SetEntries(nDT2);
	h_DT3_cyctime->SetEntries(nDT3);
	h_DU1_cyctime->SetEntries(nDU1);
	h_DU2_cyctime->SetEntries(nDU2);
	h_DU3_cyctime->SetEntries(nDU3);
	h_DV1_cyctime->SetEntries(nDV1);
	h_DV2_cyctime->SetEntries(nDV2);
	h_DV3_cyctime->SetEntries(nDV3);
	h_DW1_cyctime->SetEntries(nDW1);
	h_DW2_cyctime->SetEntries(nDW2);
	h_DW3_cyctime->SetEntries(nDW3);
	h_DZ1_cyctime->SetEntries(nDZ1);
	h_DZ2_cyctime->SetEntries(nDZ2);
	h_DZ3_cyctime->SetEntries(nDZ3);
//	h_DX1_cyctime->SetEntries(nDX1);
	h_DX2_cyctime->SetEntries(nDX2);
	h_DX3_cyctime->SetEntries(nDX3);
//	h_DY1_cyctime->SetEntries(nDY1);
	h_DY2_cyctime->SetEntries(nDY2);
	h_DY3_cyctime->SetEntries(nDY3);
	
	rootfile->Write();
	rootfile->Close();
	
	printf("\n");
	printf("Number of decays:\n");
	printf("DC=%10.1f\n",nDDC);
	printf("T1=%10.1f  U1=%10.1f  V1=%10.1f  W1=%10.1f  Z1=%10.1f\n", nDT1, nDU1, nDV1, nDW1, nDZ1);
	printf("T2=%10.1f  U2=%10.1f  V2=%10.1f  W2=%10.1f  Z2=%10.1f  X2=%10.1f  Y2=%10.1f\n", nDT2, nDU2, nDV2, nDW2, nDZ2, nDX2, nDY2);
	printf("T3=%10.1f  U3=%10.1f  V3=%10.1f  W3=%10.1f  Z3=%10.1f  X3=%10.1f  Y3=%10.1f\n", nDT3, nDU3, nDV3, nDW3, nDZ3, nDX3, nDY3);
//	printf("T2: %8d\n",nDT2);
//	printf("T3: %8d\n",nDT3);
//	printf("U1: %8d\n",nDU1);
//	printf("U2: %8d\n",nDU2);
//	printf("U3: %8d\n",nDU3);
	printf("\n");
	
}

//Double_t decay (TRandom3 *gen, Double_t n, Double_t tau, Double_t tstep) {
//	// Use the normal approximation to calculate decays if n is "large enough"
//	// Large enough means n*p>10 && n*(1-p)>10 according to the internet.
//	// I will be more conservative and use 20.
//	
//	static Double_t ndecays;
//	static Double_t p;
//	p = tstep/tau;
//	if (n*p>10 && n*(1-p)>10) {
//		std::cout << "Using normal approximation. n=" << n << ", p=" << p << ", n*p=" << n*p << endl;
//	//	ndecays = TMath::Nint( gen->Gaus(n*p+0.5,TMath::Sqrt(n*p*(1-p))) );
//		ndecays = gen->Gaus(n*p+0.5,TMath::Sqrt(n*p*(1-p)));
//	}
//	else {
//		ndecays = gen->Binomial(n,p);
//	}
//	//std::cout << "ndecays = " << ndecays << endl;
//	return ndecays;
//	
//}
