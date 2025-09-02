UNITY_ROOT=../Unity
SRC_DIR=../src
INC_DIR=../inc

TEST_STAGE1_DIR=stage1
TARGET_TEST_STAGE1=test_stage1
RUNNER_TEST_STAGE1=$(TEST_STAGE1_DIR)/test_stage1_runner.c
SRC_TEST_STAGE1=$(UNITY_ROOT)/src/unity.c $(SRC_DIR)/tokenizer.c $(TEST_STAGE1_DIR)/test_stage1_runner.c $(TEST_STAGE1_DIR)/test_tokenizer.c
INC_TEST=-I$(INC_DIR) -I$(UNITY_ROOT)/src
all: clean test

test: $(RUNNER_TEST_STAGE1) $(TARGET_TEST_STAGE1)

run_tests: test
	./$(TARGET_TEST_STAGE1)

$(RUNNER_TEST_STAGE1):
	@echo "ruby $(RUNNER_TEST_STAGE1)"
	@ruby $(UNITY_ROOT)/auto/generate_test_runner.rb $(TEST_STAGE1_DIR)/test_tokenizer.c $(RUNNER_TEST_STAGE1)

$(TARGET_TEST_STAGE1):
	@echo "CC $(TARGET_TEST_STAGE1)"
	@$(CC) $(CFLAGS) $(INC_TEST) $(SRC_TEST_STAGE1) -o $(TARGET_TEST_STAGE1)

clean:
	@$(RM) $(TARGET_TEST_STAGE1) $(RUNNER_TEST_STAGE1)
	@echo "Removing $(TARGET_TEST_STAGE1) $(RUNNER_TEST_STAGE1)"
