/***********************************************************/
/***********************************************************/
/***************      Author: Salma ALi      ***************/
/***************      Layer: MCAL            ***************/
/***************      SWC: ADC               ***************/
/***************      Version: 1.00          ***************/

#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_

void ADC_VoidInit(void);

u8 ADC_u8BlockingRead(u8 Copy_u8Cannel, u16 *Copy_u16Reading);

u8 ADC_u8NonBLockingRead(u8 Copy_u8Cannel, u16 *Copy_pu16Reading, void(*Copy_pvNotificationFunmc)(u16));



/*ADC Single Ended Input Channels*/
#define ADC0				0x0
#define ADC1				0x1
#define ADC2				0x2
#define ADC3				0x3
#define ADC4				0x4
#define ADC5				0x5
#define ADC6				0x6
#define ADC7				0x7
#define VBG					0x1E
#define CND					0x1F

/*ADC Differential Input Channels*/

#endif