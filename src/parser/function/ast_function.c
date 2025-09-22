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
# include "parser/stack.h"
# include "parser/variable_list.h"

# include "utils/logging.h"


ast_function_t* ast_function_init(void)
{
    ast_function_t* func = malloc(sizeof(ast_function_t));
    if (!func) {
        PERR(OUT_OF_MEM);
        return NULL;
    }

    func->name = NULL;
    func->parameters = NULL;
    func->statements = NULL;
    func->free = &ast_function_free;

    func->stack = malloc(sizeof(ast_stack_t));
    if (!func->stack) {
        PERR(OUT_OF_MEM);
        return NULL;
    }
    memset(func->stack, 0, sizeof(ast_stack_t));

    return func;
}

void ast_function_free(ast_function_t* func)
{
    if (func->parameters)
        variable_list_free(func->parameters);
    if (func->statements)
        ast_statement_list_free(func->statements);
    if (func->name)
        free(func->name);
    if (func->stack)
        ast_stack_free(func->stack);
    free(func);
}
