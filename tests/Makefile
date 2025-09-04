#########################################################################
#                                                                       #
#  This file is part of Chrysalis project, and is made available under  #
#  the terms of the GNU General Public License version 3.               #
#                                                                       #
#  Copyright (C) 2025 - Brian DELALEX-FONDU                             #
#                                                                       #
#########################################################################

UNITY_ROOT=$(PROJECT_ROOT_DIR)/Unity
INC_DIR=$(PROJECT_ROOT_DIR)/inc

TEST_COMPILE_SCRIPT=test_compile.sh
TEST_COMPILE_NO_MAIN_SCRIPT=test_compile_no_main.sh

# Stage 1 variables
TEST1_SOURCE_FILES = $(SOURCE_FILES)
TEST_STAGE1_DIR=stage1
TARGET_TEST_STAGE1=test_stage1
RUNNER_TEST_STAGE1=$(TEST_STAGE1_DIR)/test_stage1_runner.c
SRC_TEST_STAGE1=$(TEST1_SOURCE_FILES)
SRC_TEST_STAGE1+=$(UNITY_ROOT)/src/unity.c $(TEST_STAGE1_DIR)/test_stage1_runner.c $(TEST_STAGE1_DIR)/test_tokenizer.c
INC_TEST=$(INCLUDES) -I$(UNITY_ROOT)/src
STAGE1_PWD=$(shell pwd)/$(TEST_STAGE1_DIR)
STAGE1_CFLAGS=-D'STAGE1_DIR="$(STAGE1_PWD)"'
STAGE1_ASM_OUTPUT_DIR=$(TEST_STAGE1_DIR)/output_files/

all: clean test

test: $(RUNNER_TEST_STAGE1) $(TARGET_TEST_STAGE1)

run_tests: test
	./$(TARGET_TEST_STAGE1)
	@./$(TEST_COMPILE_SCRIPT) $(TEST_STAGE1_DIR) gen_main_return_0 0
	@./$(TEST_COMPILE_SCRIPT) $(TEST_STAGE1_DIR) gen_main_return_42 42
	@./$(TEST_COMPILE_NO_MAIN_SCRIPT) $(TEST_STAGE1_DIR) gen_no_main

$(RUNNER_TEST_STAGE1):
	@echo "ruby $(RUNNER_TEST_STAGE1)"
	@ruby $(UNITY_ROOT)/auto/generate_test_runner.rb $(TEST_STAGE1_DIR)/test_tokenizer.c $(RUNNER_TEST_STAGE1)

$(TARGET_TEST_STAGE1):
	@echo "CC $(TARGET_TEST_STAGE1)"
	@$(CC) $(CFLAGS) $(STAGE1_CFLAGS) $(INC_TEST) $(SRC_TEST_STAGE1) -o $(TARGET_TEST_STAGE1)

clean:
	@$(RM) $(TARGET_TEST_STAGE1) $(RUNNER_TEST_STAGE1)
	@echo "Removing $(TARGET_TEST_STAGE1) $(RUNNER_TEST_STAGE1)"
	@$(RM) $(STAGE1_ASM_OUTPUT_DIR)/*
	@echo "Removing asm files from $(STAGE1_ASM_OUTPUT_DIR)"
