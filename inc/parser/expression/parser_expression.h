/*******************************************************************\
**
**  This file is part of Chrysalis project, and is made available
**  under the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

#ifndef PARSER_EXPRESSION_H
#define PARSER_EXPRESSION_H

# include "parser/expression/expression_patterns.h"

ast_expr_t parse_integer_literal_expression(token_list_t* head);
ast_expr_t parse_identifier_expression(token_list_t* head);
ast_expr_t parse_operation_expression(token_list_t* head);
ast_expr_t parse_function_call_expression(token_list_t* head);
#endif//!PARSER_EXPRESSION_H
