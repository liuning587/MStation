/**
 ******************************************************************************
 * @file      main.c
 * @brief     C Source file of main.c.
 * @details   This file including all API functions's 
 *            implement of main.c.	
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
#include "socket.h"
#include "config.h"

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


/*-----------------------------------------------------------------------------
 Section: Global Function Prototypes
 ----------------------------------------------------------------------------*/
/* NONE */

/*-----------------------------------------------------------------------------
 Section: Function Definitions
 ----------------------------------------------------------------------------*/
/**
 ******************************************************************************
 * @brief   套接字线程
 * @param[in]  msgsock  :
 *
 * @return  None
 ******************************************************************************
 */
void thread_socket(SOCKET msgsock)
{
    char buf[16] = {0};

    if (0 < socket_recv(msgsock, buf, sizeof(buf)))
    {
        printf("接收到数据");
    }
    printf("thread_socket");
    //recv();
    //send();
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
        msgsock = accept(socket, (struct sockaddr*)&tcpaddr, &len);
        printf("accept\n");
        hThread = _beginthreadex(NULL,0,(LPTHREAD_START_ROUTINE)&thread_socket,
                (LPVOID)msgsock,0,&hThreadId);
        WaitForSingleObject(hThread, INFINITE );
    }
    CloseHandle(hThread);
    socket_close(socket);

    return 0;
}

/*----------------------------main.c--------------------------------*/
