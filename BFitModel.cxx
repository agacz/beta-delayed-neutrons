#include "BFitModel.h"
#include "CSVtoStruct.h"
#include "TMath.h"
#include "string.h"

// Variables for all functions in this file
//void bookGlobals () {
//	extern BDNCase_t stBDNCases[FILE_ROWS_BDN]; // This comes from the main program (BFit.cxx)
//	extern Int_t iBDNCaseIndex; // This comes from the main program (BFit.cxx)
////	static const Double_t tCap	= 1000.0 * stBDNCases[iBDNCaseIndex].dCaptureTime;	// Time between BPT captures (ms)
////	static const Double_t tBac	= 1000.0 * stBDNCases[iBDNCaseIndex].dBackgroundTime; // Time spent in background measurment, per cycle (ms)
////	static const Double_t tCyc	= 1000.0 * stBDNCases[iBDNCaseIndex].dCycleTime;	// Time between BPT ejections (ms)
////	static const Double_t t1	= 1000.0 * stBDNCases[iBDNCaseIndex].dLifetime1[0]; // radioactive lifetime (1/e) in ms
////	static const Double_t t2	= 1000.0 * stBDNCases[iBDNCaseIndex].dLifetime2[0]; // radioactive lifetime (1/e) in ms
////	static const Double_t t3	= 1000.0 * stBDNCases[iBDNCaseIndex].dLifetime3[0]; // radioactive lifetime (1/e) in ms
//	extern Double_t tCap;//	= 1000.0 * stBDNCases[iBDNCaseIndex].dCaptureTime;	// Time between BPT captures (ms)
//	extern Double_t tBac;//	= 1000.0 * stBDNCases[iBDNCaseIndex].dBackgroundTime; // Time spent in background measurment, per cycle (ms)
//	extern Double_t tCyc;//	= 1000.0 * stBDNCases[iBDNCaseIndex].dCycleTime;	// Time between BPT ejections (ms)
//	extern Double_t t1;//		= 1000.0 * stBDNCases[iBDNCaseIndex].dLifetime1[0]; // radioactive lifetime (1/e) in ms
//	extern Double_t t2;//		= 1000.0 * stBDNCases[iBDNCaseIndex].dLifetime2[0]; // radioactive lifetime (1/e) in ms
//	extern Double_t t3;//		= 1000.0 * stBDNCases[iBDNCaseIndex].dLifetime3[0]; // radioactive lifetime (1/e) in ms
//}

Double_t BFitNamespace::T1 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	using namespace TMath;
	static Int_t n;
	static Double_t ST1, tT1, f;
	extern Double_t tCap, tBac, tCyc, t1, t2, t3;
//	bookGlobals();
	f = 0.0; //catch bad values of t[0]
	if (tBac <= t[0] && t[0] <= tCyc)
	{
		tT1 = 1.0 / ( 1.0/t1 + a[gammaT1]/1000.0 ); // net variable lifetime (1/e) in ms
		n = Ceil((t[0]-tBac)/tCap);
		ST1 = ( Exp(n*tCap/tT1) - Power(a[rho],n) ) / ( Exp(tCap/tT1) - a[rho] );
		f = a[p] * a[r1] * tCap * ST1 * Exp(-(t[0]-tBac)/tT1);
	}
//	printf("tCap = %f\n", tCap);
//	printf("tBac = %f\n", tBac);
//	printf("tCyc = %f\n", tCyc );
//	printf("t1 = %f\n", t1);
//	printf("t2 = %f\n", t2);
//	printf("t3 = %f\n", t3);
//	static Double_t x = t[0];
//	printf("(t, n, f) = (%f, %d, %f)\n", t[0], n, f);
	return f;
}

Double_t BFitNamespace::T2 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	using namespace TMath;
	static Int_t n;
	static Double_t ST2, tT2, f;
	extern Double_t tCap, tBac, tCyc, t2;
//	bookGlobals();
	f = 0.0; //catch bad values of t[0]
	if (tBac <= t[0] && t[0] <= tCyc)
	{
		tT2 = 1.0 / ( 1.0/t2 + a[gammaT2]/1000.0 ); // net variable lifetime (1/e) in ms
		n = Ceil((t[0]-tBac)/tCap);
		ST2 = ( Exp(n*tCap/tT2) - Power(a[rho],n) ) / ( Exp(tCap/tT2) - a[rho] );
		f = a[p] * a[r2] * tCap * ST2 * Exp(-(t[0]-tBac)/tT2);
	}
//	printf("(t, n, f) = (%f, %d, %f)\n", t[0], n, f);
//	printf("t2 = %f, gammaT2 = %f, tT2 = %f\n", t2, a[gammaT2], tT2);
	return f;
}

Double_t BFitNamespace::T3 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	using namespace TMath;
	static Int_t n;
	static Double_t ST3, tT3, f;
	extern Double_t tCap, tBac, tCyc, t3;
// Needed for 134sb special case
	extern BDNCase_t stBDNCases[FILE_ROWS_BDN]; // This comes from the main program (BFit.cxx)
	extern Int_t iBDNCaseIndex; // This comes from the main program (BFit.cxx)
//	bookGlobals();
	f = 0.0; //catch bad values of t[0]
	if (tBac <= t[0] && t[0] <= tCyc)
	{
		if (!strcmp(stBDNCases[iBDNCaseIndex].pcsCaseCode,"134sb01")) a[gammaT3] = a[gammaT2];
		tT3 = 1.0 / ( 1.0/t3 + a[gammaT3]/1000.0 ); // net variable lifetime (1/e) in ms
		n = Ceil((t[0]-tBac)/tCap);
		ST3 = ( Exp(n*tCap/tT3) - Power(a[rho],n) ) / ( Exp(tCap/tT3) - a[rho] );
		f = a[p] * a[r3] * tCap * ST3 * Exp(-(t[0]-tBac)/tT3);
//		printf("t3 = %f, gammaT3 = %f, tT3 = %f\n", t3, a[gammaT3], tT3);
	}
	return f;
}

Double_t BFitNamespace::U1 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	return V1(t,a) + W1(t,a);
}
Double_t BFitNamespace::U2 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	return V2(t,a) + W2(t,a) + X2(t,a) + Y2(t,a);
}
Double_t BFitNamespace::U3 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	return V3(t,a) + W3(t,a) + X3(t,a) + Y3(t,a);
}

// Functions to plot: (obs. decay rate)x(bin dt) = counts by bin
Double_t BFitNamespace::yDC (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	return a[dt]*a[DC];
}
Double_t BFitNamespace::yT1 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	extern Double_t t1;
//	bookGlobals();
	Double_t tT1 = 1.0 / ( 1.0/t1 + a[gammaT1]/1000.0 ); // net variable lifetime (1/e) in ms
	return a[dt]*a[epsT]*T1(t,a)/t1;
}
Double_t BFitNamespace::yT2 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	extern Double_t t2;
//	bookGlobals();
	Double_t tT2 = 1.0 / ( 1.0/t2 + a[gammaT2]/1000.0 ); // net variable lifetime (1/e) in ms
	return a[dt]*a[epsT]*T2(t,a)/t2;
}
Double_t BFitNamespace::yT3 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	extern Double_t t3;
//	bookGlobals();
	Double_t tT3 = 1.0 / ( 1.0/t3 + a[gammaT3]/1000.0 ); // net variable lifetime (1/e) in ms
	return a[dt]*a[epsT]*T3(t,a)/t3;
}

Double_t BFitNamespace::yU1 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	extern Double_t t1;
//	bookGlobals();
	Double_t tU1 = 1.0 / ( 1.0/t1 + a[gammaU1]/1000.0 ); // net variable lifetime (1/e) in ms
	return a[dt] * ( a[epsV]*V1(t,a) + a[epsW]*W1(t,a) ) / t1;
}
Double_t BFitNamespace::yU2 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	extern Double_t t2;
//	bookGlobals();
	Double_t tU2 = 1.0 / ( 1.0/t2 + a[gammaU2]/1000.0 ); // net variable lifetime (1/e) in ms
	return a[dt] * ( a[epsV]*V2(t,a) + a[epsW]*W2(t,a) + a[epsX]*X2(t,a) + a[epsY]*Y2(t,a) ) / t2;
}
Double_t BFitNamespace::yU3 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	extern Double_t t3;
//	bookGlobals();
	Double_t tU3 = 1.0 / ( 1.0/t3 + a[gammaU3]/1000.0 ); // net variable lifetime (1/e) in ms
	return a[dt] * ( a[epsV]*V3(t,a) + a[epsW]*W3(t,a) + a[epsX]*X3(t,a) + a[epsY]*Y3(t,a) ) / t3;
}
Double_t BFitNamespace::yAll(Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	extern Double_t t1, t2, t3;
//	bookGlobals();
	Double_t tT1 = 1.0 / ( 1.0/t1 + a[gammaT1]/1000.0 ); // net variable lifetime (1/e) in ms
	Double_t tT2 = 1.0 / ( 1.0/t2 + a[gammaT2]/1000.0 ); // net variable lifetime (1/e) in ms
	Double_t tT3 = 1.0 / ( 1.0/t3 + a[gammaT3]/1000.0 ); // net variable lifetime (1/e) in ms
	Double_t tU1 = 1.0 / ( 1.0/t1 + a[gammaU1]/1000.0 ); // net variable lifetime (1/e) in ms
	Double_t tU2 = 1.0 / ( 1.0/t2 + a[gammaU2]/1000.0 ); // net variable lifetime (1/e) in ms
	Double_t tU3 = 1.0 / ( 1.0/t3 + a[gammaU3]/1000.0 ); // net variable lifetime (1/e) in ms
	return a[dt] * ( a[DC] + a[epsT]*(T1(t,a)/t1 + T2(t,a)/t2 + T3(t,a)/t3) + (a[epsV]*V1(t,a) + a[epsW]*W1(t,a))/t1 + (a[epsV]*V2(t,a) + a[epsW]*W2(t,a) + a[epsX]*X2(t,a) + a[epsY]*Y2(t,a))/t2 + (a[epsV]*V3(t,a) + a[epsW]*W3(t,a) + a[epsX]*X3(t,a) + a[epsY]*Y3(t,a))/t3 );
}

// Offset functions to improve visualization: offT1 = yT1 + yDC
Double_t BFitNamespace::oT1 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	extern Double_t t1;
//	bookGlobals();
	Double_t tT1 = 1.0 / ( 1.0/t1 + a[gammaT1]/1000.0 ); // net variable lifetime (1/e) in ms
	return a[dt]*(a[DC] + a[epsT]*T1(t,a)/t1);
}
Double_t BFitNamespace::oT2 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	extern Double_t t2;
//	bookGlobals();
	Double_t tT2 = 1.0 / ( 1.0/t2 + a[gammaT2]/1000.0 ); // net variable lifetime (1/e) in ms
	return a[dt]*(a[DC] + a[epsT]*T2(t,a)/t2);
}
Double_t BFitNamespace::oT3 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	extern Double_t t3;
//	bookGlobals();
	Double_t tT3 = 1.0 / ( 1.0/t3 + a[gammaT3]/1000.0 ); // net variable lifetime (1/e) in ms
	return a[dt]*(a[DC] + a[epsT]*T3(t,a)/t3);
}
Double_t BFitNamespace::oU1 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	extern Double_t t1;
//	bookGlobals();
	Double_t tU1 = 1.0 / ( 1.0/t1 + a[gammaU1]/1000.0 ); // net variable lifetime (1/e) in ms
	return a[dt]*(a[DC] + a[epsU]*U1(t,a)/t1);
}
Double_t BFitNamespace::oU2 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	extern Double_t t2;
//	bookGlobals();
	Double_t tU2 = 1.0 / ( 1.0/t2 + a[gammaU2]/1000.0 ); // net variable lifetime (1/e) in ms
	return a[dt]*(a[DC] + a[epsU]*U2(t,a)/t2);
}
Double_t BFitNamespace::oU3 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	extern Double_t t3;
//	bookGlobals();
	Double_t tU3 = 1.0 / ( 1.0/t3 + a[gammaU3]/1000.0 ); // net variable lifetime (1/e) in ms
	return a[dt]*(a[DC] + a[epsU]*U3(t,a)/t3);
}

// Per-bin rates by component, used for calculating N_beta
Double_t BFitNamespace::rDC (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	return a[DC];
}
Double_t BFitNamespace::rT1 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	extern Double_t t1;
//	bookGlobals();
	Double_t tT1 = 1.0 / ( 1.0/t1 + a[gammaT1]/1000.0 ); // net variable lifetime (1/e) in ms
	return a[epsT]*T1(t,a)/t1;
}
Double_t BFitNamespace::rT2 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	extern Double_t t2;
//	bookGlobals();
	Double_t tT2 = 1.0 / ( 1.0/t2 + a[gammaT2]/1000.0 ); // net variable lifetime (1/e) in ms
	return a[epsT]*T2(t,a)/t2;
}
Double_t BFitNamespace::rT3 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	extern Double_t t3;
//	bookGlobals();
	Double_t tT3 = 1.0 / ( 1.0/t3 + a[gammaT3]/1000.0 ); // net variable lifetime (1/e) in ms
	return a[epsT]*T3(t,a)/t3;
}
Double_t BFitNamespace::rU1 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	extern Double_t t1;
//	bookGlobals();
	Double_t tU1 = 1.0 / ( 1.0/t1 + a[gammaU1]/1000.0 ); // net variable lifetime (1/e) in ms
	return a[epsU]*U1(t,a)/t1;
}
Double_t BFitNamespace::rU2 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	extern Double_t t2;
//	bookGlobals();
	Double_t tU2 = 1.0 / ( 1.0/t2 + a[gammaU2]/1000.0 ); // net variable lifetime (1/e) in ms
	return a[epsU]*U2(t,a)/t2;
}
Double_t BFitNamespace::rU3 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	extern Double_t t3;
//	bookGlobals();
	Double_t tU3 = 1.0 / ( 1.0/t3 + a[gammaU3]/1000.0 ); // net variable lifetime (1/e) in ms
	return a[epsU]*U3(t,a)/t3;
}
Double_t BFitNamespace::rAll (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	extern Double_t t1, t2, t3;
//	bookGlobals();
	Double_t tT1 = 1.0 / ( 1.0/t1 + a[gammaT1]/1000.0 ); // net variable lifetime (1/e) in ms
	Double_t tT2 = 1.0 / ( 1.0/t2 + a[gammaT2]/1000.0 ); // net variable lifetime (1/e) in ms
	Double_t tT3 = 1.0 / ( 1.0/t3 + a[gammaT3]/1000.0 ); // net variable lifetime (1/e) in ms
	Double_t tU1 = 1.0 / ( 1.0/t1 + a[gammaU1]/1000.0 ); // net variable lifetime (1/e) in ms
	Double_t tU2 = 1.0 / ( 1.0/t2 + a[gammaU2]/1000.0 ); // net variable lifetime (1/e) in ms
	Double_t tU3 = 1.0 / ( 1.0/t3 + a[gammaU3]/1000.0 ); // net variable lifetime (1/e) in ms
	return a[DC] + a[epsT]*(T1(t,a)/t1 + T2(t,a)/t2 + T3(t,a)/t3) + a[epsU]*(U1(t,a)/t1 + U2(t,a)/t2 + U3(t,a)/t3);
}

Double_t BFitNamespace::V1 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	using namespace TMath;
	static Int_t n, N;
	static Double_t tT1, tU1, SU1, SU10, v10, v1, V1, f;
	extern Double_t tCap, tBac, tCyc, t1;
//	bookGlobals();
	tT1 = 1.0 / ( 1.0/t1 + a[gammaT1]/1000.0 ); // net variable lifetime (1/e) in ms
	tU1 = 1.0 / ( 1.0/t1 + a[gammaU1]/1000.0 ); // net variable lifetime (1/e) in ms
	f = 0.0; //catch bad values of t[0]
	n = Ceil((t[0]-tBac)/tCap);
	N = Ceil((tCyc-tBac)/tCap);
	SU1  = ( Exp(n*tCap/tU1) - 1 ) / ( Exp(tCap/tU1) - 1 );
	SU10 = ( Exp(N*tCap/tU1) - 1 ) / ( Exp(tCap/tU1) - 1 );
//	D1   = ( Exp(n*tCap/tT1) - 1 ) / ( Exp(tCap/tT1) - 1 ) - ( Exp(n*tCap/tT1) - Power(a[rho],n) ) / ( Exp(tCap/tT1) - a[rho] );
//	D10  = ( Exp(N*tCap/tT1) - 1 ) / ( Exp(tCap/tT1) - 1 ) - ( Exp(N*tCap/tT1) - Power(a[rho],N) ) / ( Exp(tCap/tT1) - a[rho] );
	// Untrapped populations at t=0
	v10 = ( a[r1] * tCap * (1-a[p]) * SU10 * Exp(-(tCyc-tBac)/tU1) ) / ( 1 - Exp(-tCyc/tU1) );
	// Untrapped population during background period
	v1 = v10 * Exp(-t[0]/tU1);
	// Background period
	if (0 <= t[0] && t[0] < tBac) {
		f = v1;
	}
	// Trapping period
	if (tBac <= t[0] && t[0] <= tCyc) {
		// Untrapped populations during trapping
		V1 = a[r1] * tCap * (1-a[p]) * SU1 * Exp(-(t[0]-tBac)/tU1);
		f = v1+V1;
	}
	return f;
}

Double_t BFitNamespace::V2 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	using namespace TMath;
	static Int_t n, N;
	static Double_t tT2, tU2, SU2, SU20, v20, v2, V2, f;
	extern Double_t tCap, tBac, tCyc, t2;
//	bookGlobals();
	tT2 = 1.0 / ( 1.0/t2 + a[gammaT2]/1000.0 ); // net variable lifetime (1/e) in ms
	tU2 = 1.0 / ( 1.0/t2 + a[gammaU2]/1000.0 ); // net variable lifetime (1/e) in ms
	f = 0.0; //catch bad values of t[0]
	n = Ceil((t[0]-tBac)/tCap);
	N = Ceil((tCyc-tBac)/tCap);
	SU2  = ( Exp(n*tCap/tU2) - 1 ) / ( Exp(tCap/tU2) - 1 );
	SU20 = ( Exp(N*tCap/tU2) - 1 ) / ( Exp(tCap/tU2) - 1 );
//	D2   = ( Exp(n*tCap/tT2) - 1 ) / ( Exp(tCap/tT2) - 1 ) - ( Exp(n*tCap/tT2) - Power(a[rho],n) ) / ( Exp(tCap/tT2) - a[rho] );
//	D20  = ( Exp(N*tCap/tT2) - 1 ) / ( Exp(tCap/tT2) - 1 ) - ( Exp(N*tCap/tT2) - Power(a[rho],N) ) / ( Exp(tCap/tT2) - a[rho] );
	// Untrapped populations at t=0
	v20 = ( a[r2] * tCap * (1-a[p]) * SU20 * Exp(-(tCyc-tBac)/tU2) ) / ( 1 - Exp(-tCyc/tU2) );
	// Untrapped population during background period
	v2 = v20 * Exp(-t[0]/tU2);
	// Background period
	if (0 <= t[0] && t[0] < tBac) {
		f = v2;
	}
	// Trapping period
	if (tBac <= t[0] && t[0] <= tCyc) {
		// Untrapped populations during trapping
		V2 = a[r2] * tCap * (1-a[p]) * SU2 * Exp(-(t[0]-tBac)/tU2);
		f = v2+V2;
	}
	return f;
}

Double_t BFitNamespace::V3 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	using namespace TMath;
	static Int_t n, N;
	static Double_t tT3, tU3, SU3, SU30, v30, v3, V3, f;
	extern Double_t tCap, tBac, tCyc, t3;
//	bookGlobals();
	tT3 = 1.0 / ( 1.0/t3 + a[gammaT3]/1000.0 ); // net variable lifetime (1/e) in ms
	tU3 = 1.0 / ( 1.0/t3 + a[gammaU3]/1000.0 ); // net variable lifetime (1/e) in ms
	f = 0.0; //catch bad values of t[0]
	n = Ceil((t[0]-tBac)/tCap);
	N = Ceil((tCyc-tBac)/tCap);
	SU3  = ( Exp(n*tCap/tU3) - 1 ) / ( Exp(tCap/tU3) - 1 );
	SU30 = ( Exp(N*tCap/tU3) - 1 ) / ( Exp(tCap/tU3) - 1 );
//	D3   = ( Exp(n*tCap/tT3) - 1 ) / ( Exp(tCap/tT3) - 1 ) - ( Exp(n*tCap/tT3) - Power(a[rho],n) ) / ( Exp(tCap/tT3) - a[rho] );
//	D30  = ( Exp(N*tCap/tT3) - 1 ) / ( Exp(tCap/tT3) - 1 ) - ( Exp(N*tCap/tT3) - Power(a[rho],N) ) / ( Exp(tCap/tT3) - a[rho] );
	// Untrapped populations at t=0
	v30 = ( a[r3] * tCap * (1-a[p]) * SU30 * Exp(-(tCyc-tBac)/tU3) ) / ( 1 - Exp(-tCyc/tU3) );
	// Untrapped population during background period
	v3 = v30 * Exp(-t[0]/tU3);
	// Background period
	if (0 <= t[0] && t[0] < tBac) {
		f = v3;
	}
	// Trapping period
	if (tBac <= t[0] && t[0] <= tCyc) {
		// Untrapped populations during trapping
		V3 = a[r3] * tCap * (1-a[p]) * SU3 * Exp(-(t[0]-tBac)/tU3);
		f = v3+V3;
	}
	return f;
}

Double_t BFitNamespace::yV1 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	extern Double_t t1;
//	bookGlobals();
	Double_t tU1 = 1.0 / ( 1.0/t1 + a[gammaU1]/1000.0 ); // net variable lifetime (1/e) in ms
	return a[dt]*a[epsV]*V1(t,a)/t1;
}
Double_t BFitNamespace::yV2 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	extern Double_t t2;
//	bookGlobals();
	Double_t tU2 = 1.0 / ( 1.0/t2 + a[gammaU2]/1000.0 ); // net variable lifetime (1/e) in ms
	return a[dt]*a[epsV]*V2(t,a)/t2;
}
Double_t BFitNamespace::yV3 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	extern Double_t t3;
//	bookGlobals();
	Double_t tU3 = 1.0 / ( 1.0/t3 + a[gammaU3]/1000.0 ); // net variable lifetime (1/e) in ms
	return a[dt]*a[epsV]*V3(t,a)/t3;
}

// W populations
Double_t BFitNamespace::W1 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	using namespace TMath;
	static Int_t n, N;
	static Double_t tT1, tU1, D1, D10, w10, w1, W1, f;
	extern Double_t tCap, tBac, tCyc, t1;
//	bookGlobals();
	tT1 = 1.0 / ( 1.0/t1 + a[gammaT1]/1000.0 ); // net variable lifetime (1/e) in ms
	tU1 = 1.0 / ( 1.0/t1 + a[gammaU1]/1000.0 ); // net variable lifetime (1/e) in ms
	f = 0.0; //catch bad values of t[0]
	n = Ceil((t[0]-tBac)/tCap);
	N = Ceil((tCyc-tBac)/tCap);
//	SU1  = ( Exp(n*tCap/tU1) - 1 ) / ( Exp(tCap/tU1) - 1 );
//	SU10 = ( Exp(N*tCap/tU1) - 1 ) / ( Exp(tCap/tU1) - 1 );
	D1   = ( Exp(n*tCap/tT1) - 1 ) / ( Exp(tCap/tT1) - 1 ) - ( Exp(n*tCap/tT1) - Power(a[rho],n) ) / ( Exp(tCap/tT1) - a[rho] );
	D10  = ( Exp(N*tCap/tT1) - 1 ) / ( Exp(tCap/tT1) - 1 ) - ( Exp(N*tCap/tT1) - Power(a[rho],N) ) / ( Exp(tCap/tT1) - a[rho] );
	// Untrapped populations at t=0
	w10 = ( a[r1] * tCap * a[p] * D10 * Exp(-(tCyc-tBac)/tU1) ) / ( 1 - Exp(-tCyc/tU1) );
	// Untrapped population during background period
	w1 = w10 * Exp(-t[0]/tU1);
	// Background period
	if (0 <= t[0] && t[0] < tBac) {
		f = w1;
	}
	// Trapping period
	if (tBac <= t[0] && t[0] <= tCyc) {
		// Untrapped populations during trapping
		W1 = a[r1] * tCap * a[p] * D1 * Exp(-(t[0]-tBac)/tU1);
		f = w1 + W1;
	}
	return f;
}
Double_t BFitNamespace::W2 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	using namespace TMath;
	static Int_t n, N;
	static Double_t tT2, tU2, D2, D20, w20, w2, W2, f;
	extern Double_t tCap, tBac, tCyc, t2;
//	bookGlobals();
	tT2 = 1.0 / ( 1.0/t2 + a[gammaT2]/1000.0 ); // net variable lifetime (1/e) in ms
	tU2 = 1.0 / ( 1.0/t2 + a[gammaU2]/1000.0 ); // net variable lifetime (1/e) in ms
	f = 0.0; //catch bad values of t[0]
	n = Ceil((t[0]-tBac)/tCap);
	N = Ceil((tCyc-tBac)/tCap);
//	SU2  = ( Exp(n*tCap/tU2) - 1 ) / ( Exp(tCap/tU2) - 1 );
//	SU20 = ( Exp(N*tCap/tU2) - 1 ) / ( Exp(tCap/tU2) - 1 );
	D2   = ( Exp(n*tCap/tT2) - 1 ) / ( Exp(tCap/tT2) - 1 ) - ( Exp(n*tCap/tT2) - Power(a[rho],n) ) / ( Exp(tCap/tT2) - a[rho] );
	D20  = ( Exp(N*tCap/tT2) - 1 ) / ( Exp(tCap/tT2) - 1 ) - ( Exp(N*tCap/tT2) - Power(a[rho],N) ) / ( Exp(tCap/tT2) - a[rho] );
	// Untrapped populations at t=0
	w20 = ( a[r2] * tCap * a[p] * D20 * Exp(-(tCyc-tBac)/tU2) ) / ( 1 - Exp(-tCyc/tU2) );
	// Untrapped population during background period
	w2 = w20 * Exp(-t[0]/tU2);
	// Background period
	if (0 <= t[0] && t[0] < tBac) {
		f = w2;
	}
	// Trapping period
	if (tBac <= t[0] && t[0] <= tCyc) {
		// Untrapped populations during trapping
		W2 = a[r2] * tCap * a[p] * D2 * Exp(-(t[0]-tBac)/tU2);
		f = w2 + W2;
	}
	return f;
}
Double_t BFitNamespace::W3 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	using namespace TMath;
	static Int_t n, N;
	static Double_t tT3, tU3, D3, D30, w30, w3, W3, f;
	extern Double_t tCap, tBac, tCyc, t3;
//	bookGlobals();
	tT3 = 1.0 / ( 1.0/t3 + a[gammaT3]/1000.0 ); // net variable lifetime (1/e) in ms
	tU3 = 1.0 / ( 1.0/t3 + a[gammaU3]/1000.0 ); // net variable lifetime (1/e) in ms
	f = 0.0; //catch bad values of t[0]
	n = Ceil((t[0]-tBac)/tCap);
	N = Ceil((tCyc-tBac)/tCap);
//	SU3  = ( Exp(n*tCap/tU3) - 1 ) / ( Exp(tCap/tU3) - 1 );
//	SU30 = ( Exp(N*tCap/tU3) - 1 ) / ( Exp(tCap/tU3) - 1 );
	D3   = ( Exp(n*tCap/tT3) - 1 ) / ( Exp(tCap/tT3) - 1 ) - ( Exp(n*tCap/tT3) - Power(a[rho],n) ) / ( Exp(tCap/tT3) - a[rho] );
	D30  = ( Exp(N*tCap/tT3) - 1 ) / ( Exp(tCap/tT3) - 1 ) - ( Exp(N*tCap/tT3) - Power(a[rho],N) ) / ( Exp(tCap/tT3) - a[rho] );
	// Untrapped populations at t=0
	w30 = ( a[r3] * tCap * a[p] * D30 * Exp(-(tCyc-tBac)/tU3) ) / ( 1 - Exp(-tCyc/tU3) );
	// Untrapped population during background period
	w3 = w30 * Exp(-t[0]/tU3);
	// Background period
	if (0 <= t[0] && t[0] < tBac) {
		f = w3;
	}
	// Trapping period
	if (tBac <= t[0] && t[0] <= tCyc) {
		// Untrapped populations during trapping
		W3 = a[r3] * tCap * a[p] * D3 * Exp(-(t[0]-tBac)/tU3);
		f = w3 + W3;
	}
	return f;
}
Double_t BFitNamespace::yW1 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	extern Double_t tCap, tBac, tCyc, t1;
//	bookGlobals();
	Double_t tU1 = 1.0 / ( 1.0/t1 + a[gammaU1]/1000.0 ); // net variable lifetime (1/e) in ms
	return a[dt]*a[epsW]*W1(t,a)/t1;
}
Double_t BFitNamespace::yW2 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	extern Double_t tCap, tBac, tCyc, t2;
//	bookGlobals();
	Double_t tU2 = 1.0 / ( 1.0/t2 + a[gammaU2]/1000.0 ); // net variable lifetime (1/e) in ms
	return a[dt]*a[epsW]*W2(t,a)/t2;
}
Double_t BFitNamespace::yW3 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	extern Double_t t3;
//	bookGlobals();
	Double_t tU3 = 1.0 / ( 1.0/t3 + a[gammaU3]/1000.0 ); // net variable lifetime (1/e) in ms
	return a[dt]*a[epsW]*W3(t,a)/t3;
}

Double_t BFitNamespace::X2 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	using namespace TMath;
	static Int_t n, N;
	static Double_t tT1, tT2, tU1, tU2, ST1, ST10, SU2, SU20, x20, x2, X2, f;
	extern Double_t tCap, tBac, tCyc, t1, t2, t3;
//	bookGlobals();
	tT1 = 1.0 / ( 1.0/t1 + a[gammaT1]/1000.0 ); // net variable lifetime (1/e) in ms
	tU1 = 1.0 / ( 1.0/t1 + a[gammaU1]/1000.0 ); // net variable lifetime (1/e) in ms
	tT2 = 1.0 / ( 1.0/t2 + a[gammaT2]/1000.0 ); // net variable lifetime (1/e) in ms
	tU2 = 1.0 / ( 1.0/t2 + a[gammaU2]/1000.0 ); // net variable lifetime (1/e) in ms
	f = 0.0; //catch bad values of t[0]
	n = Ceil((t[0]-tBac)/tCap);
	N = Ceil((tCyc-tBac)/tCap);
	ST1  = ( Exp(n*tCap/tT1) - 1 ) / ( Exp(tCap/tT1) - 1 );
	ST10 = ( Exp(N*tCap/tT1) - 1 ) / ( Exp(tCap/tT1) - 1 );
	SU2  = ( Exp(n*tCap/tU2) - 1 ) / ( Exp(tCap/tU2) - 1 );
	SU20 = ( Exp(N*tCap/tU2) - 1 ) / ( Exp(tCap/tU2) - 1 );
	// Untrapped populations at t=0
	x20 = ( a[r1] * tCap * a[p] * tT1/t1 * tU2/(tU2-tT1) * ( SU20 * Exp(-(tCyc-tBac)/tU2) - ST10 * Exp(-(tCyc-tBac)/tT1) ) ) / ( 1 - Exp(-tCyc/tU2) );
	// Untrapped population during background period
	x2 = x20*Exp(-t[0]/tU2) ;
	// Background period
	if (0 <= t[0] && t[0] < tBac) {
		f = x2;
	}
	// Trapping period
	if (tBac <= t[0] && t[0] <= tCyc) {
		// Untrapped populations during trapping
		X2 = a[r1] * tCap * a[p] * tT1/t1 * tU2/(tU2-tT1) * ( SU2 * Exp(-(t[0]-tBac)/tU2) - ST1 * Exp(-(t[0]-tBac)/tT1) );
		f = x2 + X2;
	}
	return f;
}

Double_t BFitNamespace::X3 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	using namespace TMath;
	static Int_t n, N;
	static Double_t tT2, tT3, tU2, tU3, ST2, ST20, SU3, SU30, x30, x3, X3, f;
	extern Double_t tCap, tBac, tCyc, t1, t2, t3;
//	bookGlobals();
	tT2 = 1.0 / ( 1.0/t2 + a[gammaT2]/1000.0 ); // net variable lifetime (1/e) in ms
	tU2 = 1.0 / ( 1.0/t2 + a[gammaU2]/1000.0 ); // net variable lifetime (1/e) in ms
	tT3 = 1.0 / ( 1.0/t3 + a[gammaT3]/1000.0 ); // net variable lifetime (1/e) in ms
	tU3 = 1.0 / ( 1.0/t3 + a[gammaU3]/1000.0 ); // net variable lifetime (1/e) in ms
	f = 0.0; //catch bad values of t[0]
	n = Ceil((t[0]-tBac)/tCap);
	N = Ceil((tCyc-tBac)/tCap);
	ST2  = ( Exp(n*tCap/tT2) - 1 ) / ( Exp(tCap/tT2) - 1 );
	ST20 = ( Exp(N*tCap/tT2) - 1 ) / ( Exp(tCap/tT2) - 1 );
	SU3  = ( Exp(n*tCap/tU3) - 1 ) / ( Exp(tCap/tU3) - 1 );
	SU30 = ( Exp(N*tCap/tU3) - 1 ) / ( Exp(tCap/tU3) - 1 );
	// Untrapped populations at t=0
	x30 = ( a[r2] * tCap * a[p] * tT2/t2 * tU3/(tU3-tT2) * ( SU30 * Exp(-(tCyc-tBac)/tU3) - ST20 * Exp(-(tCyc-tBac)/tT2) ) ) / ( 1 - Exp(-tCyc/tU3) );
	// Untrapped population during background period
	x3 = x30 * Exp(-t[0]/tU3);
	// Background period
	if (0 <= t[0] && t[0] < tBac) {
		f = x3;
	}
	// Trapping period
	if (tBac <= t[0] && t[0] <= tCyc) {
		// Untrapped populations during trapping
		X3 = a[r2] * tCap * a[p] * tT2/t2 * tU3/(tU3-tT2) * ( SU3 * Exp(-(t[0]-tBac)/tU3) - ST2 * Exp(-(t[0]-tBac)/tT2) );
		f = x3 + X3;
	}
	return f;
}

Double_t BFitNamespace::yX2 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	extern Double_t tCap, tBac, tCyc, t1, t2, t3;
//	bookGlobals();
	Double_t tU2 = 1.0 / ( 1.0/t2 + a[gammaU2]/1000.0 ); // net variable lifetime (1/e) in ms
	return a[dt]*a[epsX]*X2(t,a)/t2;
}
Double_t BFitNamespace::yX3 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	extern Double_t tCap, tBac, tCyc, t1, t2, t3;
//	bookGlobals();
	Double_t tU3 = 1.0 / ( 1.0/t3 + a[gammaU3]/1000.0 ); // net variable lifetime (1/e) in ms
	return a[dt]*a[epsX]*X3(t,a)/t3;
}

Double_t BFitNamespace::Y2 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	using namespace TMath;
	static Int_t n, N;
	static Double_t tT1, tT2, tU1, tU2, ST1, ST10, SU1, SU10, SU2, SU20, y10, y20, y2, Y2, f;
	extern Double_t tCap, tBac, tCyc, t1, t2, t3;
//	bookGlobals();
	tT1 = 1.0 / ( 1.0/t1 + a[gammaT1]/1000.0 ); // net variable lifetime (1/e) in ms
	tU1 = 1.0 / ( 1.0/t1 + a[gammaU1]/1000.0 ); // net variable lifetime (1/e) in ms
	tT2 = 1.0 / ( 1.0/t2 + a[gammaT2]/1000.0 ); // net variable lifetime (1/e) in ms
	tU2 = 1.0 / ( 1.0/t2 + a[gammaU2]/1000.0 ); // net variable lifetime (1/e) in ms
	f = 0.0; //catch bad values of t[0]
	n = Ceil((t[0]-tBac)/tCap);
	N = Ceil((tCyc-tBac)/tCap);
//	ST1  = ( Exp(n*tCap/tT1) - 1 ) / ( Exp(tCap/tT1) - 1 );
//	ST10 = ( Exp(N*tCap/tT1) - 1 ) / ( Exp(tCap/tT1) - 1 );
	SU1  = ( Exp(n*tCap/tU1) - 1 ) / ( Exp(tCap/tU1) - 1 );
	SU10 = ( Exp(N*tCap/tU1) - 1 ) / ( Exp(tCap/tU1) - 1 );
	SU2  = ( Exp(n*tCap/tU2) - 1 ) / ( Exp(tCap/tU2) - 1 );
	SU20 = ( Exp(N*tCap/tU2) - 1 ) / ( Exp(tCap/tU2) - 1 );
	
	// Untrapped populations at t=0
	y10 = a[r1] * tCap * (1-a[p]) * SU10 * Exp(-(tCyc-tBac)/tU1) / ( 1 - Exp(-tCyc/tU1) );
	y20 = ( y10 * tU1/t1 * tU2/(tU2-tU1) * ( Exp(-tCyc/tU2) - Exp(-tCyc/tU1) ) + a[r1] * tCap * (1-a[p]) * tU1/t1 * tU2/(tU2-tU1) * ( SU20 * Exp(-(tCyc-tBac)/tU2) - SU10 * Exp(-(tCyc-tBac)/tU1) ) ) / (1-Exp(-tCyc/tU2) );
	// Untrapped population during background period
	y2 = y20 * Exp(-t[0]/tU2) + y10 * tU1/t1 * tU2/(tU2-tU1) * ( Exp(-t[0]/tU2) - Exp(-t[0]/tU1 ) );
	// Background period
	if (0 <= t[0] && t[0] < tBac) {
		f = y2;
	}
	// Trapping period
	if (tBac <= t[0] && t[0] <= tCyc) {
		// Untrapped populations during trapping
		Y2 = a[r1] * tCap * (1-a[p]) * tU1/t1 * tU2/(tU2-tU1) * ( SU2 * Exp(-(t[0]-tBac)/tU2) - SU1 * Exp(-(t[0]-tBac)/tU1) );
		f = y2 + Y2;
	}
	return f;
}

Double_t BFitNamespace::Y3 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	using namespace TMath;
	static Int_t n, N;
	static Double_t tT1, tT2, tT3, tU1, tU2, tU3, AU, ST1, ST2, ST3, ST10, ST20, ST30, SU1, SU2, SU3, SU10, SU20, SU30, y10, y20, y30, y3, Y3, f;
	extern Double_t tCap, tBac, tCyc, t1, t2, t3;
//	bookGlobals();
	tT1 = 1.0 / ( 1.0/t1 + a[gammaT1]/1000.0 ); // net variable lifetime (1/e) in ms
	tU1 = 1.0 / ( 1.0/t1 + a[gammaU1]/1000.0 ); // net variable lifetime (1/e) in ms
	tT2 = 1.0 / ( 1.0/t2 + a[gammaT2]/1000.0 ); // net variable lifetime (1/e) in ms
	tU2 = 1.0 / ( 1.0/t2 + a[gammaU2]/1000.0 ); // net variable lifetime (1/e) in ms
	tT3 = 1.0 / ( 1.0/t3 + a[gammaT3]/1000.0 ); // net variable lifetime (1/e) in ms
	tU3 = 1.0 / ( 1.0/t3 + a[gammaU3]/1000.0 ); // net variable lifetime (1/e) in ms
	AU  = (tU3-tU2) * (tU3-tU1) * (tU2-tU1);
	f = 0.0; //catch bad values of t[0]
	n = Ceil((t[0]-tBac)/tCap);
	N = Ceil((tCyc-tBac)/tCap);
	SU1  = ( Exp(n*tCap/tU1) - 1 ) / ( Exp(tCap/tU1) - 1 );
	SU2  = ( Exp(n*tCap/tU2) - 1 ) / ( Exp(tCap/tU2) - 1 );
	SU3  = ( Exp(n*tCap/tU3) - 1 ) / ( Exp(tCap/tU3) - 1 );
	SU10 = ( Exp(N*tCap/tU1) - 1 ) / ( Exp(tCap/tU1) - 1 );
	SU20 = ( Exp(N*tCap/tU2) - 1 ) / ( Exp(tCap/tU2) - 1 );
	SU30 = ( Exp(N*tCap/tU3) - 1 ) / ( Exp(tCap/tU3) - 1 );
	// Untrapped populations at t=0
	y10 = 
		a[r1] * tCap * (1-a[p]) * SU10 * Exp(-(tCyc-tBac)/tU1) / ( 1 - Exp(-tCyc/tU1) );
	y20 = (
		y10 * tU1/t1 * tU2/(tU2-tU1) * ( Exp(-tCyc/tU2) - Exp(-tCyc/tU1) ) +
		a[r2] * tCap * (1-a[p]) *            SU20*Exp(-(tCyc-tBac)/tU2) + 
		a[r1] * tCap * (1-a[p]) * tU1/t1 * tU2/(tU2-tU1) * (SU20 * Exp(-(tCyc-tBac)/tU2) - SU10 * Exp(-(tCyc-tBac)/tU1) )
		)
		/ ( 1 - Exp(-tCyc/tU2) );
	y30 = (
		y20 * tU2/t2 * tU3/(tU3-tU2) * ( Exp(-tCyc/tU3) - Exp(-tCyc/tU2) ) + 
		y10 * tU1/t1 * tU2/t2 * tU3/AU * ( tU1 * (tU3-tU2) * Exp(-tCyc/tU1) - tU2 * (tU3-tU1) * Exp(-tCyc/tU2) + tU3 * (tU2-tU1) * Exp(-tCyc/tU3) ) + 
//		a[r3]*tCap*(1-a[p])*                 S30*Exp(-(tCyc-tBac)/t3) + 
		a[r2] * tCap * (1-a[p]) * tU2/t2 * tU3/(tU3-tU2) *     (SU30*Exp(-(tCyc-tBac)/tU3) -            SU20*Exp(-(tCyc-tBac)/tU2)) + 
		a[r1] * tCap * (1-a[p]) * tU1/t1 * tU2/t2 * tU3/AU * ( tU1 * (tU3-tU2) * SU10 * Exp(-(tCyc-tBac)/tU1) - tU2 * (tU3-tU1) * SU20 * Exp(-(tCyc-tBac)/tU2) + tU3 * (tU2-tU1) * SU30 * Exp(-(tCyc-tBac)/tU3) )
		)
		/ ( 1 - Exp(-tCyc/tU3) );
	// Untrapped population during background period
	y3 = 
		y30 * Exp(-t[0]/tU3) + 
		y20 * tU2/t2 * tU3/(tU3-tU2) * ( Exp(-t[0]/tU3) - Exp(-t[0]/tU2) ) + 
		y10 * tU1/t1 * tU2/t2 * tU3/AU * ( tU1 * (tU3-tU2) * Exp(-t[0]/tU1) - tU2 * (tU3-tU1) * Exp(-t[0]/tU2) + tU3 * (tU2-tU1) * Exp(-t[0]/tU3) );
	// Background period
	if (0 <= t[0] && t[0] < tBac) {
		f = y3;
	}
	// Trapping period
	if (tBac <= t[0] && t[0] <= tCyc) {
		// Untrapped populations during trapping
		Y3 = 
			a[r2] * tCap * (1-a[p]) * tU2/t2 * tU3/(tU3-tU2) * ( SU3 * Exp(-(t[0]-tBac)/tU3) - SU2 * Exp(-(t[0]-tBac)/tU2) ) + 
			a[r1] * tCap * (1-a[p]) * tU1/t1 * tU2/t2 * tU3/AU * ( tU1 * (tU3-tU2) * SU1 * Exp(-(t[0]-tBac)/tU1) - tU2 * (tU3-tU1) * SU2 * Exp(-(t[0]-tBac)/tU2) + tU3 * (tU2-tU1) * SU3 * Exp(-(t[0]-tBac)/tU3) );
		f = y3 + Y3;
	}
	return f;
}

Double_t BFitNamespace::yY2 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	extern Double_t tCap, tBac, tCyc, t1, t2, t3;
//	bookGlobals();
	Double_t tU2 = 1.0 / ( 1.0/t2 + a[gammaU2]/1000.0 ); // net variable lifetime (1/e) in ms
	return a[dt]*a[epsY]*Y2(t,a)/t2;
}
Double_t BFitNamespace::yY3 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	extern Double_t tCap, tBac, tCyc, t1, t2, t3;
//	bookGlobals();
	Double_t tU3 = 1.0 / ( 1.0/t3 + a[gammaU3]/1000.0 ); // net variable lifetime (1/e) in ms
	return a[dt]*a[epsY]*Y3(t,a)/t3;
}

/*
Double_t BFitNamespace::T1 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	using namespace TMath;
	static Int_t gdx;
	static const Double_t tCap = bdn_cases[gdx].T_capt;
	static const Double_t tBac = bdn_cases[gdx].T_bkgd;
	static const Double_t T  = bdn_cases[gdx].T_cycle;
	static Int_t n;
	static Double_t ST1, tT1, f;
	f = 0.0; //catch bad values of t[0]
	if (tBac <= t[0] && t[0] <= T)
	{
		tT1 = a[tauT1];
		n = Ceil((t[0]-tBac)/tCap);
		ST1 = ( Exp(n*tCap/tT1) - Power(a[rho],n) ) / ( Exp(tCap/tT1) - a[rho] );
		f = a[p] * a[r1] * tCap * ST1 * Exp(-(t[0]-tBac)/tT1);
	}
	return f;
}

Double_t BFitNamespace::T2 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	using namespace TMath;
	static Int_t gdx;
	static const Double_t tCap = bdn_cases[gdx].T_capt;
	static const Double_t tBac = bdn_cases[gdx].T_bkgd;
	static const Double_t T  = bdn_cases[gdx].T_cycle;
	static Int_t n;
	static Double_t ST2, tT2, f;
	f = 0.0; //catch bad values of t[0]
	if (tBac <= t[0] && t[0] <= T)
	{
		tT2 = a[tauT2];
		n = Ceil((t[0]-tBac)/tCap);
		ST2 = ( Exp(n*tCap/tT2) - Power(a[rho],n) ) / ( Exp(tCap/tT2) - a[rho] );
		f = a[p] * a[r2] * tCap * ST2 * Exp(-(t[0]-tBac)/tT2);
	}
	return f;
}

Double_t BFitNamespace::T3 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	using namespace TMath;
	static Int_t n;
	static Double_t ST3, tT3, f;
	static Int_t gdx;
	static const Double_t tCap = bdn_cases[gdx].T_capt;
	static const Double_t tBac = bdn_cases[gdx].T_bkgd;
	static const Double_t T  = bdn_cases[gdx].T_cycle;
	f = 0.0; //catch bad values of t[0]
	if (tBac <= t[0] && t[0] <= T)
	{
		tT3 = a[tauT3];
		n = Ceil((t[0]-tBac)/tCap);
		ST3 = ( Exp(n*tCap/tT3) - Power(a[rho],n) ) / ( Exp(tCap/tT3) - a[rho] );
		f = a[p] * a[r3] * tCap * ST3 * Exp(-(t[0]-tBac)/tT3);
	}
	return f;
}

Double_t BFitNamespace::U1 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	return V1(t,a) + W1(t,a);
}
Double_t BFitNamespace::U2 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	return V2(t,a) + W2(t,a) + X2(t,a) + Y2(t,a);
}
Double_t BFitNamespace::U3 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	return V3(t,a) + W3(t,a) + X3(t,a) + Y3(t,a);
}

// Functions to plot: (obs. decay rate)x(bin dt) = counts by bin
Double_t BFitNamespace::yDC (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	return a[dt]*a[DC];
}
Double_t BFitNamespace::yT1 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	return a[dt]*a[epsT]*T1(t,a)/a[tauT1];
}
Double_t BFitNamespace::yT2 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	return a[dt]*a[epsT]*T2(t,a)/a[tauT2];
}
Double_t BFitNamespace::yT3 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	return a[dt]*a[epsT]*T3(t,a)/a[tauT3];
}

Double_t BFitNamespace::yU1 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	return a[dt] * ( a[epsV]*V1(t,a) + a[epsW]*W1(t,a) ) / a[tauU1];
}
Double_t BFitNamespace::yU2 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	return a[dt] * ( a[epsV]*V2(t,a) + a[epsW]*W2(t,a) + a[epsX]*X2(t,a) + a[epsY]*Y2(t,a) ) / a[tauU2];
}
Double_t BFitNamespace::yU3 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	return a[dt] * ( a[epsV]*V3(t,a) + a[epsW]*W3(t,a) + a[epsX]*X3(t,a) + a[epsY]*Y3(t,a) ) / a[tauU3];
}
Double_t BFitNamespace::yAll(Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	return a[dt] * ( a[DC] + a[epsT]*(T1(t,a)/a[tauT1] + T2(t,a)/a[tauT2] + T3(t,a)/a[tauT3]) + (a[epsV]*V1(t,a) + a[epsW]*W1(t,a))/a[tauU1] + (a[epsV]*V2(t,a) + a[epsW]*W2(t,a) + a[epsX]*X2(t,a) + a[epsY]*Y2(t,a))/a[tauU2] + (a[epsV]*V3(t,a) + a[epsW]*W3(t,a) + a[epsX]*X3(t,a) + a[epsY]*Y3(t,a))/a[tauU3] );
}

// Offset functions to imporve visualization: offT1 = yT1 + yDC
Double_t BFitNamespace::oT1 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	return a[dt]*(a[DC] + a[epsT]*T1(t,a)/a[tauT1]);
}
Double_t BFitNamespace::oT2 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	return a[dt]*(a[DC] + a[epsT]*T2(t,a)/a[tauT2]);
}
Double_t BFitNamespace::oT3 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	return a[dt]*(a[DC] + a[epsT]*T3(t,a)/a[tauT3]);
}
Double_t BFitNamespace::oU1 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	return a[dt]*(a[DC] + a[epsU]*U1(t,a)/a[tauU1]);
}
Double_t BFitNamespace::oU2 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	return a[dt]*(a[DC] + a[epsU]*U2(t,a)/a[tauU2]);
}
Double_t BFitNamespace::oU3 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	return a[dt]*(a[DC] + a[epsU]*U3(t,a)/a[tauU3]);
}

// Per-bin rates by component, used for calculating N_beta
Double_t BFitNamespace::rDC (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	return a[DC];
}
Double_t BFitNamespace::rT1 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	return a[epsT]*T1(t,a)/a[tauT1];
}
Double_t BFitNamespace::rT2 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	return a[epsT]*T2(t,a)/a[tauT2];
}
Double_t BFitNamespace::rT3 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	return a[epsT]*T3(t,a)/a[tauT3];
}
Double_t BFitNamespace::rU1 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	return a[epsU]*U1(t,a)/a[tauU1];
}
Double_t BFitNamespace::rU2 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	return a[epsU]*U2(t,a)/a[tauU2];
}
Double_t BFitNamespace::rU3 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	return a[epsU]*U3(t,a)/a[tauU3];
}
Double_t BFitNamespace::rAll (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	return a[DC] + a[epsT]*(T1(t,a)/a[tauT1] + T2(t,a)/a[tauT2] + T3(t,a)/a[tauT3]) + a[epsU]*(U1(t,a)/a[tauU1] + U2(t,a)/a[tauU2] + U3(t,a)/a[tauU3]);
}

Double_t BFitNamespace::V1 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	using namespace TMath;
	static Int_t n, N;
	static Double_t tT1, tU1, SU1, SU10, v10, v1, V1, f;
	static Int_t gdx;
	static const Double_t tCap = bdn_cases[gdx].T_capt;
	static const Double_t tBac = bdn_cases[gdx].T_bkgd;
	static const Double_t T  = bdn_cases[gdx].T_cycle;
	tT1 = a[tauT1];
	tU1 = a[tauU1];
	f = 0.0; //catch bad values of t[0]
	n = Ceil((t[0]-tBac)/tCap);
	N = Ceil(   (T-tBac)/tCap);
	SU1  = ( Exp(n*tCap/tU1) - 1 ) / ( Exp(tCap/tU1) - 1 );
	SU10 = ( Exp(N*tCap/tU1) - 1 ) / ( Exp(tCap/tU1) - 1 );
//	D1   = ( Exp(n*tCap/tT1) - 1 ) / ( Exp(tCap/tT1) - 1 ) - ( Exp(n*tCap/tT1) - Power(a[rho],n) ) / ( Exp(tCap/tT1) - a[rho] );
//	D10  = ( Exp(N*tCap/tT1) - 1 ) / ( Exp(tCap/tT1) - 1 ) - ( Exp(N*tCap/tT1) - Power(a[rho],N) ) / ( Exp(tCap/tT1) - a[rho] );
	// Untrapped populations at t=0
	v10 = ( a[r1] * tCap * (1-a[p]) * SU10 * Exp(-(T-tBac)/tU1) ) / ( 1 - Exp(-T/tU1) );
	// Untrapped population during background period
	v1 = v10 * Exp(-t[0]/tU1);
	// Background period
	if (0 <= t[0] && t[0] < tBac) {
		f = v1;
	}
	// Trapping period
	if (tBac <= t[0] && t[0] <= T) {
		// Untrapped populations during trapping
		V1 = a[r1] * tCap * (1-a[p]) * SU1 * Exp(-(t[0]-tBac)/tU1);
		f = v1+V1;
	}
	return f;
}

Double_t BFitNamespace::V2 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	using namespace TMath;
	static Int_t n, N;
	static Double_t tT2, tU2, SU2, SU20, v20, v2, V2, f;
	static Int_t gdx;
	static const Double_t tCap = bdn_cases[gdx].T_capt;
	static const Double_t tBac = bdn_cases[gdx].T_bkgd;
	static const Double_t T  = bdn_cases[gdx].T_cycle;
	tT2 = a[tauT2];
	tU2 = a[tauU2];
	f = 0.0; //catch bad values of t[0]
	n = Ceil((t[0]-tBac)/tCap);
	N = Ceil(   (T-tBac)/tCap);
	SU2  = ( Exp(n*tCap/tU2) - 1 ) / ( Exp(tCap/tU2) - 1 );
	SU20 = ( Exp(N*tCap/tU2) - 1 ) / ( Exp(tCap/tU2) - 1 );
//	D2   = ( Exp(n*tCap/tT2) - 1 ) / ( Exp(tCap/tT2) - 1 ) - ( Exp(n*tCap/tT2) - Power(a[rho],n) ) / ( Exp(tCap/tT2) - a[rho] );
//	D20  = ( Exp(N*tCap/tT2) - 1 ) / ( Exp(tCap/tT2) - 1 ) - ( Exp(N*tCap/tT2) - Power(a[rho],N) ) / ( Exp(tCap/tT2) - a[rho] );
	// Untrapped populations at t=0
	v20 = ( a[r2] * tCap * (1-a[p]) * SU20 * Exp(-(T-tBac)/tU2) ) / ( 1 - Exp(-T/tU2) );
	// Untrapped population during background period
	v2 = v20 * Exp(-t[0]/tU2);
	// Background period
	if (0 <= t[0] && t[0] < tBac) {
		f = v2;
	}
	// Trapping period
	if (tBac <= t[0] && t[0] <= T) {
		// Untrapped populations during trapping
		V2 = a[r2] * tCap * (1-a[p]) * SU2 * Exp(-(t[0]-tBac)/tU2);
		f = v2+V2;
	}
	return f;
}

Double_t BFitNamespace::V3 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	using namespace TMath;
	static Int_t n, N;
	static Double_t tT3, tU3, SU3, SU30, v30, v3, V3, f;
	static Int_t gdx;
	static const Double_t tCap = bdn_cases[gdx].T_capt;
	static const Double_t tBac = bdn_cases[gdx].T_bkgd;
	static const Double_t T  = bdn_cases[gdx].T_cycle;
	tT3 = a[tauT3];
	tU3 = a[tauU3];
	f = 0.0; //catch bad values of t[0]
	n = Ceil((t[0]-tBac)/tCap);
	N = Ceil(   (T-tBac)/tCap);
	SU3  = ( Exp(n*tCap/tU3) - 1 ) / ( Exp(tCap/tU3) - 1 );
	SU30 = ( Exp(N*tCap/tU3) - 1 ) / ( Exp(tCap/tU3) - 1 );
//	D3   = ( Exp(n*tCap/tT3) - 1 ) / ( Exp(tCap/tT3) - 1 ) - ( Exp(n*tCap/tT3) - Power(a[rho],n) ) / ( Exp(tCap/tT3) - a[rho] );
//	D30  = ( Exp(N*tCap/tT3) - 1 ) / ( Exp(tCap/tT3) - 1 ) - ( Exp(N*tCap/tT3) - Power(a[rho],N) ) / ( Exp(tCap/tT3) - a[rho] );
	// Untrapped populations at t=0
	v30 = ( a[r3] * tCap * (1-a[p]) * SU30 * Exp(-(T-tBac)/tU3) ) / ( 1 - Exp(-T/tU3) );
	// Untrapped population during background period
	v3 = v30 * Exp(-t[0]/tU3);
	// Background period
	if (0 <= t[0] && t[0] < tBac) {
		f = v3;
	}
	// Trapping period
	if (tBac <= t[0] && t[0] <= T) {
		// Untrapped populations during trapping
		V3 = a[r3] * tCap * (1-a[p]) * SU3 * Exp(-(t[0]-tBac)/tU3);
		f = v3+V3;
	}
	return f;
}

Double_t BFitNamespace::yV1 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	return a[dt]*a[epsV]*V1(t,a)/a[tauU1];
}
Double_t BFitNamespace::yV2 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	return a[dt]*a[epsV]*V2(t,a)/a[tauU2];
}
Double_t BFitNamespace::yV3 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	return a[dt]*a[epsV]*V3(t,a)/a[tauU3];
}

// W populations
Double_t BFitNamespace::W1 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	using namespace TMath;
	static Int_t n, N;
	static Double_t tT1, tU1, D1, D10, w10, w1, W1, f;
	static Int_t gdx;
	static const Double_t tCap = bdn_cases[gdx].T_capt;
	static const Double_t tBac = bdn_cases[gdx].T_bkgd;
	static const Double_t T  = bdn_cases[gdx].T_cycle;
	tT1 = a[tauT1];
	tU1 = a[tauU1];
	f = 0.0; //catch bad values of t[0]
	n = Ceil((t[0]-tBac)/tCap);
	N = Ceil(   (T-tBac)/tCap);
//	SU1  = ( Exp(n*tCap/tU1) - 1 ) / ( Exp(tCap/tU1) - 1 );
//	SU10 = ( Exp(N*tCap/tU1) - 1 ) / ( Exp(tCap/tU1) - 1 );
	D1   = ( Exp(n*tCap/tT1) - 1 ) / ( Exp(tCap/tT1) - 1 ) - ( Exp(n*tCap/tT1) - Power(a[rho],n) ) / ( Exp(tCap/tT1) - a[rho] );
	D10  = ( Exp(N*tCap/tT1) - 1 ) / ( Exp(tCap/tT1) - 1 ) - ( Exp(N*tCap/tT1) - Power(a[rho],N) ) / ( Exp(tCap/tT1) - a[rho] );
	// Untrapped populations at t=0
	w10 = ( a[r1] * tCap * a[p] * D10 * Exp(-(T-tBac)/tU1) ) / ( 1 - Exp(-T/tU1) );
	// Untrapped population during background period
	w1 = w10 * Exp(-t[0]/tU1);
	// Background period
	if (0 <= t[0] && t[0] < tBac) {
		f = w1;
	}
	// Trapping period
	if (tBac <= t[0] && t[0] <= T) {
		// Untrapped populations during trapping
		W1 = a[r1] * tCap * a[p] * D1 * Exp(-(t[0]-tBac)/tU1);
		f = w1 + W1;
	}
	return f;
}
Double_t BFitNamespace::W2 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	using namespace TMath;
	static Int_t n, N;
	static Double_t tT2, tU2, D2, D20, w20, w2, W2, f;
	static Int_t gdx;
	static const Double_t tCap = bdn_cases[gdx].T_capt;
	static const Double_t tBac = bdn_cases[gdx].T_bkgd;
	static const Double_t T  = bdn_cases[gdx].T_cycle;
	tT2 = a[tauT2];
	tU2 = a[tauU2];
	f = 0.0; //catch bad values of t[0]
	n = Ceil((t[0]-tBac)/tCap);
	N = Ceil(   (T-tBac)/tCap);
//	SU2  = ( Exp(n*tCap/tU2) - 1 ) / ( Exp(tCap/tU2) - 1 );
//	SU20 = ( Exp(N*tCap/tU2) - 1 ) / ( Exp(tCap/tU2) - 1 );
	D2   = ( Exp(n*tCap/tT2) - 1 ) / ( Exp(tCap/tT2) - 1 ) - ( Exp(n*tCap/tT2) - Power(a[rho],n) ) / ( Exp(tCap/tT2) - a[rho] );
	D20  = ( Exp(N*tCap/tT2) - 1 ) / ( Exp(tCap/tT2) - 1 ) - ( Exp(N*tCap/tT2) - Power(a[rho],N) ) / ( Exp(tCap/tT2) - a[rho] );
	// Untrapped populations at t=0
	w20 = ( a[r2] * tCap * a[p] * D20 * Exp(-(T-tBac)/tU2) ) / ( 1 - Exp(-T/tU2) );
	// Untrapped population during background period
	w2 = w20 * Exp(-t[0]/tU2);
	// Background period
	if (0 <= t[0] && t[0] < tBac) {
		f = w2;
	}
	// Trapping period
	if (tBac <= t[0] && t[0] <= T) {
		// Untrapped populations during trapping
		W2 = a[r2] * tCap * a[p] * D2 * Exp(-(t[0]-tBac)/tU2);
		f = w2 + W2;
	}
	return f;
}
Double_t BFitNamespace::W3 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	using namespace TMath;
	static Int_t n, N;
	static Double_t tT3, tU3, D3, D30, w30, w3, W3, f;
	static Int_t gdx;
	static const Double_t tCap = bdn_cases[gdx].T_capt;
	static const Double_t tBac = bdn_cases[gdx].T_bkgd;
	static const Double_t T  = bdn_cases[gdx].T_cycle;
	tT3 = a[tauT3];
	tU3 = a[tauU3];
	f = 0.0; //catch bad values of t[0]
	n = Ceil((t[0]-tBac)/tCap);
	N = Ceil(   (T-tBac)/tCap);
//	SU3  = ( Exp(n*tCap/tU3) - 1 ) / ( Exp(tCap/tU3) - 1 );
//	SU30 = ( Exp(N*tCap/tU3) - 1 ) / ( Exp(tCap/tU3) - 1 );
	D3   = ( Exp(n*tCap/tT3) - 1 ) / ( Exp(tCap/tT3) - 1 ) - ( Exp(n*tCap/tT3) - Power(a[rho],n) ) / ( Exp(tCap/tT3) - a[rho] );
	D30  = ( Exp(N*tCap/tT3) - 1 ) / ( Exp(tCap/tT3) - 1 ) - ( Exp(N*tCap/tT3) - Power(a[rho],N) ) / ( Exp(tCap/tT3) - a[rho] );
	// Untrapped populations at t=0
	w30 = ( a[r3] * tCap * a[p] * D30 * Exp(-(T-tBac)/tU3) ) / ( 1 - Exp(-T/tU3) );
	// Untrapped population during background period
	w3 = w30 * Exp(-t[0]/tU3);
	// Background period
	if (0 <= t[0] && t[0] < tBac) {
		f = w3;
	}
	// Trapping period
	if (tBac <= t[0] && t[0] <= T) {
		// Untrapped populations during trapping
		W3 = a[r3] * tCap * a[p] * D3 * Exp(-(t[0]-tBac)/tU3);
		f = w3 + W3;
	}
	return f;
}
Double_t BFitNamespace::yW1 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	return a[dt]*a[epsW]*W1(t,a)/a[tauU1];
}
Double_t BFitNamespace::yW2 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	return a[dt]*a[epsW]*W2(t,a)/a[tauU2];
}
Double_t BFitNamespace::yW3 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	return a[dt]*a[epsW]*W3(t,a)/a[tauU3];
}

Double_t BFitNamespace::X2 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	using namespace TMath;
	static Int_t n, N;
	static Double_t t1, tT1, tT2, tU1, tU2, ST1, ST10, SU2, SU20, x20, x2, X2, f;
	static Int_t gdx;
	static const Double_t tCap = bdn_cases[gdx].T_capt;
	static const Double_t tBac = bdn_cases[gdx].T_bkgd;
	static const Double_t T  = bdn_cases[gdx].T_cycle;
	static const Double_t ln2= 0.69314718056;
	t1 = bdn_cases[gdx].lifetime1[0]
//	t2 = bdn_cases[gdx].lifetime2[0]
//	t3 = bdn_cases[gdx].lifetime3[0]
	tT1 = a[tauT1];
	tT2 = a[tauT2];
	tU1 = a[tauU1];
	tU2 = a[tauU2];
	f = 0.0; //catch bad values of t[0]
	n = Ceil((t[0]-tBac)/tCap);
	N = Ceil(   (T-tBac)/tCap);
	ST1  = ( Exp(n*tCap/tT1) - 1 ) / ( Exp(tCap/tT1) - 1 );
	ST10 = ( Exp(N*tCap/tT1) - 1 ) / ( Exp(tCap/tT1) - 1 );
	SU2  = ( Exp(n*tCap/tU2) - 1 ) / ( Exp(tCap/tU2) - 1 );
	SU20 = ( Exp(N*tCap/tU2) - 1 ) / ( Exp(tCap/tU2) - 1 );
	// Untrapped populations at t=0
	x20 = ( a[r1] * tCap * a[p] * tT1/t1 * tU2/(tU2-tT1) * ( SU20 * Exp(-(T-tBac)/tU2) - ST10 * Exp(-(T-tBac)/tT1) ) ) / ( 1 - Exp(-T/tU2) );
	// Untrapped population during background period
	x2 = x20*Exp(-t[0]/tU2) ;
	// Background period
	if (0 <= t[0] && t[0] < tBac) {
		f = x2;
	}
	// Trapping period
	if (tBac <= t[0] && t[0] <= T) {
		// Untrapped populations during trapping
		X2 = a[r1] * tCap * a[p] * tT1/t1 * tU2/(tU2-tT1) * ( SU2 * Exp(-(t[0]-tBac)/tU2) - ST1 * Exp(-(t[0]-tBac)/tT1) );
		f = x2 + X2;
	}
	return f;
}

Double_t BFitNamespace::X3 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	using namespace TMath;
	static Int_t n, N;
	static Double_t t2, tT2, tT3, tU2, tU3, ST2, ST20, SU3, SU30, x30, x3, X3, f;
	static Int_t gdx;
	static const Double_t tCap = bdn_cases[gdx].T_capt;
	static const Double_t tBac = bdn_cases[gdx].T_bkgd;
	static const Double_t T  = bdn_cases[gdx].T_cycle;
	static const Double_t ln2= 0.69314718056;
//	t1 = bdn_cases[gdx].lifetime1[0]
	t2 = bdn_cases[gdx].lifetime2[0]
//	t3 = bdn_cases[gdx].lifetime3[0]
	tT2 = a[tauT2];
	tT3 = a[tauT3];
	tU2 = a[tauU2];
	tU3 = a[tauU3];
	f = 0.0; //catch bad values of t[0]
	n = Ceil((t[0]-tBac)/tCap);
	N = Ceil(   (T-tBac)/tCap);
	ST2  = ( Exp(n*tCap/tT2) - 1 ) / ( Exp(tCap/tT2) - 1 );
	ST20 = ( Exp(N*tCap/tT2) - 1 ) / ( Exp(tCap/tT2) - 1 );
	SU3  = ( Exp(n*tCap/tU3) - 1 ) / ( Exp(tCap/tU3) - 1 );
	SU30 = ( Exp(N*tCap/tU3) - 1 ) / ( Exp(tCap/tU3) - 1 );
	// Untrapped populations at t=0
	x30 = ( a[r2] * tCap * a[p] * tT2/t2 * tU3/(tU3-tT2) * ( SU30 * Exp(-(T-tBac)/tU3) - ST20 * Exp(-(T-tBac)/tT2) ) ) / ( 1 - Exp(-T/tU3) );
	// Untrapped population during background period
	x3 = x30 * Exp(-t[0]/tU3);
	// Background period
	if (0 <= t[0] && t[0] < tBac) {
		f = x3;
	}
	// Trapping period
	if (tBac <= t[0] && t[0] <= T) {
		// Untrapped populations during trapping
		X3 = a[r2] * tCap * a[p] * tT2/t2 * tU3/(tU3-tT2) * ( SU3 * Exp(-(t[0]-tBac)/tU3) - ST2 * Exp(-(t[0]-tBac)/tT2) );
		f = x3 + X3;
	}
	return f;
}

Double_t BFitNamespace::yX2 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	return a[dt]*a[epsX]*X2(t,a)/a[tauU2];
}
Double_t BFitNamespace::yX3 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	return a[dt]*a[epsX]*X3(t,a)/a[tauU3];
}

Double_t BFitNamespace::Y2 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	using namespace TMath;
	static Int_t n, N;
	static Double_t t1, tT1, tT2, tU1, tU2, ST1, ST10, SU1, SU10, SU2, SU20, y10, y20, y2, Y2, f;
	static Int_t gdx;
	static const Double_t tCap = bdn_cases[gdx].T_capt;
	static const Double_t tBac = bdn_cases[gdx].T_bkgd;
	static const Double_t T  = bdn_cases[gdx].T_cycle;
	static const Double_t ln2= 0.69314718056;
	t1 = bdn_cases[gdx].lifetime1[0]
//	t2 = bdn_cases[gdx].lifetime2[0]
//	t3 = bdn_cases[gdx].lifetime3[0]
	tT1 = a[tauT1];
	tT2 = a[tauT2];
	tU1 = a[tauU1];
	tU2 = a[tauU2];
	f = 0.0; //catch bad values of t[0]
	n = Ceil((t[0]-tBac)/tCap);
	N = Ceil(   (T-tBac)/tCap);
//	ST1  = ( Exp(n*tCap/tT1) - 1 ) / ( Exp(tCap/tT1) - 1 );
//	ST10 = ( Exp(N*tCap/tT1) - 1 ) / ( Exp(tCap/tT1) - 1 );
	SU1  = ( Exp(n*tCap/tU1) - 1 ) / ( Exp(tCap/tU1) - 1 );
	SU10 = ( Exp(N*tCap/tU1) - 1 ) / ( Exp(tCap/tU1) - 1 );
	SU2  = ( Exp(n*tCap/tU2) - 1 ) / ( Exp(tCap/tU2) - 1 );
	SU20 = ( Exp(N*tCap/tU2) - 1 ) / ( Exp(tCap/tU2) - 1 );
	
	// Untrapped populations at t=0
	y10 = a[r1] * tCap * (1-a[p]) * SU10 * Exp(-(T-tBac)/tU1) / ( 1 - Exp(-T/tU1) );
	y20 = ( y10 * tU1/t1 * tU2/(tU2-tU1) * ( Exp(-T/tU2) - Exp(-T/tU1) ) + a[r1] * tCap * (1-a[p]) * tU1/t1 * tU2/(tU2-tU1) * ( SU20 * Exp(-(T-tBac)/tU2) - SU10 * Exp(-(T-tBac)/tU1) ) ) / (1-Exp(-T/tU2) );
	// Untrapped population during background period
	y2 = y20 * Exp(-t[0]/tU2) + y10 * tU1/t1 * tU2/(tU2-tU1) * ( Exp(-t[0]/tU2) - Exp(-t[0]/tU1 ) );
	// Background period
	if (0 <= t[0] && t[0] < tBac) {
		f = y2;
	}
	// Trapping period
	if (tBac <= t[0] && t[0] <= T) {
		// Untrapped populations during trapping
		Y2 = a[r1] * tCap * (1-a[p]) * tU1/t1 * tU2/(tU2-tU1) * ( SU2 * Exp(-(t[0]-tBac)/tU2) - SU1 * Exp(-(t[0]-tBac)/tU1) );
		f = y2 + Y2;
	}
	return f;
}

Double_t BFitNamespace::Y3 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	using namespace TMath;
	static Int_t n, N;
	static Double_t t1, t2, t3, tT1, tT2, tT3, tU1, tU2, tU3, AU, ST1, ST2, ST3, ST10, ST20, ST30, SU1, SU2, SU3, SU10, SU20, SU30, y10, y20, y30, y3, Y3, f;
	static Int_t gdx;
	static const Double_t tCap = bdn_cases[gdx].T_capt;
	static const Double_t tBac = bdn_cases[gdx].T_bkgd;
	static const Double_t T  = bdn_cases[gdx].T_cycle;
	t1 = bdn_cases[gdx].lifetime1[0]
	t2 = bdn_cases[gdx].lifetime2[0]
//	t3 = bdn_cases[gdx].lifetime3[0]
	tT1 = a[tauT1];
	tT2 = a[tauT2];
	tT3 = a[tauT3];
	tU1 = a[tauU1];
	tU2 = a[tauU2];
	tU3 = a[tauU3];
	AU  = (tU3-tU2) * (tU3-tU1) * (tU2-tU1);
	f = 0.0; //catch bad values of t[0]
	n = Ceil((t[0]-tBac)/tCap);
	N = Ceil(   (T-tBac)/tCap);
	SU1  = ( Exp(n*tCap/tU1) - 1 ) / ( Exp(tCap/tU1) - 1 );
	SU2  = ( Exp(n*tCap/tU2) - 1 ) / ( Exp(tCap/tU2) - 1 );
	SU3  = ( Exp(n*tCap/tU3) - 1 ) / ( Exp(tCap/tU3) - 1 );
	SU10 = ( Exp(N*tCap/tU1) - 1 ) / ( Exp(tCap/tU1) - 1 );
	SU20 = ( Exp(N*tCap/tU2) - 1 ) / ( Exp(tCap/tU2) - 1 );
	SU30 = ( Exp(N*tCap/tU3) - 1 ) / ( Exp(tCap/tU3) - 1 );
	// Untrapped populations at t=0
	y10 = 
		a[r1] * tCap * (1-a[p]) * SU10 * Exp(-(T-tBac)/tU1) / ( 1 - Exp(-T/tU1) );
	y20 = (
		y10 * tU1/t1 * tU2/(tU2-tU1) * ( Exp(-T/tU2) - Exp(-T/tU1) ) +
		a[r2] * tCap * (1-a[p]) *            SU20*Exp(-(T-tBac)/tU2) + 
		a[r1] * tCap * (1-a[p]) * tU1/t1 * tU2/(tU2-tU1) * (SU20 * Exp(-(T-tBac)/tU2) - SU10 * Exp(-(T-tBac)/tU1) )
		)
		/ ( 1 - Exp(-T/tU2) );
	y30 = (
		y20 * tU2/t2 * tU3/(tU3-tU2) * ( Exp(-T/tU3) - Exp(-T/tU2) ) + 
		y10 * tU1/t1 * tU2/t2 * tU3/AU * ( tU1 * (tU3-tU2) * Exp(-T/tU1) - tU2 * (tU3-tU1) * Exp(-T/tU2) + tU3 * (tU2-tU1) * Exp(-T/tU3) ) + 
//		a[r3]*tCap*(1-a[p])*                 S30*Exp(-(T-tBac)/t3) + 
		a[r2] * tCap * (1-a[p]) * tU2/t2 * tU3/(tU3-tU2) *     (SU30*Exp(-(T-tBac)/tU3) -            SU20*Exp(-(T-tBac)/tU2)) + 
		a[r1] * tCap * (1-a[p]) * tU1/t1 * tU2/t2 * tU3/AU * ( tU1 * (tU3-tU2) * SU10 * Exp(-(T-tBac)/tU1) - tU2 * (tU3-tU1) * SU20 * Exp(-(T-tBac)/tU2) + tU3 * (tU2-tU1) * SU30 * Exp(-(T-tBac)/tU3) )
		)
		/ ( 1 - Exp(-T/tU3) );
	// Untrapped population during background period
	y3 = 
		y30 * Exp(-t[0]/tU3) + 
		y20 * tU2/t2 * tU3/(tU3-tU2) * ( Exp(-t[0]/tU3) - Exp(-t[0]/tU2) ) + 
		y10 * tU1/t1 * tU2/t2 * tU3/AU * ( tU1 * (tU3-tU2) * Exp(-t[0]/tU1) - tU2 * (tU3-tU1) * Exp(-t[0]/tU2) + tU3 * (tU2-tU1) * Exp(-t[0]/tU3) );
	// Background period
	if (0 <= t[0] && t[0] < tBac) {
		f = y3;
	}
	// Trapping period
	if (tBac <= t[0] && t[0] <= T) {
		// Untrapped populations during trapping
		Y3 = 
			a[r2] * tCap * (1-a[p]) * tU2/t2 * tU3/(tU3-tU2) * ( SU3 * Exp(-(t[0]-tBac)/tU3) - SU2 * Exp(-(t[0]-tBac)/tU2) ) + 
			a[r1] * tCap * (1-a[p]) * tU1/t1 * tU2/t2 * tU3/AU * ( tU1 * (tU3-tU2) * SU1 * Exp(-(t[0]-tBac)/tU1) - tU2 * (tU3-tU1) * SU2 * Exp(-(t[0]-tBac)/tU2) + tU3 * (tU2-tU1) * SU3 * Exp(-(t[0]-tBac)/tU3) );
		f = y3 + Y3;
	}
	return f;
}

Double_t BFitNamespace::yY2 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	return a[dt]*a[epsY]*Y2(t,a)/a[tauU2];
}
Double_t BFitNamespace::yY3 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	return a[dt]*a[epsY]*Y3(t,a)/a[tauU3];
}
*/
