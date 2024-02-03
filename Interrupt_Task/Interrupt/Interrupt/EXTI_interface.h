/***********************************************************/
/***********************************************************/
/***************      Author: Salma ALi      ***************/
/***************      Layer: MCAL            ***************/
/***************      SWC: EXTI	             ***************/
/***************      Version: 1.00          ***************/

#ifndef EXTI_INTERFACE_H_
#define EXTI_INTERFACE_H_


#define LOW_LEVEL		1
#define ON_CHANGE		2
#define FALLING_EDGE	3
#define RISING_EDGE		4

#define INT0			5
#define INT1			6
#define INT2			7


void EXTI_voidInt0Init(void);

void EXTI_voidInt1Init(void);

void EXTI_voidInt2Init(void);

/*	Description: A function to set the required sense control of INT0 using Post build config
*	Input: Copy_u8Sense, Options: 1- LOW_LEVEL	
*								  2- ON_CHANGE	
*								  3- FALLING_EDGE
*								  4- RISING_EDGE	
*	Output: Error state with type u8
*/

u8 EXTI_u8Int0SetSenseControl(u8 Copy_u8Sense);

/*	Description: A function to set the required sense control of INT1 using Post build config
*	Input: Copy_u8Sense, Options: 1- LOW_LEVEL
*								  2- ON_CHANGE
*								  3- FALLING_EDGE
*								  4- RISING_EDGE
*	Output: Error state with type u8
*/
u8 EXTI_u8Int1SetSenseControl(u8 Copy_u8Sense);

/*	Description: A function to set the required sense control of INT2 using Post build config
*	Input: Copy_u8Sense, Options: 1- FALLING_EDGE
*								  2- RISING_EDGE
*	Output: Error state with type u8
*/
u8 EXTI_u8Int2SetSenseControl(u8 Copy_u8Sense);

u8 EXTI_u8IntEnable(u8 Copy_u8Int);

u8 EXTI_u8IntDisnable(u8 Copy_u8Int);

/*ISR of INT0*/
u8 EXTI_u8Int0SendISR(void(*Copy_PvInt0Func)(void));

/*ISR of INT1*/
u8 EXTI_u8Int1SendISR(void(*Copy_PvInt1Func)(void));

/*ISR of INT2*/
u8 EXTI_u8Int2SendISR(void(*Copy_PvInt2Func)(void));

#endif
