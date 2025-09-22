/*******************************************************************\
**
**  This file is part of Chrysalis project, and is made available
**  under the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

# include <stdlib.h>

# include "parser/expression/expression_list.h"

# include "utils/logging.h"

void expression_free(ast_expr_t* expr);

expr_list_t* expr_list_add_node(expr_list_t* head, expr_list_t* node)
{
    expr_list_t* ptr = head;
    if (!head)
        return node;

    while(ptr->next) {
        ptr = ptr->next;
    }
    ptr->next = node;
    return head;
}

expr_list_t* expr_list_create_node(expr_list_t* head, ast_expr_t expr)
{
    expr_list_t* node = malloc(sizeof(expr_list_t));

    if (!node) {
        PERR(OUT_OF_MEM);
        return NULL;
    }
    node->expr = expr;
    node->next = NULL;
    return expr_list_add_node(head, node);
}

uint32_t expr_list_size(expr_list_t* head)
{
    uint32_t size = 0;

    while (head) {
        size++;
        head = head->next;
    }
    return size;
}

void expr_list_free(expr_list_t* head)
{
    expr_list_t* ptr;

    while (head) {
        ptr = head->next;
        expression_free(&(head->expr));
        free(head);
        head = ptr;
    }
}
