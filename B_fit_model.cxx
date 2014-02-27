#include "B_fit_model.h"
#include "bdn_cases.h"

Double_t B_fit_model::T1 (Double_t *t, Double_t *a) {
	using namespace B_fit_model;
	using namespace TMath;
	static Int_t n;
	static Double_t ST1, tT1, f;
	static const Double_t Ta = 5000.0;
	static const Double_t Tb = 101000.0;
	static const Double_t T  = 246000.0;
	f = 0.0; //catch bad values of t[0]
	if (Tb <= t[0] && t[0] <= T)
	{
		tT1 = a[tauT1];
		n = Ceil((t[0]-Tb)/Ta);
		ST1 = ( Exp(n*Ta/tT1) - Power(a[l],n) ) / ( Exp(Ta/tT1) - a[l] );
		f = a[p] * a[r1] * Ta * ST1 * Exp(-(t[0]-Tb)/tT1);
	}
	return f;
}

Double_t B_fit_model::T2 (Double_t *t, Double_t *a) {
	using namespace B_fit_model;
	using namespace TMath;
	static Int_t n;
	static Double_t ST2, tT2, f;
	static const Double_t Ta = 5000.0;
	static const Double_t Tb = 101000.0;
	static const Double_t T  = 246000.0;
	f = 0.0; //catch bad values of t[0]
	if (Tb <= t[0] && t[0] <= T)
	{
		tT2 = a[tauT2];
		n = Ceil((t[0]-Tb)/Ta);
		ST2 = ( Exp(n*Ta/tT2) - Power(a[l],n) ) / ( Exp(Ta/tT2) - a[l] );
		f = a[p] * a[r2] * Ta * ST2 * Exp(-(t[0]-Tb)/tT2);
	}
	return f;
}

Double_t B_fit_model::T3 (Double_t *t, Double_t *a) {
	using namespace B_fit_model;
	using namespace TMath;
	static Int_t n;
	static Double_t ST3, tT3, f;
	static const Double_t Ta = 5000.0;
	static const Double_t Tb = 101000.0;
	static const Double_t T  = 246000.0;
	f = 0.0; //catch bad values of t[0]
	if (Tb <= t[0] && t[0] <= T)
	{
		tT3 = a[tauT3];
		n = Ceil((t[0]-Tb)/Ta);
		ST3 = ( Exp(n*Ta/tT3) - Power(a[l],n) ) / ( Exp(Ta/tT3) - a[l] );
		f = a[p] * a[r3] * Ta * ST3 * Exp(-(t[0]-Tb)/tT3);
	}
	return f;
}

Double_t B_fit_model::U1 (Double_t *t, Double_t *a) {
	using namespace B_fit_model;
	return V1(t,a) + W1(t,a);
}
Double_t B_fit_model::U2 (Double_t *t, Double_t *a) {
	using namespace B_fit_model;
	return V2(t,a) + W2(t,a) + X2(t,a) + Y2(t,a);
}
Double_t B_fit_model::U3 (Double_t *t, Double_t *a) {
	using namespace B_fit_model;
	return V3(t,a) + W3(t,a) + X3(t,a) + Y3(t,a);
}

// Functions to plot: (obs. decay rate)x(bin dt) = counts by bin
Double_t B_fit_model::yDC (Double_t *t, Double_t *a) {
	using namespace B_fit_model;
	return a[dt]*a[DC];
}
Double_t B_fit_model::yT1 (Double_t *t, Double_t *a) {
	using namespace B_fit_model;
	return a[dt]*a[epsT]*T1(t,a)/a[tauT1];
}
Double_t B_fit_model::yT2 (Double_t *t, Double_t *a) {
	using namespace B_fit_model;
	return a[dt]*a[epsT]*T2(t,a)/a[tauT2];
}
Double_t B_fit_model::yT3 (Double_t *t, Double_t *a) {
	using namespace B_fit_model;
	return a[dt]*a[epsT]*T3(t,a)/a[tauT3];
}

Double_t B_fit_model::yU1 (Double_t *t, Double_t *a) {
	using namespace B_fit_model;
	return a[dt] * ( a[epsV]*V1(t,a) + a[epsW]*W1(t,a) ) / a[tauU1];
}
Double_t B_fit_model::yU2 (Double_t *t, Double_t *a) {
	using namespace B_fit_model;
	return a[dt] * ( a[epsV]*V2(t,a) + a[epsW]*W2(t,a) + a[epsX]*X2(t,a) + a[epsY]*Y2(t,a) ) / a[tauU2];
}
Double_t B_fit_model::yU3 (Double_t *t, Double_t *a) {
	using namespace B_fit_model;
	return a[dt] * ( a[epsV]*V3(t,a) + a[epsW]*W3(t,a) + a[epsX]*X3(t,a) + a[epsY]*Y3(t,a) ) / a[tauU3];
}
Double_t B_fit_model::yAll(Double_t *t, Double_t *a) {
	using namespace B_fit_model;
	return a[dt] * ( a[DC] + a[epsT]*(T1(t,a)/a[tauT1] + T2(t,a)/a[tauT2] + T3(t,a)/a[tauT3]) + (a[epsV]*V1(t,a) + a[epsW]*W1(t,a))/a[tauU1] + (a[epsV]*V2(t,a) + a[epsW]*W2(t,a) + a[epsX]*X2(t,a) + a[epsY]*Y2(t,a))/a[tauU2] + (a[epsV]*V3(t,a) + a[epsW]*W3(t,a) + a[epsX]*X3(t,a) + a[epsY]*Y3(t,a))/a[tauU3] );
}

// Offset functions to imporve visualization: offT1 = yT1 + yDC
Double_t B_fit_model::oT1 (Double_t *t, Double_t *a) {
	using namespace B_fit_model;
	return a[dt]*(a[DC] + a[epsT]*T1(t,a)/a[tauT1]);
}
Double_t B_fit_model::oT2 (Double_t *t, Double_t *a) {
	using namespace B_fit_model;
	return a[dt]*(a[DC] + a[epsT]*T2(t,a)/a[tauT2]);
}
Double_t B_fit_model::oT3 (Double_t *t, Double_t *a) {
	using namespace B_fit_model;
	return a[dt]*(a[DC] + a[epsT]*T3(t,a)/a[tauT3]);
}
Double_t B_fit_model::oU1 (Double_t *t, Double_t *a) {
	using namespace B_fit_model;
	return a[dt]*(a[DC] + a[epsU]*U1(t,a)/a[tauU1]);
}
Double_t B_fit_model::oU2 (Double_t *t, Double_t *a) {
	using namespace B_fit_model;
	return a[dt]*(a[DC] + a[epsU]*U2(t,a)/a[tauU2]);
}
Double_t B_fit_model::oU3 (Double_t *t, Double_t *a) {
	using namespace B_fit_model;
	return a[dt]*(a[DC] + a[epsU]*U3(t,a)/a[tauU3]);
}

// Per-bin rates by component, used for calculating N_beta
Double_t B_fit_model::rDC (Double_t *t, Double_t *a) {
	using namespace B_fit_model;
	return a[DC];
}
Double_t B_fit_model::rT1 (Double_t *t, Double_t *a) {
	using namespace B_fit_model;
	return a[epsT]*T1(t,a)/a[tauT1];
}
Double_t B_fit_model::rT2 (Double_t *t, Double_t *a) {
	using namespace B_fit_model;
	return a[epsT]*T2(t,a)/a[tauT2];
}
Double_t B_fit_model::rT3 (Double_t *t, Double_t *a) {
	using namespace B_fit_model;
	return a[epsT]*T3(t,a)/a[tauT3];
}
Double_t B_fit_model::rU1 (Double_t *t, Double_t *a) {
	using namespace B_fit_model;
	return a[epsU]*U1(t,a)/a[tauU1];
}
Double_t B_fit_model::rU2 (Double_t *t, Double_t *a) {
	using namespace B_fit_model;
	return a[epsU]*U2(t,a)/a[tauU2];
}
Double_t B_fit_model::rU3 (Double_t *t, Double_t *a) {
	using namespace B_fit_model;
	return a[epsU]*U3(t,a)/a[tauU3];
}
Double_t B_fit_model::rAll (Double_t *t, Double_t *a) {
	using namespace B_fit_model;
	return a[DC] + a[epsT]*(T1(t,a)/a[tauT1] + T2(t,a)/a[tauT2] + T3(t,a)/a[tauT3]) + a[epsU]*(U1(t,a)/a[tauU1] + U2(t,a)/a[tauU2] + U3(t,a)/a[tauU3]);
}

Double_t B_fit_model::V1 (Double_t *t, Double_t *a) {
	using namespace B_fit_model;
	using namespace TMath;
	static Int_t n, N;
	static Double_t tT1, tU1, SU1, SU10, v10, v1, V1, f;
	static const Double_t Ta = 5000.0;
	static const Double_t Tb = 101000.0;
	static const Double_t T  = 246000.0;
	tT1 = a[tauT1];
	tU1 = a[tauU1];
	f = 0.0; //catch bad values of t[0]
	n = Ceil((t[0]-Tb)/Ta);
	N = Ceil(   (T-Tb)/Ta);
	SU1  = ( Exp(n*Ta/tU1) - 1 ) / ( Exp(Ta/tU1) - 1 );
	SU10 = ( Exp(N*Ta/tU1) - 1 ) / ( Exp(Ta/tU1) - 1 );
//	D1   = ( Exp(n*Ta/tT1) - 1 ) / ( Exp(Ta/tT1) - 1 ) - ( Exp(n*Ta/tT1) - Power(a[l],n) ) / ( Exp(Ta/tT1) - a[l] );
//	D10  = ( Exp(N*Ta/tT1) - 1 ) / ( Exp(Ta/tT1) - 1 ) - ( Exp(N*Ta/tT1) - Power(a[l],N) ) / ( Exp(Ta/tT1) - a[l] );
	// Untrapped populations at t=0
	v10 = ( a[r1] * Ta * (1-a[p]) * SU10 * Exp(-(T-Tb)/tU1) ) / ( 1 - Exp(-T/tU1) );
	// Untrapped population during background period
	v1 = v10 * Exp(-t[0]/tU1);
	// Background period
	if (0 <= t[0] && t[0] < Tb) {
		f = v1;
	}
	// Trapping period
	if (Tb <= t[0] && t[0] <= T) {
		// Untrapped populations during trapping
		V1 = a[r1] * Ta * (1-a[p]) * SU1 * Exp(-(t[0]-Tb)/tU1);
		f = v1+V1;
	}
	return f;
}

Double_t B_fit_model::V2 (Double_t *t, Double_t *a) {
	using namespace B_fit_model;
	using namespace TMath;
	static Int_t n, N;
	static Double_t tT2, tU2, SU2, SU20, v20, v2, V2, f;
	static const Double_t Ta = 5000.0;
	static const Double_t Tb = 101000.0;
	static const Double_t T  = 246000.0;
	tT2 = a[tauT2];
	tU2 = a[tauU2];
	f = 0.0; //catch bad values of t[0]
	n = Ceil((t[0]-Tb)/Ta);
	N = Ceil(   (T-Tb)/Ta);
	SU2  = ( Exp(n*Ta/tU2) - 1 ) / ( Exp(Ta/tU2) - 1 );
	SU20 = ( Exp(N*Ta/tU2) - 1 ) / ( Exp(Ta/tU2) - 1 );
//	D2   = ( Exp(n*Ta/tT2) - 1 ) / ( Exp(Ta/tT2) - 1 ) - ( Exp(n*Ta/tT2) - Power(a[l],n) ) / ( Exp(Ta/tT2) - a[l] );
//	D20  = ( Exp(N*Ta/tT2) - 1 ) / ( Exp(Ta/tT2) - 1 ) - ( Exp(N*Ta/tT2) - Power(a[l],N) ) / ( Exp(Ta/tT2) - a[l] );
	// Untrapped populations at t=0
	v20 = ( a[r2] * Ta * (1-a[p]) * SU20 * Exp(-(T-Tb)/tU2) ) / ( 1 - Exp(-T/tU2) );
	// Untrapped population during background period
	v2 = v20 * Exp(-t[0]/tU2);
	// Background period
	if (0 <= t[0] && t[0] < Tb) {
		f = v2;
	}
	// Trapping period
	if (Tb <= t[0] && t[0] <= T) {
		// Untrapped populations during trapping
		V2 = a[r2] * Ta * (1-a[p]) * SU2 * Exp(-(t[0]-Tb)/tU2);
		f = v2+V2;
	}
	return f;
}

Double_t B_fit_model::V3 (Double_t *t, Double_t *a) {
	using namespace B_fit_model;
	using namespace TMath;
	static Int_t n, N;
	static Double_t tT3, tU3, SU3, SU30, v30, v3, V3, f;
	static const Double_t Ta = 5000.0;
	static const Double_t Tb = 101000.0;
	static const Double_t T  = 246000.0;
	tT3 = a[tauT3];
	tU3 = a[tauU3];
	f = 0.0; //catch bad values of t[0]
	n = Ceil((t[0]-Tb)/Ta);
	N = Ceil(   (T-Tb)/Ta);
	SU3  = ( Exp(n*Ta/tU3) - 1 ) / ( Exp(Ta/tU3) - 1 );
	SU30 = ( Exp(N*Ta/tU3) - 1 ) / ( Exp(Ta/tU3) - 1 );
//	D3   = ( Exp(n*Ta/tT3) - 1 ) / ( Exp(Ta/tT3) - 1 ) - ( Exp(n*Ta/tT3) - Power(a[l],n) ) / ( Exp(Ta/tT3) - a[l] );
//	D30  = ( Exp(N*Ta/tT3) - 1 ) / ( Exp(Ta/tT3) - 1 ) - ( Exp(N*Ta/tT3) - Power(a[l],N) ) / ( Exp(Ta/tT3) - a[l] );
	// Untrapped populations at t=0
	v30 = ( a[r3] * Ta * (1-a[p]) * SU30 * Exp(-(T-Tb)/tU3) ) / ( 1 - Exp(-T/tU3) );
	// Untrapped population during background period
	v3 = v30 * Exp(-t[0]/tU3);
	// Background period
	if (0 <= t[0] && t[0] < Tb) {
		f = v3;
	}
	// Trapping period
	if (Tb <= t[0] && t[0] <= T) {
		// Untrapped populations during trapping
		V3 = a[r3] * Ta * (1-a[p]) * SU3 * Exp(-(t[0]-Tb)/tU3);
		f = v3+V3;
	}
	return f;
}

Double_t B_fit_model::yV1 (Double_t *t, Double_t *a) {
	using namespace B_fit_model;
	return a[dt]*a[epsV]*V1(t,a)/a[tauU1];
}
Double_t B_fit_model::yV2 (Double_t *t, Double_t *a) {
	using namespace B_fit_model;
	return a[dt]*a[epsV]*V2(t,a)/a[tauU2];
}
Double_t B_fit_model::yV3 (Double_t *t, Double_t *a) {
	using namespace B_fit_model;
	return a[dt]*a[epsV]*V3(t,a)/a[tauU3];
}

// W populations
Double_t B_fit_model::W1 (Double_t *t, Double_t *a) {
	using namespace B_fit_model;
	using namespace TMath;
	static Int_t n, N;
	static Double_t tT1, tU1, D1, D10, w10, w1, W1, f;
	static const Double_t Ta = 5000.0;
	static const Double_t Tb = 101000.0;
	static const Double_t T  = 246000.0;
	tT1 = a[tauT1];
	tU1 = a[tauU1];
	f = 0.0; //catch bad values of t[0]
	n = Ceil((t[0]-Tb)/Ta);
	N = Ceil(   (T-Tb)/Ta);
//	SU1  = ( Exp(n*Ta/tU1) - 1 ) / ( Exp(Ta/tU1) - 1 );
//	SU10 = ( Exp(N*Ta/tU1) - 1 ) / ( Exp(Ta/tU1) - 1 );
	D1   = ( Exp(n*Ta/tT1) - 1 ) / ( Exp(Ta/tT1) - 1 ) - ( Exp(n*Ta/tT1) - Power(a[l],n) ) / ( Exp(Ta/tT1) - a[l] );
	D10  = ( Exp(N*Ta/tT1) - 1 ) / ( Exp(Ta/tT1) - 1 ) - ( Exp(N*Ta/tT1) - Power(a[l],N) ) / ( Exp(Ta/tT1) - a[l] );
	// Untrapped populations at t=0
	w10 = ( a[r1] * Ta * a[p] * D10 * Exp(-(T-Tb)/tU1) ) / ( 1 - Exp(-T/tU1) );
	// Untrapped population during background period
	w1 = w10 * Exp(-t[0]/tU1);
	// Background period
	if (0 <= t[0] && t[0] < Tb) {
		f = w1;
	}
	// Trapping period
	if (Tb <= t[0] && t[0] <= T) {
		// Untrapped populations during trapping
		W1 = a[r1] * Ta * a[p] * D1 * Exp(-(t[0]-Tb)/tU1);
		f = w1 + W1;
	}
	return f;
}
Double_t B_fit_model::W2 (Double_t *t, Double_t *a) {
	using namespace B_fit_model;
	using namespace TMath;
	static Int_t n, N;
	static Double_t tT2, tU2, D2, D20, w20, w2, W2, f;
	static const Double_t Ta = 5000.0;
	static const Double_t Tb = 101000.0;
	static const Double_t T  = 246000.0;
	tT2 = a[tauT2];
	tU2 = a[tauU2];
	f = 0.0; //catch bad values of t[0]
	n = Ceil((t[0]-Tb)/Ta);
	N = Ceil(   (T-Tb)/Ta);
//	SU2  = ( Exp(n*Ta/tU2) - 1 ) / ( Exp(Ta/tU2) - 1 );
//	SU20 = ( Exp(N*Ta/tU2) - 1 ) / ( Exp(Ta/tU2) - 1 );
	D2   = ( Exp(n*Ta/tT2) - 1 ) / ( Exp(Ta/tT2) - 1 ) - ( Exp(n*Ta/tT2) - Power(a[l],n) ) / ( Exp(Ta/tT2) - a[l] );
	D20  = ( Exp(N*Ta/tT2) - 1 ) / ( Exp(Ta/tT2) - 1 ) - ( Exp(N*Ta/tT2) - Power(a[l],N) ) / ( Exp(Ta/tT2) - a[l] );
	// Untrapped populations at t=0
	w20 = ( a[r2] * Ta * a[p] * D20 * Exp(-(T-Tb)/tU2) ) / ( 1 - Exp(-T/tU2) );
	// Untrapped population during background period
	w2 = w20 * Exp(-t[0]/tU2);
	// Background period
	if (0 <= t[0] && t[0] < Tb) {
		f = w2;
	}
	// Trapping period
	if (Tb <= t[0] && t[0] <= T) {
		// Untrapped populations during trapping
		W2 = a[r2] * Ta * a[p] * D2 * Exp(-(t[0]-Tb)/tU2);
		f = w2 + W2;
	}
	return f;
}
Double_t B_fit_model::W3 (Double_t *t, Double_t *a) {
	using namespace B_fit_model;
	using namespace TMath;
	static Int_t n, N;
	static Double_t tT3, tU3, D3, D30, w30, w3, W3, f;
	static const Double_t Ta = 5000.0;
	static const Double_t Tb = 101000.0;
	static const Double_t T  = 246000.0;
	tT3 = a[tauT3];
	tU3 = a[tauU3];
	f = 0.0; //catch bad values of t[0]
	n = Ceil((t[0]-Tb)/Ta);
	N = Ceil(   (T-Tb)/Ta);
//	SU3  = ( Exp(n*Ta/tU3) - 1 ) / ( Exp(Ta/tU3) - 1 );
//	SU30 = ( Exp(N*Ta/tU3) - 1 ) / ( Exp(Ta/tU3) - 1 );
	D3   = ( Exp(n*Ta/tT3) - 1 ) / ( Exp(Ta/tT3) - 1 ) - ( Exp(n*Ta/tT3) - Power(a[l],n) ) / ( Exp(Ta/tT3) - a[l] );
	D30  = ( Exp(N*Ta/tT3) - 1 ) / ( Exp(Ta/tT3) - 1 ) - ( Exp(N*Ta/tT3) - Power(a[l],N) ) / ( Exp(Ta/tT3) - a[l] );
	// Untrapped populations at t=0
	w30 = ( a[r3] * Ta * a[p] * D30 * Exp(-(T-Tb)/tU3) ) / ( 1 - Exp(-T/tU3) );
	// Untrapped population during background period
	w3 = w30 * Exp(-t[0]/tU3);
	// Background period
	if (0 <= t[0] && t[0] < Tb) {
		f = w3;
	}
	// Trapping period
	if (Tb <= t[0] && t[0] <= T) {
		// Untrapped populations during trapping
		W3 = a[r3] * Ta * a[p] * D3 * Exp(-(t[0]-Tb)/tU3);
		f = w3 + W3;
	}
	return f;
}
Double_t B_fit_model::yW1 (Double_t *t, Double_t *a) {
	using namespace B_fit_model;
	return a[dt]*a[epsW]*W1(t,a)/a[tauU1];
}
Double_t B_fit_model::yW2 (Double_t *t, Double_t *a) {
	using namespace B_fit_model;
	return a[dt]*a[epsW]*W2(t,a)/a[tauU2];
}
Double_t B_fit_model::yW3 (Double_t *t, Double_t *a) {
	using namespace B_fit_model;
	return a[dt]*a[epsW]*W3(t,a)/a[tauU3];
}

Double_t B_fit_model::X2 (Double_t *t, Double_t *a) {
	using namespace B_fit_model;
	using namespace TMath;
	static Int_t n, N;
	static Double_t t1, tT1, tT2, tU1, tU2, ST1, ST10, SU2, SU20, x20, x2, X2, f;
	static const Double_t Ta = 5000.0;
	static const Double_t Tb = 101000.0;
	static const Double_t T  = 246000.0;
	static const Double_t ln2= 0.69314718056;
	t1  = 1000.0 * 2.49 / ln2;
//	t2  = 1000.0 * 24.5 / ln2;
//	t3  = 60.0 * 1000.0 * 3.818 / ln2;
	tT1 = a[tauT1];
	tT2 = a[tauT2];
	tU1 = a[tauU1];
	tU2 = a[tauU2];
	f = 0.0; //catch bad values of t[0]
	n = Ceil((t[0]-Tb)/Ta);
	N = Ceil(   (T-Tb)/Ta);
	ST1  = ( Exp(n*Ta/tT1) - 1 ) / ( Exp(Ta/tT1) - 1 );
	ST10 = ( Exp(N*Ta/tT1) - 1 ) / ( Exp(Ta/tT1) - 1 );
	SU2  = ( Exp(n*Ta/tU2) - 1 ) / ( Exp(Ta/tU2) - 1 );
	SU20 = ( Exp(N*Ta/tU2) - 1 ) / ( Exp(Ta/tU2) - 1 );
	// Untrapped populations at t=0
	x20 = ( a[r1] * Ta * a[p] * tT1/t1 * tU2/(tU2-tT1) * ( SU20 * Exp(-(T-Tb)/tU2) - ST10 * Exp(-(T-Tb)/tT1) ) ) / ( 1 - Exp(-T/tU2) );
	// Untrapped population during background period
	x2 = x20*Exp(-t[0]/tU2) ;
	// Background period
	if (0 <= t[0] && t[0] < Tb) {
		f = x2;
	}
	// Trapping period
	if (Tb <= t[0] && t[0] <= T) {
		// Untrapped populations during trapping
		X2 = a[r1] * Ta * a[p] * tT1/t1 * tU2/(tU2-tT1) * ( SU2 * Exp(-(t[0]-Tb)/tU2) - ST1 * Exp(-(t[0]-Tb)/tT1) );
		f = x2 + X2;
	}
	return f;
}

Double_t B_fit_model::X3 (Double_t *t, Double_t *a) {
	using namespace B_fit_model;
	using namespace TMath;
	static Int_t n, N;
	static Double_t t2, tT2, tT3, tU2, tU3, ST2, ST20, SU3, SU30, x30, x3, X3, f;
	static const Double_t Ta = 5000.0;
	static const Double_t Tb = 101000.0;
	static const Double_t T  = 246000.0;
	static const Double_t ln2= 0.69314718056;
//	t1  = 1000.0 * 2.49 / ln2;
	t2  = 1000.0 * 24.5 / ln2;
//	t3  = 60.0 * 1000.0 * 3.818 / ln2;
	tT2 = a[tauT2];
	tT3 = a[tauT3];
	tU2 = a[tauU2];
	tU3 = a[tauU3];
	f = 0.0; //catch bad values of t[0]
	n = Ceil((t[0]-Tb)/Ta);
	N = Ceil(   (T-Tb)/Ta);
	ST2  = ( Exp(n*Ta/tT2) - 1 ) / ( Exp(Ta/tT2) - 1 );
	ST20 = ( Exp(N*Ta/tT2) - 1 ) / ( Exp(Ta/tT2) - 1 );
	SU3  = ( Exp(n*Ta/tU3) - 1 ) / ( Exp(Ta/tU3) - 1 );
	SU30 = ( Exp(N*Ta/tU3) - 1 ) / ( Exp(Ta/tU3) - 1 );
	// Untrapped populations at t=0
	x30 = ( a[r2] * Ta * a[p] * tT2/t2 * tU3/(tU3-tT2) * ( SU30 * Exp(-(T-Tb)/tU3) - ST20 * Exp(-(T-Tb)/tT2) ) ) / ( 1 - Exp(-T/tU3) );
	// Untrapped population during background period
	x3 = x30 * Exp(-t[0]/tU3);
	// Background period
	if (0 <= t[0] && t[0] < Tb) {
		f = x3;
	}
	// Trapping period
	if (Tb <= t[0] && t[0] <= T) {
		// Untrapped populations during trapping
		X3 = a[r2] * Ta * a[p] * tT2/t2 * tU3/(tU3-tT2) * ( SU3 * Exp(-(t[0]-Tb)/tU3) - ST2 * Exp(-(t[0]-Tb)/tT2) );
		f = x3 + X3;
	}
	return f;
}

Double_t B_fit_model::yX2 (Double_t *t, Double_t *a) {
	using namespace B_fit_model;
	return a[dt]*a[epsX]*X2(t,a)/a[tauU2];
}
Double_t B_fit_model::yX3 (Double_t *t, Double_t *a) {
	using namespace B_fit_model;
	return a[dt]*a[epsX]*X3(t,a)/a[tauU3];
}

Double_t B_fit_model::Y2 (Double_t *t, Double_t *a) {
	using namespace B_fit_model;
	using namespace TMath;
	static Int_t n, N;
	static Double_t t1, tT1, tT2, tU1, tU2, ST1, ST10, SU1, SU10, SU2, SU20, y10, y20, y2, Y2, f;
	static const Double_t Ta = 5000.0;
	static const Double_t Tb = 101000.0;
	static const Double_t T  = 246000.0;
	static const Double_t ln2= 0.69314718056;
	t1  = 1000.0 * 2.49 / ln2;
//	t2  = 1000.0 * 24.5 / ln2;
//	t3  = 60.0 * 1000.0 * 3.818 / ln2;
	tT1 = a[tauT1];
	tT2 = a[tauT2];
	tU1 = a[tauU1];
	tU2 = a[tauU2];
	f = 0.0; //catch bad values of t[0]
	n = Ceil((t[0]-Tb)/Ta);
	N = Ceil(   (T-Tb)/Ta);
//	ST1  = ( Exp(n*Ta/tT1) - 1 ) / ( Exp(Ta/tT1) - 1 );
//	ST10 = ( Exp(N*Ta/tT1) - 1 ) / ( Exp(Ta/tT1) - 1 );
	SU1  = ( Exp(n*Ta/tU1) - 1 ) / ( Exp(Ta/tU1) - 1 );
	SU10 = ( Exp(N*Ta/tU1) - 1 ) / ( Exp(Ta/tU1) - 1 );
	SU2  = ( Exp(n*Ta/tU2) - 1 ) / ( Exp(Ta/tU2) - 1 );
	SU20 = ( Exp(N*Ta/tU2) - 1 ) / ( Exp(Ta/tU2) - 1 );
	
	// Untrapped populations at t=0
	y10 = a[r1] * Ta * (1-a[p]) * SU10 * Exp(-(T-Tb)/tU1) / ( 1 - Exp(-T/tU1) );
	y20 = ( y10 * tU1/t1 * tU2/(tU2-tU1) * ( Exp(-T/tU2) - Exp(-T/tU1) ) + a[r1] * Ta * (1-a[p]) * tU1/t1 * tU2/(tU2-tU1) * ( SU20 * Exp(-(T-Tb)/tU2) - SU10 * Exp(-(T-Tb)/tU1) ) ) / (1-Exp(-T/tU2) );
	// Untrapped population during background period
	y2 = y20 * Exp(-t[0]/tU2) + y10 * tU1/t1 * tU2/(tU2-tU1) * ( Exp(-t[0]/tU2) - Exp(-t[0]/tU1 ) );
	// Background period
	if (0 <= t[0] && t[0] < Tb) {
		f = y2;
	}
	// Trapping period
	if (Tb <= t[0] && t[0] <= T) {
		// Untrapped populations during trapping
		Y2 = a[r1] * Ta * (1-a[p]) * tU1/t1 * tU2/(tU2-tU1) * ( SU2 * Exp(-(t[0]-Tb)/tU2) - SU1 * Exp(-(t[0]-Tb)/tU1) );
		f = y2 + Y2;
	}
	return f;
}

Double_t B_fit_model::Y3 (Double_t *t, Double_t *a) {
	using namespace B_fit_model;
	using namespace TMath;
	static Int_t n, N;
	static Double_t t1, t2, t3, tT1, tT2, tT3, tU1, tU2, tU3, AU, ST1, ST2, ST3, ST10, ST20, ST30, SU1, SU2, SU3, SU10, SU20, SU30, y10, y20, y30, y3, Y3, f;
	static const Double_t Ta = 5000.0;
	static const Double_t Tb = 101000.0;
	static const Double_t T  = 246000.0;
	static const Double_t ln2= 0.69314718056;
	t1  = 1000.0 * 2.49 / ln2;
	t2  = 1000.0 * 24.5 / ln2;
//	t3  = 60.0 * 1000.0 * 3.818 / ln2;
	tT1 = a[tauT1];
	tT2 = a[tauT2];
	tT3 = a[tauT3];
	tU1 = a[tauU1];
	tU2 = a[tauU2];
	tU3 = a[tauU3];
	AU  = (tU3-tU2) * (tU3-tU1) * (tU2-tU1);
	f = 0.0; //catch bad values of t[0]
	n = Ceil((t[0]-Tb)/Ta);
	N = Ceil(   (T-Tb)/Ta);
	SU1  = ( Exp(n*Ta/tU1) - 1 ) / ( Exp(Ta/tU1) - 1 );
	SU2  = ( Exp(n*Ta/tU2) - 1 ) / ( Exp(Ta/tU2) - 1 );
	SU3  = ( Exp(n*Ta/tU3) - 1 ) / ( Exp(Ta/tU3) - 1 );
	SU10 = ( Exp(N*Ta/tU1) - 1 ) / ( Exp(Ta/tU1) - 1 );
	SU20 = ( Exp(N*Ta/tU2) - 1 ) / ( Exp(Ta/tU2) - 1 );
	SU30 = ( Exp(N*Ta/tU3) - 1 ) / ( Exp(Ta/tU3) - 1 );
	// Untrapped populations at t=0
	y10 = 
		a[r1] * Ta * (1-a[p]) * SU10 * Exp(-(T-Tb)/tU1) / ( 1 - Exp(-T/tU1) );
	y20 = (
		y10 * tU1/t1 * tU2/(tU2-tU1) * ( Exp(-T/tU2) - Exp(-T/tU1) ) +
		a[r2] * Ta * (1-a[p]) *            SU20*Exp(-(T-Tb)/tU2) + 
		a[r1] * Ta * (1-a[p]) * tU1/t1 * tU2/(tU2-tU1) * (SU20 * Exp(-(T-Tb)/tU2) - SU10 * Exp(-(T-Tb)/tU1) )
		)
		/ ( 1 - Exp(-T/tU2) );
	y30 = (
		y20 * tU2/t2 * tU3/(tU3-tU2) * ( Exp(-T/tU3) - Exp(-T/tU2) ) + 
		y10 * tU1/t1 * tU2/t2 * tU3/AU * ( tU1 * (tU3-tU2) * Exp(-T/tU1) - tU2 * (tU3-tU1) * Exp(-T/tU2) + tU3 * (tU2-tU1) * Exp(-T/tU3) ) + 
//		a[r3]*Ta*(1-a[p])*                 S30*Exp(-(T-Tb)/t3) + 
		a[r2] * Ta * (1-a[p]) * tU2/t2 * tU3/(tU3-tU2) *     (SU30*Exp(-(T-Tb)/tU3) -            SU20*Exp(-(T-Tb)/tU2)) + 
		a[r1] * Ta * (1-a[p]) * tU1/t1 * tU2/t2 * tU3/AU * ( tU1 * (tU3-tU2) * SU10 * Exp(-(T-Tb)/tU1) - tU2 * (tU3-tU1) * SU20 * Exp(-(T-Tb)/tU2) + tU3 * (tU2-tU1) * SU30 * Exp(-(T-Tb)/tU3) )
		)
		/ ( 1 - Exp(-T/tU3) );
	// Untrapped population during background period
	y3 = 
		y30 * Exp(-t[0]/tU3) + 
		y20 * tU2/t2 * tU3/(tU3-tU2) * ( Exp(-t[0]/tU3) - Exp(-t[0]/tU2) ) + 
		y10 * tU1/t1 * tU2/t2 * tU3/AU * ( tU1 * (tU3-tU2) * Exp(-t[0]/tU1) - tU2 * (tU3-tU1) * Exp(-t[0]/tU2) + tU3 * (tU2-tU1) * Exp(-t[0]/tU3) );
	// Background period
	if (0 <= t[0] && t[0] < Tb) {
		f = y3;
	}
	// Trapping period
	if (Tb <= t[0] && t[0] <= T) {
		// Untrapped populations during trapping
		Y3 = 
			a[r2] * Ta * (1-a[p]) * tU2/t2 * tU3/(tU3-tU2) * ( SU3 * Exp(-(t[0]-Tb)/tU3) - SU2 * Exp(-(t[0]-Tb)/tU2) ) + 
			a[r1] * Ta * (1-a[p]) * tU1/t1 * tU2/t2 * tU3/AU * ( tU1 * (tU3-tU2) * SU1 * Exp(-(t[0]-Tb)/tU1) - tU2 * (tU3-tU1) * SU2 * Exp(-(t[0]-Tb)/tU2) + tU3 * (tU2-tU1) * SU3 * Exp(-(t[0]-Tb)/tU3) );
		f = y3 + Y3;
	}
	return f;
}

Double_t B_fit_model::yY2 (Double_t *t, Double_t *a) {
	using namespace B_fit_model;
	return a[dt]*a[epsY]*Y2(t,a)/a[tauU2];
}
Double_t B_fit_model::yY3 (Double_t *t, Double_t *a) {
	using namespace B_fit_model;
	return a[dt]*a[epsY]*Y3(t,a)/a[tauU3];
}

/*
Double_t B_fit_model::T1 (Double_t *t, Double_t *a) {
	using namespace B_fit_model;
	using namespace TMath;
	extern Int_t gdx;
	static const Double_t Ta = bdn_cases[gdx].T_capt;
	static const Double_t Tb = bdn_cases[gdx].T_bkgd;
	static const Double_t T  = bdn_cases[gdx].T_cycle;
	static Int_t n;
	static Double_t ST1, tT1, f;
	f = 0.0; //catch bad values of t[0]
	if (Tb <= t[0] && t[0] <= T)
	{
		tT1 = a[tauT1];
		n = Ceil((t[0]-Tb)/Ta);
		ST1 = ( Exp(n*Ta/tT1) - Power(a[l],n) ) / ( Exp(Ta/tT1) - a[l] );
		f = a[p] * a[r1] * Ta * ST1 * Exp(-(t[0]-Tb)/tT1);
	}
	return f;
}

Double_t B_fit_model::T2 (Double_t *t, Double_t *a) {
	using namespace B_fit_model;
	using namespace TMath;
	extern Int_t gdx;
	static const Double_t Ta = bdn_cases[gdx].T_capt;
	static const Double_t Tb = bdn_cases[gdx].T_bkgd;
	static const Double_t T  = bdn_cases[gdx].T_cycle;
	static Int_t n;
	static Double_t ST2, tT2, f;
	f = 0.0; //catch bad values of t[0]
	if (Tb <= t[0] && t[0] <= T)
	{
		tT2 = a[tauT2];
		n = Ceil((t[0]-Tb)/Ta);
		ST2 = ( Exp(n*Ta/tT2) - Power(a[l],n) ) / ( Exp(Ta/tT2) - a[l] );
		f = a[p] * a[r2] * Ta * ST2 * Exp(-(t[0]-Tb)/tT2);
	}
	return f;
}

Double_t B_fit_model::T3 (Double_t *t, Double_t *a) {
	using namespace B_fit_model;
	using namespace TMath;
	static Int_t n;
	static Double_t ST3, tT3, f;
	extern Int_t gdx;
	static const Double_t Ta = bdn_cases[gdx].T_capt;
	static const Double_t Tb = bdn_cases[gdx].T_bkgd;
	static const Double_t T  = bdn_cases[gdx].T_cycle;
	f = 0.0; //catch bad values of t[0]
	if (Tb <= t[0] && t[0] <= T)
	{
		tT3 = a[tauT3];
		n = Ceil((t[0]-Tb)/Ta);
		ST3 = ( Exp(n*Ta/tT3) - Power(a[l],n) ) / ( Exp(Ta/tT3) - a[l] );
		f = a[p] * a[r3] * Ta * ST3 * Exp(-(t[0]-Tb)/tT3);
	}
	return f;
}

Double_t B_fit_model::U1 (Double_t *t, Double_t *a) {
	using namespace B_fit_model;
	return V1(t,a) + W1(t,a);
}
Double_t B_fit_model::U2 (Double_t *t, Double_t *a) {
	using namespace B_fit_model;
	return V2(t,a) + W2(t,a) + X2(t,a) + Y2(t,a);
}
Double_t B_fit_model::U3 (Double_t *t, Double_t *a) {
	using namespace B_fit_model;
	return V3(t,a) + W3(t,a) + X3(t,a) + Y3(t,a);
}

// Functions to plot: (obs. decay rate)x(bin dt) = counts by bin
Double_t B_fit_model::yDC (Double_t *t, Double_t *a) {
	using namespace B_fit_model;
	return a[dt]*a[DC];
}
Double_t B_fit_model::yT1 (Double_t *t, Double_t *a) {
	using namespace B_fit_model;
	return a[dt]*a[epsT]*T1(t,a)/a[tauT1];
}
Double_t B_fit_model::yT2 (Double_t *t, Double_t *a) {
	using namespace B_fit_model;
	return a[dt]*a[epsT]*T2(t,a)/a[tauT2];
}
Double_t B_fit_model::yT3 (Double_t *t, Double_t *a) {
	using namespace B_fit_model;
	return a[dt]*a[epsT]*T3(t,a)/a[tauT3];
}

Double_t B_fit_model::yU1 (Double_t *t, Double_t *a) {
	using namespace B_fit_model;
	return a[dt] * ( a[epsV]*V1(t,a) + a[epsW]*W1(t,a) ) / a[tauU1];
}
Double_t B_fit_model::yU2 (Double_t *t, Double_t *a) {
	using namespace B_fit_model;
	return a[dt] * ( a[epsV]*V2(t,a) + a[epsW]*W2(t,a) + a[epsX]*X2(t,a) + a[epsY]*Y2(t,a) ) / a[tauU2];
}
Double_t B_fit_model::yU3 (Double_t *t, Double_t *a) {
	using namespace B_fit_model;
	return a[dt] * ( a[epsV]*V3(t,a) + a[epsW]*W3(t,a) + a[epsX]*X3(t,a) + a[epsY]*Y3(t,a) ) / a[tauU3];
}
Double_t B_fit_model::yAll(Double_t *t, Double_t *a) {
	using namespace B_fit_model;
	return a[dt] * ( a[DC] + a[epsT]*(T1(t,a)/a[tauT1] + T2(t,a)/a[tauT2] + T3(t,a)/a[tauT3]) + (a[epsV]*V1(t,a) + a[epsW]*W1(t,a))/a[tauU1] + (a[epsV]*V2(t,a) + a[epsW]*W2(t,a) + a[epsX]*X2(t,a) + a[epsY]*Y2(t,a))/a[tauU2] + (a[epsV]*V3(t,a) + a[epsW]*W3(t,a) + a[epsX]*X3(t,a) + a[epsY]*Y3(t,a))/a[tauU3] );
}

// Offset functions to imporve visualization: offT1 = yT1 + yDC
Double_t B_fit_model::oT1 (Double_t *t, Double_t *a) {
	using namespace B_fit_model;
	return a[dt]*(a[DC] + a[epsT]*T1(t,a)/a[tauT1]);
}
Double_t B_fit_model::oT2 (Double_t *t, Double_t *a) {
	using namespace B_fit_model;
	return a[dt]*(a[DC] + a[epsT]*T2(t,a)/a[tauT2]);
}
Double_t B_fit_model::oT3 (Double_t *t, Double_t *a) {
	using namespace B_fit_model;
	return a[dt]*(a[DC] + a[epsT]*T3(t,a)/a[tauT3]);
}
Double_t B_fit_model::oU1 (Double_t *t, Double_t *a) {
	using namespace B_fit_model;
	return a[dt]*(a[DC] + a[epsU]*U1(t,a)/a[tauU1]);
}
Double_t B_fit_model::oU2 (Double_t *t, Double_t *a) {
	using namespace B_fit_model;
	return a[dt]*(a[DC] + a[epsU]*U2(t,a)/a[tauU2]);
}
Double_t B_fit_model::oU3 (Double_t *t, Double_t *a) {
	using namespace B_fit_model;
	return a[dt]*(a[DC] + a[epsU]*U3(t,a)/a[tauU3]);
}

// Per-bin rates by component, used for calculating N_beta
Double_t B_fit_model::rDC (Double_t *t, Double_t *a) {
	using namespace B_fit_model;
	return a[DC];
}
Double_t B_fit_model::rT1 (Double_t *t, Double_t *a) {
	using namespace B_fit_model;
	return a[epsT]*T1(t,a)/a[tauT1];
}
Double_t B_fit_model::rT2 (Double_t *t, Double_t *a) {
	using namespace B_fit_model;
	return a[epsT]*T2(t,a)/a[tauT2];
}
Double_t B_fit_model::rT3 (Double_t *t, Double_t *a) {
	using namespace B_fit_model;
	return a[epsT]*T3(t,a)/a[tauT3];
}
Double_t B_fit_model::rU1 (Double_t *t, Double_t *a) {
	using namespace B_fit_model;
	return a[epsU]*U1(t,a)/a[tauU1];
}
Double_t B_fit_model::rU2 (Double_t *t, Double_t *a) {
	using namespace B_fit_model;
	return a[epsU]*U2(t,a)/a[tauU2];
}
Double_t B_fit_model::rU3 (Double_t *t, Double_t *a) {
	using namespace B_fit_model;
	return a[epsU]*U3(t,a)/a[tauU3];
}
Double_t B_fit_model::rAll (Double_t *t, Double_t *a) {
	using namespace B_fit_model;
	return a[DC] + a[epsT]*(T1(t,a)/a[tauT1] + T2(t,a)/a[tauT2] + T3(t,a)/a[tauT3]) + a[epsU]*(U1(t,a)/a[tauU1] + U2(t,a)/a[tauU2] + U3(t,a)/a[tauU3]);
}

Double_t B_fit_model::V1 (Double_t *t, Double_t *a) {
	using namespace B_fit_model;
	using namespace TMath;
	static Int_t n, N;
	static Double_t tT1, tU1, SU1, SU10, v10, v1, V1, f;
	extern Int_t gdx;
	static const Double_t Ta = bdn_cases[gdx].T_capt;
	static const Double_t Tb = bdn_cases[gdx].T_bkgd;
	static const Double_t T  = bdn_cases[gdx].T_cycle;
	tT1 = a[tauT1];
	tU1 = a[tauU1];
	f = 0.0; //catch bad values of t[0]
	n = Ceil((t[0]-Tb)/Ta);
	N = Ceil(   (T-Tb)/Ta);
	SU1  = ( Exp(n*Ta/tU1) - 1 ) / ( Exp(Ta/tU1) - 1 );
	SU10 = ( Exp(N*Ta/tU1) - 1 ) / ( Exp(Ta/tU1) - 1 );
//	D1   = ( Exp(n*Ta/tT1) - 1 ) / ( Exp(Ta/tT1) - 1 ) - ( Exp(n*Ta/tT1) - Power(a[l],n) ) / ( Exp(Ta/tT1) - a[l] );
//	D10  = ( Exp(N*Ta/tT1) - 1 ) / ( Exp(Ta/tT1) - 1 ) - ( Exp(N*Ta/tT1) - Power(a[l],N) ) / ( Exp(Ta/tT1) - a[l] );
	// Untrapped populations at t=0
	v10 = ( a[r1] * Ta * (1-a[p]) * SU10 * Exp(-(T-Tb)/tU1) ) / ( 1 - Exp(-T/tU1) );
	// Untrapped population during background period
	v1 = v10 * Exp(-t[0]/tU1);
	// Background period
	if (0 <= t[0] && t[0] < Tb) {
		f = v1;
	}
	// Trapping period
	if (Tb <= t[0] && t[0] <= T) {
		// Untrapped populations during trapping
		V1 = a[r1] * Ta * (1-a[p]) * SU1 * Exp(-(t[0]-Tb)/tU1);
		f = v1+V1;
	}
	return f;
}

Double_t B_fit_model::V2 (Double_t *t, Double_t *a) {
	using namespace B_fit_model;
	using namespace TMath;
	static Int_t n, N;
	static Double_t tT2, tU2, SU2, SU20, v20, v2, V2, f;
	extern Int_t gdx;
	static const Double_t Ta = bdn_cases[gdx].T_capt;
	static const Double_t Tb = bdn_cases[gdx].T_bkgd;
	static const Double_t T  = bdn_cases[gdx].T_cycle;
	tT2 = a[tauT2];
	tU2 = a[tauU2];
	f = 0.0; //catch bad values of t[0]
	n = Ceil((t[0]-Tb)/Ta);
	N = Ceil(   (T-Tb)/Ta);
	SU2  = ( Exp(n*Ta/tU2) - 1 ) / ( Exp(Ta/tU2) - 1 );
	SU20 = ( Exp(N*Ta/tU2) - 1 ) / ( Exp(Ta/tU2) - 1 );
//	D2   = ( Exp(n*Ta/tT2) - 1 ) / ( Exp(Ta/tT2) - 1 ) - ( Exp(n*Ta/tT2) - Power(a[l],n) ) / ( Exp(Ta/tT2) - a[l] );
//	D20  = ( Exp(N*Ta/tT2) - 1 ) / ( Exp(Ta/tT2) - 1 ) - ( Exp(N*Ta/tT2) - Power(a[l],N) ) / ( Exp(Ta/tT2) - a[l] );
	// Untrapped populations at t=0
	v20 = ( a[r2] * Ta * (1-a[p]) * SU20 * Exp(-(T-Tb)/tU2) ) / ( 1 - Exp(-T/tU2) );
	// Untrapped population during background period
	v2 = v20 * Exp(-t[0]/tU2);
	// Background period
	if (0 <= t[0] && t[0] < Tb) {
		f = v2;
	}
	// Trapping period
	if (Tb <= t[0] && t[0] <= T) {
		// Untrapped populations during trapping
		V2 = a[r2] * Ta * (1-a[p]) * SU2 * Exp(-(t[0]-Tb)/tU2);
		f = v2+V2;
	}
	return f;
}

Double_t B_fit_model::V3 (Double_t *t, Double_t *a) {
	using namespace B_fit_model;
	using namespace TMath;
	static Int_t n, N;
	static Double_t tT3, tU3, SU3, SU30, v30, v3, V3, f;
	extern Int_t gdx;
	static const Double_t Ta = bdn_cases[gdx].T_capt;
	static const Double_t Tb = bdn_cases[gdx].T_bkgd;
	static const Double_t T  = bdn_cases[gdx].T_cycle;
	tT3 = a[tauT3];
	tU3 = a[tauU3];
	f = 0.0; //catch bad values of t[0]
	n = Ceil((t[0]-Tb)/Ta);
	N = Ceil(   (T-Tb)/Ta);
	SU3  = ( Exp(n*Ta/tU3) - 1 ) / ( Exp(Ta/tU3) - 1 );
	SU30 = ( Exp(N*Ta/tU3) - 1 ) / ( Exp(Ta/tU3) - 1 );
//	D3   = ( Exp(n*Ta/tT3) - 1 ) / ( Exp(Ta/tT3) - 1 ) - ( Exp(n*Ta/tT3) - Power(a[l],n) ) / ( Exp(Ta/tT3) - a[l] );
//	D30  = ( Exp(N*Ta/tT3) - 1 ) / ( Exp(Ta/tT3) - 1 ) - ( Exp(N*Ta/tT3) - Power(a[l],N) ) / ( Exp(Ta/tT3) - a[l] );
	// Untrapped populations at t=0
	v30 = ( a[r3] * Ta * (1-a[p]) * SU30 * Exp(-(T-Tb)/tU3) ) / ( 1 - Exp(-T/tU3) );
	// Untrapped population during background period
	v3 = v30 * Exp(-t[0]/tU3);
	// Background period
	if (0 <= t[0] && t[0] < Tb) {
		f = v3;
	}
	// Trapping period
	if (Tb <= t[0] && t[0] <= T) {
		// Untrapped populations during trapping
		V3 = a[r3] * Ta * (1-a[p]) * SU3 * Exp(-(t[0]-Tb)/tU3);
		f = v3+V3;
	}
	return f;
}

Double_t B_fit_model::yV1 (Double_t *t, Double_t *a) {
	using namespace B_fit_model;
	return a[dt]*a[epsV]*V1(t,a)/a[tauU1];
}
Double_t B_fit_model::yV2 (Double_t *t, Double_t *a) {
	using namespace B_fit_model;
	return a[dt]*a[epsV]*V2(t,a)/a[tauU2];
}
Double_t B_fit_model::yV3 (Double_t *t, Double_t *a) {
	using namespace B_fit_model;
	return a[dt]*a[epsV]*V3(t,a)/a[tauU3];
}

// W populations
Double_t B_fit_model::W1 (Double_t *t, Double_t *a) {
	using namespace B_fit_model;
	using namespace TMath;
	static Int_t n, N;
	static Double_t tT1, tU1, D1, D10, w10, w1, W1, f;
	extern Int_t gdx;
	static const Double_t Ta = bdn_cases[gdx].T_capt;
	static const Double_t Tb = bdn_cases[gdx].T_bkgd;
	static const Double_t T  = bdn_cases[gdx].T_cycle;
	tT1 = a[tauT1];
	tU1 = a[tauU1];
	f = 0.0; //catch bad values of t[0]
	n = Ceil((t[0]-Tb)/Ta);
	N = Ceil(   (T-Tb)/Ta);
//	SU1  = ( Exp(n*Ta/tU1) - 1 ) / ( Exp(Ta/tU1) - 1 );
//	SU10 = ( Exp(N*Ta/tU1) - 1 ) / ( Exp(Ta/tU1) - 1 );
	D1   = ( Exp(n*Ta/tT1) - 1 ) / ( Exp(Ta/tT1) - 1 ) - ( Exp(n*Ta/tT1) - Power(a[l],n) ) / ( Exp(Ta/tT1) - a[l] );
	D10  = ( Exp(N*Ta/tT1) - 1 ) / ( Exp(Ta/tT1) - 1 ) - ( Exp(N*Ta/tT1) - Power(a[l],N) ) / ( Exp(Ta/tT1) - a[l] );
	// Untrapped populations at t=0
	w10 = ( a[r1] * Ta * a[p] * D10 * Exp(-(T-Tb)/tU1) ) / ( 1 - Exp(-T/tU1) );
	// Untrapped population during background period
	w1 = w10 * Exp(-t[0]/tU1);
	// Background period
	if (0 <= t[0] && t[0] < Tb) {
		f = w1;
	}
	// Trapping period
	if (Tb <= t[0] && t[0] <= T) {
		// Untrapped populations during trapping
		W1 = a[r1] * Ta * a[p] * D1 * Exp(-(t[0]-Tb)/tU1);
		f = w1 + W1;
	}
	return f;
}
Double_t B_fit_model::W2 (Double_t *t, Double_t *a) {
	using namespace B_fit_model;
	using namespace TMath;
	static Int_t n, N;
	static Double_t tT2, tU2, D2, D20, w20, w2, W2, f;
	extern Int_t gdx;
	static const Double_t Ta = bdn_cases[gdx].T_capt;
	static const Double_t Tb = bdn_cases[gdx].T_bkgd;
	static const Double_t T  = bdn_cases[gdx].T_cycle;
	tT2 = a[tauT2];
	tU2 = a[tauU2];
	f = 0.0; //catch bad values of t[0]
	n = Ceil((t[0]-Tb)/Ta);
	N = Ceil(   (T-Tb)/Ta);
//	SU2  = ( Exp(n*Ta/tU2) - 1 ) / ( Exp(Ta/tU2) - 1 );
//	SU20 = ( Exp(N*Ta/tU2) - 1 ) / ( Exp(Ta/tU2) - 1 );
	D2   = ( Exp(n*Ta/tT2) - 1 ) / ( Exp(Ta/tT2) - 1 ) - ( Exp(n*Ta/tT2) - Power(a[l],n) ) / ( Exp(Ta/tT2) - a[l] );
	D20  = ( Exp(N*Ta/tT2) - 1 ) / ( Exp(Ta/tT2) - 1 ) - ( Exp(N*Ta/tT2) - Power(a[l],N) ) / ( Exp(Ta/tT2) - a[l] );
	// Untrapped populations at t=0
	w20 = ( a[r2] * Ta * a[p] * D20 * Exp(-(T-Tb)/tU2) ) / ( 1 - Exp(-T/tU2) );
	// Untrapped population during background period
	w2 = w20 * Exp(-t[0]/tU2);
	// Background period
	if (0 <= t[0] && t[0] < Tb) {
		f = w2;
	}
	// Trapping period
	if (Tb <= t[0] && t[0] <= T) {
		// Untrapped populations during trapping
		W2 = a[r2] * Ta * a[p] * D2 * Exp(-(t[0]-Tb)/tU2);
		f = w2 + W2;
	}
	return f;
}
Double_t B_fit_model::W3 (Double_t *t, Double_t *a) {
	using namespace B_fit_model;
	using namespace TMath;
	static Int_t n, N;
	static Double_t tT3, tU3, D3, D30, w30, w3, W3, f;
	extern Int_t gdx;
	static const Double_t Ta = bdn_cases[gdx].T_capt;
	static const Double_t Tb = bdn_cases[gdx].T_bkgd;
	static const Double_t T  = bdn_cases[gdx].T_cycle;
	tT3 = a[tauT3];
	tU3 = a[tauU3];
	f = 0.0; //catch bad values of t[0]
	n = Ceil((t[0]-Tb)/Ta);
	N = Ceil(   (T-Tb)/Ta);
//	SU3  = ( Exp(n*Ta/tU3) - 1 ) / ( Exp(Ta/tU3) - 1 );
//	SU30 = ( Exp(N*Ta/tU3) - 1 ) / ( Exp(Ta/tU3) - 1 );
	D3   = ( Exp(n*Ta/tT3) - 1 ) / ( Exp(Ta/tT3) - 1 ) - ( Exp(n*Ta/tT3) - Power(a[l],n) ) / ( Exp(Ta/tT3) - a[l] );
	D30  = ( Exp(N*Ta/tT3) - 1 ) / ( Exp(Ta/tT3) - 1 ) - ( Exp(N*Ta/tT3) - Power(a[l],N) ) / ( Exp(Ta/tT3) - a[l] );
	// Untrapped populations at t=0
	w30 = ( a[r3] * Ta * a[p] * D30 * Exp(-(T-Tb)/tU3) ) / ( 1 - Exp(-T/tU3) );
	// Untrapped population during background period
	w3 = w30 * Exp(-t[0]/tU3);
	// Background period
	if (0 <= t[0] && t[0] < Tb) {
		f = w3;
	}
	// Trapping period
	if (Tb <= t[0] && t[0] <= T) {
		// Untrapped populations during trapping
		W3 = a[r3] * Ta * a[p] * D3 * Exp(-(t[0]-Tb)/tU3);
		f = w3 + W3;
	}
	return f;
}
Double_t B_fit_model::yW1 (Double_t *t, Double_t *a) {
	using namespace B_fit_model;
	return a[dt]*a[epsW]*W1(t,a)/a[tauU1];
}
Double_t B_fit_model::yW2 (Double_t *t, Double_t *a) {
	using namespace B_fit_model;
	return a[dt]*a[epsW]*W2(t,a)/a[tauU2];
}
Double_t B_fit_model::yW3 (Double_t *t, Double_t *a) {
	using namespace B_fit_model;
	return a[dt]*a[epsW]*W3(t,a)/a[tauU3];
}

Double_t B_fit_model::X2 (Double_t *t, Double_t *a) {
	using namespace B_fit_model;
	using namespace TMath;
	static Int_t n, N;
	static Double_t t1, tT1, tT2, tU1, tU2, ST1, ST10, SU2, SU20, x20, x2, X2, f;
	extern Int_t gdx;
	static const Double_t Ta = bdn_cases[gdx].T_capt;
	static const Double_t Tb = bdn_cases[gdx].T_bkgd;
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
	n = Ceil((t[0]-Tb)/Ta);
	N = Ceil(   (T-Tb)/Ta);
	ST1  = ( Exp(n*Ta/tT1) - 1 ) / ( Exp(Ta/tT1) - 1 );
	ST10 = ( Exp(N*Ta/tT1) - 1 ) / ( Exp(Ta/tT1) - 1 );
	SU2  = ( Exp(n*Ta/tU2) - 1 ) / ( Exp(Ta/tU2) - 1 );
	SU20 = ( Exp(N*Ta/tU2) - 1 ) / ( Exp(Ta/tU2) - 1 );
	// Untrapped populations at t=0
	x20 = ( a[r1] * Ta * a[p] * tT1/t1 * tU2/(tU2-tT1) * ( SU20 * Exp(-(T-Tb)/tU2) - ST10 * Exp(-(T-Tb)/tT1) ) ) / ( 1 - Exp(-T/tU2) );
	// Untrapped population during background period
	x2 = x20*Exp(-t[0]/tU2) ;
	// Background period
	if (0 <= t[0] && t[0] < Tb) {
		f = x2;
	}
	// Trapping period
	if (Tb <= t[0] && t[0] <= T) {
		// Untrapped populations during trapping
		X2 = a[r1] * Ta * a[p] * tT1/t1 * tU2/(tU2-tT1) * ( SU2 * Exp(-(t[0]-Tb)/tU2) - ST1 * Exp(-(t[0]-Tb)/tT1) );
		f = x2 + X2;
	}
	return f;
}

Double_t B_fit_model::X3 (Double_t *t, Double_t *a) {
	using namespace B_fit_model;
	using namespace TMath;
	static Int_t n, N;
	static Double_t t2, tT2, tT3, tU2, tU3, ST2, ST20, SU3, SU30, x30, x3, X3, f;
	extern Int_t gdx;
	static const Double_t Ta = bdn_cases[gdx].T_capt;
	static const Double_t Tb = bdn_cases[gdx].T_bkgd;
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
	n = Ceil((t[0]-Tb)/Ta);
	N = Ceil(   (T-Tb)/Ta);
	ST2  = ( Exp(n*Ta/tT2) - 1 ) / ( Exp(Ta/tT2) - 1 );
	ST20 = ( Exp(N*Ta/tT2) - 1 ) / ( Exp(Ta/tT2) - 1 );
	SU3  = ( Exp(n*Ta/tU3) - 1 ) / ( Exp(Ta/tU3) - 1 );
	SU30 = ( Exp(N*Ta/tU3) - 1 ) / ( Exp(Ta/tU3) - 1 );
	// Untrapped populations at t=0
	x30 = ( a[r2] * Ta * a[p] * tT2/t2 * tU3/(tU3-tT2) * ( SU30 * Exp(-(T-Tb)/tU3) - ST20 * Exp(-(T-Tb)/tT2) ) ) / ( 1 - Exp(-T/tU3) );
	// Untrapped population during background period
	x3 = x30 * Exp(-t[0]/tU3);
	// Background period
	if (0 <= t[0] && t[0] < Tb) {
		f = x3;
	}
	// Trapping period
	if (Tb <= t[0] && t[0] <= T) {
		// Untrapped populations during trapping
		X3 = a[r2] * Ta * a[p] * tT2/t2 * tU3/(tU3-tT2) * ( SU3 * Exp(-(t[0]-Tb)/tU3) - ST2 * Exp(-(t[0]-Tb)/tT2) );
		f = x3 + X3;
	}
	return f;
}

Double_t B_fit_model::yX2 (Double_t *t, Double_t *a) {
	using namespace B_fit_model;
	return a[dt]*a[epsX]*X2(t,a)/a[tauU2];
}
Double_t B_fit_model::yX3 (Double_t *t, Double_t *a) {
	using namespace B_fit_model;
	return a[dt]*a[epsX]*X3(t,a)/a[tauU3];
}

Double_t B_fit_model::Y2 (Double_t *t, Double_t *a) {
	using namespace B_fit_model;
	using namespace TMath;
	static Int_t n, N;
	static Double_t t1, tT1, tT2, tU1, tU2, ST1, ST10, SU1, SU10, SU2, SU20, y10, y20, y2, Y2, f;
	extern Int_t gdx;
	static const Double_t Ta = bdn_cases[gdx].T_capt;
	static const Double_t Tb = bdn_cases[gdx].T_bkgd;
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
	n = Ceil((t[0]-Tb)/Ta);
	N = Ceil(   (T-Tb)/Ta);
//	ST1  = ( Exp(n*Ta/tT1) - 1 ) / ( Exp(Ta/tT1) - 1 );
//	ST10 = ( Exp(N*Ta/tT1) - 1 ) / ( Exp(Ta/tT1) - 1 );
	SU1  = ( Exp(n*Ta/tU1) - 1 ) / ( Exp(Ta/tU1) - 1 );
	SU10 = ( Exp(N*Ta/tU1) - 1 ) / ( Exp(Ta/tU1) - 1 );
	SU2  = ( Exp(n*Ta/tU2) - 1 ) / ( Exp(Ta/tU2) - 1 );
	SU20 = ( Exp(N*Ta/tU2) - 1 ) / ( Exp(Ta/tU2) - 1 );
	
	// Untrapped populations at t=0
	y10 = a[r1] * Ta * (1-a[p]) * SU10 * Exp(-(T-Tb)/tU1) / ( 1 - Exp(-T/tU1) );
	y20 = ( y10 * tU1/t1 * tU2/(tU2-tU1) * ( Exp(-T/tU2) - Exp(-T/tU1) ) + a[r1] * Ta * (1-a[p]) * tU1/t1 * tU2/(tU2-tU1) * ( SU20 * Exp(-(T-Tb)/tU2) - SU10 * Exp(-(T-Tb)/tU1) ) ) / (1-Exp(-T/tU2) );
	// Untrapped population during background period
	y2 = y20 * Exp(-t[0]/tU2) + y10 * tU1/t1 * tU2/(tU2-tU1) * ( Exp(-t[0]/tU2) - Exp(-t[0]/tU1 ) );
	// Background period
	if (0 <= t[0] && t[0] < Tb) {
		f = y2;
	}
	// Trapping period
	if (Tb <= t[0] && t[0] <= T) {
		// Untrapped populations during trapping
		Y2 = a[r1] * Ta * (1-a[p]) * tU1/t1 * tU2/(tU2-tU1) * ( SU2 * Exp(-(t[0]-Tb)/tU2) - SU1 * Exp(-(t[0]-Tb)/tU1) );
		f = y2 + Y2;
	}
	return f;
}

Double_t B_fit_model::Y3 (Double_t *t, Double_t *a) {
	using namespace B_fit_model;
	using namespace TMath;
	static Int_t n, N;
	static Double_t t1, t2, t3, tT1, tT2, tT3, tU1, tU2, tU3, AU, ST1, ST2, ST3, ST10, ST20, ST30, SU1, SU2, SU3, SU10, SU20, SU30, y10, y20, y30, y3, Y3, f;
	extern Int_t gdx;
	static const Double_t Ta = bdn_cases[gdx].T_capt;
	static const Double_t Tb = bdn_cases[gdx].T_bkgd;
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
	n = Ceil((t[0]-Tb)/Ta);
	N = Ceil(   (T-Tb)/Ta);
	SU1  = ( Exp(n*Ta/tU1) - 1 ) / ( Exp(Ta/tU1) - 1 );
	SU2  = ( Exp(n*Ta/tU2) - 1 ) / ( Exp(Ta/tU2) - 1 );
	SU3  = ( Exp(n*Ta/tU3) - 1 ) / ( Exp(Ta/tU3) - 1 );
	SU10 = ( Exp(N*Ta/tU1) - 1 ) / ( Exp(Ta/tU1) - 1 );
	SU20 = ( Exp(N*Ta/tU2) - 1 ) / ( Exp(Ta/tU2) - 1 );
	SU30 = ( Exp(N*Ta/tU3) - 1 ) / ( Exp(Ta/tU3) - 1 );
	// Untrapped populations at t=0
	y10 = 
		a[r1] * Ta * (1-a[p]) * SU10 * Exp(-(T-Tb)/tU1) / ( 1 - Exp(-T/tU1) );
	y20 = (
		y10 * tU1/t1 * tU2/(tU2-tU1) * ( Exp(-T/tU2) - Exp(-T/tU1) ) +
		a[r2] * Ta * (1-a[p]) *            SU20*Exp(-(T-Tb)/tU2) + 
		a[r1] * Ta * (1-a[p]) * tU1/t1 * tU2/(tU2-tU1) * (SU20 * Exp(-(T-Tb)/tU2) - SU10 * Exp(-(T-Tb)/tU1) )
		)
		/ ( 1 - Exp(-T/tU2) );
	y30 = (
		y20 * tU2/t2 * tU3/(tU3-tU2) * ( Exp(-T/tU3) - Exp(-T/tU2) ) + 
		y10 * tU1/t1 * tU2/t2 * tU3/AU * ( tU1 * (tU3-tU2) * Exp(-T/tU1) - tU2 * (tU3-tU1) * Exp(-T/tU2) + tU3 * (tU2-tU1) * Exp(-T/tU3) ) + 
//		a[r3]*Ta*(1-a[p])*                 S30*Exp(-(T-Tb)/t3) + 
		a[r2] * Ta * (1-a[p]) * tU2/t2 * tU3/(tU3-tU2) *     (SU30*Exp(-(T-Tb)/tU3) -            SU20*Exp(-(T-Tb)/tU2)) + 
		a[r1] * Ta * (1-a[p]) * tU1/t1 * tU2/t2 * tU3/AU * ( tU1 * (tU3-tU2) * SU10 * Exp(-(T-Tb)/tU1) - tU2 * (tU3-tU1) * SU20 * Exp(-(T-Tb)/tU2) + tU3 * (tU2-tU1) * SU30 * Exp(-(T-Tb)/tU3) )
		)
		/ ( 1 - Exp(-T/tU3) );
	// Untrapped population during background period
	y3 = 
		y30 * Exp(-t[0]/tU3) + 
		y20 * tU2/t2 * tU3/(tU3-tU2) * ( Exp(-t[0]/tU3) - Exp(-t[0]/tU2) ) + 
		y10 * tU1/t1 * tU2/t2 * tU3/AU * ( tU1 * (tU3-tU2) * Exp(-t[0]/tU1) - tU2 * (tU3-tU1) * Exp(-t[0]/tU2) + tU3 * (tU2-tU1) * Exp(-t[0]/tU3) );
	// Background period
	if (0 <= t[0] && t[0] < Tb) {
		f = y3;
	}
	// Trapping period
	if (Tb <= t[0] && t[0] <= T) {
		// Untrapped populations during trapping
		Y3 = 
			a[r2] * Ta * (1-a[p]) * tU2/t2 * tU3/(tU3-tU2) * ( SU3 * Exp(-(t[0]-Tb)/tU3) - SU2 * Exp(-(t[0]-Tb)/tU2) ) + 
			a[r1] * Ta * (1-a[p]) * tU1/t1 * tU2/t2 * tU3/AU * ( tU1 * (tU3-tU2) * SU1 * Exp(-(t[0]-Tb)/tU1) - tU2 * (tU3-tU1) * SU2 * Exp(-(t[0]-Tb)/tU2) + tU3 * (tU2-tU1) * SU3 * Exp(-(t[0]-Tb)/tU3) );
		f = y3 + Y3;
	}
	return f;
}

Double_t B_fit_model::yY2 (Double_t *t, Double_t *a) {
	using namespace B_fit_model;
	return a[dt]*a[epsY]*Y2(t,a)/a[tauU2];
}
Double_t B_fit_model::yY3 (Double_t *t, Double_t *a) {
	using namespace B_fit_model;
	return a[dt]*a[epsY]*Y3(t,a)/a[tauU3];
}
*/
