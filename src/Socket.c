#include <stdio.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h> // struct sockaddr_in
#include <arpa/inet.h> // inet_pton()
#include <unistd.h> // close()
#include <stdlib.h> // exit()
#include <netdb.h> // getaddrinfo()
#include <string.h> // memset()

#include "Socket.h"


Socket *
socket_new(u_int16_t family)
{
    Socket *socket = (Socket *) malloc(sizeof(Socket));

    socket->family      = family;
    socket->connfd      = 0;
    socket->addressPair = NULL;

    return socket;
}

int
socket_connect(Socket *this, const char *host, const char *port)
{
    struct addrinfo hints;
    struct addrinfo *servinfo;
    int err;

    this->connfd = socket(this->family, SOCK_STREAM, 0);

    if (this->connfd == -1) {
        perror("socket died");
        return -1;
    }

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family   = this->family;
    hints.ai_socktype = SOCK_STREAM;
    err = getaddrinfo(host, port, &hints, &servinfo);
    if (err != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(err));
        return -1;
    }

    if (connect(this->connfd, servinfo->ai_addr, servinfo->ai_addrlen) == -1) {
        perror("connect died");
        return -1;
    }

    freeaddrinfo(servinfo);

    return 0;
}

int
socket_close(Socket *this)
{
    return close(this->connfd);
}

SocketAddress *
socket_get_local_address(Socket *this)
{
    if (this->addressPair == NULL) {
        this->addressPair = socket_address_pair_new(this);
    }

    return this->addressPair->local;
}

SocketAddress *
socket_get_remote_address(Socket *this)
{
    if (this->addressPair == NULL) {
        this->addressPair = socket_address_pair_new(this);
    }

    return this->addressPair->remote;
}

void
socket_free(Socket *this) {
    if (this->addressPair != NULL) {
        socket_address_pair_free(this->addressPair);
    }
    free(this);
}
