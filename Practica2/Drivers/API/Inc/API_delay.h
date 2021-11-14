/*
 * API_delay.h
 *
 *  Created on: 5 nov. 2021
 *      Author: alex
 */

#ifndef API_DELAY_H_
#define API_DELAY_H_


/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

/* Typedef -----------------------------------------------------------*/
typedef uint32_t tick_t;
typedef bool bool_t;

typedef struct{
	tick_t startTime;
	tick_t duration;
	bool_t running;
} delay_t;

/* Global functions ---------------------------------------------------------*/
void delayInit( delay_t * delay, tick_t duration);
bool_t delayRead( delay_t * delay);
void delayWrite( delay_t * delay, tick_t duration);

#endif /* API_DELAY_H_ */
