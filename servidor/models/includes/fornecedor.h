#ifndef FORNECEDOR_H
#define FORNECEDOR_H

#include <stdlib.h>
#include <string.h>

#define MAX_FORNECEDORES 10
#define MAX 50

typedef struct fornecedor {
    char* nome_fantasia;
    char* cnpj;
    char* telefone;
    unsigned int id;
}Fornecedor;

typedef struct forn_requisition {
    char nome_fantasia[MAX];
    char cnpj[MAX];
    char telefone[MAX];
}forn_req;

Fornecedor** fornecedor_init();
Fornecedor* fornecedor_create(char* nome_fantasia, char* cnpj, char* telefone);
Fornecedor* fornecedor_get(char* cnpj);

Fornecedor** fornecedor_database;

#endif