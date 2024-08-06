#ifndef UART_H
#define UART_H

#include"register.h"
#include"math.h"
#include"delay.h"

void SON_UART_Init(SON_USART_Typedef* SON_USARTx, SON_GPIO_t SON_GPIO_GPIOx,uint32_t baud_rate, uint32_t fclock);

SON_STATUS_t SON_UART_Transmit(SON_USART_Typedef* SON_USARTx, uint8_t* data, uint16_t size, uint32_t timeout);

SON_STATUS_t SON_UART_Receive_IT(SON_USART_Typedef* SON_USARTx);

SON_STATUS_t SON_UART_Receive_DMA(SON_USART_Typedef* SON_USARTx, uint8_t* data, uint16_t size, SON_DMA_STATE_t SON_CIRCRULAR);

uint8_t SON_UART_Get_Data(SON_USART_Typedef* SON_USARTx);

#endif
