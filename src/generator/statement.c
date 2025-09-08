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

# include "utils/logging.h"

static char** generate_return_statement(char** lines, ast_statement_t* statement, ast_stack_t* stack)
{
    ast_statement_return_t *rtn_statement = (ast_statement_return_t*) statement->statement;
    char* line;

    if (rtn_statement->expr.op.type == OP_IDENTIFIER) {
        char *identifier = ((ast_operand_identifier_t*)rtn_statement->expr.op.operand)->identifier;
        char *access_stack = asm_string_access_stack(stack, identifier);

        if (!access_stack)
            return NULL;

        int line_size = snprintf(NULL, 0, RETURN_IDENTIFIER_STATEMENT, access_stack);
        line = malloc(sizeof(char) * (line_size + 1));
        if (!line) {
            PERR(OUT_OF_MEM);
            return NULL;
        }

        if (snprintf(line, line_size + 1, RETURN_IDENTIFIER_STATEMENT, access_stack) < 0) {
            PERR("%s", strerror(errno));
            free(access_stack);
            return NULL;
        }
        free(access_stack);
    } else {
        int value = ((ast_operand_integer_integral_t*)rtn_statement->expr.op.operand)->value;
        int line_size = snprintf(NULL, 0, RETURN_INT_STATEMENT, value);
        line = malloc(sizeof(char) * (line_size + 1));
        if (!line) {
            PERR(OUT_OF_MEM);
            return NULL;
        }

        if (snprintf(line, line_size + 1, RETURN_INT_STATEMENT, value) < 0) {
            PERR("%s", strerror(errno));
            return NULL;
        }
    }
    lines = append_line(lines, line);
    CHECK_LINES_RETURN_NULL();
    free(line);

    return lines;
}

static char** generate_assignment_statement(char** lines, ast_statement_t* statement, ast_stack_t* stack)
{
    ast_statement_assign_t* assign = (ast_statement_assign_t*) statement->statement;
    (void)assign;
    (void)lines;
    (void)statement;
    (void)stack;
    PERR("TODO - generate assignment. (first var need to be register on the stack in the parser).");
    return NULL;
}

char** generate_statement(char** lines, ast_statement_t* statement, ast_stack_t* stack)
{
    switch (statement->type) {
    case RETURN:
        return generate_return_statement(lines, statement, stack);
    case ASSIGN:
        return generate_assignment_statement(lines, statement, stack);
    default:
        PERR("Unknow statement type.\n");
        return NULL;
    }
}
