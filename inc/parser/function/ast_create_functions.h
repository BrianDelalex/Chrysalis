/*******************************************************************\
**
**  This file is part of Chrysalis project, and is made available
**  under the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

#ifndef AST_CREATE_FUNCTIONS_H
#define AST_CREATE_FUNCTIONS_H

# include "tokenizer/token_list.h"

void* create_function_decl_ast(token_list_t* head);

#endif//!AST_CREATE_FUNCTIONS_H
