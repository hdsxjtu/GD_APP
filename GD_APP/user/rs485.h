/**
 * @file rs485.h
 * @author Duan, Xinyu (Xinyu.Duan@Honeywell.com)
 * @brief 
 * @version 1.0
 * @date 2023-03-30
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __USER_RS485_H__
#define __USER_RS485_H__
#include "stdio.h"


void RS485SendData(uint8_t *buffer, uint16_t length);
void RS485Dir(uint8_t var);
int fputc(int ch, FILE *f);
#endif /* __USER_RS485_H__ */
