################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../APLI_OUTPUT/Apli_OutputChange10VDC.c 

OBJS += \
./APLI_OUTPUT/Apli_OutputChange10VDC.o 

C_DEPS += \
./APLI_OUTPUT/Apli_OutputChange10VDC.d 


# Each subdirectory must supply rules for building sources it contributes
APLI_OUTPUT/%.o APLI_OUTPUT/%.su APLI_OUTPUT/%.cyclo: ../APLI_OUTPUT/%.c APLI_OUTPUT/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"D:/2.PROJECT/14.Analog10VDC/3.SOURCE/3.Gateway_1.001/LIBRARY_EEPROM" -I"D:/2.PROJECT/14.Analog10VDC/3.SOURCE/3.Gateway_1.001/MODBUS" -I"D:/2.PROJECT/14.Analog10VDC/3.SOURCE/3.Gateway_1.001/MCP3208" -I"D:/2.PROJECT/14.Analog10VDC/3.SOURCE/3.Gateway_1.001/APLI_Modbus" -I"D:/2.PROJECT/14.Analog10VDC/3.SOURCE/3.Gateway_1.001/APLI_READADC" -I"D:/2.PROJECT/14.Analog10VDC/3.SOURCE/3.Gateway_1.001/KALMAN_FILTER" -I"D:/2.PROJECT/14.Analog10VDC/3.SOURCE/3.Gateway_1.001/APLI_EPPROM" -I"D:/2.PROJECT/14.Analog10VDC/3.SOURCE/3.Gateway_1.001/OUTPUTCHANGE10VDC" -I"D:/2.PROJECT/14.Analog10VDC/3.SOURCE/3.Gateway_1.001/APLI_OUTPUT" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-APLI_OUTPUT

clean-APLI_OUTPUT:
	-$(RM) ./APLI_OUTPUT/Apli_OutputChange10VDC.cyclo ./APLI_OUTPUT/Apli_OutputChange10VDC.d ./APLI_OUTPUT/Apli_OutputChange10VDC.o ./APLI_OUTPUT/Apli_OutputChange10VDC.su

.PHONY: clean-APLI_OUTPUT

