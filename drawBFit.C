{
	TFile *tfile = new TFile("BFit.root");
	
	Int_t test = 0;
	
	if (test) {
		cTest->Close();
		cTest->Draw();
	}
	
	else {
//		c_BFit->Close();
//		c_BFit->Draw();
//		c_feeding->Close();
//		c_feeding->Draw();
//		c_Ti->Close();
//		c_Ti->Draw();
//		c_Vi->Close();
//		c_Vi->Draw();
//		c_Wi->Close();
//		c_Wi->Draw();
//		c_Zi->Close();
//		c_Zi->Draw();
//		c_Xi->Close();
//		c_Xi->Draw();
		c_Yi->Close();
		c_Yi->Draw();
	}
}
