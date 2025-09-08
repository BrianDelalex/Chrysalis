# include "unity.h"

# include <stdlib.h>

# include "tokenizer/tokenizer.h"
# include "parser/parser.h"

# include "files/files.h"

# include "stage2.h"

void test_tokenize_main_return_identifier(void);
void test_tokenize_main_return_identifier(void)
{
    char* file = read_file(SOURCE_FILES("main_return_identifier.c"));
    TEST_ASSERT_NOT_NULL(file);
    token_list_t* tokens = tokenizer(file);
    TEST_ASSERT_NOT_NULL(tokens);
    ast_program_t* prg = create_ast_struct(tokens);
    TEST_ASSERT_NOT_NULL(prg);
    free(file);
    token_list_free(tokens);
    ast_program_free(prg);
}

void test_stage2(void);
void test_stage2(void)
{
    TEST_ASSERT_NULL(NULL);
}
