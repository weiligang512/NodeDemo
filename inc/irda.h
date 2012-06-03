#ifndef __IRDA_H__
#define __IRDA_H__


/********************������豸�йصĺ�**************************/
#define GREE_YB0F2	0x01	//����YB0F2��ң����

//���������豸......

/****************************************************************/

/********************�����YB0F2��ң�����йصĺ�*****************/

/*****************************BYTE1******************************/
//BYTE[0-2]:000�Զ�,001����,010��ʪ,011ͨ��,100����
#define AUTOMODE  	0x00
#define REFRIGMODE	0x01
#define AREFACMODE	0x02
#define AIRMODE		0x03
#define HEATMODE	0x04

//BYTE[3]:0 �ػ�, 1 ����
#define POWERON		0x00
#define POWEROFF	0x80

//����00�Զ�,01С,10��,11��(����ʱΪ0)
#define WINDSPEEDAUTO	0x00
#define WINDSPEEDLOW	0x10
#define WINDSPEEDMIDDLE	0x20
#define WINDSPEEDHIGH	0x30

//BYTE[6]:0��ɨ��,1��ɨ��(����ɨ�������ɨ��)
#define NOWINDDIR	0x00
#define WINDDIR		0x40

//BYTE[7]:0��˯��,1��˯��
#define NOSLEEP		0x00
#define SLEEP		0x80
/****************************************************************/

/************************BYTE2***********************************/
//BYTE[0-3]:0000-1111��ʾ16��C-30��C
#define TMP16	0x00
/****************************************************************/

/****************************************************************/


void IrGetData(IrData_Typ *IrData);
void IrSendRepeat(void);
void IrSendFrame(uint8 *Data);
void IrDeviceSend(uint8 *Data);


#endif