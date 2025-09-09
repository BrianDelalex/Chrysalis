/*******************************************************************\
**
**  This file is part of Chrysalis project, and is made available
**  under the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

#ifndef STATEMENT_PATTERNS_H
#define STATEMENT_PATTERNS_H

# include "parser/patterns.h"

# include <stddef.h>
# include <stdio.h>

void* parse_return_statement_ast(token_list_t* head);


extern const int STATEMENT_RET_EXPR_TOKENS[];
extern const pattern_t STATEMENT_RET_EXPR;

extern const int STATEMENT_VAR_DECL_TOKENS[];
extern const pattern_t STATEMENT_VAR_DECL;

extern const int STATEMENT_VAR_DECL_ASSIGN_TOKENS[];
extern const pattern_t STATEMENT_VAR_DECL_ASSIGN;

extern const pattern_t STATEMENT_PATTERNS[];
extern const unsigned int STATEMENT_PATTERNS_SIZE;

#endif//!STATEMENT_PATTERNS_H
