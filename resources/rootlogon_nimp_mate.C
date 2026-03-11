//***********************************************************
// Load root-based libraries defined by users
//-----------------------------------------------------------
// Created by N.T. Zhang, 9/1/2018, zhangningtao@impcas.ac.cn
//-----------------------------------------------------------
// Comments:
// - add readall() function, required by "quick cmds" in AnaLib, 10/1/2019, N.T. Zhang
// - 
//***********************************************************

void loadLibs_fairbase( TString path );
void loadLibs_NimpAnaLib( TString path );
void loadLibs_MateAnaLib( TString path );
void loadLibs_NimpSim( TString path );
void loadLibs_MateSim( TString path );

void rootlogon()
{
	TString MateRootPath = gSystem->Getenv("MATEROOTDIR");
	TString fairbasePath = MateRootPath + "/externalLib/fairbase/build";
	TString MateAnaLibPath = gSystem->Getenv("MATEANADIR");
	TString NimpAnaLibPath = gSystem->Getenv("NIMPANADIR");

	//===================
	// Add header files
	//===================
	/* Add header for fairbase */
	gInterpreter->AddIncludePath(fairbasePath + "/Include");
	/* Add header for fairlogger */
	gInterpreter->AddIncludePath(MateRootPath + "/externalLib/FairLogger/build/install/include/fairlogger");
	/* Add header for MateRoot */
	gInterpreter->AddIncludePath(MateAnaLibPath + "/Include");
	/* Add header for NimpRoot */
	gInterpreter->AddIncludePath(NimpAnaLibPath + "/Include");

	//=====================================================
	// Add analysis libs (if not needed, pls comment relevant lines)
	//=====================================================
	///gSystem->Load(Form("%s/Lib/libNimpCmds.so", NimpAnaLibPath.Data()));
	//gSystem->Load(Form("%s/Lib/libNimpCore.so", NimpAnaLibPath.Data()));
	//gSystem->Load(Form("%s/Lib/libNimpLoop.so", NimpAnaLibPath.Data()));
	/* Add lib for fairbase */
	loadLibs_fairbase(fairbasePath + "/Lib");
	/* Add lib for quick commands in ROOT */
	gSystem->Load(Form("%s/Lib/libMateCmds.so", MateAnaLibPath.Data()));
	/* Add lib for anaroot */
	gSystem->Load(Form("%s/Lib/libMateCore.so", MateAnaLibPath.Data()));
	/* Add lib for MateAnaLib */
	loadLibs_MateAnaLib(MateAnaLibPath + "/Lib");
	loadLibs_NimpAnaLib(NimpAnaLibPath + "/Lib");

	//========================
	//-Set lib for simulation
	//========================
	TString simLibPath = gSystem->Getenv("MATESIMDIR");
	gInterpreter->ProcessLine(Form(".include %s/include", simLibPath.Data()));
	loadLibs_MateSim(simLibPath + "/lib");
	simLibPath = gSystem->Getenv("NIMPSIMDIR");
	gInterpreter->AddIncludePath(Form("%s/include", simLibPath.Data()));
	loadLibs_NimpSim(simLibPath + "/lib");


	//-Load all objects to memory
	gROOT->ProcessLine("readall()");
}

void loadLibs_fairbase(TString path)
{
	gSystem->Load(path + "/libFairBase.so");
	gSystem->Load(path + "/libFairGeoBase.so");
	gSystem->Load(path + "/libFairMbsAPI.so");
	gSystem->Load(path + "/libFairParBase.so");
	gSystem->Load(path + "/libFairOnline.so");
	gSystem->Load(path + "/libFairAlignment.so");
	//gSystem->Load(path + "/libFairTools.so");
}

void loadLibs_NimpAnaLib(TString path)
{
	gSystem->Load(path + "/libAtTpcMap.so");
	gSystem->Load(path + "/libAtTPCPar.so");
	gSystem->Load(path + "/libAtTpcReco.so");
	//gSystem->Load(path + "/libAtMbs.so");
	gSystem->Load(path + "/libATDigi.so");
}

void loadLibs_MateAnaLib(TString path)
{
	gSystem->Load(path + "/libMateOnline.so");
	gSystem->Load(path + "/libMateReconst.so");
	gSystem->Load(path + "/libMateTpcMap.so");
	gSystem->Load(path + "/libMateTPCPar.so");
	gSystem->Load(path + "/libMateTpcRecon.so");
	gSystem->Load(path + "/libMateMbs.so");
	gSystem->Load(path + "/libMateDigi.so");
}

void loadLibs_MateSim(TString path)
{
	gSystem->Load(path + "/libNPSDataContainer.so");
	//gSystem->Load(path + "/libNPAnaTNT.so");
}
void loadLibs_NimpSim(TString path)
{
	gSystem->Load(path + "/libNpAnaCont.so");
	//gSystem->Load(path + "/libNpsDataContainer.so");
	//gSystem->Load(path + "/libNPAnaTNT.so");
}

