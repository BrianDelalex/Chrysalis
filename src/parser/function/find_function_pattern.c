/*******************************************************************\
**
**  This file is part of Chrysalis project, and is made available
**  under the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>

# include "parser/types/types.h"
# include "parser/function/function_patterns.h"


static bool check_params_list(token_list_t** head)
{
    token_list_t* ptr = *head;

    while (ptr && ptr->token.type != PARENTHESES_CLOSE) {
        if (!is_valid_type(&ptr))
            return false;
        if (ptr->token.type != IDENTIFIER)
            return false;
        ptr = ptr->next;
        if (ptr && ptr->token.type == COMMA)
            ptr = ptr->next;
    }
    *head = ptr;
    return true;
}

static bool check_extended_func_token_type(token_list_t** head, token_type_ext_t token)
{
    switch(token) {
    case TOKEN_PARAMS_LIST:
        return check_params_list(head);
    default:
        return false;
    }
}

static bool does_pattern_match(token_list_t *head, const pattern_t* pattern) {
    token_list_t* ptr = head;

    for (int i = 0; i < pattern->token_count; i++) {
        if (!ptr)
            return false;
        if (pattern->tokens[i] >= EXTENDED_TOKEN_TYPES_START) {
            if (!check_extended_func_token_type(&ptr, pattern->tokens[i])) {
                return false;
            } else {
                continue;
            }
        }
        if (pattern->tokens[i] != (int)ptr->token.type)
            return false;
        ptr = ptr->next;
    }
    return true;
}

const pattern_t* find_function_pattern(token_list_t* head)
{
    for (unsigned int i = 0; i < FUNCTION_PATTERNS_SIZE; i++) {
        if (does_pattern_match(head, &FUNCTION_PATTERNS[i]))
            return &FUNCTION_PATTERNS[i];
    }
    return NULL;
}
