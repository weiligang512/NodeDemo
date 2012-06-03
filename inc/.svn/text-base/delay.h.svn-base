#ifndef __DELAY_H__
#define __DELAY_H__


typedef struct
{
	unsigned int uiSetTime;	   //设置时间
	unsigned int uiCurTime;    //当前时间
	unsigned int uiOldTime;	   //上一次扫描时时间
	char 		 cFlag;		   //bit0:完成标志，1完成；bit1初始化标志 1初始化
}SysDelay_Tye;

void Delay5us(uint16 t);		//@11.0592MHz
void Delay100ms(uint16 t);		//@11.0592MHz
void Delay1ms(uint16 t);		//@11.0592MHz
void Delay10us(uint16 t);		//@11.0592MHz
void Delay100us(uint16 t);		//@11.0592MHz

bit sys_delay(SysDelay_Tye *Time, unsigned int uiSet);




#endif