/*******************************************************************\
**
**  This file is part of Chrysalis project, and is made available
**  under the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

#ifndef FUNCTION_PATTERNS_H
#define FUNCTION_PATTERNS_H

# include "parser/patterns.h"

# include "parser/ast_types.h"

void *get_function_decl_ast(token_list_t* head);

const int FUNC_DECL_NO_ARG_TOKENS[] = {KEYWORD, IDENTIFIER, PARENTHESES_OPEN, PARENTHESES_CLOSE, CURLY_OPEN};
const pattern_t FUNC_DECL_NO_ARG = {
    .tokens = FUNC_DECL_NO_ARG_TOKENS,
    .type = FUNCTION_DECL,
    .ast_gen = &get_function_decl_ast,
};

const pattern_t FUNCTION_PATTERNS[] = {
    FUNC_DECL_NO_ARG,
};

#endif//!FUNCTION_PATTERNS_H
