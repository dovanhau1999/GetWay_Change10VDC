/*
 * Multi_ReadADC.c
 *
 *  Created on: Oct 4, 2025
 *      Author: PC
 */

#include "Apli_MultiReadADC.h"
#include "Apli_RS485.h"
#include "HEADWAVE_MCP3208.h"
#include "PROTOCAL_Kalman.h"
#include "Apli_RS485.h"

#define USE_KALMAN_FILTER

#define ENABLE_CS1_Pin GPIO_PIN_4
#define ENABLE_CS1_GPIO_Port GPIOA

MCP3208_SPI _SPI1_ADC;

// extern uint16_t last_ValueSetSector;
extern uint16_t last_ADC_N40;
extern uint16_t last_ADC_N30;
extern uint16_t last_ADC_N20;
extern uint16_t last_ADC_N10;
extern uint16_t last_ADC_0;
extern uint16_t last_ADC_P10;
extern uint16_t last_ADC_P20;
extern uint16_t last_ADC_P30;
extern uint16_t last_ADC_P40;

float Value_ADCVolt_filtered[2] = {0};
uint16_t Value_Of_VoltADC[2] = {0};
int16_t OutputAngle;

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
                    2E-3f, // Q tỉ lệ thuận với độ trễ (Q càng nhỏ thì thay đổi giá trị càng chậm)
                    5E1f,  // R tỉ lệ nghịch với độ nhiễu (R càng nhỏ thì lọc nhiều nhiễu hơn, độ trễ hơn)
                    adc);
    }

#endif
}

void Apli_Multi_Read_Loop(void)
{
#ifdef USE_KALMAN_FILTER

    Value_Of_VoltADC[0] = MCP3208_Read_Channel(&_SPI1_ADC, 0);
    Value_ADCVolt_filtered[0] = Kalman_Update(&kalman[0], (float)Value_Of_VoltADC[0]);
    // OutputAngle = (int16_t)(((Value_ADCVolt_filtered[0] - last_ValueSetSector) * 360.0f / 4096.0f) * 10.0f);

    Value_Of_VoltADC[1] = MCP3208_Read_Channel(&_SPI1_ADC, 1);
    Value_ADCVolt_filtered[1] = Kalman_Update(&kalman[1], (float)Value_Of_VoltADC[1]);

     if ((Value_ADCVolt_filtered[0] < last_ADC_0) && (Value_ADCVolt_filtered[0] >= last_ADC_N30))
     {
         OutputAngle = (Value_ADCVolt_filtered[0] - last_ADC_N30) * 300 / (last_ADC_0 - last_ADC_N30) - 300;
     }
     else if ((Value_ADCVolt_filtered[0] >= last_ADC_0) && (Value_ADCVolt_filtered[0] < last_ADC_P30))
     {
         OutputAngle = (Value_ADCVolt_filtered[0] - last_ADC_0) * 300 / (last_ADC_P30 - last_ADC_0);
     }

     if ((Value_ADCVolt_filtered[0] < last_ADC_N30) || (Value_ADCVolt_filtered[0] > last_ADC_P30))
     {
         OutputAngle = (Value_ADCVolt_filtered[0] - last_ADC_0) * 3600.0f / 4096.0f;
     }

//    if (Value_ADCVolt_filtered[0] >= last_ADC_N40)
//    {
//        OutputAngle = (Value_ADCVolt_filtered[0] - last_ADC_N40) * 100 /
//                          (last_ADC_N30 - last_ADC_N40) -
//                      400;
//    }
//    else if (Value_ADCVolt_filtered[0] > last_ADC_N30)
//    {
//        OutputAngle = (Value_ADCVolt_filtered[0] - last_ADC_N30) * 100 /
//                          (last_ADC_N20 - last_ADC_N30) -
//                      300;
//    }
//    else if (Value_ADCVolt_filtered[0] > last_ADC_N20)
//    {
//        OutputAngle = (Value_ADCVolt_filtered[0] - last_ADC_N20) * 100 /
//                          (last_ADC_N10 - last_ADC_N20) -
//                      200;
//    }
//    else if (Value_ADCVolt_filtered[0] > last_ADC_N10)
//    {
//        OutputAngle = (Value_ADCVolt_filtered[0] - last_ADC_N10) * 100 /
//                          (last_ADC_0 - last_ADC_N10) -
//                      100;
//    }
//    else if (Value_ADCVolt_filtered[0] < last_ADC_P10)
//    {
//        OutputAngle = (Value_ADCVolt_filtered[0] - last_ADC_P10) * 100 /
//                      (last_ADC_P10 - last_ADC_0);
//    }
//    else if (Value_ADCVolt_filtered[0] < last_ADC_P20)
//    {
//        OutputAngle = (Value_ADCVolt_filtered[0] - last_ADC_P20) * 100 /
//                          (last_ADC_P20 - last_ADC_P10) +
//                      100;
//    }
//    else if (Value_ADCVolt_filtered[0] < last_ADC_P30)
//    {
//        OutputAngle = (Value_ADCVolt_filtered[0] - last_ADC_P20) * 100 /
//                          (last_ADC_P30 - last_ADC_P20) +
//                      200;
//    }
//    else if (Value_ADCVolt_filtered[0] <= last_ADC_P40)
//    {
//        OutputAngle = (Value_ADCVolt_filtered[0] - last_ADC_P30) * 100 /
//                          (last_ADC_P40 - last_ADC_P30) +
//                      300;
//    }
//
//    if (Value_ADCVolt_filtered[0] > last_ADC_P40)
//    {
//        // Ngoài vùng +40°
//        OutputAngle = (Value_ADCVolt_filtered[0] - last_ADC_0) * 3600L / 4096L;
//    }
//
//    if (Value_ADCVolt_filtered[0] < last_ADC_N40)
//    {
//        // Ngoài vùng -40°
//        OutputAngle = (Value_ADCVolt_filtered[0] - last_ADC_0) * 3600L / 4096L;
//    }
#endif
}
