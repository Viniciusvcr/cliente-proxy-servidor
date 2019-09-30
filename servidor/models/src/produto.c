#include "../includes/produto.h"

Produto* produtos_init() {
    database_prod = (Database_prod*)malloc(sizeof(Database_prod));
    memset(database_prod, 0, sizeof(Database_prod));
    for (int i = 0; i < MAX_PRODUTOS; i++) {
        database_prod->db[i].id = -1;
    }
    database_prod->last_id = 0;

    return database_prod->db;
}

Produto* produto_create(char* nome, unsigned int valor, unsigned int qtdEstoque){
    Produto newProduto;

    strcpy(newProduto.nome, nome);
    newProduto.id = database_prod->last_id++;
    newProduto.qdtEstoque = qtdEstoque;
    newProduto.valor = valor;

    database_prod->db[newProduto.id] = newProduto;
    return &database_prod->db[newProduto.id];
}

Produto* produto_get(unsigned int id){
    for(int i = 0; i<MAX_PRODUTOS;i++){
        if(database_prod->db[i].id == id){
            return &database_prod->db[i];
        }
    }

    return NULL;
}