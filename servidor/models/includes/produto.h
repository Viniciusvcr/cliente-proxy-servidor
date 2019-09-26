#ifndef PRODUTO_H
#define PRODUTO_H

#include <stdlib.h>
#include <string.h>

#define MAX_PRODUTOS 100
#define STR_MAX 50

typedef struct produto {
    char nome[STR_MAX];
    unsigned int valor;
    unsigned int qdtEstoque;
    unsigned int id;
}Produto;

typedef struct prod_database {
    Produto db[MAX_PRODUTOS];
    unsigned int last_id;
}Database;

typedef struct prod_requisition {
    char nome[STR_MAX];
    unsigned int valor;
    unsigned int qtdEstoque;
    unsigned int req_method;
}prod_req;

typedef struct prod_response {
    Produto response_model;
    unsigned int status;
    char error_message[STR_MAX];
}prod_res;

Produto* produtos_init();
Produto* produto_create(char* nome,unsigned int valor, unsigned int qtdEstoque);
Produto* produto_get(unsigned int id);

Database* database;

#endif