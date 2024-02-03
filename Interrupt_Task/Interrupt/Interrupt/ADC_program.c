/***********************************************************/
/***********************************************************/
/***************      Author: Salma ALi      ***************/
/***************      Layer: MCAL          	 ***************/
/***************      SWC: ADC               ***************/
/***************      Version: 1.00          ***************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "ADC_config.h"
#include "ADC_interface.h"
#include "ADC_private.h"
#include "ADC_register.h"

/*Variables for Asynchronous single function*/
static u16* ADC_pu16Reading = NULL;
static void(*ADC_CallBackpvNotificationFunc)(void) = NULL;

/*Busy state Variable for ADC*/
static u8 ADC_u8BusyState =IDLE;

/*Conversion mode : Single or Chain*/
static u8 ADC_u8ConversionMode;

/*Variables for Asynchronous chain function*/
static Chain_t *ADC_psChain = NULL;
static u8 ADC_u8ChainIndex = 0;
 
void ADC_VoidInit(void)
{
	/*Reference voltage selection*/
	#if ADC_REF_SELECTION == ADC_AVCC
		SET_BIT(ADMUX, ADMUX_REFS0);
		CLR_BIT(ADMUX, ADMUX_REFS1);
		
	#elif ADC_REF_SELECTION == ADC_AREF
		CLR_BIT(ADMUX, ADMUX_REFS0);
		CLR_BIT(ADMUX, ADMUX_REFS1);
		
	#elif ADC_REF_SELECTION == ADC_INTERNAL_REF
		SET_BIT(ADMUX, ADMUX_REFS0);
		SET_BIT(ADMUX, ADMUX_REFS1);
		
	#else
	#error "Wrong reference selection"
	#endif
	
	/*ADC adjustment*/
	#if ADC_ADJUST == LIFT_ADJ
		SET_BIT(ADMUX, ADMUX_ADLAR);
		
	#elif ADC_ADJUST == RIGHT_ADJ
		CLR_BIT(ADMUX, ADMUX_ADLAR);
		
	#else
	#error "Wrong adjust option"
	#endif
	
	 /*Auto trigger setting*/
	#if AUTO_TRIGGER == ENABLE
		SET_BIT(ADCSRA,ADCSRA_ADATE);
		
		/*Auto trigger source*/
		SFIOR&=AUTO_TRIG_SRC_MASK;
		SFIOR|=(AUTO_TRIGGER_SOURCE<<5);
		
		#if AUTO_TRIGGER_SOURCE == FREE_RUNNING
		/*start conversion*/
		SET_BIT(ADCSRA, ADCSRA_ADSC);
		#endif
		
	#elif AUTO_TRIGGER == DISABLE
		CLR_BIT(ADCSRA,ADCSRA_ADATE);
	#else
	#error "Wrong Auto_trigger option"
	#endif
	
	
	/*ADC Pre_scaler Selections*/
	ADCSRA &= ADC_PRESC_MASK;
	ADCSRA |= ADC_PRESC;
	
	/*Interrupt initial state*/
	#if ADC_Interrupt == ENABLE
		SET_BIT(ADCSRA, ADCSRA_ADIE);
	#elif ADC_Interrupt == DISABLE
		CLR_BIT(ADCSRA, ADCSRA_ADIE);
	#else 
	#error "Wrong ADC_Interrupt option"
	
	/*Enable peripheral*/
	#if ADC_ENABLE == ENABLE
		SET_BIT(ADCSRA, ADCSRA_ADEN);
	#elif	ADC_ENABLE == DISABLE
		SET_BIT(ADCSRA, ADCSRA_ADEN);
	#else
	#error "Wrong ADC_ENABLE option"
	#endif
	
}

u8 ADC_u8StartConversionSynch(u8 Copy_u8Channel , u16* Copy_pu16Reading)
{
	u8 Local_u8ErrorState = OK;
	u32 Local_u32Counter = 0;
	
	if(ADC_u8BusyState == IDLE)
	{
		if(Copy_pu16Reading == NULL)
		{
			Local_u8ErrorState = NULL_POINTER;
		}
		else
		{
			/*make ADC busy in order to work until being idle*/
			ADC_u8BusyState = BUSY;
			
			/*Clear the MUX bits in ADMUX register*/
			ADMUX &= ADC_MUX_MASK;
			/*Set the required channel into the MUX bits*/
			ADMUX |=Copy_u8Channel;
			
			/*start conversion*/
			SET_BIT(ADCSRA, ADCSRA_ADSC);
			
			/*Polling (busy waiting) until the conversion flag is set or counter reaching time out*/
			while((GET_BIT(ADCSRA, ADCSRA_ADIF)==0) && (Local_u32Counter!= ADC_u32TIMEOUT))
			{
				Local_u32Counter++;
			}
			if(Local_u32Counter == ADC_u32TIMEOUT)
			{
				/*Loop is broken because the timeout is reached*/
				Local_u8ErrorState = TIMEOUT;
			}
			else
			{
				/*Loop is broken because flag is raised*/
				
				/*Clear the conversion complete flag*/
				SET_BIT(ADCSRA, ADCSRA_ADIF);
				
				/*return the reading*/
				#if ADC_ADJUST == LIFT_ADJ
				*Copy_pu16Reading = ADCH;
				
				#elif ADC_ADJUST == RIGHT_ADJ
				*Copy_pu16Reading = ADC;
				
				#else
				#error "Wrong adjust option"
				#endif
				
				/*ADC is finished returning it to IDLE*/
				ADC_u8BusyState = IDLE;
			}
		}
	}
	else
	{
		Local_u8ErrorState = BUSY_FUNC;
	}
	
	return Local_u8ErrorState;
}

u8 ADC_u8StartConversionAsynch(u8 Copy_u8Channel , u16* Copy_pu16Reading, void(*Copy_pvNotificationFunc)(void))
{
	u8 Local_u8ErrorState = OK;
	if(ADC_u8BusyState == IDLE)
	{
		/*make ADC busy in order to work until being idle*/
		ADC_u8BusyState = BUSY;
		
		if ( Copy_pu16Reading == NULL || Copy_pvNotificationFunc == NULL)
		{
			Local_u8ErrorState = NULL_POINTER;
		}
		else
		{
			ADC_u8ConversionMode = SINGLE;			
			/*Initialize the reading variable globally*/
			ADC_pu16Reading = Copy_pu16Reading;
			
			/*Initialize the callback notification function globally*/
			ADC_CallBackpvNotificationFunc = Copy_pvNotificationFunc;
			
			/*Clear the MUX bits in ADMUX register*/
			ADMUX &= ADC_MUX_MASK;
			
			/*Set the required channel into the MUX bits*/
			ADMUX |=Copy_u8Channel;
			
			/*start conversion*/
			SET_BIT(ADCSRA, ADCSRA_ADSC);
			
			/*ADC interrupt enable*/
			SET_BIT(ADCSRA, ADCSRA_ADIE);
			
		}
	}
	else
	{
		Local_u8ErrorState = BUSY_FUNC;
	}
	
	return Local_u8ErrorState;
}
u8 ADC_u8StartChainConversionAsynch(Chain_t* Copy_psADCChain)
{
	
	u8 Local_u8ErrorState = OK;
	if(ADC_u8BusyState == IDLE)
	{
		if(Copy_psADCChain!= NULL)
		{
			/*Make ADC busy*/
			ADC_u8BusyState = BUSY;
			/*Make conversion Mode-> Chain Conversion*/
			ADC_u8ConversionMode = CHAIN;
			/*Assign the local variables into global variables*/
			ADC_psChain = Copy_psADCChain;
			
			ADC_u8ChainIndex = 0;
			/*Clear the MUX bits in ADMUX register*/
			ADMUX &= ADC_MUX_MASK;
			/*Set the required channel into the MUX bits*/
			ADMUX |= Copy_psADCChain->ChannelArr[ADC_u8ChainIndex];
			
			/*start conversion*/
			SET_BIT(ADCSRA, ADCSRA_ADSC);
			
			/*ADC interrupt enable*/
			SET_BIT(ADCSRA, ADCSRA_ADIE);
			
		}
		else
		{
			Local_u8ErrorState= NULL_POINTER;	
		}
	}
	else
	{
		Local_u8ErrorState = BUSY_FUNC;
	}
	return Local_u8ErrorState;
}
void __vector_16 (void) __attribute__((signal));
void __vector_16 (void)
{
	if(ADC_u8ConversionMode == SINGLE)
	{
		/*Read ADC result*/
		#if ADC_ADJUST == LIFT_ADJ
		*ADC_pu16Reading = ADCH;
		
		#elif ADC_ADJUST == RIGHT_ADJ
		*ADC_pu16Reading = ADC;
		
		#else
		#error "Wrong adjust option"
		#endif
		
		/*Make ADC state be IDLE because it finished*/
		ADC_u8BusyState = IDLE;
		
		/*Invoke the callback notification function*/
		ADC_CallBackpvNotificationFunc();
		
		/*Disable ADC conversion complete interrupt*/
		CLR_BIT(ADCSRA, ADCSRA_ADIE);
	}
	else if(ADC_u8ConversionMode == CHAIN)
	{
		/*Read ADC result*/
		#if ADC_ADJUST == LIFT_ADJ
		ADC_psChain->ResultArr[ADC_u8ChainIndex]= ADCH;
		
		#elif ADC_ADJUST == RIGHT_ADJ
		ADC_psChain->ResultArr[ADC_u8ChainIndex] = ADC;
		
		#else
		#error "Wrong adjust option"
		#endif
		
		ADC_u8ChainIndex++;
		
		if(ADC_u8ChainIndex == ADC_psChain->Size)
		{
			ADC_psChain->NotiFunc();
			/*Chain index reset*/
			ADC_u8ChainIndex =0;
			/*disable interrupt*/
			CLR_BIT(ADCSRA, ADCSRA_ADIE);
			/*Make the ADC idle to work again*/
			ADC_u8BusyState = IDLE;
		}		
		else
		{
			/*Clear the MUX bits in ADMUX register*/
			ADMUX &= ADC_MUX_MASK;
			/*Set the required channel into the MUX bits*/
			ADMUX |= ADC_psChain->ChannelArr[ADC_u8ChainIndex];
			
			/*start conversion*/
			SET_BIT(ADCSRA, ADCSRA_ADSC);
			
		}
	}
	
	
}

