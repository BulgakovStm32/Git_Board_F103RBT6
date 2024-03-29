
#include "Lcd_TIC32.h"
//*******************************************************************************************
//*******************************************************************************************
//Тестовая картинка.
const unsigned char qweqwe[512] = {
 0 , 16 , 16 , 16 ,240 , 16 , 16 , 0 , 0 ,240
 , 0 , 0 ,240 , 16 , 16 , 16 , 16 , 0 , 0 , 16
 , 16 , 16 , 16 ,224 , 0 , 0 , 32 , 16 , 16 , 16
 ,224 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0
 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0
 , 0 ,254 ,254 ,254 , 14 , 14 , 14 , 14 , 14 , 14
 ,142 ,142 ,142 ,254 ,254 ,254 , 64 , 64 , 32 , 32
 , 32 , 32 , 32 , 32 , 32 , 32 , 32 , 16 , 16 ,144
 ,144 ,144 ,144 , 80 , 80 , 80 , 48 , 48 , 48 , 16
 , 16 , 16 , 16 , 24 , 24 , 24 , 20 , 20 , 20 , 20
 , 18 , 18 , 28 , 16 , 48 ,208 , 32 , 32 , 32 , 32
 , 32 , 32 , 32 , 32 , 32 , 64 , 64 , 64 , 64 , 64
 ,128 ,128 ,128 , 0 , 0 , 0 , 0 , 0 , 0 , 0
 , 0 , 0 , 63 , 0 , 0 , 0 , 0 , 63 , 0 , 0
 , 31 , 32 , 32 , 32 , 32 , 0 , 0 , 32 , 33 , 33
 , 33 , 30 , 0 , 0 , 32 , 56 , 38 , 35 , 32 , 0
 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0
 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,255
 ,255 ,255 ,224 ,224 ,224 ,224 ,226 ,229 ,232 ,232
 ,232 ,255 ,255 ,255 , 16 , 16 , 32 , 32 , 32 , 32
 , 32 , 32 , 32 , 32 , 32 , 67 , 67 , 66 , 68 , 68
 , 68 , 68 , 72 , 72 , 72 , 72 , 80 , 80 , 80 , 80
 , 96 , 96 , 96 , 96 , 64 , 64 , 64 , 64 ,192 ,192
 ,192 ,192 , 64 , 64 , 33 , 38 , 40 , 48 , 96 ,160
 , 32 , 32 , 32 , 16 , 16 , 16 , 16 , 16 , 8 , 8
 , 8 , 5 , 2 , 0 , 0 , 0 , 0 , 0 , 0 ,128
 ,252 , 4 , 4 ,252 , 0 , 0 , 0 ,224 , 32 , 32
 , 32 ,224 , 0 , 0 ,192 , 32 , 32 , 32 ,224 , 0
 , 0 ,224 , 4 , 4 , 4 ,224 , 0 , 0 ,252 , 36
 , 52 , 40 ,224 , 0 , 0 ,192 , 32 , 32 , 32 ,224
 , 0 , 0 ,224 , 32 , 32 , 32 ,224 , 0 , 0 , 0
 , 0 , 0 , 0 , 0 , 0 ,252 ,132 ,132 ,132 ,132
 ,124 , 0 , 0 ,252 , 4 , 4 , 4 , 4 , 0 , 0
 ,252 , 68 , 68 , 68 , 68 , 0 , 0 ,128 ,252 , 68
 , 68 ,108 ,152 , 0 , 0 ,124 , 68 , 68 , 68 ,132
 , 0 , 0 , 4 , 68 , 68 , 68 ,184 , 0 , 0 , 16
 , 9 ,253 , 1 , 1 , 2 , 2 , 2 , 2 , 7 , 4
 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0
 , 0 , 0 , 0 , 0 , 0 , 0 , 24 , 15 , 8 , 8
 , 8 , 15 , 24 , 0 , 0 ,127 , 8 , 8 , 8 , 7
 , 0 , 0 , 7 , 8 , 8 , 8 , 7 , 8 , 0 , 7
 , 8 , 8 , 8 , 15 , 0 , 0 , 7 , 8 , 8 , 8
 , 7 , 0 , 0 , 7 , 9 , 9 , 9 , 9 , 0 , 0
 ,127 , 8 , 8 , 8 , 7 , 0 , 0 , 0 , 0 , 0
 , 0 , 0 , 0 , 15 , 0 , 0 , 0 , 0 , 0 , 0
 , 0 , 7 , 8 , 8 , 8 , 8 , 0 , 0 , 15 , 0
 , 0 , 0 , 0 , 0 , 0 , 7 , 12 , 8 , 8 , 12
 , 7 , 0 , 0 , 8 , 8 , 8 , 8 , 7 , 0 , 0
 , 8 , 8 , 8 , 8 , 7 , 0 , 0 , 0 , 0 , 15
 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0
 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0
 , 0 , 0
 };
//*************************************
static uint8_t Tic32Buf[2] = {0};
static uint8_t *pic;
//*******************************************************************************************
//*******************************************************************************************
//Инициализация PCF8531
void Lcd_TIC32_Init(void){

	I2C_Init(LCD_TIC32_I2C, 0);
	//-------------------------
	I2C_StartAndSendDeviceAddr(LCD_TIC32_I2C, LCD_TIC32_ADDR);
	//на основн стр
	Tic32Buf[0] = LCD_TIC32_CON1;
	Tic32Buf[1] = 0x01;
	I2C_SendData(LCD_TIC32_I2C, Tic32Buf, 2);
	//Enable chip, горизонтальная
	Tic32Buf[0] = LCD_TIC32_CON1;
	Tic32Buf[1] = 0b00100000;
	I2C_SendData(LCD_TIC32_I2C, Tic32Buf, 2);
	//page select
	Tic32Buf[0] = LCD_TIC32_CON1;
	Tic32Buf[1] = 0b00001001;
	I2C_SendData(LCD_TIC32_I2C, Tic32Buf, 2);
	//Display Mode: NORMAL
	Tic32Buf[0] = LCD_TIC32_CON1;
	Tic32Buf[1] = 0b00001100;
	I2C_SendData(LCD_TIC32_I2C, Tic32Buf, 2);
	//MUX-rate: 1/34
	Tic32Buf[0] = LCD_TIC32_CON1;
	Tic32Buf[1] = 0b00000101;
	I2C_SendData(LCD_TIC32_I2C, Tic32Buf, 2);
	//Bias system: 3
	Tic32Buf[0] = LCD_TIC32_CON1;
	Tic32Buf[1] = 0b00010100;
	I2C_SendData(LCD_TIC32_I2C, Tic32Buf, 2);
	// на основн стр
	Tic32Buf[0] = LCD_TIC32_CON1;
	Tic32Buf[1] = 0x01;
	I2C_SendData(LCD_TIC32_I2C, Tic32Buf, 2);
	// page select
	Tic32Buf[0] = LCD_TIC32_CON1;
	Tic32Buf[1] = 0b00001010;
	I2C_SendData(LCD_TIC32_I2C, Tic32Buf, 2);
	// voltage multiplication factor: 2*V
	Tic32Buf[0] = LCD_TIC32_CON1;
	Tic32Buf[1] = 0b00001011;
	I2C_SendData(LCD_TIC32_I2C, Tic32Buf, 2);
	// temperature coefficient: 0
	Tic32Buf[0] = LCD_TIC32_CON1;
	Tic32Buf[1] = 0b00100000;
	I2C_SendData(LCD_TIC32_I2C, Tic32Buf, 2);

	//Остановиться имеет смысл пожалуй лишь на напряжении Vlcd.
	//Если установить слишком малое напряжение – пиксели будут плохо видны.
	//Если же превысить нужное – будет заметна засветка лишних пикселей,
	//которые должны быть неактивны.
	//Поэтому важно подобрать оптимальное значение для конкретного индикатора
	//и конкретной схемы.

	// Vlcd - LOW; Voltage multiplier ON
	Tic32Buf[0] = LCD_TIC32_CON1;
	Tic32Buf[1] = 0b00000101;
	I2C_SendData(LCD_TIC32_I2C, Tic32Buf, 2);
	// Vlcd set
	Tic32Buf[0] = LCD_TIC32_CON1;
	Tic32Buf[1] = (1 << 7) | LCD_TIC32_Vlcd;
	I2C_SendData(LCD_TIC32_I2C, Tic32Buf, 2);

	I2C_Stop(LCD_TIC32_I2C);
}
//************************************************************
//Очистка ОЗУ драйвера
void Lcd_TIC32_ClearRAM(void){

	I2C_StartAndSendDeviceAddr(LCD_TIC32_I2C, LCD_TIC32_ADDR);

	Tic32Buf[0] = LCD_TIC32_CON2;
	I2C_SendData(LCD_TIC32_I2C, Tic32Buf, 1);

	for(uint16_t cnt = 0; cnt < 640; cnt++)
		{
			Tic32Buf[0] = 0;
			I2C_SendData(LCD_TIC32_I2C, Tic32Buf, 1);
		}

	I2C_Stop(LCD_TIC32_I2C);
}
//************************************************************
//Вывод буфера на дисплей.
void Lcd_TIC32_SendData(uint8_t *pBuf){

	 I2C_StartAndSendDeviceAddr(LCD_TIC32_I2C, LCD_TIC32_ADDR);
	// на основн стр
	Tic32Buf[0] = LCD_TIC32_CON1;
	Tic32Buf[1] = 0x01;
	I2C_SendData(LCD_TIC32_I2C, Tic32Buf, 2);
	// set Y-адрес
	Tic32Buf[0] = LCD_TIC32_CON1;
	Tic32Buf[1] = 0b01000000;
	I2C_SendData(LCD_TIC32_I2C, Tic32Buf, 2);
	// set X-адрес
	Tic32Buf[0] = LCD_TIC32_CON1;
	Tic32Buf[1] = 0b10000000;
	I2C_SendData(LCD_TIC32_I2C, Tic32Buf, 2);

	I2C_Stop(LCD_TIC32_I2C);
	//------------------
	I2C_StartAndSendDeviceAddr(LCD_TIC32_I2C, LCD_TIC32_ADDR);

	Tic32Buf[0] = LCD_TIC32_CON2;
	I2C_SendData(LCD_TIC32_I2C, Tic32Buf, 1);

	for(uint16_t cnt = 0; cnt < 640; cnt++)
		{
			if (cnt < 512)
				{
					I2C_SendData(LCD_TIC32_I2C, (pBuf + cnt), 1);
				}
			else
				{
					Tic32Buf[0] = 0;
					I2C_SendData(LCD_TIC32_I2C, Tic32Buf, 1);
				}
		}
	I2C_Stop(LCD_TIC32_I2C);
}
//************************************************************

//*******************************************************************************************
//*******************************************************************************************
