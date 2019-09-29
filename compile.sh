#!/bin/bash

DIR=$(pwd)

OUT_FOLDER="$DIR/out"

getHelp(){
    echo "Como usar: ./$0 {--servers | --proxy | --client | --tests | --clean}.
    -h: Este menu
    --servers: Compila os três servidores desta aplicação.
    --proxy: Compila o proxy desta aplicação
    --client: Compila o cliente desta aplicação
    --tests: Compila os testes desta aplicação
    --clean: Exclui todos os executáveis gerados na pasta '$OUT_FOLDER' por esta aplicação"
}

makedir(){
    if [ ! -d $1 ]; then
        mkdir $1
    fi
    cd $1
}

compileServers() {
    cd $DIR
    make servers
}

compileProxy() {
    cd $DIR
    make proxy
}

compileClient() {
    cd $DIR
    make client
}

compileTests() {
    cd $DIR
    make test_model_funcionario
    make test_model_fornecedor
    make test_model_produto
    make test_server_funcionario
    make test_server_fornecedor
    make test_server_produto
}

# Início
makedir $OUT_FOLDER
cd $DIR
while [[ "$1" =~ ^- && ! "$1" == "--" ]]; do
    case $1 in
        -h) getHelp;
        ;;

        --servers | -s) compileServers;
        ;;

        --proxy | -p) compileProxy;
        ;;

        --client | -c) compileClient;
        ;;

        --tests | -t) compileTests;
        ;;

        --clean) make clean;
        ;;
    esac; 
    cd $DIR;
    shift;
    
done
if [[ "$1" == '--' ]]; then shift; fi
