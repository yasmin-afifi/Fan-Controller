/******************************************************************************
 *
 * File Name: main.c
 *
 * Description:
 *
 * Author: Yasmin Khaled
 *
 *******************************************************************************/

#include "adc.h"
#include "lcd.h"
#include "lm35_sensor.h"
#include "dc_motor.h"

int main(void)
{
	uint8 temp;
	ADC_ConfigType ConfigType = { Internal_Vref, F_CPU_8 };

	ADC_init(&ConfigType); 	// initialize ADC driver
	LCD_init(); 			// initialize LCD driver
	DcMotor_Init();			// initialize Motor driver

	LCD_moveCursor(0,3); 	// Move the cursor to the first row with suitable location
	LCD_displayString("FAN is ");

	LCD_moveCursor(1,3); 	// Move the cursor to the second row with suitable location
	LCD_displayString("Temp =    C");

    while(1)
    {

    	temp = LM35_getTemperature();



							// Display the temperature value every time at same position
		LCD_moveCursor(1,10);
		if(temp >= 100)
		{
			LCD_intgerToString(temp);
		}
		else
		{
			LCD_intgerToString(temp);
							// In case the digital value is two or one digits print space in the next digit place
			LCD_displayCharacter(' ');
		}



							// Display the state every time at same position
		LCD_moveCursor(0,10);
		if (temp < 30)
		{
			LCD_displayString("OFF");
			DcMotor_Rotate(stop,0);      // Turn off the motor and assign its speed to ZERO
		}
		else if (temp >= 30 && temp < 60)
		{
			LCD_displayString("ON");
			LCD_displayCharacter(' ');
			DcMotor_Rotate(CW,25);      // Turn on the motor with 25% of its speed
		}
		else if (temp >=60 && temp < 90)
		{
			LCD_displayString("ON");
			DcMotor_Rotate(CW,50);      // Turn on the motor with 50% of its speed
		}
		else if (temp >=90 && temp < 120)
		{
			LCD_displayString("ON");
			DcMotor_Rotate(CW,75);      // Turn on the motor with 75% of its speed
		}
		else if (temp >=120)
		{
			LCD_displayString("ON");
			DcMotor_Rotate(CW,100);     // Turn on the motor with 100% of its speed
		}


    }
}
