################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MCUv7/GpioMCU.c \
../MCUv7/Protocol_I2C.c 

OBJS += \
./MCUv7/GpioMCU.o \
./MCUv7/Protocol_I2C.o 

C_DEPS += \
./MCUv7/GpioMCU.d \
./MCUv7/Protocol_I2C.d 


# Each subdirectory must supply rules for building sources it contributes
MCUv7/%.o MCUv7/%.su MCUv7/%.cyclo: ../MCUv7/%.c MCUv7/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32F103RBTx -DSTM32 -DSTM32F1 -c -I"E:/Anton/07_Git/Git_Board_F103RBT6/04_f103rbt6_ADS1x15/MCUv7" -I"E:/Anton/07_Git/Git_Board_F103RBT6/04_f103rbt6_ADS1x15/My/Application" -I"E:/Anton/07_Git/Git_Board_F103RBT6/04_f103rbt6_ADS1x15/My/CMSIS" -I"E:/Anton/07_Git/Git_Board_F103RBT6/04_f103rbt6_ADS1x15/My/Display" -I"E:/Anton/07_Git/Git_Board_F103RBT6/04_f103rbt6_ADS1x15/My/Main" -I"E:/Anton/07_Git/Git_Board_F103RBT6/04_f103rbt6_ADS1x15/My/Sheduler" -I"E:/Anton/07_Git/Git_Board_F103RBT6/04_f103rbt6_ADS1x15/My/Startup" -I"E:/Anton/07_Git/Git_Board_F103RBT6/04_f103rbt6_ADS1x15/My/STM32_Perif" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-MCUv7

clean-MCUv7:
	-$(RM) ./MCUv7/GpioMCU.cyclo ./MCUv7/GpioMCU.d ./MCUv7/GpioMCU.o ./MCUv7/GpioMCU.su ./MCUv7/Protocol_I2C.cyclo ./MCUv7/Protocol_I2C.d ./MCUv7/Protocol_I2C.o ./MCUv7/Protocol_I2C.su

.PHONY: clean-MCUv7

