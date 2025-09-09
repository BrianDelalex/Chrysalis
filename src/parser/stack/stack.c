/*******************************************************************\
**
**  This file is part of Chrysalis project, and is made available
**  under the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

# include <stdlib.h>
# include <string.h>
# include <stdint.h>

# include "parser/stack.h"

# include "utils/logging.h"

void ast_stack_free(ast_stack_t* stack)
{
    ast_stack_entry_t* entries = stack->entries;

    while (entries) {
        entries = stack->entries->next;
        free(stack->entries->identifier);
        free(stack->entries);
        stack->entries = entries;
    }
    free(stack);
}

ast_stack_t *ast_stack_create()
{
    ast_stack_t* stack = malloc(sizeof(ast_stack_t));

    if (!stack) {
        PERR(OUT_OF_MEM);
        return NULL;
    }
    memset(stack, 0, sizeof(ast_stack_t));
    return stack;
}

int ast_stack_add_entry(ast_stack_t* stack, uint64_t size, const char*identifier)
{
    ast_stack_entry_t* new;
    ast_stack_entry_t* entries = stack->entries;
    uint64_t offset = size;

    new = malloc(sizeof(ast_stack_entry_t));
    if (!new) {
        PERR(OUT_OF_MEM);
        return -1;
    }

    while (entries && entries->next) {
        entries = entries->next;
    }
    if (entries) {
        offset = entries->offset + entries->size;
        entries->next = new;
    } else {
        stack->entries = new;
    }

    new->offset = offset;
    new->size = size;
    new->next = NULL;

    int id_len = strlen(identifier);
    new->identifier = malloc(sizeof(char) * (id_len + 1));
    if (!new->identifier) {
        PERR(OUT_OF_MEM);
        free(new);
        return -1;
    }
    memcpy(new->identifier, identifier, id_len + 1);

    return 0;
}
