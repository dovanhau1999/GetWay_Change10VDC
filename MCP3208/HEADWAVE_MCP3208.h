/*
 * SPI_MCP3208.h
 *
 *  Created on: Jul 8, 2024
 *      Author: PC
 */

#ifndef HEADWAVE_MCP3208_H_
#define HEADWAVE_MCP3208_H_

#include "main.h"

typedef struct {
  GPIO_TypeDef* CS_PORT;
  uint16_t CS_PIN;
  SPI_HandleTypeDef* hspi;
}MCP3208_SPI;

void MCP3208_Init(MCP3208_SPI* spi, SPI_HandleTypeDef* hspi, GPIO_TypeDef* CS_PORT, uint16_t CS_PIN);
uint16_t MCP3208_Read_Channel(MCP3208_SPI* spi, uint8_t channel);

#endif /* HEADWAVE_MCP3208_H_ */
