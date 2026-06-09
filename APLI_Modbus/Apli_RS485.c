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

extern uint16_t Value_VRMS[2];

static uint16_t last_ID;

void Apli_Modbus_RS485_Init(void)
{
    PE_ReadExtEepromU16(PE_ID, &last_ID);
    if (last_ID == 0xFFFF)
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

    REGISTOR_MODBUS[VALUE_VRMS_CHANNEL1] = Value_VRMS[0];
    REGISTOR_MODBUS[VALUE_VRMS_CHANNEL2] = Value_VRMS[1];

    if (last_ID != REGISTOR_MODBUS[VALUE_ID])
    {
        last_ID = REGISTOR_MODBUS[VALUE_ID];
        PE_WriteExtEepromU16(PE_ID, last_ID);
    }

}
