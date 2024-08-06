#include"GPIO.h"

void GPIO_Init()
{
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
}

void SON_GPIO_Initialize(SON_GPIO_Typedef* GPIOx, SON_GPIO_Pin_t GPIO_Pin, SON_GPIO_Mode_t GPIO_Mode)
{
	GPIOx->MODER &= ~(0x03 << (GPIO_Pin * 2));
	if(GPIO_Mode <= SON_GPIO_INPUT_PULL_DOWN)
	{
		GPIOx->MODER |= (uint32_t)(0x0 << (GPIO_Pin * 2));
		GPIOx->PUPDR &= ~(0x03 << (GPIO_Pin * 2));
		GPIOx->PUPDR |= (uint32_t)((GPIO_Mode - SON_GPIO_INPUT_FLOATING) << (GPIO_Pin * 2));
	}
	else if(GPIO_Mode <= SON_GPIO_OUTPUT_OPEN_DRAIN)
	{
		GPIOx->MODER |= (uint32_t)(0x01 << (GPIO_Pin * 2));
		GPIOx->OTYPER &= ~(0x01 << GPIO_Pin);
		GPIOx->OTYPER |= (uint32_t)((GPIO_Mode - SON_GPIO_OUTPUT_PUSH_PULL) << GPIO_Pin);
	}
	else
	{
		//Something write later
	}
}

void SON_GPIO_WritePin(SON_GPIO_Typedef* GPIOx, SON_GPIO_Pin_t GPIO_Pin, SON_GPIO_Pin_State_t GPIO_State)
{
	if(GPIO_State == SON_GPIO_Pin_Reset)
	{
		GPIOx->BSRR |= (uint32_t)(0x01 << (GPIO_Pin + 16));
	}
	else if(GPIO_State == SON_GPIO_Pin_Set)
	{
		GPIOx->BSRR |= (uint32_t)(0x01 << GPIO_Pin);
	}
}

SON_GPIO_Pin_State_t SON_GPIO_ReadPin(SON_GPIO_Typedef* GPIOx, SON_GPIO_Pin_t GPIO_Pin)
{
	return ((GPIOx->IDR >> GPIO_Pin) & 0x01);
}
