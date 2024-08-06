/*
 * Timer2.c
 *
 *  Created on: Aug 1, 2024
 *      Author: Sonbe
 */


#include "Timer2.h"

void SON_TIM2_Init(uint16_t prescaler, uint32_t autoReload)
{
	__HAL_RCC_TIM2_CLK_ENABLE();

	//bit 3 -> 7 of CR1 register = 0
	SON_TIM2->CR1 &= ~(0x7f << 3);

	//Only overflow generates an update interrupt or DMA request if enabled
	SON_TIM2->CR1 |= (0x01 << 2);

	//UEV enabled
	SON_TIM2->CR1 &= ~(0x01 << 1);

	SON_TIM2->PSC = prescaler;

	SON_TIM2->ARR = autoReload;

	//Generate an update event
	SON_TIM2->EGR |= (0x01 << 0);

	//Counter Enable
	SON_TIM2->CR1 |= (0x01 << 0);
}

void SON_TIM2_InputCapture_Mode(void)
{
	__HAL_RCC_GPIOA_CLK_ENABLE();

	/***Config alternate function1 for PA0 (TIM2_CH1)***/

	SON_GPIOA->MODER &= ~(0x03 << 0);
	SON_GPIOA->MODER |= (0x02 << 0);

	SON_GPIOA->OSPEEDR |= (0x03 << 0);

	SON_GPIOA->AFRL &= ~(0x0f << 0);
	SON_GPIOA->AFRL |= (0x01 << 0);

	/***Config Input capture CH1-TI1 mode (rising)***/
	//Input, IC1 is mapped on TI1
	SON_TIM2->CCMR1 &= ~(0x03 << 0);
	SON_TIM2->CCMR1 |= (0x01 << 0);

	//No filter and f=fDTS(Tần số sau bộ chia thì phải)
	SON_TIM2->CCMR1 &= ~(0x0f << 4);

	//rising edge
	SON_TIM2->CCER &= ~((0x01 << 1) | (0x01 << 3));

	//IC1PSC = 00: capture is done each time an edge is detected on the capture input
	SON_TIM2->CCMR1 &= ~(0x03 << 2);

	/***Config Input capture CH2-TI1 mode (falling)***/
	//IC2 mapped on TI1
	SON_TIM2->CCMR1 &= ~(0x03 << 8);
	SON_TIM2->CCMR1 |= (0x02 << 8);

	//falling edge
	SON_TIM2->CCER |=(0x01 << 5);
	SON_TIM2->CCER &= ~(0x01 << 7);

	/***timer slave mode control - reset CNT when rising ***/
	//Filered Timer Input 1(TI1FP1)
	SON_TIM2->SMCR &= ~(0x07 << 4);
	SON_TIM2->SMCR |= (0x05 << 4);

	//Reset mode at rising edge
	SON_TIM2->SMCR &= ~(0x03 << 0);
	SON_TIM2->SMCR |= (0x04 << 0);

	//Capture enable
	SON_TIM2->CCER |= (0x01 << 0);
	SON_TIM2->CCER |= (0x01 << 4);

}

