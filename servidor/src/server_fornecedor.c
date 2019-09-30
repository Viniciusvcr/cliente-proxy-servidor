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

void log_response(forn_res* response) {
    printf("  Resultado:\n");
    
    if (response->status > 200) {
        printf("    Erro com status: %d\n", response->status);
        printf("    Razão: %s\n", response->error_message);
    } else {
        printf("    Sucesso com status: %d\n", response->status);
        printf("    Response:\n");
        printf("      Nome Fantasia: %s\n", response->response_model.nome_fantasia);
        printf("      CNPJ         : %s\n", response->response_model.cnpj);
        printf("      Telefone     : %s\n", response->response_model.telefone);
        printf("      ID           : %d\n", response->response_model.id);
    }
}

void error(forn_res* response, unsigned int status, char* message) {
    response->status = status;
    strcpy(response->error_message, message);
    response->response_model = empty;
    log_response(response);
}

void create_response(forn_res* response, Fornecedor* model_response) {
    strcpy(response->response_model.nome_fantasia, model_response->nome_fantasia);
    strcpy(response->response_model.cnpj, model_response->cnpj);
    strcpy(response->response_model.telefone, model_response->telefone);
    response->response_model.id = model_response->id;
    response->status = 200;
    log_response(response);
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
    write(com_fifo, database_forn, sizeof(Database_forn));
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
                    read(com_fifo, database_forn, sizeof(Database_forn));

                    if (req_buffer.req_method == GET) {
                        printf("\nNova requisição GET:\n");
                        Fornecedor* handled = fornecedor_get(req_buffer.cnpj);

                        if (handled != NULL) {
                            create_response(&response, handled);
                        } else {
                            error(&response, 404, "Fornecedor não encontrado");
                        }
                    } else if (req_buffer.req_method == POST) {
                        printf("\nNova requisição POST:\n");
                        Fornecedor* handled = fornecedor_create(req_buffer.nome_fantasia, req_buffer.cnpj, req_buffer.telefone);

                        if (handled == NULL) {
                            error(&response, 500, "Internal Server Error");
                        } else {
                            create_response(&response, handled);
                        }
                    }

                    write(com_fifo, database_forn, sizeof(Database_forn));
                } else {
                    printf("\nNova requisição desconhecida:\n");
                    printf("  Resultado:\n");
                    printf("    Erro com status: 400\n");
                    printf("    Razão: Requisição não tem o número de bytes correto para este servidor\n");
                }
            }

            write(new_socket, &response, sizeof(forn_res));
            return EXIT_SUCCESS;
        }
    }
    return 0;
}
