#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include "../models/includes/fornecedor.h"
#include "../includes/req_methods.h"
#include "../includes/connector.h"

#define PORT 8081
#define LOCALHOST "127.0.0.1"

int main(int argc, char const *argv[]){
    int sock = 0, escolha;
    struct sockaddr_in serv_addr; 
    char nome_fantasia[STR_MAX];
    char cnpj[STR_MAX];
    char telefone[STR_MAX];
    forn_req req;

    do {
        printf("[1] Cadastrar\n");
        printf("[2] Buscar\n");
        printf("[0] Sair\n");
        scanf("%d", &escolha);
        switch (escolha) {
            case 1:
                printf("POST\n");
                getchar();
                fgets(nome_fantasia, STR_MAX, stdin);
                fgets(telefone, STR_MAX, stdin);
                fgets(cnpj, STR_MAX, stdin);
                nome_fantasia[strlen(nome_fantasia) - 1] = '\0';
                telefone[strlen(telefone) - 1] = '\0';
                cnpj[strlen(cnpj) - 1] = '\0';
                strcpy(req.cnpj, cnpj);
                strcpy(req.telefone, telefone);
                strcpy(req.nome_fantasia, nome_fantasia);
                req.req_method = POST;

                create_client_connection(&sock, PORT, &serv_addr, LOCALHOST);

                if (send(sock, &req, sizeof(forn_req), 0) == -1) {
                    perror("Error sending message");
                } else {
                    printf("Message sent\n");
                }
                
                forn_res response;
                read(sock, &response, sizeof(forn_res));
                if (response.status == 200) {
                    printf("Response:\n");
                    printf("\tNome fantasia: %s\n", response.response_model.nome_fantasia);
                    printf("\tTelefone     : %s\n", response.response_model.telefone);
                    printf("\tCNPJ         : %s\n", response.response_model.cnpj);
                    printf("\tID           : %d\n", response.response_model.id);
                    printf("%d\n", response.status);
                } else {
                    printf("Status de erro: %d", response.status);
                    printf("Mensagem: %s", response.error_message);
                }
            break;

            case 2:
                printf("GET\n");
                getchar();
                fgets(cnpj, STR_MAX, stdin);
                cnpj[strlen(cnpj) - 1] = '\0';
                strcpy(req.cnpj, cnpj);
                req.req_method = GET;

                create_client_connection(&sock, PORT, &serv_addr, LOCALHOST);

                if (send(sock, &req, sizeof(forn_req), 0) == -1) {
                    perror("Error sending message");
                } else {
                    printf("Message sent\n");
                }
                
                forn_res get;
                read(sock, &get, sizeof(forn_res));
                if (get.status == 200) {
                    printf("\tNome        : %s\n", get.response_model.nome_fantasia);
                    printf("\tDepartamento: %s\n", get.response_model.telefone);
                    printf("\tCPF         : %s\n", get.response_model.cnpj);
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
