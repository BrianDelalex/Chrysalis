/*******************************************************************\
**
**  This file is part of Chrysalis project, and is made available
**  under the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

# include "parser/patterns.h"

# include <stddef.h>

const int EXPR_INTEGER_LITERAL_TOKENS[] = {INTEGER_LITERAL};
const pattern_t EXPR_INTEGER_LITERAL = {
    .tokens = EXPR_INTEGER_LITERAL_TOKENS,
    .token_count = GET_TOKEN_COUNT(EXPR_INTEGER_LITERAL_TOKENS),
    .type = EXPR,
    .ast_create = NULL
};

const int EXPR_IDENTIFIER_TOKENS[] = {IDENTIFIER};
const pattern_t EXPR_IDENTIFIER = {
    .tokens = EXPR_IDENTIFIER_TOKENS,
    .token_count = GET_TOKEN_COUNT(EXPR_IDENTIFIER_TOKENS),
    .type = EXPR,
    .ast_create = NULL
};

const pattern_t EXPRESSION_PATTERNS[] = {
    EXPR_INTEGER_LITERAL,
    EXPR_IDENTIFIER
};
const unsigned int EXPRESSION_PATTERNS_SIZE = sizeof(EXPRESSION_PATTERNS) / sizeof(pattern_t);
