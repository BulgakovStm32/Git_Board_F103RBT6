################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../My/Application/AHT10.c \
../My/Application/Blink.c \
../My/Application/Buttons.c \
../My/Application/Config.c \
../My/Application/Crc.c \
../My/Application/DS18B20.c \
../My/Application/DS2782.c \
../My/Application/Delay.c \
../My/Application/Encoder.c \
../My/Application/Filters.c \
../My/Application/MyString.c \
../My/Application/PID.c \
../My/Application/Time.c 

OBJS += \
./My/Application/AHT10.o \
./My/Application/Blink.o \
./My/Application/Buttons.o \
./My/Application/Config.o \
./My/Application/Crc.o \
./My/Application/DS18B20.o \
./My/Application/DS2782.o \
./My/Application/Delay.o \
./My/Application/Encoder.o \
./My/Application/Filters.o \
./My/Application/MyString.o \
./My/Application/PID.o \
./My/Application/Time.o 

C_DEPS += \
./My/Application/AHT10.d \
./My/Application/Blink.d \
./My/Application/Buttons.d \
./My/Application/Config.d \
./My/Application/Crc.d \
./My/Application/DS18B20.d \
./My/Application/DS2782.d \
./My/Application/Delay.d \
./My/Application/Encoder.d \
./My/Application/Filters.d \
./My/Application/MyString.d \
./My/Application/PID.d \
./My/Application/Time.d 


# Each subdirectory must supply rules for building sources it contributes
My/Application/%.o My/Application/%.su My/Application/%.cyclo: ../My/Application/%.c My/Application/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -DSTM32F103RBTx -DSTM32 -DSTM32F1 -c -I"E:/Anton/07_Git/Git_Board_F103RBT6/04_f103rbt6_ADS1x15/MCUv7" -I"E:/Anton/07_Git/Git_Board_F103RBT6/04_f103rbt6_ADS1x15/My/Application" -I"E:/Anton/07_Git/Git_Board_F103RBT6/04_f103rbt6_ADS1x15/My/CMSIS" -I"E:/Anton/07_Git/Git_Board_F103RBT6/04_f103rbt6_ADS1x15/My/Display" -I"E:/Anton/07_Git/Git_Board_F103RBT6/04_f103rbt6_ADS1x15/My/Main" -I"E:/Anton/07_Git/Git_Board_F103RBT6/04_f103rbt6_ADS1x15/My/Sheduler" -I"E:/Anton/07_Git/Git_Board_F103RBT6/04_f103rbt6_ADS1x15/My/Startup" -I"E:/Anton/07_Git/Git_Board_F103RBT6/04_f103rbt6_ADS1x15/My/STM32_Perif" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-My-2f-Application

clean-My-2f-Application:
	-$(RM) ./My/Application/AHT10.cyclo ./My/Application/AHT10.d ./My/Application/AHT10.o ./My/Application/AHT10.su ./My/Application/Blink.cyclo ./My/Application/Blink.d ./My/Application/Blink.o ./My/Application/Blink.su ./My/Application/Buttons.cyclo ./My/Application/Buttons.d ./My/Application/Buttons.o ./My/Application/Buttons.su ./My/Application/Config.cyclo ./My/Application/Config.d ./My/Application/Config.o ./My/Application/Config.su ./My/Application/Crc.cyclo ./My/Application/Crc.d ./My/Application/Crc.o ./My/Application/Crc.su ./My/Application/DS18B20.cyclo ./My/Application/DS18B20.d ./My/Application/DS18B20.o ./My/Application/DS18B20.su ./My/Application/DS2782.cyclo ./My/Application/DS2782.d ./My/Application/DS2782.o ./My/Application/DS2782.su ./My/Application/Delay.cyclo ./My/Application/Delay.d ./My/Application/Delay.o ./My/Application/Delay.su ./My/Application/Encoder.cyclo ./My/Application/Encoder.d ./My/Application/Encoder.o ./My/Application/Encoder.su ./My/Application/Filters.cyclo ./My/Application/Filters.d ./My/Application/Filters.o ./My/Application/Filters.su ./My/Application/MyString.cyclo ./My/Application/MyString.d ./My/Application/MyString.o ./My/Application/MyString.su ./My/Application/PID.cyclo ./My/Application/PID.d ./My/Application/PID.o ./My/Application/PID.su ./My/Application/Time.cyclo ./My/Application/Time.d ./My/Application/Time.o ./My/Application/Time.su

.PHONY: clean-My-2f-Application

