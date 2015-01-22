{
	TFile *tfile = new TFile("BFit.root");
	
	Int_t test	= 0;
	Int_t MC	= 1;
	Int_t data	= 1;
	
	if (test) {
		cTest->Close();
		cTest->Draw();
	}
	else if (data) {
		c_BFit->Close();
		c_BFit->Draw();
	}
	else if (MC) {
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
