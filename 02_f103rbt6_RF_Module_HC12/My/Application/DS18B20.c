/*
 * ds18b20.c
 *
 *  Created on: 20 дек. 2020 г.
 *      Author: Zver
 */
#include "DS18B20.h"
//*******************************************************************************************
//*******************************************************************************************

//static uint32_t DELAY_WAIT_CONVERT = DELAY_T_CONVERT;

//*******************************************************************************************
//*******************************************************************************************
//Функция задержки в микросекундах.
__STATIC_INLINE void OneWire_usDelay(const uint32_t us){

	microDelay(us);

//	us *= 4;  //Эти цифры подобраны эмпирическим путем для Fclk=72MHz.
//	us += 4;
//	while(us--);
}
//**********************************************************
static void OneWire_GpioInit(const DS18B20_t *sensor){

	uint32_t pin = sensor->GPIO_PIN;
	//---------------------
	//Включение тактирования портов.
		 if(sensor->GPIO_PORT == GPIOA) RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	else if(sensor->GPIO_PORT == GPIOB) RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
	else if(sensor->GPIO_PORT == GPIOC) RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
	else return;
	//Конфигурация выводы в режим 50MHz output open-drain.
	if(sensor->GPIO_PIN <= 7)
	{
		pin = pin * 4;
		sensor->GPIO_PORT->CRL |=  (0X03 << pin);          //MODEy[1:0] - 11: Output mode, max speed 50 MHz
		sensor->GPIO_PORT->CRL |=  (0X01 << (0X02 << pin));//CNFy[1:0]  - 01: General purpose output Open-drain
		sensor->GPIO_PORT->CRL &= ~(0x02 << (0x02 << pin));//
	}
	else
	{
		pin = (pin - 8) * 4;
		sensor->GPIO_PORT->CRH |=  (0x03 << pin);          //MODEy[1:0] - 11: Output mode, max speed 50 MHz
		sensor->GPIO_PORT->CRH |=  (0x01 << (0x02 << pin));//CNFy[1:0]  - 01: General purpose output Open-drain
		sensor->GPIO_PORT->CRH &= ~(0x02 << (0x02 << pin));//
	}
}
//**********************************************************
static uint8_t OneWire_Reset(const DS18B20_t *sensor){

  uint16_t status = 0;
  uint32_t pin    = (1 << sensor->GPIO_PIN);
  //---------------------
  //низкий уровень
  sensor->GPIO_PORT->ODR &= ~pin;
  OneWire_usDelay(480);//задержка как минимум на 480 микросекунд
  //высокий уровень
  sensor->GPIO_PORT->ODR |= pin;
  OneWire_usDelay(60); //задержка как минимум на 60 микросекунд
  //проверяем уровень
  status = (sensor->GPIO_PORT->IDR & pin);
  OneWire_usDelay(DELAY_RESET_PULSE / 2);//на всякий случай подождём, так как могут быть неточности в задержке.
  return status;
}
//**********************************************************
static void OneWire_WriteBit(const DS18B20_t *sensor, uint8_t bit){

	uint32_t pin = (1 << sensor->GPIO_PIN);
	//---------------------
	//низкий уровень
	sensor->GPIO_PORT->ODR &= ~pin;
	if(bit) OneWire_usDelay(DELAY_WRITE_1);
	else    OneWire_usDelay(DELAY_WRITE_0);

	//высокий уровень
	sensor->GPIO_PORT->ODR |= pin;
	if(bit) OneWire_usDelay(DELAY_WRITE_1_PAUSE);
	else    OneWire_usDelay(DELAY_WRITE_0_PAUSE);
}
//**********************************************************
static void OneWire_WriteByte(const DS18B20_t *sensor, uint8_t data){

	for(uint8_t i = 0; i < 8; i++)
	{
		OneWire_WriteBit(sensor, ((data >> i) & 0x01));
	}
}
//**********************************************************
static uint8_t OneWire_ReadBit(const DS18B20_t *sensor){

	uint8_t  bit = 0;
	uint32_t pin = (1 << sensor->GPIO_PIN);
	//---------------------
	//шину к земле.
	sensor->GPIO_PORT->ODR &= ~pin;
	OneWire_usDelay(DELAY_READ_SLOT);
	//отпустили шину.
	sensor->GPIO_PORT->ODR |= pin;
	OneWire_usDelay(DELAY_BUS_RELAX);
	//Чтение состояния линии
	if(sensor->GPIO_PORT->IDR & pin) bit = 1;
	OneWire_usDelay(DELAY_READ_PAUSE);

	return bit;
}
//*******************************************************************************************
//*******************************************************************************************
//static uint8_t DS18B20_GetDevider(DS18B20_t *sensor){
//
//	switch (sensor->RESOLUTION){
//		case DS18B20_Resolution_9_bit:  return 8;
//		case DS18B20_Resolution_10_bit: return 4;
//		case DS18B20_Resolution_11_bit: return 2;
//		case DS18B20_Resolution_12_bit:
//		default: 						return 1;
//	}
//}
//**********************************************************
static void DS18B20_ReadTemperature(DS18B20_t *sensor){

	uint32_t data = 0;
	//---------------------
	__disable_irq();

	for(uint8_t i = 0; i < 16; i++)
	{
		data |= (uint32_t)(OneWire_ReadBit(sensor) << i);
	}
	//Отрицательная температура.
	if(data & 0x0000F800)
	{
		sensor->TEMPERATURE_SIGN = DS18B20_SIGN_NEGATIVE;
		data  = (data ^ 0x0000FFFF) + 1;
		data &= 0x00000FFF;//Маска для выделения 12 бит.
	}
	else sensor->TEMPERATURE_SIGN = DS18B20_SIGN_POSITIVE;

	__enable_irq();
	//Расчет температуры
	sensor->TEMPERATURE = (uint32_t)(((data * 625) + 500) / 1000);
}
//**********************************************************
/*! \brief  Sends the SEARCH ROM command and returns 1 id found on the
 *          1-Wire(R) bus.
 *
 *  \param  bitPattern      A pointer to an 8 byte char array where the
 *                          discovered identifier will be placed. When
 *                          searching for several slaves, a copy of the
 *                          last found identifier should be supplied in
 *                          the array, or the search will fail.
 *
 *  \param  lastDeviation   The bit position where the algorithm made a
 *                          choice the last time it was run. This argument
 *                          should be 0 when a search is initiated. Supplying
 *                          the return argument of this function when calling
 *                          repeatedly will go through the complete slave
 *                          search.
 *
 *  \param  pin             A bit-mask of the bus to perform a ROM search on.
 *
 *  \return The last bit position where there was a discrepancy between slave addresses the last time this function was run. Returns OWI_ROM_SEARCH_FAILED if an error was detected (e.g. a device was connected to the bus during the search), or OWI_ROM_SEARCH_FINISHED when there are no more devices to be discovered.
 *
 *  \note   See main.c for an example of how to utilize this function.
 */
//unsigned char OWI_SearchRom(uint8_t *bitPattern, uint8_t lastDeviation, uint8_t pin){
//
//	uint8_t currentBit = 1;
//	uint8_t newDeviation = 0;
//	uint8_t bitMask = 0x01;
//	uint8_t bitA;
//	uint8_t bitB;
//
//	// Send SEARCH ROM command on the bus.
//	OWI_SendByte(OWI_ROM_SEARCH, pin);
//
//	// Walk through all 64 bits.
//	while(currentBit <= 64)
//	{
//		// Read bit from bus twice.
//		bitA = OWI_ReadBit(pin);
//		bitB = OWI_ReadBit(pin);
//
//		if (bitA && bitB)
//		{
//			// Both bits 1 (Error).
//			newDeviation = OWI_ROM_SEARCH_FAILED;
//			return SEARCH_ERROR;
//		}
//		else if (bitA ^ bitB)
//		{
//			// Bits A and B are different. All devices have the same bit here.
//			// Set the bit in bitPattern to this value.
//			if (bitA)
//			{
//				(*bitPattern) |= bitMask;
//			}
//			else
//			{
//				(*bitPattern) &= ~bitMask;
//			}
//		}
//		else // Both bits 0
//		{
//			// If this is where a choice was made the last time,
//			// a '1' bit is selected this time.
//			if (currentBit == lastDeviation)
//			{
//				(*bitPattern) |= bitMask;
//			}
//			// For the rest of the id, '0' bits are selected when
//			// discrepancies occur.
//			else if (currentBit > lastDeviation)
//			{
//				(*bitPattern) &= ~bitMask;
//				newDeviation = currentBit;
//			}
//			// If current bit in bit pattern = 0, then this is
//			// out new deviation.
//			else if ( !(*bitPattern & bitMask))
//			{
//				newDeviation = currentBit;
//			}
//			// IF the bit is already 1, do nothing.
//			else
//			{
//
//			}
//		}
//
//
//		// Send the selected bit to the bus.
//		if ((*bitPattern) & bitMask)
//		{
//			OWI_WriteBit1(pin);
//		}
//		else
//		{
//			OWI_WriteBit0(pin);
//		}
//
//		// Increment current bit.
//		currentBit++;
//
//		// Adjust bitMask and bitPattern pointer.
//		bitMask <<= 1;
//		if (!bitMask)
//		{
//			bitMask = 0x01;
//			bitPattern++;
//		}
//	}
//	return newDeviation;
//}
//*******************************************************************************************
//*******************************************************************************************
void TemperatureSens_GpioInit(DS18B20_t *sensor){

	OneWire_GpioInit(sensor);
}
//**********************************************************
void TemperatureSens_SetResolution(DS18B20_t *sensor){

	OneWire_Reset(sensor);//reset();
	OneWire_WriteByte(sensor, SKIP_ROM);
	OneWire_WriteByte(sensor, WRITE_SCRATCHPAD);
	OneWire_WriteByte(sensor, TH_REGISTER);
	OneWire_WriteByte(sensor, TL_REGISTER);
	OneWire_WriteByte(sensor, sensor->RESOLUTION);
	//DELAY_WAIT_CONVERT = DELAY_T_CONVERT / DS18B20_GetDevider(sensor);
}
//**********************************************************
void TemperatureSens_StartConvertTemperature(DS18B20_t *sensor){

	if(OneWire_Reset(sensor)) return;
	OneWire_WriteByte(sensor, SKIP_ROM);
	OneWire_WriteByte(sensor, CONVERT_T);
}
//**********************************************************
void TemperatureSens_ReadTemperature(DS18B20_t *sensor){

	if(!sensor->GPIO_PORT) return;

	if(OneWire_Reset(sensor))
	{
		sensor->TEMPERATURE = 0;
		return;
	}
	OneWire_WriteByte(sensor, SKIP_ROM);
	OneWire_WriteByte(sensor, READ_SCRATCHPAD);
	DS18B20_ReadTemperature(sensor);

	TemperatureSens_StartConvertTemperature(sensor);
}
//**********************************************************
uint32_t TemperatureSens_Sign(DS18B20_t *sensor){

	return sensor->TEMPERATURE_SIGN;
}
//**********************************************************
uint32_t TemperatureSens_Temperature(DS18B20_t *sensor){

	return sensor->TEMPERATURE;
}
//*******************************************************************************************
//*******************************************************************************************
