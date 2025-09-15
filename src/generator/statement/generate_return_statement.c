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
# include "generator/expression.h"
# include "generator/stack/stack.h"
# include "generator/asm/generate_asm.h"
# include "generator/statement.h"

# include "utils/logging.h"

static const char ASM_RET_STR[] = "    ret\n\n";

static char** generate_return_statement_identifier(char** lines, ast_statement_return_t* statement, ast_stack_t* stack, char** line)
{
    char* identifier = ((ast_operand_identifier_t*)statement->expr.op.operand)->identifier;
    char* access_stack = asm_string_access_stack(stack, identifier);
    const char* reg = ast_get_accumulator_register_from_size(stack, identifier);

    if (!access_stack) {
        free_lines(lines);
        return NULL;
    }

    *line = generate_asm_mov(reg, access_stack);
    if (!(*line)) {
        free(access_stack);
        free_lines(lines);
        return NULL;
    }
    free(access_stack);
    return lines;
}

static char** generate_return_statement_int_literal(char** lines, ast_statement_return_t* statement, ast_stack_t* stack, char** line)
{
    char* value;
    lines = generate_expression(lines, &statement->expr, stack, &value);

    if (!value) {
        free_lines(lines);
        return NULL;
    }

    *line = generate_asm_mov("rax", value);
    free(value);
    if (!(*line)) {
        free_lines(lines);
        return NULL;
    }
    return lines;
}

static char** generate_return_statement_operation(char** lines, ast_statement_return_t* statement, ast_stack_t* stack, char** line)
{
    char* value;
    lines = generate_expression(lines, &statement->expr, stack, &value);
    if (!value) {
        return NULL;
    }

    if (strcmp(value, "eax") != 0) {
        *line = generate_asm_mov("eax", value);
        if (!(*line)) {
            free(value);
            free_lines(lines);
            return NULL;
        }
    } else {
        *line = NULL;
    }
    free(value);
    return lines;
}

char** generate_return_statement(char** lines, ast_statement_t* statement, ast_stack_t* stack)
{
    ast_statement_return_t *rtn_statement = (ast_statement_return_t*) statement->statement;
    char* line;

    switch (rtn_statement->expr.op.type) {
    case OP_IDENTIFIER:
        lines = generate_return_statement_identifier(lines, rtn_statement, stack, &line);
        break;
    case OP_INTEGER_LITERAL:
        lines = generate_return_statement_int_literal(lines, rtn_statement, stack, &line);
        break;
    case OP_OPERATION:
        lines = generate_return_statement_operation(lines, rtn_statement, stack, &line);
        break;
    default:
        PERR("Unknow statement type: %d\n", rtn_statement->expr.op.type);
        free_lines(lines);
        return NULL;
    }
    CHECK_LINES_RETURN_NULL();

    if (line) {
        lines = append_line(lines, line);
        CHECK_LINES_RETURN_NULL();
    }
    lines = generate_stack_restore(lines);
    CHECK_LINES_RETURN_NULL();
    lines = append_line(lines, ASM_RET_STR);
    CHECK_LINES_RETURN_NULL();

    free(line);

    return lines;
}
