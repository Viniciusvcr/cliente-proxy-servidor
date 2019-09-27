CC=gcc
MODELS=servidor/models
SRC_FUNCIONARIOS=servidor/models/funcionario.c
SRC_PRODUTO=servidor/models/produto.c
SRC_FORNECEDOR=servidor/models/fornecedor.c
SERVER_FUNCIONARIOS=servidor/server_funcionario.c servidor/connector.c
EXEC_FUNCIONARIOS=server_funcionarios

TEST_MODEL=servidor/models/test
SRC_TEST_FUNCIONARIOS=$(TEST_MODEL)/test_funcionario.c
SRC_TEST_PRODUTO=$(TEST_MODEL)/test_produto.c
SRC_TEST_FORNECEDOR=$(TEST_MODEL)/test_fornecedor.c

servers: 
	@$(CC) $(SRC_FUNCIONARIOS) $(SERVER_FUNCIONARIOS) -o $(EXEC_FUNCIONARIOS).out

test_model_funcionario:
	@$(CC) $(SRC_FUNCIONARIOS) $(SRC_TEST_FUNCIONARIOS) -o test_model_funcionario.out

test_model_fornecedor:
	@$(CC) $(SRC_FORNECEDOR) $(SRC_TEST_FORNECEDOR) -o test_model_fornecedor.out

test_model_produto:
	@$(CC) $(SRC_PRODUTO) $(SRC_TEST_PRODUTO) -o test_model_produto.out

test_server_funcionario:
	@$(CC) $(TEST_MODEL)/server_test.c $(SRC_FUNCIONARIOS) -o test_server_funcionario.out

clean:
	rm -rf *.out $(TEST_MODEL)/*.out