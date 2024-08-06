/*
 * SPI.c
 *
 *  Created on: Jul 26, 2024
 *      Author: Sonbe
 */

#include "SPI.h"

/****
 * This function Init SPI1
 * PA4 is the SS Pin
 * PA5 is the CLK Pin
 * PA6 is the MISO Pin
 * PA7 is the MOSI Pin
 *
 */
void SON_SPI1_Init()
{
	/*
	 * Config PA5, PA6, PA7 Pin are in the alternate function mode and alternate function 5
	 * Config PA4 Pin is in the output mode
	 *
	 */
	__HAL_RCC_GPIOA_CLK_ENABLE();
	SON_GPIOA->MODER &= ~(0xff << 8);
	SON_GPIOA->MODER |= (0x02 << 14) | (0x02 << 12) | (0x02 << 10) | (0x01 << 8);
	SON_GPIOA->AFRL &= ~(0x0fff << 20);
	SON_GPIOA->AFRL |= (0x0555 << 20);

	//PA4 is in output put-pull mode
	SON_GPIOA->OTYPER &= ~(0x01 << 4);

	__HAL_RCC_SPI1_CLK_ENABLE();

	// Fpclk/16
	SON_SPI1->CR1 &= ~(0x07 << 3);
	SON_SPI1->CR1 |= (0x03 << 3);

	//CPOL = 1 and CPHA = 1
	SON_SPI1->CR1 |= (0x03 << 0);

	//DFF = 0 : 8 bit data frame
	SON_SPI1->CR1 &= ~(0x01 << 11);

	// MSB First
	SON_SPI1->CR1 &= ~(0x01 << 7);
	SON_SPI1->CR1 |= (0x01 << 7);

	//Software slave management
	SON_SPI1->CR1 |= (0x03 <<8);

	//master mode and peripheral enabled
	SON_SPI1->CR1 |= (0x01 << 2) | (0x01 << 6);
}


void SON_SPI1_Transmit_Data(uint8_t* data, uint16_t size)
{
	for(int i = 0; i < size ; i++)
	{
		// Wait for TXE bit is set->This will indicate that the tx buffer is empty
		while(((SON_SPI1->SR >> 1) & 0x01) != 1);
		SON_SPI1->DR = data[i];
	}
	// Wait for TXE bit is set->This will indicate that the tx buffer is empty
	while(((SON_SPI1->SR >> 1) & 0x01) != 1);
	// wait for BSY bit is reset->this will indicate that spi is not busy in communication
	while(((SON_SPI1->SR >> 7) & 0x01) == 1);

	//Clear OverRun Flag by read the DR register and the SR register
	uint32_t temp = SON_SPI1->DR;
	temp = SON_SPI1->SR;
	temp = temp;   // this action doesn't need to do, but I do it because i want to clear the warning: variable 'temp' set but not used
}

void SON_SPI1_Receive_Data(uint8_t* data, uint16_t size)
{
	// wait for BSY bit is reset->this will indicate that spi is not busy in communication
	while(((SON_SPI1->SR >> 7) & 0x01) == 1);
	for(int i =0; i < size ; i++)
	{
		// Wait for TXE bit is set->This will indicate that the tx buffer is empty
		while(((SON_SPI1->SR >> 1) & 0x01) != 1);
		SON_SPI1->DR = 0; // Send Dummy data


		// wait for RXNE bit is reset->this will indicate that there is data to read
		while(((SON_SPI1->SR >> 0) & 0x01) == 1);
		data[i] = SON_SPI1->DR;
	}

	while(((SON_SPI1->SR >> 7) & 1) == 1);// wait for BSY bit is reset->this will indicate that spi is not busy in communication
}



