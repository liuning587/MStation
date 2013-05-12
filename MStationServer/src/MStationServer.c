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
    int *outret = (int*)(pout + sizeof(int));
    char *pos = (char*)pin + sizeof(int);
    char *ESAMNo, *state, *VersionNum, *SessionID, *R1, *message1;
    const char *pfname = "3. 会话初始化/恢复";

    ESAMNo = pos ;  //ESAM序列号; 8字节 
    pos += strlen(pos) + 1;
    state = pos;    //证书状态标识; 1字节, 00--测试证书, 01--正式证书
    pos += strlen(pos) + 1;
    VersionNum = pos;   //版本号; 1字节,固定“01” 
    pos += strlen(pos) + 1;
    SessionID = pos;    //会话ID; 1字节, 00-- 新建注册, 01--恢复 
    pos += strlen(pos) + 1;
    R1 = pos;   //随机数1; 16字节
    pos += strlen(pos) + 1;
    if ((pos - pin - sizeof(int)) != *inlen)
    {
        log_print("%s[长度不匹配]", pfname);
    }

    message1 = pout + 2 * sizeof(int);  //报文1; N字节(大于1K,小于2K) 
    message1[0] = '\0';

    ret = SessionInitRec(ESAMNo, state, VersionNum, SessionID, R1, message1);
    *outret = ret;
    *outlen = sizeof(ret);

    switch (ret)
    {
        case 0:
            *outlen += strlen(message1) + 1;
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
    int *outret = (int*)(pout + sizeof(int));
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
    message3 = pout + 2 * sizeof(int);
    message3 = '\0';
    ret = SessionKeyConsult(ESAMNo, state, message2, message3);
    *outret = ret;
    *outlen = sizeof(ret);

    switch (ret)
    {
        case 0:
            *outlen += strlen(message3) + 1;
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
    int *outret = (int*)(pout + sizeof(int));
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
    *outret = ret;
    *outlen = sizeof(ret);

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
    int *outret = (int*)(pout + sizeof(int));
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
    *outret = ret;
    *outlen = sizeof(ret);

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
    int ret = 0;
    int *inlen = (int*)pin;
    int *outlen = (int*)pout;
    int *outret = (int*)(pout + sizeof(int));
    char *pos = (char*)pin + sizeof(int);
    int keyID = 0;
    char *state, *ESAMNo, *indata, *MAC;
    const char *pfname = "7. MAC校验";

    state = pos;
    pos += strlen(pos) + 1;
    memcpy(&keyID, pos, sizeof(keyID));
    pos += sizeof(keyID);
    ESAMNo = pos;
    pos += strlen(pos) + 1;
    indata = pos;
    pos += strlen(pos) + 1;
    if ((pos - pin - sizeof(int)) != *inlen)
    {
        log_print("%s[长度不匹配]", pfname);
    }
    MAC = pout + 2 * sizeof(int);
    ret = MACVerify(state, keyID, ESAMNo, indata, MAC);

    *outret = ret;
    *outlen = sizeof(ret);

    switch (ret)
    {
        case 0:
            log_print("%s[成功]", pfname);
            break;
        case 1001:
            log_print("%s[密钥索引错误]", pfname);
            break;
        case 1002:
            log_print("%s[ESAM序列号错误]", pfname);
            break;
        case 1003:
            log_print("%s[源数据错误]", pfname);
            break;
        default:
            log_print("%s[未知错误]", pfname);
            break;
    }
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
    int ret = 0;
    int *inlen = (int*)pin;
    int *outlen = (int*)pout;
    int *outret = (int*)(pout + sizeof(int));
    char *pos = (char*)pin + sizeof(int);
    int keynum = 0;
    char *state, *keyIDlist, *ESAMNo, *keycipherdata;
    const char *pfname = "8. 对称密钥更新";

    state = pos;
    pos += strlen(pos) + 1;
    memcpy(&keynum, pos, sizeof(keynum));
    pos += sizeof(keynum);
    keyIDlist = pos;
    pos += strlen(pos) + 1;
    ESAMNo = pos;
    pos += strlen(pos) + 1;
    if ((pos - pin - sizeof(int)) != *inlen)
    {
        log_print("%s[长度不匹配]", pfname);
    }
    keycipherdata = pout + 2 * sizeof(int);

    ret = SymmetricKeyUpdate(state, keynum, keyIDlist, ESAMNo, keycipherdata);
    *outret = ret;
    *outlen = sizeof(ret);
    switch (ret)
    {
        case 0:
            log_print("%s[成功]", pfname);
            break;
        case 1001:
            log_print("%s[密钥状态错误]", pfname);
            break;
        case 1002:
            log_print("%s[密钥条数错误]", pfname);
            break;
        case 1003:
            log_print("%s[密钥列表错误]", pfname);
            break;
        case 1004:
            log_print("%s[ESAM序列号错误]", pfname);
            break;
        default:
            log_print("%s[未知错误]", pfname);
            break;
    }
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
    int ret = 0;
    int *inlen = (int*)pin;
    int *outlen = (int*)pout;
    int *outret = (int*)(pout + sizeof(int));
    char *pos = (char*)pin + sizeof(int);

    char *state, *CerType, *strserial_Number_Terminal;
    char *Term_PK, *CACertificateCipherData;
    const char *pfname = "9. 证书更新";

    state = pos;
    pos += strlen(pos) + 1;
    CerType = pos;
    pos += strlen(pos) + 1;
    strserial_Number_Terminal = pos;
    pos += strlen(pos) + 1;
    Term_PK = pos;
    pos += strlen(pos) + 1;

    if ((pos - pin - sizeof(int)) != *inlen)
    {
        log_print("%s[长度不匹配]", pfname);
    }
    CACertificateCipherData = pout + 2 * sizeof(int);

    ret = CACertificateUpdate(state, CerType, strserial_Number_Terminal,
            Term_PK, CACertificateCipherData);

    *outret = ret;
    *outlen = sizeof(ret);
    switch (ret)
    {
        case 0:
            //todo
            log_print("%s[成功]", pfname);
            break;
        case 1001:
            log_print("%s[终端公钥错误]", pfname);
            break;
        case 1002:
            log_print("%s[终端证书序列号错误]", pfname);
            break;
        default:
            log_print("%s[未知错误]", pfname);
            break;
    }
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
    int ret = 0;
    int *inlen = (int*)pin;
    int *outlen = (int*)pout;
    int *outret = (int*)(pout + sizeof(int));
    char *pos = (char*)pin + sizeof(int);
    char *R4;
    const char *pfname = "10. 内部认证";

    R4 = pos;
    pos += strlen(pos) + 1;

    if ((pos - pin - sizeof(int)) != *inlen)
    {
        log_print("%s[长度不匹配]", pfname);
    }
    ret = InternalAuth(R4);
    *outret = ret;
    *outlen = sizeof(ret);
    switch (ret)
    {
        case 0:
            log_print("%s[成功]", pfname);
            break;
        case 1:
            log_print("%s[错误]", pfname);
            break;
        default:
            log_print("%s[未知错误]", pfname);
            break;
    }
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
    int ret = 0;
    int *inlen = (int*)pin;
    int *outlen = (int*)pout;
    int *outret = (int*)(pout + sizeof(int));
    char *pos = (char*)pin + sizeof(int);
    char *state, *ESAMNo, *ER4, *R5, *ER5;
    const char *pfname = "11. 外部认证";

    state = pos;
    pos += strlen(pos) + 1;
    ESAMNo = pos;
    pos += strlen(pos) + 1;
    ER4 = pos;
    pos += strlen(pos) + 1;
    ER4 = pos;
    pos += strlen(pos) + 1;
    R5 = pos;
    pos += strlen(pos) + 1;

    if ((pos - pin - sizeof(int)) != *inlen)
    {
        log_print("%s[长度不匹配]", pfname);
    }

    ER5 = pout + 2 * sizeof(int);

    ret = ExternalAuth(state, ESAMNo, ER4, R5, ER5);
    *outret = ret;
    *outlen = sizeof(ret);
    switch (ret)
    {
        case 0:
            log_print("%s[成功]", pfname);
            break;
        case 1001:
            log_print("%s[密钥状态标识错误]", pfname);
            break;
        case 1002:
            log_print("%s[ESAM序列号错误]", pfname);
            break;
        case 1003:
            log_print("%s[随机数4密文错误]", pfname);
            break;
        case 1004:
            log_print("%s[随机数5错误]", pfname);
            break;
        default:
            log_print("%s[未知错误]", pfname);
            break;
    }
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
    int ret = 0;
    int *inlen = (int*)pin;
    int *outlen = (int*)pout;
    int *outret = (int*)(pout + sizeof(int));
    char *pos = (char*)pin + sizeof(int);
    char *state, *cerstate, *ESAMNo, *R6, *StateER6MAC6;
    const char *pfname = "12. 证书切换状态";

    state = pos;
    pos += strlen(pos) + 1;
    cerstate = pos;
    pos += strlen(pos) + 1;
    ESAMNo = pos;
    pos += strlen(pos) + 1;
    R6 = pos;
    pos += strlen(pos) + 1;

    if ((pos - pin - sizeof(int)) != *inlen)
    {
        log_print("%s[长度不匹配]", pfname);
    }

    StateER6MAC6 = pout + 2 * sizeof(int);

    ret = CertificateStateChange(state, cerstate, ESAMNo, R6, StateER6MAC6);
    *outret = ret;
    *outlen = sizeof(ret);
    switch (ret)
    {
        case 0:
            log_print("%s[成功]", pfname);
            break;
        case 1001:
            log_print("%s[密钥状态标识错误]", pfname);
            break;
        case 1002:
            log_print("%s[证书切换状态错误]", pfname);
            break;
        case 1003:
            log_print("%s[ESAM序列号错误 ]", pfname);
            break;
        case 1004:
            log_print("%s[随机数6错误]", pfname);
            break;
        default:
            log_print("%s[未知错误]", pfname);
            break;
    }
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
    int ret = 0;
    int *inlen = (int*)pin;
    int *outlen = (int*)pout;
    int *outret = (int*)(pout + sizeof(int));
    char *pos = (char*)pin + sizeof(int);
    char *state, *ESAMNo, *Counter, *EnCounter;
    const char *pfname = "13. 置离线计数器";

    state = pos;
    pos += strlen(pos) + 1;
    ESAMNo = pos;
    pos += strlen(pos) + 1;
    Counter = pos;
    pos += strlen(pos) + 1;

    if ((pos - pin - sizeof(int)) != *inlen)
    {
        log_print("%s[长度不匹配]", pfname);
    }

    EnCounter = pout + 2 * sizeof(int);

    ret = SetOfflineCounter(state, ESAMNo, Counter, EnCounter);
    *outret = ret;
    *outlen = sizeof(ret);
    switch (ret)
    {
        case 0:
            log_print("%s[成功]", pfname);
            break;
        case 1001:
            log_print("%s[密钥状态标识错误]", pfname);
            break;
        case 1002:
            log_print("%s[ESAM序列号错误]", pfname);
            break;
        case 1003:
            log_print("%s[离线计数器数量错误]", pfname);
            break;
        default:
            log_print("%s[未知错误]", pfname);
            break;
    }
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
    int ret = 0;
    int *inlen = (int*)pin;
    int *outlen = (int*)pout;
    int *outret = (int*)(pout + sizeof(int));
    char *pos = (char*)pin + sizeof(int);
    char *indata, *ChangeDataMAC;
    const char *pfname = "14. 转加密授权";

    indata = pos;
    pos += strlen(pos) + 1;
    if ((pos - pin - sizeof(int)) != *inlen)
    {
        log_print("%s[长度不匹配]", pfname);
    }
    ChangeDataMAC = pout + 2 * sizeof(int);

    ret = ChangeDataAuthorize(indata, ChangeDataMAC);
    *outret = ret;
    *outlen = sizeof(ret);
    switch (ret)
    {
        case 0:
            log_print("%s[成功]", pfname);
            break;
        case 1001:
            log_print("%s[转加密授权数据错误]", pfname);
            break;
        default:
            log_print("%s[未知错误]", pfname);
            break;
    }
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
    int ret = 0;
    int *inlen = (int*)pin;
    int *outlen = (int*)pout;
    int *outret = (int*)(pout + sizeof(int));
    char *pos = (char*)pin + sizeof(int);
    int meterkeystate;
    char *meterNo;
    int tasktype;
    char *MeterKeyTaskData;
    const char *pfname = "15. 获取电表密钥密文";

    memcpy(&meterkeystate, pos, sizeof(int));
    pos += sizeof(int);
    meterNo = pos;
    pos += strlen(pos) + 1;
    memcpy(&tasktype, pos, sizeof(int));
    pos += sizeof(int);
    if ((pos - pin - sizeof(int)) != *inlen)
    {
        log_print("%s[长度不匹配]", pfname);
    }
    MeterKeyTaskData = pout + 2 * sizeof(int);

    ret = GetCipherMeterKey(meterkeystate, meterNo, tasktype,
            MeterKeyTaskData);
    *outret = ret;
    *outlen = sizeof(ret);
    switch (ret)
    {
        case 0:
            log_print("%s[成功]", pfname);
            break;
        case 1001:
            log_print("%s[表号分散因子错误]", pfname);
            break;
        case 1002:
            log_print("%s[电表密钥状态错误]", pfname);
            break;
        case 1003:
            log_print("%s[任务类型错误]", pfname);
            break;
        default:
            log_print("%s[未知错误]", pfname);
            break;
    }
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
    int ret = 0;
    int *inlen = (int*)pin;
    int *outlen = (int*)pout;
    int *outret = (int*)(pout + sizeof(int));
    char *pos = (char*)pin + sizeof(int);
    int indataflag;
    char *taskV;
    char *taskdata;
    const char *pfname = "16. 组对时任务包";

    memcpy(&indataflag, pos, sizeof(int));
    pos += sizeof(int);
    taskV = pos;
    pos += strlen(pos) + 1;
    if ((pos - pin - sizeof(int)) != *inlen)
    {
        log_print("%s[长度不匹配]", pfname);
    }
    taskdata = pout + 2 * sizeof(int);

    ret = GenerateTimeTask(indataflag, taskV, taskdata);
    *outret = ret;
    *outlen = sizeof(ret);
    switch (ret)
    {
        case 0:
            log_print("%s[成功]", pfname);
            break;
        case 1001:
            log_print("%s[数据类型错误 ]", pfname);
            break;
        case 1002:
            log_print("%s[任务数据错误]", pfname);
            break;
        default:
            log_print("%s[未知错误]", pfname);
            break;
    }
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
    int ret = 0;
    int *inlen = (int*)pin;
    int *outlen = (int*)pout;
    int *outret = (int*)(pout + sizeof(int));
    char *pos = (char*)pin + sizeof(int);
    char *state, *ESAMKID, *ESAMNo;
    int Datatype;
    char *GroupNo, *MTime, *Data, *BroadData;
    const char *pfname = "17. 组广播";

    state = pos;
    pos += strlen(pos) + 1;
    ESAMKID = pos;
    pos += strlen(pos) + 1;
    ESAMNo = pos;
    pos += strlen(pos) + 1;
    memcpy(&Datatype, pos, sizeof(int));
    pos += sizeof(int);
    GroupNo = pos;
    pos += strlen(pos) + 1;
    MTime = pos;
    pos += strlen(pos) + 1;
    Data = pos;
    pos += strlen(pos) + 1;
    if ((pos - pin - sizeof(int)) != *inlen)
    {
        log_print("%s[长度不匹配]", pfname);
    }
    BroadData = pout + 2 * sizeof(int);

    ret = GroupBroadcast(state, ESAMKID, ESAMNo, Datatype, GroupNo,
            MTime, Data, BroadData);
    *outret = ret;
    *outlen = sizeof(ret);
    switch (ret)
    {
        case 0:
            log_print("%s[成功]", pfname);
            break;
        case 1001:
            log_print("%s[密钥状态错误]", pfname);
            break;
        case 1002:
            log_print("%s[广播密钥组号错误]", pfname);
            break;
        case 1003:
            log_print("%s[ESAM 序列号错误]", pfname);
            break;
        case 1004:
            log_print("%s[组地址错误]", pfname);
            break;
        case 1005:
            log_print("%s[主站时间错误]", pfname);
            break;
        case 1006:
            log_print("%s[广播数据错误]", pfname);
            break;
        default:
            log_print("%s[未知错误]", pfname);
            break;
    }
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
