/*******************************************************************\
**
**  This file is part of Chrysalis project, and is made available
**  under the terms of the GNU General Public License version 3.
**
**  Copyright (C) 2025 - Brian DELALEX-FONDU
**
\*******************************************************************/

# include <stdlib.h>

# include "generator/expression.h"
# include "generator/stack/stack.h"
# include "generator/asm/generate_asm.h"
# include "generator/statement.h"

# include "utils/logging.h"
# include "utils/string_array.h"

static const char ASM_RET_STR[] = "    ret\n\n";

static bool generate_return_statement_identifier(gen_func_data_t* data, ast_statement_return_t* statement)
{
    char* identifier = ((ast_operand_identifier_t*)statement->expr.op.operand)->identifier;
    char* access_stack = asm_string_access_stack(data->stack, identifier);
    char** file = data->gen_data->file;
    char* line;
    const char* reg = ast_get_accumulator_register_from_size(data->stack, identifier);

    if (!access_stack) {
        string_array_free(file);
        return false;
    }

    line = generate_asm_mov(reg, access_stack);
    if (!line) {
        free(access_stack);
        string_array_free(file);
        return false;
    }
    free(access_stack);

    bool status = append_line_to_file(data->gen_data, line);
    free(line);
    return status;
}

static bool generate_return_statement_int_literal(gen_func_data_t* data, ast_statement_return_t* statement)
{
    char* value;
    char* line;
    if (!generate_expression(data, &statement->expr, &value)) {
        return false;
    }

    if (!value) {
        string_array_free(data->gen_data->file);
        return false;
    }

    line = generate_asm_mov("rax", value);
    free(value);
    if (!line) {
        string_array_free(data->gen_data->file);
        return false;
    }

    bool status = append_line_to_file(data->gen_data, line);
    free(line);
    return status;
}

static bool generate_return_statement_operation(gen_func_data_t* data, ast_statement_return_t* statement)
{
    char* line;
    char* value;
    bool status = true;
    if (!generate_expression(data, &statement->expr, &value)) {
        return false;
    }
    if (!value) {
        return false;
    }

    if (strcmp(value, "eax") != 0) {
        line = generate_asm_mov("eax", value);
        if (!line) {
            free(value);
            string_array_free(data->gen_data->file);
            return NULL;
        }
        status = append_line_to_file(data->gen_data, line);
        free(line);
    }
    free(value);
    return status;
}

bool generate_return_statement(gen_func_data_t* data, ast_statement_t* statement)
{
    ast_statement_return_t *rtn_statement = (ast_statement_return_t*) statement->statement;

    switch (rtn_statement->expr.op.type) {
    case OP_IDENTIFIER:
         if (!generate_return_statement_identifier(data, rtn_statement))
            return false;
        break;
    case OP_INTEGER_LITERAL:
        if (!generate_return_statement_int_literal(data, rtn_statement))
            return false;
        break;
    case OP_OPERATION:
        if (!generate_return_statement_operation(data, rtn_statement))
            return false;
        break;
    default:
        PERR("Unknow statement type: %d\n", rtn_statement->expr.op.type);
        string_array_free(data->gen_data->file);
        return false;
    }

    if (!generate_stack_restore(data->gen_data))
        return false;
    if (!append_line_to_file(data->gen_data, ASM_RET_STR))
        return false;

    return true;
}
