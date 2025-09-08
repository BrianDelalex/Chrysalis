/*******************************************************************\
**
**  This file is part of Chrysalis project, and is made available
**  under the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

# include "parser/statement/statement_patterns.h"
# include "parser/expression/expression_patterns.h"

# include "utils/logging.h"

# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <string.h>

static bool does_expression_pattern_macth(token_list_t **head, const pattern_t* pattern)
{
    token_list_t* ptr = *head;

    for (int i = 0; i < pattern->token_count; i++) {
        if (!ptr)
            return false;

        if (pattern->tokens[i] != (int) ptr->token.type)
            return false;
        ptr = ptr->next;
    }

    *head = ptr;
    return true;
}

bool is_expression_valid(token_list_t **head)
{
    for (unsigned int i = 0; i < EXPRESSION_PATTERNS_SIZE; i++) {
        if (does_expression_pattern_macth(head, &EXPRESSION_PATTERNS[i]))
            return true;
    }
    return false;
}

bool is_token_return(token_list_t token)
{
    return token.token.type == KEYWORD && strcmp(token.token.value, "return") == 0;
}

bool check_extended_token_type(token_list_t **ptr, token_type_ext_t type)
{
    switch (type) {
        case TOKEN_EXPR:
            return is_expression_valid(ptr);
        case TOKEN_RETURN:
            bool ret = is_token_return(*(*ptr));
            if (ret)
                *ptr = (*ptr)->next;
            return ret;
        default:
            PERR("Unknow extended token type %d\n", type);
            return false;
    }
}

static bool does_statement_pattern_macth(token_list_t **head, const pattern_t* pattern) {
    token_list_t* ptr = *head;

    for (int i = 0; i < pattern->token_count; i++) {
        if (!ptr)
            return false;

        if (pattern->tokens[i] >= EXTENDED_TOKEN_TYPES_START) {
            if (!check_extended_token_type(&ptr, pattern->tokens[i])) {
                return false;
            } else {
                continue;
            }
        }

        if (pattern->tokens[i] != (int) ptr->token.type)
            return false;
        ptr = ptr->next;
    }
    *head = ptr;
    return true;
}

const pattern_t* find_statement_pattern(token_list_t** head)
{
    for (unsigned int i = 0; i < STATEMENT_PATTERNS_SIZE; i++) {
        if (does_statement_pattern_macth(head, &STATEMENT_PATTERNS[i]))
            return &STATEMENT_PATTERNS[i];
    }
    return NULL;
}
