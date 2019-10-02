package Modelos;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author caio
 */
public class Funcionario {
    private int id, idade;
    private char[] nome, departamento, cpf;

    public Funcionario(int id, int idade, char[] nome, char[] departamento, char[] cpf) {
        this.id = id;
        this.idade = idade;
        this.nome = nome;
        this.departamento = departamento;
        this.cpf = cpf;
    }
    
    public Funcionario(){
        
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public int getIdade() {
        return idade;
    }

    public void setIdade(int idade) {
        this.idade = idade;
    }

    public char[] getNome() {
        return nome;
    }

    public void setNome(char[] nome) {
        this.nome = nome;
    }

    public char[] getDepartamento() {
        return departamento;
    }

    public void setDepartamento(char[] departamento) {
        this.departamento = departamento;
    }

    public char[] getCpf() {
        return cpf;
    }

    public void setCpf(char[] cpf) {
        this.cpf = cpf;
    }
    
    
}
