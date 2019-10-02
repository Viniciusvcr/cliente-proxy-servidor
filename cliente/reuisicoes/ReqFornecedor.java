
package reuisicoes;


public class ReqFornecedor {
    private char[] nomeFantasia;
    private char[] cnpj;
    private char[] telefone;
    private int reqMetod;

    public ReqFornecedor(char[] nomeFantasia, char[] cnpj, char[] telefone, int reqMetod) {
        this.nomeFantasia = nomeFantasia;
        this.cnpj = cnpj;
        this.telefone = telefone;
        this.reqMetod = reqMetod;
    }
    
    public ReqFornecedor(){
        
    }

    public char[] getNomeFantasia() {
        return nomeFantasia;
    }

    public void setNomeFantasia(char[] nomeFantasia) {
        this.nomeFantasia = nomeFantasia;
    }

    public char[] getCnpj() {
        return cnpj;
    }

    public void setCnpj(char[] cnpj) {
        this.cnpj = cnpj;
    }

    public char[] getTelefone() {
        return telefone;
    }

    public void setTelefone(char[] telefone) {
        this.telefone = telefone;
    }

    public int getReqMetod() {
        return reqMetod;
    }

    public void setReqMetod(int reqMetod) {
        this.reqMetod = reqMetod;
    }
    
    
}
