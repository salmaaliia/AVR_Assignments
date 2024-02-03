/***********************************************************/
/***********************************************************/
/***************      Author: Salma ALi      ***************/
/***************      Layer: MCAL          	 ***************/
/***************      SWC: ADC               ***************/
/***************      Version: 1.00          ***************/

#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_


typedef struct Chain{
	u8* ChannelArr;
	u16* ResultArr;
	u8 Size;
	void (*NotiFunc)(void);
}Chain_t;

void ADC_VoidInit(void);

u8 ADC_u8StartConversionSynch(u8 Copy_u8Channel, u16* Copy_pu8Reading);

u8 ADC_u8StartConversionAsynch(u8 Copy_u8Channel , u16* Copy_pu8Reading, void(*Copy_pvNotificationFunc)(void));

u8 ADC_u8StartChainConversionAsynch(Chain_t* Copy_psADCChain);


#endif