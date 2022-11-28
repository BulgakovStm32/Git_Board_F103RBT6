
/*
 * LM6063D.c
 *
 *  Created on:
 *      Author:
 */
#include "LM6063D.h"
//*******************************************************************************************
//*******************************************************************************************



//*******************************************************************************************
//*******************************************************************************************
//*******************************************************************************************
//*******************************************************************************************
static void Lm6063LcdPause(uint16_t pause){

  while(pause != 0) {--pause;}
}
//**********************************************************
static void _lcd_lm6063_GpioInit(void){
  
	//Включаем тактирование порта
	RCC->APB2ENR |= (RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPBEN);
	//--------------------
	// A1   - PB10.
	// /RES - PB12.
	// /CS  - PB11.
	//выход, режим - push-pull.
	GPIOB->CRH &= ~(GPIO_CRH_CNF10 |
					GPIO_CRH_CNF11 |
					GPIO_CRH_CNF12 );
	//тактирование 50МГц.
	GPIOB->CRH |= (GPIO_CRH_MODE10 |
                   GPIO_CRH_MODE11 |
                   GPIO_CRH_MODE12 );

	Lm6063LcdResHight();
	Lm6063LcdCsHight();
}	
//**********************************************************
//Передача байта в дисплей..
static void _lcd_lm6063_SendByte(uint8_t byte, uint8_t cmd){

//	Lm6063LcdCsLow();   //Enable display controller (active low)
//	Lm6063LcdPause(50); //Пауза что бы дисплей успел перейти в активный режим

	if(cmd == LM6063_DATA) Lm6063LcdA1Hight();//данные.
	else    			   Lm6063LcdA1Low();  //команда.
	SPI_TxByte(LM6063_SPI, byte);

//	Lm6063LcdCsHight(); //Disable display controller
}
//*******************************************************************************************
//*******************************************************************************************
//*******************************************************************************************
//*******************************************************************************************
//инициализация SPI и дисплея
void LCD_LM6063_Init(void){
  
	SPI_Init(LM6063_SPI);
	_lcd_lm6063_GpioInit();
	//--------------------
	//Сброс дисплея.
	Lm6063LcdResLow();
	Lm6063LcdPause(50);
	Lm6063LcdResHight();
	Lm6063LcdPause(50);


	//Enable display controller (active low)
	Lm6063LcdCsLow();
	//--------------------
	//
	_lcd_lm6063_SendByte(0xaf, LM6063_CMD);	//Display OFF
	_lcd_lm6063_SendByte(0x40, LM6063_CMD);
	//--------------------
	//ADC select
	//Sets the display RAM address SEG output correspondence
	_lcd_lm6063_SendByte(0xa0, LM6063_CMD);//normal
	//Lm6063LcdSendByte(0xa1, LM6063_CMD);//reverse 
	//--------------------
	//
	_lcd_lm6063_SendByte(0xa6, LM6063_CMD);
	_lcd_lm6063_SendByte(0xa4, LM6063_CMD);
	_lcd_lm6063_SendByte(0xa2, LM6063_CMD);
	
	//--------------------
	//Common Output Mode Select
	//Lm6063LcdSendByte(0xc0, LM6063_CMD);//Normal
	_lcd_lm6063_SendByte(0xc8, LM6063_CMD);//Reverse
	//--------------------
	//
	_lcd_lm6063_SendByte(0x2f, LM6063_CMD);
	_lcd_lm6063_SendByte(0x25, LM6063_CMD);
	_lcd_lm6063_SendByte(0xf8, LM6063_CMD);
	
	_lcd_lm6063_SendByte(0x00, LM6063_CMD);
	//_lcd_lm6063_SendByte(0x01, LM6063_CMD);
	//--------------------
	//Контрастность - Electronic volume mode set
	_lcd_lm6063_SendByte(0x81, LM6063_CMD);//Команда
	_lcd_lm6063_SendByte(0x22, LM6063_CMD);//Значение
	
	//--------------------	
	_lcd_lm6063_SendByte(0xaf, LM6063_CMD);


	//Disable display controller
	Lm6063LcdCsHight();
}
//**********************************************************
//Copies the LCD cache into the device RAM
void LCD_LM6063_Update(uint8_t *displayBuf){
  
//  uint8_t  i, j;
//  //--------------------
//	Lm6063LcdSendByte(0x40, LM6063_CMD);	//Set Display Start Line = com0
//	for(i = 0; i < 8; i++)
//    {
//      Lm6063LcdSendByte(0xB0|i, LM6063_CMD); //Set Page Address as ComTable
//      Lm6063LcdSendByte(0x10,   LM6063_CMD); //Set Column Address = 0
//      Lm6063LcdSendByte(0x04,   LM6063_CMD); //Colum from 4 -> 132 auto add
//      for(j = 0; j < 128; j++)
//        {
//          Lm6063LcdSendByte(*(displayBuf++), LM6063_DATA);
//        }
//    }


	//Передача данных для дисплея, за раз передается 128 байта(~1.5мС)
	static uint32_t count    = 0;
	static uint32_t bufIndex = 0;
	//--------------------
	Lm6063LcdCsLow(); //Enable display controller (active low)

	if(count == 0) _lcd_lm6063_SendByte(0x40, LM6063_CMD);//Set Display Start Line = com0
	_lcd_lm6063_SendByte(0xB0|count, LM6063_CMD); 		  //Set Page Address as ComTable
	_lcd_lm6063_SendByte(0x10	   , LM6063_CMD); 		  //Set Column Address = 0
	_lcd_lm6063_SendByte(0x04      , LM6063_CMD); 		  //Colum from 4 -> 132 auto add
	for(uint32_t i = 0; i < 128; i++)
	{
		_lcd_lm6063_SendByte(*(displayBuf + bufIndex), LM6063_DATA);
		bufIndex++;
	}

	if(++count >= 8)
	{
		count    = 0;
		bufIndex = 0;
	}

	Lm6063LcdCsHight(); //Disable display controller
}
//*******************************************************************************************
//*******************************************************************************************
//*******************************************************************************************
//*******************************************************************************************



















