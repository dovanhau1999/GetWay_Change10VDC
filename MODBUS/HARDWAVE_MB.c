/*
 * HARDWAVE_MB.c
 *
 *  Created on: Oct 4, 2025
 *      Author: PC
 */

#include <PROTOCOL_RS485.h>
#include "HARDWAVE_MB.h"

/**
 *
 * ********************************************************************************************************
 * ********************************************************************************************************
 * HARDWAVE LAYER CONFIG
 * ********************************************************************************************************
 * ********************************************************************************************************
 *
 *
 */

uint8_t uartRxData;
uint32_t modbus_frame_timeout = 5; // default (ms), sẽ update khi init

void RS485_Config(CONFIG_RS485 *rs485, UART_HandleTypeDef *huart, GPIO_TypeDef *CS_PORT, uint16_t CS_PIN)
{
    rs485->huart = huart;
    rs485->CS_PORT = CS_PORT;
    rs485->CS_PIN = CS_PIN;
}
void RS485_Init(CONFIG_RS485 *rs485)
{
    // Bắt đầu nhận interrupt 1 byte
    HAL_UART_Receive_IT(rs485->huart, (uint8_t *)&uartRxData, 1);

    uint32_t baud = rs485->huart->Init.BaudRate;

    // Tính thời gian 1 ký tự (11 bit) tính theo ms
    float charTimeMs = (1000.0f * 11.0f) / (float)baud;

    // Thời gian frame timeout = 3.5 ký tự
    modbus_frame_timeout = (uint32_t)(3.5f * charTimeMs + 0.5f); // làm tròn

    if (modbus_frame_timeout == 0)
        modbus_frame_timeout = 1; // tối thiểu 1 ms

    // Set DE = 0 (RX mode mặc định)
    HAL_GPIO_WritePin(rs485->CS_PORT, rs485->CS_PIN, GPIO_PIN_RESET);
}

void RS485_SendData(CONFIG_RS485 *rs485, uint8_t *data, uint16_t len)
{
    // Bật DE = 1 (TX mode)
    HAL_GPIO_WritePin(rs485->CS_PORT, rs485->CS_PIN, GPIO_PIN_SET);

    HAL_UART_Transmit(rs485->huart, data, len, HAL_MAX_DELAY);

    // Sau khi gửi xong, trả về RX
    HAL_GPIO_WritePin(rs485->CS_PORT, rs485->CS_PIN, GPIO_PIN_RESET);
}

// gọi trong HAL_UART_RxCpltCallback
void RS485_ReceiveHandler(CONFIG_RS485 *rs485)
{
    Modbus_ReceiveByte(&uartRxData);

    // Gọi lại nhận IT cho UART tương ứng
    HAL_UART_Receive_IT(rs485->huart, (uint8_t *)&uartRxData, 1);
}

uint32_t RS485_GetTick(void)
{
    return HAL_GetTick(); // ms
}
