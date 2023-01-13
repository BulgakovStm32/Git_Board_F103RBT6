/*
 * Blink.h
 *
 * Created on:
 *     Author:
 */
#include "Blink.h"
//*******************************************************************************************
//*******************************************************************************************

static volatile uint16_t blinkReg      = 0;
static volatile uint32_t blink_mSCount = 0;

//*******************************************************************************************
//*******************************************************************************************
//Процесс для мигания светодиодами.
void Blink_Loop(void){
	
	static uint16_t blinkCount = 0;
	//--------------------
	++blink_mSCount;
	++blinkCount;
	if((blinkCount % 50)   == 0) blinkReg ^= (1 << INTERVAL_50_mS);
	if((blinkCount % 100)  == 0) blinkReg ^= (1 << INTERVAL_100_mS);
	if((blinkCount % 250)  == 0) blinkReg ^= (1 << INTERVAL_250_mS);
	if((blinkCount % 500)  == 0) blinkReg ^= (1 << INTERVAL_500_mS);
	if((blinkCount % 1000) == 0)
	{
		blinkReg ^= (1 << INTERVAL_1000_mS);
		blinkCount = 0;
	}
}
//**********************************************************
uint32_t Blink(BlinkIntervalEnum_t interval){
	
	if(blinkReg & (1 << interval)) return 1;
	else						   return 0;
}
//**********************************************************
uint32_t Blink_SwitchOnTime(uint32_t period, uint32_t switch_on_time){

	static uint32_t mSCountOld = 0;
	static uint32_t flag       = 0;
	//-------------------
	if((blink_mSCount - mSCountOld) >= (flag ? (period - switch_on_time) : switch_on_time ))
	{
		mSCountOld = blink_mSCount;
		flag = !flag;
	}
	return flag;
}
//*******************************************************************************************
//*******************************************************************************************

