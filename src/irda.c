/*stc12c5A60s2 MCU
* ���� ��11.0592MHz
*/

#include "STC_NEW_8051.H"
#include <intrins.h>
#include "type.h"
#include "irda.h"
#include "uart.h"
#include "cpu.h"
#include "delay.h"


volatile IIrData_Typ xdata IIrData = {0};
volatile uint16 data SysBase = 0;
volatile uint16 data SysCount = 0;
volatile bit IRFlag = 0;

void IrGetData(IrData_Typ *IrData)
{
	int8 i, j;

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 8; j++)
		{
			//11.0592M����PCA����ʱ��Ϊϵͳʱ��1/12
			//921������Ϊ1ms��516������Ϊ0.56ms	 ��1556������Ϊ1.69ms
			//0.56ms+0.56ms ��ʾ0
			if ((IIrData.uiIrData[i*16+j*2] >= 480 && IIrData.uiIrData[i*16+j*2] <= 680) && \
				(IIrData.uiIrData[i*16+j*2+1] >= 480 && IIrData.uiIrData[i*16+j*2+1] <= 600)) //1.12ms 0
			{
				IrData->IrData.ucIrData[i] >>= 1;	
			}
			//0.56+1.69ms ��ʾ1
			if ((IIrData.uiIrData[i*16+j*2] >= 480 && IIrData.uiIrData[i*16+j*2] <= 680) && \
				(IIrData.uiIrData[i*16+j*2+1] >= 1450 && IIrData.uiIrData[i*16+j*2+1] <= 1600)) //1.12ms 0
			{
				IrData->IrData.ucIrData[i] >>= 1;
				IrData->IrData.ucIrData[i] |= (0x80);	
			}   
		}
	}
	IrData->IrData.ucIrData[i] = 0x02; 

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 8; j++)
		{
			//11.0592M����PCA����ʱ��Ϊϵͳʱ��1/12
			//921������Ϊ1ms��516������Ϊ0.56ms	 ��1556������Ϊ1.69ms
			//0.56ms+0.56ms ��ʾ0
			if ((IIrData.uiIrData[72+i*16+j*2] >= 480 && IIrData.uiIrData[72+i*16+j*2] <= 680) && \
				(IIrData.uiIrData[72+i*16+j*2+1] >= 480 && IIrData.uiIrData[72+i*16+j*2+1] <= 600)) //1.12ms 0
			{
				IrData->IrData.ucIrData[5+i] >>= 1;	
			}
			//0.56+1.69ms ��ʾ1
			if ((IIrData.uiIrData[72+i*16+j*2] >= 480 && IIrData.uiIrData[72+i*16+j*2] <= 680) && \
				(IIrData.uiIrData[72+i*16+j*2+1] >= 1450 && IIrData.uiIrData[72+i*16+j*2+1] <= 1600)) //1.12ms 0
			{
				IrData->IrData.ucIrData[5+i] >>= 1;
				IrData->IrData.ucIrData[5+i] |= (0x80);	
			}   
		}
	}
}


#if 1
//���������룬9ms
static void IrSendHeard(void)
{
	ENABLEPOT;
	Delay100us(12);
	Delay5us(1);
	IR = 1;
	IR = 1;
	DISABLEPOT;
	Delay100us(43);
	Delay10us(5);
}

static void IrSendEnd(void)
{
	ENABLEPOT;
	Delay100us(0);
	Delay10us(3);
	IR = 1;
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	DISABLEPOT;
}

static void IrSendByte(uint8 Data)
{
	int8 i, t;

	for (i = 0; i < 8; i++)
	{
		ENABLEPOT;
	//	Delay100us(0);
		Delay10us(3);
		Delay5us(0);
		Delay5us(0);
		IR = 1;
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		DISABLEPOT;
		((Data >> i) & 0x01) ? (t=15) : (t = 4);
		Delay100us(t);
		Delay10us(5);
	} 
}

#if 0
void IrSendRepeat(void)
{
	ENABLEPOT;
	Delay100us(90);
	DISABLEPOT;
	Delay100us(23);	
}
#endif

void IrSend20ms(uint8 Data)
{
	int8 i, t;

	for (i = 0; i < 3; i++)
	{
		ENABLEPOT;
	//	Delay100us(0);
		Delay10us(3);
		Delay5us(0);
		Delay5us(0);
		IR = 1;
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		DISABLEPOT;
		((Data >> i) & 0x01) ? (t=15) : (t = 4);
		Delay100us(t);
		Delay10us(5);
	}
	ENABLEPOT; 
//	Delay100us(0);
	Delay10us(3);
	Delay5us(0);
	Delay5us(0);
	IR = 1;
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	DISABLEPOT;
	Delay100us(197);
	Delay100us(1);	
}

void IrSendFrame(uint8 *Data)
{
	uint8 i;

	DISABLEPCA0
	ENABLEPOT
	ET0 = 0;
	IrSendHeard();

	for (i = 0; i < 9; i++)
	{
		if (i == 4)
		{
			IrSend20ms(Data[i]&0x07);
			continue;
		}
		IrSendByte(Data[i]);
	}
	IrSendEnd();
	ET0 = 1;
	DISABLEPOT
	ENABLEPCA0
	IR = 1;	
}
#endif

/*****************************************************************
*FunctionName	: IrDeviceSend(uint8 *Data)
*Description	: ����Ӧ�ĺ����豸����
*EntryParameter	: Data[0]:�豸���ͣ�Data[1-9]:����������
*ReturnValue	: None
*****************************************************************/
void IrDeviceSend(uint8 *Data)
{
	switch (Data[0])
	{
		case GREE_YB0F2: 
			IrSendFrame(&Data[1]);  	
		break;

		//�����豸......
		default :
		break;
	}
}


