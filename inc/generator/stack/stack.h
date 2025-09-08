/*******************************************************************\
**
**  This file is part of Chrysalis project, and is made available
**  under the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

#ifndef GENERATOR_STACK_H
#define GENERATOR_STACK_H

struct ast_stack_s;
typedef struct ast_stack_s ast_stack_t;

# define ACCESS_STACK_FMT "%s -%ld[rbp]"

char *asm_string_access_stack(ast_stack_t* stack, const char* identifier);

#endif//!GENERATOR_STACK_H
