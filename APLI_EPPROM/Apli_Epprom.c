/*
 * Apli_Epprom.c
 *
 *  Created on: Jun 6, 2026
 *      Author: PC
 */

#include "Apli_Epprom.h"
#include "Apli_RS485.h"
#include "PROTOCAL_EEPROM.h"

uint16_t last_VarOutput, last_ValOfVoltage;

void Apli_Epprom_Init(void)
{
    // Read date from EEPROM and save to variable
    PE_ReadExtEepromU16(PE_VALUESETOUTPUT10VDC, &last_VarOutput);
    PE_ReadExtEepromU16(PE_VALUEOFVLOTAGE, &last_ValOfVoltage);
    REGISTOR_MODBUS[VALUE_OUTPUT_10VDC] = last_VarOutput;
    REGISTOR_MODBUS[VALUE_OF_VOLTAGE] = last_ValOfVoltage;
    }

void Apli_Epprom_Loop(void)
{
    // Write data to EEPROM when variable change
//    static uint16_t var1, var2;
//    var1 = REGISTOR_MODBUS[VALUE_OUTPUT_10VDC];
//    var2 = REGISTOR_MODBUS[VALUE_OF_VOLTAGE];

    // if (var1 != last_VarOutput)
    // {
    //     last_VarOutput = var1;
    //     PE_WriteExtEepromU16(PE_VALUESETOUTPUT10VDC, var1);
    // }
    // if (var2 != last_ValOfVoltage)
    // {
    //     last_ValOfVoltage = var2;
    //     PE_WriteExtEepromU16(PE_VALUEOFVLOTAGE, var2);
    // }
}
