/***********************************************************/
/***********************************************************/
/***************      Author: Salma ALi      ***************/
/***************      Layer: HAL          	 ***************/
/***************      SWC: CLCD              ***************/
/***************      Version: 1.00          ***************/

#include <util/delay.h>

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "MATH.h"

#include "DIO_interface.h"

#include "CLCD_config.h"
#include "CLCD_interface.h"
#include "CLCD_private.h"

void CLCD_voidSendCommand(u8 Copy_u8Command)
{
	#if CLCD_MODE == CLCD_4BIT
		/*Set RS pin to low for command*/
		DIO_u8SetPinValue(CLCD_CTRL_PORT, CLCD_RS_PIN, DIO_u8PIN_LOW);
		
		/*Set RW pin to low for write*/
		DIO_u8SetPinValue(CLCD_CTRL_PORT, CLCD_RW_PIN, DIO_u8PIN_LOW);
		
		/*Send higher nibble*/
		DIO_u8SetPortValue(CLCD_DATA_PORT, (Copy_u8Command & 0xF0));
		
		/*Send enable pulse*/
		DIO_u8SetPinValue(CLCD_CTRL_PORT, CLCD_E_PIN, DIO_u8PIN_HIGH);
		_delay_ms(2);
		DIO_u8SetPinValue(CLCD_CTRL_PORT, CLCD_E_PIN, DIO_u8PIN_LOW);
		
		_delay_us(200);
		
		/*Send lower nibble*/
		DIO_u8SetPortValue(CLCD_DATA_PORT, ((Copy_u8Command<<4)& 0xF0));
		
		/*Send enable pulse*/
		DIO_u8SetPinValue(CLCD_CTRL_PORT, CLCD_E_PIN, DIO_u8PIN_HIGH);
		_delay_ms(2);
		DIO_u8SetPinValue(CLCD_CTRL_PORT, CLCD_E_PIN, DIO_u8PIN_LOW);
		
	#elif CLCD_MODE == CLCD_8BIT
		/*Set RS pin to low for command*/
		DIO_u8SetPinValue(CLCD_CTRL_PORT, CLCD_RS_PIN, DIO_u8PIN_LOW);
		
		/*Set RW pin to low for write*/
		DIO_u8SetPinValue(CLCD_CTRL_PORT, CLCD_RW_PIN, DIO_u8PIN_LOW);
		
		/*Send command to data pins*/
		DIO_u8SetPortValue(CLCD_DATA_PORT, Copy_u8Command);
		
		 /*Send enable pulse*/
		 DIO_u8SetPinValue(CLCD_CTRL_PORT, CLCD_E_PIN, DIO_u8PIN_HIGH);
		 _delay_ms(2);
		 DIO_u8SetPinValue(CLCD_CTRL_PORT, CLCD_E_PIN, DIO_u8PIN_LOW);
	#else
	#error "Wrong CLCD MODE"
	#endif
} 
void CLCD_voidSendData(u8 Copy_u8Data)
{
	#if CLCD_MODE == CLCD_4BIT
		/*Set RS pin to high for Data*/
		DIO_u8SetPinValue(CLCD_CTRL_PORT, CLCD_RS_PIN, DIO_u8PIN_HIGH);
		
		/*Set RW pin to low for write*/
		DIO_u8SetPinValue(CLCD_CTRL_PORT, CLCD_RW_PIN, DIO_u8PIN_LOW);
		
		/*Send higher nibble*/
		DIO_u8SetPortValue(CLCD_DATA_PORT, (Copy_u8Data &0xF0));
		
		/*Send enable pulse*/
		DIO_u8SetPinValue(CLCD_CTRL_PORT, CLCD_E_PIN, DIO_u8PIN_HIGH);
		_delay_ms(2);
		DIO_u8SetPinValue(CLCD_CTRL_PORT, CLCD_E_PIN, DIO_u8PIN_LOW);
		
		_delay_us(200);
		
		/*Send lower nibble*/
		DIO_u8SetPortValue(CLCD_DATA_PORT, ((Copy_u8Data<<4) &0xF0));
		
		/*Send enable pulse*/
		DIO_u8SetPinValue(CLCD_CTRL_PORT, CLCD_E_PIN, DIO_u8PIN_HIGH);
		_delay_ms(2);
		DIO_u8SetPinValue(CLCD_CTRL_PORT, CLCD_E_PIN, DIO_u8PIN_LOW);
		
	#elif CLCD_MODE == CLCD_8BIT
		/*Set RS pin to high for Data*/
		DIO_u8SetPinValue(CLCD_CTRL_PORT, CLCD_RS_PIN, DIO_u8PIN_HIGH);
		
		/*Set RW pin to low for write*/
		DIO_u8SetPinValue(CLCD_CTRL_PORT, CLCD_RW_PIN, DIO_u8PIN_LOW);
		
		/*Send command to data pins*/
		DIO_u8SetPortValue(CLCD_DATA_PORT, Copy_u8Data);
		
		/*Send enable pulse*/
		DIO_u8SetPinValue(CLCD_CTRL_PORT, CLCD_E_PIN, DIO_u8PIN_HIGH);
		_delay_ms(2);
		DIO_u8SetPinValue(CLCD_CTRL_PORT, CLCD_E_PIN, DIO_u8PIN_LOW);
	#else
	#error "Wrong CLCD MODE"
	#endif
}

void CLCD_voidSendString(const char* Copy_pcString)
{
	int i;
	for (i= 0; Copy_pcString[i]!='\0'; i++)
	{
		CLCD_voidSendData(Copy_pcString[i]);   
	}
}

void CLCD_voidG0ToXY(u8 Copy_u8Xpos, u8 Copy_u8Ypos)
{
	u8 Local_u8Address = 0;
	if(Copy_u8Xpos == 0)  
	{
		/*Location is at first line*/
		Local_u8Address = Copy_u8Ypos;
	}
	else if(Copy_u8Xpos == 1)
	{
		/*Location is at second line*/
		Local_u8Address = Copy_u8Ypos + 0x40;
	}
	/*set bit number 7 for set DDRAM Address command then send the command*/
	CLCD_voidSendCommand(Local_u8Address+128);
}

void CLCD_voidWriteSpecialChar(u8* Copy_pu8Pattern,  u8 Copy_u8PatternNumber, u8 Copy_u8Xpos, u8 Copy_u8Ypos)
{
	//u8 Local_u8CGRAM_Address;
	
	/*Calculate CGRAM Address whose each block is 8 bytes*/
	u8 Local_u8CGRAM_Address = Copy_u8PatternNumber*8;
	
	/*Send CGRAM Address to LCd, with setting bit 6, clearing bit 7*/
	SET_BIT(Local_u8CGRAM_Address, 6);
	CLCD_voidSendCommand(Local_u8CGRAM_Address);
	
	/*Write the pattern into CGRAM*/
	for (int i=0; i<8; i++)
	{
		CLCD_voidSendData( Copy_pu8Pattern[i]);
	}
	
	/*Go back to the DDRAM to display the pattern*/
	CLCD_voidG0ToXY( Copy_u8Xpos, Copy_u8Ypos);
	
	/*Display the pattern written in the CGRAM*/
	CLCD_voidSendData(Copy_u8PatternNumber);
	
}

void CLCD_voidSendNumber(u32 Copy_u32Number)
{
	u8 Local_u8NumOfDigits = 0;
	u8 Local_u8Quotient = 1;
	u8 Local_u8Digit;
	/*Calculate the number of digits*/
	while(Local_u8Quotient!=0)
	{
		Local_u8Quotient = Copy_u32Number/MATH_u32Power(10,++Local_u8NumOfDigits);
	}
	
	for(s32 Local_u8Power =Local_u8NumOfDigits-1;Local_u8Power>=0;Local_u8Power--)
	{
		Local_u8Digit=Copy_u32Number/MATH_u32Power(10,Local_u8Power);
		Copy_u32Number %= MATH_u32Power(10,Local_u8Power);
		Local_u8Digit+=48;
		CLCD_voidSendData(Local_u8Digit);
	}
	
}

void CLCD_voidClearDisplay(void)
{
	CLCD_voidSendCommand(0b00000001);
}

void CLCD_voidInit(void)
{
	/*Wait for more than 30ms*/
	_delay_ms(40);
	
	if(CLCD_MODE == CLCD_4BIT)
	{
		CLCD_voidSendCommand(0x33);
		CLCD_voidSendCommand(0x32);
	}
	
	/*Function set */
	CLCD_voidSendCommand(CLCD_FUNCTION_SET); 
	
	_delay_us(39);
	
	/*Display ON/OFF control*/
	CLCD_voidSendCommand(CLCD_DISPLAY_ON_OFF);
	
	_delay_us(39);
	
	/*Clear display*/
	CLCD_voidSendCommand(1);
	
	_delay_ms(2);
	
}

