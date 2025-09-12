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

BUILD_DIR=$(PROJECT_ROOT_DIR)/build

SOURCE_DIR=$(PROJECT_ROOT_DIR)/src

PROJECT_ROOT_DIR=$(shell pwd)

TESTS_DIR = $(PROJECT_ROOT_DIR)/tests

INCLUDES	:=	-I$(PROJECT_ROOT_DIR)/inc

SOURCE_DIRS :=	$(PROJECT_ROOT_DIR)/src/tokenizer	\
				$(PROJECT_ROOT_DIR)/src/files		\
				$(PROJECT_ROOT_DIR)/src/utils		\
				$(PROJECT_ROOT_DIR)/src/parser		\
				$(PROJECT_ROOT_DIR)/src/parser/function	\
				$(PROJECT_ROOT_DIR)/src/parser/statement	\
				$(PROJECT_ROOT_DIR)/src/parser/expression	\
				$(PROJECT_ROOT_DIR)/src/parser/types		\
				$(PROJECT_ROOT_DIR)/src/parser/stack		\
				$(PROJECT_ROOT_DIR)/src/parser/operation	\
				$(PROJECT_ROOT_DIR)/src/generator			\
				$(PROJECT_ROOT_DIR)/src/generator/stack		\
				$(PROJECT_ROOT_DIR)/src/generator/asm		\

SOURCE_FILES := $(wildcard $(addsuffix /*.c, $(SOURCE_DIRS)))

OBJECT_FILES := $(patsubst $(SOURCE_DIR)/%, $(BUILD_DIR)/%, $(patsubst %.c, %.o, $(SOURCE_FILES)))

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

MAIN_SOURCE_FILES+=$(SOURCE_DIR)/chrysalis.c
MAIN_OBJECT_FILES+=$(BUILD_DIR)/chrysalis.o

all: $(BINARY)

$(BINARY): $(OBJECT_FILES) $(MAIN_OBJECT_FILES)
	@echo "CC $(DEBCFLAGS) $(BINARY)"
	@$(CC) $(CFLAGS) $(INCLUDES) $(OBJECT_FILES) $(MAIN_OBJECT_FILES) -o $(BINARY)

test:
	@make -C $(TESTS_DIR) tests

run_tests:
	@make -C $(TESTS_DIR) run_tests

clean:
	@$(RM) $(BUILD_DIR)
	@echo "Removing $(BUILD_DIR)/."
	@$(RM) $(BINARY)
	@echo "Removing $(BINARY)."
	@make -C $(TESTS_DIR) clean

$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.c
	@mkdir -p $(shell dirname $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@echo "    CC $@"
