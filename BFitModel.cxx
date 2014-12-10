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
Double_t BFitNamespace::SigmaT (Double_t rho, Double_t tau, Int_t n) {
	using namespace TMath;
	extern Double_t tCap;
	static Double_t a;
	a = Exp(-tCap/tau);
	return ( 1-Power(rho*a,n) ) / (1-rho*a);
//	return ( Exp(n*tCap/tau) - Power(rho,n) ) / ( Exp(tCap/tau) - rho );
}
Double_t BFitNamespace::T1 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	using namespace TMath;
	static Int_t n;
	static Double_t ST1, tT1, f;
	extern Double_t tCap, tBac, tCyc, t1, t2, t3;
	f = 0.0; //catch bad values of t[0]
	if (tBac <= t[0] && t[0] <= tCyc)
	{
		tT1 = 1.0 / ( 1.0/t1 + a[gammaT1]/1000.0 ); // net variable lifetime (1/e) in ms
		n = Ceil((t[0]-tBac)/tCap);
		f = a[p] * a[r1] * tCap * SigmaT(a[rho],tT1,n) * Exp(-(t[0]-tBac-(n-1)*tCap)/tT1);
	}
	return f;
}

Double_t BFitNamespace::T2 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	using namespace TMath;
	static Int_t n;
	static Double_t ST2, tT2, f;
	extern Double_t tCap, tBac, tCyc, t2;
	f = 0.0; //catch bad values of t[0]
	if (tBac <= t[0] && t[0] <= tCyc)
	{
		tT2 = 1.0 / ( 1.0/t2 + a[gammaT2]/1000.0 ); // net variable lifetime (1/e) in ms
		n = Ceil((t[0]-tBac)/tCap);
		f = a[p] * a[r2] * tCap * SigmaT(a[rho],tT2,n) * Exp(-(t[0]-tBac-(n-1)*tCap)/tT2);
	}
	return f;
}

Double_t BFitNamespace::T3 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	using namespace TMath;
	static Int_t n;
	static Double_t ST3, tT3, f;
	extern Double_t tCap, tBac, tCyc, t3;
	extern BDNCase_t stBDNCases[FILE_ROWS_BDN]; // This comes from the main program (BFit.cxx)
	extern Int_t iBDNCaseIndex; // This comes from the main program (BFit.cxx)
	extern bool b134sbFlag;
	f = 0.0; //catch bad values of t[0]
	if (tBac <= t[0] && t[0] <= tCyc)
	{
		if (b134sbFlag) a[gammaT3] = a[gammaT2];
		tT3 = 1.0 / ( 1.0/t3 + a[gammaT3]/1000.0 ); // net variable lifetime (1/e) in ms
		n = Ceil((t[0]-tBac)/tCap);
		f = a[p] * a[r3] * tCap * SigmaT(a[rho],tT3,n) * Exp(-(t[0]-tBac-(n-1)*tCap)/tT3);
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
Double_t BFitNamespace::yDC (Double_t *t, Double_t *a) { return a[dt]*a[DC]; }
Double_t BFitNamespace::yT1 (Double_t *t, Double_t *a) { return a[dt]*BFitNamespace::rT1(t,a); }
Double_t BFitNamespace::yT2 (Double_t *t, Double_t *a) { return a[dt]*BFitNamespace::rT2(t,a); }
Double_t BFitNamespace::yT3 (Double_t *t, Double_t *a) { return a[dt]*BFitNamespace::rT3(t,a); }
Double_t BFitNamespace::yU1 (Double_t *t, Double_t *a) { return a[dt]*BFitNamespace::rU1(t,a); }
Double_t BFitNamespace::yU2 (Double_t *t, Double_t *a) { return a[dt]*BFitNamespace::rU2(t,a); }
Double_t BFitNamespace::yU3 (Double_t *t, Double_t *a) { return a[dt]*BFitNamespace::rU3(t,a); }
Double_t BFitNamespace::yAll(Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	return a[dt]*a[DC] + yT1(t,a) + yT2(t,a) + yT3(t,a) + yU1(t,a) + yU2(t,a) + yU3(t,a);
}

// Offset functions to improve visualization: offT1 = yT1 + yDC
Double_t BFitNamespace::oT1 (Double_t *t, Double_t *a) { return a[dt]*(a[DC] + BFitNamespace::rT1(t,a)); }
Double_t BFitNamespace::oT2 (Double_t *t, Double_t *a) { return a[dt]*(a[DC] + BFitNamespace::rT2(t,a)); }
Double_t BFitNamespace::oT3 (Double_t *t, Double_t *a) { return a[dt]*(a[DC] + BFitNamespace::rT3(t,a)); }
Double_t BFitNamespace::oU1 (Double_t *t, Double_t *a) { return a[dt]*(a[DC] + BFitNamespace::rU1(t,a)); }
Double_t BFitNamespace::oU2 (Double_t *t, Double_t *a) { return a[dt]*(a[DC] + BFitNamespace::rU2(t,a)); }
Double_t BFitNamespace::oU3 (Double_t *t, Double_t *a) { return a[dt]*(a[DC] + BFitNamespace::rU3(t,a)); }

// Per-bin rates by component, used for calculating N_beta
Double_t BFitNamespace::rDC (Double_t *t, Double_t *a) { return a[DC]; }
Double_t BFitNamespace::rT1 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	extern Double_t t1;
	return a[epsT]*T1(t,a)/t1;
}
Double_t BFitNamespace::rT2 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	extern Double_t t2;
	return a[epsT]*T2(t,a)/t2;
}
Double_t BFitNamespace::rT3 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	extern Double_t t3;
	return a[epsT]*T3(t,a)/t3;
}
Double_t BFitNamespace::rU1 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	extern Double_t t1;
	return (a[epsV]*V1(t,a) + a[epsW]*W1(t,a))/t1;
}
Double_t BFitNamespace::rU2 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	extern Double_t t2;
	return (a[epsV]*V2(t,a) + a[epsW]*W2(t,a) + a[epsX]*X2(t,a) + a[epsY]*Y2(t,a))/t2;
}
Double_t BFitNamespace::rU3 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	extern Double_t t3;
	return (a[epsV]*V3(t,a) + a[epsW]*W3(t,a) + a[epsX]*X3(t,a) + a[epsY]*Y3(t,a))/t3;
}
Double_t BFitNamespace::rAll (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	return a[DC] + rT1(t,a) + rT2(t,a) + rT3(t,a) + rU1(t,a) + rU2(t,a) + rU3(t,a);
}

Double_t BFitNamespace::V1 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	using namespace TMath;
	static Int_t n, N;
	static Double_t tU1, v10, v1, V1, f;
	extern Double_t tCap, tBac, tCyc, t1;
	tU1 = 1.0 / ( 1.0/t1 + a[gammaU1]/1000.0 ); // net variable lifetime (1/e) in ms
	f = 0.0; //catch bad values of t[0]
	n = Ceil((t[0]-tBac)/tCap);
	N = Ceil((tCyc-tBac)/tCap);
	// Untrapped populations at t=0
	v10 = ( a[r1] * tCap * (1-a[p]) * SigmaT(1,tU1,N) * Exp(-(tCyc-tBac-(N-1)*tCap)/tU1) ) / ( 1 - Exp(-tCyc/tU1) );
	// Untrapped population during background period
	v1 = v10 * Exp(-t[0]/tU1);
	// Background period
	if (0 <= t[0] && t[0] < tBac) {
		f = v1;
	}
	// Trapping period
	if (tBac <= t[0] && t[0] <= tCyc) {
		// Untrapped populations during trapping
		V1 = a[r1] * tCap * (1-a[p]) * SigmaT(1,tU1,n) * Exp(-(t[0]-tBac-(n-1)*tCap)/tU1);
		f = v1+V1;
	}
	return f;
}
Double_t BFitNamespace::V2 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	using namespace TMath;
	static Int_t n, N;
	static Double_t tU2, v20, v2, V2, f;
	extern Double_t tCap, tBac, tCyc, t2;
	tU2 = 1.0 / ( 1.0/t2 + a[gammaU2]/1000.0 ); // net variable lifetime (1/e) in ms
	f = 0.0; //catch bad values of t[0]
	n = Ceil((t[0]-tBac)/tCap);
	N = Ceil((tCyc-tBac)/tCap);
	// Untrapped populations at t=0
	v20 = ( a[r2] * tCap * (1-a[p]) * SigmaT(1,tU2,N) * Exp(-(tCyc-tBac-(N-1)*tCap)/tU2) ) / ( 1 - Exp(-tCyc/tU2) );
	// Untrapped population during background period
	v2 = v20 * Exp(-t[0]/tU2);
	// Background period
	if (0 <= t[0] && t[0] < tBac) {
		f = v2;
	}
	// Trapping period
	if (tBac <= t[0] && t[0] <= tCyc) {
		// Untrapped populations during trapping
		V2 = a[r2] * tCap * (1-a[p]) * SigmaT(1,tU2,n) * Exp(-(t[0]-tBac-(n-1)*tCap)/tU2);
		f = v2+V2;
	}
	return f;
}
Double_t BFitNamespace::V3 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	using namespace TMath;
	static Int_t n, N;
	static Double_t tU3, v30, v3, V3, f;
	extern Double_t tCap, tBac, tCyc, t3;
	tU3 = 1.0 / ( 1.0/t3 + a[gammaU3]/1000.0 ); // net variable lifetime (1/e) in ms
	f = 0.0; //catch bad values of t[0]
	n = Ceil((t[0]-tBac)/tCap);
	N = Ceil((tCyc-tBac)/tCap);
	// Untrapped populations at t=0
	v30 = ( a[r3] * tCap * (1-a[p]) * SigmaT(1,tU3,N) * Exp(-(tCyc-tBac-(N-1)*tCap)/tU3) ) / ( 1 - Exp(-tCyc/tU3) );
	// Untrapped population during background period
	v3 = v30 * Exp(-t[0]/tU3);
	// Background period
	if (0 <= t[0] && t[0] < tBac) {
		f = v3;
	}
	// Trapping period
	if (tBac <= t[0] && t[0] <= tCyc) {
		// Untrapped populations during trapping
		V3 = a[r3] * tCap * (1-a[p]) * SigmaT(1,tU3,n) * Exp(-(t[0]-tBac-(n-1)*tCap)/tU3);
		f = v3+V3;
	}
	return f;
}

Double_t BFitNamespace::yV1 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	extern Double_t t1;
	return a[dt]*a[epsV]*V1(t,a)/t1;
}
Double_t BFitNamespace::yV2 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	extern Double_t t2;
	return a[dt]*a[epsV]*V2(t,a)/t2;
}
Double_t BFitNamespace::yV3 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	extern Double_t t3;
	return a[dt]*a[epsV]*V3(t,a)/t3;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// W populations
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Double_t BFitNamespace::SigmaW (Double_t rho, Double_t tT, Double_t tU, Int_t n) {
	using namespace TMath;
	static Double_t expT, expU, f;
	static Int_t k;
	extern Double_t iota, tCap;
	f = 0.0;
	if (n>=2) {
		expT = Exp(-tCap/tT);
		expU = Exp(-tCap/tU);
		f = 1.0/(rho*(expU-1.0)) * ( Power(expU,n)*(Power(rho*expT/expU,n)-rho*expT/expU)/(rho*expT/expU-1.0) - (Power(rho*expT,n)-rho*expT)/(rho*expT-1.0) );
		//for (k=1; k<=n-1; k++) f += SigmaT(1,tU,n-k) * TMath::Power(rho*TMath::Exp(-tCap/tT),k);
//		f = 1.0/(rho*(Exp(-tCap/tU)-1.0)) * ( Exp(-n*tCap/tU)*(Power(rho*Exp(-tCap*(1.0/tT-1.0/tU)),n)-rho*Exp(-tCap*(1.0/tT-1.0/tU)))/(rho*Exp(-tCap*(1.0/tT-1.0/tU))-1.0) - (Power(rho*Exp(-tCap/tT),n)-rho*Exp(-tCap/tT))/(rho*Exp(-tCap/tT)-1.0) );
	}
//	f *= 1.0/(rho+iota);
	return f;
}
Double_t BFitNamespace::W1 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	using namespace TMath;
// externs: constant over all computations
	extern Double_t iota, tCap, tBac, tCyc, t1;
// statics: recomputed many times (keep memory allocated)
	static Int_t n, N;
	static Double_t tT1, tU1, w10, w1, W1, f, amplitude;
// Initialize function value
	f = 0.0;
// Recompute variables
	tT1 = 1.0 / ( 1.0/t1 + a[gammaT1]/1000.0 ); // net variable lifetime (1/e) in ms
	tU1 = 1.0 / ( 1.0/t1 + a[gammaU1]/1000.0 ); // net variable lifetime (1/e) in ms
	n = Ceil((t[0]-tBac)/tCap);
	N = Ceil((tCyc-tBac)/tCap);
	amplitude = (1-a[rho]) * a[p] * a[r1] * tCap;
// Initial value (t=0)
	w10 = amplitude * SigmaW(a[rho],tT1,tU1,N) * Exp(-(tCyc-tBac-(N-1)*tCap)/tU1) / (1 - Exp(-tCyc/tU1) );
// Background solution
	w1 = w10 * Exp(-t[0]/tU1);
// Background period
	if (0 <= t[0] && t[0] < tBac + tCap) { // Different from other pops: No effect from 1st injection
		f = w1;
	}
	// Trapping period
	if (tBac + tCap <= t[0] && t[0] <= tCyc) {
		// Untrapped populations during trapping
		W1 = amplitude * SigmaW(a[rho],tT1,tU1,n) * Exp(-(t[0]-tBac-(n-1)*tCap)/tU1);
		f = w1 + W1;
	}
	return f;
}
Double_t BFitNamespace::W2 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	using namespace TMath;
// externs: constant over all computations
	extern Double_t iota, tCap, tBac, tCyc, t2;
// statics: recomputed many times (keep memory allocated)
	static Int_t n, N;
	static Double_t tT2, tU2, w20, w2, W2, f, amplitude;
// Initialize function value
	f = 0.0;
// Recompute variables
	tT2 = 1.0 / ( 1.0/t2 + a[gammaT2]/1000.0 ); // net variable lifetime (1/e) in ms
	tU2 = 1.0 / ( 1.0/t2 + a[gammaU2]/1000.0 ); // net variable lifetime (1/e) in ms
	n = Ceil((t[0]-tBac)/tCap);
	N = Ceil((tCyc-tBac)/tCap);
	amplitude = (1-a[rho]) * a[p] * a[r2] * tCap;
// Initial value (t=0)
	w20 = amplitude * SigmaW(a[rho],tT2,tU2,N) * Exp(-(tCyc-tBac-(N-1)*tCap)/tU2) / (1 - Exp(-tCyc/tU2) );
// Background solution
	w2 = w20 * Exp(-t[0]/tU2);
// Background period
	if (0 <= t[0] && t[0] < tBac + tCap) { // Different from other pops: No effect from 1st injection
		f = w2;
	}
	// Trapping period
	if (tBac + tCap <= t[0] && t[0] <= tCyc) {
		// Untrapped populations during trapping
		W2 = amplitude * SigmaW(a[rho],tT2,tU2,n) * Exp(-(t[0]-tBac-(n-1)*tCap)/tU2);
		f = w2 + W2;
	}
	return f;
}
Double_t BFitNamespace::W3 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	using namespace TMath;
// externs: constant over all computations
	extern Double_t iota, tCap, tBac, tCyc, t3;
// statics: recomputed many times (keep memory allocated)
	static Int_t n, N;
	static Double_t tT3, tU3, w30, w3, W3, f, amplitude;
// Initialize function value
	f = 0.0;
// Recompute variables
	tT3 = 1.0 / ( 1.0/t3 + a[gammaT3]/1000.0 ); // net variable lifetime (1/e) in ms
	tU3 = 1.0 / ( 1.0/t3 + a[gammaU3]/1000.0 ); // net variable lifetime (1/e) in ms
	n = Ceil((t[0]-tBac)/tCap);
	N = Ceil((tCyc-tBac)/tCap);
	amplitude = (1-a[rho]) * a[p] * a[r3] * tCap;
// Initial value (t=0)
	w30 = amplitude * SigmaW(a[rho],tT3,tU3,N) * Exp(-(tCyc-tBac-(N-1)*tCap)/tU3) / (1 - Exp(-tCyc/tU3) );
// Background solution
	w3 = w30 * Exp(-t[0]/tU3);
// Background period
	if (0 <= t[0] && t[0] < tBac + tCap) { // Different from other pops: No effect from 1st injection
		f = w3;
	}
	// Trapping period
	if (tBac + tCap <= t[0] && t[0] <= tCyc) {
		// Untrapped populations during trapping
		W3 = amplitude * SigmaW(a[rho],tT3,tU3,n) * Exp(-(t[0]-tBac-(n-1)*tCap)/tU3);
		f = w3 + W3;
	}
	return f;
}
Double_t BFitNamespace::yW1 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	extern Double_t t1;
	return a[dt]*a[epsW]*W1(t,a)/t1;
}
Double_t BFitNamespace::yW2 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	extern Double_t t2;
	return a[dt]*a[epsW]*W2(t,a)/t2;
}
Double_t BFitNamespace::yW3 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	extern Double_t t3;
	return a[dt]*a[epsW]*W3(t,a)/t3;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Z populations
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Double_t BFitNamespace::SigmaZ (Double_t rho, Double_t tT, Double_t tU, Int_t n) {
	using namespace TMath;
	static Double_t expT, expU, f;
	static Int_t k;
	extern Double_t tCap;
	f = 0.0;
	if (n>=2) {
		expT = Exp(-tCap/tT);
		expU = Exp(-tCap/tU);
		f = (expU-expT) * Power(expU,n-1)/(1.0-rho*expT) * ( (Power(1/expU,n)-1/expU)/(1/expU-1.0) - (Power(rho*expT/expU,n)-rho*expT/expU)/(rho*expT/expU-1.0) );
//		for (k=1; k<=n-1; k++) f += SigmaT(rho,tT,k) * TMath::Exp(-(n-k-1)*tCap/tU);
//		f = Exp(-(n-1)*tCap/tU)/(1.0-rho*Exp(-tCap/tT)) * ( (Exp(n*tCap/tU)-Exp(tCap/tU))/(Exp(tCap/tU)-1.0) - (Power(rho*Exp(tCap*(1.0/tU-1.0/tT)),n)-rho*Exp(tCap*(1.0/tU-1.0/tT)))/(rho*Exp(tCap*(1.0/tU-1.0/tT))-1.0) );
	}
//	f *= ( TMath::Exp(-tCap/tU) - TMath::Exp(-tCap/tT) );
	return f;
}
Double_t BFitNamespace::Z1 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	using namespace TMath;
// externs: constant over all computations
	extern Double_t iota, tCap, tBac, tCyc, t1;
// statics: recomputed many times (keep memory allocated)
	static Int_t n, N;
	static Double_t tT1, tU1, z10, z1, Z1, f, amplitude;
// Initialize function value
	f = 0.0;
// Recompute variables
	tT1 = 1.0 / ( 1.0/t1 + a[gammaT1]/1000.0 ); // net variable lifetime (1/e) in ms
	tU1 = 1.0 / ( 1.0/t1 + a[gammaU1]/1000.0 ); // net variable lifetime (1/e) in ms
	n = Ceil((t[0]-tBac)/tCap);
	N = Ceil((tCyc-tBac)/tCap);
	amplitude = a[p] * a[r1] * tCap * (a[gammaT1]+iota)/((a[gammaT1]-a[gammaU1])+iota);
// Initial value (t=0)
	z10 = amplitude * ( (SigmaZ(a[rho],tT1,tU1,N)+SigmaT(a[rho],tT1,N))*Exp(-(tCyc-tBac-(N-1)*tCap)/tU1) - SigmaT(a[rho],tT1,N)*Exp(-(tCyc-tBac-(N-1)*tCap)/tT1) ) / (1 - Exp(-tCyc/tU1) );
// Background solution
	z1 = z10 * Exp(-t[0]/tU1);
// Background period
	if (0 <= t[0] && t[0] < tBac) {
		f = z1;
	}
	// Trapping period
	if (tBac <= t[0] && t[0] <= tCyc) {
		// Untrapped populations during trapping
		Z1 = amplitude * ( (SigmaZ(a[rho],tT1,tU1,n)+SigmaT(a[rho],tT1,n))*Exp(-(t[0]-tBac-(n-1)*tCap)/tU1) - SigmaT(a[rho],tT1,n)*Exp(-(t[0]-tBac-(n-1)*tCap)/tT1) );
		f = z1 + Z1;
	}
	return f;
}
Double_t BFitNamespace::Z2 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	using namespace TMath;
// externs: constant over all computations
	extern Double_t iota, tCap, tBac, tCyc, t2;
// statics: recomputed many times (keep memory allocated)
	static Int_t n, N;
	static Double_t tT2, tU2, z20, z2, Z2, f, amplitude;
// Initialize function value
	f = 0.0;
// Recompute variables
	tT2 = 1.0 / ( 1.0/t2 + a[gammaT2]/1000.0 ); // net variable lifetime (1/e) in ms
	tU2 = 1.0 / ( 1.0/t2 + a[gammaU2]/1000.0 ); // net variable lifetime (1/e) in ms
	if (t[0]==tBac)	n = 1;
	else			n = Ceil((t[0]-tBac)/tCap);
	N = Ceil((tCyc-tBac)/tCap);
	amplitude = a[p] * a[r2] * tCap * (a[gammaT2]+iota)/((a[gammaT2]-a[gammaU2])+iota);
// Initial value (t=0)
	z20 = amplitude * ( (SigmaZ(a[rho],tT2,tU2,N)+SigmaT(a[rho],tT2,N))*Exp(-(tCyc-tBac-(N-1)*tCap)/tU2) - SigmaT(a[rho],tT2,N) * Exp(-(tCyc-tBac-(N-1)*tCap)/tT2) ) / (1 - Exp(-tCyc/tU2) );
//	z20 = amplitude * ( SigmaZ(a[rho],tT2,tU2,N)*Exp(-(tCyc-tBac-(N-1)*tCap)/tU2) + SigmaT(a[rho],tT2,N) * (Exp(-(tCyc-tBac-(N-1)*tCap)/tU2) - Exp(-(tCyc-tBac-(N-1)*tCap)/tT2)) ) / (1 - Exp(-tCyc/tU2) );
// Background solution
	z2 = z20 * Exp(-t[0]/tU2);
// Background period
	if (0 <= t[0] && t[0] < tBac) {
		f = z2;
	}
	// Trapping period
	if (tBac <= t[0] && t[0] <= tCyc) {
		// Untrapped populations during trapping
		Z2 = amplitude * ( (SigmaZ(a[rho],tT2,tU2,n)+SigmaT(a[rho],tT2,n))*Exp(-(t[0]-tBac-(n-1)*tCap)/tU2) - SigmaT(a[rho],tT2,n) * Exp(-(t[0]-tBac-(n-1)*tCap)/tT2) );
//		Z2 = amplitude * ( SigmaZ(a[rho],tT2,tU2,n)*Exp(-(t[0]-tBac-(n-1)*tCap)/tU2) + SigmaT(a[rho],tT2,n) * (Exp(-(t[0]-tBac-(n-1)*tCap)/tU2) - Exp(-(t[0]-tBac-(n-1)*tCap)/tT2)) );
		f = z2 + Z2;
	}
	return f;
}
Double_t BFitNamespace::Z3 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	using namespace TMath;
// externs: constant over all computations
	extern Double_t iota, tCap, tBac, tCyc, t3;
// statics: recomputed many times (keep memory allocated)
	static Int_t n, N;
	static Double_t tT3, tU3, z30, z3, Z3, f, amplitude;
// Initialize function value
	f = 0.0;
// Recompute variables
	tT3 = 1.0 / ( 1.0/t3 + a[gammaT3]/1000.0 ); // net variable lifetime (1/e) in ms
	tU3 = 1.0 / ( 1.0/t3 + a[gammaU3]/1000.0 ); // net variable lifetime (1/e) in ms
	n = Ceil((t[0]-tBac)/tCap);
	N = Ceil((tCyc-tBac)/tCap);
	amplitude = a[p] * a[r3] * tCap * (a[gammaT3]+iota)/((a[gammaT3]-a[gammaU3])+iota);
// Initial value (t=0)
	z30 = amplitude * ( (SigmaZ(a[rho],tT3,tU3,N)+SigmaT(a[rho],tT3,N))*Exp(-(tCyc-tBac-(N-1)*tCap)/tU3) - SigmaT(a[rho],tT3,N) * Exp(-(tCyc-tBac-(N-1)*tCap)/tT3) ) / (1 - Exp(-tCyc/tU3) );
// Background solution
	z3 = z30 * Exp(-t[0]/tU3);
// Background period
	if (0 <= t[0] && t[0] < tBac) {
		f = z3;
	}
	// Trapping period
	if (tBac <= t[0] && t[0] <= tCyc) {
		// Untrapped populations during trapping
		Z3 = amplitude * ( (SigmaZ(a[rho],tT3,tU3,n)+SigmaT(a[rho],tT3,n))*Exp(-(t[0]-tBac-(n-1)*tCap)/tU3) - SigmaT(a[rho],tT3,n) * Exp(-(t[0]-tBac-(n-1)*tCap)/tT3) );
		f = z3 + Z3;
	}
	return f;
}
Double_t BFitNamespace::yZ1 (Double_t *t, Double_t *a) {
	extern Double_t t1;
	return a[dt]*a[epsZ]*BFitNamespace::Z1(t,a)/t1;
}
Double_t BFitNamespace::yZ2 (Double_t *t, Double_t *a) {
	extern Double_t t2;
	return a[dt]*a[epsZ]*BFitNamespace::Z2(t,a)/t2;
}
Double_t BFitNamespace::yZ3 (Double_t *t, Double_t *a) {
	extern Double_t t3;
	return a[dt]*a[epsZ]*BFitNamespace::Z3(t,a)/t3;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// X populations
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Double_t BFitNamespace::X2 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	using namespace TMath;
// externs: constant over all computations
	extern Double_t iota, tCap, tBac, tCyc, t1, t2;
// statics: recomputed many times (keep memory allocated)
	static Int_t n, N;
	static Double_t tT1, tU2, x20, x2, X2, f, amplitude, boundary;
// Initialize function value
	f = 0.0;
// Recompute variables
	tT1 = 1.0 / ( 1.0/t1 + a[gammaT1]/1000.0 ); // net variable lifetime (1/e) in ms
	tU2 = 1.0 / ( 1.0/t2 + a[gammaU2]/1000.0 ); // net variable lifetime (1/e) in ms
	n = Ceil((t[0]-tBac)/tCap);
	N = Ceil((tCyc-tBac)/tCap);
	amplitude = a[p] * a[r1] * tCap * (1/t1) * (tT1*tU2/(tU2-tT1));
// Initial value (t=0)
	x20 = amplitude * ( (SigmaZ(a[rho],tT1,tU2,N)+SigmaT(a[rho],tT1,N))*Exp(-(tCyc-tBac-(N-1)*tCap)/tU2) - SigmaT(a[rho],tT1,N) * Exp(-(tCyc-tBac-(N-1)*tCap)/tT1) ) / (1 - Exp(-tCyc/tU2) );
// Background solution
	x2 = x20 * Exp(-t[0]/tU2);
// Background period
	if (0 <= t[0] && t[0] < tBac) {
		f = x2;
	}
	// Trapping period
	if (tBac <= t[0] && t[0] <= tCyc) {
		// Untrapped populations during trapping
		X2 = amplitude * ( (SigmaZ(a[rho],tT1,tU2,n)+SigmaT(a[rho],tT1,n))*Exp(-(t[0]-tBac-(n-1)*tCap)/tU2) - SigmaT(a[rho],tT1,n) * Exp(-(t[0]-tBac-(n-1)*tCap)/tT1) );
		f = x2 + X2;
	}
	return f;
}
Double_t BFitNamespace::X3 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	using namespace TMath;
// externs: constant over all computations
	extern Double_t iota, tCap, tBac, tCyc, t2, t3;
// statics: recomputed many times (keep memory allocated)
	static Int_t n, N;
	static Double_t tT2, tU3, x30, x3, X3, f, amplitude, boundary;
// Initialize function value
	f = 0.0;
// Recompute variables
	tT2 = 1.0 / ( 1.0/t2 + a[gammaT2]/1000.0 ); // net variable lifetime (1/e) in ms
	tU3 = 1.0 / ( 1.0/t3 + a[gammaU3]/1000.0 ); // net variable lifetime (1/e) in ms
	n = Ceil((t[0]-tBac)/tCap);
	N = Ceil((tCyc-tBac)/tCap);
	amplitude = a[p] * a[r2] * tCap * (1/t2) * (tT2*tU3/(tU3-tT2));
// Initial value (t=0)
	x30 = amplitude * ( (SigmaZ(a[rho],tT2,tU3,N)+SigmaT(a[rho],tT2,N))*Exp(-(tCyc-tBac-(N-1)*tCap)/tU3) - SigmaT(a[rho],tT2,N) * Exp(-(tCyc-tBac-(N-1)*tCap)/tT2) ) / (1 - Exp(-tCyc/tU3) );
// Background solution
	x3 = x30 * Exp(-t[0]/tU3);
// Background period
	if (0 <= t[0] && t[0] < tBac) {
		f = x3;
	}
	// Trapping period
	if (tBac <= t[0] && t[0] <= tCyc) {
		// Untrapped populations during trapping
		X3 = amplitude * ( (SigmaZ(a[rho],tT2,tU3,n)+SigmaT(a[rho],tT2,n))*Exp(-(t[0]-tBac-(n-1)*tCap)/tU3) - SigmaT(a[rho],tT2,n) * Exp(-(t[0]-tBac-(n-1)*tCap)/tT2) );
		f = x3 + X3;
	}
	return f;
}
Double_t BFitNamespace::yX2 (Double_t *t, Double_t *a) {
	extern Double_t t2;
	return a[dt]*a[epsX]*BFitNamespace::X2(t,a)/t2;
}
Double_t BFitNamespace::yX3 (Double_t *t, Double_t *a) {
	extern Double_t t3;
	return a[dt]*a[epsX]*BFitNamespace::X3(t,a)/t3;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Y populations
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Double_t BFitNamespace::SigmaY2 (Double_t *a, Double_t tT1, Double_t tU1, Double_t tU2, Int_t n) {
	// a is params array
	// r is a[ri] for the species (ion rate)
	// tau is ti for the species (rad. lifetime)
	// tT1, tU1, tU2 are the modified pop. lifetimes, 1 and 2 just define the parent-child relationship and don't imply species 1 and 2
	using namespace BFitNamespace;
	using namespace TMath;
	static Double_t expT1, expU1, expU2, A, B, f;
	static Int_t k;
	extern Double_t iota, tCap;
	f = 0.0;
	A = 0.0;
	B = 0.0;
	expT1 = Exp(-tCap/tT1);
	expU1 = Exp(-tCap/tU1);
	expU2 = Exp(-tCap/tU2);
	if (n>=2) {
		for (k=1; k<=n-1; k++) {
			A += SigmaT(rho,tT1,k) * Power(expU2,n-k-1);
			B += ( (1-a[p])*SigmaT(a[rho],tT1,k) + p*(1-a[rho])*SigmaW(a[rho],tT1,tU1,k) + p*(a[gammaT1]+iota)/(tU1-tT1+iota)*tT1*tU1*SigmaZ(a[rho],tT1,tU1,n) ) * ( Power(expU2,n-k-1) - Power(expU1,n-k-1) );
//			B += ( (1-a[p])*SigmaT(a[rho],tT1,k) + p*(1-a[rho])*SigmaW(a[rho],tT1,tU1,k) + p*(a[gammaT1]+iota)/(a[gammaT1]-a[gammaU1]+iota)*SigmaZ(a[rho],tT1,tU1,n) ) * ( Power(expU2,n-k-1) - Power(expU1,n-k-1) );
//			A += SigmaT(rho,tT1,k) * Exp(-(n-k-1)*tCap/tU2);
//			B += ( (1-a[p])*SigmaT(a[rho],tT1,k) + p*(1-a[rho])*SigmaW(a[rho],tT1,tU1,k) + p*(a[gammaT1]+iota)/(a[gammaT1]-a[gammaU1]+iota)*SigmaZ(a[rho],tT1,tU1,n) ) * ( Exp(-(n-k-1)*tCap/tU2) - Exp(-(n-k-1)*tCap/tU1) );
		}
//		A *= a[p] * (a[gammaT1]+iota)/(tU1-tT1+iota) * tT1/(tU2-tT1) * ( tT1*(tU2-tU1)*expT1 - tU1*(tU2-tT1)*expU1 + tU2*(tU1-tT1)*expU2 );
		A *= a[p] * (a[gammaT1]+iota)/(tU1-tT1+iota) * tT1/(tU2-tT1);// * ( tT1*(tU2-tU1)*expT1 - tU1*(tU2-tT1)*expU1 + tU2*(tU1-tT1)*expU2 );
		B *= (expU2-expU1);
		f = A + B;
	}
	return f;
}
Double_t BFitNamespace::Y2InitialValue (Double_t *t, Double_t *a, Double_t t0, Double_t y0) {
	using namespace BFitNamespace;
	using namespace TMath;
	static Double_t tT1, tU1, tU2, cT1, cU1, cU2, expT1, expU1, expU2, tk, A, B, f;
	extern Double_t iota, tCap, tBac, t1, t2;
	tT1 = 1.0 / ( 1.0/t1 + a[gammaT1]/1000.0 ); // net variable lifetime (1/e) in ms
	tU1 = 1.0 / ( 1.0/t1 + a[gammaU1]/1000.0 ); // net variable lifetime (1/e) in ms
	tU2 = 1.0 / ( 1.0/t2 + a[gammaU2]/1000.0 ); // net variable lifetime (1/e) in ms
	f = 0.0;
	A = 0.0;
	B = 0.0;
	cT1 = tT1*(tU2-tU1);
	cU1	= tU1*(tU2-tT1);
	cU2	= tU2*(tU1-tT1);
	tk = t[0]-t0;
//	A = a[p] * (a[gammaT1]/1000.0+iota)/(tU1-tT1+iota) * tT1/(tU2-tT1) * SigmaT(a[rho],tT1,1) * (cT1*Exp(-tk/tT1) - cU1*Exp(-tk/tU1) + cU2*Exp(-tk/tU2));
//	B = ( (1-a[p])*SigmaT(a[rho],tT1,1) + a[p]*(1-a[rho])*SigmaW(a[rho],tT1,tU1,1) + a[p]*(a[gammaT1]+iota)/(a[gammaT1]-a[gammaU1]+iota)*SigmaZ(a[rho],tT1,tU1,1) ) * ( Exp(-tk/tU2) - Exp(-tk/tU1) );
//	B = ( (1-a[p])*SigmaT(a[rho],tT1,1) + a[p]*(1-a[rho]) + a[p]*(a[gammaT1]+iota)/(a[gammaT1]-a[gammaU1]+iota) ) * ( Exp(-tk/tU2) - Exp(-tk/tU1) );
	A = a[p] * (a[gammaT1]+iota)/(a[gammaT1]-a[gammaU1]+iota)/tU1/(tU2-tT1) * SigmaT(a[rho],tT1,1) * (cT1*Exp(-tk/tT1) - cU1*Exp(-tk/tU1) + cU2*Exp(-tk/tU2));
	B = ( (1-a[p])*SigmaT(a[rho],tT1,1) + a[p]*(1-a[rho])*SigmaW(a[rho],tT1,tU1,1) + a[p]*(a[gammaT1]+iota)/(a[gammaT1]-a[gammaU1]+iota)*SigmaZ(a[rho],tT1,tU1,1) ) * ( Exp(-tk/tU2) - Exp(-tk/tU1) );
	f = a[r1] * (tCap/t1) * tU1*tU2/(tU2-tU1) * (A + B);
	return y0*Exp(-(t[0]-t0)/tU2) + f;
}
Double_t BFitNamespace::myY2 (Double_t *t, Double_t *a, Int_t n) {
	using namespace BFitNamespace;
	using namespace TMath;
	static Double_t tT1, tU1, tU2, cT1, cU1, cU2, expT1, expU1, expU2, tk, A, B, f;
	static Int_t k;
	extern Double_t iota, tCap, tBac, t1, t2;
//	tT1 = 1.0 / ( 1.0/t1 + a[gammaT1]/1000.0 ); // net variable lifetime (1/e) in ms
//	tU1 = 1.0 / ( 1.0/t1 + a[gammaU1]/1000.0 ); // net variable lifetime (1/e) in ms
//	tU2 = 1.0 / ( 1.0/t2 + a[gammaU2]/1000.0 ); // net variable lifetime (1/e) in ms
	f = 0.0;
//	A = 0.0;
//	B = 0.0;
//	cT1 = tT1*(tU2-tU1);
//	cU1	= tU1*(tU2-tT1);
//	cU2	= tU2*(tU1-tT1);
	for (k=1; k<=n; k++) {
		tk = tBac+(k-1)*tCap;
//		A += SigmaT(a[rho],tT1,k) * (cT1*Exp(-tk/tT1) - cU1*Exp(-tk/tU1) + cU2*Exp(-tk/tU2));
////		A += a[p] * (a[gammaT1]/1000.0+iota)/(tU1-tT1+iota) * tT1/(tU2-tT1) * SigmaT(rho,tT1,k) * (cT1*Exp(-(t[0]-tBac-(k-1)*tCap)/tT1) - cU1*Exp(-(t[0]-tBac-(k-1)*tCap)/tU1) + cU2*Exp(-(t[0]-tBac-(k-1)*tCap)/tU2));
//		B += ( (1-a[p])*SigmaT(a[rho],tT1,k) + a[p]*(1-a[rho])*SigmaW(a[rho],tT1,tU1,k) + a[p]*(a[gammaT1]+iota)/(a[gammaT1]-a[gammaU1]+iota)*SigmaZ(a[rho],tT1,tU1,k) ) * ( Exp(-tk/tU2) - Exp(-tk/tU1) );
		f += Y2InitialValue(t, a, tk, 0.0);
	}
//	A *= a[p] * (a[gammaT1]/1000.0+iota)/(tU1-tT1+iota) * tT1/(tU2-tT1);// * ( tT1*(tU2-tU1)*expT1 - tU1*(tU2-tT1)*expU1 + tU2*(tU1-tT1)*expU2 );
//	f = a[r1] * (tCap/t1) * tU1*tU2/(tU2-tU1) * (A + B);
	return f;
}

Double_t BFitNamespace::Y3InitialValue (Double_t *t, Double_t *a, Double_t t0, Double_t y0) {
	using namespace BFitNamespace;
	using namespace TMath;
	static Double_t tx, tT1, tT2, tU1, tU2, tU3, expT1, expT2, expU1, expU2, expU3, ThetaU, ThetaY, ST1, SW11, SZ11, ST2, SW22, SZ12, SZ22, bU1, bU2, bU3, dT1, dU1, dU2, dU3, V, W, Z, X, Y, f;
	static Double_t cZT2, cZU2, cZU3, cXT1, cXU2, cXU3, cYU1, cYU2, cYU3;
	static Double_t ampV, ampW, ampZ, ampX, ampY_ST1, ampY_SW11, ampY_SZ11;
	extern Double_t iota, tCap, tBac, t1, t2, t3;
	tT1 = 1.0 / ( 1.0/t1 + a[gammaT1]/1000.0 ); // net variable lifetime (1/e) in ms
	tT2 = 1.0 / ( 1.0/t2 + a[gammaT2]/1000.0 ); // net variable lifetime (1/e) in ms
	tU1 = 1.0 / ( 1.0/t1 + a[gammaU1]/1000.0 ); // net variable lifetime (1/e) in ms
	tU2 = 1.0 / ( 1.0/t2 + a[gammaU2]/1000.0 ); // net variable lifetime (1/e) in ms
	tU3 = 1.0 / ( 1.0/t3 + a[gammaU3]/1000.0 ); // net variable lifetime (1/e) in ms
	f = V = W = X = Y = Z = 0.0;
//	printf("%f %f %f %f %f %f\n",f,V,W,X,Y,Z);
	ThetaU	= (tU3-tU2)*(tU3-tU1)*(tU2-tU1);
	ThetaY	= (tU3-tT1)*(tU2-tT1)*(tU1-tT1);
	ampV		= a[r2]*tCap*tU2*tU3/(tU3-tU2)/t2*(1-a[p]);
	ampW		= a[r2]*tCap*tU2*tU3/(tU3-tU2)/t2*a[p]*(1-a[rho]);
	ampZ		= a[r2]*tCap*tU2*tU3/(tU3-tU2)/t2*a[p]*(a[gammaT2]+iota)/(a[gammaT2]-a[gammaU2]+iota); // after a[p], ampZ and ampX are complementary parts of T1 decay (1/t1 and a[gammaT1] : radioactive and non-radioactive)
	ampX		= a[r1]*tCap*tU2*tU3/(tU3-tU2)/t2*a[p]*tT1*tU2/(tU2-tT1)/t1; // a[gammaT2]/(a[gammaT2]-a[gammaU2]) is a simplification of tT2*tU2/(tU2-tT2)/(1/a[gammaT2])
	ampY_ST1	= a[r1]*tCap*(tU1*tU2*tU3/ThetaU)*((a[gammaT1]+iota)/(a[gammaT1]-a[gammaU1]+iota)/t1/t2)*(tU1-tT1)/tU1/(a[gammaT1]/1000.0)/ThetaY;
	ampY_SW11	= a[r1]*tCap*a[p]*tU1*tU2*tU3/ThetaU/t1/t2*(1-a[rho]);
	ampY_SZ11	= a[r1]*tCap*a[p]*tU1*tU2*tU3/ThetaU/t1/t2*(a[gammaT1]+iota)/(a[gammaT1]-a[gammaU1]+iota);
	cZT2	= tT2*(tU3-tU2);
	cZU2	= tU2*(tU3-tT2);
	cZU3	= tU3*(tU2-tT2);
	cXT1	= tT1*(tU3-tU2);
	cXU2	= tU2*(tU3-tT1);
	cXU3	= tU3*(tU2-tT1);
	cYU1	= tU1*(tU3-tU2);
	cYU2	= tU2*(tU3-tU1);
	cYU3	= tU3*(tU2-tU1);
	tx		= t[0]-t0;
	Int_t k	= 1;
//	Int_t k	= Ceil((t[0]-tBac)/tCap);
	Double_t tp[1] = {t0};
	Double_t tN[1] = {0.0};
	Double_t v20 = V2(tp,a);
	Double_t w20 = W2(tp,a);
	Double_t x20 = X2(tp,a);
	Double_t y20 = Y2(tp,a);
	Double_t z20 = Z2(tp,a);
	expT1	= Exp(-tx/tT1);
	expT2	= Exp(-tx/tT2);
	expU1	= Exp(-tx/tU1);
	expU2	= Exp(-tx/tU2);
	expU3	= Exp(-tx/tU3);
	ST1		= SigmaT(a[rho],tT1,k);
	ST2		= SigmaT(a[rho],tT2,k);
	SW11	= SigmaW(a[rho],tT1,tU1,k);
	SW22	= SigmaW(a[rho],tT2,tU2,k);
	SZ11	= SigmaZ(a[rho],tT1,tU1,k);
	SZ12	= SigmaZ(a[rho],tT1,tU2,k);
	SZ22	= SigmaZ(a[rho],tT2,tU2,k);
	V = ampV * ST2  * (expU3 - expU2); // feeding from V2
	W = ampW * SW22 * (expU3 - expU2); // feeding from W2
//	Z = z20 * tU2*tU3/(tU3-tU2)/t2 * (expU3-expU2) + ampZ * ( (ST2/cZU2)*(cZT2*expT2-cZU2*expU2+cZU3*expU3) + SZ22*(expU3-expU2) );  // feeding from Z2
	Z = ampZ * ( (ST2/cZU2)*(cZT2*expT2-cZU2*expU2+cZU3*expU3) + SZ22*(expU3-expU2) );  // feeding from Z2
	X = ampX * ( (ST1/cXU2)*(cXT1*expT1-cXU2*expU2+cXU3*expU3) + SZ12*(expU3-expU2) );
	Y = ampY_ST1 * ST1 * 0.001 * ( // 0.001 for the a[gammaT1] from 1/s to 1/ms
			- expT1 * tT1*tT1*(tU3-tU2)*(tU3-tU1)*(tU2-tU1)*a[p]*a[gammaT1]
			+ expU1 * tU1*tU1*(tU3-tU2)*(tU3-tT1)*(tU2-tT1)*(a[gammaT1] - (1-a[p])*a[gammaU1])
			- expU2 * tU2*(tU3-tU1)*(tU3-tT1)*((a[gammaT1])*(tU1*tU2-tT1*(a[p]*tU2+(1-a[p])*tU1))-(a[gammaU1])*(1-a[p])*tU1*(tU2-tT1))
			+ expU3 * tU3*(tU2-tU1)*(tU2-tT1)*((a[gammaT1])*(tU1*tU3-tT1*(a[p]*tU3+(1-a[p])*tU1))-(a[gammaU1])*(1-a[p])*tU1*(tU3-tT1)) )
		+ ampY_SW11 * SW11 * ( cYU1*expU1 - cYU2*expU2 + cYU3*expU3 );
		+ ampY_SZ11 * SZ11 * ( cYU1*expU1 - cYU2*expU2 + cYU3*expU3 );
//	printf("SZ11 term = %f\n",SZ11);
//	if ((int)t[0]%1000==0 && t[0] != 246000.0) printf("%8f, %8f, %8f, %8f, %8f, %8f, %8f, %8f\n", t[0], ST1, ST2, SW11, SW22, SZ11, SZ12, SZ22);
//	if ((int)t[0]%10000==0 && t[0] != 246000.0) printf("t=%8f, tp=%8f, ampV%8f, ampW%8f, ampZ%8f, ampX%8f, ampY%8f\n", t[0], tp[0], ampV, ampW, ampZ, ampX, ampY_ST1);
//	if ((int)t[0]%10000==0 && t[0] != 246000.0) printf("t=%8f, tp=%8f, (V2)%8f, (W2)%8f, (Z2)%8f, (X2)%8f, (Y2)%8f\n", t[0], tp[0], V, W, Z, X, Y);
//	if ((int)t[0]%10000==0 && t[0] != 246000.0) printf("t=%8f, tp=%8f, v20=%8f, w20=%8f, z20=%8f, x20=%8f, y20=%8f\n", t[0], tp[0], v20, w20, z20, x20, y20);
//	f = y0*expU3 + y20 * tU2*tU3/(tU3-tU2)/t2 * (expU3-expU2) + V + W + X + Y + Z;
	
	Double_t u10, u20;
//	y20		= V2(tp,a) + W2(tp,a) + X2(tp,a) + Y2(tp,a) + Z2(tp,a);
//	y20		= Y2(tN,a);
//	y20		= 0.0;
//	u10 = V1(tp,a) + W1(tp,a) + Z1(tp,a);
//	u20 = V2(tp,a) + W2(tp,a) + Z2(tp,a) + X2(tp,a) + Y2(tp,a);
//	f +=   y0 * Exp(-t[0]/tU3)
//		+ u20 * tU2/t2 * tU3/(tU3-tU2) * ( Exp(-t[0]/tU3) - Exp(-t[0]/tU2) )
//		+ u10 * tU1/t1 * tU2/t2 * tU3/ThetaU * ( tU1 * (tU3-tU2) * Exp(-t[0]/tU1) - tU2 * (tU3-tU1) * Exp(-t[0]/tU2) + tU3 * (tU2-tU1) * Exp(-t[0]/tU3) );
//	f +=   y0 * expU3
//		+ u20 * tU2/t2 * tU3/(tU3-tU2) * ( expU3 - expU2 )
//		+ u10 * tU1/t1 * tU2/t2 * tU3/ThetaU * ( tU1 * (tU3-tU2) * expU1 - tU2 * (tU3-tU1) * expU2 + tU3 * (tU2-tU1) * expU3 );
	f += y0 * expU3;
//	f += y20 * tU2*tU3/(tU3-tU2)/t2 * (expU3-expU2);
	f += V + W + X + Y + Z;
	return f;
//	return 0.0;
}
/*
//Version 2
Double_t BFitNamespace::Y3InitialValue (Double_t *t, Double_t *a, Double_t t0, Double_t y0) {
	using namespace BFitNamespace;
	using namespace TMath;
	static Double_t tx, tT1, tT2, tU1, tU2, tU3, expT1, expT2, expU1, expU2, expU3, ThetaU, ThetaY, ST1, SW11, SZ11, ST2, SW22, SZ12, SZ22, bU1, bU2, bU3, dT1, dU1, dU2, dU3, V, W, Z, X, Y, f;
	static Double_t cZT2, cZU2, cZU3, cXT1, cXU2, cXU3, cYU1, cYU2, cYU3;
	static Double_t y20, ampV, ampW, ampZ, ampX, ampY_ST1, ampY_SW11, ampY_SZ11;
	extern Double_t iota, tCap, tBac, t1, t2, t3;
	tT1 = 1.0 / ( 1.0/t1 + a[gammaT1]/1000.0 ); // net variable lifetime (1/e) in ms
	tT2 = 1.0 / ( 1.0/t2 + a[gammaT2]/1000.0 ); // net variable lifetime (1/e) in ms
	tU1 = 1.0 / ( 1.0/t1 + a[gammaU1]/1000.0 ); // net variable lifetime (1/e) in ms
	tU2 = 1.0 / ( 1.0/t2 + a[gammaU2]/1000.0 ); // net variable lifetime (1/e) in ms
	tU3 = 1.0 / ( 1.0/t3 + a[gammaU3]/1000.0 ); // net variable lifetime (1/e) in ms
	f = V = W = X = Y = Z = 0.0;
	ThetaU	= (tU3-tU2)*(tU3-tU1)*(tU2-tU1);
	ThetaY	= (tU3-tT1)*(tU2-tT1)*(tU1-tT1);
	ampV = ampW	= a[r2]*tCap*tU2*tU3/(tU3-tU2)/t2;
	ampZ		= a[r2]*tCap*tU2*tU3/(tU3-tU2)/t2*a[p]*(a[gammaT2]+iota)/(a[gammaT2]-a[gammaU2]+iota); // after a[p], ampZ and ampX are complementary parts (1/t1 and a[gammaT1])
	ampX		= a[r2]*tCap*tU2*tU3/(tU3-tU2)/t2*a[p]*tT1*tU2/(tU2-tT1)/t1; // a[gammaT2]/(a[gammaT2]-a[gammaU2]) is a simplification of tT2*tU2/(tU2-tT2)/(1/a[gammaT2])
	ampY_ST1	= a[r1]*tCap*tU1*tU2*tU3/ThetaU*(a[gammaT1]+iota)/(a[gammaT1]-a[gammaU1]+iota)/t1/t2*(tU1-tT1)/tU1/(a[gammaT1]/1000.0)/ThetaY;
	ampY_SW11	= a[r1]*tCap*tU1*tU2*tU3/ThetaU*(a[gammaT1]+iota)/(a[gammaT1]-a[gammaU1]+iota)/t1/t2*a[p];
	ampY_SZ11	= a[r1]*tCap*tU1*tU2*tU3/ThetaU*(a[gammaT1]+iota)/(a[gammaT1]-a[gammaU1]+iota)/t1/t2*a[p];
	cZT2	= tT2*(tU3-tU2);
	cZU2	= tU2*(tU3-tT2);
	cZU3	= tU3*(tU2-tT2);
	cXT1	= tT1*(tU3-tU2);
	cXU2	= tU2*(tU3-tT1);
	cXU3	= tU3*(tU2-tT1);
	cYU1	= tU1*(tU3-tU2);
	cYU2	= tU2*(tU3-tU1);
	cYU3	= tU3*(tU2-tU1);
	Double_t t0array[1] = {t0};
//	y20		= Y2(t0array,a);
	tx		= t[0]-t0;
	Int_t k	= 1;
//	Int_t k	= Ceil((t[0]-tBac)/tCap);
	expT1	= Exp(-tx/tT1);
	expT2	= Exp(-tx/tT2);
	expU1	= Exp(-tx/tU1);
	expU2	= Exp(-tx/tU2);
	expU3	= Exp(-tx/tU3);
	ST1		= SigmaT(a[rho],tT1,k);
	ST2		= SigmaT(a[rho],tT2,k);
	SW11	= SigmaW(a[rho],tT1,tU1,k);
	SW22	= SigmaW(a[rho],tT2,tU2,k);
	SZ11	= SigmaZ(a[rho],tT1,tU1,k);
	SZ12	= SigmaZ(a[rho],tT1,tU2,k);
	SZ22	= SigmaZ(a[rho],tT2,tU2,k);
	V += ampV * (1-a[p]) * ST2 * (expU3 - expU2); // feeding from V2
	W += ampW * a[p] * (1-a[rho]) * SW22 * (expU3 - expU2); // feeding from W2
	Z += ampZ * ( ST2/cZU2 * (cZT2*expT2 - cZU2*expU2 + cZU3*expU3) + SZ22 * ( expU3 - expU2 ) );  // feeding from Z2
	X += ampX * ( ST1/cXU2 * (cXT1*expT1 - cXU2*expU2 + cXU3*expU3) + SZ12 * ( expU3 - expU2 ) );
	Y += ampY_ST1 * (
			- expT1 * tT1*tT1*(tU3-tU2)*(tU3-tU1)*(tU2-tU1)*a[p]*a[gammaT1]/1000.0
			+ expU1 * tU1*tU1*(tU3-tU2)*(tU3-tT1)*(tU2-tT1)*(a[gammaT1]/1000.0 - (1-a[p])*a[gammaU1]/1000.0)
			- expU2 * tU2*(tU3-tU1)*(tU3-tT1)*((a[gammaT1]/1000.0)*(tU1*tU2-tT1*(a[p]*tU2+(1-a[p])*tU1))-(a[gammaU1]/1000.0)*(1-a[p])*tU1*(tU2-tT1))
			+ expU3 * tU3*(tU2-tU1)*(tU2-tT1)*((a[gammaT1]/1000.0)*(tU1*tU3-tT1*(a[p]*tU3+(1-a[p])*tU1))-(a[gammaU1]/1000.0)*(1-a[p])*tU1*(tU3-tT1)) )
		+ ampY_SW11 * ( cYU1*expU1 - cYU2*expU2 + cYU3*expU3 );
		+ ampY_SZ11 * ( cYU1*expU1 - cYU2*expU2 + cYU3*expU3 );
//	printf("SZ11 term = %f\n",SZ11);
//	if ((int)t[0]%1000==0 && t[0] != 246000.0) printf("%8f, %8f, %8f, %8f, %8f, %8f\n",t[0],V,W,Z,X,Y);
	f = y0*expU3 + y20 * tU2*tU3/(tU3-tU2)/t2 * (expU3-expU2) + V + W + X + Y + Z;
	return f;
//	return 0.0;
}
*/
/* Version 1
Double_t BFitNamespace::Y3InitialValue (Double_t *t, Double_t *a, Double_t t0, Double_t y0) {
	using namespace BFitNamespace;
	using namespace TMath;
	static Double_t tk, tT1, tT2, tU1, tU2, tU3, expT1, expT2, expU1, expU2, expU3, ThetaU, ST1, SW11, SZ11, ST2, SW22, SZ12, SZ22, bU1, bU2, bU3, cT2, cU2, cU3, dT1, dU1, dU2, dU3, A, B, C, D, X, f;
	static Int_t k;
	extern Double_t iota, tCap, tBac, t1, t2, t3;
	tT1 = 1.0 / ( 1.0/t1 + a[gammaT1]/1000.0 ); // net variable lifetime (1/e) in ms
	tT2 = 1.0 / ( 1.0/t2 + a[gammaT2]/1000.0 ); // net variable lifetime (1/e) in ms
	tU1 = 1.0 / ( 1.0/t1 + a[gammaU1]/1000.0 ); // net variable lifetime (1/e) in ms
	tU2 = 1.0 / ( 1.0/t2 + a[gammaU2]/1000.0 ); // net variable lifetime (1/e) in ms
	tU3 = 1.0 / ( 1.0/t3 + a[gammaU3]/1000.0 ); // net variable lifetime (1/e) in ms
	f		= 0.0;
	A		= 0.0;
	B		= 0.0;
	C		= 0.0;
	D		= 0.0;
	X		= 0.0;
	cT2		= tT2*(tU3-tU2);
	cU2		= tU2*(tU3-tT2);
	cU3		= tU3*(tU2-tT2);
	bU1		= tU1*(tU3-tU2);
	bU2		= tU2*(tU3-tU1);
	bU3		= tU3*(tU2-tU1);
	dT1		= a[p]*(a[gammaT1]/1000.0)*Power(tT1,3)/(tU3-tT1)/(tU2-tT1)/(tU1-tT1);
	dU1		= (a[p]*(a[gammaT1]/1000.0)*tT1*tU1/(tU1-tT1)+(1-a[p]))*tU1*(tU3-tU2)/ThetaU;
	dU2		= (a[p]*(a[gammaT1]/1000.0)*tT1*tU2/(tU2-tT1)+(1-a[p]))*tU2*(tU3-tU1)/ThetaU;
	dU3		= (a[p]*(a[gammaT1]/1000.0)*tT1*tU3/(tU3-tT1)+(1-a[p]))*tU3*(tU2-tU1)/ThetaU;
	ThetaU	= (tU3-tU2)*(tU3-tU1)*(tU2-tU1);
	for (k=1; k<=1; k++) {
		tk		= t[0]-t0;
		expT1	= Exp(-tk/tT1);
		expT2	= Exp(-tk/tT2);
		expU1	= Exp(-tk/tU1);
		expU2	= Exp(-tk/tU2);
		expU3	= Exp(-tk/tU3);
		ST1		= SigmaT(a[rho],tT1,k);
		ST2		= SigmaT(a[rho],tT2,k);
		SW11	= SigmaW(a[rho],tT1,tU1,k);
		SW22	= SigmaW(a[rho],tT2,tU2,k);
		SZ11	= SigmaZ(a[rho],tT1,tU1,k);
		SZ12	= SigmaZ(a[rho],tT1,tU2,k);
		SZ22	= SigmaZ(a[rho],tT2,tU2,k);
		A += ST2 * (cT2*expT2 - cU2*expU2 + cU3*expU3);
		B += ( (1-a[p])*ST2 + a[p]*(1-a[rho])*SW22 + a[p]*(a[gammaT2]+iota)/(a[gammaT2]-a[gammaU2]+iota)*SZ22 ) * ( expU3 - expU2 );
		C += ST1 * ( dT1*expT1 +  dU1*expU1 - dU2*expU2 + dU3*expU3);
		D += ( (1-a[rho])*SW11 + (a[gammaT1]+iota)/(a[gammaT1]-a[gammaU1]+iota)*SZ11 ) * (bU1*expU1 - bU2*expU2 + bU3*expU3) / ThetaU;
		X += SZ12 * ( expU3 - expU2 ) + ST1 * 1.0/tU2/(tU3-tU2) * ( tT1*(tU3-tU2)*expT1 - tU2*(tU3-tT1)*expU2 + tU3*(tU2-tT1)*expU3);
	}
	X *= 
	A *= a[p] * (a[gammaT2]/1000.0+iota)/(tU2-tT2+iota) * tT2/(tU3-tT2);
	f = a[r2]*(tCap/t2)*tU2*tU3/(tU3-tU2)*(A+B)
		+ a[r1]*(tCap/t1)*tU1*tU2*tU3/t2*(C+D)
		+ a[p]*a[r1]*(tCap/t2)*tU2*tU3/(tU3-tU2)*((1.0/t1)+iota)/((1.0/t1)-a[gammaU2]+iota)*X;
//	printf("SZ11 term = %f\n",SZ11);
	return y0*Exp(-(t[0]-t0)/tU3) + f;
//	return 0.0;
}*/
//Double_t BFitNamespace::myY3 (Double_t *t, Double_t *a, Double_t tT1, Double_t tT2, Double_t tU1, Double_t tU2, Double_t tU3, Int_t n) {
Double_t BFitNamespace::myY3 (Double_t *t, Double_t *a, Int_t n) {
	using namespace BFitNamespace;
	using namespace TMath;
	static Double_t tk, expT1, expT2, expU1, expU2, expU3, ThetaU, ST1, SW11, SZ11, ST2, SW22, SZ22, bU1, bU2, bU3, cT2, cU2, cU3, dT1, dU1, dU2, dU3, A, B, C, D, f;
	static Double_t tT1, tT2, tU1, tU2, tU3;
	static Int_t k;
	extern Double_t iota, tCap, tBac, tCyc, t1, t2, t3;
	if (t[0] < tBac || t[0] > tCyc) f=0.0;
	else {
		f	= 0.0;
		tT1 = 1.0 / ( 1.0/t1 + a[gammaT1]/1000.0 ); // net variable lifetime (1/e) in ms
		tT2 = 1.0 / ( 1.0/t2 + a[gammaT2]/1000.0 ); // net variable lifetime (1/e) in ms
		tU1 = 1.0 / ( 1.0/t1 + a[gammaU1]/1000.0 ); // net variable lifetime (1/e) in ms
		tU2 = 1.0 / ( 1.0/t2 + a[gammaU2]/1000.0 ); // net variable lifetime (1/e) in ms
		tU3 = 1.0 / ( 1.0/t3 + a[gammaU3]/1000.0 ); // net variable lifetime (1/e) in ms
/*		A		= 0.0;
		B		= 0.0;
		C		= 0.0;
		D		= 0.0;
		cT2		= tT2*(tU3-tU2);
		cU2		= tU2*(tU3-tT2);
		cU3		= tU3*(tU2-tT2);
		bU1		= tU1*(tU3-tU2);
		bU2		= tU2*(tU3-tU1);
		bU3		= tU3*(tU2-tU1);
		dT1		= a[p]*(a[gammaT1]/1000.0)*Power(tT1,3)/(tU3-tT1)/(tU2-tT1)/(tU1-tT1);
		dU1		= (a[p]*(a[gammaT1]/1000.0)*tT1*tU1/(tU1-tT1)+(1-a[p]))*tU1*(tU3-tU2)/ThetaU;
		dU2		= (a[p]*(a[gammaT1]/1000.0)*tT1*tU2/(tU2-tT1)+(1-a[p]))*tU2*(tU3-tU1)/ThetaU;
		dU3		= (a[p]*(a[gammaT1]/1000.0)*tT1*tU3/(tU3-tT1)+(1-a[p]))*tU3*(tU2-tU1)/ThetaU;
		ThetaU	= (tU3-tU2)*(tU3-tU1)*(tU2-tU1);
		for (k=1; k<=n; k++) {
			tk		= t[0]-(tBac+(k-1)*tCap);
			expT1	= Exp(-tk/tT1);
			expT2	= Exp(-tk/tT2);
			expU1	= Exp(-tk/tU1);
			expU2	= Exp(-tk/tU2);
			expU3	= Exp(-tk/tU3);
			ST1		= SigmaT(a[rho],tT1,k);
			ST2		= SigmaT(a[rho],tT2,k);
			SW11	= SigmaW(a[rho],tT1,tU1,k);
			SW22	= SigmaW(a[rho],tT2,tU2,k);
			SZ11	= SigmaZ(a[rho],tT1,tU1,k);
			SZ22	= SigmaZ(a[rho],tT2,tU2,k);
			A += ST2 * (cT2*expT2 - cU2*expU2 + cU3*expU3);
			B += ( (1-a[p])*ST2 + a[p]*(1-a[rho])*SW22 + a[p]*(a[gammaT2]+iota)/(a[gammaT2]-a[gammaU2]+iota)*SZ22 ) * ( expU3 - expU2 );
			C += ST1 * ( dT1*expT1 +  dU1*expU1 - dU2*expU2 + dU3*expU3);
			D += ( (1-a[rho])*SW11 + (a[gammaT1]+iota)/(a[gammaT1]-a[gammaU1]+iota)*SZ11 ) * (bU1*expU1 - bU2*expU2 + bU3*expU3) / ThetaU;
*/			
		for (k=1; k<=n; k++) {
			tk		= tBac+(k-1)*tCap;
			f += Y3InitialValue(t, a, tk, 0.0);
		}
//		A *= a[p] * (a[gammaT2]/1000.0+iota)/(tU2-tT2+iota) * tT2/(tU3-tT2);
//		f = a[r2]*(tCap/t2)*tU2*tU3/(tU3-tU2)*(A+B) + a[r1]*(tCap/t1)*tU1*tU2*tU3/t2*(C+D);
//		printf("t=%f,myY3=%f\n",t[0],f);
	}
	if ((int)t[0]%10000==0 && t[0] != 246000.0) printf("t=%8f, myY3(t)=%8f\n", t[0], f);
	return f;
}
Double_t BFitNamespace::Y2 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	using namespace TMath;
	static Int_t n, N;
	static Double_t tT1, tU1, tU2, tn, tN, An, AN, Bn, BN, cT1, cU1, cU2, amplitude, u10, y20, y2, Y2, f, A, B;
	static Double_t expT1n, expU1n, expU2n;
	static Double_t expT1N, expU1N, expU2N;
	extern Double_t iota, tCap, tBac, tCyc, t1, t2, t3;
//	bookGlobals();
	tT1 = 1.0 / ( 1.0/t1 + a[gammaT1]/1000.0 ); // net variable lifetime (1/e) in ms
	tU1 = 1.0 / ( 1.0/t1 + a[gammaU1]/1000.0 ); // net variable lifetime (1/e) in ms
//	tT2 = 1.0 / ( 1.0/t2 + a[gammaT2]/1000.0 ); // net variable lifetime (1/e) in ms
	tU2 = 1.0 / ( 1.0/t2 + a[gammaU2]/1000.0 ); // net variable lifetime (1/e) in ms
	f = 0.0; //catch bad values of t[0]
	A = 0.0;
	B = 0.0;
	n = Ceil((t[0]-tBac)/tCap);
	N = Ceil((tCyc-tBac)/tCap);
//	tn	= t[0]-tBac-(n-1)*tCap;
//	tN	= tCyc-tBac-(N-1)*tCap;
//	expT1n	= Exp(-(t[0]-tBac-(n-1)*tCap)/tT1);
//	expU1n	= Exp(-(t[0]-tBac-(n-1)*tCap)/tU1);
//	expU2n	= Exp(-(t[0]-tBac-(n-1)*tCap)/tU2);
//	expT1N	= Exp(-(tCyc-tBac-(N-1)*tCap)/tT1);
//	expU1N	= Exp(-(tCyc-tBac-(N-1)*tCap)/tU1);
//	expU2N	= Exp(-(tCyc-tBac-(N-1)*tCap)/tU2);
//	An	= a[p] * (a[gammaT1]+iota)/(a[gammaT1]-a[gammaU1]+iota) * tT1/(tU2-tT1) * SigmaT(a[rho],tT1,n);
//	AN	= a[p] * (a[gammaT1]+iota)/(a[gammaT1]-a[gammaU1]+iota) * tT1/(tU2-tT1) * SigmaT(a[rho],tT1,N);
//	Bn	= (1-a[p]) * SigmaT(a[rho],tT1,n) + p * (1-a[rho]) * SigmaW(a[rho],tT1,tU1,n) + p * (a[gammaT1]+iota)/(a[gammaT1]-a[gammaU1]+iota) * SigmaZ(a[rho],tT1,tU1,n);
//	BN	= (1-a[p]) * SigmaT(a[rho],tT1,N) + p * (1-a[rho]) * SigmaW(a[rho],tT1,tU1,N) + p * (a[gammaT1]+iota)/(a[gammaT1]-a[gammaU1]+iota) * SigmaZ(a[rho],tT1,tU1,N);
//	An	= a[p] * (a[gammaT1]+iota)/(tU1-tT1+iota) * tT1/(tU2-tT1) * SigmaT(a[rho],tT1,n);
//	AN	= a[p] * (a[gammaT1]+iota)/(tU1-tT1+iota) * tT1/(tU2-tT1) * SigmaT(a[rho],tT1,N);
//	Bn	= (1-a[p]) * SigmaT(a[rho],tT1,n) + p * (1-a[rho]) * SigmaW(a[rho],tT1,tU1,n) + p * (a[gammaT1]+iota)/(tU1-tT1+iota) * tT1/(tU2-tT1) * SigmaZ(a[rho],tT1,tU1,n);
//	BN	= (1-a[p]) * SigmaT(a[rho],tT1,N) + p * (1-a[rho]) * SigmaW(a[rho],tT1,tU1,N) + p * (a[gammaT1]+iota)/(tU1-tT1+iota) * tT1*tU1 * SigmaZ(a[rho],tT1,tU1,N);
//	cT1 = tT1*(tU2-tU1);
//	cU1	= tU1*(tU2-tT1);
//	cU2	= tU2*(tU1-tT1);
//	amplitude = a[r1] * (tCap/t1) * tU1*tU2/(tU2-tU1);
// Initial value (t=0)
//	y20 = amplitude * ( SigmaY2(a,tT1,tU1,tU2,N)*Exp(-tN/tU2) + ( AN * ( cT1*Exp(-tN/tT1) - cU1*Exp(-tN/tU1) + cU2*Exp(-tN/tU2) ) + BN * ( Exp(-tN/tU2) - Exp(-tN/tU1) ) ) ) / (1 - Exp(-tCyc/tU2) );
//	y20 = amplitude * ( SigmaY2(a,tT1,tU1,tU2,N)*expU2N + ( AN * ( cT1*expT1N - cU1*expU1N + cU2*expU2N ) + BN * ( expU2N - expU1N ) ) ) / (1 - Exp(-tCyc/tU2) );
	Double_t tNN[1] = {tCyc};
//	y20 = 0;//myY2(tNN,a,tT1,tU1,tU2,N);
	u10 = V1(tNN,a) + W1(tNN,a) + Z1(tNN,a);
	y20 = myY2(tNN,a,N);
// Background solution
//	y2 = Y2InitialValue(t, a, 0.0, y20);
	y2 = y20 * Exp(-t[0]/tU2) + u10 * tU1/t1 * tU2/(tU2-tU1) * ( Exp(-t[0]/tU2) - Exp(-t[0]/tU1 ) );
// Background period
	if (0 <= t[0] && t[0] < tBac) {
		f = y2;
	}
// Trapping period
	if (tBac <= t[0] && t[0] <= tCyc) {
		f = y2 + myY2(t,a,n);
/*
// Untrapped populations during trapping
//		Y2 = amplitude * ( SigmaY2(a,tT1,tU1,tU2,n)*expU2n + ( An * ( cT1*expT1n - cU1*expU1n + cU2*expU2n ) + Bn * ( expU2n - expU1n ) ) );
//		f = y2 + Y2;
		for (Int_t k=1; k<=n-1; k++) {
			A += SigmaT(rho,tT1,k) * (cT1*Exp(-(t[0]-tBac-(k-1)*tCap)/tT1) - cU1*Exp(-(t[0]-tBac-(k-1)*tCap)/tU1) + cU2*Exp(-(t[0]-tBac-(k-1)*tCap)/tU2));
			B += ( (1-a[p])*SigmaT(a[rho],tT1,k) + p*(1-a[rho])*SigmaW(a[rho],tT1,tU1,k) + p*(a[gammaT1]+iota)/(tU1-tT1+iota)*tT1*tU1*SigmaZ(a[rho],tT1,tU1,n) ) * ( Exp(-(t[0]-tBac-(k-1)*tCap)/tU2) - Exp(-(t[0]-tBac-(k-1)*tCap)/tU1) );
//			B += ( (1-a[p])*SigmaT(a[rho],tT1,k) + p*(1-a[rho])*SigmaW(a[rho],tT1,tU1,k) + p*(a[gammaT1]+iota)/(a[gammaT1]-a[gammaU1]+iota)*SigmaZ(a[rho],tT1,tU1,n) ) * ( Power(expU2,n-k-1) - Power(expU1,n-k-1) );
//			A += SigmaT(rho,tT1,k) * Exp(-(n-k-1)*tCap/tU2);
//			B += ( (1-a[p])*SigmaT(a[rho],tT1,k) + p*(1-a[rho])*SigmaW(a[rho],tT1,tU1,k) + p*(a[gammaT1]+iota)/(a[gammaT1]-a[gammaU1]+iota)*SigmaZ(a[rho],tT1,tU1,n) ) * ( Exp(-(n-k-1)*tCap/tU2) - Exp(-(n-k-1)*tCap/tU1) );
		}
//		A *= a[p] * (a[gammaT1]+iota)/(tU1-tT1+iota) * tT1/(tU2-tT1) * ( tT1*(tU2-tU1)*expT1 - tU1*(tU2-tT1)*expU1 + tU2*(tU1-tT1)*expU2 );
		A *= a[p] * (a[gammaT1]+iota)/(tU1-tT1+iota) * tT1/(tU2-tT1);// * ( tT1*(tU2-tU1)*expT1 - tU1*(tU2-tT1)*expU1 + tU2*(tU1-tT1)*expU2 );
//		B *= (expU2-expU1);
		f = A + B;
*/
	}
	return f;
}
Double_t BFitNamespace::Y3 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	using namespace TMath;
	static Int_t n, N;
	static Double_t tT1, tT2, tU1, tU2, tU3, tn, tN, An, AN, Bn, BN, cT1, cU1, cU2, amplitude, u10, u20, y30, y3, Y3, f, A, B, ThetaU;
	static Double_t expT1n, expU1n, expU2n;
	static Double_t expT1N, expU1N, expU2N;
	extern Double_t iota, tCap, tBac, tCyc, t1, t2, t3;
//	bookGlobals();
	tT1 = 1.0 / ( 1.0/t1 + a[gammaT1]/1000.0 ); // net variable lifetime (1/e) in ms
	tU1 = 1.0 / ( 1.0/t1 + a[gammaU1]/1000.0 ); // net variable lifetime (1/e) in ms
	tT2 = 1.0 / ( 1.0/t2 + a[gammaT2]/1000.0 ); // net variable lifetime (1/e) in ms
	tU2 = 1.0 / ( 1.0/t2 + a[gammaU2]/1000.0 ); // net variable lifetime (1/e) in ms
//	tT3 = 1.0 / ( 1.0/t3 + a[gammaT3]/1000.0 ); // net variable lifetime (1/e) in ms
	tU3 = 1.0 / ( 1.0/t3 + a[gammaU3]/1000.0 ); // net variable lifetime (1/e) in ms
	ThetaU	= (tU3-tU2)*(tU3-tU1)*(tU2-tU1);
	f = 0.0; //catch bad values of t[0]
	A = 0.0;
	B = 0.0;
	n = Ceil((t[0]-tBac)/tCap);
	N = Ceil((tCyc-tBac)/tCap);
	Double_t tNN[1] = {tCyc};
//	y30 = 0;
//	y30 = myY3(tNN,a,tT1,tT2,tU1,tU2,tU3,N);
	u10 = V1(tNN,a) + W1(tNN,a) + Z1(tNN,a);
	u20 = V2(tNN,a) + W2(tNN,a) + Z2(tNN,a) + X2(tNN,a) + Y2(tNN,a);
	y30 = myY3(tNN,a,N)/(1-Exp(-tCyc/tU3));
	printf("y30 = %8f\n",y30);
//	printf("y30 = %f\n",y30);
// Background solution
//	y3 = 0.0;
	y3 = y30*Exp(-t[0]/tU3);
//	y3 = Y3InitialValue(t, a, 0.0, y30);
//	y3 = 
//		y30 * Exp(-t[0]/tU3) + 
//		u20 * tU2/t2 * tU3/(tU3-tU2) * ( Exp(-t[0]/tU3) - Exp(-t[0]/tU2) ) + 
//		u10 * tU1/t1 * tU2/t2 * tU3/ThetaU * ( tU1 * (tU3-tU2) * Exp(-t[0]/tU1) - tU2 * (tU3-tU1) * Exp(-t[0]/tU2) + tU3 * (tU2-tU1) * Exp(-t[0]/tU3) );
	if (t[0] == 0.0) printf("t = 0, Y3 = %f\n", y3);
// Background period
	if (0 <= t[0] && t[0] < tBac) {
		f = y3;
	}
// Trapping period
	if (tBac <= t[0] && t[0] <= tCyc) {
//		f = y3 + myY3(t,a,tT1,tT2,tU1,tU2,tU3,n);
		f = y3 + myY3(t,a,n);
	}
//	printf("t=%f,Y3=%f\n",t[0],f);
//	printf("y30 = %8f, u20 = %8f, u10 = %8f\n", y30, u20, u10);
//	printf("Expect 1.0: %f\n",Y3InitialValue(t,a,t[0],1.0));
	if (t[0] == 0.0) printf("t = 0, f (Y3) = %f\n", f);
	return f;
}
/*
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
	extern bool b134sbFlag;
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
//	if (b134sbFlag) return 0.0;
	return f;
}
*/
Double_t BFitNamespace::yY2 (Double_t *t, Double_t *a) {
	extern Double_t t2;
	return a[dt]*a[epsY]*BFitNamespace::Y2(t,a)/t2;
}
Double_t BFitNamespace::yY3 (Double_t *t, Double_t *a) {
	extern Double_t t3;
	return a[dt]*a[epsY]*BFitNamespace::Y3(t,a)/t3;
}

