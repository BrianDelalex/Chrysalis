/*******************************************************************\
**
**  this file is part of chrysalis project, and is made available
**  under the terms of the gnu general public license version 3.
**
**  copyright (c) 2025 - brian delalex-fondu
**
\*******************************************************************/

#ifndef STATEMENT_FREE_H
#define STATEMENT_FREE_H

# include "parser/ast_types.h"
void statement_return_free(ast_statement_return_t *statement);
void statement_assign_decl_free(ast_statement_assign_t *statement);
void statement_free(ast_statement_t *statement);

#endif//!STATEMENT_FREE_H
