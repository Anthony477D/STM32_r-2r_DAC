/*
 * DMA_process.c
 *
 *  Created on: Jun 15, 2026
 *      Author: antondzisenko
 */


/*	логіка роботи
 *
 * 	- DMA_Inat -> ініціалізація DMA
 *
 * 	- DMA_Start -> перший запуск DMA периферії
 * 						|
 * 		-DMA_TransferComplite -> спрацювання DMA по перериванню містить в середині функцію
 * 		(DMA_Update)-> оновлення параметрів таймера та зміна буфера
 * 						|
 *
 *
 *
 *
 */



#include "main.h"
#include "UserUI.h"
//#include "Combine_Signal.h"

#include <stdio.h>

extern DMA_HandleTypeDef hdma_tim1_up;
extern TIM_HandleTypeDef htim1;



uint32_t dma_buffer[16] ={
    0b00000000000000000000000000000001, //pa0 1 -> 1596 mV
	0b00000000000000000000000000000010,	//pa1 1 -> 0795 mV
	0b00000000000000000000000000000100,	//pa2 1
	0b00000000000000000000000000001000,	//pa3 1
	0b00000000000000000000000000010000,	//pa4 1
	0b00000000000000000000000000100000,	//pa5 1
	0b00000000000000000000000001000000,	//pa6 1
	0b00000000000000000000000010000000,	//pa7 1

	0b00000000100000000000000000000000,	//pa0 0
	0b00000000010000000000000000000000, //pa1 0
	0b00000000001000000000000000000000,	//pa2 0
	0b00000000000100000000000000000000,	//pa3 0
	0b00000000000010000000000000000000,	//pa4 0
	0b00000000000001000000000000000000,	//pa5 0
	0b00000000000000100000000000000000,	//pa6 0
	0b00000000000000010000000000000000 //pa7 0
};

uint8_t CurentSegmentState = 0;
// Початок передачі через DMA
void DMA_Start(void){

	/*
	 *	Данна функція лише задає параметри передачі DMA, не запускає а лише вказує параметри
	 * 	_IT -> вказує на те що вкінці передачі буде згенерований Ivent(переривання)
	 *
	 * 	&hdma_tim1_up,           -> вказує таймер на якому буде тактуватись DMA
	 * 	(uint32_t)dma_buffer,	-> вказує данні які будуть передватись(вказує в вигляді адреси, а в випадку з масивом це адреса на перший елемент)
	 * 	(uint32_t)&GPIOA->BSRR,	-> вказує адресу куди данні будуть передаватись
	 * 	16);						-> вказує скільки разів буде відбуватись предача данних
	 * В CubeMX ми вказували яка адреса буде змінюватись та з яким кроком TIM1 -> DMA_Setting -> Incremnt adress(world/halfworld/byte)
	 */
	HAL_DMA_Start_IT(
				&hdma_tim1_up,
				(uint32_t)dma_buffer,
		        (uint32_t)&GPIOA->BSRR,
		        16);

	// запускаємо таймер
	HAL_TIM_Base_Start(&htim1);

}


// Зупинка передачі по DMA
void DMA_Stop(void){
		HAL_TIM_Base_Stop(&htim1);
	}



// переривання DMA
void DMA_TransferComplete(DMA_HandleTypeDef *hdma)
{
    if(hdma == &hdma_tim1_up)
    {
    	SendMessage("ITR_DMA_YIIIHYYY\r\n"); // test param

    	/*
    	 * для коректності зупяняємо таймер тактування
    	 */
    	HAL_TIM_Base_Stop(&htim1);


    	/*
    	 *  змінюємо параметри дільника та переповнення таймера
    	 *  зкидуємо до нуля внутріщній лічильник таймера
    	 *  оновлюємо регістри таймера під нові параметри
    	 */
    	//TIM1->PSC = xxx;
    	TIM1->ARR = 1000;
    	TIM1->CNT = 0;              // бажано
    	TIM1->EGR = TIM_EGR_UG;

    	/*
    	 * 	Запускаємо таймер
    	 */
    	HAL_TIM_Base_Start(&htim1);

    	/*
    	 * запускаємо переривання
    	 */
    	HAL_DMA_Start_IT(
    					&hdma_tim1_up,
    					(uint32_t)dma_buffer,
    			        (uint32_t)&GPIOA->BSRR,
    			        16);
        /* Код після завершення передачі */
    	//DMA_Start();
    }
}

// привязуємо переривання DMA по кінцю передачі буфера до
// юзерної фунеції яка буде обробляти переривання(сам факт)
void DMA_UserInit(){

	// Привязуємо користувацьку функцію до колбека переривання DMA
	hdma_tim1_up.XferCpltCallback = DMA_TransferComplete; // gpt help init interapt

	// Дозводяємо таймеру генерувати DMA запити
	__HAL_TIM_ENABLE_DMA(&htim1, TIM_DMA_UPDATE);
}


void DMA_Update(void){

}




void DMA_Work(void){

	// Затримка для зменшення передаваємої інформації в термінал
	//HAL_Delay(100); // test holding to visualisenshion send data and changed DMA

	//test module
	//char DMA_remain_Ch[32]; // cтворюжмо промідний буфер
	//	uint32_t remain = __HAL_DMA_GET_COUNTER(&hdma_tim1_up); //записуємо значення кількості передач які лишилось виконати ДМА 16-15-14-13-12-10 і т.д
	//sprintf(DMA_remain_Ch, "remain = %lu\r\n", remain); // перетворбжмо числове значення кількості передач та записужмо в буфер
	//	SendMessage(DMA_remain_Ch); // надсиоажмо


		/// main code for DMA runtime




}





/*
 *
 *
 Тоді архітектура в тебе вже практично визначена, і вона дуже хороша.

Тобі підійде саме така схема:

+-------------------+
| DMA Frame Queue   |
+-------------------+
| Buffer1 | 100 kHz |
| Buffer2 | 500 kHz |
| Buffer3 | 50 kHz  |
| Buffer4 | 1 MHz   |
+-------------------+

        |
        V

+-------------------+
| DMA Complete IRQ  |
+-------------------+
        |
        V

1. Взяти наступний кадр
2. Завантажити PSC
3. Завантажити ARR
4. Запустити DMA
5. Запустити TIM1

Наприклад:

typedef struct
{
    uint32_t *Buffer;
    uint16_t Length;

    uint16_t PSC;
    uint16_t ARR;

} DMA_Frame_t;

Масив кадрів:

DMA_Frame_t Frames[4] =
{
    {Buffer1, 16, 0, 999},   // 100 кГц
    {Buffer2, 32, 0, 199},   // 500 кГц
    {Buffer3, 24, 3, 999},   // 50 кГц
    {Buffer4, 64, 0, 99}     // 1 МГц
};

Поточний індекс:

volatile uint8_t CurrentFrame = 0;

Callback:

void DMA_TransferComplete(DMA_HandleTypeDef *hdma)
{
    if(hdma != &hdma_tim1_up)
        return;

    CurrentFrame++;

    if(CurrentFrame >= 4)
        CurrentFrame = 0;

    DMA_Frame_t *frame = &Frames[CurrentFrame];

    //Оновлюємо параметри таймера
    HAL_TIM_Base_Stop(&htim1);

	TIM1->PSC = frame->PSC;
	TIM1->ARR = frame->ARR;
	TIM1->CNT = 0;              // бажано
	TIM1->EGR = TIM_EGR_UG;

HAL_TIM_Base_Start(&htim1);
    // Запускаємо наступний буфер
    HAL_DMA_Start_IT(
            &hdma_tim1_up,
            (uint32_t)frame->Buffer,
            (uint32_t)&GPIOA->BSRR,
            frame->Length);
}
При зміні форми сигналу

Ти правильно плануєш:

Користувач змінив форму сигналу
        ↓
Зупинити DMA
        ↓
Зупинити TIM1
        ↓
Перерахувати всі буфери
        ↓
Перерахувати PSC/ARR
        ↓
Скинути CurrentFrame = 0
        ↓
Запустити передачу знову

Наприклад:

void Signal_Rebuild(void)
{
    DMA_Stop();

    BuildBuffer1();
    BuildBuffer2();
    BuildBuffer3();
    BuildBuffer4();

    CurrentFrame = 0;

    DMA_StartFrame(&Frames[0]);
}
Переваги цієї архітектури
дуже проста в налагодженні;
можна мати довільну кількість буферів;
кожен буфер може мати власну довжину;
кожен буфер може мати власну частоту;
легко додати пріоритети, повтори або нескінченні цикли;
затримка між буферами буде мінімальною (кілька сотень наносекунд + затримка на вхід/вихід з IRQ).

Для генератора цифрових протоколів, який ти зараз розробляєш через GPIO->BSRR, це дуже хороше рішення.
 */


