/******************************************************************************
 *
 * Module: APP
 *
 * File Name: app.c
 *
 * Description: Source file for the application
 *
 * Author: Mohamed IBRAHIM
 *
 *******************************************************************************/

#include "../HAL/DC_MOTOR/dc_motor.h"
#include "../HAL/LCD/lcd.h"
#include "../HAL/LM35_SENSOR/lm35_sensor.h"

#include "../MCAL/ADC/adc.h"


uint8 temp = 0; 	/* to store lm35 reading */

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Description :
 * This function is responsible for initializing the peripherals used
 */
void APP_init(void)
{

	ADC_ConfigType adc_ch2 = {.ref_volt = ADC_Internal, .prescaler = ADC_PRESCALER_8};
	ADC_init(&adc_ch2);
	LCD_init();
	DcMotor_Init();

	LCD_displayStringRowColumn(0, 4, "FAN IS ");
	LCD_displayStringRowColumn(1, 4, "TEMP = ");

}
/*
 * Description : This Function gets temperature sensor reading, prints it on the LCD, and controls the
 * 				 motor state based on the temperature value.
 */
void APP_start(void)
{

	/* get lm35 reading */
	temp = LM35_getTemperature();

	/* display temp on LCD */
	LCD_moveCursor(1, 11);
	if(temp < 10)
	{
		LCD_intgerToString(temp);
		LCD_displayString("  ");
	}
	else if (temp < 100)
	{
		LCD_intgerToString(temp);
		LCD_displayString(" ");
	}
	else
	{
		LCD_intgerToString(temp);

	}

	/* check temp level */

	/* if  temp >= 120 */
	if (temp >= 120)
	{
		/* display "FAN is ON" */
		LCD_displayStringRowColumn(0, 11, "ON ");

		/* turn motor on with 100% speed */
		DcMotor_Rotate(CW, 100);
	}

	/* if  temp >= 90 */
	else if (temp >= 90)
	{
		/* display "FAN is ON" */
		LCD_displayStringRowColumn(0, 11, "ON ");

		/* turn motor on with 75% speed */
		DcMotor_Rotate(CW, 75);
	}

	/* if  temp >= 60 */
	else if (temp >= 60)
	{
		/* display "FAN is ON" */
		LCD_displayStringRowColumn(0, 11, "ON ");

		/* turn motor on with 50% speed */
		DcMotor_Rotate(CW, 50);

	}

	/* if  temp >= 30 */
	else if (temp >= 30)
	{
		/* display "FAN is ON" */
		LCD_displayStringRowColumn(0, 11, "ON ");

		/* turn motor on with 25% speed */
		DcMotor_Rotate(CW, 25);
	}

	/* if  temp < 30 */
	else
	{
		/* display "FAN is OFF */
		LCD_displayStringRowColumn(0, 11, "OFF");

		/* turn motor off */
		DcMotor_Rotate(STOP, 0);
	}
}
