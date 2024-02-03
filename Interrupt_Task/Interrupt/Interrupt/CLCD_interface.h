/***********************************************************/
/***********************************************************/
/***************      Author: Salma ALi      ***************/
/***************      Layer: HAL          	 ***************/
/***************      SWC: CLCD              ***************/
/***************      Version: 1.00          ***************/

#ifndef CLCD_INTERFACE_H_
#define CLCD_INTERFACE_H_


void CLCD_voidSendCommand(u8 Copy_u8Command);

void CLCD_voidSendData(u8 Copy_u8Data);

void CLCD_voidInit(void);

void CLCD_voidSendString(const char* Copy_pcString);

void CLCD_voidG0ToXY(u8 Copy_u8Xpos, u8 Copy_u8Ypos);

void CLCD_voidWriteSpecialChar(u8* Copy_pu8Pattern, u8 Copy_u8PatternNumber, u8 Copy_u8Xpos, u8 Copy_u8Ypos);

void CLCD_voidSendNumber(u32 Copy_u8Number);

void CLCD_voidClearDisplay(void);


#endif