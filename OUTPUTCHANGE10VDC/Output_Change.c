/*
 * Output_Change.c
 *
 *  Created on: Jun 6, 2026
 *      Author: PC
 */

#include "Output_Change.h"

static void HardWave_Transmit24Bits(DAC8560_SPI *spi, uint32_t data)
{
    uint8_t pTxData[3];
    pTxData[0] = (data >> 16) & 0xFF; // MSB
    pTxData[1] = (data >> 8) & 0xFF;  // Middle byte
    pTxData[2] = data & 0xFF;         // LSB

    HAL_GPIO_WritePin(spi->CS_PORT, spi->CS_PIN, GPIO_PIN_RESET); // CS low
    HAL_SPI_Transmit(spi->hspi, pTxData, 3, HAL_MAX_DELAY);       // Transmit 3 bytes
    HAL_GPIO_WritePin(spi->CS_PORT, spi->CS_PIN, GPIO_PIN_SET);   // CS high
}

void DAC8560_Init(DAC8560_SPI *spi, SPI_HandleTypeDef *hspi, GPIO_TypeDef *CS_PORT, uint16_t CS_PIN)
{
    spi->hspi = hspi;
    spi->CS_PORT = CS_PORT;
    spi->CS_PIN = CS_PIN;

    // Initialize the CS pin
    HAL_GPIO_WritePin(spi->CS_PORT, spi->CS_PIN, GPIO_PIN_SET); // Set CS high
}

void DAC8560_EnableInternalVref(DAC8560_SPI *spi)
{
    HardWave_Transmit24Bits(spi, 0x004C0400);
    HardWave_Transmit24Bits(spi, 0x004901);
}

void DAC8560_DisableInternalVref(DAC8560_SPI *spi)
{
    HardWave_Transmit24Bits(spi, 0x480401);
}

void DAC8560_WriteValue(DAC8560_SPI *spi, uint16_t value)
{
    uint32_t frame;

    frame = DAC8560_CMD_WRITE_UPDATE;
    frame <<= 16;
    frame |= value;

    HardWave_Transmit24Bits(spi, frame);
}
