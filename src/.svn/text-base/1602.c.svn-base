#include "STC_NEW_8051.H"
#include "type.h"
#include <intrins.h>
#include "1602.h"


void delay_1ms(unsigned int t) //延时0.5MS
{
	unsigned int i;
	while(t--)
	{
		for(i=0;i<60;i++);
	}		
}

void LCD_wbyt(unsigned char dat,unsigned char SR)  //SR=0写指令,SR=1写数据 
{
	EN=0;
	RS=SR;
	RW=0;
	LCD=dat;
	delay_1ms(5);
	EN=1;
	delay_1ms(10);
	EN=0;
}

void LCD_init(void)  //LCD初始化
{
	delay_1ms(30);
	LCD_wbyt(0x38,0);
	delay_1ms(10);
	LCD_wbyt(0x38,0);
	delay_1ms(10);
	LCD_wbyt(0x38,0);
	LCD_wbyt(0x38,0);
	LCD_wbyt(0x08,0);
	LCD_wbyt(0x01,0);
	LCD_wbyt(0x06,0);
	LCD_wbyt(0x0c,0);
}

void LCD_disp(unsigned char *p,unsigned char row)//LCD显示
{
	unsigned char i;

	LCD_wbyt(0x80+0x40*(row & 0x01),0);
	while (*p)
	{
		LCD_wbyt(*p++, 1);
	}
}
