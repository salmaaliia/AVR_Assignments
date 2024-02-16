/***********************************************************/
/***********************************************************/
/***************      Author: Salma ALi      ***************/
/***************      Layer: MCAL            ***************/
/***************      SWC: ADC               ***************/
/***************      Version: 1.00          ***************/

#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"
#include "../DIO/DIO_interface.h"
#include "ADC_config.h"
#include "ADC_interface.h"
#include "ADC_private.h"
#include "ADC_register.h"

/*Variables for Asynchronous single function*/
static u16* ADC_pu16Reading = NULL;
static void(*ADC_CallBackpvNotificationFunc)(u16 ) = NULL;

/*Busy state Variable for ADC*/
static u8 ADC_u8BusyState =IDLE;

/*Conversion mode : Single or Chain*/
//static u8 ADC_u8ConversionMode;

void ADC_VoidInit(void)
{	
	/*Reference voltage selection*/
#if ADC_REF_SELECT == AREF
	CLR_BIT(ADMUX, ADMUX_REFS1);
	CLR_BIT(ADMUX, ADMUX_REFS0);
#elif ADC_REF_SELECT == AVCC
	CLR_BIT(ADMUX, ADMUX_REFS1);
	SET_BIT(ADMUX, ADMUX_REFS0);

#elif ADC_REF_SELECT == Internal_Voltage
	SET_BIT(ADMUX, ADMUX_REFS1);
	SET_BIT(ADMUX, ADMUX_REFS0);
#else
#error "Wrong reference selection"
#endif

	/*Adjustment selection*/
#if ADC_ADJUSTMENT_SELECT == RIGHT_ADJUST
	CLR_BIT(ADMUX, ADMUX_ADLAR);
#elif ADC_ADJUSTMENT_SELECT == LEFT_ADJUST
	SET_BIT(ADMUX, ADMUX_ADLAR);
#else
#error "Wrong adjustment selection"
#endif

	/*Auto trigger*/
#if ADC_AUTOTRIGGER_STATUS == ADC_AUTOTRIGGER_ENABLE	
	SET_BIT(ADCSRA, ADATE);
	
	SFIOR &= AUTO_TRIG_SRC_MASK;
	SFIOR |= (ADC_AUTOTRIGGER_SOURCE<<5);
	
#if ADC_AUTOTRIGGER_SOURCE == FREE_RUNNING
	/*Start conversion*/
	SET_BIT(ADCSRA, ADSC);
#endif

#elif ADC_AUTOTRIGGER_STATUS == ADC_AUTOTRIGGER_DISABLE
	CLR_BIT(ADCSRA, ADATE);
#else
#error "Wrong auto trigger selection"
#endif

	/*ADC prescaler*/
	ADCSRA &= ADC_PRESC_MASK;
	ADCSRA |= ADC_PRESC_OPTION;
	
	/*ADC interrupt status*/
#if ADC_INTERRUPT_STAT == ADC_INTERRUPT_ENABLE
	SET_BIT(ADCSRA, ADIE);
#elif ADC_INTERRUPT_STAT == ADC_INTERRUPT_DISABLE
	CLR_BIT(ADCSRA, ADIE);
#else
#error "Wrong interrupt option"
#endif
	
	
	/*ADC status options*/
#if ADC_STATUS == ADC_ENABLE
	SET_BIT(ADCSRA, ADEN);
#elif ADC_STATUS == ADC_DISABLE
	CLR_BIT(ADCSRA, ADEN);
#else
#error "Wrong status selection"
#endif

}

u8 ADC_u8BlockingRead(u8 Copy_u8Cannel, u16 *Copy_u16Reading)
{
	u8 Local_u8ErrorState = OK;
	u8 Local_u8Counter = 0;
	if(ADC_u8BusyState == IDLE)
	{
		if(Copy_u16Reading == NULL)
		{
			Local_u8ErrorState = NULL_POINTER;
		}
		else
		{
			/*make ADC busy in order to work until being idle*/
			ADC_u8BusyState = BUSY;
			
			/*Clear the MUX bits in ADMUX register*/
			ADMUX = (ADMUX & ADC_MUX_MASK) | Copy_u8Cannel;
			/*Set the required channel into the MUX bits*/
			//ADMUX |= Copy_u8Cannel;
			
			/*start conversion*/
			SET_BIT(ADCSRA, ADSC);
			
			/*turn off ADC interrupt*/
			CLR_BIT(ADCSRA, ADIE);
			
			/*Polling (busy waiting) until the conversion flag is set or counter reaching time out*/
			while((GET_BIT(ADCSRA, ADIF) == 0) && (Local_u8Counter != ADC_u32TIMEOUT))
			{
				Local_u8Counter++;
			}
			if(Local_u8Counter == ADC_u32TIMEOUT)
			{
				/*Loop is broken because the timeout is reached*/
				Local_u8ErrorState = TIMEOUT;
			}
			else
			{
				/*Loop is broken because flag is raised*/
				
				/*Clear the conversion complete flag*/
				SET_BIT(ADCSRA, ADIF);
				
				#if ADC_INTERRUPT_STAT == ADC_INTERRUPT_ENABLE
				SET_BIT(ADCSRA, ADIE);
				#endif
				
				/*return the reading*/
				#if ADC_ADJUSTMENT_SELECT == LEFT_ADJUST
				*Copy_u16Reading = ADCH;
				#elif ADC_ADJUSTMENT_SELECT == RIGHT_ADJUST
				*Copy_u16Reading = ADC;
				#else
				#error "Wrong adjust option" 
				#endif
				
				ADC_u8BusyState = IDLE;
			}
			
		}
	}
	else if(ADC_u8BusyState == BUSY)
	{
		Local_u8ErrorState = BUSY_FUNC;
	}
	return Local_u8ErrorState;
}

u8 ADC_u8NonBLockingRead(u8 Copy_u8Cannel, u16 *Copy_pu16Reading, void(*Copy_pvNotificationFunmc)(u16))
{
	u8 Local_u8ErrorState = OK;
	if(ADC_u8BusyState == IDLE)
	{
		ADC_u8BusyState = BUSY;
		if(Copy_pvNotificationFunmc == NULL)
		{
			Local_u8ErrorState = NULL_POINTER;
		}
		else
		{
			ADC_pu16Reading = Copy_pu16Reading;
			ADC_CallBackpvNotificationFunc = Copy_pvNotificationFunmc;
			
			/*Clear the MUX bits in ADMUX register*/
			ADMUX &= ADC_MUX_MASK;
			/*Set the required channel into the MUX bits*/
			ADMUX |= Copy_u8Cannel;
			
			/*start conversion*/
			SET_BIT(ADCSRA, ADSC);
			
			/*ADC interrupt enable*/
			SET_BIT(ADCSRA, ADIE);
		}
	}
	else
	{
		Local_u8ErrorState = BUSY_FUNC;
		
	}
	return Local_u8ErrorState;
}

void __vector_16 (void) __attribute__((signal));
void __vector_16(void)
{
	
	/*Read ADC result*/
	#if ADC_ADJUSTMENT_SELECT == LEFT_ADJUST
	*ADC_pu16Reading = ADCH;
	
	#elif ADC_ADJUSTMENT_SELECT == RIGHT_ADJUST
	*ADC_pu16Reading = ADC;
	
	#else
	#error "Wrong adjust option"
	#endif
	
	if(ADC_CallBackpvNotificationFunc != NULL)
	{
		ADC_CallBackpvNotificationFunc(*ADC_pu16Reading);
	}
	/*Make ADC state be IDLE because it finished*/
	ADC_u8BusyState = IDLE;
	
	/*Disable ADC conversion complete interrupt*/
	CLR_BIT(ADCSRA, ADIE);
}