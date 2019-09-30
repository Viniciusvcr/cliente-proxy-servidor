#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "../servidor/models/includes/produto.h"
#include "../servidor/models/includes/fornecedor.h"
#include "../servidor/models/includes/funcionario.h"
#include "../servidor/includes/req_methods.h"
#include "../servidor/includes/connector.h"

#define PORT 10000
#define FUNC_PORT 8080
#define FORN_PORT 8081
#define PROD_PORT 8082

#define LOCALHOST "127.0.0.1"

int main(int argc, char const *argv[]){
    pid_t pid;
    int server_fd, new_socket, opt = 1;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    prod_req prod_req = {0};
    prod_res prod_res = {0};
    forn_req forn_req = {0};
    forn_res forn_res = {0};
    func_req func_req = {0};
    func_res func_res = {0};
    const unsigned int MAX_REQ_SIZE = sizeof(func_req);
    void* req = malloc(MAX_REQ_SIZE);

    printf("Iniciando proxy...\n");
    create_server_connection(&server_fd, PORT, &opt, &address);

    printf("Ouvindo na porta %d\n", PORT);
    while((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) > 0) {
        pid = fork();

        if (pid == 0) {
            int req_size = read(new_socket, req, MAX_REQ_SIZE);
            int func_socket, forn_socket, prod_socket;

            switch (req_size) {
                case sizeof(func_req):
                    memcpy(&func_req, req, sizeof(func_req));
                    create_client_connection(&func_socket, FUNC_PORT, &address, LOCALHOST);
                    if (send(func_socket, &func_req, sizeof(func_req), 0) == -1) {
                        perror("Error sending Funcionário message");
                    } else {
                        printf("Message sent\n");
                    }
                    read(func_socket, &func_res, sizeof(func_res));
                    write(new_socket, &func_res, sizeof(func_res));
                break;

                case sizeof(forn_req):
                    memcpy(&forn_req, req, sizeof(forn_req));
                    create_client_connection(&forn_socket, FORN_PORT, &address, LOCALHOST);
                    if (send(forn_socket, &forn_req, sizeof(forn_req), 0) == -1) {
                        perror("Error sending Fornecedor message");
                    } else {
                        printf("Message sent\n");
                    }
                    read(forn_socket, &forn_res, sizeof(forn_res));
                    write(new_socket, &forn_res, sizeof(forn_res));
                break;

                case sizeof(prod_req):
                    memcpy(&prod_req, req, sizeof(prod_req));
                    create_client_connection(&prod_socket, PROD_PORT, &address, LOCALHOST);
                    if (send(prod_socket, &prod_req, sizeof(prod_req), 0) == -1) {
                        perror("Error sending Produto message");
                    } else {
                        printf("Message sent\n");
                    }
                    read(prod_socket, &prod_res, sizeof(prod_res));
                    write(new_socket, &prod_res, sizeof(prod_res));
                break;

                default: 
                    perror("Falha ao ler requisição do cliente");
            }

        }
    }

    return 0;
}
