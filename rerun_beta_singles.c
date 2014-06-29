{
	gROOT->Reset();
	gROOT->ProcessLineSync(".x fit_beta_singles.cxx+");
	//gROOT->ProcessLineSync("fit_beta_singles()");
}
