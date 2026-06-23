/*
 * UI_Layer.h
 *
 *  Created on: Jun 22, 2026
 *      Author: antondzisenko
 */

#ifndef APPLICATION_UART_UI_LAYER_H_
#define APPLICATION_UART_UI_LAYER_H_


void UILayer0 (uint32_t zeropoint);
void UILayerHelpMenu(void);

void UISquareInterface(void);
void UITriangleInterface(void);
void UISawtoothInterface(void);
void UITrapeziaInterface(void);

void UILayerFrequencySet(uint16_t Freqmax);
void UILayerParameterSignalSet(uint16_t Freq);




#endif /* APPLICATION_UART_UI_LAYER_H_ */
