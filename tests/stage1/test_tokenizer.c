/*******************************************************************\
**
**  This file is part of Chrysalis project, and is made available
**  under the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

# include "tokenizer/tokenizer.h"
# include "expected.h"
# include "utils/string_manipulation.h"
# include "files/files.h"

# include "unity.h"

# include <stdlib.h>

# include "stage1.h"
# include "parser/parser.h"
# include "generator/generator.h"

# define Q(x) #x
# define QUOTE(x) Q(x)

# define TEST_WITH_SOURCE_FILE(file)                                                            \
    char* file = read_file(SOURCE_FILES(QUOTE(file) ".c"));                                     \
    TEST_ASSERT_NOT_NULL(file);                                                                 \
    token_list_t *file##_list = tokenizer(file);                                                \
    TEST_ASSERT_NOT_NULL(file##_list);                                                          \
    check_token_list(file##_expected, sizeof(file##_expected) / sizeof(token_t), file##_list);  \
    free(file##_list);                                                                          \
    free(file);                                                                                 \

# define TEST_PARSER_WITH_EXPECTED_CONST_STRUCT(test)                                           \
    token_list_t* head = NULL;                                                                  \
    for (unsigned int i = 0; i < sizeof(test##_expected) / sizeof(token_t); i++) {              \
        head = token_list_create_node(head, test##_expected[i].type, test##_expected[i].value); \
    }                                                                                           \
    ast_program_t* program = create_ast_struct(head);                                           \
    TEST_ASSERT_NOT_NULL(program);                                                              \
    check_ast_struct(prg_##test##_expected, program);                                           \
    token_list_free(head);                                                                      \

# define TEST_PARSER_FAIL(test)                                                                 \
    token_list_t* head = NULL;                                                                  \
    for (unsigned int i = 0; i < sizeof(test##_expected) / sizeof(token_t); i++) {              \
        head = token_list_create_node(head, test##_expected[i].type, test##_expected[i].value); \
    }                                                                                           \
    ast_program_t* program = create_ast_struct(head);                                           \
    TEST_ASSERT_NULL(program);                                                                  \
    token_list_free(head);                                                                      \

void setUp(void)
{
}

void tearDown(void)
{
}

void check_token_list(const token_t *expected, int expected_size, token_list_t* token_list)
{
    token_list_t* ptr = token_list;
    int counter = 0;

    while (ptr) {
        TEST_ASSERT_LESS_THAN(expected_size, counter);
        TEST_ASSERT_EQUAL(expected[counter].type, ptr->token.type);
        if (expected[counter].value == NULL) {
            TEST_ASSERT_NULL(ptr->token.value);
        } else {
            TEST_ASSERT_EQUAL_STRING(expected[counter].value, ptr->token.value);
        }
        counter++;
        ptr = ptr->next;
    }
}

void test_read_file(void)
{
    char* main_return_0 = read_file(SOURCE_FILES("main_return_0.c"));
    char expected[] = "int main()\n{\n    return 0;\n}\n";
    TEST_ASSERT_EQUAL_STRING(expected, main_return_0);
}

void test_remove_extra_space(void)
{
    char txt[] = "  int   main  ()\n   {\n   return   0  ;\n   }   ";
    char* clear = remove_extra_spaces(txt);

    TEST_ASSERT_EQUAL_STRING("int main ()\n{\nreturn 0 ;\n} ", clear);
    free(clear);
}

void test_remove_newline(void)
{
    char txt[] = "int main ()\n{\nreturn 0 ;\n} ";
    char* clear = remove_newline(txt);

    TEST_ASSERT_EQUAL_STRING("int main (){return 0 ;} ", clear);
    free(clear);
}

void test_tokenizer(void)
{
    TEST_ASSERT_NULL(tokenizer(NULL));
}

void test_tokenizer_main_return_0(void)
{
    TEST_WITH_SOURCE_FILE(main_return_0);
}

void test_tokenizer_main_return_42(void)
{
    TEST_WITH_SOURCE_FILE(main_return_42);
}

void test_tokenizer_no_main(void)
{
    TEST_WITH_SOURCE_FILE(no_main);
}

void test_tokenizer_main_extra_spaces(void)
{
    TEST_WITH_SOURCE_FILE(main_extra_spaces);
}

void test_tokenizer_main_missing_closing_parenthesis(void)
{
    TEST_WITH_SOURCE_FILE(main_missing_closing_parenthesis);
}

void test_tokenizer_main_missing_opening_parentheses(void)
{
    TEST_WITH_SOURCE_FILE(main_missing_opening_parenthesis);
}

void test_tokenizer_main_missing_closing_curly_bracket(void)
{
    TEST_WITH_SOURCE_FILE(main_missing_closing_curly_bracket);
}

void test_tokenizer_main_missing_opening_curly_bracket(void)
{
    TEST_WITH_SOURCE_FILE(main_missing_opening_curly_bracket);
}

void test_tokenizer_main_missing_semicolon(void)
{
    TEST_WITH_SOURCE_FILE(main_missing_semicolon);
}


void check_ast_struct(const ast_program_t expected, ast_program_t *program)
{
    TEST_ASSERT_NOT_NULL(program->functions);
    TEST_ASSERT_EQUAL_STRING(expected.functions->name, program->functions->name);
    TEST_ASSERT_NOT_NULL(program->functions->statements);
    TEST_ASSERT_EQUAL(expected.functions->statements->type, program->functions->statements->type);
    TEST_ASSERT_NOT_NULL(program->functions->statements->statement);

    TEST_ASSERT_EQUAL(
        ((ast_operand_integer_integral_t*)((ast_statement_return_t *)expected.functions->statements->statement)->expr.op.operand)->value,
        ((ast_operand_integer_integral_t*)((ast_statement_return_t*)program->functions->statements->statement)->expr.op.operand)->value);
}

void test_parser_main_return_0(void)
{
    TEST_PARSER_WITH_EXPECTED_CONST_STRUCT(main_return_0);
}

void test_parser_main_return_42(void)
{
    TEST_PARSER_WITH_EXPECTED_CONST_STRUCT(main_return_42);
}

void test_parser_no_main(void)
{
    TEST_PARSER_WITH_EXPECTED_CONST_STRUCT(no_main);
}

void test_parser_main_missing_closing_parenthesis(void)
{
    TEST_PARSER_FAIL(main_missing_closing_parenthesis);
}

void test_parser_main_missing_opening_parentheses(void)
{
    TEST_PARSER_FAIL(main_missing_opening_parenthesis);
}

void test_parser_main_missing_closing_curly_bracket(void)
{
    TEST_PARSER_FAIL(main_missing_closing_curly_bracket);
}

void test_parser_main_missing_opening_curly_bracket(void)
{
    TEST_PARSER_FAIL(main_missing_opening_curly_bracket);
}

void test_parser_main_missing_semicolon(void)
{
    TEST_PARSER_FAIL(main_missing_semicolon);
}

void test_generator_main_return_0(void)
{
    TEST_ASSERT_EQUAL(0, generator(&prg_main_return_0_expected, OUTPUT_ASM_FILE("/gen_main_return_0.asm")));
}

void test_generator_main_return_42(void)
{
    TEST_ASSERT_EQUAL(0, generator(&prg_main_return_42_expected, OUTPUT_ASM_FILE("/gen_main_return_42.asm")));
}

void test_generator_no_main(void)
{
    TEST_ASSERT_EQUAL(0, generator(&prg_no_main_expected, OUTPUT_ASM_FILE("/gen_no_main.asm")));
}
