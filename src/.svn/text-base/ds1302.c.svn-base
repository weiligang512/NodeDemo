#include "STC_NEW_8051.H"
#include <intrins.h>
#include "type.h"


sbit SCLK = P3^6;                   //DS1302时钟口P3.6
sbit IO = P3^4;                     //DS1302数据口P3.4
sbit RST = P3^5;                    //DS1302片选口P3.5


/**************************************
延时X微秒(STC12C5A60S2@12M)
不同的工作环境,需要调整此函数
此延时函数是使用1T的指令周期进行计算,与传统的12T的MCU不同
**************************************/
void Delay()
{
    _nop_();
    _nop_();
}

/**************************************
从DS1302读1字节数据
**************************************/
uint8 DS1302_ReadByte()
{
    uint8 i;
    uint8 dat = 0;

    for (i=0; i<8; i++)             //8位计数器
    {
		SCLK = 0;                   //时钟线拉低
		Delay();                //延时等待
        dat >>= 1;	                //数据右移一位
		if (IO) dat |= 0x80;        //读取数据
		SCLK = 1;                   //时钟线拉高
		Delay();                //延时等待
	}

    return dat;
}

/**************************************
向DS1302写1字节数据
**************************************/
void DS1302_WriteByte(uint8 dat)
{
    char i;

    for (i=0; i<8; i++)             //8位计数器
    {
        SCLK = 0;                   //时钟线拉低
        Delay();                //延时等待
        dat >>= 1;                  //移出数据
        IO = CY;                    //送出到端口
        SCLK = 1;                   //时钟线拉高
        Delay();                //延时等待
    }
}

/**************************************
读DS1302某地址的的数据
**************************************/
uint8 DS1302_ReadData(uint8 addr)
{
    uint8 dat;

    RST = 0;
    Delay();
    SCLK = 0;
    Delay();
    RST = 1;
    Delay();
    DS1302_WriteByte(addr);         //写地址
    dat = DS1302_ReadByte();        //读数据
    SCLK = 1;
    RST = 0;

    return dat;
}

/**************************************
往DS1302的某个地址写入数据
**************************************/
void DS1302_WriteData(uint8 addr, uint8 dat)
{
    RST = 0;
    Delay();
    SCLK = 0;
    Delay();
    RST = 1;
    Delay();
    DS1302_WriteByte(addr);         //写地址
    DS1302_WriteByte(dat);          //写数据
    SCLK = 1;
    RST = 0;
}

/**************************************
写入初始时间
**************************************/
void DS1302_SetTime(uint8 *p)
{
    uint8 addr = 0x80;
    uint8 n = 7;

	EA = 0;
    DS1302_WriteData(0x8e, 0x00);   //允许写操作
    while (n--)
    {
        DS1302_WriteData(addr, *p++);
        addr += 2;
    }
    DS1302_WriteData(0x8e, 0x80);   //写保护
	EA = 1;
}

/**************************************
读取当前时间
**************************************/
void DS1302_GetTime(uint8 *p)
{
    uint8 addr = 0x81;
    uint8 n = 7;

   EA = 0;
    while (n--)
    {
        *p++ = DS1302_ReadData(addr);
        addr += 2;
    }
	EA = 1;
}

/**************************************
初始化DS1302
**************************************/
void DS1302_Initial()
{
    RST = 0;
    SCLK = 0;
    DS1302_WriteData(0x8e, 0x00);   //允许写操作
//    DS1302_WriteData(0x80, 0x00);   //时钟启动
    DS1302_WriteData(0x90, 0xa6);   //一个二极管＋4K电阻充电
    DS1302_WriteData(0x8e, 0x80);   //写保护
}

/**************************************
将BCD码转换成十进制
**************************************/
uint8 bcdtol(uint8 bcd)
{
	uint8 tmp;

	tmp = (bcd / 16) * 10 + (bcd % 16);

	return tmp;
}

/**************************************
将十进制码转换成BCD
**************************************/
uint8 ltobcd(uint8 l)
{
	uint8 tmp;

	tmp = (l / 10) * 16 + (l % 10);

	return tmp;
}

uint8 *bcdtols(uint8 *s, uint8 len)
{
	uint8 i;
	
	for (i = 0; i < len; i++)
	{
		s[i] = bcdtol(s[i]);
	}		
	
	return s;
}

uint8 *ltobcds(uint8 *s, uint8 len)
{
	uint8 i;
	
	for (i = 0; i < len; i++)
	{
		s[i] = ltobcd(s[i]);
	}		
	
	return s;	
}
