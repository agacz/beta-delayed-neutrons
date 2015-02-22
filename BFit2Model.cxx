//////////////////////////////////////////////////////////////////////////
//
// BFit2Model by Shane Caldwell
// 2015-01-22
//
// This is an overhaul of BFit designed to make it faster. The model functions,
// at least to begin with, are the same. The key upgrade is that the yAll function
// precomputes dozens of special values that are used throughout the evaluations
// of the component functions. These values live in the global namespace and are
// declared above main() in BFit2.cxx.
//
// All of the precomputed values are parameter-dependent and independent of t. Computing
// them for every t and in every component was a huge waste of time. The fitting
// was just too slow. (Also made for ugly code, but made it easy to build up the 
// model one function at a time.) So the yAll function detects a change in the parameters
// made by the TH1::Fit routine, and then updates these parameter-dependent quantities.
//
// I also tried precomputing a number of time-dependent quantites that appear repeatedly:
// namely the injection number n and the various Exp decay factors. This causes a 
// problem with the way I calculate the initial values, eg. Y20 from Ycap(t=tCyc).
// I ended up going back and just doing these in  each function. It's not the fastest 
// possible way, but it is fast enough and allows an easy construction of the initial
// value in the ComputeParameterDependentVars(), where it belongs.
//
// I have tried to lay out the code in a logical way, but the precomputation of data
// means that the definitions of values are not near their use. If you are reading this
// code to understand its logic, I recommend that you begin by learning
// how the T and V populations work. These are conceptually very simple. The T pops
// have no background component, while V is like a T but with a background part.
// The other populations, except for Y, follow the same logic.
//
// The Y populations are another beast. They differ in that there is no attempt to
// put them into closed form, as I have done for the others using the SigmaT, SigmaW,
// and SigmaZ functions. Instead I use the YxInitialValue() functions to compute a
// Yx that has the right boundary value at each injection, then I sum a bunch of
// these in a 'for' loop in Ycap(). The background parts of the Y pops contain
// feeding from other untrapped pops, as is evidenced by the computations of
// Y20 and Y30 in yAll as well as in the functions YxBackground().
//
// In case you are not aware of it, my thesis contains an appendix that describes
// the model in detail, including derivations of all functions.
//
// May the betas be ever in your favor!
//   --Shane
//////////////////////////////////////////////////////////////////////////

#include "BFit2Model.h"
#include "CSVtoStruct.h"
#include "TMath.h"
//#include "string.h"
#include <iostream>
using namespace std;

bool BFitNamespace::CompareParArrays (const Double_t *par1, const Double_t *par2, size_t n, Double_t eps) {
	if (sizeof(par1) != sizeof(par2)) cout << "Tried to compare to non-equal-length arrays! Results not guaranteed." << endl << endl;
	for (size_t i=0; i<n; i++) if (fabs(par1[i]-par2[i]) > eps) return false;
	return true;
}

void BFitNamespace::ComputeParameterDependentVars (Double_t *a) {
	using namespace BFitNamespace;
	using namespace TMath;
// Global variables that are constant throughout the fit
	extern Int_t nCapMax;
	extern Double_t iota, tCap, tBac, tCyc, t1, t2, t3;
	extern Double_t eU1tCyc, eU2tCyc, eU3tCyc;
	extern bool b134sbFlag;
// Global variables that depend only on the parameters
	extern Double_t tT1, tT2, tT3, tU1, tU2, tU3;
	extern Double_t aT1, aT2, aT3, aU1, aU2, aU3;
	extern Double_t tT1U2, tT1U3, tU1U2, tU1U3, tT2U3, tU2U3;
	extern Double_t cT1, cU1, cU2, cZT2, cZU2, cZU3, cXT1, cXU2, cXU3, cYU1, cYU2, cYU3, ThetaU, ThetaY;
	extern Double_t ST1_1cap, SW11_1cap, SZ11_1cap, ST2_1cap, SW22_1cap, SZ12_1cap, SZ22_1cap;
//	extern Double_t ST1val, SW11val, SZ11val, ST2val, SW22val, SZ12val, SZ22val;
	extern Double_t	*timeOfCapt;
	extern Double_t	*ST1val, *ST2val, *ST3val;
	extern Double_t	*SV1val, *SV2val, *SV3val;
	extern Double_t	*SW1val, *SW2val, *SW3val;
	extern Double_t	*SZ1val, *SZ2val, *SZ3val;
	extern Double_t			 *SX2val, *SX3val;
	extern Double_t	*sY2V, *sY2W, *sY2Z, *SY2val;
	extern Double_t	*sY3V, *sY3W, *sY3Z, *sY3X, *sY3YV, *sY3YW, *sY3YZ, *SY3val;
	extern Double_t	*timeOfCapt;
	extern Double_t	Gamma_T1_U2, Gamma_T2_U3;
	extern Double_t	Gamma_U1_U2, Gamma_U2_U3;
	extern Double_t	*I_V1_Y2, *I_V2_Y3;
	extern Double_t	*I_W1_Y2, *I_W2_Y3;
	extern Double_t	*I_Z1_Y2, *I_Z2_Y3;
	extern Double_t	*I_X1_Y2, *I_X2_Y3;
	extern Double_t			  *I_Y2_Y3;
	extern Double_t	*Y2InitialValues, *Y3InitialValues;
	extern Double_t ampT1, ampT2, ampT3;
	extern Double_t ampV1, ampV2, ampV3;
	extern Double_t ampW1, ampW2, ampW3;
	extern Double_t ampZ1, ampZ2, ampZ3;
	extern Double_t ampX2, ampX3;
	extern Double_t ampY2ptA, ampY2ptB;
	extern Double_t ampY3fromV2, ampY3fromW2, ampY3fromZ2, ampY3fromX2, ampY3fromY2_ST1, ampY3fromY2_SW11, ampY3fromY2_SZ11;
	extern Double_t V10, V20, V30, W10, W20, W30, Z10, Z20, Z30, X20, X30, Y20, Y30, U10, U20, U30;
//	extern Int_t nPars, nParChanges, nCap, nCapMax;
	extern Double_t *lastPar;//, *tCycArg;
	static Int_t index, tooth, k;
	static Double_t H_T1_U2, H_U1_U2, H_T2_U3, H_U2_U3;
	
// Update parameter-dependent variables
	
// Special cases:
	if (b134sbFlag) a[gammaT3] = a[gammaT2];
	
// Modified lifetimes:
	tT1 = 1.0 / ( 1.0/t1 + a[gammaT1]/1000.0 ); // net variable lifetvar (1/e) in ms
	tT2 = 1.0 / ( 1.0/t2 + a[gammaT2]/1000.0 ); // net variable lifetvar (1/e) in ms
	tT3 = 1.0 / ( 1.0/t3 + a[gammaT3]/1000.0 ); // net variable lifetvar (1/e) in ms
	tU1 = 1.0 / ( 1.0/t1 + a[gammaU1]/1000.0 ); // net variable lifetvar (1/e) in ms
	tU2 = 1.0 / ( 1.0/t2 + a[gammaU2]/1000.0 ); // net variable lifetvar (1/e) in ms
	tU3 = 1.0 / ( 1.0/t3 + a[gammaU3]/1000.0 ); // net variable lifetvar (1/e) in ms
	printf("tT1=%f, tT2=%f, tT3=%f, tU1=%f, tU2=%f, tU3=%f\n", tT1, tT2, tT3, tU1, tU2, tU3);
///////////////////////////////////////////////////////////////////////////////////////////////
	Gamma_T1_U2	= 1/tT1 - 1/tU2;
	Gamma_U1_U2	= 1/tU1 - 1/tU2;
	Gamma_T2_U3	= 1/tT2 - 1/tU3;
	Gamma_U2_U3	= 1/tU2 - 1/tU3;
///////////////////////////////////////////////////////////////////////////////////////////////
	cT1		= tT1*(tU2-tU1);
	cU1		= tU1*(tU2-tT1);
	cU2		= tU2*(tU1-tT1);
	cZT2	= tT2*(tU3-tU2);
	cZU2	= tU2*(tU3-tT2);
	cZU3	= tU3*(tU2-tT2);
	cXT1	= tT1*(tU3-tU2);
	cXU2	= tU2*(tU3-tT1);
	cXU3	= tU3*(tU2-tT1);
	cYU1	= tU1*(tU3-tU2);
	cYU2	= tU2*(tU3-tU1);
	cYU3	= tU3*(tU2-tU1);
	ThetaU	= (tU3-tU2)*(tU3-tU1)*(tU2-tU1);
//	ThetaY	= (tU3-tT1)*(tU2-tT1)*(tU1-tT1);
	aT1 = Exp(-tCap/tT1);
	aT2 = Exp(-tCap/tT2);
	aT3 = Exp(-tCap/tT3);
	aU1 = Exp(-tCap/tU1);
	aU2 = Exp(-tCap/tU2);
	aU3 = Exp(-tCap/tU3);
	tT1U2	= tT1*tU2/(tU2-tT1);
	tT1U3	= tT1*tU3/(tU3-tT1);
	tU1U2	= tU1*tU2/(tU2-tU1);
	tU1U3	= tU1*tU3/(tU3-tU1);
	tT2U3	= tT2*tU3/(tU3-tT2);
	tU2U3	= tU2*tU3/(tU3-tU2);
///////////////////////////////////////////////////////////////////////////////////////////////
	ST1_1cap	= 0.0;//SigmaT(a[rho],tT1,1);
	ST2_1cap	= 0.0;//SigmaT(a[rho],tT2,1);
	SW11_1cap	= 0.0;//SigmaW(a[rho],tT1,tU1,1);
	SW22_1cap	= 0.0;//SigmaW(a[rho],tT2,tU2,1);
	SZ11_1cap	= 0.0;//SigmaZ(a[rho],tT1,tU1,1);
	SZ12_1cap	= 0.0;//SigmaZ(a[rho],tT1,tU2,1);
	SZ22_1cap	= 0.0;//SigmaZ(a[rho],tT2,tU2,1);
///////////////////////////////////////////////////////////////////////////////////////////////
	ampT1		= a[r1] * tCap * a[p];
	ampT2		= a[r2] * tCap * a[p];
	ampT3		= a[r3] * tCap * a[p];
///////////////////////////////////////////////////////////////////////////////////////////////
	ampV1		= a[r1] * tCap * (1-a[p]);
	ampV2		= a[r2] * tCap * (1-a[p]);
	ampV3		= a[r3] * tCap * (1-a[p]);
///////////////////////////////////////////////////////////////////////////////////////////////
	ampW1		= a[r1] * tCap * (1-a[rho]) * a[p];
	ampW2		= a[r2] * tCap * (1-a[rho]) * a[p];
	ampW3		= a[r3] * tCap * (1-a[rho]) * a[p];
///////////////////////////////////////////////////////////////////////////////////////////////
	ampZ1		= a[r1] * tCap * a[p] * (a[gammaT1]+iota)/((a[gammaT1]-a[gammaU1])+iota);
	ampZ2		= a[r2] * tCap * a[p] * (a[gammaT2]+iota)/((a[gammaT2]-a[gammaU2])+iota);
	ampZ3		= a[r3] * tCap * a[p] * (a[gammaT3]+iota)/((a[gammaT3]-a[gammaU3])+iota);
///////////////////////////////////////////////////////////////////////////////////////////////
	ampX2		= a[r1] * tCap * a[p] * (1/t1) * (tT1*tU2/(tU2-tT1));
	ampX3		= a[r2] * tCap * a[p] * (1/t2) * (tT2*tU3/(tU3-tT2));
///////////////////////////////////////////////////////////////////////////////////////////////
	ampY2ptA	= a[p] * (a[gammaT1]+iota)/(a[gammaT1]-a[gammaU1]+iota)/tU1/(tU2-tT1);
	ampY2ptB	= a[r1] * (tCap/t1) * tU1*tU2/(tU2-tU1);
///////////////////////////////////////////////////////////////////////////////////////////////
	ampY3fromV2	= a[r2] * (tCap/t2) * tU2 * tU3 / (tU3-tU2) * (1-a[p]);
	ampY3fromW2	= a[r2] * (tCap/t2) * tU2 * tU3 / (tU3-tU2) * a[p] * (1-a[rho]);
	ampY3fromZ2	= a[r2] * (tCap/t2) * tU2 * tU3 / (tU3-tU2) * a[p] * (a[gammaT2]+iota) / (a[gammaT2]-a[gammaU2]+iota); // (X2,Z2)~(1/t1,a[gammaT1])~(rad,non-rad) decay of T1
	ampY3fromX2	= a[r1] * (tCap/t2) * tU2 * tU3 / (tU3-tU2) * a[p] * tT1 * tU2 / (tU2-tT1) / t1; // a[gammaT2]/(a[gammaT2]-a[gammaU2]) is a simplification of tT2*tU2/(tU2-tT2)/(1/a[gammaT2])
//	ampY3fromY2_ST1	 = a[r1] * (tCap/t2) * tU1 * tU2 * tU3 / ThetaU / t1 * (a[gammaT1]+iota) / (a[gammaT1]-a[gammaU1]+iota) * (tU1-tT1) / tU1 / (a[gammaT1]/1000.0+iota) / ThetaY;
	ampY3fromY2_ST1	 = a[r1] * (tCap/t2) * tU1 * tU2 * tU3 / ThetaU / t1 * (a[gammaT1]+iota) / (a[gammaT1]-a[gammaU1]+iota) / tU1 / (a[gammaT1]/1000.0+iota) / (tU3-tT1)/(tU2-tT1);
	ampY3fromY2_SW11 = a[r1] * (tCap/t2) * tU1 * tU2 * tU3 / ThetaU / t1 * a[p] * (1-a[rho]);
	ampY3fromY2_SZ11 = a[r1] * (tCap/t2) * tU1 * tU2 * tU3 / ThetaU / t1 * a[p] * (a[gammaT1]+iota) / (a[gammaT1]-a[gammaU1]+iota);
///////////////////////////////////////////////////////////////////////////////////////////////
	eU1tCyc	= Exp(-tCyc/tU1);
	eU2tCyc	= Exp(-tCyc/tU2);
	eU3tCyc	= Exp(-tCyc/tU3);
///////////////////////////////////////////////////////////////////////////////////////////////
	// Arrays holding all the partial sum terms ($\sigma(n)$ in my thesis)
	// zero index of these set to zero in BFit()
	for (k=1; k<=nCapMax; k++) {
		ST1val[k] = sigmaI(a[rho],aT1,k);//SigmaT(a[rho],tT1,k);
		ST2val[k] = sigmaI(a[rho],aT2,k);//SigmaT(a[rho],tT2,k);
		ST3val[k] = sigmaI(a[rho],aT3,k);//SigmaT(a[rho],tT3,k);
		SV1val[k] = sigmaI(1.0000,aU1,k);//SigmaT(1.0000,tU1,k);
		SV2val[k] = sigmaI(1.0000,aU2,k);//SigmaT(1.0000,tU2,k);
		SV3val[k] = sigmaI(1.0000,aU3,k);//SigmaT(1.0000,tU3,k);
		SW1val[k] = aT1 * sigmaII(a[rho],aT1,aU1,k);//SigmaW(a[rho],tT1,tU1,k);
		SW2val[k] = aT2 * sigmaII(a[rho],aT2,aU2,k);//SigmaW(a[rho],tT2,tU2,k);
		SW3val[k] = aT3 * sigmaII(a[rho],aT3,aU3,k);//SigmaW(a[rho],tT3,tU3,k);
		SZ1val[k] = (aU1-aT1) * sigmaII(a[rho],aT1,aU1,k) + ST1val[k];//SigmaZ(a[rho],tT1,tU1,k);
		SZ2val[k] = (aU2-aT2) * sigmaII(a[rho],aT2,aU2,k) + ST2val[k];//SigmaZ(a[rho],tT2,tU2,k);
		SZ3val[k] = (aU3-aT3) * sigmaII(a[rho],aT3,aU3,k) + ST3val[k];//SigmaZ(a[rho],tT3,tU3,k);
		SX2val[k] = (aU2-aT1) * sigmaII(a[rho],aT1,aU2,k) + ST1val[k];//SigmaZ(a[rho],tT1,tU2,k);
		SX3val[k] = (aU3-aT2) * sigmaII(a[rho],aT2,aU3,k) + ST2val[k];//SigmaZ(a[rho],tT2,tU3,k);
		// Components of Y2 initial value:
		sY2v1[k]  = tU1U2/t1 * (aU2-aU1) * sigmaII(1,aU1,aU2,k);
		sY2w1[k]  = tU1U2/t1 * (aU2-aU1) * aT1 * sigmaIII(a[rho],aT1,aU1,aU2,k);
		sY2z1[k]  = tU1U2/t1 * (aU2-aU1) * ( sigmaII(a[rho],aT1,aU2,k) + (aU1-aT1) * sigmaIII(a[rho],aT1,aU1,aU2,k) ) - tT1U2/t1 * (aU2-aT1) * sigmaII(a[rho],aT1,aU2,k);
		SY2val[k] = ampV1*sY2v1[k] + ampW1*sY2w1[k] + ampZ1*sY2z1[k];
		// Components of Y3 initial value:
		sY3v2[k]  = tU2U3/t2 * (aU3-aU2) * sigmaII(1,aU2,aU3,k);
		sY3w2[k]  = tU2U3/t2 * (aU3-aU2) * aT2 * sigmaIII(a[rho],aT2,aU2,aU3,k);
		sY3z2[k]  = tU2U3/t2 * (aU3-aU2) * ( sigmaII(a[rho],aT2,aU3,k) + (aU2-aT2) * sigmaIII(a[rho],aT2,aU2,aU3,k) ) - tT2U3/t2 * (aU3-aT2) * sigmaII(a[rho],aT2,aU3,k);
		sY3x2[k]  = tU2U3/t2 * (aU3-aU2) * ( sigmaII(a[rho],aT1,aU3,k) + (aU2-aT1) * sigmaIII(a[rho],aT1,aU2,aU3,k) ) - tT1U3/t2 * (aU3-aT1) * sigmaII(a[rho],aT1,aU3,k);
		sY3v1[k]  = tU1U2/t1 * ( tU2U3/t2 * (aU3-aU2) * ( sigmaII(1,aU1,aU3,k) + (aU2-aU1)*sigmaIII(1,aU1,aU2,aU3,k) ) - tU1U3/t2 * (aU3-aU1) * sigmaII(1,aU1,aU3,k) );
		//sY3v1[k]  = tU1U2/t1 * tU2U3/t2 * (aU3-aU2) * (aU2-aU1) * sigmaIII(1,aU1,aU2,aU3,k);
		//sY3v1[k] += tU1U2/t1 * tU2U3/t2 * (aU3-aU2) * sigmaII(1,aU1,aU3,k);
		//sY3v1[k] -= tU1U2/t1 * tU1U3/t2 * (aU3-aU1) * sigmaII(1,aU1,aU3,k);
		//sY3w1[k]  = tU1U2/t1 * ( tU2U3/t2 * (aU3-aU2) * ( sigmaIII(a[rho],aT1,aU1,aU3,k) + (aU2-aU1)*sigmaIV(a[rho],aT1,aU1,aU2,aU3,k) ) - tU1U3/t2 * (aU3-aU1) * sigmaIII(a[rho],aT1,aU1,aU3,k) ) * aT1;
		sY3w1[k]  = (aT1*tU1U2/t1/t2) * ( (aU3-aU2)*tU2U3*( sigmaIII(a[rho],aT1,aU1,aU3,k) + (aU2-aU1)*sigmaIV(a[rho],aT1,aU1,aU2,aU3,k) ) - (aU3-aU1)*tU1U3*sigmaIII(a[rho],aT1,aU1,aU3,k) );
		SY3val[k] = ampV2*sY3v2[k] + ampW2*sY3w2[k] + ampZ2*sY3z2[k] + ampX2*sY3x2[k] + ampV1*sY3v1[k] + ampW1*sY3w1[k];
		
		//Double_t aa = tU2U3/t2;
		//Double_t bb = tU2U3/t2 * tU1U2/t1;
		//Double_t cc = tU1U3/t2 * tU1U2/t1;
		//Double_t sY3w1 = tU1U2/t1 * (aU2-aU1) * sigmaIV(a[rho],aT1,aU1,aU2,aU3,k);
		//sY3w1[k]  = aa * (aU3-aU2) * aT1 * sY3w1;
		//sY3w1[k] += bb * (aU3-aU2) * aT1 * sigmaIII(a[rho],aT1,aU1,aU3,k);
		//sY3w1[k] -= cc * (aU3-aU1) * aT1 * sigmaIII(a[rho],aT1,aU1,aU3,k);
		
	//	sY3w1[k]  = tU1U2/t1 * aT1 * (aU3-aU2) * tU2U3/t2 * (aU2-aU1) * sIV;//sigmaIV(a[rho],aT1,aU1,aU2,aU3,k);
	//	sY3w1[k] += tU1U2/t1 * aT1 * (aU3-aU2) * tU2U3/t2 * sIII;//sigmaIII(a[rho],aT1,aU1,aU3,k);
	//	sY3w1[k] -= tU1U2/t1 * aT1 * (aU3-aU1) * tU1U3/t2 * sIII;//sigmaIII(a[rho],aT1,aU1,aU3,k);
		//sY3w1[k]  = aT1 * tU1U2/t1 * tU2U3/t2 * (aU3-aU2) * ( sigmaIII(a[rho],aT1,aU1,aU3,k) + (aU2-aU1)*sigmaIV(a[rho],aT1,aU1,aU2,aU3,k) );
		//sY3w1[k] -=	aT1 * tU1U2/t1 * tU1U3/t2 * (aU3-aU1) *   sigmaIII(a[rho],aT1,aU1,aU3,k);
		
		Double_t sIII = sigmaIII(a[rho],aT1,aU1,aU3,k);
		Double_t sIV  = sigmaIV (a[rho],aT1,aU1,aU2,aU3,k);
		printf("n=%d, sIII=%f, sIV=%f, sY3YW=%f, SY3=%f\n", k, sIII, sIV, sY3w1[k], SY3val[k]);
		
	//	I_V2_Y3[k] = I_V2_Y3[k-1] + SV2val[k] * H_V2_Y3(a,timeOfCapt[k-1],timeOfCapt[k]);
	//	I_W2_Y3[k] = I_W2_Y3[k-1] + SW2val[k] * H_W2_Y3(a,timeOfCapt[k-1],timeOfCapt[k]);
	//	I_Z2_Y3[k] = I_Z2_Y3[k-1] + ( SZ2val[k] * H_Z2_Y3_Zpart(a,timeOfCapt[k-1],timeOfCapt[k]) - ST2val[k] * H_Z2_Y3_Tpart(a,timeOfCapt[k-1],timeOfCapt[k]) );
	//	I_X2_Y3[k] = I_X2_Y3[k-1] + ( SX2val[k] * H_X2_Y3_Xpart(a,timeOfCapt[k-1],timeOfCapt[k]) - ST2val[k] * H_X2_Y3_Tpart(a,timeOfCapt[k-1],timeOfCapt[k]) );
		
	//	I_Y2_Y3[k] = I_Y2_Y3[k-1] + ampV1/t2 * ( ( sY2v1[k] + tU1U2/t1*SV1val[k] ) * H_V2_Y3(a,timeOfCapt[k-1],timeOfCapt[k]) - tU1U2/t1*SV1val[k] * H_U1_U3(a,timeOfCapt[k-1],timeOfCapt[k]) );	
	//	SY3val[k]+= I_Y2_Y3[k];
		
	//	SY3val[k]+= ampV1 * tU1U2/t1 * ( tU2U3/t2 * (aU3-aU2) * ( sigmaII(1,aU1,aU3,k) + (aU2-aU1)*sigmaIII(1,aU1,aU2,aU3,k) ) - tU1U3/t2 * (aU3-aU1) * sigmaII(1,aU1,aU3,k) );
	//	SY3val[k]+= ampW1 * tU1U2/t1 * ( tU2U3/t2 * (aU3-aU2) * ( sigmaII(1,aU1,aU3,k) + (aU2-aU1)*aT1*sigmaIV(1,aT1,aU1,aU2,aU3,k) ) - tU1U3/t2 * (aU3-aU1) * aT1*sigmaIII(1,aT1,aU1,aU3,k) );
		
	//	SY3val[k] = tU2U3/t2 * (aU3-aU2) * ( ampV2*sigmaII(1,aU2,aU3,k) + ampW2*aT2*sigmaIII(a[rho],aT2,aU2,aU3,k) + ampZ2*(sigmaII(a[rho],aT2,aU3,k)+(aU2-aT2)*sigmaIII(a[rho],aT2,aU2,aU3,k)) )
	//		- tT2U3/t2 * (aU3-aT2) * ampZ2 * sigmaII(a[rho],aT2,aU3,k)
	//		+ ampV1*tU1U2/t1 * ( tU2U3/t2 * ( sigmaII(1,aU1,aU3,k) + (aU2-aU1)*sigmaIII(1,aU1,aU2,aU3,k) ) - tU1U3/t2 * sigmaII(1,aU1,aU3,k) );
	//		//+ tU1U2/t1 * ( (aU3-aU2)*tU2U3/t2 - (aU3-aU1)*tU1U3/t2 ) * ampV1 * sigmaII(1,aU1,aU3,k)
	//		//+ tU1U2/t1 * aU2 * (aU2-aU1) * ampV1 * sigmaIII(1,aU1,aU2,aU3,k);
	}
	
//	// I[k] is contribution from k *previous* teeth, I[0] = 0
//	for (k=1; k<nCapMax; k++) { // k = 1, 2, 3 ... = tooth number
//	// Feeding V --> Y ////////////////////////////////////////////////////////
//		//I_V1_Y2[k] = I_V1_Y2[k-1] + SV1val[k] * H_V1_Y2(a,timeOfCapt[k-1],timeOfCapt[k]);
//		I_V2_Y3[k] = I_V2_Y3[k-1] + SV2val[k] * H_V2_Y3(a,timeOfCapt[k-1],timeOfCapt[k]);
//	// Feeding W --> Y ////////////////////////////////////////////////////////
//		//I_W1_Y2[k] = I_W1_Y2[k-1] + SW1val[k] * H_W1_Y2(a,timeOfCapt[k-1],timeOfCapt[k]);
//		I_W2_Y3[k] = I_W2_Y3[k-1] + SW2val[k] * H_W2_Y3(a,timeOfCapt[k-1],timeOfCapt[k]);
//	// Feeding Z --> Y ////////////////////////////////////////////////////////
//		//I_Z1_Y2[k] = I_Z1_Y2[k-1] + ( SZ1val[k] * H_Z1_Y2_Zpart(a,timeOfCapt[k-1],timeOfCapt[k]) - ST1val[k] * H_Z1_Y2_Tpart(a,timeOfCapt[k-1],timeOfCapt[k]) );
//		I_Z2_Y3[k] = I_Z2_Y3[k-1] + ( SZ2val[k] * H_Z2_Y3_Zpart(a,timeOfCapt[k-1],timeOfCapt[k]) - ST2val[k] * H_Z2_Y3_Tpart(a,timeOfCapt[k-1],timeOfCapt[k]) );
//		//I_Z2_Y3[k] = I_Z2_Y3[k-1] + ( SZ2val[k] * H_Z2_Y3_Zpart(a,timeOfCapt[k-1],timeOfCapt[k]) + ST2val[k] * H_Z2_Y3_Tpart(a,timeOfCapt[k-1],timeOfCapt[k]) );
//	// Feeding X --> Y ////////////////////////////////////////////////////////
//		//I_X2_Y3[k] = I_X2_Y3[k-1] + ( SX2val[k] * H_X2_Y3_Xpart(a,timeOfCapt[k-1],timeOfCapt[k]) - ST2val[k] * H_X2_Y3_Tpart(a,timeOfCapt[k-1],timeOfCapt[k]) );
//		I_X2_Y3[k] = I_X2_Y3[k-1] + ( SX2val[k] * H_X2_Y3_Xpart(a,timeOfCapt[k-1],timeOfCapt[k]) - ST2val[k] * H_X2_Y3_Tpart(a,timeOfCapt[k-1],timeOfCapt[k]) );
//	// Feeding Y --> Y ////////////////////////////////////////////////////////
//		I_Y2_Y3[k] = I_Y2_Y3[k-1] + 0.0;//( SV2val[k] * H_Y2_Y3_Vpart(a,timeOfCapt[k-1],timeOfCapt[k]) - ST2val[k] * H_X2_Y3_Tpart(a,timeOfCapt[k-1],timeOfCapt[k]) );
//		printf("k=%d, SV=%f, SW=%f, SZ=%f, IV=%f, IW=%f, IZ=%f\n", k, SV2val[k], SW2val[k], SZ2val[k], I_V2_Y3[k], I_W2_Y3[k], I_Z2_Y3[k]);
//	}
	
//	printf("Y3[tB+1tA,par,tB+0tA,0]=%f\n",Y3InitialValue(tBac+tCap,a,tBac,0.0));
//	printf("Y3[tB+2tA,par,tB+1tA,0]=%f\n",Y3InitialValue(tBac+2*tCap,a,tBac+1*tCap,0.0));
///////////////////////////////////////////////////////////////////////////////////////////////
	
// Initial values of populations
	V10 = Vcap(1,a,tCyc) / (1-eU1tCyc);
	V20 = Vcap(2,a,tCyc) / (1-eU2tCyc);
	V30 = Vcap(3,a,tCyc) / (1-eU3tCyc);
	//////////////////////////////////////////
	W10 = Wcap(1,a,tCyc) / (1-eU1tCyc);
	W20 = Wcap(2,a,tCyc) / (1-eU2tCyc);
	W30 = Wcap(3,a,tCyc) / (1-eU3tCyc);
	//////////////////////////////////////////
	Z10 = Zcap(1,a,tCyc) / (1-eU1tCyc);
	Z20 = Zcap(2,a,tCyc) / (1-eU2tCyc);
	Z30 = Zcap(3,a,tCyc) / (1-eU3tCyc);
	//////////////////////////////////////////
	X20 = Xcap(2,a,tCyc) / (1-eU2tCyc);
	X30 = Xcap(3,a,tCyc) / (1-eU3tCyc);
	//////////////////////////////////////////
	U10 = ( V10 + W10 + Z10 );
	Y20 = ( Ycap(2,a,tCyc) + U10 * tU1/t1 * tU2/(tU2-tU1) * ( eU2tCyc - eU1tCyc ) ) / ( 1 - eU2tCyc );
	//////////////////////////////////////////
	U20 = ( V20 + W20 + Z20 + X20 + Y20 );
	Y30 = ( Ycap(3,a,tCyc)
		+ U20 * tU2/t2 * tU3/(tU3-tU2) * ( eU3tCyc - eU2tCyc )
		+ U10 * tU1/t1 * tU2/t2 * tU3/ThetaU * ( tU1 * (tU3-tU2) * eU1tCyc - tU2 * (tU3-tU1) * eU2tCyc + tU3 * (tU2-tU1) * eU3tCyc ) ) / ( 1 - eU3tCyc );
	//U30 = ( V30 + W30 + Z30 + X30 + Y30 );
	printf("Parameter-dependent values computed.\n");
	//printf("ST1_1cap=%f, ST2_1cap=%f, SW11_1cap=%f, SW22_1cap=%f, SZ11_1cap=%f, SZ12_1cap=%f, SZ22_1cap=%f\n", ST1_1cap, ST2_1cap, SW11_1cap, SW22_1cap, SZ11_1cap, SZ12_1cap, SZ22_1cap);
}

Double_t BFitNamespace::sigmaI (Double_t r, Double_t a, Int_t n) {
	using namespace TMath;
	extern Double_t tCap;
	return (1-Power(r*a,n))/(1-r*a);
}
Double_t BFitNamespace::sigmaII (Double_t r, Double_t a1, Double_t a2, Int_t n) {
	using namespace TMath;
	extern Double_t iota, tCap;
//	static Double_t f1;
//	f1	= r*a1;
	return 1/(1-r*a1) * ( (1-Power(a2,n-1))/(1-a2) - (r*a1*Power(a2,n-1)-Power(r*a1,n)+iota)/(a2-r*a1+iota) );
}
Double_t BFitNamespace::sigmaIII (Double_t r, Double_t aT1, Double_t aU1, Double_t aU2, Int_t n) {
	using namespace TMath;
	extern Double_t iota, tCap;
//	static Double_t f1, f2, f3;
//	f1	= r*bT1;
//	f2	= bU1/bU2;
//	f3	= r*bT1/bU2;
//	return Power(bU2,n-1)/(1-f1) * ( 1/(1-bU1) * ( (Power(bU2,1-n)-1)/(1-bU2) - 1/bU1 * (f2-Power(f2,n))/(1-f2) ) - (1+iota)/(bU1-f1+iota) * ( f1/bU1 * (f2-Power(f2,n))/(1-f2) - (f3-Power(f3,n))/(1-f3) ) );
	return 1/(1-r*aT1) * ( 1/(1-aU1) * ( (1-Power(aU2,n-1))/(1-aU2) - (Power(aU2,n-1)-Power(aU1,n-1))/(aU2-aU1) ) - (r*aT1+iota)/(aU1-r*aT1+iota) * ( (Power(aU2,n-1)-Power(aU1,n-1))/(aU2-aU1) - (Power(aU2,n-1)-Power(r*aT1,n-1))/(aU2-r*aT1) ) );
}
Double_t BFitNamespace::sigmaIV (Double_t r, Double_t aT1, Double_t aU1, Double_t aU2, Double_t aU3, Int_t n) {
	using namespace TMath;
	extern Double_t iota, tCap;
	extern Int_t nCapMax;
//	static Double_t f1, f2, f3, f;
//	f1	= r*bT1;
//	f2	= bU1/bU2;
//	f3	= r*bT1/bU2;
//	printf("aT1=%f, aU1=%f, aU2=%f, aU3=%f, f1=%f, f2=%f, f3=%f\n", bT1, bU1, bU2, bU3, f1, f2, f3);
//	f = 0.0;
//	f += 1/(1-bU1) * ( 1/(1-bU2) * ( bU2 * (Power(bU2*bU3,1-n)-1)/(1-bU2*bU3) - (Power(bU3,1-n)-1)/(1-bU3) ) - 1/bU1/(1-bU1/bU2) * ( bU1/bU2 * (Power(bU3,1-n)-1)/(1-bU3) - (bU1/bU2/bU3-Power(bU1/bU2/bU3,n))/(1-bU1/bU2/bU3) ) );
//	f -= (1+iota)/(bU1-r*bT1+iota) * ( r*bT1/bU1/(1-bU1/bU2) * ( (Power(bU3,1-n)-1)/(1-bU3) - (bU1/bU2/bU3-Power(bU1/bU2/bU3,n))/(1-bU1/bU2/bU3) ) - 1/(1-r*bT1/bU2) * ( r*bT1/bU2 * (Power(bU3,1-n)-1)/(1-bU3) - (r*bT1/bU2/bU3-Power(r*bT1/bU2/bU3,n))/(1-r*bT1/bU2/bU3) ) );
//	f *= Power(bU2*bU3,n-1)/(1-r*bT1);

//	f = 0.0;
//	f += 1/(1-aU1) * ( 1/(1-aU2) * ( (1-Power(aU3,n-1))/(1-aU3) - (Power(aU3,n-1)-Power(aU2,n-1))/(aU3-aU2) ) - 1/(aU2-aU1) * ( (Power(aU3,n-1)-Power(aU2,n-1))/(aU3-aU2) - (Power(aU3,n-1)-Power(aU1,n-1))/(aU3-aU1) ) );
//	f -= (r*aT1+iota)/(aU1-r*aT1+iota) * ( 1/(aU2-aU1) * ( (Power(aU3,n-1)-Power(aU2,n-1))/(aU3-aU2) - (Power(aU3,n-1)-Power(aU1,n-1))/(aU3-aU1) ) ) - 1/(aU2-r*aT1) * ( (Power(aU3,n-1)-Power(aU2,n-1))/(aU3-aU2) - (Power(aU3,n-1)-Power(r*aT1,n-1))/(aU3-r*aT1) )
//	f *= 1/(1-r*aT1);
	
//	Double_t f = 0.0;
//	for (Int_t k=1; k<n; k++ ) f += sigmaIII(r,aT1,aU1,aU2,k) * Power(aU3,n-1-k);
//	return f;
	
	return 1/(1-r*aT1) * ( 1/(1-aU1) * ( 1/(1-aU2) * ( (1-Power(aU3,n-1))/(1-aU3) - (Power(aU3,n-1)-Power(aU2,n-1))/(aU3-aU2) ) - 1/(aU2-aU1) * ( (Power(aU3,n-1)-Power(aU2,n-1))/(aU3-aU2) - (Power(aU3,n-1)-Power(aU1,n-1))/(aU3-aU1) ) ) - (r*aT1+iota)/(aU1-r*aT1+iota) * ( ( 1/(aU2-aU1) * ( (Power(aU3,n-1)-Power(aU2,n-1))/(aU3-aU2) - (Power(aU3,n-1)-Power(aU1,n-1))/(aU3-aU1) ) ) - 1/(aU2-r*aT1) * ( (Power(aU3,n-1)-Power(aU2,n-1))/(aU3-aU2) - (Power(aU3,n-1)-Power(r*aT1,n-1))/(aU3-r*aT1) ) ) );
}

Double_t BFitNamespace::Ycap (Int_t i, Double_t *a, Double_t tvar) {
	using namespace BFitNamespace;
	using namespace TMath;
	extern Double_t tCap, tBac, t1, t2, tT1, tT2, tU1, tU2, tU3, aT1, aU1, aU2, aU3, tU1U2, tT1U2, tU2U3, tT2U3, tU1U3;
	extern Double_t ampV1, ampW1, ampZ1, ampV2, ampW2, ampZ2, ampX2, ampY2;
	extern Double_t *timeOfCapt, *ST1val, *SV1val, *SW1val, *SZ1val, *ST2val, *SV2val, *SW2val, *SZ2val, *SX2val, *SY2val, *SY3val, *sY2V, *sY2W, *sY2Z, *sY3YW;
	extern Double_t *I_V1_Y2, *I_W1_Y2, *I_Z1_Y2;
	extern Double_t *I_V2_Y3, *I_W2_Y3, *I_Z2_Y3, *I_X2_Y3, *I_Y2_Y3;
//	extern Double_t ampW2, ampY3fromW2, Gamma_U2_U3, *Y3InitialValues;
	static Double_t tk, V, W, Z, X, Y, f;
	static Int_t n, k;
	V = W = Z = X = Y = f = 0.0;
	n = Ceil((tvar-tBac)/tCap);
	//if (tvar==tBac) n=1;
	tk = tvar-tBac-(n-1)*tCap;
	if (i==2) {
	//	V = ampV1 * ( I_V1_Y2[n-1] + SV1val[n] * H_V1_Y2(a,timeOfCapt[n-1],tvar) );
	//	W = ampW1 * ( I_W1_Y2[n-1] + SW1val[n] * H_W1_Y2(a,timeOfCapt[n-1],tvar) );
	//	Z = ampZ1 * ( I_Z1_Y2[n-1] + SZ1val[n] * H_Z1_Y2_Zpart(a,timeOfCapt[n-1],tvar) - ST1val[n] * H_Z1_Y2_Tpart(a,timeOfCapt[n-1],tvar) );
	//	f = (V + W + Z) * Exp(-tvar/tU2) / t1;
		f = SY2val[n] * Exp(-tk/tU2)
			+ tU1U2/t1 * ( Exp(-tk/tU2) - Exp(-tk/tU1) ) * ( ampV1*SV1val[n] + ampW1*SW1val[n] + ampZ1*SZ1val[n] )
			- tT1U2/t1 * ( Exp(-tk/tU2) - Exp(-tk/tT1) ) * ampZ1 * ST1val[n];
//		printf("tk=%f, B1=%f, ampV1=%f, ampW1=%f, ampZ1=%f, SV1=%f, SW1=%f, SZ1=%f, SY2=%f, eU2=%f, eU1=%f, y2=%f\n",tk,B1,ampV1,ampW1,ampZ1,SV1val[n],SW1val[n],SZ1val[n],SZ1val[n],Exp(-tk/tU2),Exp(-tk/tU1),f);
	}
	if (i==3) {
	//	V  = ampV2 * ( I_V2_Y3[n-1] + SV2val[n] * H_V2_Y3(a,timeOfCapt[n-1],tvar) );
	//	W  = ampW2 * ( I_W2_Y3[n-1] + SW2val[n] * H_W2_Y3(a,timeOfCapt[n-1],tvar) );
	//	Z  = ampZ2 * ( I_Z2_Y3[n-1] + SZ2val[n] * H_Z2_Y3_Zpart(a,timeOfCapt[n-1],tvar) - ST2val[n] * H_Z2_Y3_Tpart(a,timeOfCapt[n-1],tvar) );
	//	X  = ampX2 * ( I_X2_Y3[n-1] + SX2val[n] * H_X2_Y3_Xpart(a,timeOfCapt[n-1],tvar) - ST1val[n] * H_X2_Y3_Tpart(a,timeOfCapt[n-1],tvar) );
	//	Y += ampV1 * ( I_V1_Y3[n-1] + SV1val[n] * H_X2_Y3_Xpart(a,timeOfCapt[n-1],tvar);
////		X = ampX2 * ( I_X2_Y3[n-1] + SX2val[n] * H_X2_Y3(a,timeOfCapt[n-1],tvar) );
////		Y = ampX2 * ( I_Y2_Y3[n-1] + SY2val[n] * H_Y2_Y3(a,timeOfCapt[n-1],tvar) );
	//	f = (V + W + Z + X + Y) * Exp(-tvar/tU3) / t2;
		
		
		f = SY3val[n] * Exp(-tk/tU3)
			+ tU2U3/t2 * ( Exp(-tk/tU3) - Exp(-tk/tU2) ) * ( ampV2*SV2val[n] + ampW2*SW2val[n] + ampZ2*SZ2val[n] + ampX2*SX2val[n] )
			- tT2U3/t2 * ( Exp(-tk/tU3) - Exp(-tk/tT2) ) * (ampZ2+ampX2) * ST2val[n]
			+ ampV1 * tU1U2/t1 * ( tU2U3/t2 * ( Exp(-tk/tU3) - Exp(-tk/tU2) ) * ( SV1val[n] + sY2v1[n]*t1/tU1U2 ) - tU1U3/t2 * ( Exp(-tk/tU3) - Exp(-tk/tU1) ) * SV1val[n] )
			+ (ampW1/t1)*tU1*tU2/(tU2-tU1) * ( 1/t2*tU2*tU3/(tU3-tU2)*(SW1val[n]+(aU2-aU1)*aT1*sigmaIII(a[rho],aT1,aU1,aU2,n))*(Exp(-tk/tU3)-Exp(-tk/tU2)) - 1/t2*tU1*tU3/(tU3-tU1)*SW1val[n]*(Exp(-tk/tU3)-Exp(-tk/tU2)) );
			
		//	+ ampW1 * tU1U2/t1 * ( Exp(-tk/tU3) - Exp(-tk/tU2) ) * tU2U3/t2 * sY2w1[n]/(tU1U2/t1);//(aU2-aU1) * sigmaIII(a[rho],aT1,aU1,aU2,n)
		//	+ ampW1 * tU1U2/t1 * ( Exp(-tk/tU3) - Exp(-tk/tU2) ) * tU2U3/t2 * SW1val[n];//sigmaII(a[rho],aT1,aU1,n)
		//	- ampW1 * tU1U2/t1 * ( Exp(-tk/tU3) - Exp(-tk/tU1) ) * tU1U3/t2 * SW1val[n];//sigmaII(a[rho],aT1,aU1,n);
		
		////	+ ampW1 * tU1U2/t1 * ( tU2U3/t2 * ( Exp(-tk/tU3) - Exp(-tk/tU2) ) * ( SW1val[n] + sY2w1[n]*t1/tU1U2 ) - tU1U3/t2 * ( Exp(-tk/tU3) - Exp(-tk/tU1) ) * SW1val[n] );
		//	+ ampW1 * tU2U3/t2 * ( sY2w1[n] + tU1U2/t1 * SW1val[n] ) * ( Exp(-tk/tU3) - Exp(-tk/tU2) )
		//	- ampW1 * tU1U3/t2 *             tU1U2/t1 * SW1val[n]   * ( Exp(-tk/tU3) - Exp(-tk/tU1) );
		//	+ ampV1 * tU1U2/t1 * ( tU2U3/t2 * ( Exp(-tk/tU3) - Exp(-tk/tU2) ) * ( sigmaI(1,aU1,n) + (aU2-aU1)*sigmaII(1,aU1,aU2,n) ) - tU1U3/t2 * (Exp(-tk/tU3)-Exp(-tk/tU1)) * SV1val[n](1,aU1,aU3,n) );
		//	+ ampV1 * tU1U2/t1 * ( tU2U3/t2 * ( Exp(-tk/tU3) - Exp(-tk/tU2) ) * ( sigmaI(1,aU1,n) + (aU2-aU1)*sigmaII(1,aU1,aU2,n) ) - tU1U3/t2 * ( Exp(-tk/tU3) - Exp(-tk/tU1) ) * sigmaI(1,aU1,n) ); 
			//+ ampV1*tU1U2/t1/t2 * ( tU2U3 * ( ( sigmaI(1,aU1,k) + (aU2-aU1)*sigmaII(1,aU1,aU2,k) ) * ( Exp(-tk/tU3) - Exp(-tk/tU2) ) - tU1U3 * sigmaII(1,aU1,aU3,k) );
			//+ tU2U3/t2 * (ampV1*tU1U2/t1*(aU2-aU1)*sigmaIII(1,aU1,aU2,aU3,n)) * ( Exp(-tk/tU3) - Exp(-tk/tU2) )
			//+ ampV1*tU1U2/t1 * (sigmaII(1,aU1,aU3,n)) * ( tU2U3/t2 * ( Exp(-tk/tU3) - Exp(-tk/tU2) ) - tU1U3/t2 * ( Exp(-tk/tU3) - Exp(-tk/tU1) ) );
			
	//	Double_t aa = tU2U3/t2;
	//	Double_t bb = tU2U3/t2 * tU1U2/t1;
	//	Double_t cc = tU1U3/t2 * tU1U2/t1;
	//	Double_t sY3w1 = tU1U2/t1 * (aU2-aU1) * aT1 * sigmaIV(a[rho],aT1,aU1,aU2,aU3,n);
	//	sY3w1[k]  = aa * (aU3-aU2) * aT1 * sY3w1;
	//	sY3w1[k] += bb * (aU3-aU2) * aT1 * sigmaIII(a[rho],aT1,aU1,aU3,n);
	//	sY3w1[k] -= cc * (aU3-aU1) * aT1 * sigmaIII(a[rho],aT1,aU1,aU3,n);
	
	//	f = 0.0;
	//	f = SY3val[n] * Exp(-tk/tU3) + (ampW1/t1)*tU1*tU2/(tU2-tU1) * ( 1/t2*tU2*tU3/(tU3-tU2)*(SW1val[n]+(aU2-aU1)*aT1*sigmaIII(a[rho],aT1,aU1,aU2,n))*(Exp(-tk/tU3)-Exp(-tk/tU2)) - 1/t2*tU1*tU3/(tU3-tU1)*SW1val[n]*(Exp(-tk/tU3)-Exp(-tk/tU2)) );
	}
	
	return f;
}

//////////////////////////////////////////////////////////////
// Feeding of Y2 -- integrals
//////////////////////////////////////////////////////////////
Double_t BFitNamespace::H_V1_Y2 (Double_t *a, Double_t s1, Double_t s2) {
	using namespace TMath;
	extern Double_t tBac, tU2, Gamma_U1_U2;
	return (Exp(tBac/tU2)/Gamma_U1_U2)*(Exp(-Gamma_U1_U2*(s1-tBac))-Exp(-Gamma_U1_U2*(s2-tBac)));
}
Double_t BFitNamespace::H_W1_Y2 (Double_t *a, Double_t s1, Double_t s2) {
	using namespace TMath;
	extern Double_t tBac, tU2, Gamma_U1_U2;
	return (Exp(tBac/tU2)/Gamma_U1_U2)*(Exp(-Gamma_U1_U2*(s1-tBac))-Exp(-Gamma_U1_U2*(s2-tBac)));
}
Double_t BFitNamespace::H_Z1_Y2_Zpart (Double_t *a, Double_t s1, Double_t s2) {
	using namespace TMath;
	extern Double_t tBac, tU2, Gamma_U1_U2;
	return (Exp(tBac/tU2)/Gamma_U1_U2)*(Exp(-Gamma_U1_U2*(s1-tBac))-Exp(-Gamma_U1_U2*(s2-tBac)));
}
Double_t BFitNamespace::H_Z1_Y2_Tpart (Double_t *a, Double_t s1, Double_t s2) {
	using namespace TMath;
	extern Double_t tBac, tU2, Gamma_T1_U2;
	return (Exp(tBac/tU2)/Gamma_T1_U2)*(Exp(-Gamma_T1_U2*(s1-tBac))-Exp(-Gamma_T1_U2*(s2-tBac)));
}
//////////////////////////////////////////////////////////////
// Feeding of Y3 -- integrals
//////////////////////////////////////////////////////////////
Double_t BFitNamespace::H_V2_Y3 (Double_t *a, Double_t s1, Double_t s2) {
	using namespace TMath;
	extern Double_t tBac, tU3, Gamma_U2_U3;
	return (Exp(tBac/tU3)/Gamma_U2_U3)*(Exp(-Gamma_U2_U3*(s1-tBac))-Exp(-Gamma_U2_U3*(s2-tBac)));
}
Double_t BFitNamespace::H_W2_Y3 (Double_t *a, Double_t s1, Double_t s2) {
	using namespace TMath;
	extern Double_t tBac, tU3, Gamma_U2_U3;
	return (Exp(tBac/tU3)/Gamma_U2_U3)*(Exp(-Gamma_U2_U3*(s1-tBac))-Exp(-Gamma_U2_U3*(s2-tBac)));
}
Double_t BFitNamespace::H_Z2_Y3_Zpart (Double_t *a, Double_t s1, Double_t s2) {
	using namespace TMath;
	extern Double_t tBac, tU3, Gamma_U2_U3;
	return (Exp(tBac/tU3)/Gamma_U2_U3)*(Exp(-Gamma_U2_U3*(s1-tBac))-Exp(-Gamma_U2_U3*(s2-tBac)));
}
Double_t BFitNamespace::H_Z2_Y3_Tpart (Double_t *a, Double_t s1, Double_t s2) {
	using namespace TMath;
	extern Double_t tBac, tU3, Gamma_T2_U3;
	return (Exp(tBac/tU3)/Gamma_T2_U3)*(Exp(-Gamma_T2_U3*(s1-tBac))-Exp(-Gamma_T2_U3*(s2-tBac)));
}
Double_t BFitNamespace::H_X2_Y3_Xpart (Double_t *a, Double_t s1, Double_t s2) {
	using namespace TMath;
	extern Double_t tBac, tU3, Gamma_U2_U3;
	return (Exp(tBac/tU3)/Gamma_U2_U3)*(Exp(-Gamma_U2_U3*(s1-tBac))-Exp(-Gamma_U2_U3*(s2-tBac)));
}
Double_t BFitNamespace::H_X2_Y3_Tpart (Double_t *a, Double_t s1, Double_t s2) {
	using namespace TMath;
	extern Double_t tBac, tU3, Gamma_T2_U3;
	return (Exp(tBac/tU3)/Gamma_T2_U3)*(Exp(-Gamma_T2_U3*(s1-tBac))-Exp(-Gamma_T2_U3*(s2-tBac)));
}
Double_t BFitNamespace::H_U1_U3 (Double_t *a, Double_t s1, Double_t s2) {
	using namespace TMath;
	extern Double_t tBac, tU3, tU1U3;
	return (tU1U3*Exp(tBac/tU3))*(Exp(-(s1-tBac)/tU1U3)-Exp(-(s2-tBac)/tU1U3));
}
//Double_t BFitNamespace::H_Y2_Y3_Tpart (Double_t *a, Double_t s1, Double_t s2) {
//	using namespace TMath;
//	extern Double_t tBac, tU3, Gamma_T2_U3;
//	return -(Exp(tBac/tU3)/Gamma_T2_U3)*(Exp(-Gamma_T2_U3*(s1-tBac))-Exp(-Gamma_T2_U3*(s2-tBac)));
//}
//Double_t BFitNamespace::H_Y2_Y3_Upart (Double_t *a, Double_t s1, Double_t s2) {
//	using namespace TMath;
//	extern Double_t tBac, tU3, Gamma_U2_U3;
//	return (Exp(tBac/tU3)/Gamma_U2_U3)*(Exp(-Gamma_U2_U3*(s1-tBac))-Exp(-Gamma_U2_U3*(s2-tBac)));
//}
//Double_t BFitNamespace::H_Z2_Y3 (Double_t *a, Double_t s1, Double_t s2) {
//	using namespace TMath;
//	extern Double_t tBac, tU3, Gamma_U2_U3;
//	return 0.0;
//}

/*
void BFitNamespace::ComputeTimeDependentVars (Double_t *t, Double_t *a) {
	using namespace TMath;
// Global variables that are constant throughout the fit
	extern Double_t tCap, tBac;//, t1, t2, t3;
// Global variables that depend only on the parameters
	extern Double_t tT1, tT2, tT3, tU1, tU2, tU3;
// Global variables that depend on t
	extern Int_t nCap;
	extern Double_t tvar;
	extern Double_t eU10, eU20, eU30;
	extern Double_t eT1nCap, eT2nCap, eT3nCap, eU1nCap, eU2nCap, eU3nCap;
// Update shared t-dependent variables
	tvar	= t[0];
	nCap	= Ceil((tvar-tBac)/tCap);
	eU10	= Exp(-tvar/tU1);
	eU20	= Exp(-tvar/tU2);
	eU30	= Exp(-tvar/tU3);
	eT1nCap	= Exp(-(tvar-tBac-(nCap-1)*tCap)/tT1);
	eT2nCap	= Exp(-(tvar-tBac-(nCap-1)*tCap)/tT2);
	eT3nCap	= Exp(-(tvar-tBac-(nCap-1)*tCap)/tT3);
	eU1nCap	= Exp(-(tvar-tBac-(nCap-1)*tCap)/tU1);
	eU2nCap	= Exp(-(tvar-tBac-(nCap-1)*tCap)/tU2);
	eU3nCap	= Exp(-(tvar-tBac-(nCap-1)*tCap)/tU3);
}
void BFitNamespace::ComputePopulations (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	extern Double_t T1val, T2val, T3val, U1val, U2val, U3val, V1val, V2val, V3val, W1val, W2val, W3val, Z1val, Z2val, Z3val, X2val, X3val, Y2val, Y3val;
	Double_t tvar;
// Evaluate ion populations
	tvar	= t[0];
	T1val	= Ttot(1,a,tvar);
	T2val	= Ttot(2,a,tvar);
	T3val	= Ttot(3,a,tvar);
	V1val	= Vtot(1,a,tvar);
	V2val	= Vtot(2,a,tvar);
	V3val	= Vtot(3,a,tvar);
	W1val	= Wtot(1,a,tvar);
	W2val	= Wtot(2,a,tvar);
	W3val	= Wtot(3,a,tvar);
	Z1val	= Ztot(1,a,tvar);
	Z2val	= Ztot(2,a,tvar);
	Z3val	= Ztot(3,a,tvar);
	X2val	= Xtot(2,a,tvar);
	X3val	= Xtot(3,a,tvar);
	Y2val	= Ytot(2,a,tvar);
	Y3val	= Ytot(3,a,tvar);
}
*/
//////////////////////////////////////////////////////////////////////////
// "y" functions
// Functions to plot: (obs. decay rate)x(bin dt) = counts by bin = y
//////////////////////////////////////////////////////////////////////////
Double_t BFitNamespace::yAll(Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
// Global variables that are constant throughout the fit
	extern char parNames[30][5];
	extern BFitCase_t stBFitCases[FILE_ROWS_BFit];
	extern Int_t iBFitCaseIndex, nPars;
	extern Double_t iota, t1, t2, t3;
// Global variables that depend only on the parameters
	extern Int_t nParChanges; // counts # of times pars have changed
	extern Double_t *lastPar; // holds most recent paramter values for comparison
// Global variables that depend on t
	extern Double_t T1val, T2val, T3val, U1val, U2val, U3val, V1val, V2val, V3val, W1val, W2val, W3val, Z1val, Z2val, Z3val, X2val, X3val, Y2val, Y3val;
// Local variables
	static Double_t f;
	static Int_t index; // index of parameter array
	
// When parameters change:
	if (!CompareParArrays(a,lastPar,sizeof(Double_t),iota)) {
		//printf("\n\nArrays not equal.\n\n");
		ComputeParameterDependentVars(a);
		memcpy(lastPar,a,nPars*sizeof(Double_t));
		nParChanges++;
		
		printf("New params (%d): ",nParChanges);
	// Print current paramters, for parameters that may have changed
		for (index = 0; index < nPars; index++) {
			if (stBFitCases[iBFitCaseIndex].pbToggle[index]) printf("%s=%.4e ",parNames[index],a[index]);
		}
		printf("\n");
	}
	
// Always:
//	ComputeTimeDependentVars(t,a);
//	ComputePopulations(t,a);
	
	f = 0.0;
	f = yDC(t,a) + yT1(t,a) + yT2(t,a) + yT3(t,a) + a[epsU]*(yU1(t,a) + yU2(t,a) + yU3(t,a));
	return f;
}
/////////////////////////////////////////////////////////////////////
// y functions with the right signature for use in a TF1
// Must run ComputerParameterDependentVars() before calling these!
/////////////////////////////////////////////////////////////////////
Double_t BFitNamespace::yDC (Double_t *t, Double_t *a) { return a[nCyc]*a[dt]*a[DC]; }
/////////////////////////////////////////////////////////////////////
Double_t BFitNamespace::yT1 (Double_t *t, Double_t *a) {
//	BFitNamespace::ComputeTimeDependentVars(t,a);
	return yT(1,a,t[0]);
}
Double_t BFitNamespace::yT2 (Double_t *t, Double_t *a) {
//	BFitNamespace::ComputeTimeDependentVars(t,a);
	return yT(2,a,t[0]);
}
Double_t BFitNamespace::yT3 (Double_t *t, Double_t *a) {
//	BFitNamespace::ComputeTimeDependentVars(t,a);
	return yT(3,a,t[0]);
}
/////////////////////////////////////////////////////////////////////
Double_t BFitNamespace::yU1 (Double_t *t, Double_t *a) {
//	BFitNamespace::ComputeTimeDependentVars(t,a);
	return yU(1,a,t[0]);
}
Double_t BFitNamespace::yU2 (Double_t *t, Double_t *a) {
//	BFitNamespace::ComputeTimeDependentVars(t,a);
	return yU(2,a,t[0]);
}
Double_t BFitNamespace::yU3 (Double_t *t, Double_t *a) {
//	BFitNamespace::ComputeTimeDependentVars(t,a);
	return yU(3,a,t[0]);
}
/////////////////////////////////////////////////////////////////////
Double_t BFitNamespace::yV1 (Double_t *t, Double_t *a) {
//	BFitNamespace::ComputeTimeDependentVars(t,a);
	return yV(1,a,t[0]);
}
Double_t BFitNamespace::yV2 (Double_t *t, Double_t *a) {
//	BFitNamespace::ComputeTimeDependentVars(t,a);
	return yV(2,a,t[0]);
}
Double_t BFitNamespace::yV3 (Double_t *t, Double_t *a) {
//	BFitNamespace::ComputeTimeDependentVars(t,a);
	return yV(3,a,t[0]);
}
/////////////////////////////////////////////////////////////////////
Double_t BFitNamespace::yW1 (Double_t *t, Double_t *a) {
//	BFitNamespace::ComputeTimeDependentVars(t,a);
	return yW(1,a,t[0]);
}
Double_t BFitNamespace::yW2 (Double_t *t, Double_t *a) {
//	BFitNamespace::ComputeTimeDependentVars(t,a);
	return yW(2,a,t[0]);
}
Double_t BFitNamespace::yW3 (Double_t *t, Double_t *a) {
//	BFitNamespace::ComputeTimeDependentVars(t,a);
	return yW(3,a,t[0]);
}
/////////////////////////////////////////////////////////////////////
Double_t BFitNamespace::yZ1 (Double_t *t, Double_t *a) {
//	BFitNamespace::ComputeTimeDependentVars(t,a);
	return yZ(1,a,t[0]);
}
Double_t BFitNamespace::yZ2 (Double_t *t, Double_t *a) {
//	BFitNamespace::ComputeTimeDependentVars(t,a);
	return yZ(2,a,t[0]);
}
Double_t BFitNamespace::yZ3 (Double_t *t, Double_t *a) {
//	BFitNamespace::ComputeTimeDependentVars(t,a);
	return yZ(3,a,t[0]);
}
/////////////////////////////////////////////////////////////////////
Double_t BFitNamespace::yX2 (Double_t *t, Double_t *a) {
//	BFitNamespace::ComputeTimeDependentVars(t,a);
	return yX(2,a,t[0]);
}
Double_t BFitNamespace::yX3 (Double_t *t, Double_t *a) {
//	BFitNamespace::ComputeTimeDependentVars(t,a);
	return yX(3,a,t[0]);
}
/////////////////////////////////////////////////////////////////////
Double_t BFitNamespace::yY2 (Double_t *t, Double_t *a) {
//	BFitNamespace::ComputeTimeDependentVars(t,a);
	return yY(2,a,t[0]);
}
Double_t BFitNamespace::yY3 (Double_t *t, Double_t *a) {
//	BFitNamespace::ComputeTimeDependentVars(t,a);
	return yY(3,a,t[0]);
}
/*
/////////////////////////////////////////////////////////////////////
Double_t BFitNamespace::yU1 (Double_t *t, Double_t *a) { return yU(1,a,t[0]); }
Double_t BFitNamespace::yU2 (Double_t *t, Double_t *a) { return yU(2,a,t[0]); }
Double_t BFitNamespace::yU3 (Double_t *t, Double_t *a) { return yU(3,a,t[0]); }
/////////////////////////////////////////////////////////////////////
Double_t BFitNamespace::yV1 (Double_t *t, Double_t *a) { return yV(1,a,t[0]); }
Double_t BFitNamespace::yV2 (Double_t *t, Double_t *a) { return yV(2,a,t[0]); }
Double_t BFitNamespace::yV3 (Double_t *t, Double_t *a) { return yV(3,a,t[0]); }
/////////////////////////////////////////////////////////////////////
Double_t BFitNamespace::yW1 (Double_t *t, Double_t *a) { return yW(1,a,t[0]); }
Double_t BFitNamespace::yW2 (Double_t *t, Double_t *a) { return yW(2,a,t[0]); }
Double_t BFitNamespace::yW3 (Double_t *t, Double_t *a) { return yW(3,a,t[0]); }
/////////////////////////////////////////////////////////////////////
Double_t BFitNamespace::yZ1 (Double_t *t, Double_t *a) { return yZ(1,a,t[0]); }
Double_t BFitNamespace::yZ2 (Double_t *t, Double_t *a) { return yZ(2,a,t[0]); }
Double_t BFitNamespace::yZ3 (Double_t *t, Double_t *a) { return yZ(3,a,t[0]); }
/////////////////////////////////////////////////////////////////////
Double_t BFitNamespace::yX2 (Double_t *t, Double_t *a) { return yX(2,a,t[0]); }
Double_t BFitNamespace::yX3 (Double_t *t, Double_t *a) { return yX(3,a,t[0]); }
/////////////////////////////////////////////////////////////////////
Double_t BFitNamespace::yY2 (Double_t *t, Double_t *a) { return yY(2,a,t[0]); }
Double_t BFitNamespace::yY3 (Double_t *t, Double_t *a) { return yY(3,a,t[0]); }
*/
/////////////////////////////////////////////////////////////////////
// y functions -- turn pops into something that matches data
/////////////////////////////////////////////////////////////////////
Double_t BFitNamespace::yT (Int_t i, Double_t *a, Double_t tvar) {
	using namespace BFitNamespace;
	extern Double_t t1, t2, t3;
	static Double_t f;
	f = 0.0;
	if (i==1) f = a[nCyc]*a[dt]*a[epsT]*Ttot(1,a,tvar)/t1;
	if (i==2) f = a[nCyc]*a[dt]*a[epsT]*Ttot(2,a,tvar)/t2;
	if (i==3) f = a[nCyc]*a[dt]*a[epsT]*Ttot(3,a,tvar)/t3;
	return f;
}
Double_t BFitNamespace::yU (Int_t i, Double_t *a, Double_t tvar) {
	using namespace BFitNamespace;
	extern Double_t t1, t2, t3;
	static Double_t f;
	f = 0.0;
	if (i==1) f = a[nCyc] *a[dt] * a[epsU]* ( a[epsV]*Vtot(1,a,tvar) + a[epsW]*Wtot(1,a,tvar) + a[epsZ]*Ztot(1,a,tvar) ) / t1;
	if (i==2) f = a[nCyc] *a[dt] * a[epsU]* ( a[epsV]*Vtot(2,a,tvar) + a[epsW]*Wtot(2,a,tvar) + a[epsZ]*Ztot(2,a,tvar) + a[epsX]*Xtot(2,a,tvar) + a[epsY]*Ytot(2,a,tvar) ) / t2;
	if (i==3) f = a[nCyc] *a[dt] * a[epsU]* ( a[epsV]*Vtot(3,a,tvar) + a[epsW]*Wtot(3,a,tvar) + a[epsZ]*Ztot(3,a,tvar) + a[epsX]*Xtot(3,a,tvar) + a[epsY]*Ytot(3,a,tvar) ) / t3;
//	printf("yU: i=%d, par=%f, tvar=%f, f=%f\n",i,t3,tvar,Ytot(3,a,tvar));
	return f;
}
Double_t BFitNamespace::yV (Int_t i, Double_t *a, Double_t tvar) {
	using namespace BFitNamespace;
	extern Double_t t1, t2, t3;
	static Double_t f;
	f = 0.0;
	if (i==1) f = a[nCyc]*a[dt]*a[epsV]*Vtot(1,a,tvar)/t1;
	if (i==2) f = a[nCyc]*a[dt]*a[epsV]*Vtot(2,a,tvar)/t2;
	if (i==3) f = a[nCyc]*a[dt]*a[epsV]*Vtot(3,a,tvar)/t3;
	return f;
}
Double_t BFitNamespace::yW (Int_t i, Double_t *a, Double_t tvar) {
	using namespace BFitNamespace;
	extern Double_t t1, t2, t3;
	static Double_t f;
	f = 0.0;
	if (i==1) f = a[nCyc]*a[dt]*a[epsW]*Wtot(1,a,tvar)/t1;
	if (i==2) f = a[nCyc]*a[dt]*a[epsW]*Wtot(2,a,tvar)/t2;
	if (i==3) f = a[nCyc]*a[dt]*a[epsW]*Wtot(3,a,tvar)/t3;
	return f;
}
Double_t BFitNamespace::yZ (Int_t i, Double_t *a, Double_t tvar) {
	using namespace BFitNamespace;
	extern Double_t t1, t2, t3;
	static Double_t f;
	f = 0.0;
	if (i==1) f = a[nCyc]*a[dt]*a[epsZ]*Ztot(1,a,tvar)/t1;
	if (i==2) f = a[nCyc]*a[dt]*a[epsZ]*Ztot(2,a,tvar)/t2;
	if (i==3) f = a[nCyc]*a[dt]*a[epsZ]*Ztot(3,a,tvar)/t3;
	return f;
}
Double_t BFitNamespace::yX (Int_t i, Double_t *a, Double_t tvar) {
	using namespace BFitNamespace;
	extern Double_t t1, t2, t3;
	static Double_t f;
	f = 0.0;
	if (i==2) f = a[nCyc]*a[dt]*a[epsX]*Xtot(2,a,tvar)/t2;
	if (i==3) f = a[nCyc]*a[dt]*a[epsX]*Xtot(3,a,tvar)/t3;
	return f;
}
Double_t BFitNamespace::yY (Int_t i, Double_t *a, Double_t tvar) {
	using namespace BFitNamespace;
	extern Double_t t1, t2, t3;
	static Double_t f;
	f = 0.0;
	if (i==2) f = a[nCyc]*a[dt]*a[epsY]*Ytot(2,a,tvar)/t2;
	if (i==3) f = a[nCyc]*a[dt]*a[epsY]*Ytot(3,a,tvar)/t3;
	return f;
}

//////////////////////////////////////////////////////////////////////////
// "o" functions
// Offset functions to improve visualization: oT1 = yT1 + yDC
//////////////////////////////////////////////////////////////////////////
Double_t BFitNamespace::oT1 (Double_t *t, Double_t *a) { return BFitNamespace::yDC(t,a) + BFitNamespace::yT(1,a,t[0]); }
Double_t BFitNamespace::oT2 (Double_t *t, Double_t *a) { return BFitNamespace::yDC(t,a) + BFitNamespace::yT(2,a,t[0]); }
Double_t BFitNamespace::oT3 (Double_t *t, Double_t *a) { return BFitNamespace::yDC(t,a) + BFitNamespace::yT(3,a,t[0]); }
Double_t BFitNamespace::oU1 (Double_t *t, Double_t *a) { return BFitNamespace::yDC(t,a) + BFitNamespace::yU(1,a,t[0]); }
Double_t BFitNamespace::oU2 (Double_t *t, Double_t *a) { return BFitNamespace::yDC(t,a) + BFitNamespace::yU(2,a,t[0]); }
Double_t BFitNamespace::oU3 (Double_t *t, Double_t *a) { return BFitNamespace::yDC(t,a) + BFitNamespace::yU(3,a,t[0]); }

//////////////////////////////////////////////////////////////////////////
// "r" functions
// Instantaneous detection rate, not corrected for nCyc
// Used for calculating the desired integrals... apply nCyc to those
//////////////////////////////////////////////////////////////////////////
Double_t BFitNamespace::rDC (Double_t *t, Double_t *a) {
	return a[DC];
}
Double_t BFitNamespace::rT1 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	extern Double_t t1;
	return a[epsT]*Ttot(1,a,t[0])/t1;
}
Double_t BFitNamespace::rT2 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	extern Double_t t2;
	return a[epsT]*Ttot(2,a,t[0])/t2;
}
Double_t BFitNamespace::rT3 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	extern Double_t t3;
	return a[epsT]*Ttot(3,a,t[0])/t3;
}
Double_t BFitNamespace::rU1 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	extern Double_t t1;
	return a[epsU]*(a[epsV]*Vtot(1,a,t[0]) + a[epsW]*Wtot(1,a,t[0]) + a[epsZ]*Ztot(1,a,t[0]))/t1;
}
Double_t BFitNamespace::rU2 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	extern Double_t t2;
	return a[epsU]*(a[epsV]*Vtot(2,a,t[0]) + a[epsW]*Wtot(2,a,t[0]) + a[epsZ]*Ztot(2,a,t[0]) + a[epsX]*Xtot(2,a,t[0]) + a[epsY]*Ytot(2,a,t[0]))/t2;
}
Double_t BFitNamespace::rU3 (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	extern Double_t t3;
	return a[epsU]*(a[epsV]*Vtot(3,a,t[0]) + a[epsW]*Wtot(3,a,t[0]) + a[epsZ]*Ztot(3,a,t[0]) + a[epsX]*Xtot(3,a,t[0]) + a[epsY]*Ytot(3,a,t[0]))/t3;
}
Double_t BFitNamespace::rAll (Double_t *t, Double_t *a) {
	using namespace BFitNamespace;
	return a[DC] + rT1(t,a) + rT2(t,a) + rT3(t,a) + rU1(t,a) + rU2(t,a) + rU3(t,a);
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// T & U populations
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Double_t BFitNamespace::Ttot (Int_t i, Double_t *a, Double_t tvar) {
	using namespace BFitNamespace;
	using namespace TMath;
	extern Double_t tCap, tBac, tCyc, tT1, tT2, tT3;
	extern Double_t ampT1, ampT2, ampT3, *ST1val, *ST2val, *ST3val;
	static Double_t f;
	static Int_t n;
	f = 0.0;
	n = Ceil((tvar-tBac)/tCap);
	if (tBac <= tvar && tvar <= tCyc) {
		if (i==1) f = ampT1 * ST1val[n] * Exp(-(tvar-tBac-(n-1)*tCap)/tT1);//SigmaT(a[rho],tT1,n) * Exp(-(tvar-tBac-(n-1)*tCap)/tT1);
		if (i==2) f = ampT2 * ST2val[n] * Exp(-(tvar-tBac-(n-1)*tCap)/tT2);//SigmaT(a[rho],tT2,n) * Exp(-(tvar-tBac-(n-1)*tCap)/tT2);
		if (i==3) f = ampT3 * ST3val[n] * Exp(-(tvar-tBac-(n-1)*tCap)/tT3);//SigmaT(a[rho],tT3,n) * Exp(-(tvar-tBac-(n-1)*tCap)/tT3);
	}
	return f;
}
Double_t BFitNamespace::Utot (Int_t i, Double_t *a, Double_t tvar) {
	using namespace BFitNamespace;
	using namespace TMath;
	extern Double_t tBac, tCyc;
	static Double_t f;
	f = 0.0;
	if (tBac <= tvar && tvar <= tCyc) {
		if (i==1) f = Vtot(1,a,tvar) + Wtot(1,a,tvar) + Ztot(1,a,tvar);
		if (i==2) f = Vtot(2,a,tvar) + Wtot(2,a,tvar) + Ztot(2,a,tvar) + Xtot(2,a,tvar) + Ytot(2,a,tvar);
		if (i==3) f = Vtot(3,a,tvar) + Wtot(3,a,tvar) + Ztot(3,a,tvar) + Xtot(3,a,tvar) + Ytot(3,a,tvar);
	}
	return f;
}
Double_t BFitNamespace::Ucap (Int_t i, Double_t *a, Double_t tvar) {
	using namespace BFitNamespace;
	using namespace TMath;
	extern Double_t tBac, tCyc;
	static Double_t f;
	f = 0.0;
	if (i==1) f = Vcap(1,a,tvar) + Wcap(1,a,tvar) + Zcap(1,a,tvar);
	if (i==2) f = Vcap(2,a,tvar) + Wcap(2,a,tvar) + Zcap(2,a,tvar) + Xcap(2,a,tvar) + Ycap(2,a,tvar);
	if (i==3) f = Vcap(3,a,tvar) + Wcap(3,a,tvar) + Zcap(3,a,tvar) + Xcap(3,a,tvar) + Ycap(3,a,tvar);
	return f;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// V populations
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Double_t BFitNamespace::Vcap (Int_t i, Double_t *a, Double_t tvar) {
	using namespace BFitNamespace;
	using namespace TMath;
	extern Double_t tCap, tBac, tU1, tU2, tU3;
	extern Double_t ampV1, ampV2, ampV3, *SV1val, *SV2val, *SV3val;
	static Double_t f;
	static Int_t n;
	f = 0.0;
	n = Ceil((tvar-tBac)/tCap);
	if (i==1) f = ampV1 * SV1val[n] * Exp(-(tvar-tBac-(n-1)*tCap)/tU1);//SigmaT(1,tU1,n) * Exp(-(tvar-tBac-(n-1)*tCap)/tU1);
	if (i==2) f = ampV2 * SV2val[n] * Exp(-(tvar-tBac-(n-1)*tCap)/tU2);//SigmaT(1,tU2,n) * Exp(-(tvar-tBac-(n-1)*tCap)/tU2);
	if (i==3) f = ampV3 * SV3val[n] * Exp(-(tvar-tBac-(n-1)*tCap)/tU3);//SigmaT(1,tU3,n) * Exp(-(tvar-tBac-(n-1)*tCap)/tU3);
	return f;
}
Double_t BFitNamespace::Vtot (Int_t i, Double_t *a, Double_t tvar) {
	extern Double_t tBac, tCyc, tU1, tU2, tU3, V10, V20, V30;
	static Double_t f;
	f = 0.0; //catch bad values of tvar
	if (0 <= tvar && tvar <= tCyc) {
		if (i==1) f += V10 * TMath::Exp(-tvar/tU1);
		if (i==2) f += V20 * TMath::Exp(-tvar/tU2);
		if (i==3) f += V30 * TMath::Exp(-tvar/tU3);
	}
	if (tBac <= tvar && tvar <= tCyc)
		f += BFitNamespace::Vcap(i,a,tvar);
	return f;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// W populations
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Double_t BFitNamespace::Wcap (Int_t i, Double_t *a, Double_t tvar) {
	using namespace BFitNamespace;
	using namespace TMath;
	extern Double_t tCap, tBac, tT1, tT2, tT3, tU1, tU2, tU3;
	extern Double_t ampW1, ampW2, ampW3, *SW1val, *SW2val, *SW3val;
	static Double_t f;
	static Int_t n;
	f = 0.0;
	n = Ceil((tvar-tBac)/tCap);
//	if (i==1) f += ampW1 * SigmaW(a[rho],tT1,tU1,n) * Exp(-(tvar-tBac)/tU1);//* Exp(-(tvar-tBac-(n-1)*tCap)/tU1);
//	if (i==2) f += ampW2 * SigmaW(a[rho],tT2,tU2,n) * Exp(-(tvar-tBac)/tU2);//* Exp(-(tvar-tBac-(n-1)*tCap)/tU2);
//	if (i==3) f += ampW3 * SigmaW(a[rho],tT3,tU3,n) * Exp(-(tvar-tBac)/tU3);//* Exp(-(tvar-tBac-(n-1)*tCap)/tU3);
	if (i==1) f += ampW1 * SW1val[n] * Exp(-(tvar-tBac-(n-1)*tCap)/tU1);//* Exp(-(tvar-tBac-(n-1)*tCap)/tU1);
	if (i==2) f += ampW2 * SW2val[n] * Exp(-(tvar-tBac-(n-1)*tCap)/tU2);//* Exp(-(tvar-tBac-(n-1)*tCap)/tU2);
	if (i==3) f += ampW3 * SW3val[n] * Exp(-(tvar-tBac-(n-1)*tCap)/tU3);//* Exp(-(tvar-tBac-(n-1)*tCap)/tU3);
//	printf("Wcap: i=%d, tvar=%f, par=%f, f=%f\n", i, tvar, SigmaW[a[rho],tT3,tU3,n], f);
	return f;
}
Double_t BFitNamespace::Wtot (Int_t i, Double_t *a, Double_t tvar) {
	extern Double_t tBac, tCyc, tU1, tU2, tU3, W10, W20, W30;
	static Double_t f;
	f = 0.0; //catch bad values of tvar
	if (0 <= tvar && tvar <= tCyc) {
		if (i==1) f += W10 * TMath::Exp(-tvar/tU1);
		if (i==2) f += W20 * TMath::Exp(-tvar/tU2);
		if (i==3) f += W30 * TMath::Exp(-tvar/tU3);
	}
	if (tBac <= tvar && tvar <= tCyc)
		f += BFitNamespace::Wcap(i,a,tvar);
//	printf("Wtot: i=%d, par=%f, tvar=%f, f=%f\n",i,W30,tvar,f);
	return f;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Z populations
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Double_t BFitNamespace::Zcap (Int_t i, Double_t *a, Double_t tvar) {
	using namespace BFitNamespace;
	using namespace TMath;
	extern Double_t tCap, tBac, tT1, tT2, tT3, tU1, tU2, tU3;
	extern Double_t ampT2, ampZ1, ampZ2, ampZ3, *ST1val, *ST2val, *ST3val, *SZ1val, *SZ2val, *SZ3val;
	static Double_t g, f;
	static Int_t n;
	f = 0.0;
	n = Ceil((tvar-tBac)/tCap);
//	if (i==1) f += ampZ1 * ( (SigmaZ(a[rho],tT1,tU1,n)+SigmaT(a[rho],tT1,n))*Exp(-(tvar-tBac-(n-1)*tCap)/tU1) - SigmaT(a[rho],tT1,n)*Exp(-(tvar-tBac-(n-1)*tCap)/tT1) );
//	if (i==2) f += ampZ2 * ( (SigmaZ(a[rho],tT2,tU2,n)+SigmaT(a[rho],tT2,n))*Exp(-(tvar-tBac-(n-1)*tCap)/tU2) - SigmaT(a[rho],tT2,n)*Exp(-(tvar-tBac-(n-1)*tCap)/tT2) );
//	if (i==3) f += ampZ3 * ( (SigmaZ(a[rho],tT3,tU3,n)+SigmaT(a[rho],tT3,n))*Exp(-(tvar-tBac-(n-1)*tCap)/tU3) - SigmaT(a[rho],tT3,n)*Exp(-(tvar-tBac-(n-1)*tCap)/tT3) );
	if (i==1) f += ampZ1 * ( SZ1val[n]*Exp(-(tvar-tBac-(n-1)*tCap)/tU1) - ST1val[n]*Exp(-(tvar-tBac-(n-1)*tCap)/tT1) );
	if (i==2) f += ampZ2 * ( SZ2val[n]*Exp(-(tvar-tBac-(n-1)*tCap)/tU2) - ST2val[n]*Exp(-(tvar-tBac-(n-1)*tCap)/tT2) );
	if (i==3) f += ampZ3 * ( SZ3val[n]*Exp(-(tvar-tBac-(n-1)*tCap)/tU3) - ST3val[n]*Exp(-(tvar-tBac-(n-1)*tCap)/tT3) );
	
//	if (i=2) {
//		g = 1/tT2 - 1/tU2;
//		f = 0.0;
//		f = (ampT2*a[gammaT2]/1000.0/g) * ( SZ2val[n] + ST2val[n]*(Exp(-g*(n-1)*tCap)-Exp(-g*(tvar-tBac))) ) * Exp(-(tvar-tBac)/tU2);
//	}
	return f;
}
Double_t BFitNamespace::Ztot (Int_t i, Double_t *a, Double_t tvar) {
	extern Double_t tBac, tCyc, tU1, tU2, tU3, Z10, Z20, Z30;
	static Double_t f;
	f = 0.0; //catch bad values of tvar
	if (0 <= tvar && tvar <= tCyc) {
		if (i==1) f += Z10 * TMath::Exp(-tvar/tU1);
		if (i==2) f += Z20 * TMath::Exp(-tvar/tU2);
		if (i==3) f += Z30 * TMath::Exp(-tvar/tU3);
	}
	if (tBac <= tvar && tvar <= tCyc)
		f += BFitNamespace::Zcap(i,a,tvar);
	return f;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// X populations
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Double_t BFitNamespace::Xcap (Int_t i, Double_t *a, Double_t tvar) {
	using namespace BFitNamespace;
	using namespace TMath;
	extern Double_t tCap, tBac, tT1, tT2, tT3, tU1, tU2, tU3;
	extern Double_t ampX2, ampX3, *ST1val, *ST2val, *SX2val, *SX3val;
	static Double_t f;
	static Int_t n;
	f = 0.0;
	n = Ceil((tvar-tBac)/tCap);
	if (i==2) f += ampX2 * ( SX2val[n] * Exp(-(tvar-tBac-(n-1)*tCap)/tU2) - ST1val[n] * Exp(-(tvar-tBac-(n-1)*tCap)/tT1) );
	if (i==3) f += ampX3 * ( SX3val[n] * Exp(-(tvar-tBac-(n-1)*tCap)/tU3) - ST2val[n] * Exp(-(tvar-tBac-(n-1)*tCap)/tT2) );
	return f;
}
Double_t BFitNamespace::Xtot (Int_t i, Double_t *a, Double_t tvar) {
	extern Double_t tBac, tCyc, tU2, tU3, X20, X30;
	static Double_t f;
	f = 0.0; //catch bad values of tvar
	if (0 <= tvar && tvar <= tCyc) {
		if (i==2) f += X20 * TMath::Exp(-tvar/tU2);
		if (i==3) f += X30 * TMath::Exp(-tvar/tU3);
	}
	if (tBac <= tvar && tvar <= tCyc)
		f += BFitNamespace::Xcap(i,a,tvar);
	return f;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Y populations
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/*
Double_t BFitNamespace::Ycap (Int_t i, Double_t *a, Double_t tvar) {
	using namespace BFitNamespace;
	using namespace TMath;
	extern Double_t tCap, tBac, t1, t2, tT1, tT2, tU1, tU2, tU3, aT1, aU1, aU2, aU3, tU1U2, tT1U2, tU2U3, tT2U3, tU1U3;
	extern Double_t ampV1, ampW1, ampZ1, ampV2, ampW2, ampZ2, ampX2, ampY2;
	extern Double_t *timeOfCapt, *ST1val, *SV1val, *SW1val, *SZ1val, *ST2val, *SV2val, *SW2val, *SZ2val, *SX2val, *SY2val, *SY3val;
	extern Double_t *I_V1_Y2, *I_W1_Y2, *I_Z1_Y2;
	extern Double_t *I_V2_Y3, *I_W2_Y3, *I_Z2_Y3, *I_X2_Y3, *I_Y2_Y3;
//	extern Double_t ampW2, ampY3fromW2, Gamma_U2_U3, *Y3InitialValues;
	static Double_t tk, V, W, Z, X, Y, f;
	static Int_t n, k;
	V = W = Z = X = Y = f = 0.0;
	n = Ceil((tvar-tBac)/tCap);
	//if (tvar==tBac) n=1;
	tk = tvar-tBac-(n-1)*tCap;
	if (i==2) {
	//	V = ampV1 * ( I_V1_Y2[n-1] + SV1val[n] * H_V1_Y2(a,timeOfCapt[n-1],tvar) );
	//	W = ampW1 * ( I_W1_Y2[n-1] + SW1val[n] * H_W1_Y2(a,timeOfCapt[n-1],tvar) );
	//	Z = ampZ1 * ( I_Z1_Y2[n-1] + SZ1val[n] * H_Z1_Y2_Zpart(a,timeOfCapt[n-1],tvar) - ST1val[n] * H_Z1_Y2_Tpart(a,timeOfCapt[n-1],tvar) );
	//	f = (V + W + Z) * Exp(-tvar/tU2) / t1;
		f = SY2val[n] * Exp(-tk/tU2)
			+ tU1U2/t1 * ( Exp(-tk/tU2) - Exp(-tk/tU1) ) * ( ampV1*SV1val[n] + ampW1*SW1val[n] + ampZ1*SZ1val[n] )
			- tT1U2/t1 * ( Exp(-tk/tU2) - Exp(-tk/tT1) ) * ampZ1 * ST1val[n];
//		printf("tk=%f, B1=%f, ampV1=%f, ampW1=%f, ampZ1=%f, SV1=%f, SW1=%f, SZ1=%f, SY2=%f, eU2=%f, eU1=%f, y2=%f\n",tk,B1,ampV1,ampW1,ampZ1,SV1val[n],SW1val[n],SZ1val[n],SZ1val[n],Exp(-tk/tU2),Exp(-tk/tU1),f);
	}
	if (i==3) {
	//	V  = ampV2 * ( I_V2_Y3[n-1] + SV2val[n] * H_V2_Y3(a,timeOfCapt[n-1],tvar) );
	//	W  = ampW2 * ( I_W2_Y3[n-1] + SW2val[n] * H_W2_Y3(a,timeOfCapt[n-1],tvar) );
	//	Z  = ampZ2 * ( I_Z2_Y3[n-1] + SZ2val[n] * H_Z2_Y3_Zpart(a,timeOfCapt[n-1],tvar) - ST2val[n] * H_Z2_Y3_Tpart(a,timeOfCapt[n-1],tvar) );
	//	X  = ampX2 * ( I_X2_Y3[n-1] + SX2val[n] * H_X2_Y3_Xpart(a,timeOfCapt[n-1],tvar) - ST1val[n] * H_X2_Y3_Tpart(a,timeOfCapt[n-1],tvar) );
	//	Y += ampV1 * ( I_V1_Y3[n-1] + SV1val[n] * H_X2_Y3_Xpart(a,timeOfCapt[n-1],tvar);
////		X = ampX2 * ( I_X2_Y3[n-1] + SX2val[n] * H_X2_Y3(a,timeOfCapt[n-1],tvar) );
////		Y = ampX2 * ( I_Y2_Y3[n-1] + SY2val[n] * H_Y2_Y3(a,timeOfCapt[n-1],tvar) );
	//	f = (V + W + Z + X + Y) * Exp(-tvar/tU3) / t2;
	
		f = SY3val[n] * Exp(-tk/tU3)
			+ tU2U3/t2 * ( Exp(-tk/tU3) - Exp(-tk/tU2) ) * ( ampV2*SV2val[n] + ampW2*SW2val[n] + ampZ2*SZ2val[n] + ampX2*SX2val[n] )
			- tT2U3/t2 * ( Exp(-tk/tU3) - Exp(-tk/tT2) ) * (ampZ2+ampX2) * ST2val[n]
			//+ ampV1*tU1U2/t1/t2 * ( tU2U3 * ( ( sigmaI(1,aU1,k) + (aU2-aU1)*sigmaII(1,aU1,aU2,k) ) * ( Exp(-tk/tU3) - Exp(-tk/tU2) ) - tU1U3 * sigmaII(1,aU1,aU3,k) );
			+ tU2U3/t2 * (ampV1*tU1U2/t1*(aU2-aU1)*sigmaIII(1,aU1,aU2,aU3,n)) * ( Exp(-tk/tU3) - Exp(-tk/tU2) )
			+ ampV1*tU1U2/t1 * (sigmaII(1,aU1,aU3,n)) * ( tU2U3/t2 * ( Exp(-tk/tU3) - Exp(-tk/tU2) ) - tU1U3/t2 * ( Exp(-tk/tU3) - Exp(-tk/tU1) ) );
	
	}
////	Y3InitialValues[k-1] = Ycap(3,a,tBac+(k-1)*tCap);
////		printf("Y3IV[%d]=%f\n",k-1,Y3InitialValues[k-1]);
	return f;
}
*/
Double_t BFitNamespace::Ytot (Int_t i, Double_t *a, Double_t tvar) {
	extern Int_t nCap;
	extern Double_t tBac, tCyc, tU1, tU2, tU3, U10, U20, Y20, Y30;
	static Double_t f;
	f = 0.0;
	if (0 <= tvar && tvar <= tCyc) {
		if (i==2) f += Y2Background(U10,Y20,tvar);
		if (i==3) f += Y3Background(U10,U20,Y30,tvar);
	}
	if (tBac < tvar && tvar <= tCyc)
		f += BFitNamespace::Ycap(i,a,tvar);
	return f;
}

Double_t BFitNamespace::Y2Background (Double_t u10, Double_t u20, Double_t tvar) {
	using namespace TMath;
	extern Double_t t1, tU1, tU2;
	return u20 * Exp(-tvar/tU2) + u10 * tU1/t1 * tU2/(tU2-tU1) * ( Exp(-tvar/tU2) - Exp(-tvar/tU1) );
}
Double_t BFitNamespace::Y3Background (Double_t u10, Double_t u20, Double_t u30, Double_t tvar) {
	using namespace TMath;
	extern Double_t tBac, tCyc, t1, t2, tU1, tU2, tU3, cYU1, cYU2, cYU3, ThetaU;
	return u30 * Exp(-tvar/tU3)
			+ u20 * tU2/t2 * tU3/(tU3-tU2) * ( Exp(-tvar/tU3) - Exp(-tvar/tU2) )
			+ u10 * tU1/t1 * tU2/t2 * tU3/ThetaU * ( cYU1*Exp(-tvar/tU1) - cYU2*Exp(-tvar/tU2) + cYU3*Exp(-tvar/tU3) );
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Y populations
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Double_t BFitNamespace::Y2InitialValue (Double_t tvar, Double_t *a, Double_t t0, Double_t y0) {
	using namespace BFitNamespace;
	using namespace TMath;
	extern Double_t iota, tT1, tU1, tU2, cT1, cU1, cU2;
	extern Double_t ST1_1cap, ampY2ptA, ampY2ptB;
	static Double_t tk, A, B, f;
	f = 0.0;
	tk = tvar-t0;
	A = ampY2ptA * ST1_1cap * (cT1*Exp(-tk/tT1) - cU1*Exp(-tk/tU1) + cU2*Exp(-tk/tU2));
	B = 0.0;//( (1-a[p])*SigmaT(a[rho],tT1,1) + a[p]*(1-a[rho])*SigmaW(a[rho],tT1,tU1,1) + a[p]*(a[gammaT1]+iota)/(a[gammaT1]-a[gammaU1]+iota)*SigmaZ(a[rho],tT1,tU1,1) ) * ( Exp(-tk/tU2) - Exp(-tk/tU1) );
	f = ampY2ptB * (A + B);
	return y0*Exp(-tk/tU2) + f;
}

Double_t BFitNamespace::Y3InitialValue (Double_t tvar, Double_t *a, Double_t t0, Double_t y0) {
	using namespace BFitNamespace;
	using namespace TMath;
	extern Double_t iota, tCap, tBac, t1, t2, t3;
	extern Double_t tT1, tT2, tU1, tU2, tU3, ThetaU, ThetaY;
	extern Double_t ST1_1cap, SW11_1cap, SZ11_1cap, ST2_1cap, SW22_1cap, SZ12_1cap, SZ22_1cap;
	extern Double_t *SW2val;
	extern Double_t cZT2, cZU2, cZU3, cXT1, cXU2, cXU3, cYU1, cYU2, cYU3;
	extern Double_t ampY3fromV2, ampY3fromW2, ampY3fromZ2, ampY3fromX2, ampY3fromY2_ST1, ampY3fromY2_SW11, ampY3fromY2_SZ11;
	static Double_t tx, eT1, eT2, eU1, eU2, eU3;
	static Double_t V, W, Z, X, Y, f;
	static Double_t SWIntegral, Gamma;
	static Int_t n, k;
	n	= Ceil((tvar-tBac)/tCap);
	Gamma = (1/tU2)-(1/tU3);
	SWIntegral = 0.0;
//	if (n >= 1) {
	SWIntegral += SW2val[n-1] * ( Exp(-Gamma*tvar) - Exp(-(n-1)*Gamma*tCap) ); // integral over current tooth
	if (n>=2) for (k = 1; k<=n-1; k++) SWIntegral += SW2val[k-1] * ( tCap + (Exp(Gamma*tCap)-1)/Gamma * Exp(-k*Gamma*tCap) ); // integral over any previous teeth
	
//			printf("n=%d, k=%d, SWI=%f\n", n, k, SWIntegral);
	
//	printf("rho=%f, tT=%f, tU=%f, SWI=%f\n", a[rho], tT2, tU2, SWIntegral);
	tx	= tvar-t0;
	eT1	= Exp(-tx/tT1);
	eT2	= Exp(-tx/tT2);
	eU1	= Exp(-tx/tU1);
	eU2	= Exp(-tx/tU2);
	eU3	= Exp(-tx/tU3);
	V = ampY3fromV2 * ST2_1cap  * (eU3 - eU2); // feeding from V2
//	W = ampY3fromW2 * SW2val[n] * (eU3 - eU2); // feeding from W2
//	W = ampY3fromW2 * SWIntegral * Exp(-(tvar-tBac)/tU3);// * (eU3 - eU2); // feeding from W2  Exp(-(tBac+(n-1)*tCap)/tU2)
//	W = ampY3fromW2 * SW22_1cap * (eU3 - eU2); // feeding from W2
//	W = ampY3fromW2 * a[epsY] * (eU3 - eU2); // feeding from W2
	Z = 0.0;//ampY3fromZ2 * ( (ST2_1cap/cZU2) * ( cZT2 * eT2 - cZU2 * eU2 + cZU3 * eU3 ) );// + SZ22_1cap*(eU3-eU2) ); // feeding from Z2
	X = ampY3fromX2 * ( (ST1_1cap/cXU2) * ( cXT1 * eT1 - cXU2 * eU2 + cXU3 * eU3 ) );// + SZ12_1cap*(eU3-eU2) ); // feeding from X2
	Y = ampY3fromY2_ST1 * ST1_1cap * 0.001 * ( // 0.001 for the a[gammaT1] from 1/s to 1/ms
			- eT1 * tT1*tT1*(tU3-tU2)*(tU3-tU1)*(tU2-tU1)*a[p]*a[gammaT1]
			+ eU1 * tU1*tU1*(tU3-tU2)*(tU3-tT1)*(tU2-tT1)*(a[gammaT1] - (1-a[p])*a[gammaU1])
			- eU2 * tU2*(tU3-tU1)*(tU3-tT1)*((a[gammaT1])*(tU1*tU2-tT1*(a[p]*tU2+(1-a[p])*tU1))-(a[gammaU1])*(1-a[p])*tU1*(tU2-tT1))
			+ eU3 * tU3*(tU2-tU1)*(tU2-tT1)*((a[gammaT1])*(tU1*tU3-tT1*(a[p]*tU3+(1-a[p])*tU1))-(a[gammaU1])*(1-a[p])*tU1*(tU3-tT1)) );//
//	printf("AW2=%f, n=%d, tx=%f, (eU3-eU2)=%f, V=%f, W=%f, Z=%f, X=%f, Y=%f, Y3=%f\n", ampY3fromW2, n, tx, eU3-eU2, V, W, Z, X, Y, y0*Exp(-tx/tU3) + V + W + X + Y + Z);
	f = y0*Exp(-tx/tU3) + V + W + X + Y + Z;
//	if (tvar == tBac+2*tCap && t0 == tBac+1*tCap) printf("Y3IV: n=%d, SW[%d]=%f, W=%f, f=%f\n", n, n-1, SW2val[n-1], W, f);
	return f;
//	return 1.0;
}

