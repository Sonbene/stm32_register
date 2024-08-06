/*
 * RCC.h
 *
 *  Created on: Aug 5, 2024
 *      Author: Admin
 */

#ifndef INC_RCC_H_
#define INC_RCC_H_

#include "stdint.h"

#ifndef SON_RCC

	typedef struct
	{
		volatile uint32_t CR;
		volatile uint32_t PLLCFGR;
		volatile uint32_t CFGR;
		volatile uint32_t CIR;
		volatile uint32_t AHB1RSTR;
		volatile uint32_t AHB2RSTR;
		uint32_t RESERVED0[2];
		volatile uint32_t APB1RSTR;
		volatile uint32_t APB2RSTR;
		uint32_t RESERVED1[2];
		volatile uint32_t AHB1ENR;
		volatile uint32_t AHB2ENR;
		uint32_t RESERVED2[2];
		volatile uint32_t APB1ENR;
		volatile uint32_t APB2ENR;
		uint32_t RESERVED3[2];
		volatile uint32_t AHB1LPENR;
		volatile uint32_t AHB2LPENR;
		uint32_t RESERVED4[2];
		volatile uint32_t APB1LPENR;
		volatile uint32_t APB2LPENR;
		uint32_t RESERVED5[2];
		volatile uint32_t BDCR;
		volatile uint32_t CSR;
		uint32_t RESERVED6[2];
		volatile uint32_t SSCGR;
		volatile uint32_t PLLI2SCFGR;
		uint32_t RESERVED7;
		volatile uint32_t DCKCFGR;
	}SON_RCC_Typedef;

	#define SON_RCC		((SON_RCC_Typedef*)0x40023800)

#endif

#ifndef SON_FLASH

	typedef struct
	{
		volatile uint32_t ACR;
		volatile uint32_t KEYR;
		volatile uint32_t OPTKEYR;
		volatile uint32_t SR;
		volatile uint32_t CR;
		volatile uint32_t OPTCR;
	}SON_FLASH_Typedef;

	#define SON_FLASH	((SON_FLASH_Typedef*)0x40023C00)

#endif

void SON_RCC_SysClockConfig_HSE(void);
void SON_RCC_SysClockConfig_PLL_HSE(void);
void SON_RCC_SysClockConfig_PLL_HSI(void);

#endif /* INC_RCC_H_ */
