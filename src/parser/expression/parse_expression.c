/*******************************************************************\
**
**  This file is part of Chrysalis project, and is made available
**  under the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

# include <stdlib.h>
# include <string.h>

# include "parser/ast_types.h"

# include "parser/operation/ast_operation.h"
# include "parser/expression/parser_expression.h"

# include "utils/logging.h"
# include "utils/string_manipulation.h"

ast_expr_t parse_integer_literal_expression(token_list_t* head)
{
    ast_expr_t expr;

    memset(&expr, 0, sizeof(ast_expr_t));

    ast_operand_integer_integral_t* op = malloc(sizeof(ast_operand_integer_integral_t));
    if (!op) {
        PERR(OUT_OF_MEM);
        return expr;
    }
    op->value = atoi(head->token.value);
    expr.op.type = OP_INTEGER_LITERAL;
    expr.op.operand = (void*) op;

    return expr;
}

ast_expr_t parse_identifier_expression(token_list_t* head)
{
    ast_expr_t expr;

    memset(&expr, 0, sizeof(ast_expr_t));

    ast_operand_identifier_t* op = malloc(sizeof(ast_operand_identifier_t));
    if (!op) {
        PERR(OUT_OF_MEM);
        return expr;
    }
    op->identifier = copy_string(head->token.value);
    if (!op->identifier)
        return expr;
    expr.op.type = OP_IDENTIFIER;
    expr.op.operand = (void*) op;

    return expr;
}

ast_expr_t parse_operation_expression(token_list_t* head)
{
    //TODO - Find a way to parse operation correctly (Reverse polish notation...)
    ast_expr_t expr;

    memset(&expr, 0, sizeof(ast_expr_t));

    ast_operation_t* operation = malloc(sizeof(ast_operation_t));
    if (!operation ) {
        PERR(OUT_OF_MEM);
        return expr;
    }
    operation->rpn_list = token_list_to_rpn(head);

    expr.op.type = OP_OPERATION;
    expr.op.operand = (void*)operation;
    return expr;
}
