/*******************************************************************\
**
**  This file is part of Chrysalis project, and is made available
**  under the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

# include <stdlib.h>

# include "parser/ast_types.h"

# include "parser/expression/expression.h"

# include "utils/logging.h"
# include "utils/string_manipulation.h"

int create_ast_expression(token_list_t **head, ast_expr_t* expr)
{
    token_list_t* ptr = *head;

    while (ptr && ptr->token.type != SEMICOLON) {
        switch (ptr->token.type) {
        case INTEGER_LITERAL:
        {
            ast_operand_integer_integral_t* op = malloc(sizeof(ast_operand_integer_integral_t));
            if (!op) {
                PERR(OUT_OF_MEM);
                return -1;
            }
            op->value = atoi(ptr->token.value);
            expr->op.type = OP_INTEGER_LITERAL;
            expr->op.operand = (void*) op;
            break;
        }
        case IDENTIFIER:
        {
            ast_operand_identifier_t* op = malloc(sizeof(ast_operand_identifier_t));
            if (!op) {
                PERR(OUT_OF_MEM);
                return -1;
            }
            op->identifier = copy_string(ptr->token.value);
            if (!op->identifier)
                return -1;
            expr->op.type = OP_IDENTIFIER;
            expr->op.operand = (void*) op;
            break;
        }
        default:
            return -1;
        }
        ptr = ptr->next;
    }

    *head = ptr;
    return 0;
}
