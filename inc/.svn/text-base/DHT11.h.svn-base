#ifndef __DHT11_H__
#define __DHT11_H__

//DHT11, 温湿度接口
sbit DHTDATA = P2^0;

#define DHTACKTIME	(400)		  //DHT应答超时时间

typedef struct 
{
	uint8 integer;
	uint8 fraction;
}DHTstp_Typ;

typedef union
{
	DHTstp_Typ point;
 	uint16 intfrac;
}DHTun_Typ;

typedef struct
{
	DHTun_Typ rh;
	DHTun_Typ temp;
	uint8 chech;		
}DHTst_Typ;

typedef union
{
	uint8 ucdata[5];
	DHTst_Typ DHTdata;
}DHT_Typ;

typedef enum
{
	DHT_OK = 0x00,	//读数正确
	DHT_TIMEOUT,    //应答超时，可能是DHT11不存在或损坏
	DHT_CHECKFAILED
}DHT_Status;

DHT_Status DHT11Read(DHT_Typ *Data);

#endif