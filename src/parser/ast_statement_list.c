/*******************************************************************\
**
**  This file is part of Chrysalis project, and is made available
**  under the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

# include "parser/ast_types.h"
# include "parser/statement/statement_free.h"

# include <stdlib.h>

ast_statement_t* ast_statement_list_add_node(ast_statement_t* head, ast_statement_t* node)
{
    ast_statement_t* ptr = head;

    if (!head)
        return node;

    while (ptr->next) {
        ptr = ptr->next;
    }
    ptr->next = node;
    return head;
}

void ast_statement_list_free(ast_statement_t* head)
{
    ast_statement_t* ptr;

    while (head) {
        ptr = head->next;
        if (head->free_statement)
            head->free_statement(head);
        else
            free(head);
        head = ptr;
    }
}
