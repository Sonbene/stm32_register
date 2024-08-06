/*
 * RCC.c
 *
 *  Created on: Aug 5, 2024
 *      Author: Sonbe
 */
#include "RCC.h"

//25M
void SON_RCC_SysClockConfig_HSE()
{
	//enable HSE
	SON_RCC->CR |= (1<< 16);

	//wait HSE is ready
	while(((SON_RCC->CR >> 17) & 0x01) == 0);

	//Set HSE as system clock
	SON_RCC->CFGR |= (0x01 << 0);

	//system clock not divided
	SON_RCC->CFGR &= ~(0x0f << 4);

	//System configuration controller clock enable
	SON_RCC->APB2ENR |= (0x01 << 14);
}

//84M
void SON_RCC_SysClockConfig_PLL_HSE()
{
	//enable HSE
	SON_RCC->CR |= (1<< 16);

	//wait HSE is ready
	while(((SON_RCC->CR >> 17) & 0x01) == 0);

	/***HSE = 25M -> M(/25)-> N(*168)->P(/2)***/
	//M(/25)
	SON_RCC->PLLCFGR &= ~(0x3f << 0);
	SON_RCC->PLLCFGR |= (25 << 0);

	//N(*168)
	SON_RCC->PLLCFGR &= ~(0x1ff << 6);
	SON_RCC->PLLCFGR |= (168 << 6);

	//P(/2)
	SON_RCC->PLLCFGR &= ~(0x03 << 16);

	//HSE oscillator clock selected as PLL and PLLI2S clock entry
	SON_RCC->PLLCFGR |= (0x01 << 22);

	//PLL ON
	SON_RCC->CR |= (0x01 << 24);
	//Wait PLL is locked
	while(((SON_RCC->CR >> 25) & 0x01 ) == 0);

    // Adjust flash latency (important for higher frequencies)
	SON_FLASH->ACR |= 0x05;

	//PLL selected as system clock
	SON_RCC->CFGR &= ~(0x03 << 0);
	SON_RCC->CFGR |= (0x02 << 0);

	// Configure prescalers
	SON_RCC->CFGR &= ~(0x0F << 4);  // AHB prescaler = 1
	SON_RCC->CFGR &= ~(0x07 << 10); // APB1 prescaler = 4 (42 MHz)
	SON_RCC->CFGR |= (0x05 << 10);
	SON_RCC->CFGR &= ~(0x07 << 13); // APB2 prescaler = 2 (84 MHz)
	SON_RCC->CFGR |= (0x04 << 13);

	//System configuration controller clock enable
	SON_RCC->APB2ENR |= (0x01 << 14);
}

//84M
void SON_RCC_SysClockConfig_PLL_HSI()
{
	//HSI ON
	SON_RCC->CR |= (0x01 << 0);

	//Wait for HSI On
	while(((SON_RCC->CR >> 0) & 0x01) ==0);


	/***HSE = 16M -> M(/8)-> N(*84)->P(/2)***/
	//M(/8)
	SON_RCC->PLLCFGR &= ~(0x3f << 0);
	SON_RCC->PLLCFGR |= (8 << 0);

	//N(*84)
	SON_RCC->PLLCFGR &= ~(0x1ff << 6);
	SON_RCC->PLLCFGR |= (84 << 6);

	//P(/2)
	SON_RCC->PLLCFGR &= ~(0x03 << 16);

	//HSI clock selected as PLL and PLLI2S clock entry
	SON_RCC->PLLCFGR &= ~(0x01 << 22);

	//PLL ON
	SON_RCC->CR |= (0x01 << 24);
	//Wait PLL is locked
	while(((SON_RCC->CR >> 25) & 0x01 ) == 0);

	// Adjust flash latency (important for higher frequencies)
	SON_FLASH->ACR |= 0x05;

	//PLL selected as system clock
	SON_RCC->CFGR &= ~(0x03 << 0);
	SON_RCC->CFGR |= (0x02 << 0);

	// Configure prescalers
	SON_RCC->CFGR &= ~(0x0F << 4);  // AHB prescaler = 1
	SON_RCC->CFGR &= ~(0x07 << 10); // APB1 prescaler = 4 (42 MHz)
	SON_RCC->CFGR |= (0x05 << 10);
	SON_RCC->CFGR &= ~(0x07 << 13); // APB2 prescaler = 2 (84 MHz)
	SON_RCC->CFGR |= (0x04 << 13);

	//System configuration controller clock enable
	SON_RCC->APB2ENR |= (0x01 << 14);
}

