/*
 * UI_Layer.c
 *
 *  Created on: Jun 22, 2026
 *      Author: antondzisenko
 *
 *      In these file i save all UI to mu program
 *      these layer we only draw in terminal
 */
#include "main.h"
#include "UserUI.h"
#include <stdio.h>

//************************************************************************
// layre 0 is layer first launch

void UILayer0 (uint32_t zeropoint){

	if (HAL_GetTick() - zeropoint >= 1000){
		zeropoint = HAL_GetTick();
		SendMessage("ready to start, send HELP to menu\r\n");

	}
}



//************************************************************
// Layer HelpMenu is layer to main menu and mune to HELP
// Layer 1
void UILayerHelpMenu(void){
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
}


//************************************************************
// Layer when have visualisate all signal form
// Layer 2
void UISquareInterface(void){
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
}

void UITriangleInterface(void){
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
}

void UISawtoothInterface(void){
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
}

void UITrapeziaInterface(void){
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
}


//************************************************************
// we see this layer when we confirm the signal forms
// layer when we say about max Frequency
void UILayerFrequencySet(uint16_t Freqmax){
	char FreqSetData [32];
	SendMessage(		"------------------------------\r\n");
	sprintf(FreqSetData,"F_max = %d\r\n", Freqmax);
	SendMessage(FreqSetData);
	SendMessage("Set Frequency value -> Hz      \r\n");

}


//************************************************************
// we see this layer when we set the frequency
// Layer when we set the parameter signal
void UILayerParameterSignalSet(uint16_t Freq){
	char FreqData [32];
		SendMessage("------------------------------\r\n");
		sprintf(FreqData, "Frequency -> %d\r\n", Freq);
		SendMessage(FreqData);
}



