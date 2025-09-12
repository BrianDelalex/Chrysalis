/*******************************************************************\
**
**  This file is part of Chrysalis project, and is made available
**  under the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

# include <stddef.h>
# include <stdlib.h>

# include "parser/operation/ast_operation.h"
# include "parser/operation/rpn_double_chained_list.h"
# include "parser/ast_types.h"

# include "attributes.h"

static rpn_double_chained_list_t* parse_operation_operand(token_list_t* token)
{
    if (token->token.type == IDENTIFIER) {
        return rpn_create_node(OPERAND_IDENTIFIER, token->token.value);
    } else if (token->token.type == INTEGER_LITERAL) {
        return rpn_create_node(OPERAND_INT, token->token.value);
    }
    return NULL;
}

static rpn_double_chained_list_t* parse_operation_type(UNUSED token_list_t* token)
{
    return rpn_create_node(OPERATOR, "+");
}

rpn_double_chained_list_t* token_list_to_rpn(token_list_t* head)
{
    rpn_double_chained_list_t* rpn_list = NULL;
    rpn_double_chained_list_t* operator = NULL;
    rpn_double_chained_list_t* operand = NULL;

    operand = parse_operation_operand(head);
    if (!operand) {
        rpn_double_list_free(rpn_list);
        return NULL;
    }
    rpn_list = rpn_double_list_push_back(rpn_list, operand);
    head = head->next;

    while (head && head->token.type != SEMICOLON) {
        operator = parse_operation_type(head);
        if (!operator) {
            rpn_double_list_free(rpn_list);
            return NULL;
        }

        head = head->next;
        operand = parse_operation_operand(head);
        if (!operand) {
            rpn_double_list_free(rpn_list);
            free(operator);
            return NULL;
        }
        rpn_list = rpn_double_list_push_back(rpn_list, operand);
        rpn_list = rpn_double_list_push_back(rpn_list, operator);
        head = head->next;
    }

    rpn_double_list_dump(rpn_list);
    return rpn_list;
}
