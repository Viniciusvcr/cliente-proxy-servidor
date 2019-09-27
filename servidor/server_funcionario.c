#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <netinet/in.h> 
#include <string.h>
#include "models/includes/funcionario.h"
#include "includes/req_methods.h"
#include "includes/connector.h"

#define PORT 8080

#define WRITE 1
#define READ 0
#define ERROR -1
#define MAXLEN 50

#define Pipe int
#define PID pid_t

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
                        strcpy(response.response_model.cpf, handled->cpf);
                        strcpy(response.response_model.departamento, handled->departamento);
                        strcpy(response.response_model.nome, handled->nome);
                        response.response_model.idade = handled->idade;
                        response.response_model.id = handled->id;
                        response.status = 200;
                    } else {
                        response.status = 404;
                        strcpy(response.error_message, "Usuário não encontrado\n");
                    }
                }else if (req_buffer.req_method == POST) {
                    Funcionario* handled = funcionario_create(req_buffer.nome, req_buffer.departamento, req_buffer.cpf, req_buffer.idade);

                    if (handled == NULL) {
                        response.status = 500;
                        strcpy(response.error_message, "Internal Server Error");
                    } else {
                        strcpy(response.response_model.cpf, handled->cpf);
                        strcpy(response.response_model.departamento, handled->departamento);
                        strcpy(response.response_model.nome, handled->nome);
                        response.response_model.idade = handled->idade;
                        response.response_model.id = handled->id;
                        response.status = 200;
                    }
                }
                write(new_socket, &response, sizeof(func_res));
            }
            write(com_pipe[WRITE], database, sizeof(Database));
            return EXIT_SUCCESS;
        }
    }
}
