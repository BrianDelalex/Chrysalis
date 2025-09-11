/*******************************************************************\
**
**  This file is part of Chrysalis project, and is made available
**  under the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

# include <string.h>
# include <stdlib.h>

# include "parser/ast_types.h"
# include "parser/statement/parser_statement.h"
# include "parser/statement/statement_free.h"
# include "parser/types/types.h"
# include "parser/expression/parser_expression.h"

# include "utils/logging.h"
# include "utils/string_manipulation.h"

static type_t get_type(token_list_t** head)
{
    token_list_t* ptr = *head;
    for (unsigned int i = 0; i < BUILTIN_TYPES_SIZE; i++) {
        if (ptr->token.value && strcmp(ptr->token.value, BUILTIN_TYPE_IDENTIFIERS[i]) == 0) {
            *head = ptr->next;
            return BUILTIN_TYPES[i];
        }
        ptr = ptr->next;
    }
    return (type_t) {.type_id = -1, .size = 0};
}

static ast_statement_t* create_ast_statement_struct(ast_statement_type_t type)
{
    ast_statement_t *statement = malloc(sizeof(ast_statement_t));

    if (!statement) {
        PERR(OUT_OF_MEM);
        return NULL;
    }
    memset(statement, 0, sizeof(ast_statement_t));
    statement->type = type;
    statement->free_statement = &statement_free;
    return statement;
}

void* parse_decl_assignment_statement_ast(token_list_t* head)
{
    ast_statement_t* statement;
    ast_statement_assign_t* assign;

    statement = create_ast_statement_struct(ASSIGN_DECL);
    if (!statement) {
        return NULL;
    }

    assign = malloc(sizeof(ast_statement_assign_t));
    if (!assign) {
        PERR(OUT_OF_MEM);
        return NULL;
    }
    statement->statement = (void*) assign;
    assign->free = &statement_assign_decl_free;

    type_t type = get_type(&head);
    if (type.type_id == -1) {
        PERR("Unknow type.\n");
        return NULL;
    }
    assign->var.type = type;

    char *identifier = copy_string(head->token.value);
    if (!identifier) {
        return NULL;
    }
    assign->var.identifier = identifier;
    head = head->next;

    // Skip '=' token
    head = head->next;

    if (parse_ast_expression(&head, &(assign->expr)) != 0) {
        PERR("ERROR - unable to create ast_expression\n");
        return NULL;
    }
    return statement;
}

void *parse_decl_statement_ast(token_list_t* head)
{
    ast_statement_t* statement;
    ast_statement_decl_t* decl;

    statement = create_ast_statement_struct(DECL);
    if (!statement)
        return NULL;

    decl = malloc(sizeof(ast_statement_decl_t));
    if (!decl) {
        PERR(OUT_OF_MEM);
        free(statement);
        return NULL;
    }
    decl->free = &statement_decl_free;

    statement->statement = (void*) decl;

    type_t type = get_type(&head);
    if (type.type_id == -1) {
        PERR("Unknow type.\n");
        return NULL;
    }
    decl->var.type = type;

    char *identifier = copy_string(head->token.value);
    if (!identifier) {
        return NULL;
    }
    decl->var.identifier = identifier;
    return statement;
}

void* parse_assignment_statement_ast(token_list_t* head)
{
    ast_statement_t* statement;
    ast_statement_assign_t* assign;

    statement = create_ast_statement_struct(ASSIGN);
    if (!statement) {
        return NULL;
    }

    assign = malloc(sizeof(ast_statement_assign_t));
    if (!assign) {
        PERR(OUT_OF_MEM);
        return NULL;
    }
    statement->statement = (void*) assign;
    assign->free = &statement_assign_decl_free;

    assign->var.type.type_id = -1;
    assign->var.type.size = 0;

    char *identifier = copy_string(head->token.value);
    if (!identifier) {
        return NULL;
    }
    assign->var.identifier = identifier;
    head = head->next;

    // Skip '=' token
    head = head->next;

    if (parse_ast_expression(&head, &(assign->expr)) != 0) {
        PERR("ERROR - unable to create ast_expression\n");
        return NULL;
    }
    return statement;
}
