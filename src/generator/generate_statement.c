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

static const char ASM_RET_STR[] = "    ret\n\n";

static char** generate_return_statement(char** lines, ast_statement_t* statement, ast_stack_t* stack)
{
    ast_statement_return_t *rtn_statement = (ast_statement_return_t*) statement->statement;
    char* line;

    if (rtn_statement->expr.op.type == OP_IDENTIFIER) {
        char* identifier = ((ast_operand_identifier_t*)rtn_statement->expr.op.operand)->identifier;
        char* access_stack = asm_string_access_stack(stack, identifier);
        const char* reg = ast_get_accumulator_register_from_size(stack, identifier);

        if (!access_stack) {
            free_lines(lines);
            return NULL;
        }

        int line_size = snprintf(NULL, 0, RETURN_IDENTIFIER_STATEMENT, reg, access_stack);
        line = malloc(sizeof(char) * (line_size + 1));
        if (!line) {
            PERR(OUT_OF_MEM);
            free_lines(lines);
            return NULL;
        }

        if (snprintf(line, line_size + 1, RETURN_IDENTIFIER_STATEMENT, reg, access_stack) < 0) {
            PERR("%s", strerror(errno));
            free(access_stack);
            free_lines(lines);
            return NULL;
        }
        free(access_stack);
    } else {
        int value = ((ast_operand_integer_integral_t*)rtn_statement->expr.op.operand)->value;
        int line_size = snprintf(NULL, 0, RETURN_INT_STATEMENT, value);
        line = malloc(sizeof(char) * (line_size + 1));
        if (!line) {
            PERR(OUT_OF_MEM);
            free_lines(lines);
            return NULL;
        }

        if (snprintf(line, line_size + 1, RETURN_INT_STATEMENT, value) < 0) {
            PERR("%s", strerror(errno));
            free_lines(lines);
            return NULL;
        }
    }

    lines = append_line(lines, line);
    CHECK_LINES_RETURN_NULL();
    lines = generate_stack_restore(lines);
    CHECK_LINES_RETURN_NULL();
    lines = append_line(lines, ASM_RET_STR);
    CHECK_LINES_RETURN_NULL();

    free(line);

    return lines;
}

static char** generate_assignment_statement(char** lines, ast_statement_t* statement, ast_stack_t* stack)
{
    ast_statement_assign_t* assign = (ast_statement_assign_t*) statement->statement;
    char* line;

    char* identifier = assign->var.identifier;
    char* access_stack = asm_string_access_stack(stack, identifier);
    int right_op = ((ast_operand_integer_integral_t*)assign->expr.op.operand)->value;

    int line_size = snprintf(NULL, 0, ASSIGN_STATEMENT_INTEGER_LITERAL, access_stack, right_op);
    line = malloc(sizeof(char) * (line_size + 1));
    if (!line) {
        PERR(OUT_OF_MEM);
        free(access_stack);
        free_lines(lines);
        return NULL;
    }
    if (snprintf(line, line_size + 1, ASSIGN_STATEMENT_INTEGER_LITERAL, access_stack, right_op) < 0) {
        PERR("%s", strerror(errno));
        free(access_stack);
        free_lines(lines);
        return NULL;
    }

    free(access_stack);

    lines = append_line(lines, line);
    CHECK_LINES_RETURN_NULL();
    free(line);

    return lines;
}

char** generate_statement(char** lines, ast_statement_t* statement, ast_stack_t* stack)
{
    ast_statement_t* ptr = statement;
    while (ptr) {
        switch (ptr->type) {
            case RETURN:
                lines = generate_return_statement(lines, ptr, stack);
                break;
            case ASSIGN:
                lines = generate_assignment_statement(lines, ptr, stack);
                break;
            default:
                free_lines(lines);
                PERR("Unknow statement type.\n");
                return NULL;
        }
        ptr = ptr->next;
    }

    return lines;
}
