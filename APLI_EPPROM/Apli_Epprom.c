/*
 * Apli_Epprom.c
 *
 *  Created on: Jun 6, 2026
 *      Author: PC
 */

#include "Apli_Epprom.h"
#include "Apli_RS485.h"
#include "PROTOCAL_EEPROM.h"


int16_t last_SetShitfZero = 0;

void Apli_Epprom_Init(void)
{
    // Read date from EEPROM and save to variable
    PE_ReadExtEepromU16(PE_ValueADCVoltShitfZero, &last_SetShitfZero);
    REGISTOR_MODBUS[VALUE_ADCVolt_ShiftToZero1] = last_SetShitfZero;
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
        // HAL_NVIC_SystemReset();
    }
}
