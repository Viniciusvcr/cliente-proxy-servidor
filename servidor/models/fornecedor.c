#include "includes/fornecedor.h"

Fornecedor** fornecedor_init() {
    fornecedor_database = (Fornecedor**)malloc(sizeof(Fornecedor*)*MAX_FORNECEDORES);

    return fornecedor_database;
}

Fornecedor* fornecedor_create(char* nome_fantasia, char* cnpj, char* telefone) {
    static int ID = 0;
    Fornecedor* newFornecedor = (Fornecedor*)malloc(sizeof(Fornecedor));

    newFornecedor->nome_fantasia = (char*)malloc(sizeof(char) * strlen(nome_fantasia));
    newFornecedor->cnpj = (char*)malloc(sizeof(char) * strlen(cnpj));
    newFornecedor->telefone = (char*)malloc(sizeof(char) * strlen(telefone));

    strcpy(newFornecedor->nome_fantasia, nome_fantasia);
    strcpy(newFornecedor->cnpj, cnpj);
    strcpy(newFornecedor->telefone, telefone);
    newFornecedor->id = ID++;

    fornecedor_database[newFornecedor->id] = newFornecedor;

    return newFornecedor;
}

Fornecedor* fornecedor_get(char* cnpj) {
    for (int i = 0; i < MAX_FORNECEDORES; i++) {
        if (fornecedor_database[i] != NULL) {
            if (strcmp(fornecedor_database[i]->cnpj, cnpj) == 0) {
                return fornecedor_database[i];
            }
        } else return NULL;
    }

    return NULL;
}
