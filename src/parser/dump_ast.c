/*******************************************************************\
**
**  This file is part of Chrysalis project, and is made available
**  under the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

# include <stdio.h>

# include "parser/ast_types.h"

# include "utils/logging.h"

static void dump_ast_expr(ast_expr_t expr)
{
    if (expr.op.type == OP_IDENTIFIER) {
            printf("<exp> ::= %s\n", ((ast_operand_identifier_t*)expr.op.operand)->identifier);
    } else if (expr.op.type == OP_INTEGER_LITERAL) {
        printf("<exp> ::= %d\n", ((ast_operand_integer_integral_t *)expr.op.operand)->value);
    } else {
        PERR("Unknow operand type %d\n", expr.op.type);
    }
}

static void dump_ast_statement_return(ast_statement_return_t* ret)
{
    printf("<statement> ::= \"return\" <exp> \";\"\n");
    dump_ast_expr(ret->expr);
}

static void dump_ast_statement_assign(ast_statement_assign_t* ret)
{
    printf("<statement> ::= \"assign\" <var> <exp> \";\"\n");
    printf("<var> ::= %s \"=\" <expr>\n", ret->var.identifier);
    printf("<expr> ::= %d\n", ((ast_operand_integer_integral_t*)ret->expr.op.operand)->value);
}

static void dump_ast_decl(ast_statement_decl_t* decl)
{
    printf("<statement> ::= \"declaration\" <var> \";\"\n");
    printf("<var> ::= %s\n", decl->var.identifier);
}

static void dump_ast_statement(ast_statement_t* statement)
{
    switch(statement->type) {
    case RETURN:
    {
        ast_statement_return_t* rtn = (ast_statement_return_t*)statement->statement;
        dump_ast_statement_return(rtn);
        break;
    }
    case ASSIGN_DECL:
    {
        ast_statement_assign_t* assign = (ast_statement_assign_t*)statement->statement;
        dump_ast_statement_assign(assign);
        break;
    }
    case ASSIGN:
    {
        ast_statement_assign_t* assign = (ast_statement_assign_t*)statement->statement;
        dump_ast_statement_assign(assign);
        break;
    }
    case DECL:
    {
        ast_statement_decl_t* decl = (ast_statement_decl_t*)statement->statement;
        dump_ast_decl(decl);
        break;
    }
    default:
        PERR("Unexpected statement type\n");
    }
}

static void dump_ast_statement_list(ast_statement_t* head)
{
    while (head) {
        dump_ast_statement(head);
        head = head->next;
    }
}

void dump_ast(ast_program_t* program);
void dump_ast(ast_program_t* program)
{
    printf("<program> ::= <function>\n");
    printf("<function> ::= \"int\" <%s> \"(\" \")\" \"{\" <statements> \"}\"\n", program->functions->name);
    dump_ast_statement_list(program->functions->statements);
}
