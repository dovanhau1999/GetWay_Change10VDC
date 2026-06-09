/*
 * SPI_MCP3208.c
 *
 *  Created on: Jul 8, 2024
 *      Author: PC
 */

#include <HEADWAVE_MCP3208.h>
#include "main.h"

/*
 * Set the MISO, MOSI, SCK and CS
 * SPI settings:
 * CPHA = 1 Edge
 * Prescaler = 8
 * First bit = MBS first
 * CPOL = Low
 */
void MCP3208_Init(MCP3208_SPI *spi, SPI_HandleTypeDef *hspi, GPIO_TypeDef *CS_PORT, uint16_t CS_PIN)
{
  spi->hspi = hspi;
  spi->CS_PORT = CS_PORT;
  spi->CS_PIN = CS_PIN;
}

/**
 * @brief Read the channels from 0 to 7
 *
 * @param spi  Opject of typedef struct MCP3208
 *
 * @param chanel  Chanel read ADC on MCP3208 from 0..7
 *
 * @retval uint16_t
 *
 * @note Frame Transmitted/Received Data (copy form datasheet of MCP3208)
 * @note Mode: MSB Fisrt
 * @note  CLK: | 7 | 6 | 5 | 4 | 3 |     2    |    1     |  0  |       |  7   | 6  | 5 | 4    | 3   |  2  |  1  | 0   |          | 7  | 6  | 5  | 4  | 3  | 2  | 1  | 0  |
 * @note MOSI: | X | X | X | X | X |Start Bit | SGL/DIFF | D2  |       |  D1  | D0 | X | X    | X   |  X  |  X  | X   |          | X  | X  | X  | X  | X  | X  | X  | X  |
 * @note MISO: | ? | ? | ? | ? | ? |    ?     |    ?     | ?   |       |  ?   | ?  | ? | NULL | B11 | B10 | B9  | B8  |          | B7 | B6 | B5 | B4 | B3 | B2 | B1 | B0 |
 */
uint16_t MCP3208_Read_Channel(MCP3208_SPI *spi, uint8_t channel)
{
  /*Declare data that we will send*/
  uint8_t pTxData[3] = {0};
  pTxData[0] = ((0x01 << 2) |             // Start bit
                (0x01 << 1) |             // SGL/DIFF
                ((channel & 0x04) >> 2)); // Channel number
  pTxData[1] = ((channel & 0x03) << 6);
  pTxData[2] = 0x00;

  /*Data that we will get*/
  uint8_t pRxData[3] = {0};

  /*CS low, Send and receive, CS high*/
  HAL_GPIO_WritePin(spi->CS_PORT, spi->CS_PIN, GPIO_PIN_RESET);
  HAL_SPI_TransmitReceive(spi->hspi, pTxData, pRxData, 3, 10);
  HAL_GPIO_WritePin(spi->CS_PORT, spi->CS_PIN, GPIO_PIN_SET);

  /*Compute the ADC*/
  return 0x0FFF & ((pRxData[1] & 0x0F) << 8 | (pRxData[2] & 0xFF));
}
