/*******************************************************************\
**
**  This file is part of Chrysalis project, and is made available
**  under the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

# include "parser/ast_types.h"

# include "parser/patterns.h"

# include "utils/logging.h"

# include <stdlib.h>
# include <string.h>

ast_statement_t* get_statement_ast(token_list_t** head)
{
    token_list_t* head_save = *head;
    const pattern_t* pattern = find_statement_pattern(head);

    if (!pattern) {
        PERR("Expected statement starting at:");
        token_dump(*head_save);
        return NULL;
    }
    return pattern->ast_gen(head_save);
}

ast_statement_return_t* get_ast_statement_return(token_list_t* head)
{
    ast_statement_return_t* rtn_statement;

    if (!head)
        return NULL;

    rtn_statement = malloc(sizeof(ast_statement_return_t));
    if (!rtn_statement) {
        PERR(OUT_OF_MEM);
        return NULL;
    }


    switch (head->token.type) {
    case INTEGER_LITERAL:
    {
        ast_operand_integer_integral_t* op = malloc(sizeof(ast_operand_integer_integral_t));
        if (!op) {
            PERR(OUT_OF_MEM);
            return NULL;
        }
        op->value = atoi(head->token.value);
        rtn_statement->expr.op.type = OP_INTEGER_LITERAL;
        rtn_statement->expr.op.operand = (void *)op;
        return rtn_statement;
    }
    case IDENTIFIER:
    {
        ast_operand_identifier_t* op = malloc(sizeof(ast_operand_identifier_t));
        if (!op) {
            PERR(OUT_OF_MEM);
            return NULL;
        }
        op->identifier = head->token.value;
        rtn_statement->expr.op.type = OP_IDENTIFIER;
        rtn_statement->expr.op.operand = (void*)op;
        return rtn_statement;
    }
    default:
        PERR("Expected IDENTIFIER or INTEGER_LITERAL after 'return'\n");
        return NULL;
    }
}

void* get_statement_ret(token_list_t* head)
{
    ast_statement_t* statement;
    ast_statement_return_t* rtn_statement;

    if (!head || head->token.type != KEYWORD || strcmp(head->token.value, "return") != 0) { \
        PERR("Expected 'return' keyword instead found:");                                   \
        if (head)                                                                           \
            token_dump(*head);                                                              \
        else                                                                                \
            PERR("END OF FILE \n");                                                         \
        return NULL;                                                                        \
    }
    head = head->next;

    rtn_statement = get_ast_statement_return(head);
    if (!rtn_statement)
        return NULL;
    head = head->next;

    if (!head || head->token.type != SEMICOLON) {
        PERR("Expected ';' after return\n");
        free(rtn_statement);
        return NULL;
    }
    statement = malloc(sizeof(ast_statement_t));
    if (!statement) {
        PERR(OUT_OF_MEM);
        return NULL;
    }
    statement->type = RETURN;
    statement->statement = rtn_statement;
    return statement;
}
