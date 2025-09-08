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
# include "parser/statement/ast_create_statement.h"
# include "parser/statement/statement_free.h"
# include "parser/types/types.h"
# include "parser/expression/expression.h"

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

void* create_statement_assigment_decl_ast(token_list_t* head)
{
    ast_statement_t* statement;
    ast_statement_assign_t* assign;

    statement = malloc(sizeof(ast_statement_t));
    if (!statement) {
        PERR(OUT_OF_MEM);
        return NULL;
    }
    memset(statement, 0, sizeof(ast_statement_t));
    statement->type = ASSIGN;
    statement->free_statement = &statement_free;

    assign = malloc(sizeof(ast_statement_assign_t));
    if (!assign) {
        PERR(OUT_OF_MEM);
        return NULL;
    }
    statement->statement = (void*) assign;

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

    if (create_ast_expression(&head, &(assign->expr)) != 0) {
        PERR("ERROR - unable to create ast_expression\n");
        return NULL;
    }
    PERR("TODO - REGISTER STACK ENTRY\n");
    return statement;
}
