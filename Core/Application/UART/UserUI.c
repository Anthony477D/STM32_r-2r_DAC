/*
 * UserUI.c
 *
 *  Created on: Jun 15, 2026
 *      Author: antondzisenko
 */
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include "main.h"
#include "UserUI.h"

extern UART_HandleTypeDef huart1;

// перерахування вибору форми сигналу
typedef enum
{
    MENU_SQUARE,
    MENU_TRIANGLE,
    MENU_SAW,
	MENU_TRAP
//	MENU_SIN,

}SetSignalUI;
SetSignalUI CurrentSignal;

// перерахування вибору слою меню
typedef enum
{
	LAYER_0,
	LAYER_HELP,
	LAYER_SIGNAL
//	LAYER_PARAM
} LayerMashin;
LayerMashin SetLayer;


// маркери
bool SendIvent = false;
bool UpdateMenu = false;

// змінні для Rx буферу та запису
uint8_t rxByte; 		// байт для запису з ортимання
char rxBuffer[64];	// буфер для зберігання отриманих данних
uint8_t rxIndex = 0;	// індекс масиву char, для поелементного запису

uint32_t messageTimer; // нульова точка відліку для таймера на повіломлення layer_0



void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{

    if (huart->Instance == USART1)
    {
    	if((rxByte == '\r') || (rxByte == '\n'))
    	{
    	    rxBuffer[rxIndex] = '\0';
    	    SendIvent = true;
    	    //rxIndex = 0;
    	}else{
    		rxBuffer[rxIndex++] = rxByte;
    	}

        HAL_UART_Receive_IT(&huart1, &rxByte, 1);
    }
    //SendIvent = true;
}
//************************************************************************


void ClearRxBuffer (void){
	rxIndex = 0;
	for(int i = 0; i < sizeof(rxBuffer); i++)
	{
		rxBuffer[i] = '\0';
	}

}
//************************************************************************


void ParserF (void)
{

	// set help menu -> always
	if(strcmp(rxBuffer, "HELP") == 0){
		SetLayer = LAYER_HELP;
		UpdateMenu = true;
	}


	if(SetLayer != LAYER_0){

	// якщо ми не викликаємо HELP меню, то парсимо далі ввід данних
	switch (SetLayer){
		case LAYER_HELP:
			// парсимот назви функцій
			if(strcmp(rxBuffer, "SQUARE") == 0){
				CurrentSignal = MENU_SQUARE;
				SetLayer = LAYER_SIGNAL;
				UpdateMenu = true;

			}
			else if(strcmp(rxBuffer, "TRIANGLE") == 0){
				CurrentSignal = MENU_TRIANGLE;
				SetLayer = LAYER_SIGNAL;
				UpdateMenu = true;

			}else if(strcmp(rxBuffer, "SAWTOOTH") == 0){
				CurrentSignal = MENU_SAW;
				SetLayer = LAYER_SIGNAL;
				UpdateMenu = true;

			}else if(strcmp(rxBuffer, "TRAPESSIA") == 0){
				CurrentSignal = MENU_TRAP;
				SetLayer = LAYER_SIGNAL;
				UpdateMenu = true;

			}
			break;


		case LAYER_SIGNAL:
			// парсимо підтвкрдження та параметри функції
			if(strcmp(rxBuffer, "CONF") == 0){
				//SetLayer = LAYER_PARAM;
				UpdateMenu = true;

			}
			else if(strcmp(rxBuffer, "EXIT") == 0){
				SetLayer = LAYER_HELP;
				UpdateMenu = true;

			}
			break;

		}

	}


	ClearRxBuffer();
}
//************************************************************************

void UILayer0 (void){

	if (HAL_GetTick() - messageTimer >= 1000){
		messageTimer = HAL_GetTick();
		SendMessage("ready to start, send HELP to menu\r\n");
	}

}
//************************************************************

void UILayerHelpMenu(void){

	if(UpdateMenu == true){
		SendMessage(
				"                              \r\n"
				"------------------------------\r\n"
				"Set signal form:              \r\n"
				"  -> SQUARE                   \r\n"
				"  -> TRIANGLE                 \r\n"
				"  -> SAWTOOTH                 \r\n"
				"  -> TRAPESSIA                \r\n"
				"  -> SIN                      \r\n"
				);

		UpdateMenu = false;
	}

}
//************************************************************



void UISquareInterface(void){
	if(UpdateMenu == true){
		SendMessage(
				"                              \r\n"
				"------------------------------\r\n"
				"MENU  SQUARE                  \r\n"
				"set parameters:               \r\n"
				"      _____          _____    \r\n"
				"     |     |        |     |   \r\n"
				"     |     |        |     |   \r\n"
				"_____|     |________|     |___\r\n"
				"     ^     ^        ^         \r\n"
				"     |--a--|        |         \r\n"
				"     |-------b------|         \r\n"
				"                              \r\n"
				"Send --> EXIT to exit         \r\n"
				"Send --> CONF to set paramer  \n\r"
			);

		UpdateMenu = false;

	}

}
//************************************************************

void UITriangleInterface(void){
	if(UpdateMenu == true){
		SendMessage(
				"                              \r\n"
				"------------------------------\r\n"
				"MENU  TRIANGLE                \r\n"
				"set parameters:               \r\n"
				"       _             _        \r\n"
				"      /|\\           / \\      \r\n"
				"     / | \\         /   \\     \r\n"
				"    /  |  \\       /     \\    \r\n"
				"___/   |   \\_____/       \\___\r\n"
				"   ^   ^   ^    ^             \r\n"
				"   |-a-|-b-|    |             \r\n"
				"   |------c-----|             \r\n"
				"                              \r\n"
				"Send --> EXIT to exit         \r\n"
				"Send --> CONF to set paramer  \n\r"
			);

		UpdateMenu = false;

	}

}
//************************************************************
void UISawtoothInterface(void){
	if(UpdateMenu == true){
		SendMessage(
				"                              \r\n"
				"------------------------------\r\n"
				"MENU  TRIANGLE                \r\n"
				"set parameters:               \r\n"
				"                              \r\n"
				"        /|           /|       \r\n"
				"       / |          / |       \r\n"
				"      /  |         /  |       \r\n"
				"_____/   |________/   |_______\r\n"
				"     ^   ^        ^           \r\n"
				"     |-a-|        |           \r\n"
				"     |------b-----|           \r\n"
				"                              \r\n"
				"Send --> EXIT to exit         \r\n"
				"Send --> CONF to set paramer  \n\r"
			);

		UpdateMenu = false;

	}
}
//************************************************************

void UITrapeziaInterface(void){
	if(UpdateMenu == true){
		SendMessage(
				"                              \r\n"
				"------------------------------\r\n"
				"MENU  TRIANGLE                \r\n"
				"set parameters:               \r\n"
				"     _______            _____\r\n"
				"    /|     |\\          /     \r\n"
				"   / |     | \\        /      \r\n"
				"  /  |     |  \\      /       \r\n"
				"_/   |     |   \\____/        \r\n"
				" ^   ^     ^   ^    ^         \r\n"
				" |-a-|--b--|-c-|    |         \r\n"
				" |---------d--------|         \r\n"
				"                              \r\n"
				"Send --> EXIT to exit         \r\n"
				"Send --> CONF to set paramer  \n\r"
			);

		UpdateMenu = false;

	}
}
//************************************************************


void UISetSignal(void){
	switch (CurrentSignal){
	case MENU_SQUARE:
		UISquareInterface();
		break;

	case MENU_TRIANGLE:
		UITriangleInterface();
		break;

	case MENU_SAW:
		UISawtoothInterface();
		break;

	case MENU_TRAP:
		UITrapeziaInterface();
		break;
	}
}

void UISetSignalParam(void){

}
/*
 *
 *
 */

void StarComunication(void){
	// запускаємо переривання на отримання данних
	if(SendIvent == true){
		ParserF();
		SendIvent = false;
	}


	switch (SetLayer){
		case LAYER_0:
		UILayer0();
	break;

		case LAYER_HELP:
		UILayerHelpMenu();
	break;

		case LAYER_SIGNAL:
		UISetSignal();
	break;


	}


}
//************************************************************************



void UserUI_Init(void)
{
    HAL_UART_Receive_IT(&huart1, &rxByte, 1);
    SetLayer = LAYER_0;
    messageTimer = 0;
}
//************************************************************************





// функція для надсилання данних
void SendMessage(char *str)
{
    HAL_UART_Transmit(
        &huart1,
        (uint8_t*)str,
        strlen(str),
        HAL_MAX_DELAY
    );
}
