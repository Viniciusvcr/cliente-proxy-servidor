#include "includes/funcionario.h"

Funcionario** funcionarios_init() {
    funcionario_database = (Funcionario**)malloc(sizeof(Funcionario*)*MAX_FUNCIONARIOS);

    return funcionario_database;
}

Funcionario* funcionario_create(char* nome, char* departamento, char* cpf, unsigned int idade) {
    static int ID = 0;
    Funcionario* newFuncionario = (Funcionario*)malloc(sizeof(Funcionario));

    strcpy(newFuncionario->nome, nome);
    strcpy(newFuncionario->departamento, departamento);
    strcpy(newFuncionario->cpf, cpf);
    newFuncionario->idade = idade;
    newFuncionario->id = ID++;

    funcionario_database[newFuncionario->id] = newFuncionario;

    return newFuncionario;
}

Funcionario* funcionario_get(char* cpf) {
    for (int i = 0; i < MAX_FUNCIONARIOS; i++) {
        if (funcionario_database[i] != NULL) {
            if (strcmp(funcionario_database[i]->cpf, cpf) == 0) {
                return funcionario_database[i];
            }
        } else return NULL;
    }

    return NULL;
}