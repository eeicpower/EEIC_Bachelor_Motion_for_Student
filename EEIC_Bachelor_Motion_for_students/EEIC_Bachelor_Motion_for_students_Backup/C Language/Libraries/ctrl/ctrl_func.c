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
//(0.002410215665390, -0.004696051975687, 0.002287759841875)/(1, -1.792775409956901, 0.792775409956901)
	stpInf->dB[0] =0.002410215665390;
    stpInf->dB[1] = -0.004696051975687; 
	stpInf->dB[2] = 0.002287759841875; 
	stpInf->dA[0] = 1.0;
    stpInf->dA[1] =-1.792775409956901;
	stpInf->dA[2] =  0.792775409956901;
}

void	func_ObsBlk1ParaInit( volatile TF2_INF *stpInf ){//100Hz LPF
//(1.771 z^2 + 0.9174 z + 0.3964)/(z^2 - 0.6252 z - 0.3748)//500Hz
//(1.771276184247606, 0.917379441270306, 0.396449111472512)/(1, -0.625172927224906, -0.374827072775094)
	stpInf->dB[0] = 1.771276184247606;
    stpInf->dB[1] = 0.917379441270306 ; 
	stpInf->dB[2] = 0.396449111472512; 
	stpInf->dA[0] = 1.0;
    stpInf->dA[1] = -0.625172927224906;
	stpInf->dA[2] = -0.374827072775094;
}

void	func_ObsBlk2ParaInit( volatile TF1_INF *stpInf ){//100Hz LPF
//(0.429 z - 0.4205)/( z + 0.3748)//500Hz
//(0.429049589317858,-0.420490473188110)/(1, 0.374827072775094)
	stpInf->dB[0] = 0.429049589317858; 
	stpInf->dB[1] =  -0.420490473188110; 
	stpInf->dA[0] = 1.0;
    stpInf->dA[1] = 0.374827072775094;
}

void func_CpdParaInit(volatile TF1_INF *stpInf){//(0.06543 z - 0.06111)/(z + 0.9873) 20Hz PD OK
 //(0.065430470658705, -0.061109535294222)/(1, 0.987348750066021)
	stpInf->dB[0] = 0.065430470658705;
    stpInf->dB[1] = -0.061109535294222; 
	stpInf->dA[0] = 1.0;
    stpInf->dA[1] = 0.987348750066021;
}

void	func_LPFParaInit( volatile TF2_INF *stpInf ){//200Hz LPF
	stpInf->dB[0] = 0.1628;
    stpInf->dB[1] = 0.3256; 
	stpInf->dB[2] = 0.1628; 
	stpInf->dA[0] = 1.0;
    stpInf->dA[1] = -0.4991;
	stpInf->dA[2] = 0.1502;
}

void	func_LFmathParaInit( volatile TF2_INF *stpInf){//500Hz LPF
	stpInf->dB[0] = 0.435435304277647;
    stpInf->dB[1] = 0.870870608555294; 
	stpInf->dB[2] = 0.435435304277647; 
	stpInf->dA[0] = 1.0;
    stpInf->dA[1] = 0.517920045122713;
	stpInf->dA[2] = 0.223821171987876;
}

void	func_INVQmathParaInit(volatile TF2_INF *stpInf){//500Hz LPF
	stpInf->dB[0] = 0.242226250843037;
    stpInf->dB[1] = -0.479620326892631; 
	stpInf->dB[2] = 0.237394076049594; 
	stpInf->dA[0] = 1.0;
    stpInf->dA[1] = 0.517920045122713;
	stpInf->dA[2] = 0.223821171987876;
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

double func_TFOUT( double dIn[],double dOut[], volatile CTRL_dob *stpInf){
	dOut[0] =  (stpInf->dB[0] * dIn[0])
		 +	(stpInf->dB[1] * stpInf->dIn[1])
		 +	(stpInf->dB[2] * stpInf->dIn[2])
		 -	(stpInf->dA[1] * stpInf->dOut[1])
		 -	(stpInf->dA[2] * stpInf->dOut[2]);
	return dOut[0];
}
