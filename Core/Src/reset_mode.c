/*
 * reset_mode.h
 *
 *  Created on: Aug 6, 2024
 *      Author: Admin
 */

#include "reset_mode.h"

void SON_IWDG_Init()
{
	SON_IWDG->KR = 0x5555;
	SON_IWDG->PR = 0x03;
	SON_IWDG->RLR = 3999;
	SON_IWDG->KR = 0xAAAA;
	SON_IWDG->KR = 0xCCCC;
}


