/**
 * @file user_common.c
 * @author Duan, Xinyu (Xinyu.Duan@Honeywell.com)
 * @brief 
 * @version 1.0
 * @date 2023-03-30
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "user_common.h"


   
/**
 * @brief 将4个字节的大端数据转换成float型数据
 * 
 * @param data 指向存放4字节数据的指针
 * @return float 转换后的float数据
 */
float User4BytesMSBLSBToFloat(uint8_t *data)
{
    float fValue     = 0.0;
    uint8_t tmp[ 4 ] = {0};
    tmp[ 3 ]         = *data;
    tmp[ 2 ]         = *(data + 1);
    tmp[ 1 ]         = *(data + 2);
    tmp[ 0 ]         = *(data + 3);
    fValue           = *(float *)&tmp;
    return fValue;
}

/**
 * @brief 将float型数据转换成4个字节的大端数据
 * 
 * @param fValue 待转换的float数据
 * @param data 指向存放4字节数据的指针
 */
void UserFloatToMSBLSB4Bytes(float fValue, uint8_t *data)
{
    uint32_t tmp;

    tmp = *(uint32_t *)&fValue;

    *data       = (tmp >> 24) & 0xFF;
    *(data + 1) = (tmp >> 16) & 0xFF;
    *(data + 2) = (tmp >> 8) & 0xFF;
    *(data + 3) = tmp & 0xFF;
}

/**
 * @brief 将4个字节的大端数据转换成无符号int型数据
 * 
 * @param data 指向存放4字节数据的指针
 * @return uint32_t 转换后的无符号int数据
 */
uint32_t User4BytesMSBLSBToUint(uint8_t *data)
{
    uint32_t value   = 0;
    uint8_t tmp[ 4 ] = {0};
    tmp[ 3 ]         = *data;
    tmp[ 2 ]         = *(data + 1);
    tmp[ 1 ]         = *(data + 2);
    tmp[ 0 ]         = *(data + 3);
    value            = *(uint32_t *)&tmp;
    return value;
}

/**
 * @brief 将4个字节的小端数据转换成无符号int型数据
 * 
 * @param data 指向存放4字节数据的指针
 * @return uint32_t 转换后的无符号int数据
 */
uint32_t User4BytesLSBToUint(uint8_t *data)
{
    uint32_t value   = 0;
    uint8_t tmp[ 4 ] = {0};
    tmp[ 0 ]         = *data;
    tmp[ 1 ]         = *(data + 1);
    tmp[ 2 ]         = *(data + 2);
    tmp[ 3 ]         = *(data + 3);
    value            = *(uint32_t *)&tmp;
    return value;
}
      
      
/**
 * @brief 将无符号int型数据转换成4个字节的大端数据
 * 
 * @param value 待转换的无符号int型数据
 * @param data 指向存放4字节数据的指针
 */
void UserUintToMSBLSB4Bytes(uint32_t value, uint8_t *data)
{
    *data       = (value >> 24) & 0xFF;
    *(data + 1) = (value >> 16) & 0xFF;
    *(data + 2) = (value >> 8) & 0xFF;
    *(data + 3) = value & 0xFF;
}

/**
 * @brief 将2个字节的大端数据转换成无符号short型数据
 * 
 * @param data 指向存放2字节数据的指针
 * @return uint16_t 转换后的无符号short数据
 */
uint16_t User2BytesMSBLSBToUshort(uint8_t *data)
{
    uint16_t value   = 0;
    uint8_t tmp[ 4 ] = {0};

    tmp[ 1 ] = *data;
    tmp[ 0 ] = *(data + 1);
    value    = *(uint16_t *)&tmp;
    return value;
}

/**
 * @brief 将无符号short型数据转换成4个字节的大端数据
 * 
 * @param value 待转换的无符号short型数据
 * @param data 指向存放2字节数据的指针
 */
void UserUshortToMSBLSB2Bytes(uint16_t value, uint8_t *data)
{
    *data = (value >> 8) & 0xFF;

    *(data + 1) = value & 0xFF;
}

/**
 * @brief 将2个字节的大端数据转换成无符号int型数据
 * 
 * @param data 指向存放4字节数据的指针
 * @return uint16_t 转换后的无符号int数据
 */
uint16_t User2BytesMSBLSBToUint(uint8_t *data)
{
    uint32_t value   = 0;
    uint8_t tmp[ 4 ] = {0};
    tmp[ 1 ]         = *data;
    tmp[ 0 ]         = *(data + 1);
    value            = *(uint16_t *)&tmp;
    return value;
}

/**
 * @brief 将无符号int型数据转换成4个字节的大端数据
 * 
 * @param value 待转换的无符号int型数据
 * @param data 指向存放4字节数据的指针
 */
void UserUintToMSBLSB2Bytes(uint32_t value, uint8_t *data)
{
    *(data + 0) = (value >> 8) & 0xFF;
    *(data + 1) = value & 0xFF;
}

