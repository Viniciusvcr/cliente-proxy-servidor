#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h> 
#include <arpa/inet.h>
#include "../servidor/includes/connector.h"
#include "../servidor/includes/req_methods.h"
#include "../servidor/models/includes/funcionario.h"
#include "../servidor/models/includes/fornecedor.h"
#include "../servidor/models/includes/produto.h"

#define PORT 10000
#define HOST "127.0.0.1"

void cut_str(char* str) {
    str[strlen(str) - 1] = '\0';
}

void get_info_funcionario(char* nome, char* departamento, char* cpf, unsigned int* idade) {
    system("clear");

    getchar();
    printf("Insira nome do novo funcionário: ");
    fgets(nome, STR_MAX, stdin);
    printf("Insira o departamento do novo funcionário: ");
    fgets(departamento, STR_MAX, stdin);
    printf("Insira o CPF do novo funcionário: ");
    fgets(cpf, STR_MAX, stdin);
    printf("Insira a idade do novo funcionário: ");
    scanf("%d", idade);
}

void handle_funcionario () {
    int escolha, socket_fd;
    unsigned int idade;
    char cpf[STR_MAX], nome[STR_MAX], departamento[STR_MAX];
    struct sockaddr_in serv_addr;
    func_req req;


    do {
        memset(&req, 0, sizeof(func_req));
        system("clear");

        printf("Escolha um das opções:\n");
        printf("[1] Cadastrar Funcionário\n");
        printf("[2] Buscar Funcionário\n");
        printf("[0] Voltar\n");

        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                // get_info_funcionario(nome, departamento, cpf, &idade);
                getchar();
                printf("Insira nome do novo funcionário: ");
                fgets(nome, STR_MAX, stdin);
                printf("Insira o departamento do novo funcionário: ");
                fgets(departamento, STR_MAX, stdin);
                printf("Insira o CPF do novo funcionário: ");
                fgets(cpf, STR_MAX, stdin);
                printf("Insira a idade do novo funcionário: ");
                scanf("%d", &idade);

                cut_str(nome);
                cut_str(departamento);
                cut_str(cpf);

                strcpy(req.cpf, cpf);
                strcpy(req.departamento, departamento);
                strcpy(req.nome, nome);
                req.idade = idade;

                req.req_method = POST;

                getchar();
            break;
            
            case 2:
                printf("Insira o CPF do funcionário: ");
                getchar();
                fgets(cpf, STR_MAX, stdin);
                cut_str(cpf);

                strcpy(req.cpf, cpf);
                req.req_method = GET;

            break;
        }
        create_client_connection(&socket_fd, PORT, &serv_addr, HOST);

        if (send(socket_fd, &req, sizeof(req), 0) == -1) {
            perror("\nErro ao enviar a mensagem");
        } else {
            printf("\nMensagem enviada\n");
        }
        
        func_res get;
        read(socket_fd, &get, sizeof(func_res));
        printf("\nResposta do servidor: \n");
        if (get.status == 200) {
            printf("  Nome        : %s\n", get.response_model.nome);
            printf("  Departamento: %s\n", get.response_model.departamento);
            printf("  CPF         : %s\n", get.response_model.cpf);
            printf("  Idade       : %d\n", get.response_model.idade);
            printf("  ID          : %d\n\n", get.response_model.id);
        } else {
            printf("  Status de erro: %d\n", get.status);
            printf("  Mensagem: %s\n\n", get.error_message);
        }

        fflush(stdin);
        printf("Pressione ENTER para continuar\n");
        getchar();
    } while (escolha);
}

void handle_fornecedor() {

} 

void handle_produto() {

}

int main() {
    int escolha;

    do {
        printf("Selecione o modelo:\n");
        printf("[1] Funcionário\n");
        printf("[2] Fornecedor\n");
        printf("[3] Produto\n");
        printf("[0] Sair\n");
        
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                handle_funcionario();
            break;

            case 2:
                handle_fornecedor();
            break;

            case 3:
                handle_produto();
            break;


        }
    } while (escolha);
}