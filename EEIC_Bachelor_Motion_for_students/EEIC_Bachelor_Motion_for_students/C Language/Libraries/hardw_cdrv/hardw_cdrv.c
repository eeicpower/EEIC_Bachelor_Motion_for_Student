#include <gplib.h>
#include <RtGpShm.h>	// Global Rt/Gp Shared memory pointers
//-------------------------------------------------------------
// The following is a projpp created file from the User defines
//-------------------------------------------------------------
#include "../../Include/pp_proj.h"

/************************************************************************************
MOTOR POWER-ELEC MODULE
-----------------------
Descr.:		hardware module for current driver
Boards:		PMAC CK3M AX1212N NX-ECC203 AD4608 
PWelec:		ServoTechno LA220
Author:		Yui Shirato
			Koseki Lab, University of Tokyo, 2018
************************************************************************************/
//#include <gplib.h>
//#include <stdio.h>
//#include <dlfcn.h>


#include <math.h>

//----------------------------------------------------------------------------------
// pp_proj.h is the C header for accessing PMAC Global, CSGlobal, Ptr vars
// _PPScriptMode_ for Pmac Script like access global & csglobal
// _EnumMode_ for Pmac enum data type checking on Set & Get global functions
//------------------------------------------------------------------------------------
// #define _PPScriptMode_	// uncomment for Pmac Script type access
// #define _EnumMode_			// uncomment for Pmac enum data type checking on Set & Get global functions		


//#include "../../Include/ECATMap.h" //add ADin
#include "hardw_cdrv.h"

#define		TOIDA_Single	(3276.7)	//DA�|�[�g��10V�o�������Ƃ���32767�� MyGate3->Chan[0].Dac[axis] = (int)32767 << 16; �ɏ���
void hardw_vref(double vref)
{
	volatile struct GateArray3  *MyGate3; // Gate3�p�\���̕ϐ��̒�`
	MyGate3 = GetGate3MemPtr(0); // Acc24E3[0]�̃A�h���X��ݒ�

	if (vref>5){
      vref=5;
	 } else if (vref<-5){
      vref=-5;
	 } else {
	 vref = vref;
	 }

	MyGate3->Chan[0].Dac[0] = (int)(vref*TOIDA_Single) << 16; //32767=10V�Ȃ̂ŁCTOIDA_Single��p�����Ɣ��f����
	
}

#define TRQ_MAX 5 // [Nm]
#define MAX_VAL 32767
#define TRQ_CONST 0.9800 // [Nm/V]

// hardware input 10 V -> (32767 << 16)
void hardw_trqref(double trqref)
{
	volatile struct GateArray3  *MyGate3;
	MyGate3 = GetGate3MemPtr(0);
	
	// saturation
	if (trqref > TRQ_MAX){
    trqref = TRQ_MAX;
	} else if (trqref < -TRQ_MAX) {
		trqref = -TRQ_MAX;
	}

	MyGate3->Chan[0].Dac[0] = (int)(trqref / TRQ_CONST * MAX_VAL) << 16;
}

#define One_Circle_Num	(312500) //1 circle = 360 deg = 312500

void hardw_angle_fromdeg_tonum(double deg, double *out){
*out = One_Circle_Num /360.0 * deg;
}

void hardw_angle_fromnum_todeg(double num, double *out){
*out = num / One_Circle_Num * 360.0;
} 