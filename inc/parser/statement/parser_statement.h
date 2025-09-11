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

void* parse_return_statement_ast(token_list_t* head);
void* parse_decl_assignment_statement_ast(token_list_t* head);
void* parse_decl_statement_ast(token_list_t* head);
void* parse_assignment_statement_ast(token_list_t* head);

#endif//!AST_CREATE_STATEMENT_H
