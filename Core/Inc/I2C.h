/*
 * I2C.h
 *
 *  Created on: Jul 28, 2024
 *      Author: Sonbe
 */

#ifndef INC_I2C_H_
#define INC_I2C_H_

#include "register.h"

void SON_I2C_Master_Transmit(uint8_t slave_address, uint8_t* data, uint16_t size);
void SON_I2C_Master_Receive(uint8_t slave_address, uint8_t* data, uint16_t size);
void SON_I2C1_Master_Init(void);


#endif /* INC_I2C_H_ */
