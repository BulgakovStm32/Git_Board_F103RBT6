################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include My/Startup/subdir.mk
-include My/Sheduler/subdir.mk
-include My/STM32_Perif/subdir.mk
-include My/Main/subdir.mk
-include My/Display/subdir.mk
-include My/CMSIS/subdir.mk
-include My/Application/subdir.mk
-include MCUv7/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := f103rbt6_ADS1x15
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
f103rbt6_ADS1x15.elf \

MAP_FILES += \
f103rbt6_ADS1x15.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
f103rbt6_ADS1x15.list \

OBJCOPY_HEX += \
f103rbt6_ADS1x15.hex \


# All Target
all: main-build

# Main-build Target
main-build: f103rbt6_ADS1x15.elf secondary-outputs

# Tool invocations
f103rbt6_ADS1x15.elf f103rbt6_ADS1x15.map: $(OBJS) $(USER_OBJS) E:\Anton\07_Git\Git_Board_F103RBT6\04_f103rbt6_ADS1x15\My\Startup\STM32F103RBTX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "f103rbt6_ADS1x15.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"E:\Anton\07_Git\Git_Board_F103RBT6\04_f103rbt6_ADS1x15\My\Startup\STM32F103RBTX_FLASH.ld" --specs=nosys.specs -Wl,-Map="f103rbt6_ADS1x15.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

f103rbt6_ADS1x15.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "f103rbt6_ADS1x15.list"
	@echo 'Finished building: $@'
	@echo ' '

f103rbt6_ADS1x15.hex: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O ihex $(EXECUTABLES) "f103rbt6_ADS1x15.hex"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) default.size.stdout f103rbt6_ADS1x15.elf f103rbt6_ADS1x15.hex f103rbt6_ADS1x15.list f103rbt6_ADS1x15.map
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_HEX)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
