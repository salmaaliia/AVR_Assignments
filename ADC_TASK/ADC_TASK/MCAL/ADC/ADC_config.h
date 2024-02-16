/***********************************************************/
/***********************************************************/
/***************      Author: Salma ALi      ***************/
/***************      Layer: MCAL            ***************/
/***************      SWC: ADC               ***************/
/***************      Version: 1.00          ***************/

#ifndef ADC_CONFIG_H_
#define ADC_CONFIG_H_

/*Voltage reference select
** options:	AREF
**			AVCC
**			Internal_Voltage
*/
#define ADC_REF_SELECT				AVCC

/*Adjustment select
** options:	RIGHT_ADJUST
**			LEFT_ADJUST
*/
#define ADC_ADJUSTMENT_SELECT		RIGHT_ADJUST

/*ADC status
**options:	ADC_DISABLE
**			ADC_ENABLE
*/
#define  ADC_STATUS					ADC_ENABLE

/*ADC auto trigger
**options:	ADC_OUTOTRIGGER_ENABLE
**			ADC_OUTOTRIGGER_DISABLE	
*/
#define ADC_AUTOTRIGGER_STATUS		ADC_AUTOTRIGGER_DISABLE	

/*ADC auto trigger source*/
#define ADC_AUTOTRIGGER_SOURCE		EXTI0

/*Prescaler
** Options:	DIV_BY_2	
			DIV_BY_4	
			DIV_BY_8	
			DIV_BY_16	
			DIV_BY_32	
			DIV_BY_64	
 			DIV_BY_128	
*/
#define ADC_PRESC_OPTION			DIV_BY_128

/*ADC interrupt status*/
#define ADC_INTERRUPT_STAT			ADC_INTERRUPT_ENABLE
		
#define ADC_u32TIMEOUT			50000

#endif