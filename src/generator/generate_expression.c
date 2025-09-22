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
# include "parser/expression/function_call.h"
# include "parser/operation/rpn_double_chained_list.h"

# include "generator/stack/stack.h"
# include "generator/generator.h"
# include "generator/asm/generate_asm.h"
# include "generator/operation/operation.h"
# include "generator/statement.h"

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
static bool generate_expr_identifier(gen_func_data_t* data, ast_operand_identifier_t* identifier, char** expr_str)
{
    char* access_stack = asm_string_access_stack(data->stack, identifier->identifier);
    char* reg_dest;
    if (*expr_str) {
        reg_dest = copy_string(*expr_str);
    } else {
        reg_dest = copy_string(ast_get_accumulator_register_from_size(data->stack, identifier->identifier));
    }


    char* line = generate_asm_mov(reg_dest, access_stack);

    if (!line) {
        free(access_stack);
        return false;
    }

    free(access_stack);
    if (!append_line_to_file(data->gen_data, line)) {
        free(line);
        return false;
    }
    free(line);
    *expr_str = reg_dest;
    return true;
}

static bool generate_expr_operation(gen_func_data_t* data, ast_operation_t* expr, char**expr_str)
{
    char *reg_dest;
    if (*expr_str) {
        reg_dest = copy_string(*expr_str);
    } else {
        reg_dest = copy_string("eax");
    }
    if (minimize_operation(expr) != 0) {
        PERR("Error while minimizing operation.\n");
        free(reg_dest);
        return false;
    }

    if (!expr->rpn_list->next) {
        *expr_str = generate_integer_literal(expr->rpn_list->data.value);
        free(reg_dest);
        return true;
    }

    rpn_double_chained_list_t* operand1 = rpn_double_list_pop_front(&(expr->rpn_list));
    char *operand1_asm_str;
    if (operand1->token == OPERAND_INT) {
        operand1_asm_str = generate_integer_literal(operand1->data.value);
    } else {
        operand1_asm_str = asm_string_access_stack(data->stack, operand1->data.identifier);
    }
    char *line = generate_asm_mov(reg_dest, operand1_asm_str);
    if (operand1->token == OPERAND_IDENTIFIER)
        free(operand1->data.identifier);
    free(operand1);
    free(operand1_asm_str);
    if (!append_line_to_file(data->gen_data, line)) {
        free(line);
        free(reg_dest);
        return false;
    }
    free(line);

    while (expr->rpn_list) {
        rpn_double_chained_list_t* operand2 = rpn_double_list_pop_front(&(expr->rpn_list));
        rpn_double_chained_list_t* operator = rpn_double_list_pop_front(&(expr->rpn_list));
        if (operator->token == OPERATOR && ((char)operator->data.value) == '+') {
            char* operand2_asm_str;
            if (operand2->token == OPERAND_INT) {
                operand2_asm_str = generate_integer_literal(operand2->data.value);
            } else {
                operand2_asm_str = asm_string_access_stack(data->stack, operand2->data.identifier);
            }
            if (operand2->token == OPERAND_IDENTIFIER)
                free(operand2->data.identifier);
            free(operand2);
            line = generate_asm_add(reg_dest, operand2_asm_str);
            free(operand2_asm_str);
            if (!append_line_to_file(data->gen_data, line)) {
                free(line);
                free(reg_dest);
                return false;
            }
            free(line);
        }
        free(operator);
    }
    *expr_str = reg_dest;

    return true;
}

static bool generate_arg_setup(gen_func_data_t* data, expr_list_t arg, int arg_index)
{
    char* args_dest[] = {"edi", "esi", "edx", "r10d", "r8d", "r9d"};
    char *reg = args_dest[arg_index];

    switch (arg.expr.op.type) {
    case OP_IDENTIFIER:
        if (!generate_expr_identifier(data, (ast_operand_identifier_t*)arg.expr.op.operand, &reg))
            return false;
        free(reg);
        return true;
    case OP_INTEGER_LITERAL:
        char* value = generate_integer_literal(((ast_operand_integer_integral_t*)arg.expr.op.operand)->value);
        if (!value)
            return false;
        char* mov = generate_asm_mov(reg, value);
        if (!mov) {
            free(value);
            return false;
        }
        free(value);
        if (!append_line_to_file(data->gen_data, mov)) {
            free(mov);
            return false;
        }
        free(mov);
        return true;
    case OP_OPERATION:
        if (!generate_expr_operation(data, (ast_operation_t*)arg.expr.op.operand, &reg)) {
            return false;
        }
        if (strcmp(reg, args_dest[arg_index]) != 0) {
            char *mov = generate_asm_mov(args_dest[arg_index], reg);
            if (!mov) {
                free(reg);
                return false;
            }
            if (!append_line_to_file(data->gen_data, mov)) {
                free(reg);
                return false;
            }
        }
        free(reg);
        return true;
    default:
        PERR("Unknow operand type %d\n", arg.expr.op.type);
        return false;
    }
}

static bool generate_expr_function_call(gen_func_data_t* data, ast_function_call_t* expr, char** expr_str)
{
    expr_list_t* args = expr->args;
    int args_count = 0;

    while (args) {
        if (!generate_arg_setup(data, *args, args_count)) {
            return false;
        }
        args_count++;
        args = args->next;
    }

    char* func_call = generate_asm_func_call(expr->func_name);
    if (!append_line_to_file(data->gen_data, func_call)) {
        free(func_call);
        return false;
    }
    *expr_str = copy_string("eax");

    return true;
}

bool generate_expression(gen_func_data_t* data, ast_expr_t* expr, char** expr_str);
bool generate_expression(gen_func_data_t* data, ast_expr_t* expr, char** expr_str)
{
    switch (expr->op.type) {
    case OP_IDENTIFIER:
        return generate_expr_identifier(data, ((ast_operand_identifier_t*)expr->op.operand), expr_str);
    case OP_INTEGER_LITERAL:
        *expr_str = generate_expr_integer_literal((ast_operand_integer_integral_t*)expr->op.operand);
        return (*expr_str != NULL);
    case OP_OPERATION:
        return generate_expr_operation(data, ((ast_operation_t*)expr->op.operand), expr_str);
        break;
    case OP_FUNC_CALL:
        return generate_expr_function_call(data, ((ast_function_call_t*)expr->op.operand), expr_str);
    default:
        PERR("Unexpected operation type: %d\n", expr->op.type);
        return NULL;
    }
    return NULL;
}
