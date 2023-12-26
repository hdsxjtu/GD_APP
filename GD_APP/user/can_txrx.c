/**
 * @file can_txrx.c
 * @author Duan, Xinyu (Xinyu.Duan@Honeywell.com)
 * @brief CAN BUS底层支持
 * @version 1.0
 * @date 2023-03-30
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "can.h"
#include <string.h>
#include "main.h"
#include "can_txrx.h"




#define CAN_ID_DIRECTION_MASK  0x400
#define CAN_ID_DIRECTION_SHIFT 10U
#define CAN_ID_CODE_MASK       0x3C0
#define CAN_ID_CODE_SHIFT      6U
#define CAN_ID_ADDRESS_MASK    0x3F
#define CAN_ID_ADDRESS_SHIFT   0U

static CAN_FIFO_T canBufQueen;
static CAN_COMMAND_PROTOCOL *canData;
// clang-format off
//static user_common_uart_rx_buffer_t rx_buffer[ CAN_RX_BUFFER_COUNT ];
// clang-format on
//      static user_common_uart_rx_buffer_t *current_rx_buffer = NULL;


void CANFilterConfig_Scale32_IdMask_StandardIdOnly(void)
{
    CanFIFOInit();

    CAN_FilterTypeDef sFilterConfig;
    uint16_t StdIdArray[4] = {0x140}; // 定义一组标准CAN ID
    uint16_t mask, num, tmp, i;

    sFilterConfig.FilterBank = 0;                      // 使用过滤器2
    sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;  // 配置为掩码模式
    sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT; // 设置为32位宽
    sFilterConfig.FilterIdHigh = (StdIdArray[0] << 5); // 验证码可以设置为StdIdArray[]数组中任意一个，这里使用StdIdArray[0]作为验证码
    sFilterConfig.FilterIdLow = 0;

    mask = 0x7ff; // 下面开始计算屏蔽码
    num = sizeof(StdIdArray) / sizeof(StdIdArray[0]);
    for (i = 0; i < num; i++) // 屏蔽码位StdIdArray[]数组中所有成员的同或结果
    {
        tmp = StdIdArray[i] ^ (~StdIdArray[0]); // 所有数组成员与第0个成员进行同或操作
        mask &= tmp;
    }
    sFilterConfig.FilterMaskIdHigh = (mask << 5);
    sFilterConfig.FilterMaskIdLow = 0 | 0x02; // 只接收数据帧

    sFilterConfig.FilterFIFOAssignment = 0; // 设置通过的数据帧进入到FIFO0中
    sFilterConfig.FilterActivation = ENABLE;
    sFilterConfig.SlaveStartFilterBank = 14;

    if (HAL_CAN_ConfigFilter(&hcan, &sFilterConfig) != HAL_OK)
    {
        Error_Handler();
    }
    // 启动CAN外围设备
    if (HAL_CAN_Start(&hcan) != HAL_OK)
    {
        Error_Handler();
    }

    // 濿活可以RX通知
    if (HAL_CAN_ActivateNotification(&hcan, CAN_IT_RX_FIFO0_MSG_PENDING) != HAL_OK)
    {
        Error_Handler();
    }    
}
/**
 * @brief  Rx Fifo 0 message pending callback in non blocking mode
 * @param  CanHandle: pointer to a CAN_HandleTypeDef structure that contains
 *         the configuration information for the specified CAN.
 * @retval None
 */
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *CanHandle)
{
    CAN_RxHeaderTypeDef rxHeader;
    uint8_t rxData[8] = {0};
    /**< 获取CAN接收的消息 */
    if (HAL_CAN_GetRxMessage(CanHandle, CAN_RX_FIFO0, &rxHeader, rxData) != HAL_OK)
    {
        /**< 错误处理 */
        Error_Handler();
    }
    CanFIFOPut(rxData, (rxHeader.StdId & CAN_ID_CODE_MASK) >> CAN_ID_CODE_SHIFT, rxHeader.DLC);
}

/**
 * @brief CAN发送消息
 *
 * @param address 源的地址
 * @param code 要发送的功能码。详见通信协议。
 * @param msg 指向待发送消息的指针
 * @param length 待发送消息长度
 */
void UserCANSendMessage(uint8_t address, uint8_t code, uint8_t *msg, uint8_t length)
{
    CAN_TxHeaderTypeDef txHeader;
    uint32_t txMailbox;

    /* Configure Transmission process */
    txHeader.StdId = CAN_ID_DIRECTION_MASK | ((code << CAN_ID_CODE_SHIFT) & CAN_ID_CODE_MASK) |
                     ((address << CAN_ID_ADDRESS_SHIFT) & CAN_ID_ADDRESS_MASK);
    txHeader.ExtId = 0x01;
    txHeader.RTR = CAN_RTR_DATA;
    txHeader.IDE = CAN_ID_STD;
    txHeader.DLC = length;

    txHeader.TransmitGlobalTime = DISABLE;

    if (HAL_CAN_AddTxMessage(&hcan, &txHeader, msg, &txMailbox) != HAL_OK)
    
    {
        /* Transmission request Error */
        Error_Handler();
    }

}

/**
 * @brief 把收到的CAN消息放入FIFO
 *
 * @param buf can消息数据
 * @param cmd can消息功能码
 * @param len can消息长度
 */
void CanFIFOPut(uint8_t *buf, uint8_t cmd, uint8_t len)
{
    // canBufQueen.Buf[s_tKey.Write][] = _KeyCode;
    memset((void *)&canBufQueen.Buf[canBufQueen.Write], 0x00, sizeof(CAN_COMMAND_PROTOCOL) / sizeof(uint8_t));
    memcpy(canBufQueen.Buf[canBufQueen.Write].data, buf, len);
    canBufQueen.Buf[canBufQueen.Write].cmd = cmd;
    canBufQueen.Buf[canBufQueen.Write].len = len;
    if (++canBufQueen.Write >= USER_COMMON_CAN_FIFO_QUEEN_SIZE)
    {
        canBufQueen.Write = 0;
    }
}

/**
 * @brief 从FIFO中获取can消息
 *
 * @return CAN_COMMAND_PROTOCOL*
 */
CAN_COMMAND_PROTOCOL *CanFIFOGet(void)
{
    CAN_COMMAND_PROTOCOL *ret;

    if (canBufQueen.Read == canBufQueen.Write)
    {
        return NULL;
    }
    else
    {
        ret = &canBufQueen.Buf[canBufQueen.Read];

        if (++canBufQueen.Read >= USER_COMMON_CAN_FIFO_QUEEN_SIZE)
        {
            canBufQueen.Read = 0;
        }
        return ret;
    }
}

/**
 * @brief 初始化CAN的FIFO
 *
 */
void CanFIFOInit(void)
{
    /* 对按键FIFO读写指针清零 */
    canBufQueen.Read = 0;
    canBufQueen.Write = 0;
    memset((void *)&canBufQueen,0x00,sizeof(canBufQueen)/sizeof(uint8_t));
}



void SystemParam_IAP()
{
  uint8_t canTxBuffer[8];
  memset(canTxBuffer, 0x00, sizeof(canTxBuffer));
  canData = CanFIFOGet();
  if (canData != NULL)
  {
    // printf("REC A CMD\r\n");
    if (canData->cmd == RESET_CMD)
    {
      NVIC_SystemReset();
    }
  }
}