/*******************************************************************\
**
**  This file is part of Chrysalis project, and is made available
**  under the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/


# include "parser/patterns.h"

# include "parser/function/ast_create_functions.h"

const int FUNC_DECL_NO_ARG_TOKENS[] = {KEYWORD, IDENTIFIER, PARENTHESES_OPEN, PARENTHESES_CLOSE, CURLY_OPEN};
const pattern_t FUNC_DECL_NO_ARG = {
    .tokens = FUNC_DECL_NO_ARG_TOKENS,
    .type = FUNCTION_DECL,
    .ast_create = &create_function_decl_ast,
};

const pattern_t FUNCTION_PATTERNS[] = {
    FUNC_DECL_NO_ARG,
};
const unsigned int FUNCTION_PATTERNS_SIZE = sizeof(FUNCTION_PATTERNS) / sizeof(pattern_t);
