/**
 ******************************************************************************
 * @file      MStation.c
 * @brief     C Source file of MStation.c.
 * @details   This file including all API functions's 
 *            implement of MStation.c.	
 *
 * @copyright Copyrigth(C), 2008-2012,Sanxing Electric Co.,Ltd.
 ******************************************************************************
 */
 
/*-----------------------------------------------------------------------------
 Section: Includes
 ----------------------------------------------------------------------------*/
#include "MStation.h"

/*-----------------------------------------------------------------------------
 Section: Type Definitions
 ----------------------------------------------------------------------------*/
/* NONE */

/*-----------------------------------------------------------------------------
 Section: Constant Definitions
 ----------------------------------------------------------------------------*/
/* NONE */ 

/*-----------------------------------------------------------------------------
 Section: Global Variables
 ----------------------------------------------------------------------------*/
/* NONE */

/*-----------------------------------------------------------------------------
 Section: Local Variables
 ----------------------------------------------------------------------------*/
/* NONE */

/*-----------------------------------------------------------------------------
 Section: Local Function Prototypes
 ----------------------------------------------------------------------------*/
/* NONE */

/*-----------------------------------------------------------------------------
 Section: Function Definitions
 ----------------------------------------------------------------------------*/
/**
 ******************************************************************************
 * @brief      1. 打开读卡器
 * @param[in]  None
 * @param[out] None
 *
 * @retval     0 : 打开读卡器端口成功
 * @retval     1 : 打开读卡器端口失败
 ******************************************************************************
 */
extern int
MS_OpenPort()
{

}

/**
 ******************************************************************************
 * @brief      2. 关闭读卡器
 * @param[in]  None
 * @param[out] None
 *
 * @retval     0 : 关闭读卡器端口成功
 * @retval     1 : 关闭读卡器端口失败
 ******************************************************************************
 */
extern int
MS_ClosePort()
{

}

/**
 ******************************************************************************
 * @brief      3. 会话初始化/恢复
 * @param[in]  ESAMNo       : ESAM序列号; 8字节 
 * @param[in]  state        : 证书状态标识; 1字节, 00--测试证书, 01--正式证书
 * @param[in]  VersionNum   : 版本号; 1字节,固定“01” 
 * @param[in]  SessionID    : 会话ID; 1字节, 00-- 新建注册, 01--恢复 
 * @param[in]  R1           : 随机数1; 16字节 
 * @param[out] message1     : 报文1; N字节(大于1K,小于2K) 
 *
 * @retval        0 : 正常返回
 * @retval     1001 : ESAM序列号错误
 * @retval     1002 : 证书状态标识错误
 * @retval     1003 : 版本号错误
 * @retval     1004 : 会话ID错误
 * @retval     1005 : 随机数错误
 ******************************************************************************
 */
extern int
SessionInitRec(char *ESAMNo, char *state, char *VersionNum,
        char *SessionID, char *R1, char *message1)
{

}

/**
 ******************************************************************************
 * @brief      4. 会话密钥协商
 * @param[in]  ESAMNo       : ESAM序列号; 8字节 
 * @param[in]  state        : 证书状态标识; 1字节, 00--测试证书, 01--正式证书
 * @param[in]  message2     : 报文2; N字节(小于2K) 
 * @param[out] message3     : 报文3; N字节(小于2K) 
 *
 * @retval        0 : 正常返回
 * @retval     1001 : ESAM序列号错误
 * @retval     1002 : 证书状态标识错误
 * @retval     1003 : 报文2错误
 ******************************************************************************
 */
extern int
SessionKeyConsult(char *ESAMNo, char *state, char *message2, char *message3)
{

}

/**
 ******************************************************************************
 * @brief      5. 会话协商验证
 * @param[in]  message4     : 报文4; 20字节
 * @param[out] None
 *
 * @retval        0 : 验证成功
 * @retval     1001 : 报文4错误
 ******************************************************************************
 */
extern int
SessionConsultVerify(char *message4)
{

}

/**
 ******************************************************************************
 * @brief      6. 会话恢复验证
 * @param[in]  ESAMNo       : ESAM序列号; 8字节 
 * @param[in]  message2     : 报文2; 38字节
 * @param[out] None
 *
 * @retval        0 : 验证成功
 * @retval     1001 : ESAM序列号错误
 * @retval     1002 : 报文2错误
 ******************************************************************************
 */
extern int
SessionRecoveryVerify(char *ESAMNo, char *message2)
{

}

/**
 ******************************************************************************
 * @brief      7. MAC校验
 * @param[in]  state    : 对称密钥状态标识; 1字节; 00--第一套密钥, 01--第二套密钥
 * @param[in]  keyID    : 密钥索引; 0x20 <= keyID值 <= 0x33
 * @param[in]  ESAMNo   : ESAM序列号; 8字节 
 * @param[in]  indata   : 计算MAC的源数据
 * @param[out] MAC      : MAC校验码; 4字节
 *
 * @retval        0 : 成功
 * @retval     1001 : 密钥索引错误
 * @retval     1002 : ESAM序列号错误
 * @retval     1003 : 源数据错误
 ******************************************************************************
 */
extern int
MACVerify(char *state, int keyID, char *ESAMNo, char *indata, char *MAC)
{

}

/**
 ******************************************************************************
 * @brief      8. 对称密钥更新
 * @param[in]  state    : 对称密钥状态标识; 1字节; 00--第一套密钥, 01--第二套密钥
 * @param[in]  keynum   : 要更新的密钥条数; 不大于51
 * @param[in]  KeyIDlist: 要更新的密钥 kid 列表
 * @param[in]  ESAMNo   : ESAM序列号; 8字节 
 * @param[out] keycipherdata    :  密钥信息密文; N*32字节(N 等于Keynum)
 *  
 * @retval        0 : 成功
 * @retval     1001 : 密钥状态错误
 * @retval     1002 : 密钥条数错误
 * @retval     1003 : 密钥列表错误
 * @retval     1004 : ESAM序列号错误
 ******************************************************************************
 */
extern int
SymmetricKeyUpdate(char *state, int keynum, char *KeyIDlist,
        char *ESAMNo, char *keycipherdata)
{

}

/**
 ******************************************************************************
 * @brief      9. 证书更新
 * @param[in]  state    : 证书状态; 1字节; 00--测试状态, 01--正式状态
 * @param[in]  CerType  : 证书类别; 1字节; 00--终端证书, 01--CRL证书 
 * @param[in]  strserial_Number_Terminal    : 终端证书序列号; 16字节 
 * @param[in]  Term_PK  : 终端公钥; 64字节 
 * @param[out] CACertificateCipherData      : 证书密文信息 + MAC 
 *
 * @retval        0 : 成功
 * @retval     1001 : 终端公钥错误
 * @retval     1002 : 终端证书序列号错误
 ******************************************************************************
 */
extern int
CACertificateUpdate(char *state, char *CerType, char *strserial_Number_Terminal,
        char *Term_PK, char *CACertificateCipherData)
{

}

/**
 ******************************************************************************
 * @brief      10. 内部认证
 * @param[in]  None
 * @param[out] R4   : 随机数4; 16字节
 *
 * @retval     0 : 成功
 * @retval     1 : 错误
 ******************************************************************************
 */
extern int
InternalAuth(char *R4)
{

}

/**
 ******************************************************************************
 * @brief      11. 外部认证
 * @param[in]  state    : 对称密钥状态标识; 1字节; 00--第一套密钥, 01--第二套密钥
 * @param[in]  ESAMNo   : ESAM序列号; 8字节 
 * @param[in]  ER4      : 随机数4密文; 16字节
 * @param[in]  R5       : 随机数5; 16字节
 * @param[out] ER5      : 随机数5密文; 16字节
 *
 * @retval        0 : 成功
 * @retval     1001 : 密钥状态标识错误
 * @retval     1002 : ESAM序列号错误
 * @retval     1003 : 随机数4密文错误 
 * @retval     1004 : 随机数5错误
 ******************************************************************************
 */
extern int
ExternalAuth(char *state, char *ESAMNo, char *ER4, char *R5, char *ER5)
{

}

/**
 ******************************************************************************
 * @brief      12. 证书切换状态
 * @param[in]  state    : 对称密钥状态标识; 1字节; 00--第一套密钥, 01--第二套密钥
 * @param[in]  cerstate : 证书切换状态; 1字节; 00--测试切换到正式, 01--正式切换到测试
 * @param[in]  ESAMNo   : ESAM序列号; 8字节 
 * @param[in]  R6       : 随机数6; 16字节 
 * @param[out] StateER6MAC6 : 切换状态(1字节) + ER6(16字节) + MAC6(4字节)  
 *
 * @retval        0 : 成功
 * @retval     1001 : 密钥状态标识错误
 * @retval     1002 : 证书切换状态错误
 * @retval     1003 : ESAM序列号错误 
 * @retval     1004 : 随机数6错误
 ******************************************************************************
 */
extern int
CertificateStateChange(char *state, char *cerstate, char *ESAMNo,
        char *R6, char *StateER6MAC6)
{

}

/**
 ******************************************************************************
 * @brief      13. 置离线计数器
 * @param[in]  state    : 对称密钥状态标识; 1字节; 00--第一套密钥, 01--第二套密钥
 * @param[in]  ESAMNo   : ESAM序列号; 8字节 
 * @param[in]  Counter  : 离线计数器数量; 4字节
 * @param[out] EnCounter: 离线计数器密文(16字节) + MAC(4字节)  
 *
 * @retval        0 : 成功
 * @retval     1001 : 密钥状态标识错误
 * @retval     1002 : ESAM序列号错误 
 * @retval     1003 : 离线计数器数量错误  
 ******************************************************************************
 */
extern int
SetOfflineCounter(char *state, char *ESAMNo, char *Counter, char *EnCounter)
{

}

/**
 ******************************************************************************
 * @brief      14. 转加密授权
 * @param[in]  indata        : 随机数; 28字节; 可任取28字节数据
 * @param[out] ChangeDataMAC : 转加密授权数据(28字节) + MAC(4字节)  
 *
 * @retval        0 : 成功
 * @retval     1001 : 转加密授权数据错误
 ******************************************************************************
 */
extern int
ChangeDataAuthorize(char *indata, char *ChangeDataMAC)
{

}

/**
 ******************************************************************************
 * @brief      15. 获取电表密钥密文
 * @param[in]  meterkeystate    : 电表密钥状态; 0电表出厂密钥  1下装密钥后状态
 * @param[in]  meterNo          : 表号分散因子; 8字节;电表表号前面补充两字节00
 * @param[in]  tasktype         : 任务类型; 1字节; 0对时任务、1 身份认证任务 
 * @param[out] MeterKeyTaskData : 电表密钥密文
 *
 * @retval        0 : 成功
 * @retval     1001 : 表号分散因子错误 
 * @retval     1002 : 电表密钥状态错误 
 * @retval     1003 : 任务类型错误
 ******************************************************************************
 */
extern int
GetCipherMeterKey(int meterkeystate, char *meterNo,
        int tasktype, char *MeterKeyTaskData)
{

}

/**
 ******************************************************************************
 * @brief      16. 组对时任务包
 * @param[in]  indataflag   : 输入数据类型; 固定为4, 密文 + MAC;
 * @param[in]  taskV        : 任务数据明文; 小于 32字节;
 * @param[out] taskdata     : 任务数据密文; 小于32字节;
 *
 * @retval        0 : 成功
 * @retval     1001 : 数据类型错误 
 * @retval     1002 : 任务数据错误
 ******************************************************************************
 */
extern int
GenerateTimeTask(int indataflag, char *taskV, char *taskdata)
{

}

/**
 ******************************************************************************
 * @brief      17. 组广播
 * @param[in]  state    : 对称密钥状态标识; 1字节; 00--第一套密钥, 01--第二套密钥
 * @param[in]  ESAMKID  : 广播密钥组号; 1字节; 01-0A (10个组) 
 * @param[in]  ESAMNo   : ESAM序列号; 8字节 
 * @param[in]  Datatype ：广播数据类型; 固定为 0：明文 + MAC
 * @param[in]  GroupNo  : 组地址; 2字节
 * @param[in]  MTime    : 主站时间; 6字节; 默认130202224622 
 * @param[in]  Data     : 广播数据; N字节
 * @param[out] BroadData: 广播数据 
 *
 * @retval        0 : 成功
 * @retval     1001 : 密钥状态错误 
 * @retval     1002 : 广播密钥组号错误 
 * @retval     1003 : ESAM 序列号错误 
 * @retval     1004 : 组地址错误 
 * @retval     1005 : 主站时间错误  
 * @retval     1006 : 广播数据错误 
 ******************************************************************************
 */
extern int
GroupBroadcast(char *state, char *ESAMKID, char *ESAMNo, int Datatype,
        char *GroupNo, char *MTime, char *Data, char *BroadData)
{

}

/*-------------------------------MStation.c----------------------------------*/
