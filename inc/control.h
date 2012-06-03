#ifndef __CONTROL_H__
#define __CONTROL_H__

#include "type.h"
#include "EEPROM.h"



#define DEFAULTUID		0x0001


/****************��ϵͳ�����йصĵ�ַ����***********************/
#define  SYSPARAMETERLEN			16						//System Parameter length
#define  SYSPARASTARTADDRESS		SECTOR1_STARTADDRESS	//System Parameter Start Address

#define  SYSUIDSTARTADDRESS			SECTOR1_STARTADDRESS	//ϵͳUID
#define  SYSUIDADDRESSLEN			2	

#define  SYSBAUDRATESTARTADDRESS	SYSUIDSTARTADDRESS + SYSUIDADDRESSLEN	 //System Baud rate
#define  SYSBAUDRATEADDRESSLEN		2		

#define  SYSPARAMETERBUFF			SECTOR2_STARTADDRESS	//System Buffer Start Address
#define  SYSBUFFFLAG				SECTOR2_ENDADDRESS - SYSPARAMETERLEN //System Buffer Flag

/**************************************************************/


/*************************�ṹ��ö�����Ͷ���*******************/
typedef enum _SysErrorCode
{
	Sys_OK = 0x00,
	Sys_ParaError,
	
	//����......
	Sys_UnKnown
}SysErrorCode_Type;

/**************************************************************/

bool SetSysParameter(uint8 *Para);
bool SysInit(void);
void DispSysPara(void);
void DispSysPara485(void);


#endif