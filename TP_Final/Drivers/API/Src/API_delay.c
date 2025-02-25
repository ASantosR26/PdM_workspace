/*
 * API_delay.c
 *
 *  Created on: 5 nov. 2021
 *      Author: alex
 */

/* Includes ------------------------------------------------------------------*/
#include "API_delay.h"


void delayInit(delay_t * delay, tick_t duration)
{
	if(delay != NULL){
		delay->running = false;
		delay->duration = duration;
	}
}

bool_t delayRead(delay_t * delay)
{
	bool_t runTime = false;
	if(delay != NULL){
		if(!delay->running){
			delay->startTime = HAL_GetTick();
			delay->running = true;
		}else if((HAL_GetTick()- delay->startTime) >= delay->duration){
			delay->running = false;
			runTime = true;
		}
	}
	return runTime;
}

void delayWrite( delay_t * delay, tick_t duration)
{
	if(delay != NULL){
		delay->duration = duration;
		delay->running = false;
	}
}
