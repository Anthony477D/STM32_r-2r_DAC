
#include "UserUI.h"
#include "DMA_process.h"

#include "main.h"

#include <stdio.h>
#include "main.h"

#include "TestGenerate.h"


extern DMA_HandleTypeDef hdma_tim1_up;


char mess_test_1[] = "helloWorld\n";



void AppInit(void){
	UserUI_Init();
	//DMA_Start();
	//DMA_UserInit();
	// create uart messege to nonstop

	HAL_Delay(5000);
}
void AppRuntime(void){
	// read uart data from PC
	//StarComunication();

	//DMA_Start();
	//DMA_Work();
	TriangleGenUp();

}
