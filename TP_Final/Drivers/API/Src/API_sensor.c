/*
 * API_sensor.c
 *
 *  Created on: 5 dic. 2021
 *      Author: alex
 */


#include "API_sensor.h"

/* Private variables ---------------------------------------------------------*/
static sensor_t sensorState;

/* Implementation of public functions ---------------------------------------------------------*/
bool_t sensorInit(sensor_t * sensorInfo)
{
	bool_t initSensor = false;
	if(sensorInfo != NULL)
	{
		sensorInfo->readerRFID = notDetect;
		sensorInfo->loopDetector = notDetect;
		sensorInfo->limitSwitchTop = notDetect;
		sensorInfo->limitSwitchBottom = detect;

		sensorState = *sensorInfo;
		initSensor = true;
	}
	return initSensor;
}

void sensorUpdateState(uint8_t  command, sensor_t * sensorInfo)
{
	switch(command){
		case 'a':
			sensorInfo->readerRFID = detect;
			break;
		case 'A':
			sensorInfo->readerRFID = notDetect;
			break;
		case 'b':
			sensorInfo->limitSwitchTop = detect;
			break;
		case 'B':
			sensorInfo->limitSwitchTop = notDetect;
			break;
		case 'c':
			sensorInfo->loopDetector = detect;
			break;
		case 'C':
			sensorInfo->loopDetector = notDetect;
			break;
		case 'd':
			sensorInfo->limitSwitchBottom =  detect;
			break;
		case 'D':
			sensorInfo->limitSwitchBottom = notDetect;
			break;
		default:
			break;
	}
}

bool_t sensorReaderRFID_getState(void)
{
	return sensorState.readerRFID;
}

bool_t sensorLoopDetector_getState(void)
{
	return sensorState.loopDetector;
}

bool_t  sensorLimitSwitchTop_getState(void)
{
	return sensorState.limitSwitchTop;
}

bool_t sensorlimitSwitchBottom_getState(void)
{
	return sensorState.limitSwitchBottom;
}

