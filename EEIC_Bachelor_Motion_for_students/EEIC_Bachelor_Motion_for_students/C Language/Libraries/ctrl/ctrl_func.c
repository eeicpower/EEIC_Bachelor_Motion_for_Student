//#include <gplib.h>
//#include <RtGpShm.h>	// Global Rt/Gp Shared memory pointers
//-------------------------------------------------------------
// The following is a projpp created file from the User defines
//-------------------------------------------------------------
#include <stdio.h>
//#include <dlfcn.h>

//----------------------------------------------------------------------------------
// pp_proj.h is the C header for accessing PMAC Global, CSGlobal, Ptr vars
// _PPScriptMode_ for Pmac Script like access global & csglobal
// _EnumMode_ for Pmac enum data type checking on Set & Get global functions
//------------------------------------------------------------------------------------
// #define _PPScriptMode_	// uncomment for Pmac Script type access
// #define _EnumMode_			// uncomment for Pmac enum data type checking on Set & Get global functions		

//#include "../../Include/pp_proj.h"
//#include "../../Include/ECATMap.h" //add ADin
#include "ctrl_func.h"

volatile TF2_INF		gstCpidInf[1];
volatile TF2_INF		gstObsBlk1Inf[1];
volatile TF2_INF		gstObsBlk2Inf[1];
volatile TF2_INF		gstLPFInf[1];
volatile TF1_INF		gstCpdInf[1];
volatile TF2_INF		LFmath[1];
volatile TF2_INF		INVQmath[1];

void	func_TF1StateInit( volatile TF1_INF *stpInf )
{
	stpInf->dInPre[0] = 0.0;
	stpInf->dOutPre[0] = 0.0;
}

void	func_TF2StateInit( volatile TF2_INF *stpInf )
{
	stpInf->dInPre[0] = 0.0;
	stpInf->dInPre[1] = 0.0;
	stpInf->dOutPre[0] = 0.0;
	stpInf->dOutPre[1] = 0.0;
}

void	func_CpidParaInit( volatile TF2_INF *stpInf ){//10Hz
	stpInf->dB[0] = 0.0;
    stpInf->dB[1] = 0.0; 
	stpInf->dB[2] = 0.0; 
	stpInf->dA[0] = 0.0;
    stpInf->dA[1] = 0.0;
	stpInf->dA[2] = 0.0;
}

void func_CpdParaInit(volatile TF1_INF *stpInf){// 20Hz PD OK
	stpInf->dB[0] = 0.0;
    stpInf->dB[1] = 0.0; 
	stpInf->dA[0] = 0.0;
    stpInf->dA[1] = 0.0;
}

void	func_LPFParaInit( volatile TF2_INF *stpInf ){//LPF for ”­“W‰Û‘è2
	stpInf->dB[0] = 0.0;
    stpInf->dB[1] = 0.0; 
	stpInf->dB[2] = 0.0; 
	stpInf->dA[0] = 0.0;
    stpInf->dA[1] = 0.0;
	stpInf->dA[2] = 0.0;
}

void	func_LFmathParaInit( volatile TF2_INF *stpInf){//LPF for DOB
	stpInf->dB[0] = 0.0;
    stpInf->dB[1] = 0.0; 
	stpInf->dB[2] = 0.0; 
	stpInf->dA[0] = 0.0;
    stpInf->dA[1] = 0.0;
	stpInf->dA[2] = 0.0;
}

void	func_INVQmathParaInit(volatile TF2_INF *stpInf){//LPF and inverse of plant
	stpInf->dB[0] = 0.0;
    stpInf->dB[1] = 0.0; 
	stpInf->dB[2] = 0.0; 
	stpInf->dA[0] = 0.0;
    stpInf->dA[1] = 0.0;
	stpInf->dA[2] = 0.0;
}

double	func_TF1Exe( double dIn, volatile TF1_INF *stpInf)
{
	double	dOut;
	
	dOut =  (stpInf->dB[0] * dIn)
		 +	(stpInf->dB[1] * stpInf->dInPre[0])
		 -	(stpInf->dA[1] * stpInf->dOutPre[0]);
	
	stpInf->dInPre[0] = dIn;
	stpInf->dOutPre[0] = dOut;
	
	return dOut;
}


double	func_TF2Exe( double dIn, volatile TF2_INF *stpInf)
{
	double	dOut;
	
	dOut =  (stpInf->dB[0] * dIn)
		 +	(stpInf->dB[1] * stpInf->dInPre[0])
		 +	(stpInf->dB[2] * stpInf->dInPre[1])
		 -	(stpInf->dA[1] * stpInf->dOutPre[0])
		 -	(stpInf->dA[2] * stpInf->dOutPre[1]);
	
	stpInf->dInPre[1] = stpInf->dInPre[0];
	stpInf->dInPre[0] = dIn;
	stpInf->dOutPre[1] = stpInf->dOutPre[0];
	stpInf->dOutPre[0] = dOut;
	
	return dOut;
}

double	func_TF2Exe_AntiWindUp( double dIn, volatile TF2_INF *stpInf, double dLimit_low, double dLimit_high)
{
	double	dOut;
	
	dOut =  (stpInf->dB[0] * dIn)
		 +	(stpInf->dB[1] * stpInf->dInPre[0])
		 +	(stpInf->dB[2] * stpInf->dInPre[1])
		 -	(stpInf->dA[1] * stpInf->dOutPre[0])
		 -	(stpInf->dA[2] * stpInf->dOutPre[1]);
	
	if (dOut > dLimit_high){
		dOut = dLimit_high;
	} 	else if (dOut < dLimit_low){  
		dOut = dLimit_low;
	}	else {
	}

	stpInf->dInPre[1] = stpInf->dInPre[0];
	stpInf->dInPre[0] = dIn;
	stpInf->dOutPre[1] = stpInf->dOutPre[0];
	stpInf->dOutPre[0] = dOut;
	
	return dOut;
}
