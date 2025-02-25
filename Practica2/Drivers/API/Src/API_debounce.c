/*
 * API_debounce.c
 *
 *  Created on: 9 nov. 2021
 *      Author: alex
 */

#include "API_debounce.h"
#include "API_delay.h"
#include "stm32f4xx_nucleo_144.h" 	/* <- BSP include */

#define DELAY_DEBOUNCING 40

/* Typedef -----------------------------------------------------------*/
typedef enum{
	BUTTON_UP,
	BUTTON_FALLING,
	BUTTON_DOWN,
	BUTTON_RISING
} debounce_t;

/* Private variables ---------------------------------------------------------*/
static debounce_t currentStatus;
static delay_t delayDebouncing;

/* Private function prototypes -----------------------------------------------*/
static void buttonPressed();
static void buttonRealeased();

bool_t debounceInit(void)
{
	currentStatus = BUTTON_UP;
	delayInit(&delayDebouncing,DELAY_DEBOUNCING);

	/* Initialize BSP PB for BUTTON_USER */
	BSP_PB_Init(BUTTON_USER, BUTTON_MODE_GPIO);

	/* Initialize BSP Led for LED1, LED2 */
	//BSP_LED_Init(LED1);
	//BSP_LED_Init(LED2);

	return true;
}

uint8_t debounceUpdate(void)
{
	switch (currentStatus){
		case BUTTON_UP:
		{
			if(BSP_PB_GetState(BUTTON_USER)){
				delayRead(&delayDebouncing);
				currentStatus = BUTTON_FALLING;
			}
			return BUTTON_UP;
			break;
		}
		case BUTTON_FALLING:
		{
			if(delayRead(&delayDebouncing)){
				if(BSP_PB_GetState(BUTTON_USER)){
					currentStatus = BUTTON_DOWN;
					buttonPressed();
					return BUTTON_PRESSED;
				}else{
					currentStatus = BUTTON_UP;
				}
			}
			break;
		}
		case BUTTON_DOWN:
		{
			if(!BSP_PB_GetState(BUTTON_USER)){
				delayRead(&delayDebouncing);
				currentStatus = BUTTON_RISING;
			}
			break;
		}
		case BUTTON_RISING:
		{
			if(delayRead(&delayDebouncing)){
				if(!BSP_PB_GetState(BUTTON_USER)){
					currentStatus = BUTTON_UP;
					buttonRealeased();
					return BUTTON_RELEASED;
				}else{
					currentStatus = BUTTON_DOWN;
				}
			}
			break;
		}
		default:
			debounceInit();
			break;
	}
	return 0;
}

static void buttonPressed()
{
	//BSP_LED_Toggle(LED1);

}

static void buttonRealeased()
{
	//BSP_LED_Toggle(LED2);
}
