#ifndef __CPU_H__
#define __CPU_H__



/******************�봮��ͨѶ��صĺ�*******************/
#define COMMRECIVEBUFFLEN	32	   //���ڽ��ջ����С
#define COMMSENDBUFFLEN		32	   //���ڷ��ͻ����С

#define COMMRECIVETIMROUT 	20	   //���ڽ��ճ�ʱ 20 * 50ms


#define BAUDRATE2400		2400    //2400bps
#define BAUDRATE4800		4800    //4800bps
#define BAUDRATE9600		9600    //9600bps
#define BAUDRATE19200		19200    //19200bps

#define BAUDRATEINDEX2400		0    //2400bps
#define BAUDRATEINDEX4800		1    //4800bps
#define BAUDRATEINDEX9600		2    //9600bps
#define BAUDRATEINDEX19200		3    //19200bps

#define DEFAULTBAUDRATEINDEX		BAUDRATEINDEX9600		//9600bps
#define DEFAULTBAUDRATE				BAUDRATE9600

/********************************************************/
/***************��ϵͳ��ʱ����صĺ�*********************/
/********************************************************/
//ϵͳʱ�������
#define SYSTIMEBASEMAX (0x7fff)

//�����ʱ����ɱ�־λ
#define SysTimeFlagClear(Flag) 	Flag &= ~(0x3 << 1) 
/********************************************************/

/********************************************************/
/**********************��PCA��صĺ�*********************/
/********************************************************/
//ʹ��PCA0����	16λ����ģʽ���£��Ͻ��ش��� ,�����ж�
#define ENABLEPCA0		CMOD = 0x00; CCAPM0 = 0x31; CR = 1;
//ʧ��PCA0����
#define DISABLEPCA0		CCAPM0 = 0x00; CR = 0;

//ʹ��PCA1�����������
#define ENABLEPOT 	CMOD = 0X08; CCAPM1 = 0x4d; CL = 0x00; CH = 0x00; CR = 1;
//ʧ��PCA1�����������
#define DISABLEPOT	CCAPM1 = 0x00; CR = 0;

/********************************************************/

void SetBaudRate(uint16 BaudRate);
void stc_uart_sendbyte(int8 cData);
int8 stc_uart_getbyte(void);

void CPUInit(void);
void sys_handler(void);

#endif