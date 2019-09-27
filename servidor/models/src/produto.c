#include "../includes/produto.h"

Produto* produtos_init(){
    database = (Database*)malloc(sizeof(Database));
    memset(database, 0, sizeof(Database));
    database->last_id = 0;

    return database->db;
}

Produto* produto_create(char* nome,unsigned int valor, unsigned int qtdEstoque){
    Produto newProduto;

    strcpy(newProduto.nome, nome);
    newProduto.id = database->last_id++;
    newProduto.qdtEstoque = qtdEstoque;
    newProduto.valor = valor;

    database->db[newProduto.id] = newProduto;
    return &database->db[newProduto.id];
}

Produto* produto_get(unsigned int id){
    for(int i = 0; i<MAX_PRODUTOS;i++){
        if(database->db[i].id == id){
            return &database->db[i];
        }
    }

    return NULL;
}