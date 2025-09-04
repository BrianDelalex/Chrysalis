/*******************************************************************\
**
**  This file is part of Chrysalis project, and is made available
**  under the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

#ifndef AST_TYPES_H
#define AST_TYPES_H

# include "tokenizer/token_list.h"

typedef enum {
    RETURN,
}ast_statement_type_t;

typedef struct ast_return_statement_t {
    int value;
}ast_return_statement_t;

typedef struct ast_statement_s {
    ast_statement_type_t type;
    void* statement;
}ast_statement_t;

typedef struct ast_function_s {
    struct ast_statement_s* statements;
    char* name;
}ast_function_t;

typedef struct ast_program_s {
    struct ast_function_s* functions;
}ast_program_t;

#endif//!AST_TYPES_H
