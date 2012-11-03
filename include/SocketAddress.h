#ifndef __SOCKET_ADDRESS_H__
#define __SOCKET_ADDRESS_H__

typedef struct _SocketAddress     SocketAddress;
typedef struct _SocketAddressPair SocketAddressPair;

#include "Socket.h"

// size=15 xxx.xxx.xxx.xxx
// size=39 yyyy:yyyy:yyyy:yyyy:yyyy:yyyy:yyyy:yyyy
#define SOCKET_ADDRESS_LEN  39+1
#define SOCKET_HOSTNAME_LEN 1024+1

// size=5 65536
#define SOCKET_PORT_LEN     5+1
#define SOCKET_SERVICE_LEN  32+1

typedef struct _SocketAddress {
    char address[SOCKET_ADDRESS_LEN];
    char hostname[SOCKET_HOSTNAME_LEN];
    char port[SOCKET_PORT_LEN];
    char service[SOCKET_SERVICE_LEN];
} SocketAddress;

typedef struct _SocketAddressPair {
    Socket        *socket;
    SocketAddress *local;
    SocketAddress *remote;
} SocketAddressPair;

SocketAddressPair *socket_address_pair_new(Socket *socket);
void socket_address_pair_free(SocketAddressPair *this);

#endif
