################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../LIBRARY_EEPROM/PROTOCAL_EEPROM.c 

OBJS += \
./LIBRARY_EEPROM/PROTOCAL_EEPROM.o 

C_DEPS += \
./LIBRARY_EEPROM/PROTOCAL_EEPROM.d 


# Each subdirectory must supply rules for building sources it contributes
LIBRARY_EEPROM/%.o LIBRARY_EEPROM/%.su LIBRARY_EEPROM/%.cyclo: ../LIBRARY_EEPROM/%.c LIBRARY_EEPROM/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"D:/2.PROJECT/14.Analog10VDC/3.SOURCE/3.Gateway_1.001/LIBRARY_EEPROM" -I"D:/2.PROJECT/14.Analog10VDC/3.SOURCE/3.Gateway_1.001/MODBUS" -I"D:/2.PROJECT/14.Analog10VDC/3.SOURCE/3.Gateway_1.001/MCP3208" -I"D:/2.PROJECT/14.Analog10VDC/3.SOURCE/3.Gateway_1.001/APLI_Modbus" -I"D:/2.PROJECT/14.Analog10VDC/3.SOURCE/3.Gateway_1.001/APLI_READADC" -I"D:/2.PROJECT/14.Analog10VDC/3.SOURCE/3.Gateway_1.001/KALMAN_FILTER" -I"D:/2.PROJECT/14.Analog10VDC/3.SOURCE/3.Gateway_1.001/APLI_EPPROM" -I"D:/2.PROJECT/14.Analog10VDC/3.SOURCE/3.Gateway_1.001/OUTPUTCHANGE10VDC" -I"D:/2.PROJECT/14.Analog10VDC/3.SOURCE/3.Gateway_1.001/APLI_OUTPUT" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-LIBRARY_EEPROM

clean-LIBRARY_EEPROM:
	-$(RM) ./LIBRARY_EEPROM/PROTOCAL_EEPROM.cyclo ./LIBRARY_EEPROM/PROTOCAL_EEPROM.d ./LIBRARY_EEPROM/PROTOCAL_EEPROM.o ./LIBRARY_EEPROM/PROTOCAL_EEPROM.su

.PHONY: clean-LIBRARY_EEPROM

