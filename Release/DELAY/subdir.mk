################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../DELAY/delay.c 

OBJS += \
./DELAY/delay.o 

C_DEPS += \
./DELAY/delay.d 


# Each subdirectory must supply rules for building sources it contributes
DELAY/delay.o: ../DELAY/delay.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../OV7725 -I../DELAY -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"DELAY/delay.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

