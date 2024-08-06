#ifndef GPIO_INTERRUPT_H
#define GPIO_INTERRUPT_H

#include "register.h"

SON_STATUS_t SON_EXTI_GPIO_Enable(SON_GPIO_t GPIOx, SON_GPIO_Pin_t GPIO_Pin,
		SON_Trigger_t Trigger, uint8_t Priority);
SON_STATUS_t SON_EXTI_GPIO_Unenable(SON_GPIO_t GPIOx,SON_GPIO_Pin_t GPIO_Pin);

#endif

