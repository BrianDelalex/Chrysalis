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

BINARY=chrysalis

PROJECT_ROOT_DIR=$(shell pwd)

TESTS_DIR = $(PROJECT_ROOT_DIR)/tests

SOURCE_DIRS =	$(PROJECT_ROOT_DIR)/src/tokenizer   \
				$(PROJECT_ROOT_DIR)/src/files       \
				$(PROJECT_ROOT_DIR)/src/utils       \
				$(PROJECT_ROOT_DIR)/src/parser      \
				$(PROJECT_ROOT_DIR)/src/parser/function \
				$(PROJECT_ROOT_DIR)/src/parser/statement    \
				$(PROJECT_ROOT_DIR)/src/parser/expression/	\
				$(PROJECT_ROOT_DIR)/src/generator   \

SOURCE_FILES = $(wildcard $(addsuffix /*.c, $(SOURCE_DIRS)))

INCLUDES = -I$(PROJECT_ROOT_DIR)/inc

ifeq ($(DEBUG),y)
	DEBCFLAGS = -g3 -Og
else
	DEBCFLAGS = -O2
endif

CFLAGS += $(DEBCFLAGS)
CFLAGS +=	-Wall						\
			-Wextra						\
			-Wpointer-arith				\
			-Werror						\
			-Wmissing-prototypes

TARGET=chrysalis

export

MAIN_SOURCE_FILES+=$(PROJECT_ROOT_DIR)/src/chrysalis.c

all: $(BINARY)

$(BINARY):
	@echo "CC $(DEBCFLAGS) $(BINARY)"
	@$(CC) $(CFLAGS) $(INCLUDES) $(MAIN_SOURCE_FILES) $(SOURCE_FILES) -o $(BINARY)

test:
	@make -C $(TESTS_DIR) tests

run_tests:
	@make -C $(TESTS_DIR) run_tests

clean:
	@$(RM) $(BINARY)
	@echo "Removing $(BINARY)."
	@make -C $(TESTS_DIR) clean
