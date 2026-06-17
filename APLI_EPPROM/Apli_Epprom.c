/*
 * Apli_Epprom.c
 *
 *  Created on: Jun 6, 2026
 *      Author: PC
 */

#include "Apli_Epprom.h"
#include "Apli_RS485.h"
#include "PROTOCAL_EEPROM.h"

uint16_t last_ValueSetTerminal = 0;
uint16_t last_ValueSetSector = 0;
uint16_t last_SetMinADCOutput = 0;
uint16_t last_SetMaxADCOutput = 0;

uint16_t last_ADC_N40 = 0;
uint16_t last_ADC_0 = 0;
uint16_t last_ADC_P40 = 0;

void Apli_Epprom_Init(void)
{
    // Read date from EEPROM and save to variable
	PE_ReadExtEepromU16(PE_ValueTerminalZERO, &last_ValueSetTerminal);
	if ((last_ValueSetTerminal == 0) || (last_ValueSetTerminal == 0xFFFF))
	{
		last_ValueSetTerminal = 100;
	}
	REGISTOR_MODBUS[VALUE_CalibTerminal] = last_ValueSetTerminal;

	PE_ReadExtEepromU16(PE_ValueSectorZERO, &last_ValueSetSector);
	if ((last_ValueSetSector == 0) || (last_ValueSetSector == 0xFFFF))
	{
		last_ValueSetSector = 100;
	}
	REGISTOR_MODBUS[VALUE_CalibSector] = last_ValueSetSector;

	PE_ReadExtEepromU16(PE_ValueADCMinOutput, &last_SetMinADCOutput);
	if ((last_SetMinADCOutput == 0) || (last_SetMinADCOutput == 0xFFFF))
	{
		last_SetMinADCOutput = 1000;
	}
	REGISTOR_MODBUS[VALUE_SetMINoutput] = last_SetMinADCOutput;

	PE_ReadExtEepromU16(PE_ValueADCMaxOutput, &last_SetMaxADCOutput);
	if ((last_SetMaxADCOutput == 0) || (last_SetMaxADCOutput == 0xFFFF))
	{
		last_SetMaxADCOutput = 1000;
	}
	REGISTOR_MODBUS[VALUE_SetMAXoutput] = last_SetMaxADCOutput;

	PE_ReadExtEepromU16(PE_ADC_N40, &last_ADC_N40);
	if ((last_ADC_N40 == 0) || (last_ADC_N40 == 0xFFFF))
	{
		last_ADC_N40 = 1000;
	}
	REGISTOR_MODBUS[VALUE_ADC_N40] = last_ADC_N40;

	PE_ReadExtEepromU16(PE_ADC_0, &last_ADC_0);
	if ((last_ADC_0 == 0) || (last_ADC_0 == 0xFFFF))
	{
		last_ADC_0 = 1500;
	}
	REGISTOR_MODBUS[VALUE_ADC_0] = last_ADC_0;

	PE_ReadExtEepromU16(PE_ADC_P40, &last_ADC_P40);
	if ((last_ADC_P40 == 0) || (last_ADC_P40 == 0xFFFF))
	{
		last_ADC_P40 = 2000;
	}
	REGISTOR_MODBUS[VALUE_ADC_P40] = last_ADC_P40;
}

void Apli_Epprom_Loop(void)
{
}
