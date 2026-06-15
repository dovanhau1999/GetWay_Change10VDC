/*
 * Apli_Epprom.h
 *
 *  Created on: Jun 6, 2026
 *      Author: PC
 */

#ifndef APLI_EPPROM_H_
#define APLI_EPPROM_H_

#include "main.h"

#define PE_ID 80
#define PE_ValueADCVoltShitfZero 100
#define PE_ValueAngleExpected 104

void Apli_Epprom_Init(void);
void Apli_Epprom_Loop(void);

#endif /* APLI_EPPROM_H_ */
