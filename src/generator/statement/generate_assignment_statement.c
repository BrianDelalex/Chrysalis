/*******************************************************************\
**
**  This file is part of Chrysalis project, and is made available
**  under the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

# include <stdlib.h>

# include "generator/generator.h"
# include "generator/asm/generate_asm.h"
# include "generator/stack/stack.h"
# include "generator/expression.h"
# include "generator/statement.h"

char** generate_assignment_statement(char** lines, ast_statement_t* statement, ast_stack_t* stack)
{
    ast_statement_assign_t* assign = (ast_statement_assign_t*) statement->statement;
    char* line;
    char* access_stack = asm_string_access_stack(stack, assign->var.identifier);
    char* right_op;
    lines = generate_expression(lines, &assign->expr, stack, &right_op);

    if (!right_op) {
        free(access_stack);
        return NULL;
    }

    line = generate_asm_mov(access_stack, right_op);

    if (!line) {
        free(right_op);
        free(access_stack);
        free_lines(lines);
        return NULL;
    }

    free(access_stack);
    free(right_op);

    lines = append_line(lines, line);
    CHECK_LINES_RETURN_NULL();
    free(line);

    return lines;
}
