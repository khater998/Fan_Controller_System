/******************************************************************************
 *
 * Module: DC_MOTOR
 *
 * File Name: dc_motor.c
 *
 * Description: Header file for the DC_MOTOR driver
 *
 * Author: Mohamed IBRAHIM
 *
 *******************************************************************************/


#include "dc_motor.h"
#include "../../MCAL/GPIO/gpio.h"
#include "../../MCAL/PWM/pwm.h"


/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Description :
 * The Function responsible for setup the direction for the two motor pins through the GPIO driver.
 * Stop at the DC-Motor at the beginning through the GPIO driver.
 */
void DcMotor_Init(void)
{
	/* set the 2 motor pins and the enable pin of the l293 driver as output */
	GPIO_setupPinDirection(DC_MOTOR_PIN1_PORT_ID, DC_MOTOR_PIN1_PIN_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(DC_MOTOR_PIN2_PORT_ID, DC_MOTOR_PIN2_PIN_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(DC_MOTOR_EN_PORT_ID, DC_MOTOR_EN_PIN_ID, PIN_OUTPUT);

	/* Initially motor is stopped "The two pin are logic low"*/
	GPIO_writePin(DC_MOTOR_PIN1_PORT_ID, DC_MOTOR_PIN1_PIN_ID, LOGIC_LOW);
	GPIO_writePin(DC_MOTOR_PIN2_PORT_ID, DC_MOTOR_PIN2_PIN_ID, LOGIC_LOW);
	GPIO_writePin(DC_MOTOR_PIN2_PORT_ID, DC_MOTOR_EN_PIN_ID, LOGIC_LOW);

}

/*
 * Description :
 * The function responsible for rotate the DC Motor CW/ or A-CW or stop the motor based on
 * the state input state value.
 * Send the required duty cycle to the PWM driver based on the required speed value.
 */
void DcMotor_Rotate(DcMotor_State state,uint8 speed)
{
	/* check which state is required */
	switch(state)
	{
	case CW:
		/* set motor pin1 to HIGH logic, clear motor pin2 */
		GPIO_writePin(DC_MOTOR_PIN1_PORT_ID, DC_MOTOR_PIN1_PIN_ID, LOGIC_HIGH);
		GPIO_writePin(DC_MOTOR_PIN2_PORT_ID, DC_MOTOR_PIN2_PIN_ID, LOGIC_LOW);

		/* generate the required PWM */
		PWM_Timer0_Start(speed);
		break;

	case A_CW:
		/* set motor pin2 to HIGH logic, clear motor pin1 */
		GPIO_writePin(DC_MOTOR_PIN1_PORT_ID, DC_MOTOR_PIN1_PIN_ID, LOGIC_LOW);
		GPIO_writePin(DC_MOTOR_PIN2_PORT_ID, DC_MOTOR_PIN2_PIN_ID, LOGIC_HIGH);

		/* generate the required PWM */
		PWM_Timer0_Start(speed);
		break;

	case STOP:
		GPIO_writePin(DC_MOTOR_PIN1_PORT_ID, DC_MOTOR_PIN1_PIN_ID, LOGIC_LOW);
		GPIO_writePin(DC_MOTOR_PIN2_PORT_ID, DC_MOTOR_PIN2_PIN_ID, LOGIC_LOW);

		/* No PWM needed */
		PWM_Timer0_Start(0);
		break;
	}
}
