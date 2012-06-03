#ifndef __1602_H__
#define __1602_H__
//sfr P4		=0xc0;
#define LCD P0
sbit RS=P2^4;
sbit RW=P2^5;
sbit EN=P2^6;

void delay_1ms(unsigned int t); //延时1MS
void LCD_wbyt(unsigned char dat,unsigned char SR);  //SR=0写指令,SR=1写数据 
void LCD_init(void);  //LCD初始化
void LCD_disp(unsigned char *p,unsigned char row);//LCD显示

#endif
