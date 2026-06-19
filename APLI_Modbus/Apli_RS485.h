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
#define VALUE_CalibSector 1
#define VALUE_CalibTerminal 2
#define VALUE_ADCVolt_CHANNEL1 3
#define VALUE_ANGLE_CHANEL1ACTUAL 4
#define VALUE_SetMINoutput 5
#define VALUE_SetMAXoutput 6
// #define VALUE_ANGLE_CHANNEL2 7
// #define VALUE_OF_VOLTAGE 8
#define VALUE_OUTPUT_10VDC 9

#define VALUE_ADC_N40 10
#define VALUE_ADC_N30 11
#define VALUE_ADC_N20 12
#define VALUE_ADC_N10 13
#define VALUE_ADC_0 14
#define VALUE_ADC_P10 15
#define VALUE_ADC_P20 16
#define VALUE_ADC_P30 17
#define VALUE_ADC_P40 18

#define MAX_DATA_MODBUS 20
extern uint16_t REGISTOR_MODBUS[MAX_DATA_MODBUS];

void Apli_Modbus_RS485_Init(void);
void Apli_Modbus_RS485_Loop(void);

#endif /* APLI_RS485_H_ */
