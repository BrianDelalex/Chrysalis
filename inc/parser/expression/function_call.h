/*******************************************************************\
**
**  This file is part of Chrysalis project, and is made available
**  under the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

#ifndef FUNCTION_CALL_H
#define FUNCTION_CALL_H

# include "parser/expression/expression_list.h"

typedef struct ast_function_call_s {
    char* func_name;
    expr_list_t* args;
}ast_function_call_t;

#endif//!FUNCTION_CALL_H
