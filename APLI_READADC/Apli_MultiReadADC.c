/*
 * Multi_ReadADC.c
 *
 *  Created on: Oct 4, 2025
 *      Author: PC
 */

#include "Apli_MultiReadADC.h"
#include "HEADWAVE_MCP3208.h"
#include "PROTOCAL_Kalman.h"
#include "Apli_RS485.h"

#define USE_KALMAN_FILTER

#define ENABLE_CS1_Pin GPIO_PIN_4
#define ENABLE_CS1_GPIO_Port GPIOA

MCP3208_SPI _SPI1_ADC1;

uint16_t Value_IRMS[2] = {0};

#ifdef USE_KALMAN_FILTER
Kalman_t kalman[2];

#endif

void Apli_Multi_Read_Init(void)
{
    MCP3208_Init(&_SPI1_ADC1, &hspi1, ENABLE_CS1_GPIO_Port, ENABLE_CS1_Pin);

#ifdef USE_KALMAN_FILTER
    uint16_t adc0 = MCP3208_Read_Channel(&_SPI1_ADC1, 0);
    for (uint8_t i = 0; i < 2; i++)
    {
        /* code */
        Kalman_Init(&kalman[i],
                    1E-5f, // Q
                    5E1f,  // R
                    adc0);
    }

#endif
}

void Apli_Multi_Read_Loop(void)
{
#ifdef USE_KALMAN_FILTER
    uint16_t Dummy;
    for (uint8_t i = 0; i < 2; i++)
    {
        /* code */
        Dummy = MCP3208_Read_Channel(&_SPI1_ADC1, i);
        float filtered = Kalman_Update(&kalman[i], (float)Dummy);
        Value_IRMS[i] = (uint16_t)(filtered * 4095.0f / (REGISTOR_MODBUS[VALUE_OF_VOLTAGE] / 100.0f)) * 100;
    }
#endif
}
