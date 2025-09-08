/*******************************************************************\
**
**  This file is part of Chrysalis project, and is made available
**  under the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

# include "parser/ast_types.h"

# include "parser/patterns.h"

# include "parser/function/ast_create_functions.h"

# include "utils/logging.h"

# include <stdlib.h>
# include <string.h>

ast_function_t* get_function_ast(token_list_t* head)
{
    const pattern_t* pattern = find_function_pattern(head);

    if (!pattern) {
        PERR("No function pattern match tokens starting at: ");
        token_dump(*head);
        return NULL;
    }
    return pattern->ast_create(head);
}

void* create_function_decl_ast(token_list_t* head)
{
    ast_function_t *func;
    token_list_t* ptr = head;

    if (ptr->token.type != KEYWORD) {
        PERR("Invalid token expected KEYWORD got %s with value %s\n",
            token_type_as_str(ptr->token.type),
            ptr->token.value ? ptr->token.value : "NULL");
        return NULL;
    }

    ptr = ptr->next;
    if (!ptr || ptr->token.type != IDENTIFIER) {
        if (ptr) {
            PERR("Invalid token expected IDENTIFIER got %s with value %s\n",
                   token_type_as_str(ptr->token.type),
                   ptr->token.value ? ptr->token.value : "NULL");
        }
        return NULL;
    }
    func = ast_function_init();
    if (!func) {
        return NULL;
    }
    int name_len = strlen(ptr->token.value);
    func->name = malloc(sizeof(char) * (name_len + 1));
    if (!func->name) {
        func->free(func);
        return NULL;
    }
    func->name = memcpy(func->name, ptr->token.value, name_len + 1);
    ptr = ptr->next;
    if (!ptr || ptr->token.type != PARENTHESES_OPEN) {
        PERR("Expected '(' after %s identifier. Found %s\n", func->name, token_type_as_str(ptr->token.type));
        func->free(func);
        return NULL;
    }
    ptr = ptr->next;
    if (!ptr || ptr->token.type != PARENTHESES_CLOSE) {
        PERR("Expected ')' after '%s('.\n", func->name);
        func->free(func);
        return NULL;
    }
    ptr = ptr->next;
    if (!ptr || ptr->token.type != CURLY_OPEN) {
        PERR("Expected '{' after '%s()'.\n", func->name);
        func->free(func);
        return NULL;
    }
    ptr = ptr->next;

    while (ptr && ptr->token.type != CURLY_CLOSE) {
        ast_statement_t* statement = get_statement_ast(&ptr);
        if (!statement) {
            func->free(func);
            return NULL;
        }
        func->statements = ast_statement_list_add_node(func->statements, statement);
        if (!func->statements) {
            func->free(func);
            return NULL;
        }
    }

    if (!ptr || ptr->token.type != CURLY_CLOSE) {
        PERR("Expected '}' after 'return'.\n");
        func->free(func);
        return NULL;
    }
    return func;
}
