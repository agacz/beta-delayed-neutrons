#include <iostream>
#include "TFile.h"
#include "TTree.h"
#include "TLeaf.h"
#include "TH1.h"

using namespace std;

void check_missing_posts () {
	
	char *filename		= "/music/bpt1/bpt/bdn/shane/134sb/rootfiles/134sb03.root";
	TFile *file			= new TFile(filename,"read");
	TTree *BDN_Tree		= (TTree*)file->Get("bdn_Tree");
	TTree *BR_Tree		= (TTree*)file->Get("beta_recoil_tree");	
	
	Int_t nEvent		= BDN_Tree->GetEntries();
	Int_t nBR			= BR_Tree->GetEntries();
	
	cout << endl;
	cout << "Opened " << filename << "." << endl;
	cout << "Events: " << nEvent << ". Beta-recoils: " << nBR << "." << endl;
	
	TH1F *hn_R_missing = new TH1F("hn_R_missing","Number of missing posts from Right MCP hits",5,0,5);
	TH1F *hn_T_missing = new TH1F("hn_T_missing","Number of missing posts from Top MCP hits",5,0,5);
	
	Int_t mRA, mRB, mRC, mRD;
	Int_t mTA, mTB, mTC, mTD;
	for (Int_t i = 0; i < nEvent; i++) {
		BDN_Tree->GetEntry(i);
		mRA = (Int_t)BDN_Tree->GetLeaf("miss_R_mcpA")->GetValue();
		mRB = (Int_t)BDN_Tree->GetLeaf("miss_R_mcpB")->GetValue();
		mRC = (Int_t)BDN_Tree->GetLeaf("miss_R_mcpC")->GetValue();
		mRD = (Int_t)BDN_Tree->GetLeaf("miss_R_mcpD")->GetValue();
		mTA = (Int_t)BDN_Tree->GetLeaf("miss_T_mcpA")->GetValue();
		mTB = (Int_t)BDN_Tree->GetLeaf("miss_T_mcpB")->GetValue();
		mTC = (Int_t)BDN_Tree->GetLeaf("miss_T_mcpC")->GetValue();
		mTD = (Int_t)BDN_Tree->GetLeaf("miss_T_mcpD")->GetValue();
		hn_R_missing	-> Fill(mRA + mRB + mRC + mRD);
		hn_T_missing	-> Fill(mTA + mTB + mTC + mTD);
//		cout << mRA << endl;
	}
	
	TFile *outfile = new TFile("MissingPosts.root","recreate");
	outfile->WriteTObject(hn_R_missing);
	outfile->WriteTObject(hn_T_missing);
//	gDirectory->WriteTObject("hn_R_missing");
//	gDirectory->WriteTObject("hn_T_missing");
	
	cout << endl;
	
}
