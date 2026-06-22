/*
 * Combine_Signal.c
 *
 *  Created on: Jun 21, 2026
 *      Author: antondzisenko
 */


/*		SignalStrutureCombine
 * 	кладається з наступних параметрів
 *
 * 		- uint8_t  SignalFrame[]; -> параметер що казує на кількість буферів з яких скоадажться сигнал
 * 	* максимальга кіоткість в трапеціі (4) більше цієї кількості не буде складатись ні олин сигнал
 * 	- підйом
 * 	- утримання 1
 * 	- спуск
 * 	- утримання 0
 *
 *
 *
 * 	Frame_NUM -> буфери з параметрами відмальовки
 *
 * 	WorkSegment_NUM -> змінна яка вказує скільки корисних елементів в буфері
 * 	(якщо велика частота сигналу то кількість точок може бути меншою так як частота дескритизаціїї занадто велтка)
 *
 * 	TimARR_NUM -> значення переповнення для кожного масиву для зміни частоти дескритиації
 *
 *  TimPrescaler -> значення дільника в таймері, підбирається автоматично, використовужться для сильної зміни сигналу
 *  (можливо потім буде теж 4)
 */

#include <stdint.h>
#include "main.h"


typedef struct
{
    uint32_t Frame_one[255];
    uint32_t Frame_two[255];
    uint32_t Frame_three[255];
    uint32_t Frame_four[255];

    uint8_t	 WorkSegmen_one;
    uint8_t  WorkSegmen_two;
    uint8_t  WorkSegmen_three;
    uint8_t  WorkSegmen_four;

    uint16_t TimARR_one;
	uint16_t TimARR_two;
	uint16_t TimARR_tree;
	uint16_t TimARR_four;

	uint16_t TimPrescaler;
} SignalStrutureCombine;

 SignalStrutureCombine RuntimeSignal;








