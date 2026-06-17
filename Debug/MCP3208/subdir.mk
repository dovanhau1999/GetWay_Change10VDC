################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MCP3208/HARDWAVE_MCP3208.c 

OBJS += \
./MCP3208/HARDWAVE_MCP3208.o 

C_DEPS += \
./MCP3208/HARDWAVE_MCP3208.d 


# Each subdirectory must supply rules for building sources it contributes
MCP3208/%.o MCP3208/%.su MCP3208/%.cyclo: ../MCP3208/%.c MCP3208/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Dell/Desktop/HAUDO/3.Gateway_1.001/3.SOURCE/3.SOURCE/3.Gateway_1.001/LIBRARY_EEPROM" -I"C:/Users/Dell/Desktop/HAUDO/3.Gateway_1.001/3.SOURCE/3.SOURCE/3.Gateway_1.001/MODBUS" -I"C:/Users/Dell/Desktop/HAUDO/3.Gateway_1.001/3.SOURCE/3.SOURCE/3.Gateway_1.001/MCP3208" -I"C:/Users/Dell/Desktop/HAUDO/3.Gateway_1.001/3.SOURCE/3.SOURCE/3.Gateway_1.001/APLI_Modbus" -I"C:/Users/Dell/Desktop/HAUDO/3.Gateway_1.001/3.SOURCE/3.SOURCE/3.Gateway_1.001/APLI_READADC" -I"C:/Users/Dell/Desktop/HAUDO/3.Gateway_1.001/3.SOURCE/3.SOURCE/3.Gateway_1.001/KALMAN_FILTER" -I"C:/Users/Dell/Desktop/HAUDO/3.Gateway_1.001/3.SOURCE/3.SOURCE/3.Gateway_1.001/APLI_EPPROM" -I"C:/Users/Dell/Desktop/HAUDO/3.Gateway_1.001/3.SOURCE/3.SOURCE/3.Gateway_1.001/OUTPUTCHANGE10VDC" -I"C:/Users/Dell/Desktop/HAUDO/3.Gateway_1.001/3.SOURCE/3.SOURCE/3.Gateway_1.001/APLI_OUTPUT" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-MCP3208

clean-MCP3208:
	-$(RM) ./MCP3208/HARDWAVE_MCP3208.cyclo ./MCP3208/HARDWAVE_MCP3208.d ./MCP3208/HARDWAVE_MCP3208.o ./MCP3208/HARDWAVE_MCP3208.su

.PHONY: clean-MCP3208

