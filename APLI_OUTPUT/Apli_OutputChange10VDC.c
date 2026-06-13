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

extern int16_t Value_AngleExpected[2];

uint16_t value_angle = 0;

DAC8560_SPI _SPI2_DAC1;

void Apli_OutputChange10VDC_Init(void)
{
    DAC8560_Init(&_SPI2_DAC1, &hspi2, ENABLE_CS2_GPIO_Port, ENABLE_CS2_Pin);
    DAC8560_EnableInternalVref(&_SPI2_DAC1);
}

void Apli_OutputChange10VDC_SetValue(void)
{

    /**
     * Dải của đồng hồ là 45 độ tương ứng -45 độ  = 0 ADC, 45 độ = 65535 ADC
     * Do đó cần chọn giá trị giới hạn của góc là -45 độ đến +45 độ, tương ứng với giá trị ADC là 0 đến 65535
     * Giá trị đo 0-5VDC tương ứng -180 độ đến +180 độ. Mà đồng hồ không hiểu thị hết nên phải giới hạn.
     */
    if (Value_AngleExpected[0] <= -4500)
    {
        Value_AngleExpected[0] = -4500;
    }
    else if (Value_AngleExpected[0] >= 4500)
    {
        Value_AngleExpected[0] = 4500;
    }

    value_angle = (uint16_t)(((Value_AngleExpected[0] + 4500.0f) * 65535.0f) / 9000.0f); /* Lấy giá trị Độ ở thanh ghi 0x01 chuyển thành dải 0 : 65535
                                                                                            Thay việc cho việc phải set giá trị vào thanh ghi 0x04
                                                                                        */
    DAC8560_WriteValue(&_SPI2_DAC1, value_angle);                                        // Giá trị được Set từ 0 : 65535, tương ứng với -10VDC : +10VDC
}
