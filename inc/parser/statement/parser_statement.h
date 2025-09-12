/*******************************************************************\
**
**  This file is part of Chrysalis project, and is made available
**  under the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

#ifndef AST_CREATE_STATEMENT_H
#define AST_CREATE_STATEMENT_H

# include "tokenizer/token_list.h"
# include "parser/ast_types.h"
# include "parser/expression/expression_patterns.h"

ast_statement_t* parse_return_statement_ast(token_list_t* head, const expr_pattern_t* expr_pattern);
ast_statement_t* parse_decl_assignment_statement_ast(token_list_t* head, const expr_pattern_t* expr_pattern);
ast_statement_t* parse_decl_statement_ast(token_list_t* head, const expr_pattern_t* expr_pattern);
ast_statement_t* parse_assignment_statement_ast(token_list_t* head, const expr_pattern_t* expr_pattern);

#endif//!AST_CREATE_STATEMENT_H
