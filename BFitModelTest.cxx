// 2014-11-10
// Program to evaluate BFitModel functions under controlled conditions

#include "BFitModel.h"
#include "TF1.h"
#include "TH1.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TROOT.h"
#include "time.h"

Double_t	tCap, tBac, tCyc;
Double_t	t1, t2, t3;
Double_t	iota;
bool		b134sbFlag = 0;
Double_t 	ln2		= 0.69314718056;
Int_t		nPars	= 20;

int main (int argc, char *argv[]) {
	
	using namespace BFitNamespace;
	
	iota	= 0.000000000001;
	tCap	= 5000.0;
	tBac	= 101000.0;
	tCyc	= 246000.0;
	t1		= 2490.0/ln2;
	t2		= 24500.0/ln2;
	t3		= 3.818*60000.0/ln2;
	
	Double_t par[nPars];
	
	par[dt]			= 1000.0;
	par[DC]			= 4.0;
	par[r1]			= 50.0;
	par[r2]			= 50.0;
	par[r3]			= 50.0;
	par[p]			= 0.713489732;
	par[rho]		= 0.935526198;
	par[epsT]		= 1.0;
	par[epsU]		= 1.0;
	par[epsV]		= 1.0;
	par[epsW]		= 1.0;
	par[epsX]		= 1.0;
	par[epsY]		= 1.0;
	par[epsZ]		= 1.0;
	par[gammaT1]	= 1.0/10.0;
	par[gammaT2]	= 1.0/20.0;
	par[gammaT3]	= 1.0/30.0;
	par[gammaU1]	= 1.0/40.0;
	par[gammaU2]	= 1.0/50.0;
	par[gammaU3]	= 1.0/60.0;
	
	TFile *MCFile = new TFile("BMC_0005.root","read");
	
//	TH1D *h	= (TH1D*)MCFile->Get("h_DY2_cyctime");
//	TF1 *fn	= new TF1("fn", yY2, 0.0, tCyc, nPars);
	
	TH1D *h	= (TH1D*)MCFile->Get("h_DY3_cyctime");
	TF1 *fn	= new TF1("fn", yY3, 0.0, tCyc, nPars);
	
	Int_t rebin = par[dt]/h->GetBinWidth(1);
	
	fn->SetParameters(par);
	fn->SetNpx(5*tCyc/rebin);
	
	TCanvas *cTest = new TCanvas("cTest","Drawing some function",945,600);
	clock_t timer = clock();
	fn->Draw();
	timer = clock() - timer;
	printf("\nDrawing took %d clicks (%f seconds).\n", timer, (Float_t)timer/CLOCKS_PER_SEC);
	
	h->Rebin(rebin);
	h->Draw("SAME");
//	MCFile->Close();
	
	Double_t tConst[1] = {0.0};
//	Double_t t0 = 100.0;
	printf("t = %f, f(t) = %f\n", tConst[0], fn->EvalPar(tConst,par));
//	for (Int_t t=0; t<= tCyc; T+= 100) {
//		printf("t = %f, f = %f\n",t,fn->Evaluate()
//	}

	TFile *outfile = new TFile("BFit.root","recreate");
	outfile->WriteTObject(cTest);
//	outfile->Close();
	
}
