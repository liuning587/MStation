/**
 ******************************************************************************
 * @file       MStationServer.h
 * @brief      API include file of MStationServer.h.
 * @details    This file including all API functions's declare of MStationServer.h.
 * @copyright  Copyrigth(C), 2008-2012,Sanxing Electric Co.,Ltd.
 *
 ******************************************************************************
 */
#ifndef MSTATIONSERVER_H_
#define MSTATIONSERVER_H_ 

/*-----------------------------------------------------------------------------
 Section: Includes
 ----------------------------------------------------------------------------*/
/* NONE */

/*-----------------------------------------------------------------------------
 Section: Macro Definitions
 ----------------------------------------------------------------------------*/
/* NONE */

/*-----------------------------------------------------------------------------
 Section: Type Definitions
 ----------------------------------------------------------------------------*/
typedef struct
{
    char ESAMNo[17];     /**< ESAM序列号; 8字节  */
    char state[3];      /**< 证书状态标识; 1字节, 00--测试证书, 01--正式证书 */
    char VersionNum[3]; /**< 版本号; 1字节,固定“01”  */
    char SessionID[1];  /**< 会话ID; 1字节, 00-- 新建注册, 01--恢复 */
    char R1[16];        /**< 随机数1; 16字节 */
} msi3_t;

typedef struct
{
    int ret;            /**< 加密机返回值 */
    char message1[2048];/**< 报文1; N字节(大于1K,小于2K) */
} mso3_t;

typedef struct
{
    char ESAMNo[8];     /**< ESAM序列号; 8字节  */
    char state[3];      /**< 证书状态标识; 1字节, 00--测试证书, 01--正式证书 */
    char message2[2048];/**< 报文2; N字节(小于2K) */
} msi4_t;

typedef struct
{
    int ret;            /**< 加密机返回值 */
    char message3[2048];/**< 报文3; N字节(小于2K) */
} mso4_t;

typedef struct
{
    char message4[20];  /**< 报文4; 20字节 */
} msi5_t;

typedef struct
{
    int ret;            /**< 加密机返回值 */
} mso5_t;

typedef struct
{
    char ESAMNo[8];     /**< ESAM序列号; 8字节 */
    char message2[38];  /**< 报文2; 38字节 */
} msi6_t;

typedef struct
{
    int ret;            /**< 加密机返回值 */
} mso6_t;

typedef struct
{
    char state[3];      /**< 证书状态标识; 1字节, 00--测试证书, 01--正式证书 */
    int keyID;          /**< 密钥索引; 0x20 <= keyID值 <= 0x33 */
    char ESAMNo[8];     /**< ESAM序列号; 8字节 */
} msi7_t;

typedef struct
{
    char MAC[4];
};
/*-----------------------------------------------------------------------------
 Section: Globals
 ----------------------------------------------------------------------------*/
/* NONE */

/*-----------------------------------------------------------------------------
 Section: Function Prototypes
 ----------------------------------------------------------------------------*/
/* NONE */


#endif /* MSTATIONSERVER_H_ */
/*--------------------------End of MStationServer.h-----------------------------*/
