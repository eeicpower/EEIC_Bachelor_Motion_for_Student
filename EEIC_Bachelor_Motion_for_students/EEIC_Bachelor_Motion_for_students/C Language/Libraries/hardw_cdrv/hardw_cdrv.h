/************************************************************************************
MOTOR POWER-ELEC MODULE
-----------------------
Descr.:		hardware module for current driver
Boards:		PMAC CK3E
PWelec:		ServoTechno **
Author:		Yui Shirato
			Koseki Lab, University of Tokyo, 2018
************************************************************************************/

#ifndef	HARDW_CDRV_H
#define	HARDW_CDRV_H




/*	READ MOTOR ADC DATA
**	-------------------
**	DES:指令値電圧を実際に出す（DA）	
**	INP:指令値の電圧	
**	OUT:なし
*/
void hardw_vref(double vref);

/*	HARDW ANGLE
**	-------------------
**	DES:angle[deg]とPMACの変な値を対応させる	
**	INP:angle[deg]	
**	OUT:angle_[num]
*/
void hardw_angle_fromdeg_tonum(double deg, double *out);
void hardw_angle_fromnum_todeg(double num, double *out);


#endif
