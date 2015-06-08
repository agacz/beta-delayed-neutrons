#include <iostream>
#include <fstream>
#include <TFile.h>
#include <TH1.h>

void HistToText () {
	
	TFile	*f = new TFile("/music/bpt1/bpt/bdn/shane/137i/rootfiles/137i07.root", "READ");
//	TFile	*f = new TFile("/music/bpt1/bpt/bdn/shane/135sb/rootfiles/135sb08.root", "READ");
//	TFile	*f = new TFile("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/136sb01.root", "READ");
//	TFile	*f = new TFile("/music/bpt1/bpt/bdn/shane/140i/rootfiles/140i0.root", "READ");
	
	TH1		*h = (TH1*)f->Get("h_En");
	Int_t nBins = h->GetXaxis()->GetNbins();
	cout << nBins << endl;
	
	ofstream outfile;
	outfile.open("HistToTextOutput.txt", std::ofstream::out);
	
	Double_t x, y;
	for (Int_t i = 0; i<=nBins; i++) {
		x = h->GetBinCenter(i);
		y = h->GetBinContent(i);
		outfile << x << "," << y << endl;
	}
	outfile.close();
}
