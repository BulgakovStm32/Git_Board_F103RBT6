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
//#define DWT_CONTROL *(volatile unsigned long *)0xE0001000
//#define SCB_DEMCR   *(volatile unsigned long *)0xE000EDFC

#define SYS_CORE_CLOCK     72000000
#define TACTS_FOR_MICROSEC (SYS_CORE_CLOCK/1000000)

//**********************************************************
void microDelay_Init(void){

	CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk; // разрешаем использовать счётчик
	DWT->CTRL        |= DWT_CTRL_CYCCNTENA_Msk;     // запускаем счётчик

	//SCB_DEMCR |= CoreDebug_DEMCR_TRCENA_Msk; // разрешаем использовать счётчик
	//DWT_CONTROL |= DWT_CTRL_CYCCNTENA_Msk;   // запускаем счётчик
}
//**********************************************************
void microDelay(uint32_t us){

    uint32_t us_count_tic = us * TACTS_FOR_MICROSEC;// получаем кол-во тактов за 1 мкс и умножаем на наше значение
    DWT->CYCCNT = 0U; // обнуляем счётчик
    while(DWT->CYCCNT < us_count_tic);
}
//*******************************************************************************************
//*******************************************************************************************
