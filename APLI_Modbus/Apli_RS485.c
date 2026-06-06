/*
 * Apli_RS485.c
 *
 *  Created on: Oct 4, 2025
 *      Author: PC
 */

#include "Apli_RS485.h"
#include "PROTOCOL_RS485.h"

// #define USE_TESTCHANEL

uint16_t REGISTOR_MODBUS[MAX_DATA_MODBUS] = {0};

extern uint16_t Value_IRMS[2];


void Apli_Modbus_RS485_Init(void)
{
    Modbus_Init(1);
    
}
void Apli_Modbus_RS485_Loop(void)
{
    Modbus_Process(REGISTOR_MODBUS, MAX_DATA_MODBUS);

    REGISTOR_MODBUS[VALUE_IRMS_CHANNEL1] = Value_IRMS[0];
    REGISTOR_MODBUS[VALUE_IRMS_CHANNEL2] = Value_IRMS[1];

}
