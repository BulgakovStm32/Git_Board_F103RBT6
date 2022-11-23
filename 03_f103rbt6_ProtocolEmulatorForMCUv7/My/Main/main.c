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

static uint32_t redaction = 0;
//*******************************************************************************************
//*******************************************************************************************
//*******************************************************************************************
//*******************************************************************************************
void IncrementOnEachPass(uint32_t *var, uint32_t event, uint32_t step, uint32_t max){

		   uint32_t riseReg  = 0;
	static uint32_t oldState = 0;
	//-------------------
	riseReg  = (oldState ^ event) & event;
	oldState = event;
//	if(riseReg) (*var)++;
	if(riseReg)
	{
		if(step == 0) step = 1;
		if((*var) < max) (*var)+= step;//Проверка на  максимум.
		else             (*var) = 0;   //Закольцовывание редактирования параметра.
	}
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
void Temperature_Display(uint8_t cursor_x, uint8_t cursor_y, DS18B20_t *sensor){

	uint32_t temperature = sensor->TEMPERATURE;
	//-------------------
	Lcd_SetCursor(cursor_x, cursor_y);
	Lcd_Print("Temp");
	Lcd_BinToDec(sensor->SENSOR_NUMBER, 1, LCD_CHAR_SIZE_NORM);
	Lcd_Print(":");
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
//	DS2782_GetTemperature(&DS2782);		//получение температуры.
// 	DS2782_GetVoltage(&DS2782);    		//получение напряжения на АКБ.
//	DS2782_GetCurrent(&DS2782);    		//получения тока потребления от АКБ.
//	DS2782_GetAverageCurrent(&DS2782);	//получения усредненного за 28 сек. тока потребления от АКБ.
//	DS2782_GetAccumulatedCurrent(&DS2782);
}
//************************************************************
void Task_DS2782_Display(void){

		   uint32_t temp;
	static uint32_t strIndex = 0;
	//-------------------
	//Очистка видеобуфера.
	Lcd_ClearVideoBuffer();
	//Шапка;
	Lcd_PrintStringAndNumber(1, 1, "_DS2782_", 0, 0);
	//Вывод времени.
	Time_Display(14, 1);
	//----------------------------------------------
	//По нажатию на кнопку энкодера переход к выбору редактируемого параметра.
	IncrementOnEachPass(&redaction, ENCODER_GetButton(&Encoder), 1, 1);
	//При редактировании параметров меню справа от редактируемого
	//параметра выводится "<=".
	if(redaction)
	{
		ENCODER_IncDecParam(&Encoder, &strIndex, 1, 0, 6);
		Lcd_PrintStringAndNumber(20, (2 + strIndex), "<=", 0, 0);
	}
	else
	{
		strIndex = 0;
	}
	//----------------------------------------------
	//Вывод ошибок обvена по I2C.
	temp = I2C_Master_GetNacCount(DS2782_I2C);
	Lcd_PrintStringAndNumber(1, 2, "I2cNac :", temp, 4);

	//Вывод адреса на шине I2C
	Lcd_SetCursor(1, 3);
	Lcd_Print("I2cAddr:");
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

		   uint32_t temp;
	static uint32_t strIndex = 0;
	//-------------------
	//Очистка видеобуфера.
	Lcd_ClearVideoBuffer();
	//Шапка
	Lcd_PrintStringAndNumber(1, 1,"Emul_MCUv7", 0, 0);
	//Вывод времени.
	Time_Display(14, 1);
	//----------------------------------------------
	//По нажатию на кнопку энкодера переход к выбору редактируемого параметра.
	IncrementOnEachPass(&redaction, ENCODER_GetButton(&Encoder), 1, 1);
	//Ходим по пунктам страницы.
	if(redaction)
	{
		ENCODER_IncDecParam(&Encoder, &strIndex, 1, 0, 6);
		Lcd_PrintStringAndNumber(20, (2 + strIndex), "<=", 0, 0);
	}
	else
	{
		strIndex = 0;
	}
	//----------------------------------------------
	Lcd_PrintStringAndNumber(18, 2, '\0', strIndex, 2);

	//Вывод ошибок обvена по I2C.
	temp = PROTOCOL_MASTER_I2C_GetI2cNacCount();
	Lcd_PrintStringAndNumber(1, 2, "I2cNac  : ", temp, 4);

	//Количество переинициализаций I2C.
	temp = PROTOCOL_MASTER_I2C_GetDataMCU()->I2cResetCount;
	Lcd_PrintStringAndNumber(1, 3, "I2cReset: ", temp, 4);

	//Значение энкодера MCUv7.
	temp = PROTOCOL_MASTER_I2C_GetDataMCU()->EncoderAngle;
	Lcd_PrintStringAndNumber(1, 4, "EncAngle: ", temp, 6);

	//Значение оптических датчиков
	temp = PROTOCOL_MASTER_I2C_GetDataMCU()->Sense;
	Lcd_SetCursor(1, 5);
	Lcd_Print("Sense:");
	Lcd_u32ToHex(temp);

	//Напряжения питания MCU
	temp = PROTOCOL_MASTER_I2C_GetDataMCU()->SupplyVoltageVal;
	Lcd_PrintStringAndNumber(1, 6, "Vin  : ", temp, 5);
	Lcd_Print(" mV");

	//Вывод темперетуры DS18B20.
	Sensor_1.TEMPERATURE_SIGN = PROTOCOL_MASTER_I2C_GetDataMCU()->TemperatureSense1 >> 24;
	Sensor_1.TEMPERATURE      = PROTOCOL_MASTER_I2C_GetDataMCU()->TemperatureSense1 & 0x0000FFFF;

	Sensor_2.TEMPERATURE_SIGN = PROTOCOL_MASTER_I2C_GetDataMCU()->TemperatureSense2 >> 24;
	Sensor_2.TEMPERATURE      = PROTOCOL_MASTER_I2C_GetDataMCU()->TemperatureSense2 & 0x0000FFFF;

	Temperature_Display(1, 7, &Sensor_1);
	Temperature_Display(1, 8, &Sensor_2);
	//----------------------------------------------
	//Расчет процентов заряда АКБ и отображение уровня заряда.
	#define	V_BAT_MIN_mV	10800U	//
	#define	V_BAT_MAX_mV	16800U	//
	#define	DEVIDER			(V_BAT_MAX_mV - V_BAT_MIN_mV)

	temp = PROTOCOL_MASTER_I2C_GetDataMCU()->SupplyVoltageVal;
	if(temp < V_BAT_MIN_mV) temp = V_BAT_MIN_mV;
	uint32_t percent = ((100000 * (temp - V_BAT_MIN_mV)) / DEVIDER) / 1000;

	if(percent > 100) percent = 100;
	Lcd_SetCursor(16, 7);
	Lcd_PrintBig("%");
	Lcd_BinToDec(percent, 3, LCD_CHAR_SIZE_BIG);

	Lcd_Bar(114, 2, 124, 17, (uint8_t)percent);

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
void Task_Motor(void){

	static uint32_t flag = 0;
	int32_t temp;
	//-----------------------------

	if(PROTOCOL_MASTER_I2C_DMAState() != I2C_DMA_READY) return;

	//Настройки режимов вращения для MCUv7
	PROTOCOL_MASTER_I2C_SetReducerRate(6);		 //передаточное число редуктора
	PROTOCOL_MASTER_I2C_SetAccelerationTime(500);//Время ускорения
	PROTOCOL_MASTER_I2C_SetMaxVelocity(10);		 //Скорость вращения
	PROTOCOL_MASTER_I2C_MotorTorqueCtrl(1);	     //Включить момент

	//На какой угол повернуться.
	if(flag) temp = -60; //угол поворота, в градусах.
	else     temp =  60;
	flag ^= 1;
	PROTOCOL_MASTER_I2C_SetTargetPosition(temp);
}
//*******************************************************************************************
//*******************************************************************************************
//*******************************************************************************************
//*******************************************************************************************
void Task_DisplayPageSelect(void){

	static uint32_t pageIndex = 0;
	//-----------------------------
	TIME_Calculation(&Time, PROTOCOL_MASTER_I2C_GetDataMCU()->msCount);//RTOS_GetTickCount());

	//Если на какой-то странице производится редактирование то выбор страницы запрешен
	if(!redaction) ENCODER_IncDecParam(&Encoder, &pageIndex, 1, 0, 2);//Выбор сраницы
	switch(pageIndex){
		//--------------------
		case 0:
			RTOS_SetTask(PROTOCOL_MASTER_I2C_RequestToMCU, 1, 0);
			RTOS_SetTask(Task_MCUv7DataDisplay, 2, 0);
		break;
		//--------------------
		case 1:
			RTOS_SetTask(Task_DS2782,	  	  1, 0);
			RTOS_SetTask(Task_DS2782_Display, 2, 0);
		break;
		//--------------------
		default:
			Lcd_ClearVideoBuffer();
			Lcd_SetCursor(1, 1);
			Lcd_Print(" EMPTY PAGE ");
		break;
		//--------------------
	}
	//Проверка состяния системного регистра SystemCtrlReg
	if(PROTOCOL_MASTER_I2C_GetDataMCU()->SysCtrlReg.f_PwrOff) BigBoardPwr_Off();
	else 									  				  BigBoardPwr_On();
}
//************************************************************
//void Task_LcdUpdate(void){
//
//	//Обновление изображения на экране.
//	//Очистка видеобуфера производится на каждой странице.
//	Lcd_Update(); //вывод сделан для LM6063D
//}
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

	MICRO_DELAY(250000);//Эта задержка нужна для стабилизации напряжения патания.
					    //Без задержки LCD-дисплей не работает.
	//***********************************************
	//Ини-я DS2782.
	//DS2782_Init(DS2782_I2C, I2C_GPIO_NOREMAP);
	//***********************************************
	//Инициализация графического дисплея LM6063D.
	Lcd_Init();
	//***********************************************
	//Инициализация Энкодера.
	Encoder.GpioPort_A 	 	= GPIOC;
	Encoder.GpioPin_A   	= 11;
	Encoder.GpioPort_B 	 	= GPIOC;
	Encoder.GpioPin_B  	 	= 12;
	Encoder.GpioPort_BUTTON = GPIOC;
	Encoder.GpioPin_BUTTON  = 10;
	ENCODER_Init(&Encoder);
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
	RTOS_SetTask(Lcd_Update, 		     0,   10);//Обновление дисплея каждые 10мс
	RTOS_SetTask(Task_DisplayPageSelect, 0,    5);
	RTOS_SetTask(Task_Motor,     	   500, 2000);

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
	PROTOCOL_MASTER_I2C_IncTimeoutAndReset();

	msDelay_Loop();
	Blink_Loop();
	ENCODER_ScanLoop(&Encoder);
}
//*******************************************************************************************
//*******************************************************************************************
