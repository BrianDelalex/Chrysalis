CC=gcc

RM=rm -rf

TESTS_DIR = ./tests

SOURCE_DIRS =   ./src           \
                ./src/tokenizer \
                ./src/files     \
                ./src/utils     \

SOURCE_FILES = $(wildcard $(addsuffix /*.c, $(SOURCE_DIRS)))

CFLAGS =	-Wall                       \
			-Wextra                     \
			-Wpointer-arith	            \
			-Werror                     \

TARGET=chrysalis

export

all: test

test:
	@make -C $(TESTS_DIR) test

run_tests: test
	@make -C $(TESTS_DIR) run_tests

clean:
	@make -C $(TESTS_DIR) clean
