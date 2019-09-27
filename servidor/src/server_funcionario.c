#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <netinet/in.h> 
#include <string.h>
#include "../models/includes/funcionario.h"
#include "../includes/req_methods.h"
#include "../includes/connector.h"

#define PORT 8080

#define WRITE 1
#define READ 0

#define Pipe int
#define PID pid_t

const Funcionario empty = {0};

void error(func_res* response, unsigned int status, char* message) {
    response->status = status;
    strcpy(response->error_message, message);
    response->response_model = empty;
}

void create_response(func_res* response, Funcionario* model_response) {
    strcpy(response->response_model.cpf, model_response->cpf);
    strcpy(response->response_model.departamento, model_response->departamento);
    strcpy(response->response_model.nome, model_response->nome);
    response->response_model.idade = model_response->idade;
    response->response_model.id = model_response->id;
    response->status = 200;
}

int main(int argc, char const *argv[]){
    PID pid;
    Pipe com_pipe[2];
    int server_fd, new_socket, opt = 1;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    Funcionario* buffer;

    printf("Iniciando servidor de funcionários...\n");

    if (pipe(com_pipe) < 0) {
        perror("Failed creating pipe");
        exit(EXIT_FAILURE);
    } else {
        printf("\tPipe criado!\n");
    }

    create_server_connection(&server_fd, PORT, &opt, &address);

    if (funcionarios_init() != NULL) {
        printf("\tBanco de dados iniciado!\n");
    } else {
        perror("Falha ao inicializar banco de dados");
        exit(EXIT_FAILURE);
    }

    write(com_pipe[WRITE], database, sizeof(Database));
    printf("Ouvindo na porta %d\n", PORT);
    while ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) > 0) {
        pid = fork();
        if (pid == 0) {
            func_req req_buffer;
            func_res response;

            memset(&req_buffer, 0, sizeof(func_req));
            memset(&response, 0, sizeof(func_res));

            read(com_pipe[READ], database, sizeof(Database));
            int v = read(new_socket, &req_buffer, sizeof(func_req));

            if (v < 0) {
                strcpy(response.error_message, "Internal Server Error");
                response.status = 500;
            } else {
                if (req_buffer.req_method == GET) {
                    Funcionario* handled = funcionario_get(req_buffer.cpf);
                    
                    if (handled != NULL) {
                        create_response(&response, handled);
                    } else {
                        error(&response, 404, "Usuário não encontrado");
                    }
                }else if (req_buffer.req_method == POST) {
                    Funcionario* handled = funcionario_create(req_buffer.nome, req_buffer.departamento, req_buffer.cpf, req_buffer.idade);

                    if (handled == NULL) {
                        error(&response, 500, "Internal Server Error");
                    } else {
                        create_response(&response, handled);
                    }
                }
                write(new_socket, &response, sizeof(func_res));
            }
            write(com_pipe[WRITE], database, sizeof(Database));
            return EXIT_SUCCESS;
        }
    }
}
