package Modelos;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
import java.util.Scanner;
/**
 *
 * @author caio
 */
public class Main {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        int id =1;
        char [] nome = new char[50];
        
        nome [1] = input.next().charAt(0);
        
        
        Fornecedor f1 = new Fornecedor(id);
        
//        f1.setNome();
        
    }
   
}
