/*******************************************************************\
**
**  this file is part of chrysalis project, and is made available
**  under the terms of the gnu general public license version 3.
**
**  copyright (c) 2025 - brian delalex-fondu
**
\*******************************************************************/

# include "parser/ast_types.h"

# include "utils/logging.h"

# include <stdlib.h>

void statement_return_free(ast_statement_return_t *statement)
{
    ast_expr_operand_t op = statement->expr.op;
    if (op.type == OP_IDENTIFIER) {
        ast_operand_identifier_t *op_identifier = (ast_operand_identifier_t*) op.operand;
        if (op_identifier->identifier)
            free(op_identifier->identifier);
    }
    if (statement->expr.op.operand)
        free(statement->expr.op.operand);
    free(statement);
}

void statement_free(ast_statement_t *statement)
{
    switch(statement->type) {
    case RETURN:
        ast_statement_return_t* rtn = (ast_statement_return_t*)statement->statement;
        if (rtn->free)
            rtn->free(rtn);
        break;
    default:
        PERR("Unexpected statement type\n");
    }
    free(statement);
}
