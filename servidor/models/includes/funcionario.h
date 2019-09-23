#ifndef FUNCIONARIO_H
#define FUNCIONARIO_H

#include <stdlib.h>
#include <string.h>

#define MAX_FUNCIONARIOS 100

typedef struct funcionario {
    char* nome;
    char* departamento;
    char* cpf;
    unsigned int idade;
    unsigned int id;
}Funcionario;

typedef struct func_requisition {
    Funcionario* func;
    unsigned int req_type;
}func_req;

Funcionario** funcionarios_init();
Funcionario* funcionario_create(char* nome, char* departamento, char* cpf, unsigned int idade);
Funcionario* funcionario_get(char* cpf);

Funcionario** funcionario_database;

#endif