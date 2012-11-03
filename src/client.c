#include <stdio.h>
#include <stdlib.h>

#include "Socket.h"
#include "SocketAddress.h"


void
usage(char *progname)
{
    printf("%s <hostname|ip> <port>\n", progname);
    exit(EXIT_FAILURE);
}

int
main(int argc, char *argv[])
{
    Socket *socket;
    SocketAddress *address;
    if (argc < 3) {
        usage(argv[0]);
    }

    if ((socket = socket_new(SOCKET_IPV6)) != NULL) {
        if (!socket_connect(socket, argv[1], argv[2])) {
            address = socket_get_local_address(socket);
            printf("local: %s:%s\n", address->address, address->port);
            printf("local: %s:%s\n", address->hostname, address->service);
            address = socket_get_remote_address(socket);
            printf("remote: %s:%s\n", address->address, address->port);
            printf("remote: %s:%s\n", address->hostname, address->service);
            socket_close(socket);
        }
        socket_free(socket);
    }

    return 0;
}
