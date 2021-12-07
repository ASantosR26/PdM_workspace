/**
  ******************************************************************************
  * @file    UART/UART_Printf/Src/main.c
  * @author  MCD Application Team
  * @brief   This example shows how to retarget the C library printf function
  *          to the UART.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2017 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "API_uart.h"
#include "API_sensor.h"
#include "API_controller_gate.h"
#include "stm32f4xx_hal.h"

/** @addtogroup STM32F4xx_HAL_Examples
  * @{
  */

/** @addtogroup UART_Printf
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static uint8_t fsm_info[200];
static uint8_t rcvData;
static sensor_t sensorsInfo;

/* UART handler declaration */

/* Private function prototypes -----------------------------------------------*/

static void SystemClock_Config(void);
static void Error_Handler(void);
static void set_leds_up_motor(void);
static void set_leds_down_motor(void);
static void set_leds_stop_motor(void);
static void printf_fms_state_and_sensor(void);
/* Private functions ---------------------------------------------------------*/

static void set_leds_up_motor(void)
{
	 BSP_LED_On(LED1);
	 BSP_LED_Off(LED2);
	 BSP_LED_Off(LED3);

	 char motorInfo[] = "Motor UP \n";
	 uartSendString((uint8_t *)motorInfo,strlen(motorInfo)/sizeof(char));
}

static void set_leds_down_motor(void)
{
	BSP_LED_Off(LED1);
	BSP_LED_On(LED2);
	BSP_LED_Off(LED3);

	char motorInfo[] = "Motor DOWN \n";
	uartSendString((uint8_t *)motorInfo,strlen(motorInfo)/sizeof(char));
}

static void set_leds_stop_motor(void)
{
	BSP_LED_Off(LED1);
	BSP_LED_Off(LED2);
	BSP_LED_On(LED3);

	char motorInfo[] = "Motor STOP \n";
	uartSendString((uint8_t *)motorInfo,strlen(motorInfo)/sizeof(char));
}

static void printf_fms_state_and_sensor(void)
{

	char stateFsm[10];
	controllerGetState(stateFsm);

	sprintf((char *)fsm_info,
			"Finite State Machine \n"
			"State -> %s \n"
			"Sensor Reader (a) -> %d "
			"Sensor Top gate (b) -> %d \n"
			"Sensor Vehicle Loop Detector (c) -> %d "
			"Sensor Bottom Gate (d) -> %d \n",
			stateFsm,
			sensorsInfo.readerRFID,
			sensorsInfo.limitSwitchTop,
			sensorsInfo.loopDetector,
			sensorsInfo.limitSwitchBottom);

	uartSendString((uint8_t *)fsm_info, strlen((char *)fsm_info)/sizeof(uint8_t));
}
/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
  /* STM32F4xx HAL library initialization:
       - Configure the Flash prefetch
       - Systick timer is configured by default as source of time base, but user 
         can eventually implement his proper time base source (a general purpose 
         timer for example or other time source), keeping in mind that Time base 
         duration should be kept 1ms since PPP_TIMEOUT_VALUEs are defined and 
         handled in milliseconds basis.
       - Set NVIC Group Priority to 4
       - Low Level Initialization
     */
  HAL_Init();
  //__USART3_CLK_ENABLE();
  /* Configure the system clock to 180 MHz */
  SystemClock_Config();

  /* Initialize BSP Led for LED2 and LED3*/
  BSP_LED_Init(LED1);
  BSP_LED_Init(LED2);
  BSP_LED_Init(LED3);
  //HAL_GPIO_WritePin();

  /* Initialize UART */
  uartInit();

  /* Initialize Simulation Sensor */
  sensorInit(&sensorsInfo);

  /* Initialize the gate controller */
  controllerGateInit(&sensorsInfo);
  printf_fms_state_and_sensor();

  uint8_t OldStateMotor = MOTOR_STOP;
  uint8_t newStateMotor = 0;

  BSP_LED_On(LED3);

  /* Infinite loop */
  while (1)
  {
	  UartReceivedChar(&rcvData);

	  sensorUpdateState(rcvData, &sensorsInfo);

	  newStateMotor = controllerGateUpdate(&sensorsInfo);

	  if(newStateMotor != OldStateMotor)
	  {
		  printf_fms_state_and_sensor();

	  	  switch(newStateMotor)
	  	  {
	  	  	  case MOTOR_DOWN:
	  	  		  set_leds_down_motor();
	  	  		  break;
	  	  	  case MOTOR_UP:
	  	  		  set_leds_up_motor();
	  	  		  break;
	  	  	  case MOTOR_STOP:
	  	  		  set_leds_stop_motor();
	  	  		  break;
	  	  	  default:
	  	  		  break;
	  	  }

	  	  OldStateMotor = newStateMotor;
	  }
  }
}


/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow : 
  *            System Clock source            = PLL (HSE)
  *            SYSCLK(Hz)                     = 180000000
  *            HCLK(Hz)                       = 180000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 4
  *            APB2 Prescaler                 = 2
  *            HSE Frequency(Hz)              = 8000000
  *            PLL_M                          = 8
  *            PLL_N                          = 360
  *            PLL_P                          = 2
  *            PLL_Q                          = 7
  *            PLL_R                          = 2
  *            VDD(V)                         = 3.3
  *            Main regulator output voltage  = Scale1 mode
  *            Flash Latency(WS)              = 5
  * @param  None
  * @retval None
  */
static void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;

  /* Enable Power Control clock */
  __HAL_RCC_PWR_CLK_ENABLE();
  
  /* The voltage scaling allows optimizing the power consumption when the device is 
     clocked below the maximum system frequency, to update the voltage scaling value 
     regarding system frequency refer to product datasheet.  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  
  /* Enable HSE Oscillator and activate PLL with HSE as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 360;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }
  
  if(HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }
  
  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 
     clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;  
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;  
  if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }
}
/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
static void Error_Handler(void)
{
  /* Turn LED2 on */
  BSP_LED_On(LED2);
  while (1)
  {
  }
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
