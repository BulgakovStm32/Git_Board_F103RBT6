################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../My/Sheduler/Scheduler.c \
../My/Sheduler/rtos.c 

OBJS += \
./My/Sheduler/Scheduler.o \
./My/Sheduler/rtos.o 

C_DEPS += \
./My/Sheduler/Scheduler.d \
./My/Sheduler/rtos.d 


# Each subdirectory must supply rules for building sources it contributes
My/Sheduler/Scheduler.o: ../My/Sheduler/Scheduler.c My/Sheduler/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -DSTM32F103RBTx -DSTM32 -DSTM32F1 -c -I"D:/04_Git/Git_Board_F103RBT6/02_f103rbt6_RF_Module_HC12/My/Application" -I"D:/04_Git/Git_Board_F103RBT6/02_f103rbt6_RF_Module_HC12/My/CMSIS" -I"D:/04_Git/Git_Board_F103RBT6/02_f103rbt6_RF_Module_HC12/My/Main" -I"D:/04_Git/Git_Board_F103RBT6/02_f103rbt6_RF_Module_HC12/My/Sheduler" -I"D:/04_Git/Git_Board_F103RBT6/02_f103rbt6_RF_Module_HC12/My/Startup" -I"D:/04_Git/Git_Board_F103RBT6/02_f103rbt6_RF_Module_HC12/My/LCD" -I"D:/04_Git/Git_Board_F103RBT6/02_f103rbt6_RF_Module_HC12/My/Perif_Drv" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"My/Sheduler/Scheduler.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
My/Sheduler/rtos.o: ../My/Sheduler/rtos.c My/Sheduler/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -DSTM32F103RBTx -DSTM32 -DSTM32F1 -c -I"D:/04_Git/Git_Board_F103RBT6/02_f103rbt6_RF_Module_HC12/My/Application" -I"D:/04_Git/Git_Board_F103RBT6/02_f103rbt6_RF_Module_HC12/My/CMSIS" -I"D:/04_Git/Git_Board_F103RBT6/02_f103rbt6_RF_Module_HC12/My/Main" -I"D:/04_Git/Git_Board_F103RBT6/02_f103rbt6_RF_Module_HC12/My/Sheduler" -I"D:/04_Git/Git_Board_F103RBT6/02_f103rbt6_RF_Module_HC12/My/Startup" -I"D:/04_Git/Git_Board_F103RBT6/02_f103rbt6_RF_Module_HC12/My/LCD" -I"D:/04_Git/Git_Board_F103RBT6/02_f103rbt6_RF_Module_HC12/My/Perif_Drv" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"My/Sheduler/rtos.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

