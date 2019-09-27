#include "../includes/fornecedor.h"

Fornecedor* fornecedor_init() {
    database = (Database*)malloc(sizeof(Database));
    memset(database, 0, sizeof(Database));
    database->last_id = 0;

    return database->db;
}

Fornecedor* fornecedor_create(char* nome_fantasia, char* cnpj, char* telefone) {
    Fornecedor newFornecedor;

    strcpy(newFornecedor.nome_fantasia, nome_fantasia);
    strcpy(newFornecedor.cnpj, cnpj);
    strcpy(newFornecedor.telefone, telefone);
    newFornecedor.id = database->last_id++;

    database->db[newFornecedor.id] = newFornecedor;

    return &database->db[newFornecedor.id];
}

Fornecedor* fornecedor_get(char* cnpj) {
    for (int i = 0; i < MAX_FORNECEDORES; i++) {
        if (strcmp(database->db[i].cnpj, cnpj) == 0) {
            return &database->db[i];
        }
    }

    return NULL;
}
