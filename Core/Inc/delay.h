#ifndef DELAY_H
#define DELAY_H

#include "register.h"
void SON_Delay_Init(uint32_t frequency_system_timer);
void SON_Delay(uint32_t ms);
uint32_t SON_GetTick();
#endif
