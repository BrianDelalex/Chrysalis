/*******************************************************************\
**
**  This file is part of Chrysalis project, and is made available
**  under the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

# include "parser/ast_types.h"

# include <stdlib.h>

void ast_function_free(ast_function_t* func)
{
    if (func->statements)
        ast_statement_list_free(func->statements);
    if (func->name)
        free(func->name);
    free(func);
}
