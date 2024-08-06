/*
 * Timer.h
 *
 *  Created on: Jul 30, 2024
 *      Author: Sonbe
 */

#include "Timer.h"

static uint32_t tick;

void SON_TIM1_Counter_Mode_Init(uint16_t prescaler, uint16_t autoReload)
{
	__HAL_RCC_TIM1_CLK_ENABLE();

	SON_TIM1->CR1 &= ~(0x03 << 8); //tDTS = tCK_INT

	SON_TIM1->CR1 &= ~(0x01 << 7); //timer ARR register is not buffered

	SON_TIM1->CR1 &= ~(0x03 << 5); //Edge-aligned mode

	SON_TIM1->CR1 &= ~(0x01 << 4); //Counter up

	SON_TIM1->CR1 &= ~(0x01 << 3); //Counter is not stopped at update event

	SON_TIM1->CR1 &= ~(0x01 << 1); //Update event is enable

	SON_TIM1->PSC = (uint32_t)prescaler;

	SON_TIM1->ARR = (uint32_t)autoReload;	   //Counter count from 0 to ARR value or ARR value to 0

	SON_TIM1->EGR |= (0x01 << 0);  // Generate an update event to reload the prescaler value immediately

	SON_TIM1->CR1 |= (0x01 << 0);  //Counter enable

	SON_TIM1->DIER |= (0x01 << 0);  //Update interrupt enable

	SON_NVIC->ISER[0] |= (0x01 << 25);	// enable interrupt of TIM1 update

	SON_NVIC->IPR[25] |= (0x01 << 4); //Priority = 1

}

//TEST PWM IN CHANNEL 1 PA8
void SON_TIM1_PWM_Mode()
{
    SON_GPIOA->MODER &= ~(0x03 << 16);
    SON_GPIOA->MODER |= (0x02 << 16);

    SON_GPIOA->OSPEEDR |= (0x03 << 16);

    SON_GPIOA->AFRH &= ~(0x0f << 0);
    SON_GPIOA->AFRH |= (0x01<< 0);

    // PWM1 mode on CH1
    SON_TIM1->CCMR1 &= ~(0x07 << 4);
    SON_TIM1->CCMR1 |= (0x06 << 4);

    // Output compare 1 preload enable
    SON_TIM1->CCMR1 |= (0x01 << 3);

    // CC1 channel is configured as output
    SON_TIM1->CCMR1 &= ~(0x03 << 0);

    // ARR register is buffered
    SON_TIM1->CR1 |= (0x01 << 7);

    // Generate an update event to reload the prescaler value immediately
    SON_TIM1->EGR |= (0x01 << 0);

    // OC1 active high
    SON_TIM1->CCER &= ~(0x01 << 1);

    // CC1E = 1 (enable output) ,
    SON_TIM1->CCER |= (0x01 << 0);

    //MOE = 1
    SON_TIM1->BDTR |= (0x01 << 15);
}


void SON_TIM1_PWM1_Value(uint16_t value)
{
	SON_TIM1->CCR1 = value;

}

weak_func void SON_TIM1_UPDATE_IRQHandler()
{

}


 void TIM1_UP_TIM10_IRQHandler()
{
	 if((SON_TIM1->SR & 0x01) == 1)
	 {
		 SON_TIM1_UPDATE_IRQHandler();
		 tick++;
		 SON_TIM1->SR &= ~(0x01 << 0); // delete update interrupt flag(UIF = 0)
	 }

}

void SON_TIM1_Delay(uint32_t ms)
{
	tick = 0;
	while(tick <= ms);
}


//
//void SON_TIM1_Delay_ms(uint32_t ms)
//{
//	for(int i = 0; i < ms ; i++)
//	{
//		SON_TIM1->CNT = 0;
//		while(SON_TIM1->CNT < 1000);
//	}
//}













