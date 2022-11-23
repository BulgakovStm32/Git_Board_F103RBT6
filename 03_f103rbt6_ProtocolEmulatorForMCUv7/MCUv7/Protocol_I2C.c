/*
 * Protocol_I2C.c
 *
 *  Created on: 22 авг. 2022 г.
 *      Author: belyaev
 */
//*******************************************************************************************
//*******************************************************************************************

#include "Protocol_I2C.h"

//*******************************************************************************************
//*******************************************************************************************

static I2C_IT_t	 	I2cProtocol;
static MCUv7_Data_t MCUc7Data;

static uint32_t responseSize = 0;
static uint32_t ledFlag      = 0;

//*******************************************************************************************
//*******************************************************************************************
static void I2cRxParsing(void){

	MCU_Response_t *response = (MCU_Response_t *)I2cProtocol.pRxBuf;
	//-----------------------------
	//Проверка CRC.
	uint8_t crcCalc = CRC_Calculate((uint8_t*)response, response->Count+1);
	uint8_t crcReq  = response->Payload[response->Count-1];
	if(crcCalc != crcReq) return;//если CRC не совпадает то выходим.
	//-----------------------------
	I2cProtocol.timeOut = 0; //Сброс таймаута.
	ledFlag = 1;		 	 //Индикация приема пакета.
	//Разбор пришедшего пакета
	switch(response->CmdCode){
		//------------------
		case(cmdGetMillisCount):
			MCUc7Data.msCount = *(uint32_t*)&response->Payload[0];
		break;
		//------------------
		case(cmdGetEncoderCode):
			MCUc7Data.EncoderCode = *(uint32_t *)&response->Payload[2];
		break;
		//------------------
		case(cmdGetEncoderAngle):
			MCUc7Data.EncoderAngle = *(uint32_t *)&response->Payload[2];
		break;
		//------------------
		case(cmdGetTemperature):
			if(response->Payload[3] == 1)	  // Датчик 1
			{
				MCUc7Data.TemperatureSense1  = (uint32_t)( response->Payload[0] << 24); //знак
				MCUc7Data.TemperatureSense1 |= (uint32_t)((response->Payload[1] << 8) | //темперетура
														   response->Payload[2]);		//
			}
			else if(response->Payload[3] == 2)// Датчик 2
			{
				MCUc7Data.TemperatureSense2  = (uint32_t)( response->Payload[0] << 24); //знак
				MCUc7Data.TemperatureSense2 |= (uint32_t)((response->Payload[1] << 8) | //темперетура
														   response->Payload[2]);		//
			}
		break;
		//------------------
		case(cmdGetSystemCtrlReg):
			*(uint32_t*)&MCUc7Data.SysCtrlReg = *(uint32_t *)&response->Payload[0];
		break;
		//------------------
		case(cmdGetSupplyVoltage):
			MCUc7Data.SupplyVoltageVal = *(uint32_t *)&response->Payload[0];
		break;
		//------------------
		case(cmdGetSenseState):
			MCUc7Data.Sense = *(uint32_t *)&response->Payload[0];
		break;
		//------------------
		case(cmdGetResetCount):
			MCUc7Data.I2cResetCount = *(uint32_t *)&response->Payload[0];
		break;
		//------------------
		default:
		break;
		//------------------
	}
}
//************************************************************
static void I2cTxParsing(void){

}
//*******************************************************************************************
//*******************************************************************************************
void PROTOCOL_MASTER_I2C_Init(void){

	//Отладка I2C по прерываниям.
//	static uint8_t i2cBuf[3] = {1, 2, 3};
//	I2C_IT_Init(I2C2, 0);
//	I2C_IT_StartTx(I2C1, SSD1306_I2C_ADDR, 0x55, i2cBuf, 3);

	//Отладка I2C+DMA.
	//I2C_DMA_Init(I2C1, I2C_GPIO_NOREMAP);

	//Вопрос - Нужно ли делать работу с ДМА через контекст(т.е. через структуру)??
	//Не везде этот способу удобен. Нужно подумать.
	I2cProtocol.i2c 	  = I2C1;
	I2cProtocol.gpioRemap = I2C_GPIO_NOREMAP;
	I2cProtocol.slaveAddr = MCUv7_I2C_ADDR;
	I2cProtocol.i2cSlaveRxCpltCallback = I2cRxParsing;
	I2cProtocol.i2cSlaveTxCpltCallback = I2cTxParsing;
	I2C_DMA_Init(&I2cProtocol);
}
//************************************************************
void PROTOCOL_MASTER_I2C_RequestToMCU(void){

	static uint32_t cyclCount = cmdGetMillisCount;
	static uint32_t flag = 0;
	MCU_Request_t   *request  = (MCU_Request_t *)I2cProtocol.pTxBuf; //I2cDma.pTxBuf;
	//-----------------------------
	//Индикация передачи
	//LedPC13Toggel();
	switch(cyclCount){
		//------------------
		case(cmdGetMillisCount):
			request->CmdCode = cmdGetMillisCount;	//
			request->Count   = 1;					//кол-во байтов в запросе
			responseSize	 = 7;					//сколько байт вычитываем(Count+Cmd+Data(uint32)+CRC)

			cyclCount = cmdGetEncoderAngle;
		break;
		//------------------
		case(cmdGetEncoderAngle):
			request->CmdCode = cmdGetEncoderAngle;//
			request->Count   = 1;				  //кол-во байтов в запросе
			responseSize	 = 17;				  //сколько байт вычитываем(Count+Cmd+Data+CRC)

			cyclCount = cmdGetTemperature;
		break;
		//------------------
		case(cmdGetTemperature):
			request->CmdCode = cmdGetTemperature; //
			request->Count   = 2;				  //кол-во байтов в запросе

			//sensor_number
			if(flag) request->Payload[0] = 1;
			else	 request->Payload[0] = 2;
			flag ^= 1;

			responseSize = 7;					//сколько байт вычитываем(Count+Cmd+Data+CRC)

			cyclCount = cmdGetSupplyVoltage;
		break;
		//------------------
		case(cmdGetSupplyVoltage):
			request->CmdCode = cmdGetSupplyVoltage;	//
			request->Count   = 1;					//
			responseSize	 = 7;					//сколько байт вычитываем(Count+Cmd+Data(uint32)+CRC)

			cyclCount = cmdGetSenseState;
		break;
		//------------------
		case(cmdGetSenseState):
			request->CmdCode = cmdGetSenseState;	//
			request->Count   = 1;					//
			responseSize	 = 7;					//сколько байт вычитываем(Count+Cmd+Data(uint32)+CRC)

			cyclCount = cmdGetResetCount;
		break;
		//------------------
		case(cmdGetResetCount):
			request->CmdCode = cmdGetResetCount;	//
			request->Count   = 1;					//
			responseSize	 = 7;					//сколько байт вычитываем(Count+Cmd+Data(uint32)+CRC)

			cyclCount = cmdGetSystemCtrlReg;
		break;
		//------------------
		case(cmdGetSystemCtrlReg):
			request->CmdCode = cmdGetSystemCtrlReg;	//
			request->Count   = 1;					//кол-во байтов в запросе
			responseSize	 = 7;					//сколько байт вычитываем
													//(Count+Cmd+Data(uint32)+CRC)
			cyclCount = cmdGetMillisCount;
		break;
		//------------------
		default:
			cyclCount = cmdGetMillisCount;
			return;
		break;
		//------------------
	}
	//-----------------------------------------
	//Расчет CRC
	request->Payload[request->Count-1] = CRC_Calculate((uint8_t*)request, request->Count+1);
	//-----------------------------------------
	//Перадача команды в MCUv7
	uint32_t err = I2C_StartAndSendDeviceAddr(MCUv7_I2C, MCUv7_I2C_ADDR|I2C_MODE_WRITE);
		 if(err == I2C_ERR_ADDR) return;//Если нет Ack то выходим.
	else if(err == I2C_ERR_START)		//Если ошибка формирования старт последовательности
	{
		I2C_DMA_Init(&I2cProtocol); //Повторная инициализация I2C.
		return;
	}
	I2C_SendDataWithoutStop(MCUv7_I2C, (uint8_t*)request, request->Count+2);
	//-----------------------------------------
	//Чтение ответа на команду от MCUv7 с помощью DMA.
	I2cProtocol.rxBufSize = responseSize;
	if(I2C_DMA_Read(&I2cProtocol) == I2C_DMA_NAC)//Если ошибка при чтении ответа
	{
		for(uint32_t i = 0; i < responseSize; i++) *(I2cProtocol.pRxBuf+i) = 0;//Очистка буфера.
		I2C_DMA_Init(&I2cProtocol);
	}
}
//****************************************************
void PROTOCOL_MASTER_I2C_SendCmdToMCU(MCU_Request_t *cmd){

	uint32_t errCount = 0;
	//-----------------------------
	//Расчет CRC
	cmd->Payload[cmd->Count-1] = CRC_Calculate((uint8_t*)cmd, cmd->Count+1);
	//Перадача команды в MCUv7. Пытаемся передать адрес 3 раза.
	while(I2C_StartAndSendDeviceAddr(I2cProtocol.i2c, (uint8_t)(I2cProtocol.slaveAddr|I2C_MODE_WRITE)) != I2C_OK)
	{
		if(++errCount >= 3)
		{
			PROTOCOL_MASTER_I2C_Init();//Повторная инициализация I2C.
			return;
		}
	}
	I2C_SendDataWithoutStop(I2cProtocol.i2c, (uint8_t*)cmd, cmd->Count+2);
	I2C_Stop(I2cProtocol.i2c);
	//-----------------------------------------
	//Блокирующее чтение ответа на команду от MCUv7.
//	I2C_StartAndSendDeviceAddr(MCUv7_I2C, MCUv7_I2C_ADDR|I2C_MODE_READ);
//	I2C_ReadData(I2cProtocol.i2c, I2cProtocol.pTxBuf, sizeResp);
}
//****************************************************
//команда установки передаточного числа редуктора
void PROTOCOL_MASTER_I2C_SetReducerRate(uint8_t rate){

	MCU_Request_t cmd;
	//-----------------------------
	cmd.CmdCode = cmdSetReducerRate;//команда
	cmd.Count   = 2;				//Размер блока данных команды в байтах
	*(uint8_t*)&cmd.Payload = rate;	//передаточное число редуктора
	PROTOCOL_MASTER_I2C_SendCmdToMCU(&cmd);
}
//****************************************************
//команда установки Времени ускорения
void PROTOCOL_MASTER_I2C_SetAccelerationTime(uint32_t accelTime){

	MCU_Request_t cmd;
	//-----------------------------
	cmd.CmdCode = cmdSetAccelerationTime;//команда
	cmd.Count   = 5;				   	 //Размер блока данных команды в байтах
	*(uint32_t*)&cmd.Payload = accelTime;//время разгона в мс.
	PROTOCOL_MASTER_I2C_SendCmdToMCU(&cmd);
}
//****************************************************
//команда установки Скорости вращения.
void PROTOCOL_MASTER_I2C_SetMaxVelocity(uint32_t maxVel){

	MCU_Request_t cmd;
	//-----------------------------
	cmd.CmdCode = cmdSetMaxVelocity;   //команда
	cmd.Count   = 5;				   //Размер блока данных команды в байтах
	*(uint32_t*)&cmd.Payload = maxVel; //скрость в RPM
	PROTOCOL_MASTER_I2C_SendCmdToMCU(&cmd);
}
//****************************************************
//команда вкл./откл. моментом на валу ШД
void PROTOCOL_MASTER_I2C_MotorTorqueCtrl(uint8_t control){

	MCU_Request_t cmd;
	//-----------------------------
	cmd.CmdCode = cmdMotorTorqueCtrl; //команда
	cmd.Count   = 2;				  //Размер блока данных команды в байтах
	*(uint8_t*)&cmd.Payload = control;//вкл. момент
	PROTOCOL_MASTER_I2C_SendCmdToMCU(&cmd);
}
//****************************************************
//команда установки На какой угол повернуться.
void PROTOCOL_MASTER_I2C_SetTargetPosition(int32_t angle){

	MCU_Request_t cmd;
	//-----------------------------
	cmd.CmdCode = cmdSetTargetPosition; //команда
	cmd.Count   = 5;				    //Размер блока данных команды в байтах
	*(int32_t*)&cmd.Payload = angle;
	PROTOCOL_MASTER_I2C_SendCmdToMCU(&cmd);
}
//****************************************************
uint32_t PROTOCOL_MASTER_I2C_GetI2cNacCount(void){

	return I2C_Master_GetNacCount(I2cProtocol.i2c);
}
//****************************************************
MCUv7_Data_t* PROTOCOL_MASTER_I2C_GetDataMCU(void){

	return &MCUc7Data;
}
//**********************************************************
uint32_t PROTOCOL_MASTER_I2C_DMAState(void){

	return I2cProtocol.DMAState;
}
//**********************************************************
void PROTOCOL_MASTER_I2C_IncTimeoutAndReset(void){

	//-----------------------------------------
	//Счетсик timeOut сбрасывается в I2cRxParsing при совпадении CRC.
	I2cProtocol.timeOut++;
	if(I2cProtocol.timeOut >= PROTOCOL_I2C_REQUEST_TIMEOUT_mS)
	{
		I2cProtocol.timeOut = 0;
		//I2cProtocol.resetCount++;
		//I2C_IT_Init(&I2cWire);
		//I2C_DMA_Init(&I2cWire);
		PROTOCOL_MASTER_I2C_Init();//Повторная инициализация I2C.
		LedPC13Toggel();//Индикация отсутствия обмена.
	}
	//-----------------------------------------
	//Индикация обмена. Мигаем светодиодом.
	static uint32_t ledCount = 0;
	if(ledFlag)
	{
		if(++ledCount >= 50)
		{
			ledCount = 0;
			ledFlag  = 0;
			LedPC13Toggel();
		}
	}
	//-----------------------------------------
}
//*******************************************************************************************
//*******************************************************************************************

