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
#define PE_ValueSectorZERO 100
#define PE_ValueTerminalZERO 104
#define PE_ValueADCMinOutput 140
#define PE_ValueADCMaxOutput 148

void Apli_Epprom_Init(void);
void Apli_Epprom_Loop(void);

#endif /* APLI_EPPROM_H_ */
