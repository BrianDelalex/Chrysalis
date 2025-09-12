/*******************************************************************\
**
**  This file is part of Chrysalis project, and is made available
**  under the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

# include <stdlib.h>
# include <errno.h>
# include <string.h>

# include "parser/ast_types.h"
# include "parser/operation/ast_operation.h"
# include "parser/operation/rpn_double_chained_list.h"

# include "generator/stack/stack.h"
# include "generator/generator.h"
# include "generator/asm/generate_asm.h"
# include "generator/operation/operation.h"

# include "utils/logging.h"
# include "utils/string_manipulation.h"

# include "attributes.h"

static char* generate_expr_integer_literal(ast_operand_integer_integral_t* operand)
{
    char* op = generate_integer_literal(operand->value);

    if (!op) {
        return NULL;
    }

    return op;
}

/*
 * Create asm instruction to put the value of 'identifier' into accumulator register and return accumulator register name in expr_str.
 */
static char** generate_expr_identifier(char** lines, ast_operand_identifier_t* identifier, ast_stack_t* stack, char** expr_str)
{
    char* access_stack = asm_string_access_stack(stack, identifier->identifier);
    const char* reg = ast_get_accumulator_register_from_size(stack, identifier->identifier);
    char* line = generate_asm_mov(reg, access_stack);

    if (!line) {
        free(access_stack);
        return NULL;
    }

    free(access_stack);
    lines = append_line(lines, line);
    free(line);
    *expr_str = copy_string(reg);
    return lines;
}

static char** generate_expr_operation(UNUSED char** lines, ast_operation_t* expr, ast_stack_t* stack, UNUSED char**expr_str)
{
    *expr_str = NULL;
    if (minimize_operation(expr) != 0) {
        PERR("Error while minimizing operation.\n");
        return NULL;
    }

    if (!expr->rpn_list->next) {
        *expr_str = generate_integer_literal(expr->rpn_list->data.value);
        return lines;
    }

    rpn_double_chained_list_t* operand1 = rpn_double_list_pop_front(&(expr->rpn_list));
    char *operand1_asm_str;
    if (operand1->token == OPERAND_INT) {
        operand1_asm_str = generate_integer_literal(operand1->data.value);
    } else {
        operand1_asm_str = asm_string_access_stack(stack, operand1->data.identifier);
    }
    char *line = generate_asm_mov("eax", operand1_asm_str);
    if (operand1->token == OPERAND_IDENTIFIER)
        free(operand1->data.identifier);
    free(operand1);
    free(operand1_asm_str);
    lines = append_line(lines, line);
    free(line);
    CHECK_LINES_RETURN_NULL();

    while (expr->rpn_list) {
        rpn_double_chained_list_t* operand2 = rpn_double_list_pop_front(&(expr->rpn_list));
        rpn_double_chained_list_t* operator = rpn_double_list_pop_front(&(expr->rpn_list));
        if (operator->token == OPERATOR && ((char)operator->data.value) == '+') {
            char* operand2_asm_str;
            if (operand2->token == OPERAND_INT) {
                operand2_asm_str = generate_integer_literal(operand2->data.value);
            } else {
                operand2_asm_str = asm_string_access_stack(stack, operand2->data.identifier);
            }
            if (operand2->token == OPERAND_IDENTIFIER)
                free(operand2->data.identifier);
            free(operand2);
            line = generate_asm_add("eax", operand2_asm_str);
            free(operand2_asm_str);
            lines = append_line(lines, line);
            free(line);
            CHECK_LINES_RETURN_NULL();
        }
        free(operator);
    }
    *expr_str = copy_string("eax");

    return lines;
}

char** generate_expression(char** lines, ast_expr_t* expr, ast_stack_t* stack, char** expr_str);
char** generate_expression(char** lines, ast_expr_t* expr, ast_stack_t* stack, char** expr_str)
{
    switch (expr->op.type) {
    case OP_IDENTIFIER:
        return generate_expr_identifier(lines, ((ast_operand_identifier_t*)expr->op.operand), stack, expr_str);
    case OP_INTEGER_LITERAL:
        *expr_str = generate_expr_integer_literal((ast_operand_integer_integral_t*)expr->op.operand);
        return lines;
    case OP_OPERATION:
        return generate_expr_operation(lines, ((ast_operation_t*)expr->op.operand), stack, expr_str);
        break;
    default:
        PERR("Unexpected operation type: %d\n", expr->op.type);
        return NULL;
    }
    return NULL;
}
