#ifndef __1602_H__
#define __1602_H__
sfr P4		=0xc0;
#define LCD P0
sbit RS=P4^6;
sbit RW=P4^5;
sbit EN=P4^4;
void delay_1ms(unsigned int t); //��ʱ1MS
void LCD_wbyt(unsigned char dat,unsigned char SR);  //SR=0дָ��,SR=1д���� 
void LCD_init(void);  //LCD��ʼ��
void LCD_disp(unsigned char *p,unsigned char row);//LCD��ʾ

#endif
