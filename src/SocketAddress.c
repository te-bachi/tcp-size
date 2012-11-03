#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#include "SocketAddress.h"

static SocketAddress *socket_address_new(struct sockaddr_storage addr, socklen_t len);

SocketAddressPair *
socket_address_pair_new(Socket *socket)
{
    SocketAddressPair *addressPair;
    struct sockaddr_storage addr;
    socklen_t len;

    addressPair = (SocketAddressPair *) malloc(sizeof(SocketAddressPair));

    addressPair->socket = socket;

    len = sizeof(addr);

    if (getsockname(socket->connfd, (struct sockaddr *) &addr, &len) == -1) {
        return NULL;
    }
    addressPair->local = socket_address_new(addr, len);

    len = sizeof(addr);
    if (getpeername(socket->connfd, (struct sockaddr *) &addr, &len) == -1) {
        return NULL;
    }
    addressPair->remote = socket_address_new(addr, len);

    return addressPair;
}

void
socket_address_pair_free(SocketAddressPair *this)
{
    if (this->local != NULL) {
        free(this->local);
    }

    if (this->remote != NULL) {
        free(this->remote);
    }
    free(this);
}

static SocketAddress *
socket_address_new(struct sockaddr_storage addr, socklen_t len)
{
    SocketAddress *address;
    int err;

    address = (SocketAddress *) malloc(sizeof(SocketAddress));

    // address and port
    err = getnameinfo((struct sockaddr *) &addr, len,
                      address->address, SOCKET_ADDRESS_LEN,
                      address->port, SOCKET_PORT_LEN,
                      NI_NUMERICHOST | NI_NUMERICSERV);
    if (err != 0) {
        fprintf(stderr, "getnameinfo: %s\n", gai_strerror(err));
    }

    // hostname and service
    err = getnameinfo((struct sockaddr *) &addr, len,
                    address->hostname, NI_MAXHOST,
                    address->service, NI_MAXSERV,
                    0);

    if (err != 0) {
        fprintf(stderr, "getnameinfo: %s\n", gai_strerror(err));
    }

    return address;
}
