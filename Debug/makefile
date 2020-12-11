################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include OV7725/subdir.mk
-include Drivers/STM32F1xx_HAL_Driver/Src/subdir.mk
-include DELAY/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include subdir.mk
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

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
OV7725.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
OV7725.list \

OBJCOPY_BIN += \
OV7725.bin \


# All Target
all: OV7725.elf secondary-outputs

# Tool invocations
OV7725.elf: $(OBJS) $(USER_OBJS) D:\STM32cubeIDE\code\OV7725\STM32F103C8TX_FLASH.ld
	arm-none-eabi-gcc -o "OV7725.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"D:\STM32cubeIDE\code\OV7725\STM32F103C8TX_FLASH.ld" --specs=nosys.specs -Wl,-Map="OV7725.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

OV7725.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "OV7725.list"
	@echo 'Finished building: $@'
	@echo ' '

OV7725.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "OV7725.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
