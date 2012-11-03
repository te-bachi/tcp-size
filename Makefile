
PROGRAMS       = server client

server_SOURCE  = server_main.c server.c
server_CFLAGS  = -Wall -ggdb -Iinclude
server_LDFLAGS = 

client_SOURCE  = client.c Socket.c SocketAddress.c
client_CFLAGS  = -Wall -ggdb -Iinclude
client_LDFLAGS = 

include Makefile.inc
