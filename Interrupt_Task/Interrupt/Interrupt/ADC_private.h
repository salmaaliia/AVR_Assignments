/***********************************************************/
/***********************************************************/
/***************      Author: Salma ALi      ***************/
/***************      Layer: MCAL          	 ***************/
/***************      SWC: ADC               ***************/
/***************      Version: 1.00          ***************/

#ifndef ADC_PRIVATE_H_
#define ADC_PRIVATE_H_

/*Prescaler*/
#define DIV_BY_2			0
#define DIV_BY_4			2
#define DIV_BY_8			3
#define DIV_BY_16			4
#define DIV_BY_32			5
#define DIV_BY_64			6
#define DIV_BY_128			7

/*ADC Reference Modes*/
#define ADC_AREF			1
#define ADC_AVCC			2
#define ADC_INTERNAL_REF	3

#define LIFT_ADJ			1
#define RIGHT_ADJ			2

#define ENABLE				1
#define DISABLE				2

#define SINGLE				0
#define CHAIN				1

#define ADC_PRESC_MASK		0b11111000
#define ADC_MUX_MASK		0b11100000	
#define AUTO_TRIG_SRC_MASK  0b00001111

/*Auto Trigger Sources*/
#define FREE_RUNNING		0
#define ANALOG_COMP			1
#define EXTI0				2
#define TIMER0_COMP_MATCH	3
#define TIMER0_OVF			4
#define TIMER_MATCH_B		5 
#define TIMER1_OVF			6
#define TIMER1_CAP_EVENT	7

#define IDLE				1
#define BUSY				2
#endif