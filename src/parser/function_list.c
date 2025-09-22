/*******************************************************************\
**
**  This file is part of Chrysalis project, and is made available
**  under the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

# include <stdlib.h>

# include "parser/function/function_list.h"

# include "utils/logging.h"

function_list_t* function_list_add_node(function_list_t* head, function_list_t* node)
{
    function_list_t* ptr = head;

    if (!head)
        return node;

    while (ptr->next) {
        ptr = ptr->next;
    }
    ptr->next = node;
    return head;
}

function_list_t* function_list_create_node(function_list_t* head, ast_function_t* func)
{
    function_list_t* node = malloc(sizeof(function_list_t));

    if (!node) {
        PERR(OUT_OF_MEM);
        return NULL;
    }
    node->func = func;
    node->next = NULL;

    return function_list_add_node(head, node);
}

void function_list_free(function_list_t* head)
{
    function_list_t* ptr;

    while (head) {
        ptr = head->next;
        head->func->free(head->func);
        free(head);
        head = ptr;
    }
}
