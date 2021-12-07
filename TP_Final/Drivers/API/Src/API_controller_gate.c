/*
 * API_controller_gate.c
 *
 *  Created on: 5 dic. 2021
 *      Author: alex
 */

#include "API_controller_gate.h"

/* Private typedef -----------------------------------------------------------*/
typedef enum{
	WAIT,
	OPENNING,
	OPEN,
	CLOSING
} controllerGate_t;

/* Private variables ---------------------------------------------------------*/
static controllerGate_t currentStatus;

bool_t controllerGateInit(sensor_t * sensors)
{
	bool_t validInit = false;
	if((false == sensors->readerRFID) &&
		(false == sensors->loopDetector) &&
		(false == sensors->limitSwitchTop) &&
		(true == sensors->limitSwitchBottom))
	{
		currentStatus = WAIT;
		validInit = true;
	}

	return validInit;
}

uint8_t controllerGateUpdate(sensor_t * sensors)
{
	uint8_t outputState;
	switch(currentStatus){
		case WAIT:
			if(sensors->readerRFID)
			{
				currentStatus = OPENNING;
				outputState = MOTOR_UP;

				/* Simulation */
				sensors->limitSwitchBottom = false;
			}
			else
			{
				outputState = MOTOR_STOP;

				/* Simulation */
				sensors->limitSwitchBottom = true;
			}

			/* Simulation */
			sensors->loopDetector = false;
			sensors->limitSwitchTop = false;

			break;
		case OPENNING:
			if(sensors->limitSwitchTop)
			{
				currentStatus = OPEN;
				outputState = MOTOR_STOP;
			}
			else
			{
				outputState = MOTOR_UP;
			}

			/* Simulation */
			sensors->readerRFID = true;
			sensors->loopDetector = false;
			sensors->limitSwitchBottom = false;

			break;
		case OPEN:
			if(sensors->loopDetector)
			{
				currentStatus = CLOSING;
				outputState = MOTOR_DOWN;
				sensors->readerRFID = false;
				sensors->limitSwitchTop = false;
			}
			else
			{
				outputState = MOTOR_STOP;
				sensors->readerRFID = true;
				sensors->limitSwitchTop = true;
			}

			/* Simulation */
			sensors->limitSwitchBottom = false;

			break;
		case CLOSING:
			if(sensors->limitSwitchBottom)
			{
				currentStatus = WAIT;
				outputState = MOTOR_STOP;

				/* Simulation */
				sensors->loopDetector = false;
			}
			else
			{
				outputState = MOTOR_DOWN;

				/* Simulation */
				sensors->loopDetector = true;
			}

			/* Simulation */
			sensors->readerRFID = false;
			sensors->limitSwitchTop = false;

			break;
		default:
			controllerGateInit(sensors);
			outputState = MOTOR_STOP;
			break;
	}
	return outputState;
}

void controllerGetState(char * state)
{
	if(state != NULL)
	{
		switch(currentStatus)
		{
			case 0:
				strcpy(state,"Wait");
				break;
			case 1:
				strcpy(state,"Opening");
				break;
			case 2:
				strcpy(state,"Open");
				break;
			case 3:
				strcpy(state,"Closing");
				break;
			default:
				break;
		}
	}
}
