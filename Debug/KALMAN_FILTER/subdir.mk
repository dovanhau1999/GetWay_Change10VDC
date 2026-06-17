################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../KALMAN_FILTER/PROTOCAL_Kalman.c 

OBJS += \
./KALMAN_FILTER/PROTOCAL_Kalman.o 

C_DEPS += \
./KALMAN_FILTER/PROTOCAL_Kalman.d 


# Each subdirectory must supply rules for building sources it contributes
KALMAN_FILTER/%.o KALMAN_FILTER/%.su KALMAN_FILTER/%.cyclo: ../KALMAN_FILTER/%.c KALMAN_FILTER/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Dell/Desktop/HAUDO/3.Gateway_1.001/3.SOURCE/3.SOURCE/3.Gateway_1.001/LIBRARY_EEPROM" -I"C:/Users/Dell/Desktop/HAUDO/3.Gateway_1.001/3.SOURCE/3.SOURCE/3.Gateway_1.001/MODBUS" -I"C:/Users/Dell/Desktop/HAUDO/3.Gateway_1.001/3.SOURCE/3.SOURCE/3.Gateway_1.001/MCP3208" -I"C:/Users/Dell/Desktop/HAUDO/3.Gateway_1.001/3.SOURCE/3.SOURCE/3.Gateway_1.001/APLI_Modbus" -I"C:/Users/Dell/Desktop/HAUDO/3.Gateway_1.001/3.SOURCE/3.SOURCE/3.Gateway_1.001/APLI_READADC" -I"C:/Users/Dell/Desktop/HAUDO/3.Gateway_1.001/3.SOURCE/3.SOURCE/3.Gateway_1.001/KALMAN_FILTER" -I"C:/Users/Dell/Desktop/HAUDO/3.Gateway_1.001/3.SOURCE/3.SOURCE/3.Gateway_1.001/APLI_EPPROM" -I"C:/Users/Dell/Desktop/HAUDO/3.Gateway_1.001/3.SOURCE/3.SOURCE/3.Gateway_1.001/OUTPUTCHANGE10VDC" -I"C:/Users/Dell/Desktop/HAUDO/3.Gateway_1.001/3.SOURCE/3.SOURCE/3.Gateway_1.001/APLI_OUTPUT" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-KALMAN_FILTER

clean-KALMAN_FILTER:
	-$(RM) ./KALMAN_FILTER/PROTOCAL_Kalman.cyclo ./KALMAN_FILTER/PROTOCAL_Kalman.d ./KALMAN_FILTER/PROTOCAL_Kalman.o ./KALMAN_FILTER/PROTOCAL_Kalman.su

.PHONY: clean-KALMAN_FILTER

