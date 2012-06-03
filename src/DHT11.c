#include "STC_NEW_8051.H"
#include "type.h"
#include "DHT11.h"
#include "delay.h"
#include "uart.h"


//��DHT11һ���ֽ�
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

//��DHT11���ݣ���5���ֽ�
//һ�����������ݴ���Ϊ40bit,��λ�ȳ���
//���ݸ�ʽ:8bitʪ����������+8bitʪ��С������
//+8bi�¶���������+8bit�¶�С������
//+8bitУ���
DHT_Status DHT11Read(DHT_Typ *Data)
{
	int16 data Time = DHTACKTIME;	  //��ʱʱ��
	uint8 data i, CheckTmp = 0;

	DHTDATA = 0;
	Delay1ms(18);	  //��ʱ����18ms����DHT11������ʼ�ź�
	EA = 0;
	DHTDATA = 1;	  //�ͷ�����
	Delay10us(2);	  //��ʱ20-40us
	DHTDATA = 1;	  //�ͷ�����

	while ((DHTDATA) && Time--);	   //���DHT11Ӧ���ź�
	if (Time <= 0)
	{
		EA = 1;
		return DHT_TIMEOUT;
	}

	Time = DHTACKTIME;
	while ((!DHTDATA) && Time--);	   //���DHT11����
	if (Time <= 0)
	{
		EA = 1;
		return DHT_TIMEOUT;
	}

	Time = DHTACKTIME; 
	while ((DHTDATA) && Time--);		//�ȴ�50us��ʼ
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

