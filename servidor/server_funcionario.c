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
#define MAXLEN 50

#define Pipe int
#define PID pid_t

#define CREATE 1
#define GET 0

Funcionario* handle_req(func_req* req) {
    printf("HANDLE_REQ");
    switch (req->req_type) {
        case CREATE:
            return funcionario_create(req->func->nome, req->func->departamento, req->func->cpf, req->func->idade);
        break;

        case GET:
            return funcionario_get(req->func->cpf);
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

    ;
    printf("Ouvindo na porta %d\n", PORT);
    while (1) {
        (new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen));
        pid = fork();
        if (pid == 0) {
            printf("Processo filho\n");
            func_req* req_buffer;
            int v = read(new_socket, req_buffer, sizeof(func_req));
            printf("%p, %d", req_buffer->func, req_buffer->req_type);
            Funcionario* res = handle_req(req_buffer);
            v = write(com_pipe[WRITE], res, sizeof(Funcionario));
            printf("%d\n", v);
            exit(EXIT_SUCCESS);
        } else {
            // wait(NULL);
            // printf("Processo pai\n");
            // buffer = NULL;
            // if (read(com_pipe[READ], buffer, sizeof(Funcionario)) > 0) {
            //     printf("%p", buffer);
            //     send(new_socket, buffer, sizeof(Funcionario), 0);
            // } else {
            //     char* message = "Falha na requisição";
            //     send(new_socket, message, strlen(message), 0);
            // }
        }
    }
}
