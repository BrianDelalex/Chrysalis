/*******************************************************************\
**
**  This file is part of Chrysalis project, and is made available
**  under the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

# include "parser/ast_types.h"
# include "parser/stack.h"

# include "utils/logging.h"

# include <stdlib.h>

ast_function_t* ast_function_init(void)
{
    ast_function_t* func = malloc(sizeof(ast_function_t));
    if (!func) {
        PERR(OUT_OF_MEM);
        return NULL;
    }
    func->name = NULL;
    func->statements = NULL;
    func->free = &ast_function_free;
    func->stack = NULL;
    return func;
}

void ast_function_free(ast_function_t* func)
{
    if (func->statements)
        ast_statement_list_free(func->statements);
    if (func->name)
        free(func->name);
    if (func->stack)
        ast_stack_free(func->stack);
    free(func);
}
