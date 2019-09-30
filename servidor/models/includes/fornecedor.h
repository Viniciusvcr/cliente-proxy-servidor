#ifndef FORNECEDOR_H
#define FORNECEDOR_H

#include <stdlib.h>
#include <string.h>

#define MAX_FORNECEDORES 10
#define STR_MAX 50

typedef struct fornecedor {
    char nome_fantasia[STR_MAX];
    char cnpj[STR_MAX];
    char telefone[STR_MAX];
    unsigned int id;
}Fornecedor;

typedef struct forn_database {
    Fornecedor db[MAX_FORNECEDORES];
    unsigned int last_id;
}Database_forn;

typedef struct forn_requisition {
    char nome_fantasia[STR_MAX];
    char cnpj[STR_MAX];
    char telefone[STR_MAX];
    unsigned int req_method;
}forn_req;

typedef struct forn_response {
    Fornecedor response_model;
    unsigned int status;
    char error_message[STR_MAX];
}forn_res;

Fornecedor* fornecedor_init();
Fornecedor* fornecedor_create(char* nome_fantasia, char* cnpj, char* telefone);
Fornecedor* fornecedor_get(char* cnpj);

Database_forn* database_forn;

#endif