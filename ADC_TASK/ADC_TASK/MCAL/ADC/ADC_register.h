/***********************************************************/
/***********************************************************/
/***************      Author: Salma ALi      ***************/
/***************      Layer: MCAL            ***************/
/***************      SWC: ADC               ***************/
/***************      Version: 1.00          ***************/

#ifndef ADC_REGISTER_H_
#define ADC_REGISTER_H_

/******************************* ADC Multiplexer Selection Register – ADMUX.*********************************/
#define ADMUX				*((volatile u8*)(u8)0x27)
/*
** bits to select the reference voltage
*/
#define ADMUX_REFS1			7
#define ADMUX_REFS0			6
/*
** ADC adjustment >> write 1 for left adjustment
**				  >> write 0 for right adjustment
*/
#define ADMUX_ADLAR			5


/******************************* ADC Control and Status Register A – ADCSRA.*********************************/

#define ADCSRA				 *((volatile u8*)(u8)0x26)

/*ADC Enable register*/
#define ADEN				7

/*ADC start conversion*/
#define ADSC				6

/*ADC Auto trigger enable*/
#define ADATE				5

/*ADC Interrupt flag*/
#define ADIF				4

/*ADC Interrupt enable*/
#define ADIE				3

/*ADC ADC Prescaler Select Bits*/
#define ADPS2				2
#define ADPS1				1
#define ADPS0				0


/******************************* The ADC Data Register – ADCL and ADCH.*********************************/
#define ADCL				*((volatile u8*)(u8)0x24)
#define ADCH				*((volatile u8*)(u8)0x25)
#define ADC					*((volatile u16*)(u16)0x24)


/******************************* Special FunctionIO Register – SFIOR.*********************************/
#define SFIOR				*((volatile u8*)(u8)0x50)
#define ADTS2				7
#define ADTS1				6
#define ADTS0				5

#endif