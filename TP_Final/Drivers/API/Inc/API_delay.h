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
/**
 * @brief  This function loads the delay duration time but does not start the account.
 * @param  delay: Struct delay_t .
 * @param  duration: Specifies the duration of the delay.
 * @retval None
 */
void delayInit( delay_t * delay, tick_t duration);

/**
 * @brief  This function verifies the status of the running flag and if it completes the duration of the delay.
 * @param  delay: Struct delay_t.
 * @retval value boolean. True: Complete the duration delay, false: Not complete the duration delay.
 */
bool_t delayRead( delay_t * delay);

/**
 * @brief  This function is executed in case of error occurrence.
 * @param  delay: Struct delay_t.
 * @param  duration: Specifies the duration of the delay.
 * @retval None
 */
void delayWrite( delay_t * delay, tick_t duration);

#endif /* API_DELAY_H_ */
