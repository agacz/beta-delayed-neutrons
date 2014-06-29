#include <iostream>
#include <iomanip>
#include <cstring>
//#include "TROOT.h"
#include "TString.h"
//#include "TStyle.h"
//#include "TMath.h"
//#include "TFitResult.h"
//#include "TMatrixDSym.h"
//#include "TFile.h"
//#include "TF1.h"
//#include "TH1.h"
//#include "TCanvas.h"
//#include "TLegend.h"
//#include "TPaveStats.h"
//#include "Fit/FitConfig.h"
//#include "TCanvas.h"
////#include "include/bdn.h"
////#include "include/sb135.h"
////#include "bdn_cases.h"

#include "CSVtoStruct.h"
using namespace std;

// Global variables
BDNCase_t	stBDNCases[FILE_ROWS_BDN];
BFitCase_t	stBFitCases[FILE_ROWS_BFit];
int			iBDNCaseIndex, iBFitCaseIndex; // global index to identify case
int			iNumStructs_BDN, iNumStructs_BFit;

int YourFunc ();
Double_t tofToMCPGrid (BDNCase_t, char, Double_t);

// MAIN FUNCTION
int main (int argc, char *argv[]) {
	// This program takes relevant casecodes from the command line and looks up the matching structs
	
	char *csvBDNCases, *csvBFitCases;
	csvBDNCases = "BDNCases.csv_transposed";
	csvBFitCases = "BFitCases.csv_transposed";
	
	cout << endl << "Importing metadata from CSV files..." << endl;
	iNumStructs_BDN  = CSVtoStruct_BDN  (csvBDNCases, stBDNCases);
	cout << "Imported " << iNumStructs_BDN << " BDN cases" << endl;
	iNumStructs_BFit = CSVtoStruct_BFit (csvBFitCases, stBFitCases);
	cout << "Imported " << iNumStructs_BFit << " B_fit cases" << endl;
	
	// Look up the data matching your case code and return its array index
	iBDNCaseIndex  = FindStructIndex ( stBDNCases,  sizeof(BDNCase_t),  iNumStructs_BDN,  argv[1] );
	iBFitCaseIndex = FindStructIndex ( stBFitCases, sizeof(BFitCase_t), iNumStructs_BFit, argv[2] );
	
	// Optional error catching
	if ( iBDNCaseIndex == -1 || iBFitCaseIndex == -1 )
	{ // One of the read-ins failed and already printed a message about it
		cout << "How to run this program:" << endl;
		cout << "'./ExampleProgram <BDN case code> <B_fit case code>'" << endl;
		cout << "where valid case codes are listed in the CSV files." << endl << endl;
		return -1; // error return
	}
	
	cout << "Performing YourFunc with BDN case " << stBDNCases[iBDNCaseIndex].pcsCaseCode << " and BFit case " << stBFitCases[iBFitCaseIndex].pcsCaseCode << endl << endl;
	return YourFunc(); // return status of YourFunc()
	
}

int YourFunc() {
	
	cout << "YourFunc started." << endl << endl;
	int iReturn = SUCCESS;
	
	// Local copies of the relevant metadata structs
	BDNCase_t  stBDNCase = stBDNCases[iBDNCaseIndex];
	BFitCase_t stBFitCase = stBFitCases[iBFitCaseIndex];
	
	cout << "Example of data readout:" << endl << endl;
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
	cout << "etc. etc. etc." << endl << endl;
	
	Double_t t2 = 1.85;
	printf("(%f, %f)\n", t2, tofToMCPGrid(stBDNCase, 'T', t2));
	
	return SUCCESS;
}
