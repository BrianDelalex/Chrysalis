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
    return pattern->ast_create(head_save);
}
