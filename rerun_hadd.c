{ // Do '.x rerun_hadd.c' at ROOT prompt
	
	gROOT->Reset();
	
//	gROOT->ProcessLineSync(".x hadd_135sb1.c");
//	
//	gROOT->ProcessLineSync(".x hadd_135sb1A.c");
//	gROOT->ProcessLineSync(".x hadd_135sb1B.c");
//	gROOT->ProcessLineSync(".x hadd_135sb1C.c");
//	gROOT->ProcessLineSync(".x hadd_135sb1D.c");
//	
//	gROOT->ProcessLineSync(".x hadd_135sb2.c");
//	
//	gROOT->ProcessLineSync(".x hadd_135sb2A.c");
//	gROOT->ProcessLineSync(".x hadd_135sb2B.c");
	
//	gROOT->ProcessLineSync(".x hadd_137i1.c+");
//	gROOT->ProcessLineSync(".x hadd_137i1_230Vpp.c+");
//	gROOT->ProcessLineSync(".x hadd_137i1_176Vpp.c+");
	
	gROOT->ProcessLineSync(".L hadd_2013.c");
//	gROOT->ProcessLineSync("hadd_238Pu_R_mcp_mask2()");
//	gROOT->ProcessLineSync("hadd_238Pu_T_mcp_mask2()");
////	gROOT->ProcessLineSync("hadd_238Pu_R_mcp_mask2_rawMCP()");
////	gROOT->ProcessLineSync("hadd_238Pu_T_mcp_mask2_rawMCP()");
////	gROOT->ProcessLineSync("hadd_238Pu_R_mcp_mask3()");
//	gROOT->ProcessLineSync("hadd_238Pu_T_mcp_mask3()");
//	gROOT->ProcessLineSync("hadd_238Pu_R_mcp_mask3_rawMCP()");
//	gROOT->ProcessLineSync("hadd_238Pu_T_mcp_mask3_rawMCP()");
//	gROOT->ProcessLineSync("hadd_238Pu_R_mcp_NoMask()");
//	gROOT->ProcessLineSync("hadd_238Pu_T_mcp_NoMask()");
//	gROOT->ProcessLineSync("hadd_238Pu_R_mcp_NoMask_rawMCP()");
//	gROOT->ProcessLineSync("hadd_238Pu_T_mcp_NoMask_rawMCP()");
	
	gROOT->ProcessLineSync("hadd_137i07()");
	gROOT->ProcessLineSync("hadd_135sb08()");
	gROOT->ProcessLineSync("hadd_135te01()");
	gROOT->ProcessLineSync("hadd_136sb01()");
	gROOT->ProcessLineSync("hadd_134sb01()");
	gROOT->ProcessLineSync("hadd_134sb02()");
	gROOT->ProcessLineSync("hadd_134sb03()");
	gROOT->ProcessLineSync("hadd_134sb0103()");
	gROOT->ProcessLineSync("hadd_135sb07()");
	
	gROOT->ProcessLineSync("hadd_138i05()");
	gROOT->ProcessLineSync("hadd_138i06()");
	gROOT->ProcessLineSync("hadd_138i07()");
	gROOT->ProcessLineSync("hadd_139i01()");
	gROOT->ProcessLineSync("hadd_140i02()");
	gROOT->ProcessLineSync("hadd_140i03()");
	gROOT->ProcessLineSync("hadd_140xe01()");
	gROOT->ProcessLineSync("hadd_144cs02()");
	gROOT->ProcessLineSync("hadd_145cs02()");
	
}
