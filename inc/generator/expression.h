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

typedef struct ast_expr_s ast_expr_t;
typedef struct ast_stack_s ast_stack_t;

char** generate_expression(char** lines, ast_expr_t* expr, ast_stack_t* stack, char** expr_str);

#endif//!GENERATOR_EXPRESSION_H
