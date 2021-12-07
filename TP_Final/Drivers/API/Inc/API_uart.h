/*
 * API_uart.h
 *
 *  Created on: 28 nov. 2021
 *      Author: alex
 */

#ifndef API_INC_API_UART_H_
#define API_INC_API_UART_H_

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "stm32f4xx_hal.h"

/* Typedef -----------------------------------------------------------*/
typedef bool bool_t;

/* Global functions ---------------------------------------------------------*/
bool_t uartInit();
void uartSendString(uint8_t *pString, uint16_t size);
void UartReceivedChar(uint8_t * data);

#endif /* API_INC_API_UART_H_ */
