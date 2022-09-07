/*
 * RingBuffer.h
 *
 *  Created on: 22 апр. 2022 г.
 *      Author: Zver
 */

#ifndef RINGBUFFER_H_
#define RINGBUFFER_H_
//*******************************************************************************************
//*******************************************************************************************

#include "main.h"

//*******************************************************************************************
//*******************************************************************************************

//**********************************
//Состояние кнопки энкодера.
//#pragma pack(push, 1)
//typedef struct{
//	uint32_t Released	:1;
//	uint32_t Press		:1;
//	uint32_t LongPress	:1;
//
////	BUTTON_RELEASED = 0,
////	BUTTON_PRESS,
////	BUTTON_LONG_PRESS,
//
//}EncoderButtonState_t;
//#pragma pack(pop)
//**********************************
//размер буфера обязательно должен быть равен степени двойки!
#define RING_RX_BUFFER_SIZE 128 //размер приёмного буфера
#define RING_RX_BUFFER_MASK (RING_RX_BUFFER_SIZE-1)

#define RING_TX_BUFFER_SIZE 128 //размер передающего буфера
#define RING_TX_BUFFER_MASK (RING_TX_BUFFER_SIZE-1)
//**********************************
typedef struct{
	volatile uint32_t rx_buffer_head;
	volatile uint32_t rx_buffer_tail;
			 uint8_t  rx_buffer[RING_RX_BUFFER_SIZE];
}RingRxBuffer_t;
//*******************************************************************************************
//*******************************************************************************************

uint16_t uart_available(void);
uint8_t  uart_read(void);
void 	 clear_uart_buff();
//*******************************************************************************************
//*******************************************************************************************
#endif /* RINGBUFFER_H_ */



