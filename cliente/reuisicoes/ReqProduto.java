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
public class ReqProduto {
    private char[] nome;
    private int  qtdEstoque, reqMethod;
    private float valor;
    
    public ReqProduto(char[] nome, float valor, int qtdEstoque, int reqMethod) {
        this.nome = nome;
        this.valor = valor;
        this.qtdEstoque = qtdEstoque;
        this.reqMethod = reqMethod;
    }
    
    private ReqProduto(){
        
    }

    public char[] getNome() {
        return nome;
    }

    public void setNome(char[] nome) {
        this.nome = nome;
    }

    public float getValor() {
        return valor;
    }

    public void setValor(float valor) {
        this.valor = valor;
    }

    public int getQtdEstoque() {
        return qtdEstoque;
    }

    public void setQtdEstoque(int qtdEstoque) {
        this.qtdEstoque = qtdEstoque;
    }

    public int getReqMethod() {
        return reqMethod;
    }

    public void setReqMethod(int reqMethod) {
        this.reqMethod = reqMethod;
    }
    
    
}
