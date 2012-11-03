#include <stdio.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h> // struct sockaddr_in
#include <arpa/inet.h> // inet_pton()
#include <unistd.h> // close()
#include <stdlib.h> // exit()
#include <netdb.h> // getaddrinfo()
#include <string.h> // memset()

int
main(int argc, char *argv[])
{
    int listenfd;
    int connfd;
    int s; // error
    struct addrinfo hints;
    struct addrinfo *servinfo;
    struct sockaddr_storage peeraddr;

    char host[NI_MAXHOST];
    char service[NI_MAXSERV];
    socklen_t len;

    listenfd = socket(AF_INET6, SOCK_STREAM, 0);

    if (listenfd == -1) {
        perror("socket died");
        exit(1);
    }

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family   = AF_INET6;     // use IPv4 or IPv6, whichever
    hints.ai_socktype = SOCK_STREAM;   // use TCP
    hints.ai_flags    = AI_PASSIVE;    // fill in my IP for me

    s = getaddrinfo(NULL, "1214", &hints, &servinfo);
    if (s != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
        exit(5);
    }

    if (bind(listenfd, servinfo->ai_addr, servinfo->ai_addrlen) == -1) {
        perror("bind died");
        exit(2);
    }
    freeaddrinfo(servinfo);

    if (listen(listenfd, 10) == -1) {
        perror("listen died");
        exit(3);
    }

    len = sizeof(struct sockaddr_storage);
    connfd = accept(listenfd, (struct sockaddr *) &peeraddr, &len);
    if (connfd == -1) {
        perror("accept died");
        exit(4);
    }

    printf("Hello server!\n");

    s = getnameinfo((struct sockaddr *) &peeraddr, len,
                    host, NI_MAXHOST,
                    service, NI_MAXSERV,
                    NI_NUMERICHOST | NI_NUMERICSERV); // numeric host and service
    if (s != 0) {
        fprintf(stderr, "getnameinfo: %s\n", gai_strerror(s));
        exit(5);
    }

    printf("Connect from %s:%s\n", host, service);

    s = getnameinfo((struct sockaddr *) &peeraddr, len,
                    host, NI_MAXHOST,
                    service, NI_MAXSERV,
                    0); // ascii host and service
    if (s != 0) {
        fprintf(stderr, "getnameinfo: %s\n", gai_strerror(s));
        exit(5);
    }

    printf("Connect from %s:%s\n", host, service);

    close(connfd);

    return 0;
}
