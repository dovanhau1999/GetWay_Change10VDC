################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include OUTPUTCHANGE10VDC/subdir.mk
-include MODBUS/subdir.mk
-include MCP3208/subdir.mk
-include LIBRARY_EEPROM/subdir.mk
-include KALMAN_FILTER/subdir.mk
-include Drivers/STM32F1xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include APLI_READADC/subdir.mk
-include APLI_OUTPUT/subdir.mk
-include APLI_Modbus/subdir.mk
-include APLI_EPPROM/subdir.mk
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


BUILD_ARTIFACT_NAME := 3.Gateway_1.001
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
3.Gateway_1.001.elf \

MAP_FILES += \
3.Gateway_1.001.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
3.Gateway_1.001.list \

OBJCOPY_HEX += \
3.Gateway_1.001.hex \


# All Target
all: main-build

# Main-build Target
main-build: 3.Gateway_1.001.elf secondary-outputs

# Tool invocations
3.Gateway_1.001.elf 3.Gateway_1.001.map: $(OBJS) $(USER_OBJS) C:\Users\Dell\Desktop\HAUDO\3.Gateway_1.001\3.SOURCE\3.SOURCE\3.Gateway_1.001\STM32F103C8TX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "3.Gateway_1.001.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"C:\Users\Dell\Desktop\HAUDO\3.Gateway_1.001\3.SOURCE\3.SOURCE\3.Gateway_1.001\STM32F103C8TX_FLASH.ld" --specs=nosys.specs -Wl,-Map="3.Gateway_1.001.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -u _printf_float -u _scanf_float -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

3.Gateway_1.001.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "3.Gateway_1.001.list"
	@echo 'Finished building: $@'
	@echo ' '

3.Gateway_1.001.hex: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O ihex $(EXECUTABLES) "3.Gateway_1.001.hex"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) 3.Gateway_1.001.elf 3.Gateway_1.001.hex 3.Gateway_1.001.list 3.Gateway_1.001.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_HEX)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
