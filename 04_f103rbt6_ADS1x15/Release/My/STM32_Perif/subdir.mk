################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../My/STM32_Perif/adc_ST.c \
../My/STM32_Perif/dma_ST.c \
../My/STM32_Perif/flash_ST.c \
../My/STM32_Perif/gpio_ST.c \
../My/STM32_Perif/i2c_ST.c \
../My/STM32_Perif/rtc_ST.c \
../My/STM32_Perif/spi_ST.c \
../My/STM32_Perif/stm32f10x_it.c \
../My/STM32_Perif/sys_ST.c \
../My/STM32_Perif/sys_tick_ST.c \
../My/STM32_Perif/timers_ST.c \
../My/STM32_Perif/uart_ST.c 

OBJS += \
./My/STM32_Perif/adc_ST.o \
./My/STM32_Perif/dma_ST.o \
./My/STM32_Perif/flash_ST.o \
./My/STM32_Perif/gpio_ST.o \
./My/STM32_Perif/i2c_ST.o \
./My/STM32_Perif/rtc_ST.o \
./My/STM32_Perif/spi_ST.o \
./My/STM32_Perif/stm32f10x_it.o \
./My/STM32_Perif/sys_ST.o \
./My/STM32_Perif/sys_tick_ST.o \
./My/STM32_Perif/timers_ST.o \
./My/STM32_Perif/uart_ST.o 

C_DEPS += \
./My/STM32_Perif/adc_ST.d \
./My/STM32_Perif/dma_ST.d \
./My/STM32_Perif/flash_ST.d \
./My/STM32_Perif/gpio_ST.d \
./My/STM32_Perif/i2c_ST.d \
./My/STM32_Perif/rtc_ST.d \
./My/STM32_Perif/spi_ST.d \
./My/STM32_Perif/stm32f10x_it.d \
./My/STM32_Perif/sys_ST.d \
./My/STM32_Perif/sys_tick_ST.d \
./My/STM32_Perif/timers_ST.d \
./My/STM32_Perif/uart_ST.d 


# Each subdirectory must supply rules for building sources it contributes
My/STM32_Perif/%.o My/STM32_Perif/%.su My/STM32_Perif/%.cyclo: ../My/STM32_Perif/%.c My/STM32_Perif/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -DSTM32F103RBTx -DSTM32 -DSTM32F1 -c -I"E:/Anton/07_Git/Git_Board_F103RBT6/04_f103rbt6_ADS1x15/MCUv7" -I"E:/Anton/07_Git/Git_Board_F103RBT6/04_f103rbt6_ADS1x15/My/Application" -I"E:/Anton/07_Git/Git_Board_F103RBT6/04_f103rbt6_ADS1x15/My/CMSIS" -I"E:/Anton/07_Git/Git_Board_F103RBT6/04_f103rbt6_ADS1x15/My/Display" -I"E:/Anton/07_Git/Git_Board_F103RBT6/04_f103rbt6_ADS1x15/My/Main" -I"E:/Anton/07_Git/Git_Board_F103RBT6/04_f103rbt6_ADS1x15/My/Sheduler" -I"E:/Anton/07_Git/Git_Board_F103RBT6/04_f103rbt6_ADS1x15/My/Startup" -I"E:/Anton/07_Git/Git_Board_F103RBT6/04_f103rbt6_ADS1x15/My/STM32_Perif" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-My-2f-STM32_Perif

clean-My-2f-STM32_Perif:
	-$(RM) ./My/STM32_Perif/adc_ST.cyclo ./My/STM32_Perif/adc_ST.d ./My/STM32_Perif/adc_ST.o ./My/STM32_Perif/adc_ST.su ./My/STM32_Perif/dma_ST.cyclo ./My/STM32_Perif/dma_ST.d ./My/STM32_Perif/dma_ST.o ./My/STM32_Perif/dma_ST.su ./My/STM32_Perif/flash_ST.cyclo ./My/STM32_Perif/flash_ST.d ./My/STM32_Perif/flash_ST.o ./My/STM32_Perif/flash_ST.su ./My/STM32_Perif/gpio_ST.cyclo ./My/STM32_Perif/gpio_ST.d ./My/STM32_Perif/gpio_ST.o ./My/STM32_Perif/gpio_ST.su ./My/STM32_Perif/i2c_ST.cyclo ./My/STM32_Perif/i2c_ST.d ./My/STM32_Perif/i2c_ST.o ./My/STM32_Perif/i2c_ST.su ./My/STM32_Perif/rtc_ST.cyclo ./My/STM32_Perif/rtc_ST.d ./My/STM32_Perif/rtc_ST.o ./My/STM32_Perif/rtc_ST.su ./My/STM32_Perif/spi_ST.cyclo ./My/STM32_Perif/spi_ST.d ./My/STM32_Perif/spi_ST.o ./My/STM32_Perif/spi_ST.su ./My/STM32_Perif/stm32f10x_it.cyclo ./My/STM32_Perif/stm32f10x_it.d ./My/STM32_Perif/stm32f10x_it.o ./My/STM32_Perif/stm32f10x_it.su ./My/STM32_Perif/sys_ST.cyclo ./My/STM32_Perif/sys_ST.d ./My/STM32_Perif/sys_ST.o ./My/STM32_Perif/sys_ST.su ./My/STM32_Perif/sys_tick_ST.cyclo ./My/STM32_Perif/sys_tick_ST.d ./My/STM32_Perif/sys_tick_ST.o ./My/STM32_Perif/sys_tick_ST.su ./My/STM32_Perif/timers_ST.cyclo ./My/STM32_Perif/timers_ST.d ./My/STM32_Perif/timers_ST.o ./My/STM32_Perif/timers_ST.su ./My/STM32_Perif/uart_ST.cyclo ./My/STM32_Perif/uart_ST.d ./My/STM32_Perif/uart_ST.o ./My/STM32_Perif/uart_ST.su

.PHONY: clean-My-2f-STM32_Perif

