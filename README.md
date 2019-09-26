# cliente-proxy-servidor

Repositório do trabalho de Sistemas Operacionais (UEM - 2019)

## Trabalho de Sistemas Operacionais

- Linguagens
    - Cliente: Java
    - Proxy e Servidores: C

- Contexto
    - Sistema CRUD de um supermercado
        - Pode-se cadastrar e recuperar Funcionários do supermercado
        - Pode-se cadastrar e recuperar Produtos vendidos no supermercado
        - Pode-se recuperar os Fornecedores do supermercado
        - Cada um dos modelos (Funcionário, Produto e Fornecedor) serão armazenados em memória, e em servidores diferentes
        - Cada servidor usará um processo filho, criado por Fork para acessar sua base de dados
        - O modelo Funcionário usará Pipe e semáforo
        - O modelo Produto usará Memória compartilhada
        - O modelo Fornecedor usará FIFO e Semáforo

- Desenvolvedores
    - [Caio Eduardo Kikuti Machado](https://github.com/Caiokikuti)
	- [Mateus Felipe Larrosa Furlan](https://github.com/furlanmateus)
	- [Vinícius da Costa Regatieri](https://github.com/Viniciusvcr)
