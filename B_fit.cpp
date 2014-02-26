/*
2013-12-07 Shane Caldwell
	Made from fit_beta_singles.cxx.
	Will modify as necessary to validate against B_monte_carlo output.

*/

#include <iostream>
#include <iomanip>
#include <cstring>
#include "TROOT.h"
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
#include "B_fit_model.h"
#include "bdn_cases.h"

//using namespace casecodes;

//bdn_case_t get_case_data(char*);

//void B_fit (char* case_code) {
void B_fit () {
	
//	using namespace std;
	using namespace TMath;
	using namespace bdn_casecodes;
	using namespace B_fit_model;
	
///////////////////////////////////////////////////////////////////////////////////
// Want to define these structured data in other source files
// Haven't gotten it to work yet
///////////////////////////////////////////////////////////////////////////////////
	
	static bdn_case_t bdn_case;
	
//	bdn_case.file		= "B_monte_carlo_nofeeding_3_highstats.root";
//	bdn_case.file		= "B_monte_carlo_nofeeding_4.root";
//	bdn_case.file		= "B_monte_carlo_nofeeding_noXe_lifetime_1.root";
//	bdn_case.file		= "B_monte_carlo_nofeeding_5.root";
//	bdn_case.file		= "B_monte_carlo_nofeeding_3_medstats.root";
//	bdn_case.file		= "B_monte_carlo_alltrapped_1_highstats.root";
//	bdn_case.file		= "B_monte_carlo_efftrap050_1_highstats.root";
//	bdn_case.file		= "B_monte_carlo_efftrap050_1_highstats_bigTstep500.root";
//	bdn_case.file		= "B_monte_carlo_feeding.root";
//	bdn_case.file		= "B_monte_carlo_feeding_highstats.root";
//	bdn_case.file		= "B_monte_carlo_feeding_veryhighstats.root";
//	bdn_case.file		= "B_monte_carlo_feeding_veryhighstats_3.root";
	bdn_case.file		= "B_monte_carlo_feeding_lifetime_1.root";
//	bdn_case.file		= "B_monte_carlo_feeding_lifetime_smallstep_1.root";
	
	bdn_case.code		= "MonteCarlo";
	bdn_case.species1	= "137-Te";
	bdn_case.species2	= "137-I ";
	bdn_case.species3	= "137-Xe";
// Timing constants describing the experiment, in ms
	bdn_case.T_capt		= 5000.0; // APT cycle time
	bdn_case.T_last		= 1000.0; // time between BPT last capt and BPT ejection
	bdn_case.T_bkgd		= 101000.0;// + Ta - Tf; // duration of background measurement
	bdn_case.T_cycle	= 246000.0; // BPT cycle time (background + trapping)
// Physical constants
	const Double_t ln2= 0.69314718056;
	bdn_case.halflife1 = {        1000.0 * 2.49,         1000.0 * 0.05		};
	bdn_case.halflife2 = {        1000.0 * 24.5,         1000.0 * 0.2		};
	bdn_case.halflife3 = { 60.0 * 1000.0 * 3.818, 60.0 * 1000.0 * 0.013		};
	bdn_case.lifetime1 = { bdn_case.halflife1[0]/ln2, bdn_case.halflife1[1]/ln2};
	bdn_case.lifetime2 = { bdn_case.halflife2[0]/ln2, bdn_case.halflife2[1]/ln2};
	bdn_case.lifetime3 = { bdn_case.halflife3[0]/ln2, bdn_case.halflife3[1]/ln2};
	
	Bool_t draw_monte_carlo = 1;
	Bool_t has_DDC = 1;
	Bool_t has_VWXY = 1;
	
	static B_fit_case_t fit_case;
	
	fit_case.histname		= "h_D_cyctime";
	fit_case.bin_width		= 500; // ms
// Parameter switches; kTrue = parameter varies; kFalse = parameter is fixed to _seed value
    fit_case.toggle[DC]		= 0;
	fit_case.toggle[r1]		= 0;
	fit_case.toggle[r2]		= 0;
	fit_case.toggle[r3]		= 0;
	fit_case.toggle[p]		= 1;
	fit_case.toggle[l]		= 0;
	fit_case.toggle[epsT]	= 0;
	fit_case.toggle[epsU]	= 0;
	fit_case.toggle[epsV]	= 0;
	fit_case.toggle[epsW]	= 0;
	fit_case.toggle[epsX]	= 0;
	fit_case.toggle[epsY]	= 1;
	fit_case.toggle[tauT1]	= 0;
	fit_case.toggle[tauT2]	= 0;
	fit_case.toggle[tauT3]	= 0;
	fit_case.toggle[tauU1]	= 0;
	fit_case.toggle[tauU2]	= 0;
	fit_case.toggle[tauU3]	= 0;
	fit_case.toggle[dt]		= 0;
// Initial parameter values
    fit_case.seed[DC]		= 10000.0 * 0.040;
	fit_case.seed[r1]		= 10000.0 * 0.024;
	fit_case.seed[r2]		= 10000.0 * 0.120;
	fit_case.seed[r3]		= 0*100.0 * 0.080;
	fit_case.seed[p]		= 0.75;
	fit_case.seed[l]		= 1.0;
	fit_case.seed[epsT]		= 1.0;
	fit_case.seed[epsU]		= 1.0;
	fit_case.seed[epsV]		= 1.0;
	fit_case.seed[epsW]		= 1.0;
	fit_case.seed[epsX]		= 1.0;
	fit_case.seed[epsY]		= 1.5;
	fit_case.seed[tauT1]	= 1.0 / ( 1.0/bdn_case.lifetime1[0] + 1.0/15000.0 );//bdn_case.lifetime1[0];
	fit_case.seed[tauT2]	= 1.0 / ( 1.0/bdn_case.lifetime2[0] + 1.0/15000.0 );//bdn_case.lifetime2[0];
	fit_case.seed[tauT3]	= 1.0 / ( 1.0/bdn_case.lifetime3[0] + 1.0/15000.0 );//bdn_case.lifetime3[0];
	fit_case.seed[tauU1]	= bdn_case.lifetime1[0];
	fit_case.seed[tauU2]	= bdn_case.lifetime2[0];
	fit_case.seed[tauU3]	= bdn_case.lifetime3[0];
	fit_case.seed[dt]		= fit_case.bin_width;
// Initial parameter step sizes
	fit_case.step[DC]		= 0.1;
	fit_case.step[r1]		= 0.1;
	fit_case.step[r2]		= 0.1;
	fit_case.step[r3]		= 0.1;
	fit_case.step[p]		= 0.02;
	fit_case.step[l]		= 0.02;
	fit_case.step[epsT]		= 0.02;
	fit_case.step[epsU]		= 0.02;
	fit_case.step[epsV]		= 0.02;
	fit_case.step[epsW]		= 0.02;
	fit_case.step[epsX]		= 0.02;
	fit_case.step[epsY]		= 0.02;
	fit_case.step[tauT1]	= 100.0;
	fit_case.step[tauT2]	= 100.0;
	fit_case.step[tauT3]	= 100.0;
	fit_case.step[tauU1]	= 100.0;
	fit_case.step[tauU2]	= 100.0;
	fit_case.step[tauU3]	= 100.0;
	fit_case.step[dt]		= 0.0000000001;
// Fitting options
	fit_case.options		= "QIR0MESLL";
	fit_case.do_fit			= 0;
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

//	extern bdn_case_t bdn_case[2];
//	extern bdn_case_t bdn_case;
	
//	bdn_cases();
	
//	bdn_case_t bdn_case = get_case_data(case_code);
//	bdn_case_t bdn_case = bdn_case;//get_case_data(case_code);
//	bdn_case_t bdn_case = bdn_case[rc137i07];

//	printf("\n");
//	printf("Hello. Here is your case data:\n");
////	printf("Case code: %s\n",bdn_case[0].code);
//	printf("Case code: %s\n",bdn_case.code);
////	printf("Species 2 lifetime = %8.3f s  (half-life %8.3f s)\n",(*bdn_case.lifetime2[0],bdn_case.halflife2[0]);
//	printf("\n");
	
	TString separator = "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
	std::cout << endl << separator << endl;
	std::cout << "BETA SINGLES MODEL" << endl << separator << endl;
	std::cout << "Case: " << bdn_case.code << endl;
	std::cout << "File: " << bdn_case.file << endl;
	std::cout << "Histogram: " << fit_case.histname << endl;
	printf("Total cycle time\t= %9.3f s\n",bdn_case.T_cycle/1000.0);
	printf("Background time\t\t= %9.3f s\n",bdn_case.T_bkgd/1000.0);
	printf("Capture cycle time\t= %9.3f s\n",bdn_case.T_capt/1000.0);
	std::cout << bdn_case.species1; printf(" halflife\t\t= %9.3f s  (lifetime %9.3f s)\n",bdn_case.halflife1[0]/1000.0,bdn_case.lifetime1[0]/1000.0);
	std::cout << bdn_case.species2; printf(" halflife\t\t= %9.3f s  (lifetime %9.3f s)\n",bdn_case.halflife2[0]/1000.0,bdn_case.lifetime2[0]/1000.0);
	std::cout << bdn_case.species3; printf(" halflife\t\t= %9.3f s  (lifetime %9.3f s)\n",bdn_case.halflife3[0]/1000.0,bdn_case.lifetime3[0]/1000.0);
	std::cout << separator << endl;
	if (fit_case.do_fit) std::cout << "Doing fit with option string: " << fit_case.options << endl;
	else std::cout << "Not fitting! Drawing functions using parameter seed values." << endl;
	std::cout << separator << endl;
	
	// Get histogram
	TFile *f = new TFile(bdn_case.file);
	TH1D *h	= (TH1D*)f->Get(fit_case.histname);
	Double_t rebin_factor = fit_case.bin_width/(h->GetBinWidth(1));
	TH1D *h1	= (TH1D*)h->Rebin(rebin_factor,fit_case.histname);
	TH1D *h2	= (TH1D*)h->Rebin(rebin_factor,fit_case.histname);
	
// Initial parameter values and initial step sizes
// err contains initial step sizes now, will contains error estimates later.
	Double_t par[nPars];
	Double_t err[nPars];
	Int_t index;
	for (index = 0; index < nPars; index++) {
	//	std::cout << fit_case.seed[index] << "+/-" << fit_case.step[index] << endl;
		par[index] = fit_case.seed[index];
		err[index] = fit_case.step[index];
	}
// Species populations
	TF1 *fyDC	= new TF1("fyDC", yDC, 0.0, bdn_case.T_cycle, nPars);
	TF1 *fyT1	= new TF1("fyT1", yT1, 0.0, bdn_case.T_cycle, nPars);
	TF1 *fyT2	= new TF1("fyT2", yT2, 0.0, bdn_case.T_cycle, nPars);
	TF1 *fyT3	= new TF1("fyT3", yT3, 0.0, bdn_case.T_cycle, nPars);
	TF1 *fyU1	= new TF1("fyU1", yU1, 0.0, bdn_case.T_cycle, nPars);
	TF1 *fyU2	= new TF1("fyU2", yU2, 0.0, bdn_case.T_cycle, nPars);
	TF1 *fyU3	= new TF1("fyU3", yU3, 0.0, bdn_case.T_cycle, nPars);
	TF1 *fyAll	= new TF1("fyAll",yAll, 0.0, bdn_case.T_cycle, nPars); // This one fits the data!
// Beta rates to be used by TF1::Integral() and TF1::IntegralError()
	TF1 *frDC	= new TF1("frDC", rDC, 0.0, bdn_case.T_cycle, nPars);
	TF1 *frT1	= new TF1("frT1", rT1, 0.0, bdn_case.T_cycle, nPars);
	TF1 *frT2	= new TF1("frT2", rT2, 0.0, bdn_case.T_cycle, nPars);
	TF1 *frT3	= new TF1("frT3", rT3, 0.0, bdn_case.T_cycle, nPars);
	TF1 *frU1	= new TF1("frU1", rU1, 0.0, bdn_case.T_cycle, nPars);
	TF1 *frU2	= new TF1("frU2", rU2, 0.0, bdn_case.T_cycle, nPars);
	TF1 *frU3	= new TF1("frU3", rU3, 0.0, bdn_case.T_cycle, nPars);
	TF1 *frAll	= new TF1("frAll",rAll, 0.0, bdn_case.T_cycle, nPars);
// Offset functions for plotting
	TF1 *foT1	= new TF1("foT1", oT1, 0.0, bdn_case.T_cycle, nPars);
	TF1 *foT2	= new TF1("foT2", oT2, 0.0, bdn_case.T_cycle, nPars);
	TF1 *foT3	= new TF1("foT3", oT3, 0.0, bdn_case.T_cycle, nPars);
	TF1 *foU1	= new TF1("foU1", oU1, 0.0, bdn_case.T_cycle, nPars);
	TF1 *foU2	= new TF1("foU2", oU2, 0.0, bdn_case.T_cycle, nPars);
	TF1 *foU3	= new TF1("foU3", oU3, 0.0, bdn_case.T_cycle, nPars);
// Initiailize function to fit the data
	fyAll->SetParName(DC,"DC rate");
	fyAll->SetParName(r1,"Rate 1");
	fyAll->SetParName(r2,"Rate 2");
	fyAll->SetParName(r3,"Rate 3");
	fyAll->SetParName(p,"Capture eff");
	fyAll->SetParName(l,"Capture ret");
	fyAll->SetParName(epsT,"T det eff");
	fyAll->SetParName(epsU,"U det eff");
	fyAll->SetParName(epsV,"V det eff");
	fyAll->SetParName(epsW,"W det eff");
	fyAll->SetParName(epsX,"X det eff");
	fyAll->SetParName(epsY,"Y det eff");
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
	std::cout << "PARAMETER SEED VALUES" << endl << separator << endl;
	std::cout << setw(12) << "Par name" << setw(12) << "Varying?" << "\t" << "Par init val and step" << endl << separator << endl;
	for (index = 0; index < nPars; index++) {
		std::cout << setw(12) << fyAll->GetParName(index) << setw(12) << fit_case.toggle[index] << "\t" << fyAll->GetParameter(index) << " +/- " << fyAll->GetParError(index) << endl;
	}
	std::cout << separator << endl << endl;
	
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
	
	if (fit_case.do_fit) {
	// Fix the parameters that are supposed to be fixed
		for (index = 0; index < nPars; index++) {
			if (fit_case.toggle[index] == 0) fyAll->FixParameter(index,fit_case.seed[index]);
		}
	// Do fit and get results
		TFitResultPtr fit = h1->Fit("fyAll",fit_case.options);
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
		
	//// Calculate integrals and errors (OLD WAY)
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
		T1_integral = frT1->Integral(0.0,bdn_case.T_cycle);
		T2_integral = frT2->Integral(0.0,bdn_case.T_cycle);
		T3_integral = frT3->Integral(0.0,bdn_case.T_cycle);
		U1_integral = frU1->Integral(0.0,bdn_case.T_cycle);
		U2_integral = frU2->Integral(0.0,bdn_case.T_cycle);
		U3_integral = frU3->Integral(0.0,bdn_case.T_cycle);
		DC_integral = frDC->Integral(0.0,bdn_case.T_cycle);
		All_integral = frAll->Integral(0.0,bdn_case.T_cycle);
		
		Integral_sum = DC_integral + T1_integral + T2_integral + T3_integral + U1_integral + U2_integral + U3_integral;
		
		T1_integral_error = frT1->IntegralError( 0.0, bdn_case.T_cycle, par, cov.GetMatrixArray() );
		T2_integral_error = frT2->IntegralError( 0.0, bdn_case.T_cycle, par, cov.GetMatrixArray() );
		T3_integral_error = frT3->IntegralError( 0.0, bdn_case.T_cycle, par, cov.GetMatrixArray() );
		U1_integral_error = frU1->IntegralError( 0.0, bdn_case.T_cycle, par, cov.GetMatrixArray() );
		U2_integral_error = frU2->IntegralError( 0.0, bdn_case.T_cycle, par, cov.GetMatrixArray() );
		U3_integral_error = frU3->IntegralError( 0.0, bdn_case.T_cycle, par, cov.GetMatrixArray() );
		DC_integral_error = frDC->IntegralError( 0.0, bdn_case.T_cycle, par, cov.GetMatrixArray() );
		All_integral_error = frAll->IntegralError( 0.0, bdn_case.T_cycle, par, cov.GetMatrixArray() );
		
		Integral_sum_error = Sqrt( Power(DC_integral_error,2.0) + Power(T1_integral_error,2.0) + Power(T2_integral_error,2.0) + Power(T3_integral_error,2.0) + Power(U1_integral_error,2.0) + Power(U2_integral_error,2.0) + Power(U3_integral_error,2.0) );
		
		std::cout << endl << separator << endl;
		printf("NUMBER OF BETAS DETECTED, by population:\n");
		std::cout << separator << endl;
		printf("T1 integral = %f +/- %f\n", T1_integral, T1_integral_error);
		printf("U1 integral = %f +/- %f\n", U1_integral, U1_integral_error);
		printf("T2 integral = %f +/- %f\n", T2_integral, T2_integral_error);
		printf("U2 integral = %f +/- %f\n", U2_integral, U2_integral_error);
		printf("T3 integral = %f +/- %f\n", T3_integral, T3_integral_error);
		printf("U3 integral = %f +/- %f\n", U3_integral, U3_integral_error);
		printf("DC integral = %f +/- %f\n", DC_integral, DC_integral_error);
		std::cout << separator << endl;
		printf("Sum of above = %f +/- %f <-- no cov in unc\n", Integral_sum, Integral_sum_error);
		printf("All integral = %f +/- %f\n", All_integral, All_integral_error);
		std::cout << separator << endl << endl;
		
	} // end if (fit_case.do_fit)
	
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
	
	Double_t nPoints = bdn_case.T_cycle;
	fyAll->SetNpx(nPoints);
	foT1->SetNpx(nPoints);
	foT2->SetNpx(nPoints);
	foT3->SetNpx(nPoints);
	foU1->SetNpx(nPoints);
	foU2->SetNpx(nPoints);
	foU3->SetNpx(nPoints);
	
	TCanvas *c_B_fit	= new TCanvas("c_B_fit","Beta singles fit",945,600);
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
	h1->GetXaxis()->SetRangeUser(-1000,bdn_case.T_cycle+1000);
//	h2->GetXaxis()->SetRangeUser(-1000,bdn_case.T_cycle+1000);
	
	TLegend *leg_1 = new TLegend(0.13, 0.69, 0.32, 0.94);
	leg_1->AddEntry(h1 , "Data");
	leg_1->AddEntry(fyDC, "DC");
	leg_1->AddEntry(foT1, bdn_case.species1 + " trapped");
	leg_1->AddEntry(foU1, bdn_case.species1 + " untrapped");
	leg_1->AddEntry(foT2, bdn_case.species2 + " trapped");
	leg_1->AddEntry(foU2, bdn_case.species2 + " untrapped");
	leg_1->AddEntry(foT3, bdn_case.species3 + " trapped");
	leg_1->AddEntry(foU3, bdn_case.species3 + " untrapped");
	leg_1->AddEntry(fyAll , "Fit function (all species)");
	leg_1->SetFillColor(0);
	leg_1->Draw();
	
	if (fit_case.do_fit) {
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
	} // end if (fit_case.do_fit)
	
	gPad->Update();
	TPaveStats *stats_1 = (TPaveStats*)h1->FindObject("stats");
	stats_1->SetX1NDC(.32);
	stats_1->SetX2NDC(.55);
	stats_1->SetY1NDC(.69);
	stats_1->SetY2NDC(.94);
	gPad->Update();
	c_B_fit->Modified();
	
	if (draw_monte_carlo == 1) {
		
		TH1D *h_DDC	= (TH1D*)f->Get("h_DDC_cyctime");
		TH1D *h_DT1	= (TH1D*)f->Get("h_DT1_cyctime");
		TH1D *h_DT2	= (TH1D*)f->Get("h_DT2_cyctime");
		TH1D *h_DT3	= (TH1D*)f->Get("h_DT3_cyctime");
		TH1D *h_DU1	= (TH1D*)f->Get("h_DU1_cyctime");
		TH1D *h_DU2	= (TH1D*)f->Get("h_DU2_cyctime");
		TH1D *h_DU3	= (TH1D*)f->Get("h_DU3_cyctime");
		
		h2->SetLineColor(kBlack);
		if (has_DDC==1) h_DDC->SetLineColor(kBlack);
		h_DT1->SetLineColor(kGreen);
		h_DU1->SetLineColor(kGreen);
		h_DT2->SetLineColor(kBlue);
		h_DU2->SetLineColor(kBlue);
		h_DT3->SetLineColor(kRed);
		h_DU3->SetLineColor(kRed);
		
		if (has_DDC==1) h_DDC->SetLineStyle(7);
		h_DU1->SetLineStyle(7);
		h_DU2->SetLineStyle(7);
		h_DU3->SetLineStyle(7);
		
		if (has_DDC==1) h_DDC->Rebin(rebin_factor);
		h_DT1->Rebin(rebin_factor);
		h_DT2->Rebin(rebin_factor);
		h_DT3->Rebin(rebin_factor);
		h_DU1->Rebin(rebin_factor);
		h_DU2->Rebin(rebin_factor);
		h_DU3->Rebin(rebin_factor);
		
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
		h2->GetXaxis()->SetRangeUser(-1000,bdn_case.T_cycle+1000);
/*	
		TCanvas *c_decays_cyctime = new TCanvas("c_decays_cyctime","Decays versus cycle time",945,600);
		h2->Draw();
		fyAll->Draw("SAME");
		if (has_DDC==1) fyDC->Draw("SAME");
		fyT1->Draw("SAME");
		fyT2->Draw("SAME");
		fyT3->Draw("SAME");
		fyU1->Draw("SAME");
		fyU2->Draw("SAME");
		fyU3->Draw("SAME");
		if (has_DDC==1) h_DDC->Draw("SAME");
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
		
		printf("T1 entries:    %10d\n",(Int_t)h_DT1->GetEntries());
		printf("U1 entries:    %10d\n",(Int_t)h_DU1->GetEntries());
		printf("T2 entries:    %10d\n",(Int_t)h_DT2->GetEntries());
		printf("U2 entries:    %10d\n",(Int_t)h_DU2->GetEntries());
		printf("T3 entries:    %10d\n",(Int_t)h_DT3->GetEntries());
		printf("U3 entries:    %10d\n",(Int_t)h_DU3->GetEntries());
		if (has_DDC==1) printf("DC entries:    %10d\n",(Int_t)h_DDC->GetEntries());
		printf("Total entries: %10d\n",(Int_t)h1->GetEntries());
*/		
		if (has_VWXY == 1) { // X and Y pops	
			
			TH1D *h_DV1	= (TH1D*)f->Get("h_DV1_cyctime");
			TH1D *h_DV2	= (TH1D*)f->Get("h_DV2_cyctime");
			TH1D *h_DV3	= (TH1D*)f->Get("h_DV3_cyctime");
			TH1D *h_DX2	= (TH1D*)f->Get("h_DX2_cyctime");
			TH1D *h_DX3	= (TH1D*)f->Get("h_DX3_cyctime");
			TH1D *h_DY2	= (TH1D*)f->Get("h_DY2_cyctime");
			TH1D *h_DY3	= (TH1D*)f->Get("h_DY3_cyctime");
			
			h_DV1 ->Rebin(rebin_factor);
			h_DV2 ->Rebin(rebin_factor);
			h_DV3 ->Rebin(rebin_factor);
			h_DX2 ->Rebin(rebin_factor);
			h_DX3 ->Rebin(rebin_factor);
			h_DY2 ->Rebin(rebin_factor);
			h_DY3 ->Rebin(rebin_factor);
			
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
			
			TH1D *h_DU2_1	= (TH1D*)h_DU2->Rebin(rebin_factor,"h_DU2_1");
			TH1D *h_DU3_1	= (TH1D*)h_DU3->Rebin(rebin_factor,"h_DU3_1");
			
			h_DU2_1->SetLineStyle(1);
			h_DU3_1->SetLineStyle(1);
			h_DU2_1->SetLineColor(kBlack);
			h_DU3_1->SetLineColor(kBlack);
			
			TF1 *fyV1	= new TF1("fyV1", yV1, 0.0, bdn_case.T_cycle, nPars);
			TF1 *fyV2	= new TF1("fyV2", yV2, 0.0, bdn_case.T_cycle, nPars);
			TF1 *fyV3	= new TF1("fyV3", yV3, 0.0, bdn_case.T_cycle, nPars);
			TF1 *fyX2	= new TF1("fyX2", yX2, 0.0, bdn_case.T_cycle, nPars);
			TF1 *fyX3	= new TF1("fyX3", yX3, 0.0, bdn_case.T_cycle, nPars);
			TF1 *fyY2	= new TF1("fyY2", yY2, 0.0, bdn_case.T_cycle, nPars);
			TF1 *fyY3	= new TF1("fyY3", yY3, 0.0, bdn_case.T_cycle, nPars);
			
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
			
		} // end if (has_VWXY == 1)
		
	} // end if (draw_monte_carlo == 1)
	
}

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
	return a[dt] * ( a[epsV]*V2(t,a) + a[epsW]*W2(t,a) + a[epsX]*X2(t,a) + /*a[epsY]**/Y2(t,a) ) / a[tauU2];
}
Double_t B_fit_model::yU3 (Double_t *t, Double_t *a) {
	using namespace B_fit_model;
	return a[dt] * ( a[epsV]*V3(t,a) + a[epsW]*W3(t,a) + a[epsX]*X3(t,a) + a[epsY]*Y3(t,a) ) / a[tauU3];
}
Double_t B_fit_model::yAll(Double_t *t, Double_t *a) {
	using namespace B_fit_model;
	return a[dt] * ( a[DC] + a[epsT]*(T1(t,a)/a[tauT1] + T2(t,a)/a[tauT2] + T3(t,a)/a[tauT3]) + (a[epsV]*V1(t,a) + a[epsW]*W1(t,a))/a[tauU1] + (a[epsV]*V2(t,a) + a[epsW]*W2(t,a) + a[epsX]*X2(t,a) + /*a[epsY]**/Y2(t,a))/a[tauU2] + (a[epsV]*V3(t,a) + a[epsW]*W3(t,a) + a[epsX]*X3(t,a) + a[epsY]*Y3(t,a))/a[tauU3] );
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
	return a[dt]*/*a[epsY]*/Y2(t,a)/a[tauU2];
}
Double_t B_fit_model::yY3 (Double_t *t, Double_t *a) {
	using namespace B_fit_model;
	return a[dt]*a[epsY]*Y3(t,a)/a[tauU3];
}
