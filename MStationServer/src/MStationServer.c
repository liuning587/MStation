/**
 ******************************************************************************
 * @file      MStationServer.c
 * @brief     TESAM加密机服务器程序。
 * @details   This file including all API functions's 
 *            implement of MStationServer.c.	
 *
 * @copyright Copyrigth(C), 2008-2012,Sanxing Electric Co.,Ltd.
 ******************************************************************************
 */
 
/*-----------------------------------------------------------------------------
 Section: Includes
 ----------------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <MStation.h>
#include "config.h"
#include "log.h"
#include "iniparser.h"

/*-----------------------------------------------------------------------------
 Section: Type Definitions
 ----------------------------------------------------------------------------*/
typedef void (*pfn_mstation)(const char *pin, char *pout);

/*-----------------------------------------------------------------------------
 Section: Constant Definitions
 ----------------------------------------------------------------------------*/
/* NONE */ 

/*-----------------------------------------------------------------------------
 Section: Global Variables
 ----------------------------------------------------------------------------*/
/* NONE */

/*-----------------------------------------------------------------------------
 Section: Local Function Prototypes
 ----------------------------------------------------------------------------*/
static void pfn1(const char *pin, char *pout);
static void pfn2(const char *pin, char *pout);
static void pfn3(const char *pin, char *pout);
static void pfn4(const char *pin, char *pout);
static void pfn5(const char *pin, char *pout);
static void pfn6(const char *pin, char *pout);
static void pfn7(const char *pin, char *pout);
static void pfn8(const char *pin, char *pout);
static void pfn9(const char *pin, char *pout);
static void pfn10(const char *pin, char *pout);
static void pfn11(const char *pin, char *pout);
static void pfn12(const char *pin, char *pout);
static void pfn13(const char *pin, char *pout);
static void pfn14(const char *pin, char *pout);
static void pfn15(const char *pin, char *pout);
static void pfn16(const char *pin, char *pout);
static void pfn17(const char *pin, char *pout);

/*-----------------------------------------------------------------------------
 Section: Local Variables
 ----------------------------------------------------------------------------*/
static pfn_mstation the_pfn[18] =
{
        NULL,
        pfn1,
        pfn2,
        pfn3,
        pfn4,
        pfn5,
        pfn6,
        pfn7,
        pfn8,
        pfn9,
        pfn10,
        pfn11,
        pfn12,
        pfn13,
        pfn14,
        pfn15,
        pfn16,
        pfn17,
};

/*-----------------------------------------------------------------------------
 Section: Function Definitions
 ----------------------------------------------------------------------------*/
/**
 ******************************************************************************
 * @brief      1. 打开读卡器
 * @param[in]  *pbuf    : 数据输入输出缓存
 * @retval     None
 ******************************************************************************
 */
static void pfn1(const char *pin, char *pout)
{

}

/**
 ******************************************************************************
 * @brief      2. 关闭读卡器
 * @param[in]  *pbuf    : 数据输入输出缓存
 * @retval     None
 ******************************************************************************
 */
static void pfn2(const char *pin, char *pout)
{

}

/**
 ******************************************************************************
 * @brief      3. 会话初始化/恢复
 * @param[in]  *pbuf    : 数据输入输出缓存
 * @retval     None
 ******************************************************************************
 */
static void pfn3(const char *pin, char *pout)
{
    int ret = 0;
    int *inlen = (int*)pin;
    int *outlen = (int*)pout;
    char *pos = (char*)pin + sizeof(int);
    char *ESAMNo, *state, *VersionNum, *SessionID, *R1, *message1;
    const char *pfname = "3. 会话初始化/恢复";

    ESAMNo = pos ;
    pos += strlen(pos) + 1;
    state = pos;
    pos += strlen(pos) + 1;
    VersionNum = pos;
    pos += strlen(pos) + 1;
    SessionID = pos;
    pos += strlen(pos) + 1;
    R1 = pos;
    pos += strlen(pos) + 1;
    if ((pos - pin - sizeof(int)) != *inlen)
    {
        log_print("%s[长度不匹配]", pfname);
    }

    message1 = pout + sizeof(int);
    message1 = '\0';

    ret = SessionInitRec(ESAMNo, state, VersionNum, SessionID, R1, message1);
    memcpy(pout, &ret, sizeof(int));
    *pout = sizeof(int);

    switch (ret)
    {
        case 0:
            *pout += strlen(message1) + 1;
            log_print("%s[成功]", pfname);
            break;
        case 1001:
            log_print("%s[ESAM序列号错误]", pfname);
            break;
        case 1002:
            log_print("%s[证书状态标识错误]", pfname);
            break;
        case 1003:
            log_print("%s[版本号错误]", pfname);
            break;
        case 1004:
            log_print("%s[会话ID错误]", pfname);
            break;
        case 1005:
            log_print("%s[随机数错误]", pfname);
            break;
        default:
            log_print("%s[未知]", pfname);
            break;
    }
}

/**
 ******************************************************************************
 * @brief      4. 会话密钥协商
 * @param[in]  *pbuf    : 数据输入输出缓存
 * @retval     None
 ******************************************************************************
 */
static void pfn4(const char *pin, char *pout)
{
    int ret = 0;
    int *inlen = (int*)pin;
    int *outlen = (int*)pout;
    char *pos = (char*)pin + sizeof(int);
    char *ESAMNo, *state, *VersionNum, *message2, *message3;
    const char *pfname = "4. 会话密钥协商";

    ESAMNo = pos ;
    pos += strlen(pos) + 1;
    state = pos;
    pos += strlen(pos) + 1;
    VersionNum = pos;
    pos += strlen(pos) + 1;
    message2 = pos;
    pos += strlen(pos) + 1;
    message3 = pos;
    pos += strlen(pos) + 1;
    if ((pos - pin - sizeof(int)) != *inlen)
    {
        log_print("%s[长度不匹配]", pfname);
    }
    message3 = pout + sizeof(int);
    message3 = '\0';
    ret = SessionKeyConsult(ESAMNo, state, message2, message3);
    memcpy(pout, &ret, sizeof(int));
    *pout = sizeof(int);

    switch (ret)
    {
        case 0:
            *pout += strlen(message3) + 1;
            log_print("%s[成功]", pfname);
            break;
        case 1001:
            log_print("%s[ESAM序列号错误]", pfname);
            break;
        case 1002:
            log_print("%s[证书状态标识错误]", pfname);
            break;
        case 1003:
            log_print("%s[报文2错误]", pfname);
            break;
        default:
            log_print("%s[未知]", pfname);
            break;
    }
}

/**
 ******************************************************************************
 * @brief      5. 会话协商验证
 * @param[in]  *pbuf    : 数据输入输出缓存
 * @retval     None
 ******************************************************************************
 */
static void pfn5(const char *pin, char *pout)
{
    int ret = 0;
    int *inlen = (int*)pin;
    int *outlen = (int*)pout;
    char *pos = (char*)pin + sizeof(int);
    char *message4;
    const char *pfname = "5. 会话协商验证";

    message4 = pos ;
    pos += strlen(pos) + 1;
    if ((pos - pin - sizeof(int)) != *inlen)
    {
        log_print("%s[长度不匹配]", pfname);
    }

    ret = SessionConsultVerify(message4);
    memcpy(pout, &ret, sizeof(int));
    *pout = sizeof(int);

    switch (ret)
    {
        case 0:
            log_print("%s[成功]", pfname);
            break;
        case 1001:
            log_print("%s[报文4错误]", pfname);
            break;
        default:
            log_print("%s[未知]", pfname);
            break;
    }
}

/**
 ******************************************************************************
 * @brief      6. 会话恢复验证
 * @param[in]  *pbuf    : 数据输入输出缓存
 * @retval     None
 ******************************************************************************
 */
static void pfn6(const char *pin, char *pout)
{
    int ret = 0;
    int *inlen = (int*)pin;
    int *outlen = (int*)pout;
    char *pos = (char*)pin + sizeof(int);
    char *ESAMNo, *message2;
    const char *pfname = "6. 会话恢复验证";

    ESAMNo = pos;
    pos += strlen(pos) + 1;
    message2 = pos;
    pos += strlen(pos) + 1;
    if ((pos - pin - sizeof(int)) != *inlen)
    {
        log_print("%s[长度不匹配]", pfname);
    }

    ret = SessionRecoveryVerify(ESAMNo, message2);
    memcpy(pout, &ret, sizeof(int));
    *pout = sizeof(int);

    switch (ret)
    {
        case 0:
            log_print("%s[成功]", pfname);
            break;
        case 1001:
            log_print("%s[ESAM序列号错误]", pfname);
            break;
        case 1002:
            log_print("%s[报文2错误]", pfname);
            break;
        default:
            log_print("%s[未知]", pfname);
            break;
    }
}

/**
 ******************************************************************************
 * @brief      7. MAC校验
 * @param[in]  *pbuf    : 数据输入输出缓存
 * @retval     None
 ******************************************************************************
 */
static void pfn7(const char *pin, char *pout)
{

}

/**
 ******************************************************************************
 * @brief      8. 对称密钥更新
 * @param[in]  *pbuf    : 数据输入输出缓存
 * @retval     None
 ******************************************************************************
 */
static void pfn8(const char *pin, char *pout)
{

}

/**
 ******************************************************************************
 * @brief      9. 证书更新
 * @param[in]  *pbuf    : 数据输入输出缓存
 * @retval     None
 ******************************************************************************
 */
static void pfn9(const char *pin, char *pout)
{

}

/**
 ******************************************************************************
 * @brief      10. 内部认证
 * @param[in]  *pbuf    : 数据输入输出缓存
 * @retval     None
 ******************************************************************************
 */
static void pfn10(const char *pin, char *pout)
{

}

/**
 ******************************************************************************
 * @brief      11. 外部认证
 * @param[in]  *pbuf    : 数据输入输出缓存
 * @retval     None
 ******************************************************************************
 */
static void pfn11(const char *pin, char *pout)
{

}

/**
 ******************************************************************************
 * @brief      12. 证书切换状态
 * @param[in]  *pbuf    : 数据输入输出缓存
 * @retval     None
 ******************************************************************************
 */
static void pfn12(const char *pin, char *pout)
{

}

/**
 ******************************************************************************
 * @brief      13. 置离线计数器
 * @param[in]  *pbuf    : 数据输入输出缓存
 * @retval     None
 ******************************************************************************
 */
static void pfn13(const char *pin, char *pout)
{

}

/**
 ******************************************************************************
 * @brief      14. 转加密授权
 * @param[in]  *pbuf    : 数据输入输出缓存
 * @retval     None
 ******************************************************************************
 */
static void pfn14(const char *pin, char *pout)
{

}

/**
 ******************************************************************************
 * @brief      15. 获取电表密钥密文
 * @param[in]  *pbuf    : 数据输入输出缓存
 * @retval     None
 ******************************************************************************
 */
static void pfn15(const char *pin, char *pout)
{

}

/**
 ******************************************************************************
 * @brief      16. 组对时任务包
 * @param[in]  *pbuf    : 数据输入输出缓存
 * @retval     None
 ******************************************************************************
 */
static void pfn16(const char *pin, char *pout)
{

}

/**
 ******************************************************************************
 * @brief      17. 组广播
 * @param[in]  *pbuf    : 数据输入输出缓存
 * @retval     None
 ******************************************************************************
 */
static void pfn17(const char *pin, char *pout)
{

}


int main(int argc, char **argv)
{
    if (0 != log_init(DEFAULT_LOG_FILE_NAME))
    {
        printf("日志模块初始化失败!\n");
        return -1;
    }
    if (0 == MS_OpenPort())
    {
        log_print("打开读卡器端口成功!\n");
    }
    else
    {
        log_print("打开读卡器端口失败!\n");
        log_exit();
        return -1;
    }



    if (0 == MS_ClosePort())
    {
        log_print("关闭读卡器端口成功!\n");
    }
    else
    {
        log_print("关闭读卡器端口失败!\n");
    }
    log_exit();

    return 0;
}

/*----------------------------MStationServer.c--------------------------------*/
