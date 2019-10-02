/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package resposta;
import Modelos.Produto;

public class RespProduto {
    private Produto responseModel;
    private int status;
    private String errorMessage;

    public RespProduto(Produto responseModel, int status, String errorMessage) {
        this.responseModel = responseModel;
        this.status = status;
        this.errorMessage = errorMessage;
    }
    
    public RespProduto(){
        
    }
    
    public Produto getResponseModel() {
        return responseModel;
    }

    public void setResponseModel(Produto responseModel) {
        this.responseModel = responseModel;
    }

    public int getStatus() {
        return status;
    }

    public void setStatus(int status) {
        this.status = status;
    }

    public String getErrorMessage() {
        return errorMessage;
    }

    public void setErrorMessage(String errorMessage) {
        this.errorMessage = errorMessage;
    }
    
    
}
