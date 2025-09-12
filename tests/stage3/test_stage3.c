# include "unity.h"

# include <stdlib.h>

# include "stage3.h"

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

void test_all_main_assign_var_to_var(void);
void test_all_main_assign_var_to_var(void)
{
    token_list_t* tokens = open_file_and_tokenize(SOURCE_FILES("main_assign_var_to_var.c"));
    TEST_ASSERT_NOT_NULL(tokens);
    token_list_dump(tokens);
    ast_program_t* prg = create_ast_struct(tokens);
    TEST_ASSERT_NOT_NULL(prg);
    //generator(prg, OUTPUT_ASM_FILE("gen_main_assign_var_to_var.asm"));
    token_list_free(tokens);
}
void test_all_simple_add(void);
void test_all_simple_add(void)
{
    token_list_t* tokens = open_file_and_tokenize(SOURCE_FILES("simple_add.c"));
    TEST_ASSERT_NOT_NULL(tokens);
    token_list_dump(tokens);
    ast_program_t* prg = create_ast_struct(tokens);
    TEST_ASSERT_NOT_NULL(prg);
    token_list_free(tokens);
}

void test_all_add3(void);
void test_all_add3(void)
{

    token_list_t* tokens = open_file_and_tokenize(SOURCE_FILES("add3.c"));
    TEST_ASSERT_NOT_NULL(tokens);
    ast_program_t* prg = create_ast_struct(tokens);
    TEST_ASSERT_NOT_NULL(prg);
    token_list_dump(tokens);
    token_list_free(tokens);
}

void test_all_big_add(void);
void test_all_big_add(void)
{
    token_list_t* tokens = open_file_and_tokenize(SOURCE_FILES("big_add.c"));
    TEST_ASSERT_NOT_NULL(tokens);
    token_list_dump(tokens);
    token_list_free(tokens);
}

void test_all_add_identifier(void);
void test_all_add_identifier(void)
{
    token_list_t* tokens = open_file_and_tokenize(SOURCE_FILES("add_identifier.c"));
    TEST_ASSERT_NOT_NULL(tokens);
    token_list_dump(tokens);
    token_list_free(tokens);
}

void test_all_add_two_identifier(void);
void test_all_add_two_identifier(void)
{
    token_list_t* tokens = open_file_and_tokenize(SOURCE_FILES("add_two_identifier.c"));
    TEST_ASSERT_NOT_NULL(tokens);
    token_list_dump(tokens);
    token_list_free(tokens);
}

void test_all_final_add(void);
void test_all_final_add(void)
{
    token_list_t* tokens = open_file_and_tokenize(SOURCE_FILES("final_add.c"));
    TEST_ASSERT_NOT_NULL(tokens);
    token_list_dump(tokens);
    token_list_free(tokens);
}
