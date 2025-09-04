#########################################################################
#                                                                       #
#  This file is part of Chrysalis project, and is made available under  #
#  the terms of the GNU General Public License version 3.               #
#                                                                       #
#  Copyright (C) 2025 - Brian DELALEX-FONDU                             #
#                                                                       #
#########################################################################

CC=gcc

RM=rm -rf

PROJECT_ROOT_DIR=$(shell pwd)

TESTS_DIR = $(PROJECT_ROOT_DIR)/tests

SOURCE_DIRS =   $(PROJECT_ROOT_DIR)/src           \
                $(PROJECT_ROOT_DIR)/src/tokenizer \
                $(PROJECT_ROOT_DIR)/src/files     \
                $(PROJECT_ROOT_DIR)/src/utils     \
                $(PROJECT_ROOT_DIR)/src/parser    \

SOURCE_FILES = $(wildcard $(addsuffix /*.c, $(SOURCE_DIRS)))

INCLUDES = -I$(PROJECT_ROOT_DIR)/inc

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
