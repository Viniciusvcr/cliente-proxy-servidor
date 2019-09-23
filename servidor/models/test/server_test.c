#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include "../includes/funcionario.h"

#define PORT 8080
#define LOCALHOST "127.0.0.1"

int main(int argc, char const *argv[]){
    int sock = 0, escolha;
    struct sockaddr_in serv_addr; 
    char* nome = "Vinícius";
    char* departamento = "TI";
    char* cpf = "11243593970";
    unsigned int idade = 20;
    Funcionario* newFuncionario = (Funcionario*)malloc(sizeof(Funcionario));

    do {
        printf("[1] Cadastrar");
        printf("[2] Buscar");
        printf("[0] Sair");
        scanf("%d", &escolha);

        switch (escolha) {

            case 1:
                newFuncionario->nome = (char*)malloc(sizeof(char) * strlen(nome));
                newFuncionario->departamento = (char*)malloc(sizeof(char) * strlen(departamento));
                newFuncionario->cpf = (char*)malloc(sizeof(char) * strlen(cpf));

                strcpy(newFuncionario->nome, nome);
                strcpy(newFuncionario->departamento, departamento);
                strcpy(newFuncionario->cpf, cpf);
                newFuncionario->idade = idade;

                func_req* req = (func_req*)malloc(sizeof(func_req));
                req->func = newFuncionario;
                req->req_type = 1;

                if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) { 
                    perror("\n Socket creation error \n"); 
                    return -1; 
                }

                serv_addr.sin_family = AF_INET; 
                serv_addr.sin_port = htons(PORT);

                if(inet_pton(AF_INET, LOCALHOST, &serv_addr.sin_addr)<=0)  { 
                    printf("\nInvalid address/ Address not supported \n"); 
                    return -1; 
                } 

                if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) { 
                    perror("\nConnection Failed \n"); 
                    return -1; 
                }

                if (send(sock, req, sizeof(func_req), 0) == -1) {
                    perror("Error sending message");
                } else {
                    printf("Message sent\n");
                    free(req);
                }
                
                Funcionario* buffer = NULL;
                printf("%ld\n", read(sock, buffer, sizeof(Funcionario)));

                // printf("\tNome        : %s\n", buffer->nome);
                // printf("\tDepartamento: %s\n", buffer->departamento);
                // printf("\tCPF         : %s\n", buffer->cpf);
                // printf("\tIdade       : %d\n", buffer->idade);
                // printf("\tId          : %d\n", buffer->id);
            break;
        }

    } while (escolha);
}
