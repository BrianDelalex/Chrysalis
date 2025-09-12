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

# include "utils/logging.h"

static const char ASM_RET_STR[] = "    ret\n\n";

char** generate_expression(char** lines, ast_expr_t* expr, ast_stack_t* stack, char** expr_str);

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
        line = generate_asm_mov(reg, access_stack);

        if (!line) {
            free(access_stack);
            free_lines(lines);
            return NULL;
        }

        free(access_stack);
    } else {
        char* value;
        lines = generate_expression(lines, &rtn_statement->expr, stack, &value);

        if (!value) {
            free_lines(lines);
            return NULL;
        }
        line = generate_asm_mov("rax", value);
        free(value);
        if (!line) {
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
