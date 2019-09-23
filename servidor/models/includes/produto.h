#ifndef PRODUTO_H
#define PRODUTO_H

#include <stdlib.h>
#include <string.h>

#define MAX_PRODUTOS 100
#define MAX 50

typedef struct produto {
    char* nome;
    unsigned int valor;
    unsigned int id;
    unsigned int qdtEstoque;
}Produto;

typedef struct func_requisition {
    char nome[MAX];
    unsigned int valor;
    unsigned int id;
    unsigned int qtdEstoque;
    unsigned int req_type;
}func_req;

Produto** produtos_init();
Produto* produto_create(char* nome,unsigned int valor, unsigned int qtdEstoque);
Produto* produto_get(unsigned int id);

Produto** produto_database;

#endif