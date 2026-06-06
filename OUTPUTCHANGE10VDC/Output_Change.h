/*
 * Output_Change.h
 *
 *  Created on: Jun 6, 2026
 *      Author: PC
 */

#ifndef OUTPUT_CHANGE_H_
#define OUTPUT_CHANGE_H_

#include "main.h"

#define DAC8560_CMD_WRITE_UPDATE      0x00

// power down modes
#define DAC8560_POWER_NORMAL          0x00
#define DAC8560_POWER_1K              0x01
#define DAC8560_POWER_100K            0x02
#define DAC8560_POWER_HIZ             0x03

typedef struct
{
    GPIO_TypeDef *CS_PORT;
    uint16_t CS_PIN;
    SPI_HandleTypeDef *hspi;
} DAC8560_SPI;

void DAC8560_Init(DAC8560_SPI *spi, SPI_HandleTypeDef *hspi, GPIO_TypeDef *CS_PORT, uint16_t CS_PIN);
void DAC8560_EnableInternalVref(DAC8560_SPI *spi);
void DAC8560_DisableInternalVref(DAC8560_SPI *spi);
void DAC8560_WriteValue(DAC8560_SPI *spi, uint8_t value);

#endif /* OUTPUT_CHANGE_H_ */
