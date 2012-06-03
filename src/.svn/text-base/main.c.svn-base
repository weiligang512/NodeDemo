/*stc12c5A60s2 MCU
* 晶振 ：11.0592MHz
*/


#include "STC_NEW_8051.H"
#include <stdio.h>
#include <string.h>
#include "type.h"
#include "uart.h"
#include "delay.h"
#include "cpu.h"
#include "irda.h"
#include "1602.h"
#include "ds1302.h"
#include "DHT11.h"
#include "comm.h"
#include "EEPROM.h"
#include "ADC.h"


IrData_Typ idata IrData;
uint8 tmp = 0;
uint8 sum = 0;

extern volatile IIrData_Typ xdata IIrData;
extern volatile ADCValue_Type ADCValue;

uint8 code Oncode[] = {0x4b, 0x00, 0x20, 0x50, 0x12, 0x11, 0x21, 0x00, \
					0x80};

uint8 code Offcode[] = {0x12, 0x02, 0xa0, 0x50, 0x04, 0x10, 0x20, 0x00, 0x10};

                    //秒    分    时    日    月  星期    年
uint8 code init[] = {0x10, 0x12, 0x23, 0x01, 0x01, 0x05, 0x10};
uint8 xdata now[8];
uint8 xdata rtc[17];




void main(void)
{
	unsigned char i;
	bit f = 0;


	SysInit();
	Delay1ms(100);

	#if !USER485
	DispSysPara();
	#else
	DispSysPara485();
	#endif

	while (1)
	{
		Delay1ms(100);
		Delay1ms(100);
	
		CommCmd();

		if (IIrData.FrameOK)
		{
			IIrData.FrameOK = 0;
			IrGetData(&IrData);
			//prints("@");
			for (i = 0; i < 9; i++)
			{
			//	EA = 0;
				
			//	printi485((uint16)IrData.IrData.ucIrData[i], 16);
			//	printi(i, 16);
			//	printi(IIrData.uiIrData[i], 10);
			//	prints(" ");
			//	;
			//	EA = 1;
			}
			

		}

		
		if (f)
		{
			if (i == 'A')
			{
				LCD_disp("1", 0);
			}
			IrSendFrame(Oncode);
			stc_uart_getbyte();
			Delay100ms(1);
		}
		sys_handler();
	}

}

