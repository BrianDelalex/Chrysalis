/*******************************************************************\
**
**  This file is part of Chrysalis project, and is made available
**  under the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

# include "parser/patterns.h"

# include "parser/statement/parser_statement.h"
# include "parser/statement/statement_patterns.h"

# include <stddef.h>
# include <stdio.h>

const int STATEMENT_RET_EXPR_TOKENS[] = {TOKEN_RETURN, TOKEN_EXPR, SEMICOLON};
const statement_pattern_t STATEMENT_RET_EXPR = {
    .tokens = STATEMENT_RET_EXPR_TOKENS,
    .token_count = GET_TOKEN_COUNT(STATEMENT_RET_EXPR_TOKENS),
    .parse_ast = &parse_return_statement_ast
};
const int STATEMENT_VAR_DECL_TOKENS[] = {TOKEN_TYPE, IDENTIFIER, SEMICOLON};
const statement_pattern_t STATEMENT_VAR_DECL = {
    .tokens = STATEMENT_VAR_DECL_TOKENS,
    .token_count = GET_TOKEN_COUNT(STATEMENT_VAR_DECL_TOKENS),
    .parse_ast = &parse_decl_statement_ast
};

const int STATEMENT_VAR_DECL_ASSIGN_TOKENS[] = {TOKEN_TYPE, IDENTIFIER, EQUAL, TOKEN_EXPR, SEMICOLON};
const statement_pattern_t STATEMENT_VAR_DECL_ASSIGN = {
    .tokens = STATEMENT_VAR_DECL_ASSIGN_TOKENS,
    .token_count = GET_TOKEN_COUNT(STATEMENT_VAR_DECL_ASSIGN_TOKENS),
    .parse_ast = &parse_decl_assignment_statement_ast
};

const int STATEMENT_ASSIGN_TOKENS[] = {IDENTIFIER, EQUAL, TOKEN_EXPR, SEMICOLON};
const statement_pattern_t STATEMENT_ASSIGN = {
    .tokens = STATEMENT_ASSIGN_TOKENS,
    .token_count = GET_TOKEN_COUNT(STATEMENT_ASSIGN_TOKENS),
    .parse_ast = &parse_assignment_statement_ast
};

const statement_pattern_t STATEMENT_PATTERNS[] = {
    STATEMENT_RET_EXPR,
    STATEMENT_VAR_DECL,
    STATEMENT_VAR_DECL_ASSIGN,
    STATEMENT_ASSIGN,
};
const unsigned int STATEMENT_PATTERNS_SIZE = sizeof(STATEMENT_PATTERNS) / sizeof(pattern_t);
