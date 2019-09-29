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

#define ERROR = 1

#define Pipe int
#define PID pid_t

const Funcionario empty = {0};

void log_response(func_res* response) {
    printf("  Resultado:\n");
    
    if (response->status > 200) {
        printf("    Erro com status: %d\n", response->status);
        printf("    Razão: %s\n", response->error_message);
    } else {
        printf("    Sucesso com status: %d\n", response->status);
        printf("    Response:\n");
        printf("      Nome        : %s\n", response->response_model.nome);
        printf("      Departamento: %s\n", response->response_model.departamento);
        printf("      CPF         : %s\n", response->response_model.cpf);
        printf("      Idade       : %d\n", response->response_model.idade);
        printf("      ID          : %d\n", response->response_model.id);
    }
}

void error(func_res* response, unsigned int status, char* message) {
    response->status = status;
    strcpy(response->error_message, message);
    response->response_model = empty;
    log_response(response);
}

void create_response(func_res* response, Funcionario* model_response) {
    strcpy(response->response_model.cpf, model_response->cpf);
    strcpy(response->response_model.departamento, model_response->departamento);
    strcpy(response->response_model.nome, model_response->nome);
    response->response_model.idade = model_response->idade;
    response->response_model.id = model_response->id;
    response->status = 200;
    log_response(response);
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
    while (((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) > 0)) {
        pid = fork();
        if (pid == 0) {
            func_req req_buffer;
            func_res response;

            memset(&req_buffer, 0, sizeof(func_req));
            memset(&response, 0, sizeof(func_res));

            int req_size = read(new_socket, &req_buffer, sizeof(func_req));
            if (req_size < 0) {
                error(&response, 500, "Internal Server Error");
            } else {
                if (req_size == sizeof(func_req)) {
                    read(com_pipe[READ], database, sizeof(Database));

                    if (req_buffer.req_method == GET) {
                        printf("\nNova requisição GET:\n");
                        Funcionario* handled = funcionario_get(req_buffer.cpf);
                        
                        if (handled != NULL) {
                            create_response(&response, handled);
                        } else {
                            error(&response, 404, "Usuário não encontrado");
                        }
                    }else if (req_buffer.req_method == POST) {
                        printf("\nNova requisição POST:\n");
                        Funcionario* handled = funcionario_create(req_buffer.nome, req_buffer.departamento, req_buffer.cpf, req_buffer.idade);

                        if (handled == NULL) {
                            error(&response, 500, "Internal Server Error");
                        } else {
                            create_response(&response, handled);
                        }
                    }

                    write(com_pipe[WRITE], database, sizeof(Database));
                } else {
                    printf("\nNova requisição desconhecida:\n");
                    printf("  Resultado:\n");
                    printf("    Erro com status: 400\n");
                    printf("    Razão: Requisição não tem o número de bytes correto para este servidor\n");
                }
            }

            write(new_socket, &response, sizeof(func_res));
            return EXIT_SUCCESS;
        }
    }
}
