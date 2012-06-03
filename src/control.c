#include "STC_NEW_8051.H"
#include "type.h"
#include "config.h"
#include "control.h"
#include "uart.h"
#include "delay.h"
#include "cpu.h"
#include "irda.h"
#include "1602.h"
#include "ds1302.h"
#include "DHT11.h"
#include "comm.h"


SysParameter_Tyep SysParatmeter;	//系统参数结构
SysErrorCode_Type SysErrorCode;		//系统错误代码

/*****************************************************************
*FunctionName	: SysparameterInit()
*Description	: System Parameter Initialize
*EntryParameter	: None
*ReturnValue	: TRUE: 成功，FLASE：失败
*****************************************************************/
static bool SysParameterInit(void)
{
	uint8 xdata TmpBuff[16];
	uint8 xdata TmpBuff1[16];
	uint8 Flag;
	uint8 i;

	IAPRead(SYSBUFFFLAG, &Flag, 1);			 //Write Flag
	if (0xf0 == Flag)						 //上次设置参数断电或其他问题
	{
		IAPRead(SYSPARAMETERBUFF, TmpBuff, SYSPARAMETERLEN);
		IAPProgram(SYSPARASTARTADDRESS, TmpBuff, SYSPARAMETERLEN);	// Store with Parameter
		Flag = 0x00;
		IAPProgram(SYSBUFFFLAG, &Flag, 1);			 //Write Flag
		IAPRead(SYSPARASTARTADDRESS, TmpBuff1, SYSPARAMETERLEN);	 //读出原来的参数
		for (i = 0; i < SYSPARAMETERLEN; i++)					//校验一次
		{
			if (TmpBuff[i] != TmpBuff1[i])
			{
				break;											//校验失败
			}
		} 
		if (i != SYSPARAMETERLEN)
		{
			SysErrorCode = Sys_ParaError;					  //系统参数代码为系统参数错误
			return FALSE;
		}		
	}

	IAPRead(SYSUIDSTARTADDRESS, (uint8 *)&SysParatmeter.SysUID, SYSUIDADDRESSLEN); //读UID
	if (SysParatmeter.SysUID == 0 || SysParatmeter.SysUID == 0xffff)
	{
		SysParatmeter.SysUID = DEFAULTUID;
	}

	IAPRead(SYSBAUDRATESTARTADDRESS, (uint8 *)&SysParatmeter.BaudRate, SYSBAUDRATEADDRESSLEN); //读波特率
	if (SysParatmeter.BaudRate == 0 || SysParatmeter.BaudRate == 0xffff)
	{
		SysParatmeter.BaudRate = DEFAULTBAUDRATE;		
	}
	SetBaudRate(SysParatmeter.BaudRate);	//更新波特率

	return TRUE;
}


/*****************************************************************
*FunctionName	: SetSysParameter(uint8 *Para)
*Description	: 设置系统参数，先将参数存储到EEPROM缓存，然后再更改
*EntryParameter	: 系统参数 16字节
*ReturnValue	: TRUE：成功，FLASE：失败
*****************************************************************/
bool SetSysParameter(uint8 *Para)
{
	uint8 TmpBuff[16];
	uint8 WriteFlag = 0xf0;
	uint8 i;

	IAPEraseSector(SYSPARAMETERBUFF);  //Erase System Parameter Buffer
	IAPProgram(SYSPARAMETERBUFF, Para, SYSPARAMETERLEN);	//Store with Buffer
	IAPProgram(SYSBUFFFLAG, &WriteFlag, 1);			 //Write Flag
	IAPRead(SYSPARASTARTADDRESS, TmpBuff, SYSPARAMETERLEN);	 //读出原来的参数
	if (*(uint16 *)&Para[0] != 0) 	//设置了UID
	{
		TmpBuff[0] = Para[0];
		TmpBuff[1] = Para[1];	
	}
	if (*(uint16 *)&Para[2] != 0)  //设置了波特率
	{
		TmpBuff[2] = Para[2];
		TmpBuff[3] = Para[3];	
	}
	//其他参数.........

	IAPEraseSector(SECTOR1_STARTADDRESS);  //Erase System Parameter
	IAPProgram(SYSPARASTARTADDRESS, TmpBuff, SYSPARAMETERLEN);	// Store with Parameter
	WriteFlag = 0x00;
	IAPProgram(SYSBUFFFLAG, &WriteFlag, 1);			 //Write Flag

	IAPRead(SYSPARASTARTADDRESS, Para, SYSPARAMETERLEN);	 //读出原来的参数
	for (i = 0; i < SYSPARAMETERLEN; i++)
	{
		if (TmpBuff[i] != Para[i])
		{
			break;
		}
	} 
	if (i == SYSPARAMETERLEN)
	{
		return SysParameterInit();
	}

	return FALSE;	
}


/*****************************************************************
*FunctionName	: SysInit()
*Description	: 系统初始化
*EntryParameter	: None
*ReturnValue	: TRUE：成功，FLASE：失败
*****************************************************************/
bool SysInit(void)
{
	SysErrorCode = Sys_OK;

	SysParameterInit();
	DS1302_Initial();
	LCD_init();
	CPUInit();
	RS485RxENABLE	
}

#if !USER485
/*****************************************************************
*FunctionName	: DispSysPara()
*Description	: 串口显示系统参数
*EntryParameter	: None
*ReturnValue	: None
*****************************************************************/
void DispSysPara(void)
{
	prints("System Start.....\r\n");
	prints("System UID: ");
	printi(SysParatmeter.SysUID, 10);
	prints("\r\n");
	prints("System Baud Rate: ");
	printi(SysParatmeter.BaudRate, 10);
	prints("\r\n");
}
#else
/*****************************************************************
*FunctionName	: DispSysPara484()
*Description	: 串口485显示系统参数
*EntryParameter	: None
*ReturnValue	: None
*****************************************************************/
void DispSysPara485(void)
{
	prints485("System Start.....\r\n");
	prints485("System UID: ");
	printi485(SysParatmeter.SysUID, 10);
	prints485("\r\n");
	prints485("System Baud Rate: ");
	printi485(SysParatmeter.BaudRate, 10);
	prints485("\r\n");
}
#endif



