#include "../includes/funcionario.h"

Funcionario* funcionarios_init() {
    database = (Database*)malloc(sizeof(Database));
    memset(database, 0, sizeof(Database));
    database->last_id = 0;

    return database->db;
}

Funcionario* funcionario_create(char* nome, char* departamento, char* cpf, unsigned int idade) {
    Funcionario newFuncionario;
    
    strcpy(newFuncionario.nome, nome);
    strcpy(newFuncionario.departamento, departamento);
    strcpy(newFuncionario.cpf, cpf);
    newFuncionario.idade = idade;
    newFuncionario.id = database->last_id++;

    database->db[newFuncionario.id] = newFuncionario;

    return &database->db[newFuncionario.id];
}

Funcionario* funcionario_get(char* cpf) {
    for (int i = 0; i < MAX_FUNCIONARIOS; i++) {
        if (strcmp(database->db[i].cpf, cpf) == 0) {
            return &database->db[i];
        }
    }

    return NULL;
}