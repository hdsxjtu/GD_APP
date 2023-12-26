/**
 * @file user_config.c
 * @author Duan, Xinyu (Xinyu.Duan@Honeywell.com)
 * @brief
 * @version 1.0
 * @date 2023-03-30
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <string.h>
#include "user_common.h"
#include "user_config.h"
#include "stm32f1xx_hal.h"
#include "main.h"


// clang-format off
user_eeprom_data g_UserConfigDefault = {
    .magic = USER_CONFIG_MAGIC,
    .address  = 2,
    .canBaud = 0,
};

user_eeprom_data g_UserConfig = {
    .magic = USER_CONFIG_MAGIC,
    .address  = 2,
    .canBaud = 0,
};

// clang-format on

#define CONFIG_FLASH_PAGE_SIZE (uint16_t)0x800 /* Page size = 2KByte */
#define CONFIG_START_ADDRESS ((uint32_t)0x0801E000)

/**
 * @brief 从Flash中读取配置数据
 *
 * @param data 指向存放读取到的数据的指针
 * @param length 要读取的长度
 */
void UserConfigRead(uint8_t *data, uint32_t length)
{
    __IO uint32_t *startAddress = (__IO uint32_t *)CONFIG_START_ADDRESS;

    memcpy((void *)data, (void *)startAddress, length);
}


