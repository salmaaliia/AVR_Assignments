#include <util/delay.h>
#include "LIB/BIT_MATH.h"
#include "LIB/STD_TYPES.h"

#include "MCAL/DIO/DIO_interface.h"
//#include "MCAL/PORT/PORT_config.h"
#include "MCAL/PORT/PORT_interface.h"
//#include "MCAL/EXTI/EXTI_config.h"
#include "MCAL/EXTI/EXTI_interface.h"
#include "MCAL/ADC/ADC_interface.h"
#include "MCAL/GIE/GIE_interface.h"
#include "HAL/CLCD/CLCD_interface.h"
#include "HAL/LM35/LM35_interface.h"
u16 APP_ADCRead = 0;

int main(void)
{
	PORT_voidInit();
	CLCD_voidInit();
	ADC_VoidInit();
	//EXTI_voidInt0Init();
	GIE_voidEnable();
	
	while (1)
	{
		LM35_GetTempReadingBlocking(ADC2,  &APP_ADCRead);
		CLCD_voidSendNumber(APP_ADCRead);
		_delay_ms(500);
		CLCD_voidClearDisplay();
	}
}

