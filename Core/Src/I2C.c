/*
 * I2C.c
 *
 *  Created on: Jul 28, 2024
 *      Author: Sonbe
 */

#include "I2C.h"
/*
 * This funtion Init I2C1
 * PB6 is the SCL Pin
 * PB7 is the SDA Pin
 */
void SON_I2C1_Master_Init()
{
	__HAL_RCC_I2C1_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();

	//pull-up register for PB6 and PB7
	SON_GPIOB->PUPDR &= ~(0x0f << 12);
	SON_GPIOB->PUPDR |= (0x01 << 12) | (0x01 << 14);

	//open-drain register for PB6 and PB7
	SON_GPIOB->OTYPER |= (0x01 << 6) | (0x01 << 7);

	//High speed for PB6 and PB7
	SON_GPIOB->OSPEEDR |= (0x03 << 12) | (0x03 <<14);

	//Config PB6 and PB7 are in the alternate function mode and alternate funtion 4
	SON_GPIOB->MODER &= ~((0x03 << 12) | (0x03 << 14));
	SON_GPIOB->MODER |= (0x02 << 12) | (0x02 << 14);
	SON_GPIOB->AFRL &= ~(0xff << 24);
	SON_GPIOB->AFRL |= (0x44 << 24);

	//wait for no communication on the bus(BUSY bit = 0)
	while(((SON_I2C1->SR2 >> 1) & 0x01) == 1);

	//Reset the I2C
	SON_I2C1->CR1 |= (0x01 << 15);
	SON_I2C1->CR1 &= ~(0x01 << 15);

	// Program the peripheral input clock in I2C_CR2 Register in order to generate correct timings
	SON_I2C1->CR2 &= ~(0x3f); // reset 6 bit 5->0
	SON_I2C1->CR2 |= 42;

	// Configure the clock control registers
	SON_I2C1->CCR &= ~(0x01 << 15); // Standard mode
	//i want the frequency of I2C is 100KHZ so Thigh= Tlow = 1/(2* 100k) = 5 * 10^-6
	//FREQR = 42Mhz -> TPCLK1 = 1/42M
	//->CCR = Thigh / TPCLK1 = 210
	SON_I2C1->CCR &= ~(0xfff << 0); //Reset 12 bit 11->0
	SON_I2C1->CCR |= (210 << 0);

	//Configure the rise time register
	SON_I2C1->TRISE &= ~(0x3f << 0); //reset 6 bit 5-> 0
	SON_I2C1->TRISE |= (43); //TRISE = (1000* 10^-9)/(1:42*10^6) + 1

	//Program the I2C_CR1 register to enable the peripheral
	SON_I2C1->CR1 |= (0x01 << 0);
}

void SON_I2C_Master_Transmit(uint8_t slave_address, uint8_t* data, uint16_t size)
{
	uint8_t address = (slave_address << 1);
	address &= ~(0x01 << 0); //Transmit

	//wait for no communication on the bus(BUSY bit = 0)
	while(((SON_I2C1->SR2 >> 1) & 0x01) == 1);

	SON_I2C1->CR1 |= (0x01 << 8);
	//Wait for start bit is sent
	while((SON_I2C1->SR1 & 0x01) != 1);

	SON_I2C1->DR = (uint32_t)address;

	//Wait for ADDR bit is set -> this will indicate address is transmited to the slave
	while(((SON_I2C1->SR1 >> 1) & 0x01) != 1);
	uint32_t temp = SON_I2C1->SR1 | SON_I2C1->SR2; // read SR1 register followed by a read of the SR2 register to clear ADDR bit
	temp = temp; // clear the warning temp is not used :))

	for(int i = 0; i < size; i++)
	{
		//Wait for data register empty
		while(((SON_I2C1->SR1 >> 7) & 0x01 ) != 1);
		SON_I2C1->DR = (volatile uint32_t)data[i];
	}
	//Wait for data register empty
	while(((SON_I2C1->SR1 >> 7) & 0x01 ) != 1);
	//Wait for data transmit finished (BTF is set)
	while(((SON_I2C1->SR1 >> 2) & 0x01 ) != 1);

	SON_I2C1->CR1 |= (0x01 << 9); //Stop I2C
}

void SON_I2C_Master_Receive(uint8_t slave_address, uint8_t* data, uint16_t size)
{
	if(size == 1)
	{
		uint8_t address = slave_address << 1;
		address |= 0x01; //receive

		//wait for no communication on the bus(BUSY bit = 0)
		while(((SON_I2C1->SR2 >> 1) & 0x01) == 1);

		SON_I2C1->CR1 |= (0x01 << 10);
		//Generate a Start condition
		SON_I2C1->CR1 |= (0x01 << 8);

		//Wait for start bit is sent
		while((SON_I2C1->SR1 & 0x01) != 1);

		SON_I2C1->DR = (uint32_t)address;

		//Wait for ADDR bit is set -> this will indicate address is transmited to the slave
		while(((SON_I2C1->SR1 >> 1) & 0x01) != 1);

		SON_I2C1->CR1 &= ~(0x01 << 10); //Clear the ACK bit
		uint32_t temp = SON_I2C1->SR1 | SON_I2C1->SR2; // read SR1 register followed by a read of the SR2 register to clear ADDR bit
		temp = temp; // clear the warning temp is not used :))

		SON_I2C1->CR1 |= (0x01 << 9); //Stop I2C

		while(((SON_I2C1->SR1 >> 6) & 0x01) != 1); //wait for RxNE bit is set

		data[0] = SON_I2C1->DR; //Read data receive
	}
	else if(size > 1)
	{
		uint8_t address = slave_address << 1;
		address |= 0x01; //receive

		//wait for no communication on the bus(BUSY bit = 0)
		while(((SON_I2C1->SR2 >> 1) & 0x01) == 1);

		SON_I2C1->CR1 |= (0x01 << 10); // Set the ACK bit to acknowledge the data received

		//Generate a Start condition
		SON_I2C1->CR1 |= (0x01 << 8);

		//Wait for start bit is sent
		while((SON_I2C1->SR1 & 0x01) != 1);

		SON_I2C1->DR = (uint32_t)address;

		//Wait for ADDR bit is set -> this will indicate address is transmited to the slave
		while(((SON_I2C1->SR1 >> 1) & 0x01) != 1);
		uint32_t temp = SON_I2C1->SR1 | SON_I2C1->SR2; // read SR1 register followed by a read of the SR2 register to clear ADDR bit
		(void)temp;
		for(int i =0; i < size -1; i++)
		{
			while(((SON_I2C1->SR1 >> 6) & 0x01) != 1); //wait for RxNE bit is set
			data[i] = (uint8_t)SON_I2C1->DR;

			SON_I2C1->CR1 |= (0x01 << 10); // Set the ACK bit to acknowledge the dat received
		}

		SON_I2C1->CR1 &= ~(0x01 << 10); //Clear the ACK bit
		SON_I2C1->CR1 |= (0x01 << 9); //Stop I2C

		while(((SON_I2C1->SR1 >> 6) & 0x01) != 1); //wait for RxNE bit is set

		data[size - 1] = (uint8_t)SON_I2C1->DR;
	}
}


