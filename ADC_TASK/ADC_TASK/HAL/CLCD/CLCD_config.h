/***********************************************************/
/***********************************************************/
/***************      Author: Salma ALi      ***************/
/***************      Layer: HAL          	 ***************/
/***************      SWC: CLCD              ***************/
/***************      Version: 1.00          ***************/

#ifndef CLCD_CONFIG_H_
#define CLCD_CONFIG_H_

#define CLCD_DATA_PORT			DIO_u8PORTB 

#define CLCD_CTRL_PORT			DIO_u8PORTC
#define CLCD_RS_PIN				DIO_u8PIN0	
#define CLCD_RW_PIN				DIO_u8PIN1
#define CLCD_E_PIN				DIO_u8PIN2

#define CLCD_MODE				CLCD_4BIT

#define CLCD_FUNCTION_SET		CLCD_4BIT_2LINES

#define CLCD_DISPLAY_ON_OFF		CLCD_DISPLAY_ON_CURSOR_ON

#endif