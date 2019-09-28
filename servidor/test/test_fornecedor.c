#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "../models/includes/fornecedor.h"

int main() {
    char* nome_fantasia = "Frangos Canção";
    char* cnpj = "18825877000187";
    char* telefone = "30246969";

    fornecedor_init();
    Fornecedor* buffer = NULL;

    buffer = fornecedor_create(nome_fantasia, cnpj, telefone);
    if (buffer != NULL) {
        assert(strcmp(buffer->nome_fantasia, nome_fantasia) == 0);
        assert(strcmp(buffer->cnpj, cnpj) == 0);
        assert(strcmp(buffer->telefone, telefone) == 0);
        assert(buffer->id == 0);

        printf("Criação de fornecedor funcionando\n");
        printf("\tNome Fantasia: %s\n", buffer->nome_fantasia);
        printf("\tCNPJ         : %s\n", buffer->cnpj);
        printf("\tTelefone     : %s\n", buffer->telefone);
        printf("\tID           : %d\n", buffer->id);

    } else {
        perror("Falha na criação do Fornecedor");
    }

    buffer = NULL;
    buffer = fornecedor_get(cnpj);
    if (buffer != NULL) {
        assert(strcmp(buffer->nome_fantasia, nome_fantasia) == 0);
        assert(strcmp(buffer->cnpj, cnpj) == 0);
        assert(strcmp(buffer->telefone, telefone) == 0);
        assert(buffer->id == 0);

        printf("Recuperação de fornecedor funcionando\n");
        printf("\tNome Fantasia: %s\n", buffer->nome_fantasia);
        printf("\tCNPJ         : %s\n", buffer->cnpj);
        printf("\tTelefone     : %s\n", buffer->telefone);
        printf("\tID           : %d\n", buffer->id);
    
    } else {
        perror("Falha na recuperação do Fornecedor");
    }
}