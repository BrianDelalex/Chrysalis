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

# define ACCESS_STACK_FMT "%s [rbp-%ld]"

char** generate_stack_setup(char** lines);
char** generate_stack_restore(char** lines);

const char* ast_get_accumulator_register_from_size(ast_stack_t* stack, const char* identifer);
char *asm_string_access_stack(ast_stack_t* stack, const char* identifier);

#endif//!GENERATOR_STACK_H
