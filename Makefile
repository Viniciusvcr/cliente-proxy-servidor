CC=gcc
MODELS=servidor/models
SRC_FUNCIONARIOS=servidor/models/funcionario.c
SERVER_FUNCIONARIOS=servidor/server_funcionario.c
EXEC_FUNCIONARIOS=server_funcionarios

TEST_MODEL=servidor/models/test
SRC_TEST_FUNCIONARIOS=$(TEST_MODEL)/test_funcionario.c

servers: 
	@$(CC) $(SRC_FUNCIONARIOS) $(SERVER_FUNCIONARIOS) -o $(EXEC_FUNCIONARIOS).out

test_funcionario:
	# touch $(SRC_FUNCIONARIOS) $(SRC_TEST_FUNCIONARIOS)
	@$(CC) $(SRC_FUNCIONARIOS) $(SRC_TEST_FUNCIONARIOS) -o $(TEST_MODEL)/test_funcionario.out

clean:
	rm -rf *.out $(TEST_MODEL)/*.out