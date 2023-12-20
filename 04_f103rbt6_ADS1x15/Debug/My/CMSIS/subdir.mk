################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../My/CMSIS/system_stm32f1xx.c 

OBJS += \
./My/CMSIS/system_stm32f1xx.o 

C_DEPS += \
./My/CMSIS/system_stm32f1xx.d 


# Each subdirectory must supply rules for building sources it contributes
My/CMSIS/%.o My/CMSIS/%.su My/CMSIS/%.cyclo: ../My/CMSIS/%.c My/CMSIS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32F103RBTx -DSTM32 -DSTM32F1 -c -I"E:/Anton/07_Git/Git_Board_F103RBT6/04_f103rbt6_ADS1x15/MCUv7" -I"E:/Anton/07_Git/Git_Board_F103RBT6/04_f103rbt6_ADS1x15/My/Application" -I"E:/Anton/07_Git/Git_Board_F103RBT6/04_f103rbt6_ADS1x15/My/CMSIS" -I"E:/Anton/07_Git/Git_Board_F103RBT6/04_f103rbt6_ADS1x15/My/Display" -I"E:/Anton/07_Git/Git_Board_F103RBT6/04_f103rbt6_ADS1x15/My/Main" -I"E:/Anton/07_Git/Git_Board_F103RBT6/04_f103rbt6_ADS1x15/My/Sheduler" -I"E:/Anton/07_Git/Git_Board_F103RBT6/04_f103rbt6_ADS1x15/My/Startup" -I"E:/Anton/07_Git/Git_Board_F103RBT6/04_f103rbt6_ADS1x15/My/STM32_Perif" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-My-2f-CMSIS

clean-My-2f-CMSIS:
	-$(RM) ./My/CMSIS/system_stm32f1xx.cyclo ./My/CMSIS/system_stm32f1xx.d ./My/CMSIS/system_stm32f1xx.o ./My/CMSIS/system_stm32f1xx.su

.PHONY: clean-My-2f-CMSIS

