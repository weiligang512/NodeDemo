/*stc89c52 MCU
* 晶振 ：11.0592MHz
* 波特率 ：9600
* 通讯方式 ：N81
*/


#include "STC_NEW_8051.H"
#include "type.h"
#include "uart.h"
#include "cpu.h"


	

static int8 code HexA_F[] = "ABCDEF";


static int8 *itoa(int8 *Buff, uint16 Data)
{
	Buff[4]	= Data % 10 + '0';
	Buff[3]	= (Data % 100) / 10	+ '0';
	Buff[2]	= (Data % 1000) / 100 + '0';
	Buff[1]	= (Data % 10000) / 1000 + '0';
	Buff[0]	= (Data % 100000) / 10000 + '0';
	Buff[5]	= 0;

	return Buff;
}

static int8 *itox(int8 *Buff, uint16 Data)
{
	int8 i;

	Buff[0] = '0';
	Buff[1]	= 'X';
	for (i = 0; i < 4; i++)
	{
		Buff[i+2] = (Data % (0x10000 >> i*4)) / (0x10000 >> (i+1)*4) + '0';
		if (Buff[i+2] >= 10 + '0')
		{
			Buff[i+2] = HexA_F[Buff[i+2] - 10 - '0'];	
		}
	}
	Buff[i+2] = 0;
}

#if !USER485	//使用RS232
void prints(int8 *s)
{
	while (*s)
	{
		stc_uart_sendbyte(*s++);
	}
}

void Puts(int8 *s, uint8 len)
{
	while (len--)
	{
		stc_uart_sendbyte(*s++);
	}
}

void printi(uint16 Data, int8 f)
{
	int8 data buff[8];
	
	switch (f)
	{
		case 10 :
			itoa(buff, Data);
			prints(buff);
		break;
		
		case 16 :
			itox(buff, Data);
			prints(buff);
		break;
		
		default :
		break;		
	}
}
#endif

#if USER485					 //定义了使用RS485
void RS485SendByte(int8 Data)
{
	RS485TxENABLE
	stc_uart_sendbyte(Data);
	RS485RxENABLE	
}

int8 RS485ReciveByte(void)
{
	RS485RxENABLE
	stc_uart_getbyte();
}


void Puts485(int8 *s, uint8 len)
{
	while (len--)
	{
		RS485SendByte(*s++);
	}
}

void prints485(int8 *s)
{
	while (*s)
	{
		RS485SendByte(*s++);
	}
}

void printi485(uint16 Data, int8 f)
{
	int8 data buff[8];
	
	switch (f)
	{
		case 10 :
			itoa(buff, Data);
			prints485(buff);
		break;
		
		case 16 :
			itox(buff, Data);
			prints485(buff);
		break;
		
		default :
		break;		
	}
}
#endif
