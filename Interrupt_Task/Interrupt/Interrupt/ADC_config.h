/***********************************************************/
/***********************************************************/
/***************      Author: Salma ALi      ***************/
/***************      Layer: MCAL         	 ***************/
/***************      SWC: ADC               ***************/
/***************      Version: 1.00          ***************/

#ifndef ADC_CONFIG_H_
#define ADC_CONFIG_H_

/* Options: 1-AREF_REF
            2-AVCC_REF
            3-INTERNAL_REF
													*/
#define ADC_REF_SELECTION		ADC_AVCC	

/* Options: 1-LIFT_ADJ -> for 8_bit resolution
            2-RIGHT_ADJ-> for 10_bit resolution 
													*/
#define ADC_ADJUST				RIGHT_ADJ

/* Options:
            1-DIV_BY2  
            2-DIV_BY4  
            3-DIV_BY8  
            4-DIV_BY16 
            5-DIV_BY32 
            6-DIV_BY64 
            7-DIV_BY128
													*/
#define ADC_PRESC				DIV_BY_128

/* Options:
            1-ENABLE
            2-DISABLE
													 */
#define ADC_ENABLE				ENABLE

/* Options:
            1-ENABLE
            2-DISABLE
													*/
#define AUTO_TRIGGER         DISABLE

/* Options:
            1-FREE_RUNNING
            2-ANALOG_COMP
            3-EXTI0
            4-TIMER0_COMP_MATCH
            5-TIMER0_OVF
            6-TIMER_MATCH_B
            7-TIMER1_OVF
            8-TIMER1_CAP_EVENT
													*/
#define AUTO_TRIGGER_SOURCE     FREE_RUNNING

#define ADC_u32TIMEOUT			50000

#define ADC_Interrupt				ENABLE




#endif