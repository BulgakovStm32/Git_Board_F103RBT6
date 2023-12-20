################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../My/Display/Ascii_Tab_12864.c \
../My/Display/LM6063D.c \
../My/Display/LcdGraphic.c \
../My/Display/Lcd_TIC32.c \
../My/Display/Lcd_i2c_1602.c \
../My/Display/fonts.c \
../My/Display/ssd1306.c 

OBJS += \
./My/Display/Ascii_Tab_12864.o \
./My/Display/LM6063D.o \
./My/Display/LcdGraphic.o \
./My/Display/Lcd_TIC32.o \
./My/Display/Lcd_i2c_1602.o \
./My/Display/fonts.o \
./My/Display/ssd1306.o 

C_DEPS += \
./My/Display/Ascii_Tab_12864.d \
./My/Display/LM6063D.d \
./My/Display/LcdGraphic.d \
./My/Display/Lcd_TIC32.d \
./My/Display/Lcd_i2c_1602.d \
./My/Display/fonts.d \
./My/Display/ssd1306.d 


# Each subdirectory must supply rules for building sources it contributes
My/Display/%.o My/Display/%.su My/Display/%.cyclo: ../My/Display/%.c My/Display/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32F103RBTx -DSTM32 -DSTM32F1 -c -I"E:/Anton/07_Git/Git_Board_F103RBT6/04_f103rbt6_ADS1x15/MCUv7" -I"E:/Anton/07_Git/Git_Board_F103RBT6/04_f103rbt6_ADS1x15/My/Application" -I"E:/Anton/07_Git/Git_Board_F103RBT6/04_f103rbt6_ADS1x15/My/CMSIS" -I"E:/Anton/07_Git/Git_Board_F103RBT6/04_f103rbt6_ADS1x15/My/Display" -I"E:/Anton/07_Git/Git_Board_F103RBT6/04_f103rbt6_ADS1x15/My/Main" -I"E:/Anton/07_Git/Git_Board_F103RBT6/04_f103rbt6_ADS1x15/My/Sheduler" -I"E:/Anton/07_Git/Git_Board_F103RBT6/04_f103rbt6_ADS1x15/My/Startup" -I"E:/Anton/07_Git/Git_Board_F103RBT6/04_f103rbt6_ADS1x15/My/STM32_Perif" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-My-2f-Display

clean-My-2f-Display:
	-$(RM) ./My/Display/Ascii_Tab_12864.cyclo ./My/Display/Ascii_Tab_12864.d ./My/Display/Ascii_Tab_12864.o ./My/Display/Ascii_Tab_12864.su ./My/Display/LM6063D.cyclo ./My/Display/LM6063D.d ./My/Display/LM6063D.o ./My/Display/LM6063D.su ./My/Display/LcdGraphic.cyclo ./My/Display/LcdGraphic.d ./My/Display/LcdGraphic.o ./My/Display/LcdGraphic.su ./My/Display/Lcd_TIC32.cyclo ./My/Display/Lcd_TIC32.d ./My/Display/Lcd_TIC32.o ./My/Display/Lcd_TIC32.su ./My/Display/Lcd_i2c_1602.cyclo ./My/Display/Lcd_i2c_1602.d ./My/Display/Lcd_i2c_1602.o ./My/Display/Lcd_i2c_1602.su ./My/Display/fonts.cyclo ./My/Display/fonts.d ./My/Display/fonts.o ./My/Display/fonts.su ./My/Display/ssd1306.cyclo ./My/Display/ssd1306.d ./My/Display/ssd1306.o ./My/Display/ssd1306.su

.PHONY: clean-My-2f-Display

