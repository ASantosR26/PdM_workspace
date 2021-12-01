/*
 * API_delay.c
 *
 *  Created on: 5 nov. 2021
 *      Author: alex
 */

/* Includes ------------------------------------------------------------------*/
#include "API_delay.h"

/**
 * @brief  This function loads the delay duration time but does not start the account.
 * @param  delay: Struct delay_t .
 * @param  duration: Specifies the duration of the delay.
 * @retval None
 */
void delayInit(delay_t * delay, tick_t duration)
{
	if(delay != NULL){
		delay->running = false;
		delay->duration = duration;
	}
}

/**
 * @brief  This function verifies the status of the running flag and if it completes the duration of the delay.
 * @param  delay: Struct delay_t.
 * @retval value boolean. True: Complete the duration delay, false: Not complete the duration delay.
 */
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

/**
 * @brief  This function is executed in case of error occurrence.
 * @param  delay: Struct delay_t.
 * @param  duration: Specifies the duration of the delay.
 * @retval None
 */
void delayWrite( delay_t * delay, tick_t duration)
{
	if(delay != NULL){
		delay->duration = duration;
	}
}
