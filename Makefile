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

SRC_TEST_FUNCIONARIOS=$(TEST)/test_funcionario.c
SRC_TEST_PRODUTO=$(TEST)/test_produto.c
SRC_TEST_FORNECEDOR=$(TEST)/test_fornecedor.c

servers: 
	@$(CC) $(SRC_FUNCIONARIOS) $(SERVER_FUNCIONARIOS) -o $(OUT)/$(EXEC_FUNCIONARIOS).out

test_model_funcionario:
	@$(CC) $(SRC_FUNCIONARIOS) $(SRC_TEST_FUNCIONARIOS) -o $(OUT)/test_model_funcionario.out

test_model_fornecedor:
	@$(CC) $(SRC_FORNECEDOR) $(SRC_TEST_FORNECEDOR) -o $(OUT)/test_model_fornecedor.out

test_model_produto:
	@$(CC) $(SRC_PRODUTO) $(SRC_TEST_PRODUTO) -o $(OUT)/test_model_produto.out

test_server_funcionario:
	@$(CC) $(TEST)/server_test.c $(SRC_FUNCIONARIOS) $(SERVER)/connector.c -o $(OUT)/test_server_funcionario.out

clean:
	rm -rf *.out $(OUT)/*.out