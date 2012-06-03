#ifndef __CPU_H__
#define __CPU_H__



/******************与串口通讯相关的宏*******************/
#define COMMRECIVEBUFFLEN	32	   //串口接收缓存大小
#define COMMSENDBUFFLEN		32	   //串口发送缓存大小

#define COMMRECIVETIMROUT 	20	   //串口接收超时 20 * 50ms


#define BAUDRATE2400		2400    //2400bps
#define BAUDRATE4800		4800    //4800bps
#define BAUDRATE9600		9600    //9600bps
#define BAUDRATE19200		19200    //19200bps

#define BAUDRATEINDEX2400		0    //2400bps
#define BAUDRATEINDEX4800		1    //4800bps
#define BAUDRATEINDEX9600		2    //9600bps
#define BAUDRATEINDEX19200		3    //19200bps

#define DEFAULTBAUDRATEINDEX		BAUDRATEINDEX9600		//9600bps
#define DEFAULTBAUDRATE				BAUDRATE9600

/********************************************************/
/***************与系统定时器相关的宏*********************/
/********************************************************/
//系统时基最大数
#define SYSTIMEBASEMAX (0x7fff)

//清除定时器完成标志位
#define SysTimeFlagClear(Flag) 	Flag &= ~(0x3 << 1) 
/********************************************************/

/********************************************************/
/**********************与PCA相关的宏*********************/
/********************************************************/
//使能PCA0捕获	16位捕获模式，下，上降沿触发 ,允许中断
#define ENABLEPCA0		CMOD = 0x00; CCAPM0 = 0x31; CR = 1;
//失能PCA0捕获
#define DISABLEPCA0		CCAPM0 = 0x00; CR = 0;

//使能PCA1高速脉冲输出
#define ENABLEPOT 	CMOD = 0X08; CCAPM1 = 0x4d; CL = 0x00; CH = 0x00; CR = 1;
//失能PCA1高速脉冲输出
#define DISABLEPOT	CCAPM1 = 0x00; CR = 0;

/********************************************************/

void SetBaudRate(uint16 BaudRate);
void stc_uart_sendbyte(int8 cData);
int8 stc_uart_getbyte(void);

void CPUInit(void);
void sys_handler(void);

#endif