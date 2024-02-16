/***********************************************************/
/***********************************************************/
/***************      Author: Salma ALi      ***************/
/***************      Layer: HAL          	 ***************/
/***************      SWC:  LM35              ***************/
/***************      Version: 1.00          ***************/
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/MATH.h"
#include "../../MCAL/DIO/DIO_interface.h"
#include "../../MCAL/ADC/ADC_interface.h"
#include "LM35_Config.h"
#include "LM35_interface.h"
#include "LM35_private.h"


static u16 LM35_u16CalculateTemp(u16 Copy_u16Reading)
{
#if ADC_ADJUSTMENT_SELECT == RIGHT_ADJUST
		u16 Local_u16MilliVolt = ((u32)Copy_u16Reading*5000ULL)/1024ULL;
		u16 Local_u16Temp =Local_u16MilliVolt/10ULL;
#elif ADC_ADJUSTMENT_SELECT == LEFT_ADJUST
		u16 Local_u16MilliVolt = ((u32)Copy_u16Reading*5000ULL)/256ULL;
		u16 Local_u16Temp =Local_u16MilliVolt/10ULL;
#endif

return Local_u16Temp;
}
u8 LM35_GetTempReadingBlocking(u8 Copy_u8Channel, u16* Copy_u16Reading)
{
	u8 Local_u8ErrorState = OK;
	if (Copy_u16Reading == NULL)
	{
		Local_u8ErrorState = NULL_POINTER;
	}
	else
	{
		u16 Local_u16Reading = 0;
		ADC_u8BlockingRead(Copy_u8Channel, &Local_u16Reading);
		*Copy_u16Reading = LM35_u16CalculateTemp(Local_u16Reading);
		
	}
	return Local_u8ErrorState;
}
u8 LM35_GetTempReadingNonBlocking(u8 Copy_u8Channel, u16* Copy_u16Reading, void(*Copy_pvNotificationFunmc)(u16))
{
	
}

