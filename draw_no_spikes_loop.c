/*

2012-12-02 Shane Caldwell

Remove data with s_ms_since_eject in the spiky values.

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

void draw_no_spikes (const char*);

int main (int argc, char *argv[]) {
	while (*++argv) draw_no_spikes(argv[0]);
	return 0;
}

void draw_no_spikes (const char *filename) {
	
	FILE *outfile;
	outfile = fopen("sb135_no_spike_diagnostic.txt","w");
	
	TFile *f = new TFile(filename);
	
	Float_t xMin_1 = -0.1;
	Float_t xMax_1 = 10.0;
	Float_t yMax_1 = 900.0;
	
	Int_t color_no_spikes = kBlue;
	
	TCanvas *c1_no_spikes = new TCanvas("c1_no_spikes","c1_no_spikes",860,600);
	c1_no_spikes->SetLogy();
	
	TH1I *h = (TH1I*)gDirectory->Get("h_tof");;
	h->Rebin(100)->Draw();
	
	f->cd("no_spikes");
	TH1I *h_no_spikes = (TH1I*)gDirectory->Get("h_tof_no_spikes");
	h_no_spikes->SetLineColor(color_no_spikes);
	h_no_spikes->Rebin(100)->Draw("SAME");
	
	TLegend *leg_1 = new TLegend(0.6, 0.8, 1.0, 1.0);
	leg_1->AddEntry(h_no_spikes, "TOF spectrum with spikes removed");
	leg_1->AddEntry(h, "Normal TOF spectrum");
	leg_1->Draw();
	
	TPaveLabel *label = new TPaveLabel(0.5, 0.6, 0.7, 0.8, filename);
	label->Draw();
	
	fprintf(outfile, "%s\t%8d\t%8d", filename, integral, integral_no_spikes);
	
}
