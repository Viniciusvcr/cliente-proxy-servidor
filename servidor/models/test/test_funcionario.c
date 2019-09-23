#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "../includes/funcionario.h"

int main() {
    char* nome = "Vinícius Regatieri";
    char* departamento = "Gerente";
    char* cpf = "123";
    unsigned int idade = 20;
    
    funcionarios_init();
    Funcionario* buffer = NULL;

    buffer = funcionario_create(nome, departamento, cpf, idade);
    if (buffer != NULL) {
        assert(strcmp(buffer->cpf, cpf) == 0);
        assert(strcmp(buffer->nome, nome) == 0);
        assert(strcmp(buffer->departamento, departamento) == 0);
        assert(buffer->idade == idade);
        assert(buffer->id == 0);

        printf("Criação de funcionário funcionando\n");
        printf("\tNome        : %s\n", buffer->nome);
        printf("\tDepartamento: %s\n", buffer->departamento);
        printf("\tCPF         : %s\n", buffer->cpf);
        printf("\tIdade       : %d\n", buffer->idade);
        printf("\tId          : %d\n", buffer->id);

    } else {
        perror("Falha na criação do Funcionário");
    }

    buffer = NULL;
    buffer = funcionario_get(cpf);
    if (buffer != NULL) {
        assert(strcmp(buffer->cpf, cpf) == 0);
        assert(strcmp(buffer->nome, nome) == 0);
        assert(strcmp(buffer->departamento, departamento) == 0);
        assert(buffer->idade == idade);
        assert(buffer->id == 0);

        printf("Recuperação de funcionário funcionando\n");
        printf("\tNome        : %s\n", buffer->nome);
        printf("\tDepartamento: %s\n", buffer->departamento);
        printf("\tCPF         : %s\n", buffer->cpf);
        printf("\tIdade       : %d\n", buffer->idade);
        printf("\tId          : %d\n", buffer->id);

    } else {
        perror("Falha na recuperação do Funcionário");
    }
}
