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
**	DES:�w�ߒl�d�������ۂɏo���iDA�j	
**	INP:�w�ߒl�̓d��	
**	OUT:�Ȃ�
*/
void hardw_vref(double vref);

/*	HARDW ANGLE
**	-------------------
**	DES:angle[deg]��PMAC�̕ςȒl��Ή�������	
**	INP:angle[deg]	
**	OUT:angle_[num]
*/
void hardw_angle_fromdeg_tonum(double deg, double *out);
void hardw_angle_fromnum_todeg(double num, double *out);


#endif
