/*
 * lowPowerMode.h
 *
 *  Created on: Aug 6, 2024
 *      Author: Admin
 */

#ifndef SRC_LOWPOWERMODE_H_
#define SRC_LOWPOWERMODE_H_

#include "register.h"
//lưu tạm thời thôi
void stop_mode_WFI()
{
	uint32_t *SCR = (uint32_t*)0xe000ed10;
	__asm("WFI");
	*SCR |=(0x01 << 2);
}

#endif /* SRC_LOWPOWERMODE_H_ */
