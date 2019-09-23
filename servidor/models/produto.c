#include "includes/produto.h"

Produto** produtos_init(){
    produto_database = (Produto**)malloc(sizeof(Produto*)*MAX_PRODUTOS);
    return produto_database;
}

Produto* produto_create(char* nome,unsigned int valor, unsigned int qtdEstoque){
    static int ID = 0;
    Produto* newProduto = (Produto*)malloc(sizeof(Produto));
    newProduto->nome = (char*)malloc(sizeof(char) * strlen(nome));
    strcpy(newProduto->nome, nome);
    newProduto->id = ID++;
    newProduto->qdtEstoque = qtdEstoque;
    newProduto->valor = valor;

    produto_database[newProduto->id] = newProduto;
    return newProduto;
}

Produto* produto_get(unsigned int id){
    for(int i = 0; i<MAX_PRODUTOS;i++){
        if(produto_database[i] != NULL){
            if(produto_database[i]->id == id){
                return produto_database[i];
            }
        }else return NULL;
    }
    return NULL;
}