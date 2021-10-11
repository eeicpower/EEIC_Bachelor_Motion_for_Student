/************************************************************************************
FUNCTION MODULE
----------------------
Descr.:		setting gain of FF controller 
Boards:		
Author:		Yui Shirato
Koseki Lab, University of Tokyo, 2018
*************************************************************************************/


#ifndef CTRL_FUNC_H
#define	CTRL_FUNC_H

#include "ctrl_para.h"

void func_pid(double dIn, double *dOut);
void func_pd(double dIn, double *dOut);
void func_LFmath(double dIn, double *dOut);
void func_INVQmath(double dIn, double *dOut);

#endif
