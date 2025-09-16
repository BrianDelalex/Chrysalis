/*******************************************************************\
**
**  This file is part of Chrysalis project, and is made available
**  under the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

#ifndef GENERATOR_EXPRESSION_H
#define GENERATOR_EXPRESSION_H

# include "generator/function.h"

typedef struct ast_expr_s ast_expr_t;
typedef struct ast_stack_s ast_stack_t;

bool generate_expression(gen_func_data_t* data, ast_expr_t* expr, char** expr_str);

#endif//!GENERATOR_EXPRESSION_H
