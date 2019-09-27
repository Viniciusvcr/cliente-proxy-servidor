CC=gcc
OUT=out

MODELS=servidor/models/src
SERVER=servidor/src
TEST=servidor/test

SRC_FUNCIONARIOS=$(MODELS)/funcionario.c
SRC_PRODUTO=$(MODELS)/produto.c
SRC_FORNECEDOR=$(MODELS)/fornecedor.c

SERVER_FUNCIONARIOS=$(SERVER)/server_funcionario.c $(SERVER)/connector.c
EXEC_FUNCIONARIOS=server_funcionarios
SERVER_PRODUTO=$(SERVER)/server_produto.c $(SERVER)/connector.c
EXEC_PRODUTO=server_produto

SERVER_FORNECEDORES=$(SERVER)/server_fornecedor.c $(SERVER)/connector.c

SRC_TEST_FUNCIONARIOS=$(TEST)/test_funcionario.c
SRC_TEST_PRODUTO=$(TEST)/test_produto.c
SRC_TEST_FORNECEDOR=$(TEST)/test_fornecedor.c

servers: 
	@$(CC) $(SRC_FUNCIONARIOS) $(SERVER_FUNCIONARIOS) -o $(OUT)/$(EXEC_FUNCIONARIOS).out
	@$(CC) $(SRC_FORNECEDOR) $(SERVER_FORNECEDORES) -o $(OUT)/server_fornecedores.out
	@$(CC) $(SRC_PRODUTO) $(SERVER_PRODUTO) -o $(OUT)/$(EXEC_PRODUTO).out

test_model_funcionario:
	@$(CC) $(SRC_FUNCIONARIOS) $(SRC_TEST_FUNCIONARIOS) -o $(OUT)/test_model_funcionario.out

test_model_fornecedor:
	@$(CC) $(SRC_FORNECEDOR) $(SRC_TEST_FORNECEDOR) -o $(OUT)/test_model_fornecedor.out

test_model_produto:
	@$(CC) $(SRC_PRODUTO) $(SRC_TEST_PRODUTO) -o $(OUT)/test_model_produto.out

test_server_funcionario:
	@$(CC) $(TEST)/server_test.c $(SRC_FUNCIONARIOS) $(SERVER)/connector.c -o $(OUT)/test_server_funcionario.out

test_server_fornecedor:
	@$(CC) $(TEST)/server_fornecedor_test.c $(SRC_FORNECEDOR) $(SERVER)/connector.c -o $(OUT)/test_server_fornecedor.out

test_server_produto:
	@$(CC) $(TEST)/produto_server_test.c $(SRC_PRODUTO) $(SERVER)/connector.c -o $(OUT)/test_server_produto.out

clean:
	rm -rf *.out $(OUT)/*.out