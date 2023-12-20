################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../My/Startup/startup_stm32f103rbtx.s 

OBJS += \
./My/Startup/startup_stm32f103rbtx.o 

S_DEPS += \
./My/Startup/startup_stm32f103rbtx.d 


# Each subdirectory must supply rules for building sources it contributes
My/Startup/%.o: ../My/Startup/%.s My/Startup/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m3 -c -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@" "$<"

clean: clean-My-2f-Startup

clean-My-2f-Startup:
	-$(RM) ./My/Startup/startup_stm32f103rbtx.d ./My/Startup/startup_stm32f103rbtx.o

.PHONY: clean-My-2f-Startup

