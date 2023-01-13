/*
 * GpioMCU.h
 *
 *  Created on: 11 янв. 2023 г.
 *      Author: belyaev
 */

#ifndef MCUV7_GPIOMCU_H_
#define MCUV7_GPIOMCU_H_
//*******************************************************************************************
//*******************************************************************************************

#include "main.h"

//*******************************************************************************************
//*******************************************************************************************
//PC13 - Led.
#define LED_PC13_GPIO			GPIOC
#define LED_PC13_PIN			13
#define LED_PC13_On()			GPIO_PIN_Low(LED_PC13_GPIO, LED_PC13_PIN)
#define LED_PC13_Off()			GPIO_PIN_High(LED_PC13_GPIO, LED_PC13_PIN)
#define LED_PC13_Toggle()		GPIO_PIN_Toggel(LED_PC13_GPIO, LED_PC13_PIN)

//Имитация гапряжения питания БигБорда - PB14
#define BIG_BOARD_PWR_GPIO		GPIOB
#define BIG_BOARD_PWR_PIN		0
#define BIG_BOARD_PWR_On()     	GPIO_PIN_High(BIG_BOARD_PWR_GPIO, BIG_BOARD_PWR_PIN)
#define BIG_BOARD_PWR_Off()    	GPIO_PIN_Low(BIG_BOARD_PWR_GPIO, BIG_BOARD_PWR_PIN)
#define BIG_BOARD_PWR_Toggle() 	GPIO_PIN_Toggel(BIG_BOARD_PWR_GPIO, BIG_BOARD_PWR_PIN)

//*******************************************************************************************
//*******************************************************************************************
void GPIO_MCU_Init(void);

//*******************************************************************************************
//*******************************************************************************************
#endif /* MCUV7_GPIOMCU_H_ */













