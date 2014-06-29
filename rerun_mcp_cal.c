{
	gROOT->Reset();
	gROOT->ProcessLineSync(".L mcp_cal.c++");
	
// Fit 1D hole
//	gROOT->ProcessLineSync("fit_hole(\"~/shane/cal2013/rootfiles/238Pu_R_mcp_mask2_rawMCP.root\",\"mcp_cal\",\"h_R_mcpX_2\")",1);
	
// Fit 2D hole
//	gROOT->ProcessLineSync("fit_hole(\"~/shane/cal2013/rootfiles/238Pu_R_mcp_mask2.root\",\"/\",\"h_R_mcpMapPhys_3post\",2)");
//	gROOT->ProcessLineSync("fit_hole(\"~/shane/cal2013/rootfiles/238Pu_R_mcp_mask2.root\",\"/\",\"h_R_mcpMap\",2)");
//	gROOT->ProcessLineSync("fit_hole(\"~/shane/cal2013/rootfiles/238Pu_T_mcp_mask2.root\",\"/\",\"h_T_mcpMap\",2)");
//	gROOT->ProcessLineSync("fit_hole(\"~/shane/cal2013/rootfiles/238Pu_R_mcp_mask2.root\",\"/\",\"h_R_mcpMapPhysFidArea\",2)");
//	gROOT->ProcessLineSync("fit_hole(\"~/shane/cal2013/rootfiles/238Pu_R_mcp_mask2_rawMCP.root\",\"mcp_cal\",\"h_R_mcp_map_2\",2)");
//	gROOT->ProcessLineSync("fit_hole(\"~/shane/cal2013/rootfiles/238Pu_R_mcp_NoMask_rawMCP.root\",\"mcp_cal\",\"h_R_mcp_map_physical_2\",2)");
//	gROOT->ProcessLineSync("fit_hole(\"~/shane/cal2013/rootfiles/238Pu_R_mcp_mask2.root\",\"mcp_cal\",\"h_R_mcp_map_missingOne_1\",2)");
	gROOT->ProcessLineSync("fit_hole(\"~/shane/cal2013/rootfiles/238Pu_T_mcp_mask2.root\",\"mcp_cal\",\"h_T_mcp_map_missingOne_1\",2)");
//	gROOT->ProcessLineSync("fit_hole(\"~/shane/cal2013/rootfiles/238Pu_R_mcp_NoMask_rawMCP.root\",\"mcp_cal\",\"h_R_mcp_map_missingA_2\",2)");
//	gROOT->ProcessLineSync("fit_hole(\"~/shane/cal2013/rootfiles/238Pu_R_mcp_NoMask_rawMCP.root\",\"mcp_cal\",\"h_R_mcp_map_missingB_2\",2)");
//	gROOT->ProcessLineSync("fit_hole(\"~/shane/cal2013/rootfiles/238Pu_R_mcp_NoMask_rawMCP.root\",\"mcp_cal\",\"h_R_mcp_map_missingC_2\",2)");
//	gROOT->ProcessLineSync("fit_hole(\"~/shane/cal2013/rootfiles/238Pu_R_mcp_NoMask_rawMCP.root\",\"mcp_cal\",\"h_R_mcp_map_missingD_2\",2)");
//	gROOT->ProcessLineSync("fit_hole(\"~/shane/cal2013/rootfiles/238Pu_T_mcp_mask2_rawMCP.root\",\"mcp_cal\",\"h_T_mcp_map_4\",2)");
	
//	gROOT->ProcessLineSync("fit_hole(\"~/shane/cal2013/rootfiles/238Pu_T_mcp_mask2_rawMCP.root\",\"mcp_cal\",\"h_T_mcp_map_2\",2)");
	
// Calculate active area from an integral
//	gROOT->ProcessLineSync("find_active_area(\"~/shane/cal2013/rootfiles/238Pu_R_mcp_NoMask_rawMCP.root\",\"h_R_mcp_map_2\")");
//	gROOT->ProcessLineSync("find_active_area(\"~/shane/cal2013/rootfiles/238Pu_T_mcp_NoMask_rawMCP.root\",\"h_T_mcp_map_4\")");
	
}
