/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package resposta;
import Modelos.Fornecedor;
/**
 *
 * @author caio
 */
public class RespFornecedor {
    private Fornecedor responseModel;
    private int status;
    String errorMessage;

    public RespFornecedor(Fornecedor responseModel, int status, String errorMessage) {
        this.responseModel = responseModel;
        this.status = status;
        this.errorMessage = errorMessage;
    }
    
    public RespFornecedor(){
        
    }

    public Fornecedor getResponseModel() {
        return responseModel;
    }

    public void setResponseModel(Fornecedor responseModel) {
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
