/*******************************************************************\
**
**  This file is part of Chrysalis project, and is made available
**  under the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

#ifndef PATTERNS_H
#define PATTERNS_H

# include "tokenizer/token_list.h"

# define EXTENDED_TOKEN_TYPES_START UNKNOW + 1

typedef enum {
    TOKEN_EXPR = EXTENDED_TOKEN_TYPES_START,
    TOKEN_RETURN
}token_type_ext_t;

# define GET_TOKEN_COUNT(tokens) sizeof(tokens) / sizeof(int)

typedef enum {
    FUNCTION_DECL,
    STATEMENT,
    EXPR,
}PATTERN_TYPE;

typedef struct pattern_s {
    const int *tokens;
    int token_count;
    PATTERN_TYPE type;
    void *(*ast_gen)(token_list_t *);
}pattern_t;

const pattern_t* find_function_pattern(token_list_t* head);
const pattern_t* find_statement_pattern(token_list_t** head);

#endif//!PATTERNS_H
