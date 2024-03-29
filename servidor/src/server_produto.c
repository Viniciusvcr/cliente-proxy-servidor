#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <semaphore.h>
#include <sys/types.h>
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <netinet/in.h> 
#include <string.h>
#include "../models/includes/produto.h"
#include "../includes/req_methods.h"
#include "../includes/connector.h"

#define PORT 8082

#define PID pid_t

#define SHMEM_FILE "shmfile"
const unsigned int SHMEM_SIZE = sizeof(Database_prod);

sem_t semaphore;
#define PSHARED 1

const Produto empty = {0};

void log_response(prod_res* response) {
    printf("  Resultado:\n");
    
    if (response->status > 200) {
        printf("    Erro com status: %d\n", response->status);
        printf("    Razão: %s\n", response->error_message);
    } else {
        printf("    Sucesso com status: %d\n", response->status);
        printf("    Response:\n");
        printf("      Nome                 : %s\n", response->response_model.nome);
        printf("      Valor                : %d\n", response->response_model.valor);
        printf("      Quantidade em estoque: %d\n", response->response_model.qdtEstoque);
        printf("      ID                   : %d\n", response->response_model.id);
    }
}

void error(prod_res* response, unsigned int status, char* message) {
    response->status = status;
    strcpy(response->error_message, message);
    response->response_model = empty;
    log_response(response);
}

void create_response(prod_res* response, Produto* model_response) {
    strcpy(response->response_model.nome, model_response->nome);
    response->response_model.qdtEstoque = model_response->qdtEstoque;
    response->response_model.valor = model_response->valor;
    response->response_model.id = model_response->id;
    response->status = 200;
    log_response(response);
}

int main(int argc, char const *argv[]) {
    PID pid;
    key_t shmem_key;
    int shmem_id;
    int server_fd, new_socket, opt = 1;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    printf("Iniciando servidor de produtos...\n");

    shmem_key = ftok(SHMEM_FILE, 65);
    if ((shmem_id = shmget(shmem_key, SHMEM_SIZE, 0666 | IPC_CREAT)) < 0) {
        perror("Erro ao criar memória compartilhada");
        exit(EXIT_FAILURE);
    } else {
        printf("\tMemória Compartilhada criada!\n");
    }

    if (sem_init(&semaphore, PSHARED, 1) < 0) {
        perror("Erro ao inicializar o semáforo");
        exit(EXIT_FAILURE);
    } else {
        printf("\tSemáforo inicializado\n");
    }

    Database_prod* shmem_data = (Database_prod*) shmat(shmem_id, NULL, 0); 

    create_server_connection(&server_fd, PORT, &opt, &address);

    if(produtos_init() != NULL) {
        printf("\tBanco de dados iniciado!\n");
    } else {
        perror("Falha ao inicializar banco de dados");
        exit(EXIT_FAILURE);
    }

    printf("Ouvindo na porta %d\n", PORT);
    while((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) > 0) {
        pid = fork();
        if (pid == 0) {
            prod_req req_buffer;
            prod_res response;

            memset(&req_buffer, 0, sizeof(prod_req));
            memset(&response, 0, sizeof(prod_res));

            int req_size = read(new_socket, &req_buffer, sizeof(prod_req));

            if (req_size < 0) {
                error(&response, 500, "Internal Server Error");
            } else {
                if (req_size == sizeof(prod_req)) {
                    sem_wait(&semaphore);
                    memcpy(database_prod, shmem_data, sizeof(Database_prod));
                    sem_post(&semaphore);
                    
                    if (req_buffer.req_method == GET) {
                        printf("\nNova requisição GET:\n");
                        Produto* handled = produto_get(req_buffer.id);

                        if (handled != NULL) {
                            create_response(&response, handled);
                        } else {
                            error(&response, 404, "Produto não encontrado");
                        }
                    } else if (req_buffer.req_method == POST) {
                        printf("\nNova requisição POST:\n");
                        Produto* handled = produto_create(req_buffer.nome, req_buffer.valor, req_buffer.qtdEstoque);

                        if (handled == NULL) {
                            error(&response, 500, "Internal Server Error");
                        } else {
                            create_response(&response, handled);
                        }
                    }
                    
                    sem_wait(&semaphore);
                    memcpy(shmem_data, database_prod, sizeof(Database_prod));
                    sem_post(&semaphore);
                } else {
                    printf("\nNova requisição desconhecida:\n");
                    printf("  Resultado:\n");
                    printf("    Erro com status: 400\n");
                    printf("    Razão: Requisição não tem o número de bytes correto para este servidor\n");
                }
            }
            
            write(new_socket, &response, sizeof(prod_res));
            return EXIT_SUCCESS;
        }
    }

    shmdt(shmem_data);
    shmctl(shmem_id, IPC_RMID, NULL);
}
