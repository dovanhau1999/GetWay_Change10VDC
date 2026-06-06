/*
 * Apli_OutputChange10VDC.c
 *
 *  Created on: Jun 6, 2026
 *      Author: PC
 */

#include "Apli_OutputChange10VDC.h"
#include "Output_Change.h"
#include "Apli_RS485.h"

#define ENABLE_CS2_Pin GPIO_PIN_12
#define ENABLE_CS2_GPIO_Port GPIOB

DAC8560_SPI _SPI2_DAC1;

void Apli_OutputChange10VDC_Init(void)
{
    DAC8560_Init(&_SPI2_DAC1, &hspi2, ENABLE_CS2_GPIO_Port, ENABLE_CS2_Pin);
}

void Apli_OutputChange10VDC_SetValue(void)
{
    static uint16_t value;
    value = REGISTOR_MODBUS[VALUE_OUTPUT_10VDC];
    DAC8560_WriteValue(&_SPI2_DAC1, value); // Giá trị được Set từ 0 : 65535, tương ứng với -10VDC : +10VDC
}
