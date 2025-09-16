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

# include "utils/string_array.h"

bool generate_assignment_statement(gen_func_data_t* data, ast_statement_t* statement)
{
    ast_statement_assign_t* assign = (ast_statement_assign_t*) statement->statement;
    char* line;
    char* access_stack = asm_string_access_stack(data->stack, assign->var.identifier);
    char* right_op;
    if (!generate_expression(data, &assign->expr, &right_op)) {
        free(access_stack);
        return false;
    }

    line = generate_asm_mov(access_stack, right_op);

    if (!line) {
        free(right_op);
        free(access_stack);
        string_array_free(data->gen_data->file);
        return NULL;
    }

    free(access_stack);
    free(right_op);

    if (!append_line_to_file(data->gen_data, line)) {
        free(line);
        return false;
    }

    free(line);

    return true;
}
