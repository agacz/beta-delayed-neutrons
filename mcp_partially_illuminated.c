{
	TFile f("bdn.root");
//	Double_t integral = h_R_mcpMap->Integral(1,200,1,100);
//	printf("Integral = %f\n", integral);
	Double_t integral = h_R_mcpMap->Integral(20,180,116,200);
	printf("Integral = %f\n", integral);
}
