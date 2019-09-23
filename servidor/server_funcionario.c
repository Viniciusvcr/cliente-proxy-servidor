#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <netinet/in.h> 
#include <string.h>
#include "models/includes/funcionario.h"

#define PORT 8080

#define WRITE 1
#define READ 0
#define ERROR -1
#define MAXLEN 50

#define Pipe int
#define PID pid_t

#define CREATE 1
#define GET 0

Funcionario* handle_req(func_req* req) {
    printf("HANDLE_REQ\n");
    switch (req->req_type) {
        case CREATE:
            printf("CREATE\n");
            return funcionario_create(req->nome, req->departamento, req->cpf, req->idade);
        break;

        case GET:
            printf("GET\n");
            Funcionario* res = funcionario_get(req->cpf);
            printf("%p\n", res);
            return res;
        break;

        default:
            return NULL;
    }
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

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) { 
        perror("Criação do Socket falhou"); 
        exit(EXIT_FAILURE); 
    } else {
        printf("\tSocket criado!\n");
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) { 
        perror("setsockopt"); 
        exit(EXIT_FAILURE); 
    }

    address.sin_family = AF_INET; 
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) { 
        perror("Bind falhou"); 
        exit(EXIT_FAILURE); 
    } else {
        printf("\tBind criado!\n");
    }

    if (listen(server_fd, 3) < 0) { 
        perror("Listen falhou"); 
        exit(EXIT_FAILURE); 
    } else {
        printf("\tListening!\n");
    }

    if (funcionarios_init() != NULL) {
        printf("\tBanco de dados iniciado!\n");
    } else {
        perror("Falha ao inicializar banco de dados");
        exit(EXIT_FAILURE);
    }

    printf("Ouvindo na porta %d\n", PORT);
    while ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) > 0) {
        pid = fork();
        if (pid == 0) {
            func_req req_buffer;
            int v = read(new_socket, &req_buffer, sizeof(func_req));
            if (v < 0) {
                write(new_socket, "REQ_FAILED", 11);
            } else {
                func_req res;
                if (req_buffer.req_type == WRITE) {
                    Funcionario* handled = handle_req(&req_buffer);
                    
                    if (handled != NULL) {
                        strcpy(res.cpf, handled->cpf);
                        strcpy(res.departamento, handled->departamento);
                        strcpy(res.nome, handled->nome);
                        res.idade = handled->idade;
                        res.req_type = 200;

                        printf("Novo funcionário!\n");
                        printf("\tNome        : %s\n", handled->nome);
                        printf("\tDepartamento: %s\n", handled->departamento);
                        printf("\tCPF         : %s\n", handled->cpf);
                        printf("\tIdade       : %d\n", handled->idade);
                        printf("\tID          : %d\n", handled->id);
                    } else {
                        res.req_type = 500;
                        // res.message = "Falha interna de servidor"
                    }
                }else if (req_buffer.req_type == READ) {
                    printf("%s\n", req_buffer.cpf);
                    Funcionario* handled = handle_req(&req_buffer);

                    if (handled == NULL) {
                        res.req_type = 404;
                        // res.message = "Usuário não encontrado"
                    } else {
                        strcpy(res.cpf, handled->cpf);
                        strcpy(res.departamento, handled->departamento);
                        strcpy(res.nome, handled->nome);
                        res.idade = handled->idade;
                        res.req_type = 200;
                    }
                }
                write(new_socket, &res, sizeof(res));
            }
        }
    }
}