#include <gplib.h>   // Global Gp Shared memory pointer
//----------------------------------------------------------------------------------
// pp_proj.h is the C header for accessing PMAC Global, CSGlobal, Ptr vars
// _PPScriptMode_ for Pmac Script like access global & csglobal
// global Mypvar - access with "Mypvar"
// global Myparray(32) - access with "Myparray(i)"
// csglobal Myqvar - access with "Myqvar(i)" where "i" is Coord #
// csglobal Myqarray(16) - access with "Myqvar(i,j)" where "j" is index
// _EnumMode_ for Pmac enum data type checking on Set & Get global functions
// Example
// global Mypvar
// csglobal Myqvar
// "SetGlobalVar(Myqvar, data)" will give a compile error because its a csglobal var.
// "SetCSGlobalVar(Mypvar, data)" will give a compile error because its a global var.
//------------------------------------------------------------------------------------
//#define _PPScriptMode_	// uncomment for Pmac Script type access
// #define _EnumMode_			// uncomment for Pmac enum data type checking on Set & Get global functions		// uncomment for Pmac Script type access
#define _PP_PROJ_HDR_
#include "../../Include/pp_proj.h"
#include "ctrl_chirp.h"
#include <math.h>

// チャープサインの式に使える定数集
#define F0 (0.1)  //initial frequency[Hz]
#define FF (500)  //final frequency [Hz]
#define AMP (1)   //amplitude [Nm]
#define LEN (20)  //chirptime [s]

double k = pow(1.0*FF/F0, 1.0/LEN);	// rate of frequency change
double phi = 0;

void ctrl_chirp(double timer, double *out){
	while(timer > LEN){
		timer -= LEN;
	}
	// ここにチャープの式を書く。
	// See English Wikipedia
	phi = 2 * M_PI * F0 * (pow(k,timer)-1) / log(k); //[rad]
	*out = AMP * sin(phi);
}