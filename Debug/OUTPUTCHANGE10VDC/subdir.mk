################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../OUTPUTCHANGE10VDC/Output_Change.c 

OBJS += \
./OUTPUTCHANGE10VDC/Output_Change.o 

C_DEPS += \
./OUTPUTCHANGE10VDC/Output_Change.d 


# Each subdirectory must supply rules for building sources it contributes
OUTPUTCHANGE10VDC/%.o OUTPUTCHANGE10VDC/%.su OUTPUTCHANGE10VDC/%.cyclo: ../OUTPUTCHANGE10VDC/%.c OUTPUTCHANGE10VDC/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"D:/2.PROJECT/14.Analog10VDC/3.SOURCE/3.Gateway_1.001/LIBRARY_EEPROM" -I"D:/2.PROJECT/14.Analog10VDC/3.SOURCE/3.Gateway_1.001/MODBUS" -I"D:/2.PROJECT/14.Analog10VDC/3.SOURCE/3.Gateway_1.001/MCP3208" -I"D:/2.PROJECT/14.Analog10VDC/3.SOURCE/3.Gateway_1.001/APLI_Modbus" -I"D:/2.PROJECT/14.Analog10VDC/3.SOURCE/3.Gateway_1.001/APLI_READADC" -I"D:/2.PROJECT/14.Analog10VDC/3.SOURCE/3.Gateway_1.001/KALMAN_FILTER" -I"D:/2.PROJECT/14.Analog10VDC/3.SOURCE/3.Gateway_1.001/APLI_EPPROM" -I"D:/2.PROJECT/14.Analog10VDC/3.SOURCE/3.Gateway_1.001/OUTPUTCHANGE10VDC" -I"D:/2.PROJECT/14.Analog10VDC/3.SOURCE/3.Gateway_1.001/APLI_OUTPUT" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-OUTPUTCHANGE10VDC

clean-OUTPUTCHANGE10VDC:
	-$(RM) ./OUTPUTCHANGE10VDC/Output_Change.cyclo ./OUTPUTCHANGE10VDC/Output_Change.d ./OUTPUTCHANGE10VDC/Output_Change.o ./OUTPUTCHANGE10VDC/Output_Change.su

.PHONY: clean-OUTPUTCHANGE10VDC

