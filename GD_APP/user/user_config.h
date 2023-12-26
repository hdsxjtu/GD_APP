/**
 * @file user_config.h
 * @author Duan, Xinyu (Xinyu.Duan@Honeywell.com)
 * @brief
 * @version 1.0
 * @date 2023-03-30
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef __USER_CONFIG_H__
#define __USER_CONFIG_H__

#include <stdint.h>

#define USER_CONFIG_MAGIC 0x89ABCDEF

typedef struct
{
    uint32_t magic;
    uint8_t address;
    uint8_t canBaud;
} user_eeprom_data;

extern user_eeprom_data g_UserConfig;
extern user_eeprom_data g_UserConfigDefault;
extern const uint16_t gFirmwareVersion;

uint32_t UserConfigWrite(uint8_t *data, uint32_t length);
void UserConfigRead(uint8_t *data, uint32_t length);
void UserAddressSet(uint8_t address);
void LED_ALLON();
#endif
