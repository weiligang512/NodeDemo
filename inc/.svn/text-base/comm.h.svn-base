#ifndef __COOM_H__
#define __COOM_H__




#define COMMHEAD1	0x55
#define COMMHEAD2	0xAA

#define CMDSETPARA	0x01



/************与结果相关的宏**************/
#define CMDSUCCESS				0x0f
#define CMDFAILED				0xf0
/****************************************/

/************与参数设置有关的宏**********/
#define SETPARALEN			10
/****************************************/

/************与时间有关的宏**************/
#define TIMELEN				7
#define SETTIMEFRAMELEN		10
#define READTIMEFRAMELEN	17
/****************************************/

/*************与温湿度相关的宏***********/
#define THDATALEN			5
#define THFRAMELEN			15
/***************************************/

/**************与红外发码有关的宏*******/
#define IADRSENDLEN			10
/***************************************/

/************与命令相关的宏**************/
#define OTHER			0x00			//其他 
#define SETSYSPARA		0x01		    //设置系统参数
#define SETTIME			0x02			//设置时间
#define READTIME		0x03			//读取时间
#define READTH			0x04			//读取温湿度
#define IRDASEND		0x05			//红外发码
/****************************************/





void CoomCmd(void);



#endif