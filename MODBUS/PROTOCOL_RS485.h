/*
 * RS485.h
 *
 *  Created on: Oct 4, 2025
 *      Author: PC
 */

#ifndef PROTOCOL_RS485_H_
#define PROTOCOL_RS485_H_

#include "main.h"

#define BUFFERSIZE 100

#define lowByte(w) ((uint8_t)((w) & 0xff))
#define highByte(w) ((uint8_t)((w) >> 8))
#define word(h, l) (l & 0xff) | ((h & 0xff) << 8)

enum ERR_LIST
{
    ERR_TIMEOUT = -6,
    ERR_NOT_MASTER = -1,
    ERR_POLLING = -2,
    ERR_BUFF_OVERFLOW = -3,
    ERR_BAD_CRC = -4,
    ERR_EXCEPTION = -5
};

enum EXCEPTION_CODE
{
    EXC_Illegal_Function = 1,
    EXC_Illegal_Data_Address = 2,
    EXC_Illegal_Data_Value = 3,
    EXC_Slave_Device_Failure = 4
};

enum MB_FC
{
    MB_FC_NONE = 0,                     /*!< null operator */
    MB_FC_READ_COILS = 1,               /*!< FCT=1 -> read coils or digital outputs */
    MB_FC_READ_DISCRETE_INPUT = 2,      /*!< FCT=2 -> read digital inputs */
    MB_FC_READ_HOLD_REGISTERS = 3,      /*!< FCT=3 -> read registers or analog outputs */
    MB_FC_READ_INPUT_REGISTER = 4,      /*!< FCT=4 -> read analog inputs */
    MB_FC_WRITE_COIL = 5,               /*!< FCT=5 -> write single coil or output */
    MB_FC_WRITE_REGISTER = 6,           /*!< FCT=6 -> write single register */
    MB_FC_WRITE_MULTIPLE_COILS = 15,    /*!< FCT=15 -> write multiple coils or outputs */
    MB_FC_WRITE_MULTIPLE_REGISTERS = 16 /*!< FCT=16 -> write multiple registers */
};

enum MESSAGE_MODBUS_RTU
{
    ID = 0,  //!< ID field
    FUNC,    //!< Function code position
    ADD_HI,  //!< Address high byte
    ADD_LO,  //!< Address low byte
    NB_HI,   //!< Number of coils or registers high byte
    NB_LO,   //!< Number of coils or registers low byte
    BYTE_CNT //!< byte counter
};

enum
{
    RESPONSE_SIZE = 6,
    EXCEPTION_SIZE = 3,
    CHECKSUM_SIZE = 2
};

typedef struct
{
    uint8_t u8id;                  // Slave ID
    uint8_t u8BufferSize;          // số byte hiện tại trong buffer
    uint8_t au8Buffer[BUFFERSIZE]; // buffer dữ liệu
    uint16_t *au16regs;            // con trỏ tới vùng register user cấp
    uint16_t u8regsize;            // số lượng thanh ghi
} MODBUS;

void Modbus_Init(uint8_t slave_id);
void Modbus_ReceiveByte(uint8_t *byte);
void Modbus_Process(uint16_t *Regs_Data, uint16_t maxRegs);

#endif /* PROTOCOL_RS485_H_ */
