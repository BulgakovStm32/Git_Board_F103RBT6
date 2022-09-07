################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../My/Perif_Drv/adc_ST.c \
../My/Perif_Drv/dma_ST.c \
../My/Perif_Drv/gpio_ST.c \
../My/Perif_Drv/i2c_ST.c \
../My/Perif_Drv/spi_ST.c \
../My/Perif_Drv/sys_ST.c \
../My/Perif_Drv/sys_tick_ST.c \
../My/Perif_Drv/timers_ST.c \
../My/Perif_Drv/uart_ST.c 

OBJS += \
./My/Perif_Drv/adc_ST.o \
./My/Perif_Drv/dma_ST.o \
./My/Perif_Drv/gpio_ST.o \
./My/Perif_Drv/i2c_ST.o \
./My/Perif_Drv/spi_ST.o \
./My/Perif_Drv/sys_ST.o \
./My/Perif_Drv/sys_tick_ST.o \
./My/Perif_Drv/timers_ST.o \
./My/Perif_Drv/uart_ST.o 

C_DEPS += \
./My/Perif_Drv/adc_ST.d \
./My/Perif_Drv/dma_ST.d \
./My/Perif_Drv/gpio_ST.d \
./My/Perif_Drv/i2c_ST.d \
./My/Perif_Drv/spi_ST.d \
./My/Perif_Drv/sys_ST.d \
./My/Perif_Drv/sys_tick_ST.d \
./My/Perif_Drv/timers_ST.d \
./My/Perif_Drv/uart_ST.d 


# Each subdirectory must supply rules for building sources it contributes
My/Perif_Drv/adc_ST.o: ../My/Perif_Drv/adc_ST.c My/Perif_Drv/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -DSTM32F103RBTx -DSTM32 -DSTM32F1 -c -I"D:/04_Git/Git_Board_F103RBT6/02_f103rbt6_RF_Module_HC12/My/Application" -I"D:/04_Git/Git_Board_F103RBT6/02_f103rbt6_RF_Module_HC12/My/CMSIS" -I"D:/04_Git/Git_Board_F103RBT6/02_f103rbt6_RF_Module_HC12/My/Main" -I"D:/04_Git/Git_Board_F103RBT6/02_f103rbt6_RF_Module_HC12/My/Sheduler" -I"D:/04_Git/Git_Board_F103RBT6/02_f103rbt6_RF_Module_HC12/My/Startup" -I"D:/04_Git/Git_Board_F103RBT6/02_f103rbt6_RF_Module_HC12/My/LCD" -I"D:/04_Git/Git_Board_F103RBT6/02_f103rbt6_RF_Module_HC12/My/Perif_Drv" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"My/Perif_Drv/adc_ST.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
My/Perif_Drv/dma_ST.o: ../My/Perif_Drv/dma_ST.c My/Perif_Drv/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -DSTM32F103RBTx -DSTM32 -DSTM32F1 -c -I"D:/04_Git/Git_Board_F103RBT6/02_f103rbt6_RF_Module_HC12/My/Application" -I"D:/04_Git/Git_Board_F103RBT6/02_f103rbt6_RF_Module_HC12/My/CMSIS" -I"D:/04_Git/Git_Board_F103RBT6/02_f103rbt6_RF_Module_HC12/My/Main" -I"D:/04_Git/Git_Board_F103RBT6/02_f103rbt6_RF_Module_HC12/My/Sheduler" -I"D:/04_Git/Git_Board_F103RBT6/02_f103rbt6_RF_Module_HC12/My/Startup" -I"D:/04_Git/Git_Board_F103RBT6/02_f103rbt6_RF_Module_HC12/My/LCD" -I"D:/04_Git/Git_Board_F103RBT6/02_f103rbt6_RF_Module_HC12/My/Perif_Drv" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"My/Perif_Drv/dma_ST.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
My/Perif_Drv/gpio_ST.o: ../My/Perif_Drv/gpio_ST.c My/Perif_Drv/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -DSTM32F103RBTx -DSTM32 -DSTM32F1 -c -I"D:/04_Git/Git_Board_F103RBT6/02_f103rbt6_RF_Module_HC12/My/Application" -I"D:/04_Git/Git_Board_F103RBT6/02_f103rbt6_RF_Module_HC12/My/CMSIS" -I"D:/04_Git/Git_Board_F103RBT6/02_f103rbt6_RF_Module_HC12/My/Main" -I"D:/04_Git/Git_Board_F103RBT6/02_f103rbt6_RF_Module_HC12/My/Sheduler" -I"D:/04_Git/Git_Board_F103RBT6/02_f103rbt6_RF_Module_HC12/My/Startup" -I"D:/04_Git/Git_Board_F103RBT6/02_f103rbt6_RF_Module_HC12/My/LCD" -I"D:/04_Git/Git_Board_F103RBT6/02_f103rbt6_RF_Module_HC12/My/Perif_Drv" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"My/Perif_Drv/gpio_ST.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
My/Perif_Drv/i2c_ST.o: ../My/Perif_Drv/i2c_ST.c My/Perif_Drv/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -DSTM32F103RBTx -DSTM32 -DSTM32F1 -c -I"D:/04_Git/Git_Board_F103RBT6/02_f103rbt6_RF_Module_HC12/My/Application" -I"D:/04_Git/Git_Board_F103RBT6/02_f103rbt6_RF_Module_HC12/My/CMSIS" -I"D:/04_Git/Git_Board_F103RBT6/02_f103rbt6_RF_Module_HC12/My/Main" -I"D:/04_Git/Git_Board_F103RBT6/02_f103rbt6_RF_Module_HC12/My/Sheduler" -I"D:/04_Git/Git_Board_F103RBT6/02_f103rbt6_RF_Module_HC12/My/Startup" -I"D:/04_Git/Git_Board_F103RBT6/02_f103rbt6_RF_Module_HC12/My/LCD" -I"D:/04_Git/Git_Board_F103RBT6/02_f103rbt6_RF_Module_HC12/My/Perif_Drv" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"My/Perif_Drv/i2c_ST.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
My/Perif_Drv/spi_ST.o: ../My/Perif_Drv/spi_ST.c My/Perif_Drv/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -DSTM32F103RBTx -DSTM32 -DSTM32F1 -c -I"D:/04_Git/Git_Board_F103RBT6/02_f103rbt6_RF_Module_HC12/My/Application" -I"D:/04_Git/Git_Board_F103RBT6/02_f103rbt6_RF_Module_HC12/My/CMSIS" -I"D:/04_Git/Git_Board_F103RBT6/02_f103rbt6_RF_Module_HC12/My/Main" -I"D:/04_Git/Git_Board_F103RBT6/02_f103rbt6_RF_Module_HC12/My/Sheduler" -I"D:/04_Git/Git_Board_F103RBT6/02_f103rbt6_RF_Module_HC12/My/Startup" -I"D:/04_Git/Git_Board_F103RBT6/02_f103rbt6_RF_Module_HC12/My/LCD" -I"D:/04_Git/Git_Board_F103RBT6/02_f103rbt6_RF_Module_HC12/My/Perif_Drv" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"My/Perif_Drv/spi_ST.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
My/Perif_Drv/sys_ST.o: ../My/Perif_Drv/sys_ST.c My/Perif_Drv/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -DSTM32F103RBTx -DSTM32 -DSTM32F1 -c -I"D:/04_Git/Git_Board_F103RBT6/02_f103rbt6_RF_Module_HC12/My/Application" -I"D:/04_Git/Git_Board_F103RBT6/02_f103rbt6_RF_Module_HC12/My/CMSIS" -I"D:/04_Git/Git_Board_F103RBT6/02_f103rbt6_RF_Module_HC12/My/Main" -I"D:/04_Git/Git_Board_F103RBT6/02_f103rbt6_RF_Module_HC12/My/Sheduler" -I"D:/04_Git/Git_Board_F103RBT6/02_f103rbt6_RF_Module_HC12/My/Startup" -I"D:/04_Git/Git_Board_F103RBT6/02_f103rbt6_RF_Module_HC12/My/LCD" -I"D:/04_Git/Git_Board_F103RBT6/02_f103rbt6_RF_Module_HC12/My/Perif_Drv" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"My/Perif_Drv/sys_ST.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
My/Perif_Drv/sys_tick_ST.o: ../My/Perif_Drv/sys_tick_ST.c My/Perif_Drv/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -DSTM32F103RBTx -DSTM32 -DSTM32F1 -c -I"D:/04_Git/Git_Board_F103RBT6/02_f103rbt6_RF_Module_HC12/My/Application" -I"D:/04_Git/Git_Board_F103RBT6/02_f103rbt6_RF_Module_HC12/My/CMSIS" -I"D:/04_Git/Git_Board_F103RBT6/02_f103rbt6_RF_Module_HC12/My/Main" -I"D:/04_Git/Git_Board_F103RBT6/02_f103rbt6_RF_Module_HC12/My/Sheduler" -I"D:/04_Git/Git_Board_F103RBT6/02_f103rbt6_RF_Module_HC12/My/Startup" -I"D:/04_Git/Git_Board_F103RBT6/02_f103rbt6_RF_Module_HC12/My/LCD" -I"D:/04_Git/Git_Board_F103RBT6/02_f103rbt6_RF_Module_HC12/My/Perif_Drv" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"My/Perif_Drv/sys_tick_ST.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
My/Perif_Drv/timers_ST.o: ../My/Perif_Drv/timers_ST.c My/Perif_Drv/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -DSTM32F103RBTx -DSTM32 -DSTM32F1 -c -I"D:/04_Git/Git_Board_F103RBT6/02_f103rbt6_RF_Module_HC12/My/Application" -I"D:/04_Git/Git_Board_F103RBT6/02_f103rbt6_RF_Module_HC12/My/CMSIS" -I"D:/04_Git/Git_Board_F103RBT6/02_f103rbt6_RF_Module_HC12/My/Main" -I"D:/04_Git/Git_Board_F103RBT6/02_f103rbt6_RF_Module_HC12/My/Sheduler" -I"D:/04_Git/Git_Board_F103RBT6/02_f103rbt6_RF_Module_HC12/My/Startup" -I"D:/04_Git/Git_Board_F103RBT6/02_f103rbt6_RF_Module_HC12/My/LCD" -I"D:/04_Git/Git_Board_F103RBT6/02_f103rbt6_RF_Module_HC12/My/Perif_Drv" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"My/Perif_Drv/timers_ST.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
My/Perif_Drv/uart_ST.o: ../My/Perif_Drv/uart_ST.c My/Perif_Drv/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -DSTM32F103RBTx -DSTM32 -DSTM32F1 -c -I"D:/04_Git/Git_Board_F103RBT6/02_f103rbt6_RF_Module_HC12/My/Application" -I"D:/04_Git/Git_Board_F103RBT6/02_f103rbt6_RF_Module_HC12/My/CMSIS" -I"D:/04_Git/Git_Board_F103RBT6/02_f103rbt6_RF_Module_HC12/My/Main" -I"D:/04_Git/Git_Board_F103RBT6/02_f103rbt6_RF_Module_HC12/My/Sheduler" -I"D:/04_Git/Git_Board_F103RBT6/02_f103rbt6_RF_Module_HC12/My/Startup" -I"D:/04_Git/Git_Board_F103RBT6/02_f103rbt6_RF_Module_HC12/My/LCD" -I"D:/04_Git/Git_Board_F103RBT6/02_f103rbt6_RF_Module_HC12/My/Perif_Drv" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"My/Perif_Drv/uart_ST.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

