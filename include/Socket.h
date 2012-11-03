#ifndef __SOCKET_H__
#define __SOCKET_H__

typedef struct _Socket Socket;

#include <sys/socket.h>
#include "SocketAddress.h"

#define SOCKET_IPV4 AF_INET
#define SOCKET_IPV6 AF_INET6

typedef struct _Socket {
    u_int16_t      family;
    int            connfd;

    SocketAddressPair *addressPair;
} Socket;


Socket *socket_new(u_int16_t family);
int socket_connect(Socket *this, const char *host, const char *port);
int socket_close(Socket *this);
SocketAddress *socket_get_local_address(Socket *this);
SocketAddress *socket_get_remote_address(Socket *this);
int socket_free(Socket *this);

#endif
