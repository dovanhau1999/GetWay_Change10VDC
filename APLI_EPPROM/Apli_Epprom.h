/*
 * Apli_Epprom.h
 *
 *  Created on: Jun 6, 2026
 *      Author: PC
 */

#ifndef APLI_EPPROM_H_
#define APLI_EPPROM_H_

#include "main.h"

#define PE_VALUEOFADC1 100
#define PE_VALUEOFADC2 PE_VALUEOFADC1 + 2
#define PE_VALUEOFVLOTAGE PE_VALUEOFADC2 + 2
#define PE_VALUESETOUTPUT10VDC PE_VALUEOFVLOTAGE + 2

void Apli_Epprom_Init(void);
void Apli_Epprom_Loop(void);

#endif /* APLI_EPPROM_H_ */
