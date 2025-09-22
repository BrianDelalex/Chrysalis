/*******************************************************************\
**
**  This file is part of Chrysalis project, and is made available
**  under the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

# include <stdlib.h>
# include <string.h>

# include "attributes.h"

# include "parser/ast_types.h"
# include "parser/statement/parser_statement.h"
# include "parser/statement/statement_free.h"

# include "utils/logging.h"

ast_statement_t* parse_return_statement_ast(token_list_t* head, const expr_pattern_t* expr_patt)
{
    ast_statement_t* statement;
    ast_statement_return_t* rtn_statement;

    // Skip keyword 'return'
    head = head->next;

    rtn_statement = malloc(sizeof(ast_statement_return_t));
    if (!rtn_statement) {
        PERR(OUT_OF_MEM);
        return NULL;
    }
    memset(rtn_statement, 0, sizeof(ast_statement_return_t));
    rtn_statement->free = &statement_return_free;

    rtn_statement->expr = expr_patt->parse_ast(head);
    head = head->next;

    statement = malloc(sizeof(ast_statement_t));
    if (!statement) {
        PERR(OUT_OF_MEM);
        rtn_statement->free(rtn_statement);
        return NULL;
    }
    memset(statement, 0, sizeof(ast_statement_t));
    statement->type = RETURN;
    statement->statement = rtn_statement;
    statement->free_statement = &statement_free;
    return statement;
}
