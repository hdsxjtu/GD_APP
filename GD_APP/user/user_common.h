/**
 * @file user_common.h
 * @author Duan, Xinyu (Xinyu.Duan@Honeywell.com)
 * @brief 
 * @version 1.0
 * @date 2023-03-30
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __USER_COMMON_H__
#define __USER_COMMON_H__

#include <stdint.h>
#include "main.h"

#define USER_MAKE_VERSION(m, s) (((uint16_t)(m) << 8) | (s & 0xFF))
//#define USE_WDT 1

#define APP_VERSION_MASK    0xFFFF
#define APP_VERSION_SHIFT   2U

#define WAIT_TIME_FOR_BOOT_CMD 1000

#define USER_COMMON_CAN_FIFO_QUEEN_SIZE 32U
#define USER_COMMON_CAN_RX_BUFFER_SIZE 8U

typedef struct 
{
  uint8_t data[USER_COMMON_CAN_RX_BUFFER_SIZE];
  uint8_t len;
  uint8_t cmd;
}CAN_COMMAND_PROTOCOL;

typedef struct
{
	CAN_COMMAND_PROTOCOL Buf[USER_COMMON_CAN_FIFO_QUEEN_SIZE];    /* can数据接收缓冲区 */
	uint8_t Read;				   /* 缓冲区读指针1 */
	uint8_t Write;				   /* 缓冲区写指针 */
} CAN_FIFO_T;

typedef	__PACKED_STRUCT{
	uint32_t App_Version;		// APP软件版本
	uint32_t Boot_Version;		// BOOT软件版本        
	uint32_t App_Status;		// APP0的状态. @Application_Status_t
}SystemParamTypeDef;

typedef enum {
	APPLICATION_NORMAL = 0,		// APP能正常稳定运行
	APPLICATION_UPDATED,		// APP刚更新完成，等待测试启动
	APPLICATION_ERROR,	        // APP错误，不能正常工作
}Application_Status_t;

typedef enum
{
    LED_OFF = 0,
    LED_ON,
    LED_BLINK
} USER_LED_STATUS_t;

#define RESET_CMD 0x05
#define FILE_DATA 0x0F
#define FILE_MSG  0x0E
#define ASK_VER   0x0D

uint32_t User4BytesLSBToUint(uint8_t *data);
float User4BytesMSBLSBToFloat(uint8_t *data);
void UserFloatToMSBLSB4Bytes(float fValue, uint8_t *data);
uint32_t User4BytesMSBLSBToUint(uint8_t *data);
void UserUintToMSBLSB4Bytes(uint32_t value, uint8_t *data);
uint16_t User2BytesMSBLSBToUshort(uint8_t *data);
void UserUshortToMSBLSB2Bytes(uint16_t value, uint8_t *data);
uint16_t User2BytesMSBLSBToUint(uint8_t *data);
void UserUintToMSBLSB2Bytes(uint32_t value, uint8_t *data);
#endif /* __USER_COMMON_H__ */
