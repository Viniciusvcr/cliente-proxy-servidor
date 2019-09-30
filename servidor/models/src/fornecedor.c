#include "../includes/fornecedor.h"

Fornecedor* fornecedor_init() {
    database_forn = (Database_forn*)malloc(sizeof(Database_forn));
    memset(database_forn, 0, sizeof(Database_forn));
    database_forn->last_id = 0;

    return database_forn->db;
}

Fornecedor* fornecedor_create(char* nome_fantasia, char* cnpj, char* telefone) {
    Fornecedor newFornecedor;

    strcpy(newFornecedor.nome_fantasia, nome_fantasia);
    strcpy(newFornecedor.cnpj, cnpj);
    strcpy(newFornecedor.telefone, telefone);
    newFornecedor.id = database_forn->last_id++;

    database_forn->db[newFornecedor.id] = newFornecedor;

    return &database_forn->db[newFornecedor.id];
}

Fornecedor* fornecedor_get(char* cnpj) {
    for (int i = 0; i < MAX_FORNECEDORES; i++) {
        if (strcmp(database_forn->db[i].cnpj, cnpj) == 0) {
            return &database_forn->db[i];
        }
    }

    return NULL;
}
