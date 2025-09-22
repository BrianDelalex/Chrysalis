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

static bool check_args_list(token_list_t** head)
{
    token_list_t* ptr = *head;

    while (ptr && ptr->token.type != PARENTHESES_CLOSE) {
        if (ptr->token.type != IDENTIFIER && ptr->token.type != INTEGER_LITERAL)
            return false;
        ptr = ptr->next;
        if (ptr && ptr->token.type == COMMA)
            ptr = ptr->next;
    }
    *head = ptr;
    return true;
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

static bool check_expr_extended_token_type(token_list_t** head, token_type_ext_t ext_type, const token_type_t* delimiters)
{
    switch (ext_type) {
    case TOKEN_EXPR_DELIMITER:
        for (int i = 0; delimiters[i] != UNKNOW; i++) {
            if ((*head)->token.type == delimiters[i]) {
                return true;
            }
        }
        return false;
    case TOKEN_OPERATION:
        return is_operation_valid(head);
    case TOKEN_ARGS_LIST:
        return check_args_list(head);
    default:
        PERR("Unknow expression extended token type %d\n", ext_type);
        return false;
    }
}

static bool does_expression_pattern_macth(token_list_t** head, const expr_pattern_t* pattern, const token_type_t* delimiters)
{
    token_list_t* ptr = *head;
    token_list_t* save_ptr = *head;

    for (int i = 0; i < pattern->token_count; i++) {
        if (!ptr)
            return false;
        if (pattern->tokens[i] >= EXTENDED_TOKEN_TYPES_START) {
            if (!check_expr_extended_token_type(&ptr, pattern->tokens[i], delimiters)) {
                return false;
            } else {
                save_ptr = ptr;
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

bool is_expression_valid(token_list_t **head, const expr_pattern_t** patt, const token_type_t* delimiters)
{
    for (unsigned int i = 0; i < EXPRESSION_PATTERNS_SIZE; i++) {
        if (does_expression_pattern_macth(head, &EXPRESSION_PATTERNS[i], delimiters)) {
            *patt = &EXPRESSION_PATTERNS[i];
            return true;
        }
    }
    return false;
}
