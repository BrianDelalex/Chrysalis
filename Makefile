CC=gcc

UNITY_ROOT=./Unity

CFLAGS =	-Wall						\
					-Wextra					\
					-Wpointer-arith	\
					-Werror

TARGET=chrysalis

TARGET_TEST_STAGE1=test_stage1
SRC_TEST_STAGE1=$(UNITY_ROOT)/src/unity.c src/tokenizer.c tests/stage1/test_stage1_runner.c tests/stage1/test_tokenizer.c
INC_TEST=-Iinc -I$(UNITY_ROOT)/src
all: test

test: $(SRC_TEST_STAGE1)
	$(CC) $(CFLAGS) $(INC_TEST) $(SRC_TEST_STAGE1) -o $(TARGET_TEST_STAGE1)

run_tests: test
	./$(TARGET_TEST_STAGE1)

tests/stage1/test_stage1_runner.c: tests/stage1/test_tokenizer.c
	ruby $(UNITY_ROOT)/auto/generate_test_runner.rb tests/stage1/test_tokenizer.c tests/stage1/test_stage1_runner.c

