/*
 * 	main.c
 *
 *  Created on: 19 октября 2021 года.
 *  Autho     : Беляев А.А.
 *
 *	Описание        :
 *  Датчики         :
 *  Вывод информации:
 *
 */
//*******************************************************************************************
//*******************************************************************************************

#include "main.h"

//*******************************************************************************************
//*******************************************************************************************
Time_t	  Time;
DS18B20_t Sensor_1;
DS18B20_t Sensor_2;
DS2782_t  DS2782;
Encoder_t Encoder;
//*******************************************************************************************
//*******************************************************************************************
//*******************************************************************************************
//*******************************************************************************************
void IncrementOnEachPass(uint32_t *var, uint16_t event){

		   uint16_t riseReg  = 0;
	static uint16_t oldState = 0;
	//-------------------
	riseReg  = (oldState ^ event) & event;
	oldState = event;
	if(riseReg) (*var)++;
}
//************************************************************
uint32_t Led_Blink(uint32_t millis, uint32_t period, uint32_t switch_on_time){

	static uint32_t millisOld = 0;
	static uint32_t flag      = 0;
	//-------------------
	if((millis - millisOld) >= (flag ? (period - switch_on_time) : switch_on_time ))
	{
		millisOld = millis;
		flag = !flag;
	}
	return flag;
}
//************************************************************
void Temperature_Display(DS18B20_t *sensor, uint8_t cursor_x, uint8_t cursor_y){

	uint32_t temperature = sensor->TEMPERATURE;
	//-------------------
	Lcd_SetCursor(cursor_x, cursor_y);
	Lcd_Print("MCU_T");
	Lcd_BinToDec(sensor->SENSOR_NUMBER, 1, LCD_CHAR_SIZE_NORM);
	Lcd_Print("   = ");
	if(TemperatureSens_Sign(sensor) & DS18B20_SIGN_NEGATIVE)Lcd_Chr('-');
	else                    								Lcd_Chr('+');
	Lcd_BinToDec(temperature/10, 2, LCD_CHAR_SIZE_NORM);
	Lcd_Chr('.');
	Lcd_BinToDec(temperature%10, 1, LCD_CHAR_SIZE_NORM);
	Lcd_Print("o ");
	Lcd_Chr('C');
}
//************************************************************
void Temperature_TxtDisplay(DS18B20_t *sensor){

	uint32_t temperature = sensor->TEMPERATURE;
	//-------------------
	Txt_Print("Sens");
	Txt_BinToDec(sensor->SENSOR_NUMBER, 1);
	Txt_Print("= ");
	if(TemperatureSens_Sign(sensor) & DS18B20_SIGN_NEGATIVE)Txt_Chr('-');
	else                    								Txt_Chr('+');
	Txt_BinToDec(temperature/10, 2);
	Txt_Chr('.');
	Txt_BinToDec(temperature%10, 1);
	Txt_Print(" C\n");
}
//************************************************************
void Time_Display(uint8_t cursor_x, uint8_t cursor_y){

	//Вывод времени.
	Lcd_SetCursor(cursor_x, cursor_y);
//	Lcd_Print("Time: ");
	Lcd_BinToDec(Time.hour, 2, LCD_CHAR_SIZE_NORM);//часы
	Lcd_Chr(':');
	Lcd_BinToDec(Time.min,  2, LCD_CHAR_SIZE_NORM);//минуты
	//Lcd_Chr(':');
	if(Time.sec & 1) Lcd_Chr(':');//Мигание разделительным знаком
	else			 Lcd_Chr(' ');
	Lcd_BinToDec(Time.sec,  2, LCD_CHAR_SIZE_NORM);//секунды
}
//*******************************************************************************************
//*******************************************************************************************
//*******************************************************************************************
//*******************************************************************************************
//Работа с микросхемой DS2782.
void Task_DS2782(void){

	DS2782_GetI2cAddress(&DS2782); 		//получение адреса на шине I2C
	//DS2782_GetID(&DS2782);         		//получение Unique ID (factory option)
	DS2782_GetTemperature(&DS2782);		//получение температуры.
 	DS2782_GetVoltage(&DS2782);    		//получение напряжения на АКБ.
	DS2782_GetCurrent(&DS2782);    		//получения тока потребления от АКБ.
	DS2782_GetAverageCurrent(&DS2782);	//получения усредненного за 28 сек. тока потребления от АКБ.
	DS2782_GetAccumulatedCurrent(&DS2782);
}
//************************************************************
void Task_DS2782_Display(void){

	uint32_t temp = 0;

	Lcd_ClearVideoBuffer();

	//Шапка
	Lcd_SetCursor(1, 1);
	Lcd_Print("_DS2782_");
	//Вывод времени.
	Time_Display(1, 2);
	//Вывод ошибок обvена по I2C.
	Lcd_SetCursor(10, 1);
	Lcd_Print("I2CNAC=");
//	Lcd_BinToDec(I2C_GetNacCount(DS2782_I2C), 4, LCD_CHAR_SIZE_NORM);

	//Вывод адреса на шине I2C
	Lcd_SetCursor(1, 3);
	Lcd_Print("DS2782_I2C_ADDR:");
	Lcd_Print("0x");
	Lcd_u8ToHex(DS2782.I2C_Address);

	//Вывод температуры.
	Lcd_SetCursor(1, 4);
	Lcd_Print("Bat_T   = ");
	temp = DS2782.Temperature;
	Lcd_BinToDec(temp/10, 2, LCD_CHAR_SIZE_NORM);
	Lcd_Chr('.');
	Lcd_BinToDec(temp%10, 1, LCD_CHAR_SIZE_NORM);
	Lcd_Print(" C");

	//Вывод напряжения на АКБ.
	Lcd_SetCursor(1, 5);
	Lcd_Print("Bat_U   = ");
	temp = DS2782.Voltage;
	Lcd_BinToDec(temp/100, 2, LCD_CHAR_SIZE_NORM);
	Lcd_Chr('.');
	Lcd_BinToDec(temp%100, 2, LCD_CHAR_SIZE_NORM);
	Lcd_Chr('V');
	//----------------------------------------------
	//Вывод тока потребления от АКБ.
	int16_t currentTemp = DS2782.Current;

	Lcd_SetCursor(1, 6);
	Lcd_Print("Bat_I   =");

	if(currentTemp < 0)
	{
		currentTemp = (currentTemp ^ 0xFFFF) + 1;//Уберем знак.
		Lcd_Chr('-');
	}
	else Lcd_Chr(' ');

	Lcd_BinToDec(currentTemp, 4, LCD_CHAR_SIZE_NORM);
	Lcd_Print("mA");

	//----------------------------------------------
	//Вывод усредненного за 28сек. тока.
	currentTemp = DS2782.AverageCurrent;

	Lcd_SetCursor(1, 7);
	Lcd_Print("Bat_Iavr=");

	if(currentTemp < 0)
	{
		currentTemp = (currentTemp ^ 0xFFFF) + 1;//Уберем знак.
		Lcd_Chr('-');
	}
	else Lcd_Chr(' ');

	Lcd_BinToDec(currentTemp, 4, LCD_CHAR_SIZE_NORM);
	Lcd_Print("mA");
	//----------------------------------------------
	Lcd_SetCursor(1, 8);
	Lcd_Print("Bat_Iacc=");
	Lcd_BinToDec(DS2782.AccumulatedCurrent, 5, LCD_CHAR_SIZE_NORM);
	Lcd_Print("uAh");
}
//*******************************************************************************************
//*******************************************************************************************
//*******************************************************************************************
//*******************************************************************************************
void Task_MCUv7DataDisplay(void){

	//Очистка видеобуфера.
	Lcd_ClearVideoBuffer();

	//Шапка
	Lcd_SetCursor(1, 1);
	Lcd_Print("Emul_MCUv7");
	//Вывод времени.
	Time_Display(14, 1);

	//Вывод ошибок обvена по I2C.
	Lcd_SetCursor(1, 2);
	Lcd_Print("I2cNac      = ");
	Lcd_BinToDec(PROTOCOL_MASTER_I2C_GetI2cNacCount(), 4, LCD_CHAR_SIZE_NORM);

	//Количесвто переинициализаций I2C.
	Lcd_SetCursor(1, 3);
	Lcd_Print("MCUi2cReInit= ");
	Lcd_BinToDec(PROTOCOL_MASTER_I2C_GetDataMCU()->I2cResetCount, 4, LCD_CHAR_SIZE_NORM);

	//Напряжения питания MCU
	Lcd_SetCursor(1, 4);
	Lcd_Print("MCU_Vin  = ");
	Lcd_BinToDec(PROTOCOL_MASTER_I2C_GetDataMCU()->SupplyVoltageVal, 5, LCD_CHAR_SIZE_NORM);
	Lcd_Print(" mV");

	//Значение энкодера MCUv7.
	Lcd_SetCursor(1, 5);
	Lcd_Print("MCU_Enc  = ");
	Lcd_BinToDec(PROTOCOL_MASTER_I2C_GetDataMCU()->EncoderVal, 6, LCD_CHAR_SIZE_NORM);

	//Значение оптических датчиков
	Lcd_SetCursor(1, 6);
	Lcd_Print("MCU_Sense= ");
	Lcd_u32ToHex(PROTOCOL_MASTER_I2C_GetDataMCU()->Sense);

	//Вывод темперетуры DS18B20.
	Sensor_1.TEMPERATURE_SIGN = PROTOCOL_MASTER_I2C_GetDataMCU()->TemperatureSense1 >> 24;
	Sensor_1.TEMPERATURE      = PROTOCOL_MASTER_I2C_GetDataMCU()->TemperatureSense1 & 0x0000FFFF;

	Sensor_2.TEMPERATURE_SIGN = PROTOCOL_MASTER_I2C_GetDataMCU()->TemperatureSense2 >> 24;
	Sensor_2.TEMPERATURE      = PROTOCOL_MASTER_I2C_GetDataMCU()->TemperatureSense2 & 0x0000FFFF;

	Temperature_Display(&Sensor_1, 1, 7);
	Temperature_Display(&Sensor_2, 1, 8);

	//Кнопка энкодера.
//	IncrementOnEachPass(&ButtonPressCount, Encoder.BUTTON_STATE);
//	Lcd_SetCursor(1, 8);
//	Lcd_Print("Button=");
//	Lcd_BinToDec((uint16_t)ButtonPressCount, 4, LCD_CHAR_SIZE_NORM);
}
//*******************************************************************************************
//*******************************************************************************************
//*******************************************************************************************
//*******************************************************************************************
void Task_LcdUpdate(void){

	TIME_Calculation(&Time, PROTOCOL_MASTER_I2C_GetDataMCU()->msCount);//RTOS_GetTickCount());
	//Выбор сраницы отображения Енкодером.
	static uint32_t encoder = 0;
	Encoder_IncDecParam(&Encoder, &encoder, 1, 0, 2);
	switch(encoder){
		//--------------------
		case 0:
			RTOS_SetTask(PROTOCOL_MASTER_I2C_RequestToMCU, 1, 0);
			RTOS_SetTask(Task_MCUv7DataDisplay, 2, 0);
		break;
		//--------------------
		case 1:
			//RTOS_SetTask(Task_DS2782,	  	  1,  0);
			RTOS_SetTask(Task_DS2782_Display, 3, 0);
		break;
		//--------------------
		default:
			Lcd_ClearVideoBuffer();
			Lcd_SetCursor(1, 1);
			Lcd_Print(" EMPTY PAGE ");
		break;
		//--------------------
	}
	//Обновление изображения на экране.
	//Очистка видеобуфера производится на каждой странице.
	Lcd_Update(); //вывод сделан для LM6063D
}
//*******************************************************************************************
//*******************************************************************************************
//*******************************************************************************************
//*******************************************************************************************
int main(void){

	//***********************************************
	//Drivers.
	Sys_Init();
	Gpio_Init();
	MICRO_DELAY_Init();
	USART_Init(USART1, USART1_BRR);

	MICRO_DELAY(200000);//Эта задержка нужна для стабилизации напряжения патания.
					    //Без задержки LCD-дисплей не работает.
	//***********************************************
	//Ини-я DS2782.
//	DS2782_Init(DS2782_I2C, I2C_GPIO_NOREMAP);
	//***********************************************
	//Инициализация графического дисплея.
	Lcd_Init();
	//***********************************************
	//Инициализация Энкодера.
	Encoder.GPIO_PORT_A 	 = GPIOC;
	Encoder.GPIO_PIN_A   	 = 11;
	Encoder.GPIO_PORT_B 	 = GPIOC;
	Encoder.GPIO_PIN_B  	 = 12;
	Encoder.GPIO_PORT_BUTTON = GPIOC;
	Encoder.GPIO_PIN_BUTTON  = 10;
	Encoder_Init(&Encoder);
	//***********************************************
	//Инициализация датчиков температуры
	Sensor_1.SENSOR_NUMBER = 1;
	Sensor_2.SENSOR_NUMBER = 2;
	//***********************************************
	//Инициализация I2C для работы протокола.
	PROTOCOL_MASTER_I2C_Init();
	//***********************************************
	//Инициализация диспетчера.
	RTOS_Init();
	RTOS_SetTask(Task_LcdUpdate, 0, 5);

	SysTick_Init();
	__enable_irq();
	//**************************************************************
	while(1)
	{
		RTOS_DispatchLoop();
		//__WFI();//Sleep
	}
	//**************************************************************
}
//*******************************************************************************************
//*******************************************************************************************
//Прерывание каждую милисекунду.
void SysTick_IT_Handler(void){

	RTOS_TimerServiceLoop();
	msDelay_Loop();
	Blink_Loop();
	Encoder_ScanLoop(&Encoder);
	PROTOCOL_MASTER_I2C_IncTimeoutAndReset();
}
//*******************************************************************************************
//*******************************************************************************************
