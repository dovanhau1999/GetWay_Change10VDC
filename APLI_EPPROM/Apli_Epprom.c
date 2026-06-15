/*
 * Apli_Epprom.c
 *
 *  Created on: Jun 6, 2026
 *      Author: PC
 */

#include "Apli_Epprom.h"
#include "Apli_RS485.h"
#include "PROTOCAL_EEPROM.h"

extern float Value_ADCVolt_filtered[2];
// extern int16_t Value_AngleExpected[2];
int16_t last_SetShitfZero;
int16_t last_SetAngleExpected;
// int16_t last_ErrorToTerminal;

void Apli_Epprom_Init(void)
{
    // Read date from EEPROM and save to variable
    PE_ReadExtEepromU16(PE_ValueADCVoltShitfZero, &last_SetShitfZero);
    PE_ReadExtEepromU16(PE_ValueAngleExpected, &last_SetAngleExpected);
    // PE_ReadExtEepromU16(PE_ErrorToTerminal, &last_ErrorToTerminal);

    REGISTOR_MODBUS[VALUE_ADCVolt_ShiftToZero1] = last_SetShitfZero;
    REGISTOR_MODBUS[VALUE_ANGLE_CHANEL1EXPECT] = last_SetAngleExpected;
}

void Apli_Epprom_Loop(void)
{
    // Write data to EEPROM when variable change
    int16_t var1;
    var1 = REGISTOR_MODBUS[VALUE_ADCVolt_ShiftToZero1];

    if (var1 != last_SetShitfZero)
    {
        last_SetShitfZero = var1;
        PE_WriteExtEepromU16(PE_ValueADCVoltShitfZero, last_SetShitfZero);

        // last_ErrorToTerminal = (int32_t)(((Value_ADCVolt_filtered[0] - last_SetShitfZero) * 360.0f / 4095.0f) * 10.0f);
        // PE_WriteExtEepromU16(PE_ErrorToTerminal, last_ErrorToTerminal); /**Khi nào có sự thay đổi giá trị ShiftToZero thì mới lưu lại Giá trị sai số do đồng hồ vào EEPROM
        //                                                                  * Lấy giá trị Góc trừ đi giá trị góc sai số do đồng hồ thì giá trị Góc hiển thị ở thanh ghi mới là thực tế
        //                                                                  */
    }

    int16_t var2;
    var2 = REGISTOR_MODBUS[VALUE_ANGLE_CHANEL1EXPECT];
    if (var2 != last_SetAngleExpected)
    {
        last_SetAngleExpected = var2;
        PE_WriteExtEepromU16(PE_ValueAngleExpected, last_SetAngleExpected);
    }
}
