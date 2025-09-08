/*******************************************************************\
**
**  This file is part of Chrysalis project, and is made available
**  under the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

# include "parser/function/function_patterns.h"

# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>

static bool does_pattern_macth(token_list_t *head, const pattern_t* pattern) {
    token_list_t* ptr = head;

    for (int i = 0; i < pattern->token_count; i++) {
        if (!ptr)
            return false;
        if (pattern->tokens[i] != (int)ptr->token.type)
            return false;
        ptr = ptr->next;
    }
    return true;
}

const pattern_t* find_function_pattern(token_list_t* head)
{
    for (unsigned int i = 0; i < FUNCTION_PATTERNS_SIZE; i++) {
        if (does_pattern_macth(head, &FUNCTION_PATTERNS[i]))
            return &FUNCTION_PATTERNS[i];
    }
    return NULL;
}
