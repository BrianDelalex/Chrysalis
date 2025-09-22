/*******************************************************************\
**
**  This file is part of Chrysalis project, and is made available
**  under the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

#ifndef FUNCTION_LIST_H
#define FUNCTION_LIST_H

# include "parser/ast_types.h"

typedef struct function_list_s {
    ast_function_t* func;
    struct function_list_s* next;
}function_list_t;


function_list_t* function_list_add_node(function_list_t* head, function_list_t* node);
function_list_t* function_list_create_node(function_list_t* head, ast_function_t* func);
void function_list_free(function_list_t* head);

#endif//!FUNCTION_LIST_H
