#ifndef __COOM_H__
#define __COOM_H__




#define COMMHEAD1	0x55
#define COMMHEAD2	0xAA

#define CMDSETPARA	0x01



/************������صĺ�**************/
#define CMDSUCCESS				0x0f
#define CMDFAILED				0xf0
/****************************************/

/************����������йصĺ�**********/
#define SETPARALEN			10
/****************************************/

/************��ʱ���йصĺ�**************/
#define TIMELEN				7
#define SETTIMEFRAMELEN		10
#define READTIMEFRAMELEN	17
/****************************************/

/*************����ʪ����صĺ�***********/
#define THDATALEN			5
#define THFRAMELEN			15
/***************************************/

/**************����ⷢ���йصĺ�*******/
#define IADRSENDLEN			10
/***************************************/

/************��������صĺ�**************/
#define OTHER			0x00			//���� 
#define SETSYSPARA		0x01		    //����ϵͳ����
#define SETTIME			0x02			//����ʱ��
#define READTIME		0x03			//��ȡʱ��
#define READTH			0x04			//��ȡ��ʪ��
#define IRDASEND		0x05			//���ⷢ��
/****************************************/





void CoomCmd(void);



#endif