/*******************************************************************\
**
**  this file is part of chrysalis project, and is made available
**  under the terms of the gnu general public license version 3.
**
**  copyright (c) 2025 - brian delalex-fondu
**
\*******************************************************************/

# include "parser/statement/statement_free.h"
# include "parser/ast_types.h"

# include "utils/logging.h"

# include <stdlib.h>

void expression_free(ast_expr_t* expr);

void statement_return_free(ast_statement_return_t *statement)
{
    expression_free(&(statement->expr));
    free(statement);
}

void statement_assign_decl_free(ast_statement_assign_t *statement)
{
    free(statement->var.identifier);
    expression_free(&(statement->expr));
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
    case ASSIGN:
        ast_statement_assign_t* assign = (ast_statement_assign_t*)statement->statement;
        if (assign->free)
            assign->free(assign);
        break;
    default:
        PERR("Unexpected statement type\n");
    }
    free(statement);
}
