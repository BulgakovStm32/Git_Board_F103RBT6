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
/*
 * Функция пропорционально переносит значение (value) из текущего диапазона значений (fromLow .. fromHigh)
 * в новый диапазон (toLow .. toHigh), заданный параметрами.
 * Функция map() не ограничивает значение рамками диапазона, как это делает функция constrain().
 *
 * Contrain() может быть использован до или после вызова map(), если необходимо ограничить допустимые значения заданным диапазоном.
 * Обратите внимание, что "нижняя граница" может быть как меньше, так и больше "верхней границы".
 *  Это может быть использовано для того чтобы "перевернуть" диапазон:
 *  y = map(x, 1, 50, 50, 1);
 *
 * Возможно использование отрицательных значений:
 * y = map(x, 1, 50, 50, -100);
 *
 * Функция map() оперирует целыми числами.
 * При пропорциональном переносе дробная часть не округляется по правилами, а просто отбрасывается.
 *
 * Параметры
 * value	  : значение для переноса
 * in_min  : нижняя граница текущего диапазона
 * in_max  : верхняя граница текущего диапазона
 * out_min : нижняя граница нового диапазона, в который переноситься значение
 * out_max : верхняя граница нового диапазона
 * Возвращаемое значение:
 * Значение в новом диапазоне */

long map(long value, long in_min, long in_max, long out_min, long out_max){

  return (value - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
//************************************************************

int32_t map_I32(int32_t value, int32_t in_min, int32_t in_max, int32_t out_min, int32_t out_max){

  return (value - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
//*******************************************************************************************
//*******************************************************************************************
//*******************************************************************************************
//*******************************************************************************************
//стрелочный индикатор
#define ANALOG_SCALE_X0			64  				//Х-координата центра шкалы (в пикселях)
#define ANALOG_SCALE_Y0	 	   -65  				//Y-координата центра шкалы (в пикселях)
#define ANALOG_SCALE_RADIUS		95					//радиус шкалы (в пикселях)
#define ANALOG_SCALE_PI_2_8		(float)(M_PI_2 / 8) //шаг, с которым рисуются риски шкалы (радианы)

#define ANALOG_SCALE_MULTIPLIER  10									  //множитель, показывающий на сколько частей разбиваем один градус перемещения стрелки.
#define ANALOG_SCALE_ANGLE_MIN	(5  * ANALOG_SCALE_MULTIPLIER)		  //мин. угол поверота стрелки (слева направо) (в градусах).
#define ANALOG_SCALE_ANGLE_MAX	(85 * ANALOG_SCALE_MULTIPLIER)		  //макс.угол поверота стрелки (слева направо) (в градусах).

#define ANALOG_SCALE_SECTOR		(90 * ANALOG_SCALE_MULTIPLIER)		  //ширина сектора в котором богает стрлека (в градусах).
#define ANALOG_SCALE_PHI		(45 * ANALOG_SCALE_MULTIPLIER)  	  //поворот сектора ANALOG_SCALE_SECTOR от нуля градусов (в градусах).
#define ANALOG_SCALE_K_RAD		(float)(M_PI_2 / ANALOG_SCALE_SECTOR) //коэф-т для перевода углов в радианы.

/*
 * Параметры:
 * angle :угол на который нужно повернуть стрелку (слева направо)
 *		  мин. уол  - ANALOG_SCALE_ANGLE_MIN градусов.
 *		  макс.угол - ANALOG_SCALE_ANGLE_MAX градусов.
 */
void Lcd_AnalogScale(uint32_t angle){

//	const uint8_t markRadius = 95;// Радиус шкалы.
//	int8_t x0 =  62;//64;		 //Х-координата центра шкалы
//	int8_t y0 = ANALOG_SCALE_Y0; //Y-координата центра шкалы.
	float cos;
	float sin;
	//-------------------
	//Рисуем риски-метки шкалы
	for(float i = 0; i < M_PI_2; i += ANALOG_SCALE_PI_2_8)
	{
		cos = cosf(i + M_PI_4);
		sin = sinf(i + M_PI_4);
		Lcd_Line(ANALOG_SCALE_X0 +  ANALOG_SCALE_RADIUS    * cos,
				 ANALOG_SCALE_Y0 +  ANALOG_SCALE_RADIUS    * sin,
				 ANALOG_SCALE_X0 + (ANALOG_SCALE_RADIUS-6) * cos,
				 ANALOG_SCALE_Y0 + (ANALOG_SCALE_RADIUS-6) * sin,
				 PIXEL_ON);
	}
	//Стрелка.
	angle  = (ANALOG_SCALE_SECTOR - angle);	//это нужно чтобы стрелка двигалась слева направо.
	angle += ANALOG_SCALE_PHI;				//поворот сектора отображения стрелки от нуля градусов.
	float rad = angle * ANALOG_SCALE_K_RAD; //перевод углов в радианы
	cos = cosf(rad);
	sin = sinf(rad);
	//x0 += 1; //небольшое смещение по Х что бы стрелка точно поподала в среднюю риску.
	//y0 += 5; //небольшое смещение по Y что бы стрелка поподала в риски.
	Lcd_Line(ANALOG_SCALE_X0 + ANALOG_SCALE_RADIUS * cos,
			 ANALOG_SCALE_Y0 + 5 + ANALOG_SCALE_RADIUS * sin,
			 ANALOG_SCALE_X0 + 1 * cos,
			 ANALOG_SCALE_Y0 + 5 + 1 * sin,
			 PIXEL_ON);
}
//************************************************************
//Горизонтальная шкала с рисками.
/*
 * Параметры:
 * x0	: начальная координата шкалы по Х (мин. 0, макс. 127).
 * y0	: начальная координата шкалы по Y (мин. 0, макс. 63).
 * level: отображаемое значение (мин. 0, макс. 127)
 *
 */
void Lcd_HorizontalProgressBar(uint8_t x0, uint8_t y0, uint8_t level){

//	uint8_t x0	      = 3;		//Начальная координата шкалы по Х.
//	uint8_t y0	      = 2;		//Начальная координата шкалы по Y.
//	uint8_t sigLevel  = (uint8_t)map(percent, 0, 100, 0, maxVal);//Отображаемый сигнал . Мин. 0, макс. 127.

	const uint8_t numMarks  = 5;   //Необходимое кол-во вертикальных рисок на шкале.
	const uint8_t scaleStep = 1;   //Шаг приращения шкалы в пикселях
	const uint8_t maxVal    = 100; //Максимальное отображаемое значение, макс. 127 (на дисплее макс 128 пикселей).
	uint8_t marksStep = maxVal / (numMarks-1);//Шаг между рисками.
	uint8_t stepCount = x0;
	//-------------------
	//Рисуем риски.
	for(uint8_t i = 0; i < numMarks; i++)
	{
		Lcd_Line(stepCount, y0, stepCount, y0+4, PIXEL_ON);//Первая Вертикальная палочка высотой 5 пикселей.
		//Lcd_Line(stepCount+1, 1, stepCount+1, 5, PIXEL_ON);//Вторая Вертикальная палочка высотой 5 пикселей.
		stepCount += marksStep;
	}
	//Рисуем шкалу.
	stepCount = x0;
	level /= scaleStep;//равномерное распределение шагов на всю шкалу.
	for(uint8_t i = 0; i < level; i++)
	{
		Lcd_Line(stepCount, y0, stepCount, y0+2, PIXEL_ON);//Вертикальная палочка высотой 3 пикселя.
		stepCount += scaleStep;
	}
	//Циферки над рисками шкалы
	Lcd_SetCursor(1, 7);
	Lcd_Print("0   25  50  75  100");
}
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
	if( (millis - millisOld) >= (flag ? (period - switch_on_time) : switch_on_time) )
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
//************************************************************
//Расчет процентов заряда АКБ.
#define	V_BAT_MIN_mV	10800U	//
#define	V_BAT_MAX_mV	16800U	//
//#define	DEVIDER			(V_BAT_MAX_mV - V_BAT_MIN_mV)

//Расчет процентов заряда АКБ.
uint8_t Battery_GetPercentCharge(void){

	uint32_t temp;
	//-------------------
	temp = PROTOCOL_MASTER_I2C_GetDataMCU()->SupplyVoltageVal;
	if(temp < V_BAT_MIN_mV) temp = V_BAT_MIN_mV;
	temp = map_I32(temp, V_BAT_MIN_mV, V_BAT_MAX_mV, 1, 100);
	if(temp > 100) temp = 100;
	return (uint8_t)temp;
}
//*******************************************************************************************
//*******************************************************************************************
//*******************************************************************************************
//*******************************************************************************************
//Работа с микросхемой DS2782.
void Task_DS2782(void){

//	DS2782_GetI2cAddress(&DS2782); 		//получение адреса на шине I2C
	//DS2782_GetID(&DS2782);         		//получение Unique ID (factory option)
	DS2782_GetTemperature(&DS2782);		//получение температуры.
 	DS2782_GetVoltage(&DS2782);    		//получение напряжения на АКБ.
//	DS2782_GetCurrent(&DS2782);    		//получения тока потребления от АКБ.
//	DS2782_GetAverageCurrent(&DS2782);	//получения усредненного за 28 сек. тока потребления от АКБ.
//	DS2782_GetAccumulatedCurrent(&DS2782);
//	DS2782_GetACRL(&DS2782);
}
//************************************************************
void Task_DS2782_Display(void){

		   uint32_t temp;
	static uint32_t strIndex = 0;
	//-------------------
	//Очистка видеобуфера.
	Lcd_ClearVideoBuffer();
	//Шапка;
	Lcd_PrintStringAndNumber(1, 1, "_DS2782_v01", 0, 0);
	//Вывод времени.
//	Time_Display(14, 1);
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
	else strIndex = 0;
	//----------------------------------------------
	//Вывод ошибок обvена по I2C.
	temp = I2C_Master_GetNacCount(DS2782_I2C);
	Lcd_PrintStringAndNumber(1, 2, "I2cNac :", temp, 4);

	//Вывод адреса на шине I2C
//	Lcd_SetCursor(1, 3);
//	Lcd_Print("I2cAddr:");
//	Lcd_Print("0x");
//	Lcd_u8ToHex(DS2782.I2C_Address);

	//Вывод температуры.
	Lcd_SetCursor(1, 3);
	Lcd_Print("Bat_T   = ");
	temp = DS2782.Temperature;
	Lcd_BinToDec(temp/10, 2, LCD_CHAR_SIZE_NORM);
	Lcd_Chr('.');
	Lcd_BinToDec(temp%10, 1, LCD_CHAR_SIZE_NORM);
	Lcd_Print(" C");

	//Вывод напряжения на АКБ.
	Lcd_SetCursor(1, 4);
	Lcd_Print("Bat_U   = ");
	temp = DS2782.Voltage;
	Lcd_BinToDec(temp/100, 2, LCD_CHAR_SIZE_NORM);
	Lcd_Chr('.');
	Lcd_BinToDec(temp%100, 2, LCD_CHAR_SIZE_NORM);
	Lcd_Chr('V');
	//----------------------------------------------
	//Вывод тока потребления от АКБ.
	int16_t currentTemp = DS2782.Current;

	Lcd_SetCursor(1, 5);
	Lcd_Print("Bat_I   =");

//	if(currentTemp < 0)
//	{
//		currentTemp = -currentTemp;//Уберем знак.
//		Lcd_Chr('-');
//	}
//	else Lcd_Chr(' ');
//	Lcd_BinToDec(currentTemp, 4, LCD_CHAR_SIZE_NORM);
	Lcd_BinToDecWithSign(currentTemp, 8, LCD_CHAR_SIZE_NORM);
	Lcd_Print("uA");
	//----------------------------------------------
	//Вывод усредненного за 28сек. тока.
	currentTemp = DS2782.AverageCurrent;

	Lcd_SetCursor(1, 6);
	Lcd_Print("Bat_Iavr=");

//	if(currentTemp < 0)
//	{
//		currentTemp = -currentTemp;//Уберем знак.
//		Lcd_Chr('-');
//	}
//	else Lcd_Chr(' ');
//	Lcd_BinToDec(currentTemp, 4, LCD_CHAR_SIZE_NORM);
	Lcd_BinToDecWithSign(currentTemp, 4, LCD_CHAR_SIZE_NORM);
	Lcd_Print("mA");
	//----------------------------------------------
	Lcd_SetCursor(1, 7);
	Lcd_Print("Bat_Iacc= ");
	Lcd_BinToDec(DS2782.AccumulatedCurrent, 8, LCD_CHAR_SIZE_NORM);
	Lcd_Print("uAh");

	Lcd_SetCursor(1, 8);
	Lcd_Print("Bat_ACRL= ");
	Lcd_BinToDec(DS2782.ACRL, 8, LCD_CHAR_SIZE_NORM);
	Lcd_Print("nAh");
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
	Lcd_PrintStringAndNumber(1, 1,"Emul_MCUv7_000", 0, 0);
	//Вывод времени.
	//Time_Display(14, 1);
	//----------------------------------------------
	//По нажатию на кнопку энкодера переход к выбору редактируемого параметра.
	IncrementOnEachPass(&redaction, ENCODER_GetButton(&Encoder), 1, 1);
	//Ходим по пунктам страницы.
	if(redaction)
	{
		ENCODER_IncDecParam(&Encoder, &strIndex, 1, 0, 6);
		Lcd_PrintStringAndNumber(20, (2 + strIndex), "<=", 0, 0);
	}
	else strIndex = 0;
	//----------------------------------------------
	Lcd_PrintStringAndNumber(18, 3, '\0', strIndex, 2);

	//Вывод ошибок обvена по I2C.
	temp = PROTOCOL_MASTER_I2C_GetI2cNacCount();
	Lcd_PrintStringAndNumber(1, 2, "I2cNac:", temp, 3);

	//Количество переинициализаций I2C.
	temp = PROTOCOL_MASTER_I2C_GetDataMCU()->I2cResetCount;
	Lcd_PrintStringAndNumber(12, 2, "I2cRes:", temp, 3);

	//Значение энкодера MCUv7.
	temp = PROTOCOL_MASTER_I2C_GetDataMCU()->EncoderAngle;
	Lcd_PrintStringAndNumber(1, 3, "EncAngle: ", temp, 6);

	//Вывод темперетуры DS18B20.
	Sensor_1.TEMPERATURE_SIGN = PROTOCOL_MASTER_I2C_GetDataMCU()->TemperatureSense1 >> 24;
	Sensor_1.TEMPERATURE      = PROTOCOL_MASTER_I2C_GetDataMCU()->TemperatureSense1 & 0x0000FFFF;

	Sensor_2.TEMPERATURE_SIGN = PROTOCOL_MASTER_I2C_GetDataMCU()->TemperatureSense2 >> 24;
	Sensor_2.TEMPERATURE      = PROTOCOL_MASTER_I2C_GetDataMCU()->TemperatureSense2 & 0x0000FFFF;

	Temperature_Display(1, 4, &Sensor_1);
	Temperature_Display(1, 5, &Sensor_2);

	//Напряжения питания MCU
	temp = PROTOCOL_MASTER_I2C_GetDataMCU()->SupplyVoltageVal;
	Lcd_PrintStringAndNumber(1, 6, "Vin  : ", temp, 5);
	Lcd_Print(" mV");

	//Значение оптических датчиков
//	temp = PROTOCOL_MASTER_I2C_GetDataMCU()->Sense;
//	Lcd_SetCursor(1, 7);
//	Lcd_Print("Sense:");
//	Lcd_u32ToHex(temp);
	//----------------------------------------------
	//Отображение заряда АКБ в виде батарейки.
	uint8_t batPercent = Battery_GetPercentCharge();

//	Lcd_SetCursor(16, 7);
//	Lcd_PrintBig("%");
//	Lcd_BinToDec(batPercent, 3, LCD_CHAR_SIZE_BIG);
//	Lcd_Bar(114, 2, 124, 17, (uint8_t)percent);
	//----------------------------------------------
	//Горизонтальная шкала с рисками.
	Lcd_HorizontalProgressBar(3, 2, batPercent); //map(batPercent, 0, 100, 0, 100));
}
//*******************************************************************************************
//*******************************************************************************************
//*******************************************************************************************
//*******************************************************************************************
void Task_AnalogMeter(void){

	//-------------------
	//Очистка видеобуфера.
	Lcd_ClearVideoBuffer();
	//Шапка
	Lcd_SetCursor(1, 1);
	Lcd_Print("AnalogMeter");
	//Вывод времени.
	Time_Display(14, 1);
	//-------------------
	//Расчет процентов заряда АКБ
	uint8_t batPercent = Battery_GetPercentCharge();
	//-------------------
	//Энкодер
	static uint32_t angle = (ANALOG_SCALE_ANGLE_MAX - ANALOG_SCALE_ANGLE_MIN) / 2;
//	ENCODER_IncDecParam(&Encoder, &angle, 1, ANALOG_SCALE_ANGLE_MIN , ANALOG_SCALE_ANGLE_MAX);
	//-------------------
	//Аналговая стрелочная шкала.
	angle = map_I32(batPercent, 1, 100, ANALOG_SCALE_ANGLE_MIN, ANALOG_SCALE_ANGLE_MAX);

//	Lcd_PrintStringAndNumber(1, 2, "Angle: ", angle, 3);
	Lcd_PrintStringAndNumber(1, 2, "Percent: ", batPercent, 3);

	Lcd_AnalogScale(angle);
}
//*******************************************************************************************
//*******************************************************************************************
//*******************************************************************************************
//*******************************************************************************************
void Task_Motor(void){

	static uint32_t flag = 0;
	int32_t temp;
	//-----------------------------
	//Если I2C занят, то выходим.
	if(PROTOCOL_MASTER_I2C_DMAState() != I2C_DMA_READY) return;

	//Настройки режимов вращения для MCUv7
	PROTOCOL_MASTER_I2C_SetReducerRate(6);		   //передаточное число редуктора
	PROTOCOL_MASTER_I2C_SetAccelerationTime(1000); //Время ускорения
	PROTOCOL_MASTER_I2C_SetMaxVelocity(10);		   //Скорость вращения
	PROTOCOL_MASTER_I2C_MotorTorqueCtrl(1);	       //Включить момент

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

//	if(Blink_SwitchOnTime(500, 5)) LedPC13On();
//	else						   LedPC13Off();

	//Если на какой-то странице производится редактирование то выбор страницы запрешен
	//if(!redaction) ENCODER_IncDecParam(&Encoder, &pageIndex, 1, 0, 2);//Выбор сраницы
	switch(pageIndex){
		//--------------------
		case 0:
			RTOS_SetTask(PROTOCOL_MASTER_I2C_RequestToMCU, 1, 0);
			RTOS_SetTask(Task_MCUv7DataDisplay, 2, 0);
		break;
		//--------------------
		case 1:
			RTOS_SetTask(Task_DS2782,	  	  1,  0);
			RTOS_SetTask(Task_DS2782_Display, 10, 0);
		break;
		//--------------------
		case 2:
			RTOS_SetTask(Task_AnalogMeter, 2, 0);
		break;
		//--------------------
		default:
			Lcd_ClearVideoBuffer();
			Lcd_SetCursor(1, 1);
			Lcd_Print(" EMPTY PAGE ");
		break;
		//--------------------
	}
	//RTOS_SetTask(PROTOCOL_MASTER_I2C_RequestToMCU, 1, 0);
	//Проверка состяния системного регистра SystemCtrlReg
	if(PROTOCOL_MASTER_I2C_GetDataMCU()->SysCtrlReg.f_PwrOff) BIG_BOARD_PWR_Off();
	else 									  				  BIG_BOARD_PWR_On();
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
	GPIO_MCU_Init();
	DELAY_Init();
	USART_Init(USART1, USART1_BRR);
	DELAY_milliS(250);//Эта задержка нужна для стабилизации напряжения патания.
					  //Без задержки LCD-дисплей не работает.
	//***********************************************
	//Чтение конфигурации. Если первое включение, то запись заводских установок.
	Config_Init();
	//***********************************************
	//Ини-я DS2782.
	DS2782_Init(DS2782_I2C, I2C_GPIO_NOREMAP);
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
	RTOS_SetTask(Lcd_Update,      0,    5);//Обновление дисплея каждые 5мс
	RTOS_SetTask(Config_SaveLoop, 0, 1000);//Проверка и сохранение конфигурации каждую 1 сек.

	RTOS_SetTask(Task_DisplayPageSelect, 0,   20);
//	RTOS_SetTask(Task_Motor,     	   500, 2500);

	SysTick_Init();
	__enable_irq();
	//***********************************************
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
