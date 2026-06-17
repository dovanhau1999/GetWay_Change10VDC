################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MODBUS/HARDWAVE_MB.c \
../MODBUS/PROTOCOL_RS485.c 

OBJS += \
./MODBUS/HARDWAVE_MB.o \
./MODBUS/PROTOCOL_RS485.o 

C_DEPS += \
./MODBUS/HARDWAVE_MB.d \
./MODBUS/PROTOCOL_RS485.d 


# Each subdirectory must supply rules for building sources it contributes
MODBUS/%.o MODBUS/%.su MODBUS/%.cyclo: ../MODBUS/%.c MODBUS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Dell/Desktop/HAUDO/3.Gateway_1.001/3.SOURCE/3.SOURCE/3.Gateway_1.001/LIBRARY_EEPROM" -I"C:/Users/Dell/Desktop/HAUDO/3.Gateway_1.001/3.SOURCE/3.SOURCE/3.Gateway_1.001/MODBUS" -I"C:/Users/Dell/Desktop/HAUDO/3.Gateway_1.001/3.SOURCE/3.SOURCE/3.Gateway_1.001/MCP3208" -I"C:/Users/Dell/Desktop/HAUDO/3.Gateway_1.001/3.SOURCE/3.SOURCE/3.Gateway_1.001/APLI_Modbus" -I"C:/Users/Dell/Desktop/HAUDO/3.Gateway_1.001/3.SOURCE/3.SOURCE/3.Gateway_1.001/APLI_READADC" -I"C:/Users/Dell/Desktop/HAUDO/3.Gateway_1.001/3.SOURCE/3.SOURCE/3.Gateway_1.001/KALMAN_FILTER" -I"C:/Users/Dell/Desktop/HAUDO/3.Gateway_1.001/3.SOURCE/3.SOURCE/3.Gateway_1.001/APLI_EPPROM" -I"C:/Users/Dell/Desktop/HAUDO/3.Gateway_1.001/3.SOURCE/3.SOURCE/3.Gateway_1.001/OUTPUTCHANGE10VDC" -I"C:/Users/Dell/Desktop/HAUDO/3.Gateway_1.001/3.SOURCE/3.SOURCE/3.Gateway_1.001/APLI_OUTPUT" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-MODBUS

clean-MODBUS:
	-$(RM) ./MODBUS/HARDWAVE_MB.cyclo ./MODBUS/HARDWAVE_MB.d ./MODBUS/HARDWAVE_MB.o ./MODBUS/HARDWAVE_MB.su ./MODBUS/PROTOCOL_RS485.cyclo ./MODBUS/PROTOCOL_RS485.d ./MODBUS/PROTOCOL_RS485.o ./MODBUS/PROTOCOL_RS485.su

.PHONY: clean-MODBUS

