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

MCP3208_SPI _SPI1_ADC;

int16_t Value_VRMS[2] = {0};

#ifdef USE_KALMAN_FILTER
Kalman_t kalman[2];

#endif

void Apli_Multi_Read_Init(void)
{
    MCP3208_Init(&_SPI1_ADC, &hspi1, ENABLE_CS1_GPIO_Port, ENABLE_CS1_Pin);

#ifdef USE_KALMAN_FILTER
    for (uint8_t i = 0; i < 2; i++)
    {
        /* code */
        uint16_t adc = MCP3208_Read_Channel(&_SPI1_ADC, i);
        Kalman_Init(&kalman[i],
                    5E-3f, // Q tỉ lệ thuận với độ trễ (Q càng nhỏ thì thay đổi giá trị càng chậm)
                    5E1f,  // R tỉ lệ nghịch với độ nhiễu (R càng nhỏ thì lọc nhiều nhiễu hơn, độ trễ hơn)
                    adc);
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
        Dummy = MCP3208_Read_Channel(&_SPI1_ADC, i);
        float filtered = Kalman_Update(&kalman[i], (float)Dummy);
        Value_VRMS[i] = (int32_t)((filtered * 360.0f / 4095.0f - 180.0f) * 10.0f); /**Chuyển đổi giá trị ADC sang góc - Từ -180...+180 độ tương ứng vơi 0...4095 của ADC
                                                                                    * Sau đó nhân với 10 để có giá trị 1 chữ số thập phân
                                                                                    */
    }
#endif
}
