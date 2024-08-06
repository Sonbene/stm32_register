/*
 * Timer.c
 *
 *  Created on: Jul 30, 2024
 *      Author: Admin
 */

#ifndef INC_TIMER_C_
#define INC_TIMER_C_

#include "register.h"

void SON_TIM1_Counter_Mode_Init(uint16_t prescaler, uint16_t autoReload);
void SON_TIM1_Delay(uint32_t ms);
void SON_TIM1_PWM_Mode(void);
void SON_TIM1_PWM1_Value(uint16_t value);

#endif /* INC_TIMER_C_ */
