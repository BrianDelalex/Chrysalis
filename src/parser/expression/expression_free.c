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
# include "parser/operation/ast_operation.h"
# include "parser/operation/rpn_double_chained_list.h"

void expression_free(ast_expr_t* expr);
void expression_free(ast_expr_t* expr)
{
    switch (expr->op.type) {
    case OP_IDENTIFIER:
        ast_operand_identifier_t *op_identifier = (ast_operand_identifier_t*) expr->op.operand;
        if (op_identifier->identifier)
            free(op_identifier->identifier);
        break;
    case OP_OPERATION:
        ast_operation_t* op= (ast_operation_t*) expr->op.operand;
        rpn_double_list_free(op->rpn_list);
        break;
    default:
        break;
    }
    free(expr->op.operand);
}
