#ifndef __IRDA_H__
#define __IRDA_H__


/********************与红外设备有关的宏**************************/
#define GREE_YB0F2	0x01	//格力YB0F2型遥控器

//其他红外设备......

/****************************************************************/

/********************与格力YB0F2型遥控器有关的宏*****************/

/*****************************BYTE1******************************/
//BYTE[0-2]:000自动,001制冷,010除湿,011通风,100制热
#define AUTOMODE  	0x00
#define REFRIGMODE	0x01
#define AREFACMODE	0x02
#define AIRMODE		0x03
#define HEATMODE	0x04

//BYTE[3]:0 关机, 1 开机
#define POWERON		0x00
#define POWEROFF	0x80

//风速00自动,01小,10中,11大(节能时为0)
#define WINDSPEEDAUTO	0x00
#define WINDSPEEDLOW	0x10
#define WINDSPEEDMIDDLE	0x20
#define WINDSPEEDHIGH	0x30

//BYTE[6]:0无扫风,1有扫风(上下扫风或左右扫风)
#define NOWINDDIR	0x00
#define WINDDIR		0x40

//BYTE[7]:0无睡眠,1有睡眠
#define NOSLEEP		0x00
#define SLEEP		0x80
/****************************************************************/

/************************BYTE2***********************************/
//BYTE[0-3]:0000-1111表示16°C-30°C
#define TMP16	0x00
/****************************************************************/

/****************************************************************/


void IrGetData(IrData_Typ *IrData);
void IrSendRepeat(void);
void IrSendFrame(uint8 *Data);
void IrDeviceSend(uint8 *Data);


#endif