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

extern int16_t last_SetShitfZero;
extern float Value_ADCVolt_filtered[2];

int16_t ErrorAngle=0;

float Value_ADCOutputExpect[2] = {0};
static float value_angle = 0;

DAC8560_SPI _SPI2_DAC1;

void Apli_OutputChange10VDC_Init(void)
{
    DAC8560_Init(&_SPI2_DAC1, &hspi2, ENABLE_CS2_GPIO_Port, ENABLE_CS2_Pin);
    DAC8560_EnableInternalVref(&_SPI2_DAC1);

    ErrorAngle = (int16_t)(Value_ADCVolt_filtered[0] - last_SetShitfZero);
}

void Apli_OutputChange10VDC_SetValue(void)
{
        value_angle = Value_ADCVolt_filtered[0] * 360.0f / 4095.0f; /**Chuyển đổi giá trị ADC sang góc - Từ -180...+180 độ tương ứng vơi 0...4095 của ADC
                                                                                                                                        * Sau đó nhân với 10 để có giá trị 1 chữ số thập phân
                                                                                                                                        */
    /**
     * Dải của đồng hồ là 45 độ tương ứng -45 độ  = 0 ADC, 45 độ = 65535 ADC
     * Do đó cần chọn giá trị giới hạn của góc là -45 độ đến +45 độ, tương ứng với giá trị ADC là 0 đến 65535
     * Giá trị đo 0-5VDC tương ứng -180 độ đến +180 độ. Mà đồng hồ không hiểu thị hết nên phải giới hạn.
     */
    if (value_angle <= -45.00f)
    {
        Value_ADCOutputExpect[0] = 0;
    }
    else if (value_angle >= 45.00f)
    {
        Value_ADCOutputExpect[0] = 65535;
    } else {
        Value_ADCOutputExpect[0] = (Value_ADCVolt_filtered[0] + ErrorAngle) * 16.00f; /* Lấy giá trị Độ ở thanh ghi 0x01 chuyển thành dải 0 : 65535
        *  Thay việc cho việc phải set giá trị vào thanh ghi 0x04
        */
        }

        if ((value_angle > -45.00f) && (value_angle < 0.00f)){
Value_ADCOutputExpect[0] = Value_ADCOutputExpect[0] * 1.05f; 
        }else if ((value_angle >= 0.00f) && (value_angle < 45.00f)){
Value_ADCOutputExpect[0] = Value_ADCOutputExpect[0] * 0.95f; 
        } 
        
    DAC8560_WriteValue(&_SPI2_DAC1, (uint16_t)Value_ADCOutputExpect[0]);                                        // Giá trị được Set từ 0 : 65535, tương ứng với -10VDC : +10VDC
}
