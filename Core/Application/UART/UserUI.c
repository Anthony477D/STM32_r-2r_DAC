/*
 * UserUI.c
 *
 *  Created on: Jun 15, 2026
 *      Author: antondzisenko
 */
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "main.h"
#include "UserUI.h"
#include "UI_Layer.h"

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
	LAYER_SIGNALSET,
	LAYER_PARAMSET,
	LAYER_CONFGEN
} LayerMashin;
LayerMashin SetLayer;

typedef struct
{
	uint16_t SignalFrequensy;
	uint8_t LengthPatrOne;
	uint8_t LengthPartTwo;
	uint8_t LengthPartThree;
	uint8_t LengthPartFour;
}SignalParam;

SignalParam SignalParam2Generate;


// маркери
bool SendIvent;
bool UpdateMenu;

// змінні для Rx буферу та запису
uint8_t rxByte; 		// байт для запису з ортимання
char rxBuffer[64];	// буфер для зберігання отриманих данних
uint8_t rxIndex = 0;	// індекс масиву char, для поелементного запису

// param to set zero pion to start menu(LAYER_0)
uint32_t messageTimer; //zero poin to timer layer_0 interface

// param to set max Frequensi signal
int F_max = 10000; // максимальна частота сигналу

/*
 * 		Fuction to uinit UI
 * 	Start scan RX data from terminal
 */
void UserUI_Init(void)
{
    HAL_UART_Receive_IT(&huart1, &rxByte, 1);
    SetLayer = LAYER_0;
    messageTimer = 0;
    UpdateMenu = false;
    SendIvent = false;
}


/*
 * 		Function to send massege
 * 	Send massege to terminal
 */
void SendMessage(char *str)
{
    HAL_UART_Transmit(
        &huart1,
        (uint8_t*)str,
        strlen(str),
        HAL_MAX_DELAY
    );
}


/*
 * 		Function to write data from UART to rxbuffer
 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{

    if (huart->Instance == USART1)
    {
    	if((rxByte == '\r') || (rxByte == '\n'))
    	{
    	    rxBuffer[rxIndex] = '\0';
    	    SendIvent = true;

    	}else{
    		rxBuffer[rxIndex++] = rxByte;
    	}

        HAL_UART_Receive_IT(&huart1, &rxByte, 1);
    }

}


/*
 * 		Function to clear rxbuffer
 * 	we need clear always after new read operation
 */
void ClearRxBuffer (void){
	rxIndex = 0;
	for(int i = 0; i < sizeof(rxBuffer); i++)
	{
		rxBuffer[i] = '\0';
	}

}


/*
 * 		Function to set how UI we need to visualisate
 * 	When we set signal in terminal we need draw confirm signal
 */
void SetUI_Signal_to_visualisation(void){
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


/*
 * 		Steck functions when we change input buffer
 */
bool SetHelp(void){
	if(strcmp(rxBuffer, "HELP") == 0){
		return true;
	}else{
		return false;
	}
}

bool SetExit(void){
	if(strcmp(rxBuffer, "EXIT") == 0){
		return true;
	}else{
		return false;
	}
}

bool SetConfirm(void){
	if(strcmp(rxBuffer, "CONF") == 0){
		return true;
	}else{
		return false;
	}
}

bool SetSquare(void){
	if(strcmp(rxBuffer, "SQUARE") == 0){
		return true;
	}else{
		return false;
	}
}

bool SetTriangle(void){
	if(strcmp(rxBuffer, "TRIANGLE") == 0){
		return true;
	}else{
		return false;
	}
}

bool SetSawtooth(void){
	if(strcmp(rxBuffer, "SAWTOOTH") == 0){
		return true;
	}else{
		return false;
	}
}

bool SetTrapezia(void){
	if(strcmp(rxBuffer, "TRAPESSIA") == 0){
		return true;
	}else{
		return false;
	}
}




/*
 *
 */
void SetLayerHELP(void){

	if(SetSquare()){
		CurrentSignal = MENU_SQUARE;
		SetLayer = LAYER_SIGNALSET;

	}else if(SetTriangle()){
		CurrentSignal = MENU_TRIANGLE;
		SetLayer = LAYER_SIGNALSET;

	}else if(SetSawtooth()){
		CurrentSignal = MENU_SAW;
		SetLayer = LAYER_SIGNALSET;

	}else if(SetTrapezia()){
		CurrentSignal = MENU_TRAP;
		SetLayer = LAYER_SIGNALSET;
	}

}

/*
 *
 */
void SetLayerSignal(void){

	if(SetExit()){
		SetLayer = LAYER_HELP;
	}

	if(SetConfirm()){
		SetLayer = LAYER_PARAMSET;
	}
	/*
	 *

	uint16_t value = atoi(rxBuffer);

	if(value <= F_max ){
		SignalParam2Generate.SignalFrequensy = value;
	}else{
		SendMessage("Incorrect value\r\n");
	}
	*/
}

/*
 *  castom parser to set signal parameters
 */
void ParserSignalParam(void){
	uint16_t value = atoi(rxBuffer);

		if(value <= F_max ){
			SignalParam2Generate.SignalFrequensy = value;
		}else{
			SendMessage("Incorrect value\r\n");
		}

	switch (CurrentSignal){
		case MENU_SQUARE:

			break;

		case MENU_TRIANGLE:

			break;

		case MENU_SAW:

			break;

		case MENU_TRAP:

			break;
		}


}




/*
 * 		Functions whith layers state mashine
 *
 *
 */


//************************************************************************
// 			Function to read console comand
// register HELP
// regicter form signal
// register EXIT
// register and confirm parameters
void ParserF (void)
{
	// chech to send HELP
	if(SetHelp()){
		SetLayer = LAYER_HELP;
		UpdateMenu = true;
	}
	/*
	 * 		Main menu parser
	 *
	 * 	-> Layer HELP(user set signal form)
	 *
	 * 	-> Layer SIGNAL 	(user set HELP to main menu)
	 * 						(user set EXIT to main menu)
	 *						(user set CONF to setparam menu)
	 *
	 * 	-> Layer SIGPARAM 	(User set HELP to main menu)
	 * 						(user set EXIT to set frequance)
	 * 						(user set write param one by one) - use castom parser
	 *
	 * 	-> Layer CONFSIGNAL	(User set HELP to main menu)
	 * 						(user set EXIT to SIGPARAM)
	 * 						(user set CONF to generate signal and exit to main menu) - use castom parser
	 *
	 */
	if(SetLayer != LAYER_0){

	// якщо ми не викликаємо HELP меню, то парсимо далі ввід данних
	switch (SetLayer){


	case LAYER_PARAMSET:
	// check income signal parameter
		ParserSignalParam();
		UpdateMenu = true;
		break;

	case LAYER_SIGNALSET:
	//check comand and set Frequency
		SetLayerSignal();
		UpdateMenu = true;
		break;

	case LAYER_HELP:
	// check comand and set signal from layer HELP
		SetLayerHELP();
		UpdateMenu = true;
		break;

	}
	}
	ClearRxBuffer();
}

//************************************************************************

//************************************************************






void StarComunication(void){
	/* 		Check input data whith terminal
	 *  TRUE 	-> call main parser
	 *  FALSE 	-> swhith layer UI
	 */

	if(SendIvent){
		ParserF();
		SendIvent = false;
	}


	switch (SetLayer){
//-----------------------------------------
		case LAYER_0:
		UILayer0(messageTimer);
		UpdateMenu = false;
	break;
//-----------------------------------------
		case LAYER_HELP:
		if(UpdateMenu){
		UILayerHelpMenu();
		UpdateMenu = false;
			}
	break;
//-----------------------------------------
		case LAYER_SIGNALSET:
		SetUI_Signal_to_visualisation();
	break;
//-----------------------------------------
		case LAYER_PARAMSET:
		if(UpdateMenu){

		UpdateMenu = false;
		}
	break;


	}


}
