#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <netinet/in.h> 
#include <string.h>
#include "../models/includes/fornecedor.h"
#include "../includes/req_methods.h"
#include "../includes/connector.h"

#define PORT 8081

#define PID pid_t
#define Fifo int
#define FIFO_FILE "/tmp/fornecedor_fifo"

const Fornecedor empty = {0};

void error(forn_res* response, unsigned int status, char* message) {
    response->status = status;
    strcpy(response->error_message, message);
    response->response_model = empty;
}

void create_response(forn_res* response, Fornecedor* model_response) {
    strcpy(response->response_model.nome_fantasia, model_response->nome_fantasia);
    strcpy(response->response_model.cnpj, model_response->cnpj);
    strcpy(response->response_model.telefone, model_response->telefone);
    response->response_model.id = model_response->id;
    response->status = 200;
}

int main(int argc, char const *argv[]){
    PID pid;
    Fifo com_fifo;
    int server_fd, new_socket, opt = 1;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    printf("Iniciando servidor de funcionários...\n");

    remove(FIFO_FILE);
    if (mkfifo(FIFO_FILE, 0666) < 0) {
        perror("Erro criando FIFO");
        exit(EXIT_FAILURE);
    } else {
        printf("\tFIFO criado\n");
    }

    create_server_connection(&server_fd, PORT, &opt, &address);

    if (fornecedor_init() != NULL) {
        printf("\tBanco de dados iniciado\n");
    } else {
        perror("Falha ao iniciar banco de dados");
    }

    printf("Ouvindo na porta %d\n", PORT);
    com_fifo = open(FIFO_FILE, O_RDWR | O_TRUNC);
    write(com_fifo, database, sizeof(Database));
    while((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) > 0) {
        pid = fork();
        if (pid == 0) {
            forn_req req_buffer;
            forn_res response;

            memset(&req_buffer, 0, sizeof(forn_req));
            memset(&response, 0, sizeof(forn_res));
            
            int req_size = read(new_socket, &req_buffer, sizeof(forn_req));

            if (req_size < 0) {
                error(&response, 500, "Internal Server Error");
            } else {
                if (req_size == sizeof(forn_req)) {
                    read(com_fifo, database, sizeof(Database));

                    if (req_buffer.req_method == GET) {
                        Fornecedor* handled = fornecedor_get(req_buffer.cnpj);

                        if (handled != NULL) {
                            create_response(&response, handled);
                        } else {
                            error(&response, 404, "Fornecedor não encontrado");
                        }
                    } else if (req_buffer.req_method == POST) {
                        Fornecedor* handled = fornecedor_create(req_buffer.nome_fantasia, req_buffer.cnpj, req_buffer.telefone);

                        if (handled == NULL) {
                            error(&response, 500, "Internal Server Error");
                        } else {
                            create_response(&response, handled);
                        }
                    }

                    write(com_fifo, database, sizeof(Database));
                }
            }

            write(new_socket, &response, sizeof(forn_res));
            return EXIT_SUCCESS;
        }
    }
    return 0;
}
