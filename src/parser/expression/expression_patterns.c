/*******************************************************************\
**
**  This file is part of Chrysalis project, and is made available
**  under the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

# include "parser/expression/expression_patterns.h"
# include "parser/expression/parser_expression.h"

# include <stddef.h>

const int EXPR_INTEGER_LITERAL_TOKENS[] = {INTEGER_LITERAL, SEMICOLON};
const expr_pattern_t EXPR_INTEGER_LITERAL = {
    .tokens = EXPR_INTEGER_LITERAL_TOKENS,
    .token_count = GET_TOKEN_COUNT(EXPR_INTEGER_LITERAL_TOKENS),
    .parse_ast = &parse_integer_literal_expression
};

const int EXPR_IDENTIFIER_TOKENS[] = {IDENTIFIER, SEMICOLON};
const expr_pattern_t EXPR_IDENTIFIER = {
    .tokens = EXPR_IDENTIFIER_TOKENS,
    .token_count = GET_TOKEN_COUNT(EXPR_IDENTIFIER_TOKENS),
    .parse_ast = &parse_identifier_expression
};

const int EXPR_OPERATION_TOKENS[] = {TOKEN_OPERATION, SEMICOLON};
const expr_pattern_t EXPR_OPERATION = {
    .tokens = EXPR_OPERATION_TOKENS,
    .token_count = GET_TOKEN_COUNT(EXPR_OPERATION_TOKENS),
    .parse_ast = &parse_operation_expression
};

const expr_pattern_t EXPRESSION_PATTERNS[] = {
    EXPR_INTEGER_LITERAL,
    EXPR_IDENTIFIER,
    EXPR_OPERATION,
};
const unsigned int EXPRESSION_PATTERNS_SIZE = sizeof(EXPRESSION_PATTERNS) / sizeof(pattern_t);
