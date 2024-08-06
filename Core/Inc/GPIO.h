
#ifndef GPIO_H
#define GPIO_H

#include "register.h"

void GPIO_Init(void);
void SON_GPIO_Initialize(SON_GPIO_Typedef* GPIOx, SON_GPIO_Pin_t GPIO_Pin, SON_GPIO_Mode_t GPIO_Mode);
void SON_GPIO_WritePin(SON_GPIO_Typedef* GPIOx, SON_GPIO_Pin_t GPIO_Pin, SON_GPIO_Pin_State_t GPIO_State);
SON_GPIO_Pin_State_t SON_GPIO_ReadPin(SON_GPIO_Typedef* GPIOx, SON_GPIO_Pin_t GPIO_Pin);

#endif
