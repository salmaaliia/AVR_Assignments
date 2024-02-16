#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "PORT_interface.h"
#include "DIO_interface.h"
#include "EXTI_interface.h"
#include "GIE_interface.h"
#include "CLCD_interface.h"
#include <util/delay.h>



u8 Global_u8RacketPattern[] = {0x0E, 0x11, 0x11, 0x11, 0x0E, 0x04, 0x04, 0x04, 0x04, 0x04};
u8 Global_u8BallPattern[] ={0x0E, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x0E};
u8 x = 0, y = 1, l = 2;
u8 Global_u8Player1Flag = 0, Global_u8Player2Flag = 0;
u8 Global_u8StartFlag = 0, Global_u8RestartFlag = 0;
u8 Global_u8Player1WinDetect = 0, Global_u8Player2WinDetect = 0;


void INT0_ISR(void);
void INT1_ISR(void);
void INT2_ISR(void);

void APP_voidDisplayWin(u8);
void APP_voidStartScreen(void);

int main(void)
{
	PORT_voidInit();
	CLCD_voidInit();
	EXTI_voidInt0Init();
	EXTI_u8Int0SendISR(&INT0_ISR);
	
	EXTI_voidInt1Init();
	EXTI_u8Int1SendISR(&INT1_ISR);
	
	EXTI_voidInt2Init();
	EXTI_u8Int2SendISR(&INT2_ISR);
	GIE_voidEnable();
	
	APP_voidStartScreen();
	
	u8 Global_u8YIncrementOrDecrementFlag = 1;
	while(1)
    {
		if(Global_u8RestartFlag)
		 {
			 if(l == 2){
				 x = 0, y = 1;
			 }
			 else if(l == 1)
			 {
				 x = 1, y = 14;
			 }
			 
			 Global_u8Player1Flag = 0, Global_u8Player2Flag = 0;
			 
			 while(1)
			 {
				 /*
				 * Display two rackets
				 */
				 CLCD_voidWriteSpecialChar(Global_u8RacketPattern, 0, 1, 0);
				 CLCD_voidWriteSpecialChar(Global_u8RacketPattern, 0, 0, 15);
				 
				 /*
				 * Player 1
				 */
				 if(Global_u8Player1Flag == 1){
					 Global_u8Player1Flag = 0;
				 }
				 else if(Global_u8Player1Flag == 0){
						 if(y == 0){
							 APP_voidDisplayWin(2);
							 break;
						 }
					 
				 }
				 
				 
				 /*
				 * Player2
				 */
				 if(Global_u8Player2Flag == 1){
					Global_u8Player2Flag = 0;
				 }
				 else if(Global_u8Player2Flag == 0)
				 {
					 if(y == 15){
						 APP_voidDisplayWin(1);
						 break;
					 }
				 }
				 
				 
				 
				 if(y == 15) Global_u8YIncrementOrDecrementFlag = 0;
				 if(y == 0) Global_u8YIncrementOrDecrementFlag = 1;
				 CLCD_voidWriteSpecialChar(Global_u8BallPattern, 2, x, y);
				 _delay_ms(100);
				 CLCD_voidG0ToXY(x,y);
				 CLCD_voidSendData(' ');
				 //CLCD_voidWriteSpecialChar(0x00, 3, x, y);
				 if(x == 0) x = 1;
				 else if (x == 1) x = 0;
				 if(Global_u8YIncrementOrDecrementFlag) y++;
				 else y--;
				 
				 
			 }
		 }

    }
}

void APP_voidStartScreen(void)
{
	CLCD_voidG0ToXY(0, 0);
	CLCD_voidSendString("Press B2 To");
	CLCD_voidG0ToXY(1,0);
	CLCD_voidSendString("Start Playing");
	_delay_ms(1000);
	CLCD_voidClearDisplay();
}
void APP_voidDisplayWin(u8 Copy_u8PlayerNum)
{
	if(Copy_u8PlayerNum == 1)
	{
		l = 2;
		Global_u8Player1WinDetect++;
		CLCD_voidClearDisplay();
		CLCD_voidG0ToXY(0, 0);
		CLCD_voidSendString("Player 1 wins!");
		CLCD_voidG0ToXY(1, 0);
		CLCD_voidSendNumber(Global_u8Player1WinDetect);
		CLCD_voidSendString(" / ");
		CLCD_voidSendNumber(Global_u8Player2WinDetect);
		_delay_ms(1000);
		CLCD_voidClearDisplay();
		CLCD_voidG0ToXY(0, 0);
		CLCD_voidSendString("To play again");
		CLCD_voidG0ToXY(1, 0);
		CLCD_voidSendString("Press B2");
		_delay_ms(1000);
		CLCD_voidClearDisplay();
		Global_u8RestartFlag = 0;
	}
	else if(Copy_u8PlayerNum == 2)
	{
		l = 1;
		Global_u8Player2WinDetect++;
		CLCD_voidClearDisplay();
		CLCD_voidG0ToXY(0, 0);
		CLCD_voidSendString("Player 2 wins!");
		CLCD_voidG0ToXY(1, 0);
		CLCD_voidSendNumber(Global_u8Player1WinDetect);
		CLCD_voidSendString(" / ");
		CLCD_voidSendNumber(Global_u8Player2WinDetect);
		_delay_ms(1000);
		CLCD_voidClearDisplay();
		CLCD_voidG0ToXY(0, 0);
		CLCD_voidSendString("To play again");
		CLCD_voidG0ToXY(1, 0);
		CLCD_voidSendString("Press B2");
		_delay_ms(1000);
		CLCD_voidClearDisplay();
		Global_u8RestartFlag = 0;
	}
}

void INT0_ISR(void)
{
	Global_u8Player1Flag = 1;
}

void INT1_ISR(void)
{
	Global_u8Player2Flag = 1;
}

void INT2_ISR(void)
{
	CLCD_voidClearDisplay();
	Global_u8RestartFlag = 1;
}