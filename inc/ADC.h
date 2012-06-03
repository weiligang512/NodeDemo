#ifndef __ADC_H__
#define __ADC_H__



/*Define ADC operation const for ADC_CONTR*/
#define ADC_POWER   0x80            //ADC power control bit
#define ADC_FLAG    0x10            //ADC complete flag
#define ADC_START   0x08            //ADC start control bit
#define ADC_SPEEDLL 0x00            //420 clocks
#define ADC_SPEEDL  0x20            //280 clocks
#define ADC_SPEEDH  0x40            //140 clocks
#define ADC_SPEEDHH 0x60            //70 clocks

#define ADC_CHENABLE		0x80	//ADC 通道使能
#define ADC_CH				0x07	//ADC 转换通道


typedef struct _ADCSub
{
	uint8 ADCValH;
	uint8 ADCValL;
}ADCSub_Type;

typedef union _ADCValue
{
	ADCSub_Type ADCSub;
	uint16 uiADCVal;
}ADCValue_Type;


void ADCHandler(uint8 DataL, uint8 DataH);

#endif