#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include "../models/includes/produto.h"
#include "../includes/req_methods.h"
#include "../includes/connector.h"

#define PORT 10000
#define LOCALHOST "127.0.0.1"

int main(int argc, char const *argv[]) {
    int sock = 0, escolha;
    struct sockaddr_in serv_addr;
    char nome[STR_MAX];
    unsigned int valor = 24;
    unsigned int qtdEstoque = 10;
    unsigned int id = 1;
    Produto* newProduto = (Produto*)malloc(sizeof(Produto));
    prod_req req;

    do {
        printf("[1] Cadastrar\n");
        printf("[2] Buscar\n");
        printf("[0] Sair\n");
        scanf("%d", &escolha);
        switch (escolha) {
            case 1:
                printf("POST\n");
                getchar();
                fgets(nome, STR_MAX, stdin);
                nome[strlen(nome) -1] = '\0';
                strcpy(req.nome, nome);
                req.valor = valor;
                req.qtdEstoque = qtdEstoque;
                req.req_method = POST;

                create_client_connection(&sock, PORT, &serv_addr, LOCALHOST);

                if (send(sock, &req, sizeof(prod_req), 0) == -1) {
                    perror("Error sending message");
                } else {
                    printf("Message sent\n");
                }

                prod_res response;
                read(sock, &response, sizeof(prod_res));
                if (response.status == 200) {
                    printf("Response: \n");
                    printf("\tNome                 : %s\n", response.response_model.nome);
                    printf("\tValor                : %d\n", response.response_model.valor);
                    printf("\tQuantidade em estoque: %d\n", response.response_model.qdtEstoque);
                    printf("\tID                   : %d\n", response.response_model.id);
                    printf("%s\n", response.error_message);
                } else {
                    printf("Status de erro: %d", response.status);
                    printf("Mensagem: %s", response.error_message);
                }
            break;

            case 2:
                printf("GET\n");
                scanf("%d", &id);
                req.id = id;
                req.req_method = GET;

                create_client_connection(&sock, PORT, &serv_addr, LOCALHOST);

                if (send(sock, &req, sizeof(prod_req), 0) == -1) {
                    perror("Error sending message");
                } else {
                    printf("Message sent\n");
                }

                prod_res get;
                read(sock, &get, sizeof(prod_res));
                if (get.status == 200) {
                    printf("\tNome                       : %s\n", get.response_model.nome);
                    printf("\tValor                      : %d\n", get.response_model.valor);
                    printf("\tQuantidade em estoque      : %d\n", get.response_model.qdtEstoque);
                    printf("\tID                         : %d\n", get.response_model.id);
                    printf("%d\n", get.status);
                } else {
                    printf("Status de erro: %d\n", get.status);
                    printf("Mensagem: %s\n", get.error_message);
                }
            break;
        }
    } while (escolha);
}
