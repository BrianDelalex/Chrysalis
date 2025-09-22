/*******************************************************************\
**
**  This file is part of Chrysalis project, and is made available
**  under the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

#ifndef EXPRESSION_LIST_H
#define EXPRESSION_LIST_H

# include "parser/ast_types.h"

typedef struct expr_list_s {
    ast_expr_t expr;
    struct expr_list_s* next;
}expr_list_t;


expr_list_t* expr_list_add_node(expr_list_t* head, expr_list_t* node);
expr_list_t* expr_list_create_node(expr_list_t* head, ast_expr_t expr);
uint32_t expr_list_size(expr_list_t* head);
void expr_list_free(expr_list_t* head);

#endif//!EXPRESSION_LIST_H
