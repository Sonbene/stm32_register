#ifndef REGISTER_H
#define REGISTER_H

#include "main.h"

typedef enum
{
	SON_OK,
	SON_ERROR,
	SON_BUSY,
	SON_TIMEOUT
}SON_STATUS_t;

typedef enum
{
	SON_GPIO_Pin_0,
	SON_GPIO_Pin_1,
	SON_GPIO_Pin_2,
	SON_GPIO_Pin_3,
	SON_GPIO_Pin_4,
	SON_GPIO_Pin_5,
	SON_GPIO_Pin_6,
	SON_GPIO_Pin_7,
	SON_GPIO_Pin_8,
	SON_GPIO_Pin_9,
	SON_GPIO_Pin_10,
	SON_GPIO_Pin_11,
	SON_GPIO_Pin_12,
	SON_GPIO_Pin_13,
	SON_GPIO_Pin_14,
	SON_GPIO_Pin_15,
}SON_GPIO_Pin_t;

typedef enum
{
	SON_GPIO_INPUT_FLOATING,
	SON_GPIO_INPUT_PULL_UP,
	SON_GPIO_INPUT_PULL_DOWN,
	SON_GPIO_OUTPUT_PUSH_PULL,
	SON_GPIO_OUTPUT_OPEN_DRAIN,
}SON_GPIO_Mode_t;

typedef enum
{
	SON_GPIO_Pin_Reset,
	SON_GPIO_Pin_Set
}SON_GPIO_Pin_State_t;

typedef enum
{
	SON_GPIO_GPIOA,
	SON_GPIO_GPIOB,
	SON_GPIO_GPIOC
}SON_GPIO_t;

typedef enum
{
	SON_FALLING,
	SON_RISING
}SON_Trigger_t;

typedef enum
{
	SON_CIRCRULAR_DISABLE,
	SON_CIRCRULAR_ENABLE
}SON_DMA_STATE_t;

typedef enum
{
	SON_SECTOR_0,
	SON_SECTOR_1,
	SON_SECTOR_2,
	SON_SECTOR_3,
	SON_SECTOR_4,
	SON_SECTOR_5,
}SON_SECTOR_t;

typedef enum
{
	SON_FLASH_ERASE_MASS,
	SON_FLASH_ERASE_SECTOR
}SON_FLASH_ERASE_t;

typedef enum
{
	SON_FLASH_PRORAM_BYTE,
	SON_FLASH_PRORAM_HALF_WORD,
	SON_FLASH_PRORAM_WORD,
	SON_FLASH_PRORAM_DOUBLE_WOLD
}SON_FLASH_PROGRAM_TYPE_t;

typedef enum
{
/******  Cortex-M4 Processor Exceptions Numbers ****************************************************************/
  SON_NonMaskableInt_IRQn         = -14,    /*!< 2 Non Maskable Interrupt                                          */
  SON_MemoryManagement_IRQn       = -12,    /*!< 4 Cortex-M4 Memory Management Interrupt                           */
  SON_BusFault_IRQn               = -11,    /*!< 5 Cortex-M4 Bus Fault Interrupt                                   */
  SON_UsageFault_IRQn             = -10,    /*!< 6 Cortex-M4 Usage Fault Interrupt                                 */
  SON_SVCall_IRQn                 = -5,     /*!< 11 Cortex-M4 SV Call Interrupt                                    */
  SON_DebugMonitor_IRQn           = -4,     /*!< 12 Cortex-M4 Debug Monitor Interrupt                              */
  SON_PendSV_IRQn                 = -2,     /*!< 14 Cortex-M4 Pend SV Interrupt                                    */
  SON_SysTick_IRQn                = -1,     /*!< 15 Cortex-M4 System Tick Interrupt                                */
/******  STM32 specific Interrupt Numbers **********************************************************************/
  SON_WWDG_IRQn                   = 0,      /*!< Window WatchDog Interrupt                                         */
  SON_PVD_IRQn                    = 1,      /*!< PVD through EXTI Line detection Interrupt                         */
  SON_TAMP_STAMP_IRQn             = 2,      /*!< Tamper and TimeStamp interrupts through the EXTI line             */
  SON_RTC_WKUP_IRQn               = 3,      /*!< RTC Wakeup interrupt through the EXTI line                        */
  SON_FLASH_IRQn                  = 4,      /*!< FLASH global Interrupt                                            */
  SON_RCC_IRQn                    = 5,      /*!< RCC global Interrupt                                              */
  SON_EXTI0_IRQn                  = 6,      /*!< EXTI Line0 Interrupt                                              */
  SON_EXTI1_IRQn                  = 7,      /*!< EXTI Line1 Interrupt                                              */
  SON_EXTI2_IRQn                  = 8,      /*!< EXTI Line2 Interrupt                                              */
  SON_EXTI3_IRQn                  = 9,      /*!< EXTI Line3 Interrupt                                              */
  SON_EXTI4_IRQn                  = 10,     /*!< EXTI Line4 Interrupt                                              */
  SON_DMA1_Stream0_IRQn           = 11,     /*!< DMA1 Stream 0 global Interrupt                                    */
  SON_DMA1_Stream1_IRQn           = 12,     /*!< DMA1 Stream 1 global Interrupt                                    */
  SON_DMA1_Stream2_IRQn           = 13,     /*!< DMA1 Stream 2 global Interrupt                                    */
  SON_DMA1_Stream3_IRQn           = 14,     /*!< DMA1 Stream 3 global Interrupt                                    */
  SON_DMA1_Stream4_IRQn           = 15,     /*!< DMA1 Stream 4 global Interrupt                                    */
  SON_DMA1_Stream5_IRQn           = 16,     /*!< DMA1 Stream 5 global Interrupt                                    */
  SON_DMA1_Stream6_IRQn           = 17,     /*!< DMA1 Stream 6 global Interrupt                                    */
  SON_ADC_IRQn                    = 18,     /*!< ADC1, ADC2 and ADC3 global Interrupts                             */
  SON_EXTI9_5_IRQn                = 23,     /*!< External Line[9:5] Interrupts                                     */
  SON_TIM1_BRK_TIM9_IRQn          = 24,     /*!< TIM1 Break interrupt and TIM9 global interrupt                    */
  SON_TIM1_UP_TIM10_IRQn          = 25,     /*!< TIM1 Update Interrupt and TIM10 global interrupt                  */
  SON_TIM1_TRG_COM_TIM11_IRQn     = 26,     /*!< TIM1 Trigger and Commutation Interrupt and TIM11 global interrupt */
  SON_TIM1_CC_IRQn                = 27,     /*!< TIM1 Capture Compare Interrupt                                    */
  SON_TIM2_IRQn                   = 28,     /*!< TIM2 global Interrupt                                             */
  SON_TIM3_IRQn                   = 29,     /*!< TIM3 global Interrupt                                             */
  SON_TIM4_IRQn                   = 30,     /*!< TIM4 global Interrupt                                             */
  SON_I2C1_EV_IRQn                = 31,     /*!< I2C1 Event Interrupt                                              */
  SON_I2C1_ER_IRQn                = 32,     /*!< I2C1 Error Interrupt                                              */
  SON_I2C2_EV_IRQn                = 33,     /*!< I2C2 Event Interrupt                                              */
  SON_I2C2_ER_IRQn                = 34,     /*!< I2C2 Error Interrupt                                              */
  SON_SPI1_IRQn                   = 35,     /*!< SPI1 global Interrupt                                             */
  SON_SPI2_IRQn                   = 36,     /*!< SPI2 global Interrupt                                             */
  SON_USART1_IRQn                 = 37,     /*!< USART1 global Interrupt                                           */
  SON_USART2_IRQn                 = 38,     /*!< USART2 global Interrupt                                           */
  SON_EXTI15_10_IRQn              = 40,     /*!< External Line[15:10] Interrupts                                   */
  SON_RTC_Alarm_IRQn              = 41,     /*!< RTC Alarm (A and B) through EXTI Line Interrupt                   */
  SON_OTG_FS_WKUP_IRQn            = 42,     /*!< USB OTG FS Wakeup through EXTI line interrupt                     */
  SON_DMA1_Stream7_IRQn           = 47,     /*!< DMA1 Stream7 Interrupt                                            */
  SON_SDIO_IRQn                   = 49,     /*!< SDIO global Interrupt                                             */
  SON_TIM5_IRQn                   = 50,     /*!< TIM5 global Interrupt                                             */
  SON_SPI3_IRQn                   = 51,     /*!< SPI3 global Interrupt                                             */
  SON_DMA2_Stream0_IRQn           = 56,     /*!< DMA2 Stream 0 global Interrupt                                    */
  SON_DMA2_Stream1_IRQn           = 57,     /*!< DMA2 Stream 1 global Interrupt                                    */
  SON_DMA2_Stream2_IRQn           = 58,     /*!< DMA2 Stream 2 global Interrupt                                    */
  SON_DMA2_Stream3_IRQn           = 59,     /*!< DMA2 Stream 3 global Interrupt                                    */
  SON_DMA2_Stream4_IRQn           = 60,     /*!< DMA2 Stream 4 global Interrupt                                    */
  SON_OTG_FS_IRQn                 = 67,     /*!< USB OTG FS global Interrupt                                       */
  SON_DMA2_Stream5_IRQn           = 68,     /*!< DMA2 Stream 5 global interrupt                                    */
  SON_DMA2_Stream6_IRQn           = 69,     /*!< DMA2 Stream 6 global interrupt                                    */
  SON_DMA2_Stream7_IRQn           = 70,     /*!< DMA2 Stream 7 global interrupt                                    */
  SON_USART6_IRQn                 = 71,     /*!< USART6 global interrupt                                           */
  SON_I2C3_EV_IRQn                = 72,     /*!< I2C3 event interrupt                                              */
  SON_I2C3_ER_IRQn                = 73,     /*!< I2C3 error interrupt                                              */
  SON_FPU_IRQn                    = 81,     /*!< FPU global interrupt                                              */
  SON_SPI4_IRQn                   = 84      /*!< SPI4 global Interrupt                                              */
} SON_IRQn_Typedef;

typedef struct
{
	volatile uint32_t MODER;
	volatile uint32_t OTYPER;
	volatile uint32_t OSPEEDR;
	volatile uint32_t PUPDR;
	volatile uint32_t IDR;
	volatile uint32_t ODR;
	volatile uint32_t BSRR;
	volatile uint32_t LCKR;
	volatile uint32_t AFRL;
	volatile uint32_t AFRH;
}SON_GPIO_Typedef;

typedef struct
{
	volatile uint32_t MEMRMP;
	volatile uint32_t PMC;
	volatile uint32_t EXTICR[4];
	uint32_t      	  RESERVED[2];
	volatile uint32_t CMPCR;
}SON_SYSCFG_Typedef;

typedef struct
{
	volatile uint32_t IMR;
	volatile uint32_t EMR;
	volatile uint32_t RTSR;
	volatile uint32_t FTSR;
	volatile uint32_t SWIER;
	volatile uint32_t PR;
}SON_EXTI_Typedef;

typedef struct
{
	volatile uint32_t ISER[8];
	uint32_t RESERVED0[24];
	volatile uint32_t ICER[8];
	uint32_t RESERVED1[24];
	volatile uint32_t ISPR[8];
	uint32_t RESERVED2[24];
	volatile uint32_t ICPR[8];
	uint32_t RESERVED3[24];
	volatile uint32_t IABR[8];
	uint32_t RESERVED4[56];
	volatile uint8_t IPR[240];
	uint32_t RESERVED5[644U];
	volatile uint32_t STIR;
}SON_NVIC_Typedef;

typedef struct
{
	volatile uint32_t CSR;
	volatile uint32_t RVR;
	volatile uint32_t CVR;
	volatile uint32_t CALIB;
}SON_SYST_Typedef;

typedef struct
{
	volatile uint32_t SR;
	volatile uint32_t DR;
	volatile uint32_t BRR;
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t CR3;
	volatile uint32_t GTPR;
}SON_USART_Typedef;

typedef struct
{
	volatile uint32_t LISR;
	volatile uint32_t HISR;
	volatile uint32_t LIFCR;
	volatile uint32_t HIFCR;
	volatile uint32_t S0CR;
	volatile uint32_t S0NDTR;
	volatile uint32_t S0PAR;
	volatile uint32_t S0M0AR;
	volatile uint32_t S0M1AR;
	volatile uint32_t S0FCR;
	volatile uint32_t S1CR;
	volatile uint32_t S1NDTR;
	volatile uint32_t S1PAR;
	volatile uint32_t S1M0AR;
	volatile uint32_t S1M1AR;
	volatile uint32_t S1FCR;
	volatile uint32_t S2CR;
	volatile uint32_t S2NDTR;
	volatile uint32_t S2PAR;
	volatile uint32_t S2M0AR;
	volatile uint32_t S2M1AR;
	volatile uint32_t S2FCR;
	volatile uint32_t S3CR;
	volatile uint32_t S3NDTR;
	volatile uint32_t S3PAR;
	volatile uint32_t S3M0AR;
	volatile uint32_t S3M1AR;
	volatile uint32_t S3FCR;
	volatile uint32_t S4CR;
	volatile uint32_t S4NDTR;
	volatile uint32_t S4PAR;
	volatile uint32_t S4M0AR;
	volatile uint32_t S4M1AR;
	volatile uint32_t S4FCR;
	volatile uint32_t S5CR;
	volatile uint32_t S5NDTR;
	volatile uint32_t S5PAR;
	volatile uint32_t S5M0AR;
	volatile uint32_t S5M1AR;
	volatile uint32_t S5FCR;
	volatile uint32_t S6CR;
	volatile uint32_t S6NDTR;
	volatile uint32_t S6PAR;
	volatile uint32_t S6M0AR;
	volatile uint32_t S6M1AR;
	volatile uint32_t S6FCR;
	volatile uint32_t S7CR;
	volatile uint32_t S7NDTR;
	volatile uint32_t S7PAR;
	volatile uint32_t S7M0AR;
	volatile uint32_t S7M1AR;
	volatile uint32_t S7FCR;
}SON_DMA_Typedef;

typedef struct
{
	volatile uint32_t ACR;
	volatile uint32_t KEYR;
	volatile uint32_t OPTKEYR;
	volatile uint32_t SR;
	volatile uint32_t CR;
	volatile uint32_t OPTCR;
}SON_FLASH_Typedef;

typedef struct
{
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t SR;
	volatile uint32_t DR;
	volatile uint32_t CRCPR;
	volatile uint32_t RXCRCR;
	volatile uint32_t TXCRCR;
	volatile uint32_t I2SCFGR;
	volatile uint32_t I2SPR;
}SON_SPI_Typedef;

typedef struct
{
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t OAR1;
	volatile uint32_t OAR2;
	volatile uint32_t DR;
	volatile uint32_t SR1;
	volatile uint32_t SR2;
	volatile uint32_t CCR;
	volatile uint32_t TRISE;
	volatile uint32_t FLTR;
}SON_I2C_Typedef;

typedef struct
{
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t SMCR;
	volatile uint32_t DIER;
	volatile uint32_t SR;
	volatile uint32_t EGR;
	volatile uint32_t CCMR1;
	volatile uint32_t CCMR2;
	volatile uint32_t CCER;
	volatile uint32_t CNT;
	volatile uint32_t PSC;
	volatile uint32_t ARR;
	volatile uint32_t RCR;
	volatile uint32_t CCR1;
	volatile uint32_t CCR2;
	volatile uint32_t CCR3;
	volatile uint32_t CCR4;
	volatile uint32_t BDTR;
	volatile uint32_t DCR;
	volatile uint32_t DMAR;
}SON_TIM1_Typedef;


typedef struct
{
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t SMCR;
	volatile uint32_t DIER;
	volatile uint32_t SR;
	volatile uint32_t EGR;
	volatile uint32_t CCMR1;
	volatile uint32_t CCMR2;
	volatile uint32_t CCER;
	volatile uint32_t CNT;
	volatile uint32_t PSC;
	volatile uint32_t ARR;
	uint32_t RESERVED1;
	volatile uint32_t CCR1;
	volatile uint32_t CCR2;
	volatile uint32_t CCR3;
	volatile uint32_t CCR4;
	uint32_t RESERVED2;
	volatile uint32_t DCR;
	volatile uint32_t DMAR;
	volatile uint32_t OR;
}SON_TIM5_2_Typedef;

typedef struct
{
	volatile uint32_t CR1;
	uint32_t RESERVED1;
	volatile uint32_t SMCR;
	volatile uint32_t DIER;
	volatile uint32_t SR;
	volatile uint32_t EGR;
	volatile uint32_t CCMR1;
	uint32_t RESERVED2;
	volatile uint32_t CCER;
	volatile uint32_t CNT;
	volatile uint32_t PSC;
	volatile uint32_t ARR;
	uint32_t RESERVED3;
	volatile uint32_t CCR1;
	volatile uint32_t CCR2;
}SON_TIM9_Typedef;

typedef struct
{
	volatile uint32_t CR1;
	uint32_t RESERVED1;
	volatile uint32_t SMCR;
	volatile uint32_t DIER;
	volatile uint32_t SR;
	volatile uint32_t EGR;
	volatile uint32_t CCMR1;
	uint32_t RESERVED2;
	volatile uint32_t CCER;
	volatile uint32_t CNT;
	volatile uint32_t PSC;
	volatile uint32_t ARR;
	uint32_t RESERVED3;
	volatile uint32_t CCR1;
	uint32_t RESERVED4[6];
	volatile uint32_t OR;
}SON_TIM11_10_Typedef;

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

typedef struct
{
	volatile uint32_t KR;
	volatile uint32_t PR;
	volatile uint32_t RLR;
	volatile uint32_t SR;
}SON_IWDG_Typedef;

typedef struct
{
	volatile uint32_t SR;
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t SMPR1;
	volatile uint32_t SMPR2;
	volatile uint32_t JOFR1;
	volatile uint32_t JOFR2;
	volatile uint32_t JOFR3;
	volatile uint32_t JOFR4;
	volatile uint32_t HTR;
	volatile uint32_t LTR;
	volatile uint32_t SQR1;
	volatile uint32_t SQR2;
	volatile uint32_t SQR3;
	volatile uint32_t JSQR;
	volatile uint32_t JDR1;
	volatile uint32_t jDR2;
	volatile uint32_t JDR3;
	volatile uint32_t JDR4;
	volatile uint32_t DR;
}SON_ADC_Typedef;

#define weak_func __attribute__((weak))


#define SON_TIM2_BASE_ADDRESS		0x40000000
#define SON_TIM3_BASE_ADDRESS		0x40000400
#define SON_TIM4_BASE_ADDRESS		0x40000800
#define SON_TIM5_BASE_ADDRESS		0x40000C00
#define SON_RTC_BASE_ADDRESS      	0X40002800
#define	SON_WWDG_BASE_ADDRESS		0x40002C00
#define SON_IWDG_BASE_ADDRESS		0x40003000
#define SON_I2S2ext_BASE_ADDRESS	0x40003400
#define SON_SPI2_BASE_ADDRESS		0x40003800
#define SON_SPI3_BASE_ADDRESS		0x40003C00
#define SON_I2S3ext_BASE_ADDRESS	0x40004000
#define SON_USART2_BASE_ADDRESS		0x40004400
#define SON_I2C1_BASE_ADDRESS		0x40005400
#define SON_I2C2_BASE_ADDRESS		0x40005800
#define SON_I2C3_BASE_ADDRESS		0x40005C00
#define SON_PWR_BASE_ADDRESS		0x40007000
#define SON_TIM1_BASE_ADDRESS		0x40010000
#define SON_USART1_BASE_ADDRESS		0x40011000
#define SON_USART6_BASE_ADDRESS		0x40011400
#define SON_ADC1_BASE_ADDRESS		0x40012000
#define SON_SDIO_BASE_ADDRESS		0x40012C00
#define SON_SPI1_BASE_ADDRESS		0x40013000
#define SON_SPI4_BASE_ADDRESS		0x40013400
#define SON_SYSCFG_BASE_ADDRESS 	0x40013800
#define SON_EXTI_BASE_ADDRESS		0x40013C00
#define SON_TIM9_BASE_ADDRESS		0x40014000
#define SON_TIM10_BASE_ADDRESS		0x40014400
#define SON_TIM11_BASE_ADDRESS		0x40014800
#define SON_GPIOA_BASE_ADDRESS 		0x40020000
#define SON_GPIOB_BASE_ADDRESS 		0x40020400
#define SON_GPIOC_BASE_ADDRESS 		0x40020800
#define SON_GPIOD_BASE_ADDRESS		0x40020C00
#define SON_GPIOE_BASE_ADDRESS		0x40021000
#define SON_GPIOH_BASE_ADDRESS		0x40021C00
#define SON_CRC_BASE_ADDRESS		0x40023000
#define SON_RCC_BASE_ADDRESS		0x40023800
#define SON_FLASH_BASE_ADDRESS		0x40023C00
#define SON_DMA1_BASE_ADDRESS		0x40026000
#define SON_DMA2_BASE_ADDRESS		0x40026400
#define SON_USB_BASE_ADDRESS		0x50000000
#define SON_SYST_BASE_ADDRESS		0xE000E010
#define SON_NVIC_BASE_ADDRESS 		0xE000E100


#define SON_GPIOA 					((SON_GPIO_Typedef*)SON_GPIOA_BASE_ADDRESS)
#define SON_GPIOB 					((SON_GPIO_Typedef*)SON_GPIOB_BASE_ADDRESS)
#define SON_GPIOC					((SON_GPIO_Typedef*)SON_GPIOC_BASE_ADDRESS)
#define SON_SYSCFG					((SON_SYSCFG_Typedef*)SON_SYSCFG_BASE_ADDRESS)
#define SON_EXTI					((SON_EXTI_Typedef*)SON_EXTI_BASE_ADDRESS)
#define SON_SYST					((SON_SYST_Typedef*)SON_SYST_BASE_ADDRESS)
#define SON_NVIC					((SON_NVIC_Typedef*)SON_NVIC_BASE_ADDRESS)
#define SON_USART1					((SON_USART_Typedef*)SON_USART1_BASE_ADDRESS)
#define SON_USART2					((SON_USART_Typedef*)SON_USART2_BASE_ADDRESS)
#define SON_USART6					((SON_USART_Typedef*)SON_USART6_BASE_ADDRESS)
#define SON_DMA1					((SON_DMA_Typedef*)SON_DMA1_BASE_ADDRESS)
#define SON_DMA2					((SON_DMA_Typedef*)SON_DMA2_BASE_ADDRESS)
#define SON_FLASH					((SON_FLASH_Typedef*)SON_FLASH_BASE_ADDRESS)
#define SON_SPI1					((SON_SPI_Typedef*)SON_SPI1_BASE_ADDRESS)
#define SON_SPI2					((SON_SPI_Typedef*)SON_SPI2_BASE_ADDRESS)
#define SON_SPI3					((SON_SPI_Typedef*)SON_SPI3_BASE_ADDRESS)
#define SON_SPI4					((SON_SPI_Typedef*)SON_SPI4_BASE_ADDRESS)
#define SON_I2C1					((SON_I2C_Typedef*)SON_I2C1_BASE_ADDRESS)
#define SON_I2C2					((SON_I2C_Typedef*)SON_I2C2_BASE_ADDRESS)
#define SON_I2C3					((SON_I2C_Typedef*)SON_I2C3_BASE_ADDRESS)
#define SON_TIM1					((SON_TIM1_Typedef*)SON_TIM1_BASE_ADDRESS)
#define SON_TIM2					((SON_TIM5_2_Typedef*)SON_TIM2_BASE_ADDRESS)
#define SON_TIM3					((SON_TIM5_2_Typedef*)SON_TIM3_BASE_ADDRESS)
#define SON_TIM4					((SON_TIM5_2_Typedef*)SON_TIM4_BASE_ADDRESS)
#define SON_TIM5					((SON_TIM5_2_Typedef*)SON_TIM5_BASE_ADDRESS)
#define SON_TIM9					((SON_TIM9_Typedef*)SON_TIM9_BASE_ADDRESS)
#define SON_TIM10					((SON_TIM11_10_Typedef*)SON_TIM10_BASE_ADDRESS)
#define SON_TIM11					((SON_TIM11_10_Typedef*)SON_TIM11_BASE_ADDRESS)
#define SON_RCC						((SON_RCC_Typedef*)SON_RCC_BASE_ADDRESS)
#define SON_IWDG					((SON_IWDG_Typedef*)SON_IWDG_BASE_ADDRESS)
#define SON_ADC1					((SON_ADC_Typedef*)SON_ADC1_BASE_ADDRESS)
#define SON_ADC1_CCR				((uint32_t*)0x40012304)

#endif
