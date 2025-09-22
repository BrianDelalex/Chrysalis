/*******************************************************************\
**
**  This file is part of Chrysalis project, and is made available
**  under the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

# include <stdlib.h>

# include "parser/variable_list.h"

# include "utils/logging.h"

variable_list_t* variable_list_add_node(variable_list_t* head, variable_list_t* node)
{
    variable_list_t* ptr = head;
    if (!head)
        return node;

    while (ptr->next) {
        ptr = ptr->next;
    }
    ptr->next = node;
    return head;
}

variable_list_t* variable_list_create_node(variable_list_t* head, ast_variable_t var)
{
    variable_list_t* node = malloc(sizeof(variable_list_t));

    if (!node) {
        PERR(OUT_OF_MEM);
        variable_list_free(head);
        return NULL;
    }
    node->var = var;
    node->next = NULL;

    return variable_list_add_node(head, node);
}

uint32_t variable_list_size(variable_list_t* head)
{
    uint32_t size = 0;

    while (head) {
        size++;
        head = head->next;
    }
    return size;
}

void variable_list_free(variable_list_t* head)
{
    variable_list_t* ptr = head;

    while (head) {
        ptr = head->next;
        free(head->var.identifier);
        free(head);
        head = ptr;
    }
}
