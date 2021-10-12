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
#include "ctrl_math.h" // 状態方程式を解く関数

void func_pid(double dIn, double *dOut) {
	double upid[1] = { dIn };
	ctrl_math_output(Cpid[0], xpid, Dpid[0], upid, dOut, 2, 1, 1);
	ctrl_math_state(Apid[0], xpid, Bpid[0], upid, xpid, 2, 1);
}

void func_pid_awu(double dIn, double *dOut, double dOutMax) {
	double upid[1] = { dIn };
	double xpid_next[2] = {0, 0};
	ctrl_math_output(Cpid[0], xpid, Dpid[0], upid, dOut, 2, 1, 1);
	ctrl_math_state(Apid[0], xpid, Bpid[0], upid, xpid_next, 2, 1);
	// Anti Wind-Up
	if (*dOut > dOutMax) {
		upid[0] = upid[0] - (*dOut - dOutMax) / Dpid[0][0];
	} else if (*dOut < -dOutMax) {
		upid[0] = upid[0] - (*dOut + dOutMax) / Dpid[0][0];
	}
	// Re-calculate
	ctrl_math_output(Cpid[0], xpid, Dpid[0], upid, dOut, 2, 1, 1);
	ctrl_math_state(Apid[0], xpid, Bpid[0], upid, xpid, 2, 1);
}

void func_pd(double dIn, double *dOut) {
	double upd[1] = { dIn };
	ctrl_math_output(Cpd[0], xpd, Dpd[0], upd, dOut, 1, 1, 1);
	ctrl_math_state(Apd[0], xpd, Bpd[0], upd, xpd, 1, 1);
}

void func_pd_awu(double dIn, double *dOut, double dOutMax) {
	double upd[1] = { dIn };
	double xpd_next[1] = {0};
	ctrl_math_output(Cpd[0], xpd, Dpd[0], upd, dOut, 1, 1, 1);
	ctrl_math_state(Apd[0], xpd, Bpd[0], upd, xpd_next, 1, 1);
	// Anti Wind-Up
	if (*dOut > dOutMax) {
		upd[0] = upd[0] - (*dOut - dOutMax) / Dpd[0][0];
	} else if (*dOut < -dOutMax) {
		upd[0] = upd[0] - (*dOut + dOutMax) / Dpd[0][0];
	}
	// Re-calculate
	ctrl_math_output(Cpd[0], xpd, Dpd[0], upd, dOut, 1, 1, 1);
	ctrl_math_state(Apd[0], xpd, Bpd[0], upd, xpd, 1, 1);
}

void func_LFmath(double dIn, double *dOut) {
	double uLFmath[1] = { dIn };
	ctrl_math_output(CLFmath[0], xLFmath, DLFmath[0], uLFmath, dOut, 2, 1, 1);
	ctrl_math_state(ALFmath[0], xLFmath, BLFmath[0], uLFmath, xLFmath, 2, 1);
}
void func_INVQmath(double dIn, double *dOut) {
	double uINVQmath[1] = { dIn };
	ctrl_math_output(CINVQmath[0], xINVQmath, DINVQmath[0], uINVQmath, dOut, 2, 1, 1);
	ctrl_math_state(AINVQmath[0], xINVQmath, BINVQmath[0], uINVQmath, xINVQmath, 2, 1);
}
