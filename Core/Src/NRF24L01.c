#include "NRF24L01.h"

void NRF24_CS_Select()
{
	NRF24_CSN_PORT->BSRR |= (1 << (16 + NRF24_CSN_PIN));
}

void NRF24_CS_UnSelect()
{
	NRF24_CSN_PORT->BSRR |= (1 << ( NRF24_CSN_PIN));
}

void NRF24_CE_Enable()
{
	NRF24_CE_PORT->BSRR |= (1 << ( NRF24_CE_PIN));
}

void NRF24_CE_Disable()
{
	NRF24_CE_PORT->BSRR |= (1 << (16 + NRF24_CE_PIN));
}

//write a single byte to the particular register
void NRF24_WriteReg(uint8_t reg, uint8_t data)
{
	uint8_t buf[2] ={0};
	buf[0] = reg|(1 << 5);
	buf[1] = data;

	NRF24_CE_Disable();
	NRF24_CS_Select();

	SON_SPI1_Transmit_Data(buf, 2);

	NRF24_CS_UnSelect();
	NRF24_CE_Enable();
}

//write a multiple bytes starting from a particular register
void NRF24_WriteRegMulti(uint8_t reg, uint8_t *data, int size)
{
	uint8_t buf[2] = {0};
	buf[0] = reg|(1 << 5);

	NRF24_CS_Select();
	NRF24_CE_Disable();

	SON_SPI1_Transmit_Data(buf, 1);
	SON_SPI1_Transmit_Data(data, size);

	NRF24_CS_UnSelect();
	NRF24_CE_Enable();
}

void NRF24_ReadReg(uint8_t reg, uint8_t *data)
{
	uint8_t buf[2];
	buf[0] = reg;
	NRF24_CS_Select();

	SON_SPI1_Transmit_Data(buf, 1);
	SON_SPI1_Receive_Data(data, 1);

	NRF24_CS_UnSelect();
}

void NRF24_ReadRegMulti(uint8_t reg, uint8_t *data, int size)
{
	NRF24_CS_Select();

	SON_SPI1_Transmit_Data(&reg, 1);
	SON_SPI1_Receive_Data(data, size);

	NRF24_CS_UnSelect();
}

//send the command to the NRF
void NRF24_Send_Cmd(uint8_t cmd)
{
	uint8_t cmdSend = cmd;
	NRF24_CS_Select();

	SON_SPI1_Transmit_Data(&cmdSend, 1);

	NRF24_CS_UnSelect();
}

void NRF24_Init()
{
	SON_SPI1->CR1 &= ~(0x03 << 0);// lpha= 0, cpol = 0

	NRF24_WriteReg(CONFIG, 0);

	NRF24_WriteReg(EN_AA, 0);// no auto ACK

	NRF24_WriteReg(EN_RXADDR, 0);// Not enabling any data pipe right now

	NRF24_WriteReg(SETUP_AW, 0x03);// 5 bytes for the TX/RX address

	NRF24_WriteReg(SETUP_RETR, 0);// No retransmission

	NRF24_WriteReg(RF_CH, 0); // will be setup during Tx or Rx

	NRF24_WriteReg(RF_SETUP, 0x0E);//power = 0; data rate = 2Mbps

}

//setup the tx mode
void NRF24_TX_Mode(uint8_t *address,  uint8_t channel)
{
	//disable the chip before configure the device
	NRF24_CE_Disable();

	NRF24_WriteReg(RF_CH, channel);//select the channel

	NRF24_WriteRegMulti(TX_ADDR, address, 5);//write the TX address

	uint8_t config;
	NRF24_ReadReg(CONFIG, &config);
	config &= ~(1 << 0);// TX
	config |= (1 << 1);// Power up the device
	NRF24_WriteReg(CONFIG, config);

	//Enable the chip after configure the device
	NRF24_CE_Enable();
}

//Transmit the data

uint8_t NRF24_Transmit(uint8_t* data, int size)
{
	//select the device
	NRF24_CS_Select();

	uint8_t cmdToSend = W_TX_PAYLOAD;

	SON_SPI1_Transmit_Data(&cmdToSend, 1);

	SON_SPI1_Transmit_Data(data,	size);

	//Unselect the device
	NRF24_CS_UnSelect();

	SON_Delay(1);

	uint8_t fifostatus = 0;
	NRF24_ReadReg(FIFO_STATUS, &fifostatus);

	if((fifostatus & (1 << 4)) && (!(fifostatus & (1 << 3))))
	{
		cmdToSend = FLUSH_TX;
		NRF24_Send_Cmd(cmdToSend);
		return 1;
	}
	return 0;
}

void NRF24_RX_Mode(uint8_t *address,  uint8_t channel)
{
	//disable the chip before configure the device
	NRF24_CE_Disable();

	NRF24_WriteReg(RF_CH, channel);//select the channel

	uint8_t en_rxaddr;
	NRF24_ReadReg(EN_RXADDR, &en_rxaddr);
	en_rxaddr |= (0x01 << 1);

	NRF24_WriteReg(EN_RXADDR, en_rxaddr); // select data pipe 1

	NRF24_WriteRegMulti(RX_ADDR_P1, address, 5);//write the TX address

	NRF24_WriteReg(RX_PW_P1, 32);

	uint8_t config;
	NRF24_ReadReg(CONFIG, &config);
	config &= ~(1 << 0);// TX
	config |= (1 << 1) | (1 << 0);// Power up the device
	NRF24_WriteReg(CONFIG, config);

	//Enable the chip after configure the device
	NRF24_CE_Enable();
}

uint8_t isDataAvailable(int pipenum)
{
	uint8_t status;
	NRF24_ReadReg(STATUS, &status);

	if((status & (1 << 6)) && (status & (pipenum << 1)))
	{
		NRF24_WriteReg(STATUS, (1 << 6));

		return 1;
	}

	return 0;
}

void NRF24_Receive(uint8_t *data)
{
	//select the device
	NRF24_CS_Select();

	uint8_t cmdToSend = R_RX_PAYLOAD;

	SON_SPI1_Transmit_Data(&cmdToSend, 1);

	SON_SPI1_Receive_Data(data, 32);

	//Unselect the device
	NRF24_CS_UnSelect();

	SON_Delay(1);

	cmdToSend = FLUSH_RX;
	NRF24_Send_Cmd(cmdToSend);
}
















