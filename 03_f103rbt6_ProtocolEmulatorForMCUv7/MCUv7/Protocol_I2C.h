/*
 * Protocol_I2C.h
 *
 *  Created on: 22 авг. 2022 г.
 *      Author: belyaev
 */
#ifndef MCUV7_PROTOCOL_I2C_H
#define MCUV7_PROTOCOL_I2C_H
//*******************************************************************************************
//*******************************************************************************************

#include "main.h"

//*******************************************************************************************
//*******************************************************************************************
//Структура буфера.




//****************************************************
//Структура запроса.
#pragma pack(push, 1)//размер выравнивания в 1 байт
typedef struct{
	uint8_t  CmdCode;    	// Код команды.
	uint8_t  Count;       	// Размер блока.
	uint8_t	 Payload[62];	// Данные
}MCU_Request_t;
#pragma pack(pop)//вернули предыдущую настройку.
//****************************************************
//Структура ответа.
#pragma pack(push, 1)//размер выравнивания в 1 байт
typedef struct{
	uint8_t  Count;       	// Размер блока.
	uint8_t  CmdCode;    	// Код команды.
	uint8_t	 Payload[62];	// Данные
}MCU_Response_t;
#pragma pack(pop)//вернули предыдущую настройку.
//*******************************************************************************************
//*******************************************************************************************




//*******************************************************************************************
//*******************************************************************************************
#endif /* MCUV7_PROTOCOL_I2C_H */


