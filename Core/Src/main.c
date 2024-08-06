/*
 * main.c
 *
 *  Created on: Aug 2, 2024
 *      Author: Sonbe
 */


#include "register.h"
#include "GPIO.h"
#include "delay.h"
#include "RCC.h"
#include "GPIO_interrupt.h"

void ADC_Init()
{
	__HAL_RCC_ADC1_CLK_ENABLE();

}

int main()
{
	SON_RCC_SysClockConfig_PLL_HSE();

	SON_Delay_Init(84000000);

	//GPIOC clock enable
	SON_RCC->AHB1ENR |= (0x01 << 2);
	SON_GPIO_Initialize(SON_GPIOC, SON_GPIO_Pin_13, SON_GPIO_OUTPUT_PUSH_PULL);

	while(1)
	{
		SON_GPIOC->ODR ^= (1 << 13);
		SON_Delay(1000);
	}
}

