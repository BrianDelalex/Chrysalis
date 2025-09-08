/*******************************************************************\
**
**  This file is part of Chrysalis project, and is made available
**  under the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

#ifndef STACK_H
#define STACK_H

# include "parser/ast_types.h"

void ast_stack_free(ast_stack_t *stack);
ast_stack_t *ast_stack_create(void);
int ast_stack_add_entry(ast_stack_t* stack, uint64_t size, const char*identifier);

#endif//!STACK_H
