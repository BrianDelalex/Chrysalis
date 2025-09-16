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

# include <stdbool.h>

struct ast_stack_s;
typedef struct ast_stack_s ast_stack_t;
typedef struct gen_data_s gen_data_t;

# define ACCESS_STACK_FMT "%s [rbp-%ld]"

bool generate_stack_setup(gen_data_t* lines);
bool generate_stack_restore(gen_data_t* lines);

const char* ast_get_accumulator_register_from_size(ast_stack_t* stack, const char* identifer);
char *asm_string_access_stack(ast_stack_t* stack, const char* identifier);

#endif//!GENERATOR_STACK_H
