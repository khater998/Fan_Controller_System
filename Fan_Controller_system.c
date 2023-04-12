/******************************************************************************
 *
 * File Name: Fan_Controller_System.c
 *
 * Author: Mohamed IBRAHIM
 *
 *
 * Description: A temperature-controlled fan using ATmega32 microcontroller,
 * 				in which the fan is automatically turned ON or OFF according to the	temperature.
 *
 *******************************************************************************/
#include "APP/app.h"

int main()
{
	APP_init();

	while(1)
	{
		APP_start();
	}
}
