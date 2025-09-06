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
    OP_IDENTIFIER,
    OP_INTEGER_LITERAL
}ast_expr_operand_type_t;

typedef struct ast_operand_integer_integral_s {
    int value;
}ast_operand_integer_integral_t;

typedef struct ast_operand_identifier_s {
    char *identifier;
}ast_operand_identifier_t;

typedef struct ast_expr_operand_s {
    ast_expr_operand_type_t type;
    void *operand;
}ast_expr_operand_t;

typedef struct ast_expr_s {
    ast_expr_operand_t op;
}ast_expr_t;

typedef enum {
    RETURN,
}ast_statement_type_t;

typedef struct ast_statement_return_s {
    ast_expr_t expr;
    void (*free)(struct ast_statement_return_s *);
}ast_statement_return_t;

typedef struct ast_statement_s {
    ast_statement_type_t type;
    void* statement;
    void (*free_statement)(struct ast_statement_s *);
    struct ast_statement_s *next;
}ast_statement_t;

typedef struct ast_function_s {
    struct ast_statement_s* statements;
    char* name;
}ast_function_t;

typedef struct ast_program_s {
    struct ast_function_s* functions;
}ast_program_t;

ast_statement_t* ast_statement_list_add_node(ast_statement_t* head, ast_statement_t* node);
void ast_statement_list_free(ast_statement_t* head);

void ast_function_free(ast_function_t* func);

void ast_program_free(ast_program_t* prg);

ast_function_t* get_function_ast(token_list_t* head);
ast_statement_t* get_statement_ast(token_list_t** head);

#endif//!AST_TYPES_H
