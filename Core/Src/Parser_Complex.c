/*
 * Simple_Parser.c
 *
 *  Created on: Jan 4, 2022
 *      Author: jlu
 */

#include "main.h"
#include "ring_buffer.h"
#include "string.h"
#include "utils.h"
#include "Parser_Complex.h"
#include "stdio.h"
#include "stdlib.h"

#define QUANTITY_LED 6
static char MyName[32] = "No name";


void ParserTakeLine(RingBuffer_t *Buf, uint8_t *Destination)
{
	uint8_t tmp;
	uint8_t i = 0;

	do
	{
		RB_Read(Buf, &tmp);

//		if (tmp == CARRETURN)
		if (tmp == ENDLINE)
		{

			Destination[i] = 0;
		}
		else
		{
			Destination[i] = tmp;

		}

		i++;
//	} while (tmp != CARRETURN);
    } while (tmp != ENDLINE);

}
static void Parser_ParsNAME(void)
{
	char Message[64];
	char* ParsePointer = strtok(NULL, ""); // Copy all data past=

	if(strlen(ParsePointer) > 0)
	{
		if (strcmp("?", ParsePointer) == 0)
		{
			sprintf(Message, "Device name: %s \r\n", MyName);
			UartLog(Message);
		}
		else
		{
			if(strlen(ParsePointer) > 32)
			{
			UartLog("Name should by less than 32 byte \r\n");
			return;
			}
			else
			{
				strcpy(MyName, ParsePointer);
				sprintf(Message, "New device name is: %s \r\n", MyName);
				UartLog(Message);
			}
		}
	}
	else
	{
		UartLog("Wrong data  \r\n");
		return;
	}

}

static void Parser_ParsLED(void)
{
	uint8_t i;
	char msg[32];
	for (i = 0; i < QUANTITY_LED; i++)
	{
		char *ParsePointer = strtok(NULL, ",");
		if (ParsePointer[0] < '0' || ParsePointer[0] > '1')
		{
			UartLog("LED wrong value. Type 0 or 1  \r\n");
			return;
		}

		if (strlen(ParsePointer) > 0)
		{
			if (ParsePointer[0] == '1')
			{
				switch (i)
				{
				case 0:
					HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET);
					sprintf(msg, "OK LED %d ON\n\r", i);
					UartLog(msg);
					break;
				case 1:
					HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PIN_SET);
					sprintf(msg, "OK LED %d ON\n\r", i);
					UartLog(msg);
					break;
				case 2:
					HAL_GPIO_WritePin(LD4_GPIO_Port, LD4_Pin, GPIO_PIN_SET);
					sprintf(msg, "OK LED %d ON\n\r", i);
					UartLog(msg);
					break;
				case 3:
					HAL_GPIO_WritePin(LD5_GPIO_Port, LD5_Pin, GPIO_PIN_SET);
					sprintf(msg, "OK LED %d ON\n\r", i);
					UartLog(msg);
					break;
				case 4:
					HAL_GPIO_WritePin(LD6_GPIO_Port, LD6_Pin, GPIO_PIN_SET);
					sprintf(msg, "OK LED %d ON\n\r", i);
					UartLog(msg);
					break;
				case 5:
					HAL_GPIO_WritePin(LD7_GPIO_Port, LD7_Pin, GPIO_PIN_SET);
					sprintf(msg, "OK LED %d ON\n\r", i);
					UartLog(msg);
					break;
				}

			}
			else if (ParsePointer[0] == '0')
			{
				switch (i)
				{
				case 0:
					HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);
					sprintf(msg, "OK LED %d ON\n\r", i);
					UartLog(msg);
					break;
				case 1:
					HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PIN_RESET);
					sprintf(msg, "OK LED %d ON\n\r", i);
					UartLog(msg);
					break;
				case 2:
					HAL_GPIO_WritePin(LD4_GPIO_Port, LD4_Pin, GPIO_PIN_RESET);
					sprintf(msg, "OK LED %d ON\n\r", i);
					UartLog(msg);
					break;
				case 3:
					HAL_GPIO_WritePin(LD5_GPIO_Port, LD5_Pin, GPIO_PIN_RESET);
					sprintf(msg, "OK LED %d ON\n\r", i);
					UartLog(msg);
					break;
				case 4:
					HAL_GPIO_WritePin(LD6_GPIO_Port, LD6_Pin, GPIO_PIN_RESET);
					sprintf(msg, "OK LED %d ON\n\r", i);
					UartLog(msg);
					break;
				case 5:
					HAL_GPIO_WritePin(LD7_GPIO_Port, LD7_Pin, GPIO_PIN_RESET);
					sprintf(msg, "OK LED %d ON\n\r", i);
					UartLog(msg);
					break;
				}
			}
		}
	}
}


static void Parser_ParsENV(void)
{
//	uint8_t i, j;
	uint8_t i;
	char Message[32];

	float EnvParameters[3];


	for(i=0; i<3; i++)
	{
		char* ParsePointer = strtok(NULL, ",");

		if(strlen(ParsePointer) > 0)
		{
//			for(j=0; ParsePointer[j] !=0; j++)
//			{
//				if((ParsePointer[j] < '0' || ParsePointer[j] > '9') &&  ParsePointer[j] != '.')
			    if((ParsePointer[i] < '0' || ParsePointer[i] > '9') &&  ParsePointer[i] != '.')
				{
					UartLog("ENV ERROR. Example ENV=X,Y,Z - float");
				    return;
				}
//			}

			EnvParameters[i] = atof(ParsePointer);
		}
		else
		{
			UartLog("ENV ERROR. Example ENV=X,Y,Z");
		    return;
		}

	}

	sprintf(Message, "Temperature: %.1f\r\n", EnvParameters[0]);
	UartLog(Message);

	sprintf(Message, "Humanity: %.1f\r\n", EnvParameters[1]);
	UartLog(Message);

	sprintf(Message, "Pressure: %.1f\r\n", EnvParameters[2]);
	UartLog(Message);
}

// NAME=
//      STRING
//		?
void Parser_Pars(uint8_t *DateToParse)
{
	char* ParsePointer = strtok((char*)DateToParse, "=");

	if (strcmp("LED", ParsePointer) == 0)
	{
		Parser_ParsLED(); // LED=1 OR 0
	}
	else if (strcmp("ENV", ParsePointer) == 0)
	{
		Parser_ParsENV(); // ENV=1.2,2.3,4.5
	}
	else if (strcmp("NAME", ParsePointer) == 0)
	{
		Parser_ParsNAME(); // ENV=1.2,2.3,4.5
	}
	else
	{
		UartLog("incorrect command ! \r\n ");
	}


}

