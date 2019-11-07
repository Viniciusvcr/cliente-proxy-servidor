# cliente-proxy-servidor

Repositório do trabalho de Sistemas Operacionais (UEM - 2019)

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

## Trabalho de Sistemas Operacionais

- Linguagens
    - Cliente: C
    - Proxy e Servidores: C

- Contexto
    - Sistema CRUD de um supermercado
        - Pode-se cadastrar e recuperar Funcionários do supermercado
        - Pode-se cadastrar e recuperar Produtos vendidos no supermercado
        - Pode-se cadastrar e recuperar os Fornecedores do supermercado
        - Cada um dos modelos (Funcionário, Produto e Fornecedor) serão armazenados em memória, e em servidores diferentes
        - Cada servidor usa um processo filho, criado por Fork para acessar sua base de dados
        - O modelo Funcionário usa Pipe
        - O modelo Produto usa Memória compartilhada e Semáforo
        - O modelo Fornecedor usa FIFO

- Desenvolvedores
    - [Caio Eduardo Kikuti Machado](https://github.com/Caiokikuti)
	- [Mateus Felipe Larrosa Furlan](https://github.com/furlanmateus)
	- [Vinícius da Costa Regatieri](https://github.com/Viniciusvcr)


## Compilação e Execução

### Compilação

- Para compilar servidores, cliente e proxy: `bash compile.sh -p -c -s`
- Os arquivos de saída estarão na pasta `/out`

### Execução

- Para executar os servidores:
    - `./out/server_fornecedores.out`
    - `./out/server_funcionarios.out`
    - `./out/server_produto.out`
- Como alternativa, execução em paralelo dos servidores:
    - `./out/server_fornecedores.out & ./out/server_funcionarios.out & ./out/server_produto.out`
- Para executar o proxy:
    - `./out/proxy.out`
- Para executar o cliente:
    - `./out/client.out`

- **OBS**: Para melhorar a visualização de cada módulo do trabalho, recomendamos que cada um dos servidores, proxy e cliente seja executado em um terminal diferente.
