/*

2012-12-04 Shane Caldwell

Trying to find the problem with the no_spikes code.

*/

#include <unistd.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
//#include "stat.h"
#include "stdio.h"
#include "TH1.h"
#include "TH2.h"
#include "TFile.h"
#include "TTree.h"
#include "TLeaf.h"
#include "TMath.h"
#include "TPaveLabel.h"
#include "TCanvas.h"
#include "TLegend.h"

void no_spikes_diagnostic (const char*);

int main (int argc, char *argv[]) {
	while (*++argv) no_spikes_diagnostic(argv[0]);
	return 0;
}

void no_spikes_diagnostic (const char *filename) {
	
	FILE *outfile;
	outfile = fopen("sb135_no_spike_diagnostic.txt","a");
	
	TFile *f = new TFile(filename);
	
	TH1I *h = (TH1I*)gDirectory->Get("h_tof");;
	
	Int_t integral = h->Integral();
	
	f->cd("no_spikes");
	TH1I *h_no_spikes = (TH1I*)gDirectory->Get("h_tof_no_spikes");
	
	Int_t integral_no_spikes = h_no_spikes->Integral();
	
	fprintf(outfile, "%s\t%8d\n", filename, integral - integral_no_spikes);
	
	fclose(outfile);
}
