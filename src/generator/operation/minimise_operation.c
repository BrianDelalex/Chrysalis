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
    rpn_double_chained_list_t* operand2 = NULL;
    rpn_double_chained_list_t* operator = NULL;

    if (is_operation_addition_only(op)) {
        while (op->rpn_list) {
            operand1 = rpn_double_list_pop_front(&(op->rpn_list));
            if (operand1->token != OPERAND_INT) {
                new = rpn_double_list_push_back(new, operand1);
            } else {
                break;
            }
        }

        while (op->rpn_list) {
            operand2 = rpn_double_list_pop_front(&(op->rpn_list));
            if (operand2->token == OPERAND_INT) {
                operator = rpn_double_list_pop_front(&(op->rpn_list));
                if (((char)operator->data.value) == '+') {
                    operand1->data.value += operand2->data.value;
                }
                free(operand2);
                free(operator);
            } else {
                new = rpn_double_list_push_back(new, operand2);
                operator = rpn_double_list_pop_front(&(op->rpn_list));
                new = rpn_double_list_push_back(new, operator);
            }
        }

        printf("Minimized operation: ");
        if (new) {
            op->rpn_list = new;
            rpn_double_list_dump(new);
        } else {
            op->rpn_list = operand1;
            rpn_double_list_dump(operand1);
        }
    }
    return 0;
}
