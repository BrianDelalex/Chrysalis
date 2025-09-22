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
# include "parser/operation/ast_operation.h"
# include "parser/operation/rpn_double_chained_list.h"
# include "parser/function/function_list.h"
# include "parser/expression/function_call.h"

# include "utils/logging.h"

static void dump_ast_expr(ast_expr_t expr)
{
    if (expr.op.type == OP_IDENTIFIER) {
            printf("<exp> ::= %s\n", ((ast_operand_identifier_t*)expr.op.operand)->identifier);
    } else if (expr.op.type == OP_INTEGER_LITERAL) {
        printf("<exp> ::= %d\n", ((ast_operand_integer_integral_t *)expr.op.operand)->value);
    } else if (expr.op.type == OP_FUNC_CALL) {
        printf("<exp> ::= %s()\n", ((ast_function_call_t*)expr.op.operand)->func_name);
    } else if (expr.op.type == OP_OPERATION) {
        printf("<exp> ::= ");
        rpn_double_chained_list_t* rpn_list = ((ast_operation_t*)expr.op.operand)->rpn_list;
        while (rpn_list) {
            if (rpn_list->token == OPERAND_IDENTIFIER)
                printf("%s ", rpn_list->data.identifier);
            else if (rpn_list->token == OPERAND_INT)
                printf("%ld ", rpn_list->data.value);
            else
                printf("%c ", (char) rpn_list->data.value);
            rpn_list = rpn_list->next;
        }
        printf("\n");
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
    dump_ast_expr(ret->expr);
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
    function_list_t* ptr = program->functions;
    while (ptr) {
        printf("<program> ::= <function>\n");
        printf("<function> ::= \"int\" <%s> \"(\" \")\" \"{\" <statements> \"}\"\n", ptr->func->name);
        dump_ast_statement_list(ptr->func->statements);
        printf("<stack> ::= ");
        ast_stack_entry_t* stack_entry = ptr->func->stack->entries;
        while (stack_entry) {
            printf("[%s, size:%ld, offset:%ld] ", stack_entry->identifier, stack_entry->size, stack_entry->offset);
            stack_entry = stack_entry->next;
        }
        printf("\n");
        printf("\n\n");
        ptr = ptr->next;
    }
}
