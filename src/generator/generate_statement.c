/*******************************************************************\
**
**  This file is part of Chrysalis project, and is made available
**  under the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

# include <stdlib.h>
# include <stdio.h>
# include <errno.h>

# include "parser/ast_types.h"

# include "generator/stack/stack.h"
# include "generator/generator.h"
# include "generator/asm/generate_asm.h"
# include "generator/statement.h"

# include "utils/logging.h"


char** generate_statement(char** lines, ast_statement_t* statement, ast_stack_t* stack)
{
    ast_statement_t* ptr = statement;
    while (ptr) {
        switch (ptr->type) {
            case RETURN:
                lines = generate_return_statement(lines, ptr, stack);
                break;
            case ASSIGN_DECL:
                lines = generate_assignment_statement(lines, ptr, stack);
                break;
            case ASSIGN:
                lines = generate_assignment_statement(lines, ptr, stack);
                break;
            case DECL:
                break;
            default:
                free_lines(lines);
                PERR("Unknow statement type. %d\n", ptr->type);
                return NULL;
        }
        if (!lines) {
            return NULL;
        }
        ptr = ptr->next;
    }

    return lines;
}
