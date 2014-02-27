// Always enclose header file contents with these ifndef/endif directives.
#ifndef _B_fit_model_h
#define _B_fit_model_h

namespace B_fit_model {
	
	const Int_t nPars = 19;
	Double_t par[nPars];
	Double_t err[nPars];
	
// Parameter indices -- don't change
	
	enum { DC, r1, r2, r3, p, l, epsT, epsU, epsV, epsW, epsX, epsY, tauT1, tauT2, tauT3, tauU1, tauU2, tauU3, dt };
//	enum { DC, r1, r2, r3, p, effT, effU, effV, effW, t1T, t2T, t3T, t1U, t2U, t3U, dt };
	// a[DC]	= DC detection rate in cycles/ms
	// a[r1]	= Species 1 injection rate in cycles/ms
	// a[r2]	= Species 2 injection rate in cycles/ms
	// a[r3]	= Species 3 injection rate in cycles/ms
	// a[p]		= Fraction of injected ions that is succesfully trapped
	// a[l]		= Fraction of already-trapped ions that is retained in trap at each capture
	// a[effT]	= Detection efficiency for trapped ions (T)
	// a[effU]	= Detection efficiency for untrapped ion (U)
	// a[effV]	= Detection efficiency for untrapped ion (V)
	// a[effW]	= Detection efficiency for untrapped ion (W)
	// a[t1T]	= Net lifetime of trapped species 1 (T1)
	// a[t2T]	= Net lifetime of trapped species 2 (T2)
	// a[t3T]	= Net lifetime of trapped species 3 (T3)
	// a[t1U]	= Net lifetime of untrapped species 1 (U1)
	// a[t2U]	= Net lifetime of untrapped species 2 (U2)
	// a[t3U]	= Net lifetime of untrapped species 3 (U3)
	// a[dt]	= bin width in ms
	
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
	
//	B_fit_case_t B_fit_cases[];
	
// Trapped and untrapped populations 1, 2, 3
	Double_t T1 (Double_t*, Double_t*);
	Double_t T2 (Double_t*, Double_t*);
	Double_t T3 (Double_t*, Double_t*);
	Double_t U1 (Double_t*, Double_t*);
	Double_t U2 (Double_t*, Double_t*);
	Double_t U3 (Double_t*, Double_t*);
	Double_t All (Double_t*, Double_t*);
	
// Functions to plot: (obs. decay rate)x(bin dt) = counts by bin
	Double_t yDC (Double_t*, Double_t*);
	Double_t yT1 (Double_t*, Double_t*);
	Double_t yT2 (Double_t*, Double_t*);
	Double_t yT3 (Double_t*, Double_t*);
	Double_t yU1 (Double_t*, Double_t*);
	Double_t yU2 (Double_t*, Double_t*);
	Double_t yU3 (Double_t*, Double_t*);
	Double_t yAll (Double_t*, Double_t*);
	
// Detection rates (/ms) for calculating N-beta
	Double_t rDC (Double_t*, Double_t*);
	Double_t rT1 (Double_t*, Double_t*);
	Double_t rT2 (Double_t*, Double_t*);
	Double_t rT3 (Double_t*, Double_t*);
	Double_t rU1 (Double_t*, Double_t*);
	Double_t rU2 (Double_t*, Double_t*);
	Double_t rU3 (Double_t*, Double_t*);
	Double_t rAll (Double_t*, Double_t*);
	
// Offset functions to imporve visualization: offT1 = yT1 + yDC
	Double_t oT1 (Double_t*, Double_t*);
	Double_t oT2 (Double_t*, Double_t*);
	Double_t oT3 (Double_t*, Double_t*);
	Double_t oU1 (Double_t*, Double_t*);
	Double_t oU2 (Double_t*, Double_t*);
	Double_t oU3 (Double_t*, Double_t*);
	
// Functions for evaluating and plotting the V, W, X, and Y pops	
	Double_t V1 (Double_t*, Double_t*);
	Double_t V2 (Double_t*, Double_t*);
	Double_t V3 (Double_t*, Double_t*);
	Double_t W1 (Double_t*, Double_t*);
	Double_t W2 (Double_t*, Double_t*);
	Double_t W3 (Double_t*, Double_t*);
	Double_t X2 (Double_t*, Double_t*);
	Double_t X3 (Double_t*, Double_t*);
	Double_t Y2 (Double_t*, Double_t*);
	Double_t Y3 (Double_t*, Double_t*);
	Double_t yV1 (Double_t*, Double_t*);
	Double_t yV2 (Double_t*, Double_t*);
	Double_t yV3 (Double_t*, Double_t*);
	Double_t yW1 (Double_t*, Double_t*);
	Double_t yW2 (Double_t*, Double_t*);
	Double_t yW3 (Double_t*, Double_t*);
	Double_t yX2 (Double_t*, Double_t*);
	Double_t yX3 (Double_t*, Double_t*);
	Double_t yY2 (Double_t*, Double_t*);
	Double_t yY3 (Double_t*, Double_t*);
	
	Double_t T1_integral = 0.0;
	Double_t T2_integral = 0.0;
	Double_t T3_integral = 0.0;
	Double_t U1_integral = 0.0;
	Double_t U2_integral = 0.0;
	Double_t U3_integral = 0.0;
	Double_t DC_integral = 0.0;
	Double_t All_integral = 0.0;
	
	Double_t Integral_sum = 0.0;
	
	Double_t T1_integral_error = 0.0;
	Double_t T2_integral_error = 0.0;
	Double_t T3_integral_error = 0.0;
	Double_t U1_integral_error = 0.0;
	Double_t U2_integral_error = 0.0;
	Double_t U3_integral_error = 0.0;
	Double_t DC_integral_error = 0.0;
	Double_t All_integral_error = 0.0;
	
	Double_t Integral_sum_error = 0.0;
	
}

#endif
