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

extern float Value_ADCVolt_filtered[2];
extern uint16_t last_ADC_N40;
extern uint16_t last_ADC_N30;
extern uint16_t last_ADC_N20;
extern uint16_t last_ADC_N10;
extern uint16_t last_ADC_0;
extern uint16_t last_ADC_P10;
extern uint16_t last_ADC_P20;
extern uint16_t last_ADC_P30;
extern uint16_t last_ADC_P40;

// static float Kmin = 0;
// static float Kmax = 0;
static int32_t OUTPUT = 32687;

DAC8560_SPI _SPI2_DAC1;

void Apli_OutputChange10VDC_Init(void)
{
    DAC8560_Init(&_SPI2_DAC1, &hspi2, ENABLE_CS2_GPIO_Port, ENABLE_CS2_Pin);
    DAC8560_EnableInternalVref(&_SPI2_DAC1);
}

void Apli_OutputChange10VDC_SetValue(void)
{
    int32_t angle_X100;

    if (Value_ADCVolt_filtered[0] < last_ADC_N40)
    {
        angle_X100 = (last_ADC_N40 - Value_ADCVolt_filtered[0]) - 5000;
    }
    else if ((Value_ADCVolt_filtered[0] < last_ADC_N30) && (Value_ADCVolt_filtered[0] >= last_ADC_N40))
    {
        angle_X100 = ((Value_ADCVolt_filtered[0] - last_ADC_N40) * 1000 / (last_ADC_N30 - last_ADC_N40) - 4000);
    }
    else if ((Value_ADCVolt_filtered[0] < last_ADC_N20) && (Value_ADCVolt_filtered[0] >= last_ADC_N30))
    {
        angle_X100 = ((Value_ADCVolt_filtered[0] - last_ADC_N30) * 1000 / (last_ADC_N20 - last_ADC_N30) - 3000);
    }
    else if ((Value_ADCVolt_filtered[0] < last_ADC_N10) && (Value_ADCVolt_filtered[0] >= last_ADC_N20))
    {
    	angle_X100 = ((Value_ADCVolt_filtered[0] - last_ADC_N20) * 1000 / (last_ADC_N10 - last_ADC_N20) - 2000);
    }
    else if ((Value_ADCVolt_filtered[0] < last_ADC_0) && (Value_ADCVolt_filtered[0] >= last_ADC_N10))
    {
    	angle_X100 = ((Value_ADCVolt_filtered[0] - last_ADC_N10) * 1000 / (last_ADC_0 - last_ADC_N10) - 1000);
    }
    else if ((Value_ADCVolt_filtered[0] >= last_ADC_0) && (Value_ADCVolt_filtered[0] < last_ADC_P10))
    {
        angle_X100 =((Value_ADCVolt_filtered[0] - last_ADC_0) * 1000 / (last_ADC_P10 - last_ADC_0));
    }
    else if ((Value_ADCVolt_filtered[0] >= last_ADC_P10) && (Value_ADCVolt_filtered[0] < last_ADC_P20))
    {
    	 angle_X100 =((Value_ADCVolt_filtered[0] - last_ADC_P10) * 1000 / (last_ADC_P20 - last_ADC_P10) + 1000);
    }
    else if ((Value_ADCVolt_filtered[0] >= last_ADC_P20) && (Value_ADCVolt_filtered[0] < last_ADC_P30))
    {
    	 angle_X100 =((Value_ADCVolt_filtered[0] - last_ADC_P20) * 1000 / (last_ADC_P30 - last_ADC_P20) + 2000);
    }
    else if ((Value_ADCVolt_filtered[0] >= last_ADC_P30) && (Value_ADCVolt_filtered[0] < last_ADC_P40))
    {
    	 angle_X100 =((Value_ADCVolt_filtered[0] - last_ADC_P30) * 1000 / (last_ADC_P40 - last_ADC_P30) + 3000);
    }
    else if (Value_ADCVolt_filtered[0] >= last_ADC_P40)
    {
        angle_X100 = (Value_ADCVolt_filtered[0] - last_ADC_P40) + 4000;
    }

    OUTPUT = ((angle_X100 + 4500) * 65535) / 9000;

    if (angle_X100 < -4500)
    {
        OUTPUT = 0;
    }

    if (angle_X100 > 4500)
    {
        OUTPUT = 65535;
    }

    DAC8560_WriteValue(&_SPI2_DAC1, (uint16_t)(OUTPUT));
}
