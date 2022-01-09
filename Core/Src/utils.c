/*
 * utils.c
 *
 *  Created on: Jan 4, 2022
 *      Author: jlu
 */

#include "main.h"
#include "utils.h"
#include "usart.h"
#include "string.h"

void UartLog(char *Msg)
{
	HAL_UART_Transmit(&huart2, (uint8_t*) Msg, strlen(Msg), 1000);
}
