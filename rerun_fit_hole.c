{
	gROOT->Reset();
	gROOT->ProcessLineSync(".L mcp_cal.c++");
	
//	gROOT->ProcessLineSync("fit_hole(\"~/shane/cal2013/rootfiles/238Pu_R_mcp_mask2_rawMCP.root\",\"h_R_mcpX_2\")",1);
	gROOT->ProcessLineSync("fit_hole(\"~/shane/cal2013/rootfiles/238Pu_R_mcp_mask2_rawMCP.root\",\"h_R_mcp_map_2\",2)");
//	gROOT->ProcessLineSync("fit_hole(\"~/shane/cal2013/rootfiles/238Pu_R_mcp_NoMask_rawMCP.root\",\"h_R_mcp_map_physical_2\",2)");
//	gROOT->ProcessLineSync("fit_hole(\"~/shane/cal2013/rootfiles/238Pu_R_mcp_NoMask_rawMCP.root\",\"h_R_mcp_map_reconstructed_2\",2)");
//	gROOT->ProcessLineSync("fit_hole(\"~/shane/cal2013/rootfiles/238Pu_R_mcp_NoMask_rawMCP.root\",\"h_R_mcp_map_missingA_2\",2)");
//	gROOT->ProcessLineSync("fit_hole(\"~/shane/cal2013/rootfiles/238Pu_R_mcp_NoMask_rawMCP.root\",\"h_R_mcp_map_missingB_2\",2)");
//	gROOT->ProcessLineSync("fit_hole(\"~/shane/cal2013/rootfiles/238Pu_R_mcp_NoMask_rawMCP.root\",\"h_R_mcp_map_missingC_2\",2)");
//	gROOT->ProcessLineSync("fit_hole(\"~/shane/cal2013/rootfiles/238Pu_R_mcp_NoMask_rawMCP.root\",\"h_R_mcp_map_missingD_2\",2)");
	
//	gROOT->ProcessLineSync("find_active_area(\"~/shane/cal2013/rootfiles/238Pu_R_mcp_NoMask_rawMCP.root\",\"h_R_mcp_map_2\")");
	
}
