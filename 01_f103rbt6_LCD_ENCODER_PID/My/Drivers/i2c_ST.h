/*
 * i2c_ST.h
 *
 *  Created on: 20 дек. 2020 г.
 *      Author: Zver
 */

#ifndef I2C_ST_H_
#define I2C_ST_H_
//*******************************************************************************************
//*******************************************************************************************

#include "main.h"

//*******************************************************************************************
#define APB1_CLK			36000000U//Частота шины APB1 в Гц
#define I2C_RISE_TIME_100kHz	1000U    //Фронт сигнала в нС для 100кГц
#define I2C_RISE_TIME_400kHz	300U     //Фронт сигнала в нС для 400кГц
#define I2C_RISE_TIME_1000kHz	120U     //Фронт сигнала в нС для 1000кГц

#define I2C_TRISE_100kHz    ???
#define I2C_TRISE_400kHz    ???
#define I2C_TRISE_1000kHz   ???

#define I2C_GPIO_NOREMAP	0
#define I2C_GPIO_REMAP		1

//#define I2C_CR2_VALUE   (APB1_CLK / 1000000)
//#define I2C_CCR_VALUE	((APB1_CLK / I2C_BAUD_RATE) / 2)
//#define I2C_TRISE_VALUE ((1 / (I2C_TRISE * (APB1_CLK / 1000000))) + 1)
#define I2C_WAIT_TIMEOUT	5000U
//--------------------------
#define I2C_MODE_READ  			1
#define I2C_MODE_WRITE 			0
#define I2C_ADDRESS(addr, mode) ((addr<<1) | mode)

//--------------------------
typedef enum{
	I2C_OK = 0,
	I2C_BUSY,		//Шина I2C занята (передача/прием данных)
	I2C_ERR_START,	//Ошибка при фоормировании Старт-последовательности
	I2C_ERR_ADDR,	//Ошибка адреса, Slave не отвечает.
	I2C_ERR_TX_BYTE,//Вышел таймаут передачи байта.
	I2C_ERR_RX_BYTE,//Вышел таймаут приема байта.
	I2C_ERR_BTF		//Вышел таймаут Byte transfer finished
}I2C_State_t;

//--------------------------

//*******************************************************************************************
//*******************************************************************************************
void I2C_Init(I2C_TypeDef *i2c, uint32_t remap);

I2C_State_t I2C_StartAndSendDeviceAddr(I2C_TypeDef *i2c, uint8_t DeviceAddr);
uint32_t 	I2C_GetNacCount(I2C_TypeDef *i2c);
I2C_State_t I2C_SendByte(I2C_TypeDef *i2c, uint8_t byte);
I2C_State_t I2C_SendData(I2C_TypeDef *i2c, uint8_t *pBuf, uint16_t len);
I2C_State_t I2C_ReadData(I2C_TypeDef *i2c, uint8_t *pBuf, uint16_t len);

I2C_State_t I2C_Write(I2C_TypeDef *i2c, uint8_t deviceAddr, uint8_t regAddr, uint8_t *pBuf, uint16_t len);
I2C_State_t I2C_Read (I2C_TypeDef *i2c, uint8_t deviceAddr, uint8_t regAddr, uint8_t *pBuf, uint16_t len);

//Работа по прерываниям.
void 	 I2C_IT_Init(I2C_TypeDef *i2c, uint32_t remap);
void 	 I2C_IT_StartTx(I2C_TypeDef *i2c, uint8_t deviceAddr, uint8_t regAddr, uint8_t *pBuf, uint32_t len);
void 	 I2C_IT_StartRx(I2C_TypeDef *i2c, uint8_t deviceAddr, uint8_t regAddr, uint8_t *pBuf, uint32_t len);

uint32_t I2C_IT_GetState(void);
uint32_t I2C_IT_GetData(I2C_TypeDef *i2c, uint8_t *pBuf, uint32_t len);

void I2C_IT_EV_Handler(I2C_TypeDef *i2c);//Обработчик прерывания событий I2C
void I2C_IT_ER_Handler(I2C_TypeDef *i2c);//Обработчик прерывания ошибок I2C
//*******************************************************************************************
//*******************************************************************************************
//Работа чере DMA.
#define I2C1_TX_DMAChannel	DMA1_Channel6
#define I2C1_RX_DMAChannel	DMA1_Channel7

#define I2C2_TX_DMAChannel	DMA1_Channel4
#define I2C2_RX_DMAChannel	DMA1_Channel5

typedef enum{
	I2C_DMA_READY = 0,	//I2C и DMA готовы к передаче данных.
	I2C_DMA_NOT_INIT,	//I2C и DMA не инициализированны.
	I2C_DMA_NAC,		//Slave не ответил на свой адрес.
	I2C_DMA_BUSY,		//I2C и DMA заняты, идет передача/прием данных.
	I2C_DMA_ERR			//Ошибка DMA.
}I2C_DMA_State_t;
//*******************************************************************************************
void 			I2C_DMA_Init(I2C_TypeDef *i2c, uint32_t remap);
I2C_DMA_State_t I2C_DMA_State(void);
I2C_DMA_State_t I2C_DMA_Write(I2C_TypeDef *i2c, uint8_t deviceAddr, uint8_t regAddr, uint8_t *pBuf, uint32_t size);
I2C_DMA_State_t I2C_DMA_Read (I2C_TypeDef *i2c, uint8_t deviceAddr, uint8_t *pBuf, uint32_t size);
//*******************************************************************************************
//*******************************************************************************************
#endif /* I2C_ST_H_ */
