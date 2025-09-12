/*******************************************************************\
**
**  This file is part of Chrysalis project, and is made available
**  under the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

# include <stdbool.h>
# include <stddef.h>
# include <stdlib.h>
# include <stdio.h>

# include "generator/operation/operation.h"

# include "parser/operation/ast_operation.h"
# include "parser/operation/rpn_double_chained_list.h"

static bool is_operation_addition_only(ast_operation_t* op)
{
    rpn_double_chained_list_t* ptr = op->rpn_list;

    while (ptr) {
        if (ptr->token == OPERATOR && ((char)ptr->data.value) != '+')
            return false;
        ptr = ptr->next;
    }
    return true;
}

int minimize_operation(ast_operation_t* op)
{
    rpn_double_chained_list_t* new = NULL;
    rpn_double_chained_list_t* operand1 = NULL;
    rpn_double_chained_list_t* operator = NULL;
    rpn_double_chained_list_t* ptr = NULL;

    if (is_operation_addition_only(op)) {
        while (op->rpn_list) {
            ptr = rpn_double_list_pop_front(&(op->rpn_list));
            if (ptr->token == OPERAND_INT) {
                if (!operand1) {
                    operand1 = ptr;
                } else if ((char)op->rpn_list->data.value == '+'){
                    operator = rpn_double_list_pop_front(&(op->rpn_list));
                    free(operator);
                    operand1->data.value += ptr->data.value;
                    free(ptr);
                }
            } else if (ptr->token == OPERAND_IDENTIFIER) {
                new = rpn_double_list_push_back(new, ptr);
            } else if (ptr->token == OPERATOR) {
                new = rpn_double_list_push_back(new, ptr);
            }
        }

        if (new) {
            if (operand1)
                new = rpn_double_list_push_front(new, operand1);
            op->rpn_list = new;
            rpn_double_list_dump(new);
        } else {
            op->rpn_list = operand1;
            rpn_double_list_dump(operand1);
        }
    }
    return 0;
}
