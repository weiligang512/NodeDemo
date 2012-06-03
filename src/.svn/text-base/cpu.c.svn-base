/*stc89c52 MCU
* 晶振 ：11.0592MHz
* 波特率 ：9600
* 通讯方式 ：N81
*/

#include "STC_NEW_8051.H"
#include "type.h"
#include "cpu.h"
#include "uart.h"
#include "comm.h"
#include "ADC.h"


uint8 const BaudRateCode[4] = {0X70, 0XB8, 0XDC, 0XEE};	//2400, 4800, 9600, 19200 bps

extern volatile unsigned int SysTimeBase;
extern volatile bit SysTimeFlag;
extern volatile IIrData_Typ xdata IIrData;
extern volatile uint16 data SysBase;
extern volatile uint16 data SysCount;
extern volatile bit IRFlag;

volatile int8 CommReciveSuccess = 0;

uint8 xdata CommReciveBuff[COMMRECIVEBUFFLEN] = {0};
uint8 xdata CommSendBuff[COMMSENDBUFFLEN] = {0};
vuint8 CommReciveCur = 0; //数据当前位置

bit CommReciveFlag = 0;
bit ReciveStart = 0;
volatile uint16 CommReciveTimeOut = 0; 


/********************************************************/
/*************************串口***************************/
/********************************************************/
void SetBaudRate(uint16 BaudRate)
{
	uint8 index;

	switch (BaudRate)
	{
		case BAUDRATE2400 :
			index = BAUDRATEINDEX2400;
		break;
		
		case BAUDRATE4800 :
			index = BAUDRATEINDEX4800;
		break;
		
		case BAUDRATE9600 :
			index = BAUDRATEINDEX9600;
		break;
		
		case BAUDRATE19200 :
			index = BAUDRATEINDEX19200;
		break;
		
		default :
			index = DEFAULTBAUDRATEINDEX;		
	}
	BRT = BaudRateCode[index];	
}

static void stc_uart_init(void)
{		
	PCON &= 0x7F;				//波特率不倍速
	SCON = 0x50;				//8位数据,可变波特率
	AUXR |= 0x04;				//独立波特率发生器时钟为Fosc,即1T
//	SetBaudRate(BAUDRATE9600);		//设定独立波特率发生器重装值
	AUXR |= 0x01;				//串口1选择独立波特率发生器为波特率发生器
	AUXR |= 0x10;				//启动独立波特率发生器
	RI = 0;
	TI = 0;
	ES = 1;
}

void stc_uart_sendbyte(int8 cData)
{
	SBUF = cData;

	while (!TI);	
	
	TI = 0;
}

int8 stc_uart_getbyte(void)
{
	REN = 1;

	while (!RI);
	
	RI = 0;
	REN = 0;

	return SBUF;
}

void stc_uart_int(void) interrupt 4 using 3
{
	if (TI)
	{
		TI = 0;
		return ;
	}

	if (RI)
	{
		RI = 0;
		CommReciveBuff[CommReciveCur] = SBUF;
		CommReciveCur++;

		CommReciveFlag = 1;
		CommReciveTimeOut = 0;
		if (CommReciveCur == 2)
		{
			if ((CommReciveBuff[0] == COMMHEAD1) &&\
				CommReciveBuff[1] == COMMHEAD2)
			{
				ReciveStart = 1;
			}
			else
			{
				CommReciveCur = 0;
			}	
		}
		
		if (ReciveStart)
		{
			if (CommReciveCur == CommReciveBuff[2])
			{
				CommReciveSuccess = 1;
				ReciveStart = 0;
				CommReciveCur = 0;
				ES = 0;	
			}
		}

		CommReciveCur &= 0x1f; //接收数据为32字节
	}	
}

/********************************************************/


/********************************************************/
/*************************ADC***************************/
/********************************************************/
/*----------------------------
Software delay function
----------------------------*/
static void Delay(uint16 n)
{
    uint16 x;

    while (n--)
    {
        x = 5000;
        while (x--);
    }
}

/*----------------------------
Initial ADC sfr
----------------------------*/
void InitADC(void)
{
    P1ASF = ADC_CHENABLE;                   //Set all P1 as analog input port
	AUXR1 |= (1<<2);					//ADRJ=1，10 位A/D 转换结果的最高2 
										//位放在ADC_RES 寄存器的低2 位, 
										//低8 位放在ADC_RESL 寄存器
    ADC_RES = 0;                    //Clear previous result
	ADC_RESL = 0;
    ADC_CONTR = ADC_POWER | ADC_SPEEDH | ADC_START | ADC_CH;
	EADC = 1;						//enable ADC intrrupt
    Delay(2);                       //ADC power-on delay and Start A/D conversion
}

/*----------------------------
ADC interrupt service routine
----------------------------*/
void adc_int(void) interrupt 5 
{
    ADC_CONTR &= !ADC_FLAG;         //Clear ADC interrupt flag
	ADCHandler(ADC_RESL, ADC_RES);
    ADC_CONTR = ADC_POWER | ADC_SPEEDLL | ADC_START | ADC_CH;
}

/********************************************************/

/********************************************************/
/*************************PCA0***************************/
/********************************************************/
//PCA0用于捕获红外接收头脉冲宽度
static void stc_PCA0_Init(void)
{
	CCON = 0x00;
	CMOD = 0x00;		//设PCA时钟位系统1/12
	CCAPM0 = 0x31;     //16位捕获模式，下，上降沿触发 ,允许中断
	CL = 0x00;
	CH = 0x00;
	CCAP0L = 0x00;
	CCAP0H = 0x00;
	CR = 1;				//启动PCA
}

//PCA1用于产生38K脉冲，用于发送红外码
void stc_PCA1_Init(void)
{
	CCON = 0X00;
	CMOD = 0X08;	//设PCA时钟位系统
	CCAPM1 = 0x00;  //设置为高速脉冲输出模式 ，关闭比较位
	CL = 0X00;
	CH = 0X00;
	CCAP1L = 0X41;  //设置为频率38k，f=SYSclk/12*2*CCAP1;
	CCAP1H = 0X00;
	CR = 1;         //启动PCA计数
	P1M0 = 0x10;
	P1M1 = 0x00;
	IR = 1;			//红外发射为1
}
/********************************************************/


/********************************************************/
/*************************定时器0************************/
/********************************************************/
void stc_time0_init(void)  //50ms微秒@11.0592MHz
{
	AUXR &= 0x7F;		//定时器时钟12T模式
	TMOD &= 0xF0;		//设置定时器模式
	TMOD |= 0x01;		//设置定时器模式
	TL0 = 0x00;		//设置定时初值
	TH0 = 0x4C;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时
	ET0=1;    		//开中断
	TR0 = 1;		//定时器0开始计时
}

void stc_time0_int(void) interrupt 1 using 1
{
	TF0 = 0;
	TL0 = 0x00;		//设置定时初值
	TH0 = 0x4C;		//设置定时初值
	SysTimeBase++;
	if (SysTimeBase >= SYSTIMEBASEMAX)
	{
		SysTimeFlag = 1;
		SysTimeBase = 0;
	}

	if (CommReciveFlag)
	{
		CommReciveTimeOut++;
		if (COMMRECIVETIMROUT <= CommReciveTimeOut)
		{
			CommReciveFlag = 0;
			CommReciveCur = 0;
			ReciveStart = 0;
			CommReciveSuccess = 0;
		}	
	}
}
/********************************************************/


/********************************************************/
/*************************外部中断0**********************/
/********************************************************/
#if 0
void stc_exti0_init(void)
{
//	IT0 = 1;   //指定外部中断0下降沿触发，INT0 (P3.2)
// 	EX0 = 1;   //使能外部中断
// 	EA = 1;    //开总中断
}

void stc_exti0_handler(void)  interrupt 0 using 0
{


}

void stc_exti1_int(void)	interrupt 2 using 2
{

}
#endif

/*****************************************************************
*FunctionName	: stc_PCA_int(void) interrupt 7
*Description	: System Parameter Initialize
*EntryParameter	: None
*ReturnValue	: None
*****************************************************************/
void stc_PCA_int(void) interrupt 7
{
	static unsigned char start = 0;
	static unsigned char i = 0;
	static unsigned char heard = 0;
	unsigned int uiTmpData;

	if (CCF1)
	{
		CCF1 = 0;
		CL = 0;
		CH = 0;

		return;
	}

	if (CCF0)
	{
		CCF0 = 0;
		uiTmpData = (unsigned int)CCAP0L + ((unsigned int)CCAP0H << 8);
	    IIrData.uiIrHeard[heard] = uiTmpData;
		CL = 0;
		CH = 0;
	
		if (IIrData.uiIrHeard[heard] >8000 && IIrData.uiIrHeard[heard] < 8500)
		{
			heard++;
			start = 0;
	
			return;
		}
		if (heard)
		{
			if (IIrData.uiIrHeard[heard] >3800 && IIrData.uiIrHeard[heard] < 4400)
			{
				start = 1;
				i = 0;
				heard = 0;
		
				return;
			}
		}
		
		if (!start)
		{
			if (!heard)
			{
				heard = 0;
			}
			else
			{
				heard++;
			}
	
			return;
		}
	
		if (start)
		{
			IIrData.uiIrData[i] = uiTmpData;
			
			i++;
			if (i > 136)
			{
			//	prints("d");
				i = 0;
				start = 0;
				IIrData.FrameOK = 1;
			}
		}
	}
}

/********************************************************/

/********************************************************/
void CPUInit(void)
{
	CLK_DIV = 0x00;
	stc_uart_init();
	stc_time0_init();
	stc_PCA1_Init();
	stc_PCA0_Init();
	InitADC();
	EA = 1;
}

void sys_handler(void)
{
	SysTimeFlag = 0;
}


/********************************************************/