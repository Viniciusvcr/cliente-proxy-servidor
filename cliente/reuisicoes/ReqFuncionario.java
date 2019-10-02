/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package reuisicoes;

/**
 *
 * @author caio
 */
public class ReqFuncionario {
    private char[] nome, departamento, cpf;
    private int idade, reqMethod;

    public ReqFuncionario(char[] nome, char[] departamento, char[] cpf, int idade, int reqMethod) {
        this.nome = nome;
        this.departamento = departamento;
        this.cpf = cpf;
        this.idade = idade;
        this.reqMethod = reqMethod;
    }
    
    public ReqFuncionario(){
        
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

    public int getIdade() {
        return idade;
    }

    public void setIdade(int idade) {
        this.idade = idade;
    }

    public int getReqMethod() {
        return reqMethod;
    }

    public void setReqMethod(int reqMethod) {
        this.reqMethod = reqMethod;
    }
    
    
}
