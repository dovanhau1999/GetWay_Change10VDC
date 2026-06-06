/*
 * HARDWAVE_MB.h
 *
 *  Created on: Oct 4, 2025
 *      Author: PC
 */

#ifndef HARDWAVE_MB_H_
#define HARDWAVE_MB_H_

#include "main.h"

typedef struct
{
    UART_HandleTypeDef *huart; // con trỏ tới UART
    uint16_t CS_PIN;           // chân DE/RE (chân điều khiển RS485 driver)
    GPIO_TypeDef *CS_PORT;     // PORT tương ứng
} CONFIG_RS485;

/**
 * KHAI BÁO HÀM CỦA LỚP HARDWAVE
 */
void RS485_Config(CONFIG_RS485 *rs485, UART_HandleTypeDef *huart, GPIO_TypeDef *CS_PORT, uint16_t CS_PIN);
void RS485_Init(CONFIG_RS485 *rs485);
void RS485_SendData(CONFIG_RS485 *rs485, uint8_t *data, uint16_t len);
void RS485_ReceiveHandler(CONFIG_RS485 *rs485); // được gọi trong Rx callback
uint32_t RS485_GetTick(void);                                 // dùng để đo timeout

#endif /* HARDWAVE_MB_H_ */
