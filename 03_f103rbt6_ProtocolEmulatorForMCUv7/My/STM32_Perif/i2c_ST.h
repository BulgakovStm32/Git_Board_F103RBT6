/*
 * i2c_ST.h
 *
 *  Created on: 20 дек. 2020 г.
 *      Author: Zver
 */

#ifndef I2C_ST_H
#define I2C_ST_H
//*******************************************************************************************
//*******************************************************************************************

#include "main.h"

//*******************************************************************************************
//*******************************************************************************************
#define APB1_CLK			36000000U 				//Частота шины APB1 в Гц
#define I2C_FREQ	    	(APB1_CLK / 1000000U)	//Peripheral clock frequency (MHz)

//Sm mode or SMBus:
//TPCLK1 = 27,7777 ns
//CCR    = 1000nS/ (2 * TPCLK1)
//TRISE  = (1000nS/TPCLK1)
#define I2C_SM_CCR			180 //(10000U / (2 * TPCLK1))
#define I2C_SM_TRISE		36  //(1000U  / TPCLK1)

//Fm mode:
//TPCLK1 = 27,7777 ns
//CCR    = 2500nS/ (3 * TPCLK1)
//TRISE  = (300nS/TPCLK1)
#define I2C_FM_CCR			30 //(2500U / (3 * TPCLK1))
#define I2C_FM_TRISE		12 //(300U  / TPCLK1)
//--------------------------
#define I2C_WAIT_TIMEOUT	5000U
//--------------------------
#define I2C_MODE_READ  		1
#define I2C_MODE_WRITE 		0
#define I2C_ADDRESS(addr, mode) ((addr<<1) | mode)
//--------------------------
#define I2C_GPIO_NOREMAP	0
#define I2C_GPIO_REMAP		1

#define I2C_MODE_MASTER		0
#define I2C_MODE_SLAVE		1
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
typedef enum{
	I2C_DMA_READY = 0,	//I2C и DMA готовы к передаче данных.
	I2C_DMA_NOT_INIT,	//I2C и DMA не инициализированны.
	I2C_DMA_NAC,		//Slave не ответил на свой адрес.
	I2C_DMA_BUSY,		//I2C и DMA заняты, идет передача/прием данных.
	I2C_DMA_ERR			//Ошибка DMA.
}I2C_DMA_State_t;
//*******************************************************************************************
//*******************************************************************************************
//Общие функции.
I2C_State_t I2C_StartAndSendDeviceAddr(I2C_TypeDef *i2c, uint8_t deviceAddr);
I2C_State_t I2C_SendByte(I2C_TypeDef *i2c, uint8_t byte);
I2C_State_t I2C_ReadData(I2C_TypeDef *i2c, uint8_t *pBuf, uint32_t len);
I2C_State_t I2C_Stop(I2C_TypeDef *i2c);

I2C_State_t I2C_SendDataWithoutStop(I2C_TypeDef *i2c, uint8_t *pBuf, uint32_t len);
I2C_State_t I2C_SendData(I2C_TypeDef *i2c, uint8_t *pBuf, uint32_t len);
//************************************
//Функции для работы в режиме Master
void 		I2C_Master_Init(I2C_TypeDef *i2c, uint32_t remap);
uint32_t 	I2C_Master_GetNacCount(I2C_TypeDef *i2c);

I2C_State_t I2C_Master_Write(I2C_TypeDef *i2c, uint8_t deviceAddr, uint8_t regAddr, uint8_t *pBuf, uint32_t len);
I2C_State_t I2C_Master_Read (I2C_TypeDef *i2c, uint8_t deviceAddr, uint8_t regAddr, uint8_t *pBuf, uint32_t len);

//************************************
//Функции для работы в режиме Slave
void I2C_Slave_Init(I2C_TypeDef *i2c, uint32_t remap, uint32_t slaveAddr);

//*******************************************************************************************
//*******************************************************************************************
//Работа по прерываниям.
#define I2C_IT_RX_BUF_LEN_MAX	32
#define I2C_IT_TX_BUF_LEN_MAX	32

//****************************************************
//Структура контекста для работы с портом I2C по прерываниям.
//#pragma pack(push, 1)//размер выравнивания в 1 байт
typedef struct{
	I2C_TypeDef *i2c;
	uint32_t 	i2cMode;		// Master или Slave
	uint32_t 	i2cGpioRemap;	// Ремап выводов для I2C1, для I2C2 ремапа нет.
	uint32_t 	i2cItState;		//
	uint32_t 	i2cDmaState;	//

	uint32_t 	slaveAddr;		// В режиме Master - адрес Slave-устройства к которому идет обращение,
								// в режиме Slave  - адрес устройста на шине.

	uint32_t 	slaveRegAddr;	// В режиме Master - адрес регистра Slave-устройства куда хотим писать/читать данные.
								// в режиме Slave  - ???

	//uint8_t 	*pTxBuf;		// указатель на буфер передачи.
	uint8_t 	pTxBuf[I2C_IT_TX_BUF_LEN_MAX]; // буфер передачи.
	uint32_t 	txBufSize;		// размер буфера передачи
	uint32_t	txBufIndex;		// индекс буфера передачи.

	//uint8_t 	*pRxBuf;		// указатель на буфер приема.
	uint8_t 	pRxBuf[I2C_IT_RX_BUF_LEN_MAX]; // буфер приема.
	uint32_t 	rxBufSize;		// размер буфера приема.
	uint32_t	rxBufIndex;		// индекс буфера приема.

	void(*i2cRxCallback)(void); //
	void(*i2cTxCallback)(void); //

}I2C_IT_t;
//#pragma pack(pop)//вернули предыдущую настройку.
//*******************************************************************************************
void 	 I2C_IT_Init(I2C_IT_t *i2c);

uint8_t* I2C_IT_GetpTxBuf(I2C_IT_t *i2cIt);
void 	 I2C_IT_SetTxSize(I2C_IT_t *i2cIt, uint32_t size);
void     I2C_IT_NoStretch(I2C_IT_t *i2cIt);

uint8_t* I2C_IT_GetpRxBuf(I2C_IT_t *i2cIt);

//Обработчики прерывания
void I2C_IT_EV_Handler(I2C_TypeDef *i2c);
void I2C_IT_ER_Handler(I2C_TypeDef *i2c);
//*******************************************************************************************
//*******************************************************************************************
//Работа чере DMA.
#define I2C1_DMA_TX_CHANNEL	DMA1_Channel6
#define I2C1_DMA_RX_CHANNEL	DMA1_Channel7

#define I2C2_DMA_TX_CHANNEL	DMA1_Channel4
#define I2C2_DMA_RX_CHANNEL	DMA1_Channel5

//*******************************************************************************************
void 	 I2C_DMA_Init(I2C_IT_t *i2cIt);
uint32_t I2C_DMA_GetState(I2C_IT_t *i2cIt);
uint32_t I2C_DMA_Write(I2C_IT_t *i2cIt);
uint32_t I2C_DMA_Read (I2C_IT_t *i2cIt);

//Обработчики прерывания
void I2C1_DMA_IT_TX_Handler(void);
void I2C1_DMA_IT_RX_Handler(void);
//*******************************************************************************************
//*******************************************************************************************
#endif /* I2C_ST_H_ */






















