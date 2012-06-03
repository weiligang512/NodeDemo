#include "STC_NEW_8051.H"
#include "type.h"
#include "ADC.h"


volatile ADCValue_Type ADCValue;



void ADCHandler(uint8 DataL, uint8 DataH)
{
	ADCValue.ADCSub.ADCValL = DataL;
	ADCValue.ADCSub.ADCValH = DataH;	
}













