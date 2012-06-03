#ifndef __UART_H__
#define __UART_H__

#include "config.h"

sbit RS485RTEN = P2^1;

#define RS485RxENABLE 	RS485RTEN = 0;
#define RS485TxENABLE	RS485RTEN = 1;

#if !USER485	   //使用RS232
void prints(int8 *s);
void Puts(int8 *s, uint8 len);
void printi(uint16 Data, int8 f);
#else			  //使用RS485
void RS485SendByte(int8 Data);
int8 RS485ReciveByte(void);
void prints485(int8 *s);
void Puts485(int8 *s, uint8 len);
void printi485(uint16 Data, int8 f);
#endif

#endif