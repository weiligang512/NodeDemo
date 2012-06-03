#include "STC_NEW_8051.H"
#include "intrins.h"
#include "type.h"
#include "EEPROM.h"
#include "delay.h"



static void IAPIdel(void)
{
	IAP_CONTR = 0;
	IAP_CMD = 0;
	IAP_TRIG = 0;
	IAP_ADDRH = 0x80;
	IAP_ADDRL = 0;
}

static uint8 IAPReadByte(uint16 addr)
{
	uint8 dat;

	IAP_CONTR = ENABLE_IAP;
	IAP_CMD = CMD_READ;
	IAP_ADDRL = addr;
	IAP_ADDRH = addr >> 8;
	IAP_TRIG = 0x5a;
	IAP_TRIG = 0xa5;
	_nop_();

	dat = IAP_DATA;

	return dat;
}

static void IAPProgramByte(uint16 addr, uint8 dat)
{
	IAP_CONTR = ENABLE_IAP;
	IAP_CMD = CMD_PROGRAM;
	IAP_ADDRL = addr;
	IAP_ADDRH = addr >> 8;
	IAP_DATA = dat;
	IAP_TRIG = 0x5a;
	IAP_TRIG = 0xa5;
	_nop_();
	_nop_();
	_nop_();
}

void IAPEraseSector(uint16 addr)
{
	IAP_CONTR = ENABLE_IAP;
	IAP_CMD = CMD_ERASE;
	IAP_ADDRL = addr;
	IAP_ADDRH = addr >> 8;
	IAP_TRIG = 0x5a;
	IAP_TRIG = 0xa5;
	_nop_();
	_nop_();
	_nop_();
	IAPIdel();
}

bool IAPRead(uint16 addr, uint8 *buff, uint16 size)
{
	uint16 i;

	for (i = 0; i < size; i++)
	{
		buff[i] = IAPReadByte(addr + i);
	}
	IAPIdel();

	return TRUE;
}

bool IAPProgram(uint16 addr, uint8 *buff, uint16 size)
{
	uint16 i;

	for (i = 0; i < size; i++)
	{
		IAPProgramByte(addr + i, buff[i]);
	}
	IAPIdel();

	return TRUE;	
}




