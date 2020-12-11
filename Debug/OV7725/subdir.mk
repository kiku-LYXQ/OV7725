################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../OV7725/ov7725.c \
../OV7725/sccb.c 

OBJS += \
./OV7725/ov7725.o \
./OV7725/sccb.o 

C_DEPS += \
./OV7725/ov7725.d \
./OV7725/sccb.d 


# Each subdirectory must supply rules for building sources it contributes
OV7725/ov7725.o: ../OV7725/ov7725.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DDEBUG -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../DELAY -I../OV7725 -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"OV7725/ov7725.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
OV7725/sccb.o: ../OV7725/sccb.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DDEBUG -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../DELAY -I../OV7725 -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"OV7725/sccb.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

