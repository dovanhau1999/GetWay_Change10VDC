/*
 * M24C02.h
 *
 *  Created on: Jun 27, 2024
 *      Author: PC
 */

#ifndef PROTOCAL_EEPROM_H_
#define PROTOCAL_EEPROM_H_

#include "main.h"

/**
 * Model use ic M24C02
 */

#define CALIB_EEPROM_WR 0xA0
#define CALIB_EEPROM_RD 0xA1

#define TimeDelay_Of_Relay 0

#define SetPoint_Output_AVR 50
#define SetPoint_Output_SPEED 54
#define SetPoint_ADC_Volt 58
#define SetPoint_ADC_Freq 62

#define VoltageADC_PhaseA_Of_ADE1 100
#define VoltageADC_PhaseB_Of_ADE1 VoltageADC_PhaseA_Of_ADE1 + 4
#define VoltageADC_PhaseC_Of_ADE1 VoltageADC_PhaseB_Of_ADE1 + 4

#define VoltageADC_PhaseA_Of_ADE2 VoltageADC_PhaseC_Of_ADE1 + 4
#define VoltageADC_PhaseB_Of_ADE2 VoltageADC_PhaseA_Of_ADE2 + 4
#define VoltageADC_PhaseC_Of_ADE2 VoltageADC_PhaseB_Of_ADE2 + 4

#define CircuitADC_PhaseA_Of_ADE2 VoltageADC_PhaseC_Of_ADE2 + 4
#define CircuitADC_PhaseB_Of_ADE2 CircuitADC_PhaseA_Of_ADE2 + 4
#define CircuitADC_PhaseC_Of_ADE2 CircuitADC_PhaseB_Of_ADE2 + 4

#define PowerADC_PhaseA_Of_ADE2 CircuitADC_PhaseC_Of_ADE2 + 4
#define PowerADC_PhaseB_Of_ADE2 PowerADC_PhaseA_Of_ADE2 + 4
#define PowerADC_PhaseC_Of_ADE2 PowerADC_PhaseB_Of_ADE2 + 4

#define ApparentADC_PhaseA_Of_ADE2 PowerADC_PhaseC_Of_ADE2 + 4
#define ApparentADC_PhaseB_Of_ADE2 ApparentADC_PhaseA_Of_ADE2 + 4
#define ApparentADC_PhaseC_Of_ADE2 ApparentADC_PhaseB_Of_ADE2 + 4

#define ReactiveADC_PhaseA_Of_ADE2 ApparentADC_PhaseC_Of_ADE2 + 4
#define ReactiveADC_PhaseB_Of_ADE2 ReactiveADC_PhaseA_Of_ADE2 + 4
#define ReactiveADC_PhaseC_Of_ADE2 ReactiveADC_PhaseB_Of_ADE2 + 4

HAL_StatusTypeDef PE_WriteExtEepromU16(uint16_t address, uint16_t data);
HAL_StatusTypeDef PE_ReadExtEepromU16(uint16_t address, uint16_t *data);

HAL_StatusTypeDef PE_WriteExtEepromU32(uint16_t address, uint32_t data);
HAL_StatusTypeDef PE_ReadExtEEproomU32(uint16_t address, uint32_t *data);

#endif /* PROTOCAL_EEPROM_H_ */
