#include "STC_NEW_8051.H"
#include "type.h"
#include "DHT11.h"
#include "delay.h"
#include "uart.h"


//读DHT11一个字节
static uint8 DHT11ReadByte(void)
{
	uint8 i, DataTmp = 0;
	uint16 Time;

	for(i = 0; i < 8; i++)	   
	{
		Time = DHTACKTIME;
	   	while(!DHTDATA && Time--);
		if (Time <= 0)
		{
			return 0;
		}
		Delay10us(2);

		DataTmp <<= 1;
	    if (DHTDATA)
		{
			DataTmp |= 0x01;
		}
		Time = DHTACKTIME;
		while(DHTDATA && Time--);
		if (Time <= 0)
		{
			return 0;
		}
	}

	return DataTmp;
}

//读DHT11数据，共5个字节
//一次完整的数据传输为40bit,高位先出。
//数据格式:8bit湿度整数数据+8bit湿度小数数据
//+8bi温度整数数据+8bit温度小数数据
//+8bit校验和
DHT_Status DHT11Read(DHT_Typ *Data)
{
	int16 data Time = DHTACKTIME;	  //超时时间
	uint8 data i, CheckTmp = 0;

	DHTDATA = 0;
	Delay1ms(18);	  //延时至少18ms，向DHT11发送起始信号
	EA = 0;
	DHTDATA = 1;	  //释放总线
	Delay10us(2);	  //延时20-40us
	DHTDATA = 1;	  //释放总线

	while ((DHTDATA) && Time--);	   //检测DHT11应答信号
	if (Time <= 0)
	{
		EA = 1;
		return DHT_TIMEOUT;
	}

	Time = DHTACKTIME;
	while ((!DHTDATA) && Time--);	   //检测DHT11拉高
	if (Time <= 0)
	{
		EA = 1;
		return DHT_TIMEOUT;
	}

	Time = DHTACKTIME; 
	while ((DHTDATA) && Time--);		//等待50us起始
	if (Time <= 0)
	{
		EA = 1;
		return DHT_TIMEOUT;
	}

	for (i = 0; i < 5; i++)
	{
		Data->ucdata[i] = DHT11ReadByte();		
	}
	
	for (i = 0; i < 4; i++)
	{
		CheckTmp += Data->ucdata[i];		
	}
	
	if (CheckTmp != Data->ucdata[i])
	{
		EA = 1;
		return DHT_CHECKFAILED;
	}

	EA = 1;

	return DHT_OK;
}

