/*
 * Apli_RS485.c
 *
 *  Created on: Oct 4, 2025
 *      Author: PC
 */

#include "Apli_RS485.h"
#include "PROTOCOL_RS485.h"
#include "PROTOCAL_EEPROM.h"
#include "Apli_Epprom.h"

uint16_t REGISTOR_MODBUS[MAX_DATA_MODBUS] = {0};

extern float Value_ADCVolt_filtered[2];
extern int16_t OutputAngle;

static uint16_t last_ID;

void Apli_Modbus_RS485_Init(void)
{
    PE_ReadExtEepromU16(PE_ID, &last_ID);
    if ((last_ID > 128) | (last_ID == 0))
    {
        last_ID = 1;
    }

    REGISTOR_MODBUS[VALUE_ID] = last_ID;
    Modbus_Init(last_ID);

    //    PE_WriteExtEepromU16(PE_ID, 1);
}
void Apli_Modbus_RS485_Loop(void)
{
    Modbus_Process(REGISTOR_MODBUS, MAX_DATA_MODBUS);

    REGISTOR_MODBUS[VALUE_ADCVolt_CHANNEL1] = (uint16_t)(Value_ADCVolt_filtered[0]);

    REGISTOR_MODBUS[VALUE_ANGLE_CHANEL1ACTUAL] = (uint16_t) OutputAngle; /**Giá trị Góc hiển thị ở thanh ghi là giá trị thực tế, đã trừ đi sai số do đồng hồ
                                                                                                                              * Lấy giá trị Góc trừ đi giá trị góc sai số do đồng hồ thì giá trị Góc hiển thị ở thanh ghi mới là thực tế
                                                                                                                              */

    if (last_ID != REGISTOR_MODBUS[VALUE_ID])
    {
        last_ID = REGISTOR_MODBUS[VALUE_ID];
        PE_WriteExtEepromU16(PE_ID, last_ID);
        HAL_NVIC_SystemReset();
    }
}
