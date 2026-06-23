/*
 * TestGenerate.c
 *
 *  Created on: Jun 23, 2026
 *      Author: antondzisenko
 */
#include "main.h"
#include <stdbool.h>
#include "UserUI.h"
#include <stdio.h>

typedef struct {
	uint32_t PatrOne[255];
	uint32_t PartTwo[255];

}DMABuffer;
DMABuffer DMADataSignal;

//	0b0000 0000 0000 0000 	0000 0000 0000 0001, //pa0 1 -> 1596 mV
uint32_t LowOutput 		= 0b00000000111111110000000000000000;
uint32_t HightOutput 	= 0b00000000000000000000000011111111;

void TriangleGenUp(){
	int count = 0;
	int length = 255;
	int LSBSermode = 7;
	int LSBResetmode = 23;

	bool Updatebuffer = false;



	// перераховуємл почерзі кожен варіант
	for(; count < length; count++){

		// якщо це початок відліку, встановлюємо перший елемент так щоб всі піни були reset
		if(count == 0){
			DMADataSignal.PatrOne[count] = LowOutput;

			// основний блок коду де ми змінюємо біти
		}else{

			/*		записужмо в поточний елемент масиву значкння з попереднього
			 *  значення масиву в нас не присвоєні, тому нам потріюно це зробити
			 *  двалі працюємо з поточнийм значенням масиву як з попередніми змінними
			 */

			DMADataSignal.PatrOne[count] = DMADataSignal.PatrOne[count-1];

			/*
			 * 		Перевіряємо молодший біт set
			 * 	якщо він == 0 то встановлюємо його в значкння 1
			 * 	+ встановлюємо reset в 0
			 *
			 * 	якщо він == 1 то встановлюємо його в значення 0
			 * 	+ встановлюємо reset в 1
			 * 	+ встановлюємо маркер оновлення в true
			 * 		ми змінили біт 1 на 0 а отже сташий біт теж змінюється, перевіряємо і його
			 */
			if( (DMADataSignal.PatrOne[count] & (1 << LSBSermode)) == 0){

				DMADataSignal.PatrOne[count] |= (1 << LSBSermode); // -> встановлюємо біт set для PA7
				DMADataSignal.PatrOne[count] &= ~(1 << LSBResetmode); // -> зкидаємо біт reset для PA7

			}else{

				DMADataSignal.PatrOne[count] &= ~(1 << LSBSermode); // -> зкидаємо біт set для PA7
				DMADataSignal.PatrOne[count] |= (1 << LSBResetmode); // -> встановлюємо біт reset для PA7

				Updatebuffer = true; // вказуємо що потрібно запустити цикл оновлення старших бітів
				int reg = 1; // створюємо змінну яка вказує на кількісну зміну номкра біта
				while(Updatebuffer && reg < 8)
				{

					if( (DMADataSignal.PatrOne[count] & (1 << (LSBSermode - reg ))) == 0){

						DMADataSignal.PatrOne[count] |= (1 << (LSBSermode - reg)); // -> встановлюємо біт set для PA7
						DMADataSignal.PatrOne[count] &= ~(1 << (LSBResetmode - reg)); // -> зкидаємо біт reset для PA7
						Updatebuffer = false; // вказуємо що ми оновили останні біти, виходимо з while()
					}else{

						DMADataSignal.PatrOne[count] &= ~(1 << (LSBSermode - reg)); // -> зкидаємо біт set для PA7
						DMADataSignal.PatrOne[count] |= (1 << (LSBResetmode - reg)); // -> встановлюємо біт reset для PA7
						reg++;
					}
				}


			}

		}

		// перевіряємо драбинку виводячи повідомдення
		char FreqSetData[64];
		char *ptr = FreqSetData;

		ptr += sprintf(ptr, "Buffer current --> 0b");

		for (int i = 31; i >= 0; i--)
		{
		    ptr += sprintf(ptr, "%d", (DMADataSignal.PatrOne[count] >> i) & 1);

		    if ((i % 4 == 0) && (i != 0))
		        ptr += sprintf(ptr, " ");
		}

		ptr += sprintf(ptr, "\r\n");

		SendMessage(FreqSetData);
		GPIOA->BSRR = DMADataSignal.PatrOne[count];
		HAL_Delay(1);

	}


}
