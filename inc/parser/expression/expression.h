/*******************************************************************\
**
**  This file is part of Chrysalis project, and is made available
**  under the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

#ifndef EXPRESSION_H
#define EXPRESSION_H

typedef struct token_list_s token_list_t;
typedef struct ast_expr_s ast_expr_t;

int create_ast_expression(token_list_t **head, ast_expr_t* expr);

#endif//!EXPRESSION_H
