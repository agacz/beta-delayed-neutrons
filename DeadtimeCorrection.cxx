// 2013-12-08 Shane Caldwell
// Trying to finalize this algorithm after several wrong attempts
// 
// IMPORTANT: This code has to change for each BDN case, based on the cycle timing.
// For each case set t_Bkgd_ms and tCyc_ms to the right values
//
// Need to finalize the value of dCaptVetoOver_us
// Not all 250us of it sits in the first bin of the capt... only 150-200us of it
// Even though the # of events in this bin 

#include <unistd.h>
#include <iostream>
//#include "stat.h"
#include "stdio.h"
#include "TH1.h"
#include "TFile.h"
#include "TObject.h"
#include "TTree.h"
#include "TLeaf.h"
#include "TCanvas.h"
#include "TMath.h"
#include "CSVtoStruct.h"
#include "bdn.h"
#include "bdn_histograms.h"
//#include "include/sb135.h"
using namespace std;

// Global variables
BDNCase_t	stBDNCases[FILE_ROWS_BDN];
int		iBDNCaseIndex; // global index to identify case
int		iNumStructs_BDN;

int DeadtimeCorrection ();

int main (int argc, char *argv[]) {
	char *csvBDNCases;
	csvBDNCases = "BDNCases.csv_transposed";
	cout << endl << "Importing metadata from CSV files..." << endl;
	iNumStructs_BDN  = CSVtoStruct_BDN  (csvBDNCases, stBDNCases);
	cout << "Imported " << iNumStructs_BDN << " BDN cases" << endl;
	iBDNCaseIndex  = FindStructIndex ( stBDNCases,  sizeof(BDNCase_t),  iNumStructs_BDN,  argv[1] );
	cout << "BDN Case Index = " << iBDNCaseIndex << endl;
	if ( iBDNCaseIndex == -1 )
	{ // One of the read-ins failed and already printed a message about it
		cout << "How to run this program:" << endl;
		cout << "'./DeadtimeCorrection <BDN case code>'" << endl;
		cout << "where valid case codes are listed in the CSV files." << endl << endl;
		return -1; // error return
	}
	cout << "Performing DeadtimeCorrection with BDN case " << stBDNCases[iBDNCaseIndex].pcsCaseCode << endl << endl;
	return DeadtimeCorrection(); // return status of BFit
}

int DeadtimeCorrection () {
	
	using namespace TMath;
	BDNCase_t  stBDNCase = stBDNCases[iBDNCaseIndex];
	printf("DeadtimeCorrection started on %s\n",stBDNCase.pcsFilePath);
    //printf("%s\n"filename);
    
	/*****************************************************************/
	/*** Code to include source code as a string in the ROOT file: ***/
	/*****************************************************************
    FILE *fsrc = fopen("beta_gamma.cxx", "r");
    char *fbuf;
    struct stat srcbuf;
	
    stat("beta_gamma.cxx", &srcbuf);
    fbuf = new char [srcbuf.st_size+1];
    fread(fbuf, sizeof(char), srcbuf.st_size, fsrc);
    fbuf[srcbuf.st_size] = '\0';    TString fstr(fbuf);
	/*****************************************************************
	
	printf(fbuf);
*/	
	TFile *file = new TFile(stBDNCase.pcsFilePath,"UPDATE");
	TTree *tree	= (TTree*)file			->Get("bdn_Tree");
	TTree *meta = (TTree*)gDirectory	->Get("metadata_Tree");
	
	Long64_t	nEntries	= tree->GetEntries();
	Int_t		nRuns		= meta->GetEntries();
	Int_t		nTrigs		= 0;
	Int_t		runTime_sec	= 0;
	for (Int_t iRun = 0; iRun < nRuns; iRun++) {
		meta->GetEntry(iRun);
		nTrigs		+= (Int_t)meta->GetLeaf("n_trigs")->GetValue();
		runTime_sec	+= (Int_t)meta->GetLeaf("run_time_sec")->GetValue();
	}
	cout << "# runs     = "			<< nRuns				<< endl;
	cout << "# triggers = "			<< nTrigs				<< endl;
	cout << "Tot Run Time (s) = "	<< runTime_sec 			<< endl;
	cout << "Tot Run Time (h) = "	<< runTime_sec/3600.0	<< endl;
	
	Double_t	dCaptVetoOver_us		= stBDNCase.dCaptVetoOver;//168.2; // duration of elevator/capture pulse veto after capt pulse
	Double_t	dEvtDeadtime_us			= stBDNCase.dEvtDeadtime[0];//142.0;	// +/- 2.0 us
	Double_t	dEvtDeadtime_us_err		= stBDNCase.dEvtDeadtime[1];//1.0;
	Double_t	dEvtDeadtime_us_rel		= dEvtDeadtime_us_err	/dEvtDeadtime_us;
	Double_t	dEvtDeadtime_sec 		= dEvtDeadtime_us		/1000000.0;
	Double_t	dEvtDeadtime_sec_err	= dEvtDeadtime_us_err	/1000000.0;
	Double_t	tMin_ms					= tCycMin;	// from bdn_histograms.h -- histo definitions
	Int_t		tBkgd_ms				= 1000.0*stBDNCase.dBackgroundTime;	// cycle time when background msmt ends
	Int_t		tCyc_ms					= 1000.0*stBDNCase.dCycleTime;		// +/- 0.0 ms
	Int_t		tCapt_ms				= 1000.0*stBDNCase.dCaptureTime;	// time between captures
	Int_t 		binVsCycTimeBkgd		= (Int_t)(tBkgd_ms-tMin_ms+1);
	Double_t	binVsCycTimeWidth_ms	= (tCycMax-tCycMin)/tCycBins;
	Double_t	binVsCycTimeWidth_us	= 1000.0*binVsCycTimeWidth_ms;
	Double_t 	nCycles					= 1000.0 * runTime_sec / tCyc_ms;
	Double_t	rfMin					= rfPhaseMin;	// from bdn_histograms.h -- histo definitions
	Double_t	rfMax					= rfPhaseMax;	// from bdn_histograms.h -- histo definitions
	Int_t		rfBins					= rfPhaseBins;	// from bdn_histograms.h -- histo definitions
	Double_t	binWidthVsRF			= (rfMax-rfMin)/rfBins;
	Double_t	binTimeVsRF_sec			= (binWidthVsRF/wholeRFCycle) * runTime_sec; // Total amt of time spent in each bin of RF phase histo
//	Double_t	nCycles_err				= TMath::
	cout << "RF Phase bin width = " << binWidthVsRF << endl;
	cout << "RF Phase bin time = " << binTimeVsRF_sec << " sec" << endl;
	cout << "Deadtime per event (sec) = " << dEvtDeadtime_sec << endl;
	
// Variables to loop over, per bin of histo
	Int_t		i;
	Double_t	binTimeVsCycTime_sec; // Total amt of time spent in each bin of _vs_cycle_time histo; this varies in the loop!
	Double_t	binTimeVsCycTime_sec_err;
	Double_t	y, x;
	Double_t	binObservedRateHz;
	Double_t	binDeadtimeCorrFactor;
	Double_t	binDeadtimeCorrError;
	Double_t	sig_obs_rate_over_obs_rate;
//	cout << "vars defined." << endl;
	
// Delete all previous cycles (instances) of each histo
	file->Delete("h_deadtime_correction_vs_cycle_time;*");
	file->Delete("h_deadtime_correction_vs_rf_phase;*");
	file->Delete("h_all_vs_cycle_time;*");
	file->Delete("h_betas_vs_cycle_time;*");
	file->Delete("h_B_betas_vs_cycle_time;*");
	file->Delete("h_L_betas_vs_cycle_time;*");
	file->Delete("h_zero_vs_cycle_time;*");
	file->Delete("h_R_zero_vs_cycle_time;*");
	file->Delete("h_T_zero_vs_cycle_time;*");
	file->Delete("h_lowTOF_vs_cycle_time;*");
	file->Delete("h_R_lowTOF_vs_cycle_time;*");
	file->Delete("h_T_lowTOF_vs_cycle_time;*");
	file->Delete("h_fast_vs_cycle_time;*");
	file->Delete("h_R_fast_vs_cycle_time;*");
	file->Delete("h_T_fast_vs_cycle_time;*");
	file->Delete("h_slow_vs_cycle_time;*");
	file->Delete("h_R_slow_vs_cycle_time;*");
	file->Delete("h_T_slow_vs_cycle_time;*");
	file->Delete("h_oops_vs_cycle_time;*");
	file->Delete("h_R_oops_vs_cycle_time;*");
	file->Delete("h_T_oops_vs_cycle_time;*");
	file->Delete("h_all_vs_rf_phase;*");
	file->Delete("h_slow_vs_rf_phase;*");
	file->Delete("h_LT_slow_vs_rf_phase;*");
	file->Delete("h_LR_slow_vs_rf_phase;*");
	file->Delete("h_BT_slow_vs_rf_phase;*");
	file->Delete("h_BR_slow_vs_rf_phase;*");
	file->Delete("h_oops_vs_rf_phase;*");
	file->Delete("h_LT_oops_vs_rf_phase;*");
	file->Delete("h_LR_oops_vs_rf_phase;*");
	file->Delete("h_BT_oops_vs_rf_phase;*");
	file->Delete("h_BR_oops_vs_rf_phase;*");
	file->Delete("h_bkgd_slow_vs_rf_phase;*");
	file->Delete("h_bkgd_LT_slow_vs_rf_phase;*");
	file->Delete("h_bkgd_LR_slow_vs_rf_phase;*");
	file->Delete("h_bkgd_BT_slow_vs_rf_phase;*");
	file->Delete("h_bkgd_BR_slow_vs_rf_phase;*");
	
// Histos to hold deadtime correction factors, cloned from the ones they will correct to ensure same bins.
// Each will be filled in its own loop.
	TH1D *h_deadtime_correction_vs_cycle_time	= (TH1D*)gDirectory->Get("h_all_vs_cycle_time_observed")		->Clone("h_deadtime_correction_vs_cycle_time"); // Copy structure to deadtime corr histo
	TH1D *h_deadtime_correction_vs_rf_phase		= (TH1D*)gDirectory->Get("h_all_vs_rf_phase_observed")			->Clone("h_deadtime_correction_vs_rf_phase");
//	cout << "Deadtime histos defined." << endl;
// Define histos by cloning from uncorrected ones. Will be multiplied by the deadtime correction factors.
// _vs_cycle_time
	TH1D *h_all_vs_cycle_time					= (TH1D*)gDirectory->Get("h_all_vs_cycle_time_observed")		->Clone("h_all_vs_cycle_time");
	TH1D *h_betas_vs_cycle_time					= (TH1D*)gDirectory->Get("h_betas_vs_cycle_time_observed")		->Clone("h_betas_vs_cycle_time");
	TH1D *h_B_betas_vs_cycle_time				= (TH1D*)gDirectory->Get("h_B_betas_vs_cycle_time_observed")	->Clone("h_B_betas_vs_cycle_time");
	TH1D *h_L_betas_vs_cycle_time				= (TH1D*)gDirectory->Get("h_L_betas_vs_cycle_time_observed")	->Clone("h_L_betas_vs_cycle_time");
	TH1D *h_zero_vs_cycle_time					= (TH1D*)gDirectory->Get("h_zero_vs_cycle_time_observed")		->Clone("h_zero_vs_cycle_time");
	TH1D *h_R_zero_vs_cycle_time				= (TH1D*)gDirectory->Get("h_R_zero_vs_cycle_time_observed")		->Clone("h_R_zero_vs_cycle_time");
	TH1D *h_T_zero_vs_cycle_time				= (TH1D*)gDirectory->Get("h_T_zero_vs_cycle_time_observed")		->Clone("h_T_zero_vs_cycle_time");
	TH1D *h_lowTOF_vs_cycle_time				= (TH1D*)gDirectory->Get("h_lowTOF_vs_cycle_time_observed")		->Clone("h_lowTOF_vs_cycle_time");
	TH1D *h_R_lowTOF_vs_cycle_time				= (TH1D*)gDirectory->Get("h_R_lowTOF_vs_cycle_time_observed")	->Clone("h_R_lowTOF_vs_cycle_time");
	TH1D *h_T_lowTOF_vs_cycle_time				= (TH1D*)gDirectory->Get("h_T_lowTOF_vs_cycle_time_observed")	->Clone("h_T_lowTOF_vs_cycle_time");
	TH1D *h_fast_vs_cycle_time					= (TH1D*)gDirectory->Get("h_fast_vs_cycle_time_observed")		->Clone("h_fast_vs_cycle_time");
	TH1D *h_R_fast_vs_cycle_time				= (TH1D*)gDirectory->Get("h_R_fast_vs_cycle_time_observed")		->Clone("h_R_fast_vs_cycle_time");
	TH1D *h_T_fast_vs_cycle_time				= (TH1D*)gDirectory->Get("h_T_fast_vs_cycle_time_observed")		->Clone("h_T_fast_vs_cycle_time");
	TH1D *h_slow_vs_cycle_time					= (TH1D*)gDirectory->Get("h_slow_vs_cycle_time_observed")		->Clone("h_slow_vs_cycle_time");
	TH1D *h_R_slow_vs_cycle_time				= (TH1D*)gDirectory->Get("h_R_slow_vs_cycle_time_observed")		->Clone("h_R_slow_vs_cycle_time");
	TH1D *h_T_slow_vs_cycle_time				= (TH1D*)gDirectory->Get("h_T_slow_vs_cycle_time_observed")		->Clone("h_T_slow_vs_cycle_time");
	TH1D *h_oops_vs_cycle_time					= (TH1D*)gDirectory->Get("h_oops_vs_cycle_time_observed")		->Clone("h_oops_vs_cycle_time");
	TH1D *h_R_oops_vs_cycle_time				= (TH1D*)gDirectory->Get("h_R_oops_vs_cycle_time_observed")		->Clone("h_R_oops_vs_cycle_time");
	TH1D *h_T_oops_vs_cycle_time				= (TH1D*)gDirectory->Get("h_T_oops_vs_cycle_time_observed")		->Clone("h_T_oops_vs_cycle_time");
//	cout << "vs_cycle_time read-in successful." << endl;
// _vs_rf_phase
	TH1D *h_all_vs_rf_phase						= (TH1D*)gDirectory->Get("h_all_vs_rf_phase_observed")			->Clone("h_all_vs_rf_phase");
	TH1D *h_slow_vs_rf_phase					= (TH1D*)gDirectory->Get("h_slow_vs_rf_phase_observed")			->Clone("h_slow_vs_rf_phase");
	TH1D *h_LT_slow_vs_rf_phase					= (TH1D*)gDirectory->Get("h_LT_slow_vs_rf_phase_observed")		->Clone("h_LT_slow_vs_rf_phase");
	TH1D *h_LR_slow_vs_rf_phase					= (TH1D*)gDirectory->Get("h_LR_slow_vs_rf_phase_observed")		->Clone("h_LR_slow_vs_rf_phase");
	TH1D *h_BT_slow_vs_rf_phase					= (TH1D*)gDirectory->Get("h_BT_slow_vs_rf_phase_observed")		->Clone("h_BT_slow_vs_rf_phase");
	TH1D *h_BR_slow_vs_rf_phase					= (TH1D*)gDirectory->Get("h_BR_slow_vs_rf_phase_observed")		->Clone("h_BR_slow_vs_rf_phase");
	TH1D *h_oops_vs_rf_phase					= (TH1D*)gDirectory->Get("h_oops_vs_rf_phase_observed")			->Clone("h_oops_vs_rf_phase");
	TH1D *h_LT_oops_vs_rf_phase					= (TH1D*)gDirectory->Get("h_LT_oops_vs_rf_phase_observed")		->Clone("h_LT_oops_vs_rf_phase");
	TH1D *h_LR_oops_vs_rf_phase					= (TH1D*)gDirectory->Get("h_LR_oops_vs_rf_phase_observed")		->Clone("h_LR_oops_vs_rf_phase");
	TH1D *h_BT_oops_vs_rf_phase					= (TH1D*)gDirectory->Get("h_BT_oops_vs_rf_phase_observed")		->Clone("h_BT_oops_vs_rf_phase");
	TH1D *h_BR_oops_vs_rf_phase					= (TH1D*)gDirectory->Get("h_BR_oops_vs_rf_phase_observed")		->Clone("h_BR_oops_vs_rf_phase");
	TH1D *h_bkgd_slow_vs_rf_phase				= (TH1D*)gDirectory->Get("h_bkgd_slow_vs_rf_phase_observed")	->Clone("h_bkgd_slow_vs_rf_phase");
	TH1D *h_bkgd_LT_slow_vs_rf_phase			= (TH1D*)gDirectory->Get("h_bkgd_LT_slow_vs_rf_phase_observed")	->Clone("h_bkgd_LT_slow_vs_rf_phase");
	TH1D *h_bkgd_LR_slow_vs_rf_phase			= (TH1D*)gDirectory->Get("h_bkgd_LR_slow_vs_rf_phase_observed")	->Clone("h_bkgd_LR_slow_vs_rf_phase");
	TH1D *h_bkgd_BT_slow_vs_rf_phase			= (TH1D*)gDirectory->Get("h_bkgd_BT_slow_vs_rf_phase_observed")	->Clone("h_bkgd_BT_slow_vs_rf_phase");
	TH1D *h_bkgd_BR_slow_vs_rf_phase			= (TH1D*)gDirectory->Get("h_bkgd_BR_slow_vs_rf_phase_observed")	->Clone("h_bkgd_BR_slow_vs_rf_phase");
	
	cout << "Correcting _vs_cycle_time. Number of events = " << h_all_vs_cycle_time	->GetEntries() << endl;
	cout << "Correcting _vs_rf_phase.   Number of events = " << h_all_vs_rf_phase	->GetEntries() << endl;
	
// Correction for _vs_cycle_time histos
	for (i=1; i<=tCycBins; i++) {
		y = (Double_t)h_all_vs_cycle_time->GetBinContent(i); // "observed" ie. raw data
		binTimeVsCycTime_sec	= (binVsCycTimeWidth_ms/tCyc_ms)*runTime_sec;
		if (i >= binVsCycTimeBkgd && (i-binVsCycTimeBkgd)%tCapt_ms == 0) {
		// for these bins the bin time is shortened by the veto, so decrease the bin time accordingly
//			cout << i << endl;
			binTimeVsCycTime_sec *= (binVsCycTimeWidth_us-dCaptVetoOver_us)/binVsCycTimeWidth_us; // Correct for capture pulse veto
		}
		binTimeVsCycTime_sec_err = (0.5/nCycles)*binTimeVsCycTime_sec; // frac unc of due to where the file started/stopped -- crude!
		binObservedRateHz = y/binTimeVsCycTime_sec;
//		if (i >= binVsCycTimeBkgd && (i-binVsCycTimeBkgd)%tCapt_ms == 0) {
//		// for these bins the bin time is shortened by the veto, so increase the bin rate accordingly
//			binObservedRateHz *= binVsCycTimeWidth_us/(binVsCycTimeWidth_us-dCaptVetoOver_us); // Correct for capture pulse veto of ~ .175 ms
//		}
		binDeadtimeCorrFactor = 1.0 / (1.0 - binObservedRateHz*dEvtDeadtime_sec);
//		x = y/Power(binTimeVsCycTime_sec,2.0);
//		binDeadtimeCorrError = Power(binDeadtimeCorrFactor,2)*Sqrt(Power(x,2)*(1+Power(x,2)*binTimeVsCycTime_sec_err+Power(y,3)*dEvtDeadtime_sec_err));
// next line is incomplete, but the last term leads to something funny looking
// need to figure out how to incorporate uncertainty due to file start and stop (unc in # of cycles)
		sig_obs_rate_over_obs_rate = Sqrt(1.0/(y+.000000000001));// + binTimeVsCycTime_sec_err/binTimeVsCycTime_sec);
		binDeadtimeCorrError = Power(binDeadtimeCorrFactor,2)*binObservedRateHz*Sqrt(Power(dEvtDeadtime_sec_err,2)+Power(dEvtDeadtime_sec*sig_obs_rate_over_obs_rate,2));
// For vetoed bins, need another factor of 1ms/(1ms-veto) to correct for the lost *counts*
// Decreasing binTimeVsCycTime_sec previously only corrected the *rate*
		if (i >= binVsCycTimeBkgd && (i-binVsCycTimeBkgd)%tCapt_ms == 0) {
			binDeadtimeCorrFactor *= binVsCycTimeWidth_us/(binVsCycTimeWidth_us-dCaptVetoOver_us);
//			printf("\ni = %d, y = %f, rate = %f, corr = %f +/- %f\n",i,y,binObservedRateHz,binDeadtimeCorrFactor,binDeadtimeCorrError);
		}
//		printf("\ni = %d, y = %f, rate = %f, corr = %f +/- %f\n",i,y,binObservedRateHz,binDeadtimeCorrFactor,binDeadtimeCorrError);
		h_deadtime_correction_vs_cycle_time	->SetBinContent	(i,binDeadtimeCorrFactor);
		h_deadtime_correction_vs_cycle_time	->SetBinError	(i,binDeadtimeCorrError);
	}
	
// Correction for _vs_rf_phase histos
	for (i=1; i<=rfBins; i++) {
		y = (Double_t)h_all_vs_rf_phase->GetBinContent(i); // "observed" ie. raw data
		binObservedRateHz		= y/binTimeVsRF_sec;
		binDeadtimeCorrFactor	= 1.0 / (1.0 - binObservedRateHz*dEvtDeadtime_sec);
		binDeadtimeCorrError	= Power(binDeadtimeCorrFactor,2)*binObservedRateHz*Sqrt(Power(dEvtDeadtime_sec_err,2));
//		if (y>0) printf("\ni = %d, y = %f, rate = %f, corr = %f +/- %f\n",i,y,binObservedRateHz,binDeadtimeCorrFactor,binDeadtimeCorrError);
		h_deadtime_correction_vs_rf_phase	->SetBinContent	(i,binDeadtimeCorrFactor);
		h_deadtime_correction_vs_rf_phase	->SetBinError	(i,binDeadtimeCorrError);
	}
	
// Manipulate things before writing file
	// _vs_cycle_time
	h_all_vs_cycle_time->Sumw2();
	h_betas_vs_cycle_time->Sumw2();
	h_B_betas_vs_cycle_time->Sumw2();
	h_L_betas_vs_cycle_time->Sumw2();
	h_zero_vs_cycle_time->Sumw2();
	h_R_zero_vs_cycle_time->Sumw2();
	h_T_zero_vs_cycle_time->Sumw2();
	h_lowTOF_vs_cycle_time->Sumw2();
	h_R_lowTOF_vs_cycle_time->Sumw2();
	h_T_lowTOF_vs_cycle_time->Sumw2();
	h_fast_vs_cycle_time->Sumw2();
	h_R_fast_vs_cycle_time->Sumw2();
	h_T_fast_vs_cycle_time->Sumw2();
	h_slow_vs_cycle_time->Sumw2();
	h_R_slow_vs_cycle_time->Sumw2();
	h_T_slow_vs_cycle_time->Sumw2();
	h_oops_vs_cycle_time->Sumw2();
	h_R_oops_vs_cycle_time->Sumw2();
	h_T_oops_vs_cycle_time->Sumw2();
	// _vs_rf_phase
	h_all_vs_rf_phase->Sumw2();
	h_slow_vs_rf_phase->Sumw2();
	h_LT_slow_vs_rf_phase->Sumw2();
	h_LR_slow_vs_rf_phase->Sumw2();
	h_BT_slow_vs_rf_phase->Sumw2();
	h_BR_slow_vs_rf_phase->Sumw2();
	h_oops_vs_rf_phase->Sumw2();
	h_LT_oops_vs_rf_phase->Sumw2();
	h_LR_oops_vs_rf_phase->Sumw2();
	h_BT_oops_vs_rf_phase->Sumw2();
	h_BR_oops_vs_rf_phase->Sumw2();
	h_bkgd_slow_vs_rf_phase->Sumw2();
	h_bkgd_LT_slow_vs_rf_phase->Sumw2();
	h_bkgd_LR_slow_vs_rf_phase->Sumw2();
	h_bkgd_BT_slow_vs_rf_phase->Sumw2();
	h_bkgd_BR_slow_vs_rf_phase->Sumw2();
	
// Apply deadtime corrections
	// _vs_cycle_time
	h_all_vs_cycle_time			->Multiply(h_deadtime_correction_vs_cycle_time);
	h_betas_vs_cycle_time		->Multiply(h_deadtime_correction_vs_cycle_time);
	h_B_betas_vs_cycle_time		->Multiply(h_deadtime_correction_vs_cycle_time);
	h_L_betas_vs_cycle_time		->Multiply(h_deadtime_correction_vs_cycle_time);
	h_zero_vs_cycle_time		->Multiply(h_deadtime_correction_vs_cycle_time);
	h_R_zero_vs_cycle_time		->Multiply(h_deadtime_correction_vs_cycle_time);
	h_T_zero_vs_cycle_time		->Multiply(h_deadtime_correction_vs_cycle_time);
	h_lowTOF_vs_cycle_time		->Multiply(h_deadtime_correction_vs_cycle_time);
	h_R_lowTOF_vs_cycle_time	->Multiply(h_deadtime_correction_vs_cycle_time);
	h_T_lowTOF_vs_cycle_time	->Multiply(h_deadtime_correction_vs_cycle_time);
	h_fast_vs_cycle_time		->Multiply(h_deadtime_correction_vs_cycle_time);
	h_R_fast_vs_cycle_time		->Multiply(h_deadtime_correction_vs_cycle_time);
	h_T_fast_vs_cycle_time		->Multiply(h_deadtime_correction_vs_cycle_time);
	h_slow_vs_cycle_time		->Multiply(h_deadtime_correction_vs_cycle_time);
	h_R_slow_vs_cycle_time		->Multiply(h_deadtime_correction_vs_cycle_time);
	h_T_slow_vs_cycle_time		->Multiply(h_deadtime_correction_vs_cycle_time);
	h_oops_vs_cycle_time		->Multiply(h_deadtime_correction_vs_cycle_time);
	h_R_oops_vs_cycle_time		->Multiply(h_deadtime_correction_vs_cycle_time);
	h_T_oops_vs_cycle_time		->Multiply(h_deadtime_correction_vs_cycle_time);
	// _vs_rf_phase
	h_all_vs_rf_phase			->Multiply(h_deadtime_correction_vs_rf_phase);
	h_slow_vs_rf_phase			->Multiply(h_deadtime_correction_vs_rf_phase);
	h_LT_slow_vs_rf_phase		->Multiply(h_deadtime_correction_vs_rf_phase);
	h_LR_slow_vs_rf_phase		->Multiply(h_deadtime_correction_vs_rf_phase);
	h_BT_slow_vs_rf_phase		->Multiply(h_deadtime_correction_vs_rf_phase);
	h_BR_slow_vs_rf_phase		->Multiply(h_deadtime_correction_vs_rf_phase);
	h_oops_vs_rf_phase			->Multiply(h_deadtime_correction_vs_rf_phase);
	h_LT_oops_vs_rf_phase		->Multiply(h_deadtime_correction_vs_rf_phase);
	h_LR_oops_vs_rf_phase		->Multiply(h_deadtime_correction_vs_rf_phase);
	h_BT_oops_vs_rf_phase		->Multiply(h_deadtime_correction_vs_rf_phase);
	h_BR_oops_vs_rf_phase		->Multiply(h_deadtime_correction_vs_rf_phase);
	h_bkgd_slow_vs_rf_phase		->Multiply(h_deadtime_correction_vs_rf_phase);
	h_bkgd_LT_slow_vs_rf_phase	->Multiply(h_deadtime_correction_vs_rf_phase);
	h_bkgd_LR_slow_vs_rf_phase	->Multiply(h_deadtime_correction_vs_rf_phase);
	h_bkgd_BT_slow_vs_rf_phase	->Multiply(h_deadtime_correction_vs_rf_phase);
	h_bkgd_BR_slow_vs_rf_phase	->Multiply(h_deadtime_correction_vs_rf_phase);

// Update # of entries
	// _vs_cycle_time
	h_all_vs_cycle_time			->SetEntries(h_all_vs_cycle_time		->Integral());
	h_betas_vs_cycle_time		->SetEntries(h_betas_vs_cycle_time		->Integral() );
	h_B_betas_vs_cycle_time		->SetEntries(h_B_betas_vs_cycle_time	->Integral() );
	h_L_betas_vs_cycle_time		->SetEntries(h_L_betas_vs_cycle_time	->Integral() );
	h_zero_vs_cycle_time		->SetEntries(h_zero_vs_cycle_time		->Integral() );
	h_R_zero_vs_cycle_time		->SetEntries(h_R_zero_vs_cycle_time		->Integral() );
	h_T_zero_vs_cycle_time		->SetEntries(h_T_zero_vs_cycle_time		->Integral() );
	h_lowTOF_vs_cycle_time		->SetEntries(h_lowTOF_vs_cycle_time		->Integral() );
	h_R_lowTOF_vs_cycle_time	->SetEntries(h_R_lowTOF_vs_cycle_time	->Integral() );
	h_T_lowTOF_vs_cycle_time	->SetEntries(h_T_lowTOF_vs_cycle_time	->Integral() );
	h_fast_vs_cycle_time		->SetEntries(h_fast_vs_cycle_time		->Integral() );
	h_R_fast_vs_cycle_time		->SetEntries(h_R_fast_vs_cycle_time		->Integral() );
	h_T_fast_vs_cycle_time		->SetEntries(h_T_fast_vs_cycle_time		->Integral() );
	h_slow_vs_cycle_time		->SetEntries(h_slow_vs_cycle_time		->Integral() );
	h_R_slow_vs_cycle_time		->SetEntries(h_R_slow_vs_cycle_time		->Integral() );
	h_T_slow_vs_cycle_time		->SetEntries(h_T_slow_vs_cycle_time		->Integral() );
	h_oops_vs_cycle_time		->SetEntries(h_oops_vs_cycle_time		->Integral() );
	h_R_oops_vs_cycle_time		->SetEntries(h_R_oops_vs_cycle_time		->Integral() );
	h_T_oops_vs_cycle_time		->SetEntries(h_T_oops_vs_cycle_time		->Integral() );
	// _vs_rf_phase
	h_all_vs_rf_phase			->SetEntries(h_all_vs_rf_phase			->Integral() );
	h_slow_vs_rf_phase			->SetEntries(h_slow_vs_rf_phase			->Integral() );
	h_LT_slow_vs_rf_phase		->SetEntries(h_LT_slow_vs_rf_phase		->Integral() );
	h_LR_slow_vs_rf_phase		->SetEntries(h_LR_slow_vs_rf_phase		->Integral() );
	h_BT_slow_vs_rf_phase		->SetEntries(h_BT_slow_vs_rf_phase		->Integral() );
	h_BR_slow_vs_rf_phase		->SetEntries(h_BR_slow_vs_rf_phase		->Integral() );
	h_oops_vs_rf_phase			->SetEntries(h_oops_vs_rf_phase			->Integral() );
	h_LT_oops_vs_rf_phase		->SetEntries(h_LT_oops_vs_rf_phase		->Integral() );
	h_LR_oops_vs_rf_phase		->SetEntries(h_LR_oops_vs_rf_phase		->Integral() );
	h_BT_oops_vs_rf_phase		->SetEntries(h_BT_oops_vs_rf_phase		->Integral() );
	h_BR_oops_vs_rf_phase		->SetEntries(h_BR_oops_vs_rf_phase		->Integral() );
	h_bkgd_slow_vs_rf_phase		->SetEntries(h_bkgd_slow_vs_rf_phase	->Integral() );
	h_bkgd_LT_slow_vs_rf_phase	->SetEntries(h_bkgd_LT_slow_vs_rf_phase	->Integral() );
	h_bkgd_LR_slow_vs_rf_phase	->SetEntries(h_bkgd_LR_slow_vs_rf_phase	->Integral() );
	h_bkgd_BT_slow_vs_rf_phase	->SetEntries(h_bkgd_BT_slow_vs_rf_phase	->Integral() );
	h_bkgd_BR_slow_vs_rf_phase	->SetEntries(h_bkgd_BR_slow_vs_rf_phase	->Integral() );
		
/*	h_all_vs_cycle_time		->SetName("h_all_vs_cycle_time");
	h_betas_vs_cycle_time	->SetName("h_betas_vs_cycle_time");
	h_B_betas_vs_cycle_time	->SetName("h_B_betas_vs_cycle_time");
	h_L_betas_vs_cycle_time	->SetName("h_L_betas_vs_cycle_time");
	h_zero_vs_cycle_time	->SetName("h_zero_vs_cycle_time");
	h_R_zero_vs_cycle_time	->SetName("h_R_zero_vs_cycle_time");
	h_T_zero_vs_cycle_time	->SetName("h_T_zero_vs_cycle_time");
	h_lowTOF_vs_cycle_time	->SetName("h_lowTOF_vs_cycle_time");
	h_R_lowTOF_vs_cycle_time->SetName("h_R_lowTOF_vs_cycle_time");
	h_T_lowTOF_vs_cycle_time->SetName("h_T_lowTOF_vs_cycle_time");
	h_fast_vs_cycle_time	->SetName("h_fast_vs_cycle_time");
	h_R_fast_vs_cycle_time	->SetName("h_R_fast_vs_cycle_time");
	h_T_fast_vs_cycle_time	->SetName("h_T_fast_vs_cycle_time");
	h_slow_vs_cycle_time	->SetName("h_slow_vs_cycle_time");
	h_R_slow_vs_cycle_time	->SetName("h_R_slow_vs_cycle_time");
	h_T_slow_vs_cycle_time	->SetName("h_T_slow_vs_cycle_time");
	h_oops_vs_cycle_time	->SetName("h_oops_vs_cycle_time");
	h_R_oops_vs_cycle_time	->SetName("h_R_oops_vs_cycle_time");
	h_T_oops_vs_cycle_time	->SetName("h_T_oops_vs_cycle_time");
*/	
// Change histo titles
	// _vs_cycle_time
	h_deadtime_correction_vs_cycle_time			->SetTitle("1/(fraction of events lost to deadtime), per ms of cycle");
	h_all_vs_cycle_time		->SetTitle("All Triggers vs Cycle Time (ms), corrected for deadtime");
	h_betas_vs_cycle_time	->SetTitle("Beta singles vs cycle time (ms), Both detectors, corrected for deadtime");
	h_B_betas_vs_cycle_time	->SetTitle("Beta singles vs cycle time (ms), Bottom detector, corrected for deadtime");
	h_L_betas_vs_cycle_time	->SetTitle("Beta singles vs cycle time (ms), Left detector, corrected for deadtime");
	h_zero_vs_cycle_time	->SetTitle("All dE-MCP Zero-time events vs Cycle Time (ms), corrected for deadtime");
	h_R_zero_vs_cycle_time	->SetTitle("dE - Right MCP Zero-time events vs Cycle Time (ms), corrected for deadtime");
	h_T_zero_vs_cycle_time	->SetTitle("dE - Top MCP Zero-time events vs Cycle Time (ms), corrected for deadtime");
	h_lowTOF_vs_cycle_time	->SetTitle("All dE-MCP \"Low-TOF\" events vs Cycle Time (ms), corrected for deadtime");
	h_R_lowTOF_vs_cycle_time->SetTitle("dE - Right MCP \"Low-TOF\" events vs Cycle Time (ms), corrected for deadtime");
	h_T_lowTOF_vs_cycle_time->SetTitle("dE - Top MCP \"Low-TOF\" events vs Cycle Time (ms), corrected for deadtime");
	h_fast_vs_cycle_time	->SetTitle("All Fast Recoils vs Cycle Time (ms), corrected for deadtime");
	h_R_fast_vs_cycle_time	->SetTitle("Right MCP Fast Recoils vs Cycle Time (ms), corrected for deadtime");
	h_T_fast_vs_cycle_time	->SetTitle("Top MCP Fast Recoils vs Cycle Time (ms), corrected for deadtime");
	h_slow_vs_cycle_time	->SetTitle("All Slow Recoils vs Cycle Time (ms), corrected for deadtime");
	h_R_slow_vs_cycle_time	->SetTitle("Right MCP Slow Recoils vs Cycle Time (ms), corrected for deadtime");
	h_T_slow_vs_cycle_time	->SetTitle("Top MCP Slow Recoils vs Cycle Time (ms), corrected for deadtime");
	h_oops_vs_cycle_time	->SetTitle("All dE-MCP Accidentals vs Cycle Time (ms), corrected for deadtime");
	h_R_oops_vs_cycle_time	->SetTitle("dE - Right MCP Accidentals vs Cycle Time (ms), corrected for deadtime");
	h_T_oops_vs_cycle_time	->SetTitle("dE - Top MCP Accidentals vs Cycle Time (ms), corrected for deadtime");
	// _vs_rf_phase
	h_deadtime_correction_vs_rf_phase			->SetTitle("1/(fraction of events lost to deadtime), per bin of (RF Phase / 2pi)");
	h_all_vs_rf_phase		->SetTitle("All Triggers vs (RF Phase / 2pi), corrected for deadtime");
	h_slow_vs_rf_phase		->SetTitle("All Slow Recoils vs (RF Phase / 2pi), Trap full, corrected for deadtime");
	h_LT_slow_vs_rf_phase	->SetTitle("LT Slow Recoils vs (RF Phase / 2pi), Trap full, corrected for deadtime");
	h_LR_slow_vs_rf_phase	->SetTitle("LR Slow Recoils vs (RF Phase / 2pi), Trap full, corrected for deadtime");
	h_BT_slow_vs_rf_phase	->SetTitle("BT Slow Recoils vs (RF Phase / 2pi), Trap full, corrected for deadtime");
	h_BR_slow_vs_rf_phase	->SetTitle("BR Slow Recoils vs (RF Phase / 2pi), Trap full, corrected for deadtime");
	h_oops_vs_rf_phase		->SetTitle("All dE-MCP Accidentals vs (RF Phase / 2pi), corrected for deadtime");
	h_LT_oops_vs_rf_phase	->SetTitle("LT dE-MCP Accidentals vs (RF Phase / 2pi), corrected for deadtime");
	h_LR_oops_vs_rf_phase	->SetTitle("LR dE-MCP Accidentals vs (RF Phase / 2pi), corrected for deadtime");
	h_BT_oops_vs_rf_phase	->SetTitle("BT dE-MCP Accidentals vs (RF Phase / 2pi), corrected for deadtime");
	h_BR_oops_vs_rf_phase	->SetTitle("BR dE-MCP Accidentals vs (RF Phase / 2pi), corrected for deadtime");
	h_bkgd_slow_vs_rf_phase		->SetTitle("All Slow Recoils vs (RF Phase / 2pi), Trap empty, corrected for deadtime");
	h_bkgd_LT_slow_vs_rf_phase	->SetTitle("LT Slow Recoils vs (RF Phase / 2pi), Trap empty, corrected for deadtime");
	h_bkgd_LR_slow_vs_rf_phase	->SetTitle("LR Slow Recoils vs (RF Phase / 2pi), Trap empty, corrected for deadtime");
	h_bkgd_BT_slow_vs_rf_phase	->SetTitle("BT Slow Recoils vs (RF Phase / 2pi), Trap empty, corrected for deadtime");
	h_bkgd_BR_slow_vs_rf_phase	->SetTitle("BR Slow Recoils vs (RF Phase / 2pi), Trap empty, corrected for deadtime");
	
// Write deadtime-corrected histos
	gDirectory->WriteTObject(h_deadtime_correction_vs_cycle_time);
	gDirectory->WriteTObject(h_deadtime_correction_vs_rf_phase);
	gDirectory->WriteTObject(h_all_vs_cycle_time);
	gDirectory->WriteTObject(h_betas_vs_cycle_time);
	gDirectory->WriteTObject(h_B_betas_vs_cycle_time);
	gDirectory->WriteTObject(h_L_betas_vs_cycle_time);
	gDirectory->WriteTObject(h_zero_vs_cycle_time);
	gDirectory->WriteTObject(h_R_zero_vs_cycle_time);
	gDirectory->WriteTObject(h_T_zero_vs_cycle_time);
	gDirectory->WriteTObject(h_lowTOF_vs_cycle_time);
	gDirectory->WriteTObject(h_R_lowTOF_vs_cycle_time);
	gDirectory->WriteTObject(h_T_lowTOF_vs_cycle_time);
	gDirectory->WriteTObject(h_fast_vs_cycle_time);
	gDirectory->WriteTObject(h_R_fast_vs_cycle_time);
	gDirectory->WriteTObject(h_T_fast_vs_cycle_time);
	gDirectory->WriteTObject(h_slow_vs_cycle_time);
	gDirectory->WriteTObject(h_R_slow_vs_cycle_time);
	gDirectory->WriteTObject(h_T_slow_vs_cycle_time);
	gDirectory->WriteTObject(h_oops_vs_cycle_time);
	gDirectory->WriteTObject(h_R_oops_vs_cycle_time);
	gDirectory->WriteTObject(h_T_oops_vs_cycle_time);
	gDirectory->WriteTObject(h_all_vs_rf_phase);
	gDirectory->WriteTObject(h_slow_vs_rf_phase);
	gDirectory->WriteTObject(h_LT_slow_vs_rf_phase);
	gDirectory->WriteTObject(h_LR_slow_vs_rf_phase);
	gDirectory->WriteTObject(h_BT_slow_vs_rf_phase);
	gDirectory->WriteTObject(h_BR_slow_vs_rf_phase);
	gDirectory->WriteTObject(h_oops_vs_rf_phase);
	gDirectory->WriteTObject(h_LT_oops_vs_rf_phase);
	gDirectory->WriteTObject(h_LR_oops_vs_rf_phase);
	gDirectory->WriteTObject(h_BT_oops_vs_rf_phase);
	gDirectory->WriteTObject(h_BR_oops_vs_rf_phase);
	gDirectory->WriteTObject(h_bkgd_slow_vs_rf_phase);
	gDirectory->WriteTObject(h_bkgd_LT_slow_vs_rf_phase);
	gDirectory->WriteTObject(h_bkgd_LR_slow_vs_rf_phase);
	gDirectory->WriteTObject(h_bkgd_BT_slow_vs_rf_phase);
	gDirectory->WriteTObject(h_bkgd_BR_slow_vs_rf_phase);
	file->Close();
	printf("%s updated.\n",stBDNCase.pcsFilePath);
	
//	TCanvas *c_cyc = new TCanvas("c_cyc","All triggers",900,600);
//	h_all_vs_cycle_time->Draw("HIST");
//	h_all_for_reference->Draw("SAME");
//	h_all_for_reference->SetLineColor(2);
//	//h_deadtime_correction_vs_cycle_time->Draw("SAME");
//	//h_deadtime_correction_vs_cycle_time->SetLineColor(2);
//	////c_cyc->SetLogy();
	
//	////TH1D *h_diff = new TH1D("h_diff","Trying to see that deadtime \% is in linear regime",302000,-999.5,301000.5);
//	////TCanvas *c_diff = new TCanvas("c_diff","All triggers",900,600);
	
	printf("DeadtimeCorrection done.\n\n");
	
}
