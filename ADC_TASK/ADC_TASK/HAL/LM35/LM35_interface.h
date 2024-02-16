/***********************************************************/
/***********************************************************/
/***************      Author: Salma ALi      ***************/
/***************      Layer: HAL          	 ***************/
/***************      SWC: LM35              ***************/
/***************      Version: 1.00          ***************/


#ifndef LM35_INTERFACE_H_
#define LM35_INTERFACE_H_

void LM35_voidInit(u8 Copy_u8PostiveChanne);

u8 LM35_u8GetTemp(u8 , f32*);

/*Channels*/
#define	channel0					ADC0				
#define	channel1					ADC1				
#define	channel2					ADC2				
#define	channel3					ADC3				
#define	channel4					ADC4				
#define	channel5					ADC5				
#define	channel6					ADC6				
#define	channel7					ADC7	
								

#endif /* LM35_INTERFACE_H_ */