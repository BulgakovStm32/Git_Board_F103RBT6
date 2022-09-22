/*
 * Delay.c
 *
 *  Created on: 20 дек. 2020 г.
 *      Author: Zver
 */
//*******************************************************************************************
//*******************************************************************************************

#include "Delay.h"

//*******************************************************************************************
static volatile uint32_t msCounter = 0;
//*******************************************************************************************
//*******************************************************************************************
void msDelay_Loop(void){

	msCounter++;
}
//**********************************************************
void msDelay(volatile uint32_t del){

	msCounter = 0;
	while(msCounter < del){__NOP();};
}
//*******************************************************************************************
//*******************************************************************************************
//Микросекундная задержка.
#define SYS_CORE_CLOCK     72000000U//72000000U //71MHz - такое число дает более точный результат.
#define TACTS_FOR_MICROSEC (SYS_CORE_CLOCK/1000000U)

//**********************************************************
void MICRO_DELAY_Init(void){

	CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk; // разрешаем использовать счётчик
	DWT->CYCCNT       = 0;						    // сброс счетчика
	DWT->CTRL        |= DWT_CTRL_CYCCNTENA_Msk;     // запускаем счётчик
}
//**********************************************************
//Максимальная задержка 55 секунд.
uint32_t MICRO_DELAY_GetCount(void){

	uint32_t temp = DWT->CYCCNT + TACTS_FOR_MICROSEC/2;
	return (temp / TACTS_FOR_MICROSEC);
}
//**********************************************************
//Максимальная задержка 55 секунд.
void MICRO_DELAY(uint32_t microSec){

	//Выриант 1.
	if(microSec != 0) microSec = microSec - 1;
    volatile uint32_t uS_count_tic = microSec * TACTS_FOR_MICROSEC;// получаем кол-во тактов за 1 мкс и умножаем на наше значение
    DWT->CYCCNT = 0U; // обнуляем счётчик
    while(DWT->CYCCNT < uS_count_tic);

	//Выриант 2.
//    uint32_t old = MICRO_DELAY_GetCount();
//    while((MICRO_DELAY_GetCount() - old) < microSec);

	//Выриант 3.
//	uint32_t old  = MICRO_DELAY_GetCount();
//	uint32_t temp = 0;
//	uint32_t diff = 0;
//	//---------------------
////	do
////	{
////		temp = MICRO_DELAY_GetCount();
////		if(temp >= old) diff = temp - old;
////		else
////		{
////			old  = diff;
////			diff = diff - 1;
////		}
////	}
////	while(diff < microSec);
//
//	while(diff < microSec)
//	{
//		temp = MICRO_DELAY_GetCount();
//		if(temp >= old) diff = temp - old;
//		else
//		{
//			old  = diff;
//			diff = diff - 1;
//		}
//	}
}
//*******************************************************************************************
//*******************************************************************************************





















