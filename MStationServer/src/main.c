/**
 ******************************************************************************
 * @file      main.c
 * @brief     C Source file of main.c.
 * @details   �ͻ����������ͨѶЭ��
 *            �ͻ��˷���: 'G' 'E' 'T' + funID(1�ֽ�) + ����(4�ֽ�) + �����б�
 *            ����˷���: 'P' 'U' 'T' + funID(1�ֽ�) + ����(4�ֽ�) + tesam��������ֵ(4�ֽ�) + ���ܻ���������
 *
 * @copyright Copyrigth(C), 2008-2012,Sanxing Electric Co.,Ltd.
 ******************************************************************************
 */
 
/*-----------------------------------------------------------------------------
 Section: Includes
 ----------------------------------------------------------------------------*/
#include <stdio.h>
#include <winsock.h>
#include "ini.h"
#include "log.h"
#include "socket.h"
#include "config.h"
#include "MStationServer.h"

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
/* NONE */

/*-----------------------------------------------------------------------------
 Section: Local Function Prototypes
 ----------------------------------------------------------------------------*/
static char inbuf[5 * 1024];
static char outbuf[5 * 1024];

/*-----------------------------------------------------------------------------
 Section: Global Function Prototypes
 ----------------------------------------------------------------------------*/
/* NONE */

/*-----------------------------------------------------------------------------
 Section: Function Definitions
 ----------------------------------------------------------------------------*/
/**
 ******************************************************************************
 * @brief   �׽����߳�
 * @param[in]  msgsock  :
 *
 * @return  None
 ******************************************************************************
 */
void thread_socket(SOCKET msgsock)
{
    head_t head;
    int recvlen = 0;
    int pos = 0;

    memset(&head, 0x00, sizeof(head_t));
    if (socket_recv(msgsock, (char*)&head, sizeof(head_t)) != sizeof(head_t))
    {
        printf("��������ͷ����!\n");
        return ;
    }
    if ((memcmp(head.str, "GET", 3) != 0)
            || (head.pfn[0] < 1) || (head.pfn[0] > 17)
            || (head.len > (sizeof(inbuf) - sizeof(int))))
    {
        printf("����ͷ��У�����\n");
        return;
    }

    //todo ��ȡ�ź���
    memcpy(inbuf, &head.len, sizeof(int));
    pos += sizeof(int);

    if (socket_recv(msgsock, inbuf + pos, head.len) == head.len)
    {
        memset(outbuf, 0x00, sizeof(outbuf));
        do_mstation(head.pfn[0], inbuf, outbuf + 4);
        outbuf[0] = 'P';
        outbuf[1] = 'U';
        outbuf[2] = 'T';
        outbuf[3] = head.pfn[0];
        memcpy(&recvlen, outbuf + 4, sizeof(int));
        recvlen += sizeof(head_t);

        if (recvlen != socket_send(msgsock, outbuf, recvlen))
        {
            printf("���������ݳ���\n");
        }
    }
    else
    {
        printf("�������ݴ���!\n");
    }
}


int main(int argc, char **argv)
{
    char serverip[16] = {0};
    unsigned short port = 0u;
    char logflag = 0;
    unsigned int socket = 0u;

    (void)ini_get_server_ip(serverip);
    (void)ini_get_server_port(&port);
    (void)ini_get_log_flag(&logflag);

    socket = socket_server_init(serverip, port);
    if (socket < 0)
    {
        printf("socket_server_init error!\n");
        return -1;
    }
    if (0 > listen(socket, DEFAULT_SOCKET_MAX))
    {
        printf("listen error!\n");
        return -1;
    }

    struct sockaddr tcpaddr;
    int len = sizeof(struct sockaddr);
    SOCKET msgsock;
    HANDLE hThread;
    unsigned hThreadId;
    while (1)
    {
        printf("start accept\n");
        fflush(stdout);
        msgsock = accept(socket, (struct sockaddr*)&tcpaddr, &len);//��ÿͻ��˵�ip�Ͷ˿�

//        printf("accept\n");
//        hThread = _beginthreadex(NULL,0,(LPTHREAD_START_ROUTINE)&thread_socket,
//                (LPVOID)msgsock,0,&hThreadId);
//        WaitForSingleObject(hThread, INFINITE );
        thread_socket(msgsock);
        //�ر��׽���
        closesocket(msgsock);
    }
    CloseHandle(hThread);
    socket_close(socket);

    return 0;
}

/*----------------------------main.c--------------------------------*/
