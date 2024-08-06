#include "UART.h"
/*
 *USART1:
 *if use GPIOA : the tx pin is PA9 and rx pin is PA10
 *if use GPIOB : the tx pin is PB6 and rx pin is PB7
 *if USART1 use APB2
 *USART2:
 *if use GPIOA : the tx pin is PA2 and rx pin is PA3
 *USART2 use APB1
 *USART6:
 *if use GPIOA : the tx pin is PA11 and rx pin is PA12
 *USART6 use APB2
 */
void SON_UART_Init(SON_USART_Typedef* SON_USARTx, SON_GPIO_t SON_GPIO_GPIOx,uint32_t baud_rate, uint32_t fclock)
{
	if(SON_USARTx == SON_USART1)
	{
		__HAL_RCC_USART1_CLK_ENABLE();
		if(SON_GPIO_GPIOx == SON_GPIO_GPIOA)
		{
			__HAL_RCC_GPIOA_CLK_ENABLE();
			SON_GPIOA->MODER &= ~(0x03 << 18) | ~(0x03 << 20);
			SON_GPIOA->MODER |= (0x02 << 18) | (0x02 << 20);
			SON_GPIOA->AFRH &= ~(0xFF << 4);
			SON_GPIOA->AFRH |= (0x77 << 4);
		}
		else if(SON_GPIO_GPIOx == SON_GPIO_GPIOB)
		{
			__HAL_RCC_GPIOB_CLK_ENABLE();
			SON_GPIOB->MODER &= ~(0x03 << 12) | ~(0x03 << 14);
			SON_GPIOB->MODER |= (0x02 << 12) | (0x02 << 14);
			SON_GPIOB->AFRL &= ~(0xFF << 24);
			SON_GPIOB->AFRL |= (0x77 << 24);
		}
	}
	else if(SON_USARTx == SON_USART2)
	{
		__HAL_RCC_USART2_CLK_ENABLE();
		if(SON_GPIO_GPIOx == SON_GPIO_GPIOA)
		{
			__HAL_RCC_GPIOA_CLK_ENABLE();
			SON_GPIOA->MODER &= ~(0x03 << 4) | ~(0x03 << 6);
			SON_GPIOA->MODER |= (0x02 << 4) | (0x02 << 6);
			SON_GPIOA->AFRL &= ~(0xFF << 8);
			SON_GPIOA->AFRL |= (0x77 << 8);
		}
	}
	else if(SON_USARTx == SON_USART6)
	{
		__HAL_RCC_USART6_CLK_ENABLE();
		if(SON_GPIO_GPIOx == SON_GPIO_GPIOA)
		{
			__HAL_RCC_GPIOA_CLK_ENABLE();
			SON_GPIOA->MODER &= ~(0x03 << 22) | ~(0x03 << 24);
			SON_GPIOA->MODER |= (0x02 << 22) | (0x02 << 24);
			SON_GPIOA->AFRH &= ~(0xFF << 12);
			SON_GPIOA->AFRH |= (0x88 << 12);
		}
	}
	else
	{
		return;
	}

	uint16_t DIV_mantissa = fclock/(16 * baud_rate);
	uint8_t DIV_fraction = (uint8_t)round((double)(fclock % (16 * baud_rate))/baud_rate);

	SON_USARTx->BRR &= ~(0xFFFF );
	SON_USARTx->BRR |= (DIV_mantissa << 4) | (DIV_fraction);

	SON_USARTx->CR1 |= (1 << 13) | (1 << 3) | (1 << 2);
}

SON_STATUS_t SON_UART_Transmit(SON_USART_Typedef* SON_USARTx, uint8_t* data, uint16_t size, uint32_t timeout)
{
	uint32_t time = SON_GetTick();
	for(uint16_t i = 0; i < size; i++)
	{
		while(((SON_USARTx->SR >> 7) & 1) == 0)
		{
			if(SON_GetTick() - time >= timeout)
			{
				return SON_TIMEOUT;
			}
		}
		SON_USARTx->DR = *data;
		while(((SON_USARTx->SR >> 6) & 1) == 0)
		{
			if(SON_GetTick() - time >= timeout)
			{
				return SON_TIMEOUT;
			}
		}
		data++;
	}
	return SON_OK;
}

SON_STATUS_t SON_UART_Receive(SON_USART_Typedef* SON_USARTx, uint8_t* data, uint16_t size, uint32_t timeout)
{
	uint32_t time = SON_GetTick();
	for(uint16_t i = 0; i < size; i++)
	{
		while(((SON_USARTx->SR >> 5) & 1) == 0)
		{
			if(SON_GetTick() - time >= timeout)
			{
				return SON_TIMEOUT;
			}
		}
		*data = SON_USARTx->SR;
		data++;
	}
	return SON_OK;
}

SON_STATUS_t SON_UART_Receive_IT(SON_USART_Typedef* SON_USARTx)
{
	IRQn_Type IRQ;
	if(SON_USARTx == SON_USART1)
	{
		IRQ = USART1_IRQn;
	}
	else if(SON_USARTx == SON_USART2)
	{
		IRQ = USART2_IRQn;
	}
	else if(SON_USARTx == SON_USART6)
	{
		IRQ = USART6_IRQn;
	}
	SON_USARTx->CR1 |= ( 1 << 5);
	SON_NVIC->ISER[IRQ/32] |= ( 1 << (IRQ %32));
	return SON_OK;
}

/*
 * USART1_Rx used stream 2 channel 4 in DMA2
 * USART6_Rx used Stream 1 channel 5 in DMA2
 * USART2_Rx used Stream 5 channel 4 in DMA1
 */
SON_STATUS_t SON_UART_Receive_DMA(SON_USART_Typedef* SON_USARTx, uint8_t* data, uint16_t size, SON_DMA_STATE_t SON_CIRCRULAR)
{
	SON_USARTx->CR3 |= (1 << 6);
	if(SON_USARTx == SON_USART1)
	{
		__HAL_RCC_DMA2_CLK_ENABLE();
		SON_DMA2->S4NDTR = size;
		SON_DMA2->S4PAR = (uint32_t)&SON_USARTx->DR;
		SON_DMA2->S4M0AR = (uint32_t)data;
		SON_DMA2->S4CR &= ~(0x07 << 25)|~( 1 << 10) |~( 1 << 8);
		SON_DMA2->S4CR |= (0x04 << 25) | ( 1 << 10) | ((SON_CIRCRULAR - SON_CIRCRULAR_DISABLE) << 8) | (0x03 << 3) | (1 << 0);

		SON_NVIC->ISER[SON_DMA2_Stream2_IRQn/32] |= (1 << SON_DMA2_Stream2_IRQn%32);
	}
	else if(SON_USARTx == SON_USART6)
	{
		__HAL_RCC_DMA2_CLK_ENABLE();
		SON_DMA2->S1NDTR = size;
		SON_DMA2->S1PAR = (uint32_t)&SON_USARTx->DR;
		SON_DMA2->S1M0AR = (uint32_t)data;
		SON_DMA2->S1CR &= ~(0x07 << 25) |~( 1 << 10) |~( 1 << 8);
		SON_DMA2->S1CR |= (0x05 << 25) | ( 1 << 10) | ((SON_CIRCRULAR - SON_CIRCRULAR_DISABLE) << 8) | (0x03 << 3) | (1 << 0);

		SON_NVIC->ISER[SON_DMA2_Stream1_IRQn/32] |= (1 << SON_DMA2_Stream1_IRQn%32);
	}
	else if(SON_USARTx == SON_USART2)
	{
		__HAL_RCC_DMA1_CLK_ENABLE();
		SON_DMA1->S5NDTR = size;
		SON_DMA1->S5PAR = (uint32_t)&SON_USARTx->DR;
		SON_DMA1->S5M0AR = (uint32_t)data;

		SON_DMA1->S5CR &= ~(0x07 << 25)|~( 1 << 10) |~( 1 << 8);
		SON_DMA1->S5CR |= (0x04 << 25) | ( 1 << 10) | ((SON_CIRCRULAR - SON_CIRCRULAR_DISABLE) << 8) | (0x03 << 3) | (1 << 0);

		SON_NVIC->ISER[SON_DMA1_Stream5_IRQn/32] |= (1 << SON_DMA1_Stream5_IRQn%32);
	}
	else
	{
		return SON_ERROR;
	}

	return SON_OK;
}

uint8_t SON_UART_Get_Data(SON_USART_Typedef* SON_USARTx)
{
	uint8_t data = SON_USARTx->DR;
	return data;
}

weak_func void SON_UART_Rx_Complete_IRQHandler(SON_USART_Typedef* SON_USARTx)
{

}


weak_func void SON_UART_Rx_Half_Complete_IRQHandler(SON_USART_Typedef* SON_USARTx)
{

}

void DMA1_Stream5_IRQHandler()
{
	if(((SON_DMA1->HISR >> 11) & 1 ) == 1)
	{
		SON_UART_Rx_Complete_IRQHandler(SON_USART2);
		SON_DMA1->HIFCR |= (1 << 11);
	}
	else if(((SON_DMA1->HISR >> 10) & 1 ) == 1)
	{
		SON_UART_Rx_Half_Complete_IRQHandler(SON_USART2);
		SON_DMA1->HIFCR |= (1 << 10);
	}
}

void DMA2_Stream1_IRQHandler()
{
	if(((SON_DMA2->LISR >> 11) & 1 ) == 1)
	{
		SON_UART_Rx_Complete_IRQHandler(SON_USART6);
		SON_DMA2->LIFCR |= (1 << 11);
	}
	else if(((SON_DMA2->LISR >> 10) & 1 ) == 1)
	{
		SON_UART_Rx_Half_Complete_IRQHandler(SON_USART6);
		SON_DMA2->LIFCR |= (1 << 10);
	}
}

void DMA2_Stream2_IRQHandler()
{
	if(((SON_DMA2->LISR >> 21) & 1 ) == 1)
	{
		SON_UART_Rx_Complete_IRQHandler(SON_USART1);
		SON_DMA2->LIFCR |= (1 << 21);
	}
	else if(((SON_DMA2->LISR >> 20) & 1 ) == 1)
	{
		SON_UART_Rx_Half_Complete_IRQHandler(SON_USART1);
		SON_DMA2->LIFCR |= (1 << 20);
	}
}

void USART1_IRQHandler()
{
	SON_UART_Rx_Complete_IRQHandler(SON_USART1);
}

void USART2_IRQHandler()
{
	SON_UART_Rx_Complete_IRQHandler(SON_USART2);
}

void USART6_IRQHandler()
{
	SON_UART_Rx_Complete_IRQHandler(SON_USART6);
}





