/*
 * spi_ST.h
 *
 *  Created on: 1 марта 2022 г.
 *      Author: Zver
 */
#ifndef _spi_ST_H
#define _spi_ST_H
//*******************************************************************************************
//*******************************************************************************************

#include "main.h"

//*******************************************************************************************
#define SPI_INIT	(1<<0) //SPI проинициализирован.

#define SPI_RX_ONLY_MODE 0 //Output disabled (receive-only mode)
#define SPI_TX_ONLY_MODE 1 //Output enabled  (transmit-only mode)

#define SPI_WAIT ((uint32_t)0x5000)
//*******************************************************************************************
//*******************************************************************************************
void 	SPI_Init(SPI_TypeDef *spi);
void 	SPI_Enable(SPI_TypeDef *spi);
void 	SPI_Disable(SPI_TypeDef *spi);
void    SPI_BiDirMode(SPI_TypeDef *spi, uint8_t mode);

uint8_t SPI_RxByte(SPI_TypeDef *spi);
void    SPI_TxByte(SPI_TypeDef *spi, uint8_t byte);
uint8_t	SPI_TxRxByte(SPI_TypeDef *spi, uint8_t byte);


//void     Spi1Init(void);
//uint8_t	 Spi1TxRxByte(uint8_t byte);
//
//void     Spi2Init    (void);
//uint8_t  Spi2GetStat (void);
//uint16_t Spi2SendData(uint16_t data);
//uint8_t  Spi2TxRxByte(uint8_t byte);
//*******************************************************************************************
//*******************************************************************************************
#endif /*_spi_ST_H*/


