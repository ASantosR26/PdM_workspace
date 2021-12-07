/*
 * API_uart.c
 *
 *  Created on: 28 nov. 2021
 *      Author: alex
 */

#include "API_uart.h"

/* UART handler declaration */
UART_HandleTypeDef UartHandle;

/* Private function prototypes -----------------------------------------------*/
static void uartPrintfConfiguration();
static void uart_wordLengthCfg(char *);
static void uart_stopBitCfg(char *);
static void uart_parityCfg(char *);

bool_t uartInit()
{
	bool_t status = true;
	/*##-1- Configure the UART peripheral ######################################*/
	/* Put the USART peripheral in the Asynchronous mode (UART Mode) */
	/* UART configured as follows:
		- Word Length = 8 Bits (7 data bit + 1 parity bit) :
		                  BE CAREFUL : Program 7 data bits + 1 parity bit in PC HyperTerminal
		- Stop Bit    = One Stop bit
		- Parity      = ODD parity
		- BaudRate    = 9600 baud
		- Hardware flow control disabled (RTS and CTS signals) */
	UartHandle.Instance        = USART3;

	UartHandle.Init.BaudRate   = 9600;
	UartHandle.Init.WordLength = UART_WORDLENGTH_8B;
	UartHandle.Init.StopBits   = UART_STOPBITS_1;
	UartHandle.Init.Parity     = UART_PARITY_NONE;
	UartHandle.Init.HwFlowCtl  = UART_HWCONTROL_NONE;
	UartHandle.Init.Mode       = UART_MODE_TX_RX;
	UartHandle.Init.OverSampling = UART_OVERSAMPLING_16;

	if (HAL_UART_Init(&UartHandle) != HAL_OK)
	{
		status = false;
	}

	uartPrintfConfiguration();

	return status;
}

void uartSendString(uint8_t *pString, uint16_t size)
{
	if(pString != NULL){
		HAL_UART_Transmit(&UartHandle, pString,size,0xFFFF);
	}
}

void UartReceivedChar(uint8_t * data)
{
	HAL_UART_Receive(&UartHandle,data,1,0);
}

static void uartPrintfConfiguration()
{
	const char text[] = "Configuration Uart \n"
						"Baudrate:   %lu \n"
						"WordLength: %s \n"
						"StopBits:   %s \n"
						"Parity:     %s \n\n";

	uint32_t p1;
	char p2[30], p3[30], p4[30];
	char buffer[250];

	p1 = UartHandle.Init.BaudRate;
	uart_wordLengthCfg(p2);
	uart_stopBitCfg(p3);
	uart_parityCfg(p4);

	sprintf(buffer,text, p1, p2, p3, p4);
	HAL_UART_Transmit(&UartHandle,(uint8_t *)buffer, strlen(buffer)/sizeof(char),0xFFFF);
}

static void uart_wordLengthCfg(char * wordLengthCfg)
{
	if(UART_WORDLENGTH_8B == UartHandle.Init.WordLength){
		strcpy(wordLengthCfg,"8 bytes");
	}else if(UART_WORDLENGTH_9B == UartHandle.Init.WordLength){
		strcpy(wordLengthCfg,"9 bytes");
	}
}

static void uart_stopBitCfg(char * stopBitCfg)
{
	if(UART_STOPBITS_1 == UartHandle.Init.StopBits){
		strcpy(stopBitCfg,"1 bit");
	}else if(UART_STOPBITS_2 == UartHandle.Init.StopBits){
		strcpy(stopBitCfg,"2 bit");
	}
}

static void uart_parityCfg(char * parityCfg)
{
	if(UART_PARITY_NONE == UartHandle.Init.Parity){
		strcpy(parityCfg,"None");
	}else if(UART_PARITY_EVEN == UartHandle.Init.Parity){
		strcpy(parityCfg,"par");
	}else if(UART_PARITY_ODD == UartHandle.Init.Parity){
		strcpy(parityCfg,"impar");
	}
}
