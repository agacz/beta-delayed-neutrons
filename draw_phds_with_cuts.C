{
	TFile f("bdn.root");
	TCanvas c("c","PHD's for map cuts",945,600);
	bdn_Tree->Draw("a_R_mcpD>>h(8000,0,8000)","-23.0/25.0<T_mcpX&&T_mcpX<-20.0/25.0&&a_R_mcpSum>400");
}
