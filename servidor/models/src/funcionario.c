#include "../includes/funcionario.h"

Funcionario* funcionarios_init() {
    database_func = (Database_func*)malloc(sizeof(Database_func));
    memset(database_func, 0, sizeof(Database_func));
    database_func->last_id = 0;

    return database_func->db;
}

Funcionario* funcionario_create(char* nome, char* departamento, char* cpf, unsigned int idade) {
    Funcionario newFuncionario;
    
    strcpy(newFuncionario.nome, nome);
    strcpy(newFuncionario.departamento, departamento);
    strcpy(newFuncionario.cpf, cpf);
    newFuncionario.idade = idade;
    newFuncionario.id = database_func->last_id++;

    database_func->db[newFuncionario.id] = newFuncionario;

    return &database_func->db[newFuncionario.id];
}

Funcionario* funcionario_get(char* cpf) {
    for (int i = 0; i < MAX_FUNCIONARIOS; i++) {
        if (strcmp(database_func->db[i].cpf, cpf) == 0) {
            return &database_func->db[i];
        }
    }

    return NULL;
}