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

# define SOURCE_FILES(file) STAGE1_DIR "/stage1/source_files/" file

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

void test_main_return_0(void)
{
    TEST_WITH_SOURCE_FILE(main_return_0);
}

void test_main_return_42(void)
{
    TEST_WITH_SOURCE_FILE(main_return_42);
}

void test_no_main(void)
{
    TEST_WITH_SOURCE_FILE(no_main);
}

void test_main_extra_spaces(void)
{
    TEST_WITH_SOURCE_FILE(main_extra_spaces);
}

void test_main_missing_closing_parenthesis(void)
{
    TEST_WITH_SOURCE_FILE(main_missing_closing_parenthesis);
}

void test_main_missing_opening_parentheses(void)
{
    TEST_WITH_SOURCE_FILE(main_missing_opening_parenthesis);
}

void test_main_missing_closing_curly_bracket(void)
{
    TEST_WITH_SOURCE_FILE(main_missing_closing_curly_bracket);
}

void test_main_missing_opening_curly_bracket(void)
{
    TEST_WITH_SOURCE_FILE(main_missing_opening_curly_bracket);
}

void test_main_missing_semicolon(void)
{
    TEST_WITH_SOURCE_FILE(main_missing_semicolon);
}
