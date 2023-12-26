/**
 * @file rs485.c
 * @author Duan, Xinyu (Xinyu.Duan@Honeywell.com)
 * @brief RS485的底层支持文件
 * @version 1.0
 * @date 2023-03-30
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <stdint.h>
#include "main.h"
#include "usart.h"
#include "rs485.h"
#include <stdarg.h>
#include "stdio.h"

/**
 * @brief RS485 阻塞发送数据
 * 
 * @param buffer 指向待发送数据的buffer
 * @param length 待发送数据的长度
 */
void RS485SendData(uint8_t *buffer, uint16_t length)
{
    uint32_t timeout = 2000;

    HAL_GPIO_WritePin(EN_485_GPIO_Port,EN_485_Pin,GPIO_PIN_SET);
    HAL_UART_Transmit(&huart3, buffer, length, timeout);
    HAL_GPIO_WritePin(EN_485_GPIO_Port,EN_485_Pin,GPIO_PIN_RESET);
}


/**
 * @brief  Print a string on the HyperTerminal
 * @param  p_string: The string to be printed
 * @retval None
 */
void DebugPrintf(uint8_t *p_string)
{
    uint32_t timeout = 2000;
    uint16_t length = 0;
    HAL_GPIO_WritePin(EN_485_GPIO_Port,EN_485_Pin,GPIO_PIN_SET);      
    while (p_string[length] != '\0')
    {
            length++;
    }
    HAL_UART_Transmit(&huart3, p_string, length, timeout);
    HAL_GPIO_WritePin(EN_485_GPIO_Port,EN_485_Pin,GPIO_PIN_RESET);  
}



void RS485Dir(uint8_t var)
{
  if(var>0)
  {
    HAL_GPIO_WritePin(EN_485_GPIO_Port,EN_485_Pin,GPIO_PIN_SET);   
  }
  else
  {
    HAL_GPIO_WritePin(EN_485_GPIO_Port,EN_485_Pin,GPIO_PIN_RESET); 
  }
}

int fputc(int ch, FILE *f)
{
	HAL_UART_Transmit(&huart3, (uint8_t *)&ch, 1, 0xFFFF);//huart3为重定向的串口
	return ch;
}
