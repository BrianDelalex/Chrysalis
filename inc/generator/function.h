/*******************************************************************\
**
**  This file is part of Chrysalis project, and is made available
**  under the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

#ifndef GENERATOR_FUNCTION_H
#define GENERATOR_FUNCTION_H

# include <stdbool.h>

# include "generator.h"

typedef struct ast_stack_s ast_stack_t;
typedef struct ast_function_s ast_function_t;

typedef struct gen_func_data_s {
    gen_data_t* gen_data;
    ast_stack_t* stack;
}gen_func_data_t;

bool generate_function(gen_data_t* gen_data, ast_function_t* func);
bool generate_start_function(gen_data_t* gen_data);

#endif//!GENERATOR_FUNCTION_H
