/*
 * M24C02.c
 *
 *  Created on: Jun 27, 2024
 *      Author: PC
 */

#include "PROTOCAL_EEPROM.h"

/**
 * @brief
 * This function is used write two bytes to EEPROM .
 * @param address Address in EEPROM
 * @param data Two bytes write to EEPROM
 * @retval HAL status
 */
HAL_StatusTypeDef PE_WriteExtEepromU16(uint16_t address, int16_t data)
{
	HAL_StatusTypeDef output;
	uint8_t array_write[4];
	// Địa chỉ 16-bit: High trước, Low sau
	array_write[0] = (uint8_t)(address >> 8);	// High address
	array_write[1] = (uint8_t)(address & 0xFF); // Low address

	// 2 byte dữ liệu
	array_write[2] = (uint8_t)((data >> 8) & 0xFF);
	array_write[3] = (uint8_t)(data & 0xFF);

	// Gửi qua I2C (6 byte: 2 byte địa chỉ + 4 byte data)
	output = HAL_I2C_Master_Transmit(&hi2c1, CALIB_EEPROM_WR, array_write, 4, HAL_MAX_DELAY);

	// Đợi EEPROM hoàn tất ghi (tối đa ~5 ms, nhưng nên để 10 ms cho an toàn)
	// HAL_Delay(10);

	return output;
}

/**
 * @brief
 * This function is used read two bytes from EEPROM .
 * @param address Address in EEPROM
 * @param data int16 (two bytes) read from EEPROM
 * @retval HAL status
 */
HAL_StatusTypeDef PE_ReadExtEepromU16(uint16_t address, int16_t *data)
{
	HAL_StatusTypeDef output;
	uint8_t addr[2];
	uint8_t buffer[2];

	// Địa chỉ 16-bit
	addr[0] = (uint8_t)(address >> 8);
	addr[1] = (uint8_t)(address & 0xFF);

	// Gửi địa chỉ đọc
	output = HAL_I2C_Master_Transmit(&hi2c1, CALIB_EEPROM_WR, addr, 2, HAL_MAX_DELAY);
	if (output != HAL_OK)
		return output;

	// Đọc 4 byte dữ liệu
	output = HAL_I2C_Master_Receive(&hi2c1, CALIB_EEPROM_RD, buffer, 2, HAL_MAX_DELAY);
	if (output != HAL_OK)
		return output;

	// Ghép lại thành int16_t
	*data = ((int16_t)buffer[0] << 8) |
			(int16_t)buffer[1];

	return HAL_OK;
}

/**
 * @brief
 * Đang ký hàm ghi 32-bit vào EEPROM.
 * @param address Địa chỉ bắt đầu ghi trong EEPROM.
 * @param data Dữ liệu 32-bit cần ghi vào EEPROM.
 * @retval HAL status
 * @note Hàm này sẽ ghi 4 byte dữ liệu vào EEPROM bắt đầu từ địa chỉ được cung cấp.
 */
HAL_StatusTypeDef PE_WriteExtEepromU32(uint16_t address, uint32_t data)
{
	HAL_StatusTypeDef output;
	uint8_t array_write[6];
	// Địa chỉ 16-bit: High trước, Low sau
	array_write[0] = (uint8_t)(address >> 8);	// High address
	array_write[1] = (uint8_t)(address & 0xFF); // Low address

	// 4 byte dữ liệu
	array_write[2] = (uint8_t)((data >> 24) & 0xFF);
	array_write[3] = (uint8_t)((data >> 16) & 0xFF);
	array_write[4] = (uint8_t)((data >> 8) & 0xFF);
	array_write[5] = (uint8_t)(data & 0xFF);

	// Gửi qua I2C (6 byte: 2 byte địa chỉ + 4 byte data)
	output = HAL_I2C_Master_Transmit(&hi2c1, CALIB_EEPROM_WR, array_write, 6, HAL_MAX_DELAY);

	// Đợi EEPROM hoàn tất ghi (tối đa ~5 ms, nhưng nên để 10 ms cho an toàn)
	// HAL_Delay(10);

	return output;
}

/**
 * @brief
 * Đang ký hàm đọc 32-bit từ EEPROM.
 * @param address Địa chỉ bắt đầu đọc trong EEPROM.
 * @param data Con trỏ đến biến 32-bit để lưu dữ liệu đọc từ EEPROM
 * @retval HAL status
 */
HAL_StatusTypeDef PE_ReadExtEEproomU32(uint16_t address, uint32_t *data)
{
	HAL_StatusTypeDef output;
	uint8_t addr[2];
	uint8_t buffer[4];

	// Địa chỉ 16-bit
	addr[0] = (uint8_t)(address >> 8);
	addr[1] = (uint8_t)(address & 0xFF);

	// Gửi địa chỉ đọc
	output = HAL_I2C_Master_Transmit(&hi2c1, CALIB_EEPROM_WR, addr, 2, HAL_MAX_DELAY);
	if (output != HAL_OK)
		return output;

	// Đọc 4 byte dữ liệu
	output = HAL_I2C_Master_Receive(&hi2c1, CALIB_EEPROM_RD, buffer, 4, HAL_MAX_DELAY);
	if (output != HAL_OK)
		return output;

	// Ghép lại thành uint32_t
	*data = ((uint32_t)buffer[0] << 24) |
			((uint32_t)buffer[1] << 16) |
			((uint32_t)buffer[2] << 8) |
			(uint32_t)buffer[3];

	return HAL_OK;
}
