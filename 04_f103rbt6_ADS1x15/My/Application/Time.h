/*
 * Time.h
 *
 *  Created on: 22 авг. 2022 г.
 *      Author: belyaev
 */

#ifndef TIME_H
#define TIME_H
//*******************************************************************************************
//*******************************************************************************************

#include "main.h"

//*******************************************************************************************
//*******************************************************************************************
typedef struct{
	uint32_t hour;
	uint32_t min;
	uint32_t sec;
	uint32_t mSec;
}Time_t;
//---------------------------


//*******************************************************************************************
//*******************************************************************************************
void TIME_Calculation(Time_t *time, uint32_t mScount);

//*******************************************************************************************
//*******************************************************************************************
#endif /* APPLICATION_TIME_H_ */




