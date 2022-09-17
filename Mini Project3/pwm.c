/******************************************************************************
 *
 * Module: PWM
 *
 * File Name: pwm.c
 *
 * Description: source file for the PWM driver
 *
 * Author: Yasmin Khaled
 *
 *******************************************************************************/


#include "avr/io.h"
#include "gpio.h"
#include "pwm.h"


/*
 * Description :
 * Function responsible for trigger the Timer0 with the PWM Mode
 */
void PWM_Timer0_Start(uint8 duty_cycle)
{
	uint8 compare_value;
	compare_value = duty_cycle * 2.55;

	TCNT0 = 0;		//Set Timer Initial value

	OCR0 = compare_value;		// Set Compare Value

	GPIO_setupPinDirection(PORTB_ID, PIN3_ID, PIN_OUTPUT);//set PB3/OC0 as output pin --> pin where the PWM signal is generated from MC.


	/* Configure timer control register
	 * 1. Fast PWM mode FOC0=0
	 * 2. Fast PWM Mode WGM01=1 & WGM00=1
	 * 3. Clear OC0 when match occurs (non inverted mode) COM00=0 & COM01=1
	 * 4. clock = F_CPU/8 CS00=0 CS01=1 CS02=0
	 */

	TCCR0 |= ( 1 << WGM00 ) | ( 1 << WGM01 ) | ( 1 << COM01 ) | ( 1 << CS01 );
}

