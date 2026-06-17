/*
 * Apli_OutputChange10VDC.c
 *
 *  Created on: Jun 6, 2026
 *      Author: PC
 */

#include "Apli_OutputChange10VDC.h"
#include "Output_Change.h"

#define ENABLE_CS2_Pin GPIO_PIN_12
#define ENABLE_CS2_GPIO_Port GPIOB

// extern uint16_t last_ValueSetTerminal;
// extern uint16_t last_ValueSetSector;
// extern uint16_t last_SetMinADCOutput;
// extern uint16_t last_SetMaxADCOutput;
extern float Value_ADCVolt_filtered[2];
extern uint16_t last_ADC_N40;
extern uint16_t last_ADC_0;
extern uint16_t last_ADC_P40;

// static float Kmin = 0;
// static float Kmax = 0;
static int32_t OUTPUT = 32687;

DAC8560_SPI _SPI2_DAC1;

void Apli_OutputChange10VDC_Init(void)
{
    DAC8560_Init(&_SPI2_DAC1, &hspi2, ENABLE_CS2_GPIO_Port, ENABLE_CS2_Pin);
    DAC8560_EnableInternalVref(&_SPI2_DAC1);

    // Kmin = (float)(1000.0f / last_SetMinADCOutput); // Hệ số x100
    // Kmax = (float)(1000.0f / last_SetMaxADCOutput);
}

void Apli_OutputChange10VDC_SetValue(void)
{
    // float_t dummy_angle = (Value_ADCVolt_filtered[0] - last_ValueSetSector) / 11.375f; // Tìm ra góc thay đổi theo Sector

    // float dummy_OutputZERO = last_ValueSetTerminal * 16.00f; // ADC output để đồng hồ chỉ 0 độ

    // if (dummy_angle <= -45.0f)
    // {
    //     OUTPUT = 0;
    // }
    // else if (dummy_angle >= 45.0f)
    // {
    //     OUTPUT = 65535;
    // }
    // else if ((dummy_angle > -45.0f) && (dummy_angle < -38.00f))
    //     {
    //         OUTPUT = (dummy_OutputZERO + (dummy_angle * 727.18f)) * 0.98;
    //     }
    // else if ((dummy_angle >= -38.0f) && (dummy_angle < -28.00f))
    // {
    //     OUTPUT = (dummy_OutputZERO + (dummy_angle * 727.18f)) * 0.997;
    // }
    // else if ((dummy_angle >= -28.0f) && (dummy_angle < -18.00f))
    //     {
    //         OUTPUT = (dummy_OutputZERO + (dummy_angle * 727.18f)) * 1.02;
    //     }
    // else if ((dummy_angle >= 18.00f) && (dummy_angle < 45.0f))
    // {
    //     OUTPUT = (dummy_OutputZERO + (dummy_angle * 727.18f)) * Kmax;
    // }
    //   else OUTPUT = (dummy_OutputZERO + (dummy_angle * 727.18f));

    int32_t angle_X100 = ((int32_t)(Value_ADCVolt_filtered[0] - last_ADC_N40) * 4000) / (last_ADC_0 - last_ADC_N40) - 4000;

    if (Value_ADCVolt_filtered[0] <= last_ADC_0)
    {
        angle_X100 = (Value_ADCVolt_filtered[0] - last_ADC_N40) * 4000 / (last_ADC_0 - last_ADC_N40) - 4000;
    }
    else if ((Value_ADCVolt_filtered[0] > last_ADC_0) && (Value_ADCVolt_filtered[0] <= last_ADC_P40))
    {
        angle_X100 = (Value_ADCVolt_filtered[0] - last_ADC_0) * 4000 / (last_ADC_P40 - last_ADC_0);
    }

    if ((Value_ADCVolt_filtered[0] < last_ADC_N40) || (Value_ADCVolt_filtered[0] > last_ADC_P40))
    {
        angle_X100 = (Value_ADCVolt_filtered[0] - last_ADC_0) * 36000.0f / 4096.0f
    }

    OUTPUT = ((angle_X100 + 4500) * 65535) / 9000;

    DAC8560_WriteValue(&_SPI2_DAC1, (uint16_t)(OUTPUT));
}
