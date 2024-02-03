/***********************************************************/
/***********************************************************/
/***************      Author: Salma ALi      ***************/
/***************      Layer: MCAL            ***************/
/***************      SWC: POR              ***************/ 
/***************      Version: 1.00          ***************/

#ifndef DIO_CONFIG_H_
#define DIO_CONFIG_H_


/*Choose : 0 for Input
           1 for Output   */

#define PORTA_PIN0_DIR 			1
#define PORTA_PIN1_DIR 			1
#define PORTA_PIN2_DIR 			1
#define PORTA_PIN3_DIR 			1
#define PORTA_PIN4_DIR 			1
#define PORTA_PIN5_DIR 			1
#define PORTA_PIN6_DIR 			1
#define PORTA_PIN7_DIR 			1

#define PORTB_PIN0_DIR 			0
#define PORTB_PIN1_DIR 			0
#define PORTB_PIN2_DIR 			0
#define PORTB_PIN3_DIR 			0
#define PORTB_PIN4_DIR 			0
#define PORTB_PIN5_DIR 			0
#define PORTB_PIN6_DIR 			0
#define PORTB_PIN7_DIR 			0
								
#define PORTC_PIN0_DIR 			1
#define PORTC_PIN1_DIR 			1
#define PORTC_PIN2_DIR 			1
#define PORTC_PIN3_DIR 			0
#define PORTC_PIN4_DIR 			0
#define PORTC_PIN5_DIR 			0
#define PORTC_PIN6_DIR 			0
#define PORTC_PIN7_DIR 			0
								
#define PORTD_PIN0_DIR 			0
#define PORTD_PIN1_DIR 			0
#define PORTD_PIN2_DIR 			0
#define PORTD_PIN3_DIR 			0
#define PORTD_PIN4_DIR 			0
#define PORTD_PIN5_DIR 			0
#define PORTD_PIN6_DIR 			0
#define PORTD_PIN7_DIR 			0


/*Pins initial values*/
/*if pin is Output choose : 1 for high
                            0 for low
  if pin is Input choose  : 1 for pulled up
							0 for floating*/

#define PORTA_PIN0_INITIAL_VALUE 			0
#define PORTA_PIN1_INITIAL_VALUE 			0
#define PORTA_PIN2_INITIAL_VALUE 			0
#define PORTA_PIN3_INITIAL_VALUE 			0
#define PORTA_PIN4_INITIAL_VALUE 			0
#define PORTA_PIN5_INITIAL_VALUE 			0
#define PORTA_PIN6_INITIAL_VALUE 			0
#define PORTA_PIN7_INITIAL_VALUE 			0

#define PORTB_PIN0_INITIAL_VALUE 			0
#define PORTB_PIN1_INITIAL_VALUE 			0
#define PORTB_PIN2_INITIAL_VALUE 			1
#define PORTB_PIN3_INITIAL_VALUE 			0
#define PORTB_PIN4_INITIAL_VALUE 			0
#define PORTB_PIN5_INITIAL_VALUE 			0
#define PORTB_PIN6_INITIAL_VALUE 			0
#define PORTB_PIN7_INITIAL_VALUE 			0

#define PORTC_PIN0_INITIAL_VALUE 			0
#define PORTC_PIN1_INITIAL_VALUE 			0
#define PORTC_PIN2_INITIAL_VALUE 			0
#define PORTC_PIN3_INITIAL_VALUE 			0
#define PORTC_PIN4_INITIAL_VALUE 			0
#define PORTC_PIN5_INITIAL_VALUE 			0
#define PORTC_PIN6_INITIAL_VALUE 			0
#define PORTC_PIN7_INITIAL_VALUE 			0

#define PORTD_PIN0_INITIAL_VALUE 			0
#define PORTD_PIN1_INITIAL_VALUE 			0
#define PORTD_PIN2_INITIAL_VALUE 			1
#define PORTD_PIN3_INITIAL_VALUE 			1
#define PORTD_PIN4_INITIAL_VALUE 			0
#define PORTD_PIN5_INITIAL_VALUE 			0
#define PORTD_PIN6_INITIAL_VALUE 			0
#define PORTD_PIN7_INITIAL_VALUE 			0


#endif