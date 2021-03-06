/*
2013-12-07 Shane Caldwell
	Made from fit_beta_singles.cxx.
	Will modify as necessary to validate against B_monte_carlo output.
2014-02-26
	Making a standalone C++ version of B_fit.cpp, which is a ROOT program.
	Big difference: this program does not output plots to screen. Instead it saves them to a
	subdirectory of the ROOT file that is given to it.
2014-06-29
	Just now noting this: Program now (as of like easrly March) uses the CSVtoStruct.h/cxx
*/

#include <unistd.h>
#include "stdio.h"
#include <iostream>
#include <iomanip>
#include <cstring>
#include "time.h"
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
//#include "include/bdn.h"
//#include "include/sb135.h"
//#include "bdn_cases.h"
#include "bdn_histograms.h"
#include "CSVtoStruct.h"
#include "BFitModel.h"
using namespace std;

// Global variables
BDNCase_t	stBDNCases[FILE_ROWS_BDN];
BFitCase_t	stBFitCases[FILE_ROWS_BFit];
Int_t		iBDNCaseIndex, iBFitCaseIndex; // global index to identify case
Int_t		iNumStructs_BDN, iNumStructs_BFit;
Double_t	tCap, tBac, tCyc;
Double_t	t1, t2, t3;
Double_t	iota; // tiny number for avoiding divide-by-0
bool		b134sbFlag = 0;

void HistPrep (TH1*, Int_t);
void FuncPrep (TF1*, Double_t*, Int_t, Int_t);
int BFit ();

// MAIN FUNCTION
int main (int argc, char *argv[]) {
	char *csvBDNCases, *csvBFitCases;
	csvBDNCases = "BDNCases.csv_transposed";
	csvBFitCases = "BFitCases.csv_transposed";
	cout << endl << "Importing metadata from CSV files..." << endl;
	iNumStructs_BDN  = CSVtoStruct_BDN  (csvBDNCases, stBDNCases);
	cout << "Imported " << iNumStructs_BDN << " BDN cases" << endl;
	iNumStructs_BFit = CSVtoStruct_BFit (csvBFitCases, stBFitCases);
	cout << "Imported " << iNumStructs_BFit << " BFit cases" << endl;
	iBDNCaseIndex  = FindStructIndex ( stBDNCases,  sizeof(BDNCase_t),  iNumStructs_BDN,  argv[1] );
	iBFitCaseIndex = FindStructIndex ( stBFitCases, sizeof(BFitCase_t), iNumStructs_BFit, argv[2] );
	if ( iBDNCaseIndex == -1 || iBFitCaseIndex == -1 )
	{ // One of the read-ins failed and already printed a message about it
		cout << "How to run this program:" << endl;
		cout << "'./BFit <BDN case code> <B_fit case code>'" << endl;
		cout << "where valid case codes are listed in the CSV files." << endl << endl;
		return -1; // error return
	}
	cout << "Performing BFit with BDN case " << stBDNCases[iBDNCaseIndex].pcsCaseCode << " and BFit case " << stBFitCases[iBFitCaseIndex].pcsCaseCode << endl << endl;
	return BFit(); // return status of BFit
}

int BFit () {

// Timer for debugging code
	clock_t timer, timerStart, timerStop;
	timerStart = clock();
	cout << "BFit started. Timer = "<< (Float_t)timerStart/CLOCKS_PER_SEC << " sec." << endl;
	int iReturn = SUCCESS;
	using namespace BFitNamespace;
	using namespace TMath;
	TFile *outfile = new TFile("BFit.root","recreate");
	
// Local copies of the relevant metadata structs
	BDNCase_t  stBDNCase = stBDNCases[iBDNCaseIndex];
	BFitCase_t stBFitCase = stBFitCases[iBFitCaseIndex];
	//printf("Bdn Case index = %d, BFit case index = %d\n", iBDNCaseIndex, iBFitCaseIndex);
	//	bookGlobals();
	iota	= 0.000000000001;
	tCap	= 1000.0 * stBDNCase.dCaptureTime;	// Time between BPT captures (ms)
	tBac	= 1000.0 * stBDNCase.dBackgroundTime; // Time spent in background measurment, per cycle (ms)
	tCyc	= 1000.0 * stBDNCase.dCycleTime;	// Time between BPT ejections (ms)
	t1		= 1000.0 * stBDNCase.dLifetime1[0]; // radioactive lifetime (1/e) in ms
	t2		= 1000.0 * stBDNCase.dLifetime2[0]; // radioactive lifetime (1/e) in ms
	t3		= 1000.0 * stBDNCase.dLifetime3[0]; // radioactive lifetime (1/e) in ms
	
	TString separator = "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
	cout << endl << separator << endl;
	cout << "BETA SINGLES MODEL" << endl << separator << endl;
	cout << "Case: " << stBDNCase.pcsCaseCode << endl;
	cout << "File: " << stBDNCase.pcsFilePath << endl;
	cout << "Histogram: " << stBFitCase.pcsHistName << endl;
	printf("Total cycle time\t= %10.3f s\n",	stBDNCase.dCycleTime);
	printf("Background time\t\t= %10.3f s\n",	stBDNCase.dBackgroundTime);
	printf("Capture cycle time\t= %10.3f s\n",	stBDNCase.dCaptureTime);
	printf("Last capture time\t= %10.3f s\n",	stBDNCase.dLastCaptureTime);
	cout << stBDNCase.pcsSpecies1Name; printf(" halflife\t\t= %10.3f s  (lifetime %10.3f s)\n", stBDNCase.dHalfLife1[0], stBDNCase.dLifetime1[0]);
	cout << stBDNCase.pcsSpecies2Name; printf(" halflife\t\t= %10.3f s  (lifetime %10.3f s)\n", stBDNCase.dHalfLife2[0], stBDNCase.dLifetime2[0]);
	cout << stBDNCase.pcsSpecies3Name; printf(" halflife\t\t= %10.3f s  (lifetime %10.3f s)\n", stBDNCase.dHalfLife3[0], stBDNCase.dLifetime3[0]);
	cout << separator << endl;
	
// Get histogram from ROOT file
	TFile *f = new TFile(stBDNCase.pcsFilePath);
	TH1D *h	= (TH1D*)f->Get(stBFitCase.pcsHistName);
	Double_t dBinWidth		= stBFitCase.pdSeed[dt];
	Double_t dNBins			= tCyc/dBinWidth;// # of bins covered by funtion  //h->GetNbinsX();
	Double_t pointsPerBin	= 5;
	Double_t nPoints		= pointsPerBin * dNBins;
	Double_t dRebinFactor	= dBinWidth/(h->GetBinWidth(1));
//	Double_t dRebinFactor = stBFitCase.iBinWidth/(h->GetBinWidth(1));
	Double_t binZero  = (1.0/dRebinFactor)*(0.0  - tCycMin) + 1.0;
	Double_t binCapt  = (1.0/dRebinFactor)*(tBac - tCycMin) + 1.0;
	Double_t binCycle = (1.0/dRebinFactor)*(tCyc - tCycMin) + 1.0;
	TH1D *h1	= (TH1D*)h->Rebin(dRebinFactor,stBFitCase.pcsHistName);
	TH1D *h2	= (TH1D*)h->Rebin(dRebinFactor,stBFitCase.pcsHistName);
	cout << "HISTOGRAM REBINNED" << endl;
	cout << "   Number of hist bins = " << dNBins << endl;
	cout << "   Number of fn points = " << nPoints << endl;
	cout << "   Number of pts/bin   = " << pointsPerBin << endl;
	cout << separator << endl;
	if (stBFitCase.bDoFit) cout << "Doing fit with option string: " << stBFitCase.pcsOptions << endl;
	else cout << "Not fitting! Drawing functions using parameter seed values." << endl;
	cout << separator << endl;
	
// Define functions
	Int_t nPars = stBFitCase.iNPars;
//	Double_t tMax	= 1000.0 * stBDNCase.dCycleTime;
// Species populations
	TF1 *fyDC	= new TF1("fyDC", yDC, 0.0, tCyc, nPars);
	TF1 *fyT1	= new TF1("fyT1", yT1, 0.0, tCyc, nPars);
	TF1 *fyT2	= new TF1("fyT2", yT2, 0.0, tCyc, nPars);
	TF1 *fyT3	= new TF1("fyT3", yT3, 0.0, tCyc, nPars);
	TF1 *fyU1	= new TF1("fyU1", yU1, 0.0, tCyc, nPars);
	TF1 *fyU2	= new TF1("fyU2", yU2, 0.0, tCyc, nPars);
	TF1 *fyU3	= new TF1("fyU3", yU3, 0.0, tCyc, nPars);
//**************************************************************************
// This one fits the data:
	TF1 *fyAll	= new TF1("fyAll",yAll, 0.0, tCyc, nPars);
//**************************************************************************
// Beta rates to be used by TF1::Integral() and TF1::IntegralError()
	TF1 *frDC	= new TF1("frDC", rDC, 0.0, tCyc, nPars);
	TF1 *frT1	= new TF1("frT1", rT1, 0.0, tCyc, nPars);
	TF1 *frT2	= new TF1("frT2", rT2, 0.0, tCyc, nPars);
	TF1 *frT3	= new TF1("frT3", rT3, 0.0, tCyc, nPars);
	TF1 *frU1	= new TF1("frU1", rU1, 0.0, tCyc, nPars);
	TF1 *frU2	= new TF1("frU2", rU2, 0.0, tCyc, nPars);
	TF1 *frU3	= new TF1("frU3", rU3, 0.0, tCyc, nPars);
	TF1 *frAll	= new TF1("frAll",rAll, 0.0, tCyc, nPars);
// Offset functions for plotting
	TF1 *foT1	= new TF1("foT1", oT1, 0.0, tCyc, nPars);
	TF1 *foT2	= new TF1("foT2", oT2, 0.0, tCyc, nPars);
	TF1 *foT3	= new TF1("foT3", oT3, 0.0, tCyc, nPars);
	TF1 *foU1	= new TF1("foU1", oU1, 0.0, tCyc, nPars);
	TF1 *foU2	= new TF1("foU2", oU2, 0.0, tCyc, nPars);
	TF1 *foU3	= new TF1("foU3", oU3, 0.0, tCyc, nPars);
// Initiailize function to fit the data
	char pcsLifetime1ParName[100]; sprintf(pcsLifetime1ParName,"%s radioactive lifetime (1/e)", stBDNCase.pcsSpecies1Name);
	char pcsLifetime2ParName[100]; sprintf(pcsLifetime2ParName,"%s radioactive lifetime (1/e)", stBDNCase.pcsSpecies2Name);
	char pcsLifetime3ParName[100]; sprintf(pcsLifetime3ParName,"%s radioactive lifetime (1/e)", stBDNCase.pcsSpecies3Name);
	fyAll->SetParName(nCyc,"# Cyc's");
	fyAll->SetParName(DC,"DC rate");
	fyAll->SetParName(r1,"Rate 1");
	fyAll->SetParName(r2,"Rate 2");
	fyAll->SetParName(r3,"Rate 3");
	fyAll->SetParName(p,"Capt eff");
	fyAll->SetParName(rho,"Capt ret");
	fyAll->SetParName(epsT,"T eff");
	fyAll->SetParName(epsU,"U eff");
	fyAll->SetParName(epsV,"V eff");
	fyAll->SetParName(epsW,"W eff");
	fyAll->SetParName(epsX,"X eff");
	fyAll->SetParName(epsY,"Y eff");
	fyAll->SetParName(epsZ,"Z eff");
//	fyAll->SetParName(tau1,pcsLifetime1ParName);//"Lifetime 1");//pcsSpecies1ParName);
//	fyAll->SetParName(tau2,pcsLifetime2ParName);//"Lifetime 2");//pcsSpecies2ParName);
//	fyAll->SetParName(tau3,pcsLifetime3ParName);//"Lifetime 3");//pcsSpecies3ParName);
	fyAll->SetParName(gammaT1,"T1 loss");
	fyAll->SetParName(gammaT2,"T2 loss");
	fyAll->SetParName(gammaT3,"T3 loss");
	fyAll->SetParName(gammaU1,"U1 loss");
	fyAll->SetParName(gammaU2,"U2 loss");
	fyAll->SetParName(gammaU3,"U3 loss");
	fyAll->SetParName(dt,"Bin width");
	
// Initial parameter values and initial step sizes
// err contains initial step sizes now, will contain error estimates later.
	Int_t		*tog;
	Double_t	*par;//[nPars];
	Double_t	*err;//[nPars];
	tog	= stBFitCase.pbToggle;
	par = stBFitCase.pdSeed;
	err = stBFitCase.pdStep;
	Int_t index;
	
	fyAll->SetParameters(par);
	fyAll->SetParErrors(err);
// Print seed values that are assigned to the fit function
	cout << "PARAMETER SEED VALUES" << endl << separator << endl;
	cout << setw(14) << "Par name" << setw(10) << "Varying?" << "\t" << "Par init val and step" << endl << separator << endl;
	for (index = 0; index < nPars; index++) {
		cout << setw(14) << fyAll->GetParName(index) << setw(10) << tog[index] << "\t" << fyAll->GetParameter(index) << " +/- " << fyAll->GetParError(index) << endl;
	}
	cout << separator << endl;
	if (!strcmp(stBDNCases[iBDNCaseIndex].pcsCaseCode,"134sb01") ||
		!strcmp(stBDNCases[iBDNCaseIndex].pcsCaseCode,"134sb02") ||
		!strcmp(stBDNCases[iBDNCaseIndex].pcsCaseCode,"134sb03") ||
		!strcmp(stBDNCases[iBDNCaseIndex].pcsCaseCode,"134sb0103"))
	{
		b134sbFlag = 1;
		cout << "134-Sb data detected. Forcing gammaT3 = gammaT2. YOU SHOULD GUARANTEE THAT X3 = Y3 = 0. You can set epsX = epsY = 0." << endl << endl;
	}
	else cout << endl;
// Initialize all functions to parameter seed values
	fyDC	-> SetParameters(par);
	fyT1	-> SetParameters(par);
	fyT2	-> SetParameters(par);
	fyT3	-> SetParameters(par);
	fyU1	-> SetParameters(par);
	fyU2	-> SetParameters(par);
	fyU3	-> SetParameters(par);
	frDC	-> SetParameters(par);
	frT1	-> SetParameters(par);
	frT2	-> SetParameters(par);
	frT3	-> SetParameters(par);
	frU1	-> SetParameters(par);
	frU2	-> SetParameters(par);
	frU3	-> SetParameters(par);
	frAll	-> SetParameters(par);
	foT1	-> SetParameters(par);
	foT2	-> SetParameters(par);
	foT3	-> SetParameters(par);
	foU1	-> SetParameters(par);
	foU2	-> SetParameters(par);
	foU3	-> SetParameters(par);
	
	if (stBFitCase.bDoFit) {
	// Fix the parameters that are supposed to be fixed
		for (index = 0; index < nPars; index++) {
			if (tog[index] == 0) fyAll->FixParameter(index, stBFitCase.pdSeed[index]);
		}
		if (b134sbFlag && tog[gammaT2]==0) fyAll->FixParameter(gammaT3, stBFitCase.pdSeed[gammaT2]);
	// Do fit and get results
		timer = clock();
		TFitResultPtr fit = h1->Fit("fyAll",stBFitCase.pcsOptions);
		timer = clock() - timer;
		printf("Fitting done in %d clicks (%f seconds).\n", timer, (Float_t)timer/CLOCKS_PER_SEC);
		TMatrixDSym cov = fit->GetCovarianceMatrix();
		fit->Print("V");
	// Get parameter values from fit
		for (index = 0; index < nPars; index++) {
			par[index] = fyAll->GetParameter(index);
			err[index] = fyAll->GetParError(index);
		}
	// Set other functions to parameter values from fit
		fyDC	-> SetParameters(par);
		fyT1	-> SetParameters(par);
		fyT2	-> SetParameters(par);
		fyT3	-> SetParameters(par);
		fyU1	-> SetParameters(par);
		fyU2	-> SetParameters(par);
		fyU3	-> SetParameters(par);
		frDC	-> SetParameters(par);
		frT1	-> SetParameters(par);
		frT2	-> SetParameters(par);
		frT3	-> SetParameters(par);
		frU1	-> SetParameters(par);
		frU2	-> SetParameters(par);
		frU3	-> SetParameters(par);
		frAll	-> SetParameters(par);
		foT1	-> SetParameters(par);
		foT2	-> SetParameters(par);
		foT3	-> SetParameters(par);
		foU1	-> SetParameters(par);
		foU2	-> SetParameters(par);
		foU3	-> SetParameters(par);
		
	//// Calculate integrals and errors (OLD WAY -- doesn't work for arbitrary # of varying params)
	//	//Double_t N_beta_2_calc = par[p]*par[r2]*(T-Tb-t2*(1-Exp(-(T-Tb)/t2)));
	//	Double_t N_beta_1 = frT1->Integral(Tb,T);
	//	Double_t N_beta_2 = frT2->Integral(Tb,T);
	//	Double_t N_beta_3 = frT3->Integral(Tb,T);
	//	
	//	Double_t dNdp1 = par[r1]*(T-Tb-par[tauT1]*(1-Exp(-(T-Tb)/par[tauT1])));
	//	Double_t dNdr1 = par[p] *(T-Tb-par[tauT1]*(1-Exp(-(T-Tb)/par[tauT1])));
	//	Double_t dNdt1 = par[p]*par[r1]*(((T-Tb)/par[tauT1]+1)*Exp(-(T-Tb)/par[tauT1])-1);
	//	Double_t N_beta_1_err = sqrt(dNdp1*dNdp1*err[p]*err[p] + dNdr1*dNdr1*err[r1]*err[r1] + dNdt1*dNdt1*err[tauT1]*err[tauT1] + 2.0*dNdp1*dNdr1*cov[p][r1]);
	//	
	//	Double_t dNdp2 = par[r2]*(T-Tb-par[tauT2]*(1-Exp(-(T-Tb)/par[tauT2])));
	//	Double_t dNdr2 = par[p] *(T-Tb-par[tauT2]*(1-Exp(-(T-Tb)/par[tauT2])));
	//	Double_t dNdt2 = par[p]*par[r2]*(((T-Tb)/par[tauT2]+1)*Exp(-(T-Tb)/par[tauT2])-1);
	//	Double_t N_beta_2_err = sqrt(dNdp2*dNdp2*err[p]*err[p] + dNdr2*dNdr2*err[r2]*err[r2] + dNdt2*dNdt2*err[tauT2]*err[tauT2] + 2.0*dNdp2*dNdr2*cov[p][r2]);
	//	
	//	Double_t dNdp3 = par[r3]*(T-Tb-par[tauT3]*(1-Exp(-(T-Tb)/par[tauT3])));
	//	Double_t dNdr3 = par[p] *(T-Tb-par[tauT3]*(1-Exp(-(T-Tb)/par[tauT3])));
	//	Double_t dNdt3 = par[p]*par[r3]*(((T-Tb)/par[tauT3]+1)*Exp(-(T-Tb)/par[tauT3])-1);
	//	Double_t N_beta_3_err = sqrt(dNdp3*dNdp3*err[p]*err[p] + dNdr3*dNdr3*err[r3]*err[r3] + dNdt3*dNdt3*err[tauT3]*err[tauT3]+ 2.0*dNdp3*dNdr3*cov[p][r3]);
	//	
	//	printf("\n");
	//	printf("N_beta_1 (detected) = %f +/- %f\n", N_beta_1, N_beta_1_err);
	//	printf("N_beta_2 (detected) = %f +/- %f\n", N_beta_2, N_beta_2_err);
	//	printf("N_beta_3 (detected) = %f +/- %f\n", N_beta_3, N_beta_3_err);
	//	printf("\n");
		
	// Estimate # of betas detected and error
		T1_integral = par[nCyc]*frT1->Integral( 0.0, tCyc);
		T2_integral = par[nCyc]*frT2->Integral( 0.0, tCyc);
		T3_integral = par[nCyc]*frT3->Integral( 0.0, tCyc);
		U1_integral = par[nCyc]*frU1->Integral( 0.0, tCyc);
		U2_integral = par[nCyc]*frU2->Integral( 0.0, tCyc);
		U3_integral = par[nCyc]*frU3->Integral( 0.0, tCyc);
		DC_integral = par[nCyc]*frDC->Integral( 0.0, tCyc);
		All_integral = par[nCyc]*frAll->Integral( 0.0, tCyc);
		Integral_sum = DC_integral + T1_integral + T2_integral + T3_integral + U1_integral + U2_integral + U3_integral;
		
		timer = clock() - timer;
		printf("\nIntegrals computed in %d clicks (%f seconds).\n", timer, (Float_t)timer/CLOCKS_PER_SEC);
		
		if (stBFitCase.bComputeOtherIntegrals) {
			U1_integral_trap_empty = par[nCyc]*frU1->Integral( 0.0, tBac);
			U2_integral_trap_empty = par[nCyc]*frU2->Integral( 0.0, tBac);
			U3_integral_trap_empty = par[nCyc]*frU3->Integral( 0.0, tBac);
			U1_integral_trap_full  = par[nCyc]*frU1->Integral( tBac, tCyc);
			U2_integral_trap_full  = par[nCyc]*frU2->Integral( tBac, tCyc);
			U3_integral_trap_full  = par[nCyc]*frU3->Integral( tBac, tCyc);
			
			timer = clock() - timer;
			printf("Other integrals computed in %d clicks (%f seconds).\n", timer, (Float_t)timer/CLOCKS_PER_SEC);
		}
		
		T1_integral_error = par[nCyc]*frT1->IntegralError( 0.0, tCyc, par, cov.GetMatrixArray() );
		T2_integral_error = par[nCyc]*frT2->IntegralError( 0.0, tCyc, par, cov.GetMatrixArray() );
		T3_integral_error = par[nCyc]*frT3->IntegralError( 0.0, tCyc, par, cov.GetMatrixArray() );
		U1_integral_error = par[nCyc]*frU1->IntegralError( 0.0, tCyc, par, cov.GetMatrixArray() );
		U2_integral_error = par[nCyc]*frU2->IntegralError( 0.0, tCyc, par, cov.GetMatrixArray() );
		U3_integral_error = par[nCyc]*frU3->IntegralError( 0.0, tCyc, par, cov.GetMatrixArray() );
		DC_integral_error = par[nCyc]*frDC->IntegralError( 0.0, tCyc, par, cov.GetMatrixArray() );
		All_integral_error = par[nCyc]*frAll->IntegralError( 0.0, tCyc, par, cov.GetMatrixArray() );
		
		Integral_sum_error = Sqrt( Power(DC_integral_error,2.0) + Power(T1_integral_error,2.0) + Power(T2_integral_error,2.0) + Power(T3_integral_error,2.0) + Power(U1_integral_error,2.0) + Power(U2_integral_error,2.0) + Power(U3_integral_error,2.0) );
		
		timer = clock() - timer;
		printf("Errors computed in %d clicks (%f seconds).\n", timer, (Float_t)timer/CLOCKS_PER_SEC);
		
		cout << endl << separator << endl;
		printf("NUMBER OF BETAS DETECTED, by population:\n");
		cout << separator << endl;
		printf("T1 integral = %f +/- %f\n", T1_integral, T1_integral_error);
		printf("U1 integral = %f +/- %f\n", U1_integral, U1_integral_error);
		printf("T2 integral = %f +/- %f\n", T2_integral, T2_integral_error);
		printf("U2 integral = %f +/- %f\n", U2_integral, U2_integral_error);
		printf("T3 integral = %f +/- %f\n", T3_integral, T3_integral_error);
		printf("U3 integral = %f +/- %f\n", U3_integral, U3_integral_error);
		printf("DC integral = %f +/- %f\n", DC_integral, DC_integral_error);
		cout << separator << endl;
		printf("Sum of above = %f +/- %f <-- no cov in unc\n", Integral_sum, Integral_sum_error);
		printf("All integral = %f +/- %f\n", All_integral, All_integral_error);
		if (stBFitCase.bComputeOtherIntegrals) {
			cout << separator << endl;
			printf("U1 with trap emtpy = %f; trap full = %f\n", U1_integral_trap_empty, U1_integral_trap_full);
			printf("U2 with trap emtpy = %f; trap full = %f\n", U2_integral_trap_empty, U2_integral_trap_full);
			printf("U3 with trap emtpy = %f; trap full = %f\n", U3_integral_trap_empty, U3_integral_trap_full);
//			printf("All untrapped with trap empty = %f (bin %f to bin %f)\n", h1->Integral(binZero, binCapt-1) - par[DC]*tBac, binZero, binCapt);
//			printf("All data area in histogram = %f\n", h1->Integral(binZero, binCycle-1));
//			printf("All data area in histogram = %f\n", h1->Integral());
		}
		cout << separator << endl << endl;
		
	} // end if (stBFitCase.bDoFit)
	
// Draw
	Double_t yMin, yMax, yRange;

	fyAll->SetLineColor(kBlack);
	fyDC->SetLineColor(kBlack);
	foT1->SetLineColor(kGreen);
	foT2->SetLineColor(kBlue);
	foT3->SetLineColor(kRed);
	foU1->SetLineColor(kGreen);
	foU2->SetLineColor(kBlue);
	foU3->SetLineColor(kRed);
	h1->SetLineColor(16);
//	h2->SetLineColor(16);
	
	fyDC->SetLineStyle(7);
	foU1->SetLineStyle(7);
	foU2->SetLineStyle(7);
	foU3->SetLineStyle(7);
	
//	Double_t nPoints = 2 * (1000.0 * stBDNCase.dCycleTime / dRebinFactor); // leading interger is number of points per bin
// Now defined above
	fyAll->SetNpx(nPoints);
	foT1->SetNpx(nPoints);
	foT2->SetNpx(nPoints);
	foT3->SetNpx(nPoints);
	foU1->SetNpx(nPoints);
	foU2->SetNpx(nPoints);
	foU3->SetNpx(nPoints);
	
	TCanvas *c_BFit	= new TCanvas("c_BFit","Beta singles fit",945,600);
	gStyle->SetOptStat("e");
	gStyle->SetOptFit(1111);
	h1 ->Draw("HIST");
	fyAll ->Draw("SAME");
	foU1->Draw("SAME");
	foT1->Draw("SAME");
	foU3->Draw("SAME");
	foT3->Draw("SAME");
	foU2->Draw("SAME");
	foT2->Draw("SAME");
	fyDC->Draw("SAME");
	//c_B_fit->Update();
	
	//Double_t xMin = h1->GetXaxis()->GetXmin();
	//Double_t xMax = h1->GetXaxis()->GetXmax();
	yMin = par[DC]*par[dt];
	yMax = h1->GetMaximum();
//	printf("\nY Range is %f to %f\n\n",yMin,yMax);
	yRange = yMax - yMin;
	yMin = yMin - 0.05*yRange;
	yMax = yMax + 0.05*yRange;
	//printf("Range = (%f,%f)\n", yMin, yMax);
	h1->GetYaxis()->SetRangeUser(yMin,yMax);
//	h2->GetYaxis()->SetRangeUser(yMin,yMax);
	h1->GetXaxis()->SetRangeUser(-1000,tCyc+1000);
//	h2->GetXaxis()->SetRangeUser(-1000,tCyc+1000);
	
	TLegend *leg_1 = new TLegend(0.13, 0.69, 0.32, 0.94);
	leg_1->AddEntry(h1 , "Data");
	leg_1->AddEntry(fyDC, "DC");
	char pcsT1Name[STRING_SIZE], pcsT2Name[STRING_SIZE], pcsT3Name[STRING_SIZE];
	char pcsU1Name[STRING_SIZE], pcsU2Name[STRING_SIZE], pcsU3Name[STRING_SIZE];
	strcpy(pcsT1Name, stBDNCase.pcsSpecies1Name); strcat(pcsT1Name, " trapped");
	strcpy(pcsT2Name, stBDNCase.pcsSpecies2Name); strcat(pcsT2Name, " trapped");
	strcpy(pcsT3Name, stBDNCase.pcsSpecies3Name); strcat(pcsT3Name, " trapped");
	strcpy(pcsU1Name, stBDNCase.pcsSpecies1Name); strcat(pcsU1Name, " untrapped");
	strcpy(pcsU2Name, stBDNCase.pcsSpecies2Name); strcat(pcsU2Name, " untrapped");
	strcpy(pcsU3Name, stBDNCase.pcsSpecies3Name); strcat(pcsU3Name, " untrapped");
	leg_1->AddEntry(foT1, pcsT1Name);
	leg_1->AddEntry(foU1, pcsU1Name);
	leg_1->AddEntry(foT2, pcsT2Name);
	leg_1->AddEntry(foU2, pcsU2Name);
	leg_1->AddEntry(foT3, pcsT3Name);
	leg_1->AddEntry(foU3, pcsU3Name);
	leg_1->AddEntry(fyAll , "Fit function (all species)");
	leg_1->SetFillColor(0);
	leg_1->Draw();
	
	if (stBFitCase.bDoFit) {
		char int_T1[100]; char int_T2[100]; char int_T3[100]; char int_U1[100]; char int_U2[100]; char int_U3[100]; char int_All[100];
//		sprintf(int1,"T1 = %8.0f +/- %6.0f; U1 = %8.0f +/- %6.0f", T1_integral, T1_integral_error, U1_integral, U1_integral_error);
//		sprintf(int2,"T2 = %8.0f +/- %6.0f; U2 = %8.0f +/- %6.0f", T2_integral, T2_integral_error, U2_integral, U2_integral_error);
//		sprintf(int3,"T3 = %8.0f +/- %6.0f; U3 = %8.0f +/- %6.0f", T3_integral, T3_integral_error, U3_integral, U3_integral_error);
		sprintf(int_T1,"%8.0f +/- %6.0f", T1_integral, T1_integral_error);
		sprintf(int_U1,"%8.0f +/- %6.0f", U1_integral, U1_integral_error);
		sprintf(int_T2,"%8.0f +/- %6.0f", T2_integral, T2_integral_error);
		sprintf(int_U2,"%8.0f +/- %6.0f", U2_integral, U2_integral_error);
		sprintf(int_T3,"%8.0f +/- %6.0f", T3_integral, T3_integral_error);
		sprintf(int_U3,"%8.0f +/- %6.0f", U3_integral, U3_integral_error);
		sprintf(int_All,"%8.0f +/- %6.0f", All_integral, All_integral_error);
		TLegend *calc = new TLegend(0.13, 0.50, 0.32, 0.69);
		calc->AddEntry(foT1, int_T1);
		calc->AddEntry(foU1, int_U1);
		calc->AddEntry(foT2, int_T2);
		calc->AddEntry(foU2, int_U2);
		calc->AddEntry(foT3, int_T3);
		calc->AddEntry(foU3, int_U3);
		calc->AddEntry(fyAll, int_All);
		calc->SetTextSize(0.02);
		calc->SetFillColor(0);
		calc->Draw();
	} // end if (stBFitCase.bDoFit)
	
	gPad->Update();
	TPaveStats *stats_1 = (TPaveStats*)h1->FindObject("stats");
	stats_1->SetX1NDC(.32);
	stats_1->SetX2NDC(.55);
	stats_1->SetY1NDC(.69);
	stats_1->SetY2NDC(.94);
	gPad->Update();
	c_BFit->Modified();
	outfile->WriteTObject(c_BFit);
	outfile->WriteTObject(h1);
	
	if (stBFitCase.bMonteCarlo) {
		
		TH1D *h_DDC	= (TH1D*)f->Get("h_DDC_cyctime");
		TH1D *h_DT1	= (TH1D*)f->Get("h_DT1_cyctime");
		TH1D *h_DT2	= (TH1D*)f->Get("h_DT2_cyctime");
		TH1D *h_DT3	= (TH1D*)f->Get("h_DT3_cyctime");
		TH1D *h_DU1	= (TH1D*)f->Get("h_DU1_cyctime");
		TH1D *h_DU2	= (TH1D*)f->Get("h_DU2_cyctime");
		TH1D *h_DU3	= (TH1D*)f->Get("h_DU3_cyctime");
		
		h2->SetLineColor(kBlack);
		if (stBFitCase.bHasDDC) h_DDC->SetLineColor(kBlack);
		h_DT1->SetLineColor(kGreen);
		h_DU1->SetLineColor(kGreen);
		h_DT2->SetLineColor(kBlue);
		h_DU2->SetLineColor(kBlue);
		h_DT3->SetLineColor(kRed);
		h_DU3->SetLineColor(kRed);
		
		if (stBFitCase.bHasDDC) h_DDC->SetLineStyle(7);
		h_DU1->SetLineStyle(7);
		h_DU2->SetLineStyle(7);
		h_DU3->SetLineStyle(7);
		
		if (stBFitCase.bHasDDC) h_DDC->Rebin(dRebinFactor);
		h_DT1->Rebin(dRebinFactor);
		h_DT2->Rebin(dRebinFactor);
		h_DT3->Rebin(dRebinFactor);
		h_DU1->Rebin(dRebinFactor);
		h_DU2->Rebin(dRebinFactor);
		h_DU3->Rebin(dRebinFactor);
		
		fyT1->SetLineColor(kGreen);
		fyT2->SetLineColor(kBlue);
		fyT3->SetLineColor(kRed);
		fyU1->SetLineColor(kGreen);
		fyU2->SetLineColor(kBlue);
		fyU3->SetLineColor(kRed);
		
		fyU1->SetLineStyle(7);
		fyU2->SetLineStyle(7);
		fyU3->SetLineStyle(7);
		
		fyT1->SetNpx(nPoints);
		fyT2->SetNpx(nPoints);
		fyT3->SetNpx(nPoints);
		fyU1->SetNpx(nPoints);
		fyU2->SetNpx(nPoints);
		fyU3->SetNpx(nPoints);
		
		h2->GetYaxis()->SetRangeUser(0,yMax);
		h2->GetXaxis()->SetRangeUser(-1000,tCyc+1000);
		
		TCanvas *c_decays_cyctime = new TCanvas("c_decays_cyctime","Decays versus cycle time",945,600);
		h2->Draw();
		fyAll->Draw("SAME");
		if (stBFitCase.bHasDDC) fyDC->Draw("SAME");
		fyT1->Draw("SAME");
		fyT2->Draw("SAME");
		fyT3->Draw("SAME");
		fyU1->Draw("SAME");
		fyU2->Draw("SAME");
		fyU3->Draw("SAME");
		if (stBFitCase.bHasDDC) h_DDC->Draw("SAME");
		h_DT1->Draw("SAME");
		h_DT2->Draw("SAME");
		h_DT3->Draw("SAME");
		h_DU1->Draw("SAME");
		h_DU2->Draw("SAME");
		h_DU3->Draw("SAME");
		
		gPad->Update();
		TPaveStats *stats_2 = (TPaveStats*)h2->FindObject("stats");
		stats_2->SetX1NDC(.13);
		stats_2->SetX2NDC(.32);
		stats_2->SetY1NDC(.80);
		stats_2->SetY2NDC(.88);
		gPad->Update();
		c_decays_cyctime->Modified();
		outfile->WriteTObject(c_decays_cyctime);
		
		printf("T1 entries:    %10d\n",(Int_t)h_DT1->GetEntries());
		printf("U1 entries:    %10d\n",(Int_t)h_DU1->GetEntries());
		printf("T2 entries:    %10d\n",(Int_t)h_DT2->GetEntries());
		printf("U2 entries:    %10d\n",(Int_t)h_DU2->GetEntries());
		printf("T3 entries:    %10d\n",(Int_t)h_DT3->GetEntries());
		printf("U3 entries:    %10d\n",(Int_t)h_DU3->GetEntries());
		if (stBFitCase.bHasDDC) printf("DC entries:    %10d\n",(Int_t)h_DDC->GetEntries());
		printf("Total entries: %10d\n",(Int_t)h1->GetEntries());
		
		if (stBFitCase.bHasVWXY) { // used for Monte Carlo data where V, W, X, Y pops are known
			
			TH1D *h_DV1	= (TH1D*)f->Get("h_DV1_cyctime");
			TH1D *h_DV2	= (TH1D*)f->Get("h_DV2_cyctime");
			TH1D *h_DV3	= (TH1D*)f->Get("h_DV3_cyctime");
			TH1D *h_DW1	= (TH1D*)f->Get("h_DW1_cyctime");
			TH1D *h_DW2	= (TH1D*)f->Get("h_DW2_cyctime");
			TH1D *h_DW3	= (TH1D*)f->Get("h_DW3_cyctime");
			TH1D *h_DZ1	= (TH1D*)f->Get("h_DZ1_cyctime");
			TH1D *h_DZ2	= (TH1D*)f->Get("h_DZ2_cyctime");
			TH1D *h_DZ3	= (TH1D*)f->Get("h_DZ3_cyctime");
			TH1D *h_DX2	= (TH1D*)f->Get("h_DX2_cyctime");
			TH1D *h_DX3	= (TH1D*)f->Get("h_DX3_cyctime");
			TH1D *h_DY2	= (TH1D*)f->Get("h_DY2_cyctime");
			TH1D *h_DY3	= (TH1D*)f->Get("h_DY3_cyctime");
			
			HistPrep(h_DV1,dRebinFactor);
			HistPrep(h_DV2,dRebinFactor);
			HistPrep(h_DV3,dRebinFactor);
			HistPrep(h_DW1,dRebinFactor);
			HistPrep(h_DW2,dRebinFactor);
			HistPrep(h_DW3,dRebinFactor);
			HistPrep(h_DZ1,dRebinFactor);
			HistPrep(h_DZ2,dRebinFactor);
			HistPrep(h_DZ3,dRebinFactor);
			HistPrep(h_DX2,dRebinFactor);
			HistPrep(h_DX3,dRebinFactor);
			HistPrep(h_DY2,dRebinFactor);
			HistPrep(h_DY3,dRebinFactor);
			
/*			h_DV1 ->Rebin(dRebinFactor);
			h_DV2 ->Rebin(dRebinFactor);
			h_DV3 ->Rebin(dRebinFactor);
			h_DW1 ->Rebin(dRebinFactor);
			h_DW2 ->Rebin(dRebinFactor);
			h_DW3 ->Rebin(dRebinFactor);
			h_DZ1 ->Rebin(dRebinFactor);
			h_DZ2 ->Rebin(dRebinFactor);
			h_DZ3 ->Rebin(dRebinFactor);
			h_DX2 ->Rebin(dRebinFactor);
			h_DX3 ->Rebin(dRebinFactor);
			h_DY2 ->Rebin(dRebinFactor);
			h_DY3 ->Rebin(dRebinFactor);
			
			h_DV1->SetLineColor(kBlack);
			h_DV2->SetLineColor(kBlack);
			h_DV3->SetLineColor(kBlack);
			h_DX2->SetLineColor(kBlack);
			h_DY2->SetLineColor(kBlack);
			h_DX3->SetLineColor(kBlack);
			h_DY3->SetLineColor(kBlack);
*/			
//			h_DX2->SetLineStyle(8);
//			h_DY2->SetLineStyle(3);
//			h_DX3->SetLineStyle(8);
//			h_DY3->SetLineStyle(3);
			
			TH1D *h_DU2_1	= (TH1D*)h_DU2->Rebin(1,"h_DU2_1");
			TH1D *h_DU3_1	= (TH1D*)h_DU3->Rebin(1,"h_DU3_1");
			
			h_DU2_1->SetLineStyle(1);
			h_DU3_1->SetLineStyle(1);
			h_DU2_1->SetLineColor(kBlack);
			h_DU3_1->SetLineColor(kBlack);
			
			TF1 *fyV1	= new TF1("fyV1", yV1, 0.0, tCyc, nPars);
			TF1 *fyV2	= new TF1("fyV2", yV2, 0.0, tCyc, nPars);
			TF1 *fyV3	= new TF1("fyV3", yV3, 0.0, tCyc, nPars);
			TF1 *fyW1	= new TF1("fyW1", yW1, 0.0, tCyc, nPars);
			TF1 *fyW2	= new TF1("fyW2", yW2, 0.0, tCyc, nPars);
			TF1 *fyW3	= new TF1("fyW3", yW3, 0.0, tCyc, nPars);
			TF1 *fyZ1	= new TF1("fyZ1", yZ1, 0.0, tCyc, nPars);
			TF1 *fyZ2	= new TF1("fyZ2", yZ2, 0.0, tCyc, nPars);
			TF1 *fyZ3	= new TF1("fyZ3", yZ3, 0.0, tCyc, nPars);
			TF1 *fyX2	= new TF1("fyX2", yX2, 0.0, tCyc, nPars);
			TF1 *fyX3	= new TF1("fyX3", yX3, 0.0, tCyc, nPars);
			TF1 *fyY2	= new TF1("fyY2", yY2, 0.0, tCyc, nPars);
			TF1 *fyY3	= new TF1("fyY3", yY3, 0.0, tCyc, nPars);
			
			FuncPrep(fyV1,par,nPoints,kGreen);
			FuncPrep(fyV2,par,nPoints,kBlue);
			FuncPrep(fyV3,par,nPoints,kRed);
			FuncPrep(fyW1,par,nPoints,kGreen);
			FuncPrep(fyW2,par,nPoints,kBlue);
			FuncPrep(fyW3,par,nPoints,kRed);
			FuncPrep(fyZ1,par,nPoints,kGreen);
			FuncPrep(fyZ2,par,nPoints,kBlue);
			FuncPrep(fyZ3,par,nPoints,kRed);
			FuncPrep(fyX2,par,nPoints,kBlue);
			FuncPrep(fyX3,par,nPoints,kRed);
			FuncPrep(fyY2,par,nPoints,kBlue);
			FuncPrep(fyY3,par,nPoints,kRed);
/*			fyV1->SetParameters(par);
			fyV2->SetParameters(par);
			fyV3->SetParameters(par);
			fyW1->SetParameters(par);
			fyW2->SetParameters(par);
			fyW3->SetParameters(par);
			fyZ1->SetParameters(par);
			fyZ2->SetParameters(par);
			fyZ3->SetParameters(par);
			fyX2->SetParameters(par);
			fyX3->SetParameters(par);
			fyY2->SetParameters(par);
			fyY3->SetParameters(par);
			
			fyV1->SetNpx(nPoints);
			fyV2->SetNpx(nPoints);
			fyV3->SetNpx(nPoints);
			fyW1->SetNpx(nPoints);
			fyW2->SetNpx(nPoints);
			fyW3->SetNpx(nPoints);
			fyZ1->SetNpx(nPoints);
			fyZ2->SetNpx(nPoints);
			fyZ3->SetNpx(nPoints);
			fyX2->SetNpx(nPoints);
			fyX3->SetNpx(nPoints);
			fyY2->SetNpx(nPoints);
			fyY3->SetNpx(nPoints);
			
			fyV1->SetLineColor(kGreen);
			fyV2->SetLineColor(kBlue);
			fyV3->SetLineColor(kRed);
			fyW1->SetLineColor(kGreen);
			fyW2->SetLineColor(kBlue);
			fyW3->SetLineColor(kRed);
			fyZ1->SetLineColor(kGreen);
			fyZ2->SetLineColor(kBlue);
			fyZ3->SetLineColor(kRed);
			fyX2->SetLineColor(kBlue);
			fyX3->SetLineColor(kRed);
			fyY2->SetLineColor(kBlue);
			fyY3->SetLineColor(kRed);
*/			
			
			TCanvas *c_feeding = new TCanvas("c_feeding","Decays from pops X and Y versus cycle time",945,600);
			h1->Draw();
//			h_DU3_1->Draw("SAME");
//			fyU2->Draw("SAME");
//			fyU3->Draw("SAME");
			h_DV3->Draw("SAME");
			fyV3->Draw("SAME");
			h_DV1->Draw("SAME");
			h_DV2->Draw("SAME");
			fyV1->Draw("SAME");
			fyV2->Draw("SAME");
//			h_DX2->Draw("SAME");
//			h_DX3->Draw("SAME");
//			fyX2->Draw("SAME");
//			fyX3->Draw("SAME");
//			h_DY2->Draw("SAME");
//			h_DY3->Draw("SAME");
//			fyY2->Draw("SAME");
//			fyY3->Draw("SAME");
//			h_DU2_1->Draw("SAME");
			outfile->WriteTObject(c_feeding);
			
			TCanvas *c_Ti = new TCanvas("c_Ti","Decays from T pops versus cycle time",945,600);
//			h1->Draw();
//			fyT2->Draw();
			fyT2->Draw();
			fyT3->Draw("SAME");
			fyT1->Draw("SAME");
			h_DT1->Draw("SAME");
			h_DT2->Draw("SAME");
			h_DT3->Draw("SAME");
			outfile->WriteTObject(c_Ti);
			
			TCanvas *c_Vi = new TCanvas("c_Vi","Decays from V pops versus cycle time",945,600);
//			h1->Draw();
//			fyV2->Draw();
			fyV2->Draw();
			fyV3->Draw("SAME");
			fyV1->Draw("SAME");
			h_DV1->Draw("SAME");
			h_DV2->Draw("SAME");
			h_DV3->Draw("SAME");
			outfile->WriteTObject(c_Vi);
			
			TCanvas *c_Wi = new TCanvas("c_Wi","Decays from W pops versus cycle time",945,600);
//			h1->Draw();
			fyW2->Draw();
			fyW3->Draw("SAME");
			fyW1->Draw("SAME");
			h_DW1->Draw("SAME");
			h_DW2->Draw("SAME");
			h_DW3->Draw("SAME");
			outfile->WriteTObject(c_Wi);
			
			TCanvas *c_Zi = new TCanvas("c_Zi","Decays from Z pops versus cycle time",945,600);
//			h1->Draw();
			fyZ2->Draw();
			fyZ3->Draw("SAME");
			fyZ1->Draw("SAME");
			h_DZ1->Draw("SAME");
			h_DZ2->Draw("SAME");
			h_DZ3->Draw("SAME");
			outfile->WriteTObject(c_Zi);
			
			TCanvas *c_Xi = new TCanvas("c_Xi","Decays from X pops versus cycle time",945,600);
//			h1->Draw();
			fyX3->Draw();
			fyX2->Draw("SAME");
			h_DX2->Draw("SAME");
			h_DX3->Draw("SAME");
			outfile->WriteTObject(c_Xi);
			
			TCanvas *c_Yi = new TCanvas("c_Yi","Decays from Y pops versus cycle time",945,600);
//			h1->Draw();
			fyY3->Draw();
			fyY2->Draw("SAME");
			h_DY2->Draw("SAME");
			h_DY3->Draw("SAME");
			outfile->WriteTObject(c_Yi);
			
		} // end if (has_VWXY == 1)
		
	} // end if (draw_monte_carlo == 1)
	
//	TFile *outfile = new TFile("BFit.root","recreate");
//	outfile->WriteTObject(c_BFit);
//	if (stBFitCase.bMonteCarlo)	outfile->WriteTObject(c_decays_cyctime);
//	if (stBFitCase.bHasVXWY)	outfile->WriteTObject(c_feeding);
	outfile->Close();
	
	timerStop = clock();
	cout << "BFit done. Timer = " << (Float_t)timerStop/CLOCKS_PER_SEC << " sec." << endl;
	cout << "Elapsed time = " << (Float_t)(timerStop-timerStart)/CLOCKS_PER_SEC << " sec." << endl << endl;
	
	return iReturn;
}

void HistPrep (TH1 *h, Int_t rebin) {
	h->Rebin(rebin);
	h->SetLineColor(kBlack);
}

void FuncPrep (TF1 *f, Double_t *pars, Int_t nPoints, Int_t color) {
	f->SetParameters(pars);
	f->SetNpx(nPoints);
	f->SetLineColor(color);
}

//int find_struct_index (void *p, char* pcsSearchString, int numStructs, int struct_size ) {
//	// We use a dirty trick here!
//	// We tell the co
//	int struct_index = 0;
//	for (struct_index = 0; struct_index < numStructs; struct_index++ )
//	{
//		printf("%s\n",(char*)p);
//		
//		if (strcmp((char*)p, pcsSearchString) == 0) break; // treat struct as char to get casecode of any struct
//		// pcsCaseCode must be the first member of the struct!!
//		//printf("%d",struct_index);
//		p += struct_size;
//	}
//	if (struct_index == numStructs)
//	{
//		cout << "No match found for case code entered. Execute the program like this:" << endl;
//		cout << "'$ ./PROGRAM <BDN case code>" << endl << endl;
//		return 0;
//	}
//	return struct_index;
//}

//////////////////////////////////////////////////////////////////////////////////////////////
//	B_stBFitCase_t *m;
//	stBDNCase_index = 0;
//	for (m = stBDNCases; stBDNCase_index < iNumStructs_bdn; ++m, ++stBDNCase_index )
//	{
//		if (strcmp(m->pcsCaseCode, argv[2]) == 0) break;
//		printf("%d",stBDNCase_index);		
//	}
//	if (stBDNCase_index == iNumStructs_bdn)
//	{
//		cout << "No match found for casecode entered. Execute the program like this:" << endl;
//		cout << "'$ ./PROGRAM 137i07' for 137-I run 7" << endl << endl;
//		return 0;
//	}
///////////////////////////////////////////////////////////////////////////////////////////////
//	stBDNCase_t *m;
//	for (m = stBDNCases, gdx = 0; m->code != 0 && strcmp(m->code, argv[1]) != 0; ++m, ++gdx);
//	if (m->code == 0) {
//		cout << "No match found for casecode entered. Execute the program like this:" << endl;
//		cout << "'$ ./PROGRAM 137i07' for 137-I run 7" << endl << endl;
//		return 0;
//	}
//	B_fit(m->code, gdx);
//	return 0;
///////////////////////////////////////////////////////////////////////////////////////////////
