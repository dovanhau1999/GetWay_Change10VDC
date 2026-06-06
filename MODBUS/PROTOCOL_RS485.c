/*
 * RS485.c
 *
 *  Created on: Oct 4, 2025
 *      Author: PC
 */

#include "PROTOCOL_RS485.h"
#include "HARDWAVE_MB.h"

/* Extern types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
extern uint32_t modbus_frame_timeout; // default (ms), sẽ update khi init
/* USER CODE END ET */

/**
 *
 *
 * ********************************************************************************************************
 * PROTOCOL LAYER
 * ********************************************************************************************************
 *
 *
 */

// Cấu hình chân ENABLE của RS485
#define ENABLE_UART_Pin GPIO_PIN_2
#define ENABLE_UART_GPIO_Port GPIOB

// Đối tượng Modbus

CONFIG_RS485 MODBUS1;
// extern uint8_t uartRxData;

static MODBUS VD_Modbus;

static uint8_t rxBuffer[BUFFERSIZE] = {0};
static uint16_t rxIndex = 0;
static uint32_t lastByteTime = 0;

static const unsigned char fctsupported[] = {
    MB_FC_READ_COILS,
    MB_FC_READ_DISCRETE_INPUT,
    MB_FC_READ_HOLD_REGISTERS,
    MB_FC_READ_INPUT_REGISTER,
    MB_FC_WRITE_COIL,
    MB_FC_WRITE_REGISTER,
    MB_FC_WRITE_MULTIPLE_COILS,
    MB_FC_WRITE_MULTIPLE_REGISTERS,

};

static uint16_t Modbus_calcCRC(uint8_t length)
{
    unsigned int temp, temp2, flag;
    temp = 0xFFFF;
    unsigned char i = 0;
    for (i = 0; i < length; i++)
    {
        temp = temp ^ VD_Modbus.au8Buffer[i];
        unsigned char j = 0;
        for (j = 1; j <= 8; j++)
        {
            flag = temp & 0x0001;
            temp >>= 1;
            if (flag)
                temp ^= 0xA001;
        }
    }
    /* Reverse byte order. */
    temp2 = temp >> 8;
    temp = (temp << 8) | temp2;
    temp &= 0xFFFF;
    /**
     * the returned value is already swapped
     * crcLo byte is first & crcHi byte is last
     */
    return temp;
}

static void buildException(uint8_t u8Exception)
{
    uint8_t u8func = VD_Modbus.au8Buffer[FUNC]; // get the original FUNC code
    VD_Modbus.au8Buffer[ID] = VD_Modbus.u8id;
    VD_Modbus.au8Buffer[FUNC] = u8func + 0x80;
    VD_Modbus.au8Buffer[2] = u8Exception;
    VD_Modbus.u8BufferSize = EXCEPTION_SIZE;
}

static int8_t validateRequest(void)
{
    /* Check message crc vs calculated crc */
    uint16_t u16MsgCRC = ((VD_Modbus.au8Buffer[VD_Modbus.u8BufferSize - 2] << 8) | VD_Modbus.au8Buffer[VD_Modbus.u8BufferSize - 1]); // combine the crc Low & High bytes
    if (Modbus_calcCRC(VD_Modbus.u8BufferSize - 2) != u16MsgCRC)
    {
        return ERR_TIMEOUT;
    }

    /* Check fct code */
    bool isSupported = false;
    uint8_t i = 0;
    for (i = 0; i < sizeof(fctsupported); i++)
    {
        if (fctsupported[i] == VD_Modbus.au8Buffer[FUNC])
        {
            isSupported = 1;
            break;
        }
    }
    if (!isSupported)
    {
        return EXC_Illegal_Function;
    }

    /* Check start address & nb range */
    uint16_t u16regs = 0;
    uint8_t u8regs;
    switch (VD_Modbus.au8Buffer[FUNC])
    {
    case MB_FC_WRITE_REGISTER:
        u16regs = word(VD_Modbus.au8Buffer[ADD_HI],
                       VD_Modbus.au8Buffer[ADD_LO]);
        u8regs = (uint8_t)u16regs;
        if (u8regs > VD_Modbus.u8regsize)
            return EXC_Illegal_Data_Address;
        break;
    case MB_FC_READ_HOLD_REGISTERS:
        break;
    case MB_FC_READ_INPUT_REGISTER:
        break;
    case MB_FC_WRITE_MULTIPLE_REGISTERS:
        u16regs = word(VD_Modbus.au8Buffer[ADD_HI],
                       VD_Modbus.au8Buffer[ADD_LO]);
        u16regs += word(VD_Modbus.au8Buffer[NB_HI], VD_Modbus.au8Buffer[NB_LO]);
        u8regs = (uint8_t)u16regs;
        if (u8regs > VD_Modbus.u8regsize)
            return EXC_Illegal_Data_Address;
        break;
    }
    return 0;
}

/* Function Code 3: Read Holding Registers */
static void process_FC3(uint16_t *regs, uint16_t maxRegs)
{
    uint16_t u8StartAdd = word(VD_Modbus.au8Buffer[ADD_HI],
                               VD_Modbus.au8Buffer[ADD_LO]);
    uint8_t u8regsno = word(VD_Modbus.au8Buffer[NB_HI],
                            VD_Modbus.au8Buffer[NB_LO]);

    uint16_t i;
    VD_Modbus.au8Buffer[2] = u8regsno * 2;
    VD_Modbus.u8BufferSize = 3;
    for (i = u8StartAdd; i < u8StartAdd + u8regsno; i++)
    {
        VD_Modbus.au8Buffer[VD_Modbus.u8BufferSize] = highByte(regs[i]);
        VD_Modbus.u8BufferSize++;
        VD_Modbus.au8Buffer[VD_Modbus.u8BufferSize] = lowByte(regs[i]);
        VD_Modbus.u8BufferSize++;
    }
}

/* Function Code 6: Write Single Register */
static void process_FC6(uint16_t *regs, uint16_t maxRegs)
{
    uint8_t u8add = word(VD_Modbus.au8Buffer[ADD_HI],
                         VD_Modbus.au8Buffer[ADD_LO]);
    uint16_t u16val = word(VD_Modbus.au8Buffer[NB_HI],
                           VD_Modbus.au8Buffer[NB_LO]);
    regs[u8add] = u16val;
    /*keep the same header*/
    VD_Modbus.u8BufferSize = RESPONSE_SIZE;
}

/* Function Code 16: Write Multiple Registers */
static void process_FC16(uint16_t *regs, uint16_t maxRegs)
{
    uint8_t u8StartAdd = VD_Modbus.au8Buffer[ADD_HI] << 8 | VD_Modbus.au8Buffer[ADD_LO];
    uint8_t u8regsno = VD_Modbus.au8Buffer[NB_HI] << 8 | VD_Modbus.au8Buffer[NB_LO];
    uint16_t temp;

    // build header
    VD_Modbus.au8Buffer[NB_HI] = 0;
    VD_Modbus.au8Buffer[NB_LO] = u8regsno;
    VD_Modbus.u8BufferSize = RESPONSE_SIZE;

    // write registers
    uint8_t index;
    for (index = 0; index < u8regsno; index++)
    {
        temp = word(VD_Modbus.au8Buffer[(BYTE_CNT + 1) + index * 2],
                    VD_Modbus.au8Buffer[(BYTE_CNT + 2) + index * 2]);

        regs[u8StartAdd + index] = temp;
    }
}

void Modbus_Init(uint8_t slave_id)
{
    RS485_Config(&MODBUS1, &huart1, ENABLE_UART_GPIO_Port, ENABLE_UART_Pin);
    RS485_Init(&MODBUS1);
    VD_Modbus.u8id = slave_id;
    VD_Modbus.u8BufferSize = 0;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == MODBUS1.huart->Instance)
    {
        RS485_ReceiveHandler(&MODBUS1);
    }
}

void Modbus_ReceiveByte(uint8_t *byte)
{
    rxBuffer[rxIndex++] = *byte;
    lastByteTime = RS485_GetTick();

    if (rxIndex >= BUFFERSIZE)
        rxIndex = 0;
}

static void Modbus_sendTxBuffer(void)
{
    uint16_t crc = Modbus_calcCRC(VD_Modbus.u8BufferSize);
    VD_Modbus.au8Buffer[VD_Modbus.u8BufferSize++] = (uint8_t)(crc >> 8);
    VD_Modbus.au8Buffer[VD_Modbus.u8BufferSize++] = (uint8_t)(crc & 0xFF);

    RS485_SendData(&MODBUS1, VD_Modbus.au8Buffer, VD_Modbus.u8BufferSize);
    VD_Modbus.u8BufferSize = 0;
}

void Modbus_Process(uint16_t *Regs_Data, uint16_t maxRegs)
{
    VD_Modbus.u8regsize = maxRegs;

    if (rxIndex > 0 && (RS485_GetTick() - lastByteTime) >= 5)
    {
        // Lấy sao chép dữ liệu RX nhận được từ Master
        memcpy(VD_Modbus.au8Buffer, rxBuffer, rxIndex);
        VD_Modbus.u8BufferSize = rxIndex;
        rxIndex = 0;
        memset(rxBuffer, 0, BUFFERSIZE); // Reset lại Frame from Master

        // validate + xử lý request
        if (VD_Modbus.au8Buffer[ID] == VD_Modbus.u8id)
        {
            uint8_t u8exception = validateRequest();
            if (u8exception > 0)
            {
                buildException(u8exception);
                Modbus_sendTxBuffer();
            }
            else
            {
                /* Process message */
                switch (VD_Modbus.au8Buffer[FUNC])
                {
                case MB_FC_READ_INPUT_REGISTER:
                    process_FC3(Regs_Data, maxRegs);
                    Modbus_sendTxBuffer();
                    break;
                case MB_FC_READ_HOLD_REGISTERS:
                    process_FC3(Regs_Data, maxRegs);
                    Modbus_sendTxBuffer();
                    break;
                case MB_FC_WRITE_REGISTER:
                    process_FC6(Regs_Data, maxRegs);
                    Modbus_sendTxBuffer();
                    break;
                case MB_FC_WRITE_MULTIPLE_REGISTERS:
                    process_FC16(Regs_Data, maxRegs);
                    Modbus_sendTxBuffer();
                    break;
                default:
                    break;
                }
            }
        }
    }
}
