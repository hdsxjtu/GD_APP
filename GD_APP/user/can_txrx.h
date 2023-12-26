/**
 * @file can_txrx.h
 * @author Duan, Xinyu (Xinyu.Duan@Honeywell.com)
 * @brief
 * @version 1.0
 * @date 2023-03-30
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef __CAN_TXRX_H__
#define __CAN_TXRX_H__
#include "user_common.h"

void SystemParam_IAP();
void CANFilterConfig_Scale32_IdMask_StandardIdOnly();
void UserCANSendMessage(uint8_t address, uint8_t code, uint8_t *msg, uint8_t length);
void CanFIFOInit(void);                                  // 初始化队列
CAN_COMMAND_PROTOCOL *CanFIFOGet(void);                  // 获取队列can消息
void CanFIFOPut(uint8_t *buf, uint8_t cmd, uint8_t len); // can消息放入队列
CAN_COMMAND_PROTOCOL *CanFIFOGet(void);                  // can消息取出队列
#endif                                                   /** __CAN_TXRX_H__ */
