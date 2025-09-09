/*******************************************************************\
**
**  This file is part of Chrysalis project, and is made available
**  under the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

# include "parser/stack.h"

static int popuplate_function_stack_struct(ast_function_t* func)
{
    ast_statement_t* statements = func->statements;

    while (statements) {
        if (statements->type == ASSIGN) {
            ast_statement_assign_t* assign = (ast_statement_assign_t*)statements->statement;

            if (ast_stack_add_entry(func->stack, assign->var.type.size, assign->var.identifier) != 0)
                return -1;
        }
        statements = statements->next;
    }

    return 0;
}

int populate_stack_struct(ast_program_t* prg)
{
    if (prg->functions) {
        if (popuplate_function_stack_struct(prg->functions) != 0)
            return -1;
    }
    return 0;
}
