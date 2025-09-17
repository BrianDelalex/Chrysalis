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

UNITY_C=$(UNITY_ROOT)/src/unity.c
INC_TEST=$(INCLUDES) -I$(UNITY_ROOT)/src
UNITY_GENERATE_RB=$(UNITY_ROOT)/auto/generate_test_runner.rb

# Stage 1 variables
TEST_STAGE1_DIR=stage1
TARGET_TEST_STAGE1=test_stage1
RUNNER_TEST_STAGE1=$(TEST_STAGE1_DIR)/test_stage1_runner.c
SRC_TEST_STAGE1=$(SOURCE_FILES)
SRC_TEST_STAGE1+=$(UNITY_C) $(RUNNER_TEST_STAGE1) $(TEST_STAGE1_DIR)/test_tokenizer.c
STAGE1_PWD=$(shell pwd)/$(TEST_STAGE1_DIR)
STAGE1_CFLAGS=-D'STAGE1_DIR="$(STAGE1_PWD)"'
STAGE1_CFLAGS+=$(CFLAGS)
STAGE1_ASM_OUTPUT_DIR=$(TEST_STAGE1_DIR)/output_files/

# Stage 2 variables
TEST_STAGE2_DIR=stage2
TARGET_TEST_STAGE2=test_stage2
RUNNER_TEST_STAGE2=$(TEST_STAGE2_DIR)/test_stage2_runner.c
SRC_TEST_STAGE2=$(SOURCE_FILES)
SRC_TEST_STAGE2+=$(UNITY_C) $(RUNNER_TEST_STAGE2) $(TEST_STAGE2_DIR)/test_stage2.c
STAGE2_CFLAGS=-D'STAGE2_DIR="$(shell pwd)/$(TEST_STAGE2_DIR)"'
STAGE2_CFLAGS+=$(CFLAGS)
STAGE2_ASM_OUTPUT_DIR=$(TEST_STAGE2_DIR)/output_files/

# Stage 3 variables
TEST_STAGE3_DIR=stage3
TARGET_TEST_STAGE3=test_stage3
RUNNER_TEST_STAGE3=$(TEST_STAGE3_DIR)/test_stage3_runner.c
SRC_TEST_STAGE3=$(SOURCE_FILES)
SRC_TEST_STAGE3+=$(UNITY_C) $(RUNNER_TEST_STAGE3) $(TEST_STAGE3_DIR)/test_stage3.c
STAGE3_CFLAGS=-D'STAGE3_DIR="$(shell pwd)/$(TEST_STAGE3_DIR)"'
STAGE3_CFLAGS+=$(CFLAGS)
STAGE3_ASM_OUTPUT_DIR=$(TEST_STAGE3_DIR)/output_files/

# Stage 4 variables
TEST_STAGE4_DIR=stage4
TARGET_TEST_STAGE4=test_stage4
RUNNER_TEST_STAGE4=$(TEST_STAGE4_DIR)/test_stage4_runner.c
SRC_TEST_STAGE4=$(SOURCE_FILES)
SRC_TEST_STAGE4+=$(UNITY_C) $(RUNNER_TEST_STAGE4) $(TEST_STAGE4_DIR)/test_stage4.c
STAGE4_CFLAGS=-D'STAGE4_DIR="$(shell pwd)/$(TEST_STAGE4_DIR)"'
STAGE4_CFLAGS+=$(CFLAGS)
STAGE4_ASM_OUTPUT_DIR=$(TEST_STAGE4_DIR)/output_files/

all: clean tests

tests: $(TARGET_TEST_STAGE1) $(TARGET_TEST_STAGE2) $(TARGET_TEST_STAGE3) $(TARGET_TEST_STAGE4)

run_tests: $(TARGET_TEST_STAGE1) $(TARGET_TEST_STAGE2) $(TARGET_TEST_STAGE3) $(TARGET_TEST_STAGE4)
	@echo -e "\n#### Running Stage 1 test suite ####"
	./$(TARGET_TEST_STAGE1)
	@echo -e "\n#### Running Stage 2 test suite ####"
	./$(TARGET_TEST_STAGE2)
	@echo -e "\n#### Running Stage 3 test suite ####"
	./$(TARGET_TEST_STAGE3)
	@echo -e "\n#### Running Stage 4 test suite ####"
	./$(TARGET_TEST_STAGE4)

clean:
	@$(RM) $(TARGET_TEST_STAGE1) $(RUNNER_TEST_STAGE1) $(TARGET_TEST_STAGE2) $(RUNNER_TEST_STAGE2) $(TARGET_TEST_STAGE3) $(RUNNER_TEST_STAGE3) $(TARGET_TEST_STAGE4) $(RUNNER_TEST_STAGE4)
	@echo "Removing tests binaries and runners."
	@$(RM) $(STAGE1_ASM_OUTPUT_DIR)/* $(STAGE2_ASM_OUTPUT_DIR)/* $(STAGE3_ASM_OUTPUT_DIR)/*
	@echo "Removing asm files from tests output directories."

# Stage 4 recipes
$(TARGET_TEST_STAGE4): $(RUNNER_TEST_STAGE4)

$(RUNNER_TEST_STAGE4):
	@echo "ruby $(RUNNER_TEST_STAGE4)"
	@ruby $(UNITY_GENERATE_RB) $(TEST_STAGE4_DIR)/test_stage4.c $(RUNNER_TEST_STAGE4)

$(TARGET_TEST_STAGE4):
	@echo "CC $(TARGET_TEST_STAGE4)"
	@$(CC) $(STAGE4_CFLAGS) $(INC_TEST) $(SRC_TEST_STAGE4) -o $(TARGET_TEST_STAGE4)

# Stage 3 recipes
$(TARGET_TEST_STAGE3): $(RUNNER_TEST_STAGE3)

$(RUNNER_TEST_STAGE3):
	@echo "ruby $(RUNNER_TEST_STAGE3)"
	@ruby $(UNITY_GENERATE_RB) $(TEST_STAGE3_DIR)/test_stage3.c $(RUNNER_TEST_STAGE3)

$(TARGET_TEST_STAGE3):
	@echo "CC $(TARGET_TEST_STAGE3)"
	@$(CC) $(STAGE3_CFLAGS) $(INC_TEST) $(SRC_TEST_STAGE3) -o $(TARGET_TEST_STAGE3)

# Stage 2 recipes
$(TARGET_TEST_STAGE2): $(RUNNER_TEST_STAGE2)

$(RUNNER_TEST_STAGE2):
	@echo "ruby $(RUNNER_TEST_STAGE2)"
	@ruby $(UNITY_GENERATE_RB) $(TEST_STAGE2_DIR)/test_stage2.c $(RUNNER_TEST_STAGE2)

$(TARGET_TEST_STAGE2):
	@echo "CC $(TARGET_TEST_STAGE2)"
	@$(CC) $(STAGE2_CFLAGS) $(INC_TEST) $(SRC_TEST_STAGE2) -o $(TARGET_TEST_STAGE2)

# Stage 1 recipes
$(TARGET_TEST_STAGE1): $(RUNNER_TEST_STAGE1)

$(RUNNER_TEST_STAGE1):
	@echo "ruby $(RUNNER_TEST_STAGE1)"
	@ruby $(UNITY_GENERATE_RB) $(TEST_STAGE1_DIR)/test_tokenizer.c $(RUNNER_TEST_STAGE1)

$(TARGET_TEST_STAGE1):
	@echo "CC $(TARGET_TEST_STAGE1)"
	@$(CC) $(STAGE1_CFLAGS) $(INC_TEST) $(SRC_TEST_STAGE1) -o $(TARGET_TEST_STAGE1)
