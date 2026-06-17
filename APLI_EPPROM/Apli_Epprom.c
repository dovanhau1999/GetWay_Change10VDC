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
}

void Apli_Epprom_Loop(void)
{
}
