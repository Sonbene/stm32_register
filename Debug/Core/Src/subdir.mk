################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/ADC.c \
../Core/Src/GPIO.c \
../Core/Src/GPIO_interrupt.c \
../Core/Src/I2C.c \
../Core/Src/MPU6050.c \
../Core/Src/NRF24L01.c \
../Core/Src/RCC.c \
../Core/Src/SPI.c \
../Core/Src/Timer.c \
../Core/Src/Timer2.c \
../Core/Src/UART.c \
../Core/Src/delay.c \
../Core/Src/main.c \
../Core/Src/reset_mode.c \
../Core/Src/stm32f4xx_hal_msp.c \
../Core/Src/stm32f4xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f4xx.c 

OBJS += \
./Core/Src/ADC.o \
./Core/Src/GPIO.o \
./Core/Src/GPIO_interrupt.o \
./Core/Src/I2C.o \
./Core/Src/MPU6050.o \
./Core/Src/NRF24L01.o \
./Core/Src/RCC.o \
./Core/Src/SPI.o \
./Core/Src/Timer.o \
./Core/Src/Timer2.o \
./Core/Src/UART.o \
./Core/Src/delay.o \
./Core/Src/main.o \
./Core/Src/reset_mode.o \
./Core/Src/stm32f4xx_hal_msp.o \
./Core/Src/stm32f4xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f4xx.o 

C_DEPS += \
./Core/Src/ADC.d \
./Core/Src/GPIO.d \
./Core/Src/GPIO_interrupt.d \
./Core/Src/I2C.d \
./Core/Src/MPU6050.d \
./Core/Src/NRF24L01.d \
./Core/Src/RCC.d \
./Core/Src/SPI.d \
./Core/Src/Timer.d \
./Core/Src/Timer2.d \
./Core/Src/UART.d \
./Core/Src/delay.d \
./Core/Src/main.d \
./Core/Src/reset_mode.d \
./Core/Src/stm32f4xx_hal_msp.d \
./Core/Src/stm32f4xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f4xx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xC -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/ADC.cyclo ./Core/Src/ADC.d ./Core/Src/ADC.o ./Core/Src/ADC.su ./Core/Src/GPIO.cyclo ./Core/Src/GPIO.d ./Core/Src/GPIO.o ./Core/Src/GPIO.su ./Core/Src/GPIO_interrupt.cyclo ./Core/Src/GPIO_interrupt.d ./Core/Src/GPIO_interrupt.o ./Core/Src/GPIO_interrupt.su ./Core/Src/I2C.cyclo ./Core/Src/I2C.d ./Core/Src/I2C.o ./Core/Src/I2C.su ./Core/Src/MPU6050.cyclo ./Core/Src/MPU6050.d ./Core/Src/MPU6050.o ./Core/Src/MPU6050.su ./Core/Src/NRF24L01.cyclo ./Core/Src/NRF24L01.d ./Core/Src/NRF24L01.o ./Core/Src/NRF24L01.su ./Core/Src/RCC.cyclo ./Core/Src/RCC.d ./Core/Src/RCC.o ./Core/Src/RCC.su ./Core/Src/SPI.cyclo ./Core/Src/SPI.d ./Core/Src/SPI.o ./Core/Src/SPI.su ./Core/Src/Timer.cyclo ./Core/Src/Timer.d ./Core/Src/Timer.o ./Core/Src/Timer.su ./Core/Src/Timer2.cyclo ./Core/Src/Timer2.d ./Core/Src/Timer2.o ./Core/Src/Timer2.su ./Core/Src/UART.cyclo ./Core/Src/UART.d ./Core/Src/UART.o ./Core/Src/UART.su ./Core/Src/delay.cyclo ./Core/Src/delay.d ./Core/Src/delay.o ./Core/Src/delay.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/reset_mode.cyclo ./Core/Src/reset_mode.d ./Core/Src/reset_mode.o ./Core/Src/reset_mode.su ./Core/Src/stm32f4xx_hal_msp.cyclo ./Core/Src/stm32f4xx_hal_msp.d ./Core/Src/stm32f4xx_hal_msp.o ./Core/Src/stm32f4xx_hal_msp.su ./Core/Src/stm32f4xx_it.cyclo ./Core/Src/stm32f4xx_it.d ./Core/Src/stm32f4xx_it.o ./Core/Src/stm32f4xx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32f4xx.cyclo ./Core/Src/system_stm32f4xx.d ./Core/Src/system_stm32f4xx.o ./Core/Src/system_stm32f4xx.su

.PHONY: clean-Core-2f-Src

