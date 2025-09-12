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
# include "parser/ast_types.h"

# include <stddef.h>
# include <stdio.h>

typedef struct expr_pattern_s expr_pattern_t;

typedef struct statement_pattern_s {
    const int *tokens;
    int token_count;
    ast_statement_t* (*parse_ast)(token_list_t*, const expr_pattern_t*);
}statement_pattern_t;


const statement_pattern_t* find_statement_pattern(token_list_t** head, const expr_pattern_t** pattern);

extern const int STATEMENT_RET_EXPR_TOKENS[];
extern const statement_pattern_t STATEMENT_RET_EXPR;

extern const int STATEMENT_VAR_DECL_TOKENS[];
extern const statement_pattern_t STATEMENT_VAR_DECL;

extern const int STATEMENT_VAR_DECL_ASSIGN_TOKENS[];
extern const statement_pattern_t STATEMENT_VAR_DECL_ASSIGN;

extern const statement_pattern_t STATEMENT_PATTERNS[];
extern const unsigned int STATEMENT_PATTERNS_SIZE;

#endif//!STATEMENT_PATTERNS_H
