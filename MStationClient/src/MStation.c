/**
 ******************************************************************************
 * @file      MStation.c
 * @brief     C Source file of MStation.c.
 * @details   客户端与服务器通讯协议
 *            客户端发送: 'G' 'E' 'T' + funID(1字节) + 长度(4字节) + 参数列表
 *            服务端发送: 'P' 'U' 'T' + funID(1字节) + 长度(4字节) + tesam操作返回值(4字节) + 加密机返回数据
 *
 *
 * @copyright Copyrigth(C), 2008-2012,Sanxing Electric Co.,Ltd.
 ******************************************************************************
 */
 
/*-----------------------------------------------------------------------------
 Section: Includes
 ----------------------------------------------------------------------------*/
#include <string.h>
#include "log.h"
#include "ini.h"
#include "socket.h"
#include "MStation.h"


/*-----------------------------------------------------------------------------
 Section: Type Definitions
 ----------------------------------------------------------------------------*/
typedef struct
{
    char str[3];
    char pfn[1];
    int len;
} head_t;


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
static char serverip[16] = {0};
static unsigned short port = 0u;
static char logflag = 0;
static const char the_head[] = {'G', 'E', 'T'};
static char inbuf[5 * 1024];
static char outbuf[5 * 1024];

/*-----------------------------------------------------------------------------
 Section: Local Function Prototypes
 ----------------------------------------------------------------------------*/
/* NONE */

/*-----------------------------------------------------------------------------
 Section: Function Definitions
 ----------------------------------------------------------------------------*/
static unsigned int
connect_start(void)
{
    (void)ini_get_server_ip(serverip);
    (void)ini_get_server_port(&port);
    (void)ini_get_log_flag(&logflag);

    (void)log_init();
    log_on(logflag);
    return socket_init(serverip, port);
}

static void
connect_close(unsigned int socketfd)
{
    socket_close(socketfd);
    log_exit();
}
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
    unsigned int socketfd = 0;
    char buf[16] = {0};
    int pos = 0;
    int sendlen = 0;
    int recvlen = 0;
    int ret = 1;

    if ((socketfd = connect_start()) == 0)
    {
        log_exit();
        return 1;
    }
    memcpy(buf, the_head, 3);   //3字节GET
    pos += 3;
    buf[pos] = 1;
    pos += 1;
    memcpy(buf + pos, &sendlen, sizeof(int));
    pos += sizeof(int);

    do
    {
        if ((sendlen + 8) != socket_send(socketfd, buf, sendlen + 8))
        {
            log_print("%s发送数据数据出错\n", __FUNCTION__);
            break;
        }
        memset(buf, 0x00, sizeof(buf));
        recvlen = socket_recv(socketfd, buf, 12); //len = 8 + 4
        if ((recvlen == -1) || (recvlen != 12))
        {
            log_print("%s接收数据出错[recvlen:%d]\n", __FUNCTION__, recvlen);
            break;
        }
        pos = 0;
        if ((memcmp(buf, "PUT", 3) != 0) || (buf[3] != 1))
        {
            log_print("%s 头不合法\n", __FUNCTION__);
            break;
        }
        pos += 4;
        memcpy(&recvlen, buf + pos, sizeof(int));
        if (recvlen != sizeof(int))
        {
            log_print("%s 长度不合法\n", __FUNCTION__);
            break;
        }
        pos += 4;
        memcpy(&ret, buf + pos, sizeof(int));
        ret = (ret == 0) ? ret : 1;
    } while(0);
    connect_close(socketfd);

    return ret;
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
    unsigned int socketfd = 0;
    char buf[16] = {0};
    int pos = 0;
    int sendlen = 0;
    int recvlen = 0;
    int ret = 1;

    if ((socketfd = connect_start()) == 0)
    {
        return 1;
    }
    memcpy(buf, the_head, 3);   //3字节GET
    pos += 3;
    buf[pos] = 2;
    pos += 1;
    memcpy(buf + pos, &sendlen, sizeof(int));
    pos += sizeof(int);

    do
    {
        if ((sendlen + 8) != socket_send(socketfd, buf, sendlen + 8))
        {
            break;
        }
        memset(buf, 0x00, sizeof(buf));
        recvlen = socket_recv(socketfd, buf, 12); //len = 8 + 4
        if ((recvlen == -1) || (recvlen != 12))
        {
            log_print("%s接收数据出错[recvlen:%d]\n", __FUNCTION__, recvlen);
            break;
        }
        pos = 0;
        if ((memcmp(buf, "PUT", 3) != 0) || (buf[3] != 2))
        {
            break;
        }
        pos += 4;
        memcpy(&recvlen, buf + pos, sizeof(int));
        if (recvlen != sizeof(int))
        {
            break;
        }
        pos += 4;
        memcpy(&ret, buf + pos, sizeof(int));
        ret = (ret == 0) ? ret : 1;
    } while(0);
    connect_close(socketfd);

    return ret;
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
    unsigned int socket = 0;
    char *buf = inbuf;
    int pos = 0;
    int sendlen = 0;
    int recvlen = 0;
    int ret = 1001;
    head_t *head = (head_t *)inbuf;

    if (strlen(ESAMNo) != 8 * 2)
    {
        return 1001;
    }
    if (strlen(state) != 1 *2)
    {
        return 1002;
    }
    if (strcmp(VersionNum, "01") != 0)
    {
        return 1003;
    }
    if (strlen(SessionID) != 1 * 2)
    {
        return 1004;
    }
    if (strlen(R1) != 16 * 2)
    {
        return 1005;
    }

    if ((socket = connect_start()) == 0)
    {
        return 1;
    }
    memcpy(head->str, the_head, 3);   //3字节GET
    head->pfn[0] = 3;
    buf += sizeof(head_t);
    strcpy(buf, ESAMNo);
    buf += strlen(ESAMNo) + 1;
    strcpy(buf, state);
    buf += strlen(state) + 1;
    strcpy(buf, VersionNum);
    buf += strlen(VersionNum) + 1;
    strcpy(buf, SessionID);
    buf += strlen(SessionID) + 1;
    strcpy(buf, R1);
    buf += strlen(R1) + 1;

    sendlen = buf - inbuf;
    head->len = sendlen - sizeof(head_t);
    log_print("ESAMNo:%s\n", ESAMNo);
    log_print("state:%s\n", state);
    log_print("VersionNum:%s\n", VersionNum);
    log_print("SessionID:%s\n", SessionID);
    log_print("R1:%s\n", R1);

    do
    {
        if (sendlen != socket_send(socket, inbuf, sendlen))
        {
            log_print("%s发送数据出错\n", __FUNCTION__);
            break;
        }
        memset(buf, 0x00, sizeof(buf));
        recvlen = socket_recv(socket, buf, 12); //len = 8 + 4
        if ((recvlen == -1) || (recvlen != 12))
        {
            log_print("%s接收数据出错[recvlen:%d]\n", __FUNCTION__, recvlen);
            break;
        }
        pos = 0;
        if ((memcmp(buf, "PUT", 3) != 0) || (buf[3] != 3))
        {
            log_print("%s头校验错误!\n", __FUNCTION__);
            break;
        }
        pos += 4;
        memcpy(&recvlen, buf + pos, sizeof(int));
        pos += 4;
        memcpy(&ret, buf + pos, sizeof(int));
        memset(outbuf, 0x00, sizeof(outbuf));
        if (socket_recv(socket, outbuf, recvlen - 4) != recvlen - 4)
        {
            log_print("%s接收数据错误!\n", __FUNCTION__);
            break;
        }
        if (ret == 0)   //成功则读取数据
        {
            log_print("message1:%s\n", message1);
            strncpy(message1, outbuf, 1024 * 2 * 2);
        }
    } while(0);
    connect_close(socket);

    return ret;
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
