/***********************************************************/
/***********************************************************/
/***************      Author: Salma ALi      ***************/
/***************      Layer: MCAL            ***************/
/***************      SWC: ADC               ***************/
/***************      Version: 1.00          ***************/

#ifndef ADC_PRIVATE_H_
#define ADC_PRIVATE_H_

/*Reference select*/
#define AREF							2
#define	AVCC							3
#define Internal_Voltage				4

/*Adjustment selection*/
#define LEFT_ADJUST						5
#define RIGHT_ADJUST					6

/*ADC enable*/
#define ADC_ENABLE						7		
#define ADC_DISABLE						8

/*ADC enable*/
#define ADC_INTERRUPT_ENABLE						7
#define ADC_INTERRUPT_DISABLE						8

/*Auto triggering enable*/
#define ADC_AUTOTRIGGER_ENABLE			9	
#define ADC_AUTOTRIGGER_DISABLE			10	

/*Auto Trigger Sources*/
#define FREE_RUNNING					0
#define ANALOG_COMP						1
#define EXTI0							2
#define TIMER0_COMP_MATCH				3
#define TIMER0_OVF						4
#define TIMER_MATCH_B					5
#define TIMER1_OVF						6
#define TIMER1_CAP_EVENT				7

/*Prescaler*/
#define DIV_BY_2						0
#define DIV_BY_4						2
#define DIV_BY_8						3
#define DIV_BY_16						4
#define DIV_BY_32						5
#define DIV_BY_64						6
#define DIV_BY_128						7

#define ADC_PRESC_MASK					0b11111000
#define ADC_MUX_MASK					0b11100000
#define AUTO_TRIG_SRC_MASK				0b00011111

#define IDLE							1
#define BUSY							2


#endif