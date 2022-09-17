 /******************************************************************************
 *
 * Module: ADC
 *
 * File Name: adc.c
 *
 * Description: Source file for the ADC driver
 *
 * Author: Yasmin Khaled
 *
 *******************************************************************************/


#include "common_macros.h"
#include "avr/io.h"
#include "adc.h"


/*
 * Description :
 * Function responsible for initialize the ADC driver.
 * 1- set required Vref
 * 2- Enable ADC
 * 3- set required Prescaler value
 */
void ADC_init(const ADC_ConfigType * Config_Ptr)
{

	/*
	 * insert the required Vref value in the last two bits (REFS0, REFS1)
	 * of ADMUX Register
	 */
	ADMUX = (ADMUX & 0x3F) | ((Config_Ptr->ref_volt)<<6);
	SET_BIT(ADCSRA,ADEN); //Enable ADC

	/*
	 * insert the required Prescaler value in the first three bits (ADPS0, ADPS1, ADPS2)
	 * of ADCSRA Register
	 */
	ADCSRA = (ADCSRA & 0xF8) | (Config_Ptr->prescaler);

}

/*
 * Description :
 * Function responsible for read analog data from a certain ADC channel
 * and convert it to digital using the ADC driver.
 */
uint16 ADC_readChannel(uint8 ch_num)
{

	ch_num &= 0x07; 			//Input channel number must be from 0 --> 7
	ADMUX &= 0xE0;				//Clear first 5 bits in the ADMUX (channel number MUX4:0 bits) before set the required channel
	ADMUX |= ch_num;			//Choose the correct channel by setting the channel number in MUX4:0 bits
	SET_BIT(ADCSRA,ADSC);		//Start conversion  ADSC=1
	while( BIT_IS_CLEAR(ADCSRA,ADIF) ); //Polling "Wait for conversion to complete, ADIF becomes '1'"

	SET_BIT(ADCSRA,ADIF);		//Clear ADIF by write '1' to it
	return ADC;					//Read the digital value from the data register
}
