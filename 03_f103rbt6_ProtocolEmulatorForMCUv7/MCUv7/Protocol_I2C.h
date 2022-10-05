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
#define MCUv7_I2C		I2C1
#define MCUv7_I2C_ADDR	(0x06<<1)

#define PROTOCOL_I2C_REQUEST_TIMEOUT_mS		1000	//

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
//****************************************************
//Структура данных от MCUv7
typedef struct{
	uint32_t EncoderVal;
	uint32_t SupplyVoltageVal;
	uint32_t msCount;
	uint32_t Sense;
	uint32_t I2cResetCount;
	uint32_t TemperatureSense1;
	uint32_t TemperatureSense2;
}MCUv7_Data_t;
//*******************************************************************************************
//*******************************************************************************************
void 	 PROTOCOL_MASTER_I2C_Init(void);
void 	 PROTOCOL_MASTER_I2C_RequestToMCU(void);
void 	 PROTOCOL_MASTER_I2C_SendCmdToMCU(MCU_Request_t *cmd);
uint32_t PROTOCOL_MASTER_I2C_GetI2cNacCount(void);
MCUv7_Data_t* PROTOCOL_MASTER_I2C_GetDataMCU(void);
uint32_t PROTOCOL_MASTER_I2C_DMAState(void);
void 	 PROTOCOL_MASTER_I2C_IncTimeoutAndReset(void);

//*******************************************************************************************
//*******************************************************************************************
#endif /* MCUV7_PROTOCOL_I2C_H */



