/***********************************************************/
/***********************************************************/
/***************      Author: Salma ALi      ***************/
/***************      Layer: MCAL          	 ***************/
/***************      SWC: ADC               ***************/
/***************      Version: 1.00          ***************/


#ifndef ADC_REGISTER_H_
#define ADC_REGISTER_H_

#define		ADMUX			*((volatile u8*) 0x27)		//ADC multiplexer selection register
#define		ADMUX_REFS1		7							//Reference selection bit 1
#define		ADMUX_REFS0		6							//Reference selection bit 2
#define		ADMUX_ADLAR		5							//ADC lift adjust result


#define		ADCSRA          *((volatile u8*) 0x26)		//ADC control and status register
#define		ADCSRA_ADEN  	7							//ADC enable
#define		ADCSRA_ADSC		6							//start conversion
#define		ADCSRA_ADATE	5							//Auto trigger enable
#define		ADCSRA_ADIF		4							//Interrupt flag
#define		ADCSRA_ADIE		3							//Interrupt enable
#define		ADCSRA_ADPS2	2							//Pre_scaler bit2
#define		ADCSRA_ADPS1	1							//Pre_scaler bit1
#define		ADCSRA_ADPS0	0							//Pre_scaler bit0

#define		ADCH            *((volatile u8*) 0x25)		//ADC high register 
#define		ADCL            *((volatile u8*) 0x24)		//ADC low register
#define		ADC             *((volatile u16*)(0x24))	//ADC Data Low and High

#define		SFIOR            *((volatile u8*)(0x50))	 //Special Function IO Register
#define		SFIOR_ADTS2      7							 //ADC Auto Trigger Source Bit 2
#define		SFIOR_ADTS1      6							 //ADC Auto Trigger Source Bit 1
#define		SFIOR_ADTS0      5							 //ADC Auto Trigger Source Bit 0

#endif