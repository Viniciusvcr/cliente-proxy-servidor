#ifndef FUNCIONARIO_H
#define FUNCIONARIO_H

#include <stdlib.h>
#include <string.h>

#define MAX_FUNCIONARIOS 100
#define STR_MAX 50

typedef struct funcionario {
    char nome[STR_MAX];
    char departamento[STR_MAX];
    char cpf[STR_MAX];
    unsigned int idade;
    unsigned int id;
}Funcionario;

typedef struct func_database {
    Funcionario db[MAX_FUNCIONARIOS];
    unsigned int last_id;
}Database_func;

typedef struct func_requisition {
    char nome[STR_MAX];
    char departamento[STR_MAX];
    char cpf[STR_MAX];
    unsigned int idade;
    unsigned int req_method;
}func_req;

typedef struct func_response {
    Funcionario response_model;
    unsigned int status;
    char error_message[STR_MAX];
}func_res;

Funcionario* funcionarios_init();
Funcionario* funcionario_create(char* nome, char* departamento, char* cpf, unsigned int idade);
Funcionario* funcionario_get(char* cpf);

Database_func* database_func;

#endif