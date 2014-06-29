#include <string.h>
#include "TChain.h"
#include "TFile.h"
#include "TH1.h"
#include "TTree.h"
#include "TKey.h"
#include <iostream>

TList *FileList;
TFile *Target;

void MergeRootfile( TDirectory *target, TList *sourcelist );

void hadd_zero_time_5() {
   // in an interactive ROOT session, edit the file names
   // Target and FileList, then
   // root > .L hadd.C
   // root > hadd()
   
  Target = TFile::Open( "/music/bpt1/bpt/bdn/2013/setup/zero_time_5.root", "RECREATE" );
  
  FileList = new TList();

	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00385.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00386.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00387.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00388.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00389.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00390.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00391.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00392.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00393.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00394.root") );	
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00395.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00396.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00397.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00398.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00399.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00400.root") );

	MergeRootfile( Target, FileList );

}

void hadd_zero_time_6() {
   // in an interactive ROOT session, edit the file names
   // Target and FileList, then
   // root > .L hadd.C
   // root > hadd()
   
  Target = TFile::Open( "/music/bpt1/bpt/bdn/2013/setup/zero_time_6.root", "RECREATE" );
  
  FileList = new TList();

	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00407.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00408.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00409.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00410.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00411.root") );
	
	MergeRootfile( Target, FileList );

}

void hadd_zero_time_7() {
   // in an interactive ROOT session, edit the file names
   // Target and FileList, then
   // root > .L hadd.C
   // root > hadd()
   
  Target = TFile::Open( "/music/bpt1/bpt/bdn/2013/setup/zero_time_7.root", "RECREATE" );
  
  FileList = new TList();

	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00414.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00415.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00416.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00417.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00418.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00419.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00420.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00421.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00422.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00423.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00424.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00425.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00426.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00427.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00428.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00429.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00430.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00431.root") );
	
	MergeRootfile( Target, FileList );

}

void hadd_zero_time_8() {
   // in an interactive ROOT session, edit the file names
   // Target and FileList, then
   // root > .L hadd.C
   // root > hadd()
   
  Target = TFile::Open( "/music/bpt1/bpt/bdn/2013/setup/zero_time_8.root", "RECREATE" );
  
  FileList = new TList();

	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00432.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00433.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00434.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00435.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00436.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00437.root") );
	
	MergeRootfile( Target, FileList );

}

void hadd_zero_time_9() {
   // in an interactive ROOT session, edit the file names
   // Target and FileList, then
   // root > .L hadd.C
   // root > hadd()
   
  Target = TFile::Open( "/music/bpt1/bpt/bdn/2013/setup/zero_time_9.root", "RECREATE" );
  
  FileList = new TList();

	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00451.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00452.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00453.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00454.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00455.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00456.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00457.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00458.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00459.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00460.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00461.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00462.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00463.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00464.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00465.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00466.root") );
	
	MergeRootfile( Target, FileList );

}

void hadd_zero_time_all() {
   // in an interactive ROOT session, edit the file names
   // Target and FileList, then
   // root > .L hadd.C
   // root > hadd()
   
  Target = TFile::Open( "/music/bpt1/bpt/bdn/2013/setup/zero_time_all.root", "RECREATE" );
  
  FileList = new TList();
  
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00321.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00322.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00323.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00324.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00325.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00326.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00327.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00328.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00329.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00330.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00331.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00332.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00333.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00334.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00335.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00336.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00337.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00338.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00339.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00340.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00341.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00342.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00343.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00344.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00345.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00346.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00347.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00348.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00349.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00350.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00351.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00352.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00353.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00354.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00355.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00356.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00357.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00358.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00359.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00360.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00361.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00362.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00363.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00364.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00365.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00366.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00367.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00368.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00369.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00370.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00371.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00372.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00373.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00374.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00375.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00376.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00377.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00378.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00379.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00380.root") );

	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00385.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00386.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00387.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00388.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00389.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00390.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00391.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00392.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00393.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00394.root") );	
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00395.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00396.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00397.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00398.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00399.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00400.root") );
	
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00407.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00408.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00409.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00410.root") );
	
	MergeRootfile( Target, FileList );

}

void hadd_first_light_893_900() {
   // in an interactive ROOT session, edit the file names
   // Target and FileList, then
   // root > .L hadd.C
   // root > hadd()
   
  Target = TFile::Open( "/music/bpt1/bpt/bdn/2013/setup/first_light_893_900.root", "RECREATE" );
  
  FileList = new TList();

	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00893.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00894.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00895.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00896.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00897.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00898.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00899.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00900.root") );
	
	MergeRootfile( Target, FileList );

}

void hadd_first_light_914_919() {
   // in an interactive ROOT session, edit the file names
   // Target and FileList, then
   // root > .L hadd.C
   // root > hadd()
   
  Target = TFile::Open( "/music/bpt1/bpt/bdn/2013/setup/first_light_914_919.root", "RECREATE" );
  
  FileList = new TList();

	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00914.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00915.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00916.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00917.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00918.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00919.root") );
	
	MergeRootfile( Target, FileList );

}

void hadd_first_light_927_928() {
   // in an interactive ROOT session, edit the file names
   // Target and FileList, then
   // root > .L hadd.C
   // root > hadd()
   
  Target = TFile::Open( "/music/bpt1/bpt/bdn/2013/setup/first_light_927_928.root", "RECREATE" );
  
  FileList = new TList();

	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00927.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00928.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00929.root") );
	
	MergeRootfile( Target, FileList );

}

void hadd_first_light_934_962() {
   // in an interactive ROOT session, edit the file names
   // Target and FileList, then
   // root > .L hadd.C
   // root > hadd()
   
  Target = TFile::Open( "/music/bpt1/bpt/bdn/2013/setup/first_light_934_962.root", "RECREATE" );
  
  FileList = new TList();

	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00934.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00935.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00936.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00937.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00938.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00939.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00940.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00941.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00942.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00943.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00944.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00945.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00946.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00947.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00948.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00949.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00950.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00951.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00952.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00953.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00954.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00955.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00956.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00957.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00958.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00959.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00960.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00961.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run00962.root") );
	
	MergeRootfile( Target, FileList );

}

void hadd_first_light_1014_1036() {
   // in an interactive ROOT session, edit the file names
   // Target and FileList, then
   // root > .L hadd.C
   // root > hadd()
   
  Target = TFile::Open( "/music/bpt1/bpt/bdn/2013/setup/first_light_1014_1036.root", "RECREATE" );
  
  FileList = new TList();

	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run01014.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run01015.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run01016.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run01017.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run01018.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run01019.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run01020.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run01021.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run01022.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run01023.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run01024.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run01025.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run01026.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run01027.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run01028.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run01029.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run01030.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run01031.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run01032.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run01033.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run01034.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run01035.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/2013/setup/run01036.root") );
	
	MergeRootfile( Target, FileList );

}

void hadd_137i05() {
   // in an interactive ROOT session, edit the file names
   // Target and FileList, then
   // root > .L hadd.C
   // root > hadd()
   
  Target = TFile::Open( "/music/bpt1/bpt/bdn/shane/137i/rootfiles/137i05.root", "RECREATE" );
  
  FileList = new TList();

	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/run01069.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/run01070.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/run01071.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/run01072.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/run01073.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/run01074.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/run01075.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/run01076.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/run01077.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/run01078.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/run01079.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/run01080.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/run01081.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/run01082.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/run01083.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/run01084.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/run01085.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/run01086.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/run01087.root") );
	
	MergeRootfile( Target, FileList );

}

void hadd_138i04() {
   // in an interactive ROOT session, edit the file names
   // Target and FileList, then
   // root > .L hadd.C
   // root > hadd()
  Target = TFile::Open( "/music/bpt1/bpt/bdn/shane/138i/rootfiles/138i04.root", "RECREATE" );
  FileList = new TList();
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/138i/rootfiles/run01098.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/138i/rootfiles/run01099.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/138i/rootfiles/run01100.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/138i/rootfiles/run01101.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/138i/rootfiles/run01102.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/138i/rootfiles/run01103.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/138i/rootfiles/run01104.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/138i/rootfiles/run01105.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/138i/rootfiles/run01106.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/138i/rootfiles/run01107.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/138i/rootfiles/run01108.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/138i/rootfiles/run01109.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/138i/rootfiles/run01110.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/138i/rootfiles/run01111.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/138i/rootfiles/run01112.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/138i/rootfiles/run01113.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/138i/rootfiles/run01114.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/138i/rootfiles/run01115.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/138i/rootfiles/run01116.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/138i/rootfiles/run01117.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/138i/rootfiles/run01118.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/138i/rootfiles/run01119.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/138i/rootfiles/run01120.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/138i/rootfiles/run01121.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/138i/rootfiles/run01122.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/138i/rootfiles/run01123.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/138i/rootfiles/run01124.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/138i/rootfiles/run01125.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/138i/rootfiles/run01126.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/138i/rootfiles/run01127.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/138i/rootfiles/run01128.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/138i/rootfiles/run01129.root") );
	MergeRootfile( Target, FileList );
}

void hadd_138i05() {
   // in an interactive ROOT session, edit the file names
   // Target and FileList, then
   // root > .L hadd.C
   // root > hadd()
  Target = TFile::Open( "/music/bpt1/bpt/bdn/shane/138i/rootfiles/138i05.root", "RECREATE" );
  FileList = new TList();
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/138i/rootfiles/run01291.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/138i/rootfiles/run01292.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/138i/rootfiles/run01293.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/138i/rootfiles/run01294.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/138i/rootfiles/run01295.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/138i/rootfiles/run01296.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/138i/rootfiles/run01297.root") );
	MergeRootfile( Target, FileList );
}

void hadd_145cs02() {
   // in an interactive ROOT session, edit the file names
   // Target and FileList, then
   // root > .L hadd.C
   // root > hadd()
  Target = TFile::Open( "/music/bpt1/bpt/bdn/shane/145cs/rootfiles/145cs02.root", "RECREATE" );
  FileList = new TList();
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/145cs/rootfiles/run01241.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/145cs/rootfiles/run01242.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/145cs/rootfiles/run01243.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/145cs/rootfiles/run01244.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/145cs/rootfiles/run01245.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/145cs/rootfiles/run01246.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/145cs/rootfiles/run01247.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/145cs/rootfiles/run01248.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/145cs/rootfiles/run01249.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/145cs/rootfiles/run01250.root") );				
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/145cs/rootfiles/run01251.root") );	
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/145cs/rootfiles/run01252.root") );	
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/145cs/rootfiles/run01253.root") );	
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/145cs/rootfiles/run01254.root") );	
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/145cs/rootfiles/run01255.root") );	
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/145cs/rootfiles/run01256.root") );	
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/145cs/rootfiles/run01257.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/145cs/rootfiles/run01258.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/145cs/rootfiles/run01259.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/145cs/rootfiles/run01260.root") );				
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/145cs/rootfiles/run01261.root") );	
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/145cs/rootfiles/run01262.root") );	
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/145cs/rootfiles/run01263.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/145cs/rootfiles/run01264.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/145cs/rootfiles/run01265.root") );
//	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/145cs/rootfiles/run01266.root") );	// grid at +300V
//	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/145cs/rootfiles/run01267.root") );	// grid at +200V
//	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/145cs/rootfiles/run01268.root") );	// grid at +50V
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/145cs/rootfiles/run01269.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/145cs/rootfiles/run01270.root") );				
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/145cs/rootfiles/run01271.root") );	
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/145cs/rootfiles/run01272.root") );	
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/145cs/rootfiles/run01273.root") );	
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/145cs/rootfiles/run01274.root") );	
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/145cs/rootfiles/run01275.root") );	
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/145cs/rootfiles/run01276.root") );	
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/145cs/rootfiles/run01277.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/145cs/rootfiles/run01278.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/145cs/rootfiles/run01279.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/145cs/rootfiles/run01280.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/145cs/rootfiles/run01281.root") );
	MergeRootfile( Target, FileList );
}

void hadd_145cs03() {
   // in an interactive ROOT session, edit the file names
   // Target and FileList, then
   // root > .L hadd.C
   // root > hadd()
	Target = TFile::Open( "/music/bpt1/bpt/bdn/shane/145cs/rootfiles/145cs03.root", "RECREATE" );
	FileList = new TList();
	//FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/145cs/rootfiles/run01299.root") );
	//FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/145cs/rootfiles/run01300.root") );
	//FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/145cs/rootfiles/run01301.root") );
	//FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/145cs/rootfiles/run01302.root") );
	//FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/145cs/rootfiles/run01303.root") );
	//FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/145cs/rootfiles/run01304.root") );
	//FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/145cs/rootfiles/run01305.root") );	
	////FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/145cs/rootfiles/run01306.root") ); // tinkering
	//FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/145cs/rootfiles/run01307.root") );
	//FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/145cs/rootfiles/run01308.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/145cs/rootfiles/run01309.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/145cs/rootfiles/run01310.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/145cs/rootfiles/run01311.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/145cs/rootfiles/run01312.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/145cs/rootfiles/run01313.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/145cs/rootfiles/run01314.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/145cs/rootfiles/run01315.root") );	
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/145cs/rootfiles/run01316.root") );	
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/145cs/rootfiles/run01317.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/145cs/rootfiles/run01318.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/145cs/rootfiles/run01319.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/145cs/rootfiles/run01320.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/145cs/rootfiles/run01321.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/145cs/rootfiles/run01322.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/145cs/rootfiles/run01323.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/145cs/rootfiles/run01324.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/145cs/rootfiles/run01325.root") );	
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/145cs/rootfiles/run01326.root") );	
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/145cs/rootfiles/run01327.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/145cs/rootfiles/run01328.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/145cs/rootfiles/run01329.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/145cs/rootfiles/run01330.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/145cs/rootfiles/run01331.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/145cs/rootfiles/run01332.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/145cs/rootfiles/run01333.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/145cs/rootfiles/run01334.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/145cs/rootfiles/run01335.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/145cs/rootfiles/run01336.root") );
	MergeRootfile( Target, FileList );
}

void hadd_144cs02() {
   // in an interactive ROOT session, edit the file names
   // Target and FileList, then
   // root > .L hadd.C
   // root > hadd()
   
  Target = TFile::Open( "/music/bpt1/bpt/bdn/shane/144cs/rootfiles/144cs02.root", "RECREATE" );
  
  FileList = new TList();

	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/144cs/rootfiles/run01347.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/144cs/rootfiles/run01348.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/144cs/rootfiles/run01349.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/144cs/rootfiles/run01350.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/144cs/rootfiles/run01351.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/144cs/rootfiles/run01352.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/144cs/rootfiles/run01353.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/144cs/rootfiles/run01354.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/144cs/rootfiles/run01355.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/144cs/rootfiles/run01356.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/144cs/rootfiles/run01357.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/144cs/rootfiles/run01358.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/144cs/rootfiles/run01359.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/144cs/rootfiles/run01360.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/144cs/rootfiles/run01361.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/144cs/rootfiles/run01362.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/144cs/rootfiles/run01363.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/144cs/rootfiles/run01364.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/144cs/rootfiles/run01365.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/144cs/rootfiles/run01366.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/144cs/rootfiles/run01367.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/144cs/rootfiles/run01368.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/144cs/rootfiles/run01369.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/144cs/rootfiles/run01370.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/144cs/rootfiles/run01371.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/144cs/rootfiles/run01372.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/144cs/rootfiles/run01373.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/144cs/rootfiles/run01374.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/144cs/rootfiles/run01375.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/144cs/rootfiles/run01376.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/144cs/rootfiles/run01377.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/144cs/rootfiles/run01378.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/144cs/rootfiles/run01379.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/144cs/rootfiles/run01380.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/144cs/rootfiles/run01381.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/144cs/rootfiles/run01382.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/144cs/rootfiles/run01383.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/144cs/rootfiles/run01384.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/144cs/rootfiles/run01385.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/144cs/rootfiles/run01386.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/144cs/rootfiles/run01387.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/144cs/rootfiles/run01388.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/144cs/rootfiles/run01389.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/144cs/rootfiles/run01390.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/144cs/rootfiles/run01391.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/144cs/rootfiles/run01392.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/144cs/rootfiles/run01393.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/144cs/rootfiles/run01394.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/144cs/rootfiles/run01395.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/144cs/rootfiles/run01396.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/144cs/rootfiles/run01397.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/144cs/rootfiles/run01398.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/144cs/rootfiles/run01399.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/144cs/rootfiles/run01400.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/144cs/rootfiles/run01401.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/144cs/rootfiles/run01402.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/144cs/rootfiles/run01403.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/144cs/rootfiles/run01404.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/144cs/rootfiles/run01405.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/144cs/rootfiles/run01406.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/144cs/rootfiles/run01407.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/144cs/rootfiles/run01408.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/144cs/rootfiles/run01409.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/144cs/rootfiles/run01410.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/144cs/rootfiles/run01411.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/144cs/rootfiles/run01412.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/144cs/rootfiles/run01413.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/144cs/rootfiles/run01414.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/144cs/rootfiles/run01415.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/144cs/rootfiles/run01416.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/144cs/rootfiles/run01417.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/144cs/rootfiles/run01418.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/144cs/rootfiles/run01419.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/144cs/rootfiles/run01420.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/144cs/rootfiles/run01421.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/144cs/rootfiles/run01422.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/144cs/rootfiles/run01423.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/144cs/rootfiles/run01424.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/144cs/rootfiles/run01425.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/144cs/rootfiles/run01426.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/144cs/rootfiles/run01427.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/144cs/rootfiles/run01428.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/144cs/rootfiles/run01429.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/144cs/rootfiles/run01430.root") );
	
	MergeRootfile( Target, FileList );

}

void hadd_135sb07() {
   // in an interactive ROOT session, edit the file names
   // Target and FileList, then
   // root > .L hadd.C
   // root > hadd()
	Target = TFile::Open( "/music/bpt1/bpt/bdn/shane/135sb/rootfiles/135sb07.root", "RECREATE" );
	FileList = new TList();
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/135sb/rootfiles/run01431.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/135sb/rootfiles/run01432.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/135sb/rootfiles/run01433.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/135sb/rootfiles/run01434.root") );
	MergeRootfile( Target, FileList );
}

void hadd_135sb08() {
   // in an interactive ROOT session, edit the file names
   // Target and FileList, then
   // root > .L hadd.C
   // root > hadd()
	Target = TFile::Open( "/music/bpt1/bpt/bdn/shane/135sb/rootfiles/135sb08.root", "RECREATE" );
	FileList = new TList();
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/135sb/rootfiles/run01435.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/135sb/rootfiles/run01436.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/135sb/rootfiles/run01437.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/135sb/rootfiles/run01438.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/135sb/rootfiles/run01439.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/135sb/rootfiles/run01440.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/135sb/rootfiles/run01441.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/135sb/rootfiles/run01442.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/135sb/rootfiles/run01443.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/135sb/rootfiles/run01444.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/135sb/rootfiles/run01445.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/135sb/rootfiles/run01446.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/135sb/rootfiles/run01447.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/135sb/rootfiles/run01448.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/135sb/rootfiles/run01449.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/135sb/rootfiles/run01450.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/135sb/rootfiles/run01451.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/135sb/rootfiles/run01452.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/135sb/rootfiles/run01453.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/135sb/rootfiles/run01454.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/135sb/rootfiles/run01455.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/135sb/rootfiles/run01456.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/135sb/rootfiles/run01457.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/135sb/rootfiles/run01458.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/135sb/rootfiles/run01459.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/135sb/rootfiles/run01460.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/135sb/rootfiles/run01461.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/135sb/rootfiles/run01462.root") );
//	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/135sb/rootfiles/run01463.root") );
//	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/135sb/rootfiles/run01464.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/135sb/rootfiles/run01465.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/135sb/rootfiles/run01466.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/135sb/rootfiles/run01467.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/135sb/rootfiles/run01468.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/135sb/rootfiles/run01469.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/135sb/rootfiles/run01470.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/135sb/rootfiles/run01471.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/135sb/rootfiles/run01472.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/135sb/rootfiles/run01473.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/135sb/rootfiles/run01474.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/135sb/rootfiles/run01475.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/135sb/rootfiles/run01476.root") );
//	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/135sb/rootfiles/run01477.root") );
//	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/135sb/rootfiles/run01478.root") );
//	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/135sb/rootfiles/run01479.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/135sb/rootfiles/run01480.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/135sb/rootfiles/run01481.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/135sb/rootfiles/run01482.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/135sb/rootfiles/run01483.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/135sb/rootfiles/run01484.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/135sb/rootfiles/run01485.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/135sb/rootfiles/run01486.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/135sb/rootfiles/run01487.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/135sb/rootfiles/run01488.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/135sb/rootfiles/run01489.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/135sb/rootfiles/run01490.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/135sb/rootfiles/run01491.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/135sb/rootfiles/run01492.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/135sb/rootfiles/run01493.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/135sb/rootfiles/run01494.root") );
//	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/135sb/rootfiles/run01495.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/135sb/rootfiles/run01496.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/135sb/rootfiles/run01497.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/135sb/rootfiles/run01498.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/135sb/rootfiles/run01499.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/135sb/rootfiles/run01500.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/135sb/rootfiles/run01501.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/135sb/rootfiles/run01502.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/135sb/rootfiles/run01503.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/135sb/rootfiles/run01504.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/135sb/rootfiles/run01505.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/135sb/rootfiles/run01506.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/135sb/rootfiles/run01507.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/135sb/rootfiles/run01508.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/135sb/rootfiles/run01509.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/135sb/rootfiles/run01510.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/135sb/rootfiles/run01511.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/135sb/rootfiles/run01512.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/135sb/rootfiles/run01513.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/135sb/rootfiles/run01514.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/135sb/rootfiles/run01515.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/135sb/rootfiles/run01516.root") );
//	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/135sb/rootfiles/run01517.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/135sb/rootfiles/run01518.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/135sb/rootfiles/run01519.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/135sb/rootfiles/run01520.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/135sb/rootfiles/run01521.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/135sb/rootfiles/run01522.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/135sb/rootfiles/run01523.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/135sb/rootfiles/run01524.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/135sb/rootfiles/run01525.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/135sb/rootfiles/run01526.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/135sb/rootfiles/run01527.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/135sb/rootfiles/run01528.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/135sb/rootfiles/run01529.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/135sb/rootfiles/run01530.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/135sb/rootfiles/run01531.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/135sb/rootfiles/run01532.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/135sb/rootfiles/run01533.root") );
	MergeRootfile( Target, FileList );
}

void hadd_135te01() {
   // in an interactive ROOT session, edit the file names
   // Target and FileList, then
   // root > .L hadd.C
   // root > hadd()
   
  Target = TFile::Open( "/music/bpt1/bpt/bdn/shane/135te/rootfiles/135te01.root", "RECREATE" );
  
  FileList = new TList();
	
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/135te/rootfiles/run01550.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/135te/rootfiles/run01551.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/135te/rootfiles/run01552.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/135te/rootfiles/run01553.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/135te/rootfiles/run01554.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/135te/rootfiles/run01555.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/135te/rootfiles/run01556.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/135te/rootfiles/run01557.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/135te/rootfiles/run01558.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/135te/rootfiles/run01559.root") );
	//FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/135te/rootfiles/run01560.root") );
	MergeRootfile( Target, FileList );
}

void hadd_140i01() {
   // in an interactive ROOT session, edit the file names
   // Target and FileList, then
   // root > .L hadd.C
   // root > hadd()
   
  Target = TFile::Open( "/music/bpt1/bpt/bdn/shane/140i/rootfiles/140i01.root", "RECREATE" );
  
  FileList = new TList();
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01570.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01571.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01572.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01573.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01574.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01575.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01576.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01577.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01578.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01579.root") );	
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01580.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01581.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01582.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01583.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01584.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01585.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01586.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01587.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01588.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01589.root") );	
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01590.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01591.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01592.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01593.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01594.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01595.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01596.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01597.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01598.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01599.root") );	
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01600.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01601.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01602.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01603.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01604.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01605.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01606.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01607.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01608.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01609.root") );	
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01610.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01611.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01612.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01613.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01614.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01615.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01616.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01617.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01618.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01619.root") );	
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01620.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01621.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01622.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01623.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01624.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01625.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01626.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01627.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01628.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01629.root") );	
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01630.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01631.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01632.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01633.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01634.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01635.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01636.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01637.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01638.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01639.root") );	
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01640.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01641.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01642.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01643.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01644.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01645.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01646.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01647.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01648.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01649.root") );	
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01650.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01651.root") );
	MergeRootfile( Target, FileList );
}

void hadd_140i01_1570_1592() {
   // in an interactive ROOT session, edit the file names
   // Target and FileList, then
   // root > .L hadd.C
   // root > hadd()
  Target = TFile::Open( "/music/bpt1/bpt/bdn/shane/140i/rootfiles/140i01_1570_1592.root", "RECREATE" );
  FileList = new TList();
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01570.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01571.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01572.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01573.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01574.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01575.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01576.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01577.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01578.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01579.root") );	
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01580.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01581.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01582.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01583.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01584.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01585.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01586.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01587.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01588.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01589.root") );	
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01590.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01591.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01592.root") );	
	MergeRootfile( Target, FileList );
}

void hadd_140i01_1593_1613() {
   // in an interactive ROOT session, edit the file names
   // Target and FileList, then
   // root > .L hadd.C
   // root > hadd()
  Target = TFile::Open( "/music/bpt1/bpt/bdn/shane/140i/rootfiles/140i01_1593_1613.root", "RECREATE" );
  FileList = new TList();
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01593.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01594.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01595.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01596.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01597.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01598.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01599.root") );	
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01600.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01601.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01602.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01603.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01604.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01605.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01606.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01607.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01608.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01609.root") );	
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01610.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01611.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01612.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/140i/rootfiles/run01613.root") );
	MergeRootfile( Target, FileList );
}

void hadd_138i06() {
   // in an interactive ROOT session, edit the file names
   // Target and FileList, then
   // root > .L hadd.C
   // root > hadd()
  Target = TFile::Open( "/music/bpt1/bpt/bdn/shane/138i/rootfiles/138i06.root", "RECREATE" );
  FileList = new TList();
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/138i/rootfiles/run01684.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/138i/rootfiles/run01685.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/138i/rootfiles/run01686.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/138i/rootfiles/run01687.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/138i/rootfiles/run01688.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/138i/rootfiles/run01689.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/138i/rootfiles/run01690.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/138i/rootfiles/run01691.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/138i/rootfiles/run01692.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/138i/rootfiles/run01693.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/138i/rootfiles/run01694.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/138i/rootfiles/run01695.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/138i/rootfiles/run01696.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/138i/rootfiles/run01697.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/138i/rootfiles/run01698.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/138i/rootfiles/run01699.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/138i/rootfiles/run01700.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/138i/rootfiles/run01701.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/138i/rootfiles/run01702.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/138i/rootfiles/run01703.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/138i/rootfiles/run01704.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/138i/rootfiles/run01705.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/138i/rootfiles/run01706.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/138i/rootfiles/run01707.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/138i/rootfiles/run01708.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/138i/rootfiles/run01709.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/138i/rootfiles/run01710.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/138i/rootfiles/run01711.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/138i/rootfiles/run01712.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/138i/rootfiles/run01713.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/138i/rootfiles/run01714.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/138i/rootfiles/run01715.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/138i/rootfiles/run01716.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/138i/rootfiles/run01717.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/138i/rootfiles/run01718.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/138i/rootfiles/run01719.root") );
	MergeRootfile( Target, FileList );
}

void hadd_138i07() {
   // in an interactive ROOT session, edit the file names
   // Target and FileList, then
   // root > .L hadd.C
   // root > hadd()
	Target = TFile::Open( "/music/bpt1/bpt/bdn/shane/138i/rootfiles/138i07.root", "RECREATE" );
 	FileList = new TList();
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/138i/rootfiles/run01720.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/138i/rootfiles/run01721.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/138i/rootfiles/run01722.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/138i/rootfiles/run01723.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/138i/rootfiles/run01724.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/138i/rootfiles/run01725.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/138i/rootfiles/run01726.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/138i/rootfiles/run01727.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/138i/rootfiles/run01728.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/138i/rootfiles/run01729.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/138i/rootfiles/run01730.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/138i/rootfiles/run01731.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/138i/rootfiles/run01732.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/138i/rootfiles/run01733.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/138i/rootfiles/run01734.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/138i/rootfiles/run01735.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/138i/rootfiles/run01736.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/138i/rootfiles/run01737.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/138i/rootfiles/run01738.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/138i/rootfiles/run01739.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/138i/rootfiles/run01740.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/138i/rootfiles/run01741.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/138i/rootfiles/run01742.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/138i/rootfiles/run01743.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/138i/rootfiles/run01744.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/138i/rootfiles/run01745.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/138i/rootfiles/run01746.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/138i/rootfiles/run01747.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/138i/rootfiles/run01748.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/138i/rootfiles/run01749.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/138i/rootfiles/run01750.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/138i/rootfiles/run01751.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/138i/rootfiles/run01752.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/138i/rootfiles/run01753.root") );
	MergeRootfile( Target, FileList );
}

void hadd_137i06() {
   // in an interactive ROOT session, edit the file names
   // Target and FileList, then
   // root > .L hadd.C
   // root > hadd()
	Target = TFile::Open( "/music/bpt1/bpt/bdn/shane/137i/rootfiles/137i06.root", "RECREATE" );
 	FileList = new TList();
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/run01755.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/run01756.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/run01757.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/run01758.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/run01759.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/run01760.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/run01761.root") );
//	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/run01762.root") ); // CARIBU misbehaving
	MergeRootfile( Target, FileList );
}

void hadd_137i07() {
   // in an interactive ROOT session, edit the file names
   // Target and FileList, then
   // root > .L hadd.C
   // root > hadd()
	Target = TFile::Open( "/music/bpt1/bpt/bdn/shane/137i/rootfiles/137i07.root", "RECREATE" );
 	FileList = new TList();
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/run01763.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/run01764.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/run01765.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/run01766.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/run01767.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/run01768.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/run01769.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/run01770.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/run01771.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/run01772.root") );
//	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/run01773.root") );
//	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/run01774.root") );
//	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/run01775.root") );
//	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/run01776.root") );
//	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/run01777.root") );
//	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/run01778.root") );
//	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/run01779.root") );
//	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/run01780.root") );
//	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/run01781.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/run01782.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/run01783.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/run01784.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/run01785.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/run01786.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/run01787.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/run01788.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/run01789.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/run01790.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/run01791.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/run01792.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/run01793.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/run01794.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/run01795.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/run01796.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/run01797.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/run01798.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/run01799.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/run01800.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/run01801.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/run01802.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/run01803.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/run01804.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/run01805.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/run01806.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/run01807.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/run01808.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/run01809.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/run01810.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/run01811.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/run01812.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/run01813.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/run01814.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/run01815.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/run01816.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/run01817.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/run01818.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/run01819.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/run01820.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/run01821.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/run01822.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/run01823.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/run01824.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/run01825.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/run01826.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/run01827.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/run01828.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/run01829.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/run01830.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/run01831.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/run01832.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/run01833.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/run01834.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/run01835.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/run01836.root") );
//	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/run01837.root") );
//	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/run01838.root") );
//	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/run01839.root") );
//	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/run01840.root") );
//	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/run01841.root") );
//	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/run01842.root") );
//	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/run01843.root") );

	MergeRootfile( Target, FileList );
}

void hadd_137i07_alt() {
   // in an interactive ROOT session, edit the file names
   // Target and FileList, then
   // root > .L hadd.C
   // root > hadd()
	Target = TFile::Open( "/music/bpt1/bpt/bdn/shane/137i/rootfiles/137i07_alt/137i07_alt.root", "RECREATE" );
 	FileList = new TList();
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/137i07_alt/run01763.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/137i07_alt/run01764.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/137i07_alt/run01765.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/137i07_alt/run01766.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/137i07_alt/run01767.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/137i07_alt/run01768.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/137i07_alt/run01769.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/137i07_alt/run01770.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/137i07_alt/run01771.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/137i07_alt/run01772.root") );
//	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/137i07_alt/run01773.root") );
//	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/137i07_alt/run01774.root") );
//	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/137i07_alt/run01775.root") );
//	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/137i07_alt/run01776.root") );
//	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/137i07_alt/run01777.root") );
//	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/137i07_alt/run01778.root") );
//	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/137i07_alt/run01779.root") );
//	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/137i07_alt/run01780.root") );
//	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/137i07_alt/run01781.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/137i07_alt/run01782.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/137i07_alt/run01783.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/137i07_alt/run01784.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/137i07_alt/run01785.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/137i07_alt/run01786.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/137i07_alt/run01787.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/137i07_alt/run01788.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/137i07_alt/run01789.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/137i07_alt/run01790.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/137i07_alt/run01791.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/137i07_alt/run01792.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/137i07_alt/run01793.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/137i07_alt/run01794.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/137i07_alt/run01795.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/137i07_alt/run01796.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/137i07_alt/run01797.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/137i07_alt/run01798.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/137i07_alt/run01799.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/137i07_alt/run01800.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/137i07_alt/run01801.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/137i07_alt/run01802.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/137i07_alt/run01803.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/137i07_alt/run01804.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/137i07_alt/run01805.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/137i07_alt/run01806.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/137i07_alt/run01807.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/137i07_alt/run01808.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/137i07_alt/run01809.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/137i07_alt/run01810.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/137i07_alt/run01811.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/137i07_alt/run01812.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/137i07_alt/run01813.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/137i07_alt/run01814.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/137i07_alt/run01815.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/137i07_alt/run01816.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/137i07_alt/run01817.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/137i07_alt/run01818.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/137i07_alt/run01819.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/137i07_alt/run01820.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/137i07_alt/run01821.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/137i07_alt/run01822.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/137i07_alt/run01823.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/137i07_alt/run01824.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/137i07_alt/run01825.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/137i07_alt/run01826.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/137i07_alt/run01827.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/137i07_alt/run01828.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/137i07_alt/run01829.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/137i07_alt/run01830.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/137i07_alt/run01831.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/137i07_alt/run01832.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/137i07_alt/run01833.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/137i07_alt/run01834.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/137i07_alt/run01835.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/137i07_alt/run01836.root") );
//	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/137i07_alt/run01837.root") );
//	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/137i07_alt/run01838.root") );
//	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/137i07_alt/run01839.root") );
//	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/137i07_alt/run01840.root") );
//	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/137i07_alt/run01841.root") );
//	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/137i07_alt/run01842.root") );
//	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/137i/rootfiles/137i07_alt/run01843.root") );

	MergeRootfile( Target, FileList );
}

void hadd_136sb01() {
   // in an interactive ROOT session, edit the file names
   // Target and FileList, then
   // root > .L hadd.C
   // root > hadd()
	Target = TFile::Open( "/music/bpt1/bpt/bdn/shane/136sb/rootfiles/136sb01.root", "RECREATE" );
 	FileList = new TList();
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01844.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01845.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01846.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01847.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01848.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01849.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01850.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01851.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01852.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01853.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01854.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01855.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01856.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01857.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01858.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01859.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01860.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01861.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01862.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01863.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01864.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01865.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01866.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01867.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01868.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01869.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01870.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01871.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01872.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01873.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01874.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01875.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01876.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01877.root") );
//	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01878.root") );
//	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01879.root") );
//	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01880.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01881.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01882.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01883.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01884.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01885.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01886.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01887.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01888.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01889.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01890.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01891.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01892.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01893.root") );
//	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01894.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01895.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01896.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01897.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01898.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01899.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01900.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01901.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01902.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01903.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01904.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01905.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01906.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01907.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01908.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01909.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01910.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01911.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01912.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01913.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01914.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01915.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01916.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01917.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01918.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01919.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01920.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01921.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01922.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01923.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01924.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01925.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01926.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01927.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01928.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01929.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01930.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01931.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01932.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01933.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01934.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01935.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01936.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01937.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01938.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01939.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01940.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01941.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01942.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01943.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01944.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01945.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01946.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01947.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01948.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01949.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01950.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01951.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01952.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01953.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01954.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01955.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01956.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01957.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01958.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01959.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01960.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01961.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01962.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01963.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01964.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01965.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01966.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01967.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01968.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01969.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/136sb/rootfiles/run01970.root") );
	MergeRootfile( Target, FileList );
}

void hadd_139i01() {
   // in an interactive ROOT session, edit the file names
   // Target and FileList, then
   // root > .L hadd.C
   // root > hadd()
	Target = TFile::Open( "/music/bpt1/bpt/bdn/shane/139i/rootfiles/139i01.root", "RECREATE" );
 	FileList = new TList();
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/139i/rootfiles/run01971.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/139i/rootfiles/run01972.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/139i/rootfiles/run01973.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/139i/rootfiles/run01974.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/139i/rootfiles/run01975.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/139i/rootfiles/run01976.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/139i/rootfiles/run01977.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/139i/rootfiles/run01978.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/139i/rootfiles/run01979.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/139i/rootfiles/run01980.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/139i/rootfiles/run01981.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/139i/rootfiles/run01982.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/139i/rootfiles/run01983.root") );
	MergeRootfile( Target, FileList );
}

void hadd_134sb01() {
   // in an interactive ROOT session, edit the file names
   // Target and FileList, then
   // root > .L hadd.C
   // root > hadd()
	Target = TFile::Open( "/music/bpt1/bpt/bdn/shane/134sb/rootfiles/134sb01.root", "RECREATE" );
 	FileList = new TList();
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02066.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02067.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02068.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02069.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02070.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02071.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02072.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02073.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02074.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02075.root") );
//	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02076.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02077.root") );
//	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02078.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02079.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02080.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02081.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02082.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02083.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02084.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02085.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02086.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02087.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02088.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02089.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02090.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02091.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02092.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02093.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02094.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02095.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02096.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02097.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02098.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02099.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02100.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02101.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02102.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02103.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02104.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02105.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02106.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02107.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02108.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02109.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02110.root") );
//	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02111.root") );
	
	MergeRootfile( Target, FileList );
}

void hadd_134sb02() {
   // in an interactive ROOT session, edit the file names
   // Target and FileList, then
   // root > .L hadd.C
   // root > hadd()
	Target = TFile::Open( "/music/bpt1/bpt/bdn/shane/134sb/rootfiles/134sb02.root", "RECREATE" );
 	FileList = new TList();
	
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02112.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02113.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02114.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02115.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02116.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02117.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02118.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02119.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02120.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02121.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02122.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02123.root") );
//	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02124.root") );
//	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02125.root") );
//	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02126.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02127.root") );
	
	MergeRootfile( Target, FileList );
}

void hadd_134sb03() {
   // in an interactive ROOT session, edit the file names
   // Target and FileList, then
   // root > .L hadd.C
   // root > hadd()
	Target = TFile::Open( "/music/bpt1/bpt/bdn/shane/134sb/rootfiles/134sb03.root", "RECREATE" );
 	FileList = new TList();
	
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02128.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02129.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02130.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02131.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02132.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02133.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02134.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02135.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02136.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02137.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02138.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02139.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02140.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02141.root") );
//	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02142.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02143.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02144.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02145.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02146.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02147.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02148.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02149.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02150.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02151.root") );
//	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02152.root") );
//	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02153.root") );
	
	MergeRootfile( Target, FileList );
}

void hadd_134sb03_alt() {
   // in an interactive ROOT session, edit the file names
   // Target and FileList, then
   // root > .L hadd.C
   // root > hadd()
	Target = TFile::Open( "/music/bpt1/bpt/bdn/shane/134sb/rootfiles/134sb03_alt/134sb03_alt.root", "RECREATE" );
 	FileList = new TList();
	
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/134sb03_alt/run02128.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/134sb03_alt/run02129.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/134sb03_alt/run02130.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/134sb03_alt/run02131.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/134sb03_alt/run02132.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/134sb03_alt/run02133.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/134sb03_alt/run02134.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/134sb03_alt/run02135.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/134sb03_alt/run02136.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/134sb03_alt/run02137.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/134sb03_alt/run02138.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/134sb03_alt/run02139.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/134sb03_alt/run02140.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/134sb03_alt/run02141.root") );
//	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/134sb03_alt/run02142.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/134sb03_alt/run02143.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/134sb03_alt/run02144.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/134sb03_alt/run02145.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/134sb03_alt/run02146.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/134sb03_alt/run02147.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/134sb03_alt/run02148.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/134sb03_alt/run02149.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/134sb03_alt/run02150.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/134sb03_alt/run02151.root") );
//	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/134sb03_alt/run02152.root") );
//	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/134sb03_alt/run02153.root") );
	
	MergeRootfile( Target, FileList );
}

void hadd_134sb0103() {
   // in an interactive ROOT session, edit the file names
   // Target and FileList, then
   // root > .L hadd.C
   // root > hadd()
	Target = TFile::Open( "/music/bpt1/bpt/bdn/shane/134sb/rootfiles/134sb0103.root", "RECREATE" );
 	FileList = new TList();
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02066.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02067.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02068.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02069.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02070.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02071.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02072.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02073.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02074.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02075.root") );
//	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02076.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02077.root") );
//	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02078.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02079.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02080.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02081.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02082.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02083.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02084.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02085.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02086.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02087.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02088.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02089.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02090.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02091.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02092.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02093.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02094.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02095.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02096.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02097.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02098.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02099.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02100.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02101.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02102.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02103.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02104.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02105.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02106.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02107.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02108.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02109.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02110.root") );
//	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02111.root") );
// Skip 134sb02
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02128.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02129.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02130.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02131.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02132.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02133.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02134.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02135.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02136.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02137.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02138.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02139.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02140.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02141.root") );
//	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02142.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02143.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02144.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02145.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02146.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02147.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02148.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02149.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02150.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02151.root") );
//	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02152.root") );
//	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/134sb/rootfiles/run02153.root") );
	
	MergeRootfile( Target, FileList );
}

void hadd_238Pu_T_mcp_NoMask () {
   // in an interactive ROOT session, edit the file names
   // Target and FileList, then
   // root > .L hadd.C
   // root > hadd()
	Target = TFile::Open( "/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/238Pu_T_mcp_NoMask.root", "RECREATE" );
 	FileList = new TList();
	
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run02309.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run02310.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run02311.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run02312.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run02313.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run02314.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run02315.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run02316.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run02317.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run02318.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run02319.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run02320.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run02321.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run02322.root") );
	
	MergeRootfile( Target, FileList );
}

void hadd_238Pu_R_mcp_NoMask () {
   // in an interactive ROOT session, edit the file names
   // Target and FileList, then
   // root > .L hadd.C
   // root > hadd()
	Target = TFile::Open( "/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/238Pu_R_mcp_NoMask.root", "RECREATE" );
 	FileList = new TList();
	
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run02338.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run02339.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run02340.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run02341.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run02342.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run02343.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run02344.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run02345.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run02346.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run02347.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run02348.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run02349.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run02340.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run02351.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run02352.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run02353.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run02354.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run02355.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run02356.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run02357.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run02358.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run02359.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run02360.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run02361.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run02362.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run02363.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run02364.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run02365.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run02366.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run02367.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run02368.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run02369.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run02370.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run02371.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run02372.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run02373.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run02374.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run02375.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run02376.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run02377.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run02378.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run02379.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run02380.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run02381.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run02382.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run02383.root") );
	
	MergeRootfile( Target, FileList );
}

void hadd_238Pu_T_mcp_NoMask_rawMCP () {
   // in an interactive ROOT session, edit the file names
   // Target and FileList, then
   // root > .L hadd.C
   // root > hadd()
	Target = TFile::Open( "/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/238Pu_T_mcp_NoMask_rawMCP.root", "RECREATE" );
 	FileList = new TList();
	
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run_rawMCP_02309.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run_rawMCP_02310.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run_rawMCP_02311.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run_rawMCP_02312.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run_rawMCP_02313.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run_rawMCP_02314.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run_rawMCP_02315.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run_rawMCP_02316.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run_rawMCP_02317.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run_rawMCP_02318.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run_rawMCP_02319.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run_rawMCP_02320.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run_rawMCP_02321.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run_rawMCP_02322.root") );
	
	MergeRootfile( Target, FileList );
}

void hadd_238Pu_R_mcp_NoMask_rawMCP () {
   // in an interactive ROOT session, edit the file names
   // Target and FileList, then
   // root > .L hadd.C
   // root > hadd()
	Target = TFile::Open( "/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/238Pu_R_mcp_NoMask_rawMCP.root", "RECREATE" );
 	FileList = new TList();
	
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run_rawMCP_02338.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run_rawMCP_02339.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run_rawMCP_02340.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run_rawMCP_02341.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run_rawMCP_02342.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run_rawMCP_02343.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run_rawMCP_02344.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run_rawMCP_02345.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run_rawMCP_02346.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run_rawMCP_02347.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run_rawMCP_02348.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run_rawMCP_02349.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run_rawMCP_02340.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run_rawMCP_02351.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run_rawMCP_02352.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run_rawMCP_02353.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run_rawMCP_02354.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run_rawMCP_02355.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run_rawMCP_02356.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run_rawMCP_02357.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run_rawMCP_02358.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run_rawMCP_02359.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run_rawMCP_02360.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run_rawMCP_02361.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run_rawMCP_02362.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run_rawMCP_02363.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run_rawMCP_02364.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run_rawMCP_02365.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run_rawMCP_02366.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run_rawMCP_02367.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run_rawMCP_02368.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run_rawMCP_02369.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run_rawMCP_02370.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run_rawMCP_02371.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run_rawMCP_02372.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run_rawMCP_02373.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run_rawMCP_02374.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run_rawMCP_02375.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run_rawMCP_02376.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run_rawMCP_02377.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run_rawMCP_02378.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run_rawMCP_02379.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run_rawMCP_02380.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run_rawMCP_02381.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run_rawMCP_02382.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run_rawMCP_02383.root") );
	
	MergeRootfile( Target, FileList );
}

void hadd_238Pu_R_mcp_mask2 () {
   // in an interactive ROOT session, edit the file names
   // Target and FileList, then
   // root > .L hadd.C
   // root > hadd()
	Target = TFile::Open( "/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/238Pu_R_mcp_mask2.root", "RECREATE" );
 	FileList = new TList();
	
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run00305.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run00306.root") );
	
	MergeRootfile( Target, FileList );
}

void hadd_238Pu_R_mcp_mask2_rawMCP () {
   // in an interactive ROOT session, edit the file names
   // Target and FileList, then
   // root > .L hadd.C
   // root > hadd()
	Target = TFile::Open( "/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/238Pu_R_mcp_mask2_rawMCP.root", "RECREATE" );
 	FileList = new TList();
	
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run_rawMCP_00305.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run_rawMCP_00306.root") );
	
	MergeRootfile( Target, FileList );
}

void hadd_238Pu_T_mcp_mask3 () {
   // in an interactive ROOT session, edit the file names
   // Target and FileList, then
   // root > .L hadd.C
   // root > hadd()
	Target = TFile::Open( "/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/238Pu_T_mcp_mask3.root", "RECREATE" );
 	FileList = new TList();
	
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run01144.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run01145.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run01146.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run01147.root") );
	
	MergeRootfile( Target, FileList );
}

void hadd_238Pu_T_mcp_mask3_rawMCP () {
   // in an interactive ROOT session, edit the file names
   // Target and FileList, then
   // root > .L hadd.C
   // root > hadd()
	Target = TFile::Open( "/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/238Pu_T_mcp_mask3_rawMCP.root", "RECREATE" );
 	FileList = new TList();
	
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run_rawMCP_01144.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run_rawMCP_01145.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run_rawMCP_01146.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run_rawMCP_01147.root") );
	
	MergeRootfile( Target, FileList );
}

void hadd_238Pu_T_mcp_mask2 () {
   // in an interactive ROOT session, edit the file names
   // Target and FileList, then
   // root > .L hadd.C
   // root > hadd()
	Target = TFile::Open( "/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/238Pu_T_mcp_mask2.root", "RECREATE" );
 	FileList = new TList();
	
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run01182.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run01183.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run01184.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run01185.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run01186.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run01187.root") );
//	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run01188.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run01189.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run01190.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run01191.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run01192.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run01193.root") );
//	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run01194.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run01195.root") );
	
	MergeRootfile( Target, FileList );
}

void hadd_238Pu_T_mcp_mask2_rawMCP () {
   // in an interactive ROOT session, edit the file names
   // Target and FileList, then
   // root > .L hadd.C
   // root > hadd()
	Target = TFile::Open( "/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/238Pu_T_mcp_mask2_rawMCP.root", "RECREATE" );
 	FileList = new TList();
	
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run_rawMCP_01182.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run_rawMCP_01183.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run_rawMCP_01184.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run_rawMCP_01185.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run_rawMCP_01186.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run_rawMCP_01187.root") );
//	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run_rawMCP_01188.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run_rawMCP_01189.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run_rawMCP_01190.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run_rawMCP_01191.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run_rawMCP_01192.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run_rawMCP_01193.root") );
//	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run_rawMCP_01194.root") );
	FileList->Add( TFile::Open("/music/bpt1/bpt/bdn/shane/cal2013/rootfiles/run_rawMCP_01195.root") );
	
	MergeRootfile( Target, FileList );
}

void MergeRootfile( TDirectory *target, TList *sourcelist ) {

  cout << "Target path: " << target->GetPath() << endl;
  TString path( (char*)strstr( target->GetPath(), ":" ) );
  path.Remove( 0, 2 );

  TFile *first_source = (TFile*)sourcelist->First();
  first_source->cd( path );
  TDirectory *current_sourcedir = gDirectory;

  // loop over all keys in this directory
  TChain *globChain = 0;
  TIter nextkey( current_sourcedir->GetListOfKeys() );
  TKey *key;
  while ( (key = (TKey*)nextkey())) {

    // read object from first source file
    first_source->cd( path );
    TObject *obj = key->ReadObj();

    if ( obj->IsA()->InheritsFrom( "TH1" ) ) {
      // descendant of TH1 -> merge it

      cout << "Merging histogram " << obj->GetName() << endl;
      TH1 *h1 = (TH1*)obj;

      // loop over all source files and add the content of the
      // correspondant histogram to the one pointed to by "h1"
      TFile *nextsource = (TFile*)sourcelist->After( first_source );
      while ( nextsource ) {
        
        // make sure we are at the correct directory level by cd'ing to path
        nextsource->cd( path );
        TH1 *h2 = (TH1*)gDirectory->Get( h1->GetName() );
        if ( h2 ) {
          h1->Add( h2 );
          delete h2; // don't know if this is necessary, i.e. if 
                     // h2 is created by the call to gDirectory above.
        }

        nextsource = (TFile*)sourcelist->After( nextsource );
      }
    }
    else if ( obj->IsA()->InheritsFrom( "TTree" ) ) {
      
      // loop over all source files create a chain of Trees "globChain"
      const char* obj_name= obj->GetName();

      globChain = new TChain(obj_name);
      globChain->Add(first_source->GetName());
      TFile *nextsource = (TFile*)sourcelist->After( first_source );
      const char* file_name = nextsource->GetName();
      cout << "file name  " << file_name << endl;
     while ( nextsource ) {
     	  
       globChain->Add(nextsource->GetName());
       nextsource = (TFile*)sourcelist->After( nextsource );
     }

    } else if ( obj->IsA()->InheritsFrom( "TDirectory" ) ) {
      // it's a subdirectory

      cout << "Found subdirectory " << obj->GetName() << endl;

      // create a new subdir of same name and title in the target file
      target->cd();
      TDirectory *newdir = target->mkdir( obj->GetName(), obj->GetTitle() 
);

      // newdir is now the starting point of another round of merging
      // newdir still knows its depth within the target file via
      // GetPath(), so we can still figure out where we are in the recursion
      MergeRootfile( newdir, sourcelist );

    } else {

      // object is of no type that we know or can handle
      cout << "Unknown object type, name: " 
           << obj->GetName() << " title: " << obj->GetTitle() << endl;
    }

    // now write the merged histogram (which is "in" obj) to the target file
    // note that this will just store obj in the current directory level,
    // which is not persistent until the complete directory itself is stored
    // by "target->Write()" below
    if ( obj ) {
      target->cd();

      //!!if the object is a tree, it is stored in globChain...
	if(obj->IsA()->InheritsFrom( "TTree" ))
	  globChain->Write( key->GetName() );
	else
	obj->Write( key->GetName() );
    }

  } // while ( ( TKey *key = (TKey*)nextkey() ) )

  // save modifications to target file
  target->Write();

}
