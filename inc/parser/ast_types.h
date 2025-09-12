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

# include <stdint.h>

# include "tokenizer/token_list.h"

# include "parser/types/types.h"

typedef enum {
    OP_IDENTIFIER,
    OP_INTEGER_LITERAL,
    OP_OPERATION
}OPERAND_TYPE_T;

typedef struct ast_operand_integer_integral_s {
    int value;
}ast_operand_integer_integral_t;

typedef struct ast_operand_identifier_s {
    char *identifier;
}ast_operand_identifier_t;

typedef struct ast_expr_operand_s {
    OPERAND_TYPE_T type;
    void *operand;
}ast_expr_operand_t;

typedef struct ast_expr_s {
    ast_expr_operand_t op;
}ast_expr_t;

typedef struct ast_variable_s {
    char* identifier;
    type_t type;
}ast_variable_t;

typedef enum {
    RETURN,
    ASSIGN,
    ASSIGN_DECL,
    DECL,
}ast_statement_type_t;

typedef struct ast_statement_decl_s {
    ast_variable_t var;
    void (*free)(struct ast_statement_decl_s*);
}ast_statement_decl_t;

typedef struct ast_statement_assign_s {
    ast_variable_t var;
    ast_expr_t expr;
    void (*free)(struct ast_statement_assign_s *);
}ast_statement_assign_t;

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

typedef struct ast_stack_entry_s {
    uint64_t offset;
    uint64_t size;
    char* identifier;
    struct ast_stack_entry_s* next;
}ast_stack_entry_t;

typedef struct ast_stack_s {
    ast_stack_entry_t* entries;
}ast_stack_t;

typedef struct ast_function_s {
    char* name;
    void (*free)(struct ast_function_s*);
    ast_statement_t* statements;
    ast_stack_t* stack;
}ast_function_t;

typedef struct ast_program_s {
    struct ast_function_s* functions;
}ast_program_t;


/* ast statement list functions */
ast_statement_t* ast_statement_list_add_node(ast_statement_t* head, ast_statement_t* node);
void ast_statement_list_free(ast_statement_t* head);

/* ast structs init functions */
ast_function_t* ast_function_init(void);

/* ast structs free functions */
void ast_function_free(ast_function_t* func);
void ast_program_free(ast_program_t* prg);

/* ast struct creation function */
ast_function_t* parse_function_ast(token_list_t* head);
ast_statement_t* parse_statement_ast(token_list_t** head);

/* ast struct initialization macro */
# define INIT_AST_FUNCTION(func) func = {.statement = NULL, .name = NULL, .free = &ast_function_free}

#endif//!AST_TYPES_H
