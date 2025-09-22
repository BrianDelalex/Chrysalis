/*******************************************************************\
**
**  This file is part of Chrysalis project, and is made available
**  under the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

# include <string.h>
# include <stdbool.h>

# include "parser/types/types.h"
# include "parser/ast_types.h"

const char* BUILTIN_TYPE_IDENTIFIERS[] = {
    "int",
};

const unsigned int BUILTIN_TYPE_IDENTIFIERS_SIZE = sizeof(BUILTIN_TYPE_IDENTIFIERS) / sizeof(char*);

const type_t TYPE_INT = {
    .size = sizeof(int),
    .type_id = TYPE_ID_INT
};

const type_t BUILTIN_TYPES[] = {
    TYPE_INT
};
const unsigned int BUILTIN_TYPES_SIZE = sizeof(BUILTIN_TYPES) / sizeof(type_t);

type_t get_type(token_list_t** head)
{
    token_list_t* ptr = *head;
    for (unsigned int i = 0; i < BUILTIN_TYPES_SIZE; i++) {
        if (ptr->token.value && strcmp(ptr->token.value, BUILTIN_TYPE_IDENTIFIERS[i]) == 0) {
            *head = ptr->next;
            return BUILTIN_TYPES[i];
        }
        ptr = ptr->next;
    }
    return (type_t) {.type_id = -1, .size = 0};
}

bool is_valid_type(token_list_t** head)
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
