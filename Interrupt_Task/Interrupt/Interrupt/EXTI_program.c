/***********************************************************/
/***********************************************************/
/***************      Author: Salma ALi      ***************/
/***************      Layer: MCAL            ***************/
/***************      SWC: EXTI	             ***************/
/***************      Version: 1.00          ***************/


#include "STD_TYPES.H" 
#include "BIT_MATH.h"

#include "EXTI_register.h"
#include "EXTI_interface.h"
#include "EXTI_private.h"
#include "EXTI_config.h"

/*Global Pointer to function to hold INT0 ISR address */
void (*EXTI_pvInt0Func)(void) = NULL;

/*Global Pointer to function to hold INT1 ISR address */
void (*EXTI_pvInt1Func)(void) = NULL;

/*Global Pointer to function to hold INT1 ISR address */
void(*EXTI_pvInt2Func)(void) = NULL;

void EXTI_voidInt0Init(void)
{
	/*1- Check Sense control*/
#if INT0_SENSE == LOW_LEVEL
	CLR_BIT(MCUCR, MCUCR_ISC01);
	CLR_BIT(MCUCR, MCUCR_ISC00);
	
#elif INT0_SENSE == ON_CHANGE
	CLR_BIT(MCUCR, MCUCR_ISC01);
	SET_BIT(MCUCR, MCUCR_ISC00);
	
#elif INT0_SENSE == FALLING_EDGE
	SET_BIT(MCUCR, MCUCR_ISC01);
	CLR_BIT(MCUCR, MCUCR_ISC00);
	
#elif INT0_SENSE == RISING_EDGE
	SET_BIT(MCUCR, MCUCR_ISC01);
	SET_BIT(MCUCR, MCUCR_ISC00);
	
#else
#error "Wrong INT0_SENSE configration option"
#endif

	/*2-Check peripheral interrupt enable initial state*/
#if INT0_INITIAL_STATE	== ENABLED
	SET_BIT(GICR, GICR_INT0);
#elif INT0_INITIAL_STATE == DISABLED
	CLR_BIT(GICR, GICR_INT0);
#else
#error "Wrong INT0_INITIAL_STATE configration option"
#endif
}

/************************************************************************************************/
void EXTI_voidInt1Init(void)
{
	/*1- Check Sense control*/	
#if INT1_SENSE == LOW_LEVEL
	CLR_BIT(MCUCR,  MCUCR_ISC11);
	CLR_BIT(MCUCR,  MCUCR_ISC10);
#elif INT1_SENSE == ON_CHANGE
	CLR_BIT(MCUCR,  MCUCR_ISC11);
	SET_BIT(MCUCR,  MCUCR_ISC10);
#elif INT1_SENSE == FALLING_EDGE
	SET_BIT(MCUCR,  MCUCR_ISC11);
	CLR_BIT(MCUCR,  MCUCR_ISC10);
#elif INT1_SENSE == RISING_EDGE
	SET_BIT(MCUCR,  MCUCR_ISC11);
	SET_BIT(MCUCR,  MCUCR_ISC10);
#else
#error "Wrong INT1_SENSE configration option"
#endif

	/*2-Check peripheral interrupt enable initial state*/
#if INT1_INITIAL_STATE	== ENABLED
	SET_BIT(GICR, GICR_INT1);
#elif INT1_INITIAL_STATE == DISABLED
	CLR_BIT(GICR, GICR_INT1);
#else 
#error "Wrong INT1_INITIAL_STATE configration option"
#endif

}

/************************************************************************************************/
void EXTI_voidInt2Init(void)
{
	/*1- Check Sense control*/	
#if INT2_SENSE == FALLING_EDGE
	CLR_BIT(MCUCSR, MCUCSR_ISC2);
#elif INT2_SENSE == RISING_EDGE
	SET_BIT(MCUCSR, MCUCSR_ISC2);
#else
#error "Wrong INT2_SENSE configration option"
#endif

	/*2-Check peripheral interrupt enable initial state*/
#if INT2_INITIAL_STATE == ENABLED
	SET_BIT(GICR, GICR_INT2);
#elif INT2_INITIAL_STATE == DISABLED
	CLR_BIT(GICR, GICR_INT2);
#else
#error "Wrong INT2_INITIAL_STATE configration option"
#endif

}

/************************************************************************************************/
u8 EXTI_u8Int0SetSenseControl(u8 Copy_u8Sense)
{
	u8 Local_u8_ErrorState = OK;
	 
	switch (Copy_u8Sense)
	{
		case LOW_LEVEL:	CLR_BIT(MCUCR, MCUCR_ISC01); CLR_BIT(MCUCR, MCUCR_ISC00); break;
		case ON_CHANGE:	CLR_BIT(MCUCR, MCUCR_ISC01); SET_BIT(MCUCR, MCUCR_ISC00); break;
		case FALLING_EDGE: SET_BIT(MCUCR, MCUCR_ISC01); CLR_BIT(MCUCR, MCUCR_ISC00); break;
		case RISING_EDGE: SET_BIT(MCUCR, MCUCR_ISC01); SET_BIT(MCUCR, MCUCR_ISC00); break;
		default: Local_u8_ErrorState = NOK;
	}
	return Local_u8_ErrorState;
}

/************************************************************************************************/
u8 EXTI_u8Int1SetSenseControl(u8 Copy_u8Sense)
{
	u8 Local_u8_ErrorState = OK;
	
	switch (Copy_u8Sense)
	{
		case LOW_LEVEL:	CLR_BIT(MCUCR, MCUCR_ISC11); CLR_BIT(MCUCR, MCUCR_ISC10); break;
		case ON_CHANGE:	CLR_BIT(MCUCR, MCUCR_ISC11); SET_BIT(MCUCR, MCUCR_ISC10); break;
		case FALLING_EDGE: SET_BIT(MCUCR, MCUCR_ISC11); CLR_BIT(MCUCR, MCUCR_ISC10); break;
		case RISING_EDGE: SET_BIT(MCUCR, MCUCR_ISC11); SET_BIT(MCUCR, MCUCR_ISC10); break;
		default: Local_u8_ErrorState = NOK;
	}
	
	
	return Local_u8_ErrorState;
}

/************************************************************************************************/
u8 EXTI_u8Int2SetSenseControl(u8 Copy_u8Sense)
{
	u8 Local_u8_ErrorState = OK;
	
	switch(Copy_u8Sense)
	{
		case FALLING_EDGE: CLR_BIT(MCUCSR, MCUCSR_ISC2); break;
		case RISING_EDGE:  SET_BIT(MCUCSR, MCUCSR_ISC2); break;
		default: Local_u8_ErrorState = NOK;
	}
	
	return Local_u8_ErrorState;
}

/************************************************************************************************/
u8 EXTI_u8IntEnable(u8 Copy_u8Int)
{
	u8 Local_u8_ErrorState = OK;
	
	switch(Copy_u8Int)
	{
		case INT0: SET_BIT(GICR, GICR_INT0); break;
		case INT1: SET_BIT(GICR, GICR_INT1); break;
		case INT2: SET_BIT(GICR, GICR_INT2); break;
		default: Local_u8_ErrorState = NOK;
	}
	
	return Local_u8_ErrorState;
}

/************************************************************************************************/
u8 EXTI_u8IntDisnable(u8 Copy_u8Int)
{
	u8 Local_u8_ErrorState = OK;
	
	switch(Copy_u8Int)
	{
		case INT0: CLR_BIT(GICR, GICR_INT0); break;
		case INT1: CLR_BIT(GICR, GICR_INT1); break;
		case INT2: CLR_BIT(GICR, GICR_INT2); break;
		default: Local_u8_ErrorState = NOK;
	}
	
	return Local_u8_ErrorState;
}
/************************************************************************************************/
u8 EXTI_u8Int0SendISR(void(*Copy_PvInt0Func)(void))
{
	u8 Local_u8_ErrorState = OK;
	if (Copy_PvInt0Func != NULL)
	{
		EXTI_pvInt0Func = Copy_PvInt0Func;
	}
	else
	{
		Local_u8_ErrorState = NULL_POINTER;
	}
	return Local_u8_ErrorState;
}

void __vector_1(void) __attribute__((signal));
void __vector_1(void)
{
	EXTI_pvInt0Func();
}

/************************************************************************************************/
u8 EXTI_u8Int1SendISR(void(*Copy_PvInt1Func)(void))
{
	u8 Local_u8_ErrorState = OK;
	
	if(Copy_PvInt1Func!=NULL)
	{
		EXTI_pvInt1Func = Copy_PvInt1Func;
	}
	else{
		Local_u8_ErrorState = NULL_POINTER;
	}
	
	return Local_u8_ErrorState;
	
}

void __vector_2(void) __attribute__((signal));
void __vector_2(void)
{
	EXTI_pvInt1Func();
}

/************************************************************************************************/
u8 EXTI_u8Int2SendISR(void(*Copy_PvInt2Func)(void))
{
	u8 Local_u8_ErrorState = OK;
	
	if(Copy_PvInt2Func != NULL)
	{
		EXTI_pvInt2Func = Copy_PvInt2Func;
	}
	else{
		Local_u8_ErrorState = NULL_POINTER;
	}
	
	return Local_u8_ErrorState;
}

void __vector_3(void) __attribute__((signal));
void __vector_3(void)
{
	EXTI_pvInt2Func();
}

