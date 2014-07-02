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
#include "CSVtoStruct.h"
#include "BFitModel.h"
using namespace std;

// Global variables
BDNCase_t	stBDNCases[FILE_ROWS_BDN];
BFitCase_t	stBFitCases[FILE_ROWS_BFit];
int		iBDNCaseIndex, iBFitCaseIndex; // global index to identify case
int		iNumStructs_BDN, iNumStructs_BFit;

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
	cout << "Imported " << iNumStructs_BFit << " B_fit cases" << endl;
	iBDNCaseIndex  = FindStructIndex ( stBDNCases,  sizeof(BDNCase_t),  iNumStructs_BDN,  argv[1] );
	iBFitCaseIndex = FindStructIndex ( stBFitCases, sizeof(BFitCase_t), iNumStructs_BFit, argv[2] );
	if ( iBDNCaseIndex == -1 || iBFitCaseIndex == -1 )
	{ // One of the read-ins failed and already printed a message about it
		cout << "How to run this program:" << endl;
		cout << "'./B_fit <BDN case code> <B_fit case code>'" << endl;
		cout << "where valid case codes are listed in the CSV files." << endl << endl;
		return -1; // error return
	}
	cout << "Performing BFit with BDN case " << stBDNCases[iBDNCaseIndex].pcsCaseCode << " and BFit case " << stBFitCases[iBFitCaseIndex].pcsCaseCode << endl << endl;
	return BFit(); // return status of BFit
}

int BFit () {
	
	cout << "BFit started." << endl;
	int iReturn = SUCCESS;
	using namespace BFitNamespace;
	using namespace TMath;
	TFile *outfile = new TFile("BFit.root","recreate");
	
// Local copies of the relevant metadata structs
	BDNCase_t  stBDNCase = stBDNCases[iBDNCaseIndex];
	BFitCase_t stBFitCase = stBFitCases[iBFitCaseIndex];
	//printf("Bdn Case index = %d, BFit case index = %d\n", iBDNCaseIndex, iBFitCaseIndex);
	
///////////////////////////////////////////////////////////////////////////////////////////////
// Ad-hoc modifications of parameters, for rapid iteration
// Include final values in the CSV files
///////////////////////////////////////////////////////////////////////////////////////////////
//	stBFitCase.pbToggle[dt = 500;
//	stBFitCase. = 0;
//	stBFitCase.pdSeed[dt] = 500;
//	stBFitCase.iBinWidth = 500;
	
	TString separator = "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
	cout << endl << separator << endl;
	cout << "BETA SINGLES MODEL" << endl << separator << endl;
	cout << "Case: " << stBDNCase.pcsCaseCode << endl;
	cout << "File: " << stBDNCase.pcsFilePath << endl;
	cout << "Histogram: " << stBFitCase.pcsHistName << endl;
	printf("Total cycle time\t= %10.3f s\n",stBDNCase.dCycleTime);
	printf("Background time\t\t= %10.3f s\n",stBDNCase.dBackgroundTime);
	printf("Capture cycle time\t= %10.3f s\n",stBDNCase.dCaptureTime);
	printf("Last capture time\t= %10.3f s\n",stBDNCase.dLastCaptureTime);
	cout << stBDNCase.pcsSpecies1Name; printf(" halflife\t\t= %10.3f s  (lifetime %10.3f s)\n", stBDNCase.dHalfLife1[0], stBDNCase.dLifetime1[0]);
	cout << stBDNCase.pcsSpecies2Name; printf(" halflife\t\t= %10.3f s  (lifetime %10.3f s)\n", stBDNCase.dHalfLife2[0], stBDNCase.dLifetime2[0]);
	cout << stBDNCase.pcsSpecies3Name; printf(" halflife\t\t= %10.3f s  (lifetime %10.3f s)\n", stBDNCase.dHalfLife3[0], stBDNCase.dLifetime3[0]);
	cout << separator << endl;
	if (stBFitCase.bDoFit) cout << "Doing fit with option string: " << stBFitCase.pcsOptions << endl;
	else cout << "Not fitting! Drawing functions using parameter seed values." << endl;
	cout << separator << endl;
	
// Get histogram from ROOT file
	TFile *f = new TFile(stBDNCase.pcsFilePath);
	TH1D *h	= (TH1D*)f->Get(stBFitCase.pcsHistName);
	Double_t dRebinFactor = stBFitCase.iBinWidth/(h->GetBinWidth(1));
	TH1D *h1	= (TH1D*)h->Rebin(dRebinFactor,stBFitCase.pcsHistName);
	TH1D *h2	= (TH1D*)h->Rebin(dRebinFactor,stBFitCase.pcsHistName);
	
// Initial parameter values and initial step sizes
// err contains initial step sizes now, will contain error estimates later.
	Int_t nPars = stBFitCase.iNPars;
	Int_t *tog;
	Double_t *par;//[nPars];
	Double_t *err;//[nPars];
	tog = stBFitCase.pbToggle;
	par = stBFitCase.pdSeed;
	err = stBFitCase.pdStep;
	Int_t index;
//	for (index = 0; index < nPars; index++) {
//	//	cout << stBFitCase.seed[index] << "+/-" << stBFitCase.step[index] << endl;
//		par[index] = stBFitCase.pdSeed[index];
//		err[index] = stBFitCase.pdStep[index];
//	}
// Species populations
	TF1 *fyDC	= new TF1("fyDC", yDC, 0.0, stBDNCase.dCycleTime, nPars);
	TF1 *fyT1	= new TF1("fyT1", yT1, 0.0, stBDNCase.dCycleTime, nPars);
	TF1 *fyT2	= new TF1("fyT2", yT2, 0.0, stBDNCase.dCycleTime, nPars);
	TF1 *fyT3	= new TF1("fyT3", yT3, 0.0, stBDNCase.dCycleTime, nPars);
	TF1 *fyU1	= new TF1("fyU1", yU1, 0.0, stBDNCase.dCycleTime, nPars);
	TF1 *fyU2	= new TF1("fyU2", yU2, 0.0, stBDNCase.dCycleTime, nPars);
	TF1 *fyU3	= new TF1("fyU3", yU3, 0.0, stBDNCase.dCycleTime, nPars);
	TF1 *fyAll	= new TF1("fyAll",yAll, 0.0, stBDNCase.dCycleTime, nPars); // This one fits the data!
// Beta rates to be used by TF1::Integral() and TF1::IntegralError()
	TF1 *frDC	= new TF1("frDC", rDC, 0.0, stBDNCase.dCycleTime, nPars);
	TF1 *frT1	= new TF1("frT1", rT1, 0.0, stBDNCase.dCycleTime, nPars);
	TF1 *frT2	= new TF1("frT2", rT2, 0.0, stBDNCase.dCycleTime, nPars);
	TF1 *frT3	= new TF1("frT3", rT3, 0.0, stBDNCase.dCycleTime, nPars);
	TF1 *frU1	= new TF1("frU1", rU1, 0.0, stBDNCase.dCycleTime, nPars);
	TF1 *frU2	= new TF1("frU2", rU2, 0.0, stBDNCase.dCycleTime, nPars);
	TF1 *frU3	= new TF1("frU3", rU3, 0.0, stBDNCase.dCycleTime, nPars);
	TF1 *frAll	= new TF1("frAll",rAll, 0.0, stBDNCase.dCycleTime, nPars);
// Offset functions for plotting
	TF1 *foT1	= new TF1("foT1", oT1, 0.0, stBDNCase.dCycleTime, nPars);
	TF1 *foT2	= new TF1("foT2", oT2, 0.0, stBDNCase.dCycleTime, nPars);
	TF1 *foT3	= new TF1("foT3", oT3, 0.0, stBDNCase.dCycleTime, nPars);
	TF1 *foU1	= new TF1("foU1", oU1, 0.0, stBDNCase.dCycleTime, nPars);
	TF1 *foU2	= new TF1("foU2", oU2, 0.0, stBDNCase.dCycleTime, nPars);
	TF1 *foU3	= new TF1("foU3", oU3, 0.0, stBDNCase.dCycleTime, nPars);
// Initiailize function to fit the data
	char pcsLifetime1ParName[100]; sprintf(pcsLifetime1ParName,"%s radioactive lifetime (1/e)", stBDNCase.pcsSpecies1Name);
	char pcsLifetime2ParName[100]; sprintf(pcsLifetime2ParName,"%s radioactive lifetime (1/e)", stBDNCase.pcsSpecies2Name);
	char pcsLifetime3ParName[100]; sprintf(pcsLifetime3ParName,"%s radioactive lifetime (1/e)", stBDNCase.pcsSpecies3Name);
	fyAll->SetParName(DC,"DC rate");
	fyAll->SetParName(r1,"Rate 1");
	fyAll->SetParName(r2,"Rate 2");
	fyAll->SetParName(r3,"Rate 3");
	fyAll->SetParName(p,"Capture eff");
	fyAll->SetParName(rho,"Capture ret");
	fyAll->SetParName(epsT,"T det eff");
	fyAll->SetParName(epsU,"U det eff");
	fyAll->SetParName(epsV,"V det eff");
	fyAll->SetParName(epsW,"W det eff");
	fyAll->SetParName(epsX,"X det eff");
	fyAll->SetParName(epsY,"Y det eff");
	fyAll->SetParName(tau1,pcsLifetime1ParName);//"Lifetime 1");//pcsSpecies1ParName);
	fyAll->SetParName(tau2,pcsLifetime2ParName);//"Lifetime 2");//pcsSpecies2ParName);
	fyAll->SetParName(tau3,pcsLifetime3ParName);//"Lifetime 3");//pcsSpecies3ParName);
	fyAll->SetParName(tauT1,"T1 lifetime");
	fyAll->SetParName(tauT2,"T2 lifetime");
	fyAll->SetParName(tauT3,"T3 lifetime");
	fyAll->SetParName(tauU1,"U1 lifetime");
	fyAll->SetParName(tauU2,"U2 lifetime");
	fyAll->SetParName(tauU3,"U3 lifetime");
	fyAll->SetParName(dt,"Bin width");
	fyAll->SetParameters(par);
	fyAll->SetParErrors(err);
	
// Print seed values that are assigned to the fit function
	cout << "PARAMETER SEED VALUES" << endl << separator << endl;
	cout << setw(34) << "Par name" << setw(10) << "Varying?" << "\t" << "Par init val and step" << endl << separator << endl;
	for (index = 0; index < nPars; index++) {
		cout << setw(34) << fyAll->GetParName(index) << setw(10) << tog[index] << "\t" << fyAll->GetParameter(index) << " +/- " << fyAll->GetParError(index) << endl;
	}
	cout << separator << endl << endl;
	
// Initialize all functions to parameter seed values
	for (index = 0; index < nPars; index++) {
		fyDC	-> SetParameters(par);
		fyT1	-> SetParameters(par);
		fyT2	-> SetParameters(par);
		fyT3	-> SetParameters(par);
		fyU1	-> SetParameters(par);
		fyU2	-> SetParameters(par);
		fyU3	-> SetParameters(par);
		fyAll	-> SetParameters(par);
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
	}
	
	if (stBFitCase.bDoFit) {
	// Fix the parameters that are supposed to be fixed
		for (index = 0; index < nPars; index++) {
			if (tog[index] == 0) fyAll->FixParameter(index, stBFitCase.pdSeed[index]);
		}
	// Do fit and get results
		TFitResultPtr fit = h1->Fit("fyAll",stBFitCase.pcsOptions);
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
		T1_integral = frT1->Integral( 0.0, stBDNCase.dCycleTime);
		T2_integral = frT2->Integral( 0.0, stBDNCase.dCycleTime);
		T3_integral = frT3->Integral( 0.0, stBDNCase.dCycleTime);
		U1_integral = frU1->Integral( 0.0, stBDNCase.dCycleTime);
		U2_integral = frU2->Integral( 0.0, stBDNCase.dCycleTime);
		U3_integral = frU3->Integral( 0.0, stBDNCase.dCycleTime);
		DC_integral = frDC->Integral( 0.0, stBDNCase.dCycleTime);
		All_integral = frAll->Integral( 0.0, stBDNCase.dCycleTime);
		
		Integral_sum = DC_integral + T1_integral + T2_integral + T3_integral + U1_integral + U2_integral + U3_integral;
		
		T1_integral_error = frT1->IntegralError( 0.0, stBDNCase.dCycleTime, par, cov.GetMatrixArray() );
		T2_integral_error = frT2->IntegralError( 0.0, stBDNCase.dCycleTime, par, cov.GetMatrixArray() );
		T3_integral_error = frT3->IntegralError( 0.0, stBDNCase.dCycleTime, par, cov.GetMatrixArray() );
		U1_integral_error = frU1->IntegralError( 0.0, stBDNCase.dCycleTime, par, cov.GetMatrixArray() );
		U2_integral_error = frU2->IntegralError( 0.0, stBDNCase.dCycleTime, par, cov.GetMatrixArray() );
		U3_integral_error = frU3->IntegralError( 0.0, stBDNCase.dCycleTime, par, cov.GetMatrixArray() );
		DC_integral_error = frDC->IntegralError( 0.0, stBDNCase.dCycleTime, par, cov.GetMatrixArray() );
		All_integral_error = frAll->IntegralError( 0.0, stBDNCase.dCycleTime, par, cov.GetMatrixArray() );
		
		Integral_sum_error = Sqrt( Power(DC_integral_error,2.0) + Power(T1_integral_error,2.0) + Power(T2_integral_error,2.0) + Power(T3_integral_error,2.0) + Power(U1_integral_error,2.0) + Power(U2_integral_error,2.0) + Power(U3_integral_error,2.0) );
		
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
		cout << separator << endl << endl;
		
	} // end if (stBFitCase.bDoFit)
	
// Draw
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
	
	Double_t nPoints = stBDNCase.dCycleTime;
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
	Double_t yMin = par[DC]*par[dt];
	Double_t yMax = h1->GetMaximum();
	Double_t yRange = yMax - yMin;
	yMin = yMin - 0.05*yRange;
	yMax = yMax + 0.05*yRange;
	//printf("Range = (%f,%f)\n", yMin, yMax);
	h1->GetYaxis()->SetRangeUser(yMin,yMax);
//	h2->GetYaxis()->SetRangeUser(yMin,yMax);
	h1->GetXaxis()->SetRangeUser(-1000,stBDNCase.dCycleTime+1000);
//	h2->GetXaxis()->SetRangeUser(-1000,stBDNCase.dCycleTime+1000);
	
	TLegend *leg_1 = new TLegend(0.13, 0.69, 0.32, 0.94);
	leg_1->AddEntry(h1 , "Data");
	leg_1->AddEntry(fyDC, "DC");
//	leg_1->AddEntry(foT1, stBDNCase.pcsSpecies1Name + " trapped");
//	leg_1->AddEntry(foU1, stBDNCase.pcsSpecies1Name + " untrapped");
//	leg_1->AddEntry(foT2, stBDNCase.pcsSpecies2Name + " trapped");
//	leg_1->AddEntry(foU2, stBDNCase.pcsSpecies2Name + " untrapped");
//	leg_1->AddEntry(foT3, stBDNCase.pcsSpecies3Name + " trapped");
//	leg_1->AddEntry(foU3, stBDNCase.pcsSpecies3Name + " untrapped");
	leg_1->AddEntry(foT1, strcat(stBDNCase.pcsSpecies1Name, " trapped"));
	leg_1->AddEntry(foU1, strcat(stBDNCase.pcsSpecies1Name, " untrapped"));
	leg_1->AddEntry(foT2, strcat(stBDNCase.pcsSpecies2Name, " trapped"));
	leg_1->AddEntry(foU2, strcat(stBDNCase.pcsSpecies2Name, " untrapped"));
	leg_1->AddEntry(foT3, strcat(stBDNCase.pcsSpecies3Name, " trapped"));
	leg_1->AddEntry(foU3, strcat(stBDNCase.pcsSpecies3Name, " untrapped"));
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
		h2->GetXaxis()->SetRangeUser(-1000,stBDNCase.dCycleTime+1000);
		
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
		
		if (stBFitCase.bHasVWXY) { // X and Y pops	
			
			TH1D *h_DV1	= (TH1D*)f->Get("h_DV1_cyctime");
			TH1D *h_DV2	= (TH1D*)f->Get("h_DV2_cyctime");
			TH1D *h_DV3	= (TH1D*)f->Get("h_DV3_cyctime");
			TH1D *h_DX2	= (TH1D*)f->Get("h_DX2_cyctime");
			TH1D *h_DX3	= (TH1D*)f->Get("h_DX3_cyctime");
			TH1D *h_DY2	= (TH1D*)f->Get("h_DY2_cyctime");
			TH1D *h_DY3	= (TH1D*)f->Get("h_DY3_cyctime");
			
			h_DV1 ->Rebin(dRebinFactor);
			h_DV2 ->Rebin(dRebinFactor);
			h_DV3 ->Rebin(dRebinFactor);
			h_DX2 ->Rebin(dRebinFactor);
			h_DX3 ->Rebin(dRebinFactor);
			h_DY2 ->Rebin(dRebinFactor);
			h_DY3 ->Rebin(dRebinFactor);
			
			h_DV1->SetLineColor(kBlack);
//			h_DX2->SetLineStyle(8);
//			h_DY2->SetLineStyle(3);
			h_DV2->SetLineColor(kBlack);
			h_DX2->SetLineColor(kBlack);
			h_DY2->SetLineColor(kBlack);
//			h_DX3->SetLineStyle(8);
//			h_DY3->SetLineStyle(3);
			h_DV3->SetLineColor(kBlack);
			h_DX3->SetLineColor(kBlack);
			h_DY3->SetLineColor(kBlack);
			
			TH1D *h_DU2_1	= (TH1D*)h_DU2->Rebin(dRebinFactor,"h_DU2_1");
			TH1D *h_DU3_1	= (TH1D*)h_DU3->Rebin(dRebinFactor,"h_DU3_1");
			
			h_DU2_1->SetLineStyle(1);
			h_DU3_1->SetLineStyle(1);
			h_DU2_1->SetLineColor(kBlack);
			h_DU3_1->SetLineColor(kBlack);
			
			TF1 *fyV1	= new TF1("fyV1", yV1, 0.0, stBDNCase.dCycleTime, nPars);
			TF1 *fyV2	= new TF1("fyV2", yV2, 0.0, stBDNCase.dCycleTime, nPars);
			TF1 *fyV3	= new TF1("fyV3", yV3, 0.0, stBDNCase.dCycleTime, nPars);
			TF1 *fyX2	= new TF1("fyX2", yX2, 0.0, stBDNCase.dCycleTime, nPars);
			TF1 *fyX3	= new TF1("fyX3", yX3, 0.0, stBDNCase.dCycleTime, nPars);
			TF1 *fyY2	= new TF1("fyY2", yY2, 0.0, stBDNCase.dCycleTime, nPars);
			TF1 *fyY3	= new TF1("fyY3", yY3, 0.0, stBDNCase.dCycleTime, nPars);
			
			fyV1->SetParameters(par);
			fyV2->SetParameters(par);
			fyV3->SetParameters(par);
			fyV1->SetNpx(nPoints);
			fyV2->SetNpx(nPoints);
			fyV3->SetNpx(nPoints);
			fyX2->SetParameters(par);
			fyX3->SetParameters(par);
			fyX2->SetNpx(nPoints);
			fyX3->SetNpx(nPoints);
			fyY2->SetParameters(par);
			fyY3->SetParameters(par);
			fyY2->SetNpx(nPoints);
			fyY3->SetNpx(nPoints);
			
			fyV1->SetLineColor(kGreen);
			fyV2->SetLineColor(kBlue);
			fyX2->SetLineColor(kBlue);
			fyY2->SetLineColor(kBlue);
			fyV3->SetLineColor(kRed);
			fyX3->SetLineColor(kRed);
			fyY3->SetLineColor(kRed);
			
			TCanvas *c_feeding = new TCanvas("c_feeding","Decays from pops X and Y versus cycle time",945,600);
			h_DU3_1->Draw();
//			fyU2->Draw("SAME");
//			fyU3->Draw("SAME");
//			fyV3->Draw("SAME");
//			h_DV1->Draw("SAME");
//			h_DV2->Draw("SAME");
//			fyV1->Draw("SAME");
//			fyV2->Draw("SAME");
//			h_DV3->Draw("SAME");
//			h_DX2->Draw("SAME");
//			h_DX3->Draw("SAME");
//			fyX2->Draw("SAME");
//			fyX3->Draw("SAME");
			h_DY2->Draw("SAME");
			h_DY3->Draw("SAME");
			fyY2->Draw("SAME");
			fyY3->Draw("SAME");
//			h_DU2_1->Draw("SAME");
			outfile->WriteTObject(c_feeding);
			
		} // end if (has_VWXY == 1)
		
	} // end if (draw_monte_carlo == 1)
	
//	TFile *outfile = new TFile("BFit.root","recreate");
//	outfile->WriteTObject(c_BFit);
//	if (stBFitCase.bMonteCarlo)	outfile->WriteTObject(c_decays_cyctime);
//	if (stBFitCase.bHasVXWY)	outfile->WriteTObject(c_feeding);
	outfile->Close();
	
	
	
	cout << "BFit done." << endl;
	
	return iReturn;
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
