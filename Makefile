CC=gcc

RM=rm -rf

TESTS_DIR = ./tests

CFLAGS =	-Wall						\
					-Wextra					\
					-Wpointer-arith	\
					-Werror

TARGET=chrysalis

all: test

test:
	@make -C $(TESTS_DIR) test

run_tests: test
	@make -C $(TESTS_DIR) run_tests

clean:
	@make -C $(TESTS_DIR) clean
