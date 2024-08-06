/*
 * SPI.h
 *
 *  Created on: Jul 26, 2024
 *      Author: Sonbe
 */

#ifndef INC_SPI_H_
#define INC_SPI_H_

#include "register.h"

void SON_SPI1_Receive_Data(uint8_t* data, uint16_t size);
void SON_SPI1_Transmit_Data(uint8_t* data, uint16_t size);
void SON_SPI1_Init(void);

#endif /* INC_SPI_H_ */
