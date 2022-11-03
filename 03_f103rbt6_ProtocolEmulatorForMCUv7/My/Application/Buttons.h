/*
 * Buttons.h
 *
 *  Created on: 3 нояб. 2022 г.
 *      Author: belyaev
 */

#ifndef APPLICATION_BUTTONS_H_
#define APPLICATION_BUTTONS_H_
//*******************************************************************************************
//*******************************************************************************************

#include "main.h"

//*******************************************************************************************
//*******************************************************************************************


//**********************************
typedef struct{
	//-----
	uint32_t instant;		//
	uint32_t isPress;		//
	uint32_t isRelease;		//
	uint32_t isToggle;		//
	//-----
	uint32_t f_ready :1;	//
	uint32_t :31;
	//-----
}ButtonStates_t;
//**********************************
typedef enum
{
	EncoderButton = 0,
//	ALG2but,
//	ALG3but,
//	ALG4but,
//	ALG5but,
//	ALG6but,
//	ALG7but,
//	ALG8but,
//	NotBut ,
//    PUSKbut,
//    RESETbut,
//	STARTbut,
//	STOPbut,
//	ZUMMERbut,
//	TESTbut,
//	AllButtons = 0xFFFF,
}ButtonsEnum_t;
//*******************************************************************************************
//*******************************************************************************************
void 	BUTTONS_Init(void);
uint8_t BUTTONS_CheckLoop(void);

uint32_t BUTTONS_Instant  (ButtonsEnum_t but);
uint32_t BUTTONS_IsPress  (ButtonsEnum_t but);
uint32_t BUTTONS_IsRelease(ButtonsEnum_t but);
uint32_t BUTTONS_IsToggle (ButtonsEnum_t but);
void     BUTTONS_ClrToggle(ButtonsEnum_t but);

//*******************************************************************************************
//*******************************************************************************************
#endif /* APPLICATION_BUTTONS_H_ */





