/*******************************************************************\
**
**  This file is part of Chrysalis project, and is made available
**  under the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

# include "parser/ast_types.h"

ast_statement_t* ast_statement_list_add_node(ast_statement_t* head, ast_statement_t* node)
{
    if (!head)
        return node;

    while (head->next) {
        head = head->next;
    }
    head->next = node;
    return head;
}
