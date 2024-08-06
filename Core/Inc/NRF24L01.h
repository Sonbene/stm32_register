#ifndef NRF24L01_H
#define NRF24L01_H

#include "SPI.h"
#include "register.h"
#include "delay.h"

#define NRF24_SPI			SON_SPI1

#define NRF24_CE_PORT		SON_GPIOA
#define NRF24_CE_PIN		SON_GPIO_Pin_1

#define NRF24_CSN_PORT		SON_GPIOA
#define NRF24_CSN_PIN		SON_GPIO_Pin_0


void NRF24_CS_Select(void);

void NRF24_CS_UnSelect(void);

void NRF24_CE_Enable(void);

void NRF24_CE_Disable(void);

//write a single byte to the particular register
void NRF24_WriteReg(uint8_t reg, uint8_t data);

//write a multiple bytes starting from a particular register
void NRF24_WriteRegMulti(uint8_t reg, uint8_t *data, int size);

void NRF24_ReadReg(uint8_t reg, uint8_t *data);

void NRF24_ReadRegMulti(uint8_t reg, uint8_t *data, int size);

//send the command to the NRF
void NRF24_Send_Cmd(uint8_t cmd);

void NRF24_Init(void);

//setup the tx mode
void NRF24_TX_Mode(uint8_t *address,  uint8_t channel);

//Transmit the data
uint8_t NRF24_Transmit(uint8_t* data, int size);

void NRF24_RX_Mode(uint8_t *address,  uint8_t channel);

uint8_t isDataAvailable(int pipenum);

void NRF24_Receive(uint8_t *data);


#define CONFIG      0x00
#define EN_AA       0x01
#define EN_RXADDR   0x02
#define SETUP_AW    0x03
#define SETUP_RETR  0x04
#define RF_CH       0x05
#define RF_SETUP    0x06
#define STATUS      0x07
#define OBSERVE_TX  0x08
#define CD          0x09
#define RX_ADDR_P0  0x0A
#define RX_ADDR_P1  0x0B
#define RX_ADDR_P2  0x0C
#define RX_ADDR_P3  0x0D
#define RX_ADDR_P4  0x0E
#define RX_ADDR_P5  0x0F
#define TX_ADDR     0x10
#define RX_PW_P0    0x11
#define RX_PW_P1    0x12
#define RX_PW_P2    0x13
#define RX_PW_P3    0x14
#define RX_PW_P4    0x15
#define RX_PW_P5    0x16
#define FIFO_STATUS 0x17
#define DYNPD	    0x1C
#define FEATURE	    0x1D

/* Instruction Mnemonics */
#define R_REGISTER    0x00
#define W_REGISTER    0x20
#define REGISTER_MASK 0x1F
#define ACTIVATE      0x50
#define R_RX_PL_WID   0x60
#define R_RX_PAYLOAD  0x61
#define W_TX_PAYLOAD  0xA0
#define W_ACK_PAYLOAD 0xA8
#define FLUSH_TX      0xE1
#define FLUSH_RX      0xE2
#define REUSE_TX_PL   0xE3
#define NOP           0xFF




#endif
