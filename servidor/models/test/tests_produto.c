#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "../includes/produto.h"

int main(){
    char* nome = "Drogas";
    int valor, qtd;
    valor = 100;
    qtd = 200;

    produtos_init();
    Produto* buffer = NULL;

    buffer = produto_create(nome, valor, qtd);

    if(buffer != NULL){
        assert(strcmp(buffer->nome, nome) == 0);
        assert(buffer->valor == valor);
        assert(buffer->qdtEstoque == qtd);
        assert(buffer->id == 0);


        printf("Criacao do produto funcionando\n");
        printf("\tNome        : %s\n", buffer->nome);
        printf("\tValor        : %d\n", buffer->valor);
        printf("\tQuantidade em estoque        : %d\n", buffer->qdtEstoque);
        printf("\tID        : %d\n", buffer->id);
    }else{
        printf("Falha na criação de produtos\n");
    }
    //Tetste do getProduto
    buffer = NULL;

    buffer = produto_get(0);
    
    if(buffer != NULL){
        assert(strcmp(buffer->nome, nome) == 0);
        assert(buffer->valor == valor);
        assert(buffer->qdtEstoque == qtd);
        assert(buffer->id == 0);


        printf("Criacao do produto funcionando\n");
        printf("\tNome        : %s\n", buffer->nome);
        printf("\tValor        : %d\n", buffer->valor);
        printf("\tQuantidade em estoque        : %d\n", buffer->qdtEstoque);
        printf("\tID        : %d\n", buffer->id);
    }else{
        printf("Falha na criação de produtos\n");
    }

}