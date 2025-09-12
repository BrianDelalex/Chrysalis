/*******************************************************************\
**
**  This file is part of Chrysalis project, and is made available
**  under the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

#ifndef EXPRESSION_PATTERNS_H
#define EXPRESSION_PATTERNS_H

# include <stdbool.h>

# include "parser/patterns.h"
# include "parser/ast_types.h"

typedef struct expr_pattern_s {
    const int *tokens;
    int token_count;
    ast_expr_t (*parse_ast)(token_list_t*);
}expr_pattern_t;

extern const int EXPR_INTEGER_LITERAL_TOKENS[];
extern const expr_pattern_t EXPR_INTEGER_LITERAL;

extern const int EXPR_IDENTIFIER_TOKENS[];
extern const expr_pattern_t EXPR_IDENTIFIER;

extern const expr_pattern_t EXPRESSION_PATTERNS[];
extern const unsigned int EXPRESSION_PATTERNS_SIZE;

bool is_expression_valid(token_list_t **head, const expr_pattern_t** expr_patt);

#endif//!EXPRESSION_PATTERNS_H
