#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <netinet/in.h> 
#include <string.h>
#include "../models/includes/produto.h"
#include "../includes/req_methods.h"
#include "../includes/connector.h"

#define PORT 8080

#define WRITE 1
#define READ 0

#define Pipe int
#define PID pid_t

const Produto empty = {0};

void error(prod_res* response, unsigned int status, char* message) {
    response->status = status;
    strcpy(response->error_message, message);
    response->response_model = empty;
}

void create_response(prod_res* response, Produto* model_response) {
    strcpy(response->response_model.nome, model_response->nome);
    response->response_model.qdtEstoque = model_response->qdtEstoque;
    response->response_model.valor = model_response->valor;
    response->response_model.id = model_response->id;
    response->status = 200;
}

int main(int argc, char const *argv[]) {
    PID pid;
    Pipe com_pipe[2];
    int server_fd, new_socket, opt = 1;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    printf("Iniciando servidor de produtos...\n");

    if (pipe(com_pipe) < 0) {
        perror("Failed creating pipe");
        exit(EXIT_FAILURE);
    } else {
        printf("\tPipe criado\n");
    }

    create_server_connection(&server_fd, PORT, &opt, &address);

    if(produtos_init() != NULL) {
        printf("\tBanco de dados iniciado!\n");
    } else {
        perror("Falha ao inicializar banco de dados");
        exit(EXIT_FAILURE);
    }

    write(com_pipe[WRITE], database, sizeof(Database));
    printf("Ouvindo na porta %d\n", PORT);
    while((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) > 0) {
        pid = fork();
        if (pid == 0) {
            prod_req req_buffer;
            prod_res response;

            memset(&req_buffer, 0, sizeof(prod_req));
            memset(&response, 0, sizeof(prod_res));

            read(com_pipe[READ], database, sizeof(Database));
            int v = read(new_socket, &req_buffer, sizeof(prod_req));

            if (v < 0) {
                strcpy(response.error_message, "Internal Server Error");
                response.status = 500;
            } else {
                if (req_buffer.req_method == GET) {
                    Produto* handled = produto_get(req_buffer.id);

                    if (handled != NULL) {
                        create_response(&response, handled);
                    } else {
                        error(&response, 404, "Usuário não encontrado");
                    }
                } else if (req_buffer.req_method == POST) {
                    Produto* handled = produto_create(req_buffer.id, req_buffer.nome, req_buffer.qtdEstoque);

                    if (handled == NULL) {
                        error(&response, 500, "Internal Server Error");
                    } else {
                        create_response(&response, handled);
                    }
                }
                write(new_socket, &response, sizeof(prod_res));
            }
            write(com_pipe[WRITE], database, sizeof(Database));
            return EXIT_SUCCESS;
        }
    }
}
