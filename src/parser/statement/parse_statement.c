/*******************************************************************\
**
**  This file is part of Chrysalis project, and is made available
**  under the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

# include "parser/ast_types.h"
# include "parser/statement/statement_patterns.h"
# include "parser/expression/expression_patterns.h"

# include "utils/logging.h"

# include <string.h>

ast_statement_t* parse_statement_ast(token_list_t** head)
{
    token_list_t* head_save = *head;
    const expr_pattern_t* expr_patt = NULL;
    const statement_pattern_t* pattern = find_statement_pattern(head, &expr_patt);

    if (!pattern) {
        PERR("Expected statement starting at:");
        token_dump(*head_save);
        return NULL;
    }

    return pattern->parse_ast(head_save, expr_patt);
}
