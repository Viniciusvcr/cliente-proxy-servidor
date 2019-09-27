#include "includes/connector.h"

void create_server_connection(int* server_fd, int port, int* opt, struct sockaddr_in* address) {
    if ((*server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) { 
        perror("Criação do Socket falhou"); 
        exit(EXIT_FAILURE); 
    } else {
        printf("\tSocket criado!\n");
    }

    if (setsockopt(*server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, opt, sizeof(*opt))) { 
        perror("setsockopt"); 
        exit(EXIT_FAILURE); 
    }

    address->sin_family = AF_INET; 
    address->sin_addr.s_addr = INADDR_ANY; 
    address->sin_port = htons(port);

    if (bind(*server_fd, (struct sockaddr *)address, sizeof(*address)) < 0) { 
        perror("Bind falhou"); 
        exit(EXIT_FAILURE); 
    } else {
        printf("\tBind criado!\n");
    }

    if (listen(*server_fd, 3) < 0) { 
        perror("Listen falhou"); 
        exit(EXIT_FAILURE); 
    } else {
        printf("\tListening!\n");
    }
}

void create_client_connection(int* socket_fd, int port, struct sockaddr_in* serv_addr, char* host) {
    if ((*socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) { 
        perror("Criação do Socket falhou"); 
        exit(EXIT_FAILURE); 
    }

    serv_addr->sin_family = AF_INET; 
    serv_addr->sin_port = htons(port);

    if(inet_pton(AF_INET, host, &serv_addr->sin_addr) <= 0)  { 
        perror("Endereço inválido/Não suportado"); 
        exit(EXIT_FAILURE); 
    }

    if (connect(*socket_fd, (struct sockaddr *)serv_addr, sizeof(*serv_addr)) < 0) { 
        perror("Connection Failed"); 
        exit(EXIT_FAILURE); 
    }
}