/*******************************************************************\
**
**  This file is part of Chrysalis project, and is made available
**  under the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

#ifndef VARIABLE_LIST_H
#define VARIABLE_LIST_H

# include "parser/ast_types.h"

typedef struct variable_list_s {
    ast_variable_t var;
    struct variable_list_s* next;
}variable_list_t;

variable_list_t* variable_list_add_node(variable_list_t* head, variable_list_t* node);
variable_list_t* variable_list_create_node(variable_list_t* head, ast_variable_t var);
uint32_t variable_list_size(variable_list_t* head);
void variable_list_free(variable_list_t* head);

#endif//!VARIABLE_LIST_H
