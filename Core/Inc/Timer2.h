/*
 * Timer2.h
 *
 *  Created on: Aug 1, 2024
 *      Author: Sonbe
 */

#ifndef INC_TIMER2_H_
#define INC_TIMER2_H_

#include "register.h"

void SON_TIM2_Init(uint16_t prescaler, uint32_t autoReload);
void SON_TIM2_InputCapture_Mode(void);


#endif /* INC_TIMER2_H_ */
