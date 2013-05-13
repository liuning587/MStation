/**
 ******************************************************************************
 * @file       socket.h
 * @brief      API include file of socket.h.
 * @details    This file including all API functions's declare of socket.h.
 * @copyright  Copyrigth(C), 2008-2012,Sanxing Electric Co.,Ltd.
 *
 ******************************************************************************
 */
#ifndef SOCKET_H_
#define SOCKET_H_ 

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
/* NONE */

/*-----------------------------------------------------------------------------
 Section: Globals
 ----------------------------------------------------------------------------*/
/* NONE */

/*-----------------------------------------------------------------------------
 Section: Function Prototypes
 ----------------------------------------------------------------------------*/
extern unsigned int socket_init(const char *pHostName, unsigned short port);
extern int socket_send(unsigned int socket, const char *pbuf, int size);
extern int socket_recv(unsigned int socket, char *pbuf, int size);
extern void socket_close(unsigned int socket);


#endif /* SOCKET_H_ */
/*--------------------------End of socket.h-----------------------------*/
