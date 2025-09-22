/*******************************************************************\
**
**  This file is part of Chrysalis project, and is made available
**  under the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

# include "unity.h"

# include <stdlib.h>

# include "stage4.h"

# include "tokenizer/tokenizer.h"
# include "parser/parser.h"
# include "generator/generator.h"

# include "files/files.h"

token_list_t *open_file_and_tokenize(const char* filepath);
token_list_t *open_file_and_tokenize(const char* filepath)
{
    char* file = read_file(filepath);
    TEST_ASSERT_NOT_NULL(file);
    token_list_t* tokens = tokenizer(file);
    free(file);
    return tokens;
}

void test_all_func_no_arg(void);
void test_all_func_no_arg(void)
{
    token_list_t* tokens = open_file_and_tokenize(SOURCE_FILES("func_no_arg.c"));
    TEST_ASSERT_NOT_NULL(tokens);
    ast_program_t* prg = create_ast_struct(tokens);
    TEST_ASSERT_NOT_NULL(prg);
    generator(prg, OUTPUT_ASM_FILE("gen_func_no_arg.asm"));
    token_list_free(tokens);
}

void test_all_return_func_no_arg(void);
void test_all_return_func_no_arg(void)
{
    token_list_t* tokens = open_file_and_tokenize(SOURCE_FILES("return_func_no_arg.c"));
    TEST_ASSERT_NOT_NULL(tokens);
    ast_program_t* prg = create_ast_struct(tokens);
    TEST_ASSERT_NOT_NULL(prg);
    generator(prg, OUTPUT_ASM_FILE("gen_return_func_no_arg.asm"));
    token_list_free(tokens);
}

void test_all_func_add(void);
void test_all_func_add(void)
{
    token_list_t* tokens = open_file_and_tokenize(SOURCE_FILES("func_add.c"));
    TEST_ASSERT_NOT_NULL(tokens);
    ast_program_t* prg = create_ast_struct(tokens);
    TEST_ASSERT_NOT_NULL(prg);
    generator(prg, OUTPUT_ASM_FILE("gen_func_add.asm"));
    token_list_free(tokens);
}

void test_all_return_func_add(void);
void test_all_return_func_add(void)
{
    token_list_t* tokens = open_file_and_tokenize(SOURCE_FILES("return_func_add.c"));
    TEST_ASSERT_NOT_NULL(tokens);
    ast_program_t* prg = create_ast_struct(tokens);
    TEST_ASSERT_NOT_NULL(prg);
    generator(prg, OUTPUT_ASM_FILE("gen_return_func_add.asm"));
    token_list_free(tokens);
}

void test_all_func_add_identifier(void);
void test_all_func_add_identifier(void)
{
    token_list_t* tokens = open_file_and_tokenize(SOURCE_FILES("func_add_identifier.c"));
    TEST_ASSERT_NOT_NULL(tokens);
    ast_program_t* prg = create_ast_struct(tokens);
    TEST_ASSERT_NOT_NULL(prg);
    generator(prg, OUTPUT_ASM_FILE("gen_func_add_identifier.asm"));
    token_list_free(tokens);
}

void test_all_func_add_operation(void);
void test_all_func_add_operation(void)
{
    token_list_t* tokens = open_file_and_tokenize(SOURCE_FILES("func_add_operation.c"));
    TEST_ASSERT_NOT_NULL(tokens);
    ast_program_t* prg = create_ast_struct(tokens);
    TEST_ASSERT_NOT_NULL(prg);
    generator(prg, OUTPUT_ASM_FILE("gen_func_add_operation.asm"));
    token_list_free(tokens);
}

void test_all_func_add_operation_identifier(void);
void test_all_func_add_operation_identifier(void)
{
    token_list_t* tokens = open_file_and_tokenize(SOURCE_FILES("func_add_operation_identifier.c"));
    TEST_ASSERT_NOT_NULL(tokens);
    ast_program_t* prg = create_ast_struct(tokens);
    TEST_ASSERT_NOT_NULL(prg);
    generator(prg, OUTPUT_ASM_FILE("gen_func_add_operation_identifier.asm"));
    token_list_free(tokens);
}
