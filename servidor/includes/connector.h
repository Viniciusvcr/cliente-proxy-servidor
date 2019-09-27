#ifndef CONNECTOR_H
#define CONNECTOR_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <sys/socket.h>
#include <netinet/in.h> 
#include <arpa/inet.h>

void create_server_connection(int* server_fd, int port, int* opt, struct sockaddr_in* address);
void create_client_connection(int* socket_fd, int port, struct sockaddr_in* serv_addr, char* host);

#endif