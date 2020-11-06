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
#include "ctrl_step.h"

void ctrl_step_input(double A, double steptime, double t_step, double *out)
{
	if (t_step < steptime) {
		*out = 0;
	} else {
		*out = A;
	} 
}

void ctrl_step_input_with_end(double A, double begintime, double finitime, double t_step, double *out)
{
	if (t_step < begintime || t_step > finitime) {
		*out = 0;
	} else {
		*out = A;
	} 
}