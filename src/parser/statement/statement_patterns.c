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
# include <stdio.h>

void* create_statement_return_ast(token_list_t* head);

static void *not_implemented(token_list_t *)
{
    printf("NOT IMPLEMENTED!\n");
    return NULL;
}

const int STATEMENT_RET_EXPR_TOKENS[] = {TOKEN_RETURN, TOKEN_EXPR, SEMICOLON};
const pattern_t STATEMENT_RET_EXPR = {
    .tokens = STATEMENT_RET_EXPR_TOKENS,
    .token_count = GET_TOKEN_COUNT(STATEMENT_RET_EXPR_TOKENS),
    .type = STATEMENT,
    .ast_create = &create_statement_return_ast
};

const int STATEMENT_VAR_DECL_TOKENS[] = {KEYWORD, IDENTIFIER, SEMICOLON};
const pattern_t STATEMENT_VAR_DECL = {
    .tokens = STATEMENT_VAR_DECL_TOKENS,
    .token_count = GET_TOKEN_COUNT(STATEMENT_VAR_DECL_TOKENS),
    .type = STATEMENT,
    .ast_create = &not_implemented
};

const int STATEMENT_VAR_DECL_ASSIGN_TOKENS[] = {KEYWORD, IDENTIFIER, EQUAL, TOKEN_EXPR, SEMICOLON};
const pattern_t STATEMENT_VAR_DECL_ASSIGN = {
    .tokens = STATEMENT_VAR_DECL_ASSIGN_TOKENS,
    .token_count = GET_TOKEN_COUNT(STATEMENT_VAR_DECL_ASSIGN_TOKENS),
    .type = STATEMENT,
    .ast_create = not_implemented,
};

const pattern_t STATEMENT_PATTERNS[] = {
    STATEMENT_RET_EXPR,
    STATEMENT_VAR_DECL,
    STATEMENT_VAR_DECL_ASSIGN,
};
const unsigned int STATEMENT_PATTERNS_SIZE = sizeof(STATEMENT_PATTERNS) / sizeof(pattern_t);
