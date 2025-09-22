/*******************************************************************\
**
**  This file is part of Chrysalis project, and is made available
**  under the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

# include "parser/stack.h"
# include "parser/function/function_list.h"
# include "parser/variable_list.h"

static int populate_function_stack_struct(ast_function_t* func)
{
    variable_list_t* parameters = func->parameters;
    ast_statement_t* statements = func->statements;


    while (parameters) {
        if (ast_stack_add_entry(func->stack, parameters->var.type.size, parameters->var.identifier) != 0)
            return -1;
        parameters = parameters->next;
    }

    while (statements) {
        if (statements->type == ASSIGN_DECL) {
            ast_statement_assign_t* assign = (ast_statement_assign_t*)statements->statement;

            if (ast_stack_add_entry(func->stack, assign->var.type.size, assign->var.identifier) != 0)
                return -1;
        } else if (statements->type == DECL) {
            ast_statement_decl_t* decl = (ast_statement_decl_t*)statements->statement;
            if(ast_stack_add_entry(func->stack, decl->var.type.size, decl->var.identifier) != 0)
                return -1;
        }
        statements = statements->next;
    }

    return 0;
}

int populate_stack_struct(ast_program_t* prg)
{
    function_list_t* ptr = prg->functions;
    while (ptr) {
        if (populate_function_stack_struct(ptr->func) != 0)
            return -1;
        ptr = ptr->next;
    }
    return 0;
}
