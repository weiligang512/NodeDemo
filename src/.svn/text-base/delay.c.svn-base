#include <string.h>
#include <intrins.h>
#include "STC_NEW_8051.H"
#include "type.h"
#include "cpu.h"	
#include "delay.h"



volatile uint8 SysTimeBase = 0;
volatile bit SysTimeFlag = 0;

void Delay100ms(uint16 t)		//@11.0592MHz
{
	uint8 i, j, k;

	i = 5;
	j = 52;
	k = 195;

	while (t--)
	{
		do
		{
			do
			{
				while (--k);
			} while (--j);
		} while (--i);
	}
}

void Delay1ms(uint16 t)		//@11.0592MHz
{
	uint8 i, j;

	while (t--)
	{
		_nop_();
		i = 11;
		j = 190;
		do
		{
			while (--j);
		} while (--i);
	}	
}

void Delay5us(uint16 t)		//@11.0592MHz
{
	uint8 i;

	while (t--)
	{
		_nop_();
		_nop_();
		_nop_();
		i = 10;
		while (--i);
	}
}

void Delay10us(uint16 t)		//@11.0592MHz
{
	uint8 i;

   while (t--)
   {
		_nop_();
		_nop_();
		_nop_();
		i = 24;
		while (--i);
	}
}

void Delay100us(uint16 t)		//@11.0592MHz
{
	uint8 i, j;

	while (t--)
	{
		i = 2;
		j = 15;
		do
		{
			while (--j);
		} while (--i);
	}
}

#if 0
bit sys_delay(SysDelay_Tye *Time, unsigned int uiSet)	 //uiSet ×î´ó0x7fff
{
	if (!(Time->cFlag & (0x1 << 1)))
	{
		memset(Time, 0, sizeof (SysDelay_Tye));
		Time->uiOldTime = SysTimeBase;
		Time->cFlag |= (0x01 << 1);
	}

	if (Time->cFlag & (0x1))
	{
		return 1;
	}
	
	if (!SysTimeFlag)
	{
		Time->uiCurTime += SysTimeBase - Time->uiOldTime;
	} 
	else
	{
		Time->uiCurTime += (SYSTIMEBASEMAX - Time->uiOldTime + SysTimeBase);
	}
	Time->uiOldTime = SysTimeBase;

	if (Time->uiCurTime >= uiSet)
	{
		Time->cFlag |= 0x1;

		return 1;
	}

   	return 0;
}
#endif


