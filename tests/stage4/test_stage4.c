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
    token_list_dump(tokens);
    token_list_free(tokens);
}

void test_all_return_func_no_arg(void);
void test_all_return_func_no_arg(void)
{
    token_list_t* tokens = open_file_and_tokenize(SOURCE_FILES("return_func_no_arg.c"));
    TEST_ASSERT_NOT_NULL(tokens);
    token_list_dump(tokens);
    token_list_free(tokens);
}

void test_all_func_add(void);
void test_all_func_add(void)
{
    token_list_t* tokens = open_file_and_tokenize(SOURCE_FILES("func_add.c"));
    TEST_ASSERT_NOT_NULL(tokens);
    token_list_dump(tokens);
    token_list_free(tokens);
}

void test_all_return_func_add(void);
void test_all_return_func_add(void)
{
    token_list_t* tokens = open_file_and_tokenize(SOURCE_FILES("return_func_add.c"));
    TEST_ASSERT_NOT_NULL(tokens);
    token_list_dump(tokens);
    token_list_free(tokens);
}
