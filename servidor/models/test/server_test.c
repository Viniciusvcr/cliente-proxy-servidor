#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include "../includes/funcionario.h"
#include "../../includes/req_methods.h"

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
    func_req req;

    do {
        printf("[1] Cadastrar\n");
        printf("[2] Buscar\n");
        printf("[0] Sair\n");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                printf("POST\n");
                strcpy(req.cpf, cpf);
                strcpy(req.departamento, departamento);
                req.idade = idade;
                strcpy(req.nome, nome);
                req.req_method = POST;

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

                if (send(sock, &req, sizeof(func_req), 0) == -1) {
                    perror("Error sending message");
                } else {
                    printf("Message sent\n");
                }
                
                func_res response;
                read(sock, &response, sizeof(func_res));
                if (response.status == 200) {
                    printf("Response:\n");
                    printf("\tNome        : %s\n", response.response_model.nome);
                    printf("\tDepartamento: %s\n", response.response_model.departamento);
                    printf("\tCPF         : %s\n", response.response_model.cpf);
                    printf("\tIdade       : %d\n", response.response_model.idade);
                    printf("\tID          : %d\n", response.response_model.id);
                    printf("%d\n", response.status);
                } else {
                    printf("Status de erro: %d", response.status);
                    printf("Mensagem: %s", response.error_message);
                }
            break;

            case 2:
                printf("GET\n");
                strcpy(req.cpf, cpf);
                req.req_method = GET;

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

                if (send(sock, &req, sizeof(func_req), 0) == -1) {
                    perror("Error sending message");
                } else {
                    printf("Message sent\n");
                }
                
                func_res get;
                read(sock, &get, sizeof(func_res));
                if (get.status == 200) {
                    printf("\tNome        : %s\n", get.response_model.nome);
                    printf("\tDepartamento: %s\n", get.response_model.departamento);
                    printf("\tCPF         : %s\n", get.response_model.cpf);
                    printf("\tIdade       : %d\n", get.response_model.idade);
                    printf("\tID          : %d\n", get.response_model.id);
                    printf("%d\n", get.status);
                } else {
                    printf("Status de erro: %d\n", get.status);
                    printf("Mensagem: %s\n", get.error_message);
                }
            break;
        }

    } while (escolha);
}
