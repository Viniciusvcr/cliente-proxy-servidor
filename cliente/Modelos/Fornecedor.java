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
public class Fornecedor {
    private char[] nome;
    private char[] cnpj;
    private char[] telefone;
    private int id;

    public Fornecedor(int id) {
        this.nome = new char[50];
        this.cnpj = new char[50];
        this.telefone = new char[50];
        this.id = id;
    }
    

    public char[] getNome() {
        return nome;
    }

    public void setNome(char[] nome) {
        this.nome = nome;
    }

    public char[] getCnpj() {
        return cnpj;
    }

    public void setCpnj(char[] cpnj) {
        this.cnpj = cpnj;
    }

    public char[] getTelefone() {
        return telefone;
    }

    public void setTelefone(char[] telefone) {
        this.telefone = telefone;
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }
    
   
    
}
