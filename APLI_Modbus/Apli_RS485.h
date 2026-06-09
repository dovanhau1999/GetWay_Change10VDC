/*
 * Apli_RS485.h
 *
 *  Created on: Oct 4, 2025
 *      Author: PC
 */

#ifndef APLI_RS485_H_
#define APLI_RS485_H_

#include "main.h"

#define VALUE_ID 0
#define VALUE_VRMS_CHANNEL1 1
#define VALUE_VRMS_CHANNEL2 2
#define VALUE_OF_VOLTAGE 3
#define VALUE_OUTPUT_10VDC 4

#define MAX_DATA_MODBUS 18
extern uint16_t REGISTOR_MODBUS[MAX_DATA_MODBUS];

void Apli_Modbus_RS485_Init(void);
void Apli_Modbus_RS485_Loop(void);

#endif /* APLI_RS485_H_ */
