/*******************************************************************\
**
**  This file is part of Chrysalis project, and is made available
**  under the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

# include <stdbool.h>

# include "parser/ast_types.h"
# include "parser/patterns.h"
# include "parser/expression/expression_patterns.h"

# include "utils/logging.h"

static bool is_operand(token_type_t type)
{
    return type == IDENTIFIER || type == INTEGER_LITERAL;
}

static bool is_operation_sign(token_type_t type)
{
    return type == PLUS;
}

static bool is_operation_valid(token_list_t** head)
{
    token_list_t* ptr = *head;

    while (ptr && ptr->token.type != SEMICOLON) {
        if (!is_operand(ptr->token.type)) {
            PERR("Operand expected but got ");
            token_dump(*ptr);
            return false;
        }
        ptr = ptr->next;
        if (ptr->token.type == SEMICOLON) {
            *head = ptr;
            return true;
        }
        if (!is_operation_sign(ptr->token.type)) {
            PERR("Operation sign expected but got ");
            token_dump(*ptr);
            return false;
        }
        ptr = ptr->next;
    }
    return false;
}

static bool check_expr_extended_token_type(token_list_t** head, token_type_ext_t ext_type)
{
    switch (ext_type) {
    case TOKEN_OPERATION:
        return is_operation_valid(head);
    default:
        PERR("Unknow expression extended token type %d\n", ext_type);
        return false;
    }
}

static bool does_expression_pattern_macth(token_list_t** head, const expr_pattern_t* pattern)
{
    token_list_t* ptr = *head;
    token_list_t* save_ptr = *head;

    for (int i = 0; i < pattern->token_count; i++) {
        if (!ptr)
            return false;
        if (pattern->tokens[i] >= EXTENDED_TOKEN_TYPES_START) {
            if (!check_expr_extended_token_type(&ptr, pattern->tokens[i])) {
                return false;
            } else {
                continue;
            }
        }
        if (pattern->tokens[i] != (int) ptr->token.type)
            return false;
        save_ptr = ptr;
        ptr = ptr->next;
    }

    *head = save_ptr;
    return true;
}

bool is_expression_valid(token_list_t **head, const expr_pattern_t** patt)
{
    for (unsigned int i = 0; i < EXPRESSION_PATTERNS_SIZE; i++) {
        if (does_expression_pattern_macth(head, &EXPRESSION_PATTERNS[i])) {
            *patt = &EXPRESSION_PATTERNS[i];
            return true;
        }
    }
    return false;
}
