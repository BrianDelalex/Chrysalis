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

# include "parser/types/types.h"

# include "utils/logging.h"

# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <string.h>

static bool is_token_return(token_list_t token)
{
    return token.token.type == KEYWORD && strcmp(token.token.value, "return") == 0;
}

static bool is_valid_type(token_list_t** head)
{
    token_list_t* ptr = *head;
    for (unsigned int i = 0; i < BUILTIN_TYPE_IDENTIFIERS_SIZE; i++) {
        if (ptr->token.type == KEYWORD && strcmp(ptr->token.value, BUILTIN_TYPE_IDENTIFIERS[i]) == 0) {
            *head = ptr->next;
            return true;
        }
    }
    return false;
}

static bool check_extended_token_type(token_list_t **ptr, token_type_ext_t type, const expr_pattern_t** expr_patt)
{
    switch (type) {
        case TOKEN_EXPR:
            return is_expression_valid(ptr, expr_patt);
        case TOKEN_RETURN:
            bool ret = is_token_return(*(*ptr));
            if (ret)
                *ptr = (*ptr)->next;
            return ret;
        case TOKEN_TYPE:
            return is_valid_type(ptr);
        default:
            PERR("Unknow extended token type %d\n", type);
            return false;
    }
}

static bool does_statement_pattern_macth(token_list_t **head, const statement_pattern_t* pattern, const expr_pattern_t** expr_patt) {
    token_list_t* ptr = *head;

    for (int i = 0; i < pattern->token_count; i++) {
        if (!ptr)
            return false;

        if (pattern->tokens[i] >= EXTENDED_TOKEN_TYPES_START) {
            if (!check_extended_token_type(&ptr, pattern->tokens[i], expr_patt)) {
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

const statement_pattern_t* find_statement_pattern(token_list_t** head, const expr_pattern_t** expr_patt)
{
    for (unsigned int i = 0; i < STATEMENT_PATTERNS_SIZE; i++) {
        if (does_statement_pattern_macth(head, &STATEMENT_PATTERNS[i], expr_patt))
            return &STATEMENT_PATTERNS[i];
    }
    return NULL;
}
