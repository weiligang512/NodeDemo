#ifndef __CONTROL_H__
#define __CONTROL_H__

#include "type.h"
#include "EEPROM.h"



#define DEFAULTUID		0x0001


/****************与系统参数有关的地址定义***********************/
#define  SYSPARAMETERLEN			16						//System Parameter length
#define  SYSPARASTARTADDRESS		SECTOR1_STARTADDRESS	//System Parameter Start Address

#define  SYSUIDSTARTADDRESS			SECTOR1_STARTADDRESS	//系统UID
#define  SYSUIDADDRESSLEN			2	

#define  SYSBAUDRATESTARTADDRESS	SYSUIDSTARTADDRESS + SYSUIDADDRESSLEN	 //System Baud rate
#define  SYSBAUDRATEADDRESSLEN		2		

#define  SYSPARAMETERBUFF			SECTOR2_STARTADDRESS	//System Buffer Start Address
#define  SYSBUFFFLAG				SECTOR2_ENDADDRESS - SYSPARAMETERLEN //System Buffer Flag

/**************************************************************/


/*************************结构与枚举类型定义*******************/
typedef enum _SysErrorCode
{
	Sys_OK = 0x00,
	Sys_ParaError,
	
	//其他......
	Sys_UnKnown
}SysErrorCode_Type;

/**************************************************************/

bool SetSysParameter(uint8 *Para);
bool SysInit(void);
void DispSysPara(void);
void DispSysPara485(void);


#endif