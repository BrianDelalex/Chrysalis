# include "unity.h"

# include <stdlib.h>

# include "tokenizer/tokenizer.h"
# include "parser/parser.h"
# include "parser/stack.h"
# include "generator/generator.h"

# include "files/files.h"

# include "stage2.h"

void test_all_main_return_identifier(void);
void test_all_main_return_identifier(void)
{
    char* file = read_file(SOURCE_FILES("main_return_identifier.c"));
    TEST_ASSERT_NOT_NULL_MESSAGE(file, "file was null");
    token_list_t* tokens = tokenizer(file);
    TEST_ASSERT_NOT_NULL_MESSAGE(tokens, "tokens was null.");
    ast_program_t* prg = create_ast_struct(tokens);
    TEST_ASSERT_NOT_NULL_MESSAGE(prg, "prg was null.");
    TEST_ASSERT_EQUAL(0, generator(prg, OUTPUT_ASM_FILE("gen_main_return_identifier.asm")));
    free(file);
    token_list_free(tokens);
    ast_program_free(prg);
}

void test_all_main_return_identifier_42(void);
void test_all_main_return_identifier_42(void)
{
    char* file = read_file(SOURCE_FILES("main_return_identifier_42.c"));
    TEST_ASSERT_NOT_NULL_MESSAGE(file, "file was null");
    token_list_t* tokens = tokenizer(file);
    TEST_ASSERT_NOT_NULL_MESSAGE(tokens, "tokens was null.");
    ast_program_t* prg = create_ast_struct(tokens);
    TEST_ASSERT_NOT_NULL_MESSAGE(prg, "prg was null.");
    TEST_ASSERT_EQUAL(0, generator(prg, OUTPUT_ASM_FILE("gen_main_return_identifier_42.asm")));
    free(file);
    token_list_free(tokens);
    ast_program_free(prg);
}

void test_all_post_decl_assign_0(void);
void test_all_post_decl_assign_0(void)
{
    char* file = read_file(SOURCE_FILES("post_decl_assign_0.c"));
    TEST_ASSERT_NOT_NULL_MESSAGE(file, "file was null");
    token_list_t* tokens = tokenizer(file);
    TEST_ASSERT_NOT_NULL_MESSAGE(tokens, "tokens was null.");
    ast_program_t* prg = create_ast_struct(tokens);
    TEST_ASSERT_NOT_NULL_MESSAGE(prg, "prg was null.");
    TEST_ASSERT_EQUAL(0, generator(prg, OUTPUT_ASM_FILE("gen_post_decl_assign_0.asm")));
    free(file);
    token_list_free(tokens);
    ast_program_free(prg);
}

void test_all_post_decl_assign_42(void);
void test_all_post_decl_assign_42(void)
{
    char* file = read_file(SOURCE_FILES("post_decl_assign_42.c"));
    TEST_ASSERT_NOT_NULL_MESSAGE(file, "file was null");
    token_list_t* tokens = tokenizer(file);
    TEST_ASSERT_NOT_NULL_MESSAGE(tokens, "tokens was null.");
    ast_program_t* prg = create_ast_struct(tokens);
    TEST_ASSERT_NOT_NULL_MESSAGE(prg, "prg was null.");
    TEST_ASSERT_EQUAL(0, generator(prg, OUTPUT_ASM_FILE("gen_post_decl_assign_42.asm")));
    free(file);
    token_list_free(tokens);
    ast_program_free(prg);
}

void test_all_main_return_undef_identifier(void);
void test_all_main_return_undef_identifier(void)
{
    char* file = read_file(SOURCE_FILES("main_return_undef_identifier.c"));
    TEST_ASSERT_NOT_NULL(file);
    token_list_t* tokens = tokenizer(file);
    TEST_ASSERT_NOT_NULL(tokens);
    ast_program_t* prg = create_ast_struct(tokens);
    TEST_ASSERT_NOT_NULL(prg);
    TEST_ASSERT_EQUAL(-1, generator(prg, OUTPUT_ASM_FILE("gen_main_return_undef_identifier.asm")));
    free(file);
    token_list_free(tokens);
    ast_program_free(prg);
}

void test_ast_stack(void);
void test_ast_stack(void)
{
    ast_stack_t* stack = ast_stack_create();
    ast_stack_entry_t* ptr;
    const char var1[] = "var1";
    const char var2[] = "var2";
    const char var3[] = "var3";
    TEST_ASSERT_NOT_NULL(stack);

    TEST_ASSERT_EQUAL(0, ast_stack_add_entry(stack, sizeof(int), var1));
    TEST_ASSERT_NOT_NULL(stack->entries);
    TEST_ASSERT_EQUAL(sizeof(int), stack->entries->offset);
    TEST_ASSERT_EQUAL(sizeof(int), stack->entries->size);
    TEST_ASSERT_EQUAL_STRING(var1, stack->entries->identifier);
    TEST_ASSERT_NULL(stack->entries->next);
    ptr = stack->entries;

    TEST_ASSERT_EQUAL(0, ast_stack_add_entry(stack, sizeof(uint64_t), var2));
    ptr = ptr->next;
    TEST_ASSERT_NOT_NULL(ptr);
    TEST_ASSERT_EQUAL(sizeof(int) + sizeof(int), ptr->offset);
    TEST_ASSERT_EQUAL(sizeof(uint64_t), ptr->size);
    TEST_ASSERT_EQUAL_STRING(var2, ptr->identifier);
    TEST_ASSERT_NULL(ptr->next);

    TEST_ASSERT_EQUAL(0, ast_stack_add_entry(stack, sizeof(char), var3));
    ptr = ptr->next;
    TEST_ASSERT_NOT_NULL(ptr);
    TEST_ASSERT_EQUAL(sizeof(int) + sizeof(int) + sizeof(uint64_t), ptr->offset);
    TEST_ASSERT_EQUAL(sizeof(char), ptr->size);
    TEST_ASSERT_EQUAL_STRING(var3, ptr->identifier);
    TEST_ASSERT_NULL(ptr->next);

    ast_stack_free(stack);
}
